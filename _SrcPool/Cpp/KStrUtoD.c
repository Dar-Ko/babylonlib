/*$Workfile: KStrUtoD.c$: implementation file
  $Revision: 5$ $Date: 2/12/02 4:39:33 PM$
  $Author: Darko$

  Converts unsigned integer to decimal string.
  Jan. 90 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"  /*TCHAR*/

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

#ifndef BOOL
  #include "KTypedef.h" //BOOL
#endif

//UtoDec()---------------------------------------------------------------------
/*Converts unsigned integer to decimal string.
  Returns a pointer to string. There is no error return.
*/
LPTSTR UtoDec(unsigned long value,  //number to be converted
              LPTSTR strResult   )  //string result
{
UINT iDigit  = 1000000000;
UINT j;
BOOL flag = FALSE;

while(iDigit > 1)
  {
  if((j = value / iDigit) != 0)
    {
    value = value % iDigit;
    flag = TRUE;
    }

  if (flag)
    *strResult++ = (TCHAR)(j + _T('0'));
  iDigit /= 10;
  }

*strResult++ = (TCHAR)(value + _T('0'));
*strResult = _T('\0');

return(strResult);
}

/* ////////////////////////////////////////////////////////////////////////// */
