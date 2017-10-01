//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    TestTasks_emu.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Test Task (function pointers) used by the scheduler (emulation)
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
// 2008-09-23 hh    first design
//------------------------------------------------------------------------------

#ifndef TEST_TASK_EMU_H
#define TEST_TASK_EMU_H

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


// -----------------------------------------------------------------------------
// Initialize   initializes the task redirections (set to zero)
extern T_Void tasksRedir_Initialize( T_Void );

// -----------------------------------------------------------------------------
// SetTask      sets the redirection (function pointer) for a given task
extern T_Void tasksRedir_SetTask( TC_Byte taskID, const task_DispatchFunction redirFunction );

// -----------------------------------------------------------------------------
// GetTask      gets the redirection (function pointer) for a given task
extern task_DispatchFunction tasksRedir_GetTask( TC_Byte taskID );

// -----------------------------------------------------------------------------
// ClearTask    clears the redirection (function pointer) for a given task
extern T_Void tasksRedir_ClearTask( TC_Byte taskID );



//------------------------------------------------------------------------------
#ifdef __cplusplus
} // extern "C"
#ifdef PF_USE_NAMESPACES
} // namespace hh
#endif
#endif // __cplusplus

#endif

//--- eof ----------------------------------------------------------------------


