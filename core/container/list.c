// ======================================================================================
// File         : list.c
// Author       : Wu Jie 
// Last Change  : 06/29/2010 | 18:46:46 PM | Tuesday,June
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// decls
///////////////////////////////////////////////////////////////////////////////

static inline ex_list_node_t *__alloc_node ( ex_list_t *_list, const void *_value ) {
    // allocate the node ( node_size + value_size ), and assign the value ptr to address point 
    // to the extract space allocate in the node. 
    ex_list_node_t *node = (ex_list_node_t *)_list->alloc ( _list->element_bytes + sizeof(ex_list_node_t) ); 
    node->value = (char *)node + sizeof(ex_list_node_t); 
    memcpy ( node->value, _value, _list->element_bytes );
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void __list_init ( ex_list_t *_list, 
                   size_t _element_bytes, 
                   void *(*_alloc) ( size_t ),
                   void *(*_realloc) ( void *, size_t ),
                   void  (*_dealloc) ( void * )
                 ) 
{
    _list->alloc = _alloc;
    _list->realloc = _realloc;
    _list->dealloc = _dealloc;

    // init public members
    _list->count = 0;
    _list->element_bytes = _element_bytes;
    _list->head = NULL;
    _list->tail = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
static inline void *__list_alloc( size_t _size ) { return ex_malloc_tag ( _size, "ex_list_t" ); }
static inline void *__list_realloc( void *_ptr, size_t _size ) { return ex_realloc_tag ( _ptr, _size, "ex_list_t" ); }
static inline void  __list_dealloc( void *_ptr ) { ex_free ( _ptr ); }
// ------------------------------------------------------------------ 

ex_list_t *ex_list_new ( size_t _element_bytes )
{
    ex_list_t *list = ex_malloc( sizeof(ex_list_t) ); 
    __list_init ( list, 
                  _element_bytes,
                  __list_alloc,
                  __list_realloc,
                  __list_dealloc );
    return list;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_list_t *ex_list_new_with_allocator ( size_t _element_bytes, 
                                        void *(*_alloc) ( size_t ),
                                        void *(*_realloc) ( void *, size_t ),
                                        void  (*_dealloc) ( void * )
                                      )
{
    ex_list_t *list = _alloc( sizeof(ex_list_t) ); 
    __list_init ( list, 
                  _element_bytes,
                  _alloc,
                  _realloc,
                  _dealloc );
    return list;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_list_delete ( ex_list_t *_list ) {
    ex_list_node_t *tmp,*node;
    void  (*dealloc) ( void * ) = _list->dealloc;

    ex_assert( _list != NULL );

    node = _list->head;
    while ( node != NULL ) {
        tmp = node;
        node = node->next;
        _list->dealloc ( tmp );
    }

    _list->count = 0;
    _list->element_bytes = 0;
    _list->head = NULL;
    _list->tail = NULL;

    _list->alloc = NULL;
    _list->realloc = NULL;
    _list->dealloc = NULL;

    dealloc(_list);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_list_append ( ex_list_t *_list, const void *_value )
{
    ex_list_node_t *node = NULL;

    // allocate the node
    node = __alloc_node ( _list, _value );

    //
    if ( _list->head == NULL ) {
        _list->head = node;
        _list->tail = node;
    }
    else {
        _list->tail->next = node;
        node->prev = _list->tail;
        _list->tail = node;
    }

    //
    ++_list->count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_list_prepend ( ex_list_t *_list, const void *_value )
{
    ex_list_node_t *node = NULL;

    // allocate the node
    node = __alloc_node ( _list, _value );

    //
    if ( _list->head == NULL ) {
        _list->head = node;
        _list->tail = node;
    }
    else {
        _list->head->prev = node;
        node->next = _list->head;
        _list->head = node;
    }

    //
    ++_list->count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_list_insert_back ( ex_list_t *_list, ex_list_node_t *_at, const void *_value )
{
    ex_list_node_t *node = NULL;

    ex_assert ( _at != NULL );

    // allocate the node
    node = __alloc_node ( _list, _value );

    // link the new node's next and prev
    node->next = _at->next;
    node->prev = _at;

    // link the at's next if exists
    // if _at is _tail
    if ( _at == _list->tail )
        _list->tail = node;
    else
        _at->next->prev = node; 

    ++_list->count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_list_insert_front ( ex_list_t *_list, ex_list_node_t *_at, const void *_value )
{
    ex_list_node_t *node = NULL;

    ex_assert ( _at != NULL );

    // allocate the node
    node = __alloc_node ( _list, _value );

    // link the new node's next and prev
    node->next = _at;
    node->prev = _at->prev;

    // link the at's next if exists
    // if _at is _head
    if ( _at == _list->head )
        _list->head = node;
    else
        _at->prev->next = node; 

    ++_list->count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_list_node_t *ex_list_remove_at ( ex_list_t *_list, ex_list_node_t *_at )
{
    ex_list_node_t *next_node;

    ex_assert ( _at != NULL );

    next_node = _at->next;

    // if only one node in the list
    if ( _list->head == _list->tail ) {
        ex_assert ( _at == _list->head );
        _list->head = _list->tail = NULL;
    }
    else if ( _at == _list->head ) {
        _list->head = _list->head->next;
        _list->head->prev = NULL;
    }
    else if ( _at == _list->tail ) {
        _list->tail = _list->tail->prev;
        _list->tail->next = NULL;
    }
    else {
        _at->prev->next = _at->next;
        _at->next->prev = _at->prev;
    }

    _list->dealloc (_at);
    --_list->count;

    return next_node;
}
