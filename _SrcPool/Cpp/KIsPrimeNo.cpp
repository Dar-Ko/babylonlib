/*$Workfile: KIsPrimeNo.cpp$: header file
  $Revision: 3$ $Date: 7/16/02 1:41:12 AM$
  $Author: Darko$

  Simple mathematical functions
  Copyright: CommonSoft Inc.
  Jan. 96 D. Kolakovic
 */
 
/* Group=Mathematics                                                         */

#include <math.h> //sqrt()

#ifdef _DEBUG_TEST
  //Iteration counter
  unsigned long g_nDbgIterationCount0 = 0;
  //Iteration counter
  unsigned long g_nDbgIterationCount1 = 0;
#endif

//IsPrimeNo()------------------------------------------------------------------
/*Validates prime numbers.
  A prime number nValue is a positive integer having exactly one positive 
  divisor (itself) other than 1. The number 1 is a special case which is 
  considered neither prime nor composite number.

  Returns: true if the given value is a prime number, 0 or 1, otherwise returns
  false.
 */
bool IsPrimeNo(const unsigned long nValue //[in] a value to be evaluated
              )
{
#ifdef _DEBUG_TEST
  g_nDbgIterationCount1 = 0;
#endif

if (nValue > 3) //Skip trivial cases and 0 or 1
  {
  if( nValue & 1 ) //Validate only odd numbers (same as  (nValue % 2 != 0) )
    {
    //If nValue = a*b, then either a or b must be < nLim = sqrt(nValue) + 1
    unsigned long nLim = (unsigned long)sqrt(nValue) + 1;
	  unsigned long nDivisor;
	  for (nDivisor = 3; nDivisor < nLim; nDivisor += 2)
      {
      #ifdef _DEBUG_TEST
        g_nDbgIterationCount1++;
      #endif

      if( nValue % nDivisor == 0 )
		    return false; //Number is a composite
      }
    }
  else //Number is even
    return false;
  }
return true;
}

///////////////////////////////////////////////////////////////////////////////
// Test case used to compare alogorithms
#ifdef _DEBUG_TEST
/*Test algorithm for validating prime numbers.

  benchmark output:
                          IsPrimeNo           _IsPrime0
    593        is prime: T (11 iterations)    T (147)
    6611       is prime: F (5 iterations)     F (5)
    18496      is prime: F (0 iterations)     F (0)
    361275     is prime: F (1 iterations)     F (1)
    2147483647 is prime: T (23169 iterations) T (536870910)
 */
bool _IsPrime0(const unsigned long nValue //[in] a value to be evaluated
              )
{
g_nDbgIterationCount0 = 0;
bool bResult = true;

if (nValue > 3) //Skip trivial cases and 0 or 1
  {
  //Need to check only odd integers
	if (nValue & 1) 
    {
    //If nValue = a*b, then either a or b must be < nLim = nValue/2
		unsigned long nLim = nValue / 2;
    unsigned long nDivisor = 0;
		for (nDivisor = 3; nDivisor < nLim; nDivisor += 2)
      {
      g_nDbgIterationCount0++; 
			if (nValue % nDivisor == 0) 
        {
				bResult = false; //Number is a composite
				break;
			  }
      }
	  } 
  else //Number is even
		bResult = false;
  }

return bResult;
}

#endif

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 3    Biblioteka1.2         7/16/02 1:41:12 AM   Darko           Fixed VSS Log 
 *      tag
 * 2    Biblioteka1.1         3/11/02 7:29:47 PM   Darko           Improved
 *      algorithm
 * 1    Biblioteka1.0         3/8/02 3:04:11 PM    Darko Kolakovic 
 *$
 *****************************************************************************/
