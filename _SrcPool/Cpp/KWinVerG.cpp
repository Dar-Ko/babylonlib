/*$Workfile: KWinVerG.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  Retrieve more detailed information about Windows platform using GetVersion() function
  Copyright: CommonSoft Inc
  Darko Kolakovic  May 97
 */

#pragma warning(disable: 4201)  //warning: nonstandard extension used : nameless struct/union in WinNT.h
#include "KWinVers.h"   //constants
#pragma warning(default: 4201)

#include "KWinVerG.inl" //IsWinNT()
#ifndef _WINDOWS_
  #include <Windows.h>
#endif
#include <WinReg.h>

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
        strWinVersion = _TEXT("Unavailable");
        return FALSE;
      }
    return TRUE;
    }
 */
DWORD WINAPI GetWinVersion(int* piMajor, //resulting major version number
                           int* piMinor, //resulting minor version number
                           int* piBuild  //resulting build number
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
    Win2k     |    0       build number              5            minor
    WinNT     |    0       build number           3 or 4          minor
   Win95/98/Mi|    1       reserved                  4          0, 10 or 90
    Win32s    |    1       build number              3            minor
*/

if (IsWinNT(dwVersion)) //WinNT or Win2k
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
