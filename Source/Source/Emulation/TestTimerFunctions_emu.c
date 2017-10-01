//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    TestTimerFunctions_emu.c
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Test Timer emulation functions
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

#ifndef SW_TIMER_H
#include <SWTimer.h>
#endif

#ifndef SW_TIMER_DEFINITIONS_H
#include <SWTimerDefinitions.h>
#endif

#ifndef TEST_TIMER_FUNCTIONS_H
#include "TestTimerFunctions.h"
#endif

#ifndef TEST_TIMER_FUNCTIONS_EMU_H
#include "TestTimerFunctions_emu.h"
#endif


//------------------------------------------------------------------------------
#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
using namespace hh;
#endif
#endif


// -----------------------------------------------------------------------------
// "locals" to redirect functions
static timer_HandlerFunction tmpTimer_array[SW_TIMER_MAX_TIMER];


// -----------------------------------------------------------------------------
static T_Void timer_Helper_Function( TC_Uint32 timerNum )
{
  if(tmpTimer_array[timerNum])
    tmpTimer_array[timerNum](timerNum);
}



//------------------------------------------------------------------------------
T_Void timerFunc_KeyboardTick( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_BuzzerTick( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_DisplayBlink( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_DisplayFadeout( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_DisplayTimeout( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_StateBlink( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_StateFadeout( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_StateTimeout( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_CalcShortTimeout( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_Reserved( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}


//------------------------------------------------------------------------------
T_Void timerFunc_CLL_REC_Timeout( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_CLL_WDG_Timeout( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_HousekeepingLoPowermode( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_HousekeepingHiPowermode( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_HousekeepingUpdate( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}

//------------------------------------------------------------------------------
T_Void timerFunc_PowerOff( TC_Uint32 aTimer )
{
  timer_Helper_Function( aTimer );
}


// -----------------------------------------------------------------------------
// Initialize   initializes the timer redirections (set to zero)
T_Void timerRedir_Initialize( T_Void )
{
  T_Int32 i;

  for(i=0; i<SW_TIMER_MAX_TIMER; i++)
    tmpTimer_array[i] = 0;
}

// -----------------------------------------------------------------------------
// SetTimer      sets the redirection (function pointer) for a given timer
T_Void timerRedir_SetTimer( TC_Uint32 timerNum, const timer_HandlerFunction redirFunction )
{
  if(timerNum < SW_TIMER_MAX_TIMER)
    tmpTimer_array[timerNum] = redirFunction;
}

// -----------------------------------------------------------------------------
// GetTimer      gets the redirection (function pointer) for a given timer
timer_HandlerFunction timerRedir_GetTimer( TC_Uint32 timerNum )
{
  if(timerNum < SW_TIMER_MAX_TIMER)
    return tmpTimer_array[timerNum];
  else
    return 0;
}

// -----------------------------------------------------------------------------
// ClearTimer    clears the redirection (function pointer) for a given timer
T_Void timerRedir_ClearTimer( TC_Uint32 timerNum )
{
  if(timerNum < SW_TIMER_MAX_TIMER)
    tmpTimer_array[timerNum] = 0;
}








//--- eof ----------------------------------------------------------------------


