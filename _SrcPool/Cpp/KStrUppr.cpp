/*$Workfile: KStrUppr.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  Converts lower case characters to upper case
  Copyright: CommonSoft Inc.
  Jan 2000 Darko Kolakovic
 */

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifndef _STRING_
  #include <string> //std::string
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
std::string StrToUpper(const std::string& strSource)
{
using namespace std;
char cChar;
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
 *  4    Biblioteka1.3         1/29/02 11:22:11 PM  Darko           Used lbraries
 *       notes 
 *  3    Biblioteka1.2         1/25/02 4:58:47 PM   Darko           Updated
 *       comments
 *  2    Biblioteka1.1         12/23/01 1:21:57 AM  Darko           _DEBUG
 *  1    Biblioteka1.0         7/18/01 11:32:11 PM  Darko           
 * $
 *****************************************************************************/
