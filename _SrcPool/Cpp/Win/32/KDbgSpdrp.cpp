/*$RCSfile: KDbgSpdrp.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/07/09 22:15:44 $
  $Author: ddarko $

  Dumps the device registry property codes.

  Note: Microsoft Windows specific (Win32).

  Copyright: babylonlib.sourceforge.net
  2009-07-10 Darko Kolakovic
 */

// Group=Diagnostic

#include "stdafx.h"
#include <setupapi.h> //Device registry property codes

#if defined _ATL_VER
  #ifndef TRACE
    #include "KTraceAtl.h"
  #endif
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

//-----------------------------------------------------------------------------
/*Dumps the device registry property codes.

  The device registry property codes (SPDRP) are defined in SetupApi.h.
  These codes should cover the same set of registry properties as defined by
  the CM_DRP codes in CfgMgr32.h.

  Note: SPDRP codes are zero based while CM_DRP codes are one based.

  Note: Microsoft Windows specific (Win32);

  Returns: zero-terminated string describing device registry property code.

  See also: setupapi.h, cfgmgr32.h
 */
LPCTSTR DumpDevicePropertyCode(const DWORD dwProperty //[in] device registry property code
                              )
{

//Note: Codes marked as read-only (R) may only be used for SetupDiGetDeviceRegistryProperty

LPCTSTR szResult;
switch(dwProperty)
  {
  //Device registry property codes
  case SPDRP_DEVICEDESC                   : szResult = _T("SPDRP_DEVICEDESC")                 ; break; //00 DeviceDesc (R/W)
  case SPDRP_HARDWAREID                   : szResult = _T("SPDRP_HARDWAREID")                 ; break; //01 HardwareID (R/W)
  case SPDRP_COMPATIBLEIDS                : szResult = _T("SPDRP_COMPATIBLEIDS")              ; break; //02 CompatibleIDs (R/W)
  case SPDRP_UNUSED0                      : szResult = _T("SPDRP_UNUSED0")                    ; break; //03 unused
  case SPDRP_SERVICE                      : szResult = _T("SPDRP_SERVICE")                    ; break; //04 Service (R/W)
  case SPDRP_UNUSED1                      : szResult = _T("PDRP_UNUSED1")                     ; break; //05 unused
  case SPDRP_UNUSED2                      : szResult = _T("SPDRP_UNUSED2")                    ; break; //06 unused
  case SPDRP_CLASS                        : szResult = _T("SPDRP_CLASS")                      ; break; //07 Class (R--tied to ClassGUID)
  case SPDRP_CLASSGUID                    : szResult = _T("SPDRP_CLASSGUID")                  ; break; //08 ClassGUID (R/W)
  case SPDRP_DRIVER                       : szResult = _T("SPDRP_DRIVER")                     ; break; //09 Driver (R/W)
  case SPDRP_CONFIGFLAGS                  : szResult = _T("SPDRP_CONFIGFLAGS")                ; break; //0A ConfigFlags (R/W)
  case SPDRP_MFG                          : szResult = _T("SPDRP_MFG")                        ; break; //0B Mfg (R/W)
  case SPDRP_FRIENDLYNAME                 : szResult = _T("SPDRP_FRIENDLYNAME")               ; break; //0C FriendlyName (R/W)
  case SPDRP_LOCATION_INFORMATION         : szResult = _T("SPDRP_LOCATION_INFORMATION")       ; break; //0D LocationInformation (R/W)
  case SPDRP_PHYSICAL_DEVICE_OBJECT_NAME  : szResult = _T("SPDRP_PHYSICAL_DEVICE_OBJECT_NAME"); break; //0E PhysicalDeviceObjectName (R)
  case SPDRP_CAPABILITIES                 : szResult = _T("SPDRP_CAPABILITIES")               ; break; //0F Capabilities (R)
  case SPDRP_UI_NUMBER                    : szResult = _T("SPDRP_UI_NUMBER")                  ; break; //10 UiNumber (R)
  case SPDRP_UPPERFILTERS                 : szResult = _T("SPDRP_UPPERFILTERS")               ; break; //11 UpperFilters (R/W)
  case SPDRP_LOWERFILTERS                 : szResult = _T("SPDRP_LOWERFILTERS")               ; break; //12 LowerFilters (R/W)
  case SPDRP_BUSTYPEGUID                  : szResult = _T("SPDRP_BUSTYPEGUID")                ; break; //13 BusTypeGUID (R)
  case SPDRP_LEGACYBUSTYPE                : szResult = _T("SPDRP_LEGACYBUSTYPE")              ; break; //14 LegacyBusType (R)
  case SPDRP_BUSNUMBER                    : szResult = _T("SPDRP_BUSNUMBER")                  ; break; //15 BusNumber (R)
  case SPDRP_ENUMERATOR_NAME              : szResult = _T("SPDRP_ENUMERATOR_NAME")            ; break; //16 Enumerator Name (R)
  case SPDRP_SECURITY                     : szResult = _T("SPDRP_SECURITY")                   ; break; //17 Security (R/W, binary form)
  case SPDRP_SECURITY_SDS                 : szResult = _T("SPDRP_SECURITY_SDS")               ; break; //18 Security (W, SDS form)
  case SPDRP_DEVTYPE                      : szResult = _T("SPDRP_DEVTYPE")                    ; break; //19 Device Type (R/W)
  case SPDRP_EXCLUSIVE                    : szResult = _T("SPDRP_EXCLUSIVE")                  ; break; //1A Device is exclusive-access (R/W)
  case SPDRP_CHARACTERISTICS              : szResult = _T("SPDRP_CHARACTERISTICS")            ; break; //1B Device Characteristics (R/W)
  case SPDRP_ADDRESS                      : szResult = _T("SPDRP_ADDRESS")                    ; break; //1C Device Address (R)
  case SPDRP_UI_NUMBER_DESC_FORMAT        : szResult = _T("SPDRP_UI_NUMBER_DESC_FORMAT")      ; break; //1D UiNumberDescFormat (R/W)
  case SPDRP_DEVICE_POWER_DATA            : szResult = _T("SPDRP_DEVICE_POWER_DATA")          ; break; //1E Device Power Data (R)
  case SPDRP_REMOVAL_POLICY               : szResult = _T("SPDRP_REMOVAL_POLICY")             ; break; //1F Removal Policy (R)
  case SPDRP_REMOVAL_POLICY_HW_DEFAULT    : szResult = _T("SPDRP_REMOVAL_POLICY_HW_DEFAULT")  ; break; //20 Hardware Removal Policy (R)
  case SPDRP_REMOVAL_POLICY_OVERRIDE      : szResult = _T("SPDRP_REMOVAL_POLICY_OVERRIDE")    ; break; //21 Removal Policy Override (RW)
  case SPDRP_INSTALL_STATE                : szResult = _T("SPDRP_INSTALL_STATE")              ; break; //22 Device Install State (R)
  case SPDRP_LOCATION_PATHS               : szResult = _T("SPDRP_LOCATION_PATHS")             ; break; //23 Device Location Paths (R)
  case SPDRP_MAXIMUM_PROPERTY             : szResult = _T("SPDRP_MAXIMUM_PROPERTY")           ; break; //24 Upper bound on ordinals
  default:
    {
    TRACE1(_T("  Registry property code (%u) "), dwProperty);
    szResult = _T("Unknown registry property code");
    }
  }
return szResult;
}

///////////////////////////////////////////////////////////////////////////////
#endif //_DEBUG

/******************************************************************************
 * $Log: KDbgSpdrp.cpp,v $
 * Revision 1.2  2009/07/09 22:15:44  ddarko
 * GetDeviceDescription()
 *
 * Revision 1.1  2009/07/09 18:12:25  ddarko
 * Created
 *
 ******************************************************************************/
