/*$Workfile: KStrUppr.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:39:16 $
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
 *  4    Biblioteka1.3         29/01/2002 10:22:11 PMDarko           Used lbraries
 *       notes 
 *  3    Biblioteka1.2         25/01/2002 3:58:47 PMDarko           Updated
 *       comments
 *  2    Biblioteka1.1         23/12/2001 12:21:57 AMDarko           _DEBUG
 *  1    Biblioteka1.0         18/07/2001 10:32:11 PMDarko           
 * $
 *****************************************************************************/
