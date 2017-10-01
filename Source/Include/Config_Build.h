//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        Config_Build.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Build configuration
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
// 2008-11-26 hh   first design after need for special builds
// 2008-12-04 hh   added special builds for individual phase tables
// 2009-02-09 hh   adapted to be configured for testing
// 2009-12-02 hh   adapted for build configurations 
//------------------------------------------------------------------------------

#ifndef _CONFIG_BUILD_
#define _CONFIG_BUILD_

// -----------------------------------------------------------------------------
// Build support definitions:
//
//    BUILD_RELEASE   Build final running device
//    BUILD_DEMO_RUN  Build demo version, constant and variable data are defaults
//    BUILD_DEMO_TST  Build demo version, like Run, but SerialNum = 0

// please outcomment the one you want to use
//#define BUILD_RELEASE
#define BUILD_DEMO_RUN
//#define BUILD_DEMO_TST



// for the demo version we use some common defines
#if defined(BUILD_DEMO_RUN) || defined(BUILD_DEMO_TST)
#define _BUILD_DEMO_VERSION_WITHOUT_SETTINGS_
#endif

#endif // _CONFIG_BUILD_

