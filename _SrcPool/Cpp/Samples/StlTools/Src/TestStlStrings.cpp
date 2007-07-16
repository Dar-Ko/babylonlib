/*$Workfile: S:\_SrcPool\Cpp\Samples\StlTools\Src\TestStlStrings.cpp$: implementation file
  $Revision: 1$ $Date: 2007-07-16 17:51:51$
  $Author: Darko Kolakovic$

  Test string manipulation methods
  Copyright: CommonSoft Inc.
  2007-07-10 Darko Kolakovic
*/

// Group=Examples
#include "stdstl.h"

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

extern "C" LPCTSTR g_szText[]; //test cases

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Dumps certain configuration values used to handle Standard Template Library
  (STL) strings.

  Returns: true if successful, otherwise returns false.
 */
bool TestStlStringCfg()
{
bool bRes = true;
#if _MSC_VER <= 1200
  //Note: declaration of endl is included <iomanip.h>, MSVC 6.0 STL implementation
  std::_tcout << _T("Pointer to endl: ") << endl << std::endl;
#endif
std::_tcout << _T("std::endl ") << std::endl;
/*The "C" locale is defined by ANSI to correspond to the locale in which C
  programs have traditionally executed. The code page for the "C" locale
  ("C" code page) corresponds to the ASCII character set. 
 */
  std::cout << "Current Locale: " << std::_tcout.getloc().name() 
            << std::endl << std::flush;
  /*Note: MSVC STL implementation doesn't have wchar_t version of getloc().name();
    Result is always SBCS string.
    (error C2679: binary '<<' : no operator found which takes a right-hand operand of type 'std::string')
  */

std::_tcout << _T("sizeof(char) = ") << sizeof(char) << _T(" byte") << std::endl;
std::_tcout << _T("sizeof(wchar_t) = ") << sizeof(wchar_t) 
            << ((sizeof(wchar_t) == 1) ? _T(" byte") :  _T(" bytes")) << std::endl;

return bRes;
}

//-----------------------------------------------------------------------------
/*Validates conversion of End-of-Line markers.

  Returns: true if successful, otherwise returns false.

  Note: uses Standard Template Library (STL).
 */
bool TestReplaceEol()
{
TsWriteToViewLn(_T("TestReplaceEol()"));

  //Test object creation
TESTENTRY logEntry =
  {_T("ReplaceEOL()"), _T("KStrRplEOL.cpp"), false};

extern tstring& ReplaceEOL(LPCTSTR szText, tstring& strResult);

bool bRes = true;

int i = 0;
tstring strResult;
while (g_szText[i] != NULL)
  {
  ReplaceEOL(g_szText[i], strResult);
  std::_tcout << strResult << std::endl;
  i++;
  }

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);


TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-07-16 17:51:51  Darko Kolakovic 
 * $
 *****************************************************************************/
