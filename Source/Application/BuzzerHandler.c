//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        BuzzerHandler.c
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Buzzer handling routines
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
// 2008-11-25 hh    rewritten for new MMI demand
// 2008-12-04 hh    adjusted beeping frequency table (fast and slow)
// 2009-02-12 hh    adapted for Test MMI
//------------------------------------------------------------------------------
#include <string.h>

#ifndef HH_BASICTYPES_H
#include <HH_BasicTypes.h>
#endif

#ifndef _CONFIG_ASSERT_CHECKS_
#include <Config_AssertChecks.h>
#endif

//#ifndef __BUZZER_HIGH_LEVEL_H_
//#include "BuzzerHighLevel.h"
//#endif

#ifndef _TEST_SIG_MSG_COMMON_H
#include "Test_SigMsg.h"
#endif

#ifndef SW_TIMER_H
#include "SWTimer.h"
#endif

#ifndef TEST_TIMER_H
#include "TestTimer.h"
#endif



// --- check for correct include
#if __HH_SIMPLE_SCHEDULER_H_VERSION__ < 0x0012
#error "wrong Scheduler.h version included!"
#endif



// --- definitions for testing -------------------------------------------------
// if we are in Unit testing mode, we want access to the static local variables
// and the functions, otherwise they should be local via static declaration
#ifdef _UNIT_TESTING_PROGRAM_
#define UT_BUZZER_H_STATIC
#else
#define UT_BUZZER_H_STATIC static
#endif


#define BUZZER_DEFAULT_TEST_MMI_FREQUENCY   4000


//------------------------------------------------------------------------------
// --- typedefs ----------------------------------------------------------------

// - Buzzer handler states --------------
typedef enum
{
  e_BHS_Off             = 0,    // Buzzer is off
  e_BHS_Normal_Beep     = 1,    // Normal Beep mode (single to triple)
  e_BHS_Variable_Beep   = 2,    // Fast / Slow Beep (Special / Industrial mode)
  e_BHS_Continuous_Beep = 3     // Continuous beeping mode
} TE_BuzzerHandlerState;

// - Buzzer speed modes -----------------
typedef enum
{
  e_BSM_Normal = 0,    // Normal buzzing speed
  e_BSM_Double = 1,    // Double beeping buzzing speed
  e_BSM_Triple = 2,    // Triple beeping buzzing speed
  e_BSM_High   = 3,    // High speed beeping buzzing speed
  e_BSM_Low    = 4     // Low speed beeping buzzing speed
} TE_BuzzerSpeedMode;


//------------------------------------------------------------------------------
// --- constants ---------------------------------------------------------------
UT_BUZZER_H_STATIC TC_Uint32 cnstBeepSpeed[5][2] = {
  { 6, 4 },   // Normal
  { 5, 5 },   // Double
  { 6, 4 },   // Triple
  { 2, 2 },   // High
  { 5, 5 }    // Low
};

//------------------------------------------------------------------------------
// --- locals ------------------------------------------------------------------
UT_BUZZER_H_STATIC TE_BuzzerHandlerState lBuzzerHandlerState = e_BHS_Off;
UT_BUZZER_H_STATIC T_Uint32              lBeepCount          = 0;
UT_BUZZER_H_STATIC T_Uint32              lToggleCount[2]     = { 0, 0 };
UT_BUZZER_H_STATIC TE_BuzzerSpeedMode    lSpeedMode          = e_BSM_Normal;




//------------------------------------------------------------------------------
// --- functions ---------------------------------------------------------------

//------------------------------------------------------------------------------
T_Void bh_helper_HelpStop( T_Void )
{
  timer_Disable( TIMER_BUZZER_TICK );
  lBeepCount          = 0;
  lSpeedMode          = e_BSM_Normal;
  lToggleCount[0]     = cnstBeepSpeed[e_BSM_Normal][0];
  lToggleCount[1]     = cnstBeepSpeed[e_BSM_Normal][1];
  lBuzzerHandlerState = e_BHS_Off;
}

//------------------------------------------------------------------------------
T_Void bh_helper_handleNormal( T_Void )
{
  // Implementation...
}

//------------------------------------------------------------------------------
T_Void bh_helper_handleVariable( T_Void )
{
  // Implementation...
}



//------------------------------------------------------------------------------
// we are assuming that the tick comes every 50ms (see TestDeviceTimer.c)
UT_BUZZER_H_STATIC T_Void bh_do_tick_short( T_Void )
{
  // we only have to handle ticks if we are in a beeping state...
  if((lBuzzerHandlerState == e_BHS_Normal_Beep ) || (lBuzzerHandlerState == e_BHS_Variable_Beep ))
  {
    if(lBuzzerHandlerState == e_BHS_Normal_Beep)
      bh_helper_handleNormal();
    else
      bh_helper_handleVariable();
  }
}

//------------------------------------------------------------------------------
UT_BUZZER_H_STATIC T_Void bh_do_buzzer_off( T_Void )
{
  // Implementation...
}

//------------------------------------------------------------------------------
UT_BUZZER_H_STATIC T_Void bh_do_buzzer_beep( TC_Uint32 numBeeps )
{
  ASSERT_STRONG( numBeeps <= 3 );

  // Implementation...
  timer_Enable( TIMER_BUZZER_TICK );
}

//------------------------------------------------------------------------------
UT_BUZZER_H_STATIC T_Void bh_do_cont_on( T_Void )
{
  // Implementation...
}

//------------------------------------------------------------------------------
UT_BUZZER_H_STATIC T_Void bh_do_cont_off( T_Void )
{
  // Implementation...
}

//------------------------------------------------------------------------------
UT_BUZZER_H_STATIC T_Void bh_do_fast_on( T_Void )
{
  // Implementation...
  timer_Enable( TIMER_BUZZER_TICK );
}

//------------------------------------------------------------------------------
UT_BUZZER_H_STATIC T_Void bh_do_fast_off( T_Void )
{
  // Implementation...
}

//------------------------------------------------------------------------------
UT_BUZZER_H_STATIC T_Void bh_do_slow_on( T_Void )
{
  // Implementation...
  timer_Enable( TIMER_BUZZER_TICK );
}

//------------------------------------------------------------------------------
UT_BUZZER_H_STATIC T_Void bh_do_slow_off( T_Void )
{
  // Implementation...
}

//------------------------------------------------------------------------------
UT_BUZZER_H_STATIC T_Void bh_set_test_MMI( T_Void )
{
  // Implementation...
}


// =============================================================================

//------------------------------------------------------------------------------
T_Void BuzzerHandler_Initialize( T_Void )
{
  // Implementation...
}

//------------------------------------------------------------------------------
T_Void BuzzerHandler_Finalize( T_Void )
{
  // Implementation...
}

//------------------------------------------------------------------------------
T_Void BuzzerHandler_Reset( T_Void )
{
  // Implementation...
}


//------------------------------------------------------------------------------
T_Void BuzzerHandler_Handle( TC_Event anEvent )
{
  switch ( anEvent.msg )
  {
    case        MSG_TIM_TICK_SHORT: bh_do_tick_short();   break;
    case            MSG_BUZZER_OFF: bh_do_buzzer_off();   break;
    case           MSG_BUZZER_BEEP: bh_do_buzzer_beep(1); break;
    case    MSG_BUZZER_DOUBLE_BEEP: bh_do_buzzer_beep(2); break;
    case    MSG_BUZZER_TRIPLE_BEEP: bh_do_buzzer_beep(3); break;
    case  MSG_BUZZER_CONTINUOUS_ON: bh_do_cont_on();      break;
    case MSG_BUZZER_CONTINUOUS_OFF: bh_do_cont_off();     break;
    case   MSG_BUZZER_FAST_BEEP_ON: bh_do_fast_on();      break;
    case  MSG_BUZZER_FAST_BEEP_OFF: bh_do_fast_off();     break;
    case   MSG_BUZZER_SLOW_BEEP_ON: bh_do_slow_on();      break;
    case  MSG_BUZZER_SLOW_BEEP_OFF: bh_do_slow_off();     break;
    case   MSG_BUZZER_SET_TEST_MMI: bh_set_test_MMI();    break;
  }  //lint !e744
}


#undef UT_BUZZER_H_STATIC

//--- eof ----------------------------------------------------------------------

