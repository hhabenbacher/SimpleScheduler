//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        task_Buzzer.c
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION buzzer task
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

#ifndef __TASK_BUZZER__H__
#include "task_Buzzer.h"
#endif

#ifndef _CONFIG_PLATFORM_
#include <Config_Platform.h>
#endif

#ifndef __BUZZER_HANDLER_H__
#include "BuzzerHandler.h"
#endif


//------------------------------------------------------------------------------
#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
using namespace hh;
#endif
#endif


// --- check for correct include
#if __HH_SIMPLE_SCHEDULER_H_VERSION__ < 0x0012
#error "wrong Scheduler.h version included!"
#endif


// --- constants ---------------------------------------------------------------
static TC_Event cnstEvent_Tick_Short  = { MSG_TIM_TICK_SHORT,  0, 0, 0 };



// =============================================================================
// this task does the Buzzer handling (Beeping, etc) for the Test Device
T_Void task_Buzzer( TC_Event anEvent )
{
  if( anEvent.linkState == EVENT_STATE_IS_SIGNAL )
   {
     // signals
     // there should be only short timer tick signals for this task!
     if( anEvent.msg & SIG_TIMER_TICK_SHORT )
       BuzzerHandler_Handle( cnstEvent_Tick_Short );
   }
  else
   {
     // messages
     switch ( anEvent.msg )
     {
       case MSG_INITIALIZE: BuzzerHandler_Initialize();  break;
       case MSG_RESET:      BuzzerHandler_Reset();       break;
       case MSG_FINALIZE:   BuzzerHandler_Finalize();    break;
       default:
         // all other messages should be handled directly in the handler
         BuzzerHandler_Handle( anEvent );
     }
   }
}



//--- eof ----------------------------------------------------------------------


