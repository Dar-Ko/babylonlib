Attribute VB_Name = "KWinKernel32"
'$Workfile: KWinKernel32.bas$: implementation file
'$Revision: 6$ $Date: 2007-05-08 10:14:47$
'$Author: Darko Kolakovic$
'
'MS Windows kernel32 DLL
'2004-06-11
Option Explicit

'wtypes.h
Public Type ULARGE_INTEGER
  dwLow As Long
  dwHigh As Long
End Type

Public Type SECURITY_ATTRIBUTES
  nLength As Long
  lpSecurityDescriptor As Long
  bInheritHandle As Long
End Type

'winbase.h
Public Const INVALID_HANDLE_VALUE = &HFFFFFFFF


Public Type OVER_LAPPED
  Internal As Long
  InternalHigh As Long
  Offset As Long
  OffsetHigh As Long
  hEvent As Long
End Type

Public Type GUID
  Data1 As Long
  Data2 As Integer
  Data3 As Integer
  Data4(7) As Byte
End Type


Public Const EVENT_ALL_ACCESS = (STANDARD_RIGHTS_REQUIRED Or SYNCHRONIZE Or &H3&)
Public Const EVENT_MODIFY_STATE = &H2&
Public Const MUTEX_QUERY_STATE = &H1&
Public Const MUTEX_ALL_ACCESS = (STANDARD_RIGHTS_REQUIRED Or SYNCHRONIZE Or MUTEX_QUERY_STATE)

Public Const OPEN_EXISTING = 3

Public Const FORMAT_MESSAGE_FROM_SYSTEM = &H1000
Public Const GENERIC_READ = &H80000000
Public Const GENERIC_WRITE = &H40000000

Public Const GENERIC_NOACCESS = 0

Public Const FILE_SHARE_READ = &H1
Public Const FILE_SHARE_WRITE = &H2
Public Const FILE_FLAG_OVERLAPPED = &H40000000

Public Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Public Declare Function CompareFileTime Lib "kernel32" (lpFileTime1 As FILETIME, lpFileTime2 As FILETIME) As Long
Public Declare Function ConnectNamedPipe Lib "kernel32" (ByVal hNamedPipe As Long, ByVal lpOverlapped As Long) As Long
Public Declare Function CopyFile Lib "kernel32" Alias "CopyFileA" (ByVal lpExistingFileName As String, ByVal lpNewFileName As String, ByVal bFailIfExists As Long) As Long
Public Declare Function CreateDirectory Lib "kernel32" Alias "CreateDirectoryA" (ByVal lpPathName As String, lpSecurityAttributes As SECURITY_ATTRIBUTES) As Long
Public Declare Function CreateEvent Lib "kernel32" Alias "CreateEventA" (ByVal lpEventAttributes As Long, ByVal bManualReset As Long, ByVal bInitialState As Long, ByVal lpName As String) As Long
Public Declare Function CreateFile Lib "kernel32" Alias "CreateFileA" (ByVal lpFileName As String, ByVal dwDesiredAccess As Long, ByVal dwShareMode As Long, ByVal lpSecurityAttributes As SECURITY_ATTRIBUTES, ByVal dwCreationDisposition As Long, ByVal dwFlagsAndAttributes As Long, ByVal hTemplateFile As Long) As Long
Public Declare Function CreateFileMapping Lib "kernel32" Alias "CreateFileMappingA" (ByVal hFile As Long, ByVal lpFileMappingAttributes As Long, ByVal flProtect As Long, ByVal dwMaximumSizeHigh As Long, ByVal dwMaximumSizeLow As Long, ByVal lpName As String) As Long
Public Declare Function CreateMutex Lib "kernel32" Alias "CreateMutexA" (ByVal lpMutexAttributes As Long, ByVal bInitialOwner As Long, ByVal lpName As String) As Long
Public Declare Function CreateNamedPipe Lib "kernel32" Alias "CreateNamedPipeA" (ByVal lpName As String, ByVal dwOpenMode As Long, ByVal dwPipeMode As Long, ByVal nMaxInstances As Long, ByVal nOutBufferSize As Long, ByVal nInBufferSize As Long, ByVal nDefaultTimeOut As Long, ByVal lpSecurityAttributes As Long) As Long
Public Declare Function CreateProcess Lib "kernel32" Alias "CreateProcessA" (ByVal lpApplicationName As String, ByVal lpCommandLine As String, lpProcessAttributes As Long, lpThreadAttributes As Long, ByVal bInheritHandles As Long, ByVal dwCreationFlags As Long, lpEnvironment As Any, ByVal lpCurrentDriectory As String, lpStartupInfo As STARTUPINFO, lpProcessInformation As PROCESS_INFORMATION) As Long
Public Declare Function CreateToolhelpSnapshot Lib "kernel32" Alias "CreateToolhelp32Snapshot" (ByVal lFlags As Long, ByVal lProcessid As Long) As Long
Public Declare Function DeleteFile Lib "kernel32" Alias "DeleteFileA" (ByVal lpFileName As String) As Long
Public Declare Function DisconnectNamedPipe Lib "kernel32" (ByVal hNamedPipe As Long) As Long
Public Declare Function FileTimeToLocalFileTime Lib "kernel32" (lpFileTime As FILETIME, lpLocalFileTime As FILETIME) As Long
Public Declare Function FileTimeToSystemTime Lib "kernel32" (lpFileTime As FILETIME, lpSystemTime As SYSTEMTIME) As Long
Public Declare Function FindClose Lib "kernel32" (ByVal hFindFile As Long) As Long
Public Declare Function FindFirstChangeNotification Lib "kernel32" Alias "FindFirstChangeNotificationA" (ByVal lpPathName As String, ByVal bWatchSubtree As Long, ByVal dwNotifyFilter As Long) As Long
Public Declare Function FindFirstFile Lib "kernel32" Alias "FindFirstFileA" (ByVal lpFileName As String, lpFindFileData As WIN32_FIND_DATA) As Long
Public Declare Function FindNextChangeNotification Lib "kernel32" (ByVal hChangeHandle As Long) As Long
Public Declare Function FindNextFile Lib "kernel32" Alias "FindNextFileA" (ByVal hFindFile As Long, lpFindFileData As WIN32_FIND_DATA) As Long
Public Declare Function FreeLibrary Lib "kernel32" (ByVal hLibModule As Long) As Long
Public Declare Function GetComputerName Lib "kernel32" Alias "GetComputerNameA" (ByVal lpBuffer As String, nSize As Long) As Long
Public Declare Function GetCurrentProcess Lib "kernel32" () As Long
Public Declare Function GetCurrentProcessId Lib "kernel32" () As Long
Public Declare Function GetCurrentThread Lib "kernel32" () As Long
Public Declare Function GetCurrentThreadId Lib "kernel32" () As Long
Public Declare Function GetDiskFreeSpace Lib "kernel32" Alias "GetDiskFreeSpaceA" (ByVal RootPathName As String, SectorsPerCluster As Long, BytesPerSector As Long, NumberOfFreeClusters As Long, TotalNumberOfClusters As Long) As Long
Public Declare Function GetDiskFreeSpaceEx Lib "kernel32" Alias "GetDiskFreeSpaceExA" (ByVal lpDirectoryName As String, ByRef lpFreeBytesAvailableToCaller As ULARGE_INTEGER, ByRef lpTotalNumberOfBytes As ULARGE_INTEGER, ByRef lpTotalNumberOfFreeBytes As ULARGE_INTEGER) As Long
Public Declare Function GetEnvironmentVariable Lib "kernel32.dll" Alias "GetEnvironmentVariableA" (ByVal lpName As String, ByVal lpBuffer As String, ByVal nSize As Long) As Long
Public Declare Function GetExitCodeThread Lib "kernel32" (ByVal hThread As Long, lpExitCode As Long) As Long
Public Declare Function GetFileAttributes Lib "kernel32" Alias "GetFileAttributesA" (ByVal lpFileName As String) As Long
Public Declare Function GetFileTime Lib "kernel32" (ByVal hFile As Long, lpCreationTime As FILETIME, lpLastAccessTime As FILETIME, lpLastWriteTime As FILETIME) As Long
Public Declare Function GetFullPathName Lib "kernel32" Alias "GetFullPathNameA" (ByVal lpFileName As String, ByVal nBufferLength As Long, ByVal lpBuffer As String, lpFilePart As Long) As Long
Public Declare Function GetLastError Lib "kernel32" () As Long
Public Declare Function GetPriorityClass Lib "kernel32" (ByVal hprocess As Long) As Long
Public Declare Function GetPrivateProfileInt Lib "kernel32" Alias "GetPrivateProfileIntA" (ByVal lpSectionName As String, ByVal lpKeyName As Any, ByVal nDefault As Long, ByVal lpFileName As String) As Long
Public Declare Function GetPrivateProfileSection Lib "kernel32" Alias "GetPrivateProfileSectionA" (ByVal lpSectionName As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public Declare Function GetPrivateProfileSectionNames Lib "kernel32" Alias "GetPrivateProfileSectionNamesA" (ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpSectionName As String, ByVal lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Public Declare Function GetPrivateProfileStruct Lib "kernel32" Alias "GetPrivateProfileStructA" (ByVal lpszSection As String, ByVal lpszKey As Any, ByVal lpStruct As Long, ByVal uSizeStruct As Long, ByVal szFile As String) As Boolean
Public Declare Function GetTempFileName Lib "kernel32" Alias "GetTempFileNameA" (ByVal lpszPath As String, ByVal lpPrefixString As String, ByVal wUnique As Long, ByVal lpTempFileName As String) As Long
Public Declare Function GetTempPath Lib "kernel32" Alias "GetTempPathA" (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long
Public Declare Function GetThreadPriority Lib "kernel32" (ByVal hThread As Long) As Long
Public Declare Function GetTickCount Lib "kernel32" () As Long
Public Declare Function GetTimeZoneInformation Lib "kernel32" (lpTimeZoneInformation As TIME_ZONE_INFORMATION) As Long
Public Declare Function GetVersionEx Lib "kernel32" Alias "GetVersionExA" (lpVersionInformation As OSVERSIONINFO) As Long
Public Declare Function GlobalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long
Public Declare Function GlobalFree Lib "kernel32" (ByVal hMem As Long) As Long
Public Declare Function IsBadReadPtr Lib "kernel32" (ByVal lp As Long, ByVal ucb As Long) As Long
Public Declare Function LoadLibrary Lib "kernel32" Alias "LoadLibraryA" (ByVal lpLibFileName As String) As Long
Public Declare Function LocalFileTimeToFileTime Lib "kernel32" (lpLocalFileTime As FILETIME, lpFileTime As FILETIME) As Long
Public Declare Function lStrCat Lib "kernel32" Alias "lstrcatA" (ByVal lpString1 As String, ByVal lpString2 As String) As Long
Public Declare Function lstrcpyW Lib "kernel32" (lpString1 As Byte, ByVal lpString2 As Long) As Long
Public Declare Function lstrlenW Lib "kernel32" (ByVal lpString As Long) As Long
Public Declare Function MapViewOfFile Lib "kernel32" (ByVal hFileMappingObject As Long, ByVal dwDesiredAccess As Long, ByVal dwFileOffsetHigh As Long, ByVal dwFileOffsetLow As Long, ByVal dwNumberOfBytesToMap As Long) As Long
Public Declare Function MoveFile Lib "kernel32" Alias "MoveFileA" (ByVal lpExistingFileName As String, ByVal lpNewFileName As String) As Long
Public Declare Function MoveFileEx Lib "kernel32" Alias "MoveFileExA" (ByVal lpExistingFileName As String, ByVal lpNewFileName As String, ByVal dwFlags As Long) As Long
Public Declare Function OpenEvent Lib "kernel32" Alias "OpenEventA" (ByVal dwDesiredAccess As Long, ByVal bInheritHandle As Long, ByVal lpName As String) As Long
Public Declare Function OpenFileMapping Lib "kernel32" Alias "OpenFileMappingA" (ByVal dwDesiredAccess As Long, ByVal bInheritHandle As Long, ByVal lpName As String) As Long
Public Declare Function OpenMutex Lib "kernel32" Alias "OpenMutexA" (ByVal dwDesiredAccess As Long, ByVal bInheritHandle As Long, ByVal lpName As String) As Long
Public Declare Function OpenProcess Lib "kernel32" (ByVal dwDesiredAccess As Long, ByVal bInheritHandle As Long, ByVal dwProcessId As Long) As Long
Public Declare Function PeekNamedPipe Lib "kernel32" (ByVal hNamedPipe As Long, lpBuffer As Any, ByVal nBufferSize As Long, lpBytesRead As Long, lpTotalBytesAvail As Long, lpBytesLeftThisMessage As Long) As Long
Public Declare Function ProcessFirst Lib "kernel32" Alias "Process32First" (ByVal hSnapShot As Long, uProcess As PROCESSENTRY32) As Long
Public Declare Function ProcessNext Lib "kernel32" Alias "Process32Next" (ByVal hSnapShot As Long, uProcess As PROCESSENTRY32) As Long
Public Declare Function ReadFile Lib "kernel32" (ByVal hFile As Long, lpBuffer As Any, ByVal cb As Long, lpNumberOfBytesRead As Long, ByVal lpOverlapped As Long) As Long
Public Declare Function ReadProcessMemory Lib "kernel32" (ByVal hprocess As Long, ByVal lpBaseAddress As Long, lpBuffer As Any, ByVal nSize As Long, lpNumberOfBytesWritten As Long) As Long
Public Declare Function ReleaseMutex Lib "kernel32" (ByVal hmutex As Long) As Long
Public Declare Function ResetEvent Lib "kernel32" (ByVal hEvent As Long) As Long
Public Declare Function SendMessageTimeout Lib "user32" Alias "SendMessageTimeoutA" (ByVal hwnd As Long, ByVal msg As Long, ByVal wparam As Long, ByVal lparam As Long, ByVal fuFlags As Long, ByVal uTimeout As Long, pdwResult As Long) As Long
Public Declare Function SetCurrentDirectory Lib "kernel32" Alias "SetCurrentDirectoryA" (ByVal lpPathName As String) As Long
Public Declare Function SetEndOfFile Lib "kernel32" (ByVal hFile As Long) As Long
Public Declare Function SetEnvironmentVariable Lib "kernel32.dll" Alias "SetEnvironmentVariableA" (ByVal lpName As String, ByVal lpValue As String) As Long
Public Declare Function SetEvent Lib "kernel32" (ByVal hevent As Long) As Long
Public Declare Function SetFilePointer Lib "kernel32" (ByVal hFile As Long, ByVal lDistanceToMove As Long, lpDistanceToMoveHigh As Long, ByVal dwMoveMethod As Long) As Long
Public Declare Function SetNamedPipeHandleState Lib "kernel32" (ByVal hNamedPipe As Long, lpMode As Long, lpMaxCollectionCount As Long, lpCollectDataTimeout As Long) As Long
Public Declare Function SetPriorityClass Lib "kernel32" (ByVal hprocess As Long, ByVal dwPriorityClass As Long) As Long
Public Declare Function SetThreadPriority Lib "kernel32" (ByVal hThread As Long, ByVal nPriority As Long) As Long
Public Declare Function SystemTimeToFileTime Lib "kernel32" (lpSystemTime As SYSTEMTIME, lpFileTime As FILETIME) As Long
Public Declare Function TerminateProcess Lib "kernel32" (ByVal hprocess As Long, ByVal uExitCode As Long) As Long
Public Declare Function UnmapViewOfFile Lib "kernel32" (ByVal lpBaseAddress As Long) As Long
Public Declare Function VirtualQueryEx Lib "kernel32" (ByVal hprocess As Long, ByVal lpAddress As Long, lpBuffer As MEMORY_BASIC_INFORMATION, ByVal dwLength As Long) As Long
Public Declare Function WaitForSingleObject Lib "kernel32" (ByVal hHandle As Long, ByVal dwMilliseconds As Long) As Long
Public Declare Function WriteFile Lib "kernel32" (ByVal hFile As Long, lpBuffer As Any, ByVal cb As Long, lpNumberOfBytesWritten As Long, ByVal lpOverlapped As Long) As Long
Public Declare Function WritePrivateProfileSection Lib "kernel32" Alias "WritePrivateProfileSectionA" (ByVal lpSectionName As String, ByVal lpString As String, ByVal lpFileName As String) As Long
Public Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpSectionName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal lpFileName As String) As Long
Public Declare Function WriteProcessMemory Lib "kernel32" (ByVal hprocess As Long, ByVal lpBaseAddress As Long, lpBuffer As Any, ByVal nSize As Long, lpNumberOfBytesWritten As Long) As Long
Public Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal cb As Long)
Public Declare Sub CopyPv Lib "kernel32" Alias "RtlMoveMemory" (ByVal pvDst As Long, ByVal pvSource As Long, ByVal cb As Long)
Public Declare Sub CopySzFromPv Lib "kernel32" Alias "RtlMoveMemory" (ByVal szDst As String, ByVal pvSource As Long, ByVal cb As Long)
Public Declare Sub FillMemory Lib "kernel32" Alias "RtlFillMemory" (dest As Any, ByVal cb As Long, ByVal bFill As Long)
Public Declare Sub GetSystemTime Lib "kernel32" (ByRef lpSystemTime As SYSTEMTIME)
Public Declare Sub GetSystemTimeAsFileTime Lib "kernel32" (lpFileTime As FILETIME)
Public Declare Sub OutputDebugString Lib "kernel32" Alias "OutputDebugStringA" (ByVal lpOutputString As String)
Public Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)
Public Declare Sub ZeroMemory Lib "kernel32" Alias "RtlZeroMemory" (dest As Any, ByVal cb As Long)
Public Declare Function GetOverlappedResult _
  Lib "kernel32" _
  (ByVal hFile As Long, _
  ByRef lpOverlapped As OVER_LAPPED, _
  ByRef lpNumberOfBytesRead As Long, _
  ByVal bWait As Long) _
  As Long
Public Declare Function CancelIo _
  Lib "kernel32" _
  (ByVal hFile As Long) _
  As Long
Public Declare Function lstrlen _
  Lib "kernel32" _
  Alias "lstrlenA" _
  (ByVal source As Long) _
  As Long
Public Declare Function lstrcpy _
  Lib "kernel32" _
  Alias "lstrcpyA" _
  (ByVal dest As String, _
  ByVal source As Long) _
  As String

Public Declare Function FormatMessage _
  Lib "kernel32" _
  Alias "FormatMessageA" _
  (ByVal dwFlags As Long, _
  ByRef lpSource As Any, _
  ByVal dwMessageId As Long, _
  ByVal dwLanguageZId As Long, _
  ByVal lpBuffer As String, _
  ByVal nSize As Long, _
  ByVal Arguments As Long) _
  As Long


'///////////////////////////////////////////////////////////////////////////////
'*******************************************************************************
'$Log:
' 1 Biblioteka1.0 2007-04-20 14:03:00 Darko Kolakovic
'$
'*******************************************************************************

