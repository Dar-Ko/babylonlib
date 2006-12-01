/*$Workfile: KValidateRomVersion.c$: implementation file
  $Revision: 3$ $Date: 2004-11-12 14:57:59$
  $Author: Darko Kolakovic$

  Validates requirement for the operarting system version
  Copyright: CommonSoft Inc.
  2004-10-21 Darko Kolakovic
 */

/* Group=Palm */

#include <PalmOS.h>
#include "stdafx.h"

Err ValidateRomVersion(const UInt32 nRequiredVersion,
                       const UInt16 nLaunchFlags,
                       const UInt16 nAlertID
                       );

    /*Palm OS 2.0 version number */
#define VER_PALMOS_20   sysMakeROMVersion(2,0,0,sysROMStageDevelopment,0)

//-----------------------------------------------------------------------------
/*Compares actual Palm OS version with version required necessary to
  successfully run the application.

  Here is the operating system version format as a hexadecimal number:
        0xMMmfsbbb   where
                MM  is major version number,
               . m  is minor version number,
                 f  is bug fix version number
                 s  is release stage, wherein the value for s may be
                    one of the following:
                        0. Development
                        1. Alpha
                        2. Beta
                        3. Release,
               bbb  is build number for nonreleases,

        Palm OS System Version Numbers Table
      Number    Version   Device
    0x01003001   1.0      Pilot 1000, Pilot 5000
    0x02003000   2.0      PalmPilot Personal, PalmPilot Professional
    0x03003000   3.0      Palm III
    0x03103000   3.1      Palm IIIx, Palm IIIe, Palm V
    0x03203000   3.2      Palm VII
    0x03303000   3.3      Palm Vx; Palm III, Palm IIIx,
                          Palm V with software upgrade; Visor; original TRGPro
    0x03503000   3.5      Palm IIIxe, Palm IIIc; newer TRGPro
    0x03513000   3.5.1    Palm m100

  Note: nLaunchFlags are one of the parameters of application's PilotMain().

  Returns: error code sysErrRomIncompatible or errNone (0) if the actual ROM
  version is compatible with required minimum version.

  See also: sysFtrNumROMVersion in <SystemMgr.h>

  Note: Palm OS specific (PalmOS).
 */
Err ValidateRomVersion(const UInt32 nRequiredVersion,//[in] minimum ROM version
                                                     //required
                       const UInt16 nLaunchFlags,    //[in] flags that indicate
                                                     //if the application UI is
                                                     //initialized
                       const UInt16 nAlertID         //[in] resource ID for
                                                     //the error alert box or 0.
                      )
{
UInt32 nVersion;

/*Get current OS version number*/
FtrGet(sysFtrCreator, sysFtrNumROMVersion, &nVersion);
/*Check if minimum version is satisfied*/

if (nVersion < nRequiredVersion)
  {
  if( (nLaunchFlags &
      (sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp)) ==
      (sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp) )
    {
    if (nAlertID > 0)
      FrmAlert(nAlertID); //Display a warning.

    /*Palm OS versions before 2.0 will continuously relaunch this application
      unless we switch to another safe one.
     */
    if (nVersion < VER_PALMOS_20)
      {
        //Launch default application, exiting the current one
      AppLaunchWithCommand(sysFileCDefaultApp,
                           sysAppLaunchCmdNormalLaunch,
                           NULL
                           );
      }
  }

  return sysErrRomIncompatible;
  }

return errNone;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2004-10-28 13:07:43  Darko Kolakovic moved common
 *       elements to the SrcPool
 *  1    Biblioteka1.0         2004-10-26 14:49:55  Darko Kolakovic
 * $
 * 0 CodeWarrior 9 wizard-generated code is based on code adapted from the
 * stationery files distributed as part of the Palm OS SDK 4.0.
 *****************************************************************************/
