//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        task_Housekeeping.c
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION housekeeping task
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
// 2008-10-02 hh    first design
// 2008-12-09 hh    added handling for going into powersave mode
//------------------------------------------------------------------------------

#ifndef __TASK_HOUSEKEEPING__H__
#include "task_Housekeeping.h"
#endif

#ifndef _CONFIG_PLATFORM_
#include <Config_Platform.h>
#endif

#ifndef __HOUSEKEEPER_HANDLER_H__
#include "HousekeepingHandler.h"
#endif

#ifndef _TEST_SIG_MSG_COMMON_H
#include "Test_SigMsg.h"
#endif


//------------------------------------------------------------------------------
#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
using namespace hh;
#endif
#endif


// --- constants ---------------------------------------------------------------
static TC_Event cnstEvent_Tick_Short   = { MSG_TIM_TICK_SHORT,   0, 0, 0 };
static TC_Event cnstEvent_Tick_Normal  = { MSG_TIM_TICK_NORMAL,  0, 0, 0 };
static TC_Event cnstEvent_Tick_Long    = { MSG_TIM_TICK_LONG,    0, 0, 0 };
static TC_Event cnstEvent_Go_Powersave = { MSG_HSK_GO_POWERSAVE, 0, 0, 0 };

// --- mask definition ---------------------------------------------------------
#define DISP_SIG_TIMEOUT_MASK (SIG_TIMER_TICK_SHORT + SIG_TIMER_TICK_NORMAL + SIG_TIMER_TICK_LONG + SIG_HSK_GO_POWERSAVE)




// =============================================================================
// this task does
T_Void task_Housekeeping( TC_Event anEvent )
{
  if( anEvent.linkState == EVENT_STATE_IS_SIGNAL )
   {
     // signals
     // there should be only timer signals for this task!
     if( anEvent.msg & DISP_SIG_TIMEOUT_MASK )
      {
        if( anEvent.msg & SIG_TIMER_TICK_SHORT )  HousekeepingHandler_Handle( cnstEvent_Tick_Short );
        if( anEvent.msg & SIG_TIMER_TICK_NORMAL ) HousekeepingHandler_Handle( cnstEvent_Tick_Normal );
        if( anEvent.msg & SIG_TIMER_TICK_LONG )   HousekeepingHandler_Handle( cnstEvent_Tick_Long );
        if( anEvent.msg & SIG_HSK_GO_POWERSAVE )  HousekeepingHandler_Handle( cnstEvent_Go_Powersave );
      }
   }
  else
   {
     // messages
     switch ( anEvent.msg )
     {
       case MSG_INITIALIZE: HousekeepingHandler_Initialize();  break;
       case MSG_RESET:      HousekeepingHandler_Reset();       break;
       case MSG_FINALIZE:   HousekeepingHandler_Finalize();    break;
       default:
         // all other messages should be handled directly in the handler
         HousekeepingHandler_Handle( anEvent );
     }
   }
}



//--- eof ----------------------------------------------------------------------


