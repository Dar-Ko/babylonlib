/*$Workfile: KMatFact.cpp$: header file
  $Revision: 1$ $Date: 21/08/2002 2:38:52 AM$
  $Author: Darko$

  factorial
  Copyright: CommonSoft Inc.
  Jan 94 C Version D.K.
 */

// Group=Mathematics


//factorial()------------------------------------------------------------------
/*Computes the factorial of an integer.

  The first few factorials for n = 0, 1, 2, 3,... are
    1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800,
    479001600, 6227020800, 87178291200, 1307674368000, 20922789888000,
    355687428096000, 6402373705728000,  121645100408832000, 2432902008176640000

  Returns: n! = n * (n-1)*...*1 for n [1, 12], or 1 if n = 0
 */
unsigned int factorial(unsigned int nValue //[in] n! range[0, 12]
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
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         21/08/2002 2:38:52 AMDarko           
 * $
 *****************************************************************************/

