/*$Workfile: KItoA.c$: implementation file
  $Revision: 2$ $Date: 3/7/02 5:07:23 PM$
  $Author: Darko$
 
  Convert a signed decimal integers to ASCII string.
  Dec 1988 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "KTrace.h"   /*ASSERT macro */
#include "KTypedef.h" /*BOOL typedef */

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

/*ItoA()---------------------------------------------------------------------*/

/*Convert the digits of the given iValue argument to a zero-terminated ASCII 
  string and stores the result (up to 33 bytes) in given string buffer.

  Returns: a pointer to zero-terminated string. There is no error return.
*/
char* ItoA(int iValue,     /*[in] number to be converted                    */
           char* szResult, /*[in] pointer to string buffer                  */ 
           int iRadix      /*[in] base of value; must be in the range 2 – 36*/
          )
{
BOOL  bIsNegative;
char* pTemp;
char* pBuffer;      /*pointer to input buffer */
unsigned nDigit;    /*single digit value      */

ASSERT(szResult != NULL);
ASSERT((iRadix >= 2) && (iRadix <= 36));

pTemp = pBuffer = szResult;            /*Store buffer's start point*/

if ((bIsNegative = (iValue < 0)))
  iValue = -iValue;

do
  {
  nDigit = iValue % iRadix;

  *pTemp++ = (nDigit < 10) ?
	       ((char)(nDigit + '0')) :
           (char) (nDigit - 10 + 'A'); /*If radix > 10 use letters */

  } while ((iValue = iValue / iRadix) > 0);

if ((bIsNegative) && (iRadix == 10))  /*Append sign, if necessary  */
 *pTemp++ = '-';

*pTemp = '\0';

/*Reverse string in place*/
pTemp--; /*Pointer to the last character*/
while(pBuffer < pTemp) 
  {
  int cTemp = *pBuffer;
  *pBuffer++ = *pTemp;
  *pTemp-- = cTemp;
  }

return szResult;
}

/* ///////////////////////////////////////////////////////////////////////// */
