/*$RCSfile: KWinFileIni.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/01/06 22:27:07 $
  $Author: ddarko $

  Configuration file handles application's setting
  Copyright: CommonSoft Inc.
  1990 Darko Kolakovic
 */

#include "stdafx.h"
#include "KFileIni.h" //Declarations

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
CCfgFile::CCfgFile(LPCTSTR szFilename) :
  
{
TRACE()
if ((szFilename != NULL) && (szFilename[0] != T('\0')))
  m_strFile = szFilename;
}

CCfgFile::~CCfgFile()
{
}

//-----------------------------------------------------------------------------
/*
 */
void CCfgFile::Read()
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
void CCfgFile::Save(CString strWrite)
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
 *$Log: KWinFileIni.cpp,v $
 *Revision 1.1  2009/01/06 22:27:07  ddarko
 *moved from archive
 *
 *****************************************************************************/
