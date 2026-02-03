/*$Workfile: KMatLcm.h$: header file
  $Revision: 3$ $Date: 2005-06-20 16:20:04$
  $Author: Darko Kolakovic$

  Least common multiple (lcm)
  Copyright: CommonSoft Inc
  2005-05-17 Darko Kolakovic
 */
// Group=Mathematics

#ifndef _KMATLCM_H_
    /*$Workfile: KMatLcm.h$ sentry */
  #define _KMATLCM_H_

#include "KMatGcd.h"    /*GreatestCommonDivisor<>*/

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Inlines
#ifdef __cplusplus
//-----------------------------------------------------------------------------
/*Calculates the least common multiple of two integers.
  The least common multiple (lcm, lowest or smallest common multiple) is
  the smallest positive integer which is a multiple of given integers.

  Properties of LCM:
  - lcm(A, B) gcd(A, B) = AB
  - lcm(A, gcd(B, C)) = gcd(lcm(A, B), lcm(A, C)) (distributivity)
  - lcm(A, B) = AB if and only if A and B are relatively prime.


  Example:
      #include "KMatLcm.h"
        ...
      long lLcm = lcm<long>(-12, 30);
      std::_tcout << _T("lcm(") << -12 << _T(", ")
                                << 30 << _T(") = ")
                  << lLcm << std::endl;
      Output:
        lcm(-12, 30) = 60

  Returns: the least common multiple of two whole numbers or 0 if both operands
  are equal to zero:
      lcm(0, 0) = 0.

  See alo: GreatestCommonDivisor, gcd()
 */
template <typename TYPE>
TYPE lcm(TYPE Operand1, //[in] first operand
         TYPE Operand2  //[in] second operand
        )
{
if ((Operand1 == 0) || (Operand2 == 0))
  return 0;   //return 0 here, to avoid rounding for some types

  //Get absolute value of operands
if (Operand1 < 0)
  Operand1 = -Operand1;

if (Operand2 < 0)
  Operand2 = -Operand2;

if (Operand1 == Operand2)
  return Operand1;

return ((Operand1 / GreatestCommonDivisor(Operand1, Operand2) ) * Operand2);
}

///////////////////////////////////////////////////////////////////////////////
// C compilation
#else
  long lcm(long Operand1, long Operand2);

#endif //__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif //_KMATLCM_H_

/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-06-17 18:10:33  Darko Kolakovic
 * $
 ******************************************************************************/
