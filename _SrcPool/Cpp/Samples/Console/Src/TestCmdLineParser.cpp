/*$Workfile: TestCmdLineParser.cpp$: implementation file
  $Revision: 1$ $Date: 2005-03-11 02:13:51$
  $Author: Darko$

  Test command line parser
  Copyright: CommonSoft Inc.
  2005-03-01 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
//#include "KTChar.h"

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Function validates conversion of a string to an integer.

  Returns: true if successful, otherwise returns false.
 */
bool TestCmdLineParser(int argc, //[in] specifies how many arguments are passed
                          // to the program from the command line. The value of
                          // argc is at least one: the program name.
                       TCHAR* argv[] //[in] the program arguments as an array of
                          //pointers to null-terminated strings. The first string 
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
                       )
{
TsWriteToView(_T("TestCmdLineParser()\r\n"));
bool bRes = true;
TESTENTRY logEntry =
  {_T("CCmdLine()"), _T("KCmdLine.h"), bRes};



logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2005-03-11 02:13:51  Darko           
 * $
 *****************************************************************************/
