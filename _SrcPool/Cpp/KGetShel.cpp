/*$Workfile: KGetShel.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  Get version of Shell or Common Controls DLL
  Copyright: CommonSoft Inc.
  MSDN Q4 99 original version
  Apr 2000 Darko Kolakovic
 */ 

#ifdef _INCLUDE_KGETSHEL_CPP_
  #include "ShlWApi.h"
  #define _DECLSTAT static

#else //~_INCLUDE_KGETSHEL_CPP_
  #define _DECLSTAT
  #include "Windows.h"
  #include "ShlWApi.h"

  #ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
  #endif

#endif //_INCLUDE_KGETSHEL_CPP_

//GetShellVersion()------------------------------------------------------------
/*Returns: major and minor version number for the the Shell and Common Controls
  DLLs. In case of failure, function returns zero.

  Starting with version 4.71, the Shell and Common Controls DLLs, among others,
  began exporting DllGetVersion(). This function can be called by an application
  to determine which DLL version is present on the system. DllGetVersion()
  returns a structure  that contains version information.

      Version      DLL       Distribution Platform
        4.00       All           Win95/WinNT 4.0.
        4.70       All           IE 3.x.
        4.71       All           IE 4.0
        4.72       All           IE 4.01 and Win98
        5.00    Shlwapi.dll      IE 5
        5.00    Shell32.dll      Win2k
        5.80    Comctl32.dll     IE 5
        5.81    Comctl32.dll     Win2k



  Note: Under Win2k, DllGetVersion returns DLLVERSIONINFO2, for earlier systems
        DllGetVersion returns DLLVERSIONINFO;

  Note: Microsoft Windows specific (Win).

  Example:
      {
      ...
      if(GetShellVersion(_T("comctl32.dll")) >= MAKELONG(4,71))
        {
        //TODO: some action
        }
      else
        {
        //Use an alternate approach for older DLL versions
          ...
        }

  History: MSDN 4Q 99
 */
_DECLSTAT DWORD GetShellVersion(LPCTSTR lpszDllName //name of the Shell or Common Controls DLL
                     )
{

HINSTANCE hinstDll;
DWORD dwVersion = 0;

hinstDll = LoadLibrary(lpszDllName);

if(hinstDll)
  {
  DLLGETVERSIONPROC pDllGetVersion;
  pDllGetVersion = (DLLGETVERSIONPROC) GetProcAddress(hinstDll, "DllGetVersion");

  /*Because some DLLs may not implement this function, you must test for it
    explicitly. Depending on the particular DLL, the lack of a DllGetVersion
    function may be a useful indicator of the version.
   */
  if(pDllGetVersion)
    {
    DLLVERSIONINFO dvi;
    HRESULT hr;

    ZeroMemory(&dvi, sizeof(dvi));
    dvi.cbSize = sizeof(dvi);
    hr = (*pDllGetVersion)(&dvi);

    if(SUCCEEDED(hr))
      dwVersion = MAKELONG(dvi.dwMajorVersion, dvi.dwMinorVersion);
    }

  FreeLibrary(hinstDll);
  }
return dwVersion;
}

/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         18/07/2001 11:32:52 PMDarko           VSS tags
 *  3    Biblioteka1.2         11/07/2001 10:51:43 PMDarko
 *  2    Biblioteka1.1         08/06/2001 11:50:52 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:56:36 PMDarko
 * $
 *****************************************************************************/
