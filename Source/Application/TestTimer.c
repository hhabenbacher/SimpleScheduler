//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    TestTimer.c
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Test Timer defines
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

//! --- Doxygen comment ---------------------------------------------------------
//! \file    TestTimer.c
//! \brief   Test Timer defines (Implementation)
//! \author  Herwig Habenbacher (hh)
//! \version 1.0
//! \date    2008-10-23
//!

#ifndef _CONFIG_TIMER_
#include <Config_Timer.h>
#endif

#ifndef SW_TIMER_H
#include "SWTimer.h"
#endif

#ifndef SW_TIMER_DEFINITIONS_H
#include "SWTimerDefinitions.h"
#endif

#ifndef TEST_TIMER_FUNCTIONS_H
#include "TestTimerFunctions.h"
#endif


//------------------------------------------------------------------------------
#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
using namespace hh;
#endif
#endif

#define T_KBD_TK    ((T_Uint32)( 0  ))
#define T_KBD_MX    ((T_Uint32)( 10 ))

#define T_MI_PHI    ((T_Uint32)(  150 / TICK_INTERVALL_TIME_MS))
#define T_MA_PHI    ((T_Uint32)(  225 / TICK_INTERVALL_TIME_MS))
#define T_MI_PLO    ((T_Uint32)(  250 / TICK_INTERVALL_TIME_MS))
#define T_MA_PLO    ((T_Uint32)(  275 / TICK_INTERVALL_TIME_MS))

#define T_20__HZ    ((T_Uint32)(   25 / TICK_INTERVALL_TIME_MS))
#define T_10__HZ    ((T_Uint32)(   50 / TICK_INTERVALL_TIME_MS))
#define T__2__HZ    ((T_Uint32)(  250 / TICK_INTERVALL_TIME_MS))
#define T__1__HZ    ((T_Uint32)(  500 / TICK_INTERVALL_TIME_MS))
#define T__2p_HZ    ((T_Uint32)(  275 / TICK_INTERVALL_TIME_MS))
#define T__1p_HZ    ((T_Uint32)(  525 / TICK_INTERVALL_TIME_MS))

#define T__05SEC    ((T_Uint32)(  500 / TICK_INTERVALL_TIME_MS))
#define T__1_SEC    ((T_Uint32)( 1000 / TICK_INTERVALL_TIME_MS))
#define T__3_SEC    ((T_Uint32)( 3000 / TICK_INTERVALL_TIME_MS))
#define T__5_SEC    ((T_Uint32)( 5000 / TICK_INTERVALL_TIME_MS))
#define T_10_SEC    ((T_Uint32)(10000 / TICK_INTERVALL_TIME_MS))
#define T_15_SEC    ((T_Uint32)(15000 / TICK_INTERVALL_TIME_MS))

#define T__3pSEC    ((T_Uint32)( 3025 / TICK_INTERVALL_TIME_MS))
#define T__5pSEC    ((T_Uint32)( 5025 / TICK_INTERVALL_TIME_MS))
#define T_10pSEC    ((T_Uint32)(10025 / TICK_INTERVALL_TIME_MS))
#define T_15pSEC    ((T_Uint32)(15025 / TICK_INTERVALL_TIME_MS))

#define T__1_MIN    ((T_Uint32)(60000 / TICK_INTERVALL_TIME_MS))

// -----------------------------------------------------------------------------
// this struct is made available externally...
TCA_SW_TimerArray actTimerArray =
{
  // timeout, timeoutMax,                           handler, reload, default, variable
  { T_KBD_TK,   T_KBD_MX,            timerFunc_KeyboardTick,   True,    True,    False },  // 00: TIMER_KEYBOARD_TICK
  { T_20__HZ,   T_10__HZ,              timerFunc_BuzzerTick,   True,   False,     True },  // 01: TIMER_BUZZER_TICK
  { T__2__HZ,   T__1__HZ,            timerFunc_DisplayBlink,   True,   False,     True },  // 02: TIMER_DISPLAY_BLINK
  { T__3_SEC,   T__5_SEC,          timerFunc_DisplayFadeout,   True,   False,     True },  // 03: TIMER_DISPLAY_FADEOUT
  { T_10_SEC,   T_15_SEC,          timerFunc_DisplayTimeout,   True,   False,     True },  // 04: TIMER_DISPLAY_TIMEOUT
  { T__2p_HZ,   T__1p_HZ,              timerFunc_StateBlink,   True,   False,     True },  // 05: TIMER_STATE_BLINK
  { T__3pSEC,   T__5pSEC,            timerFunc_StateFadeout,   True,   False,     True },  // 06: TIMER_STATE_FADEOUT
  { T_10pSEC,   T_15pSEC,            timerFunc_StateTimeout,   True,   False,     True },  // 07: TIMER_STATE_TIMEOUT
  { T__05SEC,   T__3_SEC,        timerFunc_CalcShortTimeout,   True,   False,    False },  // 08: TIMER_CALC_SHORTTIMEOUT
  {       10,         80,                timerFunc_Reserved,   True,   False,    False },  // 09: TIMER_RESERVED (unused) 
  { T__05SEC,   T__1_SEC,         timerFunc_CLL_REC_Timeout,   True,   False,    False },  // 10: TIMER_CLL_REC_TIMEOUT
  { T__3_SEC,   T__5_SEC,         timerFunc_CLL_WDG_Timeout,   True,   False,    False },  // 11: TIMER_CLL_WDG_TIMEOUT
  { T_MI_PLO,   T_MA_PLO, timerFunc_HousekeepingLoPowermode,   True,   False,     True },  // 12: TIMER_HOUSEKEEPING_LO_POWERMODE
  { T_MI_PHI,   T_MA_PHI, timerFunc_HousekeepingHiPowermode,   True,   False,     True },  // 13: TIMER_HOUSEKEEPING_HI_POWERMODE
  { T__1_SEC,   T_15_SEC,      timerFunc_HousekeepingUpdate,   True,    True,     True },  // 14: TIMER_HOUSEKEEPING_UPDATE
  { T__1_MIN,   T__1_MIN,                timerFunc_PowerOff,   True,    True,     True }   // 15: TIMER_POWER_OFF
};



//--- eof ----------------------------------------------------------------------


