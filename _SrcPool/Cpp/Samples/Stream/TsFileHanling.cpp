/*$Workfile: TsFileHanling.cpp$: implementation file
  $Revision: 3$ $Date: 16/07/2002 12:41:55 AM$
  $Author: Darko$

  Test file handling
  Copyright: CommonSoft Inc.
  Mar 2k2 D.Kolakovic
*/

// Group=Examples

#include "StdAfx.h"

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

  #ifdef _MSC_VER /*MS VC/C++ - Disable warning */
    //Fix for the warning(4786) cannot debug code with symbols longer 
    //than 255 characters
  #pragma warning (disable: 4786)
  #endif
#endif

#include <vector>
#include <iostream>
#include <iomanip.h>  //std::endl
#include "KFileNmB.h" //CFileNameBrowser class

extern CString FindOldestFile(LPCTSTR strDirectoryPath,LPCTSTR strFileExt);
extern LPCTSTR CreateTmpFileName(CString& strResult, LPCTSTR strPrefix);

//TestFileHandling()-----------------------------------------------------------
/*Test file handling functions.
 */
bool TestFileHandling()
{
cout << endl << "====================" << endl;
cout << "TestFileHandling()" << endl;
bool bResult = true;
std::vector<std::string> listFileNames;

  //Test browsing a directory
CFileNameBrowser FileName("*");
while(!FileName.IsLastFileFound())
  {
  listFileNames.push_back(++FileName);
  cout << listFileNames.size() << ".\t" 
    << (LPCTSTR)FileName 
    << (FileName.IsDirectory()? _T(" directory ") : _T("")) 
    << endl;
  }

  //Find oldest file
CString strOldFile;
CString strDirectory = "./";
strOldFile = FindOldestFile(strDirectory,NULL);
if ((GetLastError() == ERROR_SUCCESS) && !strOldFile.IsEmpty())
  {
  strDirectory += strOldFile;
  cout << _T("oldest file is ") << (LPCTSTR)strDirectory << endl;
  }

  //Create Tmp File Name
LPCTSTR szTmpFileName = CreateTmpFileName(strDirectory,"New");
if( szTmpFileName != NULL )
  cout << _T("Unique file name is ") << szTmpFileName << endl;
else
  bResult = false;

return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 3    Biblioteka1.2         16/07/2002 12:41:55 AMDarko           Fixed VSS Log 
 *      tag
 * 2    Biblioteka1.1         04/04/2002 11:49:18 PMDarko          
 *      CreateTmpFileName()
 * 1    Biblioteka1.0         12/03/2002 10:01:17 PMDarko           
 *$
 *****************************************************************************/
