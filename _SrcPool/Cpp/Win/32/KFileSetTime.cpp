/*$Workfile: KFileSetTime.cpp$: implementation file
  $Revision: 1$ $Date: 2002-02-05 21:54:30$
  $Author: Darko$

  Set file creation time
  Copyright: CommonSoft Inc.
  Darko Kolakovic Jun 98
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#pragma warning(disable : 4214 4201 4514 4115) //TODO: check those level 4 warnings! D.K.

#ifndef __AFXWIN_H__
  #include <AfxWin.h>  //CFileException
#endif
#pragma hdrstop

//SetFileCreationTime()--------------------------------------------------------
/*Sets the creation date for the file to the time contained in lpCreationTime.
  Function uses CFileException to display any possible error in file creation.
  Returns: TRUE if lpszFilename is a valid filename, lpCreationTime is a valid
  FILETIME structure, and file have write access.

  Note: uses Microsoft Fundation Library (MFC),
        Microsoft Windows specific (Win).

  Example:
    void EqualTimes(LPCTSTR lpszFileNameSrc,LPCTSTR lpszFileNameTarget)
      {
      extern
      BOOL SetFileCreationTime(LPCTSTR lpszFileName,//file path
                     const FILETIME* lpCreationTime	//time the file was created
                           );
      extern
      BOOL GetFileCreationTime(LPCTSTR lpszFileName, //file path
                           LPFILETIME lpCreationTime //time the file was created
                           );

      FILETIME ftCreationTime;
      if(GetFileCreationTime(lpszFileNameSrc,&ftCreationTime))
        {
        SetFileCreationTime(lpszFileNameTarget,&ftCreationTime);
        }
      }

  TODO: check level 4 warnings
 */
BOOL SetFileCreationTime(LPCTSTR lpszFileName,          //[in] file path
                         const FILETIME* lpCreationTime	//[in] new file creation
                                                        //time to be set
                         )
{
BOOL bResult = FALSE;
try
  {
  if ((lpszFileName != NULL) && (lpCreationTime != NULL))
    {
    HANDLE hFile = CreateFile(lpszFileName,
                              GENERIC_WRITE, //The file must be opened with write access.
                              FILE_SHARE_READ | FILE_SHARE_WRITE,
                              NULL,
                              OPEN_EXISTING,
                              0, NULL );

    if (hFile != INVALID_HANDLE_VALUE)
      {
      bResult = SetFileTime(hFile, lpCreationTime, NULL, NULL);
      CloseHandle(hFile);
      }
    else
      {
      CFileException::ThrowOsError((LONG)::GetLastError());
      }
    }
  }
catch(CFileException* f)
  {
  f->ReportError();
  f->Delete();
  }
return bResult;
}

//GetFileCreationTime()--------------------------------------------------------
/*Retrieves the date and time that a file was created.
  Function uses CFileException to display any possible error in file creation.
  Returns: TRUE if lpszFilename is a valid filename, lpCreationTime is a valid
  FILETIME structure, and file have read access.

  Note: uses Microsoft Fundation Library (MFC),
        Microsoft Windows specific (Win).

 */
BOOL GetFileCreationTime(LPCTSTR lpszFileName,      //[in] file name for which
                                                    //to get dates and times
                         LPFILETIME lpCreationTime	//[out] points to a structure
                                                    //to receive the date and
                                                    //time the file was created
                         )
{
BOOL bResult = FALSE;
try
  {
  if ((lpszFileName != NULL) && (lpCreationTime != NULL))
    {
    HANDLE hFile = CreateFile(lpszFileName,
                              GENERIC_READ, //The file must be opened with write access.
                              FILE_SHARE_READ | FILE_SHARE_WRITE,
                              NULL,
                              OPEN_EXISTING,
                              0, NULL );

    if (hFile != INVALID_HANDLE_VALUE)
      {
      bResult = GetFileTime(hFile, lpCreationTime, NULL, NULL);
      CloseHandle(hFile);
      }
    else
      {
      CFileException::ThrowOsError((LONG)::GetLastError());
      }
    }
  }
catch(CFileException* f)
  {
  f->ReportError();
  f->Delete();
  }
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 *$Log: 
 * 1    Biblioteka1.0         2002-02-05 21:54:30  Darko           
 *$
 *****************************************************************************/