/*$Workfile: KDbgOSVI.cpp$: implementation file
  $Revision: 10$ $Date: 2005-06-21 11:12:58$
  $Author: Darko Kolakovic$

  Dumps operating system version information
  Copyright: CommonSoft Inc.
  D.Kolakovic Jan. 2k
 */

// Group=Diagnostic

/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
//Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)

  //Fix MS VC .Net 7.1 problem: without precompiled header WINVER not defined
#if _MSC_VER == 1310
  #ifndef WINVER
    #define WINVER 0x400
  #endif
#endif

#include <AfxWin.h>
#include "KWinVers.h" //_VER_osviInfoEX

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//DumposviInfo()-------------------------------------------------------------------
/*Dump the operating system version information. Function creates a list based
  on OSVERSIONINFO or OSVERSIONINFOEX structure.

      struct _OSVERSIONINFOA
        {
        DWORD dwOSVersionInfoSize;//size of this data structure [bytes]
        DWORD dwMajorVersion;     //major version number of the operating system
        DWORD dwMinorVersion;     //minor version number of the operating system.
        DWORD dwBuildNumber;      //the build number of the operating system
                                  //in the low-order word. The high-order word
                                  //contains the major and minor version numbers.
        DWORD dwPlatformId;       //platform supported by the operating system
        CHAR  szCSDVersion[ 128 ];//maintenance string for PSS usage
        } OSVERSIONINFO

  dwPlatformId member can have one of the following values:
  - VER_PLATFORM_WIN32s         Win32s on Windows 3.1
  - VER_PLATFORM_WIN32_WINDOWS  Win32 on Windows 9x
  - VER_PLATFORM_WIN32_NT       Windows NT, Windows 2000, Windows XP
  - VER_PLATFORM_WIN32_CE       Win32 on Windows CE

      struct _OSVERSIONINFOEXA {
        DWORD dwOSVersionInfoSize;//size of this data structure [bytes]
        DWORD dwMajorVersion;     //major version number of the operating system
        DWORD dwMinorVersion;     //minor version number of the operating system.
        DWORD dwBuildNumber;      //the build number of the operating system
                                  //in the low-order word. The high-order word
                                  //contains the major and minor version numbers.
        DWORD dwPlatformId;       //the platform supported by the operating system
        CHAR  szCSDVersion[ 128 ];//maintenance string for PSS usage
        WORD  wServicePackMajor;  //major version number of the latest
                                  //Service Pack if installed on the system or 0
        WORD  wServicePackMinor;  //the minor version number of the latest
                                  //Service Pack
        #if _VER_osviInfoEX == 3
         WORD wReserved[2];       //as defined in WinBase.h line 7998 from 24.4.98
        #elif  _VER_osviInfoEX >= 4 (or ==3) build 087 //as defined in WinNT. h
                                  //build 087 but _VER_osviInfoEX = 3 !! D.K.
         WORD wSuiteMask;         //the product suites available on the system
         BYTE wProductType;       //additional information about the system
         BYTE wReserved;
        #endif
      } OSVERSIONINFOEXA

  dwMajorVersion is the major version number of the operating system and can be
  one of the following values:
  - Windows 95                  4
  - Windows 98                  4
  - Windows Me                  4
  - Windows NT 3.51             3
  - Windows NT 4.0              4
  - Windows 2000                5
  - Windows XP                  5
  - Windows Server 2003 family  5

  dwMinorVersion is the minor version number of the operating system and can be
  one of the following values:
  - Windows 95                  0
  - Windows 98                 10
  - Windows Me                 90
  - Windows NT 3.51            51
  - Windows NT 4.0              0
  - Windows 2000                0
  - Windows XP                  1
  - Windows Server 2003 family  2

  wSuiteMask member can have one or more of the following values:

      VER_SUITE_SMALLBUSINESS             0x001 Microsoft Small Business Server
                                                is installed.
      VER_SUITE_ENTERPRISE                0x002 Windows 2000 Advanced Server
                                                is installed.
      VER_SUITE_BACKOFFICE                0x004 Microsoft BackOffice components
                                                are installed.
      VER_SUITE_COMMUNICATIONS            0x008
      VER_SUITE_TERMINAL                  0x010 Terminal Service is installed.
      VER_SUITE_SMALLBUSINESS_RESTRICTED  0x020 Microsoft Small Business Server
                                                is installed with the restrictive
                                                client license.
      VER_SUITE_EMBEDDEDNT                0x040
      VER_SUITE_DATACENTER                0x080 Windows 2000 Datacenter Server
                                                is installed.
      VER_SUITE_SINGLEUSERTS              0x100
      VER_SUITE_PERSONAL                  0x200 Windows XP Home Edition
                                                is installed.
      VER_SUITE_BLADE                     0x400 Windows Server 2003, Web Edition
                                                is installed.
      VER_SUITE_EMBEDDED_RESTRICTED       0x800
      VER_SUITE_SECURITY_APPLIANCE        TODO: Windows Server 2003 is installed
                                                as a hardened operating system
                                                as part of a security appliance.
      VER_SERVER_NT                       0x80000000
      VER_WORKSTATION_NT                  0x40000000

  wProductType member can have one of the following values:

      VER_NT_WORKSTATION                  Windows NT 4.0 Workstation,
                                          Windows 2000 Professional,
                                          Windows XP Home Edition,
                                          or Windows XP Professional.
      VER_NT_DOMAIN_CONTROLLER            Windows 2000 domain controller
      VER_NT_SERVER                       Windows 2000 Server

  Win32s Release versions and corresponding build numbers:

      Win32s version    Build
          1.1          1.1.88
          1.1a         1.1.89
          1.15         1.15.103
          1.15a        1.15.111
          1.2          1.2.123
          1.25         1.2.141
          1.25a        1.2.142
          1.30         1.2.159
          1.30a        1.2.166
          1.30c        1.2.172

  Note: uses Microsoft Foundation Library (MFC).
        Microsoft Windows specific (Win).
 */
void DumpOsviInfo()
{

#if _VER_osviInfoEX <= 1  //_VER_osviInfoEX<=1
    //OSVERSIONINFOEX is not supported
  #if _MFC_VER == 0x400
    #pragma message ( "MFC version 4.0")
  #endif

  OSVERSIONINFO osviInfo;
    {
#else                 //_VER_osviInfoEX>1
  #if _MFC_VER == 0x600
    #pragma message ( "MFC version 4.2")
  #endif
  BOOL bosviInfoEX = FALSE; //Flag is TRUE if GetVersionEx returns OSVERSIONINFOEX data
  OSVERSIONINFOEX osviInfo;
  osviInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

  if ((bosviInfoEX = GetVersionEx((LPOSVERSIONINFO)&osviInfo)) == TRUE)
    afxDump << _T("OSVERSIONINFOEX\n\t{\n");
  else
    {
    TRACE0("GetVersionEx(OSVERSIONINFOEX) is not supported\n");
#endif  //_VER_osviInfoEX<=1


    osviInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (GetVersionEx((LPOSVERSIONINFO) &osviInfo))
      afxDump << _T("OSVERSIONINFO\n\t{\n");
    else
      {
      TRACE0("GetVersionEx(OSVERSIONINFO) is not supported\n");
      return;
      }
    }


afxDump << _T("\tData Size =") <<  osviInfo.dwOSVersionInfoSize << _T("[bytes]")
        << _T("\n\tMajor ver. no.=") << osviInfo.dwMajorVersion
        << _T(" Minor ver. no.=") << osviInfo.dwMinorVersion
        << _T("\n\tBuild no.=") << ENV_BUILDNO(osviInfo.dwBuildNumber)
        << _T(" Major =") << HIBYTE(LOWORD(osviInfo.dwMajorVersion))
        << _T(" Minor =") << LOBYTE(LOWORD(osviInfo.dwMajorVersion))
        << _T("\n\tPlatform ID =") << osviInfo.dwPlatformId
        << _T("\n\tCSD =") <<  osviInfo.szCSDVersion;

#if _VER_osviInfoEX > 1 //_VER_osviInfoEX>1 OSVERSIONINFOEX is supported
  if (bosviInfoEX)
    {
    afxDump << _T("\n\tService Pack Major=") << osviInfo.wServicePackMajor
            << _T(" Minor =") << osviInfo.wServicePackMinor;

        //Note: With  WinNT.h build 087 (_VER_osviInfoEX = 3) definiton of
        //     _OSVERSIONINFOEXA has been changed (_VER_osviInfoEX >= 4
        //     disappeared) D.K. 7.7.2k1

    /*D.K. 7.7.2k1
    #if _VER_osviInfoEX == 3 //_VER_osviInfoEX=3
      afxDump << _T("\n\tSuite type =") << osviInfo.wReserved[0]
              << _T(" wProductType =")  << LOBYTE(osviInfo.wReserved[1]);
    #elif _VER_osviInfoEX > 3 //_VER_osviInfoEX>3
      afxDump << _T("\n\tSuite type =") << osviInfo.wSuiteMask
              << _T(" wProductType =") << (int)osviInfo.wProductType;
    #endif //_VER_osviInfoEX=3
    */
    #if _VER_osviInfoEX >= 3 //_VER_osviInfoEX=3 D.K. 7.7.2k1
      afxDump << _T("\n\tSuite type =") << osviInfo.wSuiteMask
              << _T(" wProductType =") << (int)osviInfo.wProductType;
    #endif //_VER_osviInfoEX>=3
    }
#endif  //_VER_osviInfoEX>1

afxDump << _T("\n\t}");

switch(osviInfo.dwPlatformId)
  {
  case VER_PLATFORM_WIN32s:
    {
    afxDump << _T("\n\tMicrosoft Windows with Win32s ")
            << osviInfo.dwMajorVersion
            << osviInfo.dwMinorVersion
            << _T(" build ") << ENV_BUILDNO(osviInfo.dwBuildNumber)
            << _T(" ") << osviInfo.szCSDVersion << _T("\n");
    }
    break;

  case VER_PLATFORM_WIN32_WINDOWS:
    {
    if(osviInfo.dwMajorVersion != ENV_PLATFORM_MAJ_WIN9x)
      afxDump << _T("\n\tUnknown platform\n");
    else
      {
      afxDump << _T("\n\tMicrosoft Windows ");
      switch (osviInfo.dwMinorVersion)
        {
        case ENV_PLATFORM_MIN_WIN95: afxDump << _T("95 ");
          if ( osviInfo.szCSDVersion[1] == 'C' || osviInfo.szCSDVersion[1] == 'B' )
            afxDump << _T("OSR2 ");
          break;
        case ENV_PLATFORM_MIN_WIN98: afxDump << _T("98 ");
          if ( osviInfo.szCSDVersion[1] == 'A' )
            afxDump << _T("SE ");
          break;
        default:                     afxDump << _T("9? ");
        }
      afxDump << _T(" build ") << ENV_BUILDNO(osviInfo.dwBuildNumber)
              << _T(" ") << osviInfo.szCSDVersion << _T("\n");
      }
    }
    break;

  case VER_PLATFORM_WIN32_NT:
    {
    if((osviInfo.dwMajorVersion < ENV_PLATFORM_MAJ_WINNT3) ||
       (osviInfo.dwMajorVersion > ENV_PLATFORM_MAJ_WIN2K)    )
      afxDump << _T("\n\tUnknown platform\n");
    else
      {
      afxDump << _T("\n\tMicrosoft Windows ");
      switch(osviInfo.dwMajorVersion)
        {
        case ENV_PLATFORM_MAJ_WINNT3: afxDump << _T("NT 3.");
          {
          switch (osviInfo.dwMinorVersion)
            {
            case ENV_PLATFORM_MIN_WINNT350: afxDump << _T("50 "); break;
            case ENV_PLATFORM_MIN_WINNT351: afxDump << _T("51 "); break;
            default:                        afxDump << _T("?? ");
            }
          }
          break;
        case ENV_PLATFORM_MAJ_WINNT4: afxDump << _T("NT 4.0 "); break;

        case ENV_PLATFORM_MAJ_WIN2K:
        //case ENV_PLATFORM_MAJ_WINXP:
          {
          switch (osviInfo.dwMinorVersion)
            {
            case ENV_PLATFORM_MIN_WIN2K:     afxDump << _T("2000 "); break;
            case ENV_PLATFORM_MIN_WINXP:     afxDump << _T("XP "); break;
            case ENV_PLATFORM_MIN_WIN2k3SER: afxDump << _T("2000 Server 2003 "); break;
            default:                         afxDump << _T("?? ");
            }
          }
          break;
        }
      afxDump << _T(" build ") << ENV_BUILDNO(osviInfo.dwBuildNumber)
              << _T(" ") << osviInfo.szCSDVersion << _T("\n");
      }
    }
    break;

  #ifdef _VER_CE_
  case VER_PLATFORM_WIN32_CE:
    {
    afxDump << _T("\n\tMicrosoft Windows CE ")
            << osviInfo.dwMajorVersion
            << osviInfo.dwMinorVersion
            << _T(" build ") << ENV_BUILDNO(osviInfo.dwBuildNumber)
            << _T(" ") << osviInfo.szCSDVersion << _T("\n");
    }
    break;
  #endif // _VER_CE_

  default: afxDump << _T("\n\tUnknown platform\n");
  }

#if _VER_osviInfoEX >= 3 //_VER_osviInfoEX>=3 OSVERSIONINFOEX is supported
  if (bosviInfoEX)
    {
    if (osviInfo.wServicePackMajor > 0)
      {
      afxDump << _T("\tService Pack ") << osviInfo.wServicePackMajor
              << _T(".") << osviInfo.wServicePackMinor
              << _T("\n");
      }

      /*D.K. 7.7.2k1
      #if _VER_osviInfoEX == 3 //_VER_osviInfoEX=3
        switch(LOBYTE(osviInfo.wReserved[1]))
      #else                //_VER_osviInfoEX>3
        switch(osviInfo.wProductType)
      #endif //_VER_osviInfoEX=3
       */
        switch(osviInfo.wProductType) //D.K. 7.7.2k1
          {
          case VER_NT_WORKSTATION      :
            {
            switch(osviInfo.dwMajorVersion)
              {
              case ENV_PLATFORM_MAJ_WINNT4:
                afxDump << _T("\tWorkstation 4.0\n");
                break;
              default:
                if( osviInfo.wSuiteMask & VER_SUITE_PERSONAL )
                  afxDump << _T("\tHome Edition\n");
                else
                  afxDump << _T("\tProfessional\n");
              }
            }
            break;
          case VER_NT_DOMAIN_CONTROLLER:
            afxDump << _T("\tDomain Controller ");
          case VER_NT_SERVER           :
            afxDump << _T(" Server ");
            if(osviInfo.dwMajorVersion == ENV_PLATFORM_MAJ_WIN2K)
              {
              switch(osviInfo.dwMinorVersion)
                {
                case ENV_PLATFORM_MIN_WIN2k3SER:
                  if( osviInfo.wSuiteMask & VER_SUITE_DATACENTER )
                     afxDump << _T("Datacenter Edition\n");
                  else if( osviInfo.wSuiteMask & VER_SUITE_ENTERPRISE )
                     afxDump << _T("Enterprise Edition\n");
                  else if ( osviInfo.wSuiteMask == VER_SUITE_BLADE )
                     afxDump << _T("Web Edition\n");
                  else
                     afxDump << _T("Standard Edition\n");
                  break;
                case ENV_PLATFORM_MIN_WIN2K:
                  if( osviInfo.wSuiteMask & VER_SUITE_DATACENTER )
                     afxDump << _T("Datacenter " );
                  else if( osviInfo.wSuiteMask & VER_SUITE_ENTERPRISE )
                     afxDump << _T("Advanced\n" );
                }
              }
            else  // Windows NT 4.0
              {
              if( osviInfo.wSuiteMask & VER_SUITE_ENTERPRISE )
                  afxDump << _T("4.0, Enterprise Edition\n");
              else
                  afxDump << _T("4.0\n");
              }
            }

            break;
          }
      /*D.K. 7.7.2k1
      #if _VER_osviInfoEX == 3 //_VER_osviInfoEX=3
        #define wSUITEMASK osviInfo.wReserved[0]
      #else                //_VER_osviInfoEX>3
        #define wSUITEMASK osviInfo.wSuiteMask
      #endif //_VER_osviInfoEX=3
      */
     #define wSUITEMASK osviInfo.wSuiteMask  //D.K. 7.7.2k1

      if (ENV_SUITETYPE(wSUITEMASK,VER_SUITE_BACKOFFICE))
        afxDump << _T("\tMicrosoft BackOffice components are installed.\n");
      if (ENV_SUITETYPE(wSUITEMASK,VER_SUITE_SMALLBUSINESS))
        afxDump << _T("\tMicrosoft Small Business Server is installed.\n");
      if (ENV_SUITETYPE(wSUITEMASK,VER_SUITE_SMALLBUSINESS_RESTRICTED))
        afxDump << _T("\tRestricted Microsoft Small Business Server is installed.\n");
      if (ENV_SUITETYPE(wSUITEMASK,VER_SUITE_TERMINAL))
        afxDump << _T("\tTerminal Service is installed.\n");
    }
  else //OSVERSIONINFOEX is not supported

#endif  //_VER_osviInfoEX>=3

    {
      //If OSVERSIONINFOEX is not available, test registry for NT product suites
    CString strProduct;
    if (GetProductSuite(strProduct))
      {
      if (!strProduct.IsEmpty())
        afxDump << _T("Installed products: ") << (LPCTSTR)strProduct << _T("\n");
      }
      //If OSVERSIONINFOEX is not available, test registry for NT workstation
      //versus NT server.
    int iType = GetProductType();
    switch (iType)
      {
      case ENV_WINWRKSTN: afxDump << _T("\tWindows NT Workstation\n"); break;
      case ENV_WINSERVER: afxDump << _T("\tWindows NT Server\n"); break;
      case ENV_WINSERADV: afxDump << _T("\tWindows NT Advanced Server\n"); break;
      }
    }

}

///////////////////////////////////////////////////////////////////////////////
#endif  // _DEBUG

/*Note: as definrd in WinNT.h build 087 (_VER_osviInfoEX = 3)

  typedef struct _OSVERSIONINFOEXA {
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    CHAR   szCSDVersion[ 128 ];     // Maintenance string for PSS usage
    WORD   wServicePackMajor;
    WORD   wServicePackMinor;
    WORD   wSuiteMask;
    BYTE  wProductType;
    BYTE  wReserved;
  } OSVERSIONINFOEXA, *POSVERSIONINFOEXA, *LPOSVERSIONINFOEXA;
*/
