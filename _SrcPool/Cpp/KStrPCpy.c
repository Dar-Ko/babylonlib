/*$Workfile: KStrPCpy.c$: implementation file
  $Revision: 6$ $Date: 2/12/02 4:39:25 PM$
  $Author: Darko$

  Copies source string to the target
  Mar 1989 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"  /*TCHAR*/

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

/*StrPCpy()------------------------------------------------------------------*/
/*This function copies szSource, including the terminating null
  character, to the location specified by szDestination. No overflow
  checking is performed when strings are copied. The behavior of function
  is undefined if the source and destination strings overlap.
  This function replicates behavior of GNU C Library function stpcpy().

  Returns a pointer to the end (terminating null) of the converted string.

  Example:
    #include <StdLib.h>
    #include <TChar.h>
    #include "KStrings.h"
    void MyFunc()
      {
      TCHAR szResult[31];
      LPTSTR pTail = StrPCpy(szResult, _T("TEXT"));
      StrPCpy(pTail,_T(" PARAGRAPH"));
      wprintf(szResult);
      }

 */
TCHAR* StrPCpy(TCHAR* szDestination  /*result                                   */,
               const TCHAR* szSource /*pointer to a null-terminated string      */
               )
{
while ((*szDestination++ = *szSource++) != '\0')
    /*Copy source to target */ ;
return (szDestination - 1);
}

/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log:
 *  0    Biblioteka1.0           Mar 1989 Darko Kolakovic
 * $
 *****************************************************************************/
