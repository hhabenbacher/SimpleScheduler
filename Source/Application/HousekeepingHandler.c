//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        HousekeepingHandler.c
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Housekeeper handling routines
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
// 2008-11-27 hh    rewritten for new MMI demand
// 2008-12-09 hh    added handling for going into powersave mode
// 2009-01-27 hh    implemented shutdown if voltage is too low
// 2009-11-30 hh    added amplification level handling
//------------------------------------------------------------------------------
#include <string.h>

#ifndef __HOUSEKEEPER_HANDLER_H__
#include "HousekeepingHandler.h"
#endif

#ifndef SCHEDULER_H
#include <Scheduler.h>
#endif

#ifndef _TEST_SIG_MSG_COMMON_H
#include "Test_SigMsg.h"
#endif

#ifndef SW_TIMER_H
#include "SWTimer.h"
#endif

#ifndef TEST_TIMER_H
#include "TestTimer.h"
#endif

#ifndef TEST_TASKS_H
#include "TestTasks.h"
#endif


// --- check for correct include
#if __HH_SIMPLE_SCHEDULER_H_VERSION__ < 0x0012
#error "wrong Scheduler.h version included!"
#endif


// --- definitions for testing -------------------------------------------------
// if we are in Unit testing mode, we want access to the static local variables
// and the functions, otherwise they should be local via static declaration
#ifdef _UNIT_TEST_PROCESSING_
#define UT_HOUSEKEEPING_H_STATIC
#else
#define UT_HOUSEKEEPING_H_STATIC static
#endif

#define HK_LOWPOWER_SHUTDOWN_COUNT 10

//------------------------------------------------------------------------------
// --- constants ---------------------------------------------------------------
UT_HOUSEKEEPING_H_STATIC TC_Event cnstEvent_HK_BattUpdate   = { MSG_DISPLAY_BATTERY_STATE, 0,      TASK_DISPLAY, 0 };
UT_HOUSEKEEPING_H_STATIC TC_Event cnstEvent_HK_AutoPowerOff = {        MSG_SM_HSK_TIMEOUT, 0, TASK_STATEMACHINE, 0 };
UT_HOUSEKEEPING_H_STATIC TC_Event cnstEvent_HK_ERR_Message  = {         SIG_ERROR_OCCURED, 0, TASK_STATEMACHINE, 0 };


//------------------------------------------------------------------------------
// --- locals ------------------------------------------------------------------
UT_HOUSEKEEPING_H_STATIC T_Int32          lAutoPowerOffCounter = 0;
UT_HOUSEKEEPING_H_STATIC T_Uint32         lLowPowerCounter = 0;
UT_HOUSEKEEPING_H_STATIC T_Uint32         lBattLevel = 0;



//------------------------------------------------------------------------------
// --- functions ---------------------------------------------------------------

//------------------------------------------------------------------------------
UT_HOUSEKEEPING_H_STATIC T_Void hkh_do_powermode_on( T_Void )
{
  timer_Disable( TIMER_HOUSEKEEPING_HI_POWERMODE );
  // Implementation...
}

//------------------------------------------------------------------------------
UT_HOUSEKEEPING_H_STATIC T_Void hkh_do_powermode_off( T_Void )
{
  timer_Disable( TIMER_HOUSEKEEPING_LO_POWERMODE );
  // Implementation...
}

//------------------------------------------------------------------------------
UT_HOUSEKEEPING_H_STATIC T_Void hkh_do_update( T_Void )
{
  // Implementation...
}

//------------------------------------------------------------------------------
UT_HOUSEKEEPING_H_STATIC T_Void hkh_do_powerOffCheck( T_Void )
{
  lAutoPowerOffCounter++;
  if( lAutoPowerOffCounter >= 150000 )
  {
    if(!sched_PostEvent( cnstEvent_HK_AutoPowerOff, SCHED_PRIORITY_MEDIUM ))
      sched_SetSignal( cnstEvent_HK_ERR_Message, SCHED_PRIORITY_HIGH );
  }
}

//------------------------------------------------------------------------------
UT_HOUSEKEEPING_H_STATIC T_Void hkh_do_resetPowerOff( T_Void )
{
  timer_ResetAndEnable( TIMER_POWER_OFF );
  lAutoPowerOffCounter = 0;
}



// =============================================================================

//------------------------------------------------------------------------------
T_Void HousekeepingHandler_Initialize( T_Void )
{
  hkh_do_resetPowerOff();
  lBattLevel = 2;
}

//------------------------------------------------------------------------------
T_Void HousekeepingHandler_Finalize( T_Void )
{
  // normally nothing to do...
  lAutoPowerOffCounter = 0;
  lBattLevel           = 0;
}

//------------------------------------------------------------------------------
T_Void HousekeepingHandler_Reset( T_Void )
{
  hkh_do_resetPowerOff();
  lBattLevel = 2;
}


//------------------------------------------------------------------------------
T_Void HousekeepingHandler_Handle( TC_Event anEvent )
{
  switch ( anEvent.msg )
  {
    case    MSG_TIM_TICK_SHORT: hkh_do_powermode_on();  break;
    case   MSG_TIM_TICK_NORMAL: hkh_do_update();        break;
    case     MSG_TIM_TICK_LONG: hkh_do_powerOffCheck(); break;
    case MSG_HSK_RESET_TIMEOUT: hkh_do_resetPowerOff(); break;
    case  MSG_HSK_GO_POWERSAVE: hkh_do_powermode_off(); break;
  } //lint !e744
}


#undef UT_HOUSEKEEPING_H_STATIC


//--- eof ----------------------------------------------------------------------

