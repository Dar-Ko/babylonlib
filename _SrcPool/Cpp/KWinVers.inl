/*$Workfile: KWinVers.inl$: header file
  $Revision: 1.3 $ $Date: 2003/01/28 05:39:56 $
  $Author: ddarko $

  Detect operating system and Windows platform version
  Copyright: CommonSoft Inc.
  Jan 97  1st Version D.Kolakovic
  Jan 2k  Updated with Win2k functions D.K.
 */
 
#ifndef _KWINVERS_INL_
    //KWinVers.inl sentry
  #define _KWINVERS_INL_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _WIN32

//#include <AfxWin.h>
#ifndef __AFX_H__
  #include <Windows.h>
#endif


///////////////////////////////////////////////////////////////////////////////
// Inlines
//IsWin9x()--------------------------------------------------------------------
/*Returns TRUE if Windows version is Win95 or Win98.

  Note: Microsoft Windows specific (Win).
 */
inline BOOL IsWin9x(LPOSVERSIONINFO posviData)
  {
  return (posviData->dwPlatformId == VER_PLATFORM_WIN32_WINDOWS);
  }
inline BOOL IsWin9x()
  {
  OSVERSIONINFO osviData;
  osviData.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    //The function fails if the value of the dwOSVersionInfoSize is too small
  VERIFY(GetVersionEx(&osviData));
  return IsWin9x(&osviData);
  }

//IsWinNT()--------------------------------------------------------------------
/*Returns TRUE if Windows version is WinNT or Win2k.

  Note: Microsoft Windows specific (Win).

  Example:
    #include "UWinVers.inl"   //Get Windows Version
    void CheckWinVersion()
      {
      OSVERSIONINFO osviData;
      osviData.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
      VERIFY(GetVersionEx(&osviData));

      if (IsWinNT(&osviData))
        {
        TRACE0("CheckWinVersion()\tWindows NT/2k\n");
        }
      else if (IsWin9x(&osviData))
        {
        TRACE0("CheckWinVersion()\tWindows 95/98\n");
        }
      }
 */
inline BOOL IsWinNT(LPOSVERSIONINFO posviData)
  {
  return (posviData->dwPlatformId == VER_PLATFORM_WIN32_NT);
  }

inline BOOL IsWinNT()
  {
  OSVERSIONINFO osviData;
  osviData.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    //The function fails if the value of the dwOSVersionInfoSize is too small
  VERIFY(GetVersionEx(&osviData));
  return IsWinNT(&osviData);
  }

//IsWin32s()-------------------------------------------------------------------
/*Returns TRUE if Windows version is 16-bit Windows with Win32s.

  Note: Microsoft Windows specific (Win).
 */
inline BOOL IsWin32s(LPOSVERSIONINFO posviData)
  {
  return (posviData->dwPlatformId == VER_PLATFORM_WIN32s);
  }

inline BOOL IsWin32s()
  {
  OSVERSIONINFO osviData;
  osviData.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    //The function fails if the value of the dwOSVersionInfoSize is too small
  VERIFY(GetVersionEx(&osviData));
  return IsWin32s(&osviData);
  }

//IsTerminalServer()-----------------------------------------------------------
/*Returns TRUE if Terminals Service is available on system with WinNT / Win2k

  Note: compatibility with Windows 95/98 requires ANSI compliance.

  Note: Microsoft Windows specific (Win).
 */
inline BOOL IsTerminalServer()
  {
  BOOL IsProductSuiteInstalled(LPCTSTR szProductSuite);
  return IsProductSuiteInstalled(_T("Terminal Server"));
  }

//GetWinVer()------------------------------------------------------------------
/*Returns value of the 32-bit Windows operating system version number, stored in
  _winver variable. In high byte is _winmajor and value of _winminor in low byte.
  Declaration for the variable is in StdLib.h

  Note: Microsoft Windows specific (Win).
 */
inline UINT GetWinVer()
  {
  return _winver;
  }

//GetWinMajor()----------------------------------------------------------------
/*Returns value of the 32-bit Windows operating system major version number,
  stored in  _winmajor variable.
  Declaration for the variable is in StdLib.h

  Note: Microsoft Windows specific (Win).
 */
inline UINT GetWinMajor()
  {
  return _winmajor;
  }

//GetWinMinor()----------------------------------------------------------------
/*Returns value of the 32-bit Windows operating system minor version number,
  stored in _winminor variable.
  Declaration for the variable is in StdLib.h

  Note: Microsoft Windows specific (Win).
 */
inline UINT GetWinMinor()
  {
  return _winminor;
  }

//GetOSBuild()-----------------------------------------------------------------
/*Returns value of the 32-bit Windows operating system build version number,
  stored in _osver variable.
  Declaration for the variable is in StdLib.h

  Note: Microsoft Windows specific (Win).
 */
inline UINT GetOSBuild()
  {
  return _osver;
  }

///////////////////////////////////////////////////////////////////////////////

  #endif  //_WIN32
#endif //_KWINVERS_INL_
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         8/16/01 11:38:29 PM  Darko           Update
 *  3    Biblioteka1.2         7/7/01 11:10:38 PM   Darko           $Revision: 1.3 $
 *       inserted
 *  2    Biblioteka1.1         6/8/01 10:52:42 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 3:04:28 PM   Darko           
 * $
 *****************************************************************************/
