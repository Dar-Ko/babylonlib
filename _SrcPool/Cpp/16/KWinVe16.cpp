/*$Workfile: H:\_SrcPool\Cpp\16\KWinVe16.cpp$: implementation file
  $Revision: 4$ $Date: 3/8/02 1:49:28 AM$
  $Author: Darko Kolakovic$

  Retrieve more detailed information about Windows platform
  Copyright: CommonSoft Inc
  May 94 Darko Kolakovic
*/
#ifndef _WIN32  //~Win32 16-bit platform
#ifndef _WINDOWS_
  #include <Windows.h>
#endif

#include "KWinVers.h"

//GetWinVersion()--------------------------------------------------------------
/*Returns the code specifying the operating system platform and current major 
  and minor version numbers of Windows.

  Note: Microsoft Windows 16b specific (Win16). 
 */
DWORD WINAPI GetWinVersion(int* piMajor, //resulting major version number
                           int* piMinor  //resulting minor version number
                           )
{
  //Check if the WOW (16-bit) layer of NT/NTAS is running now
  if (GetWinFlags() & 0x4000) 
    dwEnviron = ENV_WINNT; //WinNT or WinNT Advanced Server
  else //Win 3.x or Win95
    {
      //Check major version number to distinguish
      //Win 3.x from Win95
    if ((LOBYTE(LOWORD(dwVersion)) > 3) ||
        (HIBYTE(LOWORD(dwVersion)) > 50))
      dwEnviron = ENV_WIN95;
    else  //Win 3.x or WFW
      {
       //Determine if Win 3.x or WFW
      if (IsWinForWgp())
        dwEnviron = ENV_WFW;
      else 
        dwEnviron = ENV_WIN3X;
      }
    }

*pMajor = LOBYTE(LOWORD(dwVersion));
*pMinor = HIBYTE(LOWORD(dwVersion));   

return dwEnviron;

}

///////////////////////////////////////////////////////////////////////////////
#endif  //~_WIN32
