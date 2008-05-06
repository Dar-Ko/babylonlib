/*$Workfile: TestFilename.cpp$: implementation file
  $Revision: 6$ $Date: 2007-05-04 17:53:43$
  $Author: Darko Kolakovic$

  Test file names handling
  Copyright: CommonSoft Inc.
  Mar 2k2 D.Kolakovic
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
#include "KFileNmB.h" //CFileNameBrowser class

extern CString FindOldestFile(LPCTSTR strDirectoryPath, LPCTSTR strFileExt);
extern LPCTSTR CreateTmpFile(CString& strResult, LPCTSTR strPrefix);
extern LPCTSTR CreateUniqueFileName(CString& strResult,
                                    LPCTSTR szFilePath,
                                    LPCTSTR szPrefix,
                                    LPCTSTR szExtension);

//-----------------------------------------------------------------------------
/*Test file names handling functions.

  Returns true if test is successful; otherwise returns false.

  Note: uses Standard Template Library (STL).
 */
bool TestFilename()
{
TsWriteToViewLn(_T("Start validation of various file name manipulators"));

bool bResult = true;
try
  {
  std::vector<tstring> listFileNames;

  //Test log  creation
  g_logTest.m_szObjectName = _T("CFileNameBrowser::CFileNameBrowser(LPCTSTR)");
  g_logTest.m_szFileName   = _T("KFileNmB.cpp"); //function or object file name
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
    std::_tcout << (unsigned int)listFileNames.size() << _T(".\t" )
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
  CString strDirectory = _T("./");

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

  //Test creating an unique file name
  TsWriteToViewLn(_T("CreateUniqueFileName()"));
  g_logTest.m_szObjectName = _T("CreateUniqueFileName(LPCTSTR, LPCTSTR)");
  g_logTest.m_szFileName   = _T("KFileUnique.cpp");//function or object file name

  szTmpFileName = CreateUniqueFileName(strDirectory, _T(".\\."),_T("New"), _T("bak"));
  if( szTmpFileName != NULL )
    {
    std::_tcout << _T("File name is ") << szTmpFileName << std::endl;
    }
  else
    {
    std::_tcout << _T("Failure!")<< std::endl;
    bResult = false;
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
 *$Log:
 * 6    Biblioteka1.5         2007-05-04 17:53:43  Darko Kolakovic
 *      CreateUniqueFilename()
 * 5    Biblioteka1.4         2007-05-03 15:57:34  Darko Kolakovic TestFilename()
 * 4    Biblioteka1.3         2007-05-03 11:25:05  Darko Kolakovic
 * 3    Biblioteka1.2         2002-07-16 01:41:55  Darko           Fixed VSS Log
 *      tag
 * 2    Biblioteka1.1         2002-04-05 00:49:18  Darko
 *      CreateTmpFileName()
 * 1    Biblioteka1.0         2002-03-12 23:01:17  Darko
 *$
 *****************************************************************************/
