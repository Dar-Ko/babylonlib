/*$Workfile: main.cpp$: implementation file
  $Revision: 1$ $Date: 2004-11-08 16:38:21$
  $Author: Darko Kolakovic$

  Test debugging and tracing routines.
  Copyright: CommonSoft Inc.
  2004-08-12 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "Resource.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object
CWinApp theApp;

#ifdef _MSC_VER     /*Microsoft Visual Studio C/C++ compiler                 */
  #ifndef _CONSOLE
    #error "define _CONSOLE macro in the project"
  #endif
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern int TestAssertMain();

//-----------------------------------------------------------------------------
/*Validates different debugging and tracing routines.
  Defines the entry point for the console application.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesfull. Otherwise
  a non-zero error code is returned.

  Note: uses Microsoft Fundation Library (MFC);
        Microsoft Windows specific (Win).
 */
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
int nRetCode = EXIT_SUCCESS;

//Initialize MFC and print and error on failure
if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
  {
  TsWriteToViewLn(_T("Fatal Error: MFC initialization failed"));
  nRetCode = EXIT_FAILURE;
  }
else
  {
  nRetCode = TestAssertMain();
  }

return nRetCode;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  3    Biblioteka1.2         23/08/2004 6:00:29 PMDarko           Unicode build
 *  2    Biblioteka1.1         20/08/2004 5:21:27 PMDarko           Created buld
 *       configurations
 *  1    Biblioteka1.0         17/08/2004 6:31:37 PMDarko
 * $
 *****************************************************************************/

