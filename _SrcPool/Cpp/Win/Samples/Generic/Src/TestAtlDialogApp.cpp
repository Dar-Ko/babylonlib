/*$RCSfile: TestAtlDialogApp.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2009/02/23 20:06:44 $
  $Author: ddarko $

  Application's starting point
  2008-12-15
 */

// Group=Examples Windows

#include "stdatl.h"
#include "MainDlg.h" //CMainDlg class

CAppModule _Module; //the main application's module

//-----------------------------------------------------------------------------
/*
  Note: uses Microsoft Active Template Library (ATL);
        Windows Template Library (WTL);
        Microsoft Windows specific (Win32).
 */
int Run(LPTSTR /*lpstrCmdLine*/ = NULL,
        int nCmdShow = SW_SHOWDEFAULT
        )
{
ATLTRACE(_T("Run()\n"));
CMessageLoop theLoop;
_Module.AddMessageLoop(&theLoop);

CMainDlg dlgMain;

if(dlgMain.Create(NULL) == NULL)
  {
  ATLTRACE(_T("Main dialog creation failed!\n"));
  return 0;
  }

dlgMain.ShowWindow(nCmdShow);

int nRet = theLoop.Run();

_Module.RemoveMessageLoop();
return nRet;
}

//-----------------------------------------------------------------------------
/*
  Note: uses Microsoft Active Template Library (ATL);
        Windows Template Library (WTL);
        Microsoft Windows specific (Win32).
 */
int WINAPI _tWinMain(HINSTANCE hInstance,
                     HINSTANCE /*hPrevInstance*/,
                     LPTSTR lpstrCmdLine,
                     int nCmdShow
                     )
{
ATLTRACE(_T("_tWinMain()\n"));
HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
ATLASSERT(SUCCEEDED(hRes));

//This resolves ATL window thunking problem when Microsoft Layer for Unicode
//(MSLU) is used
::DefWindowProc(NULL, 0, 0, 0L);

AtlInitCommonControls(ICC_BAR_CLASSES);// add flags to support other controls

hRes = _Module.Init(NULL, hInstance);
ATLASSERT(SUCCEEDED(hRes));

int nRet = Run(lpstrCmdLine, nCmdShow);

_Module.Term();
::CoUninitialize();

return nRet;
}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: TestAtlDialogApp.cpp,v $
 * Revision 1.3  2009/02/23 20:06:44  ddarko
 * Test application for  ATL/WTL controls
 *
 * Revision 1.2  2009/02/23 19:12:11  ddarko
 * Modified generic main
 *
 ******************************************************************************/
