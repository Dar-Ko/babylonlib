/*$Workfile: TestWideChar.cpp$: implementation file
  $Revision: 1$ $Date: 2004-10-01 22:55:32$
  $Author: Darko$

  Test wchar_t capabilites
  Copyright: CommonSoft Inc.
  2004-06-06 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include <locale>

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Validates CStringHandler class creation and IsPalindrome methods.

  Returns: true if successful, otherwise returns false.
 */
bool TestWideChar()
{
TsWriteToView(_T("TestWideChar()\r\n"));

  //Verify if the compiler supports wide characters
wchar_t w = L'w';
std::wstring wString = L"This is a wide character string";
std::wcout << wString << std::endl;
  /*Note: Microsoft's std::wcout uses wctomb() to convert a wide character
          to the corresponding multibyte character. If the conversion is not
          possible in the current locale, wctomb() returns –1, closes the
          stream with WEOF, sets stream state to ios_base::badbit and sets
          errno to EILSEQ = 42. In other hand, _cwprintf() uses _cputws()
          to writes a wide character string directly to the console.
   */

  //Single-byte character set (SBCS)
char c = 'c';
std::string cString = "This is a SBCS string";
std::cout << cString << std::endl;

  /*Wash my transgressions, not only my face
    palindrome on the font of St. Sophia, Constantinople
   */
wchar_t szGreek[] =
  {
  0x039D, 0x0399, 0x03A8, 0x039F, 0x039D, 0x0020, 0x0391, 0x039D, 0x039F,
  0x039C, 0x0397, 0x039C, 0x0391, 0x03A4, 0x0391, 0x0020, 0x039C, 0x0397,
  0x0020, 0x039C, 0x039F, 0x039D, 0x0391, 0x039D, 0x0020, 0x039F, 0x03A8,
  0x0399, 0x039D, 0x0000
  };

  //Get current locale
std::cout << "Current locale:" << std::endl;
  /*The "C" locale is defined by ANSI to correspond to the locale in which
    C programs have traditionally executed. The code page for the "C" locale
    ("C" code page) corresponds to the ASCII character set.
   */
std::cout << "cout: "  <<  std::cout.getloc().name() << std::endl;
std::cout << "wcout: " <<  std::wcout.getloc().name() << std::endl << std::flush;

#ifdef MSVC
    //MS Visual Studio STL implementation
    std::string strLocaleName("Greek_Greece.1253");
#else
    std::string strLocaleName("gr_GR");

#endif

std::wcout.imbue(strLocaleName);
std::cout.imbue(strLocaleName);

  //Fixme! Win32 select a monospaced TrueType font, such as "Lucida Console"
  //for the console (command line window )
  //or/and type (UTF-8 code page) type c:\> chcp 65001

_cwprintf(L"%s\n",szGreek);



std::wstring wString2 = szGreek;
std::wcout << wString2 << std::endl;

std::wcout << szGreek << std::endl;

TsWriteToView(LOG_EOT);
TsWriteToView(_T("\r\n"));
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-10-01 22:55:32  Darko           
 * $
 *****************************************************************************/
