//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    TestTimer.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Test Timer defines
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
// 2008-10-23 hh    first design
//------------------------------------------------------------------------------

#ifndef TEST_TIMER_H
#define TEST_TIMER_H

// definition of the used timer numbers for the Test
#define TIMER_KEYBOARD_TICK               0
#define TIMER_BUZZER_TICK                 1
#define TIMER_DISPLAY_BLINK               2
#define TIMER_DISPLAY_FADEOUT             3
#define TIMER_DISPLAY_TIMEOUT             4
#define TIMER_STATE_BLINK                 5
#define TIMER_STATE_FADEOUT               6
#define TIMER_STATE_TIMEOUT               7
#define TIMER_CALC_SHORTTIMEOUT           8
#define TIMER_RESERVED                    9
#define TIMER_CLL_REC_TIMEOUT            10
#define TIMER_CLL_WDG_TIMEOUT            11
#define TIMER_HOUSEKEEPING_LO_POWERMODE  12
#define TIMER_HOUSEKEEPING_HI_POWERMODE  13
#define TIMER_HOUSEKEEPING_UPDATE        14
#define TIMER_POWER_OFF                  15


#endif

//--- eof ----------------------------------------------------------------------


