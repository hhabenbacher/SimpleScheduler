//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    TestTasks_emu.c
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


#ifndef SCHEDULER_H
#include <Scheduler.h>
#endif


//------------------------------------------------------------------------------
#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
using namespace hh;
#endif
#endif

// -----------------------------------------------------------------------------
// "locals" to redirect functions
static task_DispatchFunction tmpTask_array[SCHED_MAX_TASK_SIZE];


// -----------------------------------------------------------------------------
static T_Void task_Helper_Function( TC_Byte taskID, TC_Event anEvent )
{
  if(tmpTask_array[taskID])
    tmpTask_array[taskID](anEvent);
}


// -----------------------------------------------------------------------------
static T_Void task_DispatchFunction_0( TC_Event anEvent )
{
  task_Helper_Function( 0, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void task_DispatchFunction_1( TC_Event anEvent )
{
  task_Helper_Function( 1, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void task_DispatchFunction_2( TC_Event anEvent )
{
  task_Helper_Function( 2, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void task_DispatchFunction_3( TC_Event anEvent )
{
  task_Helper_Function( 3, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void task_DispatchFunction_4( TC_Event anEvent )
{
  task_Helper_Function( 4, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void task_DispatchFunction_5( TC_Event anEvent )
{
  task_Helper_Function( 5, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void task_DispatchFunction_6( TC_Event anEvent )
{
  task_Helper_Function( 6, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void task_DispatchFunction_7( TC_Event anEvent )
{
  task_Helper_Function( 7, anEvent );
}


// -----------------------------------------------------------------------------
// this struct is made available externally...
TCA_Task_array actTaskArray =
{
  task_DispatchFunction_0,
  task_DispatchFunction_1,
  task_DispatchFunction_2,
  task_DispatchFunction_3,
  task_DispatchFunction_4,
  task_DispatchFunction_5,
  task_DispatchFunction_6,
  task_DispatchFunction_7
};


// -----------------------------------------------------------------------------
// Initialize   initializes the task redirections (set to zero)
T_Void tasksRedir_Initialize( T_Void )
{
  T_Int32 i;

  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
    tmpTask_array[i] = 0;
}

// -----------------------------------------------------------------------------
// SetTask      sets the redirection (function pointer) for a given task
T_Void tasksRedir_SetTask( TC_Byte taskID, const task_DispatchFunction redirFunction )
{
  if(taskID < SCHED_MAX_TASK_SIZE)
    tmpTask_array[taskID] = redirFunction;
}

// -----------------------------------------------------------------------------
// GetTask      gets the redirection (function pointer) for a given task
task_DispatchFunction tasksRedir_GetTask( TC_Byte taskID )
{
  if(taskID < SCHED_MAX_TASK_SIZE)
    return tmpTask_array[taskID];
  else
    return 0;
}

// -----------------------------------------------------------------------------
// ClearTask    clears the redirection (function pointer) for a given task
T_Void tasksRedir_ClearTask( TC_Byte taskID)
{
  if(taskID < SCHED_MAX_TASK_SIZE)
    tmpTask_array[taskID] = 0;
}




//--- eof ----------------------------------------------------------------------


