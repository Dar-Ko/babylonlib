/*$Workfile: KTChar.h$: header file
  $Revision: 8$ $Date: 27/08/2002 10:36:18 PM$ 
  $Author: Darko$

  Unicode mapping layer for the standard C library with definitions for generic
  international text functions.
  Ported from Microsoft header files.
 */
/* Group=Strings                                                             */

#ifdef  _MSC_VER
  /*Use Microsoft header file instead of this custom file                    */
  #ifdef WIN32
    #include <windows.h> //Basic Windows type Definitions
    #include <tchar.h>   //TCHAR typedef
    #define __KTCHAR_H__ 1
  #endif
#endif

#if _MSC_VER > 1000
  #pragma once
#endif

#ifndef __KTCHAR_H__
  /*KTChar.h sentry  */
  #define __KTCHAR_H__ 2

  #ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files   */
    #ifdef  _MSC_VER  //Microsoft C/C++
      #pragma message ("   #include " __FILE__ )
    #endif
    #ifdef __GNUC__   //GNU C/C++
      #warning "   #include KTChar.h"
    #endif
  #endif

#include <String.h>

#ifdef  __cplusplus
extern "C"
  {
#endif

/* ///////////////////////////////////////////////////////////////////////// */
/* Single byte Character Set SBCS (ASCII)                                     */
#ifndef _UNICODE /* !_UNICODE */
  #ifdef _DEBUG_INCL_PREPROCESS   /* Preprocessor: debugging included files  */
    #ifdef  _MSC_VER  //Microsoft C/C++
      #pragma message ("   Single byte Character Set SBCS (ASCII)" )
    #endif
    #ifdef __GNUC__   //GNU C/C++
      #warning "   Single byte Character Set SBCS (ASCII)"
    #endif
  #endif

  #ifndef _TCHAR_DEFINED
    /*-------------------------------------------------------------------------
      "Generic-text" mappings for many data types, routines, and other objects
      has been provided to simplify code development for various international
      environments.

         Generic-Text Data Type Mappings

        Type      	SBCS         	MBCS         	_UNICODE
        TCHAR     	char         	char         	wchar_t
        _TINT      	int          	int          	wint_t
        _TSCHAR    	signed char  	signed char  	wchar_t
        _TUCHAR    	unsigned char	unsigned char	wchar_t
        _TXCHAR    	char         	unsigned char	wchar_t
        _T or _TEXT	No effect    	No effect    	L()
        _TEOF      	EOF          	EOF          	WEOF
    */
    typedef char            TCHAR;

    typedef signed char     _TSCHAR;
    typedef unsigned char   _TUCHAR;
    typedef char            _TXCHAR;
    typedef int             _TINT;
    #define _TCHAR_DEFINED 1
  #endif

  /*_TEXT macro converts constant strings and characters to its Unicode 
   counterpart if _UNICODE is defined
   */
  #define _TEXT(t)  t
  #define _T(t)     t             //See also: _TEXT
  #define _TEOF     EOF           //End of File

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

  #define _tprintf    printf      //Print formatted output to the standard output stream.
  #define _ftprintf   fprintf     //Print formatted data to a stream.
  #define _stprintf   sprintf     //Write formatted data to a string.
  #define _sntprintf  _snprintf   //Write formatted data to a string.
  #define _vtprintf   vprintf     //Write formatted output using a pointer to a list of arguments.
  #define _vftprintf  vfprintf    //Write formatted output using a pointer to a list of arguments.
  #define _vstprintf  vsprintf    //Write formatted output using a pointer to a list of arguments.
  #define _vsntprintf _vsnprintf  //Write formatted output using a pointer to a list of arguments.
  #define _tscanf     scanf       //Read formatted data from the standard input stream.
  #define _ftscanf    fscanf      //Read formatted data from a stream.
  #define _stscanf    sscanf      //Read formatted data from a stream.

  /*Unformatted I/O                                                          */

  #define _fgettc     fgetc       //Read a character from a stream.
  #define _fgettchar  _fgetchar   //Read a character from the standard input stream.
  #define _fgetts     fgets       //Get a string from a stream.
  #define _fputtc     fputc       //Writes a character to a stream.
  #define _fputtchar  _fputchar   //Writes a character to the standard output stream.
  #define _fputts     fputs       //Write a string to a stream.
  #define _gettc      getc        //Read a character from a stream.
  #define _getts      gets        //Get a line from the stdin stream.
  #define _puttc      putc        //Writes a character to a stream.
  #define _putts      puts        //Write a string to the standard output stream.
  #define _ungettc    ungetc      //Pushes a character back onto the stream.

  /*String conversion                                                        */

  #define _tcstod     strtod      //Convert strings to a double-precision value.
  #define _tcstol     strtol      //Convert strings to a long-integer value.
  #define _tcstoul    strtoul     //Convert strings to an unsigned long-integer value.
  #define _itoa       ItoA        //Convert an integer to a string (non-ANSI declaration).
  #define _itot       _itoa       //Convert an integer to a string.

  /*String manipulators                                                      */

  #define _tcscat     strcat      //Append a string.
  #define _tcschr     strchr      //Find a character in a string.
  #define _tcscmp     strcmp      //Compare strings.
  #define _tcscpy     strcpy      //Copy a string.
  #define _tcscspn    strcspn     //Find a substring in a string.
  #define _tcslen     strlen      //Get the length of a string.
  #define _tcsncat    strncat     //Append characters of a string.
  #define _tcsncmp    strncmp     //Compare characters of two strings.
  #define _tcsncpy    strncpy     //Copy characters of one string to another.
  #define _tcspbrk    strpbrk     //Scan strings for characters in specified character sets.
  #define _tcsrchr    strrchr     //Scan a string for the last occurrence of a character.
  #define _tcsspn     strspn      //Find the first substring.
  #define _tcsstr     strstr      //Find a substring.
  #define _tcstok     strtok      //Find the next token in a string.
  #define _tcsdup     _strdup     //Duplicate strings.
  #define _tcsicmp    _stricmp    //Perform a lowercase comparison of strings.
  #define _tcsnicmp   _strnicmp   //Compare characters of two strings without regard to case.
  #define _tcsnset    _strnset    //Initialize characters of a string to a given format.
  #define _tcsrev     _strrev     //Reverse characters of a string.
  #define _tcsset     _strset     //Set characters of a string to a character.

  #define _tcslwr     _strlwr     //Convert a string to lowercase.
  #define _tcsupr     _strupr     //Convert a string to uppercase.
  #define _tcsxfrm    strxfrm     //Transform a string based on locale-specific information.
  #define _tcscoll    strcoll     //Compare strings using locale-specific information.
  #define _tcsicoll   _stricoll   //Compare strings using locale-specific information.

  /*ctype functions                                                          */

  #define _istalpha   isalpha     //Query if character is within the ranges A – Z or a – z.
  #define _istupper   isupper     //Query if character is an uppercase character (A – Z). 
  #define _istlower   islower     //Query if character is a lowercase character (a – z).
  #define _istdigit   isdigit     //Query if character is a decimal digit (0 – 9).
  #define _istxdigit  isxdigit    //Query if character is a hexadecimal digit (A – F, a – f, or 0 – 9).
  #define _istspace   isspace     //Query if character is a white-space character (0x09 – 0x0D or 0x20).
  #define _istpunct   ispunct     //Query if character is any printable character that is not a space character or a letter or a digit.
  #define _istalnum   isalnum     //Query if character is within the ranges A – Z, a – z, or 0 – 9.
  #define _istprint   isprint     //Query if character is a printable character, including the space character (0x20 – 0x7E).
  #define _istgraph   isgraph     //Query if character is a printable character other than a space.
  #define _istcntrl   iscntrl     //Query if character is a control character (0x00 – 0x1F or 0x7F).
  #define _istascii   isascii     //Query if character is an ASCII character (in the range 0x00 – 0x7F).
  #define _totupper   toupper     //Convert character to uppercase.
  #define _totlower   tolower     //Convert character to lowercase.

  /*Time functions                                                           */

  #define _tasctime   asctime     //Converts a tm time structure to a character string.
  #define _tctime     ctime       //Convert a time value to a string and adjust for local time zone settings.
  #define _tstrdate   _strdate    //Copy a date to a buffer.
  #define _tstrtime   _strtime    //Copy the time to a buffer.
  #define _tutime     _utime      //Set the file modification time.
  #define _tcsftime   strftime    //Format a time string.

  /*StdIO functions                                                          */

  #define _tfdopen    fdopen      //POSIX Assign a stream to a file that was previously opened for low-level I/O
  #define _tfsopen    _fsopen     //Open a stream with file sharing.
  #define _tfopen     fopen       //Open a file.
  #define _tfreopen   freopen     //Reassign a file pointer.
  #define _tperror    perror      //Print an error message.
  #define _tpopen     _popen      //Creates a pipe and executes a command.
  #define _ttempnam   _tempnam    //Create temporary filenames.
  #define _ttmpnam    tmpnam      //Create temporary filenames.

  /* I/O functions                                                           */

  #define _tchmod     _chmod      //Change the file-permission settings.
  #define _tcreat     _creat      //Creates a new file.
  #define _tmktemp    _mktemp     //Create a unique filename.
  #define _topen      open        //POSIX Open a file.
  #define _taccess    access      //POSIX Determine file-access permission.
  #define _tremove    remove      //Delete a file.
  #define _trename    rename      //Rename a file or directory.
  #define _tsopen     _sopen      //Open a file for sharing.
  #define _tunlink    _unlink     //Delete a file.
  #define _tcsinc(pChar)     ((TCHAR*)((TCHAR*)(pChar)+1)) /*Incremets a pointer to a character for one*/
                                                           /*Added for compatiblity with MS multibyte _mbsinc()*/

/* //////////////////////////////////////////////////////////////////////////
  Unicode mapping layer for the standard C library (wide-character).
  To enable Unicode compiling define _UNICODE before including KTChar.h, 
  otherwise the standard non-unicode library functions will be used.        */
#else  //_UNICODE
  #ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
    #ifdef  _MSC_VER  //Microsoft C/C++
      #pragma message ("   Unicode (wide-character)" )
    #endif
    #ifdef __GNUC__   //GNU C/C++
      #warning "   Unicode (wide-character)"
    #endif
  #endif

  #include <WChar.h>

  #ifndef __TCHAR_DEFINED
    typedef wchar_t     TCHAR;
    typedef wchar_t     _TSCHAR;
    typedef wchar_t     _TUCHAR;
    typedef wchar_t     _TXCHAR;
    typedef wint_t      _TINT;
    typedef const unsigned short* LPCTSTR;
    #define __TCHAR_DEFINED
  #endif

  #define _TEXT(t)    L ## t
  #define _T(t)       L ## t
  #define _TEOF       WEOF

  #define  _tprintf    wprintf
  #define  _ftprintf   fwprintf
  #define  _stprintf   swprintf
  #define  _sntprintf  _snwprintf
  #define  _vtprintf   vwprintf
  #define  _vftprintf  vfwprintf
  #define _vstprintf   vswprintf
  #define  _vsntprintf _vsnwprintf
  #define  _tscanf    wscanf
  #define  _ftscanf   fwscanf
  #define  _stscanf   swscanf
  #define  _fgettc    fgetwc
  #define  _fgettchar _fgetwchar
  #define  _fgetts    fgetws
  #define  _fputtc    fputwc
  #define  _fputtchar _fputwchar
  #define  _fputts    fputws
  #define  _gettc     getwc
  #define  _getts     getws
  #define  _puttc     putwc
  #define  _putts     putws
  #define  _ungettc   ungetwc
  #define  _tcstod    wcstod
  #define  _tcstol    wcstol
  #define _tcstoul    wcstoul
  #define _itot       _itow       //Convert an integer to a string.
  #define  _tcscat    wcscat
  #define _tcschr     wcschr
  #define _tcscmp     wcscmp
  #define _tcscpy     wcscpy
  #define _tcscspn    wcscspn
  #define  _tcslen    wcslen
  #define  _tcsncat   wcsncat
  #define  _tcsncmp   wcsncmp
  #define  _tcsncpy   wcsncpy
  #define  _tcspbrk   wcspbrk
  #define  _tcsrchr   wcsrchr
  #define _tcsspn     wcsspn
  #define  _tcsstr    wcsstr
  #define _tcstok     wcstok
  #define  _tcsdup    _wcsdup
  #define  _tcsicmp   _wcsicmp
  #define  _tcsnicmp  _wcsnicmp
  #define  _tcsnset   _wcsnset
  #define  _tcsrev    _wcsrev
  #define _tcsset     _wcsset
  #define  _tcslwr    _wcslwr
  #define  _tcsupr    _wcsupr
  #define  _tcsxfrm   wcsxfrm
  #define  _tcscoll   wcscoll
  #define  _tcsicoll  _wcsicoll
  #define  _istalpha  iswalpha
  #define  _istupper  iswupper
  #define  _istlower  iswlower
  #define  _istdigit  iswdigit
  #define  _istxdigit iswxdigit
  #define  _istspace  iswspace
  #define  _istpunct  iswpunct
  #define  _istalnum  iswalnum
  #define  _istprint  iswprint
  #define  _istgraph  iswgraph
  #define  _istcntrl  iswcntrl
  #define  _istascii  iswascii
  #define _totupper   towupper
  #define  _totlower  towlower
  #define _tasctime   _wasctime
  #define _tctime     _wctime
  #define _tstrdate   _wstrdate
  #define _tstrtime   _wstrtime
  #define _tutime     _wutime
  #define _tcsftime   wcsftime
  #define _tfdopen    _wfdopen
  #define _tfsopen    _wfsopen
  #define _tfopen     _wfopen
  #define _tfreopen   _wfreopen
  #define _tperror    _wperror
  #define _tpopen     _wpopen
  #define _ttempnam   _wtempnam
  #define _ttmpnam    _wtmpnam
  #define _tchmod     _wchmod
  #define _tcreat     _wcreat
  #define _tmktemp    _wmktemp
  #define _topen      _wopen
  #define _taccess    _waccess
  #define _tremove    _wremove
  #define _trename    _wrename
  #define _tsopen     _wsopen
  #define _tunlink    _wunlink
  #define _tcsinc(pChar)     ((TCHAR*)((TCHAR*)(pChar)+1))


///////////////////////////////////////////////////////////////////////////////
#endif // _UNICODE

/* ////////////////////////////////////////////////////////////////////////// */
/* Common types                                                               */

#ifndef _LPCTSTR_DEFINED
  typedef const TCHAR*     LPCTSTR;
  #define _LPCTSTR_DEFINED 1
#endif

#ifndef _LPTSTR_DEFINED
  typedef       TCHAR*     LPTSTR;
  #define _LPTSTR_DEFINED 1
#endif


/* ////////////////////////////////////////////////////////////////////////// */
#ifdef  __cplusplus
  } //extern "C"
#endif

#endif //__KTCHAR_H__
/*****************************************************************************
 * $Log: 
 *  8    Biblioteka1.7         27/08/2002 10:36:18 PMDarko           _tcsinc()
 *  7    Biblioteka1.6         19/08/2002 9:38:17 AMDarko Kolakovic 
 *  6    Biblioteka1.5         12/02/2002 4:42:35 PMDarko           GNU issues
 *  5    Biblioteka1.4         12/02/2002 9:55:32 AMDarko           itoa()
 *  4    Biblioteka1.3         04/02/2002 6:58:44 PMDarko           ifdef  _MSC_VER
 *       include windows.h
 *  3    Biblioteka1.2         06/01/2002 12:48:03 AMDarko           
 *  2    Biblioteka1.1         13/10/2001 1:07:49 PMDarko           GNU tags
 *  1    Biblioteka1.0         05/10/2001 2:34:19 PMDarko           
 * $
 * Revision 1.1  2001/10/13 17:50:36  dkolaCVS StdIO functions
 *  1    Biblioteka1.0         10/5/01 3:34:19 PM   Darko
 * Nov 99 Used MS as template D.K. CommonSoft Inc
 *****************************************************************************/
