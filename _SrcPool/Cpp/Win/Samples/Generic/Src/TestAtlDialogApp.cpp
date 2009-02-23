/*$RCSfile: TestAtlDialogApp.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/02/23 19:12:11 $
  $Author: ddarko $

  Application's starting point
  2008-12-15
 */

#include "stdatl.h"

#include "resource.h"

//#include "aboutdlg.h"
#include "MainDlg.h" //CMainDlg template

CAppModule _Module;

//-----------------------------------------------------------------------------
/*
 */
int Run(LPTSTR /*lpstrCmdLine*/ = NULL,
        int nCmdShow = SW_SHOWDEFAULT)
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
 */
int WINAPI _tWinMain(HINSTANCE hInstance,
                     HINSTANCE /*hPrevInstance*/,
                     LPTSTR lpstrCmdLine,
                     int nCmdShow)
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
 * Revision 1.2  2009/02/23 19:12:11  ddarko
 * Modified generic main
 *
 ******************************************************************************/
