//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    Config_Timer.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Configuration for the timer
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
// 2008-11-27 hh   first design
//------------------------------------------------------------------------------
#ifndef _CONFIG_TIMER_
#define _CONFIG_TIMER_


// -----------------------------------------------------------------------------
// maximum number of used timers
#define SW_TIMER_MAX_TIMER     (16)



// -----------------------------------------------------------------------------
// Configuration of the timer ticks intervall time
//

// --- define in which intervall time in [ms] the ticks are coming
#define TICK_INTERVALL_TIME_MS  (25UL)



#endif // _CONFIG_TIMER_TICK_


