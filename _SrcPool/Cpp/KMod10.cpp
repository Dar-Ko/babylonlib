/*$Workfile: KGetLRC.cpp$: implementation file
  $Revision: 4$ $Date: 2004-06-01 17:50:31$
  $Author: Darko$

  Modulus 10 Checksum (Luhn formula)
  Copyright: CommonSoft Inc.
  2000-05-05 Darko Kolakovic (original C version)
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */


#ifndef uint8_t
  #include "KTypedef.h"
#endif
#ifdef _USE_ATL
  #define ASSERT ATLASSERT
#endif
#ifndef ASSERT
  #include "KTrace.h"
#endif

//-----------------------------------------------------------------------------
/*Calculates one digit Modulus 10 Checksum (also known as mod10 or Luhn).
  {html:
  The calculation is based on rather simple Luhn formula, invented to detect
  data entry errors:
    1. Beginning with the least significant, rightmost digit, double the value
       of every second digit to the left. If the result is equal or greater then
       10, subtract 9.

           2n < 10 -> 2n  (for n [0, 5])
           2n &ge; 10 -> 2n-9 (for n [5, 9])
   2. Sum all digits and calculate modulo 10.
   3. Sum of checksum number L and previous result have to be congruent
      modulo 10 (reminder is 0).

         (&Sigma;n + L)(mod 10) &equiv; 0, L $isin; [0, 9]
         &ther4;
         (&Sigma;n)(mod 10) + L = 10
         L = 10 - (&Sigma;n)(mod 10)

  The algorithm detects any single-digit error and almost all transpositions of
  adjacent digits.
  }
  
  Returns: Luhn number in the range [0, 9]

  Example:
  
      unsigned nSerialNo[] = {1,2,8,3,7,9,7,1,9,2,3,3,4,7,8,0,2,3,4,8, 0xffff};
      //Calculate the checksum
      nSerialNo[SIZEOFARR(nSerialNo) -1] = GetMod10(nSerialNo, 
                                                    SIZEOFARR(nSerialNo) -1);
  
  History: 1954-01-06, Luhn algorithm, Hans Peter Luhn [1896-07-01, 1964-08-19]
 */
unsigned int GetMod10(unsigned int* pnDigit, //[in] array of decimal digits [0, 9]
                     int iCount        //[in] number of digits in the array
                     )
{
uint_fast32_t nSum = 0; //sum of transformed digits
if ((pnDigit != NULL) && (iCount > 0))
  {
  //array of transformed digits obtained by transposing digit values
  // (n = pnDigit[iCount] * 2) >= 10 ? n -= 9 : n
  static uint_fast32_t nTranspose[] = { 0, 2, 4, 6, 8, 1, 3, 5, 7, 9 };
  while(--iCount >= 0)
    {
    ASSERT(pnDigit[iCount] < 10);//Only decimal digits [0, 9] are valid

    nSum += nTranspose[pnDigit[iCount--]]; //sum((2n % 10) + 1) = sum(2n - 9) = sum(Tn)
    if (iCount < 0)
      break;
    nSum += pnDigit[iCount];//Every other digit remains same
    }
  }

return (10 - (nSum % 10)); //Return calculated checksum
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: $
 ******************************************************************************/
