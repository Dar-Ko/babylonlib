/*$Workfile: TestXmlParser.cpp$: implementation file
  $Revision: 2$ $Date: 2005-03-21 03:22:22$
  $Author: Darko$

  Test XML parsers
  Copyright: CommonSoft Inc.
  2005-03-16 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);

//-----------------------------------------------------------------------------
/*Function validates XML parser framework.

  Returns: true if successful, otherwise returns false.
 * /
bool TestXmlParser(int argc, //[in] specifies how many arguments are passed
                          // to the program from the command line. The value of
                          // argc is at least one: the program name.
                       TCHAR* argv[] //[in] the program arguments as an array of
                          //pointers to null-terminated strings. The first string
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
                       )
{
TsWriteToView(_T("TestXmlParser()\r\n"));
bool bRes = true;
TESTENTRY logEntry =
  {_T("IXmlParser()"), _T("KXmlParserI.h"), bRes};

if (argc > 0)
  {
  TsWriteToView(_T("Application "));
  TsWriteToView(argv[0]);
  TsWriteToView(_T(" has "));
  TsWriteToView(argc);
  TsWriteToViewLn(_T(" argument(s)"));
  }

//Create Microsoft XML SAX parser TODO:

logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}
*/
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2005-03-21 03:22:22  Darko           excluded from
 *       the build
 *  1    Biblioteka1.0         2005-03-17 00:47:04  Darko           
 * $
 *****************************************************************************/
