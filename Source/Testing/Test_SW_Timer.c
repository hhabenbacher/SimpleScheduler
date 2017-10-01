//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    Test_SW_Timer.c
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Test software timer
//
//  REFERENCES  There are no references yet...
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
// 2008-11-06 hh   first design
//------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

// we need this define here before including Global.h (mainly for Lint)
#ifndef _UNIT_TEST_SW_TIMER_
#define _UNIT_TEST_SW_TIMER_
#endif

// and go further with the includes...

#ifndef _CONFIG_ASSERT_CHECKS_
#include <Config_AssertChecks.h>
#endif

#ifndef HH_BASICTYPES_H
#include <HH_BasicTypes.h>
#endif

#ifndef SW_TIMER_H
#include <SWTimer.h>
#endif

#ifndef SW_TIMER_DEFINITIONS_H
#include <SWTimerDefinitions.h>
#endif

#ifndef TEST_TIMER_H
#include <TestTimer.h>
#endif

#ifndef TEST_TIMER_FUNCTIONS_H
#include <TestTimerFunctions.h>
#endif

#ifndef TEST_TIMER_FUNCTIONS_EMU_H
#include <TestTimerFunctions_emu.h>
#endif


#ifdef PF_USE_NAMESPACES
using namespace hh;
#endif


#ifdef _UNIT_TESTING_PROGRAM_
extern TSA_TimeCntArray lTimeCountArray;
extern TCA_SW_TimerArray  actTimerArray;
#else
#error "You have to define _UNIT_TESTING_PROGRAM_ first!"
#endif




// -----------------------------------------------------------------------------
// locals
static T_Uint32 loc_01;
static T_Uint32 loc_02;
static T_Uint32 loc_03;

// -----------------------------------------------------------------------------
// timer redirected function 1
T_Void timer_HandlerFunction_1( TC_Uint32 aTimer )
{
  loc_01++;
}

// -----------------------------------------------------------------------------
// timer redirected function 2
T_Void timer_HandlerFunction_2( TC_Uint32 aTimer )
{
  loc_02++;
}

// -----------------------------------------------------------------------------
// timer redirected function 3
T_Void timer_HandlerFunction_3( TC_Uint32 aTimer )
{
  loc_03++;
}


// -----------------------------------------------------------------------------
// timer redirected all to function
T_Void timer_RedirectAll_to_HandlerFunction( const timer_HandlerFunction redirFunction )
{
  T_Uint32 cnt;

  for(cnt=0; cnt<SW_TIMER_MAX_TIMER; cnt++)
    timerRedir_SetTimer( cnt, redirFunction );
}

// -----------------------------------------------------------------------------
// timer clear all redirections
T_Void timer_RedirectClearAll( T_Void )
{
  T_Uint32 cnt;

  for(cnt=0; cnt<SW_TIMER_MAX_TIMER; cnt++)
    timerRedir_ClearTimer( cnt );
}


// -------------------------------------------------------------------------
void performTimerSetupTest(void)
{
  T_Uint32 cnt;

  printf(" ...Timer Setup test      ");

  timer_RedirectAll_to_HandlerFunction( timer_HandlerFunction_1 );
  timer_Initialize();
  timer_enableHandleTick();

  for(cnt=0; cnt<SW_TIMER_MAX_TIMER; cnt++)
  {
    ASSERT_STRONG( lTimeCountArray[cnt].timeCount == actTimerArray[cnt].timeOutVal  );
    ASSERT_STRONG( lTimeCountArray[cnt].isEnabled == actTimerArray[cnt].isDefaultOn  );
  }

  loc_01 = 0;

  for(cnt=0; cnt<120; cnt++)
    timer_HandleTick();

  ASSERT_STRONG( loc_01 == 123 );

  timer_Finalize();
  timer_RedirectClearAll();

  printf(" - passed \n");
}

// -------------------------------------------------------------------------
void performTimerResetTest(void)
{
  T_Uint32 cnt;

  printf(" ...Timer Reset test      ");

  timer_RedirectAll_to_HandlerFunction( timer_HandlerFunction_1 );
  timer_Initialize();
  timer_enableHandleTick();

  for(cnt=0; cnt<SW_TIMER_MAX_TIMER; cnt++)
  {
    ASSERT_STRONG( lTimeCountArray[cnt].timeCount == actTimerArray[cnt].timeOutVal  );
    ASSERT_STRONG( lTimeCountArray[cnt].isEnabled == actTimerArray[cnt].isDefaultOn  );
  }

  loc_01 = 0;

  timer_Disable( 1 );
  timer_Disable( 3 );
  timer_Disable( 8 );

  for(cnt=0; cnt<120; cnt++)
    timer_HandleTick();

  ASSERT_STRONG( loc_01 == 123 );

  timer_ResetAll();

  for(cnt=0; cnt<120; cnt++)
    timer_HandleTick();

  ASSERT_STRONG( loc_01 == 246 );

  for(cnt=0; cnt<SW_TIMER_MAX_TIMER; cnt++)
    timer_Disable( cnt );

  timer_Enable( 4 );

  for(cnt=0; cnt<120; cnt++)
  {
    if( (cnt == 40) || (cnt == 110) )
    {
      timer_Reset( 4 );
      timer_Enable( 4 );
    }

    timer_HandleTick();
  }

  ASSERT_STRONG( loc_01 == 246 );

  timer_Finalize();
  timer_RedirectClearAll();


  printf(" - passed \n");
}

// -------------------------------------------------------------------------
void performVariableTimerTest(void)
{
  T_Uint32 cnt;

  printf(" ...Variable Timer test   ");

  timer_RedirectAll_to_HandlerFunction( timer_HandlerFunction_1 );
  timer_Initialize();
  timer_enableHandleTick();

  for(cnt=0; cnt<SW_TIMER_MAX_TIMER; cnt++)
  {
    ASSERT_STRONG( lTimeCountArray[cnt].timeCount == actTimerArray[cnt].timeOutVal  );
    ASSERT_STRONG( lTimeCountArray[cnt].isEnabled == actTimerArray[cnt].isDefaultOn  );
  }

  loc_01 = 0;
  loc_02 = 0;
  loc_03 = 0;

  for(cnt=0; cnt<SW_TIMER_MAX_TIMER; cnt++)
    timer_Disable( cnt );

  timer_Enable( 2 );
  timer_Enable( 3 );
  timer_Enable( 4 );

  timerRedir_SetTimer( 2, timer_HandlerFunction_1 );
  timerRedir_SetTimer( 3, timer_HandlerFunction_2 );
  timerRedir_SetTimer( 4, timer_HandlerFunction_3 );

  ASSERT_STRONG( timer_SetVariableTimeout( 2,  20 ) ==  20 );
  ASSERT_STRONG( timer_SetVariableTimeout( 3, 130 ) == 130 );
  ASSERT_STRONG( timer_SetVariableTimeout( 4, 500 ) == 500 );

  for(cnt=0; cnt<1000; cnt++)
    timer_HandleTick();

  ASSERT_STRONG( loc_01 == 50 );
  ASSERT_STRONG( loc_02 ==  7  );
  ASSERT_STRONG( loc_03 ==  2 );

  timer_Finalize();
  timer_RedirectClearAll();

  printf(" - passed \n");
}


// -------------------------------------------------------------------------
void performTimerFunctionAssignmentsTest(void)
{
  printf(" ...Timer Functions test  ");

  ASSERT_STRONG( actTimerArray[TIMER_KEYBOARD_TICK].handler             == timerFunc_KeyboardTick );
  ASSERT_STRONG( actTimerArray[TIMER_BUZZER_TICK].handler               == timerFunc_BuzzerTick );
  ASSERT_STRONG( actTimerArray[TIMER_DISPLAY_BLINK].handler             == timerFunc_DisplayBlink );
  ASSERT_STRONG( actTimerArray[TIMER_DISPLAY_FADEOUT].handler           == timerFunc_DisplayFadeout );
  ASSERT_STRONG( actTimerArray[TIMER_DISPLAY_TIMEOUT].handler           == timerFunc_DisplayTimeout );
  ASSERT_STRONG( actTimerArray[TIMER_STATE_BLINK].handler               == timerFunc_StateBlink );
  ASSERT_STRONG( actTimerArray[TIMER_STATE_FADEOUT].handler             == timerFunc_StateFadeout );
  ASSERT_STRONG( actTimerArray[TIMER_STATE_TIMEOUT].handler             == timerFunc_StateTimeout );
  ASSERT_STRONG( actTimerArray[TIMER_CALC_SHORTTIMEOUT].handler         == timerFunc_CalcShortTimeout );
  ASSERT_STRONG( actTimerArray[TIMER_RESERVED].handler                  == timerFunc_Reserved );
  ASSERT_STRONG( actTimerArray[TIMER_CLL_REC_TIMEOUT].handler           == timerFunc_CLL_REC_Timeout );
  ASSERT_STRONG( actTimerArray[TIMER_CLL_WDG_TIMEOUT].handler           == timerFunc_CLL_WDG_Timeout );
  ASSERT_STRONG( actTimerArray[TIMER_HOUSEKEEPING_LO_POWERMODE].handler == timerFunc_HousekeepingLoPowermode );
  ASSERT_STRONG( actTimerArray[TIMER_HOUSEKEEPING_HI_POWERMODE].handler == timerFunc_HousekeepingHiPowermode );
  ASSERT_STRONG( actTimerArray[TIMER_HOUSEKEEPING_UPDATE].handler       == timerFunc_HousekeepingUpdate );
  ASSERT_STRONG( actTimerArray[TIMER_POWER_OFF].handler                 == timerFunc_PowerOff );

  printf(" - passed \n");
}


// -----------------------------------------------------------------------------
// test if the software timers work as expected...
void test_SW_Timer(void)
{
   printf("--------------------------------------------\n");
   printf("--- Software Timer test \n");

   timerRedir_Initialize();

   performTimerSetupTest();
   performTimerResetTest();
   performVariableTimerTest();
   performTimerFunctionAssignmentsTest();

 //printf("--------------------------------------------\n");
   printf("Software Timer test: ............... passed!\n");

}


//--- eof ----------------------------------------------------------------------


