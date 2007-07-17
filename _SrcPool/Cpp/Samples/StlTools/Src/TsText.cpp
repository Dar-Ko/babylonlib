/*$Workfile: TsText.cpp$: implementation file
  $Revision: 2$ $Date: 2007-07-17 09:31:18$
  $Author: Darko Kolakovic$

  Text samples used to test string manipulators
  Copyright: CommonSoft Inc.
  2007-07-16 Darko Kolakovic
*/

// Group=Examples
#include "KTChar.h" //LPCTSTR typedef

/*List of text samples. The last item in the list is NULL.
  The size of characters used for the strings dependes compilation settings.
  If _UNICODE preprocessor definition is used, characters will have size of
  wchar_t.

  Note: Size of wchar_t type depends on a compiler implementation.
 */
LPCTSTR g_szText[] =
  {
  _T(""),     // 0 empty string
  _T("\n"),   // Unix EOL
  _T("\r"),   // Mac EOL
  _T("\r\n"), // DOS EOL
  _T("\n\r"), // LFCR
  _T("vini, vidi, vici"), // string with space and comma
  _T("vini,\rvidi,\r\nvici"), // string with CR and CRLF
  _T("vini,\nvidi,\n\rvici\n"), // string with LF, LFCR and CR
  _T("Roma tibi subito motibus ibit amor."),  // palindrome
  NULL
  };

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-11-23 15:52:04  Darko Kolakovic
 * $
 *****************************************************************************/
