/*$Workfile: KDbgConfigRet.cpp$: implementation file
  $Revision: 2$ $Date: 2007-08-24 18:15:41$
  $Author: Darko Kolakovic$

  Dumps the PnP Configuration Manager return status codes
  Copyright: CommonSoft Inc.
  2007-08-01 Darko Kolakovic
 */

// Group=Diagnostic

#ifdef _USE_ATL
  //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option) 
  //or preprocessor reports unpaired #endif directive

  #include "stdafx.h" //Standard system header files
#endif

#if defined _ATL_VER 
  #ifndef TRACE
    #define TRACE ATLTRACE
    #define TRACE1 ATLTRACE
  #endif
#else
  #include <windows.h>
#endif
#include <cfgmgr32.h> //PnP Configuration Manager Functions, Windows Platform DDK

#ifndef _T
  #include <tchar.h>
#endif

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/*Dumps the PnP Configuration Manager return status codes.

  Returns: zero-terminated string representing return status code.

  See also: cfgmgr32.h
 */
LPCTSTR DumpConfigRet(const CONFIGRET crCode //[in] Configuration Manager 
                                             //return status code
                     )
{
LPTSTR szRes;
switch(crCode)
  {
  case CR_SUCCESS                  : szRes = _T("CR_SUCCESS")                  ; break;  //0x00
  case CR_DEFAULT                  : szRes = _T("CR_DEFAULT")                  ; break;  //0x01
  case CR_OUT_OF_MEMORY            : szRes = _T("CR_OUT_OF_MEMORY")            ; break;  //0x02
  case CR_INVALID_POINTER          : szRes = _T("CR_INVALID_POINTER")          ; break;  //0x03
  case CR_INVALID_FLAG             : szRes = _T("CR_INVALID_FLAG")             ; break;  //0x04
  case CR_INVALID_DEVNODE          : szRes = _T("CR_INVALID_DEVNODE")          ; break;  //0x05 CR_INVALID_DEVINST == CR_INVALID_DEVNODE
  case CR_INVALID_RES_DES          : szRes = _T("CR_INVALID_RES_DES")          ; break;  //0x06
  case CR_INVALID_LOG_CONF         : szRes = _T("CR_INVALID_LOG_CONF")         ; break;  //0x07
  case CR_INVALID_ARBITRATOR       : szRes = _T("CR_INVALID_ARBITRATOR")       ; break;  //0x08
  case CR_INVALID_NODELIST         : szRes = _T("CR_INVALID_NODELIST")         ; break;  //0x09
  case CR_DEVNODE_HAS_REQS         : szRes = _T("CR_DEVNODE_HAS_REQS")         ; break;  //0x0A CR_DEVINST_HAS_REQS == CR_DEVNODE_HAS_REQS
  case CR_INVALID_RESOURCEID       : szRes = _T("CR_INVALID_RESOURCEID")       ; break;  //0x0B
  case CR_DLVXD_NOT_FOUND          : szRes = _T("CR_DLVXD_NOT_FOUND")          ; break;  //0x0C WIN 95 ONLY
  case CR_NO_SUCH_DEVNODE          : szRes = _T("CR_NO_SUCH_DEVNODE")          ; break;  //0x0D CR_NO_SUCH_DEVINST == CR_NO_SUCH_DEVNODE
  case CR_NO_MORE_LOG_CONF         : szRes = _T("CR_NO_MORE_LOG_CONF")         ; break;  //0x0E
  case CR_NO_MORE_RES_DES          : szRes = _T("CR_NO_MORE_RES_DES")          ; break;  //0x0F
  case CR_ALREADY_SUCH_DEVNODE     : szRes = _T("CR_ALREADY_SUCH_DEVNODE")     ; break;  //0x10 CR_ALREADY_SUCH_DEVINST == CR_ALREADY_SUCH_DEVNODE
  case CR_INVALID_RANGE_LIST       : szRes = _T("CR_INVALID_RANGE_LIST")       ; break;  //0x11
  case CR_INVALID_RANGE            : szRes = _T("CR_INVALID_RANGE")            ; break;  //0x12
  case CR_FAILURE                  : szRes = _T("CR_FAILURE")                  ; break;  //0x13
  case CR_NO_SUCH_LOGICAL_DEV      : szRes = _T("CR_NO_SUCH_LOGICAL_DEV")      ; break;  //0x14
  case CR_CREATE_BLOCKED           : szRes = _T("CR_CREATE_BLOCKED")           ; break;  //0x15
  case CR_NOT_SYSTEM_VM            : szRes = _T("CR_NOT_SYSTEM_VM")            ; break;  //0x16 Win95 ONLY
  case CR_REMOVE_VETOED            : szRes = _T("CR_REMOVE_VETOED")            ; break;  //0x17
  case CR_APM_VETOED               : szRes = _T("CR_APM_VETOED")               ; break;  //0x18
  case CR_INVALID_LOAD_TYPE        : szRes = _T("CR_INVALID_LOAD_TYPE")        ; break;  //0x19
  case CR_BUFFER_SMALL             : szRes = _T("CR_BUFFER_SMALL")             ; break;  //0x1A
  case CR_NO_ARBITRATOR            : szRes = _T("CR_NO_ARBITRATOR")            ; break;  //0x1B
  case CR_NO_REGISTRY_HANDLE       : szRes = _T("CR_NO_REGISTRY_HANDLE")       ; break;  //0x1C
  case CR_REGISTRY_ERROR           : szRes = _T("CR_REGISTRY_ERROR")           ; break;  //0x1D
  case CR_INVALID_DEVICE_ID        : szRes = _T("CR_INVALID_DEVICE_ID")        ; break;  //0x1E
  case CR_INVALID_DATA             : szRes = _T("CR_INVALID_DATA")             ; break;  //0x1F
  case CR_INVALID_API              : szRes = _T("CR_INVALID_API")              ; break;  //0x20
  case CR_DEVLOADER_NOT_READY      : szRes = _T("CR_DEVLOADER_NOT_READY")      ; break;  //0x21
  case CR_NEED_RESTART             : szRes = _T("CR_NEED_RESTART")             ; break;  //0x22
  case CR_NO_MORE_HW_PROFILES      : szRes = _T("CR_NO_MORE_HW_PROFILES")      ; break;  //0x23
  case CR_DEVICE_NOT_THERE         : szRes = _T("CR_DEVICE_NOT_THERE")         ; break;  //0x24
  case CR_NO_SUCH_VALUE            : szRes = _T("CR_NO_SUCH_VALUE")            ; break;  //0x25
  case CR_WRONG_TYPE               : szRes = _T("CR_WRONG_TYPE")               ; break;  //0x26
  case CR_INVALID_PRIORITY         : szRes = _T("CR_INVALID_PRIORITY")         ; break;  //0x27
  case CR_NOT_DISABLEABLE          : szRes = _T("CR_NOT_DISABLEABLE")          ; break;  //0x28
  case CR_FREE_RESOURCES           : szRes = _T("CR_FREE_RESOURCES")           ; break;  //0x29
  case CR_QUERY_VETOED             : szRes = _T("CR_QUERY_VETOED")             ; break;  //0x2A
  case CR_CANT_SHARE_IRQ           : szRes = _T("CR_CANT_SHARE_IRQ")           ; break;  //0x2B
  case CR_NO_DEPENDENT             : szRes = _T("CR_NO_DEPENDENT")             ; break;  //0x2C
  case CR_SAME_RESOURCES           : szRes = _T("CR_SAME_RESOURCES")           ; break;  //0x2D
  case CR_NO_SUCH_REGISTRY_KEY     : szRes = _T("CR_NO_SUCH_REGISTRY_KEY")     ; break;  //0x2E
  case CR_INVALID_MACHINENAME      : szRes = _T("CR_INVALID_MACHINENAME")      ; break;  //0x2F WinNT ONLY
  case CR_REMOTE_COMM_FAILURE      : szRes = _T("CR_REMOTE_COMM_FAILURE")      ; break;  //0x30 WinNT ONLY
  case CR_MACHINE_UNAVAILABLE      : szRes = _T("CR_MACHINE_UNAVAILABLE")      ; break;  //0x31 WinNT ONLY
  case CR_NO_CM_SERVICES           : szRes = _T("CR_NO_CM_SERVICES")           ; break;  //0x32 WinNT ONLY
  case CR_ACCESS_DENIED            : szRes = _T("CR_ACCESS_DENIED")            ; break;  //0x33 WinNT ONLY
  case CR_CALL_NOT_IMPLEMENTED     : szRes = _T("CR_CALL_NOT_IMPLEMENTED")     ; break;  //0x34
  case CR_INVALID_PROPERTY         : szRes = _T("CR_INVALID_PROPERTY")         ; break;  //0x35
  case CR_DEVICE_INTERFACE_ACTIVE  : szRes = _T("CR_DEVICE_INTERFACE_ACTIVE")  ; break;  //0x36
  case CR_NO_SUCH_DEVICE_INTERFACE : szRes = _T("CR_NO_SUCH_DEVICE_INTERFACE") ; break;  //0x37
  case CR_INVALID_REFERENCE_STRING : szRes = _T("CR_INVALID_REFERENCE_STRING") ; break;  //0x38
  case CR_INVALID_CONFLICT_LIST    : szRes = _T("CR_INVALID_CONFLICT_LIST")    ; break;  //0x39
  case CR_INVALID_INDEX            : szRes = _T("CR_INVALID_INDEX")            ; break;  //0x3A
  case CR_INVALID_STRUCTURE_SIZE   : szRes = _T("CR_INVALID_STRUCTURE_SIZE")   ; break;  //0x3B
  case NUM_CR_RESULTS              : szRes = _T("NUM_CR_RESULTS")              ; break;  //0x3C
  default                          : szRes = _T("<unknown status code>"        );
  }
return szRes;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_DEBUG
/*-----------------------------------------------------------------------------
  <cfgmgr32.h>                 PnP Configuration Manager return status codes
                               Windows Driver Kit: DDK 2600.1106
   CR_SUCCESS                  (0x00)
   CR_DEFAULT                  (0x01)
   CR_OUT_OF_MEMORY            (0x02)
   CR_INVALID_POINTER          (0x03)
   CR_INVALID_FLAG             (0x04)
   CR_INVALID_DEVNODE          (0x05)
   CR_INVALID_DEVINST          CR_INVALID_DEVNODE
   CR_INVALID_RES_DES          (0x06)
   CR_INVALID_LOG_CONF         (0x07)
   CR_INVALID_ARBITRATOR       (0x08)
   CR_INVALID_NODELIST         (0x09)
   CR_DEVNODE_HAS_REQS         (0x0A)
   CR_DEVINST_HAS_REQS         CR_DEVNODE_HAS_REQS
   CR_INVALID_RESOURCEID       (0x0B)
   CR_DLVXD_NOT_FOUND          (0x0C)   // WIN 95 ONLY
   CR_NO_SUCH_DEVNODE          (0x0D)
   CR_NO_SUCH_DEVINST          CR_NO_SUCH_DEVNODE
   CR_NO_MORE_LOG_CONF         (0x0E)
   CR_NO_MORE_RES_DES          (0x0F)
   CR_ALREADY_SUCH_DEVNODE     (0x10)
   CR_ALREADY_SUCH_DEVINST     CR_ALREADY_SUCH_DEVNODE
   CR_INVALID_RANGE_LIST       (0x11)
   CR_INVALID_RANGE            (0x12)
   CR_FAILURE                  (0x13)
   CR_NO_SUCH_LOGICAL_DEV      (0x14)
   CR_CREATE_BLOCKED           (0x15)
   CR_NOT_SYSTEM_VM            (0x16)   // WIN 95 ONLY
   CR_REMOVE_VETOED            (0x17)
   CR_APM_VETOED               (0x18)
   CR_INVALID_LOAD_TYPE        (0x19)
   CR_BUFFER_SMALL             (0x1A)
   CR_NO_ARBITRATOR            (0x1B)
   CR_NO_REGISTRY_HANDLE       (0x1C)
   CR_REGISTRY_ERROR           (0x1D)
   CR_INVALID_DEVICE_ID        (0x1E)
   CR_INVALID_DATA             (0x1F)
   CR_INVALID_API              (0x20)
   CR_DEVLOADER_NOT_READY      (0x21)
   CR_NEED_RESTART             (0x22)
   CR_NO_MORE_HW_PROFILES      (0x23)
   CR_DEVICE_NOT_THERE         (0x24)
   CR_NO_SUCH_VALUE            (0x25)
   CR_WRONG_TYPE               (0x26)
   CR_INVALID_PRIORITY         (0x27)
   CR_NOT_DISABLEABLE          (0x28)
   CR_FREE_RESOURCES           (0x29)
   CR_QUERY_VETOED             (0x2A)
   CR_CANT_SHARE_IRQ           (0x2B)
   CR_NO_DEPENDENT             (0x2C)
   CR_SAME_RESOURCES           (0x2D)
   CR_NO_SUCH_REGISTRY_KEY     (0x2E)
   CR_INVALID_MACHINENAME      (0x2F)   // NT ONLY
   CR_REMOTE_COMM_FAILURE      (0x30)   // NT ONLY
   CR_MACHINE_UNAVAILABLE      (0x31)   // NT ONLY
   CR_NO_CM_SERVICES           (0x32)   // NT ONLY
   CR_ACCESS_DENIED            (0x33)   // NT ONLY
   CR_CALL_NOT_IMPLEMENTED     (0x34)
   CR_INVALID_PROPERTY         (0x35)
   CR_DEVICE_INTERFACE_ACTIVE  (0x36)
   CR_NO_SUCH_DEVICE_INTERFACE (0x37)
   CR_INVALID_REFERENCE_STRING (0x38)
   CR_INVALID_CONFLICT_LIST    (0x39)
   CR_INVALID_INDEX            (0x3A)
   CR_INVALID_STRUCTURE_SIZE   (0x3B)
   NUM_CR_RESULTS              (0x3C)
 */
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2007-08-24 18:15:41  Darko Kolakovic SBCS build
 *  1    Biblioteka1.0         2007-08-24 15:08:05  Darko Kolakovic 
 * $
 *****************************************************************************/
