/*$RCSfile: MSVC71wtype.h,v $: header file
  $Revision: 1.2 $ $Date: 2009/09/01 15:35:17 $
  $Author: ddarko $

  Fix: workaround for .NET2003 (VC7) C++ linkage problem generating the error LNK2005
  Copyright: CommonSoft Inc
  2009-08-31  Darko Kolakovic
 */

#ifndef _KMSVC71WTYPE_H_
  //$RCSfile: MSVC71wtype.h,v $ sentry
  #define _KSIMPLEARRAY7_H_
// Group=Windows

#if defined(_MSC_VER) && (_MSC_VER <= 1310)
/*Microsoft Visual C++ .Net 2003, 32-bit, version 7.1 and lesser*/
  #ifdef __cplusplus
    #ifdef _UNICODE

      #ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
        #pragma message ("   #include " __FILE__ )
      #endif

      /*Workaround for .NET2003 (VC7) C++ linkage problem.
        Folowwing macros prevent inline wtype functions from existing in both
        multithreaded Unicode runtime library LIBCMTD.lib (_wctype.obj) and your
        object files.
        The error was always with one of the wide-character inline functions:
        _iswalpha, _iswupper, _iswlower, _iswdigit, _iswxdigit, _iswspace,
        _iswpunct, _iswalnum, _iswprint, _iswgraph, _iswcntrl or _iswascii.

        The problem causes next link errors:
          LIBCMTD.lib(_wctype.obj) : error LNK2005: _isw??? already defined in your.obj

        Apperently if <tchar.h> header file is included  before <windows.h>,
        the compiler instantiates these inline functions, resulting in multiple
        defintions.

        Workaround: Insure that <tchar.h> always follows <windows.h> or <winsock.h>.
        In cases when including either windows.h or winsock.h might not be
        desirable, try to define _WCTYPE_INLINE_DEFINED as first line in your code:
            #define _WCTYPE_INLINE_DEFINED

        Note: Microsoft Windows specific (Win32)

        See also:
            http://blog.unixwiz.net/2004/11/maddening_vc7_l.html
            http://lists.boost.org/Archives/boost/2005/07/89498.php
            http://aspn.activestate.com/ASPN/Mail/Message/2509074
       */
      #define _FIXLNK2005WTYPE
      #define iswalpha(ch)  ( iswctype(ch,_ALPHA) )
      #define iswupper(ch)  ( iswctype(ch,_UPPER) )
      #define iswlower(ch)  ( iswctype(ch,_LOWER) )
      #define iswdigit(ch)  ( iswctype(ch,_DIGIT) )
      #define iswxdigit(ch) ( iswctype(ch,_HEX)   )
      #define iswspace(ch)  ( iswctype(ch,_SPACE) )
      #define iswpunct(ch)  ( iswctype(ch,_PUNCT) )
      #define iswalnum(ch)  ( iswctype(ch,_ALPHA|_DIGIT) )
      #define iswprint(ch)  ( iswctype(ch,_BLANK|_PUNCT|_ALPHA|_DIGIT) )
      #define iswgraph(ch)  ( iswctype(ch,_PUNCT|_ALPHA|_DIGIT) )
      #define iswcntrl(ch)  ( iswctype(ch,_CONTROL) )
      #define iswascii(ch)  ( (unsigned)(ch) < 0x80 )
    #endif /* _UNICODE*/
  #endif /*__cplusplus*/
#endif /*_MSC_VER*/

///////////////////////////////////////////////////////////////////////////////
#endif  /*_KMSVC71WTYPE_H_*/
/*****************************************************************************
 * $Log: MSVC71wtype.h,v $
 * Revision 1.2  2009/09/01 15:35:17  ddarko
 * Reformatted
 *
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
