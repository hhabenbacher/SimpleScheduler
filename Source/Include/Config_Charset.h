//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        Config_Charset.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Character Set configuration
//
//  REFERENCES  see PS200 Documentation
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
// 2003-07-09 hh   first design
//------------------------------------------------------------------------------

#ifndef _CONFIG_CHARSET_
#define _CONFIG_CHARSET_

// -----------------------------------------------------------------------------
// Character Set Configuration TestDevice_Definitions.
//
// This defines the default configuration for supported Char Sets.
// Main usage is the additional support for Unicode

// -----------------------------------------------------------------------------
// Unicode support definitions:
//
//    UNICODE_SUPPORT   support of Unicode Characters
#ifndef CHARSET_DEFINITIONS

//#define UNICODE_SUPPORT

#endif // CHARSET_DEFINITIONS


// -----------------------------------------------------------------------------
// Default Character length for strings TestDevice_Definitions.
//
// This defines the default size of chars for inbuild strings
// On the C-side this may be 1 byte, but for Unicode it may be up to 4 bytes

// -----------------------------------------------------------------------------
// Charlen support definitions:
//
//    DEF_CHARSIZE_C_SIZE        is the default size for C strings (default)
//
//    DEF_CHARSIZE_UNICODE_SIZE  is the default size for Unicode strings
//
#ifndef CHARSET_CHARSIZE_DEFINITIONS

// DEF_CHARSIZE_C_SIZE should be the default if not otherwise defined
#ifndef DEF_CHARSIZE_UNICODE_SIZE
#define DEF_CHARSIZE_C_SIZE
#endif

#ifndef DEF_CHARSIZE_C_SIZE
#define DEF_CHARSIZE_UNICODE_SIZE
#endif

#endif // CHARSET_CHARSIZE_DEFINITIONS



#endif // _CONFIG_CHARSET_

