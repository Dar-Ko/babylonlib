/*$Workfile: S:\_SrcPool\Cpp\KStrDup.c$: implementation file
  $Revision: 5$ $Date: 2004-10-22 17:51:19$
  $Author: Darko Kolakovic$

  Duplicates a string
  Copyright: CommonSoft Inc.
  Mar 1989 Darko Kolakovic
 */

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */


#ifndef _MSC_VER /*If not Microsoft VC/C++ compiler                          */
  #include "KTChar.h"  /*LPCTSTR*/

  #ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
  #endif

/*---------------------------------------------------------------------------*/

/*Copies source string to the allocated storage. The storage is the size of the
  original string.

  Note: This function uses malloc() to allocate storage space for the copy
  of the string. The calling application must free this memory by calling
  the free() function on the pointer returned by the call to StrDup().

  Returns: a pointer to the storage location for the copied string or NULL
  if storage cannot be allocated or if original string is a NULL pointer.

  Example:

    #include <stdio.h>
    #include <stdlib.h>
    #include "KStrings.h"   //StrDup()
    void MyCopy()
      {
      const char* szText = "  Some text.  ";
      char* szCopy = StrDup(szText);

      StrTrim(szCopy);
      printf(szCopy);

      free(szCopy);
      }
    Output:
        Some text

  See also: KStrings.h
 */
TCHAR* StrDup(LPCTSTR pszSource //[in] Address of a constant zero-terminated
                                //character string to copy into new memory.
             )
{
TCHAR* pszResult;
if (pszSource == NULL)
  return NULL;

pszResult = (TCHAR* )malloc((_tcslen(pszSource) + 1) * sizeof(TCHAR));
if (pszResult == NULL)
  return NULL;

_tcscpy(pszResult, pszSource);
return pszResult;
}

/* ///////////////////////////////////////////////////////////////////////// */
#else
  /*Microsoft VC/C++ compiler                                                */
  #include <tchar.h>
  #include <wtypes.h> /*LPCTSTR typedef */
  TCHAR* StrDup(LPCTSTR pszSource)
  {
  return _tcsdup(pszSource);
  }
#endif
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2004-10-22 17:51:19  Darko Kolakovic comments
 *  4    Biblioteka1.3         2004-10-01 21:08:39  Darko           fixed MSVC7
 *       wchar dependancy
 *  3    Biblioteka1.2         2003-08-14 05:02:34  Darko           comment
 *  2    Biblioteka1.1         2002-09-11 16:26:12  Darko Kolakovic Added example
 *  1    Biblioteka1.0         2002-08-27 17:04:59  Darko Kolakovic 
 * $
 *  0    Biblioteka1.0           Mar 1989 Darko Kolakovic
 *****************************************************************************/
