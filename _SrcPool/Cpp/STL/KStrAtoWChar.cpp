/*$Workfile: KStrAtoWChar.cpp$: implementation file
  $Revision: 3$ $Date: 2005-03-21 03:15:58$
  $Author: Darko$

  Convert ASCII string to wide-character string
  CommonSoft Inc.
  2004-09-11 Darko Kolakovic
*/

/* Group=Strings                                                             */

#include <string>

std::wstring AtoWChar(const char* lpString, int iLen = -1);

//-----------------------------------------------------------------------------
/*Converts single-byte character (ASCII) string to wide-character string.

  Returns STL string with wide-character mapping.

  Note: uses Standard Template Library (STL).

  See also: SBCS, _UNICODE
 */
std::wstring AtoWChar(const char* lpString, //[in] string to be converted
                    int iLen //[in] = -1 Specifies the number of characters
                             //to be converted. If this value is –1, the string
                             //is assumed to be zero-terminated and the size of
                             //the string is calculated. The size includes
                             //the null-terminator.
                   )
{
ASSERT(lpString != NULL);
std::wstring strResult;
if ( lpString != NULL)
  {
  if (iLen == -1)
    iLen = strlen(lpString);
  size_t nSize;
  wchar_t* szTemp = new wchar_t[nSize = (size_t)iLen + 1];
  mbstowcs(szTemp, lpString, iLen);
  szTemp[iLen] = wchar_t(0);
  strResult = szTemp;
  delete [] szTemp;
  }
return strResult;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2005-03-21 03:15:58  Darko           Replaced
 *       Microsoft version with ANSI
 *  2    Biblioteka1.1         2004-10-07 12:56:29  Darko           documentation
 *       group
 *  1    Biblioteka1.0         2004-10-06 16:00:46  Darko           
 * $
 *****************************************************************************/
