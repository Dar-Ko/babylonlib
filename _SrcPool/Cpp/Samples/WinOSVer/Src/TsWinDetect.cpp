// TsWinDetect.cpp
// Detects the version of 32-bit Windows currently running
//
// Darko Kolakovic
// Jan. 2k

#include "stdafx.h"
#include "KWinVers.h"
#include "KWinVers.inl"   //Get Windows Version 

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern BOOL TsWriteToView(LPCTSTR lszText);
BOOL CheckWinVersion();

//TestWinOS()--------------------------------------------------------------
/*Function displays operating system version.
 */
BOOL TestWinOS()
{
extern BOOL g_bWin9x;
extern BOOL g_bWinNT;
CString strText;  //Resulting output

  //Check internal dependencies
#if (_WIN32_WINNT >= 0x0500)
  #define WINDESCIPTIONNT "2000"
#elif (_WIN32_WINNT >= 0x0400)
  #define WINDESCIPTIONNT "NT 4.0"
#else
  #define WINDESCIPTIONNT ""
#endif

#if (WINVER>=0x0500)
  #define WINDESCIPTION9X "98"
#elif (WINVER>=0x0400)
  #if (_WIN32_WINDOWS >= 0x0410)
    #define WINDESCIPTION9X "98"
  #elif (_WIN32_WINNT >= 0x0400)
    #define WINDESCIPTION9X "95 OEM SR2"
  #else  
    #define WINDESCIPTION9X "95"
  #endif
#else
  #define WINDESCIPTION9X ""
#endif

#ifndef _WIN32_WINNT
  #define _WIN32_WINNT 0
#endif
#ifndef _WIN32_WINDOWS
  #define _WIN32_WINDOWS 0
#endif

if(!TsWriteToView(_T("Compiler Dependencies:\r\n")))
  {
  TRACE0("Error: main window or view is not accessible\n");
  return FALSE; //Error: main window or view is not accessible
  }

  //Show values of some predefined macros
strText.Format(_T("\t_WIN32_WINNT=%X, WINVER=%X, _WIN32_WINDOWS=%X, _MFC_VER=%X, _MSC_VER=%d\r\n"),
               _WIN32_WINNT, WINVER, _WIN32_WINDOWS,_MFC_VER,_MSC_VER);
TsWriteToView((LPCTSTR)strText);
strText.Format(_T("\tMinimum system requirement: Windows %s %s\r\n"),WINDESCIPTION9X,WINDESCIPTIONNT);
TsWriteToView((LPCTSTR)strText);

#if (_WIN32_IE >= 0x0500)
  TsWriteToView(_T("\tInternet Explorer 5.0 and later\r\n"));
#elif (_WIN32_IE >= 0x0400)
  TsWriteToView(_T("\tInternet Explorer 4.0 and later\r\n"));
#elif (_WIN32_IE >= 0x0300)
  TsWriteToView(_T("\tInternet Explorer 3.0 and later\r\n"));
#endif

#ifdef _DEBUG
    //Dump operating system version information
  DumpOSVI();
#endif

if (CheckWinVersion())
  {
    //Running OS is Win95 / 98
  if (g_bWin9x)
    {
    TsWriteToView(_T("Running OS is Win9x\r\n"));
    }
  else if (g_bWinNT)
    {
      //Running OS is WinNT / 2k
    TsWriteToView(_T("Running OS is  WinNT/2k\r\n")); 
    }
  else
    {
      //Running OS with Win32s
    if (IsWinForWgp())
      TsWriteToView(_T("Running OS is WfWgp3.11 with Win32s\r\n"));
    else
      TsWriteToView(_T("Running OS is Win3.1x with Win32s\r\n"));
      }
  }

if (IsTerminalServer())
  {
  TsWriteToView(_T("\tTerminal Service is installed.\r\n"));
  }

CString strPlatform;
GetWindowsVersion(strPlatform);
strPlatform += _T("\r\n\r\n");
TsWriteToView((LPCTSTR)strPlatform);

GetWindowsVersionEx (strPlatform);
strPlatform += _T("\r\n");
TsWriteToView((LPCTSTR)strPlatform);

return TRUE;
}

//CheckWinVersion()------------------------------------------------------------
/*Detects Windows version.

  If 32-bit Windows is running OS returns TRUE and global flags g_bWin9x and 
  g_bWinNT are set to proper value. If running OS is Windows 3.x with Win32s,
  function returns TRUE, and flags are set to FALSE.
 */
BOOL CheckWinVersion()
{
extern BOOL g_bWinNT;
extern BOOL g_bWin9x;

OSVERSIONINFO osviData;
osviData.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
VERIFY(GetVersionEx(&osviData));

if (IsWinNT(&osviData))
  {
  g_bWin9x = FALSE;
  g_bWinNT = TRUE;
  TRACE0("CheckWinVersion()\tWindows NT/2k\n");
  }
else if (IsWin9x(&osviData))
  {
  g_bWin9x = TRUE;
  g_bWinNT = FALSE;
  TRACE0("CheckWinVersion()\tWindows 95/98\n");
  }
else if (IsWin32s(&osviData))
  {
  g_bWin9x = FALSE;
  g_bWinNT = FALSE;
  TRACE0("CheckWinVersion()\tWin32s\n");
  return TRUE;
  }
return (g_bWin9x || g_bWinNT);
}

//::GetWindowsVersion()--------------------------------------------------------
/*Returns TRUE and formatted string with version of the MS Windows OS, 
  otherwise returns FALSE and string with error message.
 */
BOOL GetWindowsVersion (CString& strWinVersion)
{
int iMajor = 0;
int iMinor = 0;
int iBuild = 0;
switch(GetWinVersion(&iMajor,&iMinor,&iBuild))
  {
  case ENV_WIN32S :
    strWinVersion.Format("Win32s %d.%d build %d",iMajor,iMinor,iBuild);
    break;
  case ENV_WIN9X  :
    {
    if (iMinor == ENV_PLATFORM_MIN_WIN98)
      strWinVersion.Format("Windows 98 %d.%d",iMajor,iMinor);
    else if  (iMinor == ENV_PLATFORM_MIN_WIN95)
      strWinVersion.Format("Windows 95 %d.%d",iMajor,iMinor);
    else
      return FALSE;
    }
    break;
  case ENV_WINNT  :
    strWinVersion.Format("Windows NT %d.%d build %d",iMajor,iMinor,iBuild);
    break;
  case (ENV_WINNT+ENV_WINSERVER)  :
    strWinVersion.Format("Windows NT Server %d.%d build %d",iMajor,iMinor,iBuild);
    break;
  case (ENV_WINNT+ENV_WINSERADV)  :
    strWinVersion.Format("Windows NT Advanced Server %d.%d build %d",iMajor,iMinor,iBuild);
    break;
  case ENV_WIN2K:
    strWinVersion.Format("Windows 2000 %d.%d build %d",iMajor,iMinor,iBuild);
    break;
  case (ENV_WIN2K+ENV_WINSERVER)  :
    strWinVersion.Format("Windows 2000 Server %d.%d build %d",iMajor,iMinor,iBuild);
    break;
  case (ENV_WIN2K+ENV_WINSERADV)  :
    strWinVersion.Format("Windows 2000 Advanced Server %d.%d build %d",iMajor,iMinor,iBuild);
    break;
  default:
    #ifdef IDS_UNAVAILABLE
      strWinVersion.LoadString(IDS_UNAVAILABLE);
    #else
      strWinVersion = _TEXT("Unavailable");
    #endif
    return FALSE;
  }
  
return TRUE;
}
