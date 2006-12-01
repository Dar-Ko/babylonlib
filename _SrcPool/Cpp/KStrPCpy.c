/*$Workfile: KStrPCpy.c$: implementation file
  $Revision: 9$ $Date: 2005-06-21 10:11:53$
  $Author: Darko Kolakovic$

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

  Returns: a pointer to the end (terminating null) of the converted string.

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
TCHAR* StrPCpy(TCHAR* szDestination,  /*[out] resulting copy*/
               const TCHAR* szSource /*[in] zero-terminated string to be copyied*/
               )
{
while ((*szDestination++ = *szSource++) != '\0')
    /*Copy source to target */ ;
return (szDestination - 1);
}

/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log:
 *  8    Biblioteka1.7         2004-06-01 17:53:27  Darko           time sync
 *  7    Biblioteka1.6         2003-09-22 22:26:47  Darko           formatting
 *  6    Biblioteka1.5         2002-02-12 17:39:25  Darko           Replaced
 *       tchar.h with KTChar.h
 *  5    Biblioteka1.4         2001-08-19 23:55:28  Darko           Butyfier
 *  4    Biblioteka1.3         2001-07-11 22:52:56  Darko
 *  3    Biblioteka1.2         2001-06-08 23:51:59  Darko           VSS
 *  2    Biblioteka1.1         2000-09-21 01:16:15  Darko
 *  1    Biblioteka1.0         2000-08-13 16:00:18  Darko
 * $
 *  0    Biblioteka1.0           Mar 1989 Darko Kolakovic
 *****************************************************************************/
