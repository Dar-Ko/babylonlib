/*$Workfile: KStrEscC.c$: implementation file
  $Revision: 2$ $Date: 2004-06-01 17:53:04$
  $Author: Darko$

  Convert escape characters to printable strings
  June '90 Darko Kolakovic
*/
/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifndef _TCHAR_DEFINED
  #include "KTChar.h" //TCHAR typedef
#endif
#include "KStrings.h" //Declaration

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//CharToEsc()------------------------------------------------------------------
/*Converts an escape character to the string representation.

     Table of Escape Sequences
      char    Escape    Sequence Represents
     0x00       \0         String terminator
     0x007      \a         Bell (alert)
     0x008      \b         Backspace
     0x00C      \f         Formfeed
     0x00A      \n         New line
     0x00D      \r         Carriage return
     0x009      \t         Horizontal tab
     0x00B      \v         Vertical tab
     0x022      \"         Double quotation mark
     0x05C      \\         Backslash

  Returns: zero-terminated string representing the escape character. If
  character is not one of escape characters, function returns string with
  the character itself.

  See also: ReplaceEscapeSeq()
 */
LPTSTR CharToEsc(TCHAR cEsc //[in] escape character
                 )
{
static TCHAR szResult[2];
switch(cEsc)
  {
  case _T('\0'): return _T("\\0");
  case _T('\a'): return _T("\\a");
  case _T('\b'): return _T("\\b");
  case _T('\f'): return _T("\\f");
  case _T('\n'): return _T("\\n");
  case _T('\r'): return _T("\\r");
  case _T('\t'): return _T("\\t");
  case _T('\"'): return _T("\\\"");
  case _T('\\'): return _T("\\\\");
  default:       szResult[0] = cEsc;
  }
szResult[1] = _T('\0');
return szResult;
}

/* ///////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2004-06-01 17:53:04  Darko           time sync
 *  1    Biblioteka1.0         2003-09-22 22:22:18  Darko
 * $
 *  0 1990-06   Darko Kolakovic
 *****************************************************************************/
