/*$RCSfile: EnumComDrivers.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2013/08/27 17:19:14 $
  $Author: ddarko $; PJ Naughter
  Enumerate the serial ports installed on a PC
*/

#include "stdafx.h"
#if (defined _WIN32_WCE)

//-----------------------------------------------------------------------------
/*Enumerate the serial ports installed on a PC as reported by Device Manager
 */
bool EnumerateRunningDrivers(CSimpleArray<UINT>& ports, CSimpleArray<CString>& friendlyNames)
{
#if _WIN32_WCE > 4
  HANDLE hDriver;
    //Make sure we clear out any elements which may already be in the array(s)
  ports.RemoveAll();
  friendlyNames.RemoveAll();

  DeviceSearchType DeviceSearch = DeviceSearchByLegacyName;
  DEVMGR_DEVICE_INFORMATION DeviceInfo;

  DeviceInfo.dwSize = sizeof( DEVMGR_DEVICE_INFORMATION );

  hDriver = FindFirstDevice(DeviceSearch, L"COM*", &DeviceInfo);

  if( hDriver != INVALID_HANDLE_VALUE )
  {
    do
    {
      RETAILMSG(TRUE, (TEXT("%s %s %s %s\n"),
                        DeviceInfo.szLegacyName,
                        DeviceInfo.szDeviceKey,
                        DeviceInfo.szDeviceName,
                        DeviceInfo.szBusName ));
      int nPort = _ttoi(&DeviceInfo.szLegacyName[3]);
      ports.Add(nPort);

      HKEY hDeviceKey;
      LONG lRes = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                               DeviceInfo.szDeviceKey,
                               0,
                               KEY_READ,
                               &hDeviceKey);

      if(lRes == ERROR_SUCCESS)
      {
        LPCTSTR pszValueName =  _T("FriendlyName");
        DWORD dwSize = 0;
        DWORD dwType = 0;
        lRes = RegQueryValueEx(hDeviceKey,
                               pszValueName,
                               NULL,
                               &dwType,
                               NULL,
                               &dwSize);

        if(lRes == ERROR_SUCCESS)
        {
          ATLASSERT(dwType == REG_SZ);
          LPTSTR pszValue = new TCHAR[dwSize / sizeof(TCHAR)];
          if(pszValue != NULL)
          {
            lRes = RegQueryValueEx(hDeviceKey,
                                   pszValueName,
                                   NULL,
                                   &dwType,
                                   (BYTE*)pszValue,
                                   &dwSize);

            if(lRes == ERROR_SUCCESS)
              friendlyNames.Add(pszValue);

            delete [] pszValue;
          }
          else
            lRes = ERROR_NOT_ENOUGH_MEMORY;
        }
        RegCloseKey(hDeviceKey);
      }

      if(lRes != ERROR_SUCCESS)
        friendlyNames.Add(DeviceInfo.szBusName);

    } while( FindNextDevice( hDriver, &DeviceInfo ) );
    FindClose( hDriver );
    return true;
  }

#else
  RETAILMSG( 1, (TEXT("Cannot find drivers Windows CE Version doesn't support function\n")));
#endif
return false;
}

///////////////////////////////////////////////////////////////////////////////
#endif
