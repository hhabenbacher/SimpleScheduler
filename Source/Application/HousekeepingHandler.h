//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        HousekeepingHandler.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Housekeeper handling routines
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
// 2008-11-27 hh    rewritten for new MMI demand
//------------------------------------------------------------------------------
#ifndef __HOUSEKEEPER_HANDLER_H__
#define __HOUSEKEEPER_HANDLER_H__


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



//------------------------------------------------------------------------------
// --- functions -------------------------

extern T_Void HousekeepingHandler_Initialize( T_Void );
extern T_Void HousekeepingHandler_Finalize( T_Void );
extern T_Void HousekeepingHandler_Reset( T_Void );

extern T_Void HousekeepingHandler_Handle( TC_Event anEvent );


//------------------------------------------------------------------------------
#ifdef __cplusplus
} // extern "C"
#ifdef PF_USE_NAMESPACES
} // namespace hh
#endif
#endif // __cplusplus


#endif // __HOUSEKEEPER_HANDLER_H__
