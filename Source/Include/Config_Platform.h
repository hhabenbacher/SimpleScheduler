//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        Config_Platform.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Platform configuration
//
//  REFERENCES  there are no references yet
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
// 2006-03-15 hh   first design adapted from PS200
//------------------------------------------------------------------------------

#ifndef _CONFIG_PLATFORM_
#define _CONFIG_PLATFORM_

// -----------------------------------------------------------------------------
// Platform support definitions:
//
//    PF_EMBEDDED   Embedded Device
//    PF_Emulation  Emulated Test Software
//    PF_PC_SW      PC Platform Software


// general case (full support)
#ifndef PLATFORM_DEFINITIONS

// on PC Platforms
#if defined(__MSDOS__) || defined(_Windows) || defined(__WIN32__) || defined(__NT__) || defined(__WINDOWS__)
#define PF_PC_SW
#define PLATFORM_ALREADY_DEFINED
#endif

// our default is the Embedded Platform
#ifndef PLATFORM_ALREADY_DEFINED
#define PF_EMBEDDED
#endif

#endif // PLATFORM_DEFINITIONS


// for embedded systems we don't use namespaces...
#ifndef PF_EMBEDDED
#ifdef __cplusplus
//#define PF_USE_NAMESPACES
#endif
#endif


#endif // _CONFIG_PLATFORM_

