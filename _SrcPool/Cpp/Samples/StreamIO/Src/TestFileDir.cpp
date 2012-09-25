/*$RCSfile: TestFileDir.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2012/09/25 18:58:21 $
  $Author: ddarko $

  Test file directory handling
  2012-09 D.Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#if !defined _KTESTLOG_H_
 #error wrong stdafx.h header is included!
 //The project options for this module have "..\..\Win\32" in 
 //additional include path
#endif
extern CTestLog g_logTest;   //general test logger

/*Note: A MSVC LNK2005 error occurs when the CRT library and MFC libraries 
  (nafxcwd.lib, libcmtd.lib) are linked in the wrong order in Visual C++
  See also: MSDN Article ID: 148652 http://support.microsoft.com/kb/148652
 */
#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

  #ifdef _MSC_VER /*MS VC/C++ - Disable warning */
    //Fix for the warning(4786) cannot debug code with symbols longer
    //than 255 characters
  #pragma warning (disable: 4786)
  #endif
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);

#include <vector>

#if _MSC_VER < 1300
  //MSVC/C++ 6.0 or lesser
  #pragma include_alias(<iostream>, <iomanip.h>)
#endif
#include <iostream> //std::endl

#include "KString.h"  //CString class

extern CString GetExeDirectory();
extern CString GetAppPath();

//-----------------------------------------------------------------------------
/*Test file folders handling functions.

  Returns true if test is successful; otherwise returns false.

  Note: uses Standard Template Library (STL).
 */
bool TestFileFolder()
{
TsWriteToViewLn(_T("Start validation of various file folder manipulators"));

bool bResult = true;
try
  {
  std::vector<tstring> listFileNames;

  g_logTest.m_szObjectName = _T("MAX_PATH");
  g_logTest.m_szFileName   = _T("windef.h"); //function or object file name
  g_logTest.m_bResult      = false;          //result of the test

  std::_tcout << g_logTest.m_szObjectName << _T(" = ") << MAX_PATH <<  _T(" characters\n");
  g_logTest.m_bResult = true;
  g_logTest.LogResult(bResult);

  //Get the path of the executable file of the current process.
  g_logTest.m_szObjectName = _T("GetModuleFileName()");
  g_logTest.m_szFileName   = _T("winbase.h"); //function or object file name

  TCHAR szPath[MAX_PATH];
  DWORD nSize = GetModuleFileName(NULL, szPath, MAX_PATH);
  if ((nSize == 0) || GetLastError() == ERROR_INSUFFICIENT_BUFFER)
    {
    g_logTest.m_bResult = false;
    std::_tcout << g_logTest.m_szObjectName
                << _T(" failed with error ") << GetLastError() <<  _T("!\n");
    }
  else
    {
    std::_tcout << _T("Executable file: ") << szPath<<  _T("\n");
    }
  g_logTest.LogResult(bResult);

  if (g_logTest.m_bResult)
    {
    //Get the current directory for the current process.
    g_logTest.m_szObjectName = _T("GetCurrentDirectory()");
    nSize = GetCurrentDirectory(MAX_PATH, szPath);
    if (nSize == 0)
      {
      g_logTest.m_bResult = false;
      std::_tcout << g_logTest.m_szObjectName
                  << _T(" failed with error ") << GetLastError() <<  _T("!\n");
      }
    else
      {
      std::_tcout << _T("Current folder: ") << szPath<<  _T("\n");
      }
    }
  g_logTest.LogResult(bResult);

  if (g_logTest.m_bResult)
    {
    //Test obtaining current moudle folder
    g_logTest.m_szObjectName = _T("GetAppPath()");
    g_logTest.m_szFileName   = _T("KGetAppPath.cpp"); //function or object file name
    CString strPath = GetAppPath();
    g_logTest.m_bResult = !strPath.IsEmpty();
    std::_tcout << g_logTest.m_szObjectName
                << _T(": ") << (LPCTSTR)strPath<<  _T("\n");
    }
  g_logTest.LogResult(bResult);

  if (g_logTest.m_bResult)
    {
    //Test obtaining current moudle folder
    g_logTest.m_szObjectName = _T("GetExeDirectory()");
    g_logTest.m_szFileName   = _T("KDirGetExe.cpp"); //function or object file name
    CString strPath = GetExeDirectory();
    g_logTest.m_bResult = !strPath.IsEmpty();
    std::_tcout << g_logTest.m_szObjectName
                << _T(": ") << (LPCTSTR)strPath<<  _T("\n");
    }
  g_logTest.LogResult(bResult);


  }
catch(std::out_of_range& eoor)
  {
  std::_tcout << _T("STL out of range error occured! ") << eoor.what() << std::endl;
  bResult = false;
  }
catch(const std::exception& e)  
  {
  std::_tcout << _T("STL exception error occured! ") << e.what() << std::endl;
  bResult = false;
  }
catch(...)
  {
  TsWriteToViewLn(_T("An exception error occured!"));
  bResult = false;
  }
TsWriteToViewLn(LOG_EOT);

return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: TestFileDir.cpp,v $
 *Revision 1.1  2012/09/25 18:58:21  ddarko
 *Created
 *
 *****************************************************************************/
