/*$Workfile: KWinVerG.cpp$: implementation file
  $Revision: 8$ $Date: 2004-10-01 21:35:47$
  $Author: Darko$

  Retrieve more detailed information about Windows platform using GetVersion() function
  Copyright: CommonSoft Inc
  Darko Kolakovic  May 97
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#pragma warning(disable: 4201)  //warning: nonstandard extension used : nameless struct/union in WinNT.h
#include "KWinVers.h"   //constants
#pragma warning(default: 4201)

#include "KWinVerG.inl" //IsWinNT()
#ifndef _WINDOWS_
  #include <Windows.h>
#endif
#include <winreg.h>

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif


//GetWinVersion()--------------------------------------------------------------
/*Returns the code specifying the operating system platform and current major 
  and minor version numbers of Windows.

  Note: GetVersion() function is used to obtain platform version.

  Note: Microsoft Windows specific (Win).

  Example:
    #include "KWinVers.h"
    BOOL GetWindowsVersion (CString& strWinVersion)
    {
    int iMajor = 0;
    int iMinor = 0;
    int iBuild = 0;
    LPTSTR strWinOS;
    switch(GetWinVersion(&iMajor,&iMinor,&iBuild))
      {
      case ENV_WIN32S :
        switch(iBuild)
          {
          case  88: strWinOS = _T("1.1"  ); break;
          case  89: strWinOS = _T("1.1a" ); break;
          case 103: strWinOS = _T("1.15" ); break;
          case 111: strWinOS = _T("1.15a"); break;
          case 123: strWinOS = _T("1.2"  ); break;
          case 141: strWinOS = _T("1.25" ); break;
          case 159: strWinOS = _T("1.30" ); break;
          case 166: strWinOS = _T("1.30a"); break;
          case 172: strWinOS = _T("1.30c"); break;
          }
        strWinVersion.Format("Win32s %s %d.%d build %d",
                              strWinOS,
                              iMajor,
                              iMinor,
                              iBuild);
        break;
      case ENV_WIN9X  :
        {
        if (iMinor == ENV_PLATFORM_MIN_WIN98)
          strWinVersion.Format("Windows 98 %d.%d",iMajor,iMinor);
        else if  (iMinor == ENV_PLATFORM_MIN_WIN95)
          strWinVersion.Format("Windows 95 %d.%d",iMajor,iMinor);
        else if  (iMinor == ENV_PLATFORM_MIN_WINML)
          strWinVersion.Format("Windows Millenium %d.%d",iMajor,iMinor);
        else
          return FALSE;
        }
        break;
      case ENV_WINNT  :
        strWinVersion.Format("Windows NT %d.%d build %d",iMajor,iMinor,iBuild);
        break;
      case (ENV_WINNT+ENV_WINSERVER)  :
        strWinVersion.Format("Windows NT Server %d.%d build %d",
                              iMajor,
                              iMinor,
                              iBuild);
        break;
      case (ENV_WINNT+ENV_WINSERADV)  :
        strWinVersion.Format("Windows NT Advanced Server %d.%d build %d",
                              iMajor,
                              iMinor,
                              iBuild);
        break;
      case ENV_WIN2K:
        switch (iMinor)
          {
          case ENV_PLATFORM_MIN_WIN2K:     strWinOS = _T("2000"); break;
          case ENV_PLATFORM_MIN_WINXP:     strWinOS = _T("XP"); break;
          case ENV_PLATFORM_MIN_WIN2k3SER: strWinOS = _T("2000 Server 2003");
            break;
          default:                         strWinOS = _T("??");
          }
        strWinVersion.Format("Windows %s %d.%d build %d",
                              strWinOS,
                              iMajor,
                              iMinor,
                              iBuild);
        break;
      case (ENV_WIN2K+ENV_WINSERVER)  :
        strWinVersion.Format("Windows 2000 Server %d.%d build %d",
                              iMajor,
                              iMinor,
                              iBuild);
        break;
      case (ENV_WIN2K+ENV_WINSERADV)  :
        strWinVersion.Format("Windows 2000 Advanced Server %d.%d build %d",
                              iMajor,
                              iMinor,
                              iBuild);
        break;
      default:
        strWinVersion = _TEXT("Unavailable");
        return FALSE;
      }
    return TRUE;
    }
 */
DWORD WINAPI GetWinVersion(int* piMajor, //[out] resulting major version number
                           int* piMinor, //[out] resulting minor version number
                           int* piBuild  //[out] resulting build number
                           )

{  
DWORD dwEnviron = ENV_UNKNOWN;
DWORD dwVersion = GetVersion();
  //Get the Windows version.
*piMajor = LOBYTE(LOWORD(dwVersion));
*piMinor = HIBYTE(LOWORD(dwVersion));   

/*To distinguish between operating system platforms, the high order bit and 
  the low order byte are used, as shown in the following table:

    Platform  | High-order Remaining bits      Low-order word  Low-order word
              |  bit       in the high-order   low-order byte  high-order byte
              |            word                (major number)  (minor number)
    ----------+--------------------------------------------------------------
    Win2k,XP  |    0       build number              5            minor
    WinNT 4.0 |    0       build number              4            minor
    WinNT 3.51|    0       build number              3            minor
   Win95/98/Mi|    1       reserved                  4          0, 10 or 90
    Win32s    |    1       build number              3            minor
*/

if (IsWinNT(dwVersion)) //WinNT or Win2k or WinXP
  {
    //Get the build number for Windows NT/Windows 2000
    //High-order bit is always 0, therefore a mask is not necessary
  *piBuild = (int)(HIWORD(dwVersion));

  if (*piMajor == ENV_PLATFORM_MAJ_WIN2K)
    dwEnviron = ENV_WIN2K;
  if (*piMajor < ENV_PLATFORM_MAJ_WIN2K)
    dwEnviron = ENV_WINNT;

    //Check registry to distinguish NT from NT Server
  int iType = GetProductType();
  if (iType > 0)
    dwEnviron += iType;
  }
else  //Win32s or Win9x
  {
  //Check major version number to distinguish Win32s from Win9x
  //(in the LOBYTE of the LOWORD)
  if (LOBYTE(LOWORD(dwVersion)) == 3) 
    {
    dwEnviron = ENV_WIN32S;
    *piBuild = (int)(HIWORD(dwVersion) & ~0x8000);
    }
  else
    {
    dwEnviron = ENV_WIN9X;
      //Windows 95/98/Millennium - no build number
    *piBuild = 0;
    }
  }

return dwEnviron;
} 

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  8    Biblioteka1.7         2004-10-01 21:35:47  Darko           stdafx.h
 *  7    Biblioteka1.6         2003-09-15 00:52:02  Darko           added WinXP
 *  6    Biblioteka1.5         2003-08-13 12:53:58  Darko           comment
 *  5    Biblioteka1.4         2002-01-29 22:22:25  Darko           Used lbraries
 *       notes 
 *  4    Biblioteka1.3         2002-01-25 15:59:38  Darko           Updated
 *       comments
 *  3    Biblioteka1.2         2001-07-11 21:53:40  Darko           
 *  2    Biblioteka1.1         2001-06-08 22:52:33  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:04:18  Darko           
 * $
 *  0    1997-05 Darko Kolakovic
 *****************************************************************************/
