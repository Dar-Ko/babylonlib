/*$Workfile: KStrCatV.c$: implementation file
  $Revision: 4$ $Date: 2/12/02 4:39:12 PM$
  $Author: Darko$

  Appends multiple strings
  Jan 1990 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"  /*TCHAR*/
#include <stdarg.h>

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

    /*The last item of variable-argument list*/
#define _LIST_TERMINATOR  0x0

/*StrCatV()------------------------------------------------------------------*/
/*The StrCatV function appends one or more null-terminated strings to 
  szDestination and terminates the resulting string with a null character. 
  No overflow checking is performed when strings are copied or appended. 
  The behavior of StrCatV is undefined if the source and szRes strings overlap.
  The last item in the variable-argument list have to be zero.

  Example:
    #include <StdLib.h>
    #include <TChar.h>
    #include "KStrings.h"
    void MyFunc()
      {
      TCHAR szOutput[64];
      szOutput[0] = _T('\0');  / *Empty string* /
      StrCatV(szOutput, _T("The "), _T("quick "), _T("brown "), _T("dog "),
                        _T("jumps "), _T("over "), 
                        _T("the "), _T("lazy "), _T("fox."), 
                        0 );
      wprintf(szOutput);
      }
 */
TCHAR* StrCatV(TCHAR* szDestination  /*result                                       */, 
               const TCHAR* szSource /*pointer to a null-terminated string to append*/, 
               ...                   /*variable-argument list, last item have to be zero*/
               )
{
TCHAR* szRes = szDestination;      /*Resulting string                           */
va_list varargList;
va_start(varargList, szSource);   /*Sets arg_ptr to the first optional argument*/

while (szSource != _LIST_TERMINATOR)
  {
  while (*szSource != _T('\0'))
          *szDestination++ = *szSource++;
  szSource = va_arg(varargList, TCHAR*);
  }
*szDestination = _T('\0');

va_end(varargList);              /*Reset variable arguments.                   */

return szRes;
}
