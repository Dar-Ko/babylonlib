/*$Workfile: S:\_SrcPool\Cpp\Samples\HtmlIO\Src\TestXmlString.cpp$: implementation file
  $Revision: 3$ $Date: 2005-04-06 14:53:39$
  $Author: Darko Kolakovic$

  Test XML string conversion
  Copyright: CommonSoft Inc.
  2005-03-16 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "KStrConvert.h" //CStrToWide class, CWideToStr class
#include "KXmlStringData.h"  //CXmlStringData class

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);

bool TestXmlString();

//-----------------------------------------------------------------------------
/*Function validates XML string conversions.

  Returns: true if successful, otherwise returns false.
 */
bool TestXmlString()
{
TsWriteToView(_T("TestXmlString()\r\n"));
bool bRes = true;
const wchar_t* wszResult = NULL;
const char*     szResult = NULL;


//Test construction
TESTENTRY logEntry =
  {_T("CStrToWide()"), _T("KStrConvert.h"), bRes};

CStrToWide strTestA("");
CStrToWide strTestB("Ab Iove principium ");

logEntry.m_bResult = bRes;
LogTest(&logEntry);

logEntry.m_szObjectName = _T("CWideToStr::CWideToStr()");
logEntry.m_szFileName = _T("KStrConvert.h");

CWideToStr wstrTestA(L"Un sot, quand il sait le latin, n'est jamais tout a fait un sot.");
logEntry.m_bResult = bRes;
LogTest(&logEntry);


//Test assignment
logEntry.m_szObjectName = _T("CStrToWide::operator=()");
logEntry.m_szFileName = _T("KStrConvert.h");

strTestA = strTestB;

logEntry.m_bResult = bRes;
LogTest(&logEntry);

//Test coercion operators
logEntry.m_szObjectName = _T("CWideToStr::operator char*()");
logEntry.m_szFileName = _T("KStrConvert.h");

szResult  = wstrTestA;
TsWriteToViewLn(wstrTestA);

logEntry.m_bResult = bRes;
LogTest(&logEntry);

logEntry.m_szObjectName = _T("CWideToStr::operator wchar_t*()");
logEntry.m_szFileName = _T("KStrConvert.h");

wszResult = strTestA;
TsWriteToViewLn(strTestA);

logEntry.m_bResult = bRes;
LogTest(&logEntry);

//Test CXmlStringData construction
logEntry.m_szObjectName = _T("CXmlStringData::CXmlStringData(const char*, int)");
logEntry.m_szFileName = _T("KXmlString.cpp");

CXmlStringData testxXml((LPCTSTR)strTestA, 6);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2005-04-06 14:53:39  Darko Kolakovic Implmented
 *       XmlTypedefs
 *  2    Biblioteka1.1         2005-03-26 01:15:34  Darko           CXmlString test
 *  1    Biblioteka1.0         2005-03-21 03:23:32  Darko           
 * $
 *****************************************************************************/
