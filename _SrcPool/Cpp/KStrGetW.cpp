/*$Workfile: KStrGetW.cpp$: implementation file
  $Revision: 4$ $Date: 04/02/2002 6:56:58 PM$
  $Author: Darko$

  Retreive words
  Copyright: CommonSoft Inc.
  May '97 Darko Kolakovic
*/


/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifndef _TCHAR_DEFINED
  #include "KTChar.h" //TCHAR typedef
#endif
#include "KStrings.h" /*Declaration                                          */

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//GetWord()--------------------------------------------------------------------
/*Function copyes a single word from the source string to the destination buffer.
  Words have to be separated with one white space character or with null-character
  Returns pointer to next character following the word.
 */
TCHAR* GetWord(TCHAR* lpszResult, //pointer to destination buffer
               TCHAR* lpszSource  //pointer to a source string
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
 *  0    Biblioteka0           Darko Kolakovic  May '97
 * $
 *****************************************************************************/
