/*$Workfile: S:\_SrcPool\Cpp\KTChar.h$: header file
  $Revision: 21$ $Date: 2004-11-23 15:49:35$
  $Author: Darko Kolakovic$

  Unicode mapping layer for the standard C library with definitions for generic
  international text functions.
  Ported from Microsoft header files.
 */
/* Group=Strings                                                             */

#ifdef __MWERKS__
  //Metrowerks CodeWarrior Compiler
  #if (__MWERKS__ >= 0x3000)
    #pragma once
  #endif
  //.../MSL/MSL_C/MSL_Common/Include
  #include <wchar_t.h>
  #define wchar_t wchar_t
#endif

#ifdef  _MSC_VER
  //Microsoft Visual C/C++ Studio
  #if _MSC_VER > 1000
    #pragma once
  #endif

  #ifdef _UNICODE
    #ifndef UNICODE
      //To enable Unicode for some Microsoft Visual C/C++ header files,
      //the UNICODE definition is required
      #define UNICODE
    #endif
  #endif

  /*Use Microsoft header file instead of this custom file                    */
  #ifdef WIN32
    #include <wtypes.h>  //Basic Windows type Definitions
    #include <tchar.h>   //TCHAR typedef
  #endif

  #if (_MSC_VER < 1300)
    //Microsoft Visual Studio 6.0 or less
    //Include only parts of the header file
    #define __KTCHAR_H__ 1200
  #else
    #define __KTCHAR_H__ 1300
  #endif

#endif

#ifndef __palm_os
  /*Defined because expressions in the 
      #if constant-expression
      #endif
    directives must have integral type and can include only integer constants,
    character constants and the defined operator.
   */
  #define __palm_os 0XFFFF
#endif

#if defined (__PALMOS__) || (__dest_os == __palm_os)
  #include "Palm/KTCharPalm.h"
#endif

#ifndef __KTCHAR_H__
  /*$Workfile: S:\_SrcPool\Cpp\KTChar.h$ sentry  */
  #define __KTCHAR_H__ 1000
#endif

/* ////////////////////////////////////////////////////////////////////////// */
#if (__KTCHAR_H__ < 1300)

  #ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files   */
    #ifdef  _MSC_VER  //Microsoft C/C++
      #pragma message ("   #include " __FILE__ )
    #endif
    #ifdef __GNUC__   //GNU C/C++
      #warning "   #include KTChar.h"
    #endif
  #endif

#include <string.h>

#ifdef  __cplusplus
extern "C"
  {
#endif

/* ///////////////////////////////////////////////////////////////////////// */
#if (__KTCHAR_H__ <= 1000)

/* ========================================================================== */
/* Single byte Character Set SBCS (ASCII)                                     */
#ifndef _UNICODE /* !_UNICODE */
  #ifdef _DEBUG_INCL_PREPROCESS   /* Preprocessor: debugging included files  */
    #if defined _MSC_VER || defined __MWERKS__
      #pragma message ("   Single byte Character Set SBCS (ASCII)" )
    #endif
    #ifdef __GNUC__   //GNU C/C++
      #warning "   Single byte Character Set SBCS (ASCII)"
    #endif
  #endif

  #ifndef TCHAR
    /*-------------------------------------------------------------------------
      "Generic-text" mappings for many data types, routines, and other objects
      has been provided to simplify code development for various international
      environments.

         Generic-Text Data Type Mappings

        Type        SBCS           MBCS           _UNICODE
        TCHAR       char           char           wchar_t
        _TINT        int            int            wint_t
        _TSCHAR      signed char    signed char    wchar_t
        _TUCHAR      unsigned char  unsigned char  wchar_t
        _TXCHAR      char           unsigned char  wchar_t
        _T or _TEXT  No effect      No effect      L()
        _TEOF        EOF            EOF            WEOF

        Note: Depending on the platform, wchar_t and L"String literals" may or
              may not be Unicode, and if they are Unicode, they could be
              UTF-16 or UCS-4. Non-Unicode forms can crop up on some platforms
              in some Asian locales, and sometimes on EBCDIC based mainframes.
              Portable Unicode based applications need to stay away from any
              use of wchar_t and the wwhatever() family of functions that
              support wchar_t. Setting up Unicode string constants in portable
              C or C++ has no language support at all, and is a complete pain.
              The usual approach is to define a series of individual numeric
              constants for each character needed, then use a C array initializer
              to put together the string.
              2004-03-12 Andy Heninger, heninger@us.ibm.com, ICU Project
    */
    typedef char            TCHAR;

    typedef signed char     _TSCHAR;
    typedef unsigned char   _TUCHAR;
    typedef char            _TXCHAR;
    typedef int             _TINT;
    #define TCHAR TCHAR
  #endif

  /*_TEXT macro converts constant strings and characters to its Unicode
   counterpart if _UNICODE is defined
   */
  #define _TEXT(t)  t
  #ifndef _T
    /*Generic text literals

      Example:
        TRACE0(_T("This is a message\n"));

      See also: _TEXT
     */
    #define _T(t)     t
  #endif
  #define _TEOF     EOF           //End of File as generic text literal

  /*The following rules apply in determining what symbols are reserved for
    any standard.  These symbols are reserved for the standard and for use
    by the implementation, and must be either avoided altogether, or used
    exactly as defined by the specified standard.

    - All symbols defined by the desired standard are reserved. Refer to the
    appropriate standards documentation for a complete list of reserved symbols.
    - All symbols beginning with an underscore followed by another underscore
    or an uppercase letter are reserved for the implementation.
    - All external identifiers beginning with an underscore are reserved for
    the implementation.

    Note: symbols with preceding underscore are not part of the standard
          library. According to the ANSI C standard, external identifiers
          beginning with an underscore are reserved for library usage.
   */

  /*Formatted I/O                                                            */

  #ifndef _tprintf
    #define _tprintf    printf      //Print formatted output to the standard
                                    //output stream.
  #endif
  #ifndef _ftprintf
    #define _ftprintf   fprintf     //Print formatted data to a stream.
  #endif
  #ifndef _stprintf
    #define _stprintf   sprintf     //Write formatted data to a string.
  #endif
  #ifndef _sntprintf
    #define _sntprintf  _snprintf   //Write formatted data to a string.
  #endif
  #ifndef _vtprintf
    #define _vtprintf   vprintf     //Write formatted output using a pointer to
                                    //a list of arguments.
  #endif
  #ifndef _vftprintf
    #define _vftprintf  vfprintf    //Write formatted output using a pointer to
                                    //a list of arguments.
  #endif
  #ifndef _vstprintf
    #define _vstprintf  vsprintf    //Write formatted output using a pointer to
                                    //a list of arguments.
  #endif
  #ifndef _vsntprintf
    #define _vsntprintf _vsnprintf  //Write formatted output using a pointer to
                                    //a list of arguments.
  #endif
  #ifndef _tscanf
    #define _tscanf     scanf       //Read formatted data from the standard
                                    //input stream.
  #endif
  #ifndef _ftscanf
    #define _ftscanf    fscanf      //Read formatted data from a stream.
  #endif
  #ifndef _stscanf
    #define _stscanf    sscanf      //Read formatted data from a stream.
  #endif

  /*Unformatted I/O                                                          */

  #ifndef _fgettc
    #define _fgettc     fgetc       //Read a character from a stream.
  #endif
  #ifndef _fgettchar
    #define _fgettchar  _fgetchar   //Read a character from the standard input
                                    //stream.
  #endif
  #ifndef _fgetts
    #define _fgetts     fgets       //Get a string from a stream.
  #endif
  #ifndef _fputtc
    #define _fputtc     fputc       //Writes a character to a stream.
  #endif
  #ifndef _fputtchar
    #define _fputtchar  _fputchar   //Writes a character to the standard output
                                    //stream.
  #endif
  #ifndef _fputts
    #define _fputts     fputs       //Write a string to a stream.
  #endif
  #ifndef _gettc
    #define _gettc      getc        //Read a character from a stream.
  #endif
  #ifndef _getts
    #define _getts      gets        //Get a line from the stdin stream.
  #endif
  #ifndef _puttc
    #define _puttc      putc        //Writes a character to a stream.
  #endif
  #ifndef _putts
    #define _putts      puts        //Write a string to the standard output stream.
  #endif
  #ifndef _ungettc
    #define _ungettc    ungetc      //Pushes a character back onto the stream.
  #endif

  /*String conversion                                                        */

  #ifndef _tcstod
    #define _tcstod     strtod      //Convert strings to a double-precision value.
  #endif
  #ifndef _tcstol
    #define _tcstol     strtol      //Convert strings to a long-integer value.
  #endif
  #ifndef _tcstoul
    #define _tcstoul    strtoul     //Convert strings to an unsigned
                                    //long-integer value.
  #endif
  #ifndef _itoa
    #define _itoa       ItoA        //Convert an integer to a string
                                    //(non-ANSI declaration).
  #endif
  #ifndef _itot
    #define _itot       _itoa       //Convert an integer to a string.
  #endif

  /*String manipulators                                                      */

  #ifndef _tcscat
    #define _tcscat     strcat      //Append a string.
  #endif
  #ifndef _tcschr
    #define _tcschr     strchr      //Find a character in a string.
  #endif
  #ifndef _tcscmp
    #define _tcscmp     strcmp      //Compare strings.
  #endif
  #ifndef _tcscpy
    #define _tcscpy     strcpy      //Copy a string.
  #endif
  #ifndef _tcscspn
    #define _tcscspn    strcspn     //Find a substring in a string.
  #endif
  #ifndef _tcslen
    #define _tcslen     strlen      //Get the length of a string.
  #endif
  #ifndef _tcsncat
    #define _tcsncat    strncat     //Append characters of a string.
  #endif
  #ifndef _tcsncmp
    #define _tcsncmp    strncmp     //Compare characters of two strings.
  #endif
  #ifndef _tcsncpy
    #define _tcsncpy    strncpy     //Copy characters of one string to another.
  #endif
  #ifndef _tcspbrk
    #define _tcspbrk    strpbrk     //Scan strings for characters in specified
                                    //character sets.
  #endif
  #ifndef _tcsrchr
    #define _tcsrchr    strrchr     //Scan a string for the last occurrence of
                                    //a character.
  #endif
  #ifndef _tcsspn
    #define _tcsspn     strspn      //Find the first substring.
  #endif
  #ifndef _tcsstr
    #define _tcsstr     strstr      //Find a substring.
  #endif
  #ifndef _tcstok
    #define _tcstok     strtok      //Find the next token in a string.
  #endif
  #ifndef _tcsdup
    #define _tcsdup     _strdup     //Duplicate strings.
  #endif
  #ifndef _tcsicmp
    #define _tcsicmp    _stricmp    //Perform a lowercase comparison of strings.
  #endif
  #ifndef _tcsnicmp
    #define _tcsnicmp   _strnicmp   //Compare characters of two strings without
                                    //regard to case.
  #endif
  #ifndef _tcsnset
    #define _tcsnset    _strnset    //Initialize characters of a string to
                                    //a given format.
  #endif
  #ifndef _tcsrev
    #define _tcsrev     _strrev     //Reverse characters of a string.
  #endif
  #ifndef _tcsset
    #define _tcsset     _strset     //Set characters of a string to a character.
  #endif

  #ifndef _tcslwr
    #define _tcslwr     _strlwr     //Convert a string to lowercase.
  #endif
  #ifndef _tcsupr
    #define _tcsupr     _strupr     //Convert a string to uppercase.
  #endif
  #ifndef _tcsxfrm
    #define _tcsxfrm    strxfrm     //Transform a string based on
                                    //locale-specific information.
  #endif
  #ifndef _tcscoll
    #define _tcscoll    strcoll     //Compare strings using locale-specific
                                    //information.
  #endif
  #ifndef _tcsicoll
    #define _tcsicoll   _stricoll   //Compare strings using locale-specific
                                    //information.
  #endif

  /*ctype functions                                                          */

  #ifndef _istalpha
    #define _istalpha   isalpha     //Query if character is within the ranges
                                    //[A, Z] or [a, z].
  #endif
  #ifndef _istupper
    #define _istupper   isupper     //Query if character is an uppercase
                                    //character [A, Z].
  #endif
  #ifndef _istlower
    #define _istlower   islower     //Query if character is a lowercase
                                    //character [a, z].
  #endif
  #ifndef _istdigit
    #define _istdigit   isdigit     //Query if character is a decimal
                                    //digit [0, 9].
  #endif
  #ifndef _istxdigit
    #define _istxdigit  isxdigit    //Query if character is a hexadecimal digit
                                    //(A – F, a – f, or 0 – 9).
  #endif
  #ifndef _istspace
    #define _istspace   isspace     //Query if character is a white-space
                                    //character (0x09 – 0x0D or 0x20).
  #endif
  #ifndef _istpunct
    #define _istpunct   ispunct     //Query if character is any printable
                                    //character that is not a space character or
                                    //a letter or a digit.
  #endif
  #ifndef _istalnum
    #define _istalnum   isalnum     //Query if character is within the ranges
                                    //[A, Z], [a, z], or [0, 9].
  #endif
  #ifndef _istprint
    #define _istprint   isprint     //Query if character is a printable character,
                                    //including the space character (0x20 – 0x7E).
  #endif
  #ifndef _istgraph
    #define _istgraph   isgraph     //Query if character is a printable character
                                    //other than a space.
  #endif
  #ifndef _istcntrl
    #define _istcntrl   iscntrl     //Query if character is a control character
                                    //(0x00 – 0x1F or 0x7F).
  #endif
  #ifndef _istascii
    #define _istascii   isascii     //Query if character is an ASCII character
                                    //(in the range 0x00 – 0x7F).
  #endif
  #ifndef _totupper
    #define _totupper   toupper     //Convert character to uppercase.
  #endif
  #ifndef _totlower
    #define _totlower   tolower     //Convert character to lowercase.
  #endif

  /*Time functions                                                           */

  #ifndef _tasctime
    #define _tasctime   asctime     //Converts a tm time structure to
                                    //a character string.
  #endif
  #ifndef _tctime
    #define _tctime     ctime       //Convert a time value to a string and
                                    //adjust for local time zone settings.
  #endif
  #ifndef _tstrdate
    #define _tstrdate   _strdate    //Copy a date to a buffer.
  #endif
  #ifndef _tstrtime
    #define _tstrtime   _strtime    //Copy the time to a buffer.
  #endif
  #ifndef _tutime
    #define _tutime     _utime      //Set the file modification time.
  #endif
  #ifndef _tcsftime
    #define _tcsftime   strftime    //Format a time string.
  #endif

  /*StdIO functions                                                          */

  #ifndef _tfdopen
    #define _tfdopen    fdopen      //POSIX Assign a stream to a file that was
                                    //previously opened for low-level I/O
  #endif
  #ifndef _tfsopen
    #define _tfsopen    _fsopen     //Open a stream with file sharing.
  #endif
  #ifndef _tfopen
    #define _tfopen     fopen       //Open a file.
  #endif
  #ifndef _tfreopen
    #define _tfreopen   freopen     //Reassign a file pointer.
  #endif
  #ifndef _tperror
    #define _tperror    perror      //Print an error message.
  #endif
  #ifndef _tpopen
    #define _tpopen     _popen      //Creates a pipe and executes a command.
  #endif
  #ifndef _ttempnam
    #define _ttempnam   _tempnam    //Create temporary filenames.
  #endif
  #ifndef _ttmpnam
    #define _ttmpnam    tmpnam      //Create temporary filenames.
  #endif

  /* I/O functions                                                           */

  #ifndef _tchmod
    #define _tchmod     _chmod      //Change the file-permission settings.
  #endif
  #ifndef _tcreat
    #define _tcreat     _creat      //Creates a new file.
  #endif
  #ifndef _tmktemp
    #define _tmktemp    _mktemp     //Create a unique filename.
  #endif
  #ifndef _topen
    #define _topen      open        //POSIX Open a file.
  #endif
  #ifndef _taccess
    #define _taccess    access      //POSIX Determine file-access permission.
  #endif
  #ifndef _tremove
    #define _tremove    remove      //Delete a file.
  #endif
  #ifndef _trename
    #define _trename    rename      //Rename a file or directory.
  #endif
  #ifndef _tsopen
    #define _tsopen     _sopen      //Open a file for sharing.
  #endif
  #ifndef _tunlink
    #define _tunlink    _unlink     //Delete a file.
  #endif
  #ifndef _tcsinc
    #define _tcsinc(pChar)     ((TCHAR*)((TCHAR*)(pChar)+1)) /*Incremets a pointer
                                                  to a character for one.
                                                  Added for compatiblity with MS
                                                  multibyte _mbsinc().
                                                  */
  #endif


/* =========================================================================
  Unicode mapping layer for the standard C library (wide-character).
  To enable Unicode compiling define _UNICODE before including KTChar.h,
  otherwise the standard non-unicode library functions will be used.         */
#else  //_UNICODE
  #ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
    #ifdef  _MSC_VER  //Microsoft C/C++
      #pragma message ("   Unicode (wide-character)" )
    #endif
    #ifdef __GNUC__   //GNU C/C++
      #warning "   Unicode (wide-character)"
    #endif
  #endif

  #include <wchar.h>

  #ifndef TCHAR
    typedef wchar_t     TCHAR;
    typedef wchar_t     _TSCHAR;
    typedef wchar_t     _TUCHAR;
    typedef wchar_t     _TXCHAR;
    #ifdef WIN32
      typedef wint_t      _TINT;
    #endif
    #define TCHAR TCHAR
  #endif

  #define _TEXT(t)    L ## t
  #ifndef _T
    #define _T(t)       L ## t
  #endif
  #ifndef _TEOF
    #define _TEOF       WEOF
  #endif

  #ifndef  _tprintf
    #define  _tprintf    wprintf
  #endif
  #ifndef  _ftprintf
    #define  _ftprintf   fwprintf
  #endif
  #ifndef  _stprintf
    #define  _stprintf   swprintf
  #endif
  #ifndef  _sntprintf
    #define  _sntprintf  _snwprintf
  #endif
  #ifndef  _vtprintf
    #define  _vtprintf   vwprintf
  #endif
  #ifndef  _vftprintf
    #define  _vftprintf  vfwprintf
  #endif
  #ifndef _vstprintf
    #define _vstprintf   vswprintf
  #endif
  #ifndef  _vsntprintf
    #define  _vsntprintf _vsnwprintf
  #endif
  #ifndef  _tscanf
    #define  _tscanf    wscanf
  #endif
  #ifndef  _ftscanf
    #define  _ftscanf   fwscanf
  #endif
  #ifndef  _stscanf
    #define  _stscanf   swscanf
  #endif
  #ifndef  _fgettc
    #define  _fgettc    fgetwc
  #endif
  #ifndef  _fgettchar
    #define  _fgettchar _fgetwchar
  #endif
  #ifndef  _fgetts
    #define  _fgetts    fgetws
  #endif
  #ifndef  _fputtc
    #define  _fputtc    fputwc
  #endif
  #ifndef  _fputtchar
    #define  _fputtchar _fputwchar
  #endif
  #ifndef  _fputts
    #define  _fputts    fputws
  #endif
  #ifndef  _gettc
    #define  _gettc     getwc
  #endif
  #ifndef  _getts
    #define  _getts     getws
  #endif
  #ifndef  _puttc
    #define  _puttc     putwc
  #endif
  #ifndef  _putts
    #define  _putts     putws
  #endif
  #ifndef  _ungettc
    #define  _ungettc   ungetwc
  #endif
  #ifndef  _tcstod
    #define  _tcstod    wcstod
  #endif
  #ifndef  _tcstol
    #define  _tcstol    wcstol
  #endif
  #ifndef _tcstoul
    #define _tcstoul    wcstoul
  #endif
  #ifndef _itot
    #define _itot       _itow       //Convert an integer to a string.
  #endif
  #ifndef  _tcscat
    #define  _tcscat    wcscat
  #endif
  #ifndef _tcschr
    #define _tcschr     wcschr
  #endif
  #ifndef _tcscmp
    #define _tcscmp     wcscmp
  #endif
  #ifndef _tcscpy
    #define _tcscpy     wcscpy
  #endif
  #ifndef _tcscspn
    #define _tcscspn    wcscspn
  #endif
  #ifndef  _tcslen
    #define  _tcslen    wcslen
  #endif
  #ifndef  _tcsncat
    #define  _tcsncat   wcsncat
  #endif
  #ifndef  _tcsncmp
    #define  _tcsncmp   wcsncmp
  #endif
  #ifndef  _tcsncpy
    #define  _tcsncpy   wcsncpy
  #endif
  #ifndef  _tcspbrk
    #define  _tcspbrk   wcspbrk
  #endif
  #ifndef  _tcsrchr
    #define  _tcsrchr   wcsrchr
  #endif
  #ifndef _tcsspn
    #define _tcsspn     wcsspn
  #endif
  #ifndef  _tcsstr
    #define  _tcsstr    wcsstr
  #endif
  #ifndef _tcstok
    #define _tcstok     wcstok
  #endif
  #ifndef  _tcsdup
    #define  _tcsdup    _wcsdup
  #endif
  #ifndef  _tcsicmp
    #define  _tcsicmp   _wcsicmp
  #endif
  #ifndef  _tcsnicmp
    #define  _tcsnicmp  _wcsnicmp
  #endif
  #ifndef  _tcsnset
    #define  _tcsnset   _wcsnset
  #endif
  #ifndef  _tcsrev
    #define  _tcsrev    _wcsrev
  #endif
  #ifndef _tcsset
    #define _tcsset     _wcsset
  #endif
  #ifndef  _tcslwr
    #define  _tcslwr    _wcslwr
  #endif
  #ifndef  _tcsupr
    #define  _tcsupr    _wcsupr
  #endif
  #ifndef  _tcsxfrm
    #define  _tcsxfrm   wcsxfrm
  #endif
  #ifndef  _tcscoll
    #define  _tcscoll   wcscoll
  #endif
  #ifndef  _tcsicoll
    #define  _tcsicoll  _wcsicoll
  #endif
  #ifndef  _istalpha
    #define  _istalpha  iswalpha
  #endif
  #ifndef  _istupper
    #define  _istupper  iswupper
  #endif
  #ifndef  _istlower
    #define  _istlower  iswlower
  #endif
  #ifndef  _istdigit
    #define  _istdigit  iswdigit
  #endif
  #ifndef  _istxdigit
    #define  _istxdigit iswxdigit
  #endif
  #ifndef  _istspace
    #define  _istspace  iswspace
  #endif
  #ifndef  _istpunct
    #define  _istpunct  iswpunct
  #endif
  #ifndef  _istalnum
    #define  _istalnum  iswalnum
  #endif
  #ifndef  _istprint
    #define  _istprint  iswprint
  #endif
  #ifndef  _istgraph
    #define  _istgraph  iswgraph
  #endif
  #ifndef  _istcntrl
    #define  _istcntrl  iswcntrl
  #endif
  #ifndef  _istascii
    #define  _istascii  iswascii
  #endif
  #ifndef _totupper
    #define _totupper   towupper
  #endif
  #ifndef  _totlower
    #define  _totlower  towlower
  #endif
  #ifndef _tasctime
    #define _tasctime   _wasctime
  #endif
  #ifndef _tctime
    #define _tctime     _wctime
  #endif
  #ifndef _tstrdate
    #define _tstrdate   _wstrdate
  #endif
  #ifndef _tstrtime
    #define _tstrtime   _wstrtime
  #endif
  #ifndef _tutime
    #define _tutime     _wutime
  #endif
  #ifndef _tcsftime
    #define _tcsftime   wcsftime
  #endif
  #ifndef _tfdopen
    #define _tfdopen    _wfdopen
  #endif
  #ifndef _tfsopen
    #define _tfsopen    _wfsopen
  #endif
  #ifndef _tfopen
    #define _tfopen     _wfopen
  #endif
  #ifndef _tfreopen
    #define _tfreopen   _wfreopen
  #endif
  #ifndef _tperror
    #define _tperror    _wperror
  #endif
  #ifndef _tpopen
    #define _tpopen     _wpopen
  #endif
  #ifndef _ttempnam
    #define _ttempnam   _wtempnam
  #endif
  #ifndef _ttmpnam
    #define _ttmpnam    _wtmpnam
  #endif
  #ifndef _tchmod
    #define _tchmod     _wchmod
  #endif
  #ifndef _tcreat
    #define _tcreat     _wcreat
  #endif
  #ifndef _tmktemp
    #define _tmktemp    _wmktemp
  #endif
  #ifndef _topen
    #define _topen      _wopen
  #endif
  #ifndef _taccess
    #define _taccess    _waccess
  #endif
  #ifndef _tremove
    #define _tremove    _wremove
  #endif
  #ifndef _trename
    #define _trename    _wrename
  #endif
  #ifndef _tsopen
    #define _tsopen     _wsopen
  #endif
  #ifndef _tunlink
    #define _tunlink    _wunlink
  #endif
  #ifndef _tcsinc
    #define _tcsinc(pChar)     ((TCHAR*)((TCHAR*)(pChar)+1))
  #endif


/* ========================================================================= */
#endif // _UNICODE

/* ////////////////////////////////////////////////////////////////////////// */
/* Common types                                                               */

#ifdef __cplusplus
  //wide-character is build-in type
  #define wchar_t wchar_t
#endif

#ifndef wchar_t
  typedef unsigned short wchar_t;
  #define wchar_t wchar_t
#endif

#ifndef LPCTSTR
  typedef const TCHAR*     LPCTSTR;
  #define LPCTSTR LPCTSTR
#endif

#ifndef LPTSTR
  typedef       TCHAR*     LPTSTR;
  #define LPTSTR LPTSTR
#endif

#ifndef _WIN32
  #ifndef PCSTR
    typedef const char*    PCSTR; /*Pointer to character string constant*/
    #define PCSTR PCSTR
  #endif

  #ifndef PSTR
    typedef       char*    PSTR; /*Pointer to character string*/
    #define PSTR PSTR
  #endif

  #ifndef PCWSTR
    typedef const wchar_t* PCWSTR; /*Pointer to wide-character string constant*/
    #define PCWSTR PCWSTR
  #endif

  #ifndef PWSTR
    typedef       wchar_t* PWSTR; /*Pointer to wide-character string*/
    #define PWSTR PWSTR
  #endif

  #ifndef OLECHAR
     /*OLE (Microsoft's Object Linking and Embedding) character type used in
       Distributed Component Object Model (DCOM) interfaces*/
    typedef       wchar_t  OLECHAR;
    #define OLECHAR OLECHAR
  #endif

#endif /*!_WIN32*/

/* ///////////////////////////////////////////////////////////////////////// */
#endif  //__KTCHAR_H__ <= 1000

/* ///////////////////////////////////////////////////////////////////////// */
#if (__KTCHAR_H__ <= 1200)

  /* ======================================================================= */
  /* Single byte Character Set SBCS (ASCII)                                  */
  #ifndef _UNICODE /* !_UNICODE */
    /*String conversion                                                      */

    #ifndef _tstof
      #define _tstof    atof          /*Convert strings a double-precision,
                                        floating-point value.*/
    #endif
    #ifndef _tstoi
      #define _tstoi    atoi          //Convert strings an integer value
    #endif
    #ifndef _tstoi64
      #define _tstoi64  _atoi64       //Convert strings an integer value
    #endif
    #ifndef _tstol
      #define _tstol    atol          //Convert strings a long integer value
    #endif
    #ifndef _ttoi
      #define _ttoi     atoi          //Convert strings an integer value
    #endif
    #ifndef _ttoi64
      #define _ttoi64   _atoi64       //Convert strings an integer value
    #endif
    #ifndef _ttol
      #define _ttol     atol          //Convert strings a long integer value
    #endif

  /* ======================================================================= */
  #else  //_UNICODE

    #ifndef _tstof
      #define _tstof      _wtof
    #endif
    #ifndef _tstoi
      #define _tstoi      _wtoi
    #endif
    #ifndef _tstoi64
      #define _tstoi64    _wtoi64
    #endif
    #ifndef _tstol
      #define _tstol      _wtol
    #endif
    #ifndef _ttoi
      #define _ttoi       _wtoi
    #endif
    #ifndef _ttoi64
      #define _ttoi64     _wtoi64
    #endif
    #ifndef _ttol
      #define _ttol       _wtol
    #endif

  /* ======================================================================= */
  #endif // _UNICODE

/* ///////////////////////////////////////////////////////////////////////// */
#endif  //__KTCHAR_H__ <= 1200

/* ////////////////////////////////////////////////////////////////////////// */
#ifdef  __cplusplus
  } //extern "C"
#endif
/* ////////////////////////////////////////////////////////////////////////// */
#endif //__KTCHAR_H__ < 1300
/*****************************************************************************
 * $Log:
 *  11   Biblioteka1.10        2004-06-08 16:43:24  Darko           Note UTF-8
 *  10   Biblioteka1.9         2003-11-03 13:14:14  Darko           Replaced
 *       windows.h with wtypes.h
 *  9    Biblioteka1.8         2003-09-22 22:26:58  Darko           formatting
 *  8    Biblioteka1.7         2002-08-27 23:36:18  Darko           _tcsinc()
 *  7    Biblioteka1.6         2002-08-19 10:38:17  Darko Kolakovic
 *  6    Biblioteka1.5         2002-02-12 17:42:35  Darko           GNU issues
 *  5    Biblioteka1.4         2002-02-12 10:55:32  Darko           itoa()
 *  4    Biblioteka1.3         2002-02-04 19:58:44  Darko           ifdef  _MSC_VER
 *       include windows.h
 *  3    Biblioteka1.2         2002-01-06 01:48:03  Darko
 *  2    Biblioteka1.1         2001-10-13 14:07:49  Darko           GNU tags
 *  1    Biblioteka1.0         2001-10-05 15:34:19  Darko
 * $
 * Revision 1.1  2001/10/13 17:50:36  dkolaCVS StdIO functions
 *  1    Biblioteka1.0         10/5/01 3:34:19 PM   Darko
 * Nov 99 Used MS as template D.K. CommonSoft Inc
 *****************************************************************************/
