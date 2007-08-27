/*$Workfile: KStrWtoA.cpp$: implementation file
  $Revision: 1$ $Date: 2005-03-21 03:17:32$
  $Author: Darko$

  Convert wide-character string to ASCII string
  Copyright: Commonsoft Inc.
  2007-08-11 Darko Kolakovic
*/

/* Group=Strings                                                             */

#ifdef _WIN32
//Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
#if defined _ATL_VER
  #ifndef TRACE
    #define TRACE0 ATLTRACE
    #define TRACE1 ATLTRACE
  #endif
#else
  #include <windows.h>
//  #include <string.h>
#endif

#ifndef TRACE0
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

//-----------------------------------------------------------------------------
/*Converts wide-character string to single-byte character (ASCII) string.
  The resusult would be stored in the space allocated with new[] operator. The
  caller is responsibile for deleting the string buffer after using it.

  Returns zero-terminated string with SBCS mapping or NULL in case of a failure.
  Call GetLasteError() to obtain more information about the reason for the
  failure.

  Note: Microsoft Windows specific (Win32).

  See also: SBCS, _UNICODE
 */
LPSTR WtoA(LPWSTR szWideCharStr //[in] zero-terminated string to be converted
          )
{
ASSERT(szWideCharStr != NULL);
LPSTR szResult = NULL;
if (szWideCharStr != NULL)
  {
  //Get the length of the source string
  int iSize = WideCharToMultiByte( CP_ACP, // ANSI code page
                                0,      // performance and mapping flags
                                szWideCharStr, // wide-character string
                                -1,     // string is zero-terminated
                                NULL,   // buffer for new string
                                0,      // size of buffer
                                NULL,   // default for unmappable chars
                                NULL    // set when default char used
                                );
  if (iSize > 0)
    {
    //Allocate space to hold the converted string
    szResult = (LPSTR)new char[iSize];

    if (szResult != NULL)
      {
      //Convert the string
      int iRes = WideCharToMultiByte(CP_ACP, // ANSI code page
                        0     ,  // performance and mapping flags
                        szWideCharStr, // wide-character string
                        -1,      // string is zero-terminated
                        szResult,// buffer for new string
                        iSize,   // size of buffer
                        NULL ,   // default for unmappable chars
                        NULL     // set when default char used
                        );
      if (iRes == 0)
        {
        #ifdef _DEBUG
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
        #endif

        delete [] szResult;
        szResult = NULL;
        }
      else
        szResult[iSize -1] = '\0'; //Set string terminator
      }
    }
  }
else
  {
  SetLastError(ERROR_INVALID_DATA);
  }
return szResult;
}
#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:  $
 *****************************************************************************/
