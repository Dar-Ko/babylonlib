Attribute VB_Name = "KWinHid"
'$Workfile: S:\_SrcPool\VB\KWinMm.bas$: implementation file
'$Revision: 1$ $Date: 2007-05-08 10:12:41$
'$Author: Darko Kolakovic$
'
'MS Windows hid DLL (Human Interface Descriptor)
'2005-01-04
Option Explicit

'///////////////////////////////////////////////////////////////////////////////
'hidpi.h
Public Const HIDP_STATUS_SUCCESS = &H110000

'HidP_Report_Type as 16-bit integers
Public Const HidP_Input = 0
Public Const HidP_Output = 1
Public Const HidP_Feature = 2

Public Type HIDD_ATTRIBUTES
  Size As Long
  VendorID As Integer
  ProductID As Integer
  VersionNumber As Integer
End Type

'Note: Reference in  Windows 98 DDK documentation is outdated.
Public Type HIDP_CAPS
  Usage As Integer
  UsagePage As Integer
  InputReportByteLength As Integer
  OutputReportByteLength As Integer
  FeatureReportByteLength As Integer
  Reserved(16) As Integer
  NumberLinkCollectionNodes As Integer
  NumberInputButtonCaps As Integer
  NumberInputValueCaps As Integer
  NumberInputDataIndices As Integer
  NumberOutputButtonCaps As Integer
  NumberOutputValueCaps As Integer
  NumberOutputDataIndices As Integer
  NumberFeatureButtonCaps As Integer
  NumberFeatureValueCaps As Integer
  NumberFeatureDataIndices As Integer
End Type

Public Type HIDP_VALUE_CAPS
  UsagePage As Integer
  ReportID As Byte
  BitField As Integer
  LinkCollection As Integer
  LinkUsage As Integer
  LinkUsagePage As Integer
  IsRange As Byte 'if true, use [UsageMin, UsageMax]
  IsStringRange As Byte 'if true, use [StringMin, StringMax]
  IsDesignatorRange As Byte 'if true, use [DesignatorMin, DesignatorMax]
  IsAbsolute As Byte
  HasNull As Byte
  Reserved1 As Byte
  BitSize As Integer
  ReportCount As Integer
  Reserved2 As Integer
  Reserved3 As Integer
  Reserved4 As Integer
  Reserved5 As Integer
  Reserved6 As Integer
  UnitsExp As Long
  Units As Long
  LogicalMin As Long
  LogicalMax As Long
  PhysicalMin As Long
  PhysicalMax As Long
  UsageMin As Integer
  UsageMax As Integer
  StringMin As Integer
  StringMax As Integer
  DesignatorMin As Integer
  DesignatorMax As Integer
  DataIndexMin As Integer
  DataIndexMax As Integer
End Type

'///////////////////////////////////////////////////////////////////////////////

Public Declare Function HidD_FreePreparsedData _
  Lib "hid.dll" _
  (ByVal PreparsedData As Long) _
  As Long

Public Declare Function HidD_GetAttributes _
  Lib "hid.dll" _
  (ByVal HidDeviceObject As Long, _
  ByRef Attributes As HIDD_ATTRIBUTES) _
  As Byte

Public Declare Sub HidD_GetHidGuid _
  Lib "hid.dll" _
  (ByRef HidGuid As GUID)

Public Declare Function HidD_GetPreparsedData _
  Lib "hid.dll" _
  (ByVal HidDeviceObject As Long, _
  ByRef PreparsedData As Long) _
  As Byte

Public Declare Function HidP_GetCaps _
  Lib "hid.dll" _
  (ByVal PreparsedData As Long, _
  ByRef Capabilities As HIDP_CAPS) _
  As Long

Public Declare Function HidP_GetValueCaps _
  Lib "hid.dll" _
  (ByVal ReportType As Integer, _
  ByRef ValueCaps As HIDP_VALUE_CAPS, _
  ByRef ValueCapsLength As Integer, _
  ByVal PreparsedData As Long) _
  As Long

Public Declare Function HidP_GetSpecificValueCaps _
  Lib "hid.dll" _
  (ByVal ReportType As Integer, _
  ByVal UsagePage As Integer, _
  ByVal LinkCollection As Integer, _
  ByVal Usage As Integer, _
  ByRef ValueCaps As HIDP_VALUE_CAPS, _
  ByRef ValueCapsLength As Integer, _
  ByVal PreparsedData As Long) _
  As Long

Public Declare Function HidP_GetUsageValue _
  Lib "hid.dll" _
  (ByVal ReportType As Integer, _
  ByVal UsagePage As Integer, _
  ByVal LinkCollection As Integer, _
  ByVal Usage As Integer, _
  ByRef UsageValue As Long, _
  ByVal PreparsedData As Long, _
  ByRef Report As Byte, _
  ByVal ReportLength As Long) _
  As Long

Public Declare Function HidP_GetUsageValueArray _
  Lib "hid.dll" _
  (ByVal ReportType As Integer, _
  ByVal UsagePage As Integer, _
  ByVal LinkCollection As Integer, _
  ByVal Usage As Integer, _
  ByRef UsageValue As Byte, _
  ByVal UsageValueByteLength As Integer, _
  ByVal PreparsedData As Long, _
  ByRef Report As Byte, _
  ByVal ReportLength As Long) _
  As Long

Public Declare Function HidD_GetFeature _
  Lib "hid.dll" _
  (ByVal HidDeviceObject As Long, _
  ByRef ReportBuffer As Byte, _
  ByVal ReportBufferLength As Long) _
  As Byte

Public Declare Function HidD_SetFeature _
  Lib "hid.dll" _
  (ByVal HidDeviceObject As Long, _
  ByRef ReportBuffer As Byte, _
  ByVal ReportBufferLength As Long) _
  As Byte

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1    Biblioteka1.0         2007-05-08 10:12:41  Darko Kolakovic
'$
'*******************************************************************************
