Attribute VB_Name = "KWinSetupApi"
'$Workfile: S:\_SrcPool\VB\KWinMm.bas$: implementation file
'$Revision: 1$ $Date: 2007-05-08 10:12:41$
'$Author: Darko Kolakovic$
'
'MS Windows SetupApi DLL
'2005-01-04
Option Explicit

'///////////////////////////////////////////////////////////////////////////////
'setupapi.h
Public Const DIGCF_PRESENT = &H2
Public Const DIGCF_DEVICEINTERFACE = &H10


Public Type SP_DEVICE_INTERFACE_DATA
  cbSize As Long
  InterfaceClassGuid As GUID
  Flags As Long
  Reserved As Long
End Type

Public Type SP_DEVICE_INTERFACE_DETAIL_DATA
  cbSize As Long
  DevicePath As Byte
End Type

'///////////////////////////////////////////////////////////////////////////////

Public Declare Function SetupDiCreateDeviceInfoList _
  Lib "setupapi.dll" _
  (ByRef ClassGuid As GUID, _
  ByVal hwndParent As Long) _
  As Long

Public Declare Function SetupDiDestroyDeviceInfoList _
  Lib "setupapi.dll" _
  (ByVal DeviceInfoSet As Long) _
  As Long

Public Declare Function SetupDiEnumDeviceInterfaces _
  Lib "setupapi.dll" _
  (ByVal DeviceInfoSet As Long, _
  ByVal DeviceInfoData As Long, _
  ByRef InterfaceClassGuid As GUID, _
  ByVal MemberIndex As Long, _
  ByRef DeviceInterfaceData As SP_DEVICE_INTERFACE_DATA) _
  As Long

Public Declare Function SetupDiGetClassDevs _
  Lib "setupapi.dll" _
  Alias "SetupDiGetClassDevsA" _
  (ByRef ClassGuid As GUID, _
  ByVal Enumerator As String, _
  ByVal hwndParent As Long, _
  ByVal Flags As Long) _
  As Long

Public Declare Function SetupDiGetDeviceInterfaceDetail _
  Lib "setupapi.dll" _
  Alias "SetupDiGetDeviceInterfaceDetailA" _
  (ByVal DeviceInfoSet As Long, _
  ByRef DeviceInterfaceData As SP_DEVICE_INTERFACE_DATA, _
  ByVal DeviceInterfaceDetailData As Long, _
  ByVal DeviceInterfaceDetailDataSize As Long, _
  ByRef RequiredSize As Long, _
  ByVal DeviceInfoData As Long) _
  As Long

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1    Biblioteka1.0         2007-05-08 10:12:41  Darko Kolakovic
'$
'*******************************************************************************
