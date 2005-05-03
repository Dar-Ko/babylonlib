/*$Workfile: KSingleInstanceApp.cpp$: implementation file
  $Revision: 5$ $Date: 2004-10-01 22:35:22$
  $Author: Darko$

  Single instance Windows application
  Copyright: BRadovic
  2k3-07-17 Blazimir Radovic
 */
#include "stdafx.h"

#ifndef __AFXWIN_H__
  #include <AfxWin.h>
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#include "KSingleInstanceApp.h" //CSingleInstanceApp class

//#if _MFC_VER <= 0x420
/*Bug fix: Incorrect Function Signatures May Cause Problems in Release
  When developing applications in Visual C++ with MFC, you may receive an invalid
  page fault in Mfc42.dll in release builds due to an incorrect function signature
  for any of the following MFC macros: 
    ON_MESSAGE()
    ON_REGISTERED_MESSAGE()
    ON_THREAD_MESSAGE()
    ON_REGISTERED_THREAD_MESSAGE() 

  See also: KB195032
 * /
  #undef  ON_REGISTERED_THREAD_MESSAGE
  #define ON_REGISTERED_THREAD_MESSAGE(nMessageVariable, memberFxn) \ 
      { 0xC000, 0, 0, 0, (UINT)(UINT*)(&nMessageVariable), \ 
         (AFX_PMSG)(AFX_PMSGT)(static_cast<void (AFX_MSG_CALL
   WinThread::*)(WPARAM, LPARAM)>(&memberFxn)) },
#endif
*/

///////////////////////////////////////////////////////////////////////////////
// CSingleInstanceApp class

BEGIN_MESSAGE_MAP(CSingleInstanceApp, CWinApp)
  //{{AFX_MSG_MAP(CSingleInstanceApp)
//    ON_REGISTERED_THREAD_MESSAGE(CSingleInstanceApp::m_nMsgId, OnFindFirstInstance)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
#pragma data_seg("SharedSection")
  /*process identifier of the thread that created  a single instance application.
   */
  DWORD CSingleInstanceApp::m_dwPid = 0;
#pragma data_seg()
#pragma comment(linker, "/SECTION:SharedSection,RWS")

/*pointer to a null-terminated string specifying the name of the mutex object.
  The name is limited to MAX_PATH characters. Name comparison is case sensitive.
  If Terminal Services is running on Win2k, WinXP, the name can have a "Global\"
  or "Local\" prefix to explicitly create the object in the global or session
  name space.
  Win9x, WinNT 4: The name can contain any character except the backslash
  character.
 */
TCHAR CSingleInstanceApp::m_szMutex[] = _T("Global\\");

//-----------------------------------------------------------------------------
/*static Windows message identifier in the range [0xC000, 0xFFFF].
  TODO: test version with PID under Terminal Services. If OK, delete m_nMsgId D.K.
 */
UINT CSingleInstanceApp::m_nMsgId = 0;

//-----------------------------------------------------------------------------
/*Registers the application with globally unique identifier (GUID). 
  The Guidgen.exe GUID generator can be used to generate globally unique
  identifier. The Guidgen is supplied with the Microsoft Visual C++
  development system. Besides generating GUIDs, it can also copy the GUID to
  clipboard so the GUID can be accurately inserted into the application's source
  code. For this implemetation select the form suitable for registry entries 
  or registry editor scripts:

      Registry entry      {CA761233-ED42-11CE-BACD-00AA0057B223}

 */
CSingleInstanceApp::CSingleInstanceApp(LPCTSTR szGuid //[in] globally unique
                                       //identifier (GUID)
                                      )
{
ASSERT((szGuid != NULL) && (szGuid[0] != _T('\0')));
VERIFY((m_nMsgId = ::RegisterWindowMessage(szGuid)) != 0);
int i = 0;
while (m_szMutex[i] != _T('\0'))
  i++;
int j = 0;
while (szGuid[j] != _T('\0'))
  {
  m_szMutex[i] = szGuid[j];
  i++;
  if (i >= MAX_PATH-1)
    break;
  j++;
  }
m_szMutex[i] = _T('\0');
}

CSingleInstanceApp::~CSingleInstanceApp(void)
{
}

//-----------------------------------------------------------------------------
/*Queries number of the application instances.

  Returns: true if this is the first time the program runs; otherwise returns
  false.

  TODO: WinNT doesn't work anyhow, WinME works with and without backslash D.K.
 */
bool CSingleInstanceApp::IsFirstInstance()
{
  //Note: the system closes the mutex handle automatically when the process
  //terminates
HANDLE hMutex;
DWORD dwVersion = GetVersion();
    //Are we running Windows 2000 or XP?
if ((!(dwVersion & 0x80000000)) && (LOBYTE(LOWORD(dwVersion)) >= 5))
  {
  hMutex = ::CreateMutex(NULL, FALSE, CSingleInstanceApp::m_szMutex);
  }
else //Windows 9x,Me,NT
  {
  //The name of mutex object can contain any character except the backslash
  //character.
  //TODO: WinNT doesn't work anyhow, WinME works with and without backslash D.K.
  hMutex = ::CreateMutex(NULL, FALSE, m_szMutex);//&m_szMutex[6]);
  }

if (hMutex == NULL)
  return false; //Failed to create mutex

  //If mutex is already created error is ERROR_ALREADY_EXISTS; if mutex is
  //created  with NULL security descriptor, error is ERROR_ACCESS_DENIED.
if ( ::GetLastError() == ERROR_ALREADY_EXISTS  ||
     ::GetLastError() == ERROR_ACCESS_DENIED     )
  { 
  ::ReleaseMutex(hMutex);
  return false; //One instance already exist
  }

return true; //This is the first instance of the application
}

//-----------------------------------------------------------------------------
/*The framework's implementation of WinMain calls this function.
  This implementation prevents the second copy of the application if running.
  Override to perform Windows instance initialization, such as creating your
  window objects.

  Returns: TRUE if this is the first time the program runs; otherwise returns
  FALSE.

  Example:
      BOOL CMyApp::InitInstance()
        {
        // Standard initialization
        if(!CSingleInstanceApp::InitInstance())
          return FALSE; //Terminate the creation

        LoadStdProfileSettings();  // Load standard INI file options (including MRU)

        // Register the application's document templates.  Document templates
        //  serve as the connection between documents, frame windows and views.

        CSingleDocTemplate* pDocTemplate;
        pDocTemplate = new CSingleDocTemplate(
                      IDR_MAINFRAME,
                      RUNTIME_CLASS(CMyDoc),
                      RUNTIME_CLASS(CMainFrame), // main SDI frame window
                      RUNTIME_CLASS(CMyView));
        AddDocTemplate(pDocTemplate);

        // create a new (empty) document
        OnFileNew();

        if (m_lpCmdLine[0] != '\0')
          {
            // TODO: add command line processing here
          }

        return TRUE;
        }

 */
BOOL CSingleInstanceApp::InitInstance()
{
TRACE0("CSingleInstanceApp::InitInstance()\n");
if (!IsFirstInstance())
  {
  //Find previous instance of the application and activate it
//  HWND hOther = NULL;
  //Enumerates all top-level windows on the screen by passing the handle to each
  //window, in turn, to an application-defined callback function. 
  ::EnumWindows(CSingleInstanceApp::FindFirstInstance, (LPARAM)CSingleInstanceApp::m_dwPid);//&hOther);
/*
  if ( hOther != NULL )
      {
        //Put the thread that created the first copy of the application into
        //the foreground and activate the window
      ::SetForegroundWindow(hOther);
      if (IsIconic(hOther))          
        ::ShowWindow(hOther, SW_RESTORE);
      }
*/
  return FALSE; //Terminate the creation
  }
else
  {
  if (CSingleInstanceApp::m_dwPid == 0)
      CSingleInstanceApp::m_dwPid = GetCurrentProcessId();
  }
  //Continue with InitInstance
return CWinApp::InitInstance();
}

//-----------------------------------------------------------------------------
/*The EnumWindowsProc function is an application-defined callback function used
  with the EnumWindows or EnumDesktopWindows function. 
  It receives top-level window handles. The WNDENUMPROC type defines a pointer
  to this callback function. 

Return Value

To continue enumeration, the callback function must return TRUE; to stop enumeration, it must return FALSE. 


 */
BOOL CALLBACK CSingleInstanceApp::FindFirstInstance(HWND   hWnd, //[in] handle to a top-level window
                                                    LPARAM lParam//[in] Specifies the application-defined value given in EnumWindows or EnumDesktopWindows. 
                                                    )
{
TRACE0("CSingleInstanceApp::FindFirstInstance()\n");
DWORD dwID;
::GetWindowThreadProcessId(hWnd, &dwID);
bool _DBGPID = false; //TODO: delete temporary test flag D.K.
if(dwID == (DWORD)lParam)
  {
  TRACE1("  Found thread #%d\n", dwID);
  _DBGPID = true;
  //return FALSE; //Stop search
  }

    DWORD result;
    UINT nResult = 0;
    //Send the message to the applications main window (CMainFrame)
    LRESULT ok = ::SendMessageTimeout(
                        hWnd,
                        CSingleInstanceApp::m_nMsgId,
                        (WPARAM)&nResult, 
                        0, 
                        SMTO_BLOCK|SMTO_ABORTIFHUNG,
                        200,
                        &result
                        );
   if (ok == 0)
      // ignore this and continue
      return TRUE; 
TRACE2("  result = %d (%X)\n", nResult, result);
   if (result == m_nMsgId)
      { 
      // found it      
//      HWND* target = (HWND *)lParam;
//      *target = hWnd;


        //Put the thread that created the first copy of the application into
        //the foreground and activate the window
      ::SetForegroundWindow(hWnd);
      if(!::IsWindowVisible(hWnd))
        ::ShowWindow(hWnd, SW_SHOWNORMAL);
      if (::IsIconic(hWnd))          
        ::ShowWindow(hWnd, SW_RESTORE);

      if (!_DBGPID)
        AfxMessageBox(_T("PID error"), MB_OK|MB_ICONSTOP  );
      return FALSE; // stop search
      }
   // continue search
   return TRUE;
}

//-----------------------------------------------------------------------------
/*Enables Dynamic Data Exchange (DDE). By enabling DDE, MDI or SDI application
  could open a document from another application ( for example by selecting
  a document in Windows Explorer). Call this metof in InitInstance() after
  RegisterShellFileTypes().
 */
void CSingleInstanceApp::RegisterDde()
{
POSITION pos = GetFirstDocTemplatePosition();
CString strFileTypeId;
LPCTSTR szDdeOpen = _T("[open(\"%1\")]");

while (pos)
  {
  CDocTemplate* pTemplate = GetNextDocTemplate(pos);
  if (pTemplate->GetDocString(strFileTypeId, CDocTemplate::regFileTypeId) && 
      !strFileTypeId.IsEmpty() )
    {
    CString strTemp;
    strTemp.Format(_T("%s\\shell\\open\\ddeexec"), (LPCTSTR)strFileTypeId);
    ::RegSetValue(HKEY_CLASSES_ROOT, strTemp, REG_SZ,
                            szDdeOpen, lstrlen(szDdeOpen) * sizeof(TCHAR));
    strTemp += _T("\\Application");
    CString strAppName = AfxGetAppName();
    ::RegSetValue(HKEY_CLASSES_ROOT, strTemp, REG_SZ, strAppName, strAppName.GetLength());
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
// CSingleInstanceApp message handlers

//void /*LRESULT*/ CSingleInstanceApp::OnFindFirstInstance(WPARAM ppResult, LPARAM)
/*{
TRACE0("CSingleInstanceApp::OnFindFirstInstance()\n");
*(UINT*)ppResult = CSingleInstanceApp::m_nMsgId;
   //return CSingleInstanceApp::m_nMsgId;
} */

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2004-10-01 22:35:22  Darko           stdafx.h
 *  4    Biblioteka1.3         2003-09-15 02:44:19  Darko           Uses PID as
 *       unique identifier
 *  3    Biblioteka1.2         2003-09-15 01:53:21  Darko           Displaying top
 *       window mived to FindFirstInstance()
 *  2    Biblioteka1.1         2003-09-12 16:12:02  Darko           comment
 *  1    Biblioteka1.0         2003-09-12 13:09:19  Blazimir Radovic 
 * $
 *  0    2k3-07-17 Blazimir Radovic
 *****************************************************************************/
