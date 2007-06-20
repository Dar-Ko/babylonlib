/*$Workfile: KStrRplEscSeq.cpp$: implementation file
  $Revision: 8$ $Date: 2007-06-20 14:43:32$
  $Author: Darko Kolakovic$

  Replace "C" escape sequences with characters
  Dec 2k1 Darko Kolakovic
*/
/* Group=Strings                                                             */

#ifndef _TCHAR_DEFINED
  #include "KTChar.h" //TCHAR typedef
#endif
#include <ctype.h>     //isxdigit()
#include "KStrings.h" //Declaration

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#ifndef LPTSTR
  typedef TCHAR*   LPTSTR;
#endif

//ReplaceEscapeSeq()-----------------------------------------------------------
/*Call this function to replace all occurrences of the escape sequences with
  corresponding single characters. Character combinations consisting of
  a backslash (\) followed by a letter or by a combination of digits are
  called “escape sequences”.

      Table of Escape Sequences
      Escape   Hex    Sequence Represents
        \a     007       Bell (alert)
        \b     008       Backspace
        \f     00C       Formfeed
        \n     00A       New line
        \r     00D       Carriage return
        \t     009       Horizontal tab
        \v     00B       Vertical tab
        \'     027       Single quotation mark
        \"     022       Double quotation mark
        \\     05C       Backslash
        \?     03F       Literal question mark
        \OOO   OOO       ASCII character in octal notation
        \xhhh  hhh       ASCII character in hexadecimal notation

  Returns: pointer to the zero-terminated string with escape sequences replaced.

  Note: If a backslash precedes a character that does not appear in Escape
  Sequences Table, the undefined character will be represented as the character
  itself (without backslash).

  See also: CharToEsc()
 */
LPTSTR ReplaceEscapeSeq(LPTSTR szFormat //[in] zero-terminated format string
                        //consisting of characters and escape sequences
                        )
{
if (szFormat != NULL)
  {
  int i = 0;
  //Find first escape delimiter in order to speed up browsing
  while ((szFormat[i] != _T('\\')) && (szFormat[i] != _T('\0')))
    i++;
  int iNext = i;
  while (szFormat[iNext] != _T('\0'))
    {
    if(szFormat[iNext] == _T('\\'))
      {
      iNext++;
      //Replace escape sequence with the proper character
      switch(szFormat[iNext])
        {
        case _T('\0'):szFormat[i] = _T('\0'); return szFormat;
        case _T('a'): szFormat[i] = _T('\a'); break;
        case _T('b'): szFormat[i] = _T('\b'); break;
        case _T('t'): szFormat[i] = _T('\t'); break;
        case _T('n'): szFormat[i] = _T('\n'); break;
        case _T('v'): szFormat[i] = _T('\v'); break;
        case _T('f'): szFormat[i] = _T('\f'); break;
        case _T('r'): szFormat[i] = _T('\r'); break;
        case _T('\"'):szFormat[i] = _T('\"'); break;
        case _T('\''):szFormat[i] = _T('\''); break;
        case _T('?'): szFormat[i] = _T('?');  break;
        case _T('\\'):szFormat[i] = _T('\\'); break;
        case _T('x'): //Hexadecimal number
          {
            //Check if following 3 characters are hexadecimal numbers
          int j = 1;
          int iChar = 0;
          while(j <= 3 )
            {
            TCHAR& cChar = szFormat[iNext + j];
            if ((_istxdigit(cChar)) )
              {
              iChar <<= 4;
              if(_istdigit(cChar))
                iChar |= (cChar - _T('0'));
              else
                iChar |= (_toupper(cChar) - _T('A') + 10);
              }
            else //Exit if it is not \xhhh sequence
              {
              j = -1;
              break;
              }
            j++;
            }
          if ( j > 0) //Replace hexadecimal value
            {
            szFormat[i] = TCHAR(iChar);
            iNext += 3;
            }
          else //Omit backslash
            szFormat[i] = szFormat[iNext];
          }
          break;

        case _T('0'): //Octal number
        case _T('1'):
        case _T('2'):
        case _T('3'):
        case _T('4'):
        case _T('5'):
        case _T('6'):
        case _T('7'):
          {
          int iChar = szFormat[iNext] - _T('0');
          int j = 0;
          while(++j < 3)
            {
            TCHAR& cChar = szFormat[iNext + j];
            if ( (cChar >= _T('0')) && (cChar <= _T('7')) )
              {
              iChar <<= 3;
              iChar |= (cChar - _T('0'));
              }
            else //Exit if it is not \OOO sequence
              {
              j = -1;
              break;
              }
            }
          if ( j > 0) //Replace octal value
            {
            szFormat[i] = TCHAR(iChar);
            iNext += 2;
            }
          else //Omit backslash
            szFormat[i] = szFormat[iNext];
          }
          break;

        default: szFormat[i] = szFormat[iNext];
        }
      }
    else
      szFormat[i] = szFormat[iNext]; //Shift string left
    i++;
    iNext++;
    }
  szFormat[i] = szFormat[iNext]; //Shift terminating zero to left
  }
return szFormat;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  8    Biblioteka1.7         2007-06-20 14:43:32  Darko Kolakovic fixed while
 *       condition
 *  7    Biblioteka1.6         2003-09-22 22:26:50  Darko           formatting
 *  6    Biblioteka1.5         2002-02-04 19:57:28  Darko           include
 *       KTChar.h
 *  5    Biblioteka1.4         2002-01-29 23:22:01  Darko           Used lbraries
 *       notes 
 *  4    Biblioteka1.3         2001-12-30 20:19:55  Darko           Find first
 *       escape delimiter; fix missing termminating zero
 *  3    Biblioteka1.2         2001-12-23 18:08:14  Darko           declaration
 *       header file
 *  2    Biblioteka1.1         2001-12-23 00:25:24  Darko           changed header
 *  1    Biblioteka1.0         2001-12-23 00:12:50  Darko           
 * $
 *****************************************************************************/
