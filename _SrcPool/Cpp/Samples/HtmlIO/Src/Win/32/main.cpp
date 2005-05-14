/*$Workfile: S:\_SrcPool\Cpp\Samples\HtmlIO\Src\Win\32\main.cpp$: implementation file
  $Revision: 1$ $Date: 2005-03-21 02:25:07$
  $Author: Darko$

  Test HTML and XML streams with MFC.
  Copyright: CommonSoft Inc.
  2004-08-12 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "Resource.h"

#ifndef __AFXWIN_H__
  #error include required MFC header files in 'stdafx.h'
#endif

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
extern int TestCommonHtmlIO(int argc, TCHAR* argv[]);

//-----------------------------------------------------------------------------
/*Validates HTML and XML handling routines.
  Defines the entry point for the console application.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.

  Note: uses Microsoft Foundation Library (MFC);
        Microsoft Windows specific (Win).
 */
int _tmain(int argc,      //[in] specifies how many arguments are passed to the
                          //program from the command line. The value of argc is
                          //at least one: the program name.
           TCHAR* argv[], //[in] the program arguments as an array of pointers
                          //to null-terminated strings. The first string 
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
           TCHAR* envp[]  //[in] the user's environment variables as a pointer 
                          //to an array of null-terminated strings. The end of
                          //the array is indicated by a NULL pointer. 
                          //Note: Microsoft Windows specific (Win).
           )
{
int nRetCode = EXIT_SUCCESS;

/*Note: GetModuleHandle(lpModuleName) 
   - lpModuleName [in] Pointer to a null-terminated string that contains the 
     name of the module (either a .dll or .exe file). If the file name extension 
     is omitted, the default library extension .dll is appended. The file name 
     string can include a trailing point character (.) to indicate that the 
     module name has no extension. The string does not have to specify a path. 
     When specifying a path, be sure to use backslashes (\), not forward 
     slashes (/). The name is compared (case independently) to the names of 
     modules currently mapped into the address space of the calling process. 
     If this parameter is NULL, GetModuleHandle returns a handle to the file used 
     to create the calling process.
 */

//Initialize theApp object and print and error on failure
if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
  {
  TsWriteToViewLn(_T("Fatal Error: MFC initialization failed!"));
  nRetCode = EXIT_FAILURE;
  }
else
  {
  TsWriteToViewLn(_T("Start HTML and XML Tests"));
  TsWriteToViewLn(_T(""));

  nRetCode = TestCommonHtmlIO(argc, argv);
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

