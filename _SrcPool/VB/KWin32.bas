Attribute VB_Name = "KWin32.bas"
'$Workfile: S:\_SrcPool\VB\KWin32.bas$: implementation file
'$Revision: 1$ $Date: 2007-04-18 15:59:40$
'$Author: Darko Kolakovic$
'
'Microsoft Windows SDK prototypes
'babylonlib@sourceforge.net
'2002-11-02

'Pointer to string (SBCS)
Public Type LPSTR
  Ptr As Long
End Type
'Pointer to wide-character string
Public Type LPWSTR
  Ptr As Long
End Type

'Unsigned integer 32-bit
Public Type DWORD
  m_Byte0 As Byte
  m_Byte1 As Byte
  m_Byte2 As Byte
  MByte3 As Byte
End Type

'Filetime 64-bit unsigned integer
Public Type FILETIME
  dwLowDateTime As Long
  dwHighDateTime As Long
End Type

'Point structure
Public Type POINTAPI
  x As Long
  y As Long
End Type

'Rectangle structure
Public Type RECT
  Left As Long
  Top  As Long
  Right As Long
  Bottom As Long
End Type

'Color quadruplet
Public Type RGBQUAD
  rgbBlue     As Byte
  rgbGreen    As Byte
  rgbRed      As Byte
  rgbReserved As Byte
End Type

'Windows-OS/2 Bitmap Header structure sizeof = 40 bytes
Public Type BITMAPINFOHEADER
  biSize          As Long
  biWidth         As Long
  biHeight        As Long
  biPlanes        As Integer
  biBitCount      As Integer
  biCompression   As Long
  biSizeImage     As Long
  biXPelsPerMeter As Long
  biYPelsPerMeter As Long
  biClrUsed       As Long
  biClrImportant  As Long
End Type

Public Type BITMAPINFO
  bmiHeader   As BITMAPINFOHEADER
  bmiColors   As RGBQUAD
End Type

'Font structure
Public Type LOGFONT
  lfHeight          As Long
  lfWidth           As Long
  lfEscapement      As Long
  lfOrientation     As Long
  lfWeight          As Long
  lfItalic          As Byte
  lfUnderline       As Byte
  lfStrikeOut       As Byte
  lfCharSet         As Byte
  lfOutPrecision    As Byte
  lfClipPrecision   As Byte
  lfQuality         As Byte
  lfPitchAndFamily  As Byte
  lfFaceName        As String * 32
End Type

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log: 
' 1    Biblioteka1.0         2007-04-18 15:59:40  Darko Kolakovic 
'$
'*******************************************************************************
