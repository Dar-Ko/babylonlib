/*$Workfile: KStrAtoU.c$: implementation file
  $Revision: 2$ $Date: 2004-06-01 17:52:56$
  $Author: Darko$

  Converts a string to unsigned integer
  Copyright: CommonSoft Inc.
  2003-09-23 Darko Kolakovic
*/

/* Group=Strings                                                             */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTypedef.h"
#include "KTChar.h"

//-----------------------------------------------------------------------------
/*Convert an array of decimal digits to unsigned integer. 
  Function parses until last digit found up to maximum nLen characters.
  The string could contain only decimal digits.
  The function stops reading the input string at the first character that it
  cannot recognize as part of a number.

  Returns: integer value produced by interpreting the input characters
  as a number or 0 if the input cannot be converted and number of characters
  successfuly parsed. The return value is undefined in case of overflow.
 */
unsigned AtoU(LPCTSTR strSource, uint_fast16_t* pnLen)
{
unsigned nResult = 0;
uint_fast16_t nCount = 0; //parsed characters count

while ((*strSource >= _T('0')) && 
       (*strSource <= _T('9')) &&
       (nCount < *pnLen)          )
  {
  nResult = 10 * nResult + *strSource++ - _T('0');
  nCount++;
  }

*pnLen = nCount;
return nResult;
}

/* ///////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-06-01 17:52:56  Darko           time sync
 *  1    Biblioteka1.0         2003-09-24 18:41:34  Darko           
 * $
 *****************************************************************************/
