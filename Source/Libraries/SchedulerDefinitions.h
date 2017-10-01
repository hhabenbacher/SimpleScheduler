//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    SchedulerDefinitions.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Definitions for the Scheduler structure and interface
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
// 2008-09-27 hh    first design
//------------------------------------------------------------------------------

#ifndef SCHEDULER_DEFINITIONS_H
#define SCHEDULER_DEFINITIONS_H

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


// -----------------------------------------------------------------------------
// some range and setting definitions
#define SCHED_INVALID_TASK      ((TC_Byte) 0xFF)
#define SCHED_INVALID_MSG       ((TC_Byte) 0xFF)

// some priority levels - freelist should be one higher than the priorities
#define SCHED_EVENT_FREELIST    ((T_Byte) 3)
#define SCHED_PRIORITY_ILLEGAL  ((T_Byte) 0xFF)
// maximum number of levels including free list
#define SCHED_PRIO_FREE_LEVEL   ((T_Byte) 4)

// maximum size of message queue
#define SCHED_MSG_INVALID_POS   ((T_Byte) 0xFF)


// =============================================================================
// -----------------------------------------------------------------------------
// enumerations for scheduler state
typedef enum
{
  eSchedStateIdle        = 0,   // state on startup
  eSchedStateInitialized = 1,   // initialized, but not started
  eSchedStateRunning     = 2,   // running
  eSchedStateStopping    = 3,   // stopping
  eSchedStateFinalizing  = 4    // shut down and finalized
} TE_SchedState;


// -----------------------------------------------------------------------------
// definition of the message queue link, see SCHED_PRIORITY_* and SCHED_EVENT_FREELIST
// This is an array of "pointers" (index) of all priorities and the freelist
// into the message queue. We use stoppers (SCHED_MSG_INVALID_POS) to mark the end.
typedef T_Byte  TA_MsgQueueLink[SCHED_PRIO_FREE_LEVEL];
typedef TC_Byte TCA_MsgQueueLink[SCHED_PRIO_FREE_LEVEL];


// -----------------------------------------------------------------------------
// definition of an task signal
// the idea is that we can use up to 8 signals (bits) with 3 priorities per task
// so some communication may be done via signals instead of messages
typedef struct
{
  T_Byte  sigPrio[3];   // 8 signals with priority low / medium / high
  T_Byte  state;        // additional task state info
} TS_TaskSignal;        // size: 4 bytes



// -----------------------------------------------------------------------------
// Structure for the scheduler
//
// The scheduler stores events posted to them in his message queue, sorted by
// priorities. It then dispatches the available events to the corresponding
// tasks, highest priorities first and then in the order they were posted.
//
// The scheduler starts after the call to sched_Start, until sched_Stop is
// called he accepts incoming posted events.
// If no events are available, the idle function (Task 0) is called.
//
typedef struct
{
  T_Event          msgQueue[SCHED_MSG_QUEUE_SIZE];  // message queue for events
  TS_TaskSignal    signals[SCHED_MAX_TASK_SIZE];    // task signals and state
  TA_MsgQueueLink  queueLinkHead;                   // link for managing the message queue
  TA_MsgQueueLink  queueLinkTail;                   // link for managing the message queue
  T_Event          actEvent;                        // actual scheduled event
  TE_SchedState    state;                           // scheduler state (see TE_SchedState)
  T_Byte           execLevel;                       // only events with priotities higher that that level are dispatched
  T_Bool           isResuming;                      // is in resuming state
  T_Bool           isInterrupted;                   // is in interrupted mode
} TS_Scheduler;                                     



// -----------------------------------------------------------------------------
// typedefs for helper functions

// structure to return search result
typedef struct {
  T_Byte foundPos;   // position in queue
  T_Byte prevLink;   // possible link which points here
  T_Byte prio;       // priority queue
  T_Byte info;       // possible additional info
} TS_MSGsFound;

typedef const TS_MSGsFound TCS_MSGsFound;




//------------------------------------------------------------------------------
#ifdef __cplusplus
} // extern "C"
#ifdef PF_USE_NAMESPACES
} // namespace hh
#endif
#endif // __cplusplus

#endif

//--- eof ----------------------------------------------------------------------

