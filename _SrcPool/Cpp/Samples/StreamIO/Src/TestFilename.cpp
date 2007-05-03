/*$Workfile: TestFilename.cpp$: implementation file
  $Revision: 5$ $Date: 2007-05-03 15:57:34$
  $Author: Darko Kolakovic$

  Test file names handling
  Copyright: CommonSoft Inc.
  Mar 2k2 D.Kolakovic
*/

// Group=Examples

#include "stdafx.h"
extern CTestLog g_logTest;   //general test logger

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
#include <iostream>
//#include <iomanip.h>  //std::endl 
#include "KString.h"  //CString class
#include "KFileNmB.h" //CFileNameBrowser class

extern CString FindOldestFile(LPCTSTR strDirectoryPath, LPCTSTR strFileExt);
extern LPCTSTR CreateTmpFile(CString& strResult, LPCTSTR strPrefix);

//-----------------------------------------------------------------------------
/*Test file names handling functions.

  Returns true if test is successful; otherwise returns false.

  Note: uses Standard Template Library (STL).
 */
bool TestFilename()
{
TsWriteToViewLn(_T("Start validation of various file name manipulators"));

bool bResult = true;
std::vector<tstring> listFileNames;

//Test log  creation
g_logTest.m_szObjectName = _T("CFileNameBrowser::CFileNameBrowser(LPCTSTR)");
g_logTest.m_szFileName   = _T("KFileNmB.cpp");//function or object file name
g_logTest.m_bResult      = false;              //result of the test

//Test browsing a directory
TsWriteToViewLn(_T("CFileNameBrowser()"));
CFileNameBrowser FileName(_T("*")); //Find any file in the working directory
bResult = FileName.IsFileFound();
g_logTest.LogResult(bResult);
g_logTest.m_szObjectName = _T("CFileNameBrowser::IsFileFound()");
g_logTest.LogResult(bResult);

//Browse working folder
g_logTest.m_szObjectName = _T("CFileNameBrowser::operator ++()");
while(!FileName.IsLastFileFound())
  {
  listFileNames.push_back(++FileName);
  std::_tcout << listFileNames.size() << _T(".\t" )
    << (LPCTSTR)FileName 
    << (FileName.IsDirectory()? _T(" directory ") : _T("")) 
    << std::endl;
  }
g_logTest.LogResult(bResult);

g_logTest.m_szObjectName = _T("CFileNameBrowser::IsLastFileFound()");
bResult = FileName.IsLastFileFound();
g_logTest.LogResult(bResult);

//Test searching for the oldest file
TsWriteToViewLn(_T("FindOldestFile()"));
g_logTest.m_szObjectName = _T("FindOldestFile(LPCTSTR, LPCTSTR)");
g_logTest.m_szFileName   = _T("KFileFindOld.cpp");//function or object file name

CString strOldFile;
CString strDirectory = "./";
strOldFile = FindOldestFile(strDirectory,NULL);
if ((GetLastError() == ERROR_SUCCESS) && !strOldFile.IsEmpty())
  {
  strDirectory += strOldFile;
  std::_tcout << _T("oldest file is ") << (LPCTSTR)strDirectory << std::endl;
  }
else
  {
  std::_tcout << _T("Failure!")<< std::endl;
  bResult = false;
  }
  
g_logTest.LogResult(bResult);
  
//Test creating a temporary file
TsWriteToViewLn(_T("CreateTmpFile()"));
g_logTest.m_szObjectName = _T("CreateTmpFile(CString&, LPCTSTR)");
g_logTest.m_szFileName   = _T("KFileTmp.cpp");//function or object file name

LPCTSTR szTmpFileName = CreateTmpFile(strDirectory,_T("New"));
if( szTmpFileName != NULL )
  std::_tcout << _T("Temporary file is ") << szTmpFileName << std::endl;
else
  {
  std::_tcout << _T("Failure!")<< std::endl;
  bResult = false;
  }
g_logTest.LogResult(bResult);

TsWriteToViewLn(LOG_EOT);

return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 5    Biblioteka1.4         2007-05-03 15:57:34  Darko Kolakovic TestFilename()
 * 4    Biblioteka1.3         2007-05-03 11:25:05  Darko Kolakovic 
 * 3    Biblioteka1.2         2002-07-16 01:41:55  Darko           Fixed VSS Log 
 *      tag
 * 2    Biblioteka1.1         2002-04-05 00:49:18  Darko          
 *      CreateTmpFileName()
 * 1    Biblioteka1.0         2002-03-12 23:01:17  Darko           
 *$
 *****************************************************************************/
