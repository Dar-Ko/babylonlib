Attribute VB_Name = "KWinTypes"
'$Workfile: KWinTypes.bas$: implementation file
'$Revision: 1.1 $ $Date: 2008/05/23 20:30:53 $
'$Author: ddarko $
'
'Microsoft Windows Data types [Data Structures] WTypes.h
'2003-05-29
Option Explicit

'-------------------------------------------------------------------------------
' Microsoft Windows Data types [Data Structures] WTypes.h

'Rectangle structure
Public Type RECT
  left As Long
  top  As Long
  right As Long
  bottom As Long
End Type

Public Type RECTL
  left As Long
  top As Long
  right As Long
  bottom As Long
End Type

'Point structure
Public Type POINT
  x As Long
  Y As Long
End Type

Public Type SIZE
  cx As Long
  cy As Long
End Type

Public Type LPSIZE
  Ptr As Long
End Type

Public Type SHORT
  m_Byte0 As Byte
  m_Byte1 As Byte
End Type

Public Type USHORT
  m_Byte0 As Byte
  m_Byte1 As Byte
End Type

Public Type LPUSHORT
  Ptr As Long
End Type

Public Type ULONG
  m_ULong As Long
End Type

Public Type WORD
  m_Byte0 As Byte
  m_Byte1 As Byte
End Type

'Unsigned integer 32-bit
Public Type DWORD
  m_Byte0 As Byte
  m_Byte1 As Byte
  m_Byte2 As Byte
  m_Byte3 As Byte
End Type

Public Type ULARGE_INTEGER
  dwLow As Long
  dwHigh As Long
End Type

Public Type PALETTEENTRY
  peRed   As Byte
  peGreen As Byte
  peBlue  As Byte
  peFlags As Byte
End Type
    
Public Type LOGPALETTE
  palVersion    As WORD
  palNumEntries As WORD
  palPalEntry   As PALETTEENTRY
End Type
    
'Filetime 64-bit unsigned integer
Public Type FILETIME
  dwLowDateTime  As Long
  dwHighDateTime As Long
End Type

Public Type SYSTEMTIME
  wYear      As Integer
  wMonth     As Integer
  wDayOfWeek As Integer
  wDay       As Integer
  wHour      As Integer
  wMinute    As Integer
  wSecond    As Integer
  wMilliseconds As Integer
End Type
    
'Security information for a securable object. A security descriptor identifies
'the object's owner and primary group. It can also contain a DACL that controls
'access to the object, and a SACL that controls the logging of attempts to access
'the object.
Public Type SECURITY_ATTRIBUTES
  nLength As Long   'size, in bytes, of this structure. Set this value to
                    'the size of the SECURITY_ATTRIBUTES structure.
  lpSecurityDescriptor As Long 'security descriptor for the object that
                               'controls the sharing of it.
  bInheritHandle As Long 'TRUE specifies whether the returned handle is
                         'inherited when a new process is created.
End Type

Public Type ACL
  AclRevision As UCHAR
  Sbz1        As UCHAR
  AclSize     As USHORT
  AceCount    As USHORT
  Sbz2        As USHORT
End Type
    
Public Type PACL
  Ptr As Long
End If

'Public Type SECURITY_DESCRIPTOR
'    UCHAR Revision;
'    UCHAR Sbz1;
'    SECURITY_DESCRIPTOR_CONTROL Control; todo
'    PSID Owner;
'    PSID Group;
'    Sacl as PACL;
'    Dacl as PACL;
'End Type
    
Public Type COAUTHIDENTITY
    User As LPUSHORT
    UserLength  As ULONG
    Domain As LPUSHORT
    DomainLength  As ULONG
    Password asLPUSHORT
    PasswordLength  As ULONG
    Flags As ULONG
End Type

Public Type PCOAUTHIDENTITY
  Ptr As Long
End Type

Public Type COAUTHINFO
  dwAuthnSvc As DWORD
  dwAuthzSvc As DWORD
  pwszServerPrincName As LPWSTR
  dwAuthnLevel  As DWORD
  dwImpersonationLevel  As DWORD
  pAuthIdentityData     As PCOAUTHIDENTITY
  dwCapabilities        As DWORD
End Type
    
Public Type TEXTMETRICW
  tmHeight            As Long
  tmAscent            As Long
  tmDescent           As Long
  tmInternalLeading   As Long
  tmExternalLeading   As Long
  tmAveCharWidth      As Long
  tmMaxCharWidth      As Long
  tmWeight            As Long
  tmOverhang          As Long
  tmDigitizedAspectX  As Long
  tmDigitizedAspectY  As Long
  tmFirstChar         As WCHAR
  tmLastChar          As WCHAR
  tmDefaultChar       As WCHAR
  tmBreakChar         As WCHAR
  tmItalic            As Byte
  tmUnderlined        As Byte
  tmStruckOut         As Byte
  tmPitchAndFamily    As Byte
  tmCharSet           As Byte
End Type
    
Public Type CSPLATFORM
  dwPlatformId As DWORD
  dwVersionHi  As DWORD
  dwVersionLo  As DWORD
  dwProcessorArch  As DWORD
End Type

'Public Type QUERYCONTEXT
'  dwContext  As DWORD
'  Platform As CSPLATFORM
'  LCID Locale; TODO:
'  dwVersionHi  As DWORD
'  dwVersionLo  As DWORD
'End Type
    
'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: KWinTypes.bas,v $
'Revision 1.1  2008/05/23 20:30:53  ddarko
'Moved data types from KWin32
'
'*******************************************************************************
