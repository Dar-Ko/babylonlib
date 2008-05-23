Attribute VB_Name = "KWinError"
'$Workfile: KWinError.bas$: implementation file
'$Revision: 2$ $Date: 2007-05-11 17:28:23$
'$Author: Darko Kolakovic$
'
'WinError.h error code definitions for the Win32 API functions
'2004-06-11
Option Explicit

'-------------------------------------------------------------------------------
' [Error Codes] WinError.h

'Values are 32 bit values layed out as follows:
' 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
' 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
'+---+-+-+-----------------------+-------------------------------+
'|Sev|C|R|     Facility          |               Code            |
'+---+-+-+-----------------------+-------------------------------+
'where
'    Sev - is the severity code
'        00 - Success
'        01 - Informational
'        10 - Warning
'        11 - Error
'    C - is the Customer code flag
'    R - is a reserved bit
'    Facility - is the facility code
'    Code - is the facility's status code

'Define the facility codes
Public Const FACILITY_WINDOWS_CE = 24
Public Const FACILITY_WINDOWS = 8
Public Const FACILITY_URT = 19
Public Const FACILITY_UMI = 22
Public Const FACILITY_SXS = 23
Public Const FACILITY_STORAGE = 3
Public Const FACILITY_STATE_MANAGEMENT = 34
Public Const FACILITY_SSPI = 9
Public Const FACILITY_SCARD = 16
Public Const FACILITY_SETUPAPI = 15
Public Const FACILITY_SECURITY = 9
Public Const FACILITY_RPC = 1
Public Const FACILITY_WIN32 = 7
Public Const FACILITY_CONTROL = 10
Public Const FACILITY_NULL = 0
Public Const FACILITY_METADIRECTORY = 35
Public Const FACILITY_MSMQ = 14
Public Const FACILITY_MEDIASERVER = 13
Public Const FACILITY_INTERNET = 12
Public Const FACILITY_ITF = 4
Public Const FACILITY_HTTP = 25
Public Const FACILITY_DPLAY = 21
Public Const FACILITY_DISPATCH = 2
Public Const FACILITY_CONFIGURATION = 33
Public Const FACILITY_COMPLUS = 17
Public Const FACILITY_CERT = 11
Public Const FACILITY_BACKGROUNDCOPY = 32
Public Const FACILITY_ACS = 20
Public Const FACILITY_AAF = 18

'------------------------------------------------------------------------------
'Define the severity codes

'The operation completed successfully.
Public Const ERROR_SUCCESS = 0

Public Const NO_ERROR = 0                             'dderror
Public Const SEC_E_OK = &H0
'Incorrect function.
Public Const ERROR_INVALID_FUNCTION = 1              'dderror
'The system cannot find the file specified.
Public Const ERROR_FILE_NOT_FOUND = 2
'The system cannot find the path specified.
Public Const ERROR_PATH_NOT_FOUND = 3
'The system cannot open the file.
Public Const ERROR_TOO_MANY_OPEN_FILES = 4
'Access is denied.
Public Const ERROR_ACCESS_DENIED = 5
'The handle is invalid.
Public Const ERROR_INVALID_HANDLE = 6
'The storage control blocks were destroyed.
Public Const ERROR_ARENA_TRASHED = 7
'Not enough storage is available to process this command.
Public Const ERROR_NOT_ENOUGH_MEMORY = 8          'dderror
'The storage control block address is invalid.
Public Const ERROR_INVALID_BLOCK = 9
'The environment is incorrect.
Public Const ERROR_BAD_ENVIRONMENT = 10
'An attempt was made to load a program with an incorrect format.
Public Const ERROR_BAD_FORMAT = 11
'The access code is invalid.
Public Const ERROR_INVALID_ACCESS = 12
'The data is invalid.
Public Const ERROR_INVALID_DATA = 13
'Not enough storage is available to complete this operation.
Public Const ERROR_OUTOFMEMORY = 14
'The system cannot find the drive specified.
Public Const ERROR_INVALID_DRIVE = 15
'The directory cannot be removed.
Public Const ERROR_CURRENT_DIRECTORY = 16
'The system cannot move the file to a different disk drive.
Public Const ERROR_NOT_SAME_DEVICE = 17
'There are no more files.
Public Const ERROR_NO_MORE_FILES = 18
'The media is write protected.
Public Const ERROR_WRITE_PROTECT = 19
'The system cannot find the device specified.
Public Const ERROR_BAD_UNIT = 20
'The device is not ready.
Public Const ERROR_NOT_READY = 21
'The device does not recognize the command.
Public Const ERROR_BAD_COMMAND = 22
'Data error (cyclic redundancy check).
Public Const ERROR_CRC = 23
'The program issued a command but the command length is incorrect.
Public Const ERROR_BAD_LENGTH = 24
'The drive cannot locate a specific area or track on the disk.
Public Const ERROR_SEEK = 25
'The specified disk or diskette cannot be accessed.
Public Const ERROR_NOT_DOS_DISK = 26
'The drive cannot find the sector requested.
Public Const ERROR_SECTOR_NOT_FOUND = 27
'The printer is out of paper.
Public Const ERROR_OUT_OF_PAPER = 28
'The system cannot write to the specified device.
Public Const ERROR_WRITE_FAULT = 29
'The system cannot read from the specified device.
Public Const ERROR_READ_FAULT = 30
'A device attached to the system is not functioning.
Public Const ERROR_GEN_FAILURE = 31
'The process cannot access the file because it is being used by another process.
Public Const ERROR_SHARING_VIOLATION = 32
'The process cannot access the file because another process has locked a
'portion of the file.
Public Const ERROR_LOCK_VIOLATION = 33
'The wrong diskette is in the drive.
'Insert %2 (Volume Serial Number: %3) into drive %1.
Public Const ERROR_WRONG_DISK = 34
'Too many files opened for sharing.
Public Const ERROR_SHARING_BUFFER_EXCEEDED = 36
'Reached the end of the file.
Public Const ERROR_HANDLE_EOF = 38
'The disk is full.
Public Const ERROR_HANDLE_DISK_FULL = 39
'The request is not supported.
Public Const ERROR_NOT_SUPPORTED = 50
'Windows cannot find the network path. Verify that the network path is correct
'and the destination computer is not busy or turned off. If Windows still
'cannot find the network path, contact your network administrator.
Public Const ERROR_REM_NOT_LIST = 51
'You were not connected because a duplicate name exists on the network.
'Go to System in Control Panel to change the computer name and try again.
Public Const ERROR_DUP_NAME = 52
'The network path was not found.
Public Const ERROR_BAD_NETPATH = 53
'The network is busy.
Public Const ERROR_NETWORK_BUSY = 54
'The specified network resource or device is no longer available.
Public Const ERROR_DEV_NOT_EXIST = 55              'dderror
'The network BIOS command limit has been reached.
Public Const ERROR_TOO_MANY_CMDS = 56
'A network adapter hardware error occurred.
Public Const ERROR_ADAP_HDW_ERR = 57
'The specified server cannot perform the requested operation.
Public Const ERROR_BAD_NET_RESP = 58
'An unexpected network error occurred.
Public Const ERROR_UNEXP_NET_ERR = 59
'The remote adapter is not compatible.
Public Const ERROR_BAD_REM_ADAP = 60
'The printer queue is full.
Public Const ERROR_PRINTQ_FULL = 61
'Space to store the file waiting to be printed is not available on the server.
Public Const ERROR_NO_SPOOL_SPACE = 62
'Your file waiting to be printed was deleted.
Public Const ERROR_PRINT_CANCELLED = 63
'The specified network name is no longer available.
Public Const ERROR_NETNAME_DELETED = 64
'Network access is denied.
Public Const ERROR_NETWORK_ACCESS_DENIED = 65
'The network resource type is not correct.
Public Const ERROR_BAD_DEV_TYPE = 66
'The network name cannot be found.
Public Const ERROR_BAD_NET_NAME = 67
'The name limit for the local computer network adapter card was exceeded.
Public Const ERROR_TOO_MANY_NAMES = 68
'The network BIOS session limit was exceeded.
Public Const ERROR_TOO_MANY_SESS = 69
'The remote server has been paused or is in the process of being started.
Public Const ERROR_SHARING_PAUSED = 70
'No more connections can be made to this remote computer at this time because
'there are already as many connections as the computer can accept.
Public Const ERROR_REQ_NOT_ACCEP = 71
'The specified printer or disk device has been paused.
Public Const ERROR_REDIR_PAUSED = 72
'The file exists.
Public Const ERROR_FILE_EXISTS = 80
'The directory or file cannot be created.
Public Const ERROR_CANNOT_MAKE = 82
'Fail on INT 24.
Public Const ERROR_FAIL_I24 = 83
'Storage to process this request is not available.
Public Const ERROR_OUT_OF_STRUCTURES = 84
'The local device name is already in use.
Public Const ERROR_ALREADY_ASSIGNED = 85
'The specified network password is not correct.
Public Const ERROR_INVALID_PASSWORD = 86
'The parameter is incorrect.
Public Const ERROR_INVALID_PARAMETER = 87          'dderror
'A write fault occurred on the network.
Public Const ERROR_NET_WRITE_FAULT = 88
'The system cannot start another process at this time.
Public Const ERROR_NO_PROC_SLOTS = 89
'Cannot create another system semaphore.
Public Const ERROR_TOO_MANY_SEMAPHORES = 100
'The exclusive semaphore is owned by another process.
Public Const ERROR_EXCL_SEM_ALREADY_OWNED = 101
'The semaphore is set and cannot be closed.
Public Const ERROR_SEM_IS_SET = 102
'The semaphore cannot be set again.
Public Const ERROR_TOO_MANY_SEM_REQUESTS = 103
'Cannot request exclusive semaphores at interrupt time.
Public Const ERROR_INVALID_AT_INTERRUPT_TIME = 104
'The previous ownership of this semaphore has ended.
Public Const ERROR_SEM_OWNER_DIED = 105
'Insert the diskette for drive %1.
Public Const ERROR_SEM_USER_LIMIT = 106
'The program stopped because an alternate diskette was not inserted.
Public Const ERROR_DISK_CHANGE = 107
'The disk is in use or locked by another process.
Public Const ERROR_DRIVE_LOCKED = 108
'The pipe has been ended.
Public Const ERROR_BROKEN_PIPE = 109
'The system cannot open the device or file specified.
Public Const ERROR_OPEN_FAILED = 110
'The file name is too long.
Public Const ERROR_BUFFER_OVERFLOW = 111
'There is not enough space on the disk.
Public Const ERROR_DISK_FULL = 112
'No more internal file identifiers available.
Public Const ERROR_NO_MORE_SEARCH_HANDLES = 113
'The target internal file identifier is incorrect.
Public Const ERROR_INVALID_TARGET_HANDLE = 114
'The IOCTL call made by the application program is not correct.
Public Const ERROR_INVALID_CATEGORY = 117
'The verify-on-write switch parameter value is not correct.
Public Const ERROR_INVALID_VERIFY_SWITCH = 118
'The system does not support the command requested.
Public Const ERROR_BAD_DRIVER_LEVEL = 119
'This function is not supported on this system.
Public Const ERROR_CALL_NOT_IMPLEMENTED = 120
'The semaphore timeout period has expired.
Public Const ERROR_SEM_TIMEOUT = 121
'The data area passed to a system call is too small.
Public Const ERROR_INSUFFICIENT_BUFFER = 122        'dderror
'The filename, directory name, or volume label syntax is incorrect.
Public Const ERROR_INVALID_NAME = 123               'dderror
'The system call level is not correct.
Public Const ERROR_INVALID_LEVEL = 124
'The disk has no volume label.
Public Const ERROR_NO_VOLUME_LABEL = 125
'The specified module could not be found.
Public Const ERROR_MOD_NOT_FOUND = 126
'The specified procedure could not be found.
Public Const ERROR_PROC_NOT_FOUND = 127
'There are no child processes to wait for.
Public Const ERROR_WAIT_NO_CHILDREN = 128
'The %1 application cannot be run in Win32 mode.
Public Const ERROR_CHILD_NOT_COMPLETE = 129
'Attempt to use a file handle to an open disk partition for an operation other
'than raw disk I/O.
Public Const ERROR_DIRECT_ACCESS_HANDLE = 130
'An attempt was made to move the file pointer before the beginning of the file.
Public Const ERROR_NEGATIVE_SEEK = 131
'The file pointer cannot be set on the specified device or file.
Public Const ERROR_SEEK_ON_DEVICE = 132
'A JOIN or SUBST command cannot be used for a drive that contains previously
'joined drives.
Public Const ERROR_IS_JOIN_TARGET = 133
'An attempt was made to use a JOIN or SUBST command on a drive that has already
'been joined.
Public Const ERROR_IS_JOINED = 134
'An attempt was made to use a JOIN or SUBST command on a drive that has already
'been substituted.
Public Const ERROR_IS_SUBSTED = 135
'The system tried to delete the JOIN of a drive that is not joined.
Public Const ERROR_NOT_JOINED = 136
'The system tried to delete the substitution of a drive that is not substituted.
Public Const ERROR_NOT_SUBSTED = 137
'The system tried to join a drive to a directory on a joined drive.
Public Const ERROR_JOIN_TO_JOIN = 138
'The system tried to substitute a drive to a directory on a substituted drive.
Public Const ERROR_SUBST_TO_SUBST = 139
'The system tried to join a drive to a directory on a substituted drive.
Public Const ERROR_JOIN_TO_SUBST = 140
'The system tried to SUBST a drive to a directory on a joined drive.
Public Const ERROR_SUBST_TO_JOIN = 141
'The system cannot perform a JOIN or SUBST at this time.
Public Const ERROR_BUSY_DRIVE = 142
'The system cannot join or substitute a drive to or for a directory on the same
'drive.
Public Const ERROR_SAME_DRIVE = 143
'The directory is not a subdirectory of the root directory.
Public Const ERROR_DIR_NOT_ROOT = 144
'The directory is not empty.
Public Const ERROR_DIR_NOT_EMPTY = 145
'The path specified is being used in a substitute.
Public Const ERROR_IS_SUBST_PATH = 146
'Not enough resources are available to process this command.
Public Const ERROR_IS_JOIN_PATH = 147
'The path specified cannot be used at this time.
Public Const ERROR_PATH_BUSY = 148
'An attempt was made to join or substitute a drive for which a directory on
'the drive is the target of a previous substitute.
Public Const ERROR_IS_SUBST_TARGET = 149
'System trace information was not specified in your CONFIG.SYS file,
'or tracing is disallowed.
Public Const ERROR_SYSTEM_TRACE = 150
'The number of specified semaphore events for DosMuxSemWait is not correct.
Public Const ERROR_INVALID_EVENT_COUNT = 151
'DosMuxSemWait did not execute; too many semaphores are already set.
Public Const ERROR_TOO_MANY_MUXWAITERS = 152
'The DosMuxSemWait list is not correct.
Public Const ERROR_INVALID_LIST_FORMAT = 153
'The volume label you entered exceeds the label character limit of the target
'file system.
Public Const ERROR_LABEL_TOO_LONG = 154
'Cannot create another thread.
Public Const ERROR_TOO_MANY_TCBS = 155
'The recipient process has refused the signal.
Public Const ERROR_SIGNAL_REFUSED = 156
'The segment is already discarded and cannot be locked.
Public Const ERROR_DISCARDED = 157
'The segment is already unlocked.
Public Const ERROR_NOT_LOCKED = 158
'The address for the thread ID is not correct.
Public Const ERROR_BAD_THREADID_ADDR = 159
'One or more arguments are not correct.
Public Const ERROR_BAD_ARGUMENTS = 160
'The specified path is invalid.
Public Const ERROR_BAD_PATHNAME = 161
'A signal is already pending.
Public Const ERROR_SIGNAL_PENDING = 162
'No more threads can be created in the system.
Public Const ERROR_MAX_THRDS_REACHED = 164
'Unable to lock a region of a file.
Public Const ERROR_LOCK_FAILED = 167
'The requested resource is in use.
Public Const ERROR_BUSY = 170                       'dderror
'A lock request was not outstanding for the supplied cancel region.
Public Const ERROR_CANCEL_VIOLATION = 173
'The file system does not support atomic changes to the lock type.
Public Const ERROR_ATOMIC_LOCKS_NOT_SUPPORTED = 174
'The system detected a segment number that was not correct.
Public Const ERROR_INVALID_SEGMENT_NUMBER = 180
'The operating system cannot run %1.
Public Const ERROR_INVALID_ORDINAL = 182
'Cannot create a file when that file already exists.
Public Const ERROR_ALREADY_EXISTS = 183
'The flag passed is not correct.
Public Const ERROR_INVALID_FLAG_NUMBER = 186
'The specified system semaphore name was not found.
Public Const ERROR_SEM_NOT_FOUND = 187
'The operating system cannot run %1.
Public Const ERROR_INVALID_STARTING_CODESEG = 188
'The operating system cannot run %1.
Public Const ERROR_INVALID_STACKSEG = 189
'The operating system cannot run %1.
Public Const ERROR_INVALID_MODULETYPE = 190
'Cannot run %1 in Win32 mode.
Public Const ERROR_INVALID_EXE_SIGNATURE = 191
'The operating system cannot run %1.
Public Const ERROR_EXE_MARKED_INVALID = 192
'%1 is not a valid Win32 application.
Public Const ERROR_BAD_EXE_FORMAT = 193
'The operating system cannot run %1.
Public Const ERROR_ITERATED_DATA_EXCEEDS_64k = 194
'The operating system cannot run %1.
Public Const ERROR_INVALID_MINALLOCSIZE = 195
'The operating system cannot run this application program.
Public Const ERROR_DYNLINK_FROM_INVALID_RING = 196
'The operating system is not presently configured to run this application.
Public Const ERROR_IOPL_NOT_ENABLED = 197
'The operating system cannot run %1.
Public Const ERROR_INVALID_SEGDPL = 198
'The operating system cannot run this application program.
Public Const ERROR_AUTODATASEG_EXCEEDS_64k = 199
'The code segment cannot be greater than or equal to 64K.
Public Const ERROR_RING2SEG_MUST_BE_MOVABLE = 200
'The operating system cannot run %1.
Public Const ERROR_RELOC_CHAIN_XEEDS_SEGLIM = 201
'The operating system cannot run %1.
Public Const ERROR_INFLOOP_IN_RELOC_CHAIN = 202
'The system could not find the environment option that was entered.
Public Const ERROR_ENVVAR_NOT_FOUND = 203
'No process in the command subtree has a signal handler.
Public Const ERROR_NO_SIGNAL_SENT = 205
'The filename or extension is too long.
Public Const ERROR_FILENAME_EXCED_RANGE = 206
'The ring 2 stack is in use.
Public Const ERROR_RING2_STACK_IN_USE = 207
'The global filename characters, * or ?, are entered incorrectly or too many
'global filename characters are specified.
Public Const ERROR_META_EXPANSION_TOO_LONG = 208
'The signal being posted is not correct.
Public Const ERROR_INVALID_SIGNAL_NUMBER = 209
'The signal handler cannot be set.
Public Const ERROR_THREAD_1_INACTIVE = 210
'The segment is locked and cannot be reallocated.
Public Const ERROR_LOCKED = 212
'Too many dynamic-link modules are attached to this program or dynamic-link module.
Public Const ERROR_TOO_MANY_MODULES = 214
'Cannot nest calls to LoadModule.
Public Const ERROR_NESTING_NOT_ALLOWED = 215
'The image file %1 is valid, but is for a machine type other than the current
'machine.
Public Const ERROR_EXE_MACHINE_TYPE_MISMATCH = 216
'The image file %1 is signed, unable to modify.
Public Const ERROR_EXE_CANNOT_MODIFY_SIGNED_BINARY = 217
'The image file %1 is strong signed, unable to modify.
Public Const ERROR_EXE_CANNOT_MODIFY_STRONG_SIGNED_BINARY = 218
'The pipe state is invalid.
Public Const ERROR_BAD_PIPE = 230
'All pipe instances are busy.
Public Const ERROR_PIPE_BUSY = 231
'The pipe is being closed.
Public Const ERROR_NO_DATA = 232
'No process is on the other end of the pipe.
Public Const ERROR_PIPE_NOT_CONNECTED = 233
'More data is available.
Public Const ERROR_MORE_DATA = 234                  'dderror
'The session was canceled.
Public Const ERROR_VC_DISCONNECTED = 240
'The specified extended attribute name was invalid.
Public Const ERROR_INVALID_EA_NAME = 254
'The extended attributes are inconsistent.
Public Const ERROR_EA_LIST_INCONSISTENT = 255
'The wait operation timed out.
Public Const WAIT_TIMEOUT = 258                     'dderror
'No more data is available.
Public Const ERROR_NO_MORE_ITEMS = 259
'The copy functions cannot be used.
Public Const ERROR_CANNOT_COPY = 266
'The directory name is invalid.
Public Const ERROR_DIRECTORY = 267
'The extended attributes did not fit in the buffer.
Public Const ERROR_EAS_DIDNT_FIT = 275
'The extended attribute file on the mounted file system is corrupt.
Public Const ERROR_EA_FILE_CORRUPT = 276
'The extended attribute table file is full.
Public Const ERROR_EA_TABLE_FULL = 277
'The specified extended attribute handle is invalid.
Public Const ERROR_INVALID_EA_HANDLE = 278
'The mounted file system does not support extended attributes.
Public Const ERROR_EAS_NOT_SUPPORTED = 282
'Attempt to release mutex not owned by caller.
Public Const ERROR_NOT_OWNER = 288
'Too many posts were made to a semaphore.
Public Const ERROR_TOO_MANY_POSTS = 298
'Only part of a ReadProcessMemory or WriteProcessMemory request was completed.
Public Const ERROR_PARTIAL_COPY = 299
'The oplock request is denied.
Public Const ERROR_OPLOCK_NOT_GRANTED = 300
'An invalid oplock acknowledgment was received by the system.
Public Const ERROR_INVALID_OPLOCK_PROTOCOL = 301
'The volume is too fragmented to complete this operation.
Public Const ERROR_DISK_TOO_FRAGMENTED = 302
'The file cannot be opened because it is in the process of being deleted.
Public Const ERROR_DELETE_PENDING = 303
'The system cannot find message text for message number &H%1 in the message file for %2.
Public Const ERROR_MR_MID_NOT_FOUND = 317
'The scope specified was not found.
Public Const ERROR_SCOPE_NOT_FOUND = 318
'Attempt to access invalid address.
Public Const ERROR_INVALID_ADDRESS = 487
'Arithmetic result exceeded 32 bits.
Public Const ERROR_ARITHMETIC_OVERFLOW = 534
'There is a process on other end of the pipe.
Public Const ERROR_PIPE_CONNECTED = 535
'Waiting for a process to open the other end of the pipe.
Public Const ERROR_PIPE_LISTENING = 536
'Access to the extended attribute was denied.
Public Const ERROR_EA_ACCESS_DENIED = 994
'The I/O operation has been aborted because of either a thread exit or
'an application request.
Public Const ERROR_OPERATION_ABORTED = 995
'Overlapped I/O event is not in a signaled state.
Public Const ERROR_IO_INCOMPLETE = 996
'Overlapped I/O operation is in progress.
Public Const ERROR_IO_PENDING = 997                 'dderror
'Invalid access to memory location.
Public Const ERROR_NOACCESS = 998
'Error performing inpage operation.
Public Const ERROR_SWAPERROR = 999
'Recursion too deep; the stack overflowed.
Public Const ERROR_STACK_OVERFLOW = 1001
'The window cannot act on the sent message.
Public Const ERROR_INVALID_MESSAGE = 1002
'Cannot complete this function.
Public Const ERROR_CAN_NOT_COMPLETE = 1003
'Invalid flags.
Public Const ERROR_INVALID_FLAGS = 1004
'The volume does not contain a recognized file system.
'Please make sure that all required file system drivers are loaded and that
'the volume is not corrupted.
Public Const ERROR_UNRECOGNIZED_VOLUME = 1005
'The volume for a file has been externally altered so that the opened file
'is no longer valid.
Public Const ERROR_FILE_INVALID = 1006
'The requested operation cannot be performed in full-screen mode.
Public Const ERROR_FULLSCREEN_MODE = 1007
'An attempt was made to reference a token that does not exist.
Public Const ERROR_NO_TOKEN = 1008
'The configuration registry database is corrupt.
Public Const ERROR_BADDB = 1009
'The configuration registry key is invalid.
Public Const ERROR_BADKEY = 1010
'The configuration registry key could not be opened.
Public Const ERROR_CANTOPEN = 1011
'The configuration registry key could not be read.
Public Const ERROR_CANTREAD = 1012
'The configuration registry key could not be written.
Public Const ERROR_CANTWRITE = 1013
'One of the files in the registry database had to be recovered by use of a log
'or alternate copy. The recovery was successful.
Public Const ERROR_REGISTRY_RECOVERED = 1014
'The registry is corrupted. The structure of one of the files containing
'registry data is corrupted, or the system's memory image of the file
'is corrupted, or the file could not be recovered because the alternate copy or
'log was absent or corrupted.
Public Const ERROR_REGISTRY_CORRUPT = 1015
'An I/O operation initiated by the registry failed unrecoverably.
'The registry could not read in, or write out, or flush, one of the files
'that contain the system's image of the registry.
Public Const ERROR_REGISTRY_IO_FAILED = 1016
'The system has attempted to load or restore a file into the registry,
'but the specified file is not in a registry file format.
Public Const ERROR_NOT_REGISTRY_FILE = 1017
'Illegal operation attempted on a registry key that has been marked for deletion.
Public Const ERROR_KEY_DELETED = 1018
'System could not allocate the required space in a registry log.
Public Const ERROR_NO_LOG_SPACE = 1019
'Cannot create a symbolic link in a registry key that already has subkeys or
'values.
Public Const ERROR_KEY_HAS_CHILDREN = 1020
'Cannot create a stable subkey under a volatile parent key.
Public Const ERROR_CHILD_MUST_BE_VOLATILE = 1021
'A notify change request is being completed and the information is not being
'returned in the caller's buffer. The caller now needs to enumerate the files
'to find the changes.
Public Const ERROR_NOTIFY_ENUM_DIR = 1022
'A stop control has been sent to a service that other running services are
'dependent on.
Public Const ERROR_DEPENDENT_SERVICES_RUNNING = 1051
'The requested control is not valid for this service.
Public Const ERROR_INVALID_SERVICE_CONTROL = 1052
'The service did not respond to the start or control request in a timely fashion.
Public Const ERROR_SERVICE_REQUEST_TIMEOUT = 1053
'A thread could not be created for the service.
Public Const ERROR_SERVICE_NO_THREAD = 1054
'The service database is locked.
Public Const ERROR_SERVICE_DATABASE_LOCKED = 1055
'An instance of the service is already running.
Public Const ERROR_SERVICE_ALREADY_RUNNING = 1056
'The account name is invalid or does not exist, or the password is invalid for
'the account name specified.
Public Const ERROR_INVALID_SERVICE_ACCOUNT = 1057
'The service cannot be started, either because it is disabled or because it has
'no enabled devices associated with it.
Public Const ERROR_SERVICE_DISABLED = 1058
'Circular service dependency was specified.
Public Const ERROR_CIRCULAR_DEPENDENCY = 1059
'The specified service does not exist as an installed service.
Public Const ERROR_SERVICE_DOES_NOT_EXIST = 1060
'The service cannot accept control messages at this time.
Public Const ERROR_SERVICE_CANNOT_ACCEPT_CTRL = 1061
'The service has not been started.
Public Const ERROR_SERVICE_NOT_ACTIVE = 1062
'The service process could not connect to the service controller.
Public Const ERROR_FAILED_SERVICE_CONTROLLER_CONNECT = 1063
'An exception occurred in the service when handling the control request.
Public Const ERROR_EXCEPTION_IN_SERVICE = 1064
'The database specified does not exist.
Public Const ERROR_DATABASE_DOES_NOT_EXIST = 1065
'The service has returned a service-specific error code.
Public Const ERROR_SERVICE_SPECIFIC_ERROR = 1066
'The process terminated unexpectedly.
Public Const ERROR_PROCESS_ABORTED = 1067
'The dependency service or group failed to start.
Public Const ERROR_SERVICE_DEPENDENCY_FAIL = 1068
'The service did not start due to a logon failure.
Public Const ERROR_SERVICE_LOGON_FAILED = 1069
'After starting, the service hung in a start-pending state.
Public Const ERROR_SERVICE_START_HANG = 1070
'The specified service database lock is invalid.
Public Const ERROR_INVALID_SERVICE_LOCK = 1071
'The specified service has been marked for deletion.
Public Const ERROR_SERVICE_MARKED_FOR_DELETE = 1072
'The specified service already exists.
Public Const ERROR_SERVICE_EXISTS = 1073
'The system is currently running with the last-known-good configuration.
Public Const ERROR_ALREADY_RUNNING_LKG = 1074
'The dependency service does not exist or has been marked for deletion.
Public Const ERROR_SERVICE_DEPENDENCY_DELETED = 1075
'The current boot has already been accepted for use as the last-known-good
'control set.
Public Const ERROR_BOOT_ALREADY_ACCEPTED = 1076
'No attempts to start the service have been made since the last boot.
Public Const ERROR_SERVICE_NEVER_STARTED = 1077
'The name is already in use as either a service name or a service display name.
Public Const ERROR_DUPLICATE_SERVICE_NAME = 1078
'The account specified for this service is different from the account specified
'for other services running in the same process.
Public Const ERROR_DIFFERENT_SERVICE_ACCOUNT = 1079
'Failure actions can only be set for Win32 services, not for drivers.
Public Const ERROR_CANNOT_DETECT_DRIVER_FAILURE = 1080
'This service runs in the same process as the service control manager.
'Therefore, the service control manager cannot take action if this service's
'process terminates unexpectedly.
Public Const ERROR_CANNOT_DETECT_PROCESS_ABORT = 1081
'No recovery program has been configured for this service.
Public Const ERROR_NO_RECOVERY_PROGRAM = 1082
'The executable program that this service is configured to run in does not
'implement the service.
Public Const ERROR_SERVICE_NOT_IN_EXE = 1083
'This service cannot be started in Safe Mode
Public Const ERROR_NOT_SAFEBOOT_SERVICE = 1084
'The physical end of the tape has been reached.
Public Const ERROR_END_OF_MEDIA = 1100
'A tape access reached a filemark.
Public Const ERROR_FILEMARK_DETECTED = 1101
'The beginning of the tape or a partition was encountered.
Public Const ERROR_BEGINNING_OF_MEDIA = 1102
'A tape access reached the end of a set of files.
Public Const ERROR_SETMARK_DETECTED = 1103
'No more data is on the tape.
Public Const ERROR_NO_DATA_DETECTED = 1104
'Tape could not be partitioned.
Public Const ERROR_PARTITION_FAILURE = 1105
'When accessing a new tape of a multivolume partition, the current block size
'is incorrect.
Public Const ERROR_INVALID_BLOCK_LENGTH = 1106
'Tape partition information could not be found when loading a tape.
Public Const ERROR_DEVICE_NOT_PARTITIONED = 1107
'Unable to lock the media eject mechanism.
Public Const ERROR_UNABLE_TO_LOCK_MEDIA = 1108
'Unable to unload the media.
Public Const ERROR_UNABLE_TO_UNLOAD_MEDIA = 1109
'The media in the drive may have changed.
Public Const ERROR_MEDIA_CHANGED = 1110
'The I/O bus was reset.
Public Const ERROR_BUS_RESET = 1111
'No media in drive.
Public Const ERROR_NO_MEDIA_IN_DRIVE = 1112
'No mapping for the Unicode character exists in the target multi-byte code page.
Public Const ERROR_NO_UNICODE_TRANSLATION = 1113
'A dynamic link library (DLL) initialization routine failed.
Public Const ERROR_DLL_INIT_FAILED = 1114
'A system shutdown is in progress.
Public Const ERROR_SHUTDOWN_IN_PROGRESS = 1115
'Unable to abort the system shutdown because no shutdown was in progress.
Public Const ERROR_NO_SHUTDOWN_IN_PROGRESS = 1116
'The request could not be performed because of an I/O device error.
Public Const ERROR_IO_DEVICE = 1117
'No serial device was successfully initialized. The serial driver will unload.
Public Const ERROR_SERIAL_NO_DEVICE = 1118
'Unable to open a device that was sharing an interrupt request (IRQ) with other
'devices. At least one other device that uses that IRQ was already opened.
Public Const ERROR_IRQ_BUSY = 1119
'A serial I/O operation was completed by another write to the serial port.
'(The IOCTL_SERIAL_XOFF_COUNTER reached zero.)
Public Const ERROR_MORE_WRITES = 1120
'A serial I/O operation completed because the timeout period expired.
'(The IOCTL_SERIAL_XOFF_COUNTER did not reach zero.)
Public Const ERROR_COUNTER_TIMEOUT = 1121
'No ID address mark was found on the floppy disk.
Public Const ERROR_FLOPPY_ID_MARK_NOT_FOUND = 1122
'Mismatch between the floppy disk sector ID field and the floppy disk controller
'track address.
Public Const ERROR_FLOPPY_WRONG_CYLINDER = 1123
'The floppy disk controller reported an error that is not recognized by
'the floppy disk driver.
Public Const ERROR_FLOPPY_UNKNOWN_ERROR = 1124
'The floppy disk controller returned inconsistent results in its registers.
Public Const ERROR_FLOPPY_BAD_REGISTERS = 1125
'While accessing the hard disk, a recalibrate operation failed, even after retries.
Public Const ERROR_DISK_RECALIBRATE_FAILED = 1126
'While accessing the hard disk, a disk operation failed even after retries.
Public Const ERROR_DISK_OPERATION_FAILED = 1127
'While accessing the hard disk, a disk controller reset was needed, but even
'that failed.
Public Const ERROR_DISK_RESET_FAILED = 1128
'Physical end of tape encountered.
Public Const ERROR_EOM_OVERFLOW = 1129
'Not enough server storage is available to process this command.
Public Const ERROR_NOT_ENOUGH_SERVER_MEMORY = 1130
'A potential deadlock condition has been detected.
Public Const ERROR_POSSIBLE_DEADLOCK = 1131
'The base address or the file offset specified does not have the proper alignment.
Public Const ERROR_MAPPED_ALIGNMENT = 1132
'An attempt to change the system power state was vetoed by another application
'or driver.
Public Const ERROR_SET_POWER_STATE_VETOED = 1140
'The system BIOS failed an attempt to change the system power state.
Public Const ERROR_SET_POWER_STATE_FAILED = 1141
'An attempt was made to create more links on a file than the file system supports.
Public Const ERROR_TOO_MANY_LINKS = 1142
'The specified program requires a newer version of Windows.
Public Const ERROR_OLD_WIN_VERSION = 1150
'The specified program is not a Windows or MS-DOS program.
Public Const ERROR_APP_WRONG_OS = 1151
'Cannot start more than one instance of the specified program.
Public Const ERROR_SINGLE_INSTANCE_APP = 1152
'The specified program was written for an earlier version of Windows.
Public Const ERROR_RMODE_APP = 1153
'One of the library files needed to run this application is damaged.
Public Const ERROR_INVALID_DLL = 1154
'No application is associated with the specified file for this operation.
Public Const ERROR_NO_ASSOCIATION = 1155
'An error occurred in sending the command to the application.
Public Const ERROR_DDE_FAIL = 1156
'One of the library files needed to run this application cannot be found.
Public Const ERROR_DLL_NOT_FOUND = 1157
'The current process has used all of its system allowance of handles for
'Window Manager objects.
Public Const ERROR_NO_MORE_USER_HANDLES = 1158
'The message can be used only with synchronous operations.
Public Const ERROR_MESSAGE_SYNC_ONLY = 1159
'The indicated source element has no media.
Public Const ERROR_SOURCE_ELEMENT_EMPTY = 1160
'The indicated destination element already contains media.
Public Const ERROR_DESTINATION_ELEMENT_FULL = 1161
'The indicated element does not exist.
Public Const ERROR_ILLEGAL_ELEMENT_ADDRESS = 1162
'The indicated element is part of a magazine that is not present.
Public Const ERROR_MAGAZINE_NOT_PRESENT = 1163
'The indicated device requires reinitialization due to hardware errors.
Public Const ERROR_DEVICE_REINITIALIZATION_NEEDED = 1164 'dderror
'The device has indicated that cleaning is required before further operations
'are attempted.
Public Const ERROR_DEVICE_REQUIRES_CLEANING = 1165
'The device has indicated that its door is open.
Public Const ERROR_DEVICE_DOOR_OPEN = 1166
'The device is not connected.
Public Const ERROR_DEVICE_NOT_CONNECTED = 1167
'Element not found.
Public Const ERROR_NOT_FOUND = 1168
'There was no match for the specified key in the index.
Public Const ERROR_NO_MATCH = 1169
'The property set specified does not exist on the object.
Public Const ERROR_SET_NOT_FOUND = 1170
'The point passed to GetMouseMovePoints is not in the buffer.
Public Const ERROR_POINT_NOT_FOUND = 1171
'The tracking (workstation) service is not running.
Public Const ERROR_NO_TRACKING_SERVICE = 1172
'The Volume ID could not be found.
Public Const ERROR_NO_VOLUME_ID = 1173
'Unable to remove the file to be replaced.
Public Const ERROR_UNABLE_TO_REMOVE_REPLACED = 1175
'Unable to move the replacement file to the file to be replaced.
'The file to be replaced has retained its original name.
Public Const ERROR_UNABLE_TO_MOVE_REPLACEMENT = 1176
'Unable to move the replacement file to the file to be replaced.
'The file to be replaced has been renamed using the backup name.
Public Const ERROR_UNABLE_TO_MOVE_REPLACEMENT_2 = 1177
'The volume change journal is being deleted.
Public Const ERROR_JOURNAL_DELETE_IN_PROGRESS = 1178
'The volume change journal is not active.
Public Const ERROR_JOURNAL_NOT_ACTIVE = 1179
'A file was found, but it may not be the correct file.
Public Const ERROR_POTENTIAL_FILE_FOUND = 1180
'The journal entry has been deleted from the journal.
Public Const ERROR_JOURNAL_ENTRY_DELETED = 1181
'The specified device name is invalid.
Public Const ERROR_BAD_DEVICE = 1200
'The device is not currently connected but it is a remembered connection.
Public Const ERROR_CONNECTION_UNAVAIL = 1201
'The local device name has a remembered connection to another network resource.
Public Const ERROR_DEVICE_ALREADY_REMEMBERED = 1202
'No network provider accepted the given network path.
Public Const ERROR_NO_NET_OR_BAD_PATH = 1203
'The specified network provider name is invalid.
Public Const ERROR_BAD_PROVIDER = 1204
'Unable to open the network connection profile.
Public Const ERROR_CANNOT_OPEN_PROFILE = 1205
'The network connection profile is corrupted.
Public Const ERROR_BAD_PROFILE = 1206
'Cannot enumerate a noncontainer.
Public Const ERROR_NOT_CONTAINER = 1207
'An extended error has occurred.
Public Const ERROR_EXTENDED_ERROR = 1208
'The format of the specified group name is invalid.
Public Const ERROR_INVALID_GROUPNAME = 1209
'The format of the specified computer name is invalid.
Public Const ERROR_INVALID_COMPUTERNAME = 1210
'The format of the specified event name is invalid.
Public Const ERROR_INVALID_EVENTNAME = 1211
'The format of the specified domain name is invalid.
Public Const ERROR_INVALID_DOMAINNAME = 1212
'The format of the specified service name is invalid.
Public Const ERROR_INVALID_SERVICENAME = 1213
'The format of the specified network name is invalid.
Public Const ERROR_INVALID_NETNAME = 1214
'The format of the specified share name is invalid.
Public Const ERROR_INVALID_SHARENAME = 1215
'The format of the specified password is invalid.
Public Const ERROR_INVALID_PASSWORDNAME = 1216
'The format of the specified message name is invalid.
Public Const ERROR_INVALID_MESSAGENAME = 1217
'The format of the specified message destination is invalid.
Public Const ERROR_INVALID_MESSAGEDEST = 1218
'Multiple connections to a server or shared resource by the same user,
'using more than one user name, are not allowed. Disconnect all previous
'connections to the server or shared resource and try again.
Public Const ERROR_SESSION_CREDENTIAL_CONFLICT = 1219
'An attempt was made to establish a session to a network server, but there are
'already too many sessions established to that server.
Public Const ERROR_REMOTE_SESSION_LIMIT_EXCEEDED = 1220
'The workgroup or domain name is already in use by another computer on the network.
Public Const ERROR_DUP_DOMAINNAME = 1221
'The network is not present or not started.
Public Const ERROR_NO_NETWORK = 1222
'The operation was canceled by the user.
Public Const ERROR_CANCELLED = 1223
'The requested operation cannot be performed on a file with a user-mapped
'section open.
Public Const ERROR_USER_MAPPED_FILE = 1224
'The remote system refused the network connection.
Public Const ERROR_CONNECTION_REFUSED = 1225
'The network connection was gracefully closed.
Public Const ERROR_GRACEFUL_DISCONNECT = 1226
'The network transport endpoint already has an address associated with it.
Public Const ERROR_ADDRESS_ALREADY_ASSOCIATED = 1227
'An address has not yet been associated with the network endpoint.
Public Const ERROR_ADDRESS_NOT_ASSOCIATED = 1228
'An operation was attempted on a nonexistent network connection.
Public Const ERROR_CONNECTION_INVALID = 1229
'An invalid operation was attempted on an active network connection.
Public Const ERROR_CONNECTION_ACTIVE = 1230
'The network location cannot be reached. For information about network
'troubleshooting, see Windows Help.
Public Const ERROR_NETWORK_UNREACHABLE = 1231
'The network location cannot be reached. For information about network
'troubleshooting, see Windows Help.
Public Const ERROR_HOST_UNREACHABLE = 1232
'The network location cannot be reached. For information about network
'troubleshooting, see Windows Help.
Public Const ERROR_PROTOCOL_UNREACHABLE = 1233
'No service is operating at the destination network endpoint on the remote system.
Public Const ERROR_PORT_UNREACHABLE = 1234
'The request was aborted.
Public Const ERROR_REQUEST_ABORTED = 1235
'The network connection was aborted by the local system.
Public Const ERROR_CONNECTION_ABORTED = 1236
'The operation could not be completed. A retry should be performed.
Public Const ERROR_RETRY = 1237
'A connection to the server could not be made because the limit on the number
'of concurrent connections for this account has been reached.
Public Const ERROR_CONNECTION_COUNT_LIMIT = 1238
'Attempting to log in during an unauthorized time of day for this account.
Public Const ERROR_LOGIN_TIME_RESTRICTION = 1239
'The account is not authorized to log in from this station.
Public Const ERROR_LOGIN_WKSTA_RESTRICTION = 1240
'The network address could not be used for the operation requested.
Public Const ERROR_INCORRECT_ADDRESS = 1241
'The service is already registered.
Public Const ERROR_ALREADY_REGISTERED = 1242
'The specified service does not exist.
Public Const ERROR_SERVICE_NOT_FOUND = 1243
'The operation being requested was not performed because the user has not
'been authenticated.
Public Const ERROR_NOT_AUTHENTICATED = 1244
'The operation being requested was not performed because the user has not
'logged on to the network.
'The specified service does not exist.
Public Const ERROR_NOT_LOGGED_ON = 1245
'Continue with work in progress.
Public Const ERROR_CONTINUE = 1246                   'dderror
'An attempt was made to perform an initialization operation when initialization
'has already been completed.
Public Const ERROR_ALREADY_INITIALIZED = 1247
'No more local devices.
Public Const ERROR_NO_MORE_DEVICES = 1248            'dderror
'The specified site does not exist.
Public Const ERROR_NO_SUCH_SITE = 1249
'A domain controller with the specified name already exists.
Public Const ERROR_DOMAIN_CONTROLLER_EXISTS = 1250
'This operation is supported only when you are connected to the server.
Public Const ERROR_ONLY_IF_CONNECTED = 1251
'The group policy framework should call the extension even if there are no changes.
Public Const ERROR_OVERRIDE_NOCHANGES = 1252
'The specified user does not have a valid profile.
Public Const ERROR_BAD_USER_PROFILE = 1253
'This operation is not supported on a Microsoft Small Business Server
Public Const ERROR_NOT_SUPPORTED_ON_SBS = 1254
'The server machine is shutting down.
Public Const ERROR_SERVER_SHUTDOWN_IN_PROGRESS = 1255
'The remote system is not available. For information about network
'troubleshooting, see Windows Help.
Public Const ERROR_HOST_DOWN = 1256
'The security identifier provided is not from an account domain.
Public Const ERROR_NON_ACCOUNT_SID = 1257
'The security identifier provided does not have a domain component.
Public Const ERROR_NON_DOMAIN_SID = 1258
'AppHelp dialog canceled thus preventing the application from starting.
Public Const ERROR_APPHELP_BLOCK = 1259
'Windows cannot open this program because it has been prevented by a software
'restriction policy. For more information, open Event Viewer or contact your
'system administrator.
Public Const ERROR_ACCESS_DISABLED_BY_POLICY = 1260
'A program attempt to use an invalid register value. Normally caused by
'an uninitialized register. This error is Itanium specific.
Public Const ERROR_REG_NAT_CONSUMPTION = 1261
'The share is currently offline or does not exist.
Public Const ERROR_CSCSHARE_OFFLINE = 1262
'The kerberos protocol encountered an error while validating the
'KDC certificate during smartcard logon.
Public Const ERROR_PKINIT_FAILURE = 1263
'The kerberos protocol encountered an error while attempting to utilize
'the smartcard subsystem.
Public Const ERROR_SMARTCARD_SUBSYSTEM_FAILURE = 1264
'The system detected a possible attempt to compromise security. Please ensure
'that you can contact the server that authenticated you.
Public Const ERROR_DOWNGRADE_DETECTED = 1265

'...............................................................................
'Do not use ID's 1266 - 1270 as the symbolicNames have been moved to SEC_E_*


'The machine is locked and can not be shut down without the force option.
Public Const ERROR_MACHINE_LOCKED = 1271
'An application-defined callback gave invalid data when called.
Public Const ERROR_CALLBACK_SUPPLIED_INVALID_DATA = 1273
'The group policy framework should call the extension in the synchronous
'foreground policy refresh.
Public Const ERROR_SYNC_FOREGROUND_REFRESH_REQUIRED = 1274
'This driver has been blocked from loading
Public Const ERROR_DRIVER_BLOCKED = 1275
'A dynamic link library (DLL) referenced a module that was neither a DLL nor
'the process's executable image.
Public Const ERROR_INVALID_IMPORT_OF_NON_DLL = 1276
'Windows cannot open this program since it has been disabled.
Public Const ERROR_ACCESS_DISABLED_WEBBLADE = 1277
'Windows cannot open this program because the license enforcement system has
'been tampered with or become corrupted.
Public Const ERROR_ACCESS_DISABLED_WEBBLADE_TAMPER = 1278
'A transaction recover failed.
Public Const ERROR_RECOVERY_FAILURE = 1279
'The current thread has already been converted to a fiber.
Public Const ERROR_ALREADY_FIBER = 1280
'The current thread has already been converted from a fiber.
Public Const ERROR_ALREADY_THREAD = 1281
'The system detected an overrun of a stack-based buffer in this application.
'This overrun could potentially allow a malicious user to gain control of this
'application.
Public Const ERROR_STACK_BUFFER_OVERRUN = 1282
'Data present in one of the parameters is more than the function can operate on.
Public Const ERROR_PARAMETER_QUOTA_EXCEEDED = 1283
'An attempt to do an operation on a debug object failed because the object is
'in the process of being deleted.
Public Const ERROR_DEBUGGER_INACTIVE = 1284
'An attempt to delay-load a .dll or get a function address in a delay-loaded
'.dll failed.
Public Const ERROR_DELAY_LOAD_FAILED = 1285
'%1 is a 16-bit application. You do not have permissions to execute 16-bit
'applications. Check your permissions with your system administrator.
Public Const ERROR_VDM_DISALLOWED = 1286

'...............................................................................
'Add new status codes before this point unless there is a component specific
'section below.

'------------------------------------------------------------------------------
'Security Status Codes

'Not all privileges referenced are assigned to the caller.
Public Const ERROR_NOT_ALL_ASSIGNED = 1300
'Some mapping between account names and security IDs was not done.
Public Const ERROR_SOME_NOT_MAPPED = 1301
'No system quota limits are specifically set for this account.
Public Const ERROR_NO_QUOTAS_FOR_ACCOUNT = 1302
'No encryption key is available. A well-known encryption key was returned.
Public Const ERROR_LOCAL_USER_SESSION_KEY = 1303
'The password is too complex to be converted to a LAN Manager password.
'The LAN Manager password returned is a NULL string.
Public Const ERROR_NULL_LM_PASSWORD = 1304
'The revision level is unknown.
Public Const ERROR_UNKNOWN_REVISION = 1305
'Indicates two revision levels are incompatible.
Public Const ERROR_REVISION_MISMATCH = 1306
'This security ID may not be assigned as the owner of this object.
Public Const ERROR_INVALID_OWNER = 1307
'This security ID may not be assigned as the primary group of an object.
Public Const ERROR_INVALID_PRIMARY_GROUP = 1308
'An attempt has been made to operate on an impersonation token by a thread
'that is not currently impersonating a client.
Public Const ERROR_NO_IMPERSONATION_TOKEN = 1309
'The group may not be disabled.
Public Const ERROR_CANT_DISABLE_MANDATORY = 1310
'There are currently no logon servers available to service the logon request.
Public Const ERROR_NO_LOGON_SERVERS = 1311
'A specified logon session does not exist. It may already have been terminated.
Public Const ERROR_NO_SUCH_LOGON_SESSION = 1312
'A specified privilege does not exist.
Public Const ERROR_NO_SUCH_PRIVILEGE = 1313
'A required privilege is not held by the client.
Public Const ERROR_PRIVILEGE_NOT_HELD = 1314
'The name provided is not a properly formed account name.
Public Const ERROR_INVALID_ACCOUNT_NAME = 1315
'The specified user already exists.
Public Const ERROR_USER_EXISTS = 1316
'The specified user does not exist.
Public Const ERROR_NO_SUCH_USER = 1317
'The specified group already exists.
Public Const ERROR_GROUP_EXISTS = 1318
'The specified group does not exist.
Public Const ERROR_NO_SUCH_GROUP = 1319
'Either the specified user account is already a member of the specified group,
'or the specified group cannot be deleted because it contains a member.
Public Const ERROR_MEMBER_IN_GROUP = 1320
'The specified user account is not a member of the specified group account.
Public Const ERROR_MEMBER_NOT_IN_GROUP = 1321
'The last remaining administration account cannot be disabled or deleted.
Public Const ERROR_LAST_ADMIN = 1322
'Unable to update the password. The value provided as the current password is
'incorrect.
Public Const ERROR_WRONG_PASSWORD = 1323
'Unable to update the password. The value provided for the new password contains
'values that are not allowed in passwords.
Public Const ERROR_ILL_FORMED_PASSWORD = 1324
'Unable to update the password. The value provided for the new password does
'not meet the length, complexity, or history requirement of the domain.
Public Const ERROR_PASSWORD_RESTRICTION = 1325
'Logon failure: unknown user name or bad password.
Public Const ERROR_LOGON_FAILURE = 1326
'Logon failure: user account restriction. Possible reasons are blank passwords
'not allowed, logon hour restrictions, or a policy restriction has been enforced.
Public Const ERROR_ACCOUNT_RESTRICTION = 1327
'Logon failure: account logon time restriction violation.
Public Const ERROR_INVALID_LOGON_HOURS = 1328
'Logon failure: user not allowed to log on to this computer.
Public Const ERROR_INVALID_WORKSTATION = 1329
'Logon failure: the specified account password has expired.
Public Const ERROR_PASSWORD_EXPIRED = 1330
'Logon failure: account currently disabled.
Public Const ERROR_ACCOUNT_DISABLED = 1331
'No mapping between account names and security IDs was done.
Public Const ERROR_NONE_MAPPED = 1332
'Too many local user identifiers (LUIDs) were requested at one time.
Public Const ERROR_TOO_MANY_LUIDS_REQUESTED = 1333
'No more local user identifiers (LUIDs) are available.
Public Const ERROR_LUIDS_EXHAUSTED = 1334
'The subauthority part of a security ID is invalid for this particular use.
Public Const ERROR_INVALID_SUB_AUTHORITY = 1335
'The access control list (ACL) structure is invalid.
Public Const ERROR_INVALID_ACL = 1336
'The security ID structure is invalid.
Public Const ERROR_INVALID_SID = 1337
'The security descriptor structure is invalid.
Public Const ERROR_INVALID_SECURITY_DESCR = 1338
'The inherited access control list (ACL) or access control entry (ACE) could not
'be built.
Public Const ERROR_BAD_INHERITANCE_ACL = 1340
'The server is currently disabled.
Public Const ERROR_SERVER_DISABLED = 1341
'The server is currently enabled.
Public Const ERROR_SERVER_NOT_DISABLED = 1342
'The value provided was an invalid value for an identifier authority.
Public Const ERROR_INVALID_ID_AUTHORITY = 1343
'No more memory is available for security information updates.
Public Const ERROR_ALLOTTED_SPACE_EXCEEDED = 1344
'The specified attributes are invalid, or incompatible with the attributes for
'the group as a whole.
Public Const ERROR_INVALID_GROUP_ATTRIBUTES = 1345
'Either a required impersonation level was not provided, or the provided
'impersonation level is invalid.
Public Const ERROR_BAD_IMPERSONATION_LEVEL = 1346
'Cannot open an anonymous level security token.
Public Const ERROR_CANT_OPEN_ANONYMOUS = 1347
'The validation information class requested was invalid.
Public Const ERROR_BAD_VALIDATION_CLASS = 1348
'The type of the token is inappropriate for its attempted use.
Public Const ERROR_BAD_TOKEN_TYPE = 1349
'Unable to perform a security operation on an object that has no associated security.
Public Const ERROR_NO_SECURITY_ON_OBJECT = 1350
'Configuration information could not be read from the domain controller, either
'because the machine is unavailable, or access has been denied.
Public Const ERROR_CANT_ACCESS_DOMAIN_INFO = 1351
'The security account manager (SAM) or local security authority (LSA) server was
'in the wrong state to perform the security operation.
Public Const ERROR_INVALID_SERVER_STATE = 1352
'The domain was in the wrong state to perform the security operation.
Public Const ERROR_INVALID_DOMAIN_STATE = 1353
'This operation is only allowed for the Primary Domain Controller of the domain.
Public Const ERROR_INVALID_DOMAIN_ROLE = 1354
'The specified domain either does not exist or could not be contacted.
Public Const ERROR_NO_SUCH_DOMAIN = 1355
'The specified domain already exists.
Public Const ERROR_DOMAIN_EXISTS = 1356
'An attempt was made to exceed the limit on the number of domains per server.
Public Const ERROR_DOMAIN_LIMIT_EXCEEDED = 1357
'Unable to complete the requested operation because of either a catastrophic
'media failure or a data structure corruption on the disk.
Public Const ERROR_INTERNAL_DB_CORRUPTION = 1358
'An internal error occurred.
Public Const ERROR_INTERNAL_ERROR = 1359
'Generic access types were contained in an access mask which should already be
'mapped to nongeneric types.
Public Const ERROR_GENERIC_NOT_MAPPED = 1360
'A security descriptor is not in the right format (absolute or self-relative).
Public Const ERROR_BAD_DESCRIPTOR_FORMAT = 1361
'The requested action is restricted for use by logon processes only.
'The calling process has not registered as a logon process.
Public Const ERROR_NOT_LOGON_PROCESS = 1362
'Cannot start a new logon session with an ID that is already in use.
Public Const ERROR_LOGON_SESSION_EXISTS = 1363
'A specified authentication package is unknown.
Public Const ERROR_NO_SUCH_PACKAGE = 1364
'The logon session is not in a state that is consistent with the requested
'operation.
Public Const ERROR_BAD_LOGON_SESSION_STATE = 1365
'The logon session ID is already in use.
Public Const ERROR_LOGON_SESSION_COLLISION = 1366
'A logon request contained an invalid logon type value.
Public Const ERROR_INVALID_LOGON_TYPE = 1367
'Unable to impersonate using a named pipe until data has been read from that pipe.
Public Const ERROR_CANNOT_IMPERSONATE = 1368
'The transaction state of a registry subtree is incompatible with the requested
'operation.
Public Const ERROR_RXACT_INVALID_STATE = 1369
'An internal security database corruption has been encountered.
Public Const ERROR_RXACT_COMMIT_FAILURE = 1370
'Cannot perform this operation on built-in accounts.
Public Const ERROR_SPECIAL_ACCOUNT = 1371
'Cannot perform this operation on this built-in special group.
Public Const ERROR_SPECIAL_GROUP = 1372
'Cannot perform this operation on this built-in special user.
Public Const ERROR_SPECIAL_USER = 1373
'The user cannot be removed from a group because the group is currently
'the user's primary group.
Public Const ERROR_MEMBERS_PRIMARY_GROUP = 1374
'The token is already in use as a primary token.
Public Const ERROR_TOKEN_ALREADY_IN_USE = 1375
'The specified local group does not exist.
Public Const ERROR_NO_SUCH_ALIAS = 1376
'The specified account name is not a member of the local group.
Public Const ERROR_MEMBER_NOT_IN_ALIAS = 1377
'The specified account name is already a member of the local group.
Public Const ERROR_MEMBER_IN_ALIAS = 1378
'The specified local group already exists.
Public Const ERROR_ALIAS_EXISTS = 1379
'Logon failure: the user has not been granted the requested logon type at this
'computer.
Public Const ERROR_LOGON_NOT_GRANTED = 1380
'The maximum number of secrets that may be stored in a single system has been
'exceeded.
Public Const ERROR_TOO_MANY_SECRETS = 1381
'The length of a secret exceeds the maximum length allowed.
Public Const ERROR_SECRET_TOO_LONG = 1382
'The local security authority database contains an internal inconsistency.
Public Const ERROR_INTERNAL_DB_ERROR = 1383
'During a logon attempt, the user's security context accumulated too many
'security IDs.
Public Const ERROR_TOO_MANY_CONTEXT_IDS = 1384
'Logon failure: the user has not been granted the requested logon type at this
'computer.
Public Const ERROR_LOGON_TYPE_NOT_GRANTED = 1385
'A cross-encrypted password is necessary to change a user password.
Public Const ERROR_NT_CROSS_ENCRYPTION_REQUIRED = 1386
'A member could not be added to or removed from the local group because
'the member does not exist.
Public Const ERROR_NO_SUCH_MEMBER = 1387
'A new member could not be added to a local group because the member has
'the wrong account type.
Public Const ERROR_INVALID_MEMBER = 1388
'Too many security IDs have been specified.
Public Const ERROR_TOO_MANY_SIDS = 1389
'A cross-encrypted password is necessary to change this user password.
Public Const ERROR_LM_CROSS_ENCRYPTION_REQUIRED = 1390
'Indicates an ACL contains no inheritable components.
Public Const ERROR_NO_INHERITANCE = 1391
'The file or directory is corrupted and unreadable.
Public Const ERROR_FILE_CORRUPT = 1392
'The disk structure is corrupted and unreadable.
Public Const ERROR_DISK_CORRUPT = 1393
'There is no user session key for the specified logon session.
Public Const ERROR_NO_USER_SESSION_KEY = 1394
'The service being accessed is licensed for a particular number of connections.
'No more connections can be made to the service at this time because there are
'already as many connections as the service can accept.
Public Const ERROR_LICENSE_QUOTA_EXCEEDED = 1395
'Logon Failure: The target account name is incorrect.
Public Const ERROR_WRONG_TARGET_NAME = 1396
'Mutual Authentication failed. The server's password is out of date at
'the domain controller.
Public Const ERROR_MUTUAL_AUTH_FAILED = 1397
'There is a time and/or date difference between the client and server.
Public Const ERROR_TIME_SKEW = 1398
'This operation can not be performed on the current domain.
Public Const ERROR_CURRENT_DOMAIN_NOT_ALLOWED = 1399

'End of security error codes
'-------------------------------------------------------------------------------
'WinUser Error Codes

'Invalid window handle.
Public Const ERROR_INVALID_WINDOW_HANDLE = 1400
'Invalid menu handle.
Public Const ERROR_INVALID_MENU_HANDLE = 1401
'Invalid cursor handle.
Public Const ERROR_INVALID_CURSOR_HANDLE = 1402
'Invalid accelerator table handle.
Public Const ERROR_INVALID_ACCEL_HANDLE = 1403
'Invalid hook handle.
Public Const ERROR_INVALID_HOOK_HANDLE = 1404
'Invalid handle to a multiple-window position structure.
Public Const ERROR_INVALID_DWP_HANDLE = 1405
'Cannot create a top-level child window.
Public Const ERROR_TLW_WITH_WSCHILD = 1406
'Cannot find window class.
Public Const ERROR_CANNOT_FIND_WND_CLASS = 1407
'Invalid window; it belongs to other thread.
Public Const ERROR_WINDOW_OF_OTHER_THREAD = 1408
'Hot key is already registered.
Public Const ERROR_HOTKEY_ALREADY_REGISTERED = 1409
'Class already exists.
Public Const ERROR_CLASS_ALREADY_EXISTS = 1410
'Class does not exist.
Public Const ERROR_CLASS_DOES_NOT_EXIST = 1411
'Class still has open windows.
Public Const ERROR_CLASS_HAS_WINDOWS = 1412
'Invalid index.
Public Const ERROR_INVALID_INDEX = 1413
'Invalid icon handle.
Public Const ERROR_INVALID_ICON_HANDLE = 1414
'Using private DIALOG window words.
Public Const ERROR_PRIVATE_DIALOG_INDEX = 1415
'The list box identifier was not found.
Public Const ERROR_LISTBOX_ID_NOT_FOUND = 1416
'No wildcards were found.
Public Const ERROR_NO_WILDCARD_CHARACTERS = 1417
'Thread does not have a clipboard open.
Public Const ERROR_CLIPBOARD_NOT_OPEN = 1418
'Hot key is not registered.
Public Const ERROR_HOTKEY_NOT_REGISTERED = 1419
'The window is not a valid dialog window.
Public Const ERROR_WINDOW_NOT_DIALOG = 1420
'Control ID not found.
Public Const ERROR_CONTROL_ID_NOT_FOUND = 1421
'Invalid message for a combo box because it does not have an edit control.
Public Const ERROR_INVALID_COMBOBOX_MESSAGE = 1422
'The window is not a combo box.
Public Const ERROR_WINDOW_NOT_COMBOBOX = 1423
'Height must be less than 256.
Public Const ERROR_INVALID_EDIT_HEIGHT = 1424
'Invalid device context (DC) handle.
Public Const ERROR_DC_NOT_FOUND = 1425
'Invalid hook procedure type.
Public Const ERROR_INVALID_HOOK_FILTER = 1426
'Invalid hook procedure.
Public Const ERROR_INVALID_FILTER_PROC = 1427
'Cannot set nonlocal hook without a module handle.
Public Const ERROR_HOOK_NEEDS_HMOD = 1428
'This hook procedure can only be set globally.
Public Const ERROR_GLOBAL_ONLY_HOOK = 1429
'The journal hook procedure is already installed.
Public Const ERROR_JOURNAL_HOOK_SET = 1430
'The hook procedure is not installed.
Public Const ERROR_HOOK_NOT_INSTALLED = 1431
'Invalid message for single-selection list box.
Public Const ERROR_INVALID_LB_MESSAGE = 1432
'LB_SETCOUNT sent to non-lazy list box.
Public Const ERROR_SETCOUNT_ON_BAD_LB = 1433
'This list box does not support tab stops.
Public Const ERROR_LB_WITHOUT_TABSTOPS = 1434
'Cannot destroy object created by another thread.
Public Const ERROR_DESTROY_OBJECT_OF_OTHER_THREAD = 1435
'Child windows cannot have menus.
Public Const ERROR_CHILD_WINDOW_MENU = 1436
'The window does not have a system menu.
Public Const ERROR_NO_SYSTEM_MENU = 1437
'Invalid message box style.
Public Const ERROR_INVALID_MSGBOX_STYLE = 1438
'Invalid system-wide (SPI_*) parameter.
Public Const ERROR_INVALID_SPI_VALUE = 1439
'Screen already locked.
Public Const ERROR_SCREEN_ALREADY_LOCKED = 1440
'All handles to windows in a multiple-window position structure must have
'the same parent.
Public Const ERROR_HWNDS_HAVE_DIFF_PARENT = 1441
'The window is not a child window.
Public Const ERROR_NOT_CHILD_WINDOW = 1442
'Invalid GW_* command.
Public Const ERROR_INVALID_GW_COMMAND = 1443
'Invalid thread identifier.
Public Const ERROR_INVALID_THREAD_ID = 1444
'Cannot process a message from a window that is not a multiple document
'interface (MDI) window.
Public Const ERROR_NON_MDICHILD_WINDOW = 1445
'Popup menu already active.
Public Const ERROR_POPUP_ALREADY_ACTIVE = 1446
'The window does not have scroll bars.
Public Const ERROR_NO_SCROLLBARS = 1447
'Scroll bar range cannot be greater than MAXLONG.
Public Const ERROR_INVALID_SCROLLBAR_RANGE = 1448
'Cannot show or remove the window in the way specified.
Public Const ERROR_INVALID_SHOWWIN_COMMAND = 1449
'Insufficient system resources exist to complete the requested service.
Public Const ERROR_NO_SYSTEM_RESOURCES = 1450
'Insufficient system resources exist to complete the requested service.
Public Const ERROR_NONPAGED_SYSTEM_RESOURCES = 1451
'Insufficient system resources exist to complete the requested service.
Public Const ERROR_PAGED_SYSTEM_RESOURCES = 1452
'Insufficient quota to complete the requested service.
Public Const ERROR_WORKING_SET_QUOTA = 1453
'Insufficient quota to complete the requested service.
Public Const ERROR_PAGEFILE_QUOTA = 1454
'The paging file is too small for this operation to complete.
Public Const ERROR_COMMITMENT_LIMIT = 1455
'A menu item was not found.
Public Const ERROR_MENU_ITEM_NOT_FOUND = 1456
'Invalid keyboard layout handle.
Public Const ERROR_INVALID_KEYBOARD_HANDLE = 1457
'Hook type not allowed.
Public Const ERROR_HOOK_TYPE_NOT_ALLOWED = 1458
'This operation requires an interactive window station.
Public Const ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION = 1459
'This operation returned because the timeout period expired.
Public Const ERROR_TIMEOUT = 1460
'Invalid monitor handle.
Public Const ERROR_INVALID_MONITOR_HANDLE = 1461

'End of WinUser error codes
'------------------------------------------------------------------------------
'Eventlog Status Codes

'The event log file is corrupted.
Public Const ERROR_EVENTLOG_FILE_CORRUPT = 1500
'No event log file could be opened, so the event logging service did not start.
Public Const ERROR_EVENTLOG_CANT_START = 1501
'The event log file is full.
Public Const ERROR_LOG_FILE_FULL = 1502
'The event log file has changed between read operations.
Public Const ERROR_EVENTLOG_FILE_CHANGED = 1503

'End of eventlog error codes
'------------------------------------------------------------------------------
'MSI Error Codes

'The Windows Installer Service could not be accessed. This can occur if you are
'running Windows in safe mode, or if the Windows Installer is not correctly
'installed. Contact your support personnel for assistance.
Public Const ERROR_INSTALL_SERVICE_FAILURE = 1601
'User cancelled installation.
Public Const ERROR_INSTALL_USEREXIT = 1602
'Fatal error during installation.
Public Const ERROR_INSTALL_FAILURE = 1603
'Installation suspended, incomplete.
Public Const ERROR_INSTALL_SUSPEND = 1604
'This action is only valid for products that are currently installed.
Public Const ERROR_UNKNOWN_PRODUCT = 1605
'Feature ID not registered.
Public Const ERROR_UNKNOWN_FEATURE = 1606
'Component ID not registered.
Public Const ERROR_UNKNOWN_COMPONENT = 1607
'Unknown property.
Public Const ERROR_UNKNOWN_PROPERTY = 1608
'Handle is in an invalid state.
Public Const ERROR_INVALID_HANDLE_STATE = 1609
'The configuration data for this product is corrupt. Contact your support personnel.
Public Const ERROR_BAD_CONFIGURATION = 1610
'Component qualifier not present.
Public Const ERROR_INDEX_ABSENT = 1611
'The installation source for this product is not available. Verify that
'the source exists and that you can access it.
Public Const ERROR_INSTALL_SOURCE_ABSENT = 1612
'This installation package cannot be installed by the Windows Installer service.
'You must install a Windows service pack that contains a newer version of
'the Windows Installer service.
Public Const ERROR_INSTALL_PACKAGE_VERSION = 1613
'Product is uninstalled.
Public Const ERROR_PRODUCT_UNINSTALLED = 1614
'SQL query syntax invalid or unsupported.
Public Const ERROR_BAD_QUERY_SYNTAX = 1615
'Record field does not exist.
Public Const ERROR_INVALID_FIELD = 1616
'The device has been removed.
Public Const ERROR_DEVICE_REMOVED = 1617
'Another installation is already in progress. Complete that installation before
'proceeding with this install.
Public Const ERROR_INSTALL_ALREADY_RUNNING = 1618
'This installation package could not be opened. Verify that the package exists
'and that you can access it, or contact the application vendor to verify that
'this is a valid Windows Installer package.
Public Const ERROR_INSTALL_PACKAGE_OPEN_FAILED = 1619
'This installation package could not be opened. Contact the application vendor
'to verify that this is a valid Windows Installer package.
Public Const ERROR_INSTALL_PACKAGE_INVALID = 1620
'There was an error starting the Windows Installer service user interface.
'Contact your support personnel.
Public Const ERROR_INSTALL_UI_FAILURE = 1621
'Error opening installation log file. Verify that the specified log file
'location exists and that you can write to it.
Public Const ERROR_INSTALL_LOG_FAILURE = 1622
'The language of this installation package is not supported by your system.
Public Const ERROR_INSTALL_LANGUAGE_UNSUPPORTED = 1623
'Error applying transforms. Verify that the specified transform paths are valid.
Public Const ERROR_INSTALL_TRANSFORM_FAILURE = 1624
'This installation is forbidden by system policy. Contact your system administrator.
Public Const ERROR_INSTALL_PACKAGE_REJECTED = 1625
'Function could not be executed.
Public Const ERROR_FUNCTION_NOT_CALLED = 1626
'Function failed during execution.
Public Const ERROR_FUNCTION_FAILED = 1627
'Invalid or unknown table specified.
Public Const ERROR_INVALID_TABLE = 1628
'Data supplied is of wrong type.
Public Const ERROR_DATATYPE_MISMATCH = 1629
'Data of this type is not supported.
Public Const ERROR_UNSUPPORTED_TYPE = 1630
'The Windows Installer service failed to start. Contact your support personnel.
Public Const ERROR_CREATE_FAILED = 1631
'The Temp folder is on a drive that is full or is inaccessible. Free up space
'on the drive or verify that you have write permission on the Temp folder.
Public Const ERROR_INSTALL_TEMP_UNWRITABLE = 1632
'This installation package is not supported by this processor type. Contact your
'product vendor.
Public Const ERROR_INSTALL_PLATFORM_UNSUPPORTED = 1633
'Component not used on this computer.
Public Const ERROR_INSTALL_NOTUSED = 1634
'This patch package could not be opened. Verify that the patch package exists
'and that you can access it, or contact the application vendor to verify that
'this is a valid Windows Installer patch package.
Public Const ERROR_PATCH_PACKAGE_OPEN_FAILED = 1635
'This patch package could not be opened. Contact the application vendor to
'verify that this is a valid Windows Installer patch package.
Public Const ERROR_PATCH_PACKAGE_INVALID = 1636
'This patch package cannot be processed by the Windows Installer service.
'You must install a Windows service pack that contains a newer version of
'the Windows Installer service.
Public Const ERROR_PATCH_PACKAGE_UNSUPPORTED = 1637
'Another version of this product is already installed. Installation of this
'version cannot continue. To configure or remove the existing version of this
'product, use Add/Remove Programs on the Control Panel.
Public Const ERROR_PRODUCT_VERSION = 1638
'Invalid command line argument. Consult the Windows Installer SDK for detailed
'command line help.
Public Const ERROR_INVALID_COMMAND_LINE = 1639
'Only administrators have permission to add, remove, or configure server
'software during a Terminal services remote session. If you want to install or
'configure software on the server, contact your network administrator.
Public Const ERROR_INSTALL_REMOTE_DISALLOWED = 1640
'The requested operation completed successfully. The system will be restarted
'so the changes can take effect.
Public Const ERROR_SUCCESS_REBOOT_INITIATED = 1641
'The upgrade patch cannot be installed by the Windows Installer service because
'the program to be upgraded may be missing, or the upgrade patch may update
'a different version of the program. Verify that the program to be upgraded
'exists on your computer and that you have the correct upgrade patch.
Public Const ERROR_PATCH_TARGET_NOT_FOUND = 1642
'The patch package is not permitted by software restriction policy.
Public Const ERROR_PATCH_PACKAGE_REJECTED = 1643
'One or more customizations are not permitted by software restriction policy.
Public Const ERROR_INSTALL_TRANSFORM_REJECTED = 1644
'The Windows Installer does not permit installation from
'a Remote Desktop Connection.
Public Const ERROR_INSTALL_REMOTE_PROHIBITED = 1645

'End of MSI error codes
'------------------------------------------------------------------------------
' RPC Status Codes

'The string binding is invalid.
Public Const RPC_S_INVALID_STRING_BINDING = 1700
'The binding handle is not the correct type.
Public Const RPC_S_WRONG_KIND_OF_BINDING = 1701
'The binding handle is invalid.
Public Const RPC_S_INVALID_BINDING = 1702
'The RPC protocol sequence is not supported.
Public Const RPC_S_PROTSEQ_NOT_SUPPORTED = 1703
'The RPC protocol sequence is invalid.
Public Const RPC_S_INVALID_RPC_PROTSEQ = 1704
'The string universal unique identifier (UUID) is invalid.
Public Const RPC_S_INVALID_STRING_UUID = 1705
'The endpoint format is invalid.
Public Const RPC_S_INVALID_ENDPOINT_FORMAT = 1706
'The network address is invalid.
Public Const RPC_S_INVALID_NET_ADDR = 1707
'No endpoint was found.
Public Const RPC_S_NO_ENDPOINT_FOUND = 1708
'The timeout value is invalid.
Public Const RPC_S_INVALID_TIMEOUT = 1709
'The object universal unique identifier (UUID) was not found.
Public Const RPC_S_OBJECT_NOT_FOUND = 1710
'The object universal unique identifier (UUID) has already been registered.
Public Const RPC_S_ALREADY_REGISTERED = 1711
'The type universal unique identifier (UUID) has already been registered.
Public Const RPC_S_TYPE_ALREADY_REGISTERED = 1712
'The RPC server is already listening.
Public Const RPC_S_ALREADY_LISTENING = 1713
'No protocol sequences have been registered.
Public Const RPC_S_NO_PROTSEQS_REGISTERED = 1714
'The RPC server is not listening.
Public Const RPC_S_NOT_LISTENING = 1715
'The manager type is unknown.
Public Const RPC_S_UNKNOWN_MGR_TYPE = 1716
'The interface is unknown.
Public Const RPC_S_UNKNOWN_IF = 1717
'There are no bindings.
Public Const RPC_S_NO_BINDINGS = 1718
'There are no protocol sequences.
Public Const RPC_S_NO_PROTSEQS = 1719
'The endpoint cannot be created.
Public Const RPC_S_CANT_CREATE_ENDPOINT = 1720
'Not enough resources are available to complete this operation.
Public Const RPC_S_OUT_OF_RESOURCES = 1721
'The RPC server is unavailable.
Public Const RPC_S_SERVER_UNAVAILABLE = 1722
'The RPC server is too busy to complete this operation.
Public Const RPC_S_SERVER_TOO_BUSY = 1723
'The network options are invalid.
Public Const RPC_S_INVALID_NETWORK_OPTIONS = 1724
'There are no remote procedure calls active on this thread.
Public Const RPC_S_NO_CALL_ACTIVE = 1725
'The remote procedure call failed.
Public Const RPC_S_CALL_FAILED = 1726
'The remote procedure call failed and did not execute.
Public Const RPC_S_CALL_FAILED_DNE = 1727
'A remote procedure call (RPC) protocol error occurred.
Public Const RPC_S_PROTOCOL_ERROR = 1728
'The transfer syntax is not supported by the RPC server.
Public Const RPC_S_UNSUPPORTED_TRANS_SYN = 1730
'The universal unique identifier (UUID) type is not supported.
Public Const RPC_S_UNSUPPORTED_TYPE = 1732
'The tag is invalid.
Public Const RPC_S_INVALID_TAG = 1733
'The array bounds are invalid.
Public Const RPC_S_INVALID_BOUND = 1734
'The binding does not contain an entry name.
Public Const RPC_S_NO_ENTRY_NAME = 1735
'The name syntax is invalid.
Public Const RPC_S_INVALID_NAME_SYNTAX = 1736
'The name syntax is not supported.
Public Const RPC_S_UNSUPPORTED_NAME_SYNTAX = 1737
'No network address is available to use to construct a universal unique
'identifier (UUID).
Public Const RPC_S_UUID_NO_ADDRESS = 1739
'The endpoint is a duplicate.
Public Const RPC_S_DUPLICATE_ENDPOINT = 1740
'The authentication type is unknown.
Public Const RPC_S_UNKNOWN_AUTHN_TYPE = 1741
'The maximum number of calls is too small.
Public Const RPC_S_MAX_CALLS_TOO_SMALL = 1742
'The string is too long.
Public Const RPC_S_STRING_TOO_LONG = 1743
'The RPC protocol sequence was not found.
Public Const RPC_S_PROTSEQ_NOT_FOUND = 1744
'The procedure number is out of range.
Public Const RPC_S_PROCNUM_OUT_OF_RANGE = 1745
'The binding does not contain any authentication information.
Public Const RPC_S_BINDING_HAS_NO_AUTH = 1746
'The authentication service is unknown.
Public Const RPC_S_UNKNOWN_AUTHN_SERVICE = 1747
'The authentication level is unknown.
Public Const RPC_S_UNKNOWN_AUTHN_LEVEL = 1748
'The security context is invalid.
Public Const RPC_S_INVALID_AUTH_IDENTITY = 1749
'The authorization service is unknown.
Public Const RPC_S_UNKNOWN_AUTHZ_SERVICE = 1750
'The entry is invalid.
Public Const EPT_S_INVALID_ENTRY = 1751
'The server endpoint cannot perform the operation.
Public Const EPT_S_CANT_PERFORM_OP = 1752
'There are no more endpoints available from the endpoint mapper.
Public Const EPT_S_NOT_REGISTERED = 1753
'No interfaces have been exported.
Public Const RPC_S_NOTHING_TO_EXPORT = 1754
'The entry name is incomplete.
Public Const RPC_S_INCOMPLETE_NAME = 1755
'The version option is invalid.
Public Const RPC_S_INVALID_VERS_OPTION = 1756
'There are no more members.
Public Const RPC_S_NO_MORE_MEMBERS = 1757
'There is nothing to unexport.
Public Const RPC_S_NOT_ALL_OBJS_UNEXPORTED = 1758
'The interface was not found.
Public Const RPC_S_INTERFACE_NOT_FOUND = 1759
'The entry already exists.
Public Const RPC_S_ENTRY_ALREADY_EXISTS = 1760
'The entry is not found.
Public Const RPC_S_ENTRY_NOT_FOUND = 1761
'The name service is unavailable.
Public Const RPC_S_NAME_SERVICE_UNAVAILABLE = 1762
'The network address family is invalid.
Public Const RPC_S_INVALID_NAF_ID = 1763
'The requested operation is not supported.
Public Const RPC_S_CANNOT_SUPPORT = 1764
'No security context is available to allow impersonation.
Public Const RPC_S_NO_CONTEXT_AVAILABLE = 1765
'An internal error occurred in a remote procedure call (RPC).
Public Const RPC_S_INTERNAL_ERROR = 1766
'The RPC server attempted an integer division by zero.
Public Const RPC_S_ZERO_DIVIDE = 1767
'An addressing error occurred in the RPC server.
Public Const RPC_S_ADDRESS_ERROR = 1768
'A floating-point operation at the RPC server caused a division by zero.
Public Const RPC_S_FP_DIV_ZERO = 1769
'A floating-point underflow occurred at the RPC server.
Public Const RPC_S_FP_UNDERFLOW = 1770
'A floating-point overflow occurred at the RPC server.
Public Const RPC_S_FP_OVERFLOW = 1771
'The list of RPC servers available for the binding of auto handles has been
'exhausted.
Public Const RPC_X_NO_MORE_ENTRIES = 1772
'Unable to open the character translation table file.
Public Const RPC_X_SS_CHAR_TRANS_OPEN_FAIL = 1773
'The file containing the character translation table has fewer than 512 bytes.
Public Const RPC_X_SS_CHAR_TRANS_SHORT_FILE = 1774
'A null context handle was passed from the client to the host during a
'remote procedure call.
Public Const RPC_X_SS_IN_NULL_CONTEXT = 1775
'The context handle changed during a remote procedure call.
Public Const RPC_X_SS_CONTEXT_DAMAGED = 1777
'The binding handles passed to a remote procedure call do not match.
Public Const RPC_X_SS_HANDLES_MISMATCH = 1778
'The stub is unable to get the remote procedure call handle.
Public Const RPC_X_SS_CANNOT_GET_CALL_HANDLE = 1779
'A null reference pointer was passed to the stub.
Public Const RPC_X_NULL_REF_POINTER = 1780
'The enumeration value is out of range.
Public Const RPC_X_ENUM_VALUE_OUT_OF_RANGE = 1781
'The byte count is too small.
Public Const RPC_X_BYTE_COUNT_TOO_SMALL = 1782
'The stub received bad data.
Public Const RPC_X_BAD_STUB_DATA = 1783
'The supplied user buffer is not valid for the requested operation.
Public Const ERROR_INVALID_USER_BUFFER = 1784
'The disk media is not recognized. It may not be formatted.
Public Const ERROR_UNRECOGNIZED_MEDIA = 1785
'The workstation does not have a trust secret.
Public Const ERROR_NO_TRUST_LSA_SECRET = 1786
'The security database on the server does not have a computer account for this
'workstation trust relationship.
Public Const ERROR_NO_TRUST_SAM_ACCOUNT = 1787
'The trust relationship between the primary domain and the trusted domain failed.
Public Const ERROR_TRUSTED_DOMAIN_FAILURE = 1788
'The trust relationship between this workstation and the primary domain failed.
Public Const ERROR_TRUSTED_RELATIONSHIP_FAILURE = 1789
'The network logon failed.
Public Const ERROR_TRUST_FAILURE = 1790
'A remote procedure call is already in progress for this thread.
Public Const RPC_S_CALL_IN_PROGRESS = 1791
'An attempt was made to logon, but the network logon service was not started.
Public Const ERROR_NETLOGON_NOT_STARTED = 1792
'The user's account has expired.
Public Const ERROR_ACCOUNT_EXPIRED = 1793
'The redirector is in use and cannot be unloaded.
Public Const ERROR_REDIRECTOR_HAS_OPEN_HANDLES = 1794
'The specified printer driver is already installed.
Public Const ERROR_PRINTER_DRIVER_ALREADY_INSTALLED = 1795
'The specified port is unknown.
Public Const ERROR_UNKNOWN_PORT = 1796
'The printer driver is unknown.
Public Const ERROR_UNKNOWN_PRINTER_DRIVER = 1797
'The print processor is unknown.
Public Const ERROR_UNKNOWN_PRINTPROCESSOR = 1798
'The specified separator file is invalid.
Public Const ERROR_INVALID_SEPARATOR_FILE = 1799
'The specified priority is invalid.
Public Const ERROR_INVALID_PRIORITY = 1800
'The printer name is invalid.
Public Const ERROR_INVALID_PRINTER_NAME = 1801
'The printer already exists.
Public Const ERROR_PRINTER_ALREADY_EXISTS = 1802
'The printer command is invalid.
Public Const ERROR_INVALID_PRINTER_COMMAND = 1803
'The specified datatype is invalid.
Public Const ERROR_INVALID_DATATYPE = 1804
'The environment specified is invalid.
Public Const ERROR_INVALID_ENVIRONMENT = 1805
'There are no more bindings.
Public Const RPC_S_NO_MORE_BINDINGS = 1806
'The account used is an interdomain trust account. Use your global user account
'or local user account to access this server.
Public Const ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT = 1807
'The account used is a computer account. Use your global user account or
'local user account to access this server.
Public Const ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT = 1808
'The account used is a server trust account. Use your global user account or
'local user account to access this server.
Public Const ERROR_NOLOGON_SERVER_TRUST_ACCOUNT = 1809
'The name or security ID (SID) of the domain specified is inconsistent with
'the trust information for that domain.
Public Const ERROR_DOMAIN_TRUST_INCONSISTENT = 1810
'The server is in use and cannot be unloaded.
Public Const ERROR_SERVER_HAS_OPEN_HANDLES = 1811
'The specified image file did not contain a resource section.
Public Const ERROR_RESOURCE_DATA_NOT_FOUND = 1812
'The specified resource type cannot be found in the image file.
Public Const ERROR_RESOURCE_TYPE_NOT_FOUND = 1813
'The specified resource name cannot be found in the image file.
Public Const ERROR_RESOURCE_NAME_NOT_FOUND = 1814
'The specified resource language ID cannot be found in the image file.
Public Const ERROR_RESOURCE_LANG_NOT_FOUND = 1815
'Not enough quota is available to process this command.
Public Const ERROR_NOT_ENOUGH_QUOTA = 1816
'No interfaces have been registered.
Public Const RPC_S_NO_INTERFACES = 1817
'The remote procedure call was cancelled.
Public Const RPC_S_CALL_CANCELLED = 1818
'The binding handle does not contain all required information.
Public Const RPC_S_BINDING_INCOMPLETE = 1819
'A communications failure occurred during a remote procedure call.
Public Const RPC_S_COMM_FAILURE = 1820
'The requested authentication level is not supported.
Public Const RPC_S_UNSUPPORTED_AUTHN_LEVEL = 1821
'No principal name registered.
Public Const RPC_S_NO_PRINC_NAME = 1822
'The error specified is not a valid Windows RPC error code.
Public Const RPC_S_NOT_RPC_ERROR = 1823
'A UUID that is valid only on this computer has been allocated.
Public Const RPC_S_UUID_LOCAL_ONLY = 1824
'A security package specific error occurred.
Public Const RPC_S_SEC_PKG_ERROR = 1825
'Thread is not canceled.
Public Const RPC_S_NOT_CANCELLED = 1826
'Invalid operation on the encoding/decoding handle.
Public Const RPC_X_INVALID_ES_ACTION = 1827
'Incompatible version of the serializing package.
Public Const RPC_X_WRONG_ES_VERSION = 1828
'Incompatible version of the RPC stub.
Public Const RPC_X_WRONG_STUB_VERSION = 1829
'The RPC pipe object is invalid or corrupted.
Public Const RPC_X_INVALID_PIPE_OBJECT = 1830
'An invalid operation was attempted on an RPC pipe object.
Public Const RPC_X_WRONG_PIPE_ORDER = 1831
'Unsupported RPC pipe version.
Public Const RPC_X_WRONG_PIPE_VERSION = 1832
'The group member was not found.
Public Const RPC_S_GROUP_MEMBER_NOT_FOUND = 1898
'The endpoint mapper database entry could not be created.
Public Const EPT_S_CANT_CREATE = 1899
'The object universal unique identifier (UUID) is the nil UUID.
Public Const RPC_S_INVALID_OBJECT = 1900
'The specified time is invalid.
Public Const ERROR_INVALID_TIME = 1901
'The specified form name is invalid.
Public Const ERROR_INVALID_FORM_NAME = 1902
'The specified form size is invalid.
Public Const ERROR_INVALID_FORM_SIZE = 1903
'The specified printer handle is already being waited on
Public Const ERROR_ALREADY_WAITING = 1904
'The specified printer has been deleted.
Public Const ERROR_PRINTER_DELETED = 1905
'The state of the printer is invalid.
Public Const ERROR_INVALID_PRINTER_STATE = 1906
'The user's password must be changed before logging on the first time.
Public Const ERROR_PASSWORD_MUST_CHANGE = 1907
'Could not find the domain controller for this domain.
Public Const ERROR_DOMAIN_CONTROLLER_NOT_FOUND = 1908
'The referenced account is currently locked out and may not be logged on to.
Public Const ERROR_ACCOUNT_LOCKED_OUT = 1909
'The object exporter specified was not found.
Public Const OR_INVALID_OXID = 1910
'The object specified was not found.
Public Const OR_INVALID_OID = 1911
'The object resolver set specified was not found.
Public Const OR_INVALID_SET = 1912
'Some data remains to be sent in the request buffer.
Public Const RPC_S_SEND_INCOMPLETE = 1913
'Invalid asynchronous remote procedure call handle.
Public Const RPC_S_INVALID_ASYNC_HANDLE = 1914
'Invalid asynchronous RPC call handle for this operation.
Public Const RPC_S_INVALID_ASYNC_CALL = 1915
'The RPC pipe object has already been closed.
Public Const RPC_X_PIPE_CLOSED = 1916
'The RPC call completed before all pipes were processed.
Public Const RPC_X_PIPE_DISCIPLINE_ERROR = 1917
'No more data is available from the RPC pipe.
Public Const RPC_X_PIPE_EMPTY = 1918
'No site name is available for this machine.
Public Const ERROR_NO_SITENAME = 1919
'The file can not be accessed by the system.
Public Const ERROR_CANT_ACCESS_FILE = 1920
'The name of the file cannot be resolved by the system.
Public Const ERROR_CANT_RESOLVE_FILENAME = 1921
'The entry is not of the expected type.
Public Const RPC_S_ENTRY_TYPE_MISMATCH = 1922
'Not all object UUIDs could be exported to the specified entry.
Public Const RPC_S_NOT_ALL_OBJS_EXPORTED = 1923
'Interface could not be exported to the specified entry.
Public Const RPC_S_INTERFACE_NOT_EXPORTED = 1924
'The specified profile entry could not be added.
Public Const RPC_S_PROFILE_NOT_ADDED = 1925
'The specified profile element could not be added.
Public Const RPC_S_PRF_ELT_NOT_ADDED = 1926
'The specified profile element could not be removed.
Public Const RPC_S_PRF_ELT_NOT_REMOVED = 1927
'The group element could not be added.
Public Const RPC_S_GRP_ELT_NOT_ADDED = 1928
'The group element could not be removed.
Public Const RPC_S_GRP_ELT_NOT_REMOVED = 1929
'The printer driver is not compatible with a policy enabled on your computer
'that blocks NT 4.0 drivers.
Public Const ERROR_KM_DRIVER_BLOCKED = 1930
'The context has expired and can no longer be used.
Public Const ERROR_CONTEXT_EXPIRED = 1931
'The current user's delegated trust creation quota has been exceeded.
Public Const ERROR_PER_USER_TRUST_QUOTA_EXCEEDED = 1932
'The total delegated trust creation quota has been exceeded.
Public Const ERROR_ALL_USER_TRUST_QUOTA_EXCEEDED = 1933
'The current user's delegated trust deletion quota has been exceeded.
Public Const ERROR_USER_DELETE_TRUST_QUOTA_EXCEEDED = 1934
'Logon Failure: The machine you are logging onto is protected by
'an authentication firewall. The specified account is not allowed to
'authenticate to the machine.
Public Const ERROR_AUTHENTICATION_FIREWALL_FAILED = 1935
'Remote connections to the Print Spooler are blocked by a policy set on your
'machine.
Public Const ERROR_REMOTE_PRINT_CONNECTIONS_BLOCKED = 1936

'------------------------------------------------------------------------------
' OpenGL Error Code

'The pixel format is invalid.
Public Const ERROR_INVALID_PIXEL_FORMAT = 2000
'The specified driver is invalid.
Public Const ERROR_BAD_DRIVER = 2001
'The window style or class attribute is invalid for this operation.
Public Const ERROR_INVALID_WINDOW_STYLE = 2002
'The requested metafile operation is not supported.
Public Const ERROR_METAFILE_NOT_SUPPORTED = 2003
'The requested transformation operation is not supported.
Public Const ERROR_TRANSFORM_NOT_SUPPORTED = 2004
'The requested clipping operation is not supported.
Public Const ERROR_CLIPPING_NOT_SUPPORTED = 2005

'End of OpenGL error codes
'------------------------------------------------------------------------------
' Image Color Management Error Code

'The specified color management module is invalid.
Public Const ERROR_INVALID_CMM = 2010
'The specified color profile is invalid.
Public Const ERROR_INVALID_PROFILE = 2011
'The specified tag was not found.
Public Const ERROR_TAG_NOT_FOUND = 2012
'A required tag is not present.
Public Const ERROR_TAG_NOT_PRESENT = 2013
'The specified tag is already present.
Public Const ERROR_DUPLICATE_TAG = 2014
'The specified color profile is not associated with any device.
Public Const ERROR_PROFILE_NOT_ASSOCIATED_WITH_DEVICE = 2015
'The specified color profile was not found.
Public Const ERROR_PROFILE_NOT_FOUND = 2016
'The specified color space is invalid.
Public Const ERROR_INVALID_COLORSPACE = 2017
'Image Color Management is not enabled.
Public Const ERROR_ICM_NOT_ENABLED = 2018
'There was an error while deleting the color transform.
Public Const ERROR_DELETING_ICM_XFORM = 2019
'The specified color transform is invalid.
Public Const ERROR_INVALID_TRANSFORM = 2020
'The specified transform does not match the bitmap's color space.
Public Const ERROR_COLORSPACE_MISMATCH = 2021
'The specified named color index is not present in the profile.
Public Const ERROR_INVALID_COLORINDEX = 2022

'------------------------------------------------------------------------------
'Winnet32 Status Codes
'The range 2100 through 2999 is reserved for network status codes.
'See lmerr.h for a complete listing

'The network connection was made successfully, but the user had to be prompted
'for a password other than the one originally specified.
Public Const ERROR_CONNECTED_OTHER_PASSWORD = 2108
'The network connection was made successfully using default credentials.
Public Const ERROR_CONNECTED_OTHER_PASSWORD_DEFAULT = 2109
'The specified username is invalid.
Public Const ERROR_BAD_USERNAME = 2202
'This network connection does not exist.
Public Const ERROR_NOT_CONNECTED = 2250
'This network connection has files open or requests pending.
Public Const ERROR_OPEN_FILES = 2401
'Active connections still exist.
Public Const ERROR_ACTIVE_CONNECTIONS = 2402
'The device is in use by an active process and cannot be disconnected.
Public Const ERROR_DEVICE_IN_USE = 2404

'------------------------------------------------------------------------------
'Win32 Spooler Error Codes

'The specified print monitor is unknown.
Public Const ERROR_UNKNOWN_PRINT_MONITOR = 3000
'The specified printer driver is currently in use.
Public Const ERROR_PRINTER_DRIVER_IN_USE = 3001
'The spool file was not found.
Public Const ERROR_SPOOL_FILE_NOT_FOUND = 3002
'A StartDocPrinter call was not issued.
Public Const ERROR_SPL_NO_STARTDOC = 3003
'An AddJob call was not issued.
Public Const ERROR_SPL_NO_ADDJOB = 3004
'The specified print processor has already been installed.
Public Const ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED = 3005
'The specified print monitor has already been installed.
Public Const ERROR_PRINT_MONITOR_ALREADY_INSTALLED = 3006
'The specified print monitor does not have the required functions.
Public Const ERROR_INVALID_PRINT_MONITOR = 3007
'The specified print monitor is currently in use.
Public Const ERROR_PRINT_MONITOR_IN_USE = 3008
'The requested operation is not allowed when there are jobs queued to the printer.
Public Const ERROR_PRINTER_HAS_JOBS_QUEUED = 3009
'The requested operation is successful. Changes will not be effective until
'the system is rebooted.
Public Const ERROR_SUCCESS_REBOOT_REQUIRED = 3010
'The requested operation is successful. Changes will not be effective until
'the service is restarted.
Public Const ERROR_SUCCESS_RESTART_REQUIRED = 3011
'No printers were found.
Public Const ERROR_PRINTER_NOT_FOUND = 3012
'The printer driver is known to be unreliable.
Public Const ERROR_PRINTER_DRIVER_WARNED = 3013
'The printer driver is known to harm the system.
Public Const ERROR_PRINTER_DRIVER_BLOCKED = 3014

''''''''''''''''''
''   Wins Error Codes
''                              '''''''''''''''''

'WINS encountered an error while processing the command.
Public Const ERROR_WINS_INTERNAL = 4000
'The local WINS can not be deleted.
Public Const ERROR_CAN_NOT_DEL_LOCAL_WINS = 4001
'The importation from the file failed.
Public Const ERROR_STATIC_INIT = 4002
'The backup failed. Was a full backup done before?
Public Const ERROR_INC_BACKUP = 4003
'The backup failed. Check the directory to which you are backing the database.
Public Const ERROR_FULL_BACKUP = 4004
'The name does not exist in the WINS database.
Public Const ERROR_REC_NON_EXISTENT = 4005
'Replication with a nonconfigured partner is not allowed.
Public Const ERROR_RPL_NOT_ALLOWED = 4006

''''''''''''''''''
''   DHCP Error Codes
''                              '''''''''''''''''

'The DHCP client has obtained an IP address that is already in use on the network.
'The local interface will be disabled until the DHCP client can obtain a
'new address.
Public Const ERROR_DHCP_ADDRESS_CONFLICT = 4100

''''''''''''''''''
''   WMI Error Codes
'                              '''''''''''''''''

'The GUID passed was not recognized as valid by a WMI data provider.
Public Const ERROR_WMI_GUID_NOT_FOUND = 4200
'The instance name passed was not recognized as valid by a WMI data provider.
Public Const ERROR_WMI_INSTANCE_NOT_FOUND = 4201
'The data item ID passed was not recognized as valid by a WMI data provider.
Public Const ERROR_WMI_ITEMID_NOT_FOUND = 4202
'The WMI request could not be completed and should be retried.
Public Const ERROR_WMI_TRY_AGAIN = 4203
'The WMI data provider could not be located.
Public Const ERROR_WMI_DP_NOT_FOUND = 4204
'The WMI data provider references an instance set that has not been registered.
Public Const ERROR_WMI_UNRESOLVED_INSTANCE_REF = 4205
'The WMI data block or event notification has already been enabled.
Public Const ERROR_WMI_ALREADY_ENABLED = 4206
'The WMI data block is no longer available.
Public Const ERROR_WMI_GUID_DISCONNECTED = 4207
'The WMI data service is not available.
Public Const ERROR_WMI_SERVER_UNAVAILABLE = 4208
'The WMI data provider failed to carry out the request.
Public Const ERROR_WMI_DP_FAILED = 4209
'The WMI MOF information is not valid.
Public Const ERROR_WMI_INVALID_MOF = 4210
'The WMI registration information is not valid.
Public Const ERROR_WMI_INVALID_REGINFO = 4211
'The WMI data block or event notification has already been disabled.
Public Const ERROR_WMI_ALREADY_DISABLED = 4212
'The WMI data item or data block is read only.
Public Const ERROR_WMI_READ_ONLY = 4213
'The WMI data item or data block could not be changed.
Public Const ERROR_WMI_SET_FAILURE = 4214

'------------------------------------------------------------------------------
'NT Media Services (RSM) Error Codes

'The media identifier does not represent a valid medium.
Public Const ERROR_INVALID_MEDIA = 4300
'The library identifier does not represent a valid library.
Public Const ERROR_INVALID_LIBRARY = 4301
'The media pool identifier does not represent a valid media pool.
Public Const ERROR_INVALID_MEDIA_POOL = 4302
'The drive and medium are not compatible or exist in different libraries.
Public Const ERROR_DRIVE_MEDIA_MISMATCH = 4303
'The medium currently exists in an offline library and must be online to
'perform this operation.
Public Const ERROR_MEDIA_OFFLINE = 4304
'The operation cannot be performed on an offline library.
Public Const ERROR_LIBRARY_OFFLINE = 4305
'The library, drive, or media pool is empty.
Public Const ERROR_EMPTY = 4306
'The library, drive, or media pool must be empty to perform this operation.
Public Const ERROR_NOT_EMPTY = 4307
'No media is currently available in this media pool or library.
Public Const ERROR_MEDIA_UNAVAILABLE = 4308
'A resource required for this operation is disabled.
Public Const ERROR_RESOURCE_DISABLED = 4309
'The media identifier does not represent a valid cleaner.
Public Const ERROR_INVALID_CLEANER = 4310
'The drive cannot be cleaned or does not support cleaning.
Public Const ERROR_UNABLE_TO_CLEAN = 4311
'The object identifier does not represent a valid object.
Public Const ERROR_OBJECT_NOT_FOUND = 4312
'Unable to read from or write to the database.
Public Const ERROR_DATABASE_FAILURE = 4313
'The database is full.
Public Const ERROR_DATABASE_FULL = 4314
'The medium is not compatible with the device or media pool.
Public Const ERROR_MEDIA_INCOMPATIBLE = 4315
'The resource required for this operation does not exist.
Public Const ERROR_RESOURCE_NOT_PRESENT = 4316
'The operation identifier is not valid.
Public Const ERROR_INVALID_OPERATION = 4317
'The media is not mounted or ready for use.
Public Const ERROR_MEDIA_NOT_AVAILABLE = 4318
'The device is not ready for use.
Public Const ERROR_DEVICE_NOT_AVAILABLE = 4319
'The operator or administrator has refused the request.
Public Const ERROR_REQUEST_REFUSED = 4320
'The drive identifier does not represent a valid drive.
Public Const ERROR_INVALID_DRIVE_OBJECT = 4321
'Library is full. No slot is available for use.
Public Const ERROR_LIBRARY_FULL = 4322
'The transport cannot access the medium.
Public Const ERROR_MEDIUM_NOT_ACCESSIBLE = 4323
'Unable to load the medium into the drive.
Public Const ERROR_UNABLE_TO_LOAD_MEDIUM = 4324
'Unable to retrieve the drive status.
Public Const ERROR_UNABLE_TO_INVENTORY_DRIVE = 4325
'Unable to retrieve the slot status.
Public Const ERROR_UNABLE_TO_INVENTORY_SLOT = 4326
'Unable to retrieve status about the transport.
Public Const ERROR_UNABLE_TO_INVENTORY_TRANSPORT = 4327
'Cannot use the transport because it is already in use.
Public Const ERROR_TRANSPORT_FULL = 4328
'Unable to open or close the inject/eject port.
Public Const ERROR_CONTROLLING_IEPORT = 4329
'Unable to eject the medium because it is in a drive.
Public Const ERROR_UNABLE_TO_EJECT_MOUNTED_MEDIA = 4330
'A cleaner slot is already reserved.
Public Const ERROR_CLEANER_SLOT_SET = 4331
'A cleaner slot is not reserved.
Public Const ERROR_CLEANER_SLOT_NOT_SET = 4332
'The cleaner cartridge has performed the maximum number of drive cleanings.
Public Const ERROR_CLEANER_CARTRIDGE_SPENT = 4333
'Unexpected on-medium identifier.
Public Const ERROR_UNEXPECTED_OMID = 4334
'The last remaining item in this group or resource cannot be deleted.
Public Const ERROR_CANT_DELETE_LAST_ITEM = 4335
'The message provided exceeds the maximum size allowed for this parameter.
Public Const ERROR_MESSAGE_EXCEEDS_MAX_SIZE = 4336
'The volume contains system or paging files.
Public Const ERROR_VOLUME_CONTAINS_SYS_FILES = 4337
'The media type cannot be removed from this library since at least one drive
'in the library reports it can support this media type.
Public Const ERROR_INDIGENOUS_TYPE = 4338
'This offline media cannot be mounted on this system since no enabled drives
'are present which can be used.
Public Const ERROR_NO_SUPPORTING_DRIVES = 4339
'A cleaner cartridge is present in the tape library.
Public Const ERROR_CLEANER_CARTRIDGE_INSTALLED = 4340

''------------------------------------------------------------------------------
  'NT Remote Storage Service Error Codes

'The remote storage service was not able to recall the file.
Public Const ERROR_FILE_OFFLINE = 4350
'The remote storage service is not operational at this time.
Public Const ERROR_REMOTE_STORAGE_NOT_ACTIVE = 4351
'The remote storage service encountered a media error.
Public Const ERROR_REMOTE_STORAGE_MEDIA_ERROR = 4352

''------------------------------------------------------------------------------
  'NT Reparse Points Error Codes

'The file or directory is not a reparse point.
Public Const ERROR_NOT_A_REPARSE_POINT = 4390
'The reparse point attribute cannot be set because it conflicts with an existing
'attribute.
Public Const ERROR_REPARSE_ATTRIBUTE_CONFLICT = 4391
'The data present in the reparse point buffer is invalid.
Public Const ERROR_INVALID_REPARSE_DATA = 4392
'The tag present in the reparse point buffer is invalid.
Public Const ERROR_REPARSE_TAG_INVALID = 4393
'There is a mismatch between the tag specified in the request and the tag
'present in the reparse point.
Public Const ERROR_REPARSE_TAG_MISMATCH = 4394

'------------------------------------------------------------------------------
  'NT Single Instance Store Error Codes

'Single Instance Storage is not available on this volume.
Public Const ERROR_VOLUME_NOT_SIS_ENABLED = 4500

'------------------------------------------------------------------------------
'   Cluster Error Codes

'The cluster resource cannot be moved to another group because other resources
'are dependent on it.
Public Const ERROR_DEPENDENT_RESOURCE_EXISTS = 5001
'The cluster resource dependency cannot be found.
Public Const ERROR_DEPENDENCY_NOT_FOUND = 5002
'The cluster resource cannot be made dependent on the specified resource
'because it is already dependent.
Public Const ERROR_DEPENDENCY_ALREADY_EXISTS = 5003
'The cluster resource is not online.
Public Const ERROR_RESOURCE_NOT_ONLINE = 5004
'A cluster node is not available for this operation.
Public Const ERROR_HOST_NODE_NOT_AVAILABLE = 5005
'The cluster resource is not available.
Public Const ERROR_RESOURCE_NOT_AVAILABLE = 5006
'The cluster resource could not be found.
Public Const ERROR_RESOURCE_NOT_FOUND = 5007
'The cluster is being shut down.
Public Const ERROR_SHUTDOWN_CLUSTER = 5008
'A cluster node cannot be evicted from the cluster unless the node is down
'or it is the last node.
Public Const ERROR_CANT_EVICT_ACTIVE_NODE = 5009
'The object already exists.
Public Const ERROR_OBJECT_ALREADY_EXISTS = 5010
'The object is already in the list.
Public Const ERROR_OBJECT_IN_LIST = 5011
'The cluster group is not available for any new requests.
Public Const ERROR_GROUP_NOT_AVAILABLE = 5012
'The cluster group could not be found.
Public Const ERROR_GROUP_NOT_FOUND = 5013
'The operation could not be completed because the cluster group is not online.
Public Const ERROR_GROUP_NOT_ONLINE = 5014
'The cluster node is not the owner of the resource.
Public Const ERROR_HOST_NODE_NOT_RESOURCE_OWNER = 5015
'The cluster node is not the owner of the group.
Public Const ERROR_HOST_NODE_NOT_GROUP_OWNER = 5016
'The cluster resource could not be created in the specified resource monitor.
Public Const ERROR_RESMON_CREATE_FAILED = 5017
'The cluster resource could not be brought online by the resource monitor.
Public Const ERROR_RESMON_ONLINE_FAILED = 5018
'The operation could not be completed because the cluster resource is online.
Public Const ERROR_RESOURCE_ONLINE = 5019
'The cluster resource could not be deleted or brought offline because it is the
'quorum resource.
Public Const ERROR_QUORUM_RESOURCE = 5020
'The cluster could not make the specified resource a quorum resource because it
'is not capable of being a quorum resource.
Public Const ERROR_NOT_QUORUM_CAPABLE = 5021
'The cluster software is shutting down.
Public Const ERROR_CLUSTER_SHUTTING_DOWN = 5022
'The group or resource is not in the correct state to perform the requested
'operation.
Public Const ERROR_INVALID_STATE = 5023
'The properties were stored but not all changes will take effect until the next
'time the resource is brought online.
Public Const ERROR_RESOURCE_PROPERTIES_STORED = 5024
'The cluster could not make the specified resource a quorum resource because it
'does not belong to a shared storage class.
Public Const ERROR_NOT_QUORUM_CLASS = 5025
'The cluster resource could not be deleted since it is a core resource.
Public Const ERROR_CORE_RESOURCE = 5026
'The quorum resource failed to come online.
Public Const ERROR_QUORUM_RESOURCE_ONLINE_FAILED = 5027
'The quorum log could not be created or mounted successfully.
Public Const ERROR_QUORUMLOG_OPEN_FAILED = 5028
'The cluster log is corrupt.
Public Const ERROR_CLUSTERLOG_CORRUPT = 5029
'The record could not be written to the cluster log since it exceeds the maximum
'size.
Public Const ERROR_CLUSTERLOG_RECORD_EXCEEDS_MAXSIZE = 5030
'The cluster log exceeds its maximum size.
Public Const ERROR_CLUSTERLOG_EXCEEDS_MAXSIZE = 5031
'No checkpoint record was found in the cluster log.
Public Const ERROR_CLUSTERLOG_CHKPOINT_NOT_FOUND = 5032
'The minimum required disk space needed for logging is not available.
Public Const ERROR_CLUSTERLOG_NOT_ENOUGH_SPACE = 5033
'The cluster node failed to take control of the quorum resource because
'the resource is owned by another active node.
Public Const ERROR_QUORUM_OWNER_ALIVE = 5034
'A cluster network is not available for this operation.
Public Const ERROR_NETWORK_NOT_AVAILABLE = 5035
'A cluster node is not available for this operation.
Public Const ERROR_NODE_NOT_AVAILABLE = 5036
'All cluster nodes must be running to perform this operation.
Public Const ERROR_ALL_NODES_NOT_AVAILABLE = 5037
'A cluster resource failed.
Public Const ERROR_RESOURCE_FAILED = 5038
'The cluster node is not valid.
Public Const ERROR_CLUSTER_INVALID_NODE = 5039
'The cluster node already exists.
Public Const ERROR_CLUSTER_NODE_EXISTS = 5040
'A node is in the process of joining the cluster.
Public Const ERROR_CLUSTER_JOIN_IN_PROGRESS = 5041
'The cluster node was not found.
Public Const ERROR_CLUSTER_NODE_NOT_FOUND = 5042
'The cluster local node information was not found.
Public Const ERROR_CLUSTER_LOCAL_NODE_NOT_FOUND = 5043
'The cluster network already exists.
Public Const ERROR_CLUSTER_NETWORK_EXISTS = 5044
'The cluster network was not found.
Public Const ERROR_CLUSTER_NETWORK_NOT_FOUND = 5045
'The cluster network interface already exists.
Public Const ERROR_CLUSTER_NETINTERFACE_EXISTS = 5046
'The cluster network interface was not found.
Public Const ERROR_CLUSTER_NETINTERFACE_NOT_FOUND = 5047
'The cluster request is not valid for this object.
Public Const ERROR_CLUSTER_INVALID_REQUEST = 5048
'The cluster network provider is not valid.
Public Const ERROR_CLUSTER_INVALID_NETWORK_PROVIDER = 5049
'The cluster node is down.
Public Const ERROR_CLUSTER_NODE_DOWN = 5050
'The cluster node is not reachable.
Public Const ERROR_CLUSTER_NODE_UNREACHABLE = 5051
'The cluster node is not a member of the cluster.
Public Const ERROR_CLUSTER_NODE_NOT_MEMBER = 5052
'A cluster join operation is not in progress.
Public Const ERROR_CLUSTER_JOIN_NOT_IN_PROGRESS = 5053
'The cluster network is not valid.
Public Const ERROR_CLUSTER_INVALID_NETWORK = 5054
'The cluster node is up.
Public Const ERROR_CLUSTER_NODE_UP = 5056
'The cluster IP address is already in use.
Public Const ERROR_CLUSTER_IPADDR_IN_USE = 5057
'The cluster node is not paused.
Public Const ERROR_CLUSTER_NODE_NOT_PAUSED = 5058
'No cluster security context is available.
Public Const ERROR_CLUSTER_NO_SECURITY_CONTEXT = 5059
'The cluster network is not configured for internal cluster communication.
Public Const ERROR_CLUSTER_NETWORK_NOT_INTERNAL = 5060
'The cluster node is already up.
Public Const ERROR_CLUSTER_NODE_ALREADY_UP = 5061
'The cluster node is already down.
Public Const ERROR_CLUSTER_NODE_ALREADY_DOWN = 5062
'The cluster network is already online.
Public Const ERROR_CLUSTER_NETWORK_ALREADY_ONLINE = 5063
'The cluster network is already offline.
Public Const ERROR_CLUSTER_NETWORK_ALREADY_OFFLINE = 5064
'The cluster node is already a member of the cluster.
Public Const ERROR_CLUSTER_NODE_ALREADY_MEMBER = 5065
'The cluster network is the only one configured for internal cluster
'communication between two or more active cluster nodes.
'The internal communication capability cannot be removed from the network.
Public Const ERROR_CLUSTER_LAST_INTERNAL_NETWORK = 5066
'One or more cluster resources depend on the network to provide service
'to clients. The client access capability cannot be removed from the network.
Public Const ERROR_CLUSTER_NETWORK_HAS_DEPENDENTS = 5067
'This operation cannot be performed on the cluster resource as it
'the quorum resource. You may not bring the quorum resource offline or
'modify its possible owners list.
Public Const ERROR_INVALID_OPERATION_ON_QUORUM = 5068
'The cluster quorum resource is not allowed to have any dependencies.
Public Const ERROR_DEPENDENCY_NOT_ALLOWED = 5069
'The cluster node is paused.
Public Const ERROR_CLUSTER_NODE_PAUSED = 5070
'The cluster resource cannot be brought online. The owner node cannot run
'this resource.
Public Const ERROR_NODE_CANT_HOST_RESOURCE = 5071
'The cluster node is not ready to perform the requested operation.
Public Const ERROR_CLUSTER_NODE_NOT_READY = 5072
'The cluster node is shutting down.
Public Const ERROR_CLUSTER_NODE_SHUTTING_DOWN = 5073
'The cluster join operation was aborted.
Public Const ERROR_CLUSTER_JOIN_ABORTED = 5074
'The cluster join operation failed due to incompatible software versions
'between the joining node and its sponsor.
Public Const ERROR_CLUSTER_INCOMPATIBLE_VERSIONS = 5075
'This resource cannot be created because the cluster has reached the limit
'on the number of resources it can monitor.
Public Const ERROR_CLUSTER_MAXNUM_OF_RESOURCES_EXCEEDED = 5076
'The system configuration changed during the cluster join or form operation.
'The join or form operation was aborted.
Public Const ERROR_CLUSTER_SYSTEM_CONFIG_CHANGED = 5077
'The specified resource type was not found.
Public Const ERROR_CLUSTER_RESOURCE_TYPE_NOT_FOUND = 5078
'The specified node does not support a resource of this type. This may be due t
'o version inconsistencies or due to the absence of the resource DLL on this node.
Public Const ERROR_CLUSTER_RESTYPE_NOT_SUPPORTED = 5079
'The specified resource name is not supported by this resource DLL.
'This may be due to a bad (or changed) name supplied to the resource DLL.
Public Const ERROR_CLUSTER_RESNAME_NOT_FOUND = 5080
'No authentication package could be registered with the RPC server.
Public Const ERROR_CLUSTER_NO_RPC_PACKAGES_REGISTERED = 5081
'You cannot bring the group online because the owner of the group is not in
'the preferred list for the group. To change the owner node for the group,
'move the group.
Public Const ERROR_CLUSTER_OWNER_NOT_IN_PREFLIST = 5082
'The join operation failed because the cluster database sequence number has
'changed or is incompatible with the locker node. This may happen during
'a join operation if the cluster database was changing during the join.
Public Const ERROR_CLUSTER_DATABASE_SEQMISMATCH = 5083
'The resource monitor will not allow the fail operation to be performed while
'the resource is in its current state. This may happen if the resource is in a pending state.
Public Const ERROR_RESMON_INVALID_STATE = 5084
'A non locker code got a request to reserve the lock for making global updates.
Public Const ERROR_CLUSTER_GUM_NOT_LOCKER = 5085
'The quorum disk could not be located by the cluster service.
Public Const ERROR_QUORUM_DISK_NOT_FOUND = 5086
'The backed up cluster database is possibly corrupt.
Public Const ERROR_DATABASE_BACKUP_CORRUPT = 5087
'A DFS root already exists in this cluster node.
Public Const ERROR_CLUSTER_NODE_ALREADY_HAS_DFS_ROOT = 5088
'An attempt to modify a resource property failed because it conflicts with
'another existing property.
Public Const ERROR_RESOURCE_PROPERTY_UNCHANGEABLE = 5089

'------------------------------------------------------------------------------
'Codes from 4300 through 5889 overlap with codes in ds\published\inc\apperr2.w.
'Do not add any more error codes in that range.

'An operation was attempted that is incompatible with the current membership
'state of the node.
Public Const ERROR_CLUSTER_MEMBERSHIP_INVALID_STATE = 5890
'The quorum resource does not contain the quorum log.
Public Const ERROR_CLUSTER_QUORUMLOG_NOT_FOUND = 5891
'The membership engine requested shutdown of the cluster service on this node.
Public Const ERROR_CLUSTER_MEMBERSHIP_HALT = 5892
'The join operation failed because the cluster instance ID of the joining node
'does not match the cluster instance ID of the sponsor node.
Public Const ERROR_CLUSTER_INSTANCE_ID_MISMATCH = 5893
'A matching network for the specified IP address could not be found.
'Please also specify a subnet mask and a cluster network.
Public Const ERROR_CLUSTER_NETWORK_NOT_FOUND_FOR_IP = 5894
'The actual data type of the property did not match the expected data type of
'the property.
Public Const ERROR_CLUSTER_PROPERTY_DATA_TYPE_MISMATCH = 5895
'The cluster node was evicted from the cluster successfully, but the node
'was not cleaned up. Extended status information explaining why the node was
'not cleaned up is available.
Public Const ERROR_CLUSTER_EVICT_WITHOUT_CLEANUP = 5896
'Two or more parameter values specified for a resource's properties are in conflict.
Public Const ERROR_CLUSTER_PARAMETER_MISMATCH = 5897
'This computer cannot be made a member of a cluster.
Public Const ERROR_NODE_CANNOT_BE_CLUSTERED = 5898
'This computer cannot be made a member of a cluster because it does not have
'the correct version of Windows installed.
Public Const ERROR_CLUSTER_WRONG_OS_VERSION = 5899
'A cluster cannot be created with the specified cluster name because that
'cluster name is already in use. Specify a different name for the cluster.
Public Const ERROR_CLUSTER_CANT_CREATE_DUP_CLUSTER_NAME = 5900
'The cluster configuration action has already been committed.
Public Const ERROR_CLUSCFG_ALREADY_COMMITTED = 5901
'The cluster configuration action could not be rolled back.
Public Const ERROR_CLUSCFG_ROLLBACK_FAILED = 5902
'The drive letter assigned to a system disk on one node conflicted with the
'drive letter assigned to a disk on another node.
Public Const ERROR_CLUSCFG_SYSTEM_DISK_DRIVE_LETTER_CONFLICT = 5903
'One or more nodes in the cluster are running a version of Windows that does
'not support this operation.
Public Const ERROR_CLUSTER_OLD_VERSION = 5904
'The name of the corresponding computer account doesn't match the Network Name
'for this resource.
Public Const ERROR_CLUSTER_MISMATCHED_COMPUTER_ACCT_NAME = 5905

'------------------------------------------------------------------------------
'   EFS Error Codes

'The specified file could not be encrypted.
Public Const ERROR_ENCRYPTION_FAILED = 6000
'The specified file could not be decrypted.
Public Const ERROR_DECRYPTION_FAILED = 6001
'The specified file is encrypted and the user does not have the ability to
'decrypt it.
Public Const ERROR_FILE_ENCRYPTED = 6002
'There is no valid encryption recovery policy configured for this system.
Public Const ERROR_NO_RECOVERY_POLICY = 6003
'The required encryption driver is not loaded for this system.
Public Const ERROR_NO_EFS = 6004
'The file was encrypted with a different encryption driver than is currently
'loaded.
Public Const ERROR_WRONG_EFS = 6005
'There are no EFS keys defined for the user.
Public Const ERROR_NO_USER_KEYS = 6006
'The specified file is not encrypted.
Public Const ERROR_FILE_NOT_ENCRYPTED = 6007
'The specified file is not in the defined EFS export format.
Public Const ERROR_NOT_EXPORT_FORMAT = 6008
'The specified file is read only.
Public Const ERROR_FILE_READ_ONLY = 6009
'The directory has been disabled for encryption.
Public Const ERROR_DIR_EFS_DISALLOWED = 6010
'The server is not trusted for remote encryption operation.
Public Const ERROR_EFS_SERVER_NOT_TRUSTED = 6011
'Recovery policy configured for this system contains invalid recovery certificate.
Public Const ERROR_BAD_RECOVERY_POLICY = 6012
'The encryption algorithm used on the source file needs a bigger key buffer
'than the one on the destination file.
Public Const ERROR_EFS_ALG_BLOB_TOO_BIG = 6013
'The disk partition does not support file encryption.
Public Const ERROR_VOLUME_NOT_SUPPORT_EFS = 6014
'This machine is disabled for file encryption.
Public Const ERROR_EFS_DISABLED = 6015
'A newer system is required to decrypt this encrypted file.
Public Const ERROR_EFS_VERSION_NOT_SUPPORT = 6016

'This message number is for historical purposes and cannot be changed or re-used.


'The list of servers for this workgroup is not currently available
Public Const ERROR_NO_BROWSER_SERVERS_FOUND = 6118

'------------------------------------------------------------------------------
'Task Scheduler Error Codes that NET START must understand

'The Task Scheduler service must be configured to run in the System account
'to function properly. Individual tasks may be configured to run in other accounts.
Public Const SCHED_E_SERVICE_NOT_LOCALSYSTEM = 6200

'------------------------------------------------------------------------------
'Terminal Server Error Codes

'The specified session name is invalid.
Public Const ERROR_CTX_WINSTATION_NAME_INVALID = 7001
'The specified protocol driver is invalid.
Public Const ERROR_CTX_INVALID_PD = 7002
'The specified protocol driver was not found in the system path.
Public Const ERROR_CTX_PD_NOT_FOUND = 7003
'The specified terminal connection driver was not found in the system path.
Public Const ERROR_CTX_WD_NOT_FOUND = 7004
'A registry key for event logging could not be created for this session.
Public Const ERROR_CTX_CANNOT_MAKE_EVENTLOG_ENTRY = 7005
'A service with the same name already exists on the system.
Public Const ERROR_CTX_SERVICE_NAME_COLLISION = 7006
'A close operation is pending on the session.
Public Const ERROR_CTX_CLOSE_PENDING = 7007
'There are no free output buffers available.
Public Const ERROR_CTX_NO_OUTBUF = 7008
'The MODEM.INF file was not found.
Public Const ERROR_CTX_MODEM_INF_NOT_FOUND = 7009
'The modem name was not found in MODEM.INF.
Public Const ERROR_CTX_INVALID_MODEMNAME = 7010
'The modem did not accept the command sent to it. Verify that the configured
'modem name matches the attached modem.
Public Const ERROR_CTX_MODEM_RESPONSE_ERROR = 7011
'The modem did not respond to the command sent to it. Verify that the modem
'is properly cabled and powered on.
Public Const ERROR_CTX_MODEM_RESPONSE_TIMEOUT = 7012
'Carrier detect has failed or carrier has been dropped due to disconnect.
Public Const ERROR_CTX_MODEM_RESPONSE_NO_CARRIER = 7013
'Dial tone not detected within the required time. Verify that the phone cable
'is properly attached and functional.
Public Const ERROR_CTX_MODEM_RESPONSE_NO_DIALTONE = 7014
'Busy signal detected at remote site on callback.
Public Const ERROR_CTX_MODEM_RESPONSE_BUSY = 7015
'Voice detected at remote site on callback.
Public Const ERROR_CTX_MODEM_RESPONSE_VOICE = 7016
'Transport driver error
Public Const ERROR_CTX_TD_ERROR = 7017
'The specified session cannot be found.
Public Const ERROR_CTX_WINSTATION_NOT_FOUND = 7022
'The specified session name is already in use.
Public Const ERROR_CTX_WINSTATION_ALREADY_EXISTS = 7023
'The requested operation cannot be completed because the terminal connection
'is currently busy processing a connect, disconnect, reset, or delete operation.
Public Const ERROR_CTX_WINSTATION_BUSY = 7024
'An attempt has been made to connect to a session whose video mode is not
'supported by the current client.
Public Const ERROR_CTX_BAD_VIDEO_MODE = 7025
'The application attempted to enable DOS graphics mode.
'DOS graphics mode is not supported.
Public Const ERROR_CTX_GRAPHICS_INVALID = 7035
'Your interactive logon privilege has been disabled.
'Please contact your administrator.
Public Const ERROR_CTX_LOGON_DISABLED = 7037
'The requested operation can be performed only on the system console.
'This is most often the result of a driver or system DLL requiring direct
'console access.
Public Const ERROR_CTX_NOT_CONSOLE = 7038
'The client failed to respond to the server connect message.
Public Const ERROR_CTX_CLIENT_QUERY_TIMEOUT = 7040
'Disconnecting the console session is not supported.
Public Const ERROR_CTX_CONSOLE_DISCONNECT = 7041
'Reconnecting a disconnected session to the console is not supported.
Public Const ERROR_CTX_CONSOLE_CONNECT = 7042
'The request to control another session remotely was denied.
Public Const ERROR_CTX_SHADOW_DENIED = 7044
'The requested session access is denied.
Public Const ERROR_CTX_WINSTATION_ACCESS_DENIED = 7045
'The specified terminal connection driver is invalid.
Public Const ERROR_CTX_INVALID_WD = 7049
'The requested session cannot be controlled remotely.
'This may be because the session is disconnected or does not currently have
'a user logged on.
Public Const ERROR_CTX_SHADOW_INVALID = 7050
'The requested session is not configured to allow remote control.
Public Const ERROR_CTX_SHADOW_DISABLED = 7051
'Your request to connect to this Terminal Server has been rejected.
'Your Terminal Server client license number is currently being used by another
'user.
'Please call your system administrator to obtain a unique license number.
Public Const ERROR_CTX_CLIENT_LICENSE_IN_USE = 7052
'Your request to connect to this Terminal Server has been rejected.
'Your Terminal Server client license number has not been entered for this copy
'of the Terminal Server client.
'Please contact your system administrator.
Public Const ERROR_CTX_CLIENT_LICENSE_NOT_SET = 7053
'The system has reached its licensed logon limit.
'Please try again later.
Public Const ERROR_CTX_LICENSE_NOT_AVAILABLE = 7054
'The client you are using is not licensed to use this system.
'Your logon request is denied.
Public Const ERROR_CTX_LICENSE_CLIENT_INVALID = 7055
'The system license has expired. Your logon request is denied.
Public Const ERROR_CTX_LICENSE_EXPIRED = 7056
'Remote control could not be terminated because the specified session is
'not currently being remotely controlled.
Public Const ERROR_CTX_SHADOW_NOT_RUNNING = 7057
'The remote control of the console was terminated because the display mode
'was changed. Changing the display mode in a remote control session is not supported.
Public Const ERROR_CTX_SHADOW_ENDED_BY_MODE_CHANGE = 7058
'Activation has already been reset the maximum number of times for this
'installation. Your activation timer will not be cleared.
Public Const ERROR_ACTIVATION_COUNT_EXCEEDED = 7059

'------------------------------------------------------------------------------
'Traffic Control Error Codes 7500 to  7999 defined in: tcerror.h

'Active Directory Error Codes 8000 to  8999

'===============================================================================
'FACILITY_FILE_REPLICATION_SERVICE

'The file replication service API was called incorrectly.
Public Const FRS_ERR_INVALID_API_SEQUENCE = 8001
'The file replication service cannot be started.
Public Const FRS_ERR_STARTING_SERVICE = 8002
'The file replication service cannot be stopped.
Public Const FRS_ERR_STOPPING_SERVICE = 8003
'The file replication service API terminated the request.
'The event log may have more information.
Public Const FRS_ERR_INTERNAL_API = 8004
'The file replication service terminated the request.
'The event log may have more information.
Public Const FRS_ERR_INTERNAL = 8005
'The file replication service cannot be contacted.
'The event log may have more information.
Public Const FRS_ERR_SERVICE_COMM = 8006
'The file replication service cannot satisfy the request because the user
'has insufficient privileges.
'The event log may have more information.
Public Const FRS_ERR_INSUFFICIENT_PRIV = 8007
'The file replication service cannot satisfy the request because authenticated
'RPC is not available.
'The event log may have more information.
Public Const FRS_ERR_AUTHENTICATION = 8008
'The file replication service cannot satisfy the request because the user has
'insufficient privileges on the domain controller.
'The event log may have more information.
Public Const FRS_ERR_PARENT_INSUFFICIENT_PRIV = 8009
'The file replication service cannot satisfy the request because authenticated
'RPC is not available on the domain controller.
'The event log may have more information.
Public Const FRS_ERR_PARENT_AUTHENTICATION = 8010
'The file replication service cannot communicate with the file replication
'service on the domain controller.
'The event log may have more information.
Public Const FRS_ERR_CHILD_TO_PARENT_COMM = 8011
'The file replication service on the domain controller cannot communicate
'with the file replication service on this computer.
'The event log may have more information.
Public Const FRS_ERR_PARENT_TO_CHILD_COMM = 8012
'The file replication service cannot populate the system volume because of
'an internal error.
'The event log may have more information.
Public Const FRS_ERR_SYSVOL_POPULATE = 8013
'The file replication service cannot populate the system volume because of
'an internal timeout.
'The event log may have more information.
Public Const FRS_ERR_SYSVOL_POPULATE_TIMEOUT = 8014
'The file replication service cannot process the request. The system volume
'is busy with a previous request.
Public Const FRS_ERR_SYSVOL_IS_BUSY = 8015
'The file replication service cannot stop replicating the system volume because
'of an internal error.
'The event log may have more information.
Public Const FRS_ERR_SYSVOL_DEMOTE = 8016
'The file replication service detected an invalid parameter.
Public Const FRS_ERR_INVALID_SERVICE_PARAMETER = 8017

'*****************
'FACILITY DIRECTORY SERVICE
'*****************
Public Const DS_S_SUCCESS = NO_ERROR


'An error occurred while installing the directory service. For more information,
'see the event log.
Public Const ERROR_DS_NOT_INSTALLED = 8200
'The directory service evaluated group memberships locally.
Public Const ERROR_DS_MEMBERSHIP_EVALUATED_LOCALLY = 8201
'The specified directory service attribute or value does not exist.
Public Const ERROR_DS_NO_ATTRIBUTE_OR_VALUE = 8202
'The attribute syntax specified to the directory service is invalid.
Public Const ERROR_DS_INVALID_ATTRIBUTE_SYNTAX = 8203
'The attribute type specified to the directory service is not defined.
Public Const ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED = 8204
'The specified directory service attribute or value already exists.
Public Const ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS = 8205
'The directory service is busy.
Public Const ERROR_DS_BUSY = 8206
'The directory service is unavailable.
Public Const ERROR_DS_UNAVAILABLE = 8207
'The directory service was unable to allocate a relative identifier.
Public Const ERROR_DS_NO_RIDS_ALLOCATED = 8208
'The directory service has exhausted the pool of relative identifiers.
Public Const ERROR_DS_NO_MORE_RIDS = 8209
'The requested operation could not be performed because the directory service
'is not the master for that type of operation.
Public Const ERROR_DS_INCORRECT_ROLE_OWNER = 8210
'The directory service was unable to initialize the subsystem that allocates
'relative identifiers.
Public Const ERROR_DS_RIDMGR_INIT_ERROR = 8211
'The requested operation did not satisfy one or more constraints associated
'with the class of the object.
Public Const ERROR_DS_OBJ_CLASS_VIOLATION = 8212
'The directory service can perform the requested operation only on a leaf object.
Public Const ERROR_DS_CANT_ON_NON_LEAF = 8213
'The directory service cannot perform the requested operation on the RDN
'attribute of an object.
Public Const ERROR_DS_CANT_ON_RDN = 8214
'The directory service detected an attempt to modify the object class of an object.
Public Const ERROR_DS_CANT_MOD_OBJ_CLASS = 8215
'The requested cross-domain move operation could not be performed.
Public Const ERROR_DS_CROSS_DOM_MOVE_ERROR = 8216
'Unable to contact the global catalog server.
Public Const ERROR_DS_GC_NOT_AVAILABLE = 8217
'The policy object is shared and can only be modified at the root.
Public Const ERROR_SHARED_POLICY = 8218
'The policy object does not exist.
Public Const ERROR_POLICY_OBJECT_NOT_FOUND = 8219
'The requested policy information is only in the directory service.
Public Const ERROR_POLICY_ONLY_IN_DS = 8220
'A domain controller promotion is currently active.
Public Const ERROR_PROMOTION_ACTIVE = 8221
'A domain controller promotion is not currently active
Public Const ERROR_NO_PROMOTION_ACTIVE = 8222

'8223 unused


'An operations error occurred.
Public Const ERROR_DS_OPERATIONS_ERROR = 8224
'A protocol error occurred.
Public Const ERROR_DS_PROTOCOL_ERROR = 8225
'The time limit for this request was exceeded.
Public Const ERROR_DS_TIMELIMIT_EXCEEDED = 8226
'The size limit for this request was exceeded.
Public Const ERROR_DS_SIZELIMIT_EXCEEDED = 8227
'The administrative limit for this request was exceeded.
Public Const ERROR_DS_ADMIN_LIMIT_EXCEEDED = 8228
'The compare response was false.
Public Const ERROR_DS_COMPARE_FALSE = 8229
'The compare response was true.
Public Const ERROR_DS_COMPARE_TRUE = 8230
'The requested authentication method is not supported by the server.
Public Const ERROR_DS_AUTH_METHOD_NOT_SUPPORTED = 8231
'A more secure authentication method is required for this server.
Public Const ERROR_DS_STRONG_AUTH_REQUIRED = 8232
'Inappropriate authentication.
Public Const ERROR_DS_INAPPROPRIATE_AUTH = 8233
'The authentication mechanism is unknown.
Public Const ERROR_DS_AUTH_UNKNOWN = 8234
'A referral was returned from the server.
Public Const ERROR_DS_REFERRAL = 8235
'The server does not support the requested critical extension.
Public Const ERROR_DS_UNAVAILABLE_CRIT_EXTENSION = 8236
'This request requires a secure connection.
Public Const ERROR_DS_CONFIDENTIALITY_REQUIRED = 8237
'Inappropriate matching.
Public Const ERROR_DS_INAPPROPRIATE_MATCHING = 8238
'A constraint violation occurred.
Public Const ERROR_DS_CONSTRAINT_VIOLATION = 8239
'There is no such object on the server.
Public Const ERROR_DS_NO_SUCH_OBJECT = 8240
'There is an alias problem.
Public Const ERROR_DS_ALIAS_PROBLEM = 8241
'An invalid dn syntax has been specified.
Public Const ERROR_DS_INVALID_DN_SYNTAX = 8242
'The object is a leaf object.
Public Const ERROR_DS_IS_LEAF = 8243
'There is an alias dereferencing problem.
Public Const ERROR_DS_ALIAS_DEREF_PROBLEM = 8244
'The server is unwilling to process the request.
Public Const ERROR_DS_UNWILLING_TO_PERFORM = 8245
'A loop has been detected.
Public Const ERROR_DS_LOOP_DETECT = 8246
'There is a naming violation.
Public Const ERROR_DS_NAMING_VIOLATION = 8247
'The result set is too large.
Public Const ERROR_DS_OBJECT_RESULTS_TOO_LARGE = 8248
'The operation affects multiple DSAs
Public Const ERROR_DS_AFFECTS_MULTIPLE_DSAS = 8249
'The server is not operational.
Public Const ERROR_DS_SERVER_DOWN = 8250
'A local error has occurred.
Public Const ERROR_DS_LOCAL_ERROR = 8251
'An encoding error has occurred.
Public Const ERROR_DS_ENCODING_ERROR = 8252
'A decoding error has occurred.
Public Const ERROR_DS_DECODING_ERROR = 8253
'The search filter cannot be recognized.
Public Const ERROR_DS_FILTER_UNKNOWN = 8254
'One or more parameters are illegal.
Public Const ERROR_DS_PARAM_ERROR = 8255
'The specified method is not supported.
Public Const ERROR_DS_NOT_SUPPORTED = 8256
'No results were returned.
Public Const ERROR_DS_NO_RESULTS_RETURNED = 8257
'The specified control is not supported by the server.
Public Const ERROR_DS_CONTROL_NOT_FOUND = 8258
'A referral loop was detected by the client.
Public Const ERROR_DS_CLIENT_LOOP = 8259
'The preset referral limit was exceeded.
Public Const ERROR_DS_REFERRAL_LIMIT_EXCEEDED = 8260
'The search requires a SORT control.
Public Const ERROR_DS_SORT_CONTROL_MISSING = 8261
'The search results exceed the offset range specified.
Public Const ERROR_DS_OFFSET_RANGE_ERROR = 8262
'The root object must be the head of a naming context. The root object
'cannot have an instantiated parent.
Public Const ERROR_DS_ROOT_MUST_BE_NC = 8301
'The add replica operation cannot be performed. The naming context must
'be writeable in order to create the replica.
Public Const ERROR_DS_ADD_REPLICA_INHIBITED = 8302
'A reference to an attribute that is not defined in the schema occurred.
Public Const ERROR_DS_ATT_NOT_DEF_IN_SCHEMA = 8303
'The maximum size of an object has been exceeded.
Public Const ERROR_DS_MAX_OBJ_SIZE_EXCEEDED = 8304
'An attempt was made to add an object to the directory with a name that is
'already in use.
Public Const ERROR_DS_OBJ_STRING_NAME_EXISTS = 8305
'An attempt was made to add an object of a class that does not have an RDN
'defined in the schema.
Public Const ERROR_DS_NO_RDN_DEFINED_IN_SCHEMA = 8306
'An attempt was made to add an object using an RDN that is not the RDN defined
'in the schema.
Public Const ERROR_DS_RDN_DOESNT_MATCH_SCHEMA = 8307
'None of the requested attributes were found on the objects.
Public Const ERROR_DS_NO_REQUESTED_ATTS_FOUND = 8308
'The user buffer is too small.
Public Const ERROR_DS_USER_BUFFER_TO_SMALL = 8309
'The attribute specified in the operation is not present on the object.
Public Const ERROR_DS_ATT_IS_NOT_ON_OBJ = 8310
'Illegal modify operation. Some aspect of the modification is not permitted.
Public Const ERROR_DS_ILLEGAL_MOD_OPERATION = 8311
'The specified object is too large.
Public Const ERROR_DS_OBJ_TOO_LARGE = 8312
'The specified instance type is not valid.
Public Const ERROR_DS_BAD_INSTANCE_TYPE = 8313
'The operation must be performed at a master DSA.
Public Const ERROR_DS_MASTERDSA_REQUIRED = 8314
'The object class attribute must be specified.
Public Const ERROR_DS_OBJECT_CLASS_REQUIRED = 8315
'A required attribute is missing.
Public Const ERROR_DS_MISSING_REQUIRED_ATT = 8316
'An attempt was made to modify an object to include an attribute that is
'not legal for its class.
Public Const ERROR_DS_ATT_NOT_DEF_FOR_CLASS = 8317
'The specified attribute is already present on the object.
Public Const ERROR_DS_ATT_ALREADY_EXISTS = 8318

'8319 unused


'The specified attribute is not present, or has no values.
Public Const ERROR_DS_CANT_ADD_ATT_VALUES = 8320
'Multiple values were specified for an attribute that can have only one value.
Public Const ERROR_DS_SINGLE_VALUE_CONSTRAINT = 8321
'A value for the attribute was not in the acceptable range of values.
Public Const ERROR_DS_RANGE_CONSTRAINT = 8322
'The specified value already exists.
Public Const ERROR_DS_ATT_VAL_ALREADY_EXISTS = 8323
'The attribute cannot be removed because it is not present on the object.
Public Const ERROR_DS_CANT_REM_MISSING_ATT = 8324
'The attribute value cannot be removed because it is not present on the object.
Public Const ERROR_DS_CANT_REM_MISSING_ATT_VAL = 8325
'The specified root object cannot be a subref.
Public Const ERROR_DS_ROOT_CANT_BE_SUBREF = 8326
'Chaining is not permitted.
Public Const ERROR_DS_NO_CHAINING = 8327
'Chained evaluation is not permitted.
Public Const ERROR_DS_NO_CHAINED_EVAL = 8328
'The operation could not be performed because the object's parent is either
'uninstantiated or deleted.
Public Const ERROR_DS_NO_PARENT_OBJECT = 8329
'Having a parent that is an alias is not permitted. Aliases are leaf objects.
Public Const ERROR_DS_PARENT_IS_AN_ALIAS = 8330
'The object and parent must be of the same type, either both masters or both
'replicas.
Public Const ERROR_DS_CANT_MIX_MASTER_AND_REPS = 8331
'The operation cannot be performed because child objects exist. This operation
'can only be performed on a leaf object.
Public Const ERROR_DS_CHILDREN_EXIST = 8332
'Directory object not found.
Public Const ERROR_DS_OBJ_NOT_FOUND = 8333
'The aliased object is missing.
Public Const ERROR_DS_ALIASED_OBJ_MISSING = 8334
'The object name has bad syntax.
Public Const ERROR_DS_BAD_NAME_SYNTAX = 8335
'It is not permitted for an alias to refer to another alias.
Public Const ERROR_DS_ALIAS_POINTS_TO_ALIAS = 8336
'The alias cannot be dereferenced.
Public Const ERROR_DS_CANT_DEREF_ALIAS = 8337
'The operation is out of scope.
Public Const ERROR_DS_OUT_OF_SCOPE = 8338
'The operation cannot continue because the object is in the process of being
'removed.
Public Const ERROR_DS_OBJECT_BEING_REMOVED = 8339
'The DSA object cannot be deleted.
Public Const ERROR_DS_CANT_DELETE_DSA_OBJ = 8340
'A directory service error has occurred.
Public Const ERROR_DS_GENERIC_ERROR = 8341
'The operation can only be performed on an internal master DSA object.
Public Const ERROR_DS_DSA_MUST_BE_INT_MASTER = 8342
'The object must be of class DSA.
Public Const ERROR_DS_CLASS_NOT_DSA = 8343
'Insufficient access rights to perform the operation.
Public Const ERROR_DS_INSUFF_ACCESS_RIGHTS = 8344
'The object cannot be added because the parent is not on the list of possible
'superiors.
Public Const ERROR_DS_ILLEGAL_SUPERIOR = 8345
'Access to the attribute is not permitted because the attribute is owned by
'the Security Accounts Manager (SAM).
Public Const ERROR_DS_ATTRIBUTE_OWNED_BY_SAM = 8346
'The name has too many parts.
Public Const ERROR_DS_NAME_TOO_MANY_PARTS = 8347
'The name is too long.
Public Const ERROR_DS_NAME_TOO_LONG = 8348
'The name value is too long.
Public Const ERROR_DS_NAME_VALUE_TOO_LONG = 8349
'The directory service encountered an error parsing a name.
Public Const ERROR_DS_NAME_UNPARSEABLE = 8350
'The directory service cannot get the attribute type for a name.
Public Const ERROR_DS_NAME_TYPE_UNKNOWN = 8351
'The name does not identify an object; the name identifies a phantom.
Public Const ERROR_DS_NOT_AN_OBJECT = 8352
'The security descriptor is too short.
Public Const ERROR_DS_SEC_DESC_TOO_SHORT = 8353
'The security descriptor is invalid.
Public Const ERROR_DS_SEC_DESC_INVALID = 8354
'Failed to create name for deleted object.
Public Const ERROR_DS_NO_DELETED_NAME = 8355
'The parent of a new subref must exist.
Public Const ERROR_DS_SUBREF_MUST_HAVE_PARENT = 8356
'The object must be a naming context.
Public Const ERROR_DS_NCNAME_MUST_BE_NC = 8357
'It is not permitted to add an attribute which is owned by the system.
Public Const ERROR_DS_CANT_ADD_SYSTEM_ONLY = 8358
'The class of the object must be structural; you cannot instantiate an
'abstract class.
Public Const ERROR_DS_CLASS_MUST_BE_CONCRETE = 8359
'The schema object could not be found.
Public Const ERROR_DS_INVALID_DMD = 8360
'A local object with this GUID (dead or alive) already exists.
Public Const ERROR_DS_OBJ_GUID_EXISTS = 8361
'The operation cannot be performed on a back link.
Public Const ERROR_DS_NOT_ON_BACKLINK = 8362
'The cross reference for the specified naming context could not be found.
Public Const ERROR_DS_NO_CROSSREF_FOR_NC = 8363
'The operation could not be performed because the directory service is
'shutting down.
Public Const ERROR_DS_SHUTTING_DOWN = 8364
'The directory service request is invalid.
Public Const ERROR_DS_UNKNOWN_OPERATION = 8365
'The role owner attribute could not be read.
Public Const ERROR_DS_INVALID_ROLE_OWNER = 8366
'The requested FSMO operation failed. The current FSMO holder could not
'be contacted.
Public Const ERROR_DS_COULDNT_CONTACT_FSMO = 8367
'Modification of a DN across a naming context is not permitted.
Public Const ERROR_DS_CROSS_NC_DN_RENAME = 8368
'The attribute cannot be modified because it is owned by the system.
Public Const ERROR_DS_CANT_MOD_SYSTEM_ONLY = 8369
'Only the replicator can perform this function.
Public Const ERROR_DS_REPLICATOR_ONLY = 8370
'The specified class is not defined.
Public Const ERROR_DS_OBJ_CLASS_NOT_DEFINED = 8371
'The specified class is not a subclass.
Public Const ERROR_DS_OBJ_CLASS_NOT_SUBCLASS = 8372
'The name reference is invalid.
Public Const ERROR_DS_NAME_REFERENCE_INVALID = 8373
'A cross reference already exists.
Public Const ERROR_DS_CROSS_REF_EXISTS = 8374
'It is not permitted to delete a master cross reference.
Public Const ERROR_DS_CANT_DEL_MASTER_CROSSREF = 8375
'Subtree notifications are only supported on NC heads.
Public Const ERROR_DS_SUBTREE_NOTIFY_NOT_NC_HEAD = 8376
'Notification filter is too complex.
Public Const ERROR_DS_NOTIFY_FILTER_TOO_COMPLEX = 8377
'Schema update failed: duplicate RDN.
Public Const ERROR_DS_DUP_RDN = 8378
'Schema update failed: duplicate OID.
Public Const ERROR_DS_DUP_OID = 8379
'Schema update failed: duplicate MAPI identifier.
Public Const ERROR_DS_DUP_MAPI_ID = 8380
'Schema update failed: duplicate schema-id GUID.
Public Const ERROR_DS_DUP_SCHEMA_ID_GUID = 8381
'Schema update failed: duplicate LDAP display name.
Public Const ERROR_DS_DUP_LDAP_DISPLAY_NAME = 8382
'Schema update failed: range-lower less than range upper.
Public Const ERROR_DS_SEMANTIC_ATT_TEST = 8383
'Schema update failed: syntax mismatch.
Public Const ERROR_DS_SYNTAX_MISMATCH = 8384
'Schema deletion failed: attribute is used in must-contain.
Public Const ERROR_DS_EXISTS_IN_MUST_HAVE = 8385
'Schema deletion failed: attribute is used in may-contain.
Public Const ERROR_DS_EXISTS_IN_MAY_HAVE = 8386
'Schema update failed: attribute in may-contain does not exist.
Public Const ERROR_DS_NONEXISTENT_MAY_HAVE = 8387
'Schema update failed: attribute in must-contain does not exist.
Public Const ERROR_DS_NONEXISTENT_MUST_HAVE = 8388
'Schema update failed: class in aux-class list does not exist or is not
'an auxiliary class.
Public Const ERROR_DS_AUX_CLS_TEST_FAIL = 8389
'Schema update failed: class in poss-superiors does not exist.
Public Const ERROR_DS_NONEXISTENT_POSS_SUP = 8390
'Schema update failed: class in subclassof list does not exist or does not
'satisfy hierarchy rules.
Public Const ERROR_DS_SUB_CLS_TEST_FAIL = 8391
'Schema update failed: Rdn-Att-Id has wrong syntax.
Public Const ERROR_DS_BAD_RDN_ATT_ID_SYNTAX = 8392
'Schema deletion failed: class is used as auxiliary class.
Public Const ERROR_DS_EXISTS_IN_AUX_CLS = 8393
'Schema deletion failed: class is used as sub class.
Public Const ERROR_DS_EXISTS_IN_SUB_CLS = 8394
'Schema deletion failed: class is used as poss superior.
Public Const ERROR_DS_EXISTS_IN_POSS_SUP = 8395
'Schema update failed in recalculating validation cache.
Public Const ERROR_DS_RECALCSCHEMA_FAILED = 8396
'The tree deletion is not finished. The request must be made again to
'continue deleting the tree.
Public Const ERROR_DS_TREE_DELETE_NOT_FINISHED = 8397
'The requested delete operation could not be performed.
Public Const ERROR_DS_CANT_DELETE = 8398
'Cannot read the governs class identifier for the schema record.
Public Const ERROR_DS_ATT_SCHEMA_REQ_ID = 8399
'The attribute schema has bad syntax.
Public Const ERROR_DS_BAD_ATT_SCHEMA_SYNTAX = 8400
'The attribute could not be cached.
Public Const ERROR_DS_CANT_CACHE_ATT = 8401
'The class could not be cached.
Public Const ERROR_DS_CANT_CACHE_CLASS = 8402
'The attribute could not be removed from the cache.
Public Const ERROR_DS_CANT_REMOVE_ATT_CACHE = 8403
'The class could not be removed from the cache.
Public Const ERROR_DS_CANT_REMOVE_CLASS_CACHE = 8404
'The distinguished name attribute could not be read.
Public Const ERROR_DS_CANT_RETRIEVE_DN = 8405
'No superior reference has been configured for the directory service.
'The directory service is therefore unable to issue referrals to objects
'outside this forest.
Public Const ERROR_DS_MISSING_SUPREF = 8406
'The instance type attribute could not be retrieved.
Public Const ERROR_DS_CANT_RETRIEVE_INSTANCE = 8407
'An internal error has occurred.
Public Const ERROR_DS_CODE_INCONSISTENCY = 8408
'A database error has occurred.
Public Const ERROR_DS_DATABASE_ERROR = 8409
'The attribute GOVERNSID is missing.
Public Const ERROR_DS_GOVERNSID_MISSING = 8410
'An expected attribute is missing.
Public Const ERROR_DS_MISSING_EXPECTED_ATT = 8411
'The specified naming context is missing a cross reference.
Public Const ERROR_DS_NCNAME_MISSING_CR_REF = 8412
'A security checking error has occurred.
Public Const ERROR_DS_SECURITY_CHECKING_ERROR = 8413
'The schema is not loaded.
Public Const ERROR_DS_SCHEMA_NOT_LOADED = 8414
'Schema allocation failed. Please check if the machine is running low on memory.
Public Const ERROR_DS_SCHEMA_ALLOC_FAILED = 8415
'Failed to obtain the required syntax for the attribute schema.
Public Const ERROR_DS_ATT_SCHEMA_REQ_SYNTAX = 8416
'The global catalog verification failed. The global catalog is not available or
'does not support the operation. Some part of the directory is currently not
'available.
Public Const ERROR_DS_GCVERIFY_ERROR = 8417
'The replication operation failed because of a schema mismatch between
'the servers involved.
Public Const ERROR_DS_DRA_SCHEMA_MISMATCH = 8418
'The DSA object could not be found.
Public Const ERROR_DS_CANT_FIND_DSA_OBJ = 8419
'The naming context could not be found.
Public Const ERROR_DS_CANT_FIND_EXPECTED_NC = 8420
'The naming context could not be found in the cache.
Public Const ERROR_DS_CANT_FIND_NC_IN_CACHE = 8421
'The child object could not be retrieved.
Public Const ERROR_DS_CANT_RETRIEVE_CHILD = 8422
'The modification was not permitted for security reasons.
Public Const ERROR_DS_SECURITY_ILLEGAL_MODIFY = 8423
'The operation cannot replace the hidden record.
Public Const ERROR_DS_CANT_REPLACE_HIDDEN_REC = 8424
'The hierarchy file is invalid.
Public Const ERROR_DS_BAD_HIERARCHY_FILE = 8425
'The attempt to build the hierarchy table failed.
Public Const ERROR_DS_BUILD_HIERARCHY_TABLE_FAILED = 8426
'The directory configuration parameter is missing from the registry.
Public Const ERROR_DS_CONFIG_PARAM_MISSING = 8427
'The attempt to count the address book indices failed.
Public Const ERROR_DS_COUNTING_AB_INDICES_FAILED = 8428
'The allocation of the hierarchy table failed.
Public Const ERROR_DS_HIERARCHY_TABLE_MALLOC_FAILED = 8429
'The directory service encountered an internal failure.
Public Const ERROR_DS_INTERNAL_FAILURE = 8430
'The directory service encountered an unknown failure.
Public Const ERROR_DS_UNKNOWN_ERROR = 8431
'A root object requires a class of 'top'.
Public Const ERROR_DS_ROOT_REQUIRES_CLASS_TOP = 8432
'This directory server is shutting down, and cannot take ownership of new
'floating single-master operation roles.
Public Const ERROR_DS_REFUSING_FSMO_ROLES = 8433
'The directory service is missing mandatory configuration information, and is
'unable to determine the ownership of floating single-master operation roles.
Public Const ERROR_DS_MISSING_FSMO_SETTINGS = 8434
'The directory service was unable to transfer ownership of one or more floating
'single-master operation roles to other servers.
Public Const ERROR_DS_UNABLE_TO_SURRENDER_ROLES = 8435
'The replication operation failed.
Public Const ERROR_DS_DRA_GENERIC = 8436
'An invalid parameter was specified for this replication operation.
Public Const ERROR_DS_DRA_INVALID_PARAMETER = 8437
'The directory service is too busy to complete the replication operation at this
'time.
Public Const ERROR_DS_DRA_BUSY = 8438
'The distinguished name specified for this replication operation is invalid.
Public Const ERROR_DS_DRA_BAD_DN = 8439
'The naming context specified for this replication operation is invalid.
Public Const ERROR_DS_DRA_BAD_NC = 8440
'The distinguished name specified for this replication operation already exists.
Public Const ERROR_DS_DRA_DN_EXISTS = 8441
'The replication system encountered an internal error.
Public Const ERROR_DS_DRA_INTERNAL_ERROR = 8442
'The replication operation encountered a database inconsistency.
Public Const ERROR_DS_DRA_INCONSISTENT_DIT = 8443
'The server specified for this replication operation could not be contacted.
Public Const ERROR_DS_DRA_CONNECTION_FAILED = 8444
'The replication operation encountered an object with an invalid instance type.
Public Const ERROR_DS_DRA_BAD_INSTANCE_TYPE = 8445
'The replication operation failed to allocate memory.
Public Const ERROR_DS_DRA_OUT_OF_MEM = 8446
'The replication operation encountered an error with the mail system.
Public Const ERROR_DS_DRA_MAIL_PROBLEM = 8447
'The replication reference information for the target server already exists.
Public Const ERROR_DS_DRA_REF_ALREADY_EXISTS = 8448
'The replication reference information for the target server does not exist.
Public Const ERROR_DS_DRA_REF_NOT_FOUND = 8449
'The naming context cannot be removed because it is replicated to another server.
Public Const ERROR_DS_DRA_OBJ_IS_REP_SOURCE = 8450
'The replication operation encountered a database error.
Public Const ERROR_DS_DRA_DB_ERROR = 8451
'The naming context is in the process of being removed or is not replicated
'from the specified server.
Public Const ERROR_DS_DRA_NO_REPLICA = 8452
'Replication access was denied.
Public Const ERROR_DS_DRA_ACCESS_DENIED = 8453
'The requested operation is not supported by this version of the directory service.
Public Const ERROR_DS_DRA_NOT_SUPPORTED = 8454
'The replication remote procedure call was cancelled.
Public Const ERROR_DS_DRA_RPC_CANCELLED = 8455
'The source server is currently rejecting replication requests.
Public Const ERROR_DS_DRA_SOURCE_DISABLED = 8456
'The destination server is currently rejecting replication requests.
Public Const ERROR_DS_DRA_SINK_DISABLED = 8457
'The replication operation failed due to a collision of object names.
Public Const ERROR_DS_DRA_NAME_COLLISION = 8458
'The replication source has been reinstalled.
Public Const ERROR_DS_DRA_SOURCE_REINSTALLED = 8459
'The replication operation failed because a required parent object is missing.
Public Const ERROR_DS_DRA_MISSING_PARENT = 8460
'The replication operation was preempted.
Public Const ERROR_DS_DRA_PREEMPTED = 8461
'The replication synchronization attempt was abandoned because of a lack of updates.
Public Const ERROR_DS_DRA_ABANDON_SYNC = 8462
'The replication operation was terminated because the system is shutting down.
Public Const ERROR_DS_DRA_SHUTDOWN = 8463
'The replication synchronization attempt failed as the destination partial
'attribute set is not a subset of source partial attribute set.
Public Const ERROR_DS_DRA_INCOMPATIBLE_PARTIAL_SET = 8464
'The replication synchronization attempt failed because a master replica
'attempted to sync from a partial replica.
Public Const ERROR_DS_DRA_SOURCE_IS_PARTIAL_REPLICA = 8465
'The server specified for this replication operation was contacted, but that
'server was unable to contact an additional server needed to complete
'the operation.
Public Const ERROR_DS_DRA_EXTN_CONNECTION_FAILED = 8466
'The version of the Active Directory schema of the source forest is not
'compatible with the version of Active Directory on this computer.
Public Const ERROR_DS_INSTALL_SCHEMA_MISMATCH = 8467
'Schema update failed: An attribute with the same link identifier already exists.
Public Const ERROR_DS_DUP_LINK_ID = 8468
'Name translation: Generic processing error.
Public Const ERROR_DS_NAME_ERROR_RESOLVING = 8469
'Name translation: Could not find the name or insufficient right to see name.
Public Const ERROR_DS_NAME_ERROR_NOT_FOUND = 8470
'Name translation: Input name mapped to more than one output name.
Public Const ERROR_DS_NAME_ERROR_NOT_UNIQUE = 8471
'Name translation: Input name found, but not the associated output format.
Public Const ERROR_DS_NAME_ERROR_NO_MAPPING = 8472
'Name translation: Unable to resolve completely, only the domain was found.
Public Const ERROR_DS_NAME_ERROR_DOMAIN_ONLY = 8473
'Name translation: Unable to perform purely syntactical mapping at the client
'without going out to the wire.
Public Const ERROR_DS_NAME_ERROR_NO_SYNTACTICAL_MAPPING = 8474
'Modification of a constructed attribute is not allowed.
Public Const ERROR_DS_CONSTRUCTED_ATT_MOD = 8475
'The OM-Object-Class specified is incorrect for an attribute with the specified
'syntax.
Public Const ERROR_DS_WRONG_OM_OBJ_CLASS = 8476
'The replication request has been posted; waiting for reply.
Public Const ERROR_DS_DRA_REPL_PENDING = 8477
'The requested operation requires a directory service, and none was available.
Public Const ERROR_DS_DS_REQUIRED = 8478
'The LDAP display name of the class or attribute contains non-ASCII characters.
Public Const ERROR_DS_INVALID_LDAP_DISPLAY_NAME = 8479
'The requested search operation is only supported for base searches.
Public Const ERROR_DS_NON_BASE_SEARCH = 8480
'The search failed to retrieve attributes from the database.
Public Const ERROR_DS_CANT_RETRIEVE_ATTS = 8481
'The schema update operation tried to add a backward link attribute that has
'no corresponding forward link.
Public Const ERROR_DS_BACKLINK_WITHOUT_LINK = 8482
'Source and destination of a cross-domain move do not agree on the object's
'epoch number. Either source or destination does not have the latest version of
'the object.
Public Const ERROR_DS_EPOCH_MISMATCH = 8483
'Source and destination of a cross-domain move do not agree on the object's
'current name. Either source or destination does not have the latest version
'of the object.
Public Const ERROR_DS_SRC_NAME_MISMATCH = 8484
'Source and destination for the cross-domain move operation are identical.
'Caller should use local move operation instead of cross-domain move operation.
Public Const ERROR_DS_SRC_AND_DST_NC_IDENTICAL = 8485
'Source and destination for a cross-domain move are not in agreement on
'the naming contexts in the forest. Either source or destination does not have
'the latest version of the Partitions container.
Public Const ERROR_DS_DST_NC_MISMATCH = 8486
'Destination of a cross-domain move is not authoritative for the destination
'naming context.
Public Const ERROR_DS_NOT_AUTHORITIVE_FOR_DST_NC = 8487
'Source and destination of a cross-domain move do not agree on the identity of
'the source object. Either source or destination does not have the latest
'version of the source object.
Public Const ERROR_DS_SRC_GUID_MISMATCH = 8488
'Object being moved across-domains is already known to be deleted by
'the destination server. The source server does not have the latest
'version of the source object.
Public Const ERROR_DS_CANT_MOVE_DELETED_OBJECT = 8489
'Another operation which requires exclusive access to the PDC FSMO is
'already in progress.
Public Const ERROR_DS_PDC_OPERATION_IN_PROGRESS = 8490
'A cross-domain move operation failed such that two versions of the moved
'object exist - one each in the source and destination domains. The destination
'object needs to be removed to restore the system to a consistent state.
Public Const ERROR_DS_CROSS_DOMAIN_CLEANUP_REQD = 8491
'This object may not be moved across domain boundaries either because
'cross-domain moves for this class are disallowed, or the object has some
'special characteristics, e.g.: trust account or restricted RID, which prevent
'its move.
Public Const ERROR_DS_ILLEGAL_XDOM_MOVE_OPERATION = 8492
'Can't move objects with memberships across domain boundaries as once moved,
'this would violate the membership conditions of the account group. Remove
'the object from any account group memberships and retry.
Public Const ERROR_DS_CANT_WITH_ACCT_GROUP_MEMBERSHPS = 8493
'A naming context head must be the immediate child of another naming context
'head, not of an interior node.
Public Const ERROR_DS_NC_MUST_HAVE_NC_PARENT = 8494
'The directory cannot validate the proposed naming context name because
'it does not hold a replica of the naming context above the proposed naming
'context. Please ensure that the domain naming master role is held by a server
'that is configured as a global catalog server, and that the server is up to
'date with its replication partners.
'(Applies only to Windows 2000 Domain Naming masters)
Public Const ERROR_DS_CR_IMPOSSIBLE_TO_VALIDATE = 8495
'Destination domain must be in native mode.
Public Const ERROR_DS_DST_DOMAIN_NOT_NATIVE = 8496
'The operation can not be performed because the server does not
'have an infrastructure container in the domain of interest.
Public Const ERROR_DS_MISSING_INFRASTRUCTURE_CONTAINER = 8497
'Cross-domain move of non-empty account groups is not allowed.
Public Const ERROR_DS_CANT_MOVE_ACCOUNT_GROUP = 8498
'Cross-domain move of non-empty resource groups is not allowed.
Public Const ERROR_DS_CANT_MOVE_RESOURCE_GROUP = 8499
'The search flags for the attribute are invalid. The ANR bit is valid
'only on attributes of Unicode or Teletex strings.
Public Const ERROR_DS_INVALID_SEARCH_FLAG = 8500
'Tree deletions starting at an object which has an NC head as a descendant
'are not allowed.
Public Const ERROR_DS_NO_TREE_DELETE_ABOVE_NC = 8501
'The directory service failed to lock a tree in preparation for a tree deletion
'because the tree was in use.
Public Const ERROR_DS_COULDNT_LOCK_TREE_FOR_DELETE = 8502
'The directory service failed to identify the list of objects to delete while
'attempting a tree deletion.
Public Const ERROR_DS_COULDNT_IDENTIFY_OBJECTS_FOR_TREE_DELETE = 8503
'Security Accounts Manager initialization failed because of the
'following error: %1.
'Error Status: &H%2. Click OK to shut down the system and reboot into
'Directory Services Restore Mode. Check the event log for detailed information.
Public Const ERROR_DS_SAM_INIT_FAILURE = 8504
'Only an administrator can modify the membership list of an administrative group.
Public Const ERROR_DS_SENSITIVE_GROUP_VIOLATION = 8505
'Cannot change the primary group ID of a domain controller account.
Public Const ERROR_DS_CANT_MOD_PRIMARYGROUPID = 8506
'An attempt is made to modify the base schema.
Public Const ERROR_DS_ILLEGAL_BASE_SCHEMA_MOD = 8507
'Adding a new mandatory attribute to an existing class, deleting a mandatory
'attribute from an existing class, or adding an optional attribute to the special class Top that is not a backlink attribute (directly or through inheritance, for example, by adding or deleting an auxiliary class) is not allowed.
Public Const ERROR_DS_NONSAFE_SCHEMA_CHANGE = 8508
'Schema update is not allowed on this DC because the DC is not the schema
'FSMO Role Owner.
Public Const ERROR_DS_SCHEMA_UPDATE_DISALLOWED = 8509
'An object of this class cannot be created under the schema container.
'You can only create attribute-schema and class-schema objects under the schema container.
Public Const ERROR_DS_CANT_CREATE_UNDER_SCHEMA = 8510
'The replica/child install failed to get the objectVersion attribute on t
'he schema container on the source DC. Either the attribute is missing on
'the schema container or the credentials supplied do not have permission
'to read it.
Public Const ERROR_DS_INSTALL_NO_SRC_SCH_VERSION = 8511
'The replica/child install failed to read the objectVersion attribute
'in the SCHEMA section of the file schema.ini in the system32 directory.
Public Const ERROR_DS_INSTALL_NO_SCH_VERSION_IN_INIFILE = 8512
'The specified group type is invalid.
Public Const ERROR_DS_INVALID_GROUP_TYPE = 8513
'You cannot nest global groups in a mixed domain if the group is security-enabled.
Public Const ERROR_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN = 8514
'You cannot nest local groups in a mixed domain if the group is security-enabled.
Public Const ERROR_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN = 8515
'A global group cannot have a local group as a member.
Public Const ERROR_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER = 8516
'A global group cannot have a universal group as a member.
Public Const ERROR_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER = 8517
'A universal group cannot have a local group as a member.
Public Const ERROR_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER = 8518
'A global group cannot have a cross-domain member.
Public Const ERROR_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER = 8519
'A local group cannot have another cross domain local group as a member.
Public Const ERROR_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER = 8520
'A group with primary members cannot change to a security-disabled group.
Public Const ERROR_DS_HAVE_PRIMARY_MEMBERS = 8521
'The schema cache load failed to convert the string default SD on
'a class-schema object.
Public Const ERROR_DS_STRING_SD_CONVERSION_FAILED = 8522
'Only DSAs configured to be Global Catalog servers should be allowed to
'hold the Domain Naming Master FSMO role. (Applies only to Windows 2000 servers)
Public Const ERROR_DS_NAMING_MASTER_GC = 8523
'The DSA operation is unable to proceed because of a DNS lookup failure.
Public Const ERROR_DS_DNS_LOOKUP_FAILURE = 8524
'While processing a change to the DNS Host Name for an object,
'the Service Principal Name values could not be kept in sync.
Public Const ERROR_DS_COULDNT_UPDATE_SPNS = 8525
'The Security Descriptor attribute could not be read.
Public Const ERROR_DS_CANT_RETRIEVE_SD = 8526
'The object requested was not found, but an object with that key was found.
Public Const ERROR_DS_KEY_NOT_UNIQUE = 8527
'The syntax of the linked attribute being added is incorrect. Forward links
'can only have syntax 2.5.5.1, 2.5.5.7, and 2.5.5.14, and backlinks can only
'have syntax 2.5.5.1
Public Const ERROR_DS_WRONG_LINKED_ATT_SYNTAX = 8528
'Security Account Manager needs to get the boot password.
Public Const ERROR_DS_SAM_NEED_BOOTKEY_PASSWORD = 8529
'Security Account Manager needs to get the boot key from floppy disk.
Public Const ERROR_DS_SAM_NEED_BOOTKEY_FLOPPY = 8530
'Directory Service cannot start.
Public Const ERROR_DS_CANT_START = 8531
'Directory Services could not start.
Public Const ERROR_DS_INIT_FAILURE = 8532
'The connection between client and server requires packet privacy or better.
Public Const ERROR_DS_NO_PKT_PRIVACY_ON_CONNECTION = 8533
'The source domain may not be in the same forest as destination.
Public Const ERROR_DS_SOURCE_DOMAIN_IN_FOREST = 8534
'The destination domain must be in the forest.
Public Const ERROR_DS_DESTINATION_DOMAIN_NOT_IN_FOREST = 8535
'The operation requires that destination domain auditing be enabled.
Public Const ERROR_DS_DESTINATION_AUDITING_NOT_ENABLED = 8536
'The operation couldn't locate a DC for the source domain.
Public Const ERROR_DS_CANT_FIND_DC_FOR_SRC_DOMAIN = 8537
'The source object must be a group or user.
Public Const ERROR_DS_SRC_OBJ_NOT_GROUP_OR_USER = 8538
'The source object's SID already exists in destination forest.
Public Const ERROR_DS_SRC_SID_EXISTS_IN_FOREST = 8539
'The source and destination object must be of the same type.
Public Const ERROR_DS_SRC_AND_DST_OBJECT_CLASS_MISMATCH = 8540
'Security Accounts Manager initialization failed because of the following error: %1.
'Error Status: &H%2. Click OK to shut down the system and reboot into
'Safe Mode. Check the event log for detailed information.
Public Const ERROR_SAM_INIT_FAILURE = 8541
'Schema information could not be included in the replication request.
Public Const ERROR_DS_DRA_SCHEMA_INFO_SHIP = 8542
'The replication operation could not be completed due to a schema incompatibility.
Public Const ERROR_DS_DRA_SCHEMA_CONFLICT = 8543
'The replication operation could not be completed due to a previous schema
'incompatibility.
Public Const ERROR_DS_DRA_EARLIER_SCHEMA_CONFLICT = 8544
'The replication update could not be applied because either the source or
'the destination has not yet received information regarding a recent
'cross-domain move operation.
Public Const ERROR_DS_DRA_OBJ_NC_MISMATCH = 8545
'The requested domain could not be deleted because there exist domain
'controllers that still host this domain.
Public Const ERROR_DS_NC_STILL_HAS_DSAS = 8546
'The requested operation can be performed only on a global catalog server.
Public Const ERROR_DS_GC_REQUIRED = 8547
'A local group can only be a member of other local groups in the same domain.
Public Const ERROR_DS_LOCAL_MEMBER_OF_LOCAL_ONLY = 8548
'Foreign security principals cannot be members of universal groups.
Public Const ERROR_DS_NO_FPO_IN_UNIVERSAL_GROUPS = 8549
'The attribute is not allowed to be replicated to the GC because of security reasons.
Public Const ERROR_DS_CANT_ADD_TO_GC = 8550
'The checkpoint with the PDC could not be taken because there too many
'modifications being processed currently.
Public Const ERROR_DS_NO_CHECKPOINT_WITH_PDC = 8551
'The operation requires that source domain auditing be enabled.
Public Const ERROR_DS_SOURCE_AUDITING_NOT_ENABLED = 8552
'Security principal objects can only be created inside domain naming contexts.
Public Const ERROR_DS_CANT_CREATE_IN_NONDOMAIN_NC = 8553
'A Service Principal Name (SPN) could not be constructed because the provided
'hostname is not in the necessary format.
Public Const ERROR_DS_INVALID_NAME_FOR_SPN = 8554
'A Filter was passed that uses constructed attributes.
Public Const ERROR_DS_FILTER_USES_CONTRUCTED_ATTRS = 8555
'The unicodePwd attribute value must be enclosed in double quotes.
Public Const ERROR_DS_UNICODEPWD_NOT_IN_QUOTES = 8556
'Your computer could not be joined to the domain. You have exceeded
'the maximum number of computer accounts you are allowed to create in this domain.
'Contact your system administrator to have this limit reset or increased.
Public Const ERROR_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED = 8557
'For security reasons, the operation must be run on the destination DC.
Public Const ERROR_DS_MUST_BE_RUN_ON_DST_DC = 8558
'For security reasons, the source DC must be NT4SP4 or greater.
Public Const ERROR_DS_SRC_DC_MUST_BE_SP4_OR_GREATER = 8559
'Critical Directory Service System objects cannot be deleted during tree
'delete operations. The tree delete may have been partially performed.
Public Const ERROR_DS_CANT_TREE_DELETE_CRITICAL_OBJ = 8560
'Directory Services could not start because of the following error: %1.
'Error Status: &H%2. Please click OK to shutdown the system. You can use
'the recovery console to diagnose the system further.
Public Const ERROR_DS_INIT_FAILURE_CONSOLE = 8561
'Security Accounts Manager initialization failed because of the following error: %1.
'Error Status: &H%2. Please click OK to shutdown the system. You can use
'the recovery console to diagnose the system further.
Public Const ERROR_DS_SAM_INIT_FAILURE_CONSOLE = 8562
'The version of the operating system installed is incompatible with
'the current forest functional level. You must upgrade to a new version of
'the operating system before this server can become a domain controller in
'this forest.
Public Const ERROR_DS_FOREST_VERSION_TOO_HIGH = 8563
'The version of the operating system installed is incompatible with
'the current domain functional level. You must upgrade to a new version of
'the operating system before this server can become a domain controller in this domain.
Public Const ERROR_DS_DOMAIN_VERSION_TOO_HIGH = 8564
'The version of the operating system installed on this server no longer
'supports the current forest functional level. You must raise the forest
'functional level before this server can become a domain controller in this forest.
Public Const ERROR_DS_FOREST_VERSION_TOO_LOW = 8565
'The version of the operating system installed on this server no
'longer supports the current domain functional level. You must raise
'the domain functional level before this server can become a domain
'controller in this domain.
Public Const ERROR_DS_DOMAIN_VERSION_TOO_LOW = 8566
'The version of the operating system installed on this server is
'incompatible with the functional level of the domain or forest.
Public Const ERROR_DS_INCOMPATIBLE_VERSION = 8567
'The functional level of the domain (or forest) cannot be raised to
'the requested value, because there exist one or more domain controllers in
'the domain (or forest) that are at a lower incompatible functional level.
Public Const ERROR_DS_LOW_DSA_VERSION = 8568
'The forest functional level cannot be raised to the requested value since one
'or more domains are still in mixed domain mode. All domains in the forest
'must be in native mode, for you to raise the forest functional level.
Public Const ERROR_DS_NO_BEHAVIOR_VERSION_IN_MIXEDDOMAIN = 8569
'The sort order requested is not supported.
Public Const ERROR_DS_NOT_SUPPORTED_SORT_ORDER = 8570
'The requested name already exists as a unique identifier.
Public Const ERROR_DS_NAME_NOT_UNIQUE = 8571
'The machine account was created pre-NT4. The account needs to be recreated.
Public Const ERROR_DS_MACHINE_ACCOUNT_CREATED_PRENT4 = 8572
'The database is out of version store.
Public Const ERROR_DS_OUT_OF_VERSION_STORE = 8573
'Unable to continue operation because multiple conflicting controls were used.
Public Const ERROR_DS_INCOMPATIBLE_CONTROLS_USED = 8574
'Unable to find a valid security descriptor reference domain for this partition.
Public Const ERROR_DS_NO_REF_DOMAIN = 8575
'Schema update failed: The link identifier is reserved.
Public Const ERROR_DS_RESERVED_LINK_ID = 8576
'Schema update failed: There are no link identifiers available.
Public Const ERROR_DS_LINK_ID_NOT_AVAILABLE = 8577
'An account group can not have a universal group as a member.
Public Const ERROR_DS_AG_CANT_HAVE_UNIVERSAL_MEMBER = 8578
'Rename or move operations on naming context heads or read-only objects are
'not allowed.
Public Const ERROR_DS_MODIFYDN_DISALLOWED_BY_INSTANCE_TYPE = 8579
'Move operations on objects in the schema naming context are not allowed.
Public Const ERROR_DS_NO_OBJECT_MOVE_IN_SCHEMA_NC = 8580
'A system flag has been set on the object and does not allow the object to be
'moved or renamed.
Public Const ERROR_DS_MODIFYDN_DISALLOWED_BY_FLAG = 8581
'This object is not allowed to change its grandparent container. Moves are
'not forbidden on this object, but are restricted to sibling containers.
Public Const ERROR_DS_MODIFYDN_WRONG_GRANDPARENT = 8582
'Unable to resolve completely, a referral to another forest is generated.
Public Const ERROR_DS_NAME_ERROR_TRUST_REFERRAL = 8583
'The requested action is not supported on standard server.
Public Const ERROR_NOT_SUPPORTED_ON_STANDARD_SERVER = 8584
'Could not access a partition of the Active Directory located on a remote server.
'Make sure at least one server is running for the partition in question.
Public Const ERROR_DS_CANT_ACCESS_REMOTE_PART_OF_AD = 8585
'The directory cannot validate the proposed naming context (or partition)
'name because it does not hold a replica nor can it contact a replica of the
'naming context above the proposed naming context. Please ensure that the parent
'naming context is properly registered in DNS, and at least one replica of this
'naming context is reachable by the Domain Naming master.
Public Const ERROR_DS_CR_IMPOSSIBLE_TO_VALIDATE_V2 = 8586
'The thread limit for this request was exceeded.
Public Const ERROR_DS_THREAD_LIMIT_EXCEEDED = 8587
'The Global catalog server is not in the closest site.
Public Const ERROR_DS_NOT_CLOSEST = 8588
'The DS cannot derive a service principal name (SPN) with which to mutually
'authenticate the target server because the corresponding server object in
'the local DS database has no serverReference attribute.
Public Const ERROR_DS_CANT_DERIVE_SPN_WITHOUT_SERVER_REF = 8589
'The Directory Service failed to enter single user mode.
Public Const ERROR_DS_SINGLE_USER_MODE_FAILED = 8590
'The Directory Service cannot parse the script because of a syntax error.
Public Const ERROR_DS_NTDSCRIPT_SYNTAX_ERROR = 8591
'The Directory Service cannot process the script because of an error.
Public Const ERROR_DS_NTDSCRIPT_PROCESS_ERROR = 8592
'The directory service cannot perform the requested operation because the servers
'involved are of different replication epochs (which is usually related to a
'domain rename that is in progress).
Public Const ERROR_DS_DIFFERENT_REPL_EPOCHS = 8593
'The directory service binding must be renegotiated due to a change in the server
'extensions information.
Public Const ERROR_DS_DRS_EXTENSIONS_CHANGED = 8594
'Operation not allowed on a disabled cross ref.
Public Const ERROR_DS_REPLICA_SET_CHANGE_NOT_ALLOWED_ON_DISABLED_CR = 8595
'Schema update failed: No values for msDS-IntId are available.
Public Const ERROR_DS_NO_MSDS_INTID = 8596
'Schema update failed: Duplicate msDS-INtId. Retry the operation.
Public Const ERROR_DS_DUP_MSDS_INTID = 8597
'Schema deletion failed: attribute is used in rDNAttID.
Public Const ERROR_DS_EXISTS_IN_RDNATTID = 8598
'The directory service failed to authorize the request.
Public Const ERROR_DS_AUTHORIZATION_FAILED = 8599
'The Directory Service cannot process the script because it is invalid.
Public Const ERROR_DS_INVALID_SCRIPT = 8600
'The remote create cross reference operation failed on
'the Domain Naming Master FSMO. The operation's error is in the extended data.
Public Const ERROR_DS_REMOTE_CROSSREF_OP_FAILED = 8601
'A cross reference is in use locally with the same name.
Public Const ERROR_DS_CROSS_REF_BUSY = 8602
'The DS cannot derive a service principal name (SPN) with which to mutually
'authenticate the target server because the server's domain has been deleted
'from the forest.
Public Const ERROR_DS_CANT_DERIVE_SPN_FOR_DELETED_DOMAIN = 8603
'Writeable NCs prevent this DC from demoting.
Public Const ERROR_DS_CANT_DEMOTE_WITH_WRITEABLE_NC = 8604
'The requested object has a non-unique identifier and cannot be retrieved.
Public Const ERROR_DS_DUPLICATE_ID_FOUND = 8605
'Insufficient attributes were given to create an object. This object may not
'exist because it may have been deleted and already garbage collected.
Public Const ERROR_DS_INSUFFICIENT_ATTR_TO_CREATE_OBJECT = 8606
'The group cannot be converted due to attribute restrictions on the requested
'group type.
Public Const ERROR_DS_GROUP_CONVERSION_ERROR = 8607
'Cross-domain move of non-empty basic application groups is not allowed.
Public Const ERROR_DS_CANT_MOVE_APP_BASIC_GROUP = 8608
'Cross-domain move of non-empty query based application groups is not allowed.
Public Const ERROR_DS_CANT_MOVE_APP_QUERY_GROUP = 8609
'The FSMO role ownership could not be verified because its directory partition
'has not replicated successfully with atleast one replication partner.
Public Const ERROR_DS_ROLE_NOT_VERIFIED = 8610
'The target container for a redirection of a well known object container
'cannot already be a special container.
Public Const ERROR_DS_WKO_CONTAINER_CANNOT_BE_SPECIAL = 8611
'The Directory Service cannot perform the requested operation because
'a domain rename operation is in progress.
Public Const ERROR_DS_DOMAIN_RENAME_IN_PROGRESS = 8612
'The Active Directory detected an Active Directory child partition below the
'requested new partition name. The Active Directory's partition heiarchy must
'be created in a top down method.
Public Const ERROR_DS_EXISTING_AD_CHILD_NC = 8613
'The Active Directory cannot replicate with this server because the time since
'the last replication with this server has exceeded the tombstone lifetime.
Public Const ERROR_DS_REPL_LIFETIME_EXCEEDED = 8614
'The requested operation is not allowed on an object under the system container.
Public Const ERROR_DS_DISALLOWED_IN_SYSTEM_CONTAINER = 8615
'The LDAP servers network send queue has filled up because the client is not
'processing the results of it's requests fast enough. No more requests will
'be processed until the client catches up. If the client does not catch up
'then it will be disconnected.
Public Const ERROR_DS_LDAP_SEND_QUEUE_FULL = 8616

'===============================================================================
'   End of Active Directory Error Codes 8000 to  8999

'------------------------------------------------------------------------------
'DNS Error Codes 9000 to 9999
'=============================
'Facility DNS Error Messages
'=============================

'DNS response codes.

Public Const DNS_ERROR_RESPONSE_CODES_BASE = 9000

Public Const DNS_ERROR_RCODE_NO_ERROR = NO_ERROR

Public Const DNS_ERROR_MASK = &H2328     '9000 or DNS_ERROR_RESPONSE_CODES_BASE

'DNS_ERROR_RCODE_FORMAT_ERROR          &H00002329
'DNS server unable to interpret format.
Public Const DNS_ERROR_RCODE_FORMAT_ERROR = 9001

'DNS_ERROR_RCODE_SERVER_FAILURE        &H0000232a
'DNS server failure.
Public Const DNS_ERROR_RCODE_SERVER_FAILURE = 9002

'DNS_ERROR_RCODE_NAME_ERROR            &H0000232b
'DNS name does not exist.
Public Const DNS_ERROR_RCODE_NAME_ERROR = 9003

'DNS_ERROR_RCODE_NOT_IMPLEMENTED       &H0000232c
'DNS request not supported by name server.
Public Const DNS_ERROR_RCODE_NOT_IMPLEMENTED = 9004

'DNS_ERROR_RCODE_REFUSED               &H0000232d
'DNS operation refused.
Public Const DNS_ERROR_RCODE_REFUSED = 9005

'DNS_ERROR_RCODE_YXDOMAIN              &H0000232e
'DNS name that ought not exist, does exist.
Public Const DNS_ERROR_RCODE_YXDOMAIN = 9006

'DNS_ERROR_RCODE_YXRRSET               &H0000232f
'DNS RR set that ought not exist, does exist.
Public Const DNS_ERROR_RCODE_YXRRSET = 9007

'DNS_ERROR_RCODE_NXRRSET               &H00002330
'DNS RR set that ought to exist, does not exist.
Public Const DNS_ERROR_RCODE_NXRRSET = 9008

'DNS_ERROR_RCODE_NOTAUTH               &H00002331
'DNS server not authoritative for zone.
Public Const DNS_ERROR_RCODE_NOTAUTH = 9009

'DNS_ERROR_RCODE_NOTZONE               &H00002332
'DNS name in update or prereq is not in zone.
Public Const DNS_ERROR_RCODE_NOTZONE = 9010

'DNS_ERROR_RCODE_BADSIG                &H00002338
'DNS signature failed to verify.
Public Const DNS_ERROR_RCODE_BADSIG = 9016

'DNS_ERROR_RCODE_BADKEY                &H00002339
'DNS bad key.
Public Const DNS_ERROR_RCODE_BADKEY = 9017

'DNS_ERROR_RCODE_BADTIME               &H0000233a
'DNS signature validity expired.
Public Const DNS_ERROR_RCODE_BADTIME = 9018

Public Const DNS_ERROR_RCODE_LAST = DNS_ERROR_RCODE_BADTIME


'Packet format

Public Const DNS_ERROR_PACKET_FMT_BASE = 9500

'DNS_INFO_NO_RECORDS                   &H0000251d
'No records found for given DNS query.
Public Const DNS_INFO_NO_RECORDS = 9501

'DNS_ERROR_BAD_PACKET                  &H0000251e
'Bad DNS packet.
Public Const DNS_ERROR_BAD_PACKET = 9502

'DNS_ERROR_NO_PACKET                   &H0000251f
'No DNS packet.
Public Const DNS_ERROR_NO_PACKET = 9503

'DNS_ERROR_RCODE                       &H00002520
'DNS error, check rcode.
Public Const DNS_ERROR_RCODE = 9504

'DNS_ERROR_UNSECURE_PACKET             &H00002521
'Unsecured DNS packet.
Public Const DNS_ERROR_UNSECURE_PACKET = 9505

Public Const DNS_STATUS_PACKET_UNSECURE = DNS_ERROR_UNSECURE_PACKET


'General API errors

Public Const DNS_ERROR_NO_MEMORY = ERROR_OUTOFMEMORY
Public Const DNS_ERROR_INVALID_NAME = ERROR_INVALID_NAME
Public Const DNS_ERROR_INVALID_DATA = ERROR_INVALID_DATA

Public Const DNS_ERROR_GENERAL_API_BASE = 9550

'DNS_ERROR_INVALID_TYPE                &H0000254f
'Invalid DNS type.
Public Const DNS_ERROR_INVALID_TYPE = 9551

'DNS_ERROR_INVALID_IP_ADDRESS          &H00002550
'Invalid IP address.
Public Const DNS_ERROR_INVALID_IP_ADDRESS = 9552

'DNS_ERROR_INVALID_PROPERTY            &H00002551
'Invalid property.
Public Const DNS_ERROR_INVALID_PROPERTY = 9553

'DNS_ERROR_TRY_AGAIN_LATER             &H00002552
'Try DNS operation again later.
Public Const DNS_ERROR_TRY_AGAIN_LATER = 9554

'DNS_ERROR_NOT_UNIQUE                  &H00002553
'Record for given name and type is not unique.
Public Const DNS_ERROR_NOT_UNIQUE = 9555

'DNS_ERROR_NON_RFC_NAME                &H00002554
'DNS name does not comply with RFC specifications.
Public Const DNS_ERROR_NON_RFC_NAME = 9556

'DNS_STATUS_FQDN                       &H00002555
'DNS name is a fully-qualified DNS name.
Public Const DNS_STATUS_FQDN = 9557

'DNS_STATUS_DOTTED_NAME                &H00002556
'DNS name is dotted (multi-label).
Public Const DNS_STATUS_DOTTED_NAME = 9558

'DNS_STATUS_SINGLE_PART_NAME           &H00002557
'DNS name is a single-part name.
Public Const DNS_STATUS_SINGLE_PART_NAME = 9559

'DNS_ERROR_INVALID_NAME_CHAR           &H00002558
'DNS name contains an invalid character.
Public Const DNS_ERROR_INVALID_NAME_CHAR = 9560

'DNS_ERROR_NUMERIC_NAME                &H00002559
'DNS name is entirely numeric.
Public Const DNS_ERROR_NUMERIC_NAME = 9561

'DNS_ERROR_NOT_ALLOWED_ON_ROOT_SERVER  &H0000255A
'The operation requested is not permitted on a DNS root server.
Public Const DNS_ERROR_NOT_ALLOWED_ON_ROOT_SERVER = 9562

'DNS_ERROR_NOT_ALLOWED_UNDER_DELEGATION  &H0000255B
'The record could not be created because this part of the DNS namespace has
'been delegated to another server.
Public Const DNS_ERROR_NOT_ALLOWED_UNDER_DELEGATION = 9563

'DNS_ERROR_CANNOT_FIND_ROOT_HINTS  &H0000255C
'The DNS server could not find a set of root hints.
Public Const DNS_ERROR_CANNOT_FIND_ROOT_HINTS = 9564

'DNS_ERROR_INCONSISTENT_ROOT_HINTS  &H0000255D
'The DNS server found root hints but they were not consistent across
'all adapters.
Public Const DNS_ERROR_INCONSISTENT_ROOT_HINTS = 9565


'Zone errors

Public Const DNS_ERROR_ZONE_BASE = 9600

'DNS_ERROR_ZONE_DOES_NOT_EXIST         &H00002581
'DNS zone does not exist.
Public Const DNS_ERROR_ZONE_DOES_NOT_EXIST = 9601

'DNS_ERROR_NO_ZONE_INFO                &H00002582
'DNS zone information not available.
Public Const DNS_ERROR_NO_ZONE_INFO = 9602

'DNS_ERROR_INVALID_ZONE_OPERATION      &H00002583
'Invalid operation for DNS zone.
Public Const DNS_ERROR_INVALID_ZONE_OPERATION = 9603

'DNS_ERROR_ZONE_CONFIGURATION_ERROR    &H00002584
'Invalid DNS zone configuration.
Public Const DNS_ERROR_ZONE_CONFIGURATION_ERROR = 9604

'DNS_ERROR_ZONE_HAS_NO_SOA_RECORD      &H00002585
'DNS zone has no start of authority (SOA) record.
Public Const DNS_ERROR_ZONE_HAS_NO_SOA_RECORD = 9605

'DNS_ERROR_ZONE_HAS_NO_NS_RECORDS      &H00002586
'DNS zone has no Name Server (NS) record.
Public Const DNS_ERROR_ZONE_HAS_NO_NS_RECORDS = 9606

'DNS_ERROR_ZONE_LOCKED                 &H00002587
'DNS zone is locked.
Public Const DNS_ERROR_ZONE_LOCKED = 9607

'DNS_ERROR_ZONE_CREATION_FAILED        &H00002588
'DNS zone creation failed.
Public Const DNS_ERROR_ZONE_CREATION_FAILED = 9608

'DNS_ERROR_ZONE_ALREADY_EXISTS         &H00002589
'DNS zone already exists.
Public Const DNS_ERROR_ZONE_ALREADY_EXISTS = 9609

'DNS_ERROR_AUTOZONE_ALREADY_EXISTS     &H0000258a
'DNS automatic zone already exists.
Public Const DNS_ERROR_AUTOZONE_ALREADY_EXISTS = 9610

'DNS_ERROR_INVALID_ZONE_TYPE           &H0000258b
'Invalid DNS zone type.
Public Const DNS_ERROR_INVALID_ZONE_TYPE = 9611

'DNS_ERROR_SECONDARY_REQUIRES_MASTER_IP &H0000258c
'Secondary DNS zone requires master IP address.
Public Const DNS_ERROR_SECONDARY_REQUIRES_MASTER_IP = 9612

'DNS_ERROR_ZONE_NOT_SECONDARY          &H0000258d
'DNS zone not secondary.
Public Const DNS_ERROR_ZONE_NOT_SECONDARY = 9613

'DNS_ERROR_NEED_SECONDARY_ADDRESSES    &H0000258e
'Need secondary IP address.
Public Const DNS_ERROR_NEED_SECONDARY_ADDRESSES = 9614

'DNS_ERROR_WINS_INIT_FAILED            &H0000258f
'WINS initialization failed.
Public Const DNS_ERROR_WINS_INIT_FAILED = 9615

'DNS_ERROR_NEED_WINS_SERVERS           &H00002590
'Need WINS servers.
Public Const DNS_ERROR_NEED_WINS_SERVERS = 9616

'DNS_ERROR_NBSTAT_INIT_FAILED          &H00002591
'NBTSTAT initialization call failed.
Public Const DNS_ERROR_NBSTAT_INIT_FAILED = 9617

'DNS_ERROR_SOA_DELETE_INVALID          &H00002592
'Invalid delete of start of authority (SOA)
Public Const DNS_ERROR_SOA_DELETE_INVALID = 9618

'DNS_ERROR_FORWARDER_ALREADY_EXISTS    &H00002593
'A conditional forwarding zone already exists for that name.
Public Const DNS_ERROR_FORWARDER_ALREADY_EXISTS = 9619

'DNS_ERROR_ZONE_REQUIRES_MASTER_IP     &H00002594
'This zone must be configured with one or more master DNS server IP addresses.
Public Const DNS_ERROR_ZONE_REQUIRES_MASTER_IP = 9620

'DNS_ERROR_ZONE_IS_SHUTDOWN            &H00002595
'The operation cannot be performed because this zone is shutdown.
Public Const DNS_ERROR_ZONE_IS_SHUTDOWN = 9621


'Datafile errors

Public Const DNS_ERROR_DATAFILE_BASE = 9650

'DNS                                   &H000025b3
'Primary DNS zone requires datafile.
Public Const DNS_ERROR_PRIMARY_REQUIRES_DATAFILE = 9651

'DNS                                   &H000025b4
'Invalid datafile name for DNS zone.
Public Const DNS_ERROR_INVALID_DATAFILE_NAME = 9652

'DNS                                   &H000025b5
'Failed to open datafile for DNS zone.
Public Const DNS_ERROR_DATAFILE_OPEN_FAILURE = 9653

'DNS                                   &H000025b6
'Failed to write datafile for DNS zone.
Public Const DNS_ERROR_FILE_WRITEBACK_FAILED = 9654

'DNS                                   &H000025b7
'Failure while reading datafile for DNS zone.
Public Const DNS_ERROR_DATAFILE_PARSING = 9655
'Database errors

Public Const DNS_ERROR_DATABASE_BASE = 9700

'DNS_ERROR_RECORD_DOES_NOT_EXIST       &H000025e5
'DNS record does not exist.
Public Const DNS_ERROR_RECORD_DOES_NOT_EXIST = 9701

'DNS_ERROR_RECORD_FORMAT               &H000025e6
'DNS record format error.
Public Const DNS_ERROR_RECORD_FORMAT = 9702

'DNS_ERROR_NODE_CREATION_FAILED        &H000025e7
'Node creation failure in DNS.
Public Const DNS_ERROR_NODE_CREATION_FAILED = 9703

'DNS_ERROR_UNKNOWN_RECORD_TYPE         &H000025e8
'Unknown DNS record type.
Public Const DNS_ERROR_UNKNOWN_RECORD_TYPE = 9704

'DNS_ERROR_RECORD_TIMED_OUT            &H000025e9
'DNS record timed out.
Public Const DNS_ERROR_RECORD_TIMED_OUT = 9705

'DNS_ERROR_NAME_NOT_IN_ZONE            &H000025ea
'Name not in DNS zone.
Public Const DNS_ERROR_NAME_NOT_IN_ZONE = 9706

'DNS_ERROR_CNAME_LOOP                  &H000025eb
'CNAME loop detected.
Public Const DNS_ERROR_CNAME_LOOP = 9707

'DNS_ERROR_NODE_IS_CNAME               &H000025ec
'Node is a CNAME DNS record.
Public Const DNS_ERROR_NODE_IS_CNAME = 9708

'DNS_ERROR_CNAME_COLLISION             &H000025ed
'A CNAME record already exists for given name.
Public Const DNS_ERROR_CNAME_COLLISION = 9709

'DNS_ERROR_RECORD_ONLY_AT_ZONE_ROOT    &H000025ee
'Record only at DNS zone root.
Public Const DNS_ERROR_RECORD_ONLY_AT_ZONE_ROOT = 9710

'DNS_ERROR_RECORD_ALREADY_EXISTS       &H000025ef
'DNS record already exists.
Public Const DNS_ERROR_RECORD_ALREADY_EXISTS = 9711

'DNS_ERROR_SECONDARY_DATA              &H000025f0
'Secondary DNS zone data error.
Public Const DNS_ERROR_SECONDARY_DATA = 9712

'DNS_ERROR_NO_CREATE_CACHE_DATA        &H000025f1
'Could not create DNS cache data.
Public Const DNS_ERROR_NO_CREATE_CACHE_DATA = 9713

'DNS_ERROR_NAME_DOES_NOT_EXIST         &H000025f2
'DNS name does not exist.
Public Const DNS_ERROR_NAME_DOES_NOT_EXIST = 9714

'DNS_WARNING_PTR_CREATE_FAILED         &H000025f3
'Could not create pointer (PTR) record.
Public Const DNS_WARNING_PTR_CREATE_FAILED = 9715

'DNS_WARNING_DOMAIN_UNDELETED          &H000025f4
'DNS domain was undeleted.
Public Const DNS_WARNING_DOMAIN_UNDELETED = 9716

'DNS_ERROR_DS_UNAVAILABLE              &H000025f5
'The directory service is unavailable.
Public Const DNS_ERROR_DS_UNAVAILABLE = 9717

'DNS_ERROR_DS_ZONE_ALREADY_EXISTS      &H000025f6
'DNS zone already exists in the directory service.
Public Const DNS_ERROR_DS_ZONE_ALREADY_EXISTS = 9718

'DNS_ERROR_NO_BOOTFILE_IF_DS_ZONE      &H000025f7
'DNS server not creating or reading the boot file for the directory service integrated DNS zone.
Public Const DNS_ERROR_NO_BOOTFILE_IF_DS_ZONE = 9719


'Operation errors

Public Const DNS_ERROR_OPERATION_BASE = 9750

'DNS_INFO_AXFR_COMPLETE                &H00002617
'DNS AXFR (zone transfer) complete.
Public Const DNS_INFO_AXFR_COMPLETE = 9751

'DNS_ERROR_AXFR                        &H00002618
'DNS zone transfer failed.
Public Const DNS_ERROR_AXFR = 9752

'DNS_INFO_ADDED_LOCAL_WINS             &H00002619
'Added local WINS server.
Public Const DNS_INFO_ADDED_LOCAL_WINS = 9753


'Secure update

Public Const DNS_ERROR_SECURE_BASE = 9800

'DNS_STATUS_CONTINUE_NEEDED            &H00002649
'Secure update call needs to continue update request.
Public Const DNS_STATUS_CONTINUE_NEEDED = 9801


'Setup errors

Public Const DNS_ERROR_SETUP_BASE = 9850

'DNS_ERROR_NO_TCPIP                    &H0000267b
'TCP/IP network protocol not installed.
Public Const DNS_ERROR_NO_TCPIP = 9851

'DNS_ERROR_NO_DNS_SERVERS              &H0000267c
'No DNS servers configured for local system.
Public Const DNS_ERROR_NO_DNS_SERVERS = 9852


'Directory partition (DP) errors

Public Const DNS_ERROR_DP_BASE = 9900

'DNS_ERROR_DP_DOES_NOT_EXIST           &H000026ad
'The specified directory partition does not exist.
Public Const DNS_ERROR_DP_DOES_NOT_EXIST = 9901

'DNS_ERROR_DP_ALREADY_EXISTS           &H000026ae
'The specified directory partition already exists.
Public Const DNS_ERROR_DP_ALREADY_EXISTS = 9902

'DNS_ERROR_DP_NOT_ENLISTED             &H000026af
'This DNS server is not enlisted in the specified directory partition.
Public Const DNS_ERROR_DP_NOT_ENLISTED = 9903

'DNS_ERROR_DP_ALREADY_ENLISTED         &H000026b0
'This DNS server is already enlisted in the specified directory partition.
Public Const DNS_ERROR_DP_ALREADY_ENLISTED = 9904

'DNS_ERROR_DP_NOT_AVAILABLE            &H000026b1
'The directory partition is not available at this time. Please wait
'a few minutes and try again.
Public Const DNS_ERROR_DP_NOT_AVAILABLE = 9905

'--------------------------------------------------
'           End of DNS Error Codes
'
'                9000 to 9999
''''''''''''''''''''''''/

'--------------------------------------------------
'             WinSock Error Codes
'
'               10000 to 11999
''''''''''''''''''''''''/
'WinSock error codes are also defined in WinSock.h
'and WinSock2.h, hence the IFDEF

Public Const WSABASEERR = 10000


'A blocking operation was interrupted by a call to WSACancelBlockingCall.
Public Const WSAEINTR = 10004
'The file handle supplied is not valid.
Public Const WSAEBADF = 10009
'An attempt was made to access a socket in a way forbidden by its access
'permissions.
Public Const WSAEACCES = 10013
'The system detected an invalid pointer address in attempting to use a pointer
'argument in a call.
Public Const WSAEFAULT = 10014
'An invalid argument was supplied.
Public Const WSAEINVAL = 10022
'Too many open sockets.
Public Const WSAEMFILE = 10024
'A non-blocking socket operation could not be completed immediately.
Public Const WSAEWOULDBLOCK = 10035
'A blocking operation is currently executing.
Public Const WSAEINPROGRESS = 10036
'An operation was attempted on a non-blocking socket that already had
'an operation in progress.
Public Const WSAEALREADY = 10037
'An operation was attempted on something that is not a socket.
Public Const WSAENOTSOCK = 10038
'A required address was omitted from an operation on a socket.
Public Const WSAEDESTADDRREQ = 10039
'A message sent on a datagram socket was larger than the internal message
'buffer or some other network limit, or the buffer used to receive a datagram
'into was smaller than the datagram itself.
Public Const WSAEMSGSIZE = 10040
'A protocol was specified in the socket function call that does not support
'the semantics of the socket type requested.
Public Const WSAEPROTOTYPE = 10041
'An unknown, invalid, or unsupported option or level was specified in
'a getsockopt or setsockopt call.
Public Const WSAENOPROTOOPT = 10042
'The requested protocol has not been configured into the system, or
'no implementation for it exists.
Public Const WSAEPROTONOSUPPORT = 10043
'The support for the specified socket type does not exist in this address family.
Public Const WSAESOCKTNOSUPPORT = 10044
'The attempted operation is not supported for the type of object referenced.
Public Const WSAEOPNOTSUPP = 10045
'The protocol family has not been configured into the system or no
'implementation for it exists.
Public Const WSAEPFNOSUPPORT = 10046
'An address incompatible with the requested protocol was used.
Public Const WSAEAFNOSUPPORT = 10047
'Only one usage of each socket address (protocol/network address/port)
'is normally permitted.
Public Const WSAEADDRINUSE = 10048
'The requested address is not valid in its context.
Public Const WSAEADDRNOTAVAIL = 10049
'A socket operation encountered a dead network.
Public Const WSAENETDOWN = 10050
'A socket operation was attempted to an unreachable network.
Public Const WSAENETUNREACH = 10051
'The connection has been broken due to keep-alive activity detecting
'a failure while the operation was in progress.
Public Const WSAENETRESET = 10052
'An established connection was aborted by the software in your host machine.
Public Const WSAECONNABORTED = 10053
'An existing connection was forcibly closed by the remote host.
Public Const WSAECONNRESET = 10054
'An operation on a socket could not be performed because the system lacked
'sufficient buffer space or because a queue was full.
Public Const WSAENOBUFS = 10055
'A connect request was made on an already connected socket.
Public Const WSAEISCONN = 10056
'A request to send or receive data was disallowed because the socket is not
'connected and (when sending on a datagram socket using a sendto call) no
'address was supplied.
Public Const WSAENOTCONN = 10057
'A request to send or receive data was disallowed because the socket had
'already been shut down in that direction with a previous shutdown call.
Public Const WSAESHUTDOWN = 10058
'Too many references to some kernel object.
Public Const WSAETOOMANYREFS = 10059
'A connection attempt failed because the connected party did not properly
'respond after a period of time, or established connection failed because
'connected host has failed to respond.
Public Const WSAETIMEDOUT = 10060
'No connection could be made because the target machine actively refused it.
Public Const WSAECONNREFUSED = 10061
'Cannot translate name.
Public Const WSAELOOP = 10062
'Name component or name was too long.
Public Const WSAENAMETOOLONG = 10063
'A socket operation failed because the destination host was down.
Public Const WSAEHOSTDOWN = 10064
'A socket operation was attempted to an unreachable host.
Public Const WSAEHOSTUNREACH = 10065
'Cannot remove a directory that is not empty.
Public Const WSAENOTEMPTY = 10066
'A Windows Sockets implementation may have a limit on the number of applications
'that may use it simultaneously.
Public Const WSAEPROCLIM = 10067
'Ran out of quota.
Public Const WSAEUSERS = 10068
'Ran out of disk quota.
Public Const WSAEDQUOT = 10069
'File handle reference is no longer available.
Public Const WSAESTALE = 10070
'Item is not available locally.
Public Const WSAEREMOTE = 10071
'WSAStartup cannot function at this time because the underlying system it
'uses to provide network services is currently unavailable.
Public Const WSASYSNOTREADY = 10091
'The Windows Sockets version requested is not supported.
Public Const WSAVERNOTSUPPORTED = 10092
'Either the application has not called WSAStartup, or WSAStartup failed.
Public Const WSANOTINITIALISED = 10093
'Returned by WSARecv or WSARecvFrom to indicate the remote party has initiated
'a graceful shutdown sequence.
Public Const WSAEDISCON = 10101
'No more results can be returned by WSALookupServiceNext.
Public Const WSAENOMORE = 10102
'A call to WSALookupServiceEnd was made while this call was still processing.
'The call has been canceled.
Public Const WSAECANCELLED = 10103
'The procedure call table is invalid.
Public Const WSAEINVALIDPROCTABLE = 10104
'The requested service provider is invalid.
Public Const WSAEINVALIDPROVIDER = 10105
'The requested service provider could not be loaded or initialized.
Public Const WSAEPROVIDERFAILEDINIT = 10106
'A system call that should never fail has failed.
Public Const WSASYSCALLFAILURE = 10107
'No such service is known. The service cannot be found in the specified name space.
Public Const WSASERVICE_NOT_FOUND = 10108
'The specified class was not found.
Public Const WSATYPE_NOT_FOUND = 10109
'No more results can be returned by WSALookupServiceNext.
Public Const WSA_E_NO_MORE = 10110
'A call to WSALookupServiceEnd was made while this call was still processing.
'The call has been canceled.
Public Const WSA_E_CANCELLED = 10111
'A database query failed because it was actively refused.
Public Const WSAEREFUSED = 10112
'No such host is known.
Public Const WSAHOST_NOT_FOUND = 11001
'This is usually a temporary error during hostname resolution and means that
'the local server did not receive a response from an authoritative server.
Public Const WSATRY_AGAIN = 11002
'A non-recoverable error occurred during a database lookup.
Public Const WSANO_RECOVERY = 11003
'The requested name is valid, but no data of the requested type was found.
Public Const WSANO_DATA = 11004
'At least one reserve has arrived.
Public Const WSA_QOS_RECEIVERS = 11005
'At least one path has arrived.
Public Const WSA_QOS_SENDERS = 11006
'There are no senders.
Public Const WSA_QOS_NO_SENDERS = 11007
'There are no receivers.
Public Const WSA_QOS_NO_RECEIVERS = 11008
'Reserve has been confirmed.
Public Const WSA_QOS_REQUEST_CONFIRMED = 11009
'Error due to lack of resources.
Public Const WSA_QOS_ADMISSION_FAILURE = 11010
'Rejected for administrative reasons - bad credentials.
Public Const WSA_QOS_POLICY_FAILURE = 11011
'Unknown or conflicting style.
Public Const WSA_QOS_BAD_STYLE = 11012
'Problem with some part of the filterspec or providerspecific buffer in general.
Public Const WSA_QOS_BAD_OBJECT = 11013
'Problem with some part of the flowspec.
Public Const WSA_QOS_TRAFFIC_CTRL_ERROR = 11014
'General QOS error.
Public Const WSA_QOS_GENERIC_ERROR = 11015
'An invalid or unrecognized service type was found in the flowspec.
Public Const WSA_QOS_ESERVICETYPE = 11016
'An invalid or inconsistent flowspec was found in the QOS structure.
Public Const WSA_QOS_EFLOWSPEC = 11017
'Invalid QOS provider-specific buffer.
Public Const WSA_QOS_EPROVSPECBUF = 11018
'An invalid QOS filter style was used.
Public Const WSA_QOS_EFILTERSTYLE = 11019
'An invalid QOS filter type was used.
Public Const WSA_QOS_EFILTERTYPE = 11020
'An incorrect number of QOS FILTERSPECs were specified in the FLOWDESCRIPTOR.
Public Const WSA_QOS_EFILTERCOUNT = 11021
'An object with an invalid ObjectLength field was specified in the
'QOS provider-specific buffer.
Public Const WSA_QOS_EOBJLENGTH = 11022
'An incorrect number of flow descriptors was specified in the QOS structure.
Public Const WSA_QOS_EFLOWCOUNT = 11023
'An unrecognized object was found in the QOS provider-specific buffer.
Public Const WSA_QOS_EUNKOWNPSOBJ = 11024
'An invalid policy object was found in the QOS provider-specific buffer.
Public Const WSA_QOS_EPOLICYOBJ = 11025
'An invalid QOS flow descriptor was found in the flow descriptor list.
Public Const WSA_QOS_EFLOWDESC = 11026
'An invalid or inconsistent flowspec was found in the QOS provider specific buffer.
Public Const WSA_QOS_EPSFLOWSPEC = 11027
'An invalid FILTERSPEC was found in the QOS provider-specific buffer.
Public Const WSA_QOS_EPSFILTERSPEC = 11028
'An invalid shape discard mode object was found in the QOS provider specific buffer.
Public Const WSA_QOS_ESDMODEOBJ = 11029
'An invalid shaping rate object was found in the QOS provider-specific buffer.
Public Const WSA_QOS_ESHAPERATEOBJ = 11030
'A reserved policy element was found in the QOS provider-specific buffer.
Public Const WSA_QOS_RESERVED_PETYPE = 11031


'--------------------------------------------------
'         End of WinSock Error Codes
''
'               10000 to 11999                '
'''''''''''''''''''''''''/


'--------------------------------------------------
'           Side By Side Error Codes
''
''               14000 to 14999
'''''''''''''''''''''''''/


'The requested section was not present in the activation context.
Public Const ERROR_SXS_SECTION_NOT_FOUND = 14000
'This application has failed to start because the application configuration is
'incorrect. Reinstalling the application may fix this problem.
Public Const ERROR_SXS_CANT_GEN_ACTCTX = 14001
'The application binding data format is invalid.
Public Const ERROR_SXS_INVALID_ACTCTXDATA_FORMAT = 14002
'The referenced assembly is not installed on your system.
Public Const ERROR_SXS_ASSEMBLY_NOT_FOUND = 14003
'The manifest file does not begin with the required tag and format information.
Public Const ERROR_SXS_MANIFEST_FORMAT_ERROR = 14004
'The manifest file contains one or more syntax errors.
Public Const ERROR_SXS_MANIFEST_PARSE_ERROR = 14005
'The application attempted to activate a disabled activation context.
Public Const ERROR_SXS_ACTIVATION_CONTEXT_DISABLED = 14006
'The requested lookup key was not found in any active activation context.
Public Const ERROR_SXS_KEY_NOT_FOUND = 14007
'A component version required by the application conflicts with another
'component version already active.
Public Const ERROR_SXS_VERSION_CONFLICT = 14008
'The type requested activation context section does not match the query API used.
Public Const ERROR_SXS_WRONG_SECTION_TYPE = 14009
'Lack of system resources has required isolated activation to be disabled for
'the current thread of execution.
Public Const ERROR_SXS_THREAD_QUERIES_DISABLED = 14010
'An attempt to set the process default activation context failed because the
'process default activation context was already set.
Public Const ERROR_SXS_PROCESS_DEFAULT_ALREADY_SET = 14011
'The encoding group identifier specified is not recognized.
Public Const ERROR_SXS_UNKNOWN_ENCODING_GROUP = 14012
'The encoding requested is not recognized.
Public Const ERROR_SXS_UNKNOWN_ENCODING = 14013
'The manifest contains a reference to an invalid URI.
Public Const ERROR_SXS_INVALID_XML_NAMESPACE_URI = 14014
'The application manifest contains a reference to a dependent assembly which
'is not installed
Public Const ERROR_SXS_ROOT_MANIFEST_DEPENDENCY_NOT_INSTALLED = 14015
'The manifest for an assembly used by the application has a reference to
'a dependent assembly which is not installed
Public Const ERROR_SXS_LEAF_MANIFEST_DEPENDENCY_NOT_INSTALLED = 14016
'The manifest contains an attribute for the assembly identity which is not valid.
Public Const ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE = 14017
'The manifest is missing the required default namespace specification on
'the assembly element.
Public Const ERROR_SXS_MANIFEST_MISSING_REQUIRED_DEFAULT_NAMESPACE = 14018
'The manifest has a default namespace specified on the assembly element
'but its value is not "urn:schemas-microsoft-com:asm.v1".
Public Const ERROR_SXS_MANIFEST_INVALID_REQUIRED_DEFAULT_NAMESPACE = 14019
'The private manifest probed has crossed reparse-point-associated path
Public Const ERROR_SXS_PRIVATE_MANIFEST_CROSS_PATH_WITH_REPARSE_POINT = 14020
'Two or more components referenced directly or indirectly by the application
'manifest have files by the same name.
Public Const ERROR_SXS_DUPLICATE_DLL_NAME = 14021
'Two or more components referenced directly or indirectly by the application
'manifest have window classes with the same name.
Public Const ERROR_SXS_DUPLICATE_WINDOWCLASS_NAME = 14022
'Two or more components referenced directly or indirectly by
'the application manifest have the same COM server CLSIDs.
Public Const ERROR_SXS_DUPLICATE_CLSID = 14023
'Two or more components referenced directly or indirectly by
'the application manifest have proxies for the same COM interface IIDs.
Public Const ERROR_SXS_DUPLICATE_IID = 14024
'Two or more components referenced directly or indirectly by
'the application manifest have the same COM type library TLBIDs.
Public Const ERROR_SXS_DUPLICATE_TLBID = 14025
'Two or more components referenced directly or indirectly by
'the application manifest have the same COM ProgIDs.
Public Const ERROR_SXS_DUPLICATE_PROGID = 14026
'Two or more components referenced directly or indirectly by
'the application manifest are different versions of the same component which
'is not permitted.
Public Const ERROR_SXS_DUPLICATE_ASSEMBLY_NAME = 14027
'A component's file does not match the verification information present in the
'component manifest.
Public Const ERROR_SXS_FILE_HASH_MISMATCH = 14028
'The policy manifest contains one or more syntax errors.
Public Const ERROR_SXS_POLICY_PARSE_ERROR = 14029
'Manifest Parse Error : A string literal was expected, but no opening quote
'character was found.
Public Const ERROR_SXS_XML_E_MISSINGQUOTE = 14030
'Manifest Parse Error : Incorrect syntax was used in a comment.
Public Const ERROR_SXS_XML_E_COMMENTSYNTAX = 14031
'Manifest Parse Error : A name was started with an invalid character.
Public Const ERROR_SXS_XML_E_BADSTARTNAMECHAR = 14032
'Manifest Parse Error : A name contained an invalid character.
Public Const ERROR_SXS_XML_E_BADNAMECHAR = 14033
'Manifest Parse Error : A string literal contained an invalid character.
Public Const ERROR_SXS_XML_E_BADCHARINSTRING = 14034
'Manifest Parse Error : Invalid syntax for an xml declaration.
Public Const ERROR_SXS_XML_E_XMLDECLSYNTAX = 14035
'Manifest Parse Error : An Invalid character was found in text content.
Public Const ERROR_SXS_XML_E_BADCHARDATA = 14036
'Manifest Parse Error : Required white space was missing.
Public Const ERROR_SXS_XML_E_MISSINGWHITESPACE = 14037
'Manifest Parse Error : The character '>'was expected.
Public Const ERROR_SXS_XML_E_EXPECTINGTAGEND = 14038
'Manifest Parse Error : A semi colon character was expected.
Public Const ERROR_SXS_XML_E_MISSINGSEMICOLON = 14039
'Manifest Parse Error : Unbalanced parentheses.
Public Const ERROR_SXS_XML_E_UNBALANCEDPAREN = 14040
'Manifest Parse Error : Internal error.
Public Const ERROR_SXS_XML_E_INTERNALERROR = 14041
'Manifest Parse Error : Whitespace is not allowed at this location.
Public Const ERROR_SXS_XML_E_UNEXPECTED_WHITESPACE = 14042
'Manifest Parse Error : End of file reached in invalid state for current encoding.
Public Const ERROR_SXS_XML_E_INCOMPLETE_ENCODING = 14043
'Manifest Parse Error : Missing parenthesis.
Public Const ERROR_SXS_XML_E_MISSING_PAREN = 14044
'Manifest Parse Error : A single or double closing quote character (\'or \")
'is missing.
Public Const ERROR_SXS_XML_E_EXPECTINGCLOSEQUOTE = 14045
'Manifest Parse Error : Multiple colons are not allowed in a name.
Public Const ERROR_SXS_XML_E_MULTIPLE_COLONS = 14046
'Manifest Parse Error : Invalid character for decimal digit.
Public Const ERROR_SXS_XML_E_INVALID_DECIMAL = 14047
'Manifest Parse Error : Invalid character for hexidecimal digit.
Public Const ERROR_SXS_XML_E_INVALID_HEXIDECIMAL = 14048
'Manifest Parse Error : Invalid unicode character value for this platform.
Public Const ERROR_SXS_XML_E_INVALID_UNICODE = 14049
'Manifest Parse Error : Expecting whitespace or '?'.
Public Const ERROR_SXS_XML_E_WHITESPACEORQUESTIONMARK = 14050
'Manifest Parse Error : End tag was not expected at this location.
Public Const ERROR_SXS_XML_E_UNEXPECTEDENDTAG = 14051
'Manifest Parse Error : The following tags were not closed: %1.
Public Const ERROR_SXS_XML_E_UNCLOSEDTAG = 14052
'Manifest Parse Error : Duplicate attribute.
Public Const ERROR_SXS_XML_E_DUPLICATEATTRIBUTE = 14053
'Manifest Parse Error : Only one top level element is allowed in an XML document.
Public Const ERROR_SXS_XML_E_MULTIPLEROOTS = 14054
'Manifest Parse Error : Invalid at the top level of the document.
Public Const ERROR_SXS_XML_E_INVALIDATROOTLEVEL = 14055
'Manifest Parse Error : Invalid xml declaration.
Public Const ERROR_SXS_XML_E_BADXMLDECL = 14056
'Manifest Parse Error : XML document must have a top level element.
Public Const ERROR_SXS_XML_E_MISSINGROOT = 14057
'Manifest Parse Error : Unexpected end of file.
Public Const ERROR_SXS_XML_E_UNEXPECTEDEOF = 14058
'Manifest Parse Error : Parameter entities cannot be used inside markup
'declarations in an internal subset.
Public Const ERROR_SXS_XML_E_BADPEREFINSUBSET = 14059
'Manifest Parse Error : Element was not closed.
Public Const ERROR_SXS_XML_E_UNCLOSEDSTARTTAG = 14060
'Manifest Parse Error : End element was missing the character '>'.
Public Const ERROR_SXS_XML_E_UNCLOSEDENDTAG = 14061
'Manifest Parse Error : A string literal was not closed.
Public Const ERROR_SXS_XML_E_UNCLOSEDSTRING = 14062
'Manifest Parse Error : A comment was not closed.
Public Const ERROR_SXS_XML_E_UNCLOSEDCOMMENT = 14063
'Manifest Parse Error : A declaration was not closed.
Public Const ERROR_SXS_XML_E_UNCLOSEDDECL = 14064
'Manifest Parse Error : A CDATA section was not closed.
Public Const ERROR_SXS_XML_E_UNCLOSEDCDATA = 14065
'Manifest Parse Error : The namespace prefix is not allowed to start with the
'reserved string "xml".
Public Const ERROR_SXS_XML_E_RESERVEDNAMESPACE = 14066
'Manifest Parse Error : System does not support the specified encoding.
Public Const ERROR_SXS_XML_E_INVALIDENCODING = 14067
'Manifest Parse Error : Switch from current encoding to specified encoding not
'supported.
Public Const ERROR_SXS_XML_E_INVALIDSWITCH = 14068
'Manifest Parse Error : The name 'xml'is reserved and must be lower case.
Public Const ERROR_SXS_XML_E_BADXMLCASE = 14069
'Manifest Parse Error : The standalone attribute must have the value 'yes'or 'no'.
Public Const ERROR_SXS_XML_E_INVALID_STANDALONE = 14070
'Manifest Parse Error : The standalone attribute cannot be used in external
'entities.
Public Const ERROR_SXS_XML_E_UNEXPECTED_STANDALONE = 14071
'Manifest Parse Error : Invalid version number.
Public Const ERROR_SXS_XML_E_INVALID_VERSION = 14072
'Manifest Parse Error : Missing equals sign between attribute and attribute value.
Public Const ERROR_SXS_XML_E_MISSINGEQUALS = 14073
'Assembly Protection Error : Unable to recover the specified assembly.
Public Const ERROR_SXS_PROTECTION_RECOVERY_FAILED = 14074
'Assembly Protection Error : The public key for an assembly was too short to
'be allowed.
Public Const ERROR_SXS_PROTECTION_PUBLIC_KEY_TOO_SHORT = 14075
'Assembly Protection Error : The catalog for an assembly is not valid, or does
'not match the assembly's manifest.
Public Const ERROR_SXS_PROTECTION_CATALOG_NOT_VALID = 14076
'An HRESULT could not be translated to a corresponding Win32 error code.
Public Const ERROR_SXS_UNTRANSLATABLE_HRESULT = 14077
'Assembly Protection Error : The catalog for an assembly is missing.
Public Const ERROR_SXS_PROTECTION_CATALOG_FILE_MISSING = 14078
'The supplied assembly identity is missing one or more attributes which must
'be present in this context.
Public Const ERROR_SXS_MISSING_ASSEMBLY_IDENTITY_ATTRIBUTE = 14079
'The supplied assembly identity has one or more attribute names that contain
'characters not permitted in XML names.
Public Const ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME = 14080


'--------------------------------------------------
'         End of Side By Side Error Codes
''
''               14000 to 14999
'''''''''''''''''''''''''/


'--------------------------------------------------
'         Start of IPSec Error codes
''
''               13000 to 13999
'''''''''''''''''''''''''/
'The specified quick mode policy already exists.
Public Const ERROR_IPSEC_QM_POLICY_EXISTS = 13000
'The specified quick mode policy was not found.
Public Const ERROR_IPSEC_QM_POLICY_NOT_FOUND = 13001
'The specified quick mode policy is being used.
Public Const ERROR_IPSEC_QM_POLICY_IN_USE = 13002
'The specified main mode policy already exists.
Public Const ERROR_IPSEC_MM_POLICY_EXISTS = 13003
'The specified main mode policy was not found
Public Const ERROR_IPSEC_MM_POLICY_NOT_FOUND = 13004
'The specified main mode policy is being used.
Public Const ERROR_IPSEC_MM_POLICY_IN_USE = 13005
'The specified main mode filter already exists.
Public Const ERROR_IPSEC_MM_FILTER_EXISTS = 13006
'The specified main mode filter was not found.
Public Const ERROR_IPSEC_MM_FILTER_NOT_FOUND = 13007
'The specified transport mode filter already exists.
Public Const ERROR_IPSEC_TRANSPORT_FILTER_EXISTS = 13008
'The specified transport mode filter does not exist.
Public Const ERROR_IPSEC_TRANSPORT_FILTER_NOT_FOUND = 13009
'The specified main mode authentication list exists.
Public Const ERROR_IPSEC_MM_AUTH_EXISTS = 13010
'The specified main mode authentication list was not found.
Public Const ERROR_IPSEC_MM_AUTH_NOT_FOUND = 13011
'The specified quick mode policy is being used.
Public Const ERROR_IPSEC_MM_AUTH_IN_USE = 13012
'The specified main mode policy was not found.
Public Const ERROR_IPSEC_DEFAULT_MM_POLICY_NOT_FOUND = 13013
'The specified quick mode policy was not found
Public Const ERROR_IPSEC_DEFAULT_MM_AUTH_NOT_FOUND = 13014
'The manifest file contains one or more syntax errors.
Public Const ERROR_IPSEC_DEFAULT_QM_POLICY_NOT_FOUND = 13015
'The application attempted to activate a disabled activation context.
Public Const ERROR_IPSEC_TUNNEL_FILTER_EXISTS = 13016
'The requested lookup key was not found in any active activation context.
Public Const ERROR_IPSEC_TUNNEL_FILTER_NOT_FOUND = 13017
'The Main Mode filter is pending deletion.
Public Const ERROR_IPSEC_MM_FILTER_PENDING_DELETION = 13018
'The transport filter is pending deletion.
Public Const ERROR_IPSEC_TRANSPORT_FILTER_PENDING_DELETION = 13019
'The tunnel filter is pending deletion.
Public Const ERROR_IPSEC_TUNNEL_FILTER_PENDING_DELETION = 13020
'The Main Mode policy is pending deletion.
Public Const ERROR_IPSEC_MM_POLICY_PENDING_DELETION = 13021
'The Main Mode authentication bundle is pending deletion.
Public Const ERROR_IPSEC_MM_AUTH_PENDING_DELETION = 13022
'The Quick Mode policy is pending deletion.
Public Const ERROR_IPSEC_QM_POLICY_PENDING_DELETION = 13023
'The Main Mode policy was successfully added, but some of the requested
'offers are not supported.
Public Const WARNING_IPSEC_MM_POLICY_PRUNED = 13024
'The Quick Mode policy was successfully added, but some of the requested
'offers are not supported.
Public Const WARNING_IPSEC_QM_POLICY_PRUNED = 13025
'ERROR_IPSEC_IKE_NEG_STATUS_BEGIN
Public Const ERROR_IPSEC_IKE_NEG_STATUS_BEGIN = 13800
'IKE authentication credentials are unacceptable
Public Const ERROR_IPSEC_IKE_AUTH_FAIL = 13801
'IKE security attributes are unacceptable
Public Const ERROR_IPSEC_IKE_ATTRIB_FAIL = 13802
'IKE Negotiation in progress
Public Const ERROR_IPSEC_IKE_NEGOTIATION_PENDING = 13803
'General processing error
Public Const ERROR_IPSEC_IKE_GENERAL_PROCESSING_ERROR = 13804
'Negotiation timed out
Public Const ERROR_IPSEC_IKE_TIMED_OUT = 13805
'IKE failed to find valid machine certificate
Public Const ERROR_IPSEC_IKE_NO_CERT = 13806
'IKE SA deleted by peer before establishment completed
Public Const ERROR_IPSEC_IKE_SA_DELETED = 13807
'IKE SA deleted before establishment completed
Public Const ERROR_IPSEC_IKE_SA_REAPED = 13808
'Negotiation request sat in Queue too long
Public Const ERROR_IPSEC_IKE_MM_ACQUIRE_DROP = 13809
'Negotiation request sat in Queue too long
Public Const ERROR_IPSEC_IKE_QM_ACQUIRE_DROP = 13810
'Negotiation request sat in Queue too long
Public Const ERROR_IPSEC_IKE_QUEUE_DROP_MM = 13811
'Negotiation request sat in Queue too long
Public Const ERROR_IPSEC_IKE_QUEUE_DROP_NO_MM = 13812
'No response from peer
Public Const ERROR_IPSEC_IKE_DROP_NO_RESPONSE = 13813
'Negotiation took too long
Public Const ERROR_IPSEC_IKE_MM_DELAY_DROP = 13814
'Negotiation took too long
Public Const ERROR_IPSEC_IKE_QM_DELAY_DROP = 13815
'Unknown error occurred
Public Const ERROR_IPSEC_IKE_ERROR = 13816
'Certificate Revocation Check failed
Public Const ERROR_IPSEC_IKE_CRL_FAILED = 13817
'Invalid certificate key usage
Public Const ERROR_IPSEC_IKE_INVALID_KEY_USAGE = 13818
'Invalid certificate type
Public Const ERROR_IPSEC_IKE_INVALID_CERT_TYPE = 13819
'No private key associated with machine certificate
Public Const ERROR_IPSEC_IKE_NO_PRIVATE_KEY = 13820
'Failure in Diffie-Helman computation
Public Const ERROR_IPSEC_IKE_DH_FAIL = 13822
'Invalid header
Public Const ERROR_IPSEC_IKE_INVALID_HEADER = 13824
'No policy configured
Public Const ERROR_IPSEC_IKE_NO_POLICY = 13825
'Failed to verify signature
Public Const ERROR_IPSEC_IKE_INVALID_SIGNATURE = 13826
'Failed to authenticate using kerberos
Public Const ERROR_IPSEC_IKE_KERBEROS_ERROR = 13827
'Peer's certificate did not have a public key
Public Const ERROR_IPSEC_IKE_NO_PUBLIC_KEY = 13828

'These must stay as a unit.


'Error processing error payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR = 13829
'Error processing SA payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR_SA = 13830
'Error processing Proposal payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR_PROP = 13831
'Error processing Transform payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR_TRANS = 13832
'Error processing KE payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR_KE = 13833
'Error processing ID payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR_ID = 13834
'Error processing Cert payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR_CERT = 13835
'Error processing Certificate Request payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR_CERT_REQ = 13836
'Error processing Hash payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR_HASH = 13837
'Error processing Signature payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR_SIG = 13838
'Error processing Nonce payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR_NONCE = 13839
'Error processing Notify payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR_NOTIFY = 13840
'Error processing Delete Payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR_DELETE = 13841
'Error processing VendorId payload
Public Const ERROR_IPSEC_IKE_PROCESS_ERR_VENDOR = 13842
'Invalid payload received
Public Const ERROR_IPSEC_IKE_INVALID_PAYLOAD = 13843
'Soft SA loaded
Public Const ERROR_IPSEC_IKE_LOAD_SOFT_SA = 13844
'Soft SA torn down
Public Const ERROR_IPSEC_IKE_SOFT_SA_TORN_DOWN = 13845
'Invalid cookie received.
Public Const ERROR_IPSEC_IKE_INVALID_COOKIE = 13846
'Peer failed to send valid machine certificate
Public Const ERROR_IPSEC_IKE_NO_PEER_CERT = 13847
'Certification Revocation check of peer's certificate failed
Public Const ERROR_IPSEC_IKE_PEER_CRL_FAILED = 13848
'New policy invalidated SAs formed with old policy
Public Const ERROR_IPSEC_IKE_POLICY_CHANGE = 13849
'There is no available Main Mode IKE policy.
Public Const ERROR_IPSEC_IKE_NO_MM_POLICY = 13850
'Failed to enabled TCB privilege.
Public Const ERROR_IPSEC_IKE_NOTCBPRIV = 13851
'Failed to load SECURITY.DLL.
Public Const ERROR_IPSEC_IKE_SECLOADFAIL = 13852
'Failed to obtain security function table dispatch address from SSPI.
Public Const ERROR_IPSEC_IKE_FAILSSPINIT = 13853
'Failed to query Kerberos package to obtain max token size.
Public Const ERROR_IPSEC_IKE_FAILQUERYSSP = 13854
'Failed to obtain Kerberos server credentials for ISAKMP/ERROR_IPSEC_IKE
'service. Kerberos authentication will not function. The most likely reason
'for this is lack of domain membership. This is normal if your computer is
'a member of a workgroup.
Public Const ERROR_IPSEC_IKE_SRVACQFAIL = 13855
'Failed to determine SSPI principal name for ISAKMP/ERROR_IPSEC_IKE service
'(QueryCredentialsAttributes).
Public Const ERROR_IPSEC_IKE_SRVQUERYCRED = 13856
'Failed to obtain new SPI for the inbound SA from Ipsec driver.
'The most common cause for this is that the driver does not have the correct
'filter. Check your policy to verify the filters.
Public Const ERROR_IPSEC_IKE_GETSPIFAIL = 13857
'Given filter is invalid
Public Const ERROR_IPSEC_IKE_INVALID_FILTER = 13858
'Memory allocation failed.
Public Const ERROR_IPSEC_IKE_OUT_OF_MEMORY = 13859
'Failed to add Security Association to IPSec Driver. The most common cause for
'this is if the IKE negotiation took too long to complete. If the problem
'persists, reduce the load on the faulting machine.
Public Const ERROR_IPSEC_IKE_ADD_UPDATE_KEY_FAILED = 13860
'Invalid policy
Public Const ERROR_IPSEC_IKE_INVALID_POLICY = 13861
'Invalid DOI
Public Const ERROR_IPSEC_IKE_UNKNOWN_DOI = 13862
'Invalid situation
Public Const ERROR_IPSEC_IKE_INVALID_SITUATION = 13863
'Diffie-Hellman failure
Public Const ERROR_IPSEC_IKE_DH_FAILURE = 13864
'Invalid Diffie-Hellman group
Public Const ERROR_IPSEC_IKE_INVALID_GROUP = 13865
'Error encrypting payload
Public Const ERROR_IPSEC_IKE_ENCRYPT = 13866
'Error decrypting payload
Public Const ERROR_IPSEC_IKE_DECRYPT = 13867
'Policy match error
Public Const ERROR_IPSEC_IKE_POLICY_MATCH = 13868
'Unsupported ID
Public Const ERROR_IPSEC_IKE_UNSUPPORTED_ID = 13869
'Hash verification failed
Public Const ERROR_IPSEC_IKE_INVALID_HASH = 13870
'Invalid hash algorithm
Public Const ERROR_IPSEC_IKE_INVALID_HASH_ALG = 13871
'Invalid hash size
Public Const ERROR_IPSEC_IKE_INVALID_HASH_SIZE = 13872
'Invalid encryption algorithm
Public Const ERROR_IPSEC_IKE_INVALID_ENCRYPT_ALG = 13873
'Invalid authentication algorithm
Public Const ERROR_IPSEC_IKE_INVALID_AUTH_ALG = 13874
'Invalid certificate signature
Public Const ERROR_IPSEC_IKE_INVALID_SIG = 13875
'Load failed
Public Const ERROR_IPSEC_IKE_LOAD_FAILED = 13876
'Deleted via RPC call
Public Const ERROR_IPSEC_IKE_RPC_DELETE = 13877
'Temporary state created to perform reinit. This is not a real failure.
Public Const ERROR_IPSEC_IKE_BENIGN_REINIT = 13878
'The lifetime value received in the Responder Lifetime Notify is below the
'Windows 2000 configured minimum value. Please fix the policy on the peer machine.
Public Const ERROR_IPSEC_IKE_INVALID_RESPONDER_LIFETIME_NOTIFY = 13879
'Key length in certificate is too small for configured security requirements.
Public Const ERROR_IPSEC_IKE_INVALID_CERT_KEYLEN = 13881
'Max number of established MM SAs to peer exceeded.
Public Const ERROR_IPSEC_IKE_MM_LIMIT = 13882
'IKE received a policy that disables negotiation.
Public Const ERROR_IPSEC_IKE_NEGOTIATION_DISABLED = 13883
'ERROR_IPSEC_IKE_NEG_STATUS_END
Public Const ERROR_IPSEC_IKE_NEG_STATUS_END = 13884

''''''''''''''''''
''   COM Error Codes
''
''''''''''''''''''
'The return value of COM functions and methods is an HRESULT.
'This is not a handle to anything, but is merely a 32-bit value
'with several fields encoded in the value. The parts of an
'HRESULT are shown below.
'Many of the macros and functions below were orginally defined to
'operate on SCODEs. SCODEs are no longer used. The macros are
'still present for compatibility and easy porting of Win16 code.
'Newly written code should use the HRESULT macros and functions.

'HRESULTs are 32 bit values layed out as follows:
' 3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
' 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
'+-+-+-+-+-+---------------------+-------------------------------+
'|S|R|C|N|r|    Facility         |               Code            |
'+-+-+-+-+-+---------------------+-------------------------------+
'where
'    S - Severity - indicates success/fail
'        0 - Success
'        1 - Fail (COERROR)
'    R - reserved portion of the facility code, corresponds to NT's
'            second severity bit.
'    C - reserved portion of the facility code, corresponds to NT's
'            C field.
'    N - reserved portion of the facility code. Used to indicate a
'            mapped NT status value.
'    r - reserved portion of the facility code. Reserved for internal
'            use. Used to indicate HRESULT values that are not status
'            values, but are instead message ids for display strings.
'    Facility - is the facility code
'    Code - is the facility's status code

'Severity values

Public Const SEVERITY_SUCCESS = 0
Public Const SEVERITY_ERROR = 1

'Map a WIN32 error value into a HRESULT
'Note: This assumes that WIN32 errors fall in the range -32k to 32k.
'Define bits here so macros are guaranteed to work

Public Const FACILITY_NT_BIT = &H10000000



'---------------------- HRESULT value definitions -----------------
'HRESULT definitions


Public Const NOERROR = 0

'Error definitions follow

'Codes &H4000-&H40ff are reserved for OLE
'Error codes


'Catastrophic failure
Public Const E_UNEXPECTED = (&H8000FFFF)

'if defined(_WIN32) && !defined(_MAC)


'Not implemented
Public Const E_NOTIMPL = (&H80004001)
'Ran out of memory
Public Const E_OUTOFMEMORY = (&H8007000E)
'One or more arguments are invalid
Public Const E_INVALIDARG = (&H80070057)
'No such interface supported
Public Const E_NOINTERFACE = (&H80004002)
'Invalid pointer
Public Const E_POINTER = (&H80004003)
'Invalid handle
Public Const E_HANDLE = (&H80070006)
'Operation aborted
Public Const E_ABORT = (&H80004004)
'Unspecified error
Public Const E_FAIL = (&H80004005)
'General access denied error
Public Const E_ACCESSDENIED = (&H80070005)

'else defined(_MAC)
'Not implemented
'Public Const E_NOTIMPL =                        (&H80000001)
'Ran out of memory
'Public Const E_OUTOFMEMORY =                    (&H80000002)
'One or more arguments are invalid
'Public Const E_INVALIDARG =                     (&H80000003)
'No such interface supported
'Public Const E_NOINTERFACE =                    (&H80000004)
'Invalid pointer
'Public Const E_POINTER =                        (&H80000005)
'Invalid handle
'Public Const E_HANDLE =                         (&H80000006)
'Operation aborted
'Public Const E_ABORT =                          (&H80000007)
'Unspecified error
'Public Const E_FAIL =                           (&H80000008)
'General access denied error
'Public Const E_ACCESSDENIED =                   (&H80000009)
'endif 'WIN32


'The data necessary to complete this operation is not yet available.
Public Const E_PENDING = (&H8000000A)
'Thread local storage failure
Public Const CO_E_INIT_TLS = (&H80004006)
'Get shared memory allocator failure
Public Const CO_E_INIT_SHARED_ALLOCATOR = (&H80004007)
'Get memory allocator failure
Public Const CO_E_INIT_MEMORY_ALLOCATOR = (&H80004008)
'Unable to initialize class cache
Public Const CO_E_INIT_CLASS_CACHE = (&H80004009)
'Unable to initialize RPC services
Public Const CO_E_INIT_RPC_CHANNEL = (&H8000400A)
'Cannot set thread local storage channel control
Public Const CO_E_INIT_TLS_SET_CHANNEL_CONTROL = (&H8000400B)
'Could not allocate thread local storage channel control
Public Const CO_E_INIT_TLS_CHANNEL_CONTROL = (&H8000400C)
'The user supplied memory allocator is unacceptable
Public Const CO_E_INIT_UNACCEPTED_USER_ALLOCATOR = (&H8000400D)
'The OLE service mutex already exists
Public Const CO_E_INIT_SCM_MUTEX_EXISTS = (&H8000400E)
'The OLE service file mapping already exists
Public Const CO_E_INIT_SCM_FILE_MAPPING_EXISTS = (&H8000400F)
'Unable to map view of file for OLE service
Public Const CO_E_INIT_SCM_MAP_VIEW_OF_FILE = (&H80004010)
'Failure attempting to launch OLE service
Public Const CO_E_INIT_SCM_EXEC_FAILURE = (&H80004011)
'There was an attempt to call CoInitialize a second time while single threaded
Public Const CO_E_INIT_ONLY_SINGLE_THREADED = (&H80004012)
'A Remote activation was necessary but was not allowed
Public Const CO_E_CANT_REMOTE = (&H80004013)
'A Remote activation was necessary but the server name provided was invalid
Public Const CO_E_BAD_SERVER_NAME = (&H80004014)
'The class is configured to run as a security id different from the caller
Public Const CO_E_WRONG_SERVER_IDENTITY = (&H80004015)
'Use of Ole1 services requiring DDE windows is disabled
Public Const CO_E_OLE1DDE_DISABLED = (&H80004016)
'A RunAs specification must be <domain name>\<user name> or simply <user name>
Public Const CO_E_RUNAS_SYNTAX = (&H80004017)
'The server process could not be started. The pathname may be incorrect.
Public Const CO_E_CREATEPROCESS_FAILURE = (&H80004018)
'The server process could not be started as the configured identity.
'The pathname may be incorrect or unavailable.
Public Const CO_E_RUNAS_CREATEPROCESS_FAILURE = (&H80004019)
'The server process could not be started because the configured identity
'is incorrect. Check the username and password.
Public Const CO_E_RUNAS_LOGON_FAILURE = (&H8000401A)
'The client is not allowed to launch this server.
Public Const CO_E_LAUNCH_PERMSSION_DENIED = (&H8000401B)
'The service providing this server could not be started.
Public Const CO_E_START_SERVICE_FAILURE = (&H8000401C)
'This computer was unable to communicate with the computer providing the server.
Public Const CO_E_REMOTE_COMMUNICATION_FAILURE = (&H8000401D)
'The server did not respond after being launched.
Public Const CO_E_SERVER_START_TIMEOUT = (&H8000401E)
'The registration information for this server is inconsistent or incomplete.
Public Const CO_E_CLSREG_INCONSISTENT = (&H8000401F)
'The registration information for this interface is inconsistent or incomplete.
Public Const CO_E_IIDREG_INCONSISTENT = (&H80004020)
'The operation attempted is not supported.
Public Const CO_E_NOT_SUPPORTED = (&H80004021)
'A dll must be loaded.
Public Const CO_E_RELOAD_DLL = (&H80004022)
'A Microsoft Software Installer error was encountered.
Public Const CO_E_MSI_ERROR = (&H80004023)
'The specified activation could not occur in the client context as specified.
Public Const CO_E_ATTEMPT_TO_CREATE_OUTSIDE_CLIENT_CONTEXT = (&H80004024)
'Activations on the server are paused.
Public Const CO_E_SERVER_PAUSED = (&H80004025)
'Activations on the server are not paused.
Public Const CO_E_SERVER_NOT_PAUSED = (&H80004026)
'The component or application containing the component has been disabled.
Public Const CO_E_CLASS_DISABLED = (&H80004027)
'The common language runtime is not available
Public Const CO_E_CLRNOTAVAILABLE = (&H80004028)
'The thread-pool rejected the submitted asynchronous work.
Public Const CO_E_ASYNC_WORK_REJECTED = (&H80004029)
'The server started, but did not finish initializing in a timely fashion.
Public Const CO_E_SERVER_INIT_TIMEOUT = (&H8000402A)
'Unable to complete the call since there is no COM+ security context
'inside IObjectControl.Activate.
Public Const CO_E_NO_SECCTX_IN_ACTIVATE = (&H8000402B)
'The provided tracker configuration is invalid
Public Const CO_E_TRACKER_CONFIG = (&H80004030)
'The provided thread pool configuration is invalid
Public Const CO_E_THREADPOOL_CONFIG = (&H80004031)
'The provided side-by-side configuration is invalid
Public Const CO_E_SXS_CONFIG = (&H80004032)
'The server principal name (SPN) obtained during security negotiation is malformed.
Public Const CO_E_MALFORMED_SPN = (&H80004033)


'Success codes
Public Const S_OK = (&H0)
Public Const S_FALSE = (&H1)

'******************
'FACILITY_ITF
'******************

'Codes &H0-&H01ff are reserved for the OLE group of
'interfaces.


'Generic OLE errors that may be returned by many inerfaces

Public Const OLE_E_FIRST = (&H80040000)
Public Const OLE_E_LAST = (&H800400FF)
Public Const OLE_S_FIRST = (&H40000)
Public Const OLE_S_LAST = (&H400FF)

'Old OLE errors


'Invalid OLEVERB structure
Public Const OLE_E_OLEVERB = (&H80040000)
'Invalid advise flags
Public Const OLE_E_ADVF = (&H80040001)
'Can't enumerate any more, because the associated data is missing
Public Const OLE_E_ENUM_NOMORE = (&H80040002)
'This implementation doesn't take advises
Public Const OLE_E_ADVISENOTSUPPORTED = (&H80040003)
'There is no connection for this connection ID
Public Const OLE_E_NOCONNECTION = (&H80040004)
'Need to run the object to perform this operation
Public Const OLE_E_NOTRUNNING = (&H80040005)
'There is no cache to operate on
Public Const OLE_E_NOCACHE = (&H80040006)
'Uninitialized object
Public Const OLE_E_BLANK = (&H80040007)
'Linked object's source class has changed
Public Const OLE_E_CLASSDIFF = (&H80040008)
'Not able to get the moniker of the object
Public Const OLE_E_CANT_GETMONIKER = (&H80040009)
'Not able to bind to the source
Public Const OLE_E_CANT_BINDTOSOURCE = (&H8004000A)
'Object is static; operation not allowed
Public Const OLE_E_STATIC = (&H8004000B)
'User canceled out of save dialog
Public Const OLE_E_PROMPTSAVECANCELLED = (&H8004000C)
'Invalid rectangle
Public Const OLE_E_INVALIDRECT = (&H8004000D)
'compobj.dll is too old for the ole2.dll initialized
Public Const OLE_E_WRONGCOMPOBJ = (&H8004000E)
'Invalid window handle
Public Const OLE_E_INVALIDHWND = (&H8004000F)
'Object is not in any of the inplace active states
Public Const OLE_E_NOT_INPLACEACTIVE = (&H80040010)
'Not able to convert object
Public Const OLE_E_CANTCONVERT = (&H80040011)
'Not able to perform the operation because object is not given storage yet
Public Const OLE_E_NOSTORAGE = (&H80040012)
'Invalid FORMATETC structure
Public Const DV_E_FORMATETC = (&H80040064)
'Invalid DVTARGETDEVICE structure
Public Const DV_E_DVTARGETDEVICE = (&H80040065)
'Invalid STDGMEDIUM structure
Public Const DV_E_STGMEDIUM = (&H80040066)
'Invalid STATDATA structure
Public Const DV_E_STATDATA = (&H80040067)
'Invalid lindex
Public Const DV_E_LINDEX = (&H80040068)
'Invalid tymed
Public Const DV_E_TYMED = (&H80040069)
'Invalid clipboard format
Public Const DV_E_CLIPFORMAT = (&H8004006A)
'Invalid aspect(s)
Public Const DV_E_DVASPECT = (&H8004006B)
'tdSize parameter of the DVTARGETDEVICE structure is invalid
Public Const DV_E_DVTARGETDEVICE_SIZE = (&H8004006C)
'Object doesn't support IViewObject interface
Public Const DV_E_NOIVIEWOBJECT = (&H8004006D)

Public Const DRAGDROP_E_FIRST = &H80040100
Public Const DRAGDROP_E_LAST = &H8004010F
Public Const DRAGDROP_S_FIRST = &H40100
Public Const DRAGDROP_S_LAST = &H4010F


'Trying to revoke a drop target that has not been registered
Public Const DRAGDROP_E_NOTREGISTERED = (&H80040100)
'This window has already been registered as a drop target
Public Const DRAGDROP_E_ALREADYREGISTERED = (&H80040101)
'Invalid window handle
Public Const DRAGDROP_E_INVALIDHWND = (&H80040102)

Public Const CLASSFACTORY_E_FIRST = &H80040110
Public Const CLASSFACTORY_E_LAST = &H8004011F
Public Const CLASSFACTORY_S_FIRST = &H40110
Public Const CLASSFACTORY_S_LAST = &H4011F


'Class does not support aggregation (or class object is remote)
Public Const CLASS_E_NOAGGREGATION = (&H80040110)
'ClassFactory cannot supply requested class
Public Const CLASS_E_CLASSNOTAVAILABLE = (&H80040111)
'Class is not licensed for use
Public Const CLASS_E_NOTLICENSED = (&H80040112)

Public Const MARSHAL_E_FIRST = &H80040120
Public Const MARSHAL_E_LAST = &H8004012F
Public Const MARSHAL_S_FIRST = &H40120
Public Const MARSHAL_S_LAST = &H4012F
Public Const DATA_E_FIRST = &H80040130
Public Const DATA_E_LAST = &H8004013F
Public Const DATA_S_FIRST = &H40130
Public Const DATA_S_LAST = &H4013F
Public Const VIEW_E_FIRST = &H80040140
Public Const VIEW_E_LAST = &H8004014F
Public Const VIEW_S_FIRST = &H40140
Public Const VIEW_S_LAST = &H4014F


'Error drawing view
Public Const VIEW_E_DRAW = (&H80040140)

Public Const REGDB_E_FIRST = &H80040150
Public Const REGDB_E_LAST = &H8004015F
Public Const REGDB_S_FIRST = &H40150
Public Const REGDB_S_LAST = &H4015F


'Could not read key from registry
Public Const REGDB_E_READREGDB = (&H80040150)
'Could not write key to registry
Public Const REGDB_E_WRITEREGDB = (&H80040151)
'Could not find the key in the registry
Public Const REGDB_E_KEYMISSING = (&H80040152)
'Invalid value for registry
Public Const REGDB_E_INVALIDVALUE = (&H80040153)
'Class not registered
Public Const REGDB_E_CLASSNOTREG = (&H80040154)
'Interface not registered
Public Const REGDB_E_IIDNOTREG = (&H80040155)
'Threading model entry is not valid
Public Const REGDB_E_BADTHREADINGMODEL = (&H80040156)

Public Const CAT_E_FIRST = &H80040160
Public Const CAT_E_LAST = &H80040161


'CATID does not exist
Public Const CAT_E_CATIDNOEXIST = (&H80040160)
'Description not found
Public Const CAT_E_NODESCRIPTION = (&H80040161)

'   Class Store Error Codes
Public Const CS_E_FIRST = &H80040164
Public Const CS_E_LAST = &H8004016F


'No package in the software installation data in the Active Directory
'meets this criteria.
Public Const CS_E_PACKAGE_NOTFOUND = (&H80040164)
'Deleting this will break the referential integrity of the software
'installation data in the Active Directory.
Public Const CS_E_NOT_DELETABLE = (&H80040165)
'The CLSID was not found in the software installation data in the
'Active Directory.
Public Const CS_E_CLASS_NOTFOUND = (&H80040166)
'The software installation data in the Active Directory is corrupt.
Public Const CS_E_INVALID_VERSION = (&H80040167)
'There is no software installation data in the Active Directory.
Public Const CS_E_NO_CLASSSTORE = (&H80040168)
'There is no software installation data object in the Active Directory.
Public Const CS_E_OBJECT_NOTFOUND = (&H80040169)
'The software installation data object in the Active Directory already exists.
Public Const CS_E_OBJECT_ALREADY_EXISTS = (&H8004016A)
'The path to the software installation data in the Active Directory is not correct.
Public Const CS_E_INVALID_PATH = (&H8004016B)
'A network error interrupted the operation.
Public Const CS_E_NETWORK_ERROR = (&H8004016C)
'The size of this object exceeds the maximum size set by the Administrator.
Public Const CS_E_ADMIN_LIMIT_EXCEEDED = (&H8004016D)
'The schema for the software installation data in the Active Directory does
'not match the required schema.
Public Const CS_E_SCHEMA_MISMATCH = (&H8004016E)
'An error occurred in the software installation data in the Active Directory.
Public Const CS_E_INTERNAL_ERROR = (&H8004016F)

Public Const CACHE_E_FIRST = &H80040170
Public Const CACHE_E_LAST = &H8004017F
Public Const CACHE_S_FIRST = &H40170
Public Const CACHE_S_LAST = &H4017F


'Cache not updated
Public Const CACHE_E_NOCACHE_UPDATED = (&H80040170)

Public Const OLEOBJ_E_FIRST = &H80040180
Public Const OLEOBJ_E_LAST = &H8004018F
Public Const OLEOBJ_S_FIRST = &H40180
Public Const OLEOBJ_S_LAST = &H4018F


'No verbs for OLE object
Public Const OLEOBJ_E_NOVERBS = (&H80040180)
'Invalid verb for OLE object
Public Const OLEOBJ_E_INVALIDVERB = (&H80040181)

Public Const CLIENTSITE_E_FIRST = &H80040190
Public Const CLIENTSITE_E_LAST = &H8004019F
Public Const CLIENTSITE_S_FIRST = &H40190
Public Const CLIENTSITE_S_LAST = &H4019F


'Undo is not available
Public Const INPLACE_E_NOTUNDOABLE = (&H800401A0)
'Space for tools is not available
Public Const INPLACE_E_NOTOOLSPACE = (&H800401A1)

Public Const INPLACE_E_FIRST = &H800401A0
Public Const INPLACE_E_LAST = &H800401AF
Public Const INPLACE_S_FIRST = &H401A0
Public Const INPLACE_S_LAST = &H401AF
Public Const ENUM_E_FIRST = &H800401B0
Public Const ENUM_E_LAST = &H800401BF
Public Const ENUM_S_FIRST = &H401B0
Public Const ENUM_S_LAST = &H401BF
Public Const CONVERT10_E_FIRST = &H800401C0
Public Const CONVERT10_E_LAST = &H800401CF
Public Const CONVERT10_S_FIRST = &H401C0
Public Const CONVERT10_S_LAST = &H401CF


'OLESTREAM Get method failed
Public Const CONVERT10_E_OLESTREAM_GET = (&H800401C0)
'OLESTREAM Put method failed
Public Const CONVERT10_E_OLESTREAM_PUT = (&H800401C1)
'Contents of the OLESTREAM not in correct format
Public Const CONVERT10_E_OLESTREAM_FMT = (&H800401C2)
'There was an error in a Windows GDI call while converting the bitmap to a DIB
Public Const CONVERT10_E_OLESTREAM_BITMAP_TO_DIB = (&H800401C3)
'Contents of the IStorage not in correct format
Public Const CONVERT10_E_STG_FMT = (&H800401C4)
'Contents of IStorage is missing one of the standard streams
Public Const CONVERT10_E_STG_NO_STD_STREAM = (&H800401C5)
'There was an error in a Windows GDI call while converting the DIB to a bitmap.
'
Public Const CONVERT10_E_STG_DIB_TO_BITMAP = (&H800401C6)

Public Const CLIPBRD_E_FIRST = &H800401D0
Public Const CLIPBRD_E_LAST = &H800401DF
Public Const CLIPBRD_S_FIRST = &H401D0
Public Const CLIPBRD_S_LAST = &H401DF


'OpenClipboard Failed
Public Const CLIPBRD_E_CANT_OPEN = (&H800401D0)
'EmptyClipboard Failed
Public Const CLIPBRD_E_CANT_EMPTY = (&H800401D1)
'SetClipboard Failed
Public Const CLIPBRD_E_CANT_SET = (&H800401D2)
'Data on clipboard is invalid
Public Const CLIPBRD_E_BAD_DATA = (&H800401D3)
'CloseClipboard Failed
Public Const CLIPBRD_E_CANT_CLOSE = (&H800401D4)

Public Const MK_E_FIRST = &H800401E0
Public Const MK_E_LAST = &H800401EF
Public Const MK_S_FIRST = &H401E0
Public Const MK_S_LAST = &H401EF


'Moniker needs to be connected manually
Public Const MK_E_CONNECTMANUALLY = (&H800401E0)
'Operation exceeded deadline
Public Const MK_E_EXCEEDEDDEADLINE = (&H800401E1)
'Moniker needs to be generic
Public Const MK_E_NEEDGENERIC = (&H800401E2)
'Operation unavailable
Public Const MK_E_UNAVAILABLE = (&H800401E3)
'Invalid syntax
Public Const MK_E_SYNTAX = (&H800401E4)
'No object for moniker
Public Const MK_E_NOOBJECT = (&H800401E5)
'Bad extension for file
Public Const MK_E_INVALIDEXTENSION = (&H800401E6)
'Intermediate operation failed
Public Const MK_E_INTERMEDIATEINTERFACENOTSUPPORTED = (&H800401E7)
'Moniker is not bindable
Public Const MK_E_NOTBINDABLE = (&H800401E8)
'Moniker is not bound
Public Const MK_E_NOTBOUND = (&H800401E9)
'Moniker cannot open file
Public Const MK_E_CANTOPENFILE = (&H800401EA)
'User input required for operation to succeed
Public Const MK_E_MUSTBOTHERUSER = (&H800401EB)
'Moniker class has no inverse
Public Const MK_E_NOINVERSE = (&H800401EC)
'Moniker does not refer to storage
Public Const MK_E_NOSTORAGE = (&H800401ED)
'No common prefix
Public Const MK_E_NOPREFIX = (&H800401EE)
'Moniker could not be enumerated
Public Const MK_E_ENUMERATION_FAILED = (&H800401EF)

Public Const CO_E_FIRST = &H800401F0
Public Const CO_E_LAST = &H800401FF
Public Const CO_S_FIRST = &H401F0
Public Const CO_S_LAST = &H401FF


'CoInitialize has not been called.
Public Const CO_E_NOTINITIALIZED = (&H800401F0)
'CoInitialize has already been called.
Public Const CO_E_ALREADYINITIALIZED = (&H800401F1)
'Class of object cannot be determined
Public Const CO_E_CANTDETERMINECLASS = (&H800401F2)
'Invalid class string
Public Const CO_E_CLASSSTRING = (&H800401F3)
'Invalid interface string
Public Const CO_E_IIDSTRING = (&H800401F4)
'Application not found
Public Const CO_E_APPNOTFOUND = (&H800401F5)
'Application cannot be run more than once
Public Const CO_E_APPSINGLEUSE = (&H800401F6)
'Some error in application program
Public Const CO_E_ERRORINAPP = (&H800401F7)
'DLL for class not found
Public Const CO_E_DLLNOTFOUND = (&H800401F8)
'Error in the DLL
Public Const CO_E_ERRORINDLL = (&H800401F9)
'Wrong OS or OS version for application
Public Const CO_E_WRONGOSFORAPP = (&H800401FA)
'Object is not registered
Public Const CO_E_OBJNOTREG = (&H800401FB)
'Object is already registered
Public Const CO_E_OBJISREG = (&H800401FC)
'Object is not connected to server
Public Const CO_E_OBJNOTCONNECTED = (&H800401FD)
'Application was launched but it didn't register a class factory
Public Const CO_E_APPDIDNTREG = (&H800401FE)
'Object has been released
Public Const CO_E_RELEASED = (&H800401FF)

Public Const EVENT_E_FIRST = &H80040200
Public Const EVENT_E_LAST = &H8004021F
Public Const EVENT_S_FIRST = &H40200
Public Const EVENT_S_LAST = &H4021F


'An event was able to invoke some but not all of the subscribers
Public Const EVENT_S_SOME_SUBSCRIBERS_FAILED = (&H40200)
'An event was unable to invoke any of the subscribers
Public Const EVENT_E_ALL_SUBSCRIBERS_FAILED = (&H80040201)
'An event was delivered but there were no subscribers
Public Const EVENT_S_NOSUBSCRIBERS = (&H40202)
'A syntax error occurred trying to evaluate a query string
Public Const EVENT_E_QUERYSYNTAX = (&H80040203)
'An invalid field name was used in a query string
Public Const EVENT_E_QUERYFIELD = (&H80040204)
'An unexpected exception was raised
Public Const EVENT_E_INTERNALEXCEPTION = (&H80040205)
'An unexpected internal error was detected
Public Const EVENT_E_INTERNALERROR = (&H80040206)
'The owner SID on a per-user subscription doesn't exist
Public Const EVENT_E_INVALID_PER_USER_SID = (&H80040207)
'A user-supplied component or subscriber raised an exception
Public Const EVENT_E_USER_EXCEPTION = (&H80040208)
'An interface has too many methods to fire events from
Public Const EVENT_E_TOO_MANY_METHODS = (&H80040209)
'A subscription cannot be stored unless its event class already exists
Public Const EVENT_E_MISSING_EVENTCLASS = (&H8004020A)
'Not all the objects requested could be removed
Public Const EVENT_E_NOT_ALL_REMOVED = (&H8004020B)
'COM+ is required for this operation, but is not installed
Public Const EVENT_E_COMPLUS_NOT_INSTALLED = (&H8004020C)
'Cannot modify or delete an object that was not added using the COM+ Admin SDK
Public Const EVENT_E_CANT_MODIFY_OR_DELETE_UNCONFIGURED_OBJECT = (&H8004020D)
'Cannot modify or delete an object that was added using the COM+ Admin SDK
Public Const EVENT_E_CANT_MODIFY_OR_DELETE_CONFIGURED_OBJECT = (&H8004020E)
'The event class for this subscription is in an invalid partition
Public Const EVENT_E_INVALID_EVENT_CLASS_PARTITION = (&H8004020F)
'The owner of the PerUser subscription is not logged on to the system specified
Public Const EVENT_E_PER_USER_SID_NOT_LOGGED_ON = (&H80040210)

Public Const XACT_E_FIRST = &H8004D000
Public Const XACT_E_LAST = &H8004D029
Public Const XACT_S_FIRST = &H4D000
Public Const XACT_S_LAST = &H4D010


'Another single phase resource manager has already been enlisted in this
'transaction.
Public Const XACT_E_ALREADYOTHERSINGLEPHASE = (&H8004D000)
'A retaining commit or abort is not supported
Public Const XACT_E_CANTRETAIN = (&H8004D001)
'The transaction failed to commit for an unknown reason. The transaction was aborted.
Public Const XACT_E_COMMITFAILED = (&H8004D002)
'Cannot call commit on this transaction object because the calling application
'did not initiate the transaction.
Public Const XACT_E_COMMITPREVENTED = (&H8004D003)
'Instead of committing, the resource heuristically aborted.
Public Const XACT_E_HEURISTICABORT = (&H8004D004)
'Instead of aborting, the resource heuristically committed.
Public Const XACT_E_HEURISTICCOMMIT = (&H8004D005)
'Some of the states of the resource were committed while others were aborted,
'likely because of heuristic decisions.
Public Const XACT_E_HEURISTICDAMAGE = (&H8004D006)
'Some of the states of the resource may have been committed while others may
'have been aborted, likely because of heuristic decisions.
Public Const XACT_E_HEURISTICDANGER = (&H8004D007)
'The requested isolation level is not valid or supported.
Public Const XACT_E_ISOLATIONLEVEL = (&H8004D008)
'The transaction manager doesn't support an asynchronous operation for this
' method.
Public Const XACT_E_NOASYNC = (&H8004D009)
'Unable to enlist in the transaction.
Public Const XACT_E_NOENLIST = (&H8004D00A)
'The requested semantics of retention of isolation across retaining commit
'and abort boundaries cannot be supported by this transaction implementation,
'or isoFlags was not equal to zero.
Public Const XACT_E_NOISORETAIN = (&H8004D00B)
'There is no resource presently associated with this enlistment
Public Const XACT_E_NORESOURCE = (&H8004D00C)
'The transaction failed to commit due to the failure of optimistic concurrency
'control in at least one of the resource managers.
Public Const XACT_E_NOTCURRENT = (&H8004D00D)
'The transaction has already been implicitly or explicitly committed or aborted
Public Const XACT_E_NOTRANSACTION = (&H8004D00E)
'An invalid combination of flags was specified
Public Const XACT_E_NOTSUPPORTED = (&H8004D00F)
'The resource manager id is not associated with this transaction or
'the transaction manager.
Public Const XACT_E_UNKNOWNRMGRID = (&H8004D010)
'This method was called in the wrong state
Public Const XACT_E_WRONGSTATE = (&H8004D011)
'The indicated unit of work does not match the unit of work expected by
'the resource manager.
Public Const XACT_E_WRONGUOW = (&H8004D012)
'An enlistment in a transaction already exists.
Public Const XACT_E_XTIONEXISTS = (&H8004D013)
'An import object for the transaction could not be found.
Public Const XACT_E_NOIMPORTOBJECT = (&H8004D014)
'The transaction cookie is invalid.
Public Const XACT_E_INVALIDCOOKIE = (&H8004D015)
'The transaction status is in doubt. A communication failure occurred,
'or a transaction manager or resource manager has failed
Public Const XACT_E_INDOUBT = (&H8004D016)
'A time-out was specified, but time-outs are not supported.
Public Const XACT_E_NOTIMEOUT = (&H8004D017)
'The requested operation is already in progress for the transaction.
Public Const XACT_E_ALREADYINPROGRESS = (&H8004D018)
'The transaction has already been aborted.
Public Const XACT_E_ABORTED = (&H8004D019)
'The Transaction Manager returned a log full error.
Public Const XACT_E_LOGFULL = (&H8004D01A)
'The Transaction Manager is not available.
Public Const XACT_E_TMNOTAVAILABLE = (&H8004D01B)
'A connection with the transaction manager was lost.
Public Const XACT_E_CONNECTION_DOWN = (&H8004D01C)
'A request to establish a connection with the transaction manager was denied.
Public Const XACT_E_CONNECTION_DENIED = (&H8004D01D)
'Resource manager reenlistment to determine transaction status timed out.
Public Const XACT_E_REENLISTTIMEOUT = (&H8004D01E)
'This transaction manager failed to establish a connection with another
'TIP transaction manager.
Public Const XACT_E_TIP_CONNECT_FAILED = (&H8004D01F)
'This transaction manager encountered a protocol error with another
'TIP transaction manager.
Public Const XACT_E_TIP_PROTOCOL_ERROR = (&H8004D020)
'This transaction manager could not propagate a transaction from another
'TIP transaction manager.
Public Const XACT_E_TIP_PULL_FAILED = (&H8004D021)
'The Transaction Manager on the destination machine is not available.
Public Const XACT_E_DEST_TMNOTAVAILABLE = (&H8004D022)
'The Transaction Manager has disabled its support for TIP.
Public Const XACT_E_TIP_DISABLED = (&H8004D023)
'The transaction manager has disabled its support for remote/network transactions.
Public Const XACT_E_NETWORK_TX_DISABLED = (&H8004D024)
'The partner transaction manager has disabled its support for remote/network transactions.
Public Const XACT_E_PARTNER_NETWORK_TX_DISABLED = (&H8004D025)
'The transaction manager has disabled its support for XA transactions.
Public Const XACT_E_XA_TX_DISABLED = (&H8004D026)
'MSDTC was unable to read its configuration information.
Public Const XACT_E_UNABLE_TO_READ_DTC_CONFIG = (&H8004D027)
'MSDTC was unable to load the dtc proxy dll.
Public Const XACT_E_UNABLE_TO_LOAD_DTC_PROXY = (&H8004D028)
'The local transaction has aborted.
Public Const XACT_E_ABORTING = (&H8004D029)

'TXF & CRM errors start 4d080.


'XACT_E_CLERKNOTFOUND
Public Const XACT_E_CLERKNOTFOUND = (&H8004D080)
'XACT_E_CLERKEXISTS
Public Const XACT_E_CLERKEXISTS = (&H8004D081)
'XACT_E_RECOVERYINPROGRESS
Public Const XACT_E_RECOVERYINPROGRESS = (&H8004D082)
'XACT_E_TRANSACTIONCLOSED
Public Const XACT_E_TRANSACTIONCLOSED = (&H8004D083)
'XACT_E_INVALIDLSN
Public Const XACT_E_INVALIDLSN = (&H8004D084)
'XACT_E_REPLAYREQUEST
Public Const XACT_E_REPLAYREQUEST = (&H8004D085)

'OleTx Success codes.


'An asynchronous operation was specified. The operation has begun, but
'its outcome is not known yet.
Public Const XACT_S_ASYNC = (&H4D000)
'XACT_S_DEFECT
Public Const XACT_S_DEFECT = (&H4D001)
'The method call succeeded because the transaction was read-only.
Public Const XACT_S_READONLY = (&H4D002)
'The transaction was successfully aborted. However, this is a coordinated
'transaction, and some number of enlisted resources were aborted outright
'because they could not support abort-retaining semantics
Public Const XACT_S_SOMENORETAIN = (&H4D003)
'No changes were made during this call, but the sink wants another chance
'to look if any other sinks make further changes.
Public Const XACT_S_OKINFORM = (&H4D004)
'The sink is content and wishes the transaction to proceed. Changes were made
'to one or more resources during this call.
Public Const XACT_S_MADECHANGESCONTENT = (&H4D005)
'The sink is for the moment and wishes the transaction to proceed, but if other
'changes are made following this return by other event sinks then this sink
'wants another chance to look
Public Const XACT_S_MADECHANGESINFORM = (&H4D006)
'The transaction was successfully aborted. However, the abort was non-retaining.
Public Const XACT_S_ALLNORETAIN = (&H4D007)
'An abort operation was already in progress.
Public Const XACT_S_ABORTING = (&H4D008)
'The resource manager has performed a single-phase commit of the transaction.
Public Const XACT_S_SINGLEPHASE = (&H4D009)
'The local transaction has not aborted.
Public Const XACT_S_LOCALLY_OK = (&H4D00A)
'The resource manager has requested to be the coordinator (last resource manager)
'for the transaction.
Public Const XACT_S_LASTRESOURCEMANAGER = (&H4D010)

Public Const CONTEXT_E_FIRST = &H8004E000
Public Const CONTEXT_E_LAST = &H8004E02F
Public Const CONTEXT_S_FIRST = &H4E000
Public Const CONTEXT_S_LAST = &H4E02F


'The root transaction wanted to commit, but transaction aborted
Public Const CONTEXT_E_ABORTED = (&H8004E002)
'You made a method call on a COM+ component that has a transaction that has
'already aborted or in the process of aborting.
Public Const CONTEXT_E_ABORTING = (&H8004E003)
'There is no MTS object context
Public Const CONTEXT_E_NOCONTEXT = (&H8004E004)
'The component is configured to use synchronization and this method call
'would cause a deadlock to occur.
Public Const CONTEXT_E_WOULD_DEADLOCK = (&H8004E005)
'The component is configured to use synchronization and a thread has timed
'out waiting to enter the context.
Public Const CONTEXT_E_SYNCH_TIMEOUT = (&H8004E006)
'You made a method call on a COM+ component that has a transaction that has
'already committed or aborted.
Public Const CONTEXT_E_OLDREF = (&H8004E007)
'The specified role was not configured for the application
Public Const CONTEXT_E_ROLENOTFOUND = (&H8004E00C)
'COM+ was unable to talk to the Microsoft Distributed Transaction Coordinator
Public Const CONTEXT_E_TMNOTAVAILABLE = (&H8004E00F)
'An unexpected error occurred during COM+ Activation.
Public Const CO_E_ACTIVATIONFAILED = (&H8004E021)
'COM+ Activation failed. Check the event log for more information
Public Const CO_E_ACTIVATIONFAILED_EVENTLOGGED = (&H8004E022)
'COM+ Activation failed due to a catalog or configuration error.
Public Const CO_E_ACTIVATIONFAILED_CATALOGERROR = (&H8004E023)
'COM+ activation failed because the activation could not be completed in
'the specified amount of time.
Public Const CO_E_ACTIVATIONFAILED_TIMEOUT = (&H8004E024)
'COM+ Activation failed because an initialization function failed. Check
'the event log for more information.
Public Const CO_E_INITIALIZATIONFAILED = (&H8004E025)
'The requested operation requires that JIT be in the current context and it
'is not
Public Const CONTEXT_E_NOJIT = (&H8004E026)
'The requested operation requires that the current context have a Transaction,
'and it does not
Public Const CONTEXT_E_NOTRANSACTION = (&H8004E027)
'The components threading model has changed after install
'into a COM+ Application. Please re-install component.
Public Const CO_E_THREADINGMODEL_CHANGED = (&H8004E028)
'IIS intrinsics not available. Start your work with IIS.
Public Const CO_E_NOIISINTRINSICS = (&H8004E029)
'An attempt to write a cookie failed.
Public Const CO_E_NOCOOKIES = (&H8004E02A)
'An attempt to use a database generated a database specific error.
Public Const CO_E_DBERROR = (&H8004E02B)
'The COM+ component you created must use object pooling to work.
Public Const CO_E_NOTPOOLED = (&H8004E02C)
'The COM+ component you created must use object construction to work correctly.
Public Const CO_E_NOTCONSTRUCTED = (&H8004E02D)
'The COM+ component requires synchronization, and it is not configured for it.
Public Const CO_E_NOSYNCHRONIZATION = (&H8004E02E)
'The TxIsolation Level property for the COM+ component being created is stronger
'than the TxIsolationLevel for the "root" component for the transaction.
'The creation failed.
Public Const CO_E_ISOLEVELMISMATCH = (&H8004E02F)

'Old OLE Success Codes


'Use the registry database to provide the requested information
Public Const OLE_S_USEREG = (&H40000)
'Success, but static
Public Const OLE_S_STATIC = (&H40001)
'Macintosh clipboard format
Public Const OLE_S_MAC_CLIPFORMAT = (&H40002)
'Successful drop took place
Public Const DRAGDROP_S_DROP = (&H40100)
'Drag-drop operation canceled
Public Const DRAGDROP_S_CANCEL = (&H40101)
'Use the default cursor
Public Const DRAGDROP_S_USEDEFAULTCURSORS = (&H40102)
'Data has same FORMATETC
Public Const DATA_S_SAMEFORMATETC = (&H40130)
'View is already frozen
Public Const VIEW_S_ALREADY_FROZEN = (&H40140)
'FORMATETC not supported
Public Const CACHE_S_FORMATETC_NOTSUPPORTED = (&H40170)
'Same cache
Public Const CACHE_S_SAMECACHE = (&H40171)
'Some cache(s) not updated
Public Const CACHE_S_SOMECACHES_NOTUPDATED = (&H40172)
'Invalid verb for OLE object
Public Const OLEOBJ_S_INVALIDVERB = (&H40180)
'Verb number is valid but verb cannot be done now
Public Const OLEOBJ_S_CANNOT_DOVERB_NOW = (&H40181)
'Invalid window handle passed
Public Const OLEOBJ_S_INVALIDHWND = (&H40182)
'Message is too long; some of it had to be truncated before displaying
Public Const INPLACE_S_TRUNCATED = (&H401A0)
'Unable to convert OLESTREAM to IStorage
Public Const CONVERT10_S_NO_PRESENTATION = (&H401C0)
'Moniker reduced to itself
Public Const MK_S_REDUCED_TO_SELF = (&H401E2)
'Common prefix is this moniker
Public Const MK_S_ME = (&H401E4)
'Common prefix is input moniker
Public Const MK_S_HIM = (&H401E5)
'Common prefix is both monikers
Public Const MK_S_US = (&H401E6)
'Moniker is already registered in running object table
Public Const MK_S_MONIKERALREADYREGISTERED = (&H401E7)

'Task Scheduler errors


'The task is ready to run at its next scheduled time.
Public Const SCHED_S_TASK_READY = (&H41300)
'The task is currently running.
Public Const SCHED_S_TASK_RUNNING = (&H41301)
'The task will not run at the scheduled times because it has been disabled.
Public Const SCHED_S_TASK_DISABLED = (&H41302)
'The task has not yet run.
Public Const SCHED_S_TASK_HAS_NOT_RUN = (&H41303)
'There are no more runs scheduled for this task.
Public Const SCHED_S_TASK_NO_MORE_RUNS = (&H41304)
'One or more of the properties that are needed to run this task on a schedule
'have not been set.
Public Const SCHED_S_TASK_NOT_SCHEDULED = (&H41305)
'The last run of the task was terminated by the user.
Public Const SCHED_S_TASK_TERMINATED = (&H41306)
'Either the task has no triggers or the existing triggers are disabled or not set.
Public Const SCHED_S_TASK_NO_VALID_TRIGGERS = (&H41307)
'Event triggers don't have set run times.
Public Const SCHED_S_EVENT_TRIGGER = (&H41308)
'Trigger not found.
Public Const SCHED_E_TRIGGER_NOT_FOUND = (&H80041309)
'One or more of the properties that are needed to run this task have not been set.
Public Const SCHED_E_TASK_NOT_READY = (&H8004130A)
'There is no running instance of the task to terminate.
Public Const SCHED_E_TASK_NOT_RUNNING = (&H8004130B)
'The Task Scheduler Service is not installed on this computer.
Public Const SCHED_E_SERVICE_NOT_INSTALLED = (&H8004130C)
'The task object could not be opened.
Public Const SCHED_E_CANNOT_OPEN_TASK = (&H8004130D)
'The object is either an invalid task object or is not a task object.
Public Const SCHED_E_INVALID_TASK = (&H8004130E)
'No account information could be found in the Task Scheduler security database
'for the task indicated.
Public Const SCHED_E_ACCOUNT_INFORMATION_NOT_SET = (&H8004130F)
'Unable to establish existence of the account specified.
Public Const SCHED_E_ACCOUNT_NAME_NOT_FOUND = (&H80041310)
'Corruption was detected in the Task Scheduler security database; the database
'has been reset.
Public Const SCHED_E_ACCOUNT_DBASE_CORRUPT = (&H80041311)
'Task Scheduler security services are available only on Windows NT.
Public Const SCHED_E_NO_SECURITY_SERVICES = (&H80041312)
'The task object version is either unsupported or invalid.
Public Const SCHED_E_UNKNOWN_OBJECT_VERSION = (&H80041313)
'The task has been configured with an unsupported combination of account
'settings and run time options.
Public Const SCHED_E_UNSUPPORTED_ACCOUNT_OPTION = (&H80041314)
'The Task Scheduler Service is not running.
Public Const SCHED_E_SERVICE_NOT_RUNNING = (&H80041315)

'******************
'FACILITY_WINDOWS
'******************
'Codes &H0-&H01ff are reserved for the OLE group of
'interfaces.


'Attempt to create a class object failed
Public Const CO_E_CLASS_CREATE_FAILED = (&H80080001)
'OLE service could not bind object
Public Const CO_E_SCM_ERROR = (&H80080002)
'RPC communication failed with OLE service
Public Const CO_E_SCM_RPC_FAILURE = (&H80080003)
'Bad path to object
Public Const CO_E_BAD_PATH = (&H80080004)
'Server execution failed
Public Const CO_E_SERVER_EXEC_FAILURE = (&H80080005)
'OLE service could not communicate with the object server
Public Const CO_E_OBJSRV_RPC_FAILURE = (&H80080006)
'Moniker path could not be normalized
Public Const MK_E_NO_NORMALIZED = (&H80080007)
'Object server is stopping when OLE service contacts it
Public Const CO_E_SERVER_STOPPING = (&H80080008)
'An invalid root block pointer was specified
Public Const MEM_E_INVALID_ROOT = (&H80080009)
'An allocation chain contained an invalid link pointer
Public Const MEM_E_INVALID_LINK = (&H80080010)
'The requested allocation size was too large
Public Const MEM_E_INVALID_SIZE = (&H80080011)
'Not all the requested interfaces were available
Public Const CO_S_NOTALLINTERFACES = (&H80012)
'The specified machine name was not found in the cache.
Public Const CO_S_MACHINENAMENOTFOUND = (&H80013)

'******************
'FACILITY_DISPATCH
'******************


'Unknown interface.
Public Const DISP_E_UNKNOWNINTERFACE = (&H80020001)
'Member not found.
Public Const DISP_E_MEMBERNOTFOUND = (&H80020003)
'Parameter not found.
Public Const DISP_E_PARAMNOTFOUND = (&H80020004)
'Type mismatch.
Public Const DISP_E_TYPEMISMATCH = (&H80020005)
'Unknown name.
Public Const DISP_E_UNKNOWNNAME = (&H80020006)
'No named arguments.
Public Const DISP_E_NONAMEDARGS = (&H80020007)
'Bad variable type.
Public Const DISP_E_BADVARTYPE = (&H80020008)
'Exception occurred.
Public Const DISP_E_EXCEPTION = (&H80020009)
'Out of present range.
Public Const DISP_E_OVERFOW = (&H8002000A)
'Invalid index.
Public Const DISP_E_BADINDEX = (&H8002000B)
'Unknown language.
Public Const DISP_E_UNKNOWNLCID = (&H8002000C)
'Memory is locked.
Public Const DISP_E_ARRAYISLOCKED = (&H8002000D)
'Invalid number of parameters.
Public Const DISP_E_BADPARAMCOUNT = (&H8002000E)
'Parameter not optional.
Public Const DISP_E_PARAMNOTOPTIONAL = (&H8002000F)
'Invalid callee.
Public Const DISP_E_BADCALLEE = (&H80020010)
'Does not support a collection.
Public Const DISP_E_NOTACOLLECTION = (&H80020011)
'Division by zero.
Public Const DISP_E_DIVBYZERO = (&H80020012)
'Buffer too small
Public Const DISP_E_BUFFERTOOSMALL = (&H80020013)
'Buffer too small.
Public Const TYPE_E_BUFFERTOOSMALL = (&H80028016)
'Field name not defined in the record.
Public Const TYPE_E_FIELDNOTFOUND = (&H80028017)
'Old format or invalid type library.
Public Const TYPE_E_INVDATAREAD = (&H80028018)
'Old format or invalid type library.
Public Const TYPE_E_UNSUPFORMAT = (&H80028019)
'Error accessing the OLE registry.
Public Const TYPE_E_REGISTRYACCESS = (&H8002801C)
'Library not registered.
Public Const TYPE_E_LIBNOTREGISTERED = (&H8002801D)
'Bound to unknown type.
Public Const TYPE_E_UNDEFINEDTYPE = (&H80028027)
'Qualified name disallowed.
Public Const TYPE_E_QUALIFIEDNAMEDISALLOWED = (&H80028028)
'Invalid forward reference, or reference to uncompiled type.
Public Const TYPE_E_INVALIDSTATE = (&H80028029)
'Type mismatch.
Public Const TYPE_E_WRONGTYPEKIND = (&H8002802A)
'Element not found.
Public Const TYPE_E_ELEMENTNOTFOUND = (&H8002802B)
'Ambiguous name.
Public Const TYPE_E_AMBIGUOUSNAME = (&H8002802C)
'Name already exists in the library.
Public Const TYPE_E_NAMECONFICT = (&H8002802D)
'Unknown LCID.
Public Const TYPE_E_UNKNOWNLCID = (&H8002802E)
'Function not defined in specified DLL.
Public Const TYPE_E_DLLFUNCTIONNOTFOUND = (&H8002802F)
'Wrong module kind for the operation.
Public Const TYPE_E_BADMODULEKIND = (&H800288BD)
'Size may not exceed 64K.
Public Const TYPE_E_SIZETOOBIG = (&H800288C5)
'Duplicate ID in inheritance hierarchy.
Public Const TYPE_E_DUPLICATEID = (&H800288C6)
'Incorrect inheritance depth in standard OLE hmember.
Public Const TYPE_E_INVALIDID = (&H800288CF)
'Type mismatch.
Public Const TYPE_E_TYPEMISMATCH = (&H80028CA0)
'Invalid number of arguments.
Public Const TYPE_E_OUTOFBOUNDS = (&H80028CA1)
'I/O Error.
Public Const TYPE_E_IOERROR = (&H80028CA2)
'Error creating unique tmp file.
Public Const TYPE_E_CANTCREATETMPFILE = (&H80028CA3)
'Error loading type library/DLL.
Public Const TYPE_E_CANTLOADLIBRARY = (&H80029C4A)
'Inconsistent property functions.
Public Const TYPE_E_INCONSISTENTPROPFUNCS = (&H80029C83)
'Circular dependency between types/modules.
Public Const TYPE_E_CIRCULARTYPE = (&H80029C84)

'******************
'FACILITY_STORAGE
'******************


'Unable to perform requested operation.
Public Const STG_E_INVALIDFUNCTION = (&H80030001)
'%1 could not be found.
Public Const STG_E_FILENOTFOUND = (&H80030002)
'The path %1 could not be found.
Public Const STG_E_PATHNOTFOUND = (&H80030003)
'There are insufficient resources to open another file.
Public Const STG_E_TOOMANYOPENFILES = (&H80030004)
'Access Denied.
Public Const STG_E_ACCESSDENIED = (&H80030005)
'Attempted an operation on an invalid object.
Public Const STG_E_INVALIDHANDLE = (&H80030006)
'There is insufficient memory available to complete operation.
Public Const STG_E_INSUFFICIENTMEMORY = (&H80030008)
'Invalid pointer error.
Public Const STG_E_INVALIDPOINTER = (&H80030009)
'There are no more entries to return.
Public Const STG_E_NOMOREFILES = (&H80030012)
'Disk is write-protected.
Public Const STG_E_DISKISWRITEPROTECTED = (&H80030013)
'An error occurred during a seek operation.
Public Const STG_E_SEEKERROR = (&H80030019)
'A disk error occurred during a write operation.
Public Const STG_E_WRITEFAULT = (&H8003001D)
'A disk error occurred during a read operation.
Public Const STG_E_READFAULT = (&H8003001E)
'A share violation has occurred.
Public Const STG_E_SHAREVIOLATION = (&H80030020)
'A lock violation has occurred.
Public Const STG_E_LOCKVIOLATION = (&H80030021)
'%1 already exists.
Public Const STG_E_FILEALREADYEXISTS = (&H80030050)
'Invalid parameter error.
Public Const STG_E_INVALIDPARAMETER = (&H80030057)
'There is insufficient disk space to complete operation.
Public Const STG_E_MEDIUMFULL = (&H80030070)
'Illegal write of non-simple property to simple property set.
Public Const STG_E_PROPSETMISMATCHED = (&H800300F0)
'An API call exited abnormally.
Public Const STG_E_ABNORMALAPIEXIT = (&H800300FA)
'The file %1 is not a valid compound file.
Public Const STG_E_INVALIDHEADER = (&H800300FB)
'The name %1 is not valid.
Public Const STG_E_INVALIDNAME = (&H800300FC)
'An unexpected error occurred.
Public Const STG_E_UNKNOWN = (&H800300FD)
'That function is not implemented.
Public Const STG_E_UNIMPLEMENTEDFUNCTION = (&H800300FE)
'Invalid flag error.
Public Const STG_E_INVALIDFAG = (&H800300FF)
'Attempted to use an object that is busy.
Public Const STG_E_INUSE = (&H80030100)
'The storage has been changed since the last commit.
Public Const STG_E_NOTCURRENT = (&H80030101)
'Attempted to use an object that has ceased to exist.
Public Const STG_E_REVERTED = (&H80030102)
'Can't save.
Public Const STG_E_CANTSAVE = (&H80030103)
'The compound file %1 was produced with an incompatible version of storage.
Public Const STG_E_OLDFORMAT = (&H80030104)
'The compound file %1 was produced with a newer version of storage.
Public Const STG_E_OLDDLL = (&H80030105)
'Share.exe or equivalent is required for operation.
Public Const STG_E_SHAREREQUIRED = (&H80030106)
'Illegal operation called on non-file based storage.
Public Const STG_E_NOTFILEBASEDSTORAGE = (&H80030107)
'Illegal operation called on object with extant marshallings.
Public Const STG_E_EXTANTMARSHALLINGS = (&H80030108)
'The docfile has been corrupted.
Public Const STG_E_DOCFILECORRUPT = (&H80030109)
'OLE32.DLL has been loaded at the wrong address.
Public Const STG_E_BADBASEADDRESS = (&H80030110)
'The compound file is too large for the current implementation
Public Const STG_E_DOCFILETOOLARGE = (&H80030111)
'The compound file was not created with the STGM_SIMPLE flag
Public Const STG_E_NOTSIMPLEFORMAT = (&H80030112)
'The file download was aborted abnormally. The file is incomplete.
Public Const STG_E_INCOMPLETE = (&H80030201)
'The file download has been terminated.
Public Const STG_E_TERMINATED = (&H80030202)
'The underlying file was converted to compound file format.
Public Const STG_S_CONVERTED = (&H30200)
'The storage operation should block until more data is available.
Public Const STG_S_BLOCK = (&H30201)
'The storage operation should retry immediately.
Public Const STG_S_RETRYNOW = (&H30202)
'The notified event sink will not influence the storage operation.
Public Const STG_S_MONITORING = (&H30203)
'Multiple opens prevent consolidated. (commit succeeded).
Public Const STG_S_MULTIPLEOPENS = (&H30204)
'Consolidation of the storage file failed. (commit succeeded).
Public Const STG_S_CONSOLIDATIONFAILED = (&H30205)
'Consolidation of the storage file is inappropriate. (commit succeeded).
Public Const STG_S_CANNOTCONSOLIDATE = (&H30206)

'------------------------------------------------------------------------------
'MessageId's &H0305 - &H031f (inclusive) are reserved for **STORAGE**
'copy protection errors.

'Generic Copy Protection Error.
Public Const STG_E_STATUS_COPY_PROTECTION_FAILURE = (&H80030305)
'Copy Protection Error - DVD CSS Authentication failed.
Public Const STG_E_CSS_AUTHENTICATION_FAILURE = (&H80030306)
'Copy Protection Error - The given sector does not have a valid CSS key.
Public Const STG_E_CSS_KEY_NOT_PRESENT = (&H80030307)
'Copy Protection Error - DVD session key not established.
Public Const STG_E_CSS_KEY_NOT_ESTABLISHED = (&H80030308)
'Copy Protection Error - The read failed because the sector is encrypted.
Public Const STG_E_CSS_SCRAMBLED_SECTOR = (&H80030309)
'Copy Protection Error - The current DVD's region does not correspond to
'the region setting of the drive.
Public Const STG_E_CSS_REGION_MISMATCH = (&H8003030A)
'Copy Protection Error - The drive's region setting may be permanent or
'the number of user resets has been exhausted.
Public Const STG_E_RESETS_EXHAUSTED = (&H8003030B)

'******************
'FACILITY_RPC
'******************
'Codes &H0-&H11 are propagated from 16 bit OLE.


'Call was rejected by callee.
Public Const RPC_E_CALL_REJECTED = (&H80010001)
'Call was canceled by the message filter.
Public Const RPC_E_CALL_CANCELED = (&H80010002)
'The caller is dispatching an intertask SendMessage call and cannot call
'out via PostMessage.
Public Const RPC_E_CANTPOST_INSENDCALL = (&H80010003)
'The caller is dispatching an asynchronous call and cannot make an outgoing
'call on behalf of this call.
Public Const RPC_E_CANTCALLOUT_INASYNCCALL = (&H80010004)
'It is illegal to call out while inside message filter.
Public Const RPC_E_CANTCALLOUT_INEXTERNALCALL = (&H80010005)
'The connection terminated or is in a bogus state and cannot be used any more.
'Other connections are still valid.
Public Const RPC_E_CONNECTION_TERMINATED = (&H80010006)
'The callee (server [not server application]) is not available and disappeared;
'all connections are invalid. The call may have executed.
Public Const RPC_E_SERVER_DIED = (&H80010007)
'The caller (client) disappeared while the callee (server) was processing a call.
Public Const RPC_E_CLIENT_DIED = (&H80010008)
'The data packet with the marshalled parameter data is incorrect.
Public Const RPC_E_INVALID_DATAPACKET = (&H80010009)
'The call was not transmitted properly; the message queue was full and was not
'emptied after yielding.
Public Const RPC_E_CANTTRANSMIT_CALL = (&H8001000A)
'The client (caller) cannot marshall the parameter data - low memory, etc.
Public Const RPC_E_CLIENT_CANTMARSHAL_DATA = (&H8001000B)
'The client (caller) cannot unmarshall the return data - low memory, etc.
Public Const RPC_E_CLIENT_CANTUNMARSHAL_DATA = (&H8001000C)
'The server (callee) cannot marshall the return data - low memory, etc.
Public Const RPC_E_SERVER_CANTMARSHAL_DATA = (&H8001000D)
'The server (callee) cannot unmarshall the parameter data - low memory, etc.
Public Const RPC_E_SERVER_CANTUNMARSHAL_DATA = (&H8001000E)
'Received data is invalid; could be server or client data.
Public Const RPC_E_INVALID_DATA = (&H8001000F)
'A particular parameter is invalid and cannot be (un)marshalled.
Public Const RPC_E_INVALID_PARAMETER = (&H80010010)
'There is no second outgoing call on same channel in DDE conversation.
Public Const RPC_E_CANTCALLOUT_AGAIN = (&H80010011)
'The callee (server [not server application]) is not available and disappeared;
'all connections are invalid. The call did not execute.
Public Const RPC_E_SERVER_DIED_DNE = (&H80010012)
'System call failed.
Public Const RPC_E_SYS_CALL_FAILED = (&H80010100)
'Could not allocate some required resource (memory, events, ...)
Public Const RPC_E_OUT_OF_RESOURCES = (&H80010101)
'Attempted to make calls on more than one thread in single threaded mode.
Public Const RPC_E_ATTEMPTED_MULTITHREAD = (&H80010102)
'The requested interface is not registered on the server object.
Public Const RPC_E_NOT_REGISTERED = (&H80010103)
'RPC could not call the server or could not return the results of calling
'the server.
Public Const RPC_E_FAULT = (&H80010104)
'The server threw an exception.
Public Const RPC_E_SERVERFAULT = (&H80010105)
'Cannot change thread mode after it is set.
Public Const RPC_E_CHANGED_MODE = (&H80010106)
'The method called does not exist on the server.
Public Const RPC_E_INVALIDMETHOD = (&H80010107)
'The object invoked has disconnected from its clients.
Public Const RPC_E_DISCONNECTED = (&H80010108)
'The object invoked chose not to process the call now. Try again later.
Public Const RPC_E_RETRY = (&H80010109)
'The message filter indicated that the application is busy.
Public Const RPC_E_SERVERCALL_RETRYLATER = (&H8001010A)
'The message filter rejected the call.
Public Const RPC_E_SERVERCALL_REJECTED = (&H8001010B)
'A call control interfaces was called with invalid data.
Public Const RPC_E_INVALID_CALLDATA = (&H8001010C)
'An outgoing call cannot be made since the application is dispatching an
'input-synchronous call.
Public Const RPC_E_CANTCALLOUT_ININPUTSYNCCALL = (&H8001010D)
'The application called an interface that was marshalled for a different thread.
Public Const RPC_E_WRONG_THREAD = (&H8001010E)
'CoInitialize has not been called on the current thread.
Public Const RPC_E_THREAD_NOT_INIT = (&H8001010F)
'The version of OLE on the client and server machines does not match.
Public Const RPC_E_VERSION_MISMATCH = (&H80010110)
'OLE received a packet with an invalid header.
Public Const RPC_E_INVALID_HEADER = (&H80010111)
'OLE received a packet with an invalid extension.
Public Const RPC_E_INVALID_EXTENSION = (&H80010112)
'The requested object or interface does not exist.
Public Const RPC_E_INVALID_IPID = (&H80010113)
'The requested object does not exist.
Public Const RPC_E_INVALID_OBJECT = (&H80010114)
'OLE has sent a request and is waiting for a reply.
Public Const RPC_S_CALLPENDING = (&H80010115)
'OLE is waiting before retrying a request.
Public Const RPC_S_WAITONTIMER = (&H80010116)
'Call context cannot be accessed after call completed.
Public Const RPC_E_CALL_COMPLETE = (&H80010117)
'Impersonate on unsecure calls is not supported.
Public Const RPC_E_UNSECURE_CALL = (&H80010118)
'Security must be initialized before any interfaces are marshalled or
'unmarshalled. It cannot be changed once initialized.
Public Const RPC_E_TOO_LATE = (&H80010119)
'No security packages are installed on this machine or the user is not
'logged on or there are no compatible security packages between the client
'and server.
Public Const RPC_E_NO_GOOD_SECURITY_PACKAGES = (&H8001011A)
'Access is denied.
Public Const RPC_E_ACCESS_DENIED = (&H8001011B)
'Remote calls are not allowed for this process.
Public Const RPC_E_REMOTE_DISABLED = (&H8001011C)
'The marshaled interface data packet (OBJREF) has an invalid or unknown format.
Public Const RPC_E_INVALID_OBJREF = (&H8001011D)
'No context is associated with this call. This happens for some custom
'marshalled calls and on the client side of the call.
Public Const RPC_E_NO_CONTEXT = (&H8001011E)
'This operation returned because the timeout period expired.
Public Const RPC_E_TIMEOUT = (&H8001011F)
'There are no synchronize objects to wait on.
Public Const RPC_E_NO_SYNC = (&H80010120)
'Full subject issuer chain SSL principal name expected from the server.
Public Const RPC_E_FULLSIC_REQUIRED = (&H80010121)
'Principal name is not a valid MSSTD name.
Public Const RPC_E_INVALID_STD_NAME = (&H80010122)
'Unable to impersonate DCOM client
Public Const CO_E_FAILEDTOIMPERSONATE = (&H80010123)
'Unable to obtain server's security context
Public Const CO_E_FAILEDTOGETSECCTX = (&H80010124)
'Unable to open the access token of the current thread
Public Const CO_E_FAILEDTOOPENTHREADTOKEN = (&H80010125)
'Unable to obtain user info from an access token
Public Const CO_E_FAILEDTOGETTOKENINFO = (&H80010126)
'The client who called IAccessControl::IsAccessPermitted was not the trustee
'provided to the method
Public Const CO_E_TRUSTEEDOESNTMATCHCLIENT = (&H80010127)
'Unable to obtain the client's security blanket
Public Const CO_E_FAILEDTOQUERYCLIENTBLANKET = (&H80010128)
'Unable to set a discretionary ACL into a security descriptor
Public Const CO_E_FAILEDTOSETDACL = (&H80010129)
'The system function, AccessCheck, returned false
Public Const CO_E_ACCESSCHECKFAILED = (&H8001012A)
'Either NetAccessDel or NetAccessAdd returned an error code.
Public Const CO_E_NETACCESSAPIFAILED = (&H8001012B)
'One of the trustee strings provided by the user did not conform to
'the <Domain>\<Name> syntax and it was not the "*" string
Public Const CO_E_WRONGTRUSTEENAMESYNTAX = (&H8001012C)
'One of the security identifiers provided by the user was invalid
Public Const CO_E_INVALIDSID = (&H8001012D)
'Unable to convert a wide character trustee string to a multibyte trustee string
Public Const CO_E_CONVERSIONFAILED = (&H8001012E)
'Unable to find a security identifier that corresponds to a trustee string
'provided by the user
Public Const CO_E_NOMATCHINGSIDFOUND = (&H8001012F)
'The system function, LookupAccountSID, failed
Public Const CO_E_LOOKUPACCSIDFAILED = (&H80010130)
'Unable to find a trustee name that corresponds to a security identifier
'provided by the user
Public Const CO_E_NOMATCHINGNAMEFOUND = (&H80010131)
'The system function, LookupAccountName, failed
Public Const CO_E_LOOKUPACCNAMEFAILED = (&H80010132)
'Unable to set or reset a serialization handle
Public Const CO_E_SETSERLHNDLFAILED = (&H80010133)
'Unable to obtain the Windows directory
Public Const CO_E_FAILEDTOGETWINDIR = (&H80010134)
'Path too long
Public Const CO_E_PATHTOOLONG = (&H80010135)
'Unable to generate a uuid.
Public Const CO_E_FAILEDTOGENUUID = (&H80010136)
'Unable to create file
Public Const CO_E_FAILEDTOCREATEFILE = (&H80010137)
'Unable to close a serialization handle or a file handle.
Public Const CO_E_FAILEDTOCLOSEHANDLE = (&H80010138)
'The number of ACEs in an ACL exceeds the system limit.
Public Const CO_E_EXCEEDSYSACLLIMIT = (&H80010139)
'Not all the DENY_ACCESS ACEs are arranged in front of the GRANT_ACCESS
'ACEs in the stream.
Public Const CO_E_ACESINWRONGORDER = (&H8001013A)
'The version of ACL format in the stream is not supported by this
'implementation of IAccessControl
Public Const CO_E_INCOMPATIBLESTREAMVERSION = (&H8001013B)
'Unable to open the access token of the server process
Public Const CO_E_FAILEDTOOPENPROCESSTOKEN = (&H8001013C)
'Unable to decode the ACL in the stream provided by the user
Public Const CO_E_DECODEFAILED = (&H8001013D)
'The COM IAccessControl object is not initialized
Public Const CO_E_ACNOTINITIALIZED = (&H8001013F)
'Call Cancellation is disabled
Public Const CO_E_CANCEL_DISABLED = (&H80010140)
'An internal error occurred.
Public Const RPC_E_UNEXPECTED = (&H8001FFFF)
'''''''''''''''''''
''Additional Security Status Codes
''
''Facility=Security
''                                ''''''''''''''''''
'The specified event is currently not being audited.
Public Const ERROR_AUDITING_DISABLED = (&HC0090001)
'The SID filtering operation removed all SIDs.
Public Const ERROR_ALL_SIDS_FILTERED = (&HC0090002)
'''''''''''''''''''''
''/
''end of Additional Security Status Codes
''
''''''''''''''''''''''/


 '''''''/  'FACILITY_SSPI
  '''''''/


'Bad UID.
Public Const NTE_BAD_UID = (&H80090001)
'Bad Hash.
Public Const NTE_BAD_HASH = (&H80090002)
'Bad Key.
Public Const NTE_BAD_KEY = (&H80090003)
'Bad Length.
Public Const NTE_BAD_LEN = (&H80090004)
'Bad Data.
Public Const NTE_BAD_DATA = (&H80090005)
'Invalid Signature.
Public Const NTE_BAD_SIGNATURE = (&H80090006)
'Bad Version of provider.
Public Const NTE_BAD_VER = (&H80090007)
'Invalid algorithm specified.
Public Const NTE_BAD_ALGID = (&H80090008)
'Invalid flags specified.
Public Const NTE_BAD_FAGS = (&H80090009)
'Invalid type specified.
Public Const NTE_BAD_TYPE = (&H8009000A)
'Key not valid for use in specified state.
Public Const NTE_BAD_KEY_STATE = (&H8009000B)
'Hash not valid for use in specified state.
Public Const NTE_BAD_HASH_STATE = (&H8009000C)
'Key does not exist.
Public Const NTE_NO_KEY = (&H8009000D)
'Insufficient memory available for the operation.
Public Const NTE_NO_MEMORY = (&H8009000E)
'Object already exists.
Public Const NTE_EXISTS = (&H8009000F)
'Access denied.
Public Const NTE_PERM = (&H80090010)
'Object was not found.
Public Const NTE_NOT_FOUND = (&H80090011)
'Data already encrypted.
Public Const NTE_DOUBLE_ENCRYPT = (&H80090012)
'Invalid provider specified.
Public Const NTE_BAD_PROVIDER = (&H80090013)
'Invalid provider type specified.
Public Const NTE_BAD_PROV_TYPE = (&H80090014)
'Provider's public key is invalid.
Public Const NTE_BAD_PUBLIC_KEY = (&H80090015)
'Keyset does not exist
Public Const NTE_BAD_KEYSET = (&H80090016)
'Provider type not defined.
Public Const NTE_PROV_TYPE_NOT_DEF = (&H80090017)
'Provider type as registered is invalid.
Public Const NTE_PROV_TYPE_ENTRY_BAD = (&H80090018)
'The keyset is not defined.
Public Const NTE_KEYSET_NOT_DEF = (&H80090019)
'Keyset as registered is invalid.
Public Const NTE_KEYSET_ENTRY_BAD = (&H8009001A)
'Provider type does not match registered value.
Public Const NTE_PROV_TYPE_NO_MATCH = (&H8009001B)
'The digital signature file is corrupt.
Public Const NTE_SIGNATURE_FILE_BAD = (&H8009001C)
'Provider DLL failed to initialize correctly.
Public Const NTE_PROVIDER_DLL_FAIL = (&H8009001D)
'Provider DLL could not be found.
Public Const NTE_PROV_DLL_NOT_FOUND = (&H8009001E)
'The Keyset parameter is invalid.
Public Const NTE_BAD_KEYSET_PARAM = (&H8009001F)
'An internal error occurred.
Public Const NTE_FAIL = (&H80090020)
'A base error occurred.
Public Const NTE_SYS_ERR = (&H80090021)
'Provider could not perform the action since the context was acquired as silent.
Public Const NTE_SILENT_CONTEXT = (&H80090022)
'The security token does not have storage space available for an additional container.
Public Const NTE_TOKEN_KEYSET_STORAGE_FULL = (&H80090023)
'The profile for the user is a temporary profile.
Public Const NTE_TEMPORARY_PROFILE = (&H80090024)
'The key parameters could not be set because the CSP uses fixed parameters.
Public Const NTE_FIXEDPARAMETER = (&H80090025)
'Not enough memory is available to complete this request
Public Const SEC_E_INSUFFICIENT_MEMORY = (&H80090300)
'The handle specified is invalid
Public Const SEC_E_INVALID_HANDLE = (&H80090301)
'The function requested is not supported
Public Const SEC_E_UNSUPPORTED_FUNCTION = (&H80090302)
'The specified target is unknown or unreachable
Public Const SEC_E_TARGET_UNKNOWN = (&H80090303)
'The Local Security Authority cannot be contacted
Public Const SEC_E_INTERNAL_ERROR = (&H80090304)
'The requested security package does not exist
Public Const SEC_E_SECPKG_NOT_FOUND = (&H80090305)
'The caller is not the owner of the desired credentials
Public Const SEC_E_NOT_OWNER = (&H80090306)
'The security package failed to initialize, and cannot be installed
Public Const SEC_E_CANNOT_INSTALL = (&H80090307)
'The token supplied to the function is invalid
Public Const SEC_E_INVALID_TOKEN = (&H80090308)
'The security package is not able to marshall the logon buffer, so the logon attempt has failed
Public Const SEC_E_CANNOT_PACK = (&H80090309)
'The per-message Quality of Protection is not supported by the security package
Public Const SEC_E_QOP_NOT_SUPPORTED = (&H8009030A)
'The security context does not allow impersonation of the client
Public Const SEC_E_NO_IMPERSONATION = (&H8009030B)
'The logon attempt failed
Public Const SEC_E_LOGON_DENIED = (&H8009030C)
'The credentials supplied to the package were not recognized
Public Const SEC_E_UNKNOWN_CREDENTIALS = (&H8009030D)
'No credentials are available in the security package
Public Const SEC_E_NO_CREDENTIALS = (&H8009030E)
'The message or signature supplied for verification has been altered
Public Const SEC_E_MESSAGE_ALTERED = (&H8009030F)
'The message supplied for verification is out of sequence
Public Const SEC_E_OUT_OF_SEQUENCE = (&H80090310)
'No authority could be contacted for authentication.
Public Const SEC_E_NO_AUTHENTICATING_AUTHORITY = (&H80090311)
'The function completed successfully, but must be called again to complete the context
Public Const SEC_I_CONTINUE_NEEDED = (&H90312)
'The function completed successfully, but CompleteToken must be called
Public Const SEC_I_COMPLETE_NEEDED = (&H90313)
'The function completed successfully, but both CompleteToken and this function
'must be called to complete the context
Public Const SEC_I_COMPLETE_AND_CONTINUE = (&H90314)
'The logon was completed, but no network authority was available.
'The logon was made using locally known information
Public Const SEC_I_LOCAL_LOGON = (&H90315)
'The requested security package does not exist
Public Const SEC_E_BAD_PKGID = (&H80090316)
'The context has expired and can no longer be used.
Public Const SEC_E_CONTEXT_EXPIRED = (&H80090317)
'The context has expired and can no longer be used.
Public Const SEC_I_CONTEXT_EXPIRED = (&H90317)
'The supplied message is incomplete. The signature was not verified.
Public Const SEC_E_INCOMPLETE_MESSAGE = (&H80090318)
'The credentials supplied were not complete, and could not be verified.
'The context could not be initialized.
Public Const SEC_E_INCOMPLETE_CREDENTIALS = (&H80090320)
'The buffers supplied to a function was too small.
Public Const SEC_E_BUFFER_TOO_SMALL = (&H80090321)
'The credentials supplied were not complete, and could not be verified.
'Additional information can be returned from the context.
Public Const SEC_I_INCOMPLETE_CREDENTIALS = (&H90320)
'The context data must be renegotiated with the peer.
Public Const SEC_I_RENEGOTIATE = (&H90321)
'The target principal name is incorrect.
Public Const SEC_E_WRONG_PRINCIPAL = (&H80090322)
'There is no LSA mode context associated with this context.
Public Const SEC_I_NO_LSA_CONTEXT = (&H90323)
'The clocks on the client and server machines are skewed.
Public Const SEC_E_TIME_SKEW = (&H80090324)
'The certificate chain was issued by an authority that is not trusted.
Public Const SEC_E_UNTRUSTED_ROOT = (&H80090325)
'The message received was unexpected or badly formatted.
Public Const SEC_E_ILLEGAL_MESSAGE = (&H80090326)
'An unknown error occurred while processing the certificate.
Public Const SEC_E_CERT_UNKNOWN = (&H80090327)
'The received certificate has expired.
Public Const SEC_E_CERT_EXPIRED = (&H80090328)
'The specified data could not be encrypted.
Public Const SEC_E_ENCRYPT_FAILURE = (&H80090329)
'The specified data could not be decrypted.
Public Const SEC_E_DECRYPT_FAILURE = (&H80090330)
'The client and server cannot communicate, because they do not possess a
'common algorithm.
Public Const SEC_E_ALGORITHM_MISMATCH = (&H80090331)
'The security context could not be established due to a failure in
'the requested quality of service (e.g. mutual authentication or delegation).
Public Const SEC_E_SECURITY_QOS_FAILED = (&H80090332)
'A security context was deleted before the context was completed.
'This is considered a logon failure.
Public Const SEC_E_UNFINISHED_CONTEXT_DELETED = (&H80090333)
'The client is trying to negotiate a context and the server requires
'user-to-user but didn't send a TGT reply.
Public Const SEC_E_NO_TGT_REPLY = (&H80090334)
'Unable to accomplish the requested task because the local machine
'does not have any IP addresses.
Public Const SEC_E_NO_IP_ADDRESSES = (&H80090335)
'The supplied credential handle does not match the credential
'associated with the security context.
Public Const SEC_E_WRONG_CREDENTIAL_HANDLE = (&H80090336)
'The crypto system or checksum function is invalid because
'a required function is unavailable.
Public Const SEC_E_CRYPTO_SYSTEM_INVALID = (&H80090337)
'The number of maximum ticket referrals has been exceeded.
Public Const SEC_E_MAX_REFERRALS_EXCEEDED = (&H80090338)
'The local machine must be a Kerberos KDC (domain controller) and it is not.
Public Const SEC_E_MUST_BE_KDC = (&H80090339)
'The other end of the security negotiation is requires strong
'crypto but it is not supported on the local machine.
Public Const SEC_E_STRONG_CRYPTO_NOT_SUPPORTED = (&H8009033A)
'The KDC reply contained more than one principal name.
Public Const SEC_E_TOO_MANY_PRINCIPALS = (&H8009033B)
'Expected to find PA data for a hint of what etype to use, but it was not found.
Public Const SEC_E_NO_PA_DATA = (&H8009033C)
'The client certificate does not contain a valid UPN, or does not match
'the client name
'in the logon request. Please contact your administrator.
Public Const SEC_E_PKINIT_NAME_MISMATCH = (&H8009033D)
'Smartcard logon is required and was not used.
Public Const SEC_E_SMARTCARD_LOGON_REQUIRED = (&H8009033E)
'A system shutdown is in progress.
Public Const SEC_E_SHUTDOWN_IN_PROGRESS = (&H8009033F)
'An invalid request was sent to the KDC.
Public Const SEC_E_KDC_INVALID_REQUEST = (&H80090340)
'The KDC was unable to generate a referral for the service requested.
Public Const SEC_E_KDC_UNABLE_TO_REFER = (&H80090341)
'The encryption type requested is not supported by the KDC.
Public Const SEC_E_KDC_UNKNOWN_ETYPE = (&H80090342)
'An unsupported preauthentication mechanism was presented to the kerberos package.
Public Const SEC_E_UNSUPPORTED_PREAUTH = (&H80090343)
'The requested operation cannot be completed. The computer must be trusted
'for delegation and the current user account must be configured to allow delegation.
Public Const SEC_E_DELEGATION_REQUIRED = (&H80090345)
'Client's supplied SSPI channel bindings were incorrect.
Public Const SEC_E_BAD_BINDINGS = (&H80090346)
'The received certificate was mapped to multiple accounts.
Public Const SEC_E_MULTIPLE_ACCOUNTS = (&H80090347)
'SEC_E_NO_KERB_KEY
Public Const SEC_E_NO_KERB_KEY = (&H80090348)
'The certificate is not valid for the requested usage.
Public Const SEC_E_CERT_WRONG_USAGE = (&H80090349)
'The system detected a possible attempt to compromise security.
'Please ensure that you can contact the server that authenticated you.
Public Const SEC_E_DOWNGRADE_DETECTED = (&H80090350)
'The smartcard certificate used for authentication has been revoked.
'Please contact your system administrator. There may be additional information in the
'event log.
Public Const SEC_E_SMARTCARD_CERT_REVOKED = (&H80090351)
'An untrusted certificate authority was detected While processing the
'smartcard certificate used for authentication. Please contact your system
'administrator.
Public Const SEC_E_ISSUING_CA_UNTRUSTED = (&H80090352)
'The revocation status of the smartcard certificate used for
'authentication could not be determined. Please contact your system administrator.
Public Const SEC_E_REVOCATION_OFFINE_C = (&H80090353)
'The smartcard certificate used for authentication was not trusted. Please
'contact your system administrator.
Public Const SEC_E_PKINIT_CLIENT_FAILURE = (&H80090354)
'The smartcard certificate used for authentication has expired. Please
'contact your system administrator.
Public Const SEC_E_SMARTCARD_CERT_EXPIRED = (&H80090355)
'The Kerberos subsystem encountered an error. A service for user protocol
'request was made
'against a domain controller which does not support service for user.
Public Const SEC_E_NO_S4U_PROT_SUPPORT = (&H80090356)
'An attempt was made by this server to make a Kerberos constrained delegation
'request for a target outside of the server's realm.
'This is not supported, and indicates a misconfiguration on this
'server's allowed to delegate to list. Please contact your administrator.
Public Const SEC_E_CROSSREALM_DELEGATION_FAILURE = (&H80090357)

'Provided for backwards compatibility
Public Const SEC_E_NO_SPM As Long = SEC_E_INTERNAL_ERROR
Public Const SEC_E_NOT_SUPPORTED As Long = SEC_E_UNSUPPORTED_FUNCTION
'An error occurred while performing an operation on a cryptographic message.
Public Const CRYPT_E_MSG_ERROR = (&H80091001)
'Unknown cryptographic algorithm.
Public Const CRYPT_E_UNKNOWN_ALGO = (&H80091002)
'The object identifier is poorly formatted.
Public Const CRYPT_E_OID_FORMAT = (&H80091003)
'Invalid cryptographic message type.
Public Const CRYPT_E_INVALID_MSG_TYPE = (&H80091004)
'Unexpected cryptographic message encoding.
Public Const CRYPT_E_UNEXPECTED_ENCODING = (&H80091005)
'The cryptographic message does not contain an expected authenticated attribute.
Public Const CRYPT_E_AUTH_ATTR_MISSING = (&H80091006)
'The hash value is not correct.
Public Const CRYPT_E_HASH_VALUE = (&H80091007)
'The index value is not valid.
Public Const CRYPT_E_INVALID_INDEX = (&H80091008)
'The content of the cryptographic message has already been decrypted.
Public Const CRYPT_E_ALREADY_DECRYPTED = (&H80091009)
'The content of the cryptographic message has not been decrypted yet.
Public Const CRYPT_E_NOT_DECRYPTED = (&H8009100A)
'The enveloped-data message does not contain the specified recipient.
Public Const CRYPT_E_RECIPIENT_NOT_FOUND = (&H8009100B)
'Invalid control type.
Public Const CRYPT_E_CONTROL_TYPE = (&H8009100C)
'Invalid issuer and/or serial number.
Public Const CRYPT_E_ISSUER_SERIALNUMBER = (&H8009100D)
'Cannot find the original signer.
Public Const CRYPT_E_SIGNER_NOT_FOUND = (&H8009100E)
'The cryptographic message does not contain all of the requested attributes.
Public Const CRYPT_E_ATTRIBUTES_MISSING = (&H8009100F)
'The streamed cryptographic message is not ready to return data.
Public Const CRYPT_E_STREAM_MSG_NOT_READY = (&H80091010)
'The streamed cryptographic message requires more data to complete the
'decode operation.
Public Const CRYPT_E_STREAM_INSUFFICIENT_DATA = (&H80091011)
'The protected data needs to be re-protected.
Public Const CRYPT_I_NEW_PROTECTION_REQUIRED = (&H91012)
'The length specified for the output data was insufficient.
Public Const CRYPT_E_BAD_LEN = (&H80092001)
'An error occurred during encode or decode operation.
Public Const CRYPT_E_BAD_ENCODE = (&H80092002)
'An error occurred while reading or writing to a file.
Public Const CRYPT_E_FILE_ERROR = (&H80092003)
'Cannot find object or property.
Public Const CRYPT_E_NOT_FOUND = (&H80092004)
'The object or property already exists.
Public Const CRYPT_E_EXISTS = (&H80092005)
'No provider was specified for the store or object.
Public Const CRYPT_E_NO_PROVIDER = (&H80092006)
'The specified certificate is self signed.
Public Const CRYPT_E_SELF_SIGNED = (&H80092007)
'The previous certificate or CRL context was deleted.
Public Const CRYPT_E_DELETED_PREV = (&H80092008)
'Cannot find the requested object.
Public Const CRYPT_E_NO_MATCH = (&H80092009)
'The certificate does not have a property that references a private key.
Public Const CRYPT_E_UNEXPECTED_MSG_TYPE = (&H8009200A)
'Cannot find the certificate and private key for decryption.
Public Const CRYPT_E_NO_KEY_PROPERTY = (&H8009200B)
'Cannot find the certificate and private key to use for decryption.
Public Const CRYPT_E_NO_DECRYPT_CERT = (&H8009200C)
'Not a cryptographic message or the cryptographic message is not formatted
'correctly.
Public Const CRYPT_E_BAD_MSG = (&H8009200D)
'The signed cryptographic message does not have a signer for the specified
'signer index.
Public Const CRYPT_E_NO_SIGNER = (&H8009200E)
'Final closure is pending until additional frees or closes.
Public Const CRYPT_E_PENDING_CLOSE = (&H8009200F)
'The certificate is revoked.
Public Const CRYPT_E_REVOKED = (&H80092010)
'No Dll or exported function was found to verify revocation.
Public Const CRYPT_E_NO_REVOCATION_DLL = (&H80092011)
'The revocation function was unable to check revocation for the certificate.
Public Const CRYPT_E_NO_REVOCATION_CHECK = (&H80092012)
'The revocation function was unable to check revocation because the revocation
'server was offline.
Public Const CRYPT_E_REVOCATION_OFFINE = (&H80092013)
'The certificate is not in the revocation server's database.
Public Const CRYPT_E_NOT_IN_REVOCATION_DATABASE = (&H80092014)
'The string contains a non-numeric character.
Public Const CRYPT_E_INVALID_NUMERIC_STRING = (&H80092020)
'The string contains a non-printable character.
Public Const CRYPT_E_INVALID_PRINTABLE_STRING = (&H80092021)
'The string contains a character not in the 7 bit ASCII character set.
Public Const CRYPT_E_INVALID_IA5_STRING = (&H80092022)
'The string contains an invalid X500 name attribute key, oid, value or delimiter.
Public Const CRYPT_E_INVALID_X500_STRING = (&H80092023)
'The dwValueType for the CERT_NAME_VALUE is not one of the character strings.
'Most likely it is either a CERT_RDN_ENCODED_BLOB or CERT_TDN_OCTED_STRING.
Public Const CRYPT_E_NOT_CHAR_STRING = (&H80092024)
'The Put operation can not continue. The file needs to be resized. However,
'there is already a signature present. A complete signing operation must be done.
Public Const CRYPT_E_FILERESIZED = (&H80092025)
'The cryptographic operation failed due to a local security option setting.
Public Const CRYPT_E_SECURITY_SETTINGS = (&H80092026)
'No DLL or exported function was found to verify subject usage.
Public Const CRYPT_E_NO_VERIFY_USAGE_DLL = (&H80092027)
'The called function was unable to do a usage check on the subject.
Public Const CRYPT_E_NO_VERIFY_USAGE_CHECK = (&H80092028)
'Since the server was offline, the called function was unable to complete
'the usage check.
Public Const CRYPT_E_VERIFY_USAGE_OFFINE = (&H80092029)
'The subject was not found in a Certificate Trust List (CT).
Public Const CRYPT_E_NOT_IN_CTL = (&H8009202A)
'None of the signers of the cryptographic message or certificate trust
'list is trusted.
Public Const CRYPT_E_NO_TRUSTED_SIGNER = (&H8009202B)
'The public key's algorithm parameters are missing.
Public Const CRYPT_E_MISSING_PUBKEY_PARA = (&H8009202C)
'OSS Certificate encode/decode error code base
'
'See asn1code.h for a definition of the OSS runtime errors. The OSS
'error values are offset by CRYPT_E_OSS_ERROR.
Public Const CRYPT_E_OSS_ERROR = (&H80093000)
'OSS ASN.1 Error: Output Buffer is too small.
Public Const OSS_MORE_BUF = (&H80093001)
'OSS ASN.1 Error: Signed integer is encoded as a unsigned integer.
Public Const OSS_NEGATIVE_UINTEGER = (&H80093002)
'OSS ASN.1 Error: Unknown ASN.1 data type.
Public Const OSS_PDU_RANGE = (&H80093003)
'OSS ASN.1 Error: Output buffer is too small, the decoded data has been truncated.
Public Const OSS_MORE_INPUT = (&H80093004)
'OSS ASN.1 Error: Invalid data.
Public Const OSS_DATA_ERROR = (&H80093005)
'OSS ASN.1 Error: Invalid argument.
Public Const OSS_BAD_ARG = (&H80093006)
'OSS ASN.1 Error: Encode/Decode version mismatch.
Public Const OSS_BAD_VERSION = (&H80093007)
'OSS ASN.1 Error: Out of memory.
Public Const OSS_OUT_MEMORY = (&H80093008)
'OSS ASN.1 Error: Encode/Decode Error.
Public Const OSS_PDU_MISMATCH = (&H80093009)
'OSS ASN.1 Error: Internal Error.
Public Const OSS_LIMITED = (&H8009300A)
'OSS ASN.1 Error: Invalid data.
Public Const OSS_BAD_PTR = (&H8009300B)
'OSS ASN.1 Error: Invalid data.
Public Const OSS_BAD_TIME = (&H8009300C)
'OSS ASN.1 Error: Unsupported BER indefinite-length encoding.
Public Const OSS_INDEFINITE_NOT_SUPPORTED = (&H8009300D)
'OSS ASN.1 Error: Access violation.
Public Const OSS_MEM_ERROR = (&H8009300E)
'OSS ASN.1 Error: Invalid data.
Public Const OSS_BAD_TABLE = (&H8009300F)
'OSS ASN.1 Error: Invalid data.
Public Const OSS_TOO_LONG = (&H80093010)
'OSS ASN.1 Error: Invalid data.
Public Const OSS_CONSTRAINT_VIOLATED = (&H80093011)
'OSS ASN.1 Error: Internal Error.
Public Const OSS_FATAL_ERROR = (&H80093012)
'OSS ASN.1 Error: Multi-threading conflict.
Public Const OSS_ACCESS_SERIALIZATION_ERROR = (&H80093013)
'OSS ASN.1 Error: Invalid data.
Public Const OSS_NULL_TBL = (&H80093014)
'OSS ASN.1 Error: Invalid data.
Public Const OSS_NULL_FCN = (&H80093015)
'OSS ASN.1 Error: Invalid data.
Public Const OSS_BAD_ENCRULES = (&H80093016)
'OSS ASN.1 Error: Encode/Decode function not implemented.
Public Const OSS_UNAVAIL_ENCRULES = (&H80093017)
'OSS ASN.1 Error: Trace file error.
Public Const OSS_CANT_OPEN_TRACE_WINDOW = (&H80093018)
'OSS ASN.1 Error: Function not implemented.
Public Const OSS_UNIMPLEMENTED = (&H80093019)
'OSS ASN.1 Error: Program link error.
Public Const OSS_OID_DLL_NOT_LINKED = (&H8009301A)
'OSS ASN.1 Error: Trace file error.
Public Const OSS_CANT_OPEN_TRACE_FILE = (&H8009301B)
'OSS ASN.1 Error: Trace file error.
Public Const OSS_TRACE_FILE_ALREADY_OPEN = (&H8009301C)
'OSS ASN.1 Error: Invalid data.
Public Const OSS_TABLE_MISMATCH = (&H8009301D)
'OSS ASN.1 Error: Invalid data.
Public Const OSS_TYPE_NOT_SUPPORTED = (&H8009301E)
'OSS ASN.1 Error: Program link error.
Public Const OSS_REAL_DLL_NOT_LINKED = (&H8009301F)
'OSS ASN.1 Error: Program link error.
Public Const OSS_REAL_CODE_NOT_LINKED = (&H80093020)
'OSS ASN.1 Error: Program link error.
Public Const OSS_OUT_OF_RANGE = (&H80093021)
'OSS ASN.1 Error: Program link error.
Public Const OSS_COPIER_DLL_NOT_LINKED = (&H80093022)
'OSS ASN.1 Error: Program link error.
Public Const OSS_CONSTRAINT_DLL_NOT_LINKED = (&H80093023)
'OSS ASN.1 Error: Program link error.
Public Const OSS_COMPARATOR_DLL_NOT_LINKED = (&H80093024)
'OSS ASN.1 Error: Program link error.
Public Const OSS_COMPARATOR_CODE_NOT_LINKED = (&H80093025)
'OSS ASN.1 Error: Program link error.
Public Const OSS_MEM_MGR_DLL_NOT_LINKED = (&H80093026)
'OSS ASN.1 Error: Program link error.
Public Const OSS_PDV_DLL_NOT_LINKED = (&H80093027)
'OSS ASN.1 Error: Program link error.
Public Const OSS_PDV_CODE_NOT_LINKED = (&H80093028)
'OSS ASN.1 Error: Program link error.
Public Const OSS_API_DLL_NOT_LINKED = (&H80093029)
'OSS ASN.1 Error: Program link error.
Public Const OSS_BERDER_DLL_NOT_LINKED = (&H8009302A)
'OSS ASN.1 Error: Program link error.
Public Const OSS_PER_DLL_NOT_LINKED = (&H8009302B)
'OSS ASN.1 Error: Program link error.
Public Const OSS_OPEN_TYPE_ERROR = (&H8009302C)
'OSS ASN.1 Error: System resource error.
Public Const OSS_MUTEX_NOT_CREATED = (&H8009302D)
'OSS ASN.1 Error: Trace file error.
Public Const OSS_CANT_CLOSE_TRACE_FILE = (&H8009302E)
'ASN1 Certificate encode/decode error code base.
'
'The ASN1 error values are offset by CRYPT_E_ASN1_ERROR.
Public Const CRYPT_E_ASN1_ERROR = (&H80093100)
'ASN1 internal encode or decode error.
Public Const CRYPT_E_ASN1_INTERNAL = (&H80093101)
'ASN1 unexpected end of data.
Public Const CRYPT_E_ASN1_EOD = (&H80093102)
'ASN1 corrupted data.
Public Const CRYPT_E_ASN1_CORRUPT = (&H80093103)
'ASN1 value too large.
Public Const CRYPT_E_ASN1_LARGE = (&H80093104)
'ASN1 constraint violated.
Public Const CRYPT_E_ASN1_CONSTRAINT = (&H80093105)
'ASN1 out of memory.
Public Const CRYPT_E_ASN1_MEMORY = (&H80093106)
'ASN1 buffer overflow.
Public Const CRYPT_E_ASN1_OVERFOW = (&H80093107)
'ASN1 function not supported for this PDU.
Public Const CRYPT_E_ASN1_BADPDU = (&H80093108)
'ASN1 bad arguments to function call.
Public Const CRYPT_E_ASN1_BADARGS = (&H80093109)
'ASN1 bad real value.
Public Const CRYPT_E_ASN1_BADREAL = (&H8009310A)
'ASN1 bad tag value met.
Public Const CRYPT_E_ASN1_BADTAG = (&H8009310B)
'ASN1 bad choice value.
Public Const CRYPT_E_ASN1_CHOICE = (&H8009310C)
'ASN1 bad encoding rule.
Public Const CRYPT_E_ASN1_RULE = (&H8009310D)
'ASN1 bad unicode (UTF8).
Public Const CRYPT_E_ASN1_UTF8 = (&H8009310E)
'ASN1 bad PDU type.
Public Const CRYPT_E_ASN1_PDU_TYPE = (&H80093133)
'ASN1 not yet implemented.
Public Const CRYPT_E_ASN1_NYI = (&H80093134)
'ASN1 skipped unknown extension(s).
Public Const CRYPT_E_ASN1_EXTENDED = (&H80093201)
'ASN1 end of data expected
Public Const CRYPT_E_ASN1_NOEOD = (&H80093202)
'The request subject name is invalid or too long.
Public Const CERTSRV_E_BAD_REQUESTSUBJECT = (&H80094001)
'The request does not exist.
Public Const CERTSRV_E_NO_REQUEST = (&H80094002)
'The request's current status does not allow this operation.
Public Const CERTSRV_E_BAD_REQUESTSTATUS = (&H80094003)
'The requested property value is empty.
Public Const CERTSRV_E_PROPERTY_EMPTY = (&H80094004)
'The certification authority's certificate contains invalid data.
Public Const CERTSRV_E_INVALID_CA_CERTIFICATE = (&H80094005)
'Certificate service has been suspended for a database restore operation.
Public Const CERTSRV_E_SERVER_SUSPENDED = (&H80094006)
'The certificate contains an encoded length that is potentially
'incompatible with older enrollment software.
Public Const CERTSRV_E_ENCODING_LENGTH = (&H80094007)
'The operation is denied. The user has multiple roles assigned
'and the certification authority is configured to enforce role separation.
Public Const CERTSRV_E_ROLECONFICT = (&H80094008)
'The operation is denied. It can only be performed by a certificate
'manager that is allowed to manage certificates for the current requester.
Public Const CERTSRV_E_RESTRICTEDOFFICER = (&H80094009)
'Cannot archive private key. The certification authority is not
'configured for key archival.
Public Const CERTSRV_E_KEY_ARCHIVAL_NOT_CONFIGURED = (&H8009400A)
'Cannot archive private key. The certification authority could not
'verify one or more key recovery certificates.
Public Const CERTSRV_E_NO_VALID_KRA = (&H8009400B)
'The request is incorrectly formatted. The encrypted private key must
'be in an unauthenticated attribute in an outermost signature.
Public Const CERTSRV_E_BAD_REQUEST_KEY_ARCHIVAL = (&H8009400C)
'At least one security principal must have the permission to manage this CA.
Public Const CERTSRV_E_NO_CAADMIN_DEFINED = (&H8009400D)
'The request contains an invalid renewal certificate attribute.
Public Const CERTSRV_E_BAD_RENEWAL_CERT_ATTRIBUTE = (&H8009400E)
'An attempt was made to open a Certification Authority database session,
'but there are already too many active sessions. The server may need
'to be configured to allow additional sessions.
Public Const CERTSRV_E_NO_DB_SESSIONS = (&H8009400F)
'A memory reference caused a data alignment fault.
Public Const CERTSRV_E_ALIGNMENT_FAULT = (&H80094010)
'The permissions on this certification authority do not allow the current
'user to enroll for certificates.
Public Const CERTSRV_E_ENROLL_DENIED = (&H80094011)
'The permissions on the certificate template do not allow the current
'user to enroll for this type of certificate.
Public Const CERTSRV_E_TEMPLATE_DENIED = (&H80094012)
'The contacted domain controller cannot support signed LDAP traffic.
'Update the domain controller or configure Certificate Services to
'use SSL for Active Directory access.
Public Const CERTSRV_E_DOWNLEVEL_DC_SSL_OR_UPGRADE = (&H80094013)
'The requested certificate template is not supported by this CA.
Public Const CERTSRV_E_UNSUPPORTED_CERT_TYPE = (&H80094800)
'The request contains no certificate template information.
Public Const CERTSRV_E_NO_CERT_TYPE = (&H80094801)
'The request contains conflicting template information.
Public Const CERTSRV_E_TEMPLATE_CONFICT = (&H80094802)
'The request is missing a required Subject Alternate name extension.
Public Const CERTSRV_E_SUBJECT_ALT_NAME_REQUIRED = (&H80094803)
'The request is missing a required private key for archival by the server.
Public Const CERTSRV_E_ARCHIVED_KEY_REQUIRED = (&H80094804)
'The request is missing a required SMIME capabilities extension.
Public Const CERTSRV_E_SMIME_REQUIRED = (&H80094805)
'The request was made on behalf of a subject other than the caller.
'The certificate template must be configured to require at least one
'signature to authorize the request.
Public Const CERTSRV_E_BAD_RENEWAL_SUBJECT = (&H80094806)
'The request template version is newer than the supported template version.
Public Const CERTSRV_E_BAD_TEMPLATE_VERSION = (&H80094807)
'The template is missing a required signature policy attribute.
Public Const CERTSRV_E_TEMPLATE_POLICY_REQUIRED = (&H80094808)
'The request is missing required signature policy information.
Public Const CERTSRV_E_SIGNATURE_POLICY_REQUIRED = (&H80094809)
'The request is missing one or more required signatures.
Public Const CERTSRV_E_SIGNATURE_COUNT = (&H8009480A)
'One or more signatures did not include the required application or issuance
'policies. The request is missing one or more required valid signatures.
Public Const CERTSRV_E_SIGNATURE_REJECTED = (&H8009480B)
'The request is missing one or more required signature issuance policies.
Public Const CERTSRV_E_ISSUANCE_POLICY_REQUIRED = (&H8009480C)
'The UPN is unavailable and cannot be added to the Subject Alternate name.
Public Const CERTSRV_E_SUBJECT_UPN_REQUIRED = (&H8009480D)
'The Active Directory GUID is unavailable and cannot be added to the
'Subject Alternate name.
Public Const CERTSRV_E_SUBJECT_DIRECTORY_GUID_REQUIRED = (&H8009480E)
'The DNS name is unavailable and cannot be added to the Subject Alternate name.
Public Const CERTSRV_E_SUBJECT_DNS_REQUIRED = (&H8009480F)
'The request includes a private key for archival by the server, but key
'archival is not enabled for the specified certificate template.
Public Const CERTSRV_E_ARCHIVED_KEY_UNEXPECTED = (&H80094810)
'The public key does not meet the minimum size required by the specified
'certificate template.
Public Const CERTSRV_E_KEY_LENGTH = (&H80094811)
'The EMail name is unavailable and cannot be added to the Subject or
'Subject Alternate name.
Public Const CERTSRV_E_SUBJECT_EMAIL_REQUIRED = (&H80094812)
'One or more certificate templates to be enabled on this certification
'authority could not be found.
Public Const CERTSRV_E_UNKNOWN_CERT_TYPE = (&H80094813)
'The certificate template renewal period is longer than the certificate
'validity period. The template should be reconfigured or the CA certificate
'renewed.
Public Const CERTSRV_E_CERT_TYPE_OVERLAP = (&H80094814)

'The range &H5000-&H51ff is reserved for XENROLL errors.


'The key is not exportable.
Public Const XENROLL_E_KEY_NOT_EXPORTABLE = (&H80095000)
'You cannot add the root CA certificate into your local store.
Public Const XENROLL_E_CANNOT_ADD_ROOT_CERT = (&H80095001)
'The key archival hash attribute was not found in the response.
Public Const XENROLL_E_RESPONSE_KA_HASH_NOT_FOUND = (&H80095002)
'An unexpected key archival hash attribute was found in the response.
Public Const XENROLL_E_RESPONSE_UNEXPECTED_KA_HASH = (&H80095003)
'There is a key archival hash mismatch between the request and the response.
Public Const XENROLL_E_RESPONSE_KA_HASH_MISMATCH = (&H80095004)
'Signing certificate cannot include SMIME extension.
Public Const XENROLL_E_KEYSPEC_SMIME_MISMATCH = (&H80095005)
'A system-level error occurred while verifying trust.
Public Const TRUST_E_SYSTEM_ERROR = (&H80096001)
'The certificate for the signer of the message is invalid or not found.
Public Const TRUST_E_NO_SIGNER_CERT = (&H80096002)
'One of the counter signatures was invalid.
Public Const TRUST_E_COUNTER_SIGNER = (&H80096003)
'The signature of the certificate can not be verified.
Public Const TRUST_E_CERT_SIGNATURE = (&H80096004)
'The timestamp signature and/or certificate could not be verified or is malformed.
Public Const TRUST_E_TIME_STAMP = (&H80096005)
'The digital signature of the object did not verify.
Public Const TRUST_E_BAD_DIGEST = (&H80096010)
'A certificate's basic constraint extension has not been observed.
Public Const TRUST_E_BASIC_CONSTRAINTS = (&H80096019)
'The certificate does not meet or contain the Authenticode financial extensions.
Public Const TRUST_E_FINANCIAL_CRITERIA = (&H8009601E)

'Error codes for mssipotf.dll
'Most of the error codes can only occur when an error occurs
'  during font file signing


'Tried to reference a part of the file outside the proper range.
Public Const MSSIPOTF_E_OUTOFMEMRANGE = (&H80097001)
'Could not retrieve an object from the file.
Public Const MSSIPOTF_E_CANTGETOBJECT = (&H80097002)
'Could not find the head table in the file.
Public Const MSSIPOTF_E_NOHEADTABLE = (&H80097003)
'The magic number in the head table is incorrect.
Public Const MSSIPOTF_E_BAD_MAGICNUMBER = (&H80097004)
'The offset table has incorrect values.
Public Const MSSIPOTF_E_BAD_OFFSET_TABLE = (&H80097005)
'Duplicate table tags or tags out of alphabetical order.
Public Const MSSIPOTF_E_TABLE_TAGORDER = (&H80097006)
'A table does not start on a long word boundary.
Public Const MSSIPOTF_E_TABLE_LONGWORD = (&H80097007)
'First table does not appear after header information.
Public Const MSSIPOTF_E_BAD_FIRST_TABLE_PLACEMENT = (&H80097008)
'Two or more tables overlap.
Public Const MSSIPOTF_E_TABLES_OVERLAP = (&H80097009)
'Too many pad bytes between tables or pad bytes are not 0.
Public Const MSSIPOTF_E_TABLE_PADBYTES = (&H8009700A)
'File is too small to contain the last table.
Public Const MSSIPOTF_E_FILETOOSMALL = (&H8009700B)
'A table checksum is incorrect.
Public Const MSSIPOTF_E_TABLE_CHECKSUM = (&H8009700C)
'The file checksum is incorrect.
Public Const MSSIPOTF_E_FILE_CHECKSUM = (&H8009700D)
'The signature does not have the correct attributes for the policy.
Public Const MSSIPOTF_E_FAILED_POLICY = (&H80097010)
'The file did not pass the hints check.
Public Const MSSIPOTF_E_FAILED_HINTS_CHECK = (&H80097011)
'The file is not an OpenType file.
Public Const MSSIPOTF_E_NOT_OPENTYPE = (&H80097012)
'Failed on a file operation (open, map, read, write).
Public Const MSSIPOTF_E_FILE = (&H80097013)
'A call to a CryptoAPI function failed.
Public Const MSSIPOTF_E_CRYPT = (&H80097014)
'There is a bad version number in the file.
Public Const MSSIPOTF_E_BADVERSION = (&H80097015)
'The structure of the DSIG table is incorrect.
Public Const MSSIPOTF_E_DSIG_STRUCTURE = (&H80097016)
'A check failed in a partially constant table.
Public Const MSSIPOTF_E_PCONST_CHECK = (&H80097017)
'Some kind of structural error.
Public Const MSSIPOTF_E_STRUCTURE = (&H80097018)

Public Const NTE_OP_OK = 0

'Note that additional FACILITY_SSPI errors are in issperr.h
'******************
'FACILITY_CERT
'******************


'Unknown trust provider.
Public Const TRUST_E_PROVIDER_UNKNOWN = (&H800B0001)
'The trust verification action specified is not supported by the specified
'trust provider.
Public Const TRUST_E_ACTION_UNKNOWN = (&H800B0002)
'The form specified for the subject is not one supported or known by
'the specified trust provider.
Public Const TRUST_E_SUBJECT_FORM_UNKNOWN = (&H800B0003)
'The subject is not trusted for the specified action.
Public Const TRUST_E_SUBJECT_NOT_TRUSTED = (&H800B0004)
'Error due to problem in ASN.1 encoding process.
Public Const DIGSIG_E_ENCODE = (&H800B0005)
'Error due to problem in ASN.1 decoding process.
Public Const DIGSIG_E_DECODE = (&H800B0006)
'Reading / writing Extensions where Attributes are appropriate, and visa versa.
Public Const DIGSIG_E_EXTENSIBILITY = (&H800B0007)
'Unspecified cryptographic failure.
Public Const DIGSIG_E_CRYPTO = (&H800B0008)
'The size of the data could not be determined.
Public Const PERSIST_E_SIZEDEFINITE = (&H800B0009)
'The size of the indefinite-sized data could not be determined.
Public Const PERSIST_E_SIZEINDEFINITE = (&H800B000A)
'This object does not read and write self-sizing data.
Public Const PERSIST_E_NOTSELFSIZING = (&H800B000B)
'No signature was present in the subject.
Public Const TRUST_E_NOSIGNATURE = (&H800B0100)
'A required certificate is not within its validity period when verifying
'against the current system clock or the timestamp in the signed file.
Public Const CERT_E_EXPIRED = (&H800B0101)
'The validity periods of the certification chain do not nest correctly.
Public Const CERT_E_VALIDITYPERIODNESTING = (&H800B0102)
'A certificate that can only be used as an end-entity is being used as
'a CA or visa versa.
Public Const CERT_E_ROLE = (&H800B0103)
'A path length constraint in the certification chain has been violated.
Public Const CERT_E_PATHLENCONST = (&H800B0104)
'A certificate contains an unknown extension that is marked 'critical'.
Public Const CERT_E_CRITICAL = (&H800B0105)
'A certificate being used for a purpose other than the ones specified by its CA.
Public Const CERT_E_PURPOSE = (&H800B0106)
'A parent of a given certificate in fact did not issue that child certificate.
Public Const CERT_E_ISSUERCHAINING = (&H800B0107)
'A certificate is missing or has an empty value for an important field, such
'as a subject or issuer name.
Public Const CERT_E_MALFORMED = (&H800B0108)
'A certificate chain processed, but terminated in a root certificate which
'is not trusted by the trust provider.
Public Const CERT_E_UNTRUSTEDROOT = (&H800B0109)
'A certificate chain could not be built to a trusted root authority.
Public Const CERT_E_CHAINING = (&H800B010A)
'Generic trust failure.
Public Const TRUST_E_FAIL = (&H800B010B)
'A certificate was explicitly revoked by its issuer.
Public Const CERT_E_REVOKED = (&H800B010C)
'The certification path terminates with the test root which is not trusted
'with the current policy settings.
Public Const CERT_E_UNTRUSTEDTESTROOT = (&H800B010D)
'The revocation process could not continue - the certificate(s) could not be checked.
Public Const CERT_E_REVOCATION_FAILURE = (&H800B010E)
'The certificate's CN name does not match the passed value.
Public Const CERT_E_CN_NO_MATCH = (&H800B010F)
'The certificate is not valid for the requested usage.
Public Const CERT_E_WRONG_USAGE = (&H800B0110)
'The certificate was explicitly marked as untrusted by the user.
Public Const TRUST_E_EXPLICIT_DISTRUST = (&H800B0111)
'A certification chain processed correctly, but one of the CA certificates
'is not trusted by the policy provider.
Public Const CERT_E_UNTRUSTEDCA = (&H800B0112)
'The certificate has invalid policy.
Public Const CERT_E_INVALID_POLICY = (&H800B0113)
'The certificate has an invalid name. The name is not included in
'the permitted list or is explicitly excluded.
Public Const CERT_E_INVALID_NAME = (&H800B0114)

'*****************
'FACILITY_SETUPAPI
'*****************
'A non-empty line was encountered in the INF before the start of a section.
Public Const SPAPI_E_EXPECTED_SECTION_NAME = (&H800F0000)
'A section name marker in the INF is not complete, or does not exist on
'a line by itself.
Public Const SPAPI_E_BAD_SECTION_NAME_LINE = (&H800F0001)
'An INF section was encountered whose name exceeds the maximum section name length.
Public Const SPAPI_E_SECTION_NAME_TOO_LONG = (&H800F0002)
'The syntax of the INF is invalid.
Public Const SPAPI_E_GENERAL_SYNTAX = (&H800F0003)
'The style of the INF is different than what was requested.
Public Const SPAPI_E_WRONG_INF_STYLE = (&H800F0100)
'The required section was not found in the INF.
Public Const SPAPI_E_SECTION_NOT_FOUND = (&H800F0101)
'The required line was not found in the INF.
Public Const SPAPI_E_LINE_NOT_FOUND = (&H800F0102)
'The files affected by the installation of this file queue have not been
'backed up for uninstall.
Public Const SPAPI_E_NO_BACKUP = (&H800F0103)
'The INF or the device information set or element does not have
'an associated install class.
Public Const SPAPI_E_NO_ASSOCIATED_CLASS = (&H800F0200)
'The INF or the device information set or element does not match
'the specified install class.
Public Const SPAPI_E_CLASS_MISMATCH = (&H800F0201)
'An existing device was found that is a duplicate of the device
'being manually installed.
Public Const SPAPI_E_DUPLICATE_FOUND = (&H800F0202)
'There is no driver selected for the device information set or element.
Public Const SPAPI_E_NO_DRIVER_SELECTED = (&H800F0203)
'The requested device registry key does not exist.
Public Const SPAPI_E_KEY_DOES_NOT_EXIST = (&H800F0204)
'The device instance name is invalid.
Public Const SPAPI_E_INVALID_DEVINST_NAME = (&H800F0205)
'The install class is not present or is invalid.
Public Const SPAPI_E_INVALID_CLASS = (&H800F0206)
'The device instance cannot be created because it already exists.
Public Const SPAPI_E_DEVINST_ALREADY_EXISTS = (&H800F0207)
'The operation cannot be performed on a device information element
'that has not been registered.
Public Const SPAPI_E_DEVINFO_NOT_REGISTERED = (&H800F0208)
'The device property code is invalid.
Public Const SPAPI_E_INVALID_REG_PROPERTY = (&H800F0209)
'The INF from which a driver list is to be built does not exist.
Public Const SPAPI_E_NO_INF = (&H800F020A)
'The device instance does not exist in the hardware tree.
Public Const SPAPI_E_NO_SUCH_DEVINST = (&H800F020B)
'The icon representing this install class cannot be loaded.
Public Const SPAPI_E_CANT_LOAD_CLASS_ICON = (&H800F020C)
'The class installer registry entry is invalid.
Public Const SPAPI_E_INVALID_CLASS_INSTALLER = (&H800F020D)
'The class installer has indicated that the default action should be performed
'for this installation request.
Public Const SPAPI_E_DI_DO_DEFAULT = (&H800F020E)
'The operation does not require any files to be copied.
Public Const SPAPI_E_DI_NOFILECOPY = (&H800F020F)
'The specified hardware profile does not exist.
Public Const SPAPI_E_INVALID_HWPROFILE = (&H800F0210)
'There is no device information element currently selected for
'this device information set.
Public Const SPAPI_E_NO_DEVICE_SELECTED = (&H800F0211)
'The operation cannot be performed because the device information set is locked.
Public Const SPAPI_E_DEVINFO_LIST_LOCKED = (&H800F0212)
'The operation cannot be performed because the device information element is locked.
Public Const SPAPI_E_DEVINFO_DATA_LOCKED = (&H800F0213)
'The specified path does not contain any applicable device INFs.
Public Const SPAPI_E_DI_BAD_PATH = (&H800F0214)
'No class installer parameters have been set for the device
'information set or element.
Public Const SPAPI_E_NO_CLASSINSTALL_PARAMS = (&H800F0215)
'The operation cannot be performed because the file queue is locked.
Public Const SPAPI_E_FILEQUEUE_LOCKED = (&H800F0216)
'A service installation section in this INF is invalid.
Public Const SPAPI_E_BAD_SERVICE_INSTALLSECT = (&H800F0217)
'There is no class driver list for the device information element.
Public Const SPAPI_E_NO_CLASS_DRIVER_LIST = (&H800F0218)
'The installation failed because a function driver was not specified
'for this device instance.
Public Const SPAPI_E_NO_ASSOCIATED_SERVICE = (&H800F0219)
'There is presently no default device interface designated for this
'interface class.
Public Const SPAPI_E_NO_DEFAULT_DEVICE_INTERFACE = (&H800F021A)
'The operation cannot be performed because the device interface is
'currently active.
Public Const SPAPI_E_DEVICE_INTERFACE_ACTIVE = (&H800F021B)
'The operation cannot be performed because the device interface
'has been removed from the system.
Public Const SPAPI_E_DEVICE_INTERFACE_REMOVED = (&H800F021C)
'An interface installation section in this INF is invalid.
Public Const SPAPI_E_BAD_INTERFACE_INSTALLSECT = (&H800F021D)
'This interface class does not exist in the system.
Public Const SPAPI_E_NO_SUCH_INTERFACE_CLASS = (&H800F021E)
'The reference string supplied for this interface device is invalid.
Public Const SPAPI_E_INVALID_REFERENCE_STRING = (&H800F021F)
'The specified machine name does not conform to UNC naming conventions.
Public Const SPAPI_E_INVALID_MACHINENAME = (&H800F0220)
'A general remote communication error occurred.
Public Const SPAPI_E_REMOTE_COMM_FAILURE = (&H800F0221)
'The machine selected for remote communication is not available at this time.
Public Const SPAPI_E_MACHINE_UNAVAILABLE = (&H800F0222)
'The Plug and Play service is not available on the remote machine.
Public Const SPAPI_E_NO_CONFIGMGR_SERVICES = (&H800F0223)
'The property page provider registry entry is invalid.
Public Const SPAPI_E_INVALID_PROPPAGE_PROVIDER = (&H800F0224)
'The requested device interface is not present in the system.
Public Const SPAPI_E_NO_SUCH_DEVICE_INTERFACE = (&H800F0225)
'The device's co-installer has additional work to perform after
'installation is complete.
Public Const SPAPI_E_DI_POSTPROCESSING_REQUIRED = (&H800F0226)
'The device's co-installer is invalid.
Public Const SPAPI_E_INVALID_COINSTALLER = (&H800F0227)
'There are no compatible drivers for this device.
Public Const SPAPI_E_NO_COMPAT_DRIVERS = (&H800F0228)
'There is no icon that represents this device or device type.
Public Const SPAPI_E_NO_DEVICE_ICON = (&H800F0229)
'A logical configuration specified in this INF is invalid.
Public Const SPAPI_E_INVALID_INF_LOGCONFIG = (&H800F022A)
'The class installer has denied the request to install or upgrade this device.
Public Const SPAPI_E_DI_DONT_INSTALL = (&H800F022B)
'One of the filter drivers installed for this device is invalid.
Public Const SPAPI_E_INVALID_FILTER_DRIVER = (&H800F022C)
'The driver selected for this device does not support Windows XP.
Public Const SPAPI_E_NON_WINDOWS_NT_DRIVER = (&H800F022D)
'The driver selected for this device does not support Windows.
Public Const SPAPI_E_NON_WINDOWS_DRIVER = (&H800F022E)
'The third-party INF does not contain digital signature information.
Public Const SPAPI_E_NO_CATALOG_FOR_OEM_INF = (&H800F022F)
'An invalid attempt was made to use a device installation file queue
'for verification of digital signatures relative to other platforms.
Public Const SPAPI_E_DEVINSTALL_QUEUE_NONNATIVE = (&H800F0230)
'The device cannot be disabled.
Public Const SPAPI_E_NOT_DISABLEABLE = (&H800F0231)
'The device could not be dynamically removed.
Public Const SPAPI_E_CANT_REMOVE_DEVINST = (&H800F0232)
'Cannot copy to specified target.
Public Const SPAPI_E_INVALID_TARGET = (&H800F0233)
'Driver is not intended for this platform.
Public Const SPAPI_E_DRIVER_NONNATIVE = (&H800F0234)
'Operation not allowed in WOW64.
Public Const SPAPI_E_IN_WOW64 = (&H800F0235)
'The operation involving unsigned file copying was rolled back, so that
'a system restore point could be set.
Public Const SPAPI_E_SET_SYSTEM_RESTORE_POINT = (&H800F0236)
'An INF was copied into the Windows INF directory in an improper manner.
Public Const SPAPI_E_INCORRECTLY_COPIED_INF = (&H800F0237)
'The Security Configuration Editor (SCE) APIs have been disabled
'on this Embedded product.
Public Const SPAPI_E_SCE_DISABLED = (&H800F0238)
'No installed components were detected.
Public Const SPAPI_E_ERROR_NOT_INSTALLED = (&H800F1000)

'*****************
'FACILITY_SCARD
'*****************
'=============================
'Facility SCARD Error Messages
'=============================
Public Const SCARD_S_SUCCESS = NO_ERROR


'An internal consistency check failed.
Public Const SCARD_F_INTERNAL_ERROR = (&H80100001)
'The action was cancelled by an SCardCancel request.
Public Const SCARD_E_CANCELLED = (&H80100002)
'The supplied handle was invalid.
Public Const SCARD_E_INVALID_HANDLE = (&H80100003)
'One or more of the supplied parameters could not be properly interpreted.
Public Const SCARD_E_INVALID_PARAMETER = (&H80100004)
'Registry startup information is missing or invalid.
Public Const SCARD_E_INVALID_TARGET = (&H80100005)
'Not enough memory available to complete this command.
Public Const SCARD_E_NO_MEMORY = (&H80100006)
'An internal consistency timer has expired.
Public Const SCARD_F_WAITED_TOO_LONG = (&H80100007)
'The data buffer to receive returned data is too small for the returned data.
Public Const SCARD_E_INSUFFICIENT_BUFFER = (&H80100008)
'The specified reader name is not recognized.
Public Const SCARD_E_UNKNOWN_READER = (&H80100009)
'The user-specified timeout value has expired.
Public Const SCARD_E_TIMEOUT = (&H8010000A)
'The smart card cannot be accessed because of other connections outstanding.
Public Const SCARD_E_SHARING_VIOLATION = (&H8010000B)
'The operation requires a Smart Card, but no Smart Card is currently in the device.
Public Const SCARD_E_NO_SMARTCARD = (&H8010000C)
'The specified smart card name is not recognized.
Public Const SCARD_E_UNKNOWN_CARD = (&H8010000D)
'The system could not dispose of the media in the requested manner.
Public Const SCARD_E_CANT_DISPOSE = (&H8010000E)
'The requested protocols are incompatible with the protocol currently
'in use with the smart card.
Public Const SCARD_E_PROTO_MISMATCH = (&H8010000F)
'The reader or smart card is not ready to accept commands.
Public Const SCARD_E_NOT_READY = (&H80100010)
'One or more of the supplied parameters values could not be properly interpreted.
Public Const SCARD_E_INVALID_VALUE = (&H80100011)
'The action was cancelled by the system, presumably to log off or shut down.
Public Const SCARD_E_SYSTEM_CANCELLED = (&H80100012)
'An internal communications error has been detected.
Public Const SCARD_F_COMM_ERROR = (&H80100013)
'An internal error has been detected, but the source is unknown.
Public Const SCARD_F_UNKNOWN_ERROR = (&H80100014)
'An ATR obtained from the registry is not a valid ATR string.
Public Const SCARD_E_INVALID_ATR = (&H80100015)
'An attempt was made to end a non-existent transaction.
Public Const SCARD_E_NOT_TRANSACTED = (&H80100016)
'The specified reader is not currently available for use.
Public Const SCARD_E_READER_UNAVAILABLE = (&H80100017)
'The operation has been aborted to allow the server application to exit.
Public Const SCARD_P_SHUTDOWN = (&H80100018)
'The PCI Receive buffer was too small.
Public Const SCARD_E_PCI_TOO_SMALL = (&H80100019)
'The reader driver does not meet minimal requirements for support.
Public Const SCARD_E_READER_UNSUPPORTED = (&H8010001A)
'The reader driver did not produce a unique reader name.
Public Const SCARD_E_DUPLICATE_READER = (&H8010001B)
'The smart card does not meet minimal requirements for support.
Public Const SCARD_E_CARD_UNSUPPORTED = (&H8010001C)
'The Smart card resource manager is not running.
Public Const SCARD_E_NO_SERVICE = (&H8010001D)
'The Smart card resource manager has shut down.
Public Const SCARD_E_SERVICE_STOPPED = (&H8010001E)
'An unexpected card error has occurred.
Public Const SCARD_E_UNEXPECTED = (&H8010001F)
'No Primary Provider can be found for the smart card.
Public Const SCARD_E_ICC_INSTALLATION = (&H80100020)
'The requested order of object creation is not supported.
Public Const SCARD_E_ICC_CREATEORDER = (&H80100021)
'This smart card does not support the requested feature.
Public Const SCARD_E_UNSUPPORTED_FEATURE = (&H80100022)
'The identified directory does not exist in the smart card.
Public Const SCARD_E_DIR_NOT_FOUND = (&H80100023)
'The identified file does not exist in the smart card.
Public Const SCARD_E_FILE_NOT_FOUND = (&H80100024)
'The supplied path does not represent a smart card directory.
Public Const SCARD_E_NO_DIR = (&H80100025)
'The supplied path does not represent a smart card file.
Public Const SCARD_E_NO_FILE = (&H80100026)
'Access is denied to this file.
Public Const SCARD_E_NO_ACCESS = (&H80100027)
'The smartcard does not have enough memory to store the information.
Public Const SCARD_E_WRITE_TOO_MANY = (&H80100028)
'There was an error trying to set the smart card file object pointer.
Public Const SCARD_E_BAD_SEEK = (&H80100029)
'The supplied PIN is incorrect.
Public Const SCARD_E_INVALID_CHV = (&H8010002A)
'An unrecognized error code was returned from a layered component.
Public Const SCARD_E_UNKNOWN_RES_MNG = (&H8010002B)
'The requested certificate does not exist.
Public Const SCARD_E_NO_SUCH_CERTIFICATE = (&H8010002C)
'The requested certificate could not be obtained.
Public Const SCARD_E_CERTIFICATE_UNAVAILABLE = (&H8010002D)
'Cannot find a smart card reader.
Public Const SCARD_E_NO_READERS_AVAILABLE = (&H8010002E)
'A communications error with the smart card has been detected.
'Retry the operation.
Public Const SCARD_E_COMM_DATA_LOST = (&H8010002F)
'The requested key container does not exist on the smart card.
Public Const SCARD_E_NO_KEY_CONTAINER = (&H80100030)
'The Smart card resource manager is too busy to complete this operation.
Public Const SCARD_E_SERVER_TOO_BUSY = (&H80100031)

'These are warning codes.


'The reader cannot communicate with the smart card, due to
'ATR configuration conflicts.
Public Const SCARD_W_UNSUPPORTED_CARD = (&H80100065)
'The smart card is not responding to a reset.
Public Const SCARD_W_UNRESPONSIVE_CARD = (&H80100066)
'Power has been removed from the smart card, so that further
'communication is not possible.
Public Const SCARD_W_UNPOWERED_CARD = (&H80100067)
'The smart card has been reset, so any shared state information is invalid.
Public Const SCARD_W_RESET_CARD = (&H80100068)
'The smart card has been removed, so that further communication is not possible.
Public Const SCARD_W_REMOVED_CARD = (&H80100069)
'Access was denied because of a security violation.
Public Const SCARD_W_SECURITY_VIOLATION = (&H8010006A)
'The card cannot be accessed because the wrong PIN was presented.
Public Const SCARD_W_WRONG_CHV = (&H8010006B)
'The card cannot be accessed because the maximum number of PIN
'entry attempts has been reached.
Public Const SCARD_W_CHV_BLOCKED = (&H8010006C)
'The end of the smart card file has been reached.
Public Const SCARD_W_EOF = (&H8010006D)
'The action was cancelled by the user.
Public Const SCARD_W_CANCELLED_BY_USER = (&H8010006E)
'No PIN was presented to the smart card.
Public Const SCARD_W_CARD_NOT_AUTHENTICATED = (&H8010006F)

'*****************
'FACILITY_COMPLUS
'*****************
'===============================
'Facility COMPLUS Error Messages
'===============================
'The following are the subranges  within the COMPLUS facility
'&H400 - &H4ff               COMADMIN_E_CAT
'&H600 - &H6ff               COMQC errors
'&H700 - &H7ff               MSDTC errors
'&H800 - &H8ff               Other COMADMIN errors
'COMPLUS Admin errors


'Errors occurred accessing one or more objects - the ErrorInfo
'collection may have more detail
Public Const COMADMIN_E_OBJECTERRORS = (&H80110401)
'One or more of the object's properties are missing or invalid
Public Const COMADMIN_E_OBJECTINVALID = (&H80110402)
'The object was not found in the catalog
Public Const COMADMIN_E_KEYMISSING = (&H80110403)
'The object is already registered
Public Const COMADMIN_E_ALREADYINSTALLED = (&H80110404)
'Error occurred writing to the application file
Public Const COMADMIN_E_APP_FILE_WRITEFAIL = (&H80110407)
'Error occurred reading the application file
Public Const COMADMIN_E_APP_FILE_READFAIL = (&H80110408)
'Invalid version number in application file
Public Const COMADMIN_E_APP_FILE_VERSION = (&H80110409)
'The file path is invalid
Public Const COMADMIN_E_BADPATH = (&H8011040A)
'The application is already installed
Public Const COMADMIN_E_APPLICATIONEXISTS = (&H8011040B)
'The role already exists
Public Const COMADMIN_E_ROLEEXISTS = (&H8011040C)
'An error occurred copying the file
Public Const COMADMIN_E_CANTCOPYFILE = (&H8011040D)
'One or more users are not valid
Public Const COMADMIN_E_NOUSER = (&H8011040F)
'One or more users in the application file are not valid
Public Const COMADMIN_E_INVALIDUSERIDS = (&H80110410)
'The component's CLSID is missing or corrupt
Public Const COMADMIN_E_NOREGISTRYCLSID = (&H80110411)
'The component's progID is missing or corrupt
Public Const COMADMIN_E_BADREGISTRYPROGID = (&H80110412)
'Unable to set required authentication level for update request
Public Const COMADMIN_E_AUTHENTICATIONLEVEL = (&H80110413)
'The identity or password set on the application is not valid
Public Const COMADMIN_E_USERPASSWDNOTVALID = (&H80110414)
'Application file CLSIDs or IIDs do not match corresponding DLLs
Public Const COMADMIN_E_CLSIDORIIDMISMATCH = (&H80110418)
'Interface information is either missing or changed
Public Const COMADMIN_E_REMOTEINTERFACE = (&H80110419)
'DllRegisterServer failed on component install
Public Const COMADMIN_E_DLLREGISTERSERVER = (&H8011041A)
'No server file share available
Public Const COMADMIN_E_NOSERVERSHARE = (&H8011041B)
'DLL could not be loaded
Public Const COMADMIN_E_DLLLOADFAILED = (&H8011041D)
'The registered TypeLib ID is not valid
Public Const COMADMIN_E_BADREGISTRYLIBID = (&H8011041E)
'Application install directory not found
Public Const COMADMIN_E_APPDIRNOTFOUND = (&H8011041F)
'Errors occurred while in the component registrar
Public Const COMADMIN_E_REGISTRARFAILED = (&H80110423)
'The file does not exist
Public Const COMADMIN_E_COMPFILE_DOESNOTEXIST = (&H80110424)
'The DLL could not be loaded
Public Const COMADMIN_E_COMPFILE_LOADDLLFAIL = (&H80110425)
'GetClassObject failed in the DLL
Public Const COMADMIN_E_COMPFILE_GETCLASSOBJ = (&H80110426)
'The DLL does not support the components listed in the TypeLib
Public Const COMADMIN_E_COMPFILE_CLASSNOTAVAIL = (&H80110427)
'The TypeLib could not be loaded
Public Const COMADMIN_E_COMPFILE_BADTLB = (&H80110428)
'The file does not contain components or component information
Public Const COMADMIN_E_COMPFILE_NOTINSTALLABLE = (&H80110429)
'Changes to this object and its sub-objects have been disabled
Public Const COMADMIN_E_NOTCHANGEABLE = (&H8011042A)
'The delete function has been disabled for this object
Public Const COMADMIN_E_NOTDELETEABLE = (&H8011042B)
'The server catalog version is not supported
Public Const COMADMIN_E_SESSION = (&H8011042C)
'The component move was disallowed, because the source or destination
'application is either a system application or currently locked against changes
Public Const COMADMIN_E_COMP_MOVE_LOCKED = (&H8011042D)
'The component move failed because the destination application no longer exists
Public Const COMADMIN_E_COMP_MOVE_BAD_DEST = (&H8011042E)
'The system was unable to register the TypeLib
Public Const COMADMIN_E_REGISTERTLB = (&H80110430)
'This operation can not be performed on the system application
Public Const COMADMIN_E_SYSTEMAPP = (&H80110433)
'The component registrar referenced in this file is not available
Public Const COMADMIN_E_COMPFILE_NOREGISTRAR = (&H80110434)
'A component in the same DLL is already installed
Public Const COMADMIN_E_COREQCOMPINSTALLED = (&H80110435)
'The service is not installed
Public Const COMADMIN_E_SERVICENOTINSTALLED = (&H80110436)
'One or more property settings are either invalid or in conflict with each other
Public Const COMADMIN_E_PROPERTYSAVEFAILED = (&H80110437)
'The object you are attempting to add or rename already exists
Public Const COMADMIN_E_OBJECTEXISTS = (&H80110438)
'The component already exists
Public Const COMADMIN_E_COMPONENTEXISTS = (&H80110439)
'The registration file is corrupt
Public Const COMADMIN_E_REGFILE_CORRUPT = (&H8011043B)
'The property value is too large
Public Const COMADMIN_E_PROPERTY_OVERFOW = (&H8011043C)
'Object was not found in registry
Public Const COMADMIN_E_NOTINREGISTRY = (&H8011043E)
'This object is not poolable
Public Const COMADMIN_E_OBJECTNOTPOOLABLE = (&H8011043F)
'A CLSID with the same GUID as the new application ID is
'already installed on this machine
Public Const COMADMIN_E_APPLID_MATCHES_CLSID = (&H80110446)
'A role assigned to a component, interface, or method did not exist in the application
Public Const COMADMIN_E_ROLE_DOES_NOT_EXIST = (&H80110447)
'You must have components in an application in order to start the application
Public Const COMADMIN_E_START_APP_NEEDS_COMPONENTS = (&H80110448)
'This operation is not enabled on this platform
Public Const COMADMIN_E_REQUIRES_DIFFERENT_PLATFORM = (&H80110449)
'Application Proxy is not exportable
Public Const COMADMIN_E_CAN_NOT_EXPORT_APP_PROXY = (&H8011044A)
'Failed to start application because it is either a library application
'or an application proxy
Public Const COMADMIN_E_CAN_NOT_START_APP = (&H8011044B)
'System application is not exportable
Public Const COMADMIN_E_CAN_NOT_EXPORT_SYS_APP = (&H8011044C)
'Can not subscribe to this component (the component may have been imported)
Public Const COMADMIN_E_CANT_SUBSCRIBE_TO_COMPONENT = (&H8011044D)
'An event class cannot also be a subscriber component
Public Const COMADMIN_E_EVENTCLASS_CANT_BE_SUBSCRIBER = (&H8011044E)
'Library applications and application proxies are incompatible
Public Const COMADMIN_E_LIB_APP_PROXY_INCOMPATIBLE = (&H8011044F)
'This function is valid for the base partition only
Public Const COMADMIN_E_BASE_PARTITION_ONLY = (&H80110450)
'You cannot start an application that has been disabled
Public Const COMADMIN_E_START_APP_DISABLED = (&H80110451)
'The specified partition name is already in use on this computer
Public Const COMADMIN_E_CAT_DUPLICATE_PARTITION_NAME = (&H80110457)
'The specified partition name is invalid. Check that the name contains
'at least one visible character
Public Const COMADMIN_E_CAT_INVALID_PARTITION_NAME = (&H80110458)
'The partition cannot be deleted because it is the default partition
'for one or more users
Public Const COMADMIN_E_CAT_PARTITION_IN_USE = (&H80110459)
'The partition cannot be exported, because one or more components in
'the partition have the same file name
Public Const COMADMIN_E_FILE_PARTITION_DUPLICATE_FILES = (&H8011045A)
'Applications that contain one or more imported components cannot be
'installed into a non-base partition
Public Const COMADMIN_E_CAT_IMPORTED_COMPONENTS_NOT_ALLOWED = (&H8011045B)
'The application name is not unique and cannot be resolved to an application id
Public Const COMADMIN_E_AMBIGUOUS_APPLICATION_NAME = (&H8011045C)
'The partition name is not unique and cannot be resolved to a partition id
Public Const COMADMIN_E_AMBIGUOUS_PARTITION_NAME = (&H8011045D)
'The COM+ registry database has not been initialized
Public Const COMADMIN_E_REGDB_NOTINITIALIZED = (&H80110472)
'The COM+ registry database is not open
Public Const COMADMIN_E_REGDB_NOTOPEN = (&H80110473)
'The COM+ registry database detected a system error
Public Const COMADMIN_E_REGDB_SYSTEMERR = (&H80110474)
'The COM+ registry database is already running
Public Const COMADMIN_E_REGDB_ALREADYRUNNING = (&H80110475)
'This version of the COM+ registry database cannot be migrated
Public Const COMADMIN_E_MIG_VERSIONNOTSUPPORTED = (&H80110480)
'The schema version to be migrated could not be found in
'the COM+ registry database
Public Const COMADMIN_E_MIG_SCHEMANOTFOUND = (&H80110481)
'There was a type mismatch between binaries
Public Const COMADMIN_E_CAT_BITNESSMISMATCH = (&H80110482)
'A binary of unknown or invalid type was provided
Public Const COMADMIN_E_CAT_UNACCEPTABLEBITNESS = (&H80110483)
'There was a type mismatch between a binary and an application
Public Const COMADMIN_E_CAT_WRONGAPPBITNESS = (&H80110484)
'The application cannot be paused or resumed
Public Const COMADMIN_E_CAT_PAUSE_RESUME_NOT_SUPPORTED = (&H80110485)
'The COM+ Catalog Server threw an exception during execution
Public Const COMADMIN_E_CAT_SERVERFAULT = (&H80110486)

'COMPLUS Queued component errors


'Only COM+ Applications marked "queued" can be invoked using the "queue" moniker
Public Const COMQC_E_APPLICATION_NOT_QUEUED = (&H80110600)
'At least one interface must be marked "queued" in order to create
'a queued component instance with the "queue" moniker
Public Const COMQC_E_NO_QUEUEABLE_INTERFACES = (&H80110601)
'MSMQ is required for the requested operation and is not installed
Public Const COMQC_E_QUEUING_SERVICE_NOT_AVAILABLE = (&H80110602)
'Unable to marshal an interface that does not support IPersistStream
Public Const COMQC_E_NO_IPERSISTSTREAM = (&H80110603)
'The message is improperly formatted or was damaged in transit
Public Const COMQC_E_BAD_MESSAGE = (&H80110604)
'An unauthenticated message was received by an application that accepts
'only authenticated messages
Public Const COMQC_E_UNAUTHENTICATED = (&H80110605)
'The message was requeued or moved by a user not in the "QC Trusted User" role
Public Const COMQC_E_UNTRUSTED_ENQUEUER = (&H80110606)

'The range &H700-&H7ff is reserved for MSDTC errors.


'Cannot create a duplicate resource of type Distributed Transaction Coordinator
Public Const MSDTC_E_DUPLICATE_RESOURCE = (&H80110701)

'More COMADMIN errors from &H8**


'One of the objects being inserted or updated does not belong to a valid
'parent collection
Public Const COMADMIN_E_OBJECT_PARENT_MISSING = (&H80110808)
'One of the specified objects cannot be found
Public Const COMADMIN_E_OBJECT_DOES_NOT_EXIST = (&H80110809)
'The specified application is not currently running
Public Const COMADMIN_E_APP_NOT_RUNNING = (&H8011080A)
'The partition(s) specified are not valid.
Public Const COMADMIN_E_INVALID_PARTITION = (&H8011080B)
'COM+ applications that run as NT service may not be pooled or recycled
Public Const COMADMIN_E_SVCAPP_NOT_POOLABLE_OR_RECYCLABLE = (&H8011080D)
'One or more users are already assigned to a local partition set.
Public Const COMADMIN_E_USER_IN_SET = (&H8011080E)
'Library applications may not be recycled.
Public Const COMADMIN_E_CANTRECYCLELIBRARYAPPS = (&H8011080F)
'Applications running as NT services may not be recycled.
Public Const COMADMIN_E_CANTRECYCLESERVICEAPPS = (&H80110811)
'The process has already been recycled.
Public Const COMADMIN_E_PROCESSALREADYRECYCLED = (&H80110812)
'A paused process may not be recycled.
Public Const COMADMIN_E_PAUSEDPROCESSMAYNOTBERECYCLED = (&H80110813)
'Library applications may not be NT services.
Public Const COMADMIN_E_CANTMAKEINPROCSERVICE = (&H80110814)
'The ProgID provided to the copy operation is invalid. The ProgID is in use
'by another registered CLSID.
Public Const COMADMIN_E_PROGIDINUSEBYCLSID = (&H80110815)
'The partition specified as default is not a member of the partition set.
Public Const COMADMIN_E_DEFAULT_PARTITION_NOT_IN_SET = (&H80110816)
'A recycled process may not be paused.
Public Const COMADMIN_E_RECYCLEDPROCESSMAYNOTBEPAUSED = (&H80110817)
'Access to the specified partition is denied.
Public Const COMADMIN_E_PARTITION_ACCESSDENIED = (&H80110818)
'Only Application Files (*.MSI files) can be installed into partitions.
Public Const COMADMIN_E_PARTITION_MSI_ONLY = (&H80110819)
'Applications containing one or more legacy components may not be
'exported to 1.0 format.
Public Const COMADMIN_E_LEGACYCOMPS_NOT_ALLOWED_IN_1_0_FORMAT = (&H8011081A)
'Legacy components may not exist in non-base partitions.
Public Const COMADMIN_E_LEGACYCOMPS_NOT_ALLOWED_IN_NONBASE_PARTITIONS = (&H8011081B)
'A component cannot be moved (or copied) from the System Application,
'an application proxy or a non-changeable application
Public Const COMADMIN_E_COMP_MOVE_SOURCE = (&H8011081C)
'A component cannot be moved (or copied) to the System Application,
'an application proxy or a non-changeable application
Public Const COMADMIN_E_COMP_MOVE_DEST = (&H8011081D)
'A private component cannot be moved (or copied) to a library
'application or to the base partition
Public Const COMADMIN_E_COMP_MOVE_PRIVATE = (&H8011081E)
'The Base Application Partition exists in all partition sets
'and cannot be removed.
Public Const COMADMIN_E_BASEPARTITION_REQUIRED_IN_SET = (&H8011081F)
'Alas, Event Class components cannot be aliased.
Public Const COMADMIN_E_CANNOT_ALIAS_EVENTCLASS = (&H80110820)
'Access is denied because the component is private.
Public Const COMADMIN_E_PRIVATE_ACCESSDENIED = (&H80110821)
'The specified SAFER level is invalid.
Public Const COMADMIN_E_SAFERINVALID = (&H80110822)
'The specified user cannot write to the system registry
Public Const COMADMIN_E_REGISTRY_ACCESSDENIED = (&H80110823)
'COM+ partitions are currently disabled.
Public Const COMADMIN_E_PARTITIONS_DISABLED = (&H80110824)

'Generic test for success on any status value (non-negative numbers
'indicate success).
Public Function SUCCEEDED(Status) As Boolean
  SUCCEEDED = (Status) >= 0
End Function

'and the inverse
Public Function FAILED(Status) As Boolean
  FAILED = ((Status) < 0)
End Function

'Generic test for error on any status value.
Public Function IS_ERROR(Status) As Boolean
  IS_ERROR = (((Status) / &H80000000) > SEVERITY_ERROR)
End Function

'Return the code

Public Function HRESULT_CODE(hr) As Long
  HRESULT_CODE = ((hr) And &HFFFF)
End Function

Public Function SCODE_CODE(sc) As Long
  SCODE_CODE = ((sc) And &HFFFF)
End Function


'Return the facility

Public Function HRESULT_FACILITY(hr) As Long
  HRESULT_FACILITY = (((hr) / &H10000) And &H1FFF)
End Function

Public Function SCODE_FACILITY(sc) As Long
  SCODE_FACILITY = (((sc) / &H10000) And &H1FFF)
End Function


'Return the severity

'Public Function HRESULT_SEVERITY(hr) =  (((hr) >> 31) & &H1)
'Public Function SCODE_SEVERITY(sc) =    (((sc) >> 31) & &H1)

'Create an HRESULT value from component pieces

'Public Function MAKE_HRESULT(sev,fac,code) = \
'    ((HRESULT) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )
'Public Function MAKE_SCODE(sev,fac,code) = \
'    ((SCODE) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )

'-------------------------------------------------------------------------------
'__HRESULT_FROM_WIN32 will always be a macro.
'The goal will be to enable INLINE_HRESULT_FROM_WIN32 all the time,
'but there's too much code to change to do that at this time.
Public Function HRESULT_FROM_WIN32(x) ' As HRESULT
  If (x <= 0) Then
    HRESULT_FROM_WIN32 = x
  Else
    HRESULT_FROM_WIN32 = ((((x) And &HFFFF) Or (FACILITY_WIN32 * &H10000) Or &H80000000))
  End If
End Function
'-------------------------------------------------------------------------------
'Since these error codes aren't in the standard Win32 range (i.e., 0-64K), define a
'macro to map either Win32 or SetupAPI error codes into an HRESULT.
Public Function HRESULT_FROM_SETUPAPI(x) ' As HRESULT
  If ((x) And (APPLICATION_ERROR_MASK Or ERROR_SEVERITY_ERROR)) = _
       (APPLICATION_ERROR_MASK Or ERROR_SEVERITY_ERROR) Then
    HRESULT_FROM_SETUPAPI = ((((x) And &HFFFF) Or (FACILITY_SETUPAPI * &H10000) Or &H80000000))
  Else
    HRESULT_FROM_SETUPAPI = HRESULT_FROM_WIN32(x)
  End If
End Function

'Map an NT status value into a HRESULT

'Public Function HRESULT_FROM_NT(x) =      ((HRESULT) ((x) | FACILITY_NT_BIT))


'===============================================================================
'*******************************************************************************
'$Log:
' 1    Biblioteka1.0         2007-05-10 11:10:47  Darko Kolakovic
'$
'*******************************************************************************
