/*$Workfile: KDbgError.c$: implementation file
  $Revision: 4$ $Date: 2004-11-09 18:45:08$
  $Author: Darko Kolakovic$

  Dumps error code values
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DbgErrorCode(const Err nErrorCode);
void DbgErrorDlk(const Err nErrorCode);
void DbgErrorINet(const Err nErrorCode);
void DbgErrorBlth(const Err nErrorCode);
void DbgErrorSsl(const Err nErrorCode);
void DbgErrorHost(const Err nErrorCode);
void DbgErrorPwr(const Err nErrorCode);
void DbgErrorCnc(const Err nErrorCode);
void DbgErrorLz(const Err nErrorCode);
void DbgErrorSms(const Err nErrorCode);
void DbgErrorExp(const Err nErrorCode);
void DbgErrorVfs(const Err nErrorCode);
void DbgErrorPdi(const Err nErrorCode);
void DbgErrorUda(const Err nErrorCode);
void DbgErrorCpm(const Err nErrorCode);
void DbgErrorTel(const Err nErrorCode);

/*----------------------------------------------------------------------------*/
/*Dump Palm OS API error codes.

  See also: Palm OS Programmer's API Reference: Appendix D. Palm OS Error Codes

  Note: Palm OS specific (PalmOS).
 */
void DbgErrorCode(const Err nErrorCode //[in] Palm OS API error code
                 )
{
  /*Dump most of the error codes used by the Palm OS*/
switch (nErrorCode)
  {
  case errNone:                              TRACE0(_T("errNone")                              ); break;/*0x0000 No error*/
  //case hostErrBase:                          TRACE0(_T("hostErrBase")                          ); break;/*0x0000 No error*/
  case memErrorClass:                        TRACE0(_T("memErrorClass")                        ); break;/*0x0100 Memory Manager errors*/
  case memErrChunkLocked:                    TRACE0(_T("memErrChunkLocked")                    ); break;/*0x0101 The associated memory chunk is locked.*/
  case memErrNotEnoughSpace:                 TRACE0(_T("memErrNotEnoughSpace")                 ); break;/*0x0102 A memory error occurred.*/
  case memErrInvalidParam:                   TRACE0(_T("memErrInvalidParam")                   ); break;/*0x0103 One of the function's parameters is invalid or the requested size is too big.*/
  case memErrChunkNotLocked:                 TRACE0(_T("memErrChunkNotLocked")                 ); break;/*0x0104*/
  case memErrCardNotPresent:                 TRACE0(_T("memErrCardNotPresent")                 ); break;/*0x0105 The specified card can't be found.*/
  case memErrNoCardHeader:                   TRACE0(_T("memErrNoCardHeader")                   ); break;/*0x0106*/
  case memErrInvalidStoreHeader:             TRACE0(_T("memErrInvalidStoreHeader")             ); break;/*0x0107 The specified card has no storage RAM.*/
  case memErrRAMOnlyCard:                    TRACE0(_T("memErrRAMOnlyCard")                    ); break;/*0x0108 The specified card has no storage RAM.*/
  case memErrWriteProtect:                   TRACE0(_T("memErrWriteProtect")                   ); break;/*0x0109*/
  case memErrNoRAMOnCard:                    TRACE0(_T("memErrNoRAMOnCard")                    ); break;/*0x010a*/
  case memErrNoStore:                        TRACE0(_T("memErrNoStore")                        ); break;/*0x010b*/
  case memErrROMOnlyCard:                    TRACE0(_T("memErrROMOnlyCard")                    ); break;/*0x010c*/
  case dmErrorClass:                         TRACE0(_T("dmErrorClass")                         ); break;/*0x0200 Data Manager errors*/
  case dmErrMemError:                        TRACE0(_T("dmErrMemError")                        ); break;/*0x0201 A memory error occurred.*/
  case dmErrIndexOutOfRange:                 TRACE0(_T("dmErrIndexOutOfRange")                 ); break;/*0x0202 The specified index is out of range.*/
  case dmErrInvalidParam:                    TRACE0(_T("dmErrInvalidParam")                    ); break;/*0x0203 The function received an invalid parameter.*/
  case dmErrReadOnly:                        TRACE0(_T("dmErrReadOnly")                        ); break;/*0x0204 You've attempted to write to or modify a database that is in read-only mode.*/
  case dmErrDatabaseOpen:                    TRACE0(_T("dmErrDatabaseOpen")                    ); break;/*0x0205 The function cannot be performed on an open database, and the database is open.*/
  case dmErrCantOpen:                        TRACE0(_T("dmErrCantOpen")                        ); break;/*0x0206 The database cannot be opened.*/
  case dmErrCantFind:                        TRACE0(_T("dmErrCantFind")                        ); break;/*0x0207 The specified resource can't be found.*/
  case dmErrRecordInWrongCard:               TRACE0(_T("dmErrRecordInWrongCard")               ); break;/*0x0208 You've attempted to attach a record to a database when the record and database reside on different memory cards.*/
  case dmErrCorruptDatabase:                 TRACE0(_T("dmErrCorruptDatabase")                 ); break;/*0x0209 The database is corrupted.*/
  case dmErrRecordDeleted:                   TRACE0(_T("dmErrRecordDeleted")                   ); break;/*0x020a The record has been deleted.*/
  case dmErrRecordArchived:                  TRACE0(_T("dmErrRecordArchived")                  ); break;/*0x020b The function requires that the record not be archived, but it is.*/
  case dmErrNotRecordDB:                     TRACE0(_T("dmErrNotRecordDB")                     ); break;/*0x020c You've attempted to perform a record function on a resource database.*/
  case dmErrNotResourceDB:                   TRACE0(_T("dmErrNotResourceDB")                   ); break;/*0x020d You've attempted to perform a resource manager function on a record database.*/
  case dmErrROMBased:                        TRACE0(_T("dmErrROMBased")                        ); break;/*0x020e You've attempted to delete or modify a ROM-based database.*/
  case dmErrRecordBusy:                      TRACE0(_T("dmErrRecordBusy")                      ); break;/*0x020f The function requires that the record not be busy, but it is.*/
  case dmErrResourceNotFound:                TRACE0(_T("dmErrResourceNotFound")                ); break;/*0x0210 The resource can't be found.*/
  case dmErrNoOpenDatabase:                  TRACE0(_T("dmErrNoOpenDatabase")                  ); break;/*0x0211 The function is to search all open databases, but there are none.*/
  case dmErrInvalidCategory:                 TRACE0(_T("dmErrInvalidCategory")                 ); break;/*0x0212*/
  case dmErrNotValidRecord:                  TRACE0(_T("dmErrNotValidRecord")                  ); break;/*0x0213 The record handle is invalid.*/
  case dmErrWriteOutOfBounds:                TRACE0(_T("dmErrWriteOutOfBounds")                ); break;/*0x0214 A write operation exceeded the bounds of the record.*/
  case dmErrSeekFailed:                      TRACE0(_T("dmErrSeekFailed")                      ); break;/*0x0215 The operation of seeking the next record in the category failed.*/
  case dmErrAlreadyOpenForWrites:            TRACE0(_T("dmErrAlreadyOpenForWrites")            ); break;/*0x0216 The database is already open with write access.*/
  case dmErrOpenedByAnotherTask:             TRACE0(_T("dmErrOpenedByAnotherTask")             ); break;/*0x0217 You've attempted to open a database that another task already has open.*/
  case dmErrUniqueIDNotFound:                TRACE0(_T("dmErrUniqueIDNotFound")                ); break;/*0x0218 A record with the specified unique ID can't be found.*/
  case dmErrAlreadyExists:                   TRACE0(_T("dmErrAlreadyExists")                   ); break;/*0x0219 Another database with the same name already exists in RAM store.*/
  case dmErrInvalidDatabaseName:             TRACE0(_T("dmErrInvalidDatabaseName")             ); break;/*0x021a The name you've specified for the database is invalid.*/
  case dmErrDatabaseProtected:               TRACE0(_T("dmErrDatabaseProtected")               ); break;/*0x021b The database is marked as protected.*/
  case dmErrDatabaseNotProtected:            TRACE0(_T("dmErrDatabaseNotProtected")            ); break;/*0x021c DmDatabaseProtect() failed to protect the specified database.*/
  case serErrorClass:                        TRACE0(_T("serErrorClass")                        ); break;/*0x0300 Serial Manager errors*/
  case serErrBadParam:                       TRACE0(_T("serErrBadParam")                       ); break;/*0x0301 One of the function's parameters is invalid. See the Serial Manager function's description for additional detail.*/
  case serErrBadPort:                        TRACE0(_T("serErrBadPort")                        ); break;/*0x0302 The specified port doesn't exist.*/
  case serErrNoMem:                          TRACE0(_T("serErrNoMem")                          ); break;/*0x0303*/
  case serErrBadConnID:                      TRACE0(_T("serErrBadConnID")                      ); break;/*0x0304*/
  case serErrTimeOut:                        TRACE0(_T("serErrTimeOut")                        ); break;/*0x0305 Unable to receive data within the specified timeout period.*/
  case serErrLineErr:                        TRACE0(_T("serErrLineErr")                        ); break;/*0x0306 A line error occurred during the receipt of data. Use SrmGetStatus() to obtain the exact line error.*/
  case serErrAlreadyOpen:                    TRACE0(_T("serErrAlreadyOpen")                    ); break;/*0x0307 The Serial Manager already has a port open, or the specified port already has an installed foreground or background owner.*/
  case serErrStillOpen:                      TRACE0(_T("serErrStillOpen")                      ); break;/*0x0308*/
  case serErrNotOpen:                        TRACE0(_T("serErrNotOpen")                        ); break;/*0x0309 The serial port is not open.*/
  case serErrNotSupported:                   TRACE0(_T("serErrNotSupported")                   ); break;/*0x030a The specified port is not the foreground port, the specified op code is not supported in the current configuration, the port is a yielded port, or the feature isn't supported by the hardware.*/
  case serErrNoDevicesAvail:                 TRACE0(_T("serErrNoDevicesAvail")                 ); break;/*0x030b No serial devices could be found.*/
  case serErrConfigurationFailed:            TRACE0(_T("serErrConfigurationFailed")            ); break;/*0x030c The port needs time to configure, and the configuration has failed.*/
  case slkErrorClass:                        TRACE0(_T("slkErrorClass")                        ); break;/*0x0400 Serial Link Manager errors*/
  case slkErrChecksum:                       TRACE0(_T("slkErrChecksum")                       ); break;/*0x0401*/
  case slkErrFormat:                         TRACE0(_T("slkErrFormat")                         ); break;/*0x0402*/
  case slkErrBuffer:                         TRACE0(_T("slkErrBuffer")                         ); break;/*0x0403*/
  case slkErrTimeOut:                        TRACE0(_T("slkErrTimeOut")                        ); break;/*0x0404*/
  case slkErrHandle:                         TRACE0(_T("slkErrHandle")                         ); break;/*0x0405*/
  case slkErrBodyLimit:                      TRACE0(_T("slkErrBodyLimit")                      ); break;/*0x0406*/
  case slkErrTransId:                        TRACE0(_T("slkErrTransId")                        ); break;/*0x0407*/
  case slkErrResponse:                       TRACE0(_T("slkErrResponse")                       ); break;/*0x0408*/
  case slkErrNoDefaultProc:                  TRACE0(_T("slkErrNoDefaultProc")                  ); break;/*0x0409*/
  case slkErrWrongPacketType:                TRACE0(_T("slkErrWrongPacketType")                ); break;/*0x040a*/
  case slkErrBadParam:                       TRACE0(_T("slkErrBadParam")                       ); break;/*0x040b*/
  case slkErrAlreadyOpen:                    TRACE0(_T("slkErrAlreadyOpen")                    ); break;/*0x040c*/
  case slkErrOutOfSockets:                   TRACE0(_T("slkErrOutOfSockets")                   ); break;/*0x040d*/
  case slkErrSocketNotOpen:                  TRACE0(_T("slkErrSocketNotOpen")                  ); break;/*0x040e*/
  case slkErrWrongDestSocket:                TRACE0(_T("slkErrWrongDestSocket")                ); break;/*0x040f*/
  case slkErrWrongPktType:                   TRACE0(_T("slkErrWrongPktType")                   ); break;/*0x0410*/
  case slkErrBusy:                           TRACE0(_T("slkErrBusy")                           ); break;/*0x0411*/
  case slkErrNotOpen:                        TRACE0(_T("slkErrNotOpen")                        ); break;/*0x0412*/
  case sysErrorClass:                        TRACE0(_T("sysErrorClass")                        ); break;/*0x0500 System Manager errors*/
  case sysErrTimeout:                        TRACE0(_T("sysErrTimeout")                        ); break;/*0x0501*/
  case sysErrParamErr:                       TRACE0(_T("sysErrParamErr")                       ); break;/*0x0502*/
  case sysErrNoFreeResource:                 TRACE0(_T("sysErrNoFreeResource")                 ); break;/*0x0503*/
  case sysErrNoFreeRAM:                      TRACE0(_T("sysErrNoFreeRAM")                      ); break;/*0x0504*/
  case sysErrNotAllowed:                     TRACE0(_T("sysErrNotAllowed")                     ); break;/*0x0505*/
  case sysErrSemInUse:                       TRACE0(_T("sysErrSemInUse")                       ); break;/*0x0506*/
  case sysErrInvalidID:                      TRACE0(_T("sysErrInvalidID")                      ); break;/*0x0507*/
  case sysErrOutOfOwnerIDs:                  TRACE0(_T("sysErrOutOfOwnerIDs")                  ); break;/*0x0508*/
  case sysErrNoFreeLibSlots:                 TRACE0(_T("sysErrNoFreeLibSlots")                 ); break;/*0x0509*/
  case sysErrLibNotFound:                    TRACE0(_T("sysErrLibNotFound")                    ); break;/*0x050a The Exchange Manager couldn't find library or application to respond to URL.*/
  case sysErrDelayWakened:                   TRACE0(_T("sysErrDelayWakened")                   ); break;/*0x050b*/
  case sysErrRomIncompatible:                TRACE0(_T("sysErrRomIncompatible")                ); break;/*0x050c*/
  case sysErrBufTooSmall:                    TRACE0(_T("sysErrBufTooSmall")                    ); break;/*0x050d*/
  case sysErrPrefNotFound:                   TRACE0(_T("sysErrPrefNotFound")                   ); break;/*0x050e*/
  case sysNotifyErrEntryNotFound:            TRACE0(_T("sysNotifyErrEntryNotFound")            ); break;/*0x0510*/
  case sysNotifyErrDuplicateEntry:           TRACE0(_T("sysNotifyErrDuplicateEntry")           ); break;/*0x0511*/
  case sysNotifyErrBroadcastBusy:            TRACE0(_T("sysNotifyErrBroadcastBusy")            ); break;/*0x0513*/
  case sysNotifyErrBroadcastCancelled:       TRACE0(_T("sysNotifyErrBroadcastCancelled")       ); break;/*0x0514*/
  case sysErrMbId:                           TRACE0(_T("sysErrMbId")                           ); break;/*0x0515*/
  case sysErrMbNone:                         TRACE0(_T("sysErrMbNone")                         ); break;/*0x0516*/
  case sysErrMbBusy:                         TRACE0(_T("sysErrMbBusy")                         ); break;/*0x0517*/
  case sysErrMbFull:                         TRACE0(_T("sysErrMbFull")                         ); break;/*0x0518*/
  case sysErrMbDepth:                        TRACE0(_T("sysErrMbDepth")                        ); break;/*0x0519*/
  case sysErrMbEnv:                          TRACE0(_T("sysErrMbEnv")                          ); break;/*0x051a*/
  case sysNotifyErrQueueFull:                TRACE0(_T("sysNotifyErrQueueFull")                ); break;/*0x051b*/
  case sysNotifyErrQueueEmpty:               TRACE0(_T("sysNotifyErrQueueEmpty")               ); break;/*0x051c*/
  case sysNotifyErrNoStackSpace:             TRACE0(_T("sysNotifyErrNoStackSpace")             ); break;/*0x051d*/
  case sysErrNotInitialized:                 TRACE0(_T("sysErrNotInitialized")                 ); break;/*0x051e*/
  case sysErrNotAsleep:                      TRACE0(_T("sysErrNotAsleep")                      ); break;/*0x051f*/
  case sysErrNotAsleepN:                     TRACE0(_T("sysErrNotAsleepN")                     ); break;/*0x0520*/
  case fplErrorClass:                        TRACE0(_T("fplErrorClass")                        ); break;/*0x0600 Old Floating Point Library errors*/
  case flpErrorClass:                        TRACE0(_T("flpErrorClass")                        ); break;/*0x0680 Floating Point Library errors*/
  case flpErrOutOfRange:                     TRACE0(_T("flpErrOutOfRange")                     ); break;/*0x0681*/
  case evtErrorClass:                        TRACE0(_T("evtErrorClass")                        ); break;/*0x0700 System Event Manager errors*/
  case evtErrParamErr:                       TRACE0(_T("evtErrParamErr")                       ); break;/*0x0701*/
  case evtErrQueueFull:                      TRACE0(_T("evtErrQueueFull")                      ); break;/*0x0702*/
  case evtErrQueueEmpty:                     TRACE0(_T("evtErrQueueEmpty")                     ); break;/*0x0703*/
  case sndErrorClass:                        TRACE0(_T("sndErrorClass")                        ); break;/*0x0800 Sound Manager errors*/
  case sndErrBadParam:                       TRACE0(_T("sndErrBadParam")                       ); break;/*0x0801*/
  case sndErrBadChannel:                     TRACE0(_T("sndErrBadChannel")                     ); break;/*0x0802*/
  case sndErrMemory:                         TRACE0(_T("sndErrMemory")                         ); break;/*0x0803*/
  case sndErrOpen:                           TRACE0(_T("sndErrOpen")                           ); break;/*0x0804*/
  case sndErrQFull:                          TRACE0(_T("sndErrQFull")                          ); break;/*0x0805*/
  case sndErrQEmpty:                         TRACE0(_T("sndErrQEmpty")                         ); break;/*0x0806*/
  case sndErrFormat:                         TRACE0(_T("sndErrFormat")                         ); break;/*0x0807*/
  case sndErrBadStream:                      TRACE0(_T("sndErrBadStream")                      ); break;/*0x0808*/
  case sndErrInterrupted:                    TRACE0(_T("sndErrInterrupted")                    ); break;/*0x0809*/
  case sndErrNotImpl:                        TRACE0(_T("sndErrNotImpl")                        ); break;/*0x080a*/
  case sndErrInvalidStream:                  TRACE0(_T("sndErrInvalidStream")                  ); break;/*0x080b*/
  case almErrorClass:                        TRACE0(_T("almErrorClass")                        ); break;/*0x0900 Alarm Manager errors*/
  case almErrMemory:                         TRACE0(_T("almErrMemory")                         ); break;/*0x0901 There is insufficient memory to complete the requested operation.*/
  case almErrFull:                           TRACE0(_T("almErrFull")                           ); break;/*0x0902 The alarm table is full.*/
  case timErrorClass:                        TRACE0(_T("timErrorClass")                        ); break;/*0x0a00 Time Manager errors*/
  case timErrMemory:                         TRACE0(_T("timErrMemory")                         ); break;/*0x0a01*/
  case penErrorClass:                        TRACE0(_T("penErrorClass")                        ); break;/*0x0b00 Pen Manager errors*/
  case penErrBadParam:                       TRACE0(_T("penErrBadParam")                       ); break;/*0x0b01*/
  case penErrIgnorePoint:                    TRACE0(_T("penErrIgnorePoint")                    ); break;/*0x0b02*/
  case ftrErrorClass:                        TRACE0(_T("ftrErrorClass")                        ); break;/*0x0c00 Feature Manager errors*/
  case ftrErrInvalidParam:                   TRACE0(_T("ftrErrInvalidParam")                   ); break;/*0x0c01*/
  case ftrErrNoSuchFeature:                  TRACE0(_T("ftrErrNoSuchFeature")                  ); break;/*0x0c02 The specified feature number doesn't exist for the specified creator, the index is out of range, or some other error exists. See the Feature Manager function's description for more details.*/
  case ftrErrAlreadyExists:                  TRACE0(_T("ftrErrAlreadyExists")                  ); break;/*0x0c03*/
  case ftrErrROMBased:                       TRACE0(_T("ftrErrROMBased")                       ); break;/*0x0c04*/
  case ftrErrInternalErr:                    TRACE0(_T("ftrErrInternalErr")                    ); break;/*0x0c05*/
  case cmpErrorClass:                        TRACE0(_T("cmpErrorClass")                        ); break;/*0x0d00 Connection Manager (HotSync) errors*/

  case padErrorClass:                        TRACE0(_T("padErrorClass")                        ); break;/*0x0f00 PAD Manager errors*/
  case grfErrorClass:                        TRACE0(_T("grfErrorClass")                        ); break;/*0x1000 Graffiti Manager errors*/
  case grfErrBadParam:                       TRACE0(_T("grfErrBadParam")                       ); break;/*0x1001*/
  case grfErrPointBufferFull:                TRACE0(_T("_grfErrPointBufferFull")               ); break;/*0x1002*/
  case grfErrNoGlyphTable:                   TRACE0(_T("grfErrNoGlyphTable")                   ); break;/*0x1003*/
  case grfErrNoDictionary:                   TRACE0(_T("grfErrNoDictionary")                   ); break;/*0x1004*/
  case grfErrNoMapping:                      TRACE0(_T("grfErrNoMapping")                      ); break;/*0x1005*/
  case grfErrMacroNotFound:                  TRACE0(_T("grfErrMacroNotFound")                  ); break;/*0x1006*/
  case grfErrDepthTooDeep:                   TRACE0(_T("grfErrDepthTooDeep")                   ); break;/*0x1007*/
  case grfErrMacroPtrTooSmall:               TRACE0(_T("grfErrMacroPtrTooSmall")               ); break;/*0x1008*/
  case grfErrNoMacros:                       TRACE0(_T("grfErrNoMacros")                       ); break;/*0x1009*/
  case grfErrGenericHWRErrBase:              TRACE0(_T("grfErrGenericHWRErrBase")              ); break;/*0x1010*/
  case grfErrMacroIncomplete:                TRACE0(_T("grfErrMacroIncomplete")                ); break;/*0x1081*/
  case grfErrBranchNotFound:                 TRACE0(_T("grfErrBranchNotFound")                 ); break;/*0x1082*/
  case mdmErrorClass:                        TRACE0(_T("mdmErrorClass")                        ); break;/*0x1100 Modem Manager errors*/
  case mdmErrNoTone:                         TRACE0(_T("mdmErrNoTone")                         ); break;/*0x1101*/
  case mdmErrNoDCD:                          TRACE0(_T("mdmErrNoDCD")                          ); break;/*0x1102*/
  case mdmErrBusy:                           TRACE0(_T("mdmErrBusy")                           ); break;/*0x1103*/
  case mdmErrUserCan:                        TRACE0(_T("mdmErrUserCan")                        ); break;/*0x1104*/
  case mdmErrCmdError:                       TRACE0(_T("mdmErrCmdError")                       ); break;/*0x1105*/
  case mdmErrNoModem:                        TRACE0(_T("mdmErrNoModem")                        ); break;/*0x1106*/
  case mdmErrMemory:                         TRACE0(_T("mdmErrMemory")                         ); break;/*0x1107*/
  case mdmErrPrefs:                          TRACE0(_T("mdmErrPrefs")                          ); break;/*0x1108*/
  case mdmErrDial:                           TRACE0(_T("mdmErrDial")                           ); break;/*0x1109*/
  case mdmErrNoPhoneNum:                     TRACE0(_T("mdmErrNoPhoneNum")                     ); break;/*0x110a*/
  case netErrorClass:                        TRACE0(_T("netErrorClass")                        ); break;/*0x1200 Net Library errors*/
  case netErrAlreadyOpen:                    TRACE0(_T("netErrAlreadyOpen")                    ); break;/*0x1201*/
  case netErrNotOpen:                        TRACE0(_T("netErrNotOpen")                        ); break;/*0x1202*/
  case netErrStillOpen:                      TRACE0(_T("netErrStillOpen")                      ); break;/*0x1203*/
  case netErrParamErr:                       TRACE0(_T("netErrParamErr")                       ); break;/*0x1204*/
  case netErrNoMoreSockets:                  TRACE0(_T("netErrNoMoreSockets")                  ); break;/*0x1205*/
  case netErrOutOfResources:                 TRACE0(_T("netErrOutOfResources")                 ); break;/*0x1206*/
  case netErrOutOfMemory:                    TRACE0(_T("netErrOutOfMemory")                    ); break;/*0x1207*/
  case netErrSocketNotOpen:                  TRACE0(_T("netErrSocketNotOpen")                  ); break;/*0x1208*/
  case netErrSocketBusy:                     TRACE0(_T("netErrSocketBusy")                     ); break;/*0x1209*/
  case netErrMessageTooBig:                  TRACE0(_T("netErrMessageTooBig")                  ); break;/*0x120a*/
  case netErrSocketNotConnected:             TRACE0(_T("netErrSocketNotConnected")             ); break;/*0x120b*/
  case netErrNoInterfaces:                   TRACE0(_T("netErrNoInterfaces")                   ); break;/*0x120c*/
  case netErrBufTooSmall:                    TRACE0(_T("netErrBufTooSmall")                    ); break;/*0x120d*/
  case netErrUnimplemented:                  TRACE0(_T("netErrUnimplemented")                  ); break;/*0x120e*/
  case netErrPortInUse:                      TRACE0(_T("netErrPortInUse")                      ); break;/*0x120f*/
  case netErrQuietTimeNotElapsed:            TRACE0(_T("netErrQuietTimeNotElapsed")            ); break;/*0x1210*/
  case netErrInternal:                       TRACE0(_T("netErrInternal")                       ); break;/*0x1211*/
  case netErrTimeout:                        TRACE0(_T("netErrTimeout")                        ); break;/*0x1212*/
  case netErrSocketAlreadyConnected:         TRACE0(_T("netErrSocketAlreadyConnected")         ); break;/*0x1213*/
  case netErrSocketClosedByRemote:           TRACE0(_T("netErrSocketClosedByRemote")           ); break;/*0x1214*/
  case netErrOutOfCmdBlocks:                 TRACE0(_T("netErrOutOfCmdBlocks")                 ); break;/*0x1215*/
  case netErrWrongSocketType:                TRACE0(_T("netErrWrongSocketType")                ); break;/*0x1216*/
  case netErrSocketNotListening:             TRACE0(_T("netErrSocketNotListening")             ); break;/*0x1217*/
  case netErrUnknownSetting:                 TRACE0(_T("netErrUnknownSetting")                 ); break;/*0x1218*/
  case netErrInvalidSettingSize:             TRACE0(_T("netErrInvalidSettingSize")             ); break;/*0x1219*/
  case netErrPrefNotFound:                   TRACE0(_T("netErrPrefNotFound")                   ); break;/*0x121a*/
  case netErrInvalidInterface:               TRACE0(_T("netErrInvalidInterface")               ); break;/*0x121b*/
  case netErrInterfaceNotFound:              TRACE0(_T("netErrInterfaceNotFound")              ); break;/*0x121c*/
  case netErrTooManyInterfaces:              TRACE0(_T("netErrTooManyInterfaces")              ); break;/*0x121d*/
  case netErrBufWrongSize:                   TRACE0(_T("netErrBufWrongSize")                   ); break;/*0x121e*/
  case netErrUserCancel:                     TRACE0(_T("netErrUserCancel")                     ); break;/*0x121f*/
  case netErrBadScript:                      TRACE0(_T("netErrBadScript")                      ); break;/*0x1220*/
  case netErrNoSocket:                       TRACE0(_T("netErrNoSocket")                       ); break;/*0x1221*/
  case netErrSocketRcvBufFull:               TRACE0(_T("netErrSocketRcvBufFull")               ); break;/*0x1222*/
  case netErrNoPendingConnect:               TRACE0(_T("netErrNoPendingConnect")               ); break;/*0x1223*/
  case netErrUnexpectedCmd:                  TRACE0(_T("netErrUnexpectedCmd")                  ); break;/*0x1224*/
  case netErrNoTCB:                          TRACE0(_T("netErrNoTCB")                          ); break;/*0x1225*/
  case netErrNilRemoteWindowSize:            TRACE0(_T("netErrNilRemoteWindowSize")            ); break;/*0x1226*/
  case netErrNoTimerProc:                    TRACE0(_T("netErrNoTimerProc")                    ); break;/*0x1227*/
  case netErrSocketInputShutdown:            TRACE0(_T("netErrSocketInputShutdown")            ); break;/*0x1228*/
  case netErrCmdBlockNotCheckedOut:          TRACE0(_T("netErrCmdBlockNotCheckedOut")          ); break;/*0x1229*/
  case netErrCmdNotDone:                     TRACE0(_T("netErrCmdNotDone")                     ); break;/*0x122a*/
  case netErrUnknownProtocol:                TRACE0(_T("netErrUnknownProtocol")                ); break;/*0x122b*/
  case netErrUnknownService:                 TRACE0(_T("netErrUnknownService")                 ); break;/*0x122c*/
  case netErrUnreachableDest:                TRACE0(_T("netErrUnreachableDest")                ); break;/*0x122d*/
  case netErrReadOnlySetting:                TRACE0(_T("netErrReadOnlySetting")                ); break;/*0x122e*/
  case netErrWouldBlock:                     TRACE0(_T("netErrWouldBlock")                     ); break;/*0x122f*/
  case netErrAlreadyInProgress:              TRACE0(_T("netErrAlreadyInProgress")              ); break;/*0x1230*/
  case netErrPPPTimeout:                     TRACE0(_T("netErrPPPTimeout")                     ); break;/*0x1231*/
  case netErrPPPBroughtDown:                 TRACE0(_T("netErrPPPBroughtDown")                 ); break;/*0x1232*/
  case netErrAuthFailure:                    TRACE0(_T("netErrAuthFailure")                    ); break;/*0x1233*/
  case netErrPPPAddressRefused:              TRACE0(_T("netErrPPPAddressRefused")              ); break;/*0x1234*/
  case netErrDNSNameTooLong:                 TRACE0(_T("netErrDNSNameTooLong")                 ); break;/*0x1235*/
  case netErrDNSBadName:                     TRACE0(_T("netErrDNSBadName")                     ); break;/*0x1236*/
  case netErrDNSBadArgs:                     TRACE0(_T("netErrDNSBadArgs")                     ); break;/*0x1237*/
  case netErrDNSLabelTooLong:                TRACE0(_T("netErrDNSLabelTooLong")                ); break;/*0x1238*/
  case netErrDNSAllocationFailure:           TRACE0(_T("netErrDNSAllocationFailure")           ); break;/*0x1239*/
  case netErrDNSTimeout:                     TRACE0(_T("netErrDNSTimeout")                     ); break;/*0x123a*/
  case netErrDNSUnreachable:                 TRACE0(_T("netErrDNSUnreachable")                 ); break;/*0x123b*/
  case netErrDNSFormat:                      TRACE0(_T("netErrDNSFormat")                      ); break;/*0x123c*/
  case netErrDNSServerFailure:               TRACE0(_T("netErrDNSServerFailure")               ); break;/*0x123d*/
  case netErrDNSNonexistantName:             TRACE0(_T("netErrDNSNonexistantName")             ); break;/*0x123e*/
  case netErrDNSNIY:                         TRACE0(_T("netErrDNSNIY")                         ); break;/*0x123f*/
  case netErrDNSRefused:                     TRACE0(_T("netErrDNSRefused")                     ); break;/*0x1240*/
  case netErrDNSImpossible:                  TRACE0(_T("netErrDNSImpossible")                  ); break;/*0x1241*/
  case netErrDNSNoRRS:                       TRACE0(_T("netErrDNSNoRRS")                       ); break;/*0x1242*/
  case netErrDNSAborted:                     TRACE0(_T("netErrDNSAborted")                     ); break;/*0x1243*/
  case netErrDNSBadProtocol:                 TRACE0(_T("netErrDNSBadProtocol")                 ); break;/*0x1244*/
  case netErrDNSTruncated:                   TRACE0(_T("netErrDNSTruncated")                   ); break;/*0x1245*/
  case netErrDNSNoRecursion:                 TRACE0(_T("netErrDNSNoRecursion")                 ); break;/*0x1246*/
  case netErrDNSIrrelevant:                  TRACE0(_T("netErrDNSIrrelevant")                  ); break;/*0x1247*/
  case netErrDNSNotInLocalCache:             TRACE0(_T("netErrDNSNotInLocalCache")             ); break;/*0x1248*/
  case netErrDNSNoPort:                      TRACE0(_T("netErrDNSNoPort")                      ); break;/*0x1249*/
  case netErrIPCantFragment:                 TRACE0(_T("netErrIPCantFragment")                 ); break;/*0x124a*/
  case netErrIPNoRoute:                      TRACE0(_T("netErrIPNoRoute")                      ); break;/*0x124b*/
  case netErrIPNoSrc:                        TRACE0(_T("netErrIPNoSrc")                        ); break;/*0x124c*/
  case netErrIPNoDst:                        TRACE0(_T("netErrIPNoDst")                        ); break;/*0x124d*/
  case netErrIPktOverflow:                   TRACE0(_T("netErrIPktOverflow")                   ); break;/*0x124e*/
  case netErrTooManyTCPConnections:          TRACE0(_T("netErrTooManyTCPConnections")          ); break;/*0x124f*/
  case netErrNoDNSServers:                   TRACE0(_T("netErrNoDNSServers")                   ); break;/*0x1250*/
  case netErrInterfaceDown:                  TRACE0(_T("netErrInterfaceDown")                  ); break;/*0x1251*/
  case netErrNoChannel:                      TRACE0(_T("netErrNoChannel")                      ); break;/*0x1252*/
  case netErrDieState:                       TRACE0(_T("netErrDieState")                       ); break;/*0x1253*/
  case netErrReturnedInMail:                 TRACE0(_T("netErrReturnedInMail")                 ); break;/*0x1254*/
  case netErrReturnedNoTransfer:             TRACE0(_T("netErrReturnedNoTransfer")             ); break;/*0x1255*/
  case netErrReturnedIllegal:                TRACE0(_T("netErrReturnedIllegal")                ); break;/*0x1256*/
  case netErrReturnedCongest:                TRACE0(_T("netErrReturnedCongest")                ); break;/*0x1257*/
  case netErrReturnedError:                  TRACE0(_T("netErrReturnedError")                  ); break;/*0x1258*/
  case netErrReturnedBusy:                   TRACE0(_T("netErrReturnedBusy")                   ); break;/*0x1259*/
  case netErrGMANState:                      TRACE0(_T("netErrGMANState")                      ); break;/*0x125a*/
  case netErrQuitOnTxFail:                   TRACE0(_T("netErrQuitOnTxFail")                   ); break;/*0x125b*/
  case netErrFlexListFull:                   TRACE0(_T("netErrFlexListFull")                   ); break;/*0x125c*/
  case netErrSenderMAN:                      TRACE0(_T("netErrSenderMAN")                      ); break;/*0x125d*/
  case netErrIllegalType:                    TRACE0(_T("netErrIllegalType")                    ); break;/*0x125e*/
  case netErrIllegalState:                   TRACE0(_T("netErrIllegalState")                   ); break;/*0x125f*/
  case netErrIllegalFlags:                   TRACE0(_T("netErrIllegalFlags")                   ); break;/*0x1260*/
  case netErrIllegalSendlist:                TRACE0(_T("netErrIllegalSendlist")                ); break;/*0x1261*/
  case netErrIllegalMPAKLength:              TRACE0(_T("netErrIllegalMPAKLength")              ); break;/*0x1262*/
  case netErrIllegalAddressee:               TRACE0(_T("netErrIllegalAddressee")               ); break;/*0x1263*/
  case netErrIllegalPacketClass:             TRACE0(_T("netErrIllegalPacketClass")             ); break;/*0x1264*/
  case netErrBufferLength:                   TRACE0(_T("netErrBufferLength")                   ); break;/*0x1265*/
  case netErrNiCdLowBattery:                 TRACE0(_T("netErrNiCdLowBattery")                 ); break;/*0x1266*/
  case netErrRFinterfaceFatal:               TRACE0(_T("netErrRFinterfaceFatal")               ); break;/*0x1267*/
  case netErrIllegalLogout:                  TRACE0(_T("netErrIllegalLogout")                  ); break;/*0x1268*/
  case netErrAAARadioLoad:                   TRACE0(_T("netErrAAARadioLoad")                   ); break;/*0x1269*/
  case netErrAntennaDown:                    TRACE0(_T("netErrAntennaDown")                    ); break;/*0x126a*/
  case netErrNiCdCharging:                   TRACE0(_T("netErrNiCdCharging")                   ); break;/*0x126b*/
  case netErrAntennaWentDown:                TRACE0(_T("netErrAntennaWentDown")                ); break;/*0x126c*/
  case netErrNotActivated:                   TRACE0(_T("netErrNotActivated")                   ); break;/*0x126d*/
  case netErrRadioTemp:                      TRACE0(_T("netErrRadioTemp")                      ); break;/*0x126e*/
  case netErrNiCdChargeError:                TRACE0(_T("netErrNiCdChargeError")                ); break;/*0x126f*/
  case netErrNiCdSag:                        TRACE0(_T("netErrNiCdSag")                        ); break;/*0x1270*/
  case netErrNiCdChargeSuspend:              TRACE0(_T("netErrNiCdChargeSuspend")              ); break;/*0x1271*/
  case netErrConfigNotFound:                 TRACE0(_T("netErrConfigNotFound")                 ); break;/*0x1273*/
  case netErrConfigCantDelete:               TRACE0(_T("netErrConfigCantDelete")               ); break;/*0x1274*/
  case netErrConfigTooMany:                  TRACE0(_T("netErrConfigTooMany")                  ); break;/*0x1275*/
  case netErrConfigBadName:                  TRACE0(_T("netErrConfigBadName")                  ); break;/*0x1276*/
  case netErrConfigNotAlias:                 TRACE0(_T("netErrConfigNotAlias")                 ); break;/*0x1277*/
  case netErrConfigCantPointToAlias:         TRACE0(_T("netErrConfigCantPointToAlias")         ); break;/*0x1278*/
  case netErrConfigEmpty:                    TRACE0(_T("netErrConfigEmpty")                    ); break;/*0x1279*/
  case netErrAlreadyOpenWithOtherConfig:     TRACE0(_T("netErrAlreadyOpenWithOtherConfig")     ); break;/*0x127a*/
  case netErrConfigAliasErr:                 TRACE0(_T("netErrConfigAliasErr")                 ); break;/*0x127b*/
  case netErrNoMultiPktAddr:                 TRACE0(_T("netErrNoMultiPktAddr")                 ); break;/*0x127c*/
  case netErrOutOfPackets:                   TRACE0(_T("netErrOutOfPackets")                   ); break;/*0x127d*/
  case netErrMultiPktAddrReset:              TRACE0(_T("netErrMultiPktAddrReset")              ); break;/*0x127e*/
  case netErrStaleMultiPktAddr:              TRACE0(_T("netErrStaleMultiPktAddr")              ); break;/*0x127f*/
  case netErrScptPluginMissing:              TRACE0(_T("netErrScptPluginMissing")              ); break;/*0x1280*/
  case netErrScptPluginLaunchFail:           TRACE0(_T("netErrScptPluginLaunchFail")           ); break;/*0x1281*/
  case netErrScptPluginCmdFail:              TRACE0(_T("netErrScptPluginCmdFail")              ); break;/*0x1282*/
  case netErrScptPluginInvalidCmd:           TRACE0(_T("netErrScptPluginInvalidCmd")           ); break;/*0x1283*/
  case netErrTelMissingComponent:            TRACE0(_T("netErrTelMissingComponent")            ); break;/*0x1284*/
  case netErrTelErrorNotHandled:             TRACE0(_T("netErrTelErrorNotHandled")             ); break;/*0x1285*/
  case netErrDeviceNotReady:                 TRACE0(_T("netErrDeviceNotReady")                 ); break;/*0x1286*/
  case netErrDeviceInitFail:                 TRACE0(_T("netErrDeviceInitFail")                 ); break;/*0x1287*/
  case netErrInterfaceIncompatible:          TRACE0(_T("netErrInterfaceIncompatible")          ); break;/*0x1288*/
  case htalErrorClass:                       TRACE0(_T("htalErrorClass")                       ); break;/*0x1300 HTAL Library errors*/

  case exgErrorClass:                        TRACE0(_T("exgErrorClass")                        ); break;/*0x1500 Exchange Manager errors*/
  case exgMemError:                          TRACE0(_T("exgMemError")                          ); break;/*0x1501 There isn't enough free memory to respond to the request; or the Exchange Manager ouldn't read the data to be sent.*/
  case exgErrStackInit:                      TRACE0(_T("exgErrStackInit")                      ); break;/*0x1502*/
  case exgErrUserCancel:                     TRACE0(_T("exgErrUserCancel")                     ); break;/*0x1503 The user cancelled the connection operation.*/
  case exgErrNoReceiver:                     TRACE0(_T("exgErrNoReceiver")                     ); break;/*0x1504*/
  case exgErrNoKnownTarget:                  TRACE0(_T("exgErrNoKnownTarget")                  ); break;/*0x1505 There is no default application or library for the specified type of data.*/
  case exgErrTargetMissing:                  TRACE0(_T("exgErrTargetMissing")                  ); break;/*0x1506 The target field contains a creator ID, but the application with that creator ID does not exist.*/
  case exgErrNotAllowed:                     TRACE0(_T("exgErrNotAllowed")                     ); break;/*0x1507*/
  case exgErrBadData:                        TRACE0(_T("exgErrBadData")                        ); break;/*0x1508*/
  case exgErrAppError:                       TRACE0(_T("exgErrAppError")                       ); break;/*0x1509*/
  case exgErrUnknown:                        TRACE0(_T("exgErrUnknown")                        ); break;/*0x150a*/
  case exgErrDeviceFull:                     TRACE0(_T("exgErrDeviceFull")                     ); break;/*0x150b*/
  case exgErrDisconnected:                   TRACE0(_T("exgErrDisconnected")                   ); break;/*0x150c*/
  case exgErrNotFound:                       TRACE0(_T("exgErrNotFound")                       ); break;/*0x150d*/
  case exgErrBadParam:                       TRACE0(_T("exgErrBadParam")                       ); break;/*0x150e*/
  case exgErrNotSupported:                   TRACE0(_T("exgErrNotSupported")                   ); break;/*0x150f A preview is in progress, and the exchange library identified by libraryRef doesn't support preview mode; or the library doesn't support the operation specified in socketP; or the exchange library does not support the requested operation. See the Exchange Manager function's description for more detail.*/
  case exgErrDeviceBusy:                     TRACE0(_T("exgErrDeviceBusy")                     ); break;/*0x1510*/
  case exgErrBadLibrary:                     TRACE0(_T("exgErrBadLibrary")                     ); break;/*0x1511 The default exchange library couldn't be found.*/
  case exgErrNotEnoughPower:                 TRACE0(_T("exgErrNotEnoughPower")                 ); break;/*0x1512 The battery does not have enough power to perform the operation.*/
  case fileErrorClass:                       TRACE0(_T("fileErrorClass")                       ); break;/*0x1600 File Stream Manager errors*/
  case fileErrMemError:                      TRACE0(_T("fileErrMemError")                      ); break;/*0x1601*/
  case fileErrInvalidParam:                  TRACE0(_T("fileErrInvalidParam")                  ); break;/*0x1602*/
  case fileErrCorruptFile:                   TRACE0(_T("fileErrCorruptFile")                   ); break;/*0x1603*/
  case fileErrNotFound:                      TRACE0(_T("fileErrNotFound")                      ); break;/*0x1604*/
  case fileErrTypeCreatorMismatch:           TRACE0(_T("fileErrTypeCreatorMismatch")           ); break;/*0x1605*/
  case fileErrReplaceError:                  TRACE0(_T("fileErrReplaceError")                  ); break;/*0x1606*/
  case fileErrCreateError:                   TRACE0(_T("fileErrCreateError")                   ); break;/*0x1607*/
  case fileErrOpenError:                     TRACE0(_T("fileErrOpenError")                     ); break;/*0x1608*/
  case fileErrInUse:                         TRACE0(_T("fileErrInUse")                         ); break;/*0x1609*/
  case fileErrReadOnly:                      TRACE0(_T("fileErrReadOnly")                      ); break;/*0x160a*/
  case fileErrInvalidDescriptor:             TRACE0(_T("fileErrInvalidDescriptor")             ); break;/*0x160b*/
  case fileErrCloseError:                    TRACE0(_T("fileErrCloseError")                    ); break;/*0x160c*/
  case fileErrOutOfBounds:                   TRACE0(_T("fileErrOutOfBounds")                   ); break;/*0x160d*/
  case fileErrPermissionDenied:              TRACE0(_T("fileErrPermissionDenied")              ); break;/*0x160e*/
  case fileErrIOError:                       TRACE0(_T("fileErrIOError")                       ); break;/*0x160f*/
  case fileErrEOF:                           TRACE0(_T("fileErrEOF")                           ); break;/*0x1610*/
  case fileErrNotStream:                     TRACE0(_T("fileErrNotStream")                     ); break;/*0x1611*/
  case rfutErrorClass:                       TRACE0(_T("rfutErrorClass")                       ); break;/*0x1700 RFUT Library errors*/
  case txtErrorClass:                        TRACE0(_T("txtErrorClass")                        ); break;/*0x1800 Text Manager errors*/
  case txtErrUknownTranslitOp:               TRACE0(_T("txtErrUknownTranslitOp")               ); break;/*0x1801*/
  case txtErrTranslitOverrun:                TRACE0(_T("txtErrTranslitOverrun")                ); break;/*0x1802*/
  case txtErrTranslitOverflow:               TRACE0(_T("txtErrTranslitOverflow")               ); break;/*0x1803*/
  case txtErrConvertOverflow:                TRACE0(_T("txtErrConvertOverflow")                ); break;/*0x1804*/
  case txtErrConvertUnderflow:               TRACE0(_T("txtErrConvertUnderflow")               ); break;/*0x1805*/
  case txtErrUnknownEncoding:                TRACE0(_T("txtErrUnknownEncoding")                ); break;/*0x1806*/
  case txtErrNoCharMapping:                  TRACE0(_T("txtErrNoCharMapping")                  ); break;/*0x1807*/
  case txtErrTranslitUnderflow:              TRACE0(_T("txtErrTranslitUnderflow")              ); break;/*0x1808*/
  case txtErrMalformedText:                  TRACE0(_T("txtErrMalformedText")                  ); break;/*0x1809*/
  case txtErrUnknownEncodingFallbackCopy:    TRACE0(_T("txtErrUnknownEncodingFallbackCopy")    ); break;/*0x180a*/
  case tsmErrorClass:                        TRACE0(_T("tsmErrorClass")                        ); break;/*0x1900 Text Services Manager errors*/
  case webErrorClass:                        TRACE0(_T("webErrorClass")                        ); break;/*0x1a00 Web Library errors*/
  case secErrorClass:                        TRACE0(_T("secErrorClass")                        ); break;/*0x1b00 Security Library errors*/

  case flshErrorClass:                       TRACE0(_T("flshErrorClass")                       ); break;/*0x1d00 Flash Manager errors*/

  case actvErrorClass:                       TRACE0(_T("actvErrorClass")                       ); break;/*0x2000 Activation application errors*/
  case radioErrorClass:                      TRACE0(_T("radioErrorClass")                      ); break;/*0x2100 Radio Manager (library) errors*/
  case dispErrorClass:                       TRACE0(_T("dispErrorClass")                       ); break;/*0x2200 Display Driver errors*/
  case bltErrorClass:                        TRACE0(_T("bltErrorClass")                        ); break;/*0x2300 Blitter Driver errors*/
  case winErrorClass:                        TRACE0(_T("winErrorClass")                        ); break;/*0x2400 Window Manager errors*/
  case winErrPalette:                        TRACE0(_T("winErrPalette")                        ); break;/*0x2401*/
  case omErrorClass:                         TRACE0(_T("omErrorClass")                         ); break;/*0x2500 Overlay Manager errors*/
  case omErrBaseRequiresOverlay:             TRACE0(_T("omErrBaseRequiresOverlay")             ); break;/*0x2501 An attempt was made to open a stripped resource database, but no associated overlay could be found.*/
  case omErrUnknownLocale:                   TRACE0(_T("omErrUnknownLocale")                   ); break;/*0x2502 An attempt was made to open a resource database with overlays using an unknown locale.*/
  case omErrBadOverlayDBName:                TRACE0(_T("omErrBadOverlayDBName")                ); break;/*0x2503*/
  case omErrInvalidLocaleIndex:              TRACE0(_T("omErrInvalidLocaleIndex")              ); break;/*0x2504*/
  case omErrInvalidLocale:                   TRACE0(_T("omErrInvalidLocale")                   ); break;/*0x2505*/
  case omErrInvalidSystemOverlay:            TRACE0(_T("omErrInvalidSystemOverlay")            ); break;/*0x2506*/
  case omErrNoNextSystemLocale:              TRACE0(_T("omErrNoNextSystemLocale")              ); break;/*0x2507*/
  case menuErrorClass:                       TRACE0(_T("menuErrorClass")                       ); break;/*0x2600 Menu Manager errors*/
  case menuErrNoMenu:                        TRACE0(_T("menuErrNoMenu")                        ); break;/*0x2601 The textP parameter is NULL.*/
  case menuErrNotFound:                      TRACE0(_T("menuErrNotFound")                      ); break;/*0x2602 The menu doesn't contain an item with the specified ID.*/
  case menuErrSameId:                        TRACE0(_T("menuErrSameId")                        ); break;/*0x2603 The menu already contains an item with the specified ID*/
  case menuErrTooManyItems:                  TRACE0(_T("menuErrTooManyItems")                  ); break;/*0x2604 The command toolbar already has the maximum number of buttons allowed.*/
  case menuErrOutOfMemory:                   TRACE0(_T("menuErrOutOfMemory")                   ); break;/*0x2605 There is not enough memory available to perform the operation.*/

  case lmErrorClass:                         TRACE0(_T("lmErrorClass")                         ); break;/*0x2b00 Locale Manager errors*/
  case lmErrUnknownLocale:                   TRACE0(_T("lmErrUnknownLocale")                   ); break;/*0x2b01 The locale could not be found.*/
  case lmErrBadLocaleIndex:                  TRACE0(_T("lmErrBadLocaleIndex")                  ); break;/*0x2b02 The locale index is out of range.*/
  case lmErrBadLocaleSettingChoice:          TRACE0(_T("lmErrBadLocaleSettingChoice")          ); break;/*0x2b03 The locale setting choice parameter contains an unknown or unsupported value.*/
  case lmErrSettingDataOverflow:             TRACE0(_T("lmErrSettingDataOverflow")             ); break;/*0x2b04 The output buffer is too small to hold the setting's value.*/
  case intlErrorClass:                       TRACE0(_T("intlErrorClass")                       ); break;/*0x2c00 International Manager errors*/
  case intlErrInvalidSelector:               TRACE0(_T("intlErrInvalidSelector")               ); break;/*0x2c01*/

  case attnErrorClass:                       TRACE0(_T("attnErrorClass")                       ); break;/*0x2e00 Attention Manager errors*/
  case attnErrMemory:                        TRACE0(_T("attnErrMemory")                        ); break;/*0x2e01 There is insufficient memory to perform the requested operation.*/

  case hwrErrorClass:                        TRACE0(_T("hwrErrorClass")                        ); break;/*0x3000 Handwriting Recognition Manager errors*/


  case uilibErrorClass:                      TRACE0(_T("uilibErrorClass")                      ); break;/*0x3a00 UI Library errors*/
  case oemErrorClass:                        TRACE0(_T("oemErrorClass")                        ); break;/*0x7000 OEM/Licensee errors*/
  case appErrorClass:                        TRACE0(_T("appErrorClass")                        ); break;/*0x8000 Application-defined errors*/
  default:
    if((nErrorCode >= dlkErrorClass) && (nErrorCode < padErrorClass))
      {
      DbgErrorDlk(nErrorCode);
      return;
      }
    else if((nErrorCode >= inetErrorClass) && (nErrorCode < exgErrorClass))
      {
      DbgErrorINet(nErrorCode);
      return;
      }
    else if((nErrorCode >= emuErrorClass) && (nErrorCode < flshErrorClass))
      {
      DbgErrorHost(nErrorCode);
      return;
      }
    else if((nErrorCode >= blthErrorClass) && (nErrorCode < udaErrorClass))
      {
      DbgErrorBlth(nErrorCode);
      return;
      }
    else if((nErrorCode >= sslErrorClass) && (nErrorCode < uilibErrorClass))
      {
      DbgErrorSsl(nErrorCode);
      return;
      }
    else if((nErrorCode >= pwrErrorClass) && (nErrorCode < cncErrorClass))
      {
      DbgErrorPwr(nErrorCode);
      return;
      }
    else if((nErrorCode >= cncErrorClass) && (nErrorCode < flshErrorClass))
      {
      DbgErrorCnc(nErrorCode);
      return;
      }
    else if((nErrorCode >= lz77ErrorClass) && (nErrorCode < smsErrorClass))
      {
      DbgErrorLz(nErrorCode);
      return;
      }
    else if((nErrorCode >= smsErrorClass) && (nErrorCode < expErrorClass))
      {
      DbgErrorSms(nErrorCode);
      return;
      }
    else if((nErrorCode >= expErrorClass) && (nErrorCode < vfsErrorClass))
      {
      DbgErrorExp(nErrorCode);
      return;
      }
    else if((nErrorCode >= vfsErrorClass) && (nErrorCode < lmErrorClass))
      {
      DbgErrorVfs(nErrorCode);
      return;
      }
    else if((nErrorCode >= pdiErrorClass) && (nErrorCode < attnErrorClass))
      {
      DbgErrorPdi(nErrorCode);
      return;
      }
    else if((nErrorCode >= udaErrorClass) && (nErrorCode < 0x3300))
      {
      DbgErrorUda(nErrorCode);
      return;
      }
    else if((nErrorCode >= cpmErrorClass) && (nErrorCode < sslErrorClass))
      {
      DbgErrorCpm(nErrorCode);
      return;
      }
    else if((nErrorCode >= telErrorClass) && (nErrorCode < 0x8200))
      {
      DbgErrorTel(nErrorCode);
      return;
      }
    else
      TRACE0(_T("Unknown error"));
  }
TRACE1(_T(" (%d).\n"), (UInt32)nErrorCode);
}

/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-11-02 14:31:37  Darko Kolakovic
 * $
 *****************************************************************************/
