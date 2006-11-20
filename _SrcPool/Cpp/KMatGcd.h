/*$Workfile: KMatGcd.h$: header file
  $Revision: 7$ $Date: 2005-06-20 17:20:39$
  $Author: Darko Kolakovic$

  Greatest common divisor (gcd)
  Copyright: CommonSoft Inc
  ~300 BC Euclid
  Dec '89 Darko Kolakovic
 */
// Group=Mathematics

#ifndef _KMATGCD_H_
    /*$Workfile: KMatGcd.h$ sentry */
  #define _KMATGCD_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Inlines
#ifdef __cplusplus
//-----------------------------------------------------------------------------
/*Calculates the greatest common divisor of two integers.
  The greatest common divisor (gcd) or highest common factor (hcf) is the
  largest integer that divides two numbers without a remainder.
  The numbers that have no factors in common, except 1, are said to be coprime
  or relatively prime.

  This implementation is based on Euclid's algorithm for whole numbers:
      gcd(A,B) = gcd(A, A mod B),
  where (A mod B) is the remainder of division of A by B.

  Properties of GCD:
  - gcd(KA, KB) = K gcd(A, B)
  - If gcd(A,B) = 1 then gcd(A,KB) = gcd(A,K)
  - gcd(A, B) = gcd(A - B, B)

  Returns: the greatest common divisor of two integers or 0 if both operands
  are equal to zero:
      gcd(0, 0) = 0.

  See also: Euclid, Elements, Book 7, Propositions 1-2 (Samizdat, ~300 BC),
  lcm()

  History: Euclid, ~300 BC
 */
template <typename TYPE>
TYPE GreatestCommonDivisor(TYPE Operand1, //[in] first operand
                           TYPE Operand2  //[in] second operand
                          )
{
  /*Euclid's division algorithm:
    0. Obtain two positive integers A and B, A >= B.
    1. Get the remainder of dividing A by B
    2. If remainder is zero, then B is GCD.
    3. If not, find GCD of B and remainder (step 0.)
   */

  //Get absolute value of operands
if (Operand1 < 0)
  Operand1 = -Operand1;

if (Operand2 < 0)
  Operand2 = -Operand2;

while (Operand2 != 0)
  {
  TYPE nRemainder = Operand1 % Operand2;
  Operand1 = Operand2;
  Operand2 = nRemainder;
  }

return Operand1;
}

/*Calculates the greatest common divisor of two whole numbers.

  TODO: move to KMatGcdDouble.inl

  Example:
        #include <math.h>
        #include "KMatGcd.h"
        ...
        double dGcd = GreatestCommonDivisor<double>(4294967295.0 ,2147483646.0);
        bool bRes = (3.0 == lGcd);
        std::_tcout << _T("gcd(") << 4294967295 << _T(", ")
                                  << 2147483646 << _T(") = ")
                    << dGcd << _T(" == ") << (tbool)bRes << std::endl;

 */
template <> inline
double GreatestCommonDivisor<double>(double Operand1, //[in] whole number as
                                                      //first operand
                                     double Operand2  //[in] whole number as
                                                      //second operand
                                    )
{
if (Operand2 == 0)
  return Operand1;

if (Operand1 == 0)
  return Operand2;

  //Get absolute value of operands
if (Operand1 < 0)
  Operand1 = -Operand1;

if (Operand2 < 0)
  Operand2 = -Operand2;

while (Operand2 != 0)
  {
  double nRemainder = fmod(Operand1, Operand2);
  Operand1 = Operand2;
  Operand2 = nRemainder;
  }

return Operand1;
}

//-----------------------------------------------------------------------------
/*Calculates the greatest common divisor of a vector of two whole numbers.
  The greatest common divisor of three or more integers is the largest integer
  that divides all the numbers without a remainder.

  This implementation uses GCD associativity:
      gcd(A, B, C) = gcd(A, gcd(B, C)) = gcd(gcd(A, B), C).

  Returns: the greatest common denominator of a vector of whole numbers
  positive integers. Result is undefined if nCount is 0.

  See also: gcd()
 */
template <typename TYPE>
TYPE GreatestCommonDivisor(TYPE nArray[], //[in] array of whole numbers
                           size_t nCount  //[in] number of elements in the array
                                          //[1, n]
                          )
{
ASSERT(nCount > 0);
ASSERT(nArray != NULL);

TYPE nGcd = nArray[0];
if (nGcd < 0)
  nGcd = -nGcd;

size_t i = 1;
while (i < nCount)
  {
  nGcd = GreatestCommonDivisor<TYPE>(nGcd, nArray[i++]);
  }
return nGcd;
}

///////////////////////////////////////////////////////////////////////////////
// C compilation
#else
  long gcd(long Operand1, long Operand2);

#endif //__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif //_KMATGCD_H_

/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-06-03 16:18:22  Darko Kolakovic
 * $
 *   Dec '89 Darko Kolakovic C version
 *   ~300 BC Euclid
 ******************************************************************************/
