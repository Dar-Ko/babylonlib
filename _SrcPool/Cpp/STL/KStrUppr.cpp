/*$Workfile: KStrUppr.cpp$: implementation file
  $Revision: 8$ $Date: 2007-07-17 12:01:55$
  $Author: Darko Kolakovic$

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
tstring StrToUpper(const tstring& strSource //[in] string to be converted
                  )
{
using namespace std;
TCHAR cChar;
tstring strResult = strSource;

tstring::iterator i = strResult.begin();
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
 *  8    Biblioteka1.7         2007-07-17 12:01:55  Darko Kolakovic fixed wchar_t
 *       strings
 *  7    Biblioteka1.6         2007-07-17 09:21:47  Darko Kolakovic Argument
 *       comment
 *  6    Biblioteka1.5         2005-05-11 22:33:34  Darko           Unicode
 *  5    Biblioteka1.4         2004-06-01 18:03:52  Darko           STLport
 *       included
 *  4    Biblioteka1.3         2002-01-29 23:22:11  Darko           Used libraries
 *       notes 
 *  3    Biblioteka1.2         2002-01-25 16:58:47  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-12-23 01:21:57  Darko           _DEBUG
 *  1    Biblioteka1.0         2001-07-18 23:32:11  Darko           
 * $
 *****************************************************************************/
