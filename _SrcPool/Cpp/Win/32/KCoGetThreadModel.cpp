/*$Workfile: KCoGetThreadModel.cpp$: implementation file
  $Revision: 3$ $Date: 2004-10-01 22:33:52$
  $Author: Darko$

  Retreives.COM threading model.
  Microsoft Systems Journal.
  1999-10 John Robbins
 */
#include "stdafx.h"
#include "KType32.h"  //ISO C99: 7.18 Integer types

typedef struct tagAPARTMENT 
  {
  struct tagAPARTMENT* next;
  struct tagAPARTMENT* prev;
  struct tagAPARTMENT* parent;
  DWORD model;             //threading model   
  DWORD dwCount;           //CoInitialize count
  DWORD tid;               //thread ID         
  HANDLE thread;           //thread handle     
  //TODO: Fixme!typedefs for OXID D.K.
 /* OXID oxid;               //object exporter ID
  OID oidc;                //object ID counter 
  HWND win;                //message window    
  CRITICAL_SECTION cs;     //thread safety     
  LPMESSAGEFILTER filter;  //message filter    
  XOBJECT *objs;           //exported objects  
  IOBJECT *proxies;        //imported objects  
  LPVOID ErrorInfo;        //thread error information */
  } _APARTMENT, *_PAPARTMENT;

//-----------------------------------------------------------------------------
/*Obatins Thread Environment Block (TEB).
  
  Returns: pointer to Thread Environment Block structure _TEB.
 */
struct _TEB* WINAPI _NtCurrentTeb(void)
{
_TEB* pTeb;
  //Get the Thread Environment Block (TEB)
__asm MOV EAX , FS:018h
__asm MOV pTeb , EAX
return pTeb;
};

//-----------------------------------------------------------------------------
/*Obtains the COM threading model for the current thread.

      typedef enum tagCOINIT 
        {
        COINIT_MULTITHREADED     = 0x0,//Initializes the thread for 
                                       //multi-threaded object concurrency
        COINIT_APARTMENTTHREADED = 0x2,//Initializes the thread for 
                                       //apartment-threaded object concurrency
        COINIT_DISABLE_OLE1DDE   = 0x4,//Disables DDE for Ole1 support
        COINIT_SPEED_OVER_MEMORY = 0x8,//Trades memory for speed.
        } COINIT;

  Returns: current Apartment type (COINIT_MULTITHREADED or COINIT_APARTMENTTHREADED),
  or 0xFF if COM library is not initialized.

  Note: Microsoft Windows specific (Win).

  History: John Robbins, Microsoft Systems Journal, Bugslayer Column, 1999-10

  TODO: verify COINIT_DISABLE_OLE1DDE, COINIT_SPEED_OVER_MEMORY, and combinations results D.K.
  TODO: check why pOleApartment->dwCount is always 0. D.K.
 */
uint_least32_t ComGetThreadingModel (void)
{
_PAPARTMENT pOleApartment;
const uint_least32_t COGET_NOT_INTIALIZED = 0xFF;
const uint32_t OLE_APT_MASK  = 0x080; //multi-threaded object concurrency mask
const uint32_t OLE_FREE_MASK = 0x140; //apartment-threaded object concurrency mask

  //Get the OLE thread structure out of the TEB block.

//_TEB* pTeb = _NtCurrentTeb();
//PVOID p = pTeb->ReservedForOle;//TlsSlots ;//TlsSlots

  //Get the Thread Environment Block (TEB)
__asm MOV EAX , FS:018h
//Get the COM TLS structure from its offset.
__asm MOV EAX , [EAX + 0F80h]
__asm MOV pOleApartment , EAX

  //If the value is zero, OLE has not been initialized.
if ( NULL == pOleApartment )
  return COGET_NOT_INTIALIZED;
uint_least32_t nResult = COGET_NOT_INTIALIZED;

__try
  {
  //Get the threading model flag, which is 12 bytes or 3 sizeof(int32) into 
  //the structure.
  uint32_t dwFlags = pOleApartment->model;

  if (OLE_APT_MASK == (dwFlags & OLE_APT_MASK))
    nResult = COINIT_APARTMENTTHREADED;

  //Valid on Windows NT 4.0
  #if  (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) //DCOM
    //If any flag of COINIT_MULTITHREADED, COINIT_DISABLE_OLE1DDE, or
    //COINIT_SPEED_OVER_MEMORY is set, mask results with COINIT_MULTITHREADED D.K.
    if (OLE_FREE_MASK == (dwFlags & OLE_FREE_MASK))
      nResult = COINIT_MULTITHREADED;
  #endif
  }
 __except(EXCEPTION_EXECUTE_HANDLER)
  {
  return COGET_NOT_INTIALIZED;
  }
return nResult;
}

///////////////////////////////////////////////////////////////////////////////
/*Note:
  The Thread Environment Block (TEB) structure contains data that describes 
  the state of a thread. TEB exists in the process address space (as opposed 
  to the system space). TEB is accessable at address fs:[0018h].

  Declared in Winternl.h. Included in Windows XP and Windows 2000 Professional.

      typedef struct _TEB 
        {  
        BYTE Reserved1[1952];
        PVOID Reserved2[412];
        PVOID TlsSlots[64];
        BYTE Reserved3[8];
        PVOID Reserved4[26];
        PVOID ReservedForOle; <- pOleTls = (PTEB + 0xF80)
        PVOID Reserved5[4];   <- pOleTls + 0x0C = COINIT (Check this D.K.)
        PVOID TlsExpansionSlots;
        } TEB, *PTEB;

      typedef struct _TEB 
        {
        NT_TIB          Tib;
        PVOID           EnvironmentPointer;
        CLIENT_ID       Cid;
        PVOID           ActiveRpcInfo;
        PVOID           ThreadLocalStoragePointer;
        PPEB            Peb;
        ULONG           LastErrorValue;
        ULONG           CountOfOwnedCriticalSections;
        PVOID           CsrClientThread;
        PVOID           Win32ThreadInfo;
        ULONG           Win32ClientInfo[0x1F];
        PVOID           WOW32Reserved;
        ULONG           CurrentLocale;
        ULONG           FpSoftwareStatusRegister;
        PVOID           SystemReserved1[0x36];
        PVOID           Spare1;
        ULONG           ExceptionCode;
        ULONG           SpareBytes1[0x28];
        PVOID           SystemReserved2[0xA];
        ULONG           GdiRgn;
        ULONG           GdiPen;
        ULONG           GdiBrush;
        CLIENT_ID       RealClientId;
        PVOID           GdiCachedProcessHandle;
        ULONG           GdiClientPID;
        ULONG           GdiClientTID;
        PVOID           GdiThreadLocaleInfo;
        PVOID           UserReserved[5];
        PVOID           GlDispatchTable[0x118];
        ULONG           GlReserved1[0x1A];
        PVOID           GlReserved2;
        PVOID           GlSectionInfo;
        PVOID           GlSection;
        PVOID           GlTable;
        PVOID           GlCurrentRC;
        PVOID           GlContext;
        NTSTATUS        LastStatusValue;
        UNICODE_STRING  StaticUnicodeString;
        WCHAR           StaticUnicodeBuffer[0x105];
        PVOID           DeallocationStack;
        PVOID           TlsSlots[0x40];
        LIST_ENTRY      TlsLinks;
        PVOID           Vdm;
        PVOID           ReservedForNtRpc;
        PVOID           DbgSsReserved[0x2];
        ULONG           HardErrorDisabled;
        PVOID           Instrumentation[0x10];
        PVOID           WinSockData;
        ULONG           GdiBatchCount;
        ULONG           Spare2;
        ULONG           Spare3;
        ULONG           Spare4;
        PVOID           ReservedForOle;
        ULONG           WaitingOnLoaderLock;
        PVOID           StackCommit;
        PVOID           StackCommitMax;
        PVOID           StackReserved;
        } TEB, *PTEB;

http://undocumented.ntinternals.net/

// apartment  http://WineHq.org \dlls\ole32\compobj_private.h
typedef struct tagAPARTMENT {
  struct tagAPARTMENT *next, *prev, *parent;
  DWORD model;             // threading model    // <-
  DWORD inits;             // CoInitialize count //
  DWORD tid;               // thread id          //
  HANDLE thread;           // thread handle      //
  OXID oxid;               // object exporter ID //
  OID oidc;                // object ID counter  //
  HWND win;                // message window     //
  CRITICAL_SECTION cs;     // thread safety      //
  LPMESSAGEFILTER filter;  // message filter     //
  XOBJECT *objs;           // exported objects   //
  IOBJECT *proxies;        // imported objects   //
  LPVOID ErrorInfo;        // thread error info  //
} APARTMENT;

\Vc7\PlatformSDK\Include\ObjBase.h
// COM initialization flags; passed to CoInitialize.
typedef enum tagCOINIT
{
  COINIT_APARTMENTTHREADED  = 0x2,      // Apartment model

  #if  (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
    // These constants are only valid on Windows NT 4.0
    COINIT_MULTITHREADED      = 0x0,      // OLE calls objects on any thread.
    COINIT_DISABLE_OLE1DDE    = 0x4,      // Don't use DDE for Ole1 support.
    COINIT_SPEED_OVER_MEMORY  = 0x8,      // Trade memory for speed.
  #endif // DCOM
} COINIT;

 */
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2004-10-01 22:33:52  Darko           stdafx.h
 *  2    Biblioteka1.1         2003-08-13 14:39:27  Darko           formatting
 *  1    Biblioteka1.0         2003-08-09 14:06:20  Darko           
 * $
 *****************************************************************************/
