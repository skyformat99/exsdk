// ======================================================================================
// File         : hashmap.h
// Author       : Wu Jie 
// Last Change  : 06/28/2010 | 08:03:23 AM | Monday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef HASHMAP_H_1277683404
#define HASHMAP_H_1277683404
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" {
#endif
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// foreach
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
/*! 
 @def ex_hashmap_each
 @param _hashmap the in hashmap
 @param _type the type of the value in the hashmap.
 @param _el the value variable you want to define.
 @details macro for easy iterates the hashmap container.

 when use the macro, it will define the local variable below:
 - __node__: the current node of the hashmap
 - __node_begin__: the the beginning of the node

 to finish the code, you must write ex_hashmap_each_end.

 Usage:
 @code
 ex_hashmap_t *my_hashmap = ex_hashmap_alloc( sizeof(int), sizeof(float), 10 );
 ex_hashmap_each ( my_hashmap, float, item ) {
    printf( "item is %f", item );
 } ex_hashmap_each_end;
 @endcode
 @sa ex_hashmap_each_end
 @note DO NOT USE continue in this loop, use ex_hashmap_continue instead 
*/// ------------------------------------------------------------------ 

#define ex_hashmap_each( _hashmap, _type, _el ) \
    { \
        size_t __idx__ = 0; \
        _type _el; \
        while ( __idx__ < (_hashmap)->count ) { \
            _el = *( (_type *) ( ex_hashmap_get_by_idx (_hashmap, __idx__) ) );

// ------------------------------------------------------------------ 
/*! 
 @def ex_hashmap_each
 @param _hashmap the in hashmap
 @param _type the point-type of the value in the hashmap.
 @param _el the value variable you want to define.
 @details macro for easy iterates the hashmap container.

 when use the macro, it will define the local variable below:
 - __node__: the current node of the hashmap
 - __node_begin__: the the beginning of the node

 to finish the code, you must write ex_hashmap_each_end.

 Usage:
 @code
 ex_hashmap_t *my_hashmap = ex_hashmap_alloc( sizeof(int), sizeof(float), 10 );
 ex_hashmap_raw_each ( my_hashmap, float *, item ) {
    printf( "item is %f", *item );
 } ex_hashmap_each_end;
 @endcode
 @sa ex_hashmap_each_end
 @note DO NOT USE continue in this loop, use ex_hashmap_continue instead 
*/// ------------------------------------------------------------------ 

#define ex_hashmap_raw_each( _hashmap, _type, _el ) \
    { \
        size_t __idx__ = 0; \
        _type _el; \
        while ( __idx__ < (_hashmap)->count ) { \
            _el = (_type)( ex_hashmap_get_by_idx (_hashmap, __idx__) );

// ------------------------------------------------------------------ 
/*! 
 @def ex_hashmap_each_end
 @details macro to end the ex_hashmap_each, ex_hashmap_raw_each macro
 @sa ex_hashmap_each
 @sa ex_hashmap_raw_each
*/// ------------------------------------------------------------------ 

#define ex_hashmap_each_end \
            ++__idx__; \
        } \
    }

// ------------------------------------------------------------------ 
/*! 
 @def ex_hashmap_continue
 @details macro to let the continue work in each
 @sa ex_hashmap_each
 @sa ex_hashmap_raw_each
*/// ------------------------------------------------------------------ 

#define ex_hashmap_continue \
    { \
        ++__idx__; \
        continue; \
    }

///////////////////////////////////////////////////////////////////////////////
// decls
// the size of indices, keys, values is fixed when inited.
// the node pool is flexible.
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

//
typedef uint32 (*hashkey_t) (const void *);
typedef int (*keycmp_t) (const void *, const void *);

//
typedef struct ex_hashmap_t {
    // public
    size_t count;
    size_t capacity;

    // private
    size_t hashsize;
    size_t key_bytes;
    size_t value_bytes;
    hashkey_t hashkey;
    keycmp_t keycmp;

    void *nodes;
    size_t *indices;
    size_t node_bytes; // node bytes = key_bytes + value_bytes + sizeof(__node_t)

    // alloc methods
    void *(*alloc)      ( size_t );
    void *(*realloc)    ( void *, size_t );
    void  (*dealloc)    ( void * );
} ex_hashmap_t;

// ------------------------------------------------------------------ 
// Desc: 
// ex_hashmap
// ex_hashmap_notype
// ------------------------------------------------------------------ 

// ex_hashset
#define ex_hashset(_type,_hashsize) \
    ex_hashmap_alloc(sizeof(_type), sizeof(_type), \
                   _hashsize, \
                   ex_hashkey_##_type, ex_keycmp_##_type \
                  )

extern ex_hashmap_t *ex_hashmap_alloc ( size_t _key_bytes, size_t _value_bytes, 
                                        size_t _hashsize, 
                                        hashkey_t _hashkey, keycmp_t _keycmp );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_hashmap_free ( ex_hashmap_t *_hashmap );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_hashmap_init ( ex_hashmap_t *_hashmap, 
                              size_t _key_bytes, size_t _value_bytes, 
                              size_t _hashsize, 
                              hashkey_t _hashkey, keycmp_t _keycmp, 
                              void *(*_alloc) ( size_t ),
                              void *(*_realloc) ( void *, size_t ),
                              void  (*_dealloc) ( void * )
                            );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_hashmap_deinit ( ex_hashmap_t *_hashmap ); 

// ------------------------------------------------------------------ 
// Desc: 
// NOTE: this operation is deprecated, you need to check if the value 
//  exists then go for it.
// ------------------------------------------------------------------ 

extern size_t ex_hashmap_add_new ( ex_hashmap_t *_hashmap, const void *_key, const void *_val, size_t _hash_idx );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern int ex_hashmap_find ( const ex_hashmap_t *_hashmap, const void *_key );

extern void *ex_hashmap_get ( const ex_hashmap_t *_hashmap, const void *_key );
extern void *ex_hashmap_get_or_new ( ex_hashmap_t *_hashmap, const void *_key );
extern void *ex_hashmap_get_by_idx ( const ex_hashmap_t *_hashmap, size_t _idx );

// ------------------------------------------------------------------ 
// Desc: 
//  @return: false: already exists
// ------------------------------------------------------------------ 

extern size_t ex_hashmap_add_unique ( ex_hashmap_t *_hashmap, const void *_key, const void *_val );
extern size_t ex_hashmap_set_or_new ( ex_hashmap_t *_hashmap, const void *_key, const void *_val );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_hashmap_cpy ( ex_hashmap_t *_to, const ex_hashmap_t *_from );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern bool ex_hashmap_remove_at ( ex_hashmap_t *_hashmap, const void *_key );
extern void ex_hashmap_remove_by_idx ( ex_hashmap_t *_hashmap, size_t _idx );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline size_t ex_hashmap_count ( const ex_hashmap_t *_hashmap ) { return _hashmap->count; }
static inline size_t ex_hashmap_capacity ( const ex_hashmap_t *_hashmap ) { return _hashmap->capacity; }

///////////////////////////////////////////////////////////////////////////////
// useful callback
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: useful hash functions 
// ------------------------------------------------------------------ 

static inline uint32 ex_hashkey_cstr ( const void *_val ) { return ex_hashstr( *((const char **)_val) ); }
static inline uint32 ex_hashkey_int ( const void *_val ) { return (uint32)(*((const int *)_val)); }
static inline uint32 ex_hashkey_uint ( const void *_val ) { return (uint32)(*((const uint *)_val)); }
static inline uint32 ex_hashkey_uint32 ( const void *_val ) { return *((const uint32 *)_val); }
static inline uint32 ex_hashkey_uint64 ( const void *_val ) { return (uint32)(*((const uint64 *)_val)); }
static inline uint32 ex_hashkey_uid ( const void *_val ) { return (uint32)(*((const ex_uid_t *)_val)); }
static inline uint32 ex_hashkey_ptr ( const void *_val ) { return (uint32)((size_t)(*(const void **)_val) >> 4); }

// ------------------------------------------------------------------ 
// Desc: useful keycmp functions
// ------------------------------------------------------------------ 

static inline int ex_keycmp_cstr ( const void *_lhs, const void *_rhs ) { return strcmp ( *((const char **)_lhs), *((const char **)_rhs) ); }
static inline int ex_keycmp_int ( const void *_lhs, const void *_rhs ) { return *((const int *)_lhs) - *((const int *)_rhs); }
static inline int ex_keycmp_uint ( const void *_lhs, const void *_rhs ) { return *((const uint *)_lhs) - *((const uint *)_rhs); }
static inline int ex_keycmp_uint32 ( const void *_lhs, const void *_rhs ) { return *((const uint32 *)_lhs) - *((const uint32 *)_rhs); }
static inline int ex_keycmp_uint64 ( const void *_lhs, const void *_rhs ) { uint64 re = *((const uint64 *)_lhs) - *((const uint64 *)_rhs); return re > 0 ? 1 : (re == 0 ? 0 : -1); }
static inline int ex_keycmp_uid ( const void *_lhs, const void *_rhs ) { ex_uid_t re = *((const ex_uid_t *)_lhs) - *((const ex_uid_t *)_rhs); return re > 0 ? 1 : (re == 0 ? 0 : -1); }
static inline int ex_keycmp_ptr ( const void *_lhs, const void *_rhs ) { return (size_t)*((const void **)_lhs) - (size_t)*((const void **)_rhs); }

// ######################### 
#ifdef __cplusplus
} // end extern "C"
#endif
// ######################### 

// #################################################################################
#endif // END HASHMAP_H_1277683404
// #################################################################################


