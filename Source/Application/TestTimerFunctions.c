//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    TestTimerFunctions.c
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
//lint -e715 -e830

#ifndef TEST_TIMER_FUNCTIONS_H
#include "TestTimerFunctions.h"
#endif

#ifndef _CONFIG_PLATFORM_
#include <Config_Platform.h>
#endif

#ifndef SCHEDULER_H
#include <Scheduler.h>
#endif

#ifndef TEST_TASKS_H
#include "TestTasks.h"
#endif

#ifndef _TEST_SIG_MSG_COMMON_H
#include "Test_SigMsg.h"
#endif

//#ifndef __COMM_LINK_LAYER_H_
//#include "CommLinkLayer.h"
//#endif

//------------------------------------------------------------------------------
#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
using namespace hh;
#endif
#endif


// --- definitions for testing -------------------------------------------------
// if we are in Unit testing mode, we want access to the static local variables
// and the functions, otherwise they should be local via static declaration
#ifdef _UNIT_TESTING_PROGRAM_
#define UT_TIMERFUNC_STATIC
#define UT_EXT _Imp
#else
#define UT_TIMERFUNC_STATIC static
#define UT_EXT _Imp
#endif


// --- constants ---------------------------------------------------------------
UT_TIMERFUNC_STATIC TC_Event cnstEvent_KeyboardTick   = {          SIG_SYS_TICK,  0,      TASK_KEYBOARD, 0 };
UT_TIMERFUNC_STATIC TC_Event cnstEvent_BuzzerTick     = {  SIG_TIMER_TICK_SHORT,  0,        TASK_BUZZER, 0 };

UT_TIMERFUNC_STATIC TC_Event cnstEvent_DisplayBlink   = {  SIG_TIMER_TICK_SHORT,  0,       TASK_DISPLAY, 0 };
UT_TIMERFUNC_STATIC TC_Event cnstEvent_DisplayFadeout = { SIG_TIMER_TICK_NORMAL,  0,       TASK_DISPLAY, 0 };
UT_TIMERFUNC_STATIC TC_Event cnstEvent_DisplayTimeout = {   SIG_TIMER_TICK_LONG,  0,       TASK_DISPLAY, 0 };

UT_TIMERFUNC_STATIC TC_Event cnstEvent_StateBlink     = {  SIG_TIMER_TICK_SHORT,  0,  TASK_STATEMACHINE, 0 };
UT_TIMERFUNC_STATIC TC_Event cnstEvent_StateFadeout   = { SIG_TIMER_TICK_NORMAL,  0,  TASK_STATEMACHINE, 0 };
UT_TIMERFUNC_STATIC TC_Event cnstEvent_StateTimeout   = {   SIG_TIMER_TICK_LONG,  0,  TASK_STATEMACHINE, 0 };

UT_TIMERFUNC_STATIC TC_Event cnstEvent_HK_LoPowermode = {  SIG_HSK_GO_POWERSAVE,  0,  TASK_HOUSEKEEPING, 0 };
UT_TIMERFUNC_STATIC TC_Event cnstEvent_HK_HiPowermode = {  SIG_TIMER_TICK_SHORT,  0,  TASK_HOUSEKEEPING, 0 };
UT_TIMERFUNC_STATIC TC_Event cnstEvent_HK_Update      = { SIG_TIMER_TICK_NORMAL,  0,  TASK_HOUSEKEEPING, 0 };
UT_TIMERFUNC_STATIC TC_Event cnstEvent_HK_PowerOff    = {   SIG_TIMER_TICK_LONG,  0,  TASK_HOUSEKEEPING, 0 };

UT_TIMERFUNC_STATIC TC_Event cnstEvent_CalcShortTO    = {  SIG_TIMER_TICK_SHORT,  0,   TASK_CALCULATION, 0 };

UT_TIMERFUNC_STATIC TC_Event cnstEvent_COMM_WatchDog  = {   SIG_TIMER_TICK_LONG,  0, TASK_COMMUNICATION, 0 };


//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_KeyboardTick_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_KeyboardTick( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_KeyboardTick, SCHED_PRIORITY_MEDIUM );
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_BuzzerTick_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_BuzzerTick( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_BuzzerTick, SCHED_PRIORITY_MEDIUM );
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_DisplayBlink_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_DisplayBlink( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_DisplayBlink, SCHED_PRIORITY_MEDIUM );
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_DisplayFadeout_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_DisplayFadeout( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_DisplayFadeout, SCHED_PRIORITY_MEDIUM );
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_DisplayTimeout_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_DisplayTimeout( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_DisplayTimeout, SCHED_PRIORITY_MEDIUM );
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_StateBlink_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_StateBlink( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_StateBlink, SCHED_PRIORITY_MEDIUM );
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_StateFadeout_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_StateFadeout( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_StateFadeout, SCHED_PRIORITY_MEDIUM );
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_StateTimeout_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_StateTimeout( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_StateTimeout, SCHED_PRIORITY_MEDIUM );
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_CalcShortTimeout_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_CalcShortTimeout( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_CalcShortTO, SCHED_PRIORITY_MEDIUM );
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_Reserved_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_Reserved( TC_Uint32 aTimer )
#endif
{
  // reserved, not yet used!
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_CLL_REC_Timeout_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_CLL_REC_Timeout( TC_Uint32 aTimer )
#endif
{
  // This is a little bit special here...
  //  Because the serial receiving is running in the background in the
  //  interrupt handling routines, we don't dispatch this timeout to a task.
  //  Instead we directly resetting the receiving state machine and buffer
  //***CommLL_ResetReceiving();
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_CLL_WDG_Timeout_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_CLL_WDG_Timeout( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_COMM_WatchDog, SCHED_PRIORITY_MEDIUM );
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_HousekeepingLoPowermode_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_HousekeepingLoPowermode( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_HK_LoPowermode, SCHED_PRIORITY_HIGH );
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_HousekeepingHiPowermode_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_HousekeepingHiPowermode( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_HK_HiPowermode, SCHED_PRIORITY_HIGH );
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_HousekeepingUpdate_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_HousekeepingUpdate( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_HK_Update, SCHED_PRIORITY_LOW );
}

//------------------------------------------------------------------------------
#ifdef _UNIT_TESTING_PROGRAM_
T_Void timerFunc_PowerOff_Imp( TC_Uint32 aTimer )
#else
T_Void timerFunc_PowerOff( TC_Uint32 aTimer )
#endif
{
  sched_SetSignal( cnstEvent_HK_PowerOff, SCHED_PRIORITY_LOW );
}




#undef UT_TIMERFUNC_STATIC

//--- eof ----------------------------------------------------------------------


