//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    TestTimerFunctions_emu.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Test Timer functions
//
//------------------------------------------------------------------------------
// Please note corresponding MIT / BSD / Apache License!
//
// This file is not guaranteed by me to be error free. Every effort
// has been made to ensure proper data-types and declarations, but this program
// is distributed WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//------------------------------------------------------------------------------
// HISTORY:
//
// 2008-11-26 hh    first design
//------------------------------------------------------------------------------

#ifndef TEST_TIMER_FUNCTIONS_EMU_H
#define TEST_TIMER_FUNCTIONS_EMU_H

#ifndef _CONFIG_PLATFORM_
#include <Config_Platform.h>
#endif

#ifndef HH_BASICTYPES_H
#include <HH_BasicTypes.h>
#endif


//------------------------------------------------------------------------------
#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
namespace hh {
#endif
extern "C" {
#endif // __cplusplus


// -----------------------------------------------------------------------------
// Initialize   initializes the timer redirections (set to zero)
extern T_Void timerRedir_Initialize( T_Void );

// -----------------------------------------------------------------------------
// SetTimer      sets the redirection (function pointer) for a given timer
extern T_Void timerRedir_SetTimer( TC_Uint32 timerNum, const timer_HandlerFunction redirFunction );

// -----------------------------------------------------------------------------
// GetTimer      gets the redirection (function pointer) for a given timer
extern timer_HandlerFunction timerRedir_GetTimer( TC_Uint32 timerNum );

// -----------------------------------------------------------------------------
// ClearTimer    clears the redirection (function pointer) for a given timer
extern T_Void timerRedir_ClearTimer( TC_Uint32 timerNum );



//------------------------------------------------------------------------------
#ifdef __cplusplus
} // extern "C"
#ifdef PF_USE_NAMESPACES
} // namespace hh
#endif
#endif // __cplusplus

#endif

//--- eof ----------------------------------------------------------------------

