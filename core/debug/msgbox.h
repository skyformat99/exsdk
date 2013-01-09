// ======================================================================================
// File         : msgbox.h
// Author       : Wu Jie 
// Last Change  : 06/27/2010 | 11:39:45 AM | Sunday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MSGBOX_H_1277609778
#define MSGBOX_H_1277609778
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////

#define EX_MSG_BOX_NONE    0
#define EX_MSG_BOX_FAILED  1
#define EX_MSG_BOX_ERROR   2
#define EX_MSG_BOX_WARNING 3

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern int ex_message_box ( int _msgType, const char *_caption, const char *_expr,  ... );

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

// #################################################################################
#endif // END MSGBOX_H_1277609778
// #################################################################################

