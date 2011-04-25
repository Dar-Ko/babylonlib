/*$Workfile: TestLimits.c$: implementation file
  $Revision: 3$ $Date: 2007-05-31 16:41:37$
  $Author: Darko Kolakovic$

  Test prototypes limits
  Copyright: CommonSoft Inc.
  2004-09-13 Darko Kolakovic
*/

/* Group=Examples                                                            */
#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);

bool TestLimits();

/*---------------------------------------------------------------------------*/
/*Test implementation-dependent ranges of values allowed for integral
  data types. The constants and are usually defined in <limits.h> header file.

  Returns true if test is successful; otherwise returns false.
 */
bool TestLimits()
{
bool bResult = true;
TsWriteToViewLn(_T("TestLimits()"));
#pragma TODO

TsWriteToViewLn(LOG_EOT);

return bResult;
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-11-25 21:59:31  Darko
 * $
 *****************************************************************************/
#if 0
//PalmPilot Category:	PocketC
//limits.c

#include "limits.h"
//Modified:	Mon 11/09/00 16:12

//PalmPilot Category:	PocketC Lib
//$limits.h
#ifndef LIMITS_H
#define LIMITS_H

//number of bits in a char
#define CHAR_BIT 8

//maximum value of char
#define CHAR_MAX 127

//minimum value of char
#define CHAR_MIN -128

//maximum value of int
#define INT_MAX 2147483647

//minimum value of int
#define INT_MIN -2147483648

//PocketC does not support "long"
//LONG_MAX
//LONG_MIN

//PocketC does not support "short"
//SHRT_MAX
//SHRT_MIN

//PocketC does not support "signed"
//SCHAR_MAX
//SCHAR_MIN

//PocketC does not support "unsigned"
//UCHAR_MAX
//UCHAR_MIN
//UINT_MAX
//ULONG_MAX
//USHRT_MAX

#endif
/*
test_char_limits()
{
  char a,b;

  puts("CHAR_BIT = " + CHAR_BIT);
  puts(" [untested]\n");

  puts("CHAR_MAX = " + CHAR_MAX);
  b = a = CHAR_MAX;
  b++;
  if (a>b) puts(" [pass]\n");
  else puts(" [fail]\n");

  puts("CHAR_MIN = " + CHAR_MIN);
  b = a = CHAR_MIN;
  b--;
  if (a<b) puts(" [pass]\n");
  else puts(" [fail]\n");
}

test_int_limits()
{
  int a,b;

  puts("INT_MAX = " + INT_MAX);
  b = a = INT_MAX;
  b++;
  if (a>b) puts(" [pass]\n");
  else puts(" [fail]\n");

  puts("INT_MIN = " + INT_MIN);
  b = a = INT_MIN;
  b--;
  if (a<b) puts(" [pass]\n");
  else puts(" [fail]\n");
}

limits_main()
{
  clear();
  puts("Demo/Test limits.h\n");
  test_char_limits();
  test_int_limits();
}
*/

/* Definitions of _HUGE and HUGE_VAL - respectively the XENIX and ANSI names
 * for a value returned in case of error by a number of the floating point
 * math routines math.h
 */
#ifdef HUGE_VAL
  #pragma message ("HUGE_VAL")
#endif
#ifdef HUGE
  #pragma message ("HUGE")
#endif
#ifdef _HUGE
  #pragma message ("_HUGE")
#endif

#include <stdio.h>
#include <float.h>
#include <math.h>
#include <fenv.h>

const double infd=(double)1.0/(double)0.0;

void testinf(double v) 
{
  if (v == infd)
    puts("infinity");

  else if (v == DBL_MAX)
    puts("ok nearest");

  else
    puts("error?");
}

int
main()
{
  volatile double max=DBL_MAX;

#if 0
  fesetround (FE_UPWARD);   
#endif

  if (fegetround() == FE_TONEAREST)
    puts ("rounding to nearest");

  testinf(max+(double)1.0);
  testinf(max+max);

  return 0;
}
#endif //0