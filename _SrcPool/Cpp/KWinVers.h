/*$Workfile: KWinVers.h$: header file
  $Revision: 1.3 $ $Date: 2003/01/28 05:39:56 $
  $Author: ddarko $

  Constants related to Windows platform version
  Note: Microsoft Windows specific (Win). 
  Copyright: CommonSoft Inc
  Jan 97  1st version D.Kolakovic
  Jan 2k  Updated with Win2k functions D.K.
  Jul 2k1 (check for WinNT.h/build 0087) 
 */
#ifndef __KWINVERS_H__
    //KWinVers.h sentry
  #define __KWINVERS_H__

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

//#include <AfxWin.h>
#ifndef __AFX_H__
  #include <Windows.h>
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

  //Win9x major version
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
  //Win 2000 major version
#define ENV_PLATFORM_MAJ_WIN2K     5

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
  //Win32s on 16-bit platform
#define ENV_WIN32S      0x00001000
  //Win9x platforms
#define ENV_WIN9X       0x00002000
  //WinNT  platforms
#define ENV_WINNT       0x00004000
  //Win2k platforms
#define ENV_WIN2K       0x00008000

///////////////////////////////////////////////////////////////////////////////
// Following constants are introduced in the Service Pack 4 for Windows NT,
// Terminal Server Edition
// (Inserted in WinNT.h/build 0087)

#if _VER_OSVIEX < 4  //_VER_OSVIEX<4
  #ifndef VER_SUITE_SMALLBUSINESS //(Inserted in WinNT.h/build 0087)
    //Used for wSuiteMask
    #define VER_SUITE_SMALLBUSINESS              1
    #define VER_SUITE_ENTERPRISE                 2
    #define VER_SUITE_BACKOFFICE                 4
    #define VER_SUITE_TERMINAL                  16
    #define VER_SUITE_SMALLBUSINESS_RESTRICTED  32
    #define VER_SUITE_DATACENTER               128

    //Used for wProductType
    #define VER_NT_WORKSTATION                   1
    #define VER_NT_DOMAIN_CONTROLLER             2
    #define VER_NT_SERVER                        3
  #endif //(WinNT.h/build 0087)
#endif //_VER_OSVIEX<4

///////////////////////////////////////////////////////////////////////////////
#endif  //__KWINVERS_H__
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         29/01/2002 10:22:35 PMDarko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         24/01/2002 6:22:38 PMDarko           Updated
 *       comments
 *  4    Biblioteka1.3         16/08/2001 11:38:26 PMDarko           Update
 *  3    Biblioteka1.2         07/07/2001 11:06:04 PMDarko           WinNT.h/build
 *       0087
 *  2    Biblioteka1.1         08/06/2001 10:52:40 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:04:26 PMDarko           
 * $
 *****************************************************************************/
