//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        task_Buzzer.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION buzzer task
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
// 2008-10-02 hh    first design
//------------------------------------------------------------------------------

#ifndef __TASK_BUZZER__H__
#define __TASK_BUZZER__H__

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


// =============================================================================
// this task does the Buzzer handling (Beeping, etc) for the Test Device
extern T_Void task_Buzzer( TC_Event anEvent );



//------------------------------------------------------------------------------
#ifdef __cplusplus
} // extern "C"
#ifdef PF_USE_NAMESPACES
} // namespace hh
#endif
#endif // __cplusplus


#endif // __TASK_BUZZER__H__
