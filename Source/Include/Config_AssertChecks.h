//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE	    Config_AssertChecks.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Configuration for checks in the device handlers
//
//  REFERENCES  There are no references.
//              Disabling all checks makes the code faster,
//              but make sure that it will be still save!
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
// 2005-02-29 hh   first design
//------------------------------------------------------------------------------

#ifndef _CONFIG_ASSERT_CHECKS_
#define _CONFIG_ASSERT_CHECKS_

// - use assert to check if pointers are valid
#ifndef _MANUAL_ASSERT_CONFIGURATION
#define _ASSERT_CHECK_USE_STRONG
#define _ASSERT_CHECK_USE_WEAK
#endif

// --- macros for asserting
#ifdef _ASSERT_CHECK_USE_STRONG

#include <assert.h>
#define ASSERT_H_INCLUDED
#define ASSERT_STRONG(stmnt) assert((stmnt))
#else
#define ASSERT_STRONG(stmnt)

#endif


// some weak checkes
#ifdef _ASSERT_CHECK_USE_WEAK

#ifndef ASSERT_H_INCLUDED
#include <assert.h>
#endif

#define ASSERT_WEAK(stmnt) assert((stmnt))
#else
#define ASSERT_WEAK(stmnt)
#endif

#define ASSERT_SMALL_EPSILON  (1.0E-16)


#endif  // _CONFIG_ASSERT_CHECKS_




