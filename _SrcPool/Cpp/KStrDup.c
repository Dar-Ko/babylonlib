/*$Workfile: KStrDup.c$: implementation file
  $Revision: 1$ $Date: 8/27/02 5:04:59 PM$
  $Author: Darko Kolakovic$

  Duplicates a string
  Copyright: CommonSoft Inc.
  Mar 1989 Darko Kolakovic
 */

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"  /*LPCTSTR*/

#ifndef _MSC_VER /*If not Microsoft VC/C++ compiler                          */

  #ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
  #endif

/*StrDup()-------------------------------------------------------------------*/

/*Copies source string in the allocated storage. The storage is the size of the
  original string.

  Note: This function uses malloc() to allocate storage space for the copy 
  of the string. The calling application must free this memory by calling
  the free() function on the pointer returned by the call to StrDup(). 

  Returns: the address of the string that was copied, or NULL if enough memory 
  could not be allocated, or original string was NULL.
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
  TCHAR* StrDup(LPCTSTR pszSource)
  {
  return _tcsdup(pszSource);
  }
#endif
/*****************************************************************************
 * $Log:
 *  0    Biblioteka1.0           Mar 1989 Darko Kolakovic
 * $
 *****************************************************************************/
