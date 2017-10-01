//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    Scheduler.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Simple Scheduler interface, based on ideas from PS 20
//              This simplified version assumes that we use only one scheduler
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
// 2008-09-22 hh    first design
//------------------------------------------------------------------------------

#ifndef SCHEDULER_H
#define SCHEDULER_H

#ifndef _CONFIG_PLATFORM_
#include <Config_Platform.h>
#endif

#ifndef _CONFIG_SCHEDULER_
#include <Config_Scheduler.h>
#endif

#ifndef HH_BASICTYPES_H
#include <HH_BasicTypes.h>
#endif


//------------------------------------------------------------------------------
#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
namespace hh {
#endif
extern "C" {
#endif // __cplusplus


// --- version check for includes ---
#define __HH_SIMPLE_SCHEDULER_H_VERSION__  0x0012



// -----------------------------------------------------------------------------
// some task priority levels - don't change here!
#define SCHED_PRIORITY_LOW      ((T_Byte) 0)
#define SCHED_PRIORITY_MEDIUM   ((T_Byte) 1)
#define SCHED_PRIORITY_HIGH     ((T_Byte) 2)

// states for the Events (linkState field)
#define EVENT_STATE_IS_MESSAGE  ((T_Byte) 0)
#define EVENT_STATE_IS_SIGNAL   ((T_Byte) 1)

// some default messages
#define MSG_IDLE                ((T_Byte) 0)
#define MSG_INITIALIZE          ((T_Byte) 1)
#define MSG_RESET               ((T_Byte) 2)
#define MSG_FINALIZE            ((T_Byte) 3)
#define MSG_SYSTICK             ((T_Byte) 4)
#define MSG_MODE_CHANGED        ((T_Byte) 5)
#define MSG_TIM_TICK_SHORT      ((T_Byte) 6)
#define MSG_TIM_TICK_NORMAL     ((T_Byte) 7)
#define MSG_TIM_TICK_LONG       ((T_Byte) 8)
#define MSG_TEST                ((T_Byte) 9)
// first freely useable message
#define MSG_FIRST_FREE          ((T_Byte) 10)

// signal definitions
#define SIG_NONE                ((T_Byte) 0)
#define SIG_1                   ((T_Byte) 1)
#define SIG_2                   ((T_Byte) 2)
#define SIG_3                   ((T_Byte) 4)
#define SIG_4                   ((T_Byte) 8)
#define SIG_5                   ((T_Byte) 16)
#define SIG_6                   ((T_Byte) 32)
#define SIG_7                   ((T_Byte) 64)
#define SIG_8                   ((T_Byte) 128)

// --- some default signals ------------------
#define SIG_SYS_TICK            SIG_1
// --- timing tick signals
// please note, that signals only show that something has happened
// the time may be set in the according software timer
// ---
// a short tick timeout (ca. 0.5s) may be used to indicate blinc toggling
#define SIG_TIMER_TICK_SHORT    SIG_2
// a normal tick timeout (ca. 3s) may be used to signal things like fading out
#define SIG_TIMER_TICK_NORMAL   SIG_3
// a long tick timeout (ca. 10s) may be used to signal things like terminating
#define SIG_TIMER_TICK_LONG     SIG_4
// --- data signals
// shows that some avaited data is here
#define SIG_DATA_HERE           SIG_5
// --- error signals
// shows that something strange has arrived
#define SIG_ERROR_OCCURED       SIG_8



// -----------------------------------------------------------------------------
// definition of an event
// the field linkState may be used in two ways:
//  - in the message queue it is used like a "pointer" for linkage
//  - if sent to a task we use it to distinguish between signals and messages
typedef struct
{
  T_Byte  msg;          // message which should be dispatched or signal
  T_Byte  param;        // message parameter
  T_Byte  taskId;       // target task to which the message should be sent
  T_Byte  linkState;    // internally used link in message queue or state info
} T_Event;              // size: 4 bytes

typedef const T_Event TC_Event;


// -----------------------------------------------------------------------------
// Actual task definitions
//
// Our tasks are based on the idea of "active objects"
// behind every task structure is a state machine which works for a small part
// of the complete task.
// An event is dispatched from the scheduler to the task.
// For a long working task the work may be splitted into smaller sub-parts, the
// task may send itself an event (or signaling) for resuming the work.

typedef T_Void  (*task_DispatchFunction)( TC_Event anEvent ) ;

// our fixed (const) task functions array...
typedef const task_DispatchFunction TCA_Task_array[SCHED_MAX_TASK_SIZE];



// =============================================================================
//  Function description for the Scheduler routines:
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Initialize   initializes the start value - must be called once before
//              the scheduler is used
//
// -----------------------------------------------------------------------------
extern T_Void sched_Initialize( T_Void );

// -----------------------------------------------------------------------------
// Finalize     to bring it down finally...
extern T_Void sched_Finalize( T_Void );


// -----------------------------------------------------------------------------
// Start       Starts the scheduler running
//             If not running, no events are stored or processed.
//
extern T_Void sched_Start( T_Void );


// -----------------------------------------------------------------------------
// Stop        Stops the scheduler running
//             Available events in the queue kept, no events are stored
//             or processed until the scheduler is started again
//
extern T_Void sched_Stop( T_Void );


// -----------------------------------------------------------------------------
// Resume      Resume with higher priority
//             This may be called from long running low priority tasks
//             The scheduler looks if there are signals or events with higher
//             priority than the current running task, if not already in resume
//             mode, the corresponding task is called and runs to completion.
//             then the actual running task will be continued.
//
extern T_Void sched_Resume( T_Void );



// -----------------------------------------------------------------------------
// PostEvent    add an event to the message queue for dispatching
//
//   Parameter:
//      anEvent    (T_Event)        event to be dispatched, see T_Event structure
//      aPriority  (TC_Byte)        priority of event, see SCHED_PRIORITY_* priority levels
//
//   Return:
//      True       (T_Bool)         if posting was successful
//      False      (T_Bool)         if posting was not successful, no error handling
extern T_Bool sched_PostEvent( T_Event anEvent, TC_Byte aPriority );


// -----------------------------------------------------------------------------
// CheckEvent   check if an event is in the message queue for the target task id
//              taskId and msg is minimum for match, optionally parameter
//
//   Parameter:
//      anEvent    (TC_Event)       event to be checked, see T_Event structure
//      matchParam (TC_Bool)        if True it is checked if the same message is in the queue,
//                                  if False it is just checked if there is any message here.
//
//   Return:
//      True       (T_Bool)         there is an event for the task id corresponding to matchParam
//      False      (T_Bool)         there is no event in the queue for the task id corresponding to matchParam
extern T_Bool sched_CheckEvent( TC_Event anEvent, TC_Bool matchParam);

// -----------------------------------------------------------------------------
// CancelEvent  remove an event from the message queue for the target task id
//              taskId and msg is minimum for match, optionally parameter
//
//   Parameter:
//      anEvent    (TC_Event)       event to be canceled, see T_Event structure
//      matchParam (TC_Bool)        if True the matching event in the queue is removed,
//                                  if False the first event in the queue for the task id is removed.
//
//   Return:
//      True       (T_Bool)         the event for the task id corresponding to matchParam was removed
//      False      (T_Bool)         the event for the task id corresponding to matchParam was not removed or found
extern T_Bool sched_CancelEvent( TC_Event anEvent, TC_Bool matchParam);


// -----------------------------------------------------------------------------
// SetSignal    set signals for the tasks of the scheduler
//
//   Parameter:
//      aSignal    (TC_Event)       msg field contains signal(s), see T_Event structure
//      aPriority  (TC_Byte)        priority of event, see SCHED_PRIORITY_* priority levels
//
extern T_Void sched_SetSignal( TC_Event aSignal, TC_Byte aPriority );


// -----------------------------------------------------------------------------
// CheckSignal  check if a signal was set for the target task id
//              taskId and msg is minimum for match
//              it is possible to check for more signals set in parallel
//
//   Parameter:
//      aSignal    (TC_Event)       signal(s) to be checked in msg field, see T_Event structure
//
//   Return:
//      True       (T_Bool)         there is a signal (or signals) set for the corresponding task id
//      False      (T_Bool)         there is no signal set for the corresponding task id
extern T_Bool sched_CheckSignal( TC_Event aSignal );

// -----------------------------------------------------------------------------
// ClearSignal  clear signal(s) set for the target task id (all priorities)
//              taskId and msg is minimum for match
//
//   Parameter:
//      aSignal    (TC_Event)       signal(s) to be checked in msg field, see T_Event structure
//
extern T_Void sched_ClearSignal( TC_Event aSignal );



//------------------------------------------------------------------------------
#ifdef __cplusplus
} // extern "C"
#ifdef PF_USE_NAMESPACES
} // namespace hh
#endif
#endif // __cplusplus

#endif

//--- eof ----------------------------------------------------------------------

