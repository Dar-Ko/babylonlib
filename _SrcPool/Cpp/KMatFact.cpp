/*$Workfile: KMatFact.cpp$: implementation file
  $Revision: 5$ $Date: 2005-06-08 17:14:42$
  $Author: Darko Kolakovic$

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
    {html: <br /><img src="Images/eqFactorial.gif" border="0"
                      alt="n!=n*(n-1)*...2*1; [0!=1]"><br />}

  The first few factorials for n = 0, 1, 2, 3,... are
    1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800,
    479001600, 6227020800, 87178291200, 1307674368000, 20922789888000,
    355687428096000, 6402373705728000,  121645100408832000, 2432902008176640000

  Returns: exact integer solution for n! = n * (n-1)*...*1; n [1, k].
  or 1 if n = 0;

  Note: k depends of maximum number representable on the current platform.
  For 32-bit integers k = 12.

  Example:
      ...
      unsigned int i = 0;
      while ( i <= 12 )
        {
        unsigned long nFactorial = factorial(byte(i));
        std::_tcout << i << _T("!") << _T(" = ")
                    << nFactorial << _T(";") << std::endl;
        i++;
        }

 */
unsigned int factorial(unsigned char nValue //[in] positive integer in range [0, k]
                      )
{
#if defined _DEBUG
  //Integer overflow
  switch (sizeof(int))
    {
    case 1: ASSERT(nValue <  6); break; //Int8
    case 2: ASSERT(nValue <  9); break; //Int16
    case 4: ASSERT(nValue < 13); break; //Int32
    case 8: ASSERT(nValue < 21); break; //Int64
    default: ASSERT(nValue < 13); break; //Int32
    }
#endif
unsigned int nResult = 1;

while (nValue > 1)
  {
  nResult *= nValue--;
  }

return nResult;
}

double factorial(unsigned int nValue //[in] positive integer in range [0, 100]
                )
{

double dResult = 1.0;
while (nValue > 1)
  {
  dResult *= nValue--;
  }

return dResult;
}

///////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER //Microsoft C/C++ compiler
    //warning C4127: conditional expression is constant
  #pragma warning(default: 4217)
  #pragma warning( pop )
#endif
/******************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2003-08-23 15:34:38  Darko           disabled
 *       warning C4127
 *  1    Biblioteka1.0         2002-08-21 03:38:52  Darko
 * $
 *****************************************************************************/

