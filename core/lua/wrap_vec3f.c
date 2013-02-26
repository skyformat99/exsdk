// ======================================================================================
// File         : wrap_vec3f.c
// Author       : Wu Jie 
// Last Change  : 02/26/2013 | 09:27:11 AM | Tuesday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_new ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,3);

    p = ex_malloc ( sizeof(ex_vec3f_t) );
    ex_vec3f_set ( (ex_vec3f_t *)p, 
                   (float)luaL_checknumber(_l,1), 
                   (float)luaL_checknumber(_l,2),
                   (float)luaL_checknumber(_l,3)
                 );

    lua_pushlightuserdata ( _l, p );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_delete ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    ex_free(p);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_get_x ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    lua_pushnumber( _l, ((ex_vec3f_t *)p)->x );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_get_y ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    lua_pushnumber( _l, ((ex_vec3f_t *)p)->y );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_get_z ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    lua_pushnumber( _l, ((ex_vec3f_t *)p)->z );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_set_x ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    ((ex_vec3f_t *)p)->x = (float)luaL_checknumber(_l,2);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_set_y ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    ((ex_vec3f_t *)p)->y = (float)luaL_checknumber(_l,2);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_set_z ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    ((ex_vec3f_t *)p)->z = (float)luaL_checknumber(_l,2);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_add ( lua_State *_l ) {
    void *r, *v1, *v2;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    luaL_checktype( _l, 3, LUA_TLIGHTUSERDATA );
    v2 = lua_touserdata(_l,3);

    ex_vec3f_add ( r, v1, v2 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_sub ( lua_State *_l ) {
    void *r, *v1, *v2;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    luaL_checktype( _l, 3, LUA_TLIGHTUSERDATA );
    v2 = lua_touserdata(_l,3);

    ex_vec3f_sub ( r, v1, v2 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_mul ( lua_State *_l ) {
    void *r, *v1, *v2;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    luaL_checktype( _l, 3, LUA_TLIGHTUSERDATA );
    v2 = lua_touserdata(_l,3);

    ex_vec3f_mul ( r, v1, v2 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_mul_scalar ( lua_State *_l ) {
    void *r, *v1;
    float s;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    s = (float)luaL_checknumber(_l,3);

    ex_vec3f_mul_scalar ( r, v1, s );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_div ( lua_State *_l ) {
    void *r, *v1, *v2;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    luaL_checktype( _l, 3, LUA_TLIGHTUSERDATA );
    v2 = lua_touserdata(_l,3);

    ex_vec3f_div ( r, v1, v2 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_div_scalar ( lua_State *_l ) {
    void *r, *v1;
    float s;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    s = (float)luaL_checknumber(_l,3);

    ex_vec3f_div_scalar ( r, v1, s );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_scalar_div_vec3f ( lua_State *_l ) {
    void *r, *v1;
    float s;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    s = (float)luaL_checknumber(_l,2);

    luaL_checktype( _l, 3, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,3);

    ex_scalar_div_vec3f ( r, s, v1 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_neg ( lua_State *_l ) {
    void *r, *v1;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    ex_vec3f_get_neg ( r, v1 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_eq ( lua_State *_l ) {
    void *v1, *v2;
    bool r;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v2 = lua_touserdata(_l,2);

    r = ex_vec3f_is_equal ( v1, v2 );
    lua_pushboolean(_l,r);

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_normalize ( lua_State *_l ) {
    void *v1;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,1);

    ex_vec3f_normalize(v1);

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_get_normalize ( lua_State *_l ) {
    void *v1, *v2;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v2 = lua_touserdata(_l,2);

    ex_vec3f_get_normalize(v1,v2);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_len ( lua_State *_l ) {
    void *v1;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,1);

    lua_pushnumber( _l, ex_vec3f_len(v1) );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_lenSQR ( lua_State *_l ) {
    void *v1;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,1);

    lua_pushnumber( _l, ex_vec3f_lenSQR(v1) );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec3f_lerp ( lua_State *_l ) {
    ex_vec3f_t *v1, *v2;
    void *r;
    float t, x, y, z;

    ex_lua_check_nargs(_l,4);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = (ex_vec3f_t *)lua_touserdata(_l,2);

    luaL_checktype( _l, 3, LUA_TLIGHTUSERDATA );
    v2 = (ex_vec3f_t *)lua_touserdata(_l,3);

    t = (float)luaL_checknumber(_l,4);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = (ex_vec3f_t *)lua_touserdata(_l,1);

    // lerp
    x = ex_lerpf ( v1->x, v2->x, t );
    y = ex_lerpf ( v1->y, v2->y, t );
    z = ex_lerpf ( v1->z, v2->z, t );

    ex_vec3f_set ( (ex_vec3f_t *)r, x, y, z );
    lua_pushlightuserdata ( _l, r );

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "vec3f_new",              __lua_vec3f_new },
    { "vec3f_delete",           __lua_vec3f_delete },
    { "vec3f_get_x",            __lua_vec3f_get_x },
    { "vec3f_get_y",            __lua_vec3f_get_y },
    { "vec3f_get_z",            __lua_vec3f_get_z },
    { "vec3f_set_x",            __lua_vec3f_set_x },
    { "vec3f_set_y",            __lua_vec3f_set_y },
    { "vec3f_set_z",            __lua_vec3f_set_z },
    { "vec3f_add",              __lua_vec3f_add },
    { "vec3f_sub",              __lua_vec3f_sub },
    { "vec3f_mul",              __lua_vec3f_mul },
    { "vec3f_mul_scalar",       __lua_vec3f_mul_scalar },
    { "vec3f_div",              __lua_vec3f_div },
    { "vec3f_div_scalar",       __lua_vec3f_div_scalar },
    { "scalar_div_vec3f",       __lua_scalar_div_vec3f },
    { "vec3f_neg",              __lua_vec3f_neg },
    { "vec3f_eq",               __lua_vec3f_eq },
    { "vec3f_normalize",        __lua_vec3f_normalize },
    { "vec3f_get_normalize",    __lua_vec3f_get_normalize },
    { "vec3f_len",              __lua_vec3f_len },
    { "vec3f_lenSQR",           __lua_vec3f_lenSQR },
    { "vec3f_lerp",             __lua_vec3f_lerp },
    { NULL, NULL }
};

int __ex_lua_add_vec3f ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
