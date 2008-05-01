/*$Workfile: ATL30Conv.inl$: header file
  $Revision: 3$ $Date: 2005-04-26 11:28:05$
  $Author: Darko Kolakovic$

  Fix: CComBSTR Constructor does not allocate enough space
  Copyright: CommonSoft Inc
  2004-04-01  Darko Kolakovic
 */
// Group=Windows

#if (_ATL_VER == 0x0300)/*Active Template Library version 3.0*/

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

//-----------------------------------------------------------------------------
/*FIX: CComBSTR Constructor does not allocate enough space.
  This problem is due to a bug in the A2WBSTR function in the <atlconv.h> file.
  There are two ways to correct this problem:
    - Use one of the conversion macros to wrap the string passed into the
      constructor: CComBSTR bstr(5, T2OLE(buf)); or CComBSTR bstr(5, OLESTR("01234");
    - or replace incorrect code in <atlconv.h> for the A2WBSTR function with code
      from this header file.

  Note: Microsoft Windows specific (Win32)
        and uses Active Template Library (ATL).

  See also: MSDN article KB241857.
 */
inline BSTR A2WBSTR(LPCSTR lp, int nLen = -1)
{
USES_CONVERSION;
BSTR str = NULL;
int nConvertedLen = MultiByteToWideChar(_acp, 0, lp, nLen, NULL, NULL);

  //BUG FIX #1 (from Q241857): only subtract 1 from the length if
  //the source data is nul-terminated
if (nLen == -1)
  nConvertedLen--;

str = ::SysAllocStringLen(NULL, nConvertedLen);
if (str != NULL)
  {
  MultiByteToWideChar(_acp, 0, lp, nLen, str, nConvertedLen);
  }
return str;
}
///////////////////////////////////////////////////////////////////////////////
#endif //( _ATL_VER == 0x0300 )
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2005-03-26 00:11:41  Darko           comment
 *  1    Biblioteka1.0         2005-03-23 03:23:26  Darko
 * $
 *****************************************************************************/
