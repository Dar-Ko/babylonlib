/*$Workfile: S:\_SrcPool\Cpp\Win\32\KStrAtoWChar.cpp$: implementation file
  $Revision: 1$ $Date: 2005-03-21 02:17:31$
  $Author: Darko$

  Convert ASCII string to wide-character string
  CommonSoft Inc.
  2004-09-11 Darko Kolakovic
*/

/* Group=Strings                                                             */

#ifdef _WIN32
  //Standard Microsoft Windows header files
  #include "stdafx.h"
#endif

#include <string>

std::wstring AtoWChar(const char* lpString, int iLen = -1);

//-----------------------------------------------------------------------------
#ifdef _WIN32
/*Converts single-byte character (ASCII) string to wide-character string.

  Returns STL string with wide-character mapping.

  Note: uses Standard Template Library (STL).
        Microsoft Windows specific (Win32).

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
    //Calculate size of the new string
  int iSize = MultiByteToWideChar(CP_ACP,   // ANSI code page
                                  0,        // character-type options
                                  lpString, // string to map
                                  iLen,     // number of bytes in string
                                  NULL,     // wide-character buffer
                                  0         // size of buffer
                                 );

  if (iSize > 0)
    {
    wchar_t* szTemp = new wchar_t[iSize];

    #ifdef _DEBUG
      int iRes = MultiByteToWideChar(CP_ACP,   // ANSI code page
                                     0,        // character-type options
                                     lpString, // string to map
                                     iLen,     // number of bytes in string
                                     szTemp,   // wide-character buffer
                                     iSize     // size of buffer
                                    );
      if ( iRes == 0)
        {
        iRes = (int)GetLastError();
        switch((DWORD)iRes)
          {
          case ERROR_INSUFFICIENT_BUFFER:
            TRACE0(_T("  ERROR_INSUFFICIENT_BUFFER\n"));
            break;
          case ERROR_INVALID_FLAGS:
            TRACE0(_T("  ERROR_INVALID_FLAGS\n"));
            break;
          case ERROR_INVALID_PARAMETER:
            TRACE0(_T("  ERROR_INVALID_PARAMETER\n"));
            break;
          case ERROR_NO_UNICODE_TRANSLATION:
            TRACE0(_T("  ERROR_NO_UNICODE_TRANSLATION\n"));
            break;
          default:
            TRACE1("  unknown error (%d)\n", (DWORD)iRes);
          }
        }
    #else //NDEBUG
      MultiByteToWideChar(CP_ACP,   // ANSI code page
                          0,        // character-type options
                          lpString, // string to map
                          iLen,     // number of bytes in string
                          szTemp,   // wide-character buffer
                          iSize     // size of buffer
                         );
    #endif //_DEBUG

    szTemp[iSize -1] = wchar_t(0);
    strResult = szTemp;
    delete [] szTemp;
    }
 }
return strResult;
}
#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2004-10-07 12:56:29  Darko           documentation
 *       group
 *  1    Biblioteka1.0         2004-10-06 16:00:46  Darko
 * $
 *****************************************************************************/
