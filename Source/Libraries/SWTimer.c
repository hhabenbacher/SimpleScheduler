//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    SWTimer.c
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

//! --- Doxygen comment ---------------------------------------------------------
//! \file    SWTimer.c
//! \brief   Software Timer implementation
//! \author  Herwig Habenbacher (hh)
//! \version 1.0
//! \date    2008-12-05
//! \note
//!  REFERENCES
//!  A simple Software Timer with possible variable timing \n
//!  \n
//!


#include <string.h>

#ifndef SW_TIMER_H
#include "SWTimer.h"
#endif

#ifndef SW_TIMER_DEFINITIONS_H
#include "SWTimerDefinitions.h"
#endif

#ifndef _CONFIG_PLATFORM_
#include <Config_Platform.h>
#endif

#ifndef _CONFIG_ASSERT_CHECKS_
#include <Config_AssertChecks.h>
#endif


//------------------------------------------------------------------------------
#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
using namespace hh;
#endif
#endif


// =============================================================================

// --- definitions for testing -------------------------------------------------
// if we are in Unit testing mode, we want access to the static local variables
// and the functions, otherwise they should be local via static declaration
#ifdef _UNIT_TESTING_PROGRAM_
#define UT_TIMER_STATIC
#else
#define UT_TIMER_STATIC static
#endif




// =============================================================================

// --- external timer array reference ------------------------------------------
extern TCA_SW_TimerArray actTimerArray;


// --- locals ------------------------------------------------------------------
// Timer counter array
UT_TIMER_STATIC TSA_TimeCntArray lTimeCountArray;
// Flag to enable / disable tick handling
UT_TIMER_STATIC T_Bool           lisTickHandlingAllowed;

// =============================================================================

// -----------------------------------------------------------------------------
// range check helper function
T_Void timer_doRangeCheck( TC_Uint32 timerNum )
{
  // check for range
  if(lTimeCountArray[timerNum].reloadCount < actTimerArray[timerNum].timeOutVal)
    lTimeCountArray[timerNum].reloadCount = actTimerArray[timerNum].timeOutVal;
  if(lTimeCountArray[timerNum].reloadCount > actTimerArray[timerNum].timeOutValMax)
    lTimeCountArray[timerNum].reloadCount = actTimerArray[timerNum].timeOutValMax;
}


// -----------------------------------------------------------------------------
// Initialize   initializes the start value - must be called once before
//              the software timer is used
//
// -----------------------------------------------------------------------------
T_Void timer_Initialize( T_Void )
{
  timer_ResetAll();
  lisTickHandlingAllowed = False;
}

// -----------------------------------------------------------------------------
// Finalize     to bring it down finally...
T_Void timer_Finalize( T_Void )
{
  T_Uint32 cnt;

  for(cnt=0; cnt<SW_TIMER_MAX_TIMER; cnt++)
    lTimeCountArray[cnt].isEnabled = False;

}

// -----------------------------------------------------------------------------
// ResetAll
T_Void timer_ResetAll( T_Void )
{
  T_Uint32 cnt;

  for(cnt=0; cnt<SW_TIMER_MAX_TIMER; cnt++)
  {
    lTimeCountArray[cnt].timeCount      = actTimerArray[cnt].timeOutVal;
    lTimeCountArray[cnt].reloadCount    = actTimerArray[cnt].timeOutVal;
    lTimeCountArray[cnt].isEnabled      = actTimerArray[cnt].isDefaultOn;
    lTimeCountArray[cnt].useReloadCount = actTimerArray[cnt].isVariable;
  }
}



// -----------------------------------------------------------------------------
// HandleTick   Handle the tick, triggered from timer ISR
T_Void timer_HandleTick( T_Void )
{
  if( lisTickHandlingAllowed )
  {
    T_Uint32 cnt;

    for(cnt=0; cnt<SW_TIMER_MAX_TIMER; cnt++)
    {
      // we only look an enabled timers
      if(lTimeCountArray[cnt].isEnabled)
      {
        // decrement if possible
        if(lTimeCountArray[cnt].timeCount > 0)
          lTimeCountArray[cnt].timeCount--;

        // ok, now check if timer is ready to fire...
        if(lTimeCountArray[cnt].timeCount == 0)
        {
          // reload count first
          if( actTimerArray[cnt].isVariable && lTimeCountArray[cnt].useReloadCount)
           {
             // check for range
             timer_doRangeCheck( cnt );
             lTimeCountArray[cnt].timeCount = lTimeCountArray[cnt].reloadCount;
           }
          else
           {
             lTimeCountArray[cnt].timeCount = actTimerArray[cnt].timeOutVal;
           }

          // we make an assert here for developement, because all timers should be set!
          ASSERT_STRONG( actTimerArray[cnt].handler != 0  );

          // fire!
          if(actTimerArray[cnt].handler)
            actTimerArray[cnt].handler( cnt );
        }

      }
    }
  }
}

// -----------------------------------------------------------------------------
// enableHandleTick   enable to handle the tick
T_Void timer_enableHandleTick( T_Void )
{
  lisTickHandlingAllowed = True;
}

// -----------------------------------------------------------------------------
// disableHandleTick   disable to handle the tick
T_Void timer_disableHandleTick( T_Void )
{
  lisTickHandlingAllowed = False;
}


// -----------------------------------------------------------------------------
// Enable       Enable given Timer
T_Void timer_Enable( TC_Uint32 timerNum )
{
  ASSERT_STRONG( timerNum < SW_TIMER_MAX_TIMER );

  lTimeCountArray[timerNum].isEnabled = True;
}

// -----------------------------------------------------------------------------
// Disable      Disable given Timer
T_Void timer_Disable( TC_Uint32 timerNum )
{
  ASSERT_STRONG( timerNum < SW_TIMER_MAX_TIMER );

  lTimeCountArray[timerNum].isEnabled = False;

  // --- on disabling we reset the counter
  // - first check if variabl timer
  if(lTimeCountArray[timerNum].useReloadCount)
   {
     // check for range
     timer_doRangeCheck( timerNum );
     lTimeCountArray[timerNum].timeCount = lTimeCountArray[timerNum].reloadCount;
   }
  else
   {
     lTimeCountArray[timerNum].timeCount = actTimerArray[timerNum].timeOutVal;
   }
}

// -----------------------------------------------------------------------------
// Reset        Resets given Timer
T_Void timer_Reset( TC_Uint32 timerNum )
{
  ASSERT_STRONG( timerNum < SW_TIMER_MAX_TIMER );

  lTimeCountArray[timerNum].timeCount      = actTimerArray[timerNum].timeOutVal;
  lTimeCountArray[timerNum].reloadCount    = actTimerArray[timerNum].timeOutVal;
  lTimeCountArray[timerNum].isEnabled      = actTimerArray[timerNum].isDefaultOn;
  lTimeCountArray[timerNum].useReloadCount = actTimerArray[timerNum].isVariable;
}

// -----------------------------------------------------------------------------
// ResetAndEnable        Resets and then enables given Timer
T_Void timer_ResetAndEnable( TC_Uint32 timerNum )
{
  ASSERT_STRONG( timerNum < SW_TIMER_MAX_TIMER );

  timer_Reset( timerNum );
  lTimeCountArray[timerNum].isEnabled = True;
}

// -----------------------------------------------------------------------------
// SetVariableTimeout  sets the timeout value for a variable timer
//                     returns the set timeout value if possible, 0 is error
T_Uint32 timer_SetVariableTimeout( TC_Uint32 timerNum, TC_Uint32 timeOutVal )
{
  T_Uint32 retVal = 0;

  ASSERT_STRONG( timerNum < SW_TIMER_MAX_TIMER );
  ASSERT_STRONG( actTimerArray[timerNum].isVariable );

  // variable time only if possible
  if(actTimerArray[timerNum].isVariable)
  {
    lTimeCountArray[timerNum].reloadCount = timeOutVal;

    // check for range
    timer_doRangeCheck( timerNum );

    lTimeCountArray[timerNum].timeCount = lTimeCountArray[timerNum].reloadCount;
    retVal = lTimeCountArray[timerNum].reloadCount;
  }

  return retVal;
}




#undef UT_TIMER_STATIC

//--- eof ----------------------------------------------------------------------

