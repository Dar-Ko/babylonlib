/*$Workfile: KFileFindOld.cpp$: implementation file
  $Revision: 4$ $Date: 2007-05-03 15:53:45$
  $Author: Darko Kolakovic$

  Find oldest File Function
  Copyright: CommonSoft Inc.
  Nov 98 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifdef WIN32
  #ifdef _AFXDLL
    //MSVC and MFC
    #include <afxwin.h>
  #else          //use MS SDK
    #include <windows.h>
    #ifndef TRACE0
      #ifndef _T
        #include "KTChar.h"
      #endif
      #include "KTrace.h" //Debugging macros
    #endif
    
    #ifdef _STL
      #include <string> //base string class
    #endif
    #include "KString.h" //CString class
  #endif

  #include "KFileNmB.h" //CFileNameBrowser class

  #ifdef _DEBUG
    #define new DEBUG_NEW
    #undef THIS_FILE
    static char THIS_FILE[] = __FILE__;
  #endif

//FindOldestFile()-------------------------------------------------------------
/*Searches for the oldest file on the specified directory. Age of the file
  is based on the last time file has been written. To get extended error
  information, call GetLastError().

  Note: Microsoft Windows specific (Win).

  Example:
    CString strOldFile;
    CString strDirectory = "C:\Personal Folder\";
    strOldFile = FindOldestFile(strDirectory,".Log");
    if ((GetLastError() == ERROR_SUCCESS) && !strOldFile.IsEmpty())
      {
      strDirectory += strOldFile;
      DeleteFile(strDirectory);
      }
 */
CString FindOldestFile(LPCTSTR strDirectoryPath, //[in] root directory
                       LPCTSTR strFileExt //File name extension; if NULL or empty
                                          //functions searches for any file
                      )
{
TRACE1(_T("FindOldestFile() in %s\n"),strDirectoryPath);

  //Create file name
CString strFileName;
strFileName = strDirectoryPath;
TCHAR chTmp = strFileName[strFileName.GetLength()-1];
if (chTmp != _T('\\') && chTmp != _T('/') )
  {
  strFileName += _T('/');  //Add directory separator
  }

if ((strFileExt == NULL) || (strFileExt[0] == _T('\0')) )
  strFileName += _T("*.*");
else
  {
  strFileName += _T('*');
  if (strFileExt[0] != _T('.'))
    strFileName += _T('.');
  strFileName += strFileExt;
  }

double timeOld     = 0.0;
double timeCurrent = 0.0;
double timeHighMultiplier    = static_cast< double >( 0xFFFFFFFF );
timeHighMultiplier++;

SetLastError(ERROR_SUCCESS);
CFileNameBrowser FileName(strFileName);
if (GetLastError() == ERROR_SUCCESS)
  {
  while (FileName.IsDirectory() && !FileName.IsLastFileFound())
    ++ FileName; //Find first file name which is not a directory
  if(!FileName.IsDirectory())
    {
      //If this file is only file in the directory, it is oldest file.
    timeOld  = FileName.FindData().ftLastWriteTime.dwLowDateTime;
    timeOld += static_cast< double >
              (static_cast< double >
                  ( FileName.FindData().ftLastWriteTime.dwHighDateTime ) *
                    timeHighMultiplier);
    strFileName = (LPCTSTR)FileName;

    while(!FileName.IsLastFileFound())
      {
      if (!FileName.IsDirectory()) //Skip directories
        {
        timeCurrent  = FileName.FindData().ftLastWriteTime.dwLowDateTime;
        timeCurrent += static_cast< double >
                    (static_cast< double >
                        ( FileName.FindData().ftLastWriteTime.dwHighDateTime ) *
                          timeHighMultiplier );

        if (timeCurrent < timeOld)  //This file is older
          {
          timeOld = timeCurrent;
          strFileName = (LPCTSTR)FileName;
          }
        }
      ++FileName;
      }
    }
  }

if (GetLastError() == ERROR_NO_MORE_FILES) //Not considered as an error
  {
  SetLastError(ERROR_SUCCESS);
  }

return strFileName;
}

///////////////////////////////////////////////////////////////////////////////
#endif //WIN32
/******************************************************************************
 *$Log: 
 * 4    Biblioteka1.3         2007-05-03 15:53:45  Darko Kolakovic Console SBCS
 * 3    Biblioteka1.2         2002-07-16 01:40:56  Darko           Fixed VSS Log 
 *      tag
 * 2    Biblioteka1.1         2002-03-13 00:38:11  Darko           
 * 1    Biblioteka1.0         2002-03-12 23:00:39  Darko           
 *$
 *****************************************************************************/
