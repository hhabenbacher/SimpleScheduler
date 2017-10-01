//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        Scheduler.c
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

//! --- Doxygen comment ---------------------------------------------------------
//! \file    Scheduler.c
//! \brief   Simple Scheduler for non-preemptive tasking
//! \author  Herwig Habenbacher (hh)
//! \version 1.0
//! \date    2008-09-22
//!



#include <string.h>

#ifndef SCHEDULER_H
#include "Scheduler.h"
#endif

#ifndef SCHEDULER_DEFINITIONS_H
#include "SchedulerDefinitions.h"
#endif

#ifndef _CONFIG_PLATFORM_
#include <Config_Platform.h>
#endif

#ifndef _CONFIG_ASSERT_CHECKS_
#include <Config_AssertChecks.h>
#endif

#ifndef _CONFIG_SCHEDULER_
#include <Config_Scheduler.h>
#endif


#ifndef __SCHEDULE_IDLE__H__
#include "schedule_Idle.h"
#endif


//------------------------------------------------------------------------------
#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
using namespace hh;
#endif
#endif


// --- check for correct type include
#if __HH_SIMPLE_SCHEDULER_H_VERSION__ != 0x0012
#error "wrong Scheduler.h version included!"
#endif


// =============================================================================

// --- definitions for testing -------------------------------------------------
// if we are in Unit testing mode, we want access to the some data
// and the functions, otherwise they should be local via static declaration
#ifdef _UNIT_TESTING_PROGRAM_
#define UT_SCHED_STATIC
#else
#define UT_SCHED_STATIC static
#endif

// if no mechanism for critical sections are defined, we use or own (=none)
#ifndef ENTER_CRITICAL_SECTION
#define ENTER_CRITICAL_SECTION
#endif
#ifndef LEAVE_CRITICAL_SECTION
#define LEAVE_CRITICAL_SECTION
#endif




// =============================================================================

// --- external task array reference -------------------------------------------
extern TCA_Task_array actTaskArray;


// --- locals ------------------------------------------------------------------
// Scheduler struct
UT_SCHED_STATIC TS_Scheduler scheduler;



// =============================================================================
// --- constants ---------------------------------------------------------------

//------------------------------------------------------------------------------
// the default start link - only the free list points to the first position
UT_SCHED_STATIC TCA_MsgQueueLink cnstStartHead = {
  (T_Byte) SCHED_MSG_INVALID_POS,   // link to lowest priority events = illegal (no entry)
  (T_Byte) SCHED_MSG_INVALID_POS,   // link to medium priority events = illegal (no entry)
  (T_Byte) SCHED_MSG_INVALID_POS,   // link to high priority events   = illegal (no entry)
  (T_Byte) 0                        // link for managing free list    = first position
};

//------------------------------------------------------------------------------
// the default end link
UT_SCHED_STATIC TCA_MsgQueueLink cnstStartTail = {
  (T_Byte) SCHED_MSG_INVALID_POS,   // link to lowest priority events = illegal (no entry)
  (T_Byte) SCHED_MSG_INVALID_POS,   // link to medium priority events = illegal (no entry)
  (T_Byte) SCHED_MSG_INVALID_POS,   // link to high priority events   = illegal (no entry)
  (T_Byte) (SCHED_MSG_QUEUE_SIZE-1) // link for managing free list    = last position
};

//------------------------------------------------------------------------------
// a default illegal event - unable to be dispatched...
UT_SCHED_STATIC TC_Event cnstStartEvent = {
  (T_Byte) SCHED_INVALID_MSG,       // message which should be dispatched
  (T_Byte) 0,                       // parameter is 0
  (T_Byte) SCHED_INVALID_TASK,      // target task to which the message should be sent
  (T_Byte) SCHED_MSG_INVALID_POS    // internally used link in message queue
};

//------------------------------------------------------------------------------
// priority search order
static TC_Byte cnstPrioSearch[3] = { SCHED_PRIORITY_HIGH, SCHED_PRIORITY_MEDIUM, SCHED_PRIORITY_LOW };

// =============================================================================
//  Helper Functions
// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------
// Scheduler cleanup
//
//   Parameter:
//      isFinalizing (TC_Bool)     if True we finalizing the scheduler,
//                                 otherwise we initializing the scheduler
UT_SCHED_STATIC T_Void sched_Cleanup( TC_Bool isFinalizing)
{
  T_Uint32 i;

  // cleanup all at first
  memset( &scheduler, 0x00, sizeof(TS_Scheduler) );

  // set links for the message queue...
  for(i=0; i<SCHED_PRIO_FREE_LEVEL; i++)
  {
    scheduler.queueLinkHead[i] = cnstStartHead[i];
    scheduler.queueLinkTail[i] = cnstStartTail[i];
  };

  // initialize the message queue
  for(i = 0; i < SCHED_MSG_QUEUE_SIZE; i++)
  {
    scheduler.msgQueue[i] = cnstStartEvent;
    scheduler.msgQueue[i].linkState = (T_Byte)(i + 1);
  };
  // set last entry to illegal value (stopper)
  scheduler.msgQueue[SCHED_MSG_QUEUE_SIZE-1].linkState = SCHED_MSG_INVALID_POS;

  if(isFinalizing)
    scheduler.actEvent.msg = MSG_FINALIZE;
  else
    scheduler.actEvent.msg = MSG_INITIALIZE;

  scheduler.actEvent.param     = 0;
  scheduler.actEvent.linkState = 0;

  // send every task the message to initialize or finalize itself,
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
    if(isFinalizing)
      scheduler.actEvent.taskId = (T_Byte)((SCHED_MAX_TASK_SIZE - 1) - i);
    else
      scheduler.actEvent.taskId = (T_Byte)i;
    if(actTaskArray[scheduler.actEvent.taskId])
      actTaskArray[scheduler.actEvent.taskId]( scheduler.actEvent );
  }

  scheduler.actEvent  = cnstStartEvent;
  scheduler.execLevel = SCHED_PRIORITY_ILLEGAL;

  if(isFinalizing)
    scheduler.state = eSchedStateFinalizing;
  else
    scheduler.state = eSchedStateInitialized;
}


// -----------------------------------------------------------------------------
// sched_getEventPosition  search for an event in the schedulers message queue
//                         we just search the same priority in the linked list
//
//   Parameter:
//
//      anEvent    (TC_Event)      event to be searched, see T_Event structure
//      matchParam (TC_Bool)       if True it is checked if the same message is in the queue,
//                                 if False it is just checked if there is any message here.
//   Return:
//      position   (TS_MSGsFound)  if found it returns the last entry in the queue
//                                 else returns SCHED_MSG_INVALID_POS
//                                 and the priority level
UT_SCHED_STATIC TS_MSGsFound sched_getEventPosition( TC_Event anEvent, TC_Bool matchParam )
{
  TS_MSGsFound found = { SCHED_MSG_INVALID_POS, SCHED_MSG_INVALID_POS, SCHED_PRIORITY_ILLEGAL, 0 };
  T_Int       cnt;   // counter is T_Int because we want to check for >= 0

  // some checks first
  ASSERT_STRONG(anEvent.taskId < SCHED_MAX_TASK_SIZE);

  // we go from highest to lowest priority
  for(cnt=SCHED_PRIORITY_HIGH; cnt >= SCHED_PRIORITY_LOW; cnt--)
  {
    // search only if not already found
    if(found.foundPos == SCHED_MSG_INVALID_POS)
    {
      T_Byte startPos = scheduler.queueLinkHead[cnt];
      T_Byte prevLink = SCHED_MSG_INVALID_POS;

      // only if there are entries...
      if(startPos != SCHED_MSG_INVALID_POS)
      {
        // search in message queue
        do {
          ASSERT_STRONG(startPos < SCHED_MSG_QUEUE_SIZE);
          if((scheduler.msgQueue[startPos].taskId == anEvent.taskId) && (scheduler.msgQueue[startPos].msg == anEvent.msg))
          {
            if(matchParam)
              {
                if( scheduler.msgQueue[startPos].param == anEvent.param)
                {
                  found.foundPos = startPos;
                  found.prevLink = prevLink;
                  found.prio = (T_Byte)cnt;
                }
              }
            else
              {
                found.foundPos = startPos;
                found.prevLink = prevLink;
                found.prio = (T_Byte)cnt;
              }
          }
          prevLink = startPos;
          startPos = scheduler.msgQueue[startPos].linkState;
        } while(startPos != SCHED_MSG_INVALID_POS);
      }
    }
  }

  return found;
} 

// -----------------------------------------------------------------------------
// sched_removeFromEventQueue  remove an event from the message queue for the target task id
//
//   Parameter:
//
//      found      (TCS_MSGsFound) position and priority in the message (Event) queue
//
//   Return:
//      True       (T_Bool)        the event for the task id was removed
//      False      (T_Bool)        the event for the task id was not removed or found
UT_SCHED_STATIC T_Bool sched_removeFromEventQueue( TCS_MSGsFound found)
{
   // if element id found, we remove it from the list
   if(found.foundPos != SCHED_MSG_INVALID_POS)
    {
      ENTER_CRITICAL_SECTION

      ASSERT_STRONG(found.prio < SCHED_PRIO_FREE_LEVEL);

      // remove from the priority list first
      if(scheduler.queueLinkHead[found.prio] == found.foundPos)
        // check if at the beginning of the list
        scheduler.queueLinkHead[found.prio] = scheduler.msgQueue[found.foundPos].linkState;
      else
       {
         T_Byte prior = scheduler.queueLinkHead[found.prio];

         ASSERT_STRONG(prior < SCHED_MSG_QUEUE_SIZE);

         // find event prior to searched one in queue
         while(scheduler.msgQueue[prior].linkState != found.foundPos)
         {
           prior = scheduler.msgQueue[prior].linkState;
           ASSERT_STRONG(prior < SCHED_MSG_QUEUE_SIZE);
         }

         // check again before unlink...
         if(found.prevLink != SCHED_MSG_INVALID_POS)
           scheduler.msgQueue[found.prevLink].linkState = scheduler.msgQueue[found.foundPos].linkState;
       }
      // check if event was last entry in the list...
      if(scheduler.queueLinkTail[found.prio] == found.foundPos)
        scheduler.queueLinkTail[found.prio] = found.prevLink;
        
      // add the freed event to the free list...
      scheduler.msgQueue[found.foundPos] = cnstStartEvent;
      // link it to the start of the freelist
      scheduler.msgQueue[found.foundPos].linkState = scheduler.queueLinkHead[SCHED_EVENT_FREELIST];
      // and point the freelist to the current position
      scheduler.queueLinkHead[SCHED_EVENT_FREELIST] = found.foundPos;

      LEAVE_CRITICAL_SECTION

      return True;
    }
   else
     return False;
}




//------------------------------------------------------------------------------
// sched_getHighestSignalOrEvent
//       get the signal or event with the highest priority
//       the signals have higher priorities as the events
//       if found, clear the signal or remove the event from the message
//       queue for the highest priority (based on same or higher than execLevel)
//       and put the event into actEvent.
//
//   Parameter:
//
//      actPrio    (TC_Byte)       actual priority, we search for signals or
//                                 events with higher priority.
//                                 if prio is SCHED_PRIORITY_ILLEGAL, then all
//                                 priorities are used
//
//   Return:
//      foundPrio  (T_Byte)        if there was an event or signal available
//                                 the found priority is returned.
//                                 if nothing found we return SCHED_PRIORITY_ILLEGAL
UT_SCHED_STATIC T_Byte sched_getHighestSignalOrEvent( TC_Byte actPrio)
{
  TS_MSGsFound found   = { SCHED_MSG_INVALID_POS, SCHED_MSG_INVALID_POS, SCHED_PRIORITY_ILLEGAL, 0  };
  T_Event     tmpESig = { SCHED_INVALID_MSG, 0, SCHED_INVALID_TASK, SCHED_MSG_INVALID_POS };
  T_Byte      cnt, prio, lowPrioCnt, minPrio;
  T_Bool      isSearching;
  T_Bool      hasSignal, hasEvent;
  T_Byte      foundPrio = SCHED_PRIORITY_ILLEGAL;


  // if the actual priority for searching is highest, we do nothing...
  if( actPrio != SCHED_PRIORITY_HIGH)
  {
    lowPrioCnt = 3;
    minPrio    = SCHED_PRIORITY_LOW;

    if( actPrio == SCHED_PRIORITY_LOW)
    {
      lowPrioCnt = 2;
      minPrio    = SCHED_PRIORITY_MEDIUM;
    }
    if( actPrio == SCHED_PRIORITY_MEDIUM)
    {
      lowPrioCnt = 1;
      minPrio    = SCHED_PRIORITY_HIGH;
    }

    // ok, let's try to look for a signal
    isSearching = True;
    for(prio = 0; prio < lowPrioCnt; prio++)
    {
      cnt = 0;
      while( isSearching && (cnt < SCHED_MAX_TASK_SIZE))
      {
        if(scheduler.signals[cnt].sigPrio[cnstPrioSearch[prio]])
        {
          tmpESig.msg       = scheduler.signals[cnt].sigPrio[cnstPrioSearch[prio]];
          tmpESig.param     = 0;
          tmpESig.taskId    = cnt;
          // we store the priority temporarily in the linkState
          tmpESig.linkState = cnstPrioSearch[prio];
          isSearching       = False;
        }
        cnt++;
      }
    }

    // then look if an event is available - highest priority first
    if((scheduler.queueLinkHead[SCHED_PRIORITY_HIGH] != SCHED_MSG_INVALID_POS) && (minPrio <= SCHED_PRIORITY_HIGH))
     {
       found.prio = SCHED_PRIORITY_HIGH;
       found.foundPos = scheduler.queueLinkHead[SCHED_PRIORITY_HIGH];
     }
    else
     {
       if((scheduler.queueLinkHead[SCHED_PRIORITY_MEDIUM] != SCHED_MSG_INVALID_POS) && (minPrio <= SCHED_PRIORITY_MEDIUM))
        {
          found.prio = SCHED_PRIORITY_MEDIUM;
          found.foundPos = scheduler.queueLinkHead[SCHED_PRIORITY_MEDIUM];
        }
       else
        {
          if((scheduler.queueLinkHead[SCHED_PRIORITY_LOW] != SCHED_MSG_INVALID_POS) && (minPrio == SCHED_PRIORITY_LOW))
          {
            found.prio = SCHED_PRIORITY_LOW;
            found.foundPos = scheduler.queueLinkHead[SCHED_PRIORITY_LOW];
          }
        }
     }

    // look if a signal is available
    if((tmpESig.msg != SCHED_INVALID_TASK) && (tmpESig.taskId < SCHED_MAX_TASK_SIZE))
      hasSignal = True;
    else
      hasSignal = False;

    // is an Event here?
    if((found.prio != SCHED_PRIORITY_ILLEGAL) && (found.foundPos != SCHED_MSG_INVALID_POS))
      hasEvent = True;
    else
      hasEvent = False;

    // if both are here, decide over priority...
    if( hasSignal && hasEvent)
    {
      if(found.prio > tmpESig.linkState)
        hasSignal = False;
      else
        hasEvent = False;
    }

    // if there was an event
    if(hasEvent)
    {
      ASSERT_STRONG(found.foundPos < SCHED_MSG_QUEUE_SIZE);
      
      scheduler.actEvent = scheduler.msgQueue[found.foundPos];
      scheduler.actEvent.linkState = EVENT_STATE_IS_MESSAGE;
      if( sched_removeFromEventQueue( found))
        return found.prio;
      else
        return SCHED_PRIORITY_ILLEGAL;
    }

    // if there was an signal
    if(hasSignal)
    {
      foundPrio = tmpESig.linkState;
      scheduler.actEvent = tmpESig;
      scheduler.actEvent.linkState = EVENT_STATE_IS_SIGNAL;
      sched_ClearSignal( tmpESig );
      return foundPrio;
    }

    // otherwise we set the actual scheduler event to illegal values...
    scheduler.actEvent.msg       = SCHED_INVALID_MSG;
    scheduler.actEvent.param     = 0;
    scheduler.actEvent.taskId    = SCHED_INVALID_TASK;
    scheduler.actEvent.linkState = SCHED_MSG_INVALID_POS;
  }

  return foundPrio;
}




// =============================================================================
//  Function for the Scheduler routines:
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Initialize   initializes the start value - must be called once before
//              the scheduler is used
//
// -----------------------------------------------------------------------------
T_Void sched_Initialize( T_Void )
{
  sched_Cleanup( False );
}

// -----------------------------------------------------------------------------
// Finalize     to bring it down finally...
T_Void sched_Finalize( T_Void )
{
  if(scheduler.state == eSchedStateRunning)
    scheduler.state = eSchedStateFinalizing;
  else
    sched_Cleanup( True );
}


// -----------------------------------------------------------------------------
// Start       Starts the scheduler running
//             If not running, no events are stored or processed.
//
T_Void sched_Start( T_Void )
{
  if(scheduler.state != eSchedStateRunning)
  {
    if(scheduler.state != eSchedStateStopping)       // if not stopped...
      if(scheduler.state != eSchedStateInitialized)  // ...and not initialized
        sched_Initialize();                          // initialize!

    // start the dispatching loop
    scheduler.state = eSchedStateRunning;
    do
    {
      TC_Byte newPrio = sched_getHighestSignalOrEvent(scheduler.execLevel);
      // something found?
      if(newPrio != SCHED_PRIORITY_ILLEGAL)
       {
         // some checks first
         ASSERT_STRONG(scheduler.actEvent.taskId < SCHED_MAX_TASK_SIZE);

         // set curr. priority
         scheduler.execLevel = newPrio;

         // dispatch actEvent if task is available
         if(actTaskArray[scheduler.actEvent.taskId])
           actTaskArray[scheduler.actEvent.taskId](scheduler.actEvent);

         // reset curr. priority
         scheduler.execLevel = SCHED_PRIORITY_ILLEGAL;
       }
      else
        doIdleTask();
    } while(scheduler.state == eSchedStateRunning);

    // something makes them stop - verify it was the stopping flag
    if(scheduler.state == eSchedStateFinalizing)
      sched_Cleanup( True );
    else
      scheduler.state = eSchedStateStopping;
  }
}


// -----------------------------------------------------------------------------
// Stop        Stops the scheduler running
//             Available events in the queue kept, no events are stored
//             or processed until the scheduler is started again
//
T_Void sched_Stop( T_Void )
{
  if(scheduler.state == eSchedStateRunning)
    scheduler.state = eSchedStateStopping;
  else
    sched_Cleanup( False );
}

// -----------------------------------------------------------------------------
// Resume      Resume with higher priority
//             This may be called from long running low priority tasks
//             The scheduler looks if there are signals or events with higher
//             priority than the current running task, if not already in resume
//             mode, the corresponding task is called and runs to completion.
//             then the actual running task will be continued.
//
T_Void sched_Resume( T_Void )
{
  // we can resume only if we are in running state and not already resuming
  if((scheduler.state == eSchedStateRunning) && (!scheduler.isResuming))
  {
    // set resuming
    scheduler.isResuming = True;

    {
      TC_Byte newPrio = sched_getHighestSignalOrEvent(scheduler.execLevel);
      // something found?
      if(newPrio != SCHED_PRIORITY_ILLEGAL)
       {
         // some checks first
         ASSERT_STRONG(scheduler.actEvent.taskId < SCHED_MAX_TASK_SIZE);

         // dispatch actEvent if task is available
         if(actTaskArray[scheduler.actEvent.taskId])
           actTaskArray[scheduler.actEvent.taskId](scheduler.actEvent);
       }
    }

    // reset resuming
    scheduler.isResuming = False;
  }
}


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
T_Bool sched_PostEvent( T_Event anEvent, TC_Byte aPriority )
{
  // some checks first
  ASSERT_STRONG(anEvent.taskId < SCHED_MAX_TASK_SIZE);
  ASSERT_STRONG(aPriority < SCHED_EVENT_FREELIST);

#ifdef _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_
  // we allow the posting of events if the scheduler is initialized or running
  if(( scheduler.state == eSchedStateInitialized) || ( scheduler.state == eSchedStateRunning))
#else
  // we only allow the posting of events if the scheduler is running
  if( scheduler.state == eSchedStateRunning)
#endif
  {
    TC_Byte currPos = scheduler.queueLinkHead[SCHED_EVENT_FREELIST];
    T_Byte  lastPos;

    // check for place of the event in the message queue
#ifndef _UNIT_TESTING_PROGRAM_
    ASSERT_STRONG( currPos != SCHED_MSG_INVALID_POS);
#endif
    if(currPos == SCHED_MSG_INVALID_POS)
      return False;

    ENTER_CRITICAL_SECTION

    ASSERT_STRONG( currPos < SCHED_MSG_QUEUE_SIZE);

    // get from freelist, link freelist to next link
    scheduler.queueLinkHead[SCHED_EVENT_FREELIST] = scheduler.msgQueue[currPos].linkState;
    // since actually inserted event is added to the end, we mark with the stopper
    anEvent.linkState = SCHED_MSG_INVALID_POS;
    // insert event
    scheduler.msgQueue[currPos] = anEvent;
    // remember last position first
    lastPos = scheduler.queueLinkTail[aPriority % SCHED_EVENT_FREELIST];
    // now adjust the pointer to the end
    scheduler.queueLinkTail[aPriority % SCHED_EVENT_FREELIST] = currPos;
    // and relink from last entry or insert start position
    if(lastPos == SCHED_MSG_INVALID_POS)
      scheduler.queueLinkHead[aPriority % SCHED_EVENT_FREELIST] = currPos;
    else
     {
       ASSERT_STRONG( lastPos < SCHED_MSG_QUEUE_SIZE);
       scheduler.msgQueue[lastPos].linkState = currPos;
     }

    LEAVE_CRITICAL_SECTION

    return True;
  }

  return False;
}


// -----------------------------------------------------------------------------
// CheckEvent   check if an event is in the message queue for the target task id
//              taskId and msg is minimum for match, optionally parameter
//
//   Parameter:
//      anEvent    (TC_Event)      event to be checked, see T_Event structure
//      matchParam (TC_Bool)       if True it is checked if the same message is in the queue,
//                                 if False it is just checked if there is any message here.
//
//   Return:
//      True       (T_Bool)        there is an event for the task id corresponding to matchParam
//      False      (T_Bool)        there is no event in the queue for the task id corresponding to matchParam
T_Bool sched_CheckEvent( TC_Event anEvent, TC_Bool matchParam)
{
  // some checks first
  ASSERT_STRONG(anEvent.taskId < SCHED_MAX_TASK_SIZE);

#ifdef _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_
  // we allow the checking of events if the scheduler is initialized or running
  if(( scheduler.state == eSchedStateInitialized) || ( scheduler.state == eSchedStateRunning))
#else
  // we only allow the checking of events if the scheduler is running
  if( scheduler.state == eSchedStateRunning)
#endif
  {
    TCS_MSGsFound found = sched_getEventPosition(anEvent, matchParam);

    if(found.foundPos != SCHED_MSG_INVALID_POS)
      return True;
  }

  return False;
}


// -----------------------------------------------------------------------------
// CancelEvent  remove an event from the message queue for the target task id
//              taskId and msg is minimum for match, optionally parameter
//
//   Parameter:
//      anEvent    (TC_Event)      event to be canceled, see T_Event structure
//      matchParam (TC_Bool)       if True the matching event in the queue is removed,
//                                 if False the first event in the queue for the task id is removed.
//
//   Return:
//      True       (T_Bool)        the event for the task id corresponding to matchParam was removed
//      False      (T_Bool)        the event for the task id corresponding to matchParam was not removed or found
T_Bool sched_CancelEvent( TC_Event anEvent, TC_Bool matchParam)
{
  // some checks first
  ASSERT_STRONG(anEvent.taskId < SCHED_MAX_TASK_SIZE);

#ifdef _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_
  // we allow the cancelling of events if the scheduler is initialized or running
  if(( scheduler.state == eSchedStateInitialized) || ( scheduler.state == eSchedStateRunning))
#else
  // we only allow the cancelling of events if the scheduler is running
  if( scheduler.state == eSchedStateRunning)
#endif
  {
    // if element id found, we remove it from the list
    if(sched_removeFromEventQueue( sched_getEventPosition( anEvent, matchParam)))
      return True;
  }

  return False;
}


// -----------------------------------------------------------------------------
// SetSignal    set signals for the tasks of the scheduler
//
//   Parameter:
//      aSignal    (TC_Event)      msg field contains signal(s), see T_Event structure
//      aPriority  (TC_Byte)       priority of event, see SCHED_PRIORITY_* priority levels
//
T_Void sched_SetSignal( TC_Event aSignal, TC_Byte aPriority )
{

  // some checks first
  ASSERT_STRONG(aPriority < SCHED_EVENT_FREELIST);
  ASSERT_STRONG(aSignal.taskId < SCHED_MAX_TASK_SIZE);

  // set the signal(s) for the given priority
  scheduler.signals[aSignal.taskId].sigPrio[aPriority] |= aSignal.msg;
}


// -----------------------------------------------------------------------------
// CheckSignal  check if a signal was set for the target task id
//              taskId and msg is minimum for match
//              it is possible to check for more signals set in parallel
//
//   Parameter:
//      aSignal    (TC_Event)      signal(s) to be checked in msg field, see T_Event structure
//
//   Return:
//      True       (T_Bool)        there is a signal (or signals) set for the corresponding task id
//      False      (T_Bool)        there is no signal set for the corresponding task id
T_Bool sched_CheckSignal( TC_Event aSignal )
{
  ASSERT_STRONG(aSignal.taskId < SCHED_MAX_TASK_SIZE);

  if((scheduler.signals[aSignal.taskId].sigPrio[SCHED_PRIORITY_LOW]    & aSignal.msg) ||
     (scheduler.signals[aSignal.taskId].sigPrio[SCHED_PRIORITY_MEDIUM] & aSignal.msg) ||
     (scheduler.signals[aSignal.taskId].sigPrio[SCHED_PRIORITY_HIGH]   & aSignal.msg))
    return True;
  else
    return False;
}


// -----------------------------------------------------------------------------
// ClearSignal  clear signal(s) set for the target task id (all priorities)
//              taskId and msg is minimum for match
//
//   Parameter:
//      aSignal    (TC_Event)      signal(s) to be checked in msg field, see T_Event structure
//
T_Void sched_ClearSignal( TC_Event aSignal )
{
  T_Byte clearSig;

  // some checks first
  ASSERT_STRONG(aSignal.taskId < SCHED_MAX_TASK_SIZE);

  // negate the bits for clearing - casts to prevent overflow
  clearSig = (T_Byte) (((T_Uint32)(~((T_Uint32)aSignal.msg))) & ((T_Uint32)0x000000ff));

  // clear signal for given tast at all priorities
  scheduler.signals[aSignal.taskId].sigPrio[SCHED_PRIORITY_LOW]    &= clearSig;
  scheduler.signals[aSignal.taskId].sigPrio[SCHED_PRIORITY_MEDIUM] &= clearSig;
  scheduler.signals[aSignal.taskId].sigPrio[SCHED_PRIORITY_HIGH]   &= clearSig;
}


#undef UT_SCHED_STATIC

//--- eof ----------------------------------------------------------------------

