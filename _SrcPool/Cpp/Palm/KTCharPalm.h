/*$Workfile: KTCharPalm.h$: header file
  $Revision: 2$ $Date: 2004-11-09 18:46:04$
  $Author: Darko Kolakovic$

  PalmOS type definitions
  Copyright: CommonSoft Inc
  2004-11-09 Darko Kolakovic
 */

#ifndef _KTCHARPALM_H_
  /*$Workfile: KTCharPalm.h$ sentry*/
  #define _KTCHARPALM_H_

#if __MWERKS__ >= 0x3000
  #pragma once
#endif //__MWERKS__ >= 0x3000

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

/* ///////////////////////////////////////////////////////////////////////// */
/* // PalmOS 32-bit                                                          */

#if defined(__PALMOS__) || defined (__PALMOS_H__)

  #if !defined(_PALMOS)
    #define _PALMOS PALMOS_SDK_VERSION      /*Palm OS */
  #endif

  /*Note: Char type could be single or multi-byte character, depending of
    underlying platform.
   */
  #ifndef TCHAR
    /*"Generic-text" mappings*/
    typedef Char  TCHAR;
    #define TCHAR TCHAR
  #endif

  #ifdef __KTCHAR_H__
    #undef _T
  #endif
  /*Generic text literals

    Example:
      TRACE0(_T("This is a message\n"));
   */
  #define _T(t)   t

  #ifndef LPCTSTR
    typedef const TCHAR*     LPCTSTR;
    #define LPCTSTR LPCTSTR
  #endif

  #ifndef LPTSTR
    typedef       TCHAR*     LPTSTR;
    #define LPTSTR LPTSTR
  #endif

#ifdef __cplusplus
  extern "C" {
#endif
  #include <SystemMgr.h> /*sysTrap enum
                           See also SysTraps.h (Palm OS < v3.5) or CoreTraps.h
                           (Palm OS > v3.5)
                          */
  #include <StringMgr.h>

  /*Formatted I/O                                                            */

  #ifndef _tprintf
    #define _tprintf    printf      //Print formatted output to the standard
                                    //output stream.
  #endif
  #ifndef _ftprintf
    #define _ftprintf   fprintf     //Print formatted data to a stream.
  #endif
  #ifndef _stprintf
    #if !defined (HAS_FLOAT_SUPPORT)
      #if defined (__MWERKS__)
        #include <unix_stdarg.h>
      #else
        #include <stdarg.h>    /*va_list*/
      #endif
      Int16 _stprintf(LPTSTR s, LPCTSTR formatStr, va_list arg) SYS_TRAP(sysTrapStrVPrintF);
      #define _stprintf   _stprintf     //Write formatted data to a string.
                                        //Note: StrVPrintF implements a subset
                                        //of the ANSI C vsprintf call
    #endif
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
    LPTSTR _tcscpy(LPTSTR dst, LPCTSTR src) SYS_TRAP(sysTrapStrCopy);
    #define _tcscpy _tcscpy      //Copy a string.
  #endif
  #ifndef _tcscspn
    #define _tcscspn    strcspn     //Find a substring in a string.
  #endif
  #ifndef _tcslen
    #define _tcslen     strlen      /*Get the length of a string.
                                      Note: Native StrLen() return number of
                                      bytes, not number of characters.
                                     */
  #endif
  #ifndef _tcsncat
    #define _tcsncat    strncat     //Append characters of a string.
  #endif
  #ifndef _tcsncmp
    #define _tcsncmp    strncmp     //Compare characters of two strings.
  #endif
  #ifndef _tcsncpy
    LPTSTR _tcsncpy(LPTSTR dst, LPCTSTR src, Int16 n) SYS_TRAP(sysTrapStrNCopy);
    #define _tcsncpy    _tcsncpy     //Copy characters of one string to another.
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

#ifdef __cplusplus
}
#endif

/* ///////////////////////////////////////////////////////////////////////// */
#else
    #error "Included PalmOS specfic header file."
#endif /*__PALMOS__*/

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*_KTCHARPALM_H_*/
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-11-09 18:46:04  Darko Kolakovic implemented
 *       TsWriteToViewLn
 *  1    Biblioteka1.0         2004-11-09 13:11:07  Darko Kolakovic 
 * $
 *****************************************************************************/
