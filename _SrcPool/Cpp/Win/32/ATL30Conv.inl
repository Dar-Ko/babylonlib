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
/*Converts an ANSI string LPCSTR to an wide character BSTR.
  FIX: CComBSTR Constructor does not allocate enough space.
  This problem is due to a bug in the A2WBSTR function in the <atlconv.h> file.
  If the MultiByteToWideChar function's fourth argument is -1, the string is
  assumed to be NULL-terminated and the number of bytes returned will include
  the NULL character. The result of this function should not subtract 1 (one)
  if nLen does not equal -1; it should only do this if nLen is equal to -1.
  There are two ways to correct this problem:
    - Use one of the conversion macros to wrap the string passed into the
      constructor: CComBSTR bstr(5, T2OLE(buf)); or CComBSTR bstr(5, OLESTR("01234");
    - or replace incorrect code in <atlconv.h> for the A2WBSTR function with code
      from this header file.

  ATL 3.0 bug is fixed in: Platform SDK 2006-03, WinDDK 3790.830
  Note: The recommended way of converting to and from BSTR strings is to use
  the CComBSTR class.

  Note: Microsoft Windows specific (Win32)
        and uses Active Template Library (ATL).

  See also: MSDN article KB241857, CComBSTR class.
 */
inline BSTR A2WBSTR(LPCSTR lp, //[in] source as ANSI character string
                   int nLen = -1 //[in] = -1 zero-terminated string or length
                                 //of the source string
                   )
{
USES_CONVERSION;
BSTR str = NULL;
int nConvertedLen = MultiByteToWideChar(_acp, 0, lp, nLen, NULL, NULL);

  //BUG FIX #1 (from Q241857): only subtract 1 from the length if
  //the source data is null-terminated
if (nLen == -1)
  nConvertedLen--;

str = ::SysAllocStringLen(NULL, nConvertedLen);
if (str != NULL)
  {
  int nResult = MultiByteToWideChar(_acp, 0, lp, nLen, str, nConvertedLen);
  ATLASSERT(nResult == nConvertedLen);
  if(nResult != nConvertedLen)
    {
    SysFreeString(str);
    return NULL;
    }
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
