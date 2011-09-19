/*$RCSfile: KUpdatePnPDrv.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2011/09/19 22:42:27 $
  Device Console
  command-line interface for managing devices
  $Author: ddarko $
  Copyright (c) Microsoft Corporation.  All rights reserved.
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include <windows.h>

#ifdef _USE_SETUPAPI
  #include <setupapi.h>
  #pragma comment(lib, "setupapi") //Setup application programming interface 
#endif

#include <api/newdev.h>  /*WDK 6000: Driver Installation header
         Available in Microsoft Windows 2000 and later versions of Windows.*/

#if _WIN32_WINNT >= 0x500 //requires Microsoft Windows 2000 and later (Win2k)
  #pragma comment(lib, "newdev")   //Windows Driver Kit
#else
  #include "KDll.h" //CDll class
  #ifndef UPDATEDRIVERFORPLUGANDPLAYDEVICES
    #ifdef _UNICODE
      #define UPDATEDRIVERFORPLUGANDPLAYDEVICES "UpdateDriverForPlugAndPlayDevicesW"
    #else
      #define UPDATEDRIVERFORPLUGANDPLAYDEVICES "UpdateDriverForPlugAndPlayDevicesA"
    #endif
  #endif //UPDATEDRIVERFORPLUGANDPLAYDEVICES

  typedef BOOL (WINAPI *PFUPDATEDRIVERFORPLUGANDPLAYDEVICES)(__in HWND hwndParent,
                                                            __in LPCTSTR HardwareId,
                                                            __in LPCTSTR FullInfPath,
                                                            __in DWORD InstallFlags,
                                                            __out_opt PBOOL bRebootRequired
                                                           );
#endif

bool UpdatePnpDrv(LPCTSTR szHardwareId, LPCTSTR szFullInfPath,
                  const DWORD InstallFlags = INSTALLFLAG_FORCE,
                  bool*   pbRebootRequired = NULL);

//-----------------------------------------------------------------------------
/*Updates the drivers for devices with specified hardware identifier. If there
  are no such devices connected to the computer, the INF file will be copyied
  to the system, making it ready for automatic installation when the device is 
  connectected.
  A hardware identifier is the device identification string used by setup to 
  locate the information (INF) file that best matches the device.

  The maximum length of a NULL-terminated hardware identifier is MAX_DEVICE_ID_LEN.

  Returns true if successful, othewise returnrs false. To get extended error 
  information, call GetLastError().

  Note: requires Microsoft Windows Me, Windows 2000 and later (Win2k) 

  See also: Windows Driver Kit: Device Installation - Device Identification Strings
 */
bool UpdatePnpDrv(LPCTSTR szHardwareId,  //[in] hardware identifier of the device
                  LPCTSTR szFullInfPath, //[in] full path to an INF file and any 
                    //associated driver files. This path should not exceed MAX_PATH
                    //in size, including the terminating NULL.
                  const DWORD InstallFlags, //[in]=INSTALLFLAG_FORCE  one more of
                          //following flags:
                          // - INSTALLFLAG_NONINTERACTIVE signal failure if
                          //   any attempt to display UI is detected
                          // - INSTALLFLAG_READONLY  do not atempt to change any 
                          //   of installation files
                          // - INSTALLFLAG_FORCE  installs new drivers if device is
                          //   connected
                  bool*   pbRebootRequired //[out]=NULL optional return value
                    //indicating whether a reboot is required
                 )
{
TRACE2(TEXT("UpdatePnpDrv(%s, %s)\n"), szHardwareId, szFullInfPath);
bool bResult = false;
const HWND hwndParent = NULL;   //handle to the top-level window to use
                                //for any UI related to installing devices

BOOL bReboot   = FALSE;   //optional return value indicating whether
                          //a reboot is required 

#ifdef UPDATEDRIVERFORPLUGANDPLAYDEVICES  //explicitly link to the DLL
  //Validate function support
  PFUPDATEDRIVERFORPLUGANDPLAYDEVICES pfUpdatePnPDev;
  CDll dllNewDev(TEXT("newdev.dll"));
  if(dllNewDev.IsOpen())
    {
    pfUpdatePnPDev = (PFUPDATEDRIVERFORPLUGANDPLAYDEVICES)GetProcAddress(
                              dllNewDev, UPDATEDRIVERFORPLUGANDPLAYDEVICES);
    if (pfUpdatePnPDev == NULL)
      {
      TRACE1(TEXT("  Failure to obtain DLL's exported function %S!\n"), 
             UPDATEDRIVERFORPLUGANDPLAYDEVICES);
      return false; //Function is not supported in the version of DLL
      }
    }
   PFUPDATEDRIVERFORPLUGANDPLAYDEVICES& UpdatePnPDev = pfUpdatePnPDev;
#else //DLL linked implicitly
   PFUPDATEDRIVERFORPLUGANDPLAYDEVICES& UpdatePnPDev = UpdateDriverForPlugAndPlayDevices;
#endif

/*Given an INF file and a hardware ID, the UpdateDriverForPlugAndPlayDevices
  function installs updated drivers for devices that match the hardware ID.
 */
bResult = (UpdatePnPDev(  hwndParent,
                          szHardwareId,
                          szFullInfPath,
                          InstallFlags,
                          &bReboot
                         ) == TRUE);
if(!bResult)
  {
  DWORD dwError = GetLastError();
  switch (dwError)
    {
    case ERROR_NO_SUCH_DEVINST: //0xE000020B
      {
      //No device with the device ID as specified in the INF is accessible
      //and files didn't get automatically installed.
      TRACE(TEXT("  ERROR_NO_SUCH_DEVINST\n"));

      /*Enforce copying the INF, so when the device get plugged in, installation could
        proceed.
       */

      PCTSTR OEMSourceMediaLocation = NULL; //Source location information to
            //be stored in the precompiled INF (.pnf). This location information is specific
            //to the source media type specified.
      const DWORD OEMSourceMediaType = SPOST_NONE; //source media type referenced by the location
            //information.
      const DWORD CopyStyle = SP_COPY_NEWER_OR_SAME;   //specifies how the INF file is 
            //copied into the INF directory.
      #ifdef _DEBUG
        TCHAR DestinationInfFileName[MAX_PATH];
        DWORD DestinationInfFileNameSize = _countof(DestinationInfFileName);
        DWORD dwRequiredSize = 0xDEADBEEF;
        PDWORD RequiredSize = &dwRequiredSize;
        PTSTR  pDestinationInfFileNameComponent = NULL;
        PTSTR* DestinationInfFileNameComponent = &pDestinationInfFileNameComponent;
      #else
        const PTSTR  DestinationInfFileName = NULL;
        const DWORD  DestinationInfFileNameSize = 0;
        const PDWORD RequiredSize = NULL;
        PTSTR* const  DestinationInfFileNameComponent = NULL;
      #endif

      /*SetupCopyOEMInf() copies a specified INF file to the %windir%/Inf directory.
        The SetupCopyOEMInf function copies a specified INF file into the %windir%\Inf directory.
        SetupCopyOEMInf does not recopy the file if it finds that a binary image of the specified
        INF file already exists in the INF directory with the same name or a name of the form 
        OEM*.INF. When SetupCopyOEMInf copies a file, it renames the copied file to OEM*.INF.
        Name provided is unique and cannot be predicted.
       */
      bResult = (SetupCopyOEMInf( szFullInfPath,
                                  OEMSourceMediaLocation,
                                  OEMSourceMediaType,
                                  CopyStyle,
                                  DestinationInfFileName,
                                  DestinationInfFileNameSize,
                                  RequiredSize,
                                  DestinationInfFileNameComponent
                                 ) == TRUE);
      #ifdef _DEBUG
        if (!bResult)
          {
          dwError = GetLastError();
          TRACE1(TEXT("  SetupCopyOEMInf()\n"), dwError);
          switch (dwError)
            {
            case ERROR_FILE_NOT_FOUND:
              {
              TRACE(TEXT("    (2) ERROR_FILE_NOT_FOUND\n"));
              break;
              }
            case ERROR_FILE_EXISTS:
              {
              TRACE(TEXT("    ERROR_FILE_EXISTS\n"));
              break;
              }
            default:
              TRACE1(TEXT("    ERROR: 0x%X.\n"), dwError);
            }
          }
        else
          TRACE1(TEXT("  SetupCopyOEMInf() to %s.\n"), DestinationInfFileName);
        #endif

      /*Note: (Ref.: WDK Sample) There may exist, however, devices that were 
        once connected to the computer, but presently are not.If it is required
        for such devices to be re-installed, retrieve the list of non-present
        devices and tagg them for re-installation. This will invoke
        the "New Hardware Found" process again.
       */
      break;
      }

    case ERROR_NO_MORE_ITEMS:
      {
      //All devices found already have a better driver than what is contained
      //in the specified INF file.
      TRACE(TEXT("  ERROR_NO_MORE_ITEMS\n"));
      bResult = true;
      break;
      }
    case ERROR_FILE_NOT_FOUND:
      {
      //The path specified for INF does not exist.
      TRACE(TEXT("  ERROR_FILE_NOT_FOUND\n"));
      break;
      }
    case ERROR_IN_WOW64:
      {
      //32-bit application attempting to execute in a 64-bit environment.
      TRACE(TEXT("  ERROR_IN_WOW64\n"));
      break;
      }
    case ERROR_INVALID_FLAGS:
      {
      //The value specified for InstallFlags is invalid.
      TRACE(TEXT("  ERROR_INVALID_FLAGS\n"));
      break;
      }
    case ERROR_CANCELLED: //0x000004C7
      {
      //The operation was canceled by the user.
      TRACE(TEXT("  ERROR_CANCELLED\n"));
      break;
      }
   case TRUST_E_NOSIGNATURE:
      {
      //No signature was present in the subject.
      TRACE(TEXT("  TRUST_E_NOSIGNATURE\n"));
      break;
      }

    default:
      //An error occurred while installing driver package.
      TRACE1(TEXT("  ERROR: 0x%X.\n"), dwError);
    }
 
  }

if(pbRebootRequired != NULL)
  *pbRebootRequired = (bReboot == TRUE);
return bResult;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KUpdatePnPDrv.cpp,v $
 * Revision 1.3  2011/09/19 22:42:27  ddarko
 * Debug trace
 *
 * Revision 1.2  2011/08/18 21:32:06  ddarko
 * link with setupapi.lib
 *
 * Revision 1.1  2011/08/18 21:27:15  ddarko
 * Created from several WDK examples
 *
 *****************************************************************************/
