/*$Workfile: TestRound.cpp$: implementation file
  $Revision: 1$ $Date: 2004-07-09 01:37:08$
  $Author: Darko$

  Test basic string class
  Copyright: CommonSoft Inc.
  2004-06-04 Darko Kolakovic
*/

// Group=Examples

#include <float.h>  //DBL_MANT_DIG
#include <math.h>
#include "stdafx.h"
#include "KMathCst.h" //Round()
#include "KProgCst.h" //SIZEOFARR

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);
extern bool TsWriteToView(const double& dValue);
extern bool TsWriteToViewLn(const double& dValue);

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Validates real number rounding methods.

  Rounding real number x to the nearest integer gives the integer closest to x.
  Half-integers are always rounded to even numbers in order to avoid statistical
  biasing. For example: R(1.5) = 2, R(2.5) = 2, R(3.5) = 4, R(4.5) = 4.
  
  Rounding real number x to the least integer (Ceiling) gives the smallest 
  integer greater than or equal to x. 
  For example: ceil(2.8) = 3.0, ceil(-2.8) = -2.0

  Rounding real number x to the greatest integer (Floor function) gives the 
  largest integer less than or equal to x.
  For example: floor(2.8) = 2.0, floor(-2.8) = -3.0

  The four IEEE rounding modes are supported: rounding to nearest, 
  rounding to negative infinity, rounding to positive infinity, 
  and rounding to zero. 
  Some instructions have the option of using a static rounding mode.
  For example, fcvt.fx.trunc performs conversion of a floating-point number
  to integer using rounding to zero.

  when rounding Reals to Integers we have at least four ways:
1. rounding to -Infinite (floor() in C)
Rounding to minus infinity Always decreases the value of the number 
just remove the redundant bits (truncate)
01.01(1.25) ==> 01.0(1)
10.11(-1.25) ==> 10.1(-1.5)

2. rounding to +Infinite (ceil() in C)
Rounds by adding the MSB of the removed bits to the remaining bits. 
The effect is to round towards plus infinity.
(increases in value)01.01 (1.25 using 4 bits) rounds to 01.1 (1.5 using 3 bits)

3. rounding to nearest

4. rounding to zero
For positive numbers, the redundant bits are truncated
For negative numbers, add MSB of removed bits to the remaining bits. 
The effect is to round towards zero.
01.01 (1.25 using 4 bits) rounds to 01.0 (1 using 3 bits)
10.11 (-1.25 using 4 bits) rounds to 11.0 (-1 using 3 bits)

Rounding to infinity
positive numbers are rounded to plus infinity. MSB of deleted bits is added to the remaining bits
negative numbers are rounded to minus infinity. Redundant bits truncated.
01.01(1.25) ==> 01.1 (1.5) -> round up for positive numbers
10.11 (-1.25) ==> 10.1 (-1.5) -> truncation for negative numbers

ENTIER(x) will provide rounding to -Infinite,
ENTIER(x+0.5D0) should provide rounding to nearest,
-ENTIER(-x) should provide rounding to +Infinite.

IF x>0 THEN RETURN ENTIER(x) ELSE RETURN -ENTIER(-x) END;
should provide rounding to zero.

 round(sj) Convert floating-point to integer, rounding to nearest
 trunc(sj) Convert floating-point to integer, rounding to zero
 ceil(sj) Convert floating-point to integer, rounding up
 floor(sj)  Convert floating-point to integer, rounding down
 

  Returns: true if successful, otherwise returns false.
 */
bool TestRound()
{
TsWriteToView(_T("TestRound()\r\n"));

bool bRes = true;
int i = 0;
  //2^(DBL_MANT_DIG-1) = 4503599627370496.0 max integer value
const double DBL_INTEGER     = ldexp (1.0, DBL_MANT_DIG - 1);
  //2^DBL_MANT_DIG - 1 = 9007199254740991.0
const double DBL_INTEGER_MAX = ldexp (1.0, DBL_MANT_DIG) - 1.0;
  //2^64 = 1.8446744073709552e+019
const double DBL_TOP = ldexp (1.0, 8*8);
struct tagTestRounding
{
  double m_dSource; //real number to test
  double m_dResult; //expected result
} Test[] =
  {
   0.0,                  0.0, // 0
   1.0,                  1.0, // 1
  -1.0,                 -1.0, // 2
   0.5,                  0.0, // 3
   1.5,                  2.0, // 4
  -1.5,                 -2.0, // 5
   2.5,                  2.0, // 6
  -2.5,                 -2.0, // 7
   3.5,                  4.0, // 8
  -3.5,                 -4.0, // 9
   10.1,                10.0, //10
  -10.9,               -11.0, //11 
   DBL_INTEGER_MAX,  DBL_INTEGER_MAX, //12
  -DBL_INTEGER_MAX, -DBL_INTEGER_MAX, //13
   DBL_TOP,          DBL_TOP,         //14
  -DBL_TOP,         -DBL_TOP,         //15
  //2^(DBL_MANT_DIG-1)-1+0.5 = 4503599627370495.5
  ldexp (1.0, DBL_MANT_DIG - 1) - 1.0 + 0.5,  DBL_INTEGER,//16
-(ldexp (1.0, DBL_MANT_DIG - 1) - 1.0 + 0.5),-DBL_INTEGER,//17
  1.0497,                 1.0  //18
  };

TsWriteToView(_T("Maximum value DBL_MAX = "));
TsWriteToViewLn(DBL_MAX);
TsWriteToView(_T("No. of bits in mantissa DBL_MANT_DIG ="));
TsWriteToViewLn(DBL_MANT_DIG);
TsWriteToView(_T("No. of decimal digits of precision DBL_DIG="));
TsWriteToViewLn(DBL_DIG);
TsWriteToView(_T("Maximum decimal exponent DBL_MAX_10_EXP ="));
TsWriteToViewLn(DBL_MAX_10_EXP);
TsWriteToView(_T("Minimum decimal exponent DBL_MIN_10_EXP ="));
TsWriteToViewLn(DBL_MIN_10_EXP);
TsWriteToView(_T("Minimum positive value DBL_MIN="));
TsWriteToViewLn(DBL_MIN);
TsWriteToView(_T("Smallest increment DBL_EPSILON ="));
TsWriteToViewLn(DBL_EPSILON);

  //Test if value is already an integer
if (DBL_INTEGER_MAX != floor(DBL_INTEGER_MAX))
  {
  TsWriteToView(_T("(2^53) - 1 is not an integer on this system!\r\n"));
  Test[12].m_dSource = 12.123456;
  Test[12].m_dResult = 12.0;
  }
if (-DBL_INTEGER_MAX != floor(-DBL_INTEGER_MAX))
  {
  TsWriteToView(_T("-(2^53) + 1 is not an integer on this system!\r\n"));
  Test[13].m_dSource = -12.987654;
  Test[13].m_dResult = -13.0;
  }

  //Test rounding to the integer
TESTENTRY logEntry = 
  {_T("RoundPos(double, unsigned int)"), _T("KMathCst.inl"), false};
while ( (i < SIZEOFARR(Test))/* && bRes*/ )
  {
  double dRounded = Round(Test[i].m_dSource);
  TsWriteToView(_T("Test #"));
  TsWriteToView(i);
  TsWriteToView(_T(":"));
  TsWriteToView(Test[i].m_dSource);
  TsWriteToView(_T("=>"));
  TsWriteToView(dRounded);
  bRes = ( dRounded == Test[i].m_dResult);
  if (!bRes)
    {
    TsWriteToView(_T(":  failed to round "));
    }
  TsWriteToViewLn(_T(""));
  i++;
  }

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-07-09 01:37:08  Darko           
 * $
 *****************************************************************************/

#if 0
//TODO: check negative doubles in KMathCst.inl Round()!
//here is another algorithm
double Round2(double x, int precision) 
{
   int sign;
   double power10, temp_x, result;

   /* Determine the sign of x */
   if (x < 0) 
   {
      sign = -1 ;
   } 
   else 
   {
      sign = 1 ;
   }

   if (precision >= 0)    /* good precision */
   {
      power10 = pow(10.0, (double)precision);

      /* Work with absolute value of x so that
      floor can be used regardless of x's sign */
      temp_x = fabs(x) * power10;

      /* Adding the 0.5 causes the rounding */
      result = sign * floor(temp_x + 0.5) / power10; 

      return(result);
   } 
   else                  /* bogus precision */
   {
      printf("Error: negative precision\n");
      return(x);
   }
}

/*The nearest integer function nint(x) of x, illustrated above and also called nint or the round function, 
is defined such that [x] is the integer closest to x. Since this definition 
is ambiguous for half-integers, the additional rule that half-integers 
are always rounded to even numbers is usually added in order to avoid 
statistical biasing. For example,
  R(1.5) = 2, R(2.5) = 2, R(3.5) = 4, R(4.5) = 4, 
 */

/* scm_round is done using floor(x+0.5) to round to nearest with half-way
+   (ie. when x is an integer plus 0.5) cases going upwards.  Then half-way
+   cases are identified and adjusted down if the round-upwards didn't give
+   the desired even integer.
+
+   "plus_half == result" identifies a half-way case.  If plus_half, which is
+   x + 0.5, is an integer then x must be an integer plus 0.5.
+
+   An odd "result" value is identified with result/2 != floor(result/2).
+   This is done with plus_half, since that value is ready for use sooner in
+   a pipelined cpu, and we're already requiring plus_half == result.
+
+   Note however that we need to be careful when x is big and already an
+   integer.  In that case "x+0.5" may round to an adjacent integer, causing
+   us to return such a value, incorrectly.  For instance if the hardware is
+   in the usual default nearest-even rounding, then for x = 0x1FFFFFFFFFFFFF
+   (ie. 53 one bits) we will have x+0.5 = 0x20000000000000 and that value
+   returned.  Or if the hardware is in round-upwards mode, then other bigger
+   values like say x == 2^128 will see x+0.5 rounding up to the next higher
+   representable value, 2^128+2^76 (or whatever), again incorrect.
+
+   These bad roundings of x+0.5 are avoided by testing at the start whether
+   x is already an integer.  If it is then clearly that's the desired result
+   already.  And if it's not then the exponent must be small enough to allow
+   an 0.5 to be represented, and hence added without a bad rounding.  */
 double
 scm_round (double x)
 {
  double plus_half = x + 0.5;
  double result = floor (plus_half);
  double plus_half, result;

  if (x == floor (x))
    return x;

  plus_half = x + 0.5;
  result = floor (plus_half);
   /* Adjust so that the scm_round is towards even.  */
   return ((plus_half == result && plus_half / 2 != floor (plus_half / 2))
          ? result - 1

/* Copyright (C) 2004 Free Software Foundation, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "config.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

#if HAVE_FENV_H
#include <fenv.h>
#endif

#include "libguile.h"


#define numberof(x)  (sizeof (x) / sizeof ((x)[0]))

static void
test_scm_round ()
{
//Ix86 Microsoft
#define _MCW_RC         0x00000300              /* Rounding Control */
#define _RC_NEAR        0x00000000              /*   near */
#define _RC_DOWN        0x00000100              /*   down */
#define _RC_UP          0x00000200              /*   up */
#define _RC_CHOP        0x00000300              /*   chop */

  /* FE constants are defined only where supported, in particular for
     instance some ARM systems have been seen with only a couple of modes */
  static const int modes[] = {
    0,
#ifdef FE_TONEAREST
    FE_TONEAREST,
#endif
#ifdef FE_UPWARD
    FE_UPWARD,
#endif
#ifdef FE_DOWNWARD
    FE_DOWNWARD,
#endif
#ifdef FE_TOWARDZERO
    FE_TOWARDZERO,
#endif
  };

  double  x, want;
  int  i;

  for (i = 0; i < numberof (modes); i++)
    {
      /* First iteration is the default rounding mode, ie. no call to
         fesetround.  Subsequent iterations are the FE modes from the
         table.  */
      if (i != 0)
        {
#if HAVE_FESETROUND
          fesetround (modes[i]);
#endif
        }

      assert (scm_round (0.0) == 0.0);
      assert (scm_round (1.0) == 1.0);
      assert (scm_round (-1.0) == -1.0);

      assert (scm_round (0.5) == 0.0);
      assert (scm_round (1.5) == 2.0);
      assert (scm_round (-1.5) == -2.0);
      assert (scm_round (2.5) == 2.0);
      assert (scm_round (-2.5) == -2.0);
      assert (scm_round (3.5) == 4.0);
      assert (scm_round (-3.5) == -4.0);

      /* 2^(DBL_MANT_DIG-1)-1+0.5 */
      x = ldexp (1.0, DBL_MANT_DIG - 1) - 1.0 + 0.5;
      want = ldexp (1.0, DBL_MANT_DIG - 1);
      assert (scm_round (x) == want);

      /* -(2^(DBL_MANT_DIG-1)-1+0.5) */
      x = - (ldexp (1.0, DBL_MANT_DIG - 1) - 1.0 + 0.5);
      want = - ldexp (1.0, DBL_MANT_DIG - 1);
      assert (scm_round (x) == want);

      /* 2^DBL_MANT_DIG-1
         In the past scm_round had incorrectly incremented this value, due
         to the way that x+0.5 would round upwards (in the usual default
         nearest-even mode on most systems).  */
      x = ldexp (1.0, DBL_MANT_DIG) - 1.0;
      assert (x == floor (x));      /* should be an integer already */
      assert (scm_round (x) == x);  /* scm_round should return it unchanged */

      /* -(2^DBL_MANT_DIG-1) */
      x = - (ldexp (1.0, DBL_MANT_DIG) - 1.0);
      assert (x == floor (x));      /* should be an integer already */
      assert (scm_round (x) == x);  /* scm_round should return it unchanged */

      /* 2^64 */
      x = ldexp (1.0, 64);
      assert (scm_round (x) == x);

      /* -2^64
         In the past scm_round had incorrectely incremented this value in
         any mode except FE_NEAREST, due to x+0.5 round either up or down to
         the next representable value (an integer).  */
      x = - ldexp (1.0, 64);
      assert (scm_round (x) == x);
    }
}

int
main (int argc, char *argv[])
{
  scm_init_guile();
  test_scm_round ();
  return 0;
}

/*
**  DBLROUND.C - Rounds a double to the nearest whole number
**  public domain by Ross Cottrell
*/

#include <float.h>
#include <limits.h>
#include "snipmath.h"

#if defined(__ZTC__)
 #include <fltenv.h>
 #define SAVEROUND() \
       int fersave = fegetround(); \
       fesetround(FE_TONEAREST)
 #define RESTOREROUND() \
       fesetround(fersave)
#else
 #if !defined(FLT_ROUNDS) || (FLT_ROUNDS != 1)
  #error FLT_ROUNDS needs to be defined to be 1
 #endif
 #define SAVEROUND()
 #define RESTOREROUND()
#endif

double dround(double x)
{
      Boolean_T flag;
      static volatile double X;

      SAVEROUND();
      if (True_ == (flag = (x < 0.0)))
            X = -x;
      else  X = x;
      X += 1.0 / DBL_EPSILON;
      X -= 1.0 / DBL_EPSILON;
      RESTOREROUND();
      return ((flag) ? -X : X);
}
/*Parameters
d 
A Decimal number to be rounded. 
decimals 
The number of significant fractional digits (precision) in the return value. 
Return Value
The number nearest d with precision equal to decimals. If d is halfway between two numbers, one of which is even and the other odd, then the even number is returned. If the precision of d is less than decimals, then d is returned unchanged.

Remarks
The decimals parameter specifies the number of significant fractional digits in the return value and ranges from 0 to 28. If decimals is zero, then a whole number is returned.

The behavior of this method follows IEEE Standard 754, section 4. This kind of rounding is sometimes called rounding to nearest, or banker's rounding. If decimals is zero, this kind of rounding is sometimes called rounding toward zero.

*/
//Any number below five changes down. 
//Any number, five and above changes up.
double dround(double number, int unit)
{
  double e, hoge, d;
  e = pow(10., (double) unit);
  hoge = number * e;
  if (modf(hoge, &d) <= -0.5) {
    d--;
  } else if (modf(hoge, &d) >= 0.5) {
    d++;
  }
  return (double) ((int) d) / e;
}

#define DROUND(l,r) l ^= *(p--); r ^= ((s[((l>>24)&0xff)+0x000]+s[((l>>16)&0xff)+0x100])^s[((l>>8)&0xff)+0x200])+s[((l>>0)&0xff)+0x300]
#define DROUND(x)	((x) >= 0 ? floor((x) + 0.5) : ceil((x) - 0.5))

#endif
