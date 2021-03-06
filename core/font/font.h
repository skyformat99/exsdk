// ======================================================================================
// File         : font.h
// Author       : Wu Jie 
// Last Change  : 04/08/2013 | 16:25:18 PM | Monday,April
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef FONT_H_1365409519
#define FONT_H_1365409519
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// font
///////////////////////////////////////////////////////////////////////////////

typedef struct ex_glyph_t {
   void *page;
   int16 x;
   int16 y;
   int16 w;
   int16 h;
   int16 offset_x;
   int16 offset_y;
   int16 advance_x;
   int16 advance_y;
} ex_glyph_t;

typedef struct ex_font_t {
    void *face;
    int size;
    int outline_type; // ( 0 = None, 1 = Line, 2 = Inner, 3 = Outer )
    float outline_thickness;
    ex_hashmap_t *glyph_sets; // (size, outline_type, outline_thickness) -> ex_glyph_set_t 

    //
    void *face_buffer;
    char facename[MAX_PATH];
} ex_font_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern int ex_font_init ();
extern void ex_font_deinit ();
extern bool ex_font_initialized ();

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern ex_font_t *ex_font_load ( const char *_filepath, int _size );
extern void ex_font_destroy ( ex_font_t *_font );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_font_set_size ( ex_font_t *_font, int _size );
extern int ex_font_get_kerning ( ex_font_t *_font, uint _first, uint _second );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern ex_glyph_t *ex_font_get_glyph ( ex_font_t *_font, uint _ft_index );
extern int ex_font_get_index ( ex_font_t *_font, int _char );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern const char *ex_font_get_family_name ( ex_font_t *_font );
extern const char *ex_font_get_style_name ( ex_font_t *_font );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern int ex_font_get_height ( ex_font_t *_font );
extern void ex_font_calc_size ( ex_font_t *_font, const char *_text, int *_w, int *_h );

// #################################################################################
#endif // END FONT_H_1365409519
// #################################################################################


