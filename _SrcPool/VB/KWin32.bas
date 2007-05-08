Attribute VB_Name = "KWin32"
'$Workfile: KWin32.bas$: implementation file
'$Revision: 6$ $Date: 2007-05-08 10:14:45$
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
Public Const APPLICATION_ERROR_MASK   As Long = &H20000000
Public Const ERROR_SEVERITY_SUCCESS   As Long = &H0
Public Const ERROR_SEVERITY_INFORMATIONAL As Long = &H40000000
Public Const ERROR_SEVERITY_WARNING   As Long = &H80000000
Public Const ERROR_SEVERITY_ERROR   As Long = &HC0000000

Public Const HWND_TOP = 0
Public Const HWND_BOTTOM = 1
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
Public Const SW_RESTORE = 9
Public Const SW_SHOW = 5
Public Const SW_SHOWDEFAULT = 10
Public Const SW_SHOWNOACTIVATE = 4
Public Const SW_SHOWNORMAL = 1

Public Const SWP_NOSIZE = &H1
Public Const SWP_NOMOVE = &H2
Public Const SWP_NOZORDER = &H4
Public Const SWP_NOREDRAW = &H8
Public Const SWP_NOACTIVATE = &H10
Public Const SWP_FRAMECHANGED = &H20  '  The frame changed: send WM_NCCALCSIZE
Public Const SWP_DRAWFRAME = SWP_FRAMECHANGED
Public Const SWP_SHOWWINDOW = &H40
Public Const SWP_HIDEWINDOW = &H80
Public Const SWP_NOCOPYBITS = &H100
Public Const SWP_NOOWNERZORDER = &H200  '  Don't do owner Z ordering
Public Const SWP_NOREPOSITION = SWP_NOOWNERZORDER

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
  TheLuid  As LUID
  Attributes   As Long
End Type

Public Type GUID
  Data1  As Long
  Data2  As Integer
  Data3  As Integer
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
  rgbBlue   As Byte
  rgbGreen  As Byte
  rgbRed  As Byte
  rgbReserved As Byte
End Type

'Windows-OS/2 Bitmap Header structure sizeof = 40 bytes
Public Type BITMAPINFOHEADER
  biSize    As Long
  biWidth   As Long
  biHeight  As Long
  biPlanes  As Integer
  biBitCount  As Integer
  biCompression   As Long
  biSizeImage   As Long
  biXPelsPerMeter As Long
  biYPelsPerMeter As Long
  biClrUsed   As Long
  biClrImportant  As Long
End Type

Public Type BITMAPINFO
  bmiHeader   As BITMAPINFOHEADER
  bmiColors   As RGBQUAD
End Type

'Font structure
Public Type LOGFONT
  lfHeight    As Long
  lfWidth     As Long
  lfEscapement  As Long
  lfOrientation   As Long
  lfWeight    As Long
  lfItalic    As Byte
  lfUnderline   As Byte
  lfStrikeOut   As Byte
  lfCharSet   As Byte
  lfOutPrecision  As Byte
  lfClipPrecision   As Byte
  lfQuality   As Byte
  lfPitchAndFamily  As Byte
  lfFaceName  As String * 32
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

Public Const SYNCHRONIZE = &H100000

Public Const PROCESS_TERMINATE = &H1
Public Const PROCESS_CREATE_THREAD = &H2
Public Const PROCESS_SET_SESSIONID = &H4
Public Const PROCESS_VM_OPERATION = &H8
Public Const PROCESS_VM_READ = &H10
Public Const PROCESS_VM_WRITE = &H20
Public Const PROCESS_DUP_HANDLE = &H40
Public Const PROCESS_CREATE_PROCESS = &H80
Public Const PROCESS_SET_QUOTA = &H100
Public Const PROCESS_SET_INFORMATION = &H200
Public Const PROCESS_QUERY_INFORMATION = &H400



Public Const SMTO_BLOCK = &H1
Public Const SMTO_ABORTIFHUNG = &H2

Public Type BROWSEINFO
  hwndOwner As Long
  pIDLRoot As Long
  pszDisplayName As Long
  lpszTitle As Long
  ulFlags As Long
  lpfnCallback As Long
  lparam As Long
  iImage As Long
End Type

Public Type SECURITY_ATTRIBUTES
  nLength As Long
  lpSecurityDescriptor As Long
  bInheritHandle As Long
End Type

Public Type PROCESS_INFORMATION
  hprocess    As Long
  hThread     As Long
  dwProcessId As Long
  dwThreadId  As Long
End Type

Public Type PROCESSENTRY32
  lSize    As Long
  lUsage     As Long
  lProcessid   As Long
  lDefaultHeapId   As Long
  lModuleId  As Long
  lThreads   As Long
  lParentProcessId As Long
  lPriClassBase  As Long
  lFlags     As Long
  sExeFile   As String * MAX_PATH
End Type

Public Type PROCESS_MEMORY_COUNTERS
  cb        As Long
  PageFaultCount    As Long
  PeakWorkingSetSize    As Long
  WorkingSetSize    As Long
  QuotaPeakPagedPoolUsage   As Long
  QuotaPagedPoolUsage   As Long
  QuotaPeakNonPagedPoolUsage  As Long
  QuotaNonPagedPoolUsage  As Long
  PagefileUsage     As Long
  PeakPagefileUsage     As Long
End Type

Public Type APPINFO
  iAppID      As Long
  sStartOption    As String
  sAppName    As String
  sAppPath    As String
  sStartParams    As String
  iShowWindow     As Long
  iXPos       As Long
  iYPos       As Long
  iXSize      As Long
  iYSize      As Long
  sMonitorOption    As String
  sDependents     As String
  iLastRestart    As Long
  iLoadTime     As Integer
  iLastResponding   As Long
  iResponseTimeout  As Long
  iTotalTimeout     As Long
  iWorkingSetMax    As Long
  iWorkingSetTimeout  As Long
  iLastWorkSetNormal  As Long
  iPageFileUseMax   As Long
  iPageFileUseTimeout   As Long
  iLastPageFileNormal   As Long
  sLogOption    As String
  iPosInObjectArray   As Integer
End Type

Public Const WM_ACTIVATE = &H6
Public Const WM_ACTIVATEAPP = &H1C
Public Const WM_CHAR = &H102
Public Const WM_CLOSE = &H10
Public Const WM_COMMAND = &H111
Public Const WM_GETTEXT = &HD
Public Const WM_GETTEXTLENGTH = &HE
Public Const WM_INITMENU = &H116
Public Const WM_KEYDOWN = &H100
Public Const WM_KEYUP = &H101
Public Const WM_KILLFOCUS = &H8
Public Const WM_LBUTTONDBLCLK = &H203
Public Const WM_LBUTTONDOWN = &H201
Public Const WM_LBUTTONUP = &H202
Public Const WM_MBUTTONDBLCLK = &H209
Public Const WM_MBUTTONDOWN = &H207
Public Const WM_MBUTTONUP = &H208
Public Const WM_MOUSEHOVER = &H2A1
Public Const WM_MOUSELEAVE = &H2A3
Public Const WM_MOUSEMOVE = &H200
Public Const WM_NCACTIVATE = &H86
Public Const WM_NCHITTEST = &H84
Public Const WM_NULL = &H0
Public Const WM_PAINT = &HF
Public Const WM_QUIT = &H12
Public Const WM_RBUTTONDBLCLK = &H206
Public Const WM_RBUTTONDOWN = &H204
Public Const WM_RBUTTONUP = &H205
Public Const WM_SETCURSOR = &H20
Public Const WM_SETFOCUS = &H7
Public Const WM_SETTEXT = &HC
Public Const WM_SETTINGCHANGE = &H1A
Public Const WM_TIMER = &H113
Public Const WM_USER = &H400

Public Type SHFILEINFO
  hicon As Long
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

Public Const HWND_BROADCAST = &HFFFF&

Public Const SMTO_NORMAL = &H0



Public Const MK_LBUTTON = &H1&
Public Const MK_MBUTTON = &H10&
Public Const MK_RBUTTON = &H2&

Public Const SC_CLOSE = &HF060
Public Const SC_MAXIMIZE = &HF030
Public Const SC_MINIMIZE = &HF020
Public Const SC_RESTORE = &HF120&

Public Const BM_CLICK = &HF5
Public Const BM_GETCHECK = &HF0
Public Const BST_CHECKED = &H1

Public Const LB_ADDSTRING = &H180
Public Const LB_FINDSTRINGEXACT = &H1A2
Public Const LB_GETCOUNT = &H18B
Public Const LB_GETCURSEL = &H188
Public Const LB_GETTEXT = &H189
Public Const LB_GETTEXTLEN = &H18A
Public Const LB_INSERTSTRING = &H181
Public Const LB_SELECTSTRING = &H18C
Public Const LB_SETCURSEL = &H186
Public Const LB_ERR = (-1)
Public Const LBN_SELCHANGE = 1

Public Const CB_ADDSTRING = &H143
Public Const CB_FINDSTRINGEXACT = &H158
Public Const CB_SETCURSEL = &H14E
Public Const CB_ERR = (-1)
Public Const CBN_SELCHANGE = 1
Public Const CBN_SELENDOK = 9

Public Const EM_SETMODIFY = &HB9

Public Const BN_CLICKED = 0


Public Const SND_APPLICATION = &H80   '  look for application specific association
Public Const SND_ALIAS = &H10000
Public Const SND_FILENAME = &H20000
Public Const SND_ASYNC = &H1
Public Const SND_NODEFAULT = &H2
Public Const SND_MEMORY = &H4
Public Const SND_SYNC = &H0   '  play synchronously (default)


Public Const IDI_APPLICATION = 32512&
Public Const IDI_ERROR = 32513&
Public Const IDI_QUESTION = 32514&
Public Const IDI_EXCLAMATION = 32515&
Public Const IDI_INFORMATION = 32516&


Public Const GWL_EXSTYLE = (-20)
Public Const GWL_HINSTANCE = (-6)
Public Const GWL_HWNDPARENT = (-8)
Public Const GWL_ID = (-12)
Public Const GWL_STYLE = (-16)
Public Const GWL_USERDATA = (-21)
Public Const GWL_WNDPROC = (-4)


Public Const WS_DISABLED = &H8000000
Public Const WS_POPUP = &H80000000
Public Const WS_VISIBLE = &H10000000

Public Const SM_CMETRICS = 44
Public Const SM_CMOUSEBUTTONS = 43
Public Const SM_CXBORDER = 5
Public Const SM_CXCURSOR = 13
Public Const SM_CXDLGFRAME = 7
Public Const SM_CXDOUBLECLK = 36
Public Const SM_CXFIXEDFRAME = SM_CXDLGFRAME
Public Const SM_CXFRAME = 32
Public Const SM_CXHSCROLL = 21
Public Const SM_CXHTHUMB = 10
Public Const SM_CXICON = 11
Public Const SM_CXICONSPACING = 38
Public Const SM_CXMAXIMIZED = 61
Public Const SM_CXMIN = 28
Public Const SM_CXMINTRACK = 34
Public Const SM_CXSCREEN = 0
Public Const SM_CXSIZE = 30
Public Const SM_CXSIZEFRAME = SM_CXFRAME
Public Const SM_CXVSCROLL = 2
Public Const SM_CYBORDER = 6
Public Const SM_CYCAPTION = 4
Public Const SM_CYCURSOR = 14
Public Const SM_CYDLGFRAME = 8
Public Const SM_CYDOUBLECLK = 37
Public Const SM_CYFIXEDFRAME = SM_CYDLGFRAME
Public Const SM_CYFRAME = 33
Public Const SM_CYHSCROLL = 3
Public Const SM_CYFULLSCREEN = 17
Public Const SM_CYICON = 12
Public Const SM_CYICONSPACING = 39
Public Const SM_CYKANJIWINDOW = 18
Public Const SM_CYMAXIMIZED = 62
Public Const SM_CYMENU = 15
Public Const SM_CYMIN = 29
Public Const SM_CYMINTRACK = 35
Public Const SM_CYSCREEN = 1
Public Const SM_CYSIZEFRAME = SM_CYFRAME
Public Const SM_CYVTHUMB = 9

Public Const MOVEFILE_REPLACE_EXISTING = &H1
Public Const MOVEFILE_COPY_ALLOWED = &H2
Public Const MOVEFILE_DELAY_UNTIL_REBOOT = &H4


Public Const FILE_NOTIFY_CHANGE_ATTRIBUTES = &H4
Public Const FILE_NOTIFY_CHANGE_DIR_NAME = &H2
Public Const FILE_NOTIFY_CHANGE_FILE_NAME = &H1
Public Const FILE_NOTIFY_CHANGE_LAST_WRITE = &H10
Public Const FILE_NOTIFY_CHANGE_SECURITY = &H100
Public Const FILE_NOTIFY_CHANGE_SIZE = &H8


Public Const INFINITE = &HFFFFFFFF   '  Infinite timeout
Public Const WAIT_OBJECT_0 As Long = &H0&
Public Const WAIT_TIMEOUT As Long = &H102&
Public Const WAIT_ABANDONED As Long = &H80&

Public Type WINDOWPLACEMENT
  Length As Long
  flags As Long
  showCmd As Long
  ptMinPosition As POINTAPI
  ptMaxPosition As POINTAPI
  rcNormalPosition As RECT
End Type

Public Const ERROR_SUCCESS = 0&
Public Const ERROR_CANCELLED = 1223&
Public Const ERROR_ALREADY_EXISTS = 183&

Public Const FILE_ATTRIBUTE_ARCHIVE = &H20
Public Const FILE_ATTRIBUTE_COMPRESSED = &H800
Public Const FILE_ATTRIBUTE_DIRECTORY = &H10
Public Const FILE_ATTRIBUTE_HIDDEN = &H2
Public Const FILE_ATTRIBUTE_NORMAL = &H80
Public Const FILE_ATTRIBUTE_READONLY = &H1
Public Const FILE_ATTRIBUTE_SYSTEM = &H4
Public Const FILE_ATTRIBUTE_TEMPORARY = &H100

Public Type WIN32_FIND_DATA
  dwFileAttributes As Long
  ftCreationTime As FILETIME
  ftLastAccessTime As FILETIME
  ftLastWriteTime As FILETIME
  nFileSizeHigh As Long
  nFileSizeLow As Long
  dwReserved0 As Long
  dwReserved1 As Long
  cFileName As String * MAX_PATH
  cAlternate As String * 14
End Type


Public Const IDOK = 1
Public Const IDCANCEL = 2
Public Const IDYES = 6
Public Const IDNO = 7

Public Const PS_SOLID = 0


Public Const GW_HWNDFIRST = 0
Public Const GW_HWNDLAST = 1
Public Const GW_HWNDNEXT = 2
Public Const GW_HWNDPREV = 3
Public Const GW_OWNER = 4
Public Const GW_CHILD = 5


Public Type MEMORY_BASIC_INFORMATION
   BaseAddress As Long
   AllocationBase As Long
   AllocationProtect As Long
   RegionSize As Long
   State As Long
   Protect As Long
   lType As Long
End Type

Public Const MEM_COMMIT = &H1000
Public Const MEM_RESERVE = &H2000
Public Const MEM_FREE = &H10000

Public Type TrackMouseEventType
  cbSize As Long
  dwFlags As Long
  hwndTrack As Long
  dwHoverTime As Long
End Type
Public Const TME_HOVER = &H1
Public Const TME_LEAVE = &H2
Public Const TME_QUERY = &H40000000
Public Const TME_CANCEL = &H80000000

Public Const PIPE_ACCESS_DUPLEX = &H3
Public Const PIPE_ACCESS_INBOUND = &H1
Public Const PIPE_ACCESS_OUTBOUND = &H2
Public Const PIPE_TYPE_BYTE = &H0
Public Const PIPE_TYPE_MESSAGE = &H4
Public Const PIPE_READMODE_BYTE = &H0
Public Const PIPE_READMODE_MESSAGE = &H2
Public Const PIPE_NOWAIT = &H1
Public Const PIPE_WAIT = &H0

Public Const ERROR_PIPE_BUSY = 231&
Public Const ERROR_PIPE_CONNECTED = 535&
Public Const ERROR_PIPE_LISTENING = 536&
Public Const ERROR_PIPE_NOT_CONNECTED = 233&
Public Const ERROR_NO_DATA = 232&

Public Const STANDARD_RIGHTS_REQUIRED = &HF0000


Public Const GENERIC_READ = &H80000000
Public Const GENERIC_WRITE = &H40000000
Public Const FILE_SHARE_READ = &H1
Public Const FILE_SHARE_WRITE = &H2
Public Const FILE_SHARE_DELETE = &H4
Public Const CREATE_NEW = 1
Public Const CREATE_ALWAYS = 2
Public Const OPEN_EXISTING = 3
Public Const OPEN_ALWAYS = 4
Public Const TRUNCATE_EXISTING = 5
Public Const FILE_FLAG_RANDOM_ACCESS = &H10000000
Public Const FILE_FLAG_DELETE_ON_CLOSE = &H4000000

Public Type OVERLAPPED
  Internal As Long
  InternalHigh As Long
  offset As Long
  OffsetHigh As Long
  hevent As Long
End Type

Public Const FILE_BEGIN = 0
Public Const FILE_CURRENT = 1
Public Const FILE_END = 2

Public Const PAGE_READONLY = &H2&
Public Const PAGE_READWRITE = &H4&
Public Const PAGE_WRITECOPY = &H8&

Public Const SECTION_QUERY = &H1
Public Const SECTION_MAP_WRITE = &H2
Public Const SECTION_MAP_READ = &H4
Public Const SECTION_MAP_EXECUTE = &H8
Public Const SECTION_EXTEND_SIZE = &H10
Public Const SECTION_ALL_ACCESS = STANDARD_RIGHTS_REQUIRED Or _
  SECTION_QUERY Or SECTION_MAP_WRITE Or SECTION_MAP_READ Or _
  SECTION_MAP_EXECUTE Or SECTION_EXTEND_SIZE

Public Const FILE_MAP_ALL_ACCESS = SECTION_ALL_ACCESS
Public Const FILE_MAP_COPY = SECTION_QUERY
Public Const FILE_MAP_READ = SECTION_MAP_READ
Public Const FILE_MAP_WRITE = SECTION_MAP_WRITE


Public Type InputType
  dwType As Long
  rgdw(5) As Long
End Type

Public Const INPUT_MOUSE = 0
Public Const INPUT_KEYBOARD = 1
Public Const INPUT_HARDWARE = 2

Public Type MouseInputType
  dwType As Long
  dx As Long
  dy As Long
  mousedata As Long
  dwFlags As Long
  time As Long
  dwExtraInfo As Long
End Type

Public Const MOUSEEVENTF_ABSOLUTE = &H8000 '  absolute move
Public Const MOUSEEVENTF_LEFTDOWN = &H2 '  left button down
Public Const MOUSEEVENTF_LEFTUP = &H4 '  left button up
Public Const MOUSEEVENTF_MIDDLEDOWN = &H20 '  middle button down
Public Const MOUSEEVENTF_MIDDLEUP = &H40 '  middle button up
Public Const MOUSEEVENTF_MOVE = &H1 '  mouse move
Public Const MOUSEEVENTF_RIGHTDOWN = &H8 '  right button down
Public Const MOUSEEVENTF_RIGHTUP = &H10 '  right button up

Public Type KeybdInputType
  dwType As Long
  wVk As Integer
  wScan As Integer
  dwFlags As Long
  time As Long
  dwExtraInfo As Long
End Type

Public Const KEYEVENTF_EXTENDEDKEY = &H1
Public Const KEYEVENTF_KEYUP = &H2




Public Const NORMAL_PRIORITY_CLASS = &H20
Public Const IDLE_PRIORITY_CLASS = &H40
Public Const HIGH_PRIORITY_CLASS = &H80
Public Const REALTIME_PRIORITY_CLASS = &H100

Public Const THREAD_PRIORITY_IDLE = -15
Public Const THREAD_PRIORITY_LOWEST = -2
Public Const THREAD_PRIORITY_BELOW_NORMAL = -1
Public Const THREAD_PRIORITY_NORMAL = 0
Public Const THREAD_PRIORITY_ABOVE_NORMAL = 1
Public Const THREAD_PRIORITY_HIGHEST = 2
Public Const THREAD_PRIORITY_TIME_CRITICAL = 15



Public Type VS_FIXEDFILEINFO
  dwSignature As Long
  dwStrucVersion As Long   '
  dwFileVersionMS As Long  '
  dwFileVersionLS As Long  '
  dwProductVersionMS As Long   '
  dwProductVersionLS As Long   '
  dwFileFlagsMask As Long  '
  dwFileFlags As Long    '
  dwFileOS As Long     '
  dwFileType As Long     '
  dwFileSubtype As Long    '
  dwFileDateMS As Long     '
  dwFileDateLS As Long     '
End Type

Public Type TIME_ZONE_INFORMATION
  Bias As Long
  StandardName(32) As Integer
  StandardDate As SYSTEMTIME
  StandardBias As Long
  DaylightName(32) As Integer
  DaylightDate As SYSTEMTIME
  DaylightBias As Long
End Type

'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1  Biblioteka1.0   2007-04-18 15:59:40  Darko Kolakovic
'$
'*******************************************************************************
