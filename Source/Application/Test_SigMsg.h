//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    Test_SigMsg.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Common Signals and Messages for the Test
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
// 2008-11-26 hh    first design
//------------------------------------------------------------------------------

#ifndef _TEST_SIG_MSG_COMMON_H
#define _TEST_SIG_MSG_COMMON_H

#ifndef _CONFIG_PLATFORM_
#include <Config_Platform.h>
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


// --- check for correct scheduler include
#if __HH_SIMPLE_SCHEDULER_H_VERSION__ < 0x0012
#error "wrong Scheduler.h version included!"
#endif


// --- version check for includes ---
#define __HH_TEST_SIG_MSG_COMMON_H_VERSION__  0x0010


// --- keyboard messages -------------------------------------------------------
// the keyboard is only triggered by timer ticks and the standard messages...

// --- buzzer messages ---------------------------------------------------------
#define MSG_BUZZER_OFF                  ( MSG_FIRST_FREE + 1  )
#define MSG_BUZZER_BEEP                 ( MSG_FIRST_FREE + 2  )
#define MSG_BUZZER_DOUBLE_BEEP          ( MSG_FIRST_FREE + 3  )
#define MSG_BUZZER_TRIPLE_BEEP          ( MSG_FIRST_FREE + 4  )
#define MSG_BUZZER_CONTINUOUS_ON        ( MSG_FIRST_FREE + 5  )
#define MSG_BUZZER_CONTINUOUS_OFF       ( MSG_FIRST_FREE + 6  )
#define MSG_BUZZER_FAST_BEEP_ON         ( MSG_FIRST_FREE + 7  )
#define MSG_BUZZER_FAST_BEEP_OFF        ( MSG_FIRST_FREE + 8  )
#define MSG_BUZZER_SLOW_BEEP_ON         ( MSG_FIRST_FREE + 9  )
#define MSG_BUZZER_SLOW_BEEP_OFF        ( MSG_FIRST_FREE + 10 )
#define MSG_BUZZER_SET_TEST_MMI         ( MSG_FIRST_FREE + 11 )

// --- display messages --------------------------------------------------------
#define MSG_DISPLAY_REDRAW              ( MSG_FIRST_FREE + 1  )
#define MSG_DISPLAY_BLINK_PULSE         ( MSG_FIRST_FREE + 2  )
#define MSG_DISPLAY_CLEAR_VALUE         ( MSG_FIRST_FREE + 3  )
#define MSG_DISPLAY_DRAW_VALUE          ( MSG_FIRST_FREE + 4  )
#define MSG_DISPLAY_CHANGED_UNIT        ( MSG_FIRST_FREE + 5  )
#define MSG_DISPLAY_CHANGED_LOUDNESS    ( MSG_FIRST_FREE + 6  )
#define MSG_DISPLAY_MENU_UNIT           ( MSG_FIRST_FREE + 7  )
#define MSG_DISPLAY_MENU_BEEP_MODE      ( MSG_FIRST_FREE + 8  )
#define MSG_DISPLAY_BATTERY_STATE       ( MSG_FIRST_FREE + 9  )


// --- calculation messages ----------------------------------------------------
// signals
// notify that the Autocal values are here...
#define SIG_AUTOCAL_HERE                SIG_7
// messages
#define MSG_CALC_SHORT_TIMEOUT          ( MSG_FIRST_FREE + 1  )
#define MSG_CALC_DATA_HERE              ( MSG_FIRST_FREE + 2  )
#define MSG_CALC_AUTOCAL_HERE           ( MSG_FIRST_FREE + 3  )




// --- state machine messages --------------------------------------------------
// Key messages:
#define MSG_SM_KEY_ILLEGAL              ( MSG_FIRST_FREE + 1  )
#define MSG_SM_KEY_ON_OFF_SHORT         ( MSG_FIRST_FREE + 2  )
#define MSG_SM_KEY_ON_OFF_MIDDLE        ( MSG_FIRST_FREE + 3  )
#define MSG_SM_KEY_ON_OFF_LONG          ( MSG_FIRST_FREE + 4  )
#define MSG_SM_KEY_ON_OFF_RELEASED      ( MSG_FIRST_FREE + 5  )
#define MSG_SM_KEY_UNIT_SHORT           ( MSG_FIRST_FREE + 6  )
#define MSG_SM_KEY_UNIT_MIDDLE          ( MSG_FIRST_FREE + 7  )
#define MSG_SM_KEY_UNIT_LONG            ( MSG_FIRST_FREE + 8  )
#define MSG_SM_KEY_UNIT_RELEASED        ( MSG_FIRST_FREE + 9  )
#define MSG_SM_KEY_BUZZER_SHORT         ( MSG_FIRST_FREE + 10 )
#define MSG_SM_KEY_BUZZER_MIDDLE        ( MSG_FIRST_FREE + 11 )
#define MSG_SM_KEY_BUZZER_LONG          ( MSG_FIRST_FREE + 12 )
#define MSG_SM_KEY_BUZZER_RELEASED      ( MSG_FIRST_FREE + 13 )
#define MSG_SM_KEY_MODE_SHORT           ( MSG_FIRST_FREE + 14 )
#define MSG_SM_KEY_MODE_MIDDLE          ( MSG_FIRST_FREE + 15 )
#define MSG_SM_KEY_MODE_LONG            ( MSG_FIRST_FREE + 16 )
#define MSG_SM_KEY_MODE_RELEASED        ( MSG_FIRST_FREE + 17 )
#define MSG_SM_KEY_ILLEGAL_RELEASED     ( MSG_FIRST_FREE + 18 )
// Housekeeping messages
#define MSG_SM_HSK_TIMEOUT              ( MSG_FIRST_FREE + 19 )
#define MSG_SM_HSK_POWER_LOW            ( MSG_FIRST_FREE + 20 )
// Calculation messages
#define MSG_SM_CAL_DATA_READY_OK        ( MSG_FIRST_FREE + 21 )
#define MSG_SM_CAL_DATA_READY_NOK       ( MSG_FIRST_FREE + 22 )
#define MSG_SM_CAL_FIRST_TRIGGER        ( MSG_FIRST_FREE + 23 )



// --- remote control messages -------------------------------------------------
// Nothing yet... (for testing)


// --- communication messages --------------------------------------------------
// messages
#define MSG_CMD_COMMAND_HERE            ( MSG_FIRST_FREE + 1  )


// --- housekeeping messages ---------------------------------------------------
// signals
// notify that we should go into powersave mode
#define SIG_HSK_GO_POWERSAVE            SIG_7
// messages
#define MSG_HSK_RESET_TIMEOUT           ( MSG_FIRST_FREE + 1  )
#define MSG_HSK_GO_POWERSAVE            ( MSG_FIRST_FREE + 2  )



//------------------------------------------------------------------------------
#ifdef __cplusplus
} // extern "C"
#ifdef PF_USE_NAMESPACES
} // namespace hh
#endif
#endif // __cplusplus

#endif

//--- eof ----------------------------------------------------------------------

