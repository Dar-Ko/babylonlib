/*$Workfile: S:\_SrcPool\Cpp\Win\32\KWinVers.h$: header file
  $Revision: 11$ $Date: 2005-04-26 11:35:56$
  $Author: Darko Kolakovic$

  Constants related to Windows platform version
  Note: Microsoft Windows specific (Win). 
  Copyright: CommonSoft Inc
  Jan 97  1st version D.Kolakovic
  Jan 2k  Updated with Win2k functions D.K.
  Jul 2k1 (check for WinNT.h/build 0087) 
 */
// Group=Windows

#ifndef _KWINVERS_H_
    //$Workfile: S:\_SrcPool\Cpp\Win\32\KWinVers.h$ sentry
  #define _KWINVERS_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

//#include <AfxWin.h>
#ifndef __AFX_H__
  #include <windows.h>
#endif

///////////////////////////////////////////////////////////////////////////////
// Declarations

#ifdef _DEBUG
    //Requires <AfxWin.h>
  #ifdef __AFX_H__
    void DumpOSVI();
  #endif
#endif

BOOL IsWinForWgp();
DWORD WINAPI GetWinVersion(int* piMajor, int* piMinor, int* piBuild);
int GetProductType();
BOOL IsProductSuiteInstalled(LPCTSTR szProductSuite);
#ifdef __AFX_H__
  BOOL GetWindowsVersionEx (CString& strWinVersion);
  BOOL GetProductSuite(CString& strProductSuite);
#endif

///////////////////////////////////////////////////////////////////////////////
/*Enable different definitions of the OSVERSIONINFOEX structure.

  Note:  Predefined macro _MFC_VER is not related with OSVERSIONINFOEX,
         but will do for the moment to distinguish different included
         header files.
 */
#if _MFC_VER < 0x600    //MFC 4.0
  #define _VER_OSVIEX 1 //OSVERSIONINFOEX not supported
#elif _MFC_VER == 0x600 //MFC 4.2
  #define _VER_OSVIEX 3 //OSVERSIONINFOEX with wReserved[2]
#elif  _MFC_VER > 0x600 //MFC 4.2+
  #define _VER_OSVIEX 4 //OSVERSIONINFOEX with wProductType
#else                   //default
  #define _VER_OSVIEX 0 //OSVERSIONINFOEX not supported
#endif

///////////////////////////////////////////////////////////////////////////////
// Macros

  //Identifies the build number of the operating system. Build number is
  //low-order word of OSVERSIONINFO::dwBuildNumber
  //
  //Note: Microsoft Windows specific (Win).
#define ENV_BUILDNO(dwBuildNo)   ((WORD) (dwBuildNo))
  //Validate if the specified product suite is available on the system.
  //Arguments are wSuiteMask and suite ID
#define ENV_SUITETYPE(wSuite, SUITETYPE) ((wSuite & SUITETYPE) == SUITETYPE)

  //OS version number codes (Microsoft)

  //Win9x, WinMe major version
#define ENV_PLATFORM_MAJ_WIN9x     4
  //Win95 minor version
#define ENV_PLATFORM_MIN_WIN95     0
  //Win98 minor version
#define ENV_PLATFORM_MIN_WIN98    10
  //Win Millennium minor version
#define ENV_PLATFORM_MIN_WINML    90
  //WinNT 3x major version
#define ENV_PLATFORM_MAJ_WINNT3    3
  //WinNT 3.50 minor version
#define ENV_PLATFORM_MIN_WINNT350 50
  //WinNT 3.51 minor version
#define ENV_PLATFORM_MIN_WINNT351 51
  //WinNT 4x major version
#define ENV_PLATFORM_MAJ_WINNT4    4
  //WinNT 4x minor version
#define ENV_PLATFORM_MIN_WINNT4    0
  //Win 2000, Win Server 2003 family major version
#define ENV_PLATFORM_MAJ_WIN2K     5
  //Win2k minor version
#define ENV_PLATFORM_MIN_WIN2K     0
  //Win2k Server 2003 minor version
#define ENV_PLATFORM_MIN_WIN2k3SER 2
  //Win XP major version
#define ENV_PLATFORM_MAJ_WINXP     5
  //WinXP minor version
#define ENV_PLATFORM_MIN_WINXP     1

///////////////////////////////////////////////////////////////////////////////
// OS platform number codes used by this library
// Windows Servers are  ENV_WINNT+ENV_WINSERVER or ENV_WIN2K+ENV_WINSERVER

  //Undetermined platform
#define ENV_UNKNOWN     0x00000000
  //Win WorkStations platforms
#define ENV_WINWRKSTN   0x00000000
  //Win Server platforms
#define ENV_WINSERVER   0x00000010
  //Win Advanced Server platforms
#define ENV_WINSERADV   0x00000020
  //Win Terminal Server
#define ENV_WINTERSER   0x00000040
  //Win32s on 16-bit platform
#define ENV_WIN32S      0x00001000
  //Win9x platforms
#define ENV_WIN9X       0x00002000
  //WinNT  platforms
#define ENV_WINNT       0x00004000
  //Win2k platforms
#define ENV_WIN2K       0x00008000
  //WinCE platforms
#define ENV_WINCE       0x00010000

///////////////////////////////////////////////////////////////////////////////
// Following constants are introduced in the Service Pack 4 for Windows NT,
// Terminal Server Edition
// (Inserted in WinNT.h/build 0087)

#if _VER_OSVIEX < 4  //_VER_OSVIEX<4
  #ifndef VER_SUITE_SMALLBUSINESS //(Inserted in WinNT.h/build 0087)
    //Used for wSuiteMask
    #define VER_SUITE_SMALLBUSINESS             0x00000001
    #define VER_SUITE_ENTERPRISE                0x00000002
    #define VER_SUITE_BACKOFFICE                0x00000004
    #define VER_SUITE_COMMUNICATIONS            0x00000008
    #define VER_SUITE_TERMINAL                  0x00000010
    #define VER_SUITE_SMALLBUSINESS_RESTRICTED  0x00000020
    #define VER_SUITE_EMBEDDEDNT                0x00000040
    #define VER_SUITE_DATACENTER                0x00000080
    #define VER_SUITE_SINGLEUSERTS              0x00000100
    #define VER_SUITE_PERSONAL                  0x00000200
    #define VER_SUITE_BLADE                     0x00000400
    #define VER_SUITE_EMBEDDED_RESTRICTED       0x00000800

    //Used for wProductType
    #define VER_NT_WORKSTATION                   1
    #define VER_NT_DOMAIN_CONTROLLER             2
    #define VER_NT_SERVER                        3
  #endif //(WinNT.h/build 0087)
#endif //_VER_OSVIEX<4

///////////////////////////////////////////////////////////////////////////////
#endif  //_KWINVERS_H_
/*****************************************************************************
 * $Log: 
 *  11   Biblioteka1.10        2005-04-26 11:35:56  Darko Kolakovic Document groups
 *       and typo fixes
 *  10   Biblioteka1.9         2004-10-01 22:35:52  Darko           stdafx.h
 *  9    Biblioteka1.8         2003-09-15 01:52:08  Darko           added WinXP
 *  8    Biblioteka1.7         2003-09-12 16:12:54  Darko           sentry
 *  7    Biblioteka1.6         2003-08-27 09:14:54  Darko           windows.h in
 *       small case
 *  6    Biblioteka1.5         2002-01-29 23:22:35  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         2002-01-24 19:22:38  Darko           Updated
 *       comments
 *  4    Biblioteka1.3         2001-08-17 00:38:26  Darko           Update
 *  3    Biblioteka1.2         2001-07-08 00:06:04  Darko           WinNT.h/build
 *       0087
 *  2    Biblioteka1.1         2001-06-08 23:52:40  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 16:04:26  Darko           
 * $
 *****************************************************************************/
