// Stream.cpp : Defines the entry point for the console application.
//

// Group=Examples

#include "StdAfx.h"
#include "Stream.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TestFileHandling();
/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

//_tmain()---------------------------------------------------------------------
/*
 */
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
int nRetCode = EXIT_SUCCESS;

  //Initialize MFC and print and error on failure
if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
  {
	cerr << _T("Fatal Error: MFC initialization failed") << endl;
	nRetCode = EXIT_FAILURE;
  }
else
  {
	// TODO: code your application's behavior here.
	CString strHello;
	strHello.LoadString(IDS_HELLO);
	cout << (LPCTSTR)strHello << endl;

  if (!TestFileHandling())
    {
    cout << _T("  Failed!") << endl;
   	nRetCode = EXIT_FAILURE;
    }
  }

return nRetCode;
}


