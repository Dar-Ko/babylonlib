/*$Workfile: KItoOct.c$: implementation file
  $Revision: 4$ $Date: 2004-10-01 21:43:59$
  $Author: Darko$

  Convert an integer to octal string.
  Jan. 96 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */


//#include "KTrace.h" /*ASSERT macro */
#include "KTChar.h" /*LPCTSTR typedef*/

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

/*ItoOct()-------------------------------------------------------------------*/

/*Converts the given iValue argument to a zero-terminated string.
  Returns: a pointer to zero-terminated string. There is no error return.
 */
LPTSTR ItoOct(int iValue,     /*[in] number to be converted                   */
              LPTSTR szResult /*[in] pointer to string buffer                 */
             )
{
//ASSERT(szResult != NULL);
LPTSTR pTemp;
LPTSTR pBuffer;      /*pointer to input buffer */
unsigned nDigit;    /*single nDigit value      */
pTemp = pBuffer = szResult;            /*Store buffer's start point*/


do
  {
  nDigit = iValue & 7;
  iValue = (iValue >> 3) & 0x1FFF;
  *pTemp++ = (TCHAR)(nDigit + _T('0'));
  }
  while(iValue > 0);

*pTemp = _T('\0');

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
/******************************************************************************
 *$Log:
 * 3    Biblioteka1.2         8/14/2003 5:00:54 AM Darko           Unicode
 * 2    Biblioteka1.1         7/16/2002 1:41:15 AM Darko           Fixed VSS Log
 *      tag
 * 1    Biblioteka1.0         3/7/2002 5:03:38 PM  Darko
 *$
 *****************************************************************************/
