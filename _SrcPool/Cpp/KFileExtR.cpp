/*$Workfile: KFileExtR.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  CStdioFile class extension: I/O  operators
  Copyright: CommonSoft Inc.
  May 98 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KFileExtR.h" //Declarations

#ifndef WIN32    //Windows 32b application
  #pragma error ("Requred Windows 32b")
#endif

//operator<<()-----------------------------------------------------------------
/*Writes a single line of text. The terminating null character (‘\0’) is not 
  written to the file. Any newline character is written to the file 
  as a CR-LF pair.

  Throws: CFileException::diskFull

  Note: uses Microsoft Fundation Library (MFC),
        Microsoft Windows specific (Win).
 */
CStdioFile& AFXAPI operator<<(CStdioFile& fileDestination,  //[in] destination file
                                     //stream
                              LPCTSTR strSource //[in] a zero-terminated string
                                    //to be written to file
                              )
{
ASSERT(strSource != NULL);
ASSERT(fileDestination.m_pStream != NULL);

if (_fputts(strSource, fileDestination.m_pStream) == _TEOF)
  AfxThrowFileException(CFileException::diskFull, _doserrno, fileDestination.GetFileName());
return fileDestination;
}

//operator<<()-----------------------------------------------------------------
/*Writes single character to a file object.

  Throws: CFileException::diskFull

  Note: uses Microsoft Fundation Library (MFC),
        Microsoft Windows specific (Win).
 */
CStdioFile& AFXAPI operator<<(CStdioFile& fileDestination, //[in] destination file
                                     //stream
                              TCHAR chSource //[in] a character to be written
                                     //to file
                              )
{
if (_fputtc(chSource, fileDestination.m_pStream) == _TEOF)
  AfxThrowFileException(CFileException::diskFull, _doserrno, fileDestination.GetFileName());
return fileDestination;
}

//operator>>()-----------------------------------------------------------------
/*Reads a single line of text. Reading is stopped by a CR-LF pair.
  A null character (‘\0’) is appended in either case. 

  Note: uses Microsoft Fundation Library (MFC),
        Microsoft Windows specific (Win).
 */
CStdioFile& AFXAPI operator>>(CStdioFile& fileSource, //[in] source file stream
                              CString& strDestination //[in] destination string object
                              )
{
fileSource.ReadString(strDestination);
return fileSource;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 1    Biblioteka1.0         8/27/02 5:04:23 PM   Darko Kolakovic 
 *$
 *****************************************************************************/
