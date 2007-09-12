/*$Workfile: KOStream.h$: header file
  $Revision: 17$ $Date: 2007-07-16 18:02:59$
  $Author: Darko Kolakovic$

  STL header file
  Copyright: CommonSoft Inc.
  May 94 Darko Kolakovic
 */

#ifndef _KOSTREAM_H_
    //$Workfile: KOStream.h$ sentry
  #define _KOSTREAM_H_

#ifndef __cplusplus
  #error STL requires C++ compilation (use a .cpp suffix)
#endif

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _DEBUG
  #ifndef _STLP_DEBUG
    #ifdef _STLP_IOSTREAM  //included stlport/iostream header file
      #define _STLP_DEBUG 1    //Debug STLPort library
                               //Note: have to be defined before STL header
                               //files
    #endif //_STLP_IOSTREAM
  #endif  //_STLP_DEBUG
#else
  #ifdef _STLP_DEBUG
    #undef _STLP_DEBUG
  #endif
#endif

  //Resolve different implementations of the STL

#if defined( __MSDOS__ ) || defined( MSDOS )
  #include <strstrea.h>
#endif

#if _MSC_VER < 1200
  #include <iostream.h>
  #include <iomanip.h>  //std::endl
#endif

#if _MSC_VER >= 1200
  #include <iostream>
  #include <iomanip>    //std::endl
#endif

#ifdef _STLP_IOSTREAM //STLport library
  /*Tag indicating that standard IO stream is included

    Note: Include additional directory /I "..\..\STL\STLport\stlport" and
    appropriate STLport library in your make file, in order to replace
    compiler's native Standard Template Library.
   */
  #define KSTL_IO 4100
  #pragma message ("  Standard Template Library (STLport) is used " __FILE__ )
#endif

#ifdef _INC_IOSTREAM //MSVC v6.0 iostream.h
  #define KSTL_IO 1201
  #pragma message ("  Standard Template Library (STL .h MSVC v6.0) is used " __FILE__ )
#endif

#ifdef _IOSTREAM_ //MSVC v6.0 iostream
  #if _MSC_VER == 1200
    #define KSTL_IO 1200
    #pragma message ("  Standard Template Library (STL MSVC v6.0) is used " __FILE__ )
  #endif
  #if _MSC_VER == 1300
    #define KSTL_IO 1300
    #pragma message ("  Standard Template Library (STL MSVC v7.0 .Net) is used " __FILE__ )
  #endif
  #if _MSC_VER == 1310
    #define KSTL_IO 1310
    #pragma message ("  Standard Template Library (STL MSVC v7.1 .Net) is used " __FILE__ )
  #endif
  #if _MSC_VER >= 1400
    #define KSTL_IO 1400
    #pragma message ("  Standard Template Library (STL MSVC v8.0(or > 8.0) .Net ) is used " __FILE__ )
  #endif
#endif

#ifndef KSTL_IO
    /*Note: Depending on the platform, wchar_t and L"String literals" may or
      may not be Unicode, and if they are Unicode, they could be
      UTF-16 or UCS-4. Non-Unicode forms can crop up on some platforms
      in some Asian locales, and sometimes on EBCDIC based mainframes.
      Portable Unicode based applications need to stay away from any
      use of wchar_t and the whatever family of functions that
      support wchar_t. Setting up Unicode string constants in portable
      C or C++ has no language support at all, and is a complete pain.
      The usual approach is to define a series of individual numeric
      constants for each character needed, then use a C array initializer
      to put together the string.
      2004-03-12 Andy Heninger, heninger@us.ibm.com, ICU Project
    */
  #define KSTL_IO 900
  #pragma message ("  Standard Template Library (STL) is used " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// STL stream classes with generic character code (width) mapping
#if defined _UNICODE || defined UNICODE
  typedef std::wstring        tstring;
  typedef std::wostringstream tostringstream;
  typedef std::wistringstream tistringstream;
    //Provides a stream interface to read or write characters from or to strings.
  typedef std::wstreambuf     tstreambuf;
    //Performs output operations with a stream buffer.
  typedef std::wostream       tostream; //FixMe! typedefs
    //Reads and interprets input from a stream buffer.
  typedef std::wistream       tistream;
    //Provides a stream interface to write data to files.
  typedef std::wofstream      tofstream;
    //Provides a stream interface to read data from files.
  typedef std::wifstream      tifstream;
    //A type basic_fstream specialized on TCHAR template parameters. 
    //See also: fstream, wfstream 
  typedef std::wfstream       tfstream;

    //Represents the standard input. It corresponds to the cstdio stream stdin.
  #define _tcin  wcin
    //Represents the standard output stream.
  #define _tcout wcout
    //Represents the standard error stream.
  #define _tcerr wcerr
    //Represents the standard log stream.
  #define _tclog wclog
#else
  typedef std::string        tstring;
  typedef std::ostringstream tostringstream;
  typedef std::istringstream tistringstream;
  typedef std::streambuf     tstreambuf;
  typedef std::ostream       tostream;
  typedef std::istream       tistream;
  typedef std::ofstream      tofstream;
  typedef std::ifstream      tifstream;
  typedef std::fstream       tfstream;

  #define _tcin  cin
  #define _tcout cout
  #define _tcerr cerr
  #define _tclog clog
#endif

///////////////////////////////////////////////////////////////////////////////
#endif  //_KOSTREAM_H_

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  17   Biblioteka1.16        2007-07-16 18:02:59  Darko Kolakovic ToDo!
 *  16   Biblioteka1.15        2007-07-10 17:54:46  Darko Kolakovic pragma
 *  15   Biblioteka1.14        2007-05-03 15:50:12  Darko Kolakovic KSTL_IO 1400
 *  14   Biblioteka1.13        2005-03-21 03:15:10  Darko           Fixed STLport
 *       query
 *  13   Biblioteka1.12        2004-10-07 00:58:13  Darko           new value for
 *       KSTL_VER / MSVC7
 *  12   Biblioteka1.11        2004-10-06 16:01:22  Darko           Unicode mapping
 *  11   Biblioteka1.10        2004-10-01 22:12:14  Darko           Moved tbool to
 *       separate file
 *  10   Biblioteka1.9         2004-09-28 14:06:16  Darko           comment
 *  9    Biblioteka1.8         2004-09-07 15:48:36  Darko           Comment
 *  8    Biblioteka1.7         2004-08-26 13:21:48  Darko           C compilation
 *       error
 *  7    Biblioteka1.6         2004-08-23 17:59:29  Darko           Unicode build
 *  6    Biblioteka1.5         2004-06-03 14:26:59  Darko           Added stream
 *       tag KSTL_IO
 *  5    Biblioteka1.4         2004-06-01 18:03:43  Darko           STLport
 *       included
 *  4    Biblioteka1.3         2003-09-30 09:12:42  Darko           tbool
 *  3    Biblioteka1.2         2003-09-22 22:26:26  Darko           formatting
 *  2    Biblioteka1.1         2003-09-22 21:26:34  Darko           Unicode
 *  1    Biblioteka1.0         2003-09-22 18:34:47  Darko           
 * $
 *****************************************************************************/
