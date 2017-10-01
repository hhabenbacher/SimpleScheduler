//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer-2011
//
//  FILE	    Version.h
//
//  AUTHOR(S)   Herwig  Habenbacher (MESh)
//
//  DESCRIPTION Tracking of version numbering
//
//  REFERENCES  no references
//              About Numbering: 3 Values: Maj.Min.Build
//                Major = Main Version Number   (Architecture)
//                Minor = Minor Version Number  (Release)
//                Build = Build (Bugfixing without Interface changes)
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
// 2009-09-02 hh    first design
// 2011-01-07 hh    V1.0.0   Catchup from high Level Code
//------------------------------------------------------------------------------

#ifndef __TEST_VERSION__H__
#define __TEST_VERSION__H__

// Version numbering Software
#define TEST_SoftW_VERS_MAJOR   1
#define TEST_SoftW_VERS_MINOR   0
// build may be up to 99
#define TEST_SoftW_VERS_BUILD   0

// Version numbering Hardware
// major may be up to 9
#define TEST_HardW_VERS_MAJOR   1
// minor may be up to 9
#define TEST_HardW_VERS_MINOR   0
#define TEST_HardW_VERS_BUILD   0

// Some more information
#define TEST_DEVICE       "TEST"
#define TEST_COMPANY      "Testing Corp."
#define TEST_COPYRIGHT    "(c) Testing Corp. 1994 - 2017, Cyberspace"
#define TEST_VERS_DATE    "2017-10-01"

#define TEST_HW_VERSION   "1.0.00"
#define TEST_SW_VERSION   "1.0.00"


#endif // __TEST_VERSION__H__

