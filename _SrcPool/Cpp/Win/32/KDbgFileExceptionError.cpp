/*$Workfile: S:\_SrcPool\Cpp\Win\32\KDbgFileExceptionError.cpp$: implementation file
  $Revision: 3$ $Date: 2005-04-26 11:29:07$
  $Author: Darko Kolakovic$

  Dumps CFileException cause
  Copyright: CommonSoft Inc.
  2003-08 Darko Kolakovic
 */ 

// Group=Diagnostic
#include "stdafx.h"

//-----------------------------------------------------------------------------
/*Dump description of CFileException cause.
  CFileException::m_cause values:

      CFileException::none              No error occurred. 
      CFileException::generic           An unspecified error occurred. 
      CFileException::fileNotFound      The file could not be located. 
      CFileException::badPath           All or part of the path is invalid. 
      CFileException::tooManyOpenFiles  The permitted number of open files was exceeded. 
      CFileException::accessDenied      The file could not be accessed. 
      CFileException::invalidFile       There was an attempt to use an invalid file handle. 
      CFileException::removeCurrentDir  The current working directory cannot be removed. 
      CFileException::directoryFull     There are no more directory entries. 
      CFileException::badSeek           here was an error trying to set the file pointer. 
      CFileException::hardIO            There was a hardware error. 
      CFileException::sharingViolation  SHARE.EXE was not loaded, or a shared region was locked. 
      CFileException::lockViolation     There was an attempt to lock a region that was already locked. 
      CFileException::diskFull          The disk is full. 
      CFileException::endOfFile         The end of file was reached.

  Example:
      try
        {
        CFile f( pFileName, CFile::modeCreate | CFile::modeWrite );
        }
      catch( CFileException* e )
        {
        TRACE(DumpFileExceptionError(e->m_cause));
        e->Delete();
        }

  Note: uses Microsoft Foundation Library (MFC); 
        Microsoft Windows specific (Win).
 */
LPCTSTR DumpFileExceptionError(const int& iCause //[in] value defined by a CFileException enumerated type.

                              )
{
switch(iCause)
  {
  case CFileException::fileNotFound:
    return _T("The file could not be located.");
  case CFileException::badPath:
    return _T("All or part of the path is invalid.");
  case CFileException::tooManyOpenFiles:
    return _T("The permitted number of open files was exceeded.");
  case CFileException::accessDenied:
    return _T("The file could not be accessed.");
  case CFileException::invalidFile:
    return _T("There was an attempt to use an invalid file handle.");
  case CFileException::removeCurrentDir:
    return _T("The current working directory cannot be removed.");
  case CFileException::directoryFull:
    return _T("There are no more directory entries.");
  case CFileException::badSeek:
    return _T("There was an error trying to set the file pointer.");
  case CFileException::hardIO:
    return _T("There was a hardware error.");
  case CFileException::sharingViolation:
    return _T("SHARE.EXE was not loaded, or a shared region was locked.");
  case CFileException::lockViolation:
    return _T("There was an attempt to lock a region that was already locked.");
  case CFileException::diskFull:
    return _T("The disk is full.");
  case CFileException::endOfFile:
    return _T("The end of file was reached."); 
  }

return _T("uknown");
}

/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2005-04-26 11:29:07  Darko Kolakovic Document groups
 *       and typo fixes
 *  2    Biblioteka1.1         2004-10-01 22:34:17  Darko           stdafx.h
 *  1    Biblioteka1.0         2003-08-13 17:36:37  Darko           
 * $
 *****************************************************************************/
