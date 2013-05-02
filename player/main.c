// ======================================================================================
// File         : main.c
// Author       : Wu Jie 
// Last Change  : 01/05/2013 | 17:44:08 PM | Saturday,January
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "allegro5/allegro.h"
#include "exsdk.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#if ( EX_PLATFORM == EX_MACOSX )
    #define main _al_mangled_main
#endif

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

ALLEGRO_DISPLAY *primary_display = NULL;
static ex_array_t *__display_list = NULL;
ALLEGRO_EVENT_QUEUE *queue = NULL;

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ALLEGRO_DISPLAY *create_window ( int _w, int _h ) {
    ALLEGRO_DISPLAY *display;

    // init allegro display
    al_set_new_display_flags( ALLEGRO_OPENGL
                            | ALLEGRO_RESIZABLE
                            | ALLEGRO_GENERATE_EXPOSE_EVENTS
                            // | ALLEGRO_FRAMELESS
                            );
    display = al_create_display( _w, _h );
    if ( !display ) {
        ex_log ( "Could not create allegro display!" );
        exit(1);
    }

    // if this is the first window, create queue
    if ( ex_array_count(__display_list) == 0 ) {
        queue = al_create_event_queue();
        primary_display = display;
    }
    ex_array_add ( __display_list, &display );

    al_register_event_source(queue, al_get_display_event_source(display));

    return display;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void destroy_window ( ALLEGRO_DISPLAY *_display ) {
    int i = 0;
    lua_State *l;

    l = ex_lua_main_state();

    // call editor.window.on_destroy(_display)
    lua_getglobal ( l, "editor" );
    lua_getfield ( l, -1, "window" );
    lua_getfield ( l, -1, "on_destroy" );
    lua_pushlightuserdata ( l, _display );
    lua_pcall ( l, 1, 0, 0 );
    lua_pop ( l, 2 );

    //
    while ( i < ex_array_count(__display_list) ) {
        if ( *(ALLEGRO_DISPLAY **)ex_array_get(__display_list, i) == _display ) {
            ex_array_remove_at_fast ( __display_list, i );
            break;
        }
        ++i;
    }
    al_destroy_display(_display);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int process_event ( ALLEGRO_EVENT _event ) {
    lua_State *l;
    bool do_broadcast;

    l = ex_lua_main_state();
    do_broadcast = false;

    // clean the event type
    // editor.sys_event.type = event_type.none
    lua_getglobal( l, "editor" );
    lua_getfield( l, -1, "sys_event" );
    lua_getglobal( l, "event_type" );
    lua_getfield( l, -1, "none" );
    lua_setfield( l, -3, "type" );
    lua_pop (l,3);

    //
    switch ( _event.type ) {
    case ALLEGRO_EVENT_DISPLAY_RESIZE:
        al_acknowledge_resize(_event.display.source);
        break;

    case ALLEGRO_EVENT_DISPLAY_EXPOSE:
        break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        // if we are close the primary display, quit the app
        if ( _event.display.source == primary_display )
            return 1;

        destroy_window (_event.display.source);

        if ( ex_array_count (__display_list) == 0 )
            return 1;
        break;

    case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
        // ex_log("%p switching in\n", _event.display.source);
        break;

    case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
        // ex_log("%p switching out\n", _event.display.source);
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        lua_getglobal( l, "editor" );
        lua_getfield( l, -1, "sys_event" );

            // set event_type.type
            lua_getglobal( l, "event_type" );
            lua_getfield( l, -1, "key_down" );
            lua_setfield( l, -3, "type" );
            lua_pop (l,1);

            // set event_type.display
            lua_pushlightuserdata( l, _event.keyboard.display );
            lua_setfield( l, -2, "display" );

            // set event_type.keycode
            lua_pushinteger( l, _event.keyboard.keycode );
            lua_setfield( l, -2, "keycode" );

        lua_pop (l,2);

        do_broadcast = true;
        break;

    case ALLEGRO_EVENT_KEY_UP:
        lua_getglobal( l, "editor" );
        lua_getfield( l, -1, "sys_event" );

            // set event_type.type
            lua_getglobal( l, "event_type" );
            lua_getfield( l, -1, "key_up" );
            lua_setfield( l, -3, "type" );
            lua_pop (l,1);

            // set event_type.display
            lua_pushlightuserdata( l, _event.keyboard.display );
            lua_setfield( l, -2, "display" );

            // set event_type.keycode
            lua_pushinteger( l, _event.keyboard.keycode );
            lua_setfield( l, -2, "keycode" );

        lua_pop (l,2);

        do_broadcast = true;
        break;
    }

    // call editor.window.on_event(editor.sys_event)
    if ( do_broadcast ) {
        lua_getglobal ( l, "editor" );
        lua_getfield ( l, -1, "window" );
        lua_getfield ( l, -1, "on_event" );
        lua_getfield ( l, -3, "sys_event" );
        lua_pcall ( l, 1, 0, 0 );
        lua_pop ( l, 2 );
    }

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void event_loop () {
    ALLEGRO_EVENT event;
    lua_State *l;
    ALLEGRO_BITMAP *target;

    l = ex_lua_main_state();

    // init allegro keyboard
    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());

    // NOTE: there is two ways for update, using Timer or using Event-Poll, 
    // the timer is suitable for GUI tool, and Event-Poll is better for game

    // start main-loop
    while (1) {
        // call app.on_update()
        ex_lua_app_on_update (l);

        // handle events
        while ( !al_is_event_queue_empty(queue) ) {
            al_get_next_event(queue, &event);
            if ( process_event(event) ) {
                goto done;
            }
        }

        // draw one frame
        ex_array_each ( __display_list, ALLEGRO_DISPLAY *, display )
            target = al_get_backbuffer(display);
            al_set_target_bitmap(target);

            // call app.on_draw()
            ex_lua_app_on_draw (l);
        ex_array_each_end

        al_rest(0.001);
    }

    // finish
done:
    // call app.on_exit()
    ex_lua_app_on_exit (l);
    al_destroy_event_queue(queue);  
}

// ------------------------------------------------------------------ 
// Desc: 
extern int __ex_lua_add_player ( lua_State * );
// ------------------------------------------------------------------ 

static void __app_init ( int _argc, char **_argv ) {
    lua_State *l = ex_lua_main_state();

    // push arguments to app.arguments in lua
    ex_lua_app_init ( l, _argc, _argv );

    //
    __display_list = ex_array_alloc ( sizeof(ALLEGRO_DISPLAY *), 8 );

    // add player builtin libs to ex_c
    lua_getglobal(l, "ex_c"); /* get ex_c table */
        __ex_lua_add_player (l);
    lua_pop(l, 1);  /* remove ex_c table */

    // execute main.lua if exists  
    if ( ex_fsys_exists ("main.lua") )
        ex_lua_dofile ( l, "main.lua" );
} 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __app_deinit () {
    ex_array_free ( __display_list );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int main ( int _argc, char **_argv ) {
    lua_State *l;

    // ======================================================== 
    // init 
    // ======================================================== 

    // init exsdk ( including allegro ) 
    if ( ex_sdk_init() != 0 ) {
        ex_log ( "Could not init exsdk!" );
        return 1;
    }

    l = ex_lua_main_state();

    // load builtin modules
    ex_log ( "[exSDK] Loading builtin modules" );
    ex_lua_dofile ( l, "builtin/modules/init.lua" );

    // init app
    __app_init ( _argc, _argv );

    // ======================================================== 
    // loop 
    // ======================================================== 

    // enter the event-loop if we create display(window) 
    if ( ex_array_count (__display_list) > 0 ) {
        event_loop ();
    }

    // ======================================================== 
    // de-init 
    // ======================================================== 

    // deinit app 
    __app_deinit();

    // deinit exsdk 
    ex_sdk_deinit ();

    return 0;
}

