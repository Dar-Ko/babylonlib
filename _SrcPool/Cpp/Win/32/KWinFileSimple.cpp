/*$RCSfile: KWinFileSimple.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/05/07 21:13:22 $
  $Author: ddarko $

  Basic file-handling API wrapper.
  Copyright: CommonSoft Inc.
  2008-12-12 Darko Kolakovic
 */

#include "stdafx.h"
#include "KFileSimple.h" //Declarations

#ifndef WIN32    //Windows 32b application
  #pragma error ("Requred Windows 32b")
#endif

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[]=__FILE__;
  #define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/*
 */
CFileSimple::CFileSimple(LPCTSTR szFilename) :

{
TRACE()
if ((szFilename != NULL) && (szFilename[0] != T('\0')))
  m_strFile = szFilename;
}

CFileSimple::~CFileSimple()
{
}

//-----------------------------------------------------------------------------
/*
 */
void CFileSimple::Read()
{
try
  {
  const int BUFFER_SIZE = 1024;
  TCHAR szBuff[BUFFER_SIZE];

  CFile oFile(m_strFile,
              CFile::modeCreate |
              CFile::modeNoTruncate |
              CFile::modeRead |
              CFile::shareExclusive
              );

  unsigned int nRead = oFile.Read(szBuff, BUFFER_SIZE - 1);
  szBuff[iRead] = _T('\0');

  }
catch (CFileException e)
  {
  CString strErr;
  strErr.Format(_T("Error when reading configuration file! Error: %s"), e);
  AfxMessageBox(strErr);
  }
}

//-----------------------------------------------------------------------------
/*
 */
void CFileSimple::Write(CString strWrite)
{
try
  {
  CFile oFile(m_strFile,
              CFile::modeCreate |
              CFile::modeWrite |
              CFile::shareExclusive
              );
  oFile.Write(strWrite, strWrite.GetLength());
  oFile.Flush();
  }
catch (CFileException e)
  {
  AfxMessageBox(_T("Error: %s"), e);
  }
}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: KWinFileSimple.cpp,v $
 *Revision 1.1  2009/05/07 21:13:22  ddarko
 *Created
 *
 *****************************************************************************/
