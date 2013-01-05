// ======================================================================================
// File         : dtime.h
// Author       : Wu Jie 
// Last Change  : 12/31/2010 | 14:16:24 PM | Friday,December
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef DTIME_H_1293776186
#define DTIME_H_1293776186
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

//
typedef uint dtime_t; // we use msecs record daytime
#define EX_DTIME_INVALID -1

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern bool ex_is_valid_dtime ( uint _hour, uint _min, uint _secs, uint _ms );
extern bool ex_is_valid_dtime2 ( uint _ms );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern dtime_t ex_dtime_from ( uint _hour, uint _min, uint _secs, uint _ms );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern uint ex_dtime_hours ( dtime_t _dtime );
extern uint ex_dtime_minutes ( dtime_t _dtime );
extern uint ex_dtime_seconds ( dtime_t _dtime );
extern uint ex_dtime_mseconds ( dtime_t _dtime );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern uint64 ex_dtime_to_usecs ( dtime_t _dtime );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern dtime_t ex_dtime_add ( dtime_t _dtime, timespan_t _ts );
extern dtime_t ex_dtime_sub ( dtime_t _dtime, timespan_t _ts );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern timespan_t ex_dtime_timespan ( dtime_t _from, dtime_t _to );

// #################################################################################
#endif // END DTIME_H_1293776186
// #################################################################################
