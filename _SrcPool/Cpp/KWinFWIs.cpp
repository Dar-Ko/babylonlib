/*$Workfile: KWinFWIs.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  Inquire Windows platform version
  Copyright: CommonSoft Inc
  May 97 Darko Kolakovic
 */

#ifndef __AFX_H__
  #include <Afxwin.h> //TRACE0()
#endif

/*
#ifndef _WINDOWS_
 #include <Windows.h>
#endif
*/

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#undef WDJVER //Use 1st version D.K.

#ifndef WDJVER 
///////////////////////////////////////////////////////////////////////////////
//testing user.exe file version

  //Command to linker to search for Version.lib
#pragma comment( lib, "Version" )
#include <WinVer.h>     //GetFileVersionInfoSize()
#include "KFileHnd.inl" //IsFileInPath()

//IsWinForWgp()----------------------------------------------------------------
/*Check if Windows for Workgroups is running by examining the file version of 
  User.exe.

  Returns: TRUE if Windows for Workgroups ver. 3.11 is running.

  Note: Microsoft Windows specific (Win).
 */
BOOL IsWinForWgp()
{
  //Check if file ifshlp.sys exists and if the file version of user.exe is 3.11.
if(IsFileInPath((LPCSTR)"ifshlp.sys"))
  {
    //Note: size or content of requested file is not probed and this
    //function could be fooled with dummy file
    //Note: Win9x have file ifshlp.sys, but Win3.1 or win3.11 don't
    //      versions of user.exe  Platform  Directory
    //           3.10               Win3.1     WIN\
    //           3.11               Win3.11    WIN\
    //           3.11               WfW3.11    WIN\
    //           4.00               Win95   WIN\SYSTEM
    //           4.10               Win98   WIN\SYSTEM
    //           3.10              WinNT/2k WIN\SYSTEM32

  DWORD dwSize;
  DWORD dwhDummy;
  BYTE* lpData =NULL;   //Pointer to buffer to receive file-version info

    //Note: GetFileVersionInfoSize() works only with Win32 file images
  if((dwSize = ::GetFileVersionInfoSize(_T("user.exe"), &dwhDummy)) <= 0)
    {
    TRACE1(_T("GetFileVersionInfoSize() failed with error %d\n"),GetLastError());
    return FALSE;
    }
  lpData = new BYTE[dwSize];
  if (lpData == NULL)
    return FALSE;
  if (!::GetFileVersionInfo(_T("user.exe"), 0, dwSize, lpData))
    return FALSE;
    //Retrieve the version-information resource
  VS_FIXEDFILEINFO* pvffiData = NULL;
  if (!::VerQueryValue(lpData, _T("\\"), (LPVOID*)&pvffiData, (PUINT)&dwSize))
    return FALSE;
  if ((HIWORD(pvffiData->dwProductVersionMS) == 3) &&
      (LOWORD(pvffiData->dwProductVersionMS) == 11))
    {
    return TRUE;
    }

  delete []lpData;
  }
return FALSE;
}

///////////////////////////////////////////////////////////////////////////////

#else //WDJVER defined
///////////////////////////////////////////////////////////////////////////////
//testing a multinet driver (slower method)

//Constants are from <winnet.h> WfW SDK
//
//Note: Microsoft Windows specific (Win).
#define WNNC_NET_TYPE             0x0002
#define WNNC_SUBNET_WINWORKGROUP  0x0004
#define WNNC_NET_MultiNet         0x8000    //Network types

//IsWinForWgp()----------------------------------------------------------------
/*Check if Windows for Workgroups is running (16-bit application) by checking
  for a multinet driver

  History: Feb. 95 WDJ Paula Tomlinson.

  Note: Microsoft Windows specific (Win).
 */
BOOL IsWinForWgp()
{
typedef WORD (CALLBACK *LPFNWNETGETCAPS)(WORD);
BOOL bRes = FALSE;

HINSTANCE hLib = LoadLibrary(_T("user.exe"));
if((UINT)hLib <= (UINT)HINSTANCE_ERROR)
  {
  /*Note: Windows 9x: LoadLibrary fails 
          if you are using LoadLibrary to load a module that contains a 
          resource whose numeric identifier is greater than 0x7FFF, 
          if you are attempting to load a 16-bit DLL directly from 32-bit code,
          if you are attempting to load a DLL whose subsystem version is greater
          than 4.0,
          if your DllMain function tries to call the Unicode version of a Win32
          function. 
     user.exe is a 16-bit DLL.
   */
  return bRes;
  }
  //Search for multiple network support
LPFNWNETGETCAPS lpfnWNetGetCaps = (LPFNWNETGETCAPS)GetProcAddress(hLib,(LPCSTR)"WNetGetCaps");
if (lpfnWNetGetCaps != NULL)
  {
    //Call WNetGetCaps(WNNC_NET_TYPE)
  WORD wNetType = (*lpfnWNetGetCaps)( WNNC_NET_TYPE );
      //See if this computer includes multinet support
  if (wNetType & WNNC_NET_MultiNet)    
    if (LOBYTE(wNetType) & WNNC_SUBNET_WINWORKGROUP)
      bRes =  TRUE;
  }

if (hLib) 
  FreeLibrary(hLib); 
return bRes;
}


///////////////////////////////////////////////////////////////////////////////
#endif    //WDJVER
