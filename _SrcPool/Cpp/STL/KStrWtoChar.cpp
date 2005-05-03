/*$Workfile: KStrWtoChar.cpp$: implementation file
  $Revision: 3$ $Date: 2005-03-21 03:16:00$
  $Author: Darko$

  Convert wide-character string to ASCII string
  CommonSoft Inc.
  2004-09-11 Darko Kolakovic
*/

/* Group=Strings                                                             */

#include <string>

std::string WtoChar(const wchar_t* lpWideCharStr, int iLen = -1);

//-----------------------------------------------------------------------------
/*Converts wide-character string to single-byte character (ASCII) string.

  Returns STL string with SBCS mapping.

  Note: uses Standard Template Library (STL).

  See also: SBCS, _UNICODE
 */
std::string WtoChar(const wchar_t* lpWideCharStr, //[in] string to be converted
                    int iLen //[in] = -1 Specifies the number of characters
                             //to be converted. If this value is –1, the string
                             //is assumed to be zero-terminated and the size of
                             //the string is calculated. The size includes
                             //the null-terminator.
                   )
{
ASSERT(lpWideCharStr != NULL);
std::string strResult;
if ( lpWideCharStr != NULL)
  {
  if (iLen == -1)
    iLen = wcslen(lpWideCharStr);
  size_t nSize;
  char* szTemp = new char[nSize = (size_t)iLen + 1];
  wcstombs(szTemp, lpWideCharStr, iLen);
  szTemp[iLen] = '\0';
  strResult = szTemp;
  delete [] szTemp;
 }
return strResult;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2005-03-21 03:16:00  Darko           Replaced
 *       Microsoft version with ANSI
 *  2    Biblioteka1.1         2004-10-07 12:56:34  Darko           documentation
 *       group
 *  1    Biblioteka1.0         2004-10-06 16:00:48  Darko           
 * $
 *****************************************************************************/
