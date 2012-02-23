/*$Workfile: KStrGetW.cpp$: implementation file
  $Revision: 7$ $Date: 2007-06-15 17:24:30$
  $Author: Darko Kolakovic$

  Retreive words
  Copyright: CommonSoft Inc.
  May '97 Darko Kolakovic
*/


/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifndef _TCHAR_DEFINED
  #include "KTChar.h" //TCHAR typedef
#endif
#include "KStrings.h" /*Declaration                                          */

#ifdef _DEBUG
  #ifdef _USE_MFC
    #define new DEBUG_NEW
  #endif //_USE_MFC
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//GetWord()--------------------------------------------------------------------
/*Function copies a single word from the source string to the destination
  buffer. Words have to be separated with one white space character or with
  null-character.

  Returns: pointer to next character in source string following the word.

  See also: GetFirstSpace(), EnumSubstring()
 */
TCHAR* GetWord(TCHAR* lpszResult, //[out] pointer to destination buffer
               TCHAR* lpszSource  //[in] pointer to a source string
               )
{
while( (*lpszSource != _T('\0')) && (!_istspace(*lpszSource)) )
  *lpszResult++ = *lpszSource++;

*lpszResult = _T('\0');
return lpszSource;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  7    Biblioteka1.6         2007-06-15 17:24:30  Darko Kolakovic _USE_MFC for
 *       CString
 *  6    Biblioteka1.5         2004-06-01 17:53:23  Darko           time sync
 *  5    Biblioteka1.4         2003-09-04 11:23:27  Darko           comment
 *  4    Biblioteka1.3         2002-02-04 19:56:58  Darko           include
 *       KTChar.h
 *  3    Biblioteka1.2         2002-01-25 16:58:27  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-12-23 01:21:32  Darko           _DEBUG
 *  1    Biblioteka1.0         2001-08-18 16:04:26  Darko           
 * $
 *  0    Biblioteka0           Darko Kolakovic  May '97
 *****************************************************************************/
