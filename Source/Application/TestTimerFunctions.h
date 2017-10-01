//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    TestTimerFunctions.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION test Timer functions
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

#ifndef TEST_TIMER_FUNCTIONS_H
#define TEST_TIMER_FUNCTIONS_H

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


// definition of the used timer functions for the Test Device
extern T_Void timerFunc_KeyboardTick( TC_Uint32 aTimer );             //  0
extern T_Void timerFunc_BuzzerTick( TC_Uint32 aTimer );               //  1
extern T_Void timerFunc_DisplayBlink( TC_Uint32 aTimer );             //  2
extern T_Void timerFunc_DisplayFadeout( TC_Uint32 aTimer );           //  3
extern T_Void timerFunc_DisplayTimeout( TC_Uint32 aTimer );           //  4
extern T_Void timerFunc_StateBlink( TC_Uint32 aTimer );               //  5
extern T_Void timerFunc_StateFadeout( TC_Uint32 aTimer );             //  6
extern T_Void timerFunc_StateTimeout( TC_Uint32 aTimer );             //  7
extern T_Void timerFunc_CalcShortTimeout( TC_Uint32 aTimer );         //  8
extern T_Void timerFunc_Reserved( TC_Uint32 aTimer );                 //  9
extern T_Void timerFunc_CLL_REC_Timeout( TC_Uint32 aTimer );          // 10
extern T_Void timerFunc_CLL_WDG_Timeout( TC_Uint32 aTimer );          // 11
extern T_Void timerFunc_HousekeepingLoPowermode( TC_Uint32 aTimer );  // 12
extern T_Void timerFunc_HousekeepingHiPowermode( TC_Uint32 aTimer );  // 13
extern T_Void timerFunc_HousekeepingUpdate( TC_Uint32 aTimer );       // 14
extern T_Void timerFunc_PowerOff( TC_Uint32 aTimer );                 // 15


//------------------------------------------------------------------------------
#ifdef __cplusplus
} // extern "C"
#ifdef PF_USE_NAMESPACES
} // namespace hh
#endif
#endif // __cplusplus

#endif

//--- eof ----------------------------------------------------------------------

