/*$Workfile: KWinVers.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  Obtains extended information about the 32-bit Windows platform that is
  currently running.
  Copyright: CommonSoft Inc
  Darko Kolakovic
  Jan. 2k D.K. Win Millenuim added (based on Joakim Fredlund
   <joakim@jockesoft.com>  code)
 */

#include "StdAfx.h"
#include "KWinVers.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#if _VER_OSVIEX < 1
  #pragma message ("_VER_OSVIEX < 1")
#elif _VER_OSVIEX == 1
  #pragma message ("_VER_OSVIEX = 1")
#elif _VER_OSVIEX == 2
  #pragma message ("_VER_OSVIEX = 2")
#elif _VER_OSVIEX == 3
  #pragma message ("_VER_OSVIEX = 3")
#elif _VER_OSVIEX == 4
  #pragma message ("_VER_OSVIEX = 4")
#elif _VER_OSVIEX == 5
  #pragma message ("_VER_OSVIEX = 5")
#elif _VER_OSVIEX > 5
  #pragma message ("_VER_OSVIEX > 5")
#endif

//::GetWindowsVersionEx()--------------------------------------------------------
/*Returns TRUE and formatted string with description of the MS Windows OS,
  otherwise returns FALSE  and string with error message.

  See also: DumpOSVI()

  Note: Microsoft Windows specific (Win).
 */
BOOL GetWindowsVersionEx (CString& strWinVersion)
{
#if _VER_OSVIEX <= 1  //_VER_OSVIEX<=1
    //OSVERSIONINFOEX is not supported

  OSVERSIONINFO osviInfo;
    {
#else                 //_VER_OSVIEX>1
  BOOL bOSVIEX = FALSE; //Flag is TRUE if GetVersionEx returns OSVERSIONINFOEX data
	OSVERSIONINFOEX osviInfo;
	osviInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	if ( (bOSVIEX = GetVersionEx((LPOSVERSIONINFO)&osviInfo)) == FALSE )
    {
    TRACE0("GetVersionEx(OSVERSIONINFOEX) is not supported\n");
#endif  //_VER_OSVIEX<=1


    osviInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    if (!GetVersionEx((LPOSVERSIONINFO) &osviInfo))
      {
      TRACE0("GetVersionEx(OSVERSIONINFO) is not supported\n");
      strWinVersion = _T("GetWindowsVersionEx() is not supported.");
      return FALSE;
      }
    }


CString strWinOS;
switch(osviInfo.dwPlatformId)
  {
    //Version with OSVERSIONINFOEX support could not run on Win32s anyway
  #if _VER_OSVIEX <= 1 //_VER_OSVIEX<=1 OSVERSIONINFOEX is not supported

    case VER_PLATFORM_WIN32s:
      {
      /*Win32s     Build          Win32s     Build
         1.1      1.1.88           1.25     1.2.141
         1.1a     1.1.89           1.25a    1.2.142
         1.15     1.15.103         1.30     1.2.159
         1.15a    1.15.111         1.30a    1.2.166
         1.2      1.2.123          1.30c    1.2.172
       */
      strWinOS = _T("with Win32s ");
      switch(ENV_BUILDNO(osviInfo.dwBuildNumber))
        {
        case  88: strWinOS += _T("1.1"  ); break;
        case  89: strWinOS += _T("1.1a" ); break;
        case 103: strWinOS += _T("1.15" ); break;
        case 111: strWinOS += _T("1.15a"); break;
        case 123: strWinOS += _T("1.2"  ); break;
        case 141: strWinOS += _T("1.25" ); break;
        case 159: strWinOS += _T("1.30" ); break;
        case 166: strWinOS += _T("1.30a"); break;
        case 172: strWinOS += _T("1.30c"); break;
        }
      }
		  break;
  #endif //_VER_OSVIEX<=1


	case VER_PLATFORM_WIN32_WINDOWS:
    {
    if(osviInfo.dwMajorVersion != ENV_PLATFORM_MAJ_WIN9x)
      strWinOS = _T("Unknown platform");
    else
      {
      switch (osviInfo.dwMinorVersion)
        {
        case ENV_PLATFORM_MIN_WIN95: strWinOS = _T("95"); break;
        case ENV_PLATFORM_MIN_WIN98: strWinOS = _T("98"); break;
        case ENV_PLATFORM_MIN_WINML: strWinOS = _T("Millenium"); break;
        default:          strWinOS = _T("Unknown platform");
        }
      }
    }
    break;

	case VER_PLATFORM_WIN32_NT:
    {
    switch(osviInfo.dwMajorVersion)
      {
      case ENV_PLATFORM_MAJ_WINNT3: strWinOS = _T("NT 3.");
        {
        switch (osviInfo.dwMinorVersion)
          {
          case ENV_PLATFORM_MIN_WINNT350: strWinOS += _T("50"); break;
          case ENV_PLATFORM_MIN_WINNT351: strWinOS += _T("51"); break;
          default:                        strWinOS += _T("??");
          }
        }
        break;
      case ENV_PLATFORM_MAJ_WINNT4: strWinOS = _T("NT 4.0"); break;
      case ENV_PLATFORM_MAJ_WIN2K:  strWinOS = _T("2000");   break;
      default: strWinOS = _T("Unknown platform");
      }

    #if _VER_OSVIEX >= 3 //_VER_OSVIEX>=3 OSVERSIONINFOEX is supported
      if (bOSVIEX)
        {
        //Note: With  WinNT.h build 087 (_VER_OSVIEX = 3) definiton of
        //     _OSVERSIONINFOEXA has been changed (_VER_OSVIEX >= 4
        //     disappeared) D.K. 7.7.2k1

        /* D.K. 7.7.2k1
        #if _VER_OSVIEX == 3   //_VER_OSVIEX=3
          switch( LOBYTE(osviInfo.wReserved[1]))
        #elif _VER_OSVIEX > 3   //_VER_OSVIEX>3
          switch(osviInfo.wProductType)
        #endif //_VER_OSVIEX=3
        */
          switch(osviInfo.wProductType) //replaced #elif D.K. 7.7.2k1
            {
            case VER_NT_WORKSTATION      :
              strWinOS += _T(" Workstation");
              break;
            case VER_NT_DOMAIN_CONTROLLER:
              strWinOS += _T(" Domain Controller");
              break;
            case VER_NT_SERVER           :
              strWinOS += _T(" Server");
              break;
            }
        }
      else
    #endif //_VER_OSVIEX>=3
        {
          //If OSVERSIONINFOEX is not available, test registry to discriminate NT workstation
          //from NT server.
        int iType = GetProductType();
        switch (iType)
          {
          case ENV_WINWRKSTN: strWinOS += _T(" Workstation")    ; break;
          case ENV_WINSERVER: strWinOS += _T(" Server")         ; break;
          case ENV_WINSERADV: strWinOS += _T(" Advanced Server"); break;
          }
        }

    }
    break;

  #ifdef _VER_CE_ // _VER_CE_
  case VER_PLATFORM_WIN32_CE:
    {
     strWinOS = _T("CE");
    }
		break;
  #endif // _VER_CE_

  default: strWinOS = _T("Unknown platform");
  }

strWinVersion.Format(_T("Microsoft Windows %s %d.%d build %d %s"),
                 (LPCTSTR)strWinOS,
                 osviInfo.dwMajorVersion,
                 osviInfo.dwMinorVersion,
                 ENV_BUILDNO(osviInfo.dwBuildNumber),
                 osviInfo.szCSDVersion);


#if _VER_OSVIEX >= 3 //_VER_OSVIEX>=3 OSVERSIONINFOEX is supported
  if (bOSVIEX)
    {
    if (osviInfo.wServicePackMajor > 0)
      {
      strWinOS.Format(_T("\tService Pack %d.%d"),
                      osviInfo.wServicePackMajor,
                      osviInfo.wServicePackMinor);
      strWinVersion += strWinOS;
      }

      strWinOS.Empty();
      /* replaced #elif; see previous note D.K. 7.7.2k1
      #if _VER_OSVIEX == 3 //_VER_OSVIEX=3
        #define wSUITEMASK osviInfo.wReserved[0]
      #else                //_VER_OSVIEX>3
        #define wSUITEMASK osviInfo.wSuiteMask
      #endif //_VER_OSVIEX=3
      */
      #define wSUITEMASK osviInfo.wSuiteMask //D.K. 7.7.2k1

      if (ENV_SUITETYPE(wSUITEMASK,VER_SUITE_BACKOFFICE))
        strWinOS  = _T("\tMicrosoft BackOffice components are installed.");
      if (ENV_SUITETYPE(wSUITEMASK,VER_SUITE_DATACENTER))
        strWinOS += _T("\tWindows 2000 Datacenter Server is installed.");
      if (ENV_SUITETYPE(wSUITEMASK,VER_SUITE_ENTERPRISE))
        strWinOS += _T("\tWindows 2000 Advanced Server is installed.");
      if (ENV_SUITETYPE(wSUITEMASK,VER_SUITE_SMALLBUSINESS))
        strWinOS += _T("\tMicrosoft Small Business Server is installed.");
      if (ENV_SUITETYPE(wSUITEMASK,VER_SUITE_SMALLBUSINESS_RESTRICTED))
        strWinOS += _T("\tRestricted Microsoft Small Business Server is installed.");
      if (ENV_SUITETYPE(wSUITEMASK,VER_SUITE_TERMINAL))
        strWinOS += _T("\tTerminal Service is installed.");
    if (!strWinOS.IsEmpty())
      strWinVersion += strWinOS;
    }
  else
#endif  //_VER_OSVIEX>=3
    {
      //If OSVERSIONINFOEX is not available, test registry for NT product suites
    if (GetProductSuite(strWinOS))
      {
      if (!strWinOS.IsEmpty())
        {
          //Append TAB delimited text
        strWinVersion += strWinOS;
        }
      }

    }

return TRUE;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         1/29/02 11:22:32 PM  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         1/25/02 4:59:48 PM   Darko           Updated
 *       comments
 *  4    Biblioteka1.3         8/17/01 12:38:22 AM  Darko           Update
 *  3    Biblioteka1.2         7/8/01 12:06:15 AM   Darko           WinNT.h/build
 *       0087
 *  2    Biblioteka1.1         6/8/01 11:52:37 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 4:04:23 PM   Darko           
 * $
 *****************************************************************************/
