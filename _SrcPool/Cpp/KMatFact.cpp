/*$Workfile: KMatFact.cpp$: header file
  $Revision: 2$ $Date: 2003-08-23 14:34:38$
  $Author: Darko$

  factorial
  Copyright: CommonSoft Inc.
  Jan 94 C Version D.K.
 */

// Group=Mathematics

#ifdef _MSC_VER //Microsoft C/C++ compiler
  #pragma warning( push, 3 )
    //warning C4127: conditional expression is constant(ASSERT)
  #pragma warning(disable: 4217)
#endif

#ifndef ASSERT
  #include "KTrace.h" //ASSERT macro
#endif

//factorial()------------------------------------------------------------------
/*Computes the factorial of an integer.
  The factorial n! is defined for a positive integer n as:
    {html: <BR><IMG SRC="Res/eqFactorial.gif" ALT="n!=n*(n-1)*...2*1; [0!=1]" BORDER="0">,<BR>}

  The first few factorials for n = 0, 1, 2, 3,... are
    1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800,
    479001600, 6227020800, 87178291200, 1307674368000, 20922789888000,
    355687428096000, 6402373705728000,  121645100408832000, 2432902008176640000

  Returns: n! = n * (n-1)*...*1 for n [1, 12], or 1 if n = 0

  TODO: Change upper limit if int = int64. D.K.
 */
unsigned int factorial(unsigned int nValue //[in] positive integer in range[0, 12]
                      )
{
ASSERT(nValue < 13); //Integer overflow
unsigned int nResult = 1;

while (nValue > 1)
  {
  nResult *= nValue--;
  }

return nResult;
}

///////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER //Microsoft C/C++ compiler
    //warning C4127: conditional expression is constant
  #pragma warning(default: 4217)
  #pragma warning( pop )
#endif
/******************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2003-08-23 14:34:38  Darko           disabled
 *       warning C4127
 *  1    Biblioteka1.0         2002-08-21 02:38:52  Darko           
 * $
 *****************************************************************************/

