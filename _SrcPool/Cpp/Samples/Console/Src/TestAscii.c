/*$Workfile: TestAscii.c$: implementation file
  $Revision: 1$ $Date: 2005-07-07 17:51:12$
  $Author: Darko Kolakovic$

  Test ASCII character generator.
  Copyright: CommonSoft Inc.
  2005-07-10 Darko Kolakovic
*/

/* Group=Examples                                                            */

#include <limits.h> /*SCHAR_MAX const*/
#include <stdio.h>

#if defined(_MSC_VER)  /*Microsoft Visual studio*/

  #if defined(_UNICODE)
    #if !defined(UNICODE)
      #define UNICODE
    #endif
  #endif

  #include <tchar.h>
  #if _MSC_VER >= 800    /*Visual C++, 32-bit, version 1.0 */
    #include "KType32.h" /*uint8_t typedef*/
  #else
    #include "KType16.h" /*uint8_t typedef*/
  #endif
#endif
#include "KCharCst.h" /*control characters macros*/
#ifndef bool
  #include "KTypedef.h"
#endif
#include "KTestLog.h"

#if !defined (SCHAR_MAX)
  #define SCHAR_MAX 127 /*Maximum signed char value*/
#endif

extern TCHAR* ChtoAscii(int cValue);
extern bool TsWriteToViewLn(LPCTSTR lszText);

/*---------------------------------------------------------------------------*/
/*Test a character generator. Outputs characters in the range [0, SCHAR_MAX].

  Returns: true if test is successful; otherwise returns false.

  See also: ISO/IEC 646:1991, ANSI X3.4-1986,
  {html:<a href="Documentation/KASCIICharTable.htm">Character Tables</a>}
 */
bool TestAscii()
{
LPTSTR szDecription[] =
  {
  /*  0*/_T("NULL")                ,  /*  1*/_T("START OF HEADING")    ,
  /*  2*/_T("START OF TEXT")       ,  /*  3*/_T("END OF TEXT")         ,
  /*  4*/_T("END OF TRANSMISSION") ,  /*  5*/_T("ENQUIRY")             ,
  /*  6*/_T("ACKNOWLEDGE")         ,  /*  7*/_T("BELL")                ,
  /*  8*/_T("BACKSPACE")           ,  /*  9*/_T("HORIZONTAL TAB")      ,
  /* 10*/_T("LINE FEED")           ,  /* 11*/_T("VERTICAL TAB")        ,
  /* 12*/_T("FORM FEED")           ,  /* 13*/_T("CARRIAGE RETURN")     ,
  /* 14*/_T("SHIFT OUT")           ,  /* 15*/_T("SHIFT IN")            ,
  /* 16*/_T("DATA LINK ESCAPE")    ,  /* 17*/_T("DEVICE CONTROL 1")    ,
  /* 18*/_T("DEVICE CONTROL 2")    ,  /* 19*/_T("DEVICE CONTROL 3")    ,
  /* 20*/_T("DEVICE CONTROL 4")    ,  /* 21*/_T("NEGATIVE ACKNOWLEDGE"),
  /* 22*/_T("SYNCHRONOUS")         ,  /* 23*/_T("END OF TRANSMISSION BLOCK"),
  /* 24*/_T("CANCEL")              ,  /* 25*/_T("END OF MEDIUM")       ,
  /* 26*/_T("SUBSTITUTE")          ,  /* 27*/_T("ESCAPE")              ,
  /* 28*/_T("FILE SEPARATOR")      ,  /* 29*/_T("GROUP SEPARATOR")     ,
  /* 30*/_T("RECORD SEPARATOR")    ,  /* 31*/_T("UNIT SEPARATOR")      ,
  /* 32*/_T("SPACE")               ,  /* 33*/_T("EXCLAMATION MARK")    ,
  /* 34*/_T("QUOTATION MARK")      ,  /* 35*/_T("NUMBER SIGN")         ,
  /* 36*/_T("DOLLAR SIGN")         ,  /* 37*/_T("PERCENT SIGN")        ,
  /* 38*/_T("AMPERSAND")           ,  /* 39*/_T("APOSTROPHE")          ,
  /* 40*/_T("LEFT PARENTHESIS")    ,  /* 41*/_T("RIGHT PARENTHESIS")   ,
  /* 42*/_T("ASTERISK")            ,  /* 43*/_T("PLUS SIGN")           ,
  /* 44*/_T("COMMA")               ,  /* 45*/_T("HYPHEN, MINUS SIGN")  ,
  /* 46*/_T("PERIOD, FULL STOP")   ,  /* 47*/_T("SOLIDUS, SLASH")      ,
  /* 48*/_T("DIGIT ZERO")          ,  /* 49*/_T("DIGIT ONE")           ,
  /* 50*/_T("DIGIT TWO")           ,  /* 51*/_T("DIGIT THREE")         ,
  /* 52*/_T("DIGIT FOUR")          ,  /* 53*/_T("DIGIT FIVE")          ,
  /* 54*/_T("DIGIT SIX")           ,  /* 55*/_T("DIGIT SEVEN")         ,
  /* 56*/_T("DIGIT EIGHT")         ,  /* 57*/_T("DIGIT NINE")          ,
  /* 58*/_T("COLON")               ,  /* 59*/_T("SEMICOLON")           ,
  /* 60*/_T("LESS-THAN SIGN")      ,  /* 61*/_T("EQUALS SIGN")         ,
  /* 62*/_T("GREATER-THAN SIGN")   ,  /* 63*/_T("QUESTION MARK")       ,
  /* 64*/_T("COMMERCIAL AT SIGN")  ,  /* 65*/_T("CAPITAL LETTER A")    ,
  /* 66*/_T("CAPITAL LETTER B")    ,  /* 67*/_T("CAPITAL LETTER C")    ,
  /* 68*/_T("CAPITAL LETTER D")    ,  /* 69*/_T("CAPITAL LETTER E")    ,
  /* 70*/_T("CAPITAL LETTER F")    ,  /* 71*/_T("CAPITAL LETTER G")    ,
  /* 72*/_T("CAPITAL LETTER H")    ,  /* 73*/_T("CAPITAL LETTER I")    ,
  /* 74*/_T("CAPITAL LETTER J")    ,  /* 75*/_T("CAPITAL LETTER K")    ,
  /* 76*/_T("CAPITAL LETTER L")    ,  /* 77*/_T("CAPITAL LETTER M")    ,
  /* 78*/_T("CAPITAL LETTER N")    ,  /* 79*/_T("CAPITAL LETTER O")    ,
  /* 80*/_T("CAPITAL LETTER P")    ,  /* 81*/_T("CAPITAL LETTER Q")    ,
  /* 82*/_T("CAPITAL LETTER R")    ,  /* 83*/_T("CAPITAL LETTER S")    ,
  /* 84*/_T("CAPITAL LETTER T")    ,  /* 85*/_T("CAPITAL LETTER U")    ,
  /* 86*/_T("CAPITAL LETTER V")    ,  /* 87*/_T("CAPITAL LETTER W")    ,
  /* 88*/_T("CAPITAL LETTER X")    ,  /* 89*/_T("CAPITAL LETTER Y")    ,
  /* 90*/_T("CAPITAL LETTER Z")    ,  /* 91*/_T("LEFT SQUARE BRACKET") ,
  /* 92*/_T("BACKSLASH")           ,  /* 93*/_T("RIGHT SQUARE BRACKET"),
  /* 94*/_T("CIRCUMFLEX")          ,  /* 95*/_T("UNDERLINE")           ,
  /* 96*/_T("GRAVE ACCENT")        ,  /* 97*/_T("SMALL LETTER A")      ,
  /* 98*/_T("SMALL LETTER B")      ,  /* 99*/_T("SMALL LETTER C")      ,
  /*100*/_T("SMALL LETTER D")      ,  /*101*/_T("SMALL LETTER E")      ,
  /*102*/_T("SMALL LETTER F")      ,  /*103*/_T("SMALL LETTER G")      ,
  /*104*/_T("SMALL LETTER H")      ,  /*105*/_T("SMALL LETTER I")      ,
  /*106*/_T("SMALL LETTER J")      ,  /*107*/_T("SMALL LETTER K")      ,
  /*108*/_T("SMALL LETTER L")      ,  /*109*/_T("SMALL LETTER M")      ,
  /*110*/_T("SMALL LETTER N")      ,  /*111*/_T("SMALL LETTER O")      ,
  /*112*/_T("SMALL LETTER P")      ,  /*113*/_T("SMALL LETTER Q")      ,
  /*114*/_T("SMALL LETTER R")      ,  /*115*/_T("SMALL LETTER S")      ,
  /*116*/_T("SMALL LETTER T")      ,  /*117*/_T("SMALL LETTER U")      ,
  /*118*/_T("SMALL LETTER V")      ,  /*119*/_T("SMALL LETTER W")      ,
  /*120*/_T("SMALL LETTER X")      ,  /*121*/_T("SMALL LETTER Y")      ,
  /*122*/_T("SMALL LETTER Z")      ,  /*123*/_T("LEFT CURLY BRACKET")  ,
  /*124*/_T("VERTICAL LINE")       ,  /*125*/_T("RIGHT CURLY BRACKET") ,
  /*126*/_T("TILDE")               ,  /*127*/_T("DELETE")
  };
bool bResult = false;
int i = 0;
TCHAR ch = 0;
LPCTSTR szControlCharFormat    = _T("%3d %02X %s  %s\n");
LPCTSTR szPrintabileCharFormat = _T("%3d %02X (%c)  %s\n");

TsWriteToViewLn(_T("TestAscii()"));
TsWriteToViewLn(_T("ISO/IEC 646:1991"));
TsWriteToViewLn(_T("Dec HEX char  description"));

while (i < 32) /*Print control characters*/
  {
  _tprintf(szControlCharFormat, i, i, ChtoAscii(i), szDecription[i]);
  i++;
  }

while (i < SCHAR_MAX) /*Print ASCII/Latin-1 characters*/
  {
  _tprintf(szPrintabileCharFormat, i, i, (TCHAR)i, szDecription[i]);
  i++;
  }

/*Print control character*/
_tprintf(szControlCharFormat, i, i, ChtoAscii(i), szDecription[i]);

bResult = (i == SCHAR_MAX);

TsWriteToViewLn(LOG_EOT);
return bResult;
}