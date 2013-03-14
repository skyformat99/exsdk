// ======================================================================================
// File         : renderer.c
// Author       : Wu Jie 
// Last Change  : 03/12/2013 | 16:21:54 PM | Tuesday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// static
///////////////////////////////////////////////////////////////////////////////

#define MEMBLOCK_INIT( _block, _type, _size ) \
    ex_memblock_init ( &_block \
                      , sizeof(_type) \
                      , _size \
                      , ex_func_alloc \
                      , ex_func_realloc \
                      , ex_func_dealloc \
                    )

typedef struct __ui_vertex_t {
   float x, y;
   float u, v;
   float r, g, b, a;
} __ui_vertex_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __reset_ui_state ( ex_ui_state_t *_ui_state ) {
    ui_state.matrix = EX_MAT44F_IDENTITY;
    ui_state.depth = 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __ui_node_cmp ( const void *_a, const void *_b ) {
    int r;
    ex_ui_node_t *node_a, *node_b;
    
    node_a = (ex_ui_node_t *)_a;
    node_b = (ex_ui_node_t *)_b;

    r = node_a->depth - node_b->depth;
    if ( r != 0 ) return r;

    return (uint32)node_a->texture - (uint32)node_b->texture
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline ex_ui_node_t *__request_ui_node ( ex_renderer_t *_renderer ) {
    return ex_mempool_request( &_renderer->ui_node_block, 1 );
}

///////////////////////////////////////////////////////////////////////////////
// renderer op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_renderer_init ( ex_renderer_t *_renderer ) {
    ex_assert ( _renderer->initialized == false );

    if ( _renderer->initialized )
        return -1;

    // init current ui state
    __reset_ui_state (&_renderer->ui_state);

    // create ui node pool
    MEMBLOCK_INIT ( _renderer->ui_node_block, ex_ui_node_t, 512 );
    MEMBLOCK_INIT ( _renderer->ui_vertex_buffer, __ui_vertex_t, 4096 );
    MEMBLOCK_INIT ( _renderer->ui_index_buffer, sizeof(uint16), 4096 );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_renderer_deinit ( ex_renderer_t *_renderer ) {
    ex_assert ( _renderer->initialized );

    if ( _renderer->initialized == false )
        return;

    // destroy ui node pool
    ex_memblock_deinit ( &_renderer->ui_node_block );
    ex_memblock_deinit ( &_renderer->ui_vertex_buffer );

    _renderer->initialized = false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void __flush_ui_vertices ( void *_vertices ) {
}

void __draw_ui_nodes ( ex_renderer_t *_renderer ) {
    ex_ui_node_t *node;
    int i, last_depth;
    void *last_texture;
    __ui_vertex_t *verts;

    float tex_l, tex_t, tex_r, tex_b, w, h, true_w, true_h;
    float dw = sw, dh = sh;
    ALLEGRO_BITMAP_OGL *ogl_bitmap;

    // process ui nodes
    qsort ( _renderer->ui_node_block.data, 
            _renderer->ui_node_block.block_count,
            sizeof(ex_ui_node_t),
            __ui_node_cmp );

    // loop all ui node and draw
    last_texture = NULL;
    for ( i = 0; i < _renderer->ui_node_block.block_count; ++i ) {
        node = (ex_ui_node_t *)ex_memblock_get ( &_renderer->ui_node_block, i );

        // if this is not the first node,
        if ( i != 0 && node->texture != last_texture ) {
            __flush_ui_vertices ( _renderer->ui_vertex_buffer.data );
            ex_memblock_clear(_renderer->ui_vertex_buffer);
        }

        ogl_bitmap = (ALLEGRO_BITMAP_OGL *)node->texture;


        // draw as pure sprite
        if ( node.border.l != 0 
          || node.border.r != 0 
          || node.border.t != 0 
          || node.border.b != 0 ) {

            tex_l = ogl_bitmap->left;
            tex_r = ogl_bitmap->right;
            tex_t = ogl_bitmap->top;
            tex_b = ogl_bitmap->bottom;

            w = bitmap->w;
            h = bitmap->h;
            true_w = ogl_bitmap->true_w;
            true_h = ogl_bitmap->true_h;

            tex_l += sx / true_w;
            tex_t -= sy / true_h;
            tex_r -= (w - sx - sw) / true_w;
            tex_b += (h - sy - sh) / true_h;

            // ui_vertex_buffer
            verts = (__ui_vertex_t *)ex_memblock_request ( &_renderer->ui_vertex_buffer, 6 );
        }

        // draw as border sprite
        else {
        }

        last_texture = node->texture;
    }

    // if we still have verices remain, flush it at the end
    if ( ex_memblock_count (_renderer->ui_vertex_buffer) > 0 ) {
        __flush_ui_vertices ( _renderer->ui_vertex_buffer.data );
        ex_memblock_clear(_renderer->ui_vertex_buffer);
    }
}

void ex_renderer_draw_nodes ( ex_renderer_t *_renderer ) {
    // TODO: process 2d nodes
    // __draw_2d_nodes ();
    __draw_ui_nodes (_renderer);
}

///////////////////////////////////////////////////////////////////////////////
// node op
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ui op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_ui_draw_texture ( ex_renderer_t *_renderer,
                          void *_texture,
                          ex_recti_t _pos,
                          ex_recti_t _border,
                          ex_rectf_t _uv0,
                          ex_vec4f_t _color ) 
{
    ex_ui_node_t *node;

    node = __request_ui_node(_renderer);

    node->text = NULL;
    node->texture = _texture;

    node->transform = _renderer->ui_state.matrix; 
    node->depth = _renderer->ui_state.depth; 

    node->pos = _pos;
    node->border = _border;
    node->uv0 = _uv0;
    node->color = _color;
}
