//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        schedule_Idle_emu.h
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


#ifndef SCHEDULE_IDLE_EMU_H
#define SCHEDULE_IDLE_EMU_H

#ifndef _CONFIG_PLATFORM_
#include <Config_Platform.h>
#endif

#ifndef HH_BASICTYPES_H
#include <HH_BasicTypes.h>
#endif

#ifndef SCHEDULER_H
#include <Scheduler.h>
#endif


//------------------------------------------------------------------------------
#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
namespace hh {
#endif
extern "C" {
#endif // __cplusplus


typedef T_Void  (*idle_RedirectFunction)( T_Void ) ;


// -----------------------------------------------------------------------------
// Initialize   initializes the idle redirections (set to zero)
extern T_Void idleRedir_Initialize( T_Void );

// -----------------------------------------------------------------------------
// SetIdle      sets the redirection (function pointer) for the idle task
extern T_Void idleRedir_SetIdle( idle_RedirectFunction redirFunction );

// -----------------------------------------------------------------------------
// GetIdle      gets the redirection (function pointer) for the idle task
extern idle_RedirectFunction idleRedir_GetIdle( T_Void );

// -----------------------------------------------------------------------------
// ClearIdle    clears the redirection (function pointer) for the idle task
extern T_Void idleRedir_ClearIdle( T_Void );



//------------------------------------------------------------------------------
#ifdef __cplusplus
} // extern "C"
#ifdef PF_USE_NAMESPACES
} // namespace hh
#endif
#endif // __cplusplus

#endif



//--- eof ----------------------------------------------------------------------


