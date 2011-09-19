//////////////////////////////////////////////////////////////////////////////
//
//                     (C) Philips Semiconductors 2001
//  All rights are reserved. Reproduction in whole or in part is prohibited
//  without the written consent of the copyright owner.
//
//  Philips reserves the right to make changes without notice at any time.
//  Philips makes no warranty, expressed, implied or statutory, including but
//  not limited to any implied warranty of merchantability or fitness for any
//  particular purpose, or that the use will not infringe any third party
//  patent, copyright or trademark. Philips must not be liable for any loss
//  or damage arising from its use.
//
//////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include "KCoInstaller.h"
#include <stdio.h>

//+---------------------------------------------------------------------------
//
// A Coinstaller must not generate any popup to the user,
// so we generate OutputDebugStrings in case of an error.
//
#if _DEBUG
#define TRACE(Text) OutputDebugString(TEXT("CoInstaller: ") Text TEXT("\n"))
#else
#define TRACE(Text) 
#endif 

//////////////////////////////////////////////////////////////////////////////
//
// Description:         
//  type here function description
//
// Return Value:         
//  type here return value description or remove these lines
//
//////////////////////////////////////////////////////////////////////////////
//+---------------------------------------------------------------------------
//
//  Function:   CoInstallerEntry 
//
//  Purpose:    Responds to co-installer messages for the Europa driver
//
//  Arguments:
//      InstallFunction   [in] 
//      DeviceInfoSet     [in]
//      DeviceInfoData    [in]
//      Context           [inout]
//
//  Returns:    NO_ERROR, ERROR_DI_POSTPROCESSING_REQUIRED, or an error code.
/*Co-installer Interface
A co-installer's interface consists of an exported entry point function and an associated data structure.

Co-installer Entry Point
A co-installer must export an entry point function that has the following prototype:

typedef DWORD 
  (CALLBACK* COINSTALLER_PROC) (
    IN DI_FUNCTION  InstallFunction,
    IN HDEVINFO  DeviceInfoSet,
    IN PSP_DEVINFO_DATA  DeviceInfoData  OPTIONAL,
    IN OUT PCOINSTALLER_CONTEXT_DATA  Context
    );


InstallFunction 
Specifies the device installation request being processed, in which the co-installer has the option of participating. These requests are specified using DIF codes, such as DIF_INSTALLDEVICE. For more information, see Device Installation Function Codes. 
DeviceInfoSet 
Supplies a handle to a device information set. 
DeviceInfoData 
Optionally identifies a device that is the target of the device installation request. If this parameter is non-NULL, it identifies a device information element in the device information set. DeviceInfoData is non-NULL when SetupDiCallClassInstaller calls a device-specific co-installer. A class-specific co-installer can be called with a DIF request that has a NULL DeviceInfoData, such as DIF_DETECT or DIF_FIRSTTIMESETUP. 
Context 
Points to a COINSTALLER_CONTEXT_DATA structure, described below. 
A device co-installer returns one of the following values:

NO_ERROR 
The co-installer performed the appropriate actions for the specified InstallFunction, or the co-installer determined that it didn't need to perform any actions for the request. 
The co-installer must also return NO_ERROR if it receives an unrecognized DIF code. (Note that class installers return ERROR_DI_DO_DEFAULT for unrecognized DIF codes, as described in Class Installer Interface.)

ERROR_DI_POSTPROCESSING_REQUIRED 
The co-installer performed any appropriate actions for the specified InstallFunction and is requesting to be called again after the Class Installer has processed the request. 
A Win32 error 
The co-installer encountered an error. 

A co-installer does not set a return status of ERROR_DI_DO_DEFAULT. This status can be used only by a Class Installer. If a co-installer returns this status, SetupDiCallClassInstaller will not process the DIF_Xxx request properly. A co-installer might propagate a return status of ERROR_DI_DO_DEFAULT in its postprocessing pass, but it never sets this value.

COINSTALLER_CONTEXT_DATA
COINSTALLER_CONTEXT_DATA is a co-installer-specific context structure describing an installation request. The format of the structure is:

    typedef struct 
    _COINSTALLER_CONTEXT_DATA {
        BOOLEAN  PostProcessing;
        DWORD  InstallResult;
        PVOID  PrivateData;
    } COINSTALLER_CONTEXT_DATA, *PCOINSTALLER_CONTEXT_DATA;


PostProcessing is TRUE when a co-installer is called after the appropriate class installer, if any, has processed the DIF code specified by InstallFunction. PostProcessing is read-only to the co-installer.

If PostProcessing is FALSE, InstallResult is not relevant. If PostProcessing is TRUE, InstallResult is the current status of the install request. This value is NO_ERROR or an error status returned by the previous component called for this install request. A co-installer can propagate the status by returning this value for its function return, or it can return another status. InstallResult is read-only to the co-installer.

PrivateData points to a co-installer-allocated buffer. If a co-installer sets this pointer and requests postprocessing, SetupDiCallClassInstaller passes the pointer to the co-installer when it calls the co-installer for postprocessing

*/
/*
returns one of the following values:

NO_ERROR 
The co-installer performed the appropriate actions for the specified InstallFunction, or the co-installer determined that it didn't need to perform any actions for the request. 
The co-installer must also return NO_ERROR if it receives an unrecognized DIF code. (Note that class installers return ERROR_DI_DO_DEFAULT for unrecognized DIF codes, as described in Class Installer Interface.)

ERROR_DI_POSTPROCESSING_REQUIRED 
The co-installer performed any appropriate actions for the specified InstallFunction and is requesting to be called again after the Class Installer has processed the request. 
A Win32 error 
The co-installer encountered an error.
 */
//
extern "C"
 DWORD CALLBACK CoInstallerEntryPoint
 (
DI_FUNCTION               InstallFunction,
HDEVINFO                  DeviceInfoSet,
PSP_DEVINFO_DATA          DeviceInfoData,
PCOINSTALLER_CONTEXT_DATA Context
 )
{
    HMODULE hD3D9Dll = NULL;
    switch (InstallFunction)
    {
    case DIF_INSTALLDEVICE: 
        TRACE(TEXT("DIF_INSTALLDEVICE"));
/*
        // check if DX 9 or higher is available
        hD3D9Dll = LoadLibrary(TEXT("D3D9.dll"));
        if( hD3D9Dll == NULL)
        {
            TRACE(TEXT("Error: DX9 or higher not found"));
            return ERROR_BAD_ENVIRONMENT;
        }
        else
        {
            FreeLibrary(hD3D9Dll);
        }
        */
        break;
    case DIF_REMOVE:
        TRACE(TEXT("DIF_REMOVE"));
        break;
    case DIF_SELECTDEVICE:
        TRACE(TEXT("DIF_SELECTDEVICE"));
        break;
    case DIF_ASSIGNRESOURCES:
        TRACE(TEXT("DIF_ASSIGNRESOURCES"));
        break;
    case DIF_PROPERTIES:
        TRACE(TEXT("DIF_PROPERTIES"));
        break;
    case DIF_FIRSTTIMESETUP:
        TRACE(TEXT("DIF_FIRSTTIMESETUP"));
        break;
    case DIF_FOUNDDEVICE:
        TRACE(TEXT("DIF_FOUNDDEVICE"));
        break;
    case DIF_SELECTCLASSDRIVERS:
        TRACE(TEXT("DIF_SELECTCLASSDRIVERS"));
        break;
    case DIF_VALIDATECLASSDRIVERS:
        TRACE(TEXT("DIF_VALIDATECLASSDRIVERS"));
        break;
    case DIF_INSTALLCLASSDRIVERS:
        TRACE(TEXT("DIF_INSTALLCLASSDRIVERS"));
        break;
    case DIF_CALCDISKSPACE:
        TRACE(TEXT("DIF_CALCDISKSPACE"));
        break;
    case DIF_DESTROYPRIVATEDATA:
        TRACE(TEXT("DIF_DESTROYPRIVATEDATA"));
        break;
    case DIF_VALIDATEDRIVER:
        TRACE(TEXT("DIF_VALIDATEDRIVER"));
        break;
    case DIF_MOVEDEVICE:
        TRACE(TEXT("DIF_MOVEDEVICE"));
        break;
    case DIF_DETECT:
        TRACE(TEXT("DIF_DETECT"));
        break;
    case DIF_INSTALLWIZARD:
        TRACE(TEXT("DIF_INSTALLWIZARD"));
        break;
    case DIF_DESTROYWIZARDDATA:
        TRACE(TEXT("DIF_DESTROYWIZARDDATA"));
        break;
    case DIF_PROPERTYCHANGE:
        TRACE(TEXT("DIF_PROPERTYCHANGE"));
        break;
    case DIF_ENABLECLASS:
        TRACE(TEXT("DIF_ENABLECLASS"));
        break;
    case DIF_DETECTVERIFY:
        TRACE(TEXT("DIF_DETECTVERIFY"));
        break;
    case DIF_INSTALLDEVICEFILES:
        TRACE(TEXT("DIF_INSTALLDEVICEFILES"));
        break;
    case DIF_ALLOW_INSTALL:
        TRACE(TEXT("DIF_ALLOW_INSTALL"));
        break;
    case DIF_SELECTBESTCOMPATDRV:
        TRACE(TEXT("DIF_SELECTBESTCOMPATDRV"));
        break;
    case DIF_REGISTERDEVICE:
        TRACE(TEXT("DIF_REGISTERDEVICE"));
        break;
    case DIF_NEWDEVICEWIZARD_PRESELECT:
        TRACE(TEXT("DIF_NEWDEVICEWIZARD_PRESELECT"));
        break;
    case DIF_NEWDEVICEWIZARD_SELECT:
        TRACE(TEXT("DIF_NEWDEVICEWIZARD_SELECT"));
        break;
    case DIF_NEWDEVICEWIZARD_PREANALYZE:
        TRACE(TEXT("DIF_NEWDEVICEWIZARD_PREANALYZE"));
        break;
    case DIF_NEWDEVICEWIZARD_POSTANALYZE:
        TRACE(TEXT("DIF_NEWDEVICEWIZARD_POSTANALYZE"));
        break;
    case DIF_NEWDEVICEWIZARD_FINISHINSTALL:
        TRACE(TEXT("DIF_NEWDEVICEWIZARD_FINISHINSTALL"));
        break;
    case DIF_INSTALLINTERFACES:
        TRACE(TEXT("DIF_INSTALLINTERFACES"));
        break;
    case DIF_DETECTCANCEL:
        TRACE(TEXT("DIF_DETECTCANCEL"));
        break;
    case DIF_REGISTER_COINSTALLERS:
        TRACE(TEXT("DIF_REGISTER_COINSTALLERS"));
        break;
    case DIF_ADDPROPERTYPAGE_ADVANCED:
        TRACE(TEXT("DIF_ADDPROPERTYPAGE_ADVANCED"));
        break;
    case DIF_ADDPROPERTYPAGE_BASIC:
        TRACE(TEXT("DIF_ADDPROPERTYPAGE_BASIC"));
        break;
    case DIF_TROUBLESHOOTER:
        TRACE(TEXT("DIF_TROUBLESHOOTER"));
        break;
    case DIF_POWERMESSAGEWAKE:
        TRACE(TEXT("DIF_POWERMESSAGEWAKE"));
        break;
    default:
        TRACE(TEXT("?????"));
        break;
    }
    return NO_ERROR;    
}

