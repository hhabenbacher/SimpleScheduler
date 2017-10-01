//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    SWTimer.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Software Timer
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
// 2008-10-23 hh    first design
// 2008-12-05 hh    added ResetAndEnable
//------------------------------------------------------------------------------

#ifndef SW_TIMER_H
#define SW_TIMER_H

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



// =============================================================================
//  Function description for the Software Timer routines:
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Initialize   initializes the start value - must be called once before
//              the software timer is used
//
// -----------------------------------------------------------------------------
extern T_Void timer_Initialize( T_Void );

// -----------------------------------------------------------------------------
// Finalize     to bring it down finally...
extern T_Void timer_Finalize( T_Void );

// -----------------------------------------------------------------------------
// ResetAll
extern T_Void timer_ResetAll( T_Void );



// -----------------------------------------------------------------------------
// HandleTick             Handle the tick, triggered from timer ISR
extern T_Void timer_HandleTick( T_Void );

// -----------------------------------------------------------------------------
// enableHandleTick       enable to handle the tick
extern T_Void timer_enableHandleTick( T_Void );

// -----------------------------------------------------------------------------
// disableHandleTick      disable to handle the tick
extern T_Void timer_disableHandleTick( T_Void );



// -----------------------------------------------------------------------------
// Enable           Enable given Timer
extern T_Void timer_Enable( TC_Uint32 timerNum );

// -----------------------------------------------------------------------------
// Disable          Disable given Timer
extern T_Void timer_Disable( TC_Uint32 timerNum );

// -----------------------------------------------------------------------------
// Reset            Resets given Timer
extern T_Void timer_Reset( TC_Uint32 timerNum );

// -----------------------------------------------------------------------------
// ResetAndEnable   Resets and then enables given Timer
extern T_Void timer_ResetAndEnable( TC_Uint32 timerNum );


// -----------------------------------------------------------------------------
// SetVariableTimeout  sets the timeout value for a variable timer
//                     returns the set timeout value if possible, 0 is error
extern T_Uint32 timer_SetVariableTimeout( TC_Uint32 timerNum, TC_Uint32 timeOutVal );



//------------------------------------------------------------------------------
#ifdef __cplusplus
} // extern "C"
#ifdef PF_USE_NAMESPACES
} // namespace hh
#endif
#endif // __cplusplus

#endif

//--- eof ----------------------------------------------------------------------

