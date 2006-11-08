/*$Workfile: TestCmdLineParser.cpp$: implementation file
  $Revision: 4$ $Date: 2005-07-07 17:52:51$
  $Author: Darko Kolakovic$

  Test command line parser
  Copyright: CommonSoft Inc.
  2005-03-01 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#if defined(_MSC_VER)  /*Microsoft Visual studio*/

  #if defined(_UNICODE)
    #if !defined(UNICODE)
      #define UNICODE
    #endif
  #endif

  #include <tchar.h>
#endif

#include "KCmdLineParser.h" //CmdLineParser class

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);

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
  {_T("CmdLineParser()"), _T("KCmdLineParser.h"), bRes};

if (argc > 0)
  {
  TsWriteToView(_T("Application "));
  TsWriteToView(argv[0]);
  TsWriteToView(_T(" has "));
  TsWriteToView(argc);
  TsWriteToViewLn(_T(" argument(s)"));
  }

const unsigned int NO_OF_OPTIONS = 10;
CMDLINEOPTION cmdOptions[NO_OF_OPTIONS] = 
  {
  _T('a'), CMDLINE_NONE, 0, _T("command switch a without arguments"), // 0
  _T('b'), CMDLINE_NONE, 0, _T("command switch a without arguments"), // 1
  _T('c'), CMDLINE_NONE, 0, _T("command switch a without arguments"), // 2
  _T('d'), CMDLINE_NONE, 0, _T("command switch a without arguments"), // 3
  _T('e'), CMDLINE_NONE, 0, _T("command switch a without arguments"), // 4
  _T('1'), CMDLINE_NONE, 0, _T("command switch a without arguments"), // 5
  _T('B'), CMDLINE_NONE, 0, _T("command switch a without arguments"), // 6
  _T('C'), CMDLINE_NONE, 0, _T("command switch a without arguments"), // 7
  _T('?'), CMDLINE_NONE, 0, _T("usage"),                              // 8
  _T('h'), CMDLINE_NONE, 0, _T("help about command options"),         // 9
  };

//Create command-line parser
CCmdLineParser cmdParser;
cmdParser.SetOptions(cmdOptions, NO_OF_OPTIONS);

logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2005-07-07 17:52:51  Darko Kolakovic UNICODE
 *  3    Biblioteka1.2         2005-03-21 03:23:18  Darko           fixed
 *       SetOptions()
 *  2    Biblioteka1.1         2005-03-14 01:10:33  Darko           Created test
 *  1    Biblioteka1.0         2005-03-11 03:13:51  Darko           
 * $
 *****************************************************************************/
