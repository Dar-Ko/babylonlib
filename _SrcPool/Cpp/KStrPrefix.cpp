/*$Workfile: KStrPrefix.cpp$: implementation file
  $Revision: 1$ $Date: 2005-06-21 10:11:07$
  $Author: Darko Kolakovic$

  Matches string prefixes
  Copyright: CommonSoft Inc.
  2005-06-21 Darko Kolakovic
 */

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"  /*LPCTSTR*/

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Find greatest common prefix of two strings.

  Returns: a number of same characters at begining of the strings. Returns 0 if
  string prefixes are not matched or one of the strings is empty or a
  null-pointer.

  Example:
      uint nPrefix = StrPrefix(_T("testns:int item=\"5\""),
                               _T("testns:char item=\"A\""));
      ASSERT(nPrefix == 7);

  See also: KStrings.h, StrIStr(), FindNoCase(), GetSubstring()
 */
unsigned int StrPrefix(LPCTSTR szOperand1,//[in] first zero-terminated string
                                          //with prefix to match
                       LPCTSTR szOperand2 //[in] second zero-terminated string
                                          //with prefix to match
                      )
{
unsigned int i = 0;
if ((szOperand1 != NULL) && (szOperand2 != NULL))
  while( (szOperand1[i] == szOperand2[i]) &&
       (szOperand1[i] != _T('\0')       &&
       (szOperand2[i] != _T('\0') )
    {
    i++;
    }

return (i);
}

/* ///////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2005-06-21 10:11:07  Darko Kolakovic 
 * $
 *****************************************************************************/
