//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        schedule_Idle_emu.c
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Idle routine handling for the scheduler (emulation)...
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
// 2008-08-26 hh    first design
//------------------------------------------------------------------------------

#ifndef __SCHEDULE_IDLE__H__
#include <schedule_Idle.h>
#endif

#ifndef _CONFIG_PLATFORM_
#include <Config_Platform.h>
#endif

#ifndef SCHEDULE_IDLE_EMU_H
#include "schedule_Idle_emu.h"
#endif


//------------------------------------------------------------------------------
#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
using namespace hh;
#endif
#endif

// -----------------------------------------------------------------------------
// redirection function pointer
static idle_RedirectFunction pFuncIdle;

// -----------------------------------------------------------------------------
// do the idle task
T_Void doIdleTask( T_Void )
{
  // if a redirection exists we call this function...
  if(pFuncIdle)
    pFuncIdle();
  else
    // ...or at least we stop the scheduler here...
    sched_Stop();
}

// -----------------------------------------------------------------------------
// Initialize   initializes the idle redirections (set to zero)
T_Void idleRedir_Initialize( T_Void )
{
  pFuncIdle = 0;
}

// -----------------------------------------------------------------------------
// SetIdle      sets the redirection (function pointer) for the idle task
T_Void idleRedir_SetIdle( idle_RedirectFunction redirFunction )
{
  pFuncIdle = redirFunction;
}

// -----------------------------------------------------------------------------
// GetIdle      gets the redirection (function pointer) for the idle task
idle_RedirectFunction idleRedir_GetIdle( T_Void )
{
  return pFuncIdle;
}

// -----------------------------------------------------------------------------
// ClearIdle    clears the redirection (function pointer) for the idle task
T_Void idleRedir_ClearIdle( T_Void )
{
  pFuncIdle = 0;
}


//--- eof ----------------------------------------------------------------------


