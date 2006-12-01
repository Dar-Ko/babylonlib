/*$Workfile: KMatGcd.c$: implementation file
  $Revision: 16$ $Date: 2005-09-08 17:13:07$
  $Author: Darko Kolakovic$

  greatest common divisor (gcd)
  Dec '89 Darko Kolakovic
  1967 Josef Stein
  1962 R.Silver, J.Tersian
*/

/* Group=Mathematics                                                          */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)        */

#ifdef _DEBUG
  #ifndef TCHAR
    #include "KTChar.h"
  #endif
  #ifndef __TFILE__
    #include "KTrace.h"
  #endif
  static TCHAR THIS_FILE[] = __TFILE__;
#endif

/*----------------------------------------------------------------------------*/
/*Calculates the greatest common divisor of two integers.
  The greatest common divisor (gcd) or highest common factor (hcf) is the
  largest integer that divides two numbers without a remainder.
  If their greatest common divisor is 1, the numbers are called coprime or
  relatively prime.

  This implementation is based on binary algorithm.

  Properties of GCD:
   - gcd(KA, KB) = K gcd(A, B)
   - if gcd(A,B) = 1, then gcd(A,KB) = gcd(A,K)
   - gcd(A,B) = gcd(A-B,B)

  Returns: the greatest common divisor of two integers or 0 if both operands
  are equal to zero.

  See also: Donald E. Knuth, The Art of Computer Programming,
            Volume 2: Seminumerical Algorithms (Addison-Wesley, 1998),
            section 4.5.2 (The Greatest Common Divisor);
            Josef. Stein, Computational problems associated with Racah algebra,
            Journal of Computational Physics (1:397-405, 1967).

  History: 1962 R.Silver, J.Tersian binary algorithm;
           2001 Bruno Haible <bruno@clisp.org>
 */
long gcd(long Operand1, //[in] first whole number
         long Operand2  //[in] second whole number
        )
{
/*binary algorithm

  gcd(A,B) = 2^(min(Val2(A),Val2(B)))*gcd(A/(2^Val2(A)),B/(2^Val2(B))

  Val2(x) denotes the dyadic valuation of the positive integer x,
  i.e. the greatest integer k such that 2^k | x. In another words, k is the
  number of trailing zero bits in the binary representation of x.

  The algorithm uses the following properties:
  - gcd(2a, 2b) = 2 gcd(a, b), both operands are even gcd(A,B) = 2 gcd(A/2, B/2);
  - gcd(2a+1, 2b) = gcd(2a+1, b), one operand is odd, other is even
    gcd(A,B) = gcd(A, B/2);
  - (2a+1)-(2b+1) = 2(a-b) the difference of two odd numbers is even and
    |A-B| < max(A,B);
  - gcd(2a+1, 2b+1) = gcd(2b+1, a-b), both operands are odd
    gcd(A,B) = gcd(B, |A-B|/2).

  It consists of eliminating the least significant bit at each loop iteration.
  Knuth [20,§4.5.2] quotes text "Chiu Chang Suan Shu" [~100 AD, China]:
  - If halving is possible, take half.
  - Otherwise write down the denominator and the numerator and subtract
    the smaller from the greater.
  - Repeat until both numbers are equal.
  - Simplify with this common value.

  0. Obtain two positive integers A and B.
     If B = 0, return A;
     If |B| > |A|, return gcd(B, A)
  1. If A and B are even, gcd(A, B) = n gcd(N/n, M/n), n = 2^k, k[1,N],
     n is power of two, dividing both even operands.

     A or B (or both) are odd now;
  2. If A is even while B is odd, then gcd(A, B) = gcd(A/2, B);
     if A is odd while B is even, then gcd(A, B) = gcd(A, B/2);
     if A and B are odd, then gcd(A, B) = gcd(|A-B|/2,B)
 */

long lTemp; /*mask used bitwise parity validation
         */

  /*Insure that both numbers are non-negative whole numbers
   */
if (Operand2 == 0)
  return Operand1;

if (Operand1 == 0)
  return Operand2;

  /*Get absolute value of operands
   */
if (Operand1 < 0)
  Operand1 = -Operand1;
if (Operand2 < 0)
  Operand2 = -Operand2;

lTemp = Operand1 | Operand2;
lTemp = lTemp ^ (lTemp - 1); /* lTemp = 2^(k+1)-1 = odd number*/

/*Reduction of an even number by 2 eliminates trailing bit(0) */
while ((Operand1 & lTemp) == 0) /* A % 2^k == 0; A is even number */
  Operand1 >>= 1;           /* A = A/2 */

while ((Operand2 & lTemp) == 0) /* B % 2^k == 0; B is even number */
  Operand2 >>= 1;           /* B = B/2 */

while (Operand1 != Operand2)
  {
  /*T = |A-B|/2*/
  if (Operand1 > Operand2)
    {
    Operand1 = Operand1 - Operand2;
    do /*Reduction of an even number by 2 eliminates trailing bit(0) */
      Operand1 >>= 1; /* A = A/2 */
    while ((Operand1 & lTemp) == 0);
    }
  else
    {
    Operand2 = Operand2 - Operand1;
    do
      Operand2 >>= 1; /* B = B/2 */
    while ((Operand2 & lTemp) == 0);
    }
  }

return Operand1; /* A = B = gcd(A, B) */
}

/* ///////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 *$Log:
 * 13   Biblioteka1.12        2005-06-15 11:40:14  Darko Kolakovic Shortened while
 *      loop
 * 12   Biblioteka1.11        2005-06-14 17:58:45  Darko Kolakovic rolled back to
 *      original 1999 version
 * 11   Biblioteka1.10        2005-06-08 17:16:51  Darko Kolakovic comment
 * 10   Biblioteka1.9         2005-06-07 14:29:53  Darko Kolakovic Comments
 * 9    Biblioteka1.8         2005-06-06 17:14:05  Darko Kolakovic
 * 8    Biblioteka1.7         2005-06-03 16:18:32  Darko Kolakovic
 * 7    Biblioteka1.6         2005-06-01 17:14:34  Darko Kolakovic pragma
 * 6    Biblioteka1.5         2005-05-31 17:06:33  Darko Kolakovic comment
 * 5    Biblioteka1.4         2005-05-30 14:49:20  Darko Kolakovic comment
 * 4    Biblioteka1.3         2005-05-30 09:51:03  Darko Kolakovic comment
 * 3    Biblioteka1.2         2005-05-26 15:41:09  Darko Kolakovic Example
 * 2    Biblioteka1.1         2005-04-20 13:09:49  Darko Kolakovic comments
 * 1    Biblioteka1.0         2004-11-12 17:55:53  Darko Kolakovic
 *$
 *      Jan 1999 Darko Kolakovic implemented binary algorithm
 *      Dec 1989 Darko Kolakovic implemented Euclid's algorithm
 *          1962 R.Silver, J.Tersian binary algorithm
 *****************************************************************************/

/*Calculates the greatest common divisor of two integers.
  1999 Darko Kolakovic implemented binary algorithm v0.1

#include "KMathCst.h"

long gcd(long Operand1, //[in] first whole number
         long Operand2  //[in] second whole number
        )
/ *binary algorithm v0.1

  gcd(A,B) = 2^(min(Val2(A),Val2(B)))*gcd(A/(2^Val2(A)),B/(2^Val2(B))

  Val2(x) denotes the dyadic valuation of the positive integer x,
  i.e. the greatest integer k such that 2^k | x. In another words, k is the
  number of trailing zero bits in the binary representation of x.

  The algorithm uses the following properties:
  - gcd(2a, 2b) = 2 gcd(a, b), both operands are even gcd(A,B) = 2 gcd(A/2, B/2);
  - gcd(2a+1, 2b) = gcd(2a+1, b), one operand is odd, other is even
    gcd(A,B) = gcd(A, B/2);
  - (2a+1)-(2b+1) = 2(a-b) the difference of two odd numbers is even and
    |A-B| < max(A,B);
  - gcd(2a+1, 2b+1) = gcd(2b+1, a-b), both operands are odd
    gcd(A,B) = gcd(B, |A-B|/2).

  It consists of eliminating the least significant bit at each loop iteration.
  Knuth [20,§4.5.2] quotes text "Chiu Chang Suan Shu" [~100 AD, China]:
  - If halving is possible, take half.
  - Otherwise write down the denominator and the numerator,
  - and subtract the smaller from the greater.
  - Repeat until both numbers are equal.
  - Simplify with this common value.

  0. Obtain two positive integers A and B.
     If B = 0, return A;
     If |B| > |A|, return gcd(B, A)
  1. If A and B are even, gcd(A, B) = n gcd(N/n, M/n), n = 2^k, k[1,N],
     n is power of two, dividing both even operands.

     n = 1
     while (A is even and B is even)
       {
       A = A/2     (A = A >> 1)
       B = B/2     (B = B >> 1)
       n = 2*n     (n = n << 1)
      }
     A or B (or both) are odd;
  2. If A is even while B is odd, then gcd(A, B) = gcd(A/2, B);
     if A is odd while B is even, then gcd(A, B) = gcd(A, B/2);
     if A and B are odd, then gcd(A, B) = gcd(|A-B|/2,B)

     while (A > 0)
       {
       Get a half of the even operand;
       if A is even, A = A/2
       else if B is even, B = B/2
       else
         {
         t = |A-B|/2
         if A < B, then B = t else A = t
         }
       }

  3. GCD = n*B
 * /
long n = 1; //greatest power of 2 (2^k) that
            //divides both even operands; 1 if at least one is odd.

long lTemp = 0;//Get greatest power of 2 dividing both even operands

while(IsEvenInt (Operand1) && IsEvenInt (Operand2))
  {
  n <<= 1;        // n = n*2
  Operand1 >>= 1; // A = A/2
  Operand2 >>= 1; // B = B/2
  }

if (IsOddInt (Operand1))
  lTemp = -Operand2;
else
  lTemp = Operand1 >> 1;

do
  {
    //T = |A-B|/2
  if (IsEvenInt (lTemp))
    lTemp = lTemp >> 1;
  else
    {
    if (lTemp > 0)
      Operand1 = lTemp;
    else
      Operand2 = -lTemp;

    lTemp = Operand1 - Operand2;
    }
  } while (lTemp != 0);

return Operand1 * n; //GCD = n*B
}
*/
