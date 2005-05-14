/*$Workfile: KStrNDup.c$: implementation file
  $Revision: 1$ $Date: 2004-10-22 17:51:02$
  $Author: Darko Kolakovic$

  Duplicates a n characters from a string
  Copyright: CommonSoft Inc.
  Mar 1989 Darko Kolakovic
 */

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */


#include "KTChar.h"  /*LPCTSTR*/
#ifndef TRACE0
  #include "KTrace.h"
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/*---------------------------------------------------------------------------*/

/*Duplicates a number of characters of the source string to the allocated
  storage. If nCount is greater than the length of the source string, entire
  source string will copied. The terminating zero will be appended to the new
  string.
  The storage size is nCount + 1 character or the size of the original string,
  whichever is smaller.

  Note: Because the function calls malloc to allocate storage space for the
  copy of pszSource, the caller should release this memory by calling the free()
  routine on the pointer returned by the call to StrNDup().

  Returns: a pointer to the storage location for the copied string or NULL
  if storage cannot be allocated or if original string is NULL pointer.

  Example:

    #include <stdio.h>
    #include <stdlib.h>
    #include "KStrings.h"   //StrNDup()
    void MyCopy()
      {
      const char* szText = "veni, vidi, vici";
      char* szCopy = StrNDup(szText, 4);

      printf(szCopy);

      free(szCopy);
    }
    Output:
        veni

  See also: KStrings.h
 */
TCHAR* StrNDup(LPCTSTR pszSource,//[in] Address of a constant zero-terminated
                                 //character string to copy into new memory.
               const unsigned int nCount//[in] Number of characters to be copied.
               )
{
TCHAR* pszResult;
unsigned int nSize;
if (pszSource == NULL)
  return NULL;

    /*Allocate memory for the required character and terminating zero*/
nSize = (unsigned int) _tcslen(pszSource);
if (nCount < nSize )
  nSize = nCount;

pszResult = (TCHAR* )malloc((nSize + 1) * sizeof(TCHAR));

if (pszResult == NULL)
  {
  TRACE0(_T("StrNDup() Not enough memory.\n"));
  return NULL; /*Not enough memory*/
  }

_tcsncpy(pszResult, pszSource, nCount);
pszResult[nSize] = _T('\0');

return pszResult;
}

/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-10-22 17:51:02  Darko Kolakovic 
 * $
 *  0    Biblioteka1.0           Mar 1989 Darko Kolakovic
 *****************************************************************************/
