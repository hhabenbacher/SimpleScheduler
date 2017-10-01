//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        BasicTypes.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Basic Types for Measuring Embedded Software.
//              Main usage is for portability, easy and consistent naming for
//              the usage of constant and pointer types
//              As these describes types, all start with a capitalized "T"
//              Before the underline a "C" means constant, and a "P" means pointer
//
//  REFERENCES  there are no References...
//
//------------------------------------------------------------------------------
// Please note corresponding MIT / BSD /Apache License!
//
// This file is not guaranteed by me to be error free. Every effort
// has been made to ensure proper data-types and declarations, but this program
// is distributed WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//------------------------------------------------------------------------------
// HISTORY:
//
// 2006-03-01 hh   first design
// 2007-12-05 hh   added T_Void and standard char / string types (UC Support)
// 2008-09-12 hh   added version check
// 2008-10-08 hh   changed to True and False writing for STM compatibility
// 2008-12-01 hh   changed for Handles to run under Windows if not used
// 2009-07-07 hh   changed for new naming convention / version 0x0400
//------------------------------------------------------------------------------

#ifndef HH_BASICTYPES_H
#define HH_BASICTYPES_H

#ifndef _CONFIG_PLATFORM_
#include "Config_Platform.h"
#endif

#ifndef _CONFIG_CHARSET_
#include "Config_Charset.h"
#endif

#ifdef UNICODE_SUPPORT
#include <tchar.h>
#endif

#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
namespace hh {
#endif
#endif


// --- version check for includes ---
#define __HH_BASIC_TYPES_H_VERSION__  0x0400


// some basic typedefs
typedef void               T_Void;
typedef signed char        T_Int8;
typedef unsigned char      T_Uint8;
typedef unsigned char      T_Byte;
typedef signed char        T_SByte;
typedef short int          T_Int16;
typedef unsigned short int T_Uint16;  // sizeof (T_Uint16) must == 2
typedef unsigned short int T_Word;
typedef long int           T_Int32;
typedef unsigned long int  T_Uint32;  // sizeof (T_Uint32) must == 4
typedef signed int         T_Int;
typedef unsigned int       T_Uint;
typedef float              T_Real32;
typedef double             T_Real64;
typedef double             T_Real;
typedef char               T_Char8;   // Note: see B. Stroustrup "C++" (3rd Edition) C.3.4
typedef unsigned char      T_UChar8;
typedef signed char        T_SChar8;
typedef unsigned short int T_Text16;


// boolean is normally only supported in C++
#ifdef __cplusplus
typedef bool T_Bool;
// some defines to be consistent with C - Code
#ifndef True
#define True  true
#endif
#ifndef False
#define False false
#endif
// now for C - Code
#else
// define boolean type
typedef char T_Bool;
#ifndef False
#define False  0
#endif
#ifndef True
#define True   1
#endif

#endif

// ok, now we define some constant datatypes
typedef const T_Int8     TC_Int8;
typedef const T_Uint8    TC_Uint8;
typedef const T_Byte     TC_Byte;
typedef const T_SByte    TC_SByte;
typedef const T_Int16    TC_Int16;
typedef const T_Uint16   TC_Uint16;
typedef const T_Word     TC_Word;
typedef const T_Int32    TC_Int32;
typedef const T_Uint32   TC_Uint32;
typedef const T_Int      TC_Int;
typedef const T_Uint     TC_Uint;
typedef const T_Real32   TC_Real32;
typedef const T_Real64   TC_Real64;
typedef const T_Real     TC_Real;
typedef const T_Char8    TC_Char8;  
typedef const T_UChar8   TC_UChar8;
typedef const T_SChar8   TC_SChar8;
typedef const T_Text16   TC_Text16;
typedef const T_Bool     TC_Bool;

// now pointer to this types...
typedef T_Void*          TP_Void;
typedef T_Int8*          TP_Int8;
typedef T_Uint8*         TP_Uint8;
typedef T_Byte*          TP_Byte;
typedef T_SByte*         TP_SByte;
typedef T_Int16*         TP_Int16;
typedef T_Uint16*        TP_Uint16;
typedef T_Word*          TP_Word;
typedef T_Int32*         TP_Int32;
typedef T_Uint32*        TP_Uint32;
typedef T_Int*           TP_Int;
typedef T_Uint*          TP_Uint;
typedef T_Real32*        TP_Real32;
typedef T_Real64*        TP_Real64;
typedef T_Real*          TP_Real;
typedef T_Char8*         TP_Char8;
typedef T_UChar8*        TP_UChar8;
typedef T_SChar8*        TP_SChar8;
typedef T_Text16*        TP_Text16;
typedef T_Bool*          TP_Bool;
// pointer to constant types
typedef TC_Int8*         TPC_Int8;
typedef TC_Uint8*        TPC_Uint8;
typedef TC_Byte*         TPC_Byte;
typedef TC_SByte*        TPC_SByte;
typedef TC_Int16*        TPC_Int16;
typedef TC_Uint16*       TPC_Uint16;
typedef TC_Word*         TPC_Word;
typedef TC_Int32*        TPC_Int32;
typedef TC_Uint32*       TPC_Uint32;
typedef TC_Int*          TPC_Int;
typedef TC_Uint*         TPC_Uint;
typedef TC_Real32*       TPC_Real32;
typedef TC_Real64*       TPC_Real64;
typedef TC_Real*         TPC_Real;
typedef TC_Char8*        TPC_Char8;
typedef TC_UChar8*       TPC_UChar8;
typedef TC_SChar8*       TPC_SChar8;
typedef TC_Text16*       TPC_Text16;
typedef TC_Bool*         TPC_Bool;

// and finally some const pointers...
typedef const TP_Void    TCP_Void;
typedef const TP_Int8    TCP_Int8;
typedef const TP_Uint8   TCP_Uint8;
typedef const TP_Byte    TCP_Byte;
typedef const TP_SByte   TCP_SByte;
typedef const TP_Int16   TCP_Int16;
typedef const TP_Uint16  TCP_Uint16;
typedef const TP_Word    TCP_Word;
typedef const TP_Int32   TCP_Int32;
typedef const TP_Uint32  TCP_Uint32;
typedef const TP_Int     TCP_Int;
typedef const TP_Uint    TCP_Uint;
typedef const TP_Real32  TCP_Real32;
typedef const TP_Real64  TCP_Real64;
typedef const TP_Real    TCP_Real;
typedef const TP_Char8   TCP_Char8;
typedef const TP_UChar8  TCP_UChar8;
typedef const TP_SChar8  TCP_SChar8;
typedef const TP_Text16  TCP_Text16;
typedef const TP_Bool    TCP_Bool;
typedef const TPC_Int8   TCPC_Int8;
typedef const TPC_Uint8  TCPC_Uint8;
typedef const TPC_Byte   TCPC_Byte;
typedef const TPC_SByte  TCPC_SByte;
typedef const TPC_Int16  TCPC_Int16;
typedef const TPC_Uint16 TCPC_Uint16;
typedef const TPC_Word   TCPC_Word;
typedef const TPC_Int32  TCPC_Int32;
typedef const TPC_Uint32 TCPC_Uint32;
typedef const TPC_Int    TCPC_Int;
typedef const TPC_Uint   TCPC_Uint;
typedef const TPC_Real32 TCPC_Real32;
typedef const TPC_Real64 TCPC_Real64;
typedef const TPC_Real   TCPC_Real;
typedef const TPC_Char8  TCPC_Char8;
typedef const TPC_UChar8 TCPC_UChar8;
typedef const TPC_SChar8 TCPC_SChar8;
typedef const TPC_Text16 TCPC_Text16;
typedef const TPC_Bool   TCPC_Bool;


#ifdef UNICODE_SUPPORT
typedef wchar_t          T_CharW;
typedef const wchar_t    TC_CharW;
typedef wchar_t*         TP_CharW;
typedef TC_CharW*        TPC_CharW;
typedef const TP_CharW   TCP_CharW;
typedef const TPC_CharW  TCPC_CharW;
#endif

// what is your default string and char representation?
#ifdef UNICODE_SUPPORT

#ifdef DEF_CHARSIZE_UNICODE_SIZE
typedef T_CharW          T_Char;
typedef TC_CharW         TC_Char;
typedef TP_CharW         TP_Char;
typedef TPC_CharW        TPC_Char;
typedef TCP_CharW        TCP_Char;
typedef TCPC_CharW       TCPC_Char;
#else  // DEF_CHARSIZE_UNICODE_SIZE
typedef T_Char8          T_Char;
typedef TC_Char8         TC_Char;
typedef TP_Char8         TP_Char;
typedef TPC_Char8        TPC_Char;
typedef TCP_Char8        TCP_Char;
typedef TCPC_Char8       TCPC_Char;
#endif // DEF_CHARSIZE_UNICODE_SIZE

#else  // UNICODE_SUPPORT
typedef T_Char8          T_Char;
typedef TC_Char8         TC_Char;
typedef TP_Char8         TP_Char;
typedef TPC_Char8        TPC_Char;
typedef TCP_Char8        TCP_Char;
typedef TCPC_Char8       TCPC_Char;
#endif // UNICODE_SUPPORT

// some defines for null values
// maybe on future OS a pointer may not fit into an integer,
// so we differentiate between NULL values and NIL pointers
#ifndef NULL
#define NULL 0
#endif

#ifndef NIL
#ifdef __cplusplus
#define NIL  (TCP_Void(0))
#else
#define NIL  ((TCP_Void)0)
#endif
#endif

#ifdef __cplusplus
#ifdef PF_USE_NAMESPACES
} // namespace hh
#endif
#endif

#endif

//--- eof ----------------------------------------------------------------------

