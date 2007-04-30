Attribute VB_Name = "KWin32"
'$Workfile: KWin32.bas$: implementation file
'$Revision: 5$ $Date: 2007-04-30 16:53:21$
'$Author: Darko Kolakovic$
'
'Microsoft Windows SDK prototypes
'babylonlib@sourceforge.net
'2002-11-02
Option Explicit

Public Const MAX_COMPUTERNAME_LENGTH = 31
Public Const MAX_PATH = 260
Public Const INVALID_HANDLE_VALUE As Long = -1

'From WINNT.H
Public Const APPLICATION_ERROR_MASK       As Long = &H20000000
Public Const ERROR_SEVERITY_SUCCESS       As Long = &H0
Public Const ERROR_SEVERITY_INFORMATIONAL As Long = &H40000000
Public Const ERROR_SEVERITY_WARNING       As Long = &H80000000
Public Const ERROR_SEVERITY_ERROR         As Long = &HC0000000


Public Const HWND_TOPMOST = -1
Public Const HWND_NOTOPMOST = -2

Public Const SW_HIDE = 0
Public Const SW_MAXIMIZE = 3
Public Const SW_MINIMIZE = 6
Public Const SW_NORMAL = 1
Public Const SW_SHOWMAXIMIZED = 3
Public Const SW_SHOWMINIMIZED = 2
Public Const SW_SHOWMINNOACTIVE = 7
Public Const SW_SHOWNA = 8

Public Const SWP_NOMOVE = 2
Public Const SWP_NOSIZE = 1

Public Const EVENTLOG_SUCCESS = 0
Public Const EVENTLOG_ERROR_TYPE = 1
Public Const EVENTLOG_WARNING_TYPE = 2
Public Const EVENTLOG_INFORMATION_TYPE = 4
Public Const EVENTLOG_AUDIT_SUCCESS = 8
Public Const EVENTLOG_AUDIT_FAILURE = 10

Public Const S_OK = 0

Public Type LUID
  UsedPart As Long
  IgnoredForNowHigh32BitPart As Long
End Type

Public Type TOKEN_PRIVILEGES
  PrivilegeCount As Long
  TheLuid        As LUID
  Attributes     As Long
End Type

Public Type GUID
  Data1    As Long
  Data2    As Integer
  Data3    As Integer
  Data4(7) As Byte
End Type

Public Const EWX_LOGOFF As Long = 0
Public Const EWX_SHUTDOWN As Long = 1
Public Const EWX_REBOOT = 2
Public Const EWX_FORCE As Long = 4
Public Const EWX_POWEROFF As Long = 8

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

Public Type SYSTEMTIME
  wYear As Integer
  wMonth As Integer
  wDayOfWeek As Integer
  wDay As Integer
  wHour As Integer
  wMinute As Integer
  wSecond As Integer
  wMilliseconds As Integer
End Type

'Point structure
Public Type POINTAPI
  X As Long
  Y As Long
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

Public Const NIM_ADD = &H0     'add icon to system tray
Public Const NIM_MODIFY = &H1  'modify icon in system tray
Public Const NIM_DELETE = &H2  'delete icon in system tray

Public Const NIF_MESSAGE = &H1 'windows message about event is sent
Public Const NIF_ICON = &H2    'icon is displayed
Public Const NIF_TIP = &H4     'tooltip availibility

Public Type NOTIFYICONDATA
  cbSize           As Long 'size of the structure
  hWnd             As Long 'handle of the window
  uID              As Long 'unique ID for the icon
  uFlags           As Long 'flags
  uCallbackMessage As Long '
  hIcon            As Long 'memory location of the icon
  szTip     As String * 64 'tooltip of 64 characters maximum
End Type

Public Type STARTUPINFO
  cb              As Long
  lpReserved      As String
  lpDesktop       As String
  lpTitle         As String
  dwX             As Long
  dwY             As Long
  dwXSize         As Long
  dwYSize         As Long
  dwXCountChars   As Long
  dwYCountChars   As Long
  dwFillAttribute As Long
  dwFlags         As Long
  wShowWindow     As Integer
  cbReserved2     As Integer
  lpReserved2     As Long
  hStdInput       As Long
  hStdOutput      As Long
  hStdError       As Long
End Type

Public Const PROCESS_TERMINATE = &H1
Public Const SYNCHRONIZE = &H100000
Public Const PROCESS_QUERY_INFORMATION = 1024
Public Const PROCESS_VM_READ = 16

Public Const SMTO_BLOCK = &H1
Public Const SMTO_ABORTIFHUNG = &H2

Public Type BROWSEINFO
    hwndOwner As Long
    pIDLRoot As Long
    pszDisplayName As Long
    lpszTitle As Long
    ulFlags As Long
    lpfnCallback As Long
    lParam As Long
    iImage As Long
End Type

Public Type SECURITY_ATTRIBUTES
  nLength As Long
  lpSecurityDescriptor As Long
  bInheritHandle As Long
End Type

Public Type PROCESS_INFORMATION
        hProcess As Long
        hThread As Long
        dwProcessId As Long
        dwThreadId As Long
End Type

Public Type PROCESSENTRY32
    lSize            As Long
    lUsage           As Long
    lProcessid       As Long
    lDefaultHeapId   As Long
    lModuleId        As Long
    lThreads         As Long
    lParentProcessId As Long
    lPriClassBase    As Long
    lFlags           As Long
    sExeFile         As String * MAX_PATH
End Type

Public Type PROCESS_MEMORY_COUNTERS
    cb                          As Long
    PageFaultCount              As Long
    PeakWorkingSetSize          As Long
    WorkingSetSize              As Long
    QuotaPeakPagedPoolUsage     As Long
    QuotaPagedPoolUsage         As Long
    QuotaPeakNonPagedPoolUsage  As Long
    QuotaNonPagedPoolUsage      As Long
    PagefileUsage               As Long
    PeakPagefileUsage           As Long
End Type

Public Type APPINFO
  iAppID                  As Long
  sStartOption            As String
  sAppName                As String
  sAppPath                As String
  sStartParams            As String
  iShowWindow             As Long
  iXPos                   As Long
  iYPos                   As Long
  iXSize                  As Long
  iYSize                  As Long
  sMonitorOption          As String
  sDependents             As String
  iLastRestart            As Long
  iLoadTime               As Integer
  iLastResponding         As Long
  iResponseTimeout        As Long
  iTotalTimeout           As Long
  iWorkingSetMax          As Long
  iWorkingSetTimeout      As Long
  iLastWorkSetNormal      As Long
  iPageFileUseMax         As Long
  iPageFileUseTimeout     As Long
  iLastPageFileNormal     As Long
  sLogOption              As String
  iPosInObjectArray       As Integer
End Type

Public Const WM_NULL = &H0
Public Const WM_CLOSE = &H10
Public Const WM_MOUSEMOVE = &H200
Public Const WM_RBUTTONUP = &H205
Public Const WM_RBUTTONDOWN = &H204
Public Const WM_LBUTTONDBLCLK = &H203
Public Const WM_GETTEXT = &HD
Public Const WM_GETTEXTLENGTH = &HE

Public Type SHFILEINFO
  hIcon As Long
  iIcon As Long
  dwAttributes As Long
  szDisplayName As String * 260
  szTypeName As String * 80
End Type

Public Type OSVERSIONINFO
   dwOSVersionInfoSize As Long
   dwMajorVersion As Long
   dwMinorVersion As Long
   dwBuildNumber As Long
   dwPlatformId As Long
   szCSDVersion As String * 128
End Type
Public Const VER_PLATFORM_WIN32s = 0
Public Const VER_PLATFORM_WIN32_WINDOWS = 1
Public Const VER_PLATFORM_WIN32_NT = 2

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1    Biblioteka1.0         2007-04-18 15:59:40  Darko Kolakovic
'$
'*******************************************************************************
