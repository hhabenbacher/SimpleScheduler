//------------------------------------------------------------------------------
//  A simple "Cooperative Scheduler" in "C" with Priorities by Messages
//  License is MIT / BSD / Apache - whatever you prefer  - 2009
//
//  FILE        Test_BasicTypeSize.c
//
//  AUTHOR(S)   Herwig Habenbacher (hh)
//
//  DESCRIPTION Test Size of Basic Types
//
//  REFERENCES  There are no references yet...
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
// 2006-03-24 hh   first design
// 2008-12-16 hh   latest adaption
// 2009-01-12 hh   changed phase table size and structures
// 2009-07-07 hh   adapted to new naming convention
//------------------------------------------------------------------------------

#include <stdio.h>


#ifndef _CONFIG_ASSERT_CHECKS_
#include <Config_AssertChecks.h>
#endif

#ifndef HH_BASICTYPES_H
#include <HH_BasicTypes.h>
#endif


#ifdef PF_USE_NAMESPACES
using namespace hh;
#endif


// --- check for correct type include
#if __HH_BASIC_TYPES_H_VERSION__ != 0x0400
#error "wrong BasicTypes.h version included!"
#endif


// -----------------------------------------------------------------------------
// test if size of structures are the way as expected...
void test_MESBasicTypesSize(void)
{
   printf("--------------------------------------------\n");
   printf("--- Basic Types size test \n");

   // Basic types...
   // special for STMLib 
   ASSERT_STRONG(sizeof(void *)    == 4);
   ASSERT_STRONG(sizeof(TP_Void)   == 4);
   ASSERT_STRONG(sizeof(T_Bool)    == 1);
   // other types
   ASSERT_STRONG(sizeof(T_Byte)    == 1);
   ASSERT_STRONG(sizeof(T_SByte)   == 1);
   ASSERT_STRONG(sizeof(T_Word)    == 2);
   ASSERT_STRONG(sizeof(T_Int16)   == 2);
   ASSERT_STRONG(sizeof(T_Uint16)  == 2);
   ASSERT_STRONG(sizeof(T_Int32)   == 4);
   ASSERT_STRONG(sizeof(T_Uint32)  == 4);
   ASSERT_STRONG(sizeof(T_Real32)  == 4);
   ASSERT_STRONG(sizeof(T_Real64)  == 8);


 //printf("--------------------------------------------\n");
   printf("Basic Types size test: ............. passed!\n");

}





//--- eof ----------------------------------------------------------------------


