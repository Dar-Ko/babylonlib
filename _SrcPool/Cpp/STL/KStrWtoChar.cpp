/*$Workfile: KStrWtoChar.cpp$: implementation file
  $Revision: 2$ $Date: 2004-10-07 11:56:34$
  $Author: Darko$

  Convert wide-character string to ASCII string
  CommonSoft Inc.
  2004-09-11 Darko Kolakovic
*/

/* Group=Strings                                                             */

#ifdef _WIN32
  //Standard Microsoft Windows header files
  #include "stdafx.h"
#endif

#include <string>

std::string WtoChar(const wchar_t* lpWideCharStr, int iLen = -1);

//-----------------------------------------------------------------------------
#ifdef _WIN32
/*Converts wide-character string to single-byte character (ASCII) string.

  Returns STL string with SBCS mapping.

  Note: uses Standard Template Library (STL).

  TODO: non-Microsoft version

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
    //Calculate size of the new string
  int iSize = WideCharToMultiByte(CP_ACP, // ANSI code page
                                  0     ,   // performance and mapping flags
                                  lpWideCharStr, // wide-character string
                                  iLen , // number of chars in string
                                  NULL , // buffer for new string
                                  0 ,    // size of buffer
                                  NULL , // default for unmappable chars
                                  NULL   // set when default char used
                                  );
  if (iSize > 0)
    {
    char* szTemp = new char[iSize];

    #ifdef _DEBUG
      int iRes = WideCharToMultiByte(CP_ACP, // ANSI code page
                        0     ,// performance and mapping flags
                        lpWideCharStr, // wide-character string
                        iLen,  // number of chars in string
                        szTemp,// buffer for new string
                        iSize, // size of buffer
                        NULL , // default for unmappable chars
                        NULL   // set when default char used
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
          default:
            TRACE1("  unknown error (%d)\n", (DWORD)iRes);
          }
        }
    #else //NDEBUG
      WideCharToMultiByte(CP_ACP, // ANSI code page
               0     ,// performance and mapping flags
               lpWideCharStr, // wide-character string
               iLen,  // number of chars in string
               szTemp,// buffer for new string
               iSize, // size of buffer
               NULL , // default for unmappable chars
               NULL   // set when default char used
               );

    #endif //_DEBUG

    szTemp[iSize -1] = '\0';
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
 *  1    Biblioteka1.0         2004-10-06 16:00:48  Darko
 * $
 *****************************************************************************/
