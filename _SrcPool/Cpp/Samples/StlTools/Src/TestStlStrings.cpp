/*$Workfile: TestStlStrings.cpp$: implementation file
  $Revision: 2$ $Date: 2007-07-17 12:02:37$
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

extern LPCTSTR g_szText[]; //test cases

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

//-----------------------------------------------------------------------------
/*Validates conversion to all upper case string.

  Returns: true if successful, otherwise returns false.

  Note: uses Standard Template Library (STL).
*/
bool TestStrToUpper()
{
TsWriteToViewLn(_T("TestStrToUpper()"));

//Test object creation
TESTENTRY logEntry =
  {_T("StrToUpper()"), _T("KStrUppr.cpp"), false};

extern tstring StrToUpper(const tstring& strSource);

bool bRes = true;

int i = 0;
tstring strResult;
while (g_szText[i] != NULL)
  {
  strResult = StrToUpper(g_szText[i]);
  std::_tcout << strResult << std::endl;
  i++;
  }

//Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);


TsWriteToViewLn(LOG_EOT);
return bRes;
}

//-----------------------------------------------------------------------------
/*Validates writing 32-bit characters to the stream.

  Returns: true if successful, otherwise returns false.

  Note: uses Standard Template Library (STL).
*/
bool TestUcstoHex()
{
TsWriteToViewLn(_T("TestUcstoHex()"));

//Test object creation
TESTENTRY logEntry =
  {_T("UcstoHex(tostream&, UCS4)"), _T("KUcstoHex.cpp"), false};

extern tostream& UcstoHex(tostream& outStream, UCS4 ucsValue);

bool bRes = true;

UCS4 uscChar[] =
  {
  0x0, 0x1, 0x8, 0xF, 0x10, 0xFF, 0x100, 0xFFF, 0x1000, 0xFFFF,
  0x10000, 0XFFFFF, 0x100000, 0xFFFFFF, 0X1000000, 0xFFFFFFF,
  0x10000000, 0xFFFFFFFF, 3435973836
  };
  
int i = 0;
tstring strResult;
while (i < (sizeof(uscChar)/sizeof(UCS4)))
  {
  std::_tcout << i << _T(". ");
  UcstoHex(std::_tcout, uscChar[i]) << std::endl;
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
 *  2    Biblioteka1.1         2007-07-17 12:02:37  Darko Kolakovic UscToHex()
 *  1    Biblioteka1.0         2007-07-16 17:51:51  Darko Kolakovic 
 * $
 *****************************************************************************/
