/*$Workfile: TestIsPalindrome.cpp$: implementation file
  $Revision: 8$ $Date: 2007-06-27 16:52:38$
  $Author: Darko Kolakovic$

  Test IsPalindrome methods
  Copyright: CommonSoft Inc.
  2004-06-06 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include <locale>
#include <string>
#include "STL/KOStream.h"
#include "STL/KTString.h"  //tstring template
#include "TestCptString.h" //CPTString class

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

  Note: uses Standard Template Library (STL).
 */
bool TestIsPalindrome()
{
TsWriteToView(_T("TestIsPalindrome()\r\n"));

#ifdef KSTL_IO
  //See "KOStream.h" for values of KSTL_IO
  #if (KSTL_IO == 1200) || (KSTL_IO == 1201)
    //MS Visual Studio 6.0 STL implementation
    std::_tcout.imbue( std::locale("Greek_Greece.1253"));
  #elif (KSTL_IO == 1300) || (KSTL_IO == 1310)
    //MS Visual Studio .Net 7.0 STL implementation
    std::_tcout.imbue( std::locale("Greek_Greece.1253"));
  #elif (KSTL_IO == 1400)
    //MS Visual Studio .Net 8.0 STL implementation
    std::_tcout.imbue( std::locale("Greek_Greece.1253"));
  #else
    //Note: MS Visual Studio could generate an exception 
    //'unknown resource' on this point. 
    //Validate correct KSTL_IO value
    
    std::_tcout.imbue( std::locale("gr_GR"));
  #endif
#else //!KSTL_IO
  #if _MSC_VER > 1000
    //MS Visual Studio STL implementation
    std::_tcout.imbue( std::locale("Greek_Greece.1253"));
  #else
    //gcc
    std::_tcout.imbue( std::locale("gr_GR"));
  #endif
#endif //KSTL_IO

/*The "C" locale is defined by ANSI to correspond to the locale in which C
  programs have traditionally executed. The code page for the "C" locale
  ("C" code page) corresponds to the ASCII character set. 
 */
std::cout << "Current Locale: " << std::_tcout.getloc().name() 
          << std::endl << std::flush;

#ifdef _UNICODE
  //Fixme! select a monospaced TrueType font, such as "Lucida Console" for the console (command line window )
  //and type c:\> chcp 65001 
  //_cwprintf() works becouse outputs directly to the console D.K. 2004-06-07
  std::wcout << L"Select font 'Lucida Console' for the Command Prompt"  
            << std::endl << std::flush;
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

  #if _MSC_VER >= 1300
    _cwprintf(L"T %s\n",szGreek); //Fixme! delete after fixing stream code page D.K.
  #endif
  #if _MSC_VER == 1200
    wprintf(L"T %s\n",szGreek); //Fixme! delete after fixing stream code page D.K.
  #endif
#endif

const int TESTCOUNT = 15;
struct tagTestPalindromeAtoi
{
  LPCTSTR m_szSource; //string to test
  bool    m_bResult;  //expected result
} Test[TESTCOUNT] =
  {
  _T(""),                                         false,  // 0 empty string
  _T("ma"),                                       false,  // 1
  _T("\"  mom!  \""),                              true,  // 2
  _T("ABCD   , DC; BA?   "),                       true,  // 3
  _T("  -2147483648"),                            false,  // 4
  _T("2147483647"),                               false,  // 5
  _T("  -123454321."),                             true,  // 6
  _T("racecar"),                                   true,  // 7
  _T("Able was I ere I saw Elba"),                 true,  // 8 mixed case palindrome (EN)
  _T("A man, a plan, a canal, Panama."),           true,  // 9 sentence
  _T("Roma tibi subito motibus ibit amor."),       true,  // A
  _T("Wash my transgressions, not only my face."),false,  // B not palindrome (EN)
  #ifndef _UNICODE
    #ifdef _DEBUG
       //Note: in debug mode characters > 127 generates assertions,
       //      causing break of the automated test
      _T("NI?ON ANOMHMATA MH MONAN O>IN"),         true,  // C palindrome (GR)
    #else
      _T("NIêON ANOMHMATA MH MONAN OêIN"),         true,  // C palindrome (GR)
    #endif
  #else
    szGreek,                                       true,  // C palindrome (GR)
  #endif
  _T("Otto"),                                      true,  // D
  _T("Go hang a salami, I'm a lasagna hog."),      true   // E punctuation palindrome (EN)
  };

  //Test object creation
TESTENTRY logEntry =
  {_T("CStringHandler::GetLength()"), _T("KStringHandler.h"), false};

bool bRes = true;
CPTString strPalindrome;
bRes = (strPalindrome.GetLength() == 0);

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

  //Test palindrome validation of <null>
logEntry.m_szObjectName = _T("IsPalindrome(LPCTSTR, unsigned int)");
logEntry.m_szFileName = _T("KStrPalindrome.cpp");

bRes = !strPalindrome.IsPalindrome(); //<null> is not a palindrome
strPalindrome.TsWriteToViewLn();

if (bRes)
  {
  int i = 0;
  while ((i < TESTCOUNT) && bRes)
    {
    strPalindrome = Test[i].m_szSource;
    strPalindrome.TsWriteToViewLn();
    bRes = (strPalindrome.IsPalindrome() == Test[i].m_bResult);
    i++;
    }

      //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2004-06-06 22:55:28  Darko           Added new test
 *       cases
 *  1    Biblioteka1.0         2004-06-04 17:47:10  Darko
 * $
 *****************************************************************************/
