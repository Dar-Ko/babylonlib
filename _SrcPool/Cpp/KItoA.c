/*$Workfile: KItoA.c$: implementation file
  $Revision: 5$ $Date: 2004-10-01 20:26:25$
  $Author: Darko$

  Convert a signed decimal integers to ASCII string.
  Dec 1988 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "KTrace.h"   /*ASSERT macro */
#include "KTypedef.h" /*BOOL typedef */

#ifdef _MSC_VER
  //warning C4127: conditional expression is constant
  //warning C4706: assignment within conditional expression
  #pragma warning ( disable: 4127 4706 )
#endif

#ifdef _DEBUG
  #ifndef THIS_FILE
    static TCHAR THIS_FILE[] = __FILE__;
  #endif
#endif

/*ItoA()---------------------------------------------------------------------*/

/*Convert the digits of the given iValue argument to a zero-terminated ASCII
  string and stores the result (up to 33 bytes) in given string buffer.

  Returns: a pointer to zero-terminated string. There is no error return.

  See also: KStrings.h

  Example:

    #ifdef _MSC_VER
      / *Microsoft VC/C++ compiler* /
      #define ItoA _itot /* expands to Microsoft specific _itoa with SBCS
                            or _itow _UNICODE mapping.
                          * /
    #endif
    #include <stdlib.h>

    void main()
    {
    TCHAR szResult[65];
    int iRadix;
    for( iRadix=10; iRadix >= 2; --iRadix )
      {
      ItoA( -1, szResult, iRadix );
      printf( "base %d: %s (%d chars)\n", iRadix, szResult, strlen(szResult) );
      }
    }

    Output:
      base 10: -1 (2 chars)
      base 9: 12068657453 (11 chars)
      base 8: 37777777777 (11 chars)
      base 7: 211301422353 (12 chars)
      base 6: 1550104015503 (13 chars)
      base 5: 32244002423140 (14 chars)
      base 4: 3333333333333333 (16 chars)
      base 3: 102002022201221111210 (21 chars)
      base 2: 11111111111111111111111111111111 (32 chars)
*/
LPTSTR ItoA(int iValue,     /*[in] number to be converted                    */
           LPTSTR szResult, /*[in] pointer to string buffer                  */
           int iRadix       /*[in] base of value; must be in the range 2 – 36*/
          )
{
BOOL   bIsNegative;
LPTSTR pTemp;
LPTSTR pBuffer;      /*pointer to input buffer */
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
  *pTemp-- = (TCHAR)cTemp;
  }

return szResult;
}

/* ///////////////////////////////////////////////////////////////////////// */
#ifdef _MSC_VER
  //warning C4127: conditional expression is constant
  //warning C4706: assignment within conditional expression
  #pragma warning ( default: 4127 4706 )
#endif
/******************************************************************************
 *$Log:
 * 4    Biblioteka1.3         2004-06-01 17:50:37  Darko           time sync
 * 3    Biblioteka1.2         2003-08-14 04:59:03  Darko           Unicode
 * 2    Biblioteka1.1         2002-03-07 17:07:23  Darko           comment updated
 * 1    Biblioteka1.0         2002-02-12 17:38:12  Darko
 *$
 *****************************************************************************/

