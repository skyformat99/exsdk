// ======================================================================================
// File         : test_memmory.c
// Author       : Wu Jie 
// Last Change  : 04/19/2013 | 10:59:20 AM | Friday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#define BUF_SIZE 1024

int main (void) {
    int i = 0;
    void *buffer[BUF_SIZE];

    ex_sdk_init ();

    i = 0;
    while ( i < BUF_SIZE ) {
        buffer[i] = ex_malloc( EX_MB(1) );
        ++i;
    }

    i = 0;
    while ( i < BUF_SIZE ) {
        buffer[i] = ex_realloc( buffer[i], EX_KB(1) * rand() % 2048  );
        ++i;
    }

    i = 0;
    while ( i < BUF_SIZE ) {
        ex_free(buffer[i]);
        ++i;
    }

    ex_sdk_deinit ();
    return 0;
}
