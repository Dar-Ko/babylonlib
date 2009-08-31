/*$Rcsfile: ATL30Conv.inl$: header file
  $Revision: 1.1 $ $Date: 2009/08/31 21:37:00 $
  $Author: ddarko $

  Fix: workaround for .NET2003 (VC7) linkage problem generating the error LNK2005
  Copyright: CommonSoft Inc
  2009-08-31  Darko Kolakovic
 */

#ifndef _KMSVC71WTYPE_H_
  //$RCSfile: MSVC71wtype.h,v $ sentry
  #define _KSIMPLEARRAY7_H_
// Group=Windows

#if defined(_MSC_VER) && (_MSC_VER <= 1310)
/*Microsoft Visual C++ .Net 2003, 32-bit, version 7.1 and lesser*/


#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

  /*Workaround for .NET2003 (VC7) linkage problem.
    Folowwing macros prevent inline wtype functions from existing in both
    multithreaded Unicode runtime library LIBCMTD.lib (_wctype.obj) and your
    object files.
    The error was always with one of the wide-character inline functions:
    _iswalpha, _iswupper, _iswlower, _iswdigit, _iswxdigit, _iswspace, _iswpunct,
    _iswalnum, _iswprint, _iswgraph, _iswcntrl or _iswascii.

    The problem causes next link errors:
      LIBCMTD.lib(_wctype.obj) : error LNK2005: _isw??? already defined in your.obj

    Apperently if <tchar.h> header file is included  before <windows.h>, the
    compiler instantiates these inline functions, resulting in multiple
    defintions.

    Workaround: Insure that <tchar.h> always follows <windows.h> or <winsock.h>.
    In cases when including either windows.h or winsock.h might not be desirable,
    try to define _WCTYPE_INLINE_DEFINED as first line in your code:
        #define _WCTYPE_INLINE_DEFINED

    Note: Microsoft Windows specific (Win32)

    See also:
        http://blog.unixwiz.net/2004/11/maddening_vc7_l.html
        http://lists.boost.org/Archives/boost/2005/07/89498.php
        http://aspn.activestate.com/ASPN/Mail/Message/2509074
   */
  #define _FIXLNK2005WTYPE _WCTYPE_INLINE_DEFINED

  #define iswalpha(_c)    ( iswctype(_c,_ALPHA) )
  #define iswupper(_c)    ( iswctype(_c,_UPPER) )
  #define iswlower(_c)    ( iswctype(_c,_LOWER) )
  #define iswdigit(_c)    ( iswctype(_c,_DIGIT) )
  #define iswxdigit(_c)   ( iswctype(_c,_HEX) )
  #define iswspace(_c)    ( iswctype(_c,_SPACE) )
  #define iswpunct(_c)    ( iswctype(_c,_PUNCT) )
  #define iswalnum(_c)    ( iswctype(_c,_ALPHA|_DIGIT) )
  #define iswprint(_c)    ( iswctype(_c,_BLANK|_PUNCT|_ALPHA|_DIGIT) )
  #define iswgraph(_c)    ( iswctype(_c,_PUNCT|_ALPHA|_DIGIT) )
  #define iswcntrl(_c)    ( iswctype(_c,_CONTROL) )
  #define iswascii(_c)    ( (unsigned)(_c) < 0x80 )

#endif /*_MSC_VER*/

///////////////////////////////////////////////////////////////////////////////
#endif  /*_KMSVC71WTYPE_H_*/
/*****************************************************************************
 * $Log: MSVC71wtype.h,v $
 * Revision 1.1  2009/08/31 21:37:00  ddarko
 * Created
 *
 *****************************************************************************/
/*boost.org blog
  This has been noticed before and stems from the fact that the inline
  directive is ignored for debug mode, causing those inline functions to exist
  both in the C runtime library and in the regex lib.
  I found a note going back to 2002 -
  http://lists.boost.org/MailArchives/boost-users/msg01398.php - which
  indicates that this problem is longstanding.
 */
