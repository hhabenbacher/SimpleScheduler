//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer
//
//  FILE        Config_CompilerSpecial.h
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Compiler special configuration
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
// 2008-02-13 hh   first design adapted from PS200
//------------------------------------------------------------------------------

#ifndef _CONFIG_COMPILER_SPECIAL_
#define _CONFIG_COMPILER_SPECIAL_

#ifndef _CONFIG_PLATFORM_
#include "Config_Platform.h"
#endif


// -----------------------------------------------------------------------------
// Rowleys Cortex M3 support definitions:
//

// special for Cortex M3
#ifdef PF_EMBEDDED
        #define ATANF(x) atanf(x)
        #define FABSF(x) fabsf(x)
        #define LOGF(x)  logf(x)
	#ifdef _lint
		#define INLINE
		#define _INLINE_
		#define _COMP_CODE_SECT_
	#else
          #ifdef _POLYSPACE_
		        #define INLINE
		        #define _INLINE_
		        #define _COMP_CODE_SECT_
          #else
		        #define INLINE     inline
		        #define _INLINE_   __inline
		        #define _COMP_CODE_SECT_
          #endif
	#endif



#else  // for PC Testing

#define INLINE
#define _INLINE_
#define _COMP_CODE_SECT_
#define ATANF(x) ((T_Real32)atan(x))
#define FABSF(x) ((T_Real32)fabs(x))
#define LOGF(x)  ((T_Real32)log((double)(x)))

#endif // PF_EMBEDDED



#endif // _CONFIG_COMPILER_SPECIAL_

