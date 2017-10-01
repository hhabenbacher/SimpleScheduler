//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	Test_Scheduler.c
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Test Scheduler Functionality
//
//  REFERENCES  There are no references yet...
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
// 2008-09-26 hh    first design
//------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

#ifndef _CONFIG_ASSERT_CHECKS_
#include <Config_AssertChecks.h>
#endif

#ifndef SCHEDULER_H
#include <Scheduler.h>
#endif

#ifndef SCHEDULER_DEFINITIONS_H
#include <SchedulerDefinitions.h>
#endif

#ifndef _CONFIG_SCHEDULER_
#include <Config_Scheduler.h>
#endif

#ifndef SCHEDULE_IDLE_EMU_H
#include <schedule_Idle_emu.h>
#endif

#ifndef TEST_TASK_EMU_H
#include <TestTasks_emu.h>
#endif



#ifdef PF_USE_NAMESPACES
using namespace hh;
#endif



//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif


#ifdef _UNIT_TESTING_PROGRAM_
// extern consts
extern TCA_MsgQueueLink cnstStartHead;
extern TCA_MsgQueueLink cnstStartTail;
extern TC_Event cnstStartEvent;
// "locals"
extern TS_Scheduler scheduler;
// and some functions
extern T_Void sched_Cleanup( TC_Bool isFinalizing );
extern TS_MSGsFound sched_getEventPosition( TC_Event anEvent, TC_Bool matchParam );
extern T_Bool sched_removeFromEventQueue( TCS_MSGsFound found );
extern T_Byte sched_getHighestSignalOrEvent( TC_Byte actPrio );
#else
#error "You have to define _UNIT_TESTING_PROGRAM_ first!"
  crash -*- !!         // dirty trick to enforce you to look here!
#endif


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
//------------------------------------------------------------------------------

#define NUM_TEST_EVENTS    10
#define NUM_TEST_SIGNALS   10
#define NUM_TEST_COMBINED  (NUM_TEST_EVENTS + NUM_TEST_SIGNALS)

// -----------------------------------------------------------------------------
// some consts
static const T_Event cnstTestEvents[NUM_TEST_EVENTS] =
{
  { 1, 0, 0, 0 }, { 2, 0, 0, 0 }, { 3, 0, 0, 0 }, { 4, 0, 0, 0 }, {  5, 0, 0, 0 },
  { 6, 0, 0, 0 }, { 7, 0, 0, 0 }, { 8, 0, 0, 0 }, { 9, 0, 0, 0 }, { 10, 0, 0, 0 }
};

static TC_Byte cnstTestEventPrios[NUM_TEST_EVENTS] = {
  SCHED_PRIORITY_LOW, SCHED_PRIORITY_LOW,  SCHED_PRIORITY_MEDIUM, SCHED_PRIORITY_MEDIUM, SCHED_PRIORITY_LOW,
  SCHED_PRIORITY_LOW, SCHED_PRIORITY_HIGH, SCHED_PRIORITY_HIGH,   SCHED_PRIORITY_LOW,    SCHED_PRIORITY_MEDIUM
};

static const T_Event cnstTestSignals[NUM_TEST_EVENTS] =
{
  { SIG_1, 0, 0, 0 }, { SIG_5, 0, 0, 0 }, { SIG_3, 0, 0, 0 }, { SIG_3, 0, 1, 0 }, { SIG_5, 0, 1, 0 },
  { SIG_1, 0, 1, 0 }, { SIG_5, 0, 2, 0 }, { SIG_3, 0, 2, 0 }, { SIG_1, 0, 2, 0 }, { SIG_3, 0, 3, 0 }
};

static TC_Byte cnstTestSignalPrios[NUM_TEST_EVENTS] = {
  SCHED_PRIORITY_LOW, SCHED_PRIORITY_HIGH, SCHED_PRIORITY_MEDIUM, SCHED_PRIORITY_MEDIUM, SCHED_PRIORITY_HIGH,
  SCHED_PRIORITY_LOW, SCHED_PRIORITY_HIGH, SCHED_PRIORITY_MEDIUM, SCHED_PRIORITY_LOW,    SCHED_PRIORITY_MEDIUM
};

static TC_Byte cnstTestResultMsgOrder1[NUM_TEST_EVENTS] = {
  7, 8, 3, 4, 10, 1, 2, 5, 6, 9
};

static TC_Byte cnstTestResultMsgOrder2[NUM_TEST_COMBINED] = {
  16, 16, 16, 7, 8, 4, 4, 4, 4, 3, 4, 10, 1, 1, 1, 1, 2, 5, 6, 9
};

static const cnstSigPrioSet[4][3] = {
 { SIG_1, SIG_3, SIG_5 },    // Task 0
 { SIG_1, SIG_3, SIG_5 },    // Task 1
 { SIG_1, SIG_3, SIG_5 },    // Task 2
 {     0, SIG_3,     0 }     // Task 3
};

// -----------------------------------------------------------------------------
// some locals
static T_Byte varTestResultMsgOrder1[NUM_TEST_COMBINED];
static T_Byte varTestCnt;


// -----------------------------------------------------------------------------
// do the redirected idle task
static T_Void testTask_IdleTask( T_Void )
{
  // at least we stop the scheduler here...
  sched_Stop();
}

// -----------------------------------------------------------------------------
static T_Void testTask_DispatchCleanupFunction_0( TC_Event anEvent )
{
  // helper function
  if(varTestCnt < NUM_TEST_COMBINED)
  {
    varTestResultMsgOrder1[varTestCnt] = anEvent.msg;
    varTestCnt++;
  }
}


// -----------------------------------------------------------------------------
static T_Void testTask_HelpTaskFunction( TC_Byte TaskId, TC_Event anEvent )
{
   T_Event actEvent = { 0, 0, 0, 0 };

   ASSERT_STRONG(TaskId < SCHED_MAX_TASK_SIZE);

   if(anEvent.msg == 1)
   {
     ASSERT_STRONG(anEvent.param < 64);
     ASSERT_STRONG(varTestResultMsgOrder1[TaskId] < 64);
     varTestResultMsgOrder1[TaskId] += anEvent.param;
     // prepare for resend
     actEvent.msg    = anEvent.msg;
     actEvent.param  = anEvent.param;
     if(TaskId > 0)
       actEvent.taskId = TaskId-1;
     else
      {
        actEvent.msg    = 2;
        actEvent.param  = 2;
        actEvent.taskId = 0;
      }
     sched_PostEvent( actEvent, SCHED_PRIORITY_MEDIUM );
   }

   if(anEvent.msg == 2)
   {
     ASSERT_STRONG(anEvent.param < 64);
     ASSERT_STRONG(varTestResultMsgOrder1[TaskId] < 64);
     varTestResultMsgOrder1[TaskId] += anEvent.param;
     // prepare for resend
     actEvent.msg    = anEvent.msg;
     actEvent.param  = anEvent.param;
     if(TaskId < (SCHED_MAX_TASK_SIZE - 1))
     {
       actEvent.taskId = TaskId+1;
       sched_PostEvent( actEvent, SCHED_PRIORITY_MEDIUM );
     }
   }
}


// -----------------------------------------------------------------------------
static T_Void testTask_DispatchTaskFunction_0( TC_Event anEvent )
{
  testTask_HelpTaskFunction( 0, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void testTask_DispatchTaskFunction_1( TC_Event anEvent )
{
  testTask_HelpTaskFunction( 1, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void testTask_DispatchTaskFunction_2( TC_Event anEvent )
{
  testTask_HelpTaskFunction( 2, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void testTask_DispatchTaskFunction_3( TC_Event anEvent )
{
  testTask_HelpTaskFunction( 3, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void testTask_DispatchTaskFunction_4( TC_Event anEvent )
{
  testTask_HelpTaskFunction( 4, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void testTask_DispatchTaskFunction_5( TC_Event anEvent )
{
  testTask_HelpTaskFunction( 5, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void testTask_DispatchTaskFunction_6( TC_Event anEvent )
{
  testTask_HelpTaskFunction( 6, anEvent );
}

// -----------------------------------------------------------------------------
static T_Void testTask_DispatchTaskFunction_7( TC_Event anEvent )
{
  testTask_HelpTaskFunction( 7, anEvent );
}



// -----------------------------------------------------------------------------
// test if scheduler cleanup behaves the way as expected...
void perform_TestSchedulerCleanup( void )
{
  T_Uint32 i;

  printf(" ...Cleanup test          ");

  // --- set redirections
  idleRedir_SetIdle( testTask_IdleTask );
  tasksRedir_Initialize();
  tasksRedir_SetTask( 0, testTask_DispatchCleanupFunction_0 );


  sched_Initialize();
  ASSERT_STRONG(scheduler.state == eSchedStateInitialized);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  ASSERT_STRONG(scheduler.actEvent.msg       == cnstStartEvent.msg);
  ASSERT_STRONG(scheduler.actEvent.param     == cnstStartEvent.param);
  ASSERT_STRONG(scheduler.actEvent.taskId    == cnstStartEvent.taskId);
  ASSERT_STRONG(scheduler.actEvent.linkState == cnstStartEvent.linkState);

  // there should be no entries for the message queue...
  for(i=0; i<SCHED_PRIO_FREE_LEVEL; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] == cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] == cnstStartTail[i]);
  };

  // there should be no signals
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == 0);
  }

  // ok, now insert some messages...
#ifndef _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_
  // we need a dirty trick here for inserting...
  scheduler.state = eSchedStateRunning;
#endif
  for(i=0; i<NUM_TEST_EVENTS; i++)
  {
    ASSERT_STRONG(sched_PostEvent( cnstTestEvents[i], cnstTestEventPrios[i] ));
    varTestResultMsgOrder1[i] = 0;
  }
#ifndef _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_
  scheduler.state = eSchedStateInitialized;
#endif

  // test
  ASSERT_STRONG(scheduler.state == eSchedStateInitialized);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  ASSERT_STRONG(scheduler.actEvent.msg       == cnstStartEvent.msg);
  ASSERT_STRONG(scheduler.actEvent.param     == cnstStartEvent.param);
  ASSERT_STRONG(scheduler.actEvent.taskId    == cnstStartEvent.taskId);
  ASSERT_STRONG(scheduler.actEvent.linkState == cnstStartEvent.linkState);
  // there should be entries for the message queue...
  for(i=0; i<SCHED_PRIORITY_HIGH; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] != cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] != cnstStartTail[i]);
  };
  // there should be no signals
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == 0);
  }
  varTestCnt = 0;
  // run simplified...
  sched_Start();
  ASSERT_STRONG(scheduler.state == eSchedStateStopping);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  // there should be no entries for the message queue...
  for(i=0; i<SCHED_PRIORITY_HIGH; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] == cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] == cnstStartTail[i]);
  };
  // there should be no signals
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == 0);
  }
  // check the message order
  for(i=0; i<NUM_TEST_EVENTS; i++)
    ASSERT_STRONG( varTestResultMsgOrder1[i] == cnstTestResultMsgOrder1[i] );

  // cleanup
  sched_Cleanup( False );
  ASSERT_STRONG(scheduler.state == eSchedStateInitialized);
  sched_Finalize();
  ASSERT_STRONG(scheduler.state == eSchedStateFinalizing);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  ASSERT_STRONG(scheduler.actEvent.msg       == cnstStartEvent.msg);
  ASSERT_STRONG(scheduler.actEvent.param     == cnstStartEvent.param);
  ASSERT_STRONG(scheduler.actEvent.taskId    == cnstStartEvent.taskId);
  ASSERT_STRONG(scheduler.actEvent.linkState == cnstStartEvent.linkState);

  // there should be no entries for the message queue...
  for(i=0; i<SCHED_PRIO_FREE_LEVEL; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] == cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] == cnstStartTail[i]);
  };

  // there should be no signals
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == 0);
  }

  // --- clear redirections
  idleRedir_ClearIdle();
  tasksRedir_Initialize();

  printf(" - passed \n");
}


// -----------------------------------------------------------------------------
// test if scheduler signals behaves the way as expected...
void perform_TestSchedulerSignals( void )
{
  T_Uint32 i;

  printf(" ...Signals test          ");

  // --- set redirections
  idleRedir_SetIdle( testTask_IdleTask );
  tasksRedir_Initialize();
  tasksRedir_SetTask( 0, testTask_DispatchCleanupFunction_0 );
  tasksRedir_SetTask( 1, testTask_DispatchCleanupFunction_0 );
  tasksRedir_SetTask( 2, testTask_DispatchCleanupFunction_0 );
  tasksRedir_SetTask( 3, testTask_DispatchCleanupFunction_0 );


  sched_Initialize();
  ASSERT_STRONG(scheduler.state == eSchedStateInitialized);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  ASSERT_STRONG(scheduler.actEvent.msg       == cnstStartEvent.msg);
  ASSERT_STRONG(scheduler.actEvent.param     == cnstStartEvent.param);
  ASSERT_STRONG(scheduler.actEvent.taskId    == cnstStartEvent.taskId);
  ASSERT_STRONG(scheduler.actEvent.linkState == cnstStartEvent.linkState);

  // there should be no entries for the message queue...
  for(i=0; i<SCHED_PRIO_FREE_LEVEL; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] == cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] == cnstStartTail[i]);
  };

  // there should be no signals
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == 0);
  }

  // ok, now insert some messages...
#ifndef _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_
  // we need a dirty trick here for inserting...
  scheduler.state = eSchedStateRunning;
#endif
  for(i=0; i<NUM_TEST_EVENTS; i++)
  {
    ASSERT_STRONG(sched_PostEvent( cnstTestEvents[i], cnstTestEventPrios[i] ));
    varTestResultMsgOrder1[i] = 0;
  }
  for(i=0; i<NUM_TEST_SIGNALS; i++)
  {
    sched_SetSignal( cnstTestSignals[i], cnstTestSignalPrios[i] );
    varTestResultMsgOrder1[i+NUM_TEST_EVENTS] = 0;
  }
#ifndef _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_
  scheduler.state = eSchedStateInitialized;
#endif

  // test
  ASSERT_STRONG(scheduler.state == eSchedStateInitialized);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  ASSERT_STRONG(scheduler.actEvent.msg       == cnstStartEvent.msg);
  ASSERT_STRONG(scheduler.actEvent.param     == cnstStartEvent.param);
  ASSERT_STRONG(scheduler.actEvent.taskId    == cnstStartEvent.taskId);
  ASSERT_STRONG(scheduler.actEvent.linkState == cnstStartEvent.linkState);
  // there should be entries for the message queue...
  for(i=0; i<SCHED_PRIORITY_HIGH; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] != cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] != cnstStartTail[i]);
  };
  // there should be no signals
  for(i=0; i<4; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == cnstSigPrioSet[i][0]);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == cnstSigPrioSet[i][1]);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == cnstSigPrioSet[i][2]);
  }

  // some event checking functions...
#ifndef _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_
  // we need a dirty trick here for inserting...
  scheduler.state = eSchedStateRunning;
#endif
  for(i=0; i<NUM_TEST_EVENTS; i++)
  {
    ASSERT_STRONG(sched_CheckEvent( cnstTestEvents[i], False ));
    ASSERT_STRONG(sched_CheckEvent( cnstTestEvents[i], True ));
  }
  ASSERT_STRONG(sched_CancelEvent( cnstTestEvents[7], True));
  ASSERT_STRONG(!sched_CheckEvent( cnstTestEvents[7], False ));
  ASSERT_STRONG(!sched_CheckEvent( cnstTestEvents[7], True ));
  ASSERT_STRONG(sched_PostEvent( cnstTestEvents[7], cnstTestEventPrios[7] ));
  ASSERT_STRONG(sched_CheckEvent( cnstTestEvents[7], False ));
  ASSERT_STRONG(sched_CheckEvent( cnstTestEvents[7], True ));
#ifndef _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_
  scheduler.state = eSchedStateInitialized;
#endif

  // some signaling checking functions...
  for(i=0; i<NUM_TEST_SIGNALS; i++)
    ASSERT_STRONG(sched_CheckSignal( cnstTestSignals[i] ));
  // check adding or removing some signals...
  sched_ClearSignal( cnstTestSignals[0] );
  ASSERT_STRONG(!sched_CheckSignal( cnstTestSignals[0] ));
  sched_SetSignal( cnstTestSignals[0], cnstTestSignalPrios[0] );
  ASSERT_STRONG(sched_CheckSignal( cnstTestSignals[0] ));
  // and to the higher part
  sched_ClearSignal( cnstTestSignals[NUM_TEST_SIGNALS-1] );
  ASSERT_STRONG(!sched_CheckSignal( cnstTestSignals[NUM_TEST_SIGNALS-1] ));
  sched_SetSignal( cnstTestSignals[NUM_TEST_SIGNALS-1], cnstTestSignalPrios[NUM_TEST_SIGNALS-1] );
  ASSERT_STRONG(sched_CheckSignal( cnstTestSignals[NUM_TEST_SIGNALS-1] ));

  varTestCnt = 0;
  // run simplified...
  sched_Start();
  ASSERT_STRONG(scheduler.state == eSchedStateStopping);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  // there should be no entries for the message queue...
  for(i=0; i<SCHED_PRIORITY_HIGH; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] == cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] == cnstStartTail[i]);
  };
  // there should be no signals
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == 0);
  }
  // check the message order
  for(i=0; i<NUM_TEST_COMBINED; i++)
    ASSERT_STRONG( varTestResultMsgOrder1[i] == cnstTestResultMsgOrder2[i] );

  // cleanup
  sched_Cleanup( False );
  ASSERT_STRONG(scheduler.state == eSchedStateInitialized);
  sched_Finalize();
  ASSERT_STRONG(scheduler.state == eSchedStateFinalizing);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  ASSERT_STRONG(scheduler.actEvent.msg       == cnstStartEvent.msg);
  ASSERT_STRONG(scheduler.actEvent.param     == cnstStartEvent.param);
  ASSERT_STRONG(scheduler.actEvent.taskId    == cnstStartEvent.taskId);
  ASSERT_STRONG(scheduler.actEvent.linkState == cnstStartEvent.linkState);

  // there should be no entries for the message queue...
  for(i=0; i<SCHED_PRIO_FREE_LEVEL; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] == cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] == cnstStartTail[i]);
  };

  // there should be no signals
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == 0);
  }

  // --- clear redirections
  idleRedir_ClearIdle();
  tasksRedir_Initialize();

  printf(" - passed \n");
}



// -----------------------------------------------------------------------------
// test if scheduler tasks behaves the way as expected...
void perform_TestSchedulerTasks( void )
{
  TC_Event anEvent = { 1, 1, (SCHED_MAX_TASK_SIZE - 1), 0 };
  T_Uint32 i;

  printf(" ...Tasks test            ");

  // --- set redirections
  idleRedir_SetIdle( testTask_IdleTask );
  tasksRedir_Initialize();
  tasksRedir_SetTask( 0, testTask_DispatchTaskFunction_0 );
  tasksRedir_SetTask( 1, testTask_DispatchTaskFunction_1 );
  tasksRedir_SetTask( 2, testTask_DispatchTaskFunction_2 );
  tasksRedir_SetTask( 3, testTask_DispatchTaskFunction_3 );
  tasksRedir_SetTask( 4, testTask_DispatchTaskFunction_4 );
  tasksRedir_SetTask( 5, testTask_DispatchTaskFunction_5 );
  tasksRedir_SetTask( 6, testTask_DispatchTaskFunction_6 );
  tasksRedir_SetTask( 7, testTask_DispatchTaskFunction_7 );

  sched_Initialize();
  ASSERT_STRONG(scheduler.state == eSchedStateInitialized);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  ASSERT_STRONG(scheduler.actEvent.msg       == cnstStartEvent.msg);
  ASSERT_STRONG(scheduler.actEvent.param     == cnstStartEvent.param);
  ASSERT_STRONG(scheduler.actEvent.taskId    == cnstStartEvent.taskId);
  ASSERT_STRONG(scheduler.actEvent.linkState == cnstStartEvent.linkState);

  // there should be no entries for the message queue...
  for(i=0; i<SCHED_PRIO_FREE_LEVEL; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] == cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] == cnstStartTail[i]);
  };

  // there should be no signals
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == 0);
  }

  // ok, now insert some messages...
#ifndef _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_
  // we need a dirty trick here for inserting...
  scheduler.state = eSchedStateRunning;
#endif
  for(i=0; i<NUM_TEST_EVENTS; i++)
    varTestResultMsgOrder1[i] = 0;
  ASSERT_STRONG(sched_PostEvent( anEvent, SCHED_PRIORITY_MEDIUM ));
#ifndef _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_
  scheduler.state = eSchedStateInitialized;
#endif

  // run simplified...
  sched_Start();
  ASSERT_STRONG(scheduler.state == eSchedStateStopping);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  // there should be no entries for the message queue...
  for(i=0; i<SCHED_PRIORITY_HIGH; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] == cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] == cnstStartTail[i]);
  };
  // there should be no signals
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == 0);
  }
  // check the results order
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
    ASSERT_STRONG( varTestResultMsgOrder1[i] == 3 );

  // cleanup
  sched_Cleanup( False );
  ASSERT_STRONG(scheduler.state == eSchedStateInitialized);
  sched_Finalize();
  ASSERT_STRONG(scheduler.state == eSchedStateFinalizing);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  ASSERT_STRONG(scheduler.actEvent.msg       == cnstStartEvent.msg);
  ASSERT_STRONG(scheduler.actEvent.param     == cnstStartEvent.param);
  ASSERT_STRONG(scheduler.actEvent.taskId    == cnstStartEvent.taskId);
  ASSERT_STRONG(scheduler.actEvent.linkState == cnstStartEvent.linkState);

  // there should be no entries for the message queue...
  for(i=0; i<SCHED_PRIO_FREE_LEVEL; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] == cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] == cnstStartTail[i]);
  };

  // there should be no signals
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == 0);
  }

  // --- clear redirections
  idleRedir_ClearIdle();
  tasksRedir_Initialize();


  printf(" - passed \n");
}


// -----------------------------------------------------------------------------
// test if scheduler tasks resuming behaves the way as expected...
void perform_TestSchedulerTaskResuming( void )
{
  T_Uint32 i;

  printf(" ...Task Resuming test    ");

  // --- set redirections
  idleRedir_SetIdle( testTask_IdleTask );
  tasksRedir_Initialize();
  tasksRedir_SetTask( 0, testTask_DispatchCleanupFunction_0 );
  tasksRedir_SetTask( 1, testTask_DispatchCleanupFunction_0 );
  tasksRedir_SetTask( 2, testTask_DispatchCleanupFunction_0 );
  tasksRedir_SetTask( 3, testTask_DispatchCleanupFunction_0 );


  sched_Initialize();
  ASSERT_STRONG(scheduler.state == eSchedStateInitialized);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  ASSERT_STRONG(scheduler.actEvent.msg       == cnstStartEvent.msg);
  ASSERT_STRONG(scheduler.actEvent.param     == cnstStartEvent.param);
  ASSERT_STRONG(scheduler.actEvent.taskId    == cnstStartEvent.taskId);
  ASSERT_STRONG(scheduler.actEvent.linkState == cnstStartEvent.linkState);

  // there should be no entries for the message queue...
  for(i=0; i<SCHED_PRIO_FREE_LEVEL; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] == cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] == cnstStartTail[i]);
  };

  // there should be no signals
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == 0);
  }

  // ok, now insert some messages...
#ifndef _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_
  // we need a dirty trick here for inserting...
  scheduler.state = eSchedStateRunning;
#endif
  for(i=0; i<NUM_TEST_EVENTS; i++)
  {
    ASSERT_STRONG(sched_PostEvent( cnstTestEvents[i], cnstTestEventPrios[i] ));
    varTestResultMsgOrder1[i] = 0;
  }
  for(i=0; i<NUM_TEST_SIGNALS; i++)
  {
    sched_SetSignal( cnstTestSignals[i], cnstTestSignalPrios[i] );
    varTestResultMsgOrder1[i+NUM_TEST_EVENTS] = 0;
  }
#ifndef _SCHED_ALLOW_EVENTHANDLING_AT_INITSTATE_
  scheduler.state = eSchedStateInitialized;
#endif

  // test
  ASSERT_STRONG(scheduler.state == eSchedStateInitialized);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  ASSERT_STRONG(scheduler.actEvent.msg       == cnstStartEvent.msg);
  ASSERT_STRONG(scheduler.actEvent.param     == cnstStartEvent.param);
  ASSERT_STRONG(scheduler.actEvent.taskId    == cnstStartEvent.taskId);
  ASSERT_STRONG(scheduler.actEvent.linkState == cnstStartEvent.linkState);
  // there should be entries for the message queue...
  for(i=0; i<SCHED_PRIORITY_HIGH; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] != cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] != cnstStartTail[i]);
  };
  // there should be no signals
  for(i=0; i<4; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == cnstSigPrioSet[i][0]);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == cnstSigPrioSet[i][1]);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == cnstSigPrioSet[i][2]);
  }

  varTestCnt = 0;
  // run simplified...
  // we need a dirty trick here for inserting...
  scheduler.state = eSchedStateRunning;
  for(i=0; i<NUM_TEST_COMBINED; i++)
  {
    ASSERT_STRONG( (T_Uint32)varTestCnt == i );
    sched_Resume();
    ASSERT_STRONG( varTestResultMsgOrder1[i] == cnstTestResultMsgOrder2[i] );
  }

  ASSERT_STRONG(scheduler.state == eSchedStateRunning);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  // there should be no entries for the message queue...
  for(i=0; i<SCHED_PRIORITY_HIGH; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] == cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] == cnstStartTail[i]);
  };
  // there should be no signals
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == 0);
  }
  // check the message order
  for(i=0; i<NUM_TEST_COMBINED; i++)
    ASSERT_STRONG( varTestResultMsgOrder1[i] == cnstTestResultMsgOrder2[i] );

  // cleanup
  sched_Cleanup( False );
  ASSERT_STRONG(scheduler.state == eSchedStateInitialized);
  sched_Finalize();
  ASSERT_STRONG(scheduler.state == eSchedStateFinalizing);
  ASSERT_STRONG(scheduler.execLevel == SCHED_PRIORITY_ILLEGAL);
  ASSERT_STRONG(scheduler.actEvent.msg       == cnstStartEvent.msg);
  ASSERT_STRONG(scheduler.actEvent.param     == cnstStartEvent.param);
  ASSERT_STRONG(scheduler.actEvent.taskId    == cnstStartEvent.taskId);
  ASSERT_STRONG(scheduler.actEvent.linkState == cnstStartEvent.linkState);

  // there should be no entries for the message queue...
  for(i=0; i<SCHED_PRIO_FREE_LEVEL; i++)
  {
    ASSERT_STRONG(scheduler.queueLinkHead[i] == cnstStartHead[i]);
    ASSERT_STRONG(scheduler.queueLinkTail[i] == cnstStartTail[i]);
  };

  // there should be no signals
  for(i=0; i<SCHED_MAX_TASK_SIZE; i++)
  {
     ASSERT_STRONG(scheduler.signals[i].sigPrio[0] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[1] == 0);
     ASSERT_STRONG(scheduler.signals[i].sigPrio[2] == 0);
  }

  // --- clear redirections
  idleRedir_ClearIdle();
  tasksRedir_Initialize();

  printf(" - passed \n");
}


// -----------------------------------------------------------------------------
// test if scheduler behaves the way as expected...
void test_Scheduler( void )
{

  printf("--------------------------------------------\n");
  printf("--- Scheduler test \n");

  perform_TestSchedulerCleanup();
  perform_TestSchedulerTasks();
  perform_TestSchedulerTaskResuming();
  perform_TestSchedulerSignals();

//printf("--------------------------------------------\n");
  printf("Scheduler test: .................... passed!\n");
}


//--- eof ----------------------------------------------------------------------



