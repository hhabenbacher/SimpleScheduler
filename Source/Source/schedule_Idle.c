//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        schedule_Idle.c
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Idle routine handling for the scheduler...
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
#include "schedule_Idle.h"
#endif
 
#ifndef _CONFIG_PLATFORM_
#include <Config_Platform.h>
#endif

//------------------------------------------------------------------------------
#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
using namespace hh;
#endif
#endif

// -----------------------------------------------------------------------------
// do the idle task
T_Void doIdleTask( T_Void )
{
  // Nothing yet (maybe sleeping mode in future)
}



//--- eof ----------------------------------------------------------------------


