/*$Workfile: TestLimits.c$: implementation file
  $Revision: 1$ $Date: 2004-11-25 21:59:31$
  $Author: Darko$

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

TsWriteToViewLn(LOG_EOT);

return bResult;
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-25 21:59:31  Darko           
 * $
 *****************************************************************************/

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