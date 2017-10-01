//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	SWTimerDefinitions.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION TestDevice_Definitions for the Software timer structure and interface
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
//------------------------------------------------------------------------------

#ifndef SW_TIMER_DEFINITIONS_H
#define SW_TIMER_DEFINITIONS_H

#ifndef _CONFIG_PLATFORM_
#include <Config_Platform.h>
#endif

#ifndef _CONFIG_TIMER_
#include <Config_Timer.h>
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
// Actual timer handling function definition
//   an optional argument may be the timer number - so in the handling
//   function we will know which timer has called...
typedef T_Void  (*timer_HandlerFunction)( TC_Uint32 aTimer ) ;


// -----------------------------------------------------------------------------
// definition of an actual used timer counter entry
typedef struct
{
  T_Uint32  timeCount;                    // actual timeout count
  T_Uint32  reloadCount;                  // timeout count for reloading
  T_Bool    isEnabled;                    // shows if timer is enabled
  T_Bool    useReloadCount;               // we use the value of reload count
} TS_TimeoutCounter;

// our variable timer counter array...
typedef TS_TimeoutCounter TSA_TimeCntArray[SW_TIMER_MAX_TIMER];


// -----------------------------------------------------------------------------
// definition of an actual used timer definition entry
typedef struct
{
  T_Uint32                timeOutVal;     // actual timeout count (min time)
  T_Uint32                timeOutValMax;  // maximum timeout count for variable timer
  timer_HandlerFunction   handler;        // handler function
  T_Bool                  doAutoreload;   // reload to timeOutVal after timeout
  T_Bool                  isDefaultOn;    // timer is by default enabled
  T_Bool                  isVariable;     // timeout time may be variable
} TS_TimeoutDefinition;


// our fixed (const) task functions array...
typedef const TS_TimeoutDefinition TCA_SW_TimerArray[SW_TIMER_MAX_TIMER];




//------------------------------------------------------------------------------
#ifdef __cplusplus
} // extern "C"
#ifdef PF_USE_NAMESPACES
} // namespace hh
#endif
#endif // __cplusplus

#endif

//--- eof ----------------------------------------------------------------------

