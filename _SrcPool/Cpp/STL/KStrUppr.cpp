/*$Workfile: KStrUppr.cpp$: implementation file
  $Revision: 6$ $Date: 2005-05-11 22:33:34$
  $Author: Darko$

  Converts lower case characters to upper case
  Copyright: CommonSoft Inc.
  Jan 2000 Darko Kolakovic
 */

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _DEBUG
  #ifndef _STLP_DEBUG
    #define _STLP_DEBUG 1    //Debug STLPort library
  #endif
#else
  #ifdef _STLP_DEBUG
    #undef _STLP_DEBUG
  #endif
#endif

#ifndef _STRING_
  #include <string> //std::string
  #include "KTString.h" //tstring typedef
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//StrToUpper()-----------------------------------------------------------------
/*The function converts all lower case characters within given string to upper
  case.

  Returns: STL string with upper case characters.

  Note: uses Standard Template Library (STL).
 */
tstring StrToUpper(const tstring& strSource)
{
using namespace std;
TCHAR cChar;
string strResult = strSource;

string::iterator i = strResult.begin();
while(i != strResult.end())
  {
  cChar = toupper(*i);
  strResult.replace(i, i + 1, &cChar, 1);
  i++;
  }
return strResult;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         1/29/2002 11:22:11 PMDarko           Used lbraries
 *       notes
 *  3    Biblioteka1.2         1/25/2002 4:58:47 PM Darko           Updated
 *       comments
 *  2    Biblioteka1.1         12/23/2001 1:21:57 AMDarko           _DEBUG
 *  1    Biblioteka1.0         7/18/2001 11:32:11 PMDarko
 * $
 *****************************************************************************/
