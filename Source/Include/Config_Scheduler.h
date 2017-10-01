//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    Config_Scheduler.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Configuration for the scheduler
//
//  REFERENCES  There are no references.
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
// 2008-10-07 hh   first design
//------------------------------------------------------------------------------
#ifndef _CONFIG_SCHEDULER_
#define _CONFIG_SCHEDULER_


#ifndef HH_BASICTYPES_H
#include <HH_BasicTypes.h>
#endif


// -----------------------------------------------------------------------------
// maximum number of used tasks
#define SCHED_MAX_TASK_SIZE     ((T_Byte) 8)


// -----------------------------------------------------------------------------
// maximum size of message queue
#define SCHED_MSG_QUEUE_SIZE    ((T_Byte) 32)



// -----------------------------------------------------------------------------
// Supported Insertion of events in initialized state
//
// Otherwise adding events is only allowed in running state...

// --- allow eventhandling at initialisation state
#define _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_



#endif // _CONFIG_SCHEDULER_


