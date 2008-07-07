/*$Workfile: KDbgMacr.h$: header file
  $Revision: 50$ $Date: 2007-05-31 16:43:23$
  $Author: Darko Kolakovic$

  Dumps values of some compiler-specific predefined macros
  Copyright: CommonSoft Inc.
  Darko Kolakovic April 1988
*/
/* Group=Diagnostic                                                          */

#ifndef _KDBGMACR_H_
    /*$Workfile: KDbgMacr.h$ sentry */
  #define _KDBGMACR_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "KDbgMAns.h" /*Validate ANSI/ISO Standard macro names*/

/* ========================================================================= */
#ifdef GCCx86 /*GNU C Compiler on Intel x86                                  */
  #ifdef VXWORKS
    #warning "Target OS is WindRiver VxWorks."
  #endif
#endif /*GCCx86                                                              */

#ifdef __GNUC__  /*GNU C/C++ Compiler                                        */
  /*GNU-Specific macros ---------------------------------------------------- */
  #ifdef __GNUG__
    /*GNU C compiler defines this when the compilation language is C++       */
    #warning "GNU C++ Compiler"
  #else
    #warning "GNU C Compiler"
  #endif
    /*Preprocessor Directives for Generic-Text Mappings                      */
   #if defined(_UNICODE)
      /*Unicode character (16-bit)
        ISO 10646-1 Universal Multiple Octet Coded Character Set (UCS).
       */
      #warning "Unicode (wide-character) text mapping"
    #endif
    #if !defined (_UNICODE)
      /*ASCII character (8-bit)*/
      #warning "Singlebyte-character (SBCS or ASCII) text mapping"
    #endif

  #ifdef __GNUC_MINOR__
   /*Current version of GNU compiler. Version number is a long integer in form:
     MMMMmmmm where MMMM is major version and mmmm minor version number      */
    const long g__GNUC_VER = __GNUC__<< 4 + __GNUC_MINOR__;
  #endif

  #ifdef __VERSION__
    /*Macro expands to a string which describes the version major, minor
      number of GNU C and bugfix level in the form "M.m.f"                   */
    const char* g___VERSION__ = __VERSION__;
  #endif

  /*Major version number of GNU CC                                         */
  #if __GNUC__ == 1
    #warning  "major ver. 1."
  #endif
  #if __GNUC__ == 2
    #warning "major ver. 2."
  #endif
  #if __GNUC__ > 2
    #warning  "major ver. unknown"
  #endif

  /*Minor version number of GNU CC                                         */
  #if __GNUC_MINOR__ == 1
    #warning  "minor ver. 1."
  #endif
  #if __GNUC_MINOR__ == 2
    #warning "minor ver. 2."
  #endif
  #if __GNUC_MINOR__ == 3
    #warning "minor ver. 3."
  #endif
  #if __GNUC_MINOR__ == 4
    #warning "minor ver. 4."
  #endif
  #if __GNUC_MINOR__ == 5
    #warning "minor ver. 5."
  #endif
  #if __GNUC_MINOR__ == 6
    #warning "minor ver. 6."
  #endif
  #if __GNUC_MINOR__ == 7
    #warning "minor ver. 7."
  #endif
  #if __GNUC_MINOR__ == 8
    #warning "minor ver. 8."
  #endif
  #if __GNUC_MINOR__ > 8
    #warning  "minor ver. unknown"
  #endif

    /*Byte order                                                             */
  #ifdef BIG_ENDIAN
    #warning  "Big Endian byte order"
  #endif
  #ifdef LITTLE_ENDIAN
    #warning  "Little Endian byte order"
  #endif
  #ifdef _BIG_ENDIAN
    #if _BIG_ENDIAN > 0
      #warning  "Big Endian byte order"
    #endif
  #endif
  #ifdef _LITTLE_ENDIAN
    #if _LITTLE_ENDIAN > 0
      #warning  "Little Endian byte order"
    #endif
  #endif

    #if defined(__APPLE__)
      #warning "Target OS is MacOS."
    #endif

    #ifdef __unix__
      #warning "Target OS is Unix."
    #endif
    #ifdef __BSD__
      #warning "Target OS is Berkeley Unix."
    #endif
    #ifdef __BSD_NET2__
      #warning "Target OS is Berkeley Unix."
    #endif
    #ifdef ____386BSD____
      #warning "Target OS is BSD/386 1.1."
    #endif
    #ifdef __FreeBSD__
      #warning "Target OS is FreeBSD Unix."
    #endif
    #ifdef __NetBSD__
      #warning "Target OS is Berkeley Unix."
    #endif

    #ifdef __clipper__
      #warning "Target is Clipper."
    #endif

    #ifdef Lynx
      #warning "Target is Lynx."
    #endif

    #ifdef unix
      #warning "Target OS is Unix."
    #endif
    #ifdef BSD
      #ifndef __INCvxWorksh /*VxWorks redefines BSD macro */
        #warning "Target OS is Berkeley Unix."
      #endif
    #endif

    #ifdef __hpux
      #warning "Target OS is HP Unix."
    #endif
    #ifdef SUN4_SUNOS4
      #warning "Target OS is SunOS 4."
    #endif
    #ifdef SUN4_SOLARIS2
      #warning "Target OS is Solaris 2."
    #endif
    #ifdef PARISC_HPUX9
      #warning "Target OS is HP Unix 9."
    #endif
    #ifdef PARISC_HPUX10
      #warning "Target OS is HP Unix 10."
    #endif
    #ifdef RS6000_AIX4
      #warning "Target OS is AIX 4."
    #endif
    #ifdef iris
      #warning "Target OS is iris."
    #endif
    #ifdef magnum
      #warning "Target OS is magnum."
    #endif
    #ifdef decmips
      #warning "Target OS is DEC Mips."
    #endif
    #ifdef _WIN32
      #warning "Target OS is Windows 32b."
    #endif
    #ifdef WIN32
      #warning "Target OS is Windows 32b."
    #endif
    #ifdef _WIN64
      #warning "Target OS is Windows 64b."
    #endif
    #ifdef VMS
      #warning "Target OS is VMS."
    #endif
    #ifdef __NeXT__
      #warning "Target OS is NeXTStep."
    #endif

    #ifdef VXWORKS_VERSION
      #warning "Target OS is WindRiver VxWorks (ver)."
      /*Note: version.h - VxWorks version information have to be included    */
      const char* g_VXWORKS_VERSION = VXWORKS_VERSION;
    #endif

    #ifdef VXWORKS
      #warning "Target OS is WindRiver VxWorks."
    #endif

    #ifdef __INCvxWorksh
      #warning "Target OS is WindRiver VxWorks (vxWorks.h included)."
      #ifdef BSD
        #if (BSD == 44)
          #warning BSD 4.4 like OS
        #endif
      #endif
      /*Note: host.h defines VxWorks host system                             */
      #ifdef HOST_TYPE
      /*VxWorks build host OS                                                */
        const char* g_HOST_TYPE = HOST_TYPE;
        #warning  "HOST_TYPE is defined."

        #if defined SUN4_SUNOS4
          #warning  "Host OS is sun4-sunos4"
        #elif defined SUN4_SOLARIS2
          #warning  "Host OS is sun4-solaris2"
        #elif defined PARISC_HPUX9
          #warning  "Host OS is parisc-hpux9"
        #elif defined PARISC_HPUX10
          #warning  "Host OS is parisc-hpux10"
        #elif defined decmips
          #warning  "Host OS is decmips"
        #elif defined iris
          #warning  "Host OS is iris"
        #elif defined magnum
          #warning  "Host OS is magnum"
        #elif defined RS6000_AIX4
          #warning  "Host OS is rs6000-aix4"
        #elif (defined(_M_IX86) && defined(_WIN32))
          #warning  "Host OS is x86-win32"
        #elif (defined(_M_X64) && defined(_WIN64))
          #warning  "Host OS is I64-win64"
        #endif
      #endif /*HOST_TYPE                                                     */
    #endif /*__INCvxWorksh                                                   */

    /*Current version of CPU                                                 */
    #ifdef mc68000
      #warning "CPU: Motorola 68000, 68010 or 68020."
    #endif
    #ifdef m68k
      #warning "CPU: Motorola 68000, 68010 or 68020."
    #endif
    #ifdef M68020
      #warning "CPU: Motorola 68020."
    #endif
    #if defined (__m88k__)
      #warning "CPU: Motorola 88000 CPU family."
    #endif

    #ifdef _AM29K
      #warning "CPU: AMD 29000 CPU family."
    #endif
    #ifdef _AM29000
      #warning "CPU: AMD 29000 CPU family."
    #endif
    #ifdef ns32000
      #warning "CPU: National Semiconductor 32000 CPU family."
    #endif
    #ifdef _M_IX86
      #warning "CPU: Intel x86 CPU family."
    #endif
    #ifdef _M_X64
      #warning "CPU: 64b CPU family."
    #endif
    #ifdef _M_IA64
      #warning "CPU: Intel Itanium CPU family."
    #endif
    #if defined (__i386__)
      #warning "CPU: Intel 80386."
    #endif
    #if defined (__i860__)
      #warning "CPU: Intel 80860."
    #endif
    #if defined (__i960__)
      #warning "CPU: Intel 80960."
    #endif

    #if defined(__ia64__)
      #warning "CPU: Intel 64b."
    #endif

    #if (defined(__arm__) || defined(__ARMEL__) || defined(arm))
      #warning "CPU: ARM Risc CPU family."
    #endif

    #ifdef __ns32000__
      #warning "CPU: National Semiconductor 32000 CPU family."
    #endif

    #ifdef __mn10300__
      #warning "CPU: Matsushita Electric (Panasonic) 10300 32b."
    #endif

    #ifdef __mn10200__
      #warning "CPU: Matsushita Electric (Panasonic) 10200 RISC."
    #endif

    #if defined (__H8300__) || defined (__H8300H__) || defined (__H8300S__)
      #warning "CPU: Hitachi H8/300[HS] CPU family."
    #endif

    #ifdef __v850__
      #warning "CPU: NEC V850 RISC."
    #endif

    #if defined (__z8000__)
      #warning "CPU: Z8000 16b."
    #endif

    #if defined (_TMS320C4x) || defined (_TMS320C3x)
      #warning "CPU: Texas Instruments TMS32xxx CPU family."
    #endif

    #ifdef __hppa__
      #warning "CPU: HP PA-RISC 7xxx CPU family."
    #endif

    #ifdef __M32R__
      #warning "CPU: Mitsubishi M32R RISC CPU family."
    #endif

    #if (defined(__ppc__) || defined(__PPC__) || defined(ppc))
      #warning "Compiling for PowerPC platform."
    #endif

    #ifdef __mips64
      #warning "Compiling for MIPS 64 platform."
    #endif
    #ifdef __mips__
      #warning "Compiling for MIPS platform."
    #endif

    #ifdef __alpha__
      #warning "Compiling for DEC APLHA platform."
    #endif

    #if (defined(__sparc__) || defined (__sparc_v9__) || defined(__sparcv9))
      #warning "Compiling for Scalable Processor ARChitecture platform."
    #endif

    #ifdef __sh__
      #warning "Compiling for Hitachi SH-3 and SH-4 platform."
    #endif

    #if (defined(__vax__) || defined(vax))
      #warning "Compiling for Vax platform."
    #endif

    #if defined (__arch64__)
      #warning "Compiling for CygWin/Intel 64b platform."
    #endif

    #ifdef __arc__
      #warning "Compiling for ARC target."
    #endif

    /*Current version of manufacturer of the system                          */
    #ifdef sun
      #warning "Manufacturer: Sun."
    #endif
    #ifdef pyr
      #warning "Manufacturer: Pyramid."
    #endif
    #ifdef sequent
      #warning "Manufacturer: Sequent."
    #endif

 // #endif /*~__STRICT_ANSI__                                                  */

/* ========================================================================= */
#endif /*__GNUC__                                                            */




/* ========================================================================= */
#ifdef MSC        /*Microsoft C - Windows 3.0 Compiler             */
  #pragma message ("Microsoft C 16b compiler")

  #ifdef VXWORKS
    #pragma message ("Target OS is WindRiver VxWorks.")
  #endif

#endif

#ifdef MSVC       /*Microsoft Visual C - 4.x+ Compiler               */
  #pragma message ("Microsoft Visual C/C++ 4.x+ compiler")

#endif

#ifdef _MSC_VER /*Microsoft Visual C/C++ Compiler                            */
  /*Microsoft-Specific macros ---------------------------------------------- */
  #ifdef _MSC_VER
    #ifdef _DEBUG
       #pragma message ("Debug version")
    #else
      #pragma message ("Release version")
    #endif
    /*Preprocessor Directives for Generic-Text Mappings                      */
    #if defined UNICODE || defined _UNICODE
      /*Unicode character (16-bit)
        ISO 10646-1 Universal Multiple Octet Coded Character Set (UCS).
       */
      #pragma message ("Unicode (wide-character) text mapping")
    #endif
    #if defined _MBCS && !defined _UNICODE
      #pragma message ("Multibyte-character text mapping")
    #endif
    #if !defined _MBCS && !defined _UNICODE
      /*ASCII character (8-bit)*/
      #pragma message ("Singlebyte-character (SBCS or ASCII) text mapping")
    #endif

    #if _MSC_VER >= 1300
      #pragma message ("Microsoft Visual C++.NET compiler")
    #else
      #if _MSC_VER >= 800
        #pragma message ("Microsoft Visual C/C++ compiler")
      #else
        #if _MSC_VER > 600
         #pragma message ("Microsoft C/C++ compiler")
        #else
          #pragma message ("Microsoft C compiler")
        #endif
      #endif
    #endif

   /*Current version of Microsoft compiler.
     The _MSC_VER macro will have one of the following values depending upon
     the particular Microsoft compiler:

        Compiler                             _MSC_VER value

        C Compiler version 6.0                     600
        C/C++ compiler version 7.0                 700
        Visual C++, Windows, version 1.0           800
        Visual C++, 32-bit, version 1.0            800
        Visual C++, Windows, version 1.5           850
        Visual C++, Windows, version 2.0           900
        Visual C++, 32-bit, version 2.x            900
        Visual C++, 32-bit, version 4.0           1000
        Visual C++, 32-bit, version 4.2           1020
        Visual C++, 32-bit, version 5.0           1100
        Visual C++, 32-bit, version 6.0           1200
        Visual C++ .Net 2002, 32-bit, version 7.0 1300
        Visual C++ .Net 2003, 32-bit, version 7.1 1310
        Visual C/C++ 2005, version 8.0            1400
     See also: Q65472
    */
    const int g__MSC_VER = _MSC_VER;
    #if _MSC_VER < 600
      #pragma message ("  ver. unknown")
    #endif
    #if _MSC_VER == 600
      #pragma message ("  ver. 6.0")
    #endif
    #if _MSC_VER == 700
      #pragma message ("  ver. 7.0")
    #endif
    #if _MSC_VER == 800
      #pragma message ("  ver. 1.0")
    #endif
    #if _MSC_VER == 850
      #pragma message ("  ver. 1.5")
    #endif
    #if _MSC_VER == 900
      #pragma message ("  ver. 2.0")
    #endif
    #if _MSC_VER == 1000
      #pragma message ("  ver. 4.0")
    #endif
    #if _MSC_VER == 1020
      #pragma message ("  ver. 4.2")
    #endif
    #if _MSC_VER == 1100
      #pragma message ("  ver. 5.0")
    #endif
    #if _MSC_VER == 1200
      #pragma message ("  ver. 6.0")
    #endif
    #if _MSC_VER == 1210
      #pragma message ("  ver. 6.1")
    #endif
    #if _MSC_VER == 1300
      #pragma message ("  2002 ver. 7.0")
    #endif
    #if _MSC_VER == 1310
      #pragma message ("  2003 ver. 7.1")
    #endif
    #if _MSC_VER == 1400
      #pragma message ("  2005 ver. 8.0")
    #endif
    #if _MSC_VER > 1400
      #pragma message ("  ver. unknown")
    #endif
  #endif

  #ifdef _AFX
    #pragma message ("Included Microsoft Application Framework Classes afxver_.h (AFX/MFC).")
  #endif
  #ifdef _MFC_VER
    #pragma message ("Included Microsoft Fundation Class (MFC) library.")
     /*Current version of Microsoft Fundation Class (MFC) library.
      */
    const int g__MFC_VER = _MFC_VER;
    #if _MFC_VER < 300
      #pragma message ("  ver. unknown")
    #endif
    #if _MFC_VER == 0x0320
      #pragma message ("  ver. 3.2")
    #endif
    #if _MFC_VER == 0x0400
      #pragma message ("  ver. 4.0")
    #endif
    #if _MFC_VER == 0x0410
      #pragma message ("  ver. 4.10")
    #endif
    #if _MFC_VER == 0x420
      #pragma message ("  ver. 4.20")
    #endif
    #if _MFC_VER == 0x0421
      #pragma message ("  ver. 4.21")
    #endif
    #if _MFC_VER == 0x0600
      #pragma message ("  ver. 6.00")
    #endif
    #if _MFC_VER == 0x0601
      #pragma message ("  ver. 6.01")
    #endif
    #if _MFC_VER == 0x0700
      #pragma message ("  ver. 7.00")
    #endif
    #if _MFC_VER == 0x0710
      #pragma message ("  ver. 7.10")
    #endif
    #if _MFC_VER > 0x0710
      #pragma message ("  ver. unknown")
    #endif
  #endif

  #ifdef _AFXDLL
    #ifdef __cplusplus
      #pragma message ("Use MFC in a Shared DLL.")
    #else
      #pragma message (__FILE__ " : warning: Specified use of MFC in a C code.")
    #endif
  #endif

  #include "KDbgMacrAtl.h" /*List Active Template Library macros*/

  #ifdef _MSC_EXTENSIONS
    #pragma message ("Enabled compiler extensions.")
  #endif
  #ifdef _CPPUNWIND
    #pragma message ("Enabled Exception Handling.")
  #endif
  #ifdef _CPPRTTI
    #pragma message ("Enabled Run-Time Type Information.")
  #endif
  #ifdef _MT
    /*Defined when /MD or /MDd (Multithreaded DLL) or /MT
     or /MTd (Multithreaded) is specified.*/
    #pragma message ("Enabled Multithreading.")
  #else
    #ifndef _STH
      #define _STH 1998
    #endif
    #pragma message ("Single-threaded application.")
  #endif
  #ifdef _DLL
    #pragma message ("Multithread DLL is specified.")
  #endif
  #ifdef _M_ALPHA
    #pragma message ("Compiling for for DEC ALPHA platform.")
  #endif
  #ifdef _M_IX86
    #pragma message ("Compiling for for Intel x86 platform.")
    /*Current version of Intel x86 processor option specified
     */
    const int g__M_IX86 = _M_IX86;
    #if _M_IX86 < 300
      #pragma message ("CPU: unknown")
    #endif
    #if _M_IX86 == 300
      #pragma message ("CPU: 80386")
    #endif
    #if _M_IX86 == 400
      #pragma message ("CPU: 80486")
    #endif
    #if _M_IX86 == 500
      #pragma message ("CPU: Pentium")
    #endif
    #if _M_IX86 == 600
      #pragma message ("CPU: Pentium Pro")
    #endif
    #if _M_IX86 > 600
      #pragma message ("CPU: unknown")
    #endif
  #endif /*_M_IX86*/
  #ifdef M_I8086
    #pragma message ("Compiling for for Intel x86 platform.")
    #pragma message ("CPU: 8088 or 8086")
    const int g__M_IX86 = 100;
  #endif
  #ifdef _M_I8086
    #pragma message ("Compiling for for Intel x86 platform.")
    #pragma message ("CPU: 8088 or 8086")
    const int g__M_IX86 = 100;
  #endif
  #ifdef M_I286
    #pragma message ("Compiling for for Intel x86 platform.")
    #pragma message ("CPU: 80286")
    const int g__M_IX86 = 200;
  #endif
  #ifdef _M_IA64
    #pragma message ("Compiling for for Intel Itanium platform.")
  #endif
  #ifdef _M_X64
    #pragma message ("Compiling for for 64-bit platform.")
  #endif
  #ifdef _M_MPPC
    #pragma message ("Compiling for for Power Macintosh platform.")
  #endif
  #ifdef _M_MRX000
    #pragma message ("Compiling for for MIPS platform.")
  #endif
  #ifdef _M_PPC
    #pragma message ("Compiling for for PowerPC platform.")
  #endif
  #ifdef _WIN64
    #pragma message ("Target OS is Win64.")
  #endif
  #ifdef _WIN32
    #pragma message ("Target OS is Win32.")
  #endif
  #ifdef WIN16
    #pragma message ("Target OS is Win16.")
  #endif
  #ifdef _WINDOWS
    #pragma message ("Target OS is Windows.")
  #endif
  #ifdef MSDOS
    #pragma message ("Target OS is MS-DOS.")
  #endif
  #ifdef _MSDOS
    #pragma message ("Target OS is MS-DOS.")
  #endif
  #ifdef DOS
    #pragma message ("Target OS is DOS.")
  #endif
  #ifdef _DOS
    #pragma message ("Target OS is DOS.")
  #endif
  #ifdef DOS16
    #pragma message ("Target OS is DOS.")
  #endif
  #ifdef VXWORKS
    #pragma message ("Target OS is WindRiver VxWorks.")
  #endif
  #ifdef M_I86TM
    #pragma message ("Tiny model.")
  #endif
  #ifdef _M_I86TM
    #pragma message ("Tiny model.")
  #endif
  #ifdef M_I86SM
    #pragma message ("Small model.")
  #endif
  #ifdef _M_I86SM
    #pragma message ("Small model.")
  #endif
  #ifdef M_I86CM
    #pragma message ("Compact model.")
  #endif
  #ifdef _M_I86CM
    #pragma message ("Compact model.")
  #endif
  #ifdef M_I86MM
    #pragma message ("Medium model.")
  #endif
  #ifdef _M_I86MM
    #pragma message ("Medium model.")
  #endif
  #ifdef M_I86LM
    #pragma message ("Large model.")
  #endif
  #ifdef _M_I86LM
    #pragma message ("Large model.")
  #endif
  #ifdef M_I86HM
    #pragma message ("Huge model.")
  #endif
  #ifdef _M_I86HM
    #pragma message ("Huge model.")
  #endif
  #ifdef _WINNT
    #pragma message ("Target OS is WinNT.")
  #endif
  #ifdef _WIN95
    #pragma message ("Target OS is Win95.")
  #endif
  #ifdef _MAC
    #pragma message ("Target OS is MacOS.")
  #endif
  #ifdef MAC
    #pragma message ("Target OS is MacOS.")
  #endif

  #ifdef WINVER
    /*Windows Target Version Macros

     +---------------------+---------------------------------+
     |   Macros to Define  |   Minimum System Required       |
     +---------------------+---------------------------------+
     | WINVER=0x030A       |Windows 3.1                      |
     |                     |                                 |
     | WINVER=0x0400       |Windows 95 and Windows NT 4.0    |
     |                     |                                 |
     |_WIN32_WINDOWS=0x0410|Windows 98 and Windows NT 4.0    |
     |WINVER=0x0400        |                                 |
     |                     |                                 |
     |_WIN32_WINNT=0x0400  |Windows NT 4.0                   |
     |WINVER=0x0400        |                                 |
     |                     |                                 |
     |_WIN32_WINDOWS=0x0410|Windows 98                       |
     |                     |                                 |
     |_WIN32_WINDOWS=0x0490|Windows Millenium                |
     |                     |                                 |
     |WINVER=0x040A        |Windows 98 4.10                  |
     |                     |                                 |
     |WINVER=0x045A        |Windows Millenium 4.90           |
     |                     |                                 |
     |WINVER=0x0500        |Windows 98 and Windows 2000      |
     |                     |                                 |
     |_WIN32_WINNT=0x0500  |Windows 2000                     |
     |WINVER=0x0500        |                                 |
     |                     |                                 |
     |_WIN32_WINNT=0x0501  |Windows XP                       |
     |WINVER=0x0501        |                                 |
     |                     |                                 |
     |_WIN32_WINNT=0x0502  |Windows Server 2003 family       |
     |                     |                                 |
     |WINVER=0x0600        |Windows Vista                    |
     |                     |                                 |
     |_WIN64               |                                 |
     +---------------------+---------------------------------+
     |_WIN32_IE=0x0300     |Internet Explorer 3.0, 3.01, 3.02|
     |                     |                                 |
     |_WIN32_IE=0x0400     |Internet Explorer 4.0            |
     |                     |                                 |
     |_WIN32_IE=0x0401     |Internet Explorer 4.01           |
     |                     |                                 |
     |_WIN32_IE=0x0500     |Internet Explorer 5.0, 5.0a, 5.0b|
     |                     |                                 |
     |_WIN32_IE=0x0501     |Internet Explorer 5.01           |
     |                     |                                 |
     |_WIN32_IE=0x0532     |Internet Explorer 5.5            |
     |                     |                                 |
     |_WIN32_IE=0x0600     |Internet Explorer 6.00           |
     |                     |                                 |
     |_WIN32_IE=0x0700     |Internet Explorer 7.00           |
     +---------------------+---------------------------------+

    Note: Setting WINVER to 0x0500 implies _WIN32_IE=0x0400


     */
    const WORD g__WINVER = WINVER;

    #if WINVER == 0x0300
      #pragma message ("Target OS is MS Windows 3.0.")
    #elif WINVER == 0x030a
      #pragma message ("Target OS is MS Windows 3.1.")
    #elif WINVER == 0x0400
      #pragma message ("Target OS is MS Windows NT 4.0.")
    #elif WINVER == 0x040A
      #pragma message ("Target OS is MS Windows 98 4.10.")
    #elif WINVER == 0x045A
      #pragma message ("Target OS is MS Windows Millenium 4.90.")
    #elif WINVER == 0x0500
      #pragma message ("Target OS is MS Windows 2000 or 98.")
    #elif WINVER == 0x0501
      #pragma message ("Target OS is MS Windows XP.")
    #elif WINVER == 0x0502
      #pragma message ("Target OS is MS Windows 2003 5.2.")
    #elif WINVER == 0x0600
      #pragma message ("Target OS is MS Windows Vista.")
    #else
      #pragma message ("Target OS is MS Windows ?.?.")
    #endif
  #endif

  #ifdef _WIN32_WINDOWS
    #if _WIN32_WINDOWS == 0x0410
     #pragma message ("Target OS is MS Windows 98 (9x).")
    #elif _WIN32_WINDOWS == 0x0490
      #pragma message ("Target OS is MS Windows Me (9x).")
    #else
      #pragma message ("Target OS is MS Windows 9? (9x).")
    #endif
  #else
    #if WINVER == 0x0400
      /*Windows 95 and Windows NT 4.0 */
      #pragma message ("Target OS is MS Windows 95.")
    #endif
    #if WINVER == 0x0500
      /*Windows 98 and Windows 2000 */
      #pragma message ("Target OS is MS Windows 98.")
    #endif
  #endif

  #ifdef _WIN32_WINNT
    #if _WIN32_WINNT == 0x0400
      #pragma message ("Target OS is MS Windows NT 4.0 (WINNT).")
    #elif _WIN32_WINNT == 0x0500
      #pragma message ("Target OS is MS Windows 2000 (WINNT).")
    #elif _WIN32_WINNT == 0x0501
      #pragma message ("Target OS is MS Windows XP (WINNT).")
    #elif _WIN32_WINNT == 0x0502
      #pragma message ("Target OS is MS Windows Server 2003 family.")
    #else
      #pragma message ("Target OS is MS Windows ?? (WINNT).")
    #endif
  #endif

  #ifdef _CONSOLE
    #pragma message ("Target is an console application.")
  #endif
  #ifdef _MANAGED
    #pragma message ("Target is a managed Windows application.")
  #endif

    /* 16-bit OS mode; see stdlib.h 1985-1992, Microsoft Corporation*/
  #if _OS_MODE == 0 /*  _DOS_MODE */
    #ifdef _WIN32
      #pragma message ("Target OS mode is DOS (Win32) console.")
    #else
      #pragma message ("Target OS mode is DOS.")
    #endif
  #endif
  #if _OS_MODE == 1 /* _OS2_MODE */
    #pragma message ("Target OS mode is OS/2.")
  #endif
  #if _OS_MODE == 2 /*  _WIN_MODE */
    #pragma message ("Target OS mode is Windows.")
  #endif

    /* x86 CPU mode; see stdlib.h 1985-1992, Microsoft Corporation*/
  #if _CPU_MODE == 0  /* _REAL_MODE */
    #pragma message ("Target CPU mode is real mode.")
  #endif
  #if _CPU_MODE == 1 /* _PROT_MODE */
    #pragma message ("Target CPU mode is protect mode.")
  #endif

  #ifdef _WIN32_IE
    #pragma message ("Supported Internet Explorer:")
    /*Supported version of Microsoft Internet Explorer.

        Browser                             _WIN32_IE value
        Internet Explorer 3.0, 3.01, 3.02       0x0300
        Internet Explorer 4.0                   0x0400
        Internet Explorer 5.0, 5.0a, 5.0b       0x0500
        Internet Explorer 5.01, 5.5             0x0501
        Internet Explorer 6.0                   0x0600
        Internet Explorer 7.0                   0x0700

        _WIN32_IE value    Description
         0x0200            The application will be compatible with Comctl32.dll
                           and Shell32.dll version 4.00 and later.
                           The application will not be able to implement
                           features that were added after version 4.00 of
                           Comctl32.dll.
         0x0300            The application will be compatible with Comctl32.dll
                           and Shell32.dll version 4.70 and later. The application
                           will not be able to implement features that were added
                           after version 4.70 of Comctl32.dll.
         0x0400            The application will be compatible with Comctl32.dll
                           and Shell32.dll version 4.71 and later. The application
                           will not be able to implement features that were added
                           after version 4.71 of Comctl32.dll.
         0x0401            The application will be compatible with Comctl32.dll
                           and Shell32.dll version 4.72 and later.
                           The application will not be able to implement features
                           that were added after version 4.72 of Comctl32.dll.
         0x0500            The application will be compatible with Comctl32.dll
                           version 5.80 and later, and Shell32.dll and Shlwapi.dll
                           version 5.0 and later. The application will not be able
                           to implement features that were added after version 5.80
                           of Comctl32.dll or version 5.0 of Shell32.dll and Shlwapi.dll.
         0x0501            The application will be compatible with Comctl32.dll
                           version 5.81 and later and Shell32.dll and Shlwapi.dll
                           version 5.0 and later. The application will not be able to
                           implement features that were added after version 5.81 of
                           Comctl32.dll or version 5.0 of Shell32.dll and Shlwapi.dll.
     */
    const int g__WIN32_IE = _WIN32_IE;
    #if _WIN32_IE >= 0x0700
      #pragma message ("  7.00 and later.")
    #else
      #if _WIN32_IE >= 0x0600
        #pragma message ("  6.00 and later.")
      #else
        #if _WIN32_IE >= 0x0500
          #pragma message ("  5.00 and later.")
        #else
          #if _WIN32_IE >= 0x0400
              #pragma message ("  4.0 and later.")
          #else
            #if _WIN32_IE >= 0x0300
              #pragma message ("  3.0 and later.")
             #else
               #if _WIN32_IE >= 0x0200
                 #pragma message ("  2.0 and later.")
               #else
                 #pragma message ("  unknown.")
              #endif
            #endif
          #endif
        #endif
      #endif
    #endif
  #endif /*_WIN32_IE*/
/* ========================================================================= */
#endif /*_MSC_VER                                                            */

/* ========================================================================= */
#ifdef _MSC_VER    /*Microsoft eMbedded Visual C++ Compiler TODO:             */
  #if (_MSC_VER == 1200)
    #pragma message ("Microsoft eMbedded Visual C++ compiler 4.00")
  #else
    #pragma message ("Microsoft eMbedded Visual C++ compiler ??")
  #endif

  #if defined (_WIN32_WCE) || defined (UNDER_CE)
    #ifdef _WIN32_WCE
    /*Microsoft eMbedded Visual C++ Compiler defines OS version as
      variable $(CEVersion) value:
         \D _WIN32_WCE=$(CEVersion), \D  UNDER_CE=$(CEVersion), ...
     */
      const unsigned int g__WIN32_WCE = _WIN32_WCE;
    #else
      const unsigned int g__WIN32_WCE = UNDER_CE;
    #endif //_WIN32_WCE

    #if (_WIN32_WCE == 201) || (UNDER_CE == 201) /*Windows CE 2.01*/
      #pragma message ("Target OS is MS Windows CE 2.01.")
    #elif (_WIN32_WCE == 211) || (UNDER_CE == 211) /*Windows CE 2.11*/
      #pragma message ("Target OS is MS Windows CE 2.11.")
    #elif (_WIN32_WCE == 300) || (UNDER_CE == 300) /* Windows CE 3.0*/
      #pragma message ("Target OS is MS Windows CE 3.0.")
    #elif (_WIN32_WCE == 400) || (UNDER_CE == 400) /*Windows CE 4.0*/
      #pragma message ("Target OS is MS Windows CE 4.0.")
    #elif (_WIN32_WCE == 410) || (UNDER_CE == 410) /*Windows CE 4.10*/
      #pragma message ("Target OS is MS Windows CE 4.10.")
    #elif (_WIN32_WCE == 420) || (UNDER_CE == 420) /*Windows CE 4.20*/
      #pragma message ("Target OS is MS Windows CE 4.20.")
    #else
      #pragma message ("Target OS is MS Windows CE ?.??.")
    #endif

  #endif /*_WIN32_WCE*/

    /*Microsoft eMbedded Visual C++ Compiler variable $(CePlatform) values:

        Platform                CePlatform value
        H/PC 2000               WIN32_PLATFORM_HPC2000
        H/PC Pro 2.11           WIN32_PLATFORM_HPCPRO
        Pocket PC               WIN32_PLATFORM_PSPC
        Pocket PC 2002          WIN32_PLATFORM_PSPC=310
        Smartphone 2002         WIN32_PLATFORM_WFSP=100
     */
  #ifdef WIN32_PLATFORM_HPC2000 //H/PC 2000 (Galileo)
    #pragma message ("Compiling for Handheld PC 2000 platform.")
  #endif

  #ifdef WIN32_PLATFORM_HPCPRO /*H/PC Professional*/
    #if (WIN32_PLATFORM_HPCPRO == 211)
      #pragma message ("Compiling for Handheld PC Professional 2.11 platform.")
    #elif (WIN32_PLATFORM_HPCPRO == 300) /*H/PC Professional Version 3.0 (Jupiter)*/
      #pragma message ("Compiling for Handheld PC Professional 3.0 platform.")
    #else
      #pragma message ("Compiling for Handheld PC Professional platform.")
    #endif
  #endif

  #ifdef WIN32_PLATFORM_PSPC /*Pocket PC*/
    #if (WIN32_PLATFORM_PSPC == 1) /*Pocket PC 2000*/
      #pragma message ("Compiling for Pocket PC 2000 platform.")
    #elif (WIN32_PLATFORM_PSPC == 310) /*Pocket PC 2002*/
      #pragma message ("Compiling for Pocket PC 2002 platform.")
    #else
      #pragma message ("Compiling for Pocket PC platform.")
    #endif
  #endif

  #ifdef WIN32_PLATFORM_WFSP /*Smartphone*/
    #if (WIN32_PLATFORM_WFSP == 100) /*Smartphone 2002*/
      #pragma message ("Compiling for Smartphone 2002 platform.")
    #else
      #pragma message ("Compiling for Smartphone platform.")
    #endif
  #endif

  #ifdef _WIN32_WCE_EMULATION /*PC emulator*/
    #pragma message ("Compiling for PC (emulator) platform.")
  #endif

  #ifdef _WIN32_WCE_PSPC /*Palm Size PC*/
    #if (_WIN32_WCE == 211) // for Palm-size PC 2.11 (Wyvern)
      #pragma message ("Compiling for Palm-size PC 2.11 platform.")
    #elif (_WIN32_WCE == 201) // for Palm-size PC 2.01 (Gryphon)
      #pragma message ("Compiling for Palm-size PC 2.01 platform.")
    #else
      #pragma message ("Compiling for Palm Size PC platform.")
    #endif
  #endif

  #if defined (_WIN32_WCE) || defined (UNDER_CE)
    #if defined(ARM) || defined (_ARM_)
      #pragma message ("CPU: ARM Risc CPU family")
    #endif
    #if defined(THUMB) || defined (_THUMB_) || defined ( ARMV4T)
      #pragma message ("CPU: ARM V4T Risc CPU")
    #endif
    #if defined (MIPS)
      #pragma message ("CPU: MIPS")
    #endif
    #if defined (SH3)
      #pragma message ("CPU: Hitachi SH3")
    #endif
    #if defined (SH4)
      #pragma message ("CPU: Hitachi SH4")
    #endif
    #if defined (x86) || defined (_i386_) || defined (i_386_) || defined (_X86_)
      #pragma message ("CPU: Intel x86 (emulator)")
    #endif
  #endif
/* ========================================================================= */
#endif

#if defined(__BORLANDC__) || defined(__TURBOC__) /*Borland C++ Compiler      */
/* ========================================================================= */
  #pragma message ("Borland C++ Compiler")

  #ifdef __BORLANDC__
    #if __BORLANDC__ == 0x500
      #pragma message ("ver. 5.00")
    #endif
  #endif
  #ifdef VXWORKS
    #pragma message ("Target OS is WindRiver VxWorks.")
  #endif
/* ========================================================================= */
#endif /*__BORLANDC__                                                        */




#ifdef __WATCOMC__ /*Watcom 32b Compiler                                     */
/* ========================================================================= */
  #pragma message ("Watcom 32b Compiler")


  /*The value of the macro depends on the version number of the compiler.
    The value is 100 times the version number (version 8.5 yields 850, version
    9.0 yields 900, etc.).                                                   */
  #if __WATCOMC__  == 1050
    #pragma message ("ver. 10.5")
  #endif

  #ifdef VXWORKS
    #pragma message ("Target OS is WindRiver VxWorks.")
  #endif

  /*The WATCOM C/C++ compilers support both 16-bit and 32-bit application development.  The following macros are defined for 16-bit and 32-bit target systems.


M_I86 WATCOM C/C++ predefines the macro M_I86 to identify the target as a 16-bit Intel 80x86 compatible environment (defined by the WATCOM C/C++16 compilers).
M_I386 WATCOM C/C++ predefines the macro M_I386 to identify the target as a 32-bit Intel 386 compatible environment (defined by the WATCOM C/C++32 compilers).
__386__ WATCOM C/C++ predefines the macro __386__ to identify the target as a 32-bit Intel 386 compatible environment (defined by the WATCOM C/C++32 compilers).

The WATCOM C/C++ compilers support application development for a variety of operating systems.  The following macros are defined for particular target operating systems.
__DOS__ WATCOM C/C++ predefines the macro __DOS__ to identify the target operating system as MS/DOS (including DOS Extenders).
MSDOS WATCOM C/C++ predefines the macro MSDOS to identify the target operating system as MS/DOS (including DOS Extenders).
__OS2__ WATCOM C/C++ predefines the macro __OS2__ to identify the target operating system as OS/2 (1.x or 2.x).
__QNX__ WATCOM C/C++ predefines the macro __QNX__ to identify the target operating system as QNX.
__NETWARE_386__ WATCOM C/C++ predefines the macro __NETWARE_386__ to identify the target operating system as Novell NetWare 386.
__NT__ WATCOM C/C++ predefines the macro __NT__ to identify the target operating system as NT.
__WINDOWS__ WATCOM C/C++ predefines the macro __WINDOWS__ to identify the target operating system as Microsoft Windows.
(16-bit only) This macro is defined when the "zw", "zW", "zWs", or "bt=windows" option is specified.
(32-bit only) This macro is defined when the "zw" or "bt=windows" option is specified.
__WINDOWS_386__ WATCOM C/C++ predefines the macro __WINDOWS_386__ to identify the target operating system as 32-bit Microsoft Windows.
This macro is defined when the "zw" or "bt=windows" option is specified and you are using a 32-bit compiler.

The following macros indicate which compiler is compiling the C/C++ source code.
__cplusplus WATCOM C++ predefines the macro __cplusplus to identify the compiler as a C++ compiler.
__WATCOMC__ WATCOM C/C++ predefines the macro __WATCOMC__ to identify the compiler as one of the WATCOM C/C++ compilers.
The value of the macro depends on the version number of the compiler.  The value is 100 times the version number (version 8.5 yields 850, version 9.0 yields 900, etc.).

The following macros are defined under the conditions described.
__FPI__ WATCOM C/C++ predefines the macro __FPI__ when the "fpi" or "fpi87" option is used.
__CHAR_SIGNED__ WATCOM C/C++ predefines the macro __CHAR_SIGNED__ when the "j" option is used.
__CHEAP_WINDOWS__ (16-bit only) WATCOM C/C++ predefines the macro __CHEAP_WINDOWS__ when the "zW" option is used.
__INLINE_FUNCTIONS__ WATCOM C/C++ predefines the macro __INLINE_FUNCTIONS__ when the "oi" option is used.
NO_EXT_KEYS WATCOM C/C++ predefines the macro NO_EXT_KEYS when the "za" option is used.
__FLAT__ (32-bit only) WATCOM C/C++ predefines the macro __FLAT__ when the "mf" option is used.
M_I86SM, __SMALL__ WATCOM C/C++ predefines the macros M_I86SM and __SMALL__ when the "ms" option is used.
M_I86MM, __MEDIUM__ WATCOM C/C++ predefines the macros M_I86MM and __MEDIUM__ when the "mm" option is used.
M_I86CM, __COMPACT__ WATCOM C/C++ predefines the macros M_I86CM and __COMPACT__ when the "mc" option is used.
M_I86LM, __LARGE__ WATCOM C/C++ predefines the macros M_I86LM and __LARGE__ when the "ml" option is used.
M_I86HM, __HUGE__ (16-bit only) WATCOM C/C++ predefines the macros M_I86HM and __HUGE__ when the "mh" option is used.
*/
/* ========================================================================= */
#endif /*__WATCOMC__                                                         */



/* IBM C/C++ Compiler                                                        */
/* ========================================================================= */
#if defined(__xlC__)
  #pragma message ("IBM C Compiler")

/*IBM compilers are actually two products: the C product, and the C++ product.
  The C++ compiler is always packaged with the latest version of the C compiler.
  Version numbers do not always match:
     C++ compiler           C compiler
       C Set 3.1                3.0
     C++ 3.6.6                4.3
  Visual Age C++ 4.0          n/a
  Visual Age C++ 5.0          5.0

   Note:
   __xlC__    is the version of the C compiler in hexadecimal notation
              - it's only an approximation of the C++ compiler version
  */
  #if __xlC__ == 0x300
    #pragma message ("ver. 3.0")
  #endif
  #if __xlC__ == 0x400
    #pragma message ("ver. 4.0")
  #endif
  #if __xlC__ == 0x430
    #pragma message ("ver. 4.3")
  #endif
  #if __xlC__ == 0x500
    #pragma message ("ver. 5.0")
  #endif
#endif /*__xlC__                                                             */

/*Note:   __IBMCPP__ is the version of the C++ compiler in decimal notation
                     and it is not defined on older compilers like C Set 3.1
 */
#if defined(__IBMCPP__)/* IBM C++ Compiler                                   */
  #pragma comment ("IBM C++ Compiler")


/*
IBM Integrated Language Environment (ILE) C/C++ for iSeries Predefined Macros

The ILE C/C++ compiler provides the predefined macros described in this section. These macros are defined when their corresponding pragmas are invoked in program source, or when their corresponding compiler options for the Create Module and Create Bound Program commands are specified. Unless otherwise specified, macros when defined have a value of 1.

 __ANSI__
    Defined when the LANGLVL(*ANSI) compiler option is in effect. When this macro is defined, the compiler allows only language constructs that conform to the ANSI/ISO C and C++ standards.

 __ASYNC_SIG__
    C: Defined when the SYSIFCOPT(*ASYNCSIGNAL) compiler option is in effect.

    C++: Defined when TERASPACE(*YES *TSIFC) STGMDL(*TERASPACE) DTAMDL(*LLP64) RTBND(*LLP64) is in effect.

 _CHAR_SIGNED
    Defined when the #pragma chars(signed) directive is in effect, or when the DFTCHAR compiler option is set to *SIGNED. If this macro is defined, the default character type is signed.

 _CHAR_UNSIGNED
    Defined when the #pragma chars(unsigned) directive is in effect, or when the DFTCHAR compiler option is set to *UNSIGNED. Indicates default character type is unsigned.

 __cplusplus98__interface__
    Defined by C++ compiler when the LANGLVL(*ANSI) compiler option is specified.

 __EXTENDED__
    Defined when the LANGLVL(*ANSI) compiler option is not in effect. When this macro is defined, the compiler allows language extensions provided by the ILE C/C++ compiler implementation.

 __FUNCTION__
    Indicates the name of the function currently being compiled. For C++ programs, expands to the actual function prototype.

 __HHW_AS400__
    Indicates that the host hardware is an iSeries processor.

 __HOS_OS400__
    C++: Indicates that the host operating system is OS/400.

 __IBMCPP__
    C++: Indicates the version number of the ILE C/C++ compiler.

 __IFS_IO__
    Defined when SYSIFCOPT(*IFSIO) or SYSIFCOPT(*IFS64IO) is specified on the Create Module or Create Bound Program commands.

 __IFS64_IO__
    Defined when SYSIFCOPT(*IFS64IO) is specified on the Create Module or Create Bound Program commands. When this macro is defined, _LARGE_FILES and _LARGE_FILE_API are also defined in the relevant IBM-supplied header files.

 __ILEC400__
    C: Defined only by the compiler. You can use this macro in source code that is compiled for several platforms. Mark code that is to be compiled only for the iSeries platform with #ifdef __ILEC400__ or, #if defined(__ILEC400__) preprocessor directives.

 __ILEC400_TGTVRM__
    C: Defined by the compiler as an integral value that maps to the version/release/modification of the OS/400(R) that the module or program being compiled is intended to run on. The target release, VxRyMz, translates to an __ILEC400_TGTVRM__ value of xyz, where x, y, and z are integer values. For example, a target release of V3R7M0 will cause the macro to have an integral value of 370.

 _LARGE_FILES
    Defined when the SYSIFCOPT(*IFS64IO) compiler option is in effect and system header file types.h is included.

 _LARGE_FILE_API
    Defined when the SYSIFCOPT(*IFS64IO) compiler option is in effect and system header file types.h is included.

 __LLP64_IFC__
    Defined when the DTAMDL(*LLP64) compiler option is in effect.

 __LLP64_RTBND__
    C++: Defined when the RTBND(*LLP64) compiler option is in effect.

 __OS400__
    This macro is always defined when the compiler is used with the OS/400 operating system.

 __OS400_TGTVRM__
    Defined only by the compiler as an integral value that maps to the version/release/modification of the OS/400(R) that the module or program being compiled is intended to run on. The target release, VxRyMz, translates to an __OS400_TGTVRM__ value of xyz, where x, y, and z are integer values.

 __POSIX_LOCALE__
    Defined when the LOCALETYPE(*LOCALE) or LOCALETYPE(*LOCALEUCS2) compiler options are specified.

 __RTTI_DYNAMIC_CAST__
    Defined when the OPTION(*RTTIALL) or OPTION(*RTTICAST) compiler options are specified, for C++ programs only. This macro is not defined for C.

 __SRCSTMF__
    C: Defined when the SRCSTMF compiler option specifies the location of the source file being compiled.

 __TERASPACE__
    Defined when the TERASPACE(*YES *TSIFC) compiler option is specified.

 __THW_AS400__
    Indicates that the target hardware is an iSeries processor.

 __TIMESTAMP__
    A character string literal containing the date and time when the source file was last changed.

    The date and time will be in the form:

       "Day Mmm dd hh:mm:ss yyyy"

    where:

    Day represents the day of the week (Mon, Tue, Wed, Thu, Fri, Sat, or Sun).

    Mmm represents the month in an abbreviated form (Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, or Dec).

    dd represents the day. If the day is less than 10, the first d will be a blank character.

    hh represents the hour.

    mm represents the minutes.

    ss represents the seconds.

    yyyy represents the year.

    Note:
        Other compilers may not supported this macro. If the macro is supported on other compilers, the date and time values may be different than those that are shown here.

 __TOS_OS400__
    Indicates that the target operating system is OS/400.

 __UCS2__
    Defined when LOCALETYPE(*LOCALEUCS2) is specified on the Create Module or Create Bound Program commands.

 __UTF32__
    Defined when LOCALETYPE(*LOCALEUTF) is specified on the Create Module or Create Bound Program commands.

 __wchar_t
    C: Defined by the standard header file stddef.h.
    C++: Defined by the C++ compiler.
    */



/* ========================================================================= */
#endif /*__IBMCPP__                                                          */

/*IBM Integrated Language Environment (ILE) C++ for AS/400                   */
/* ========================================================================= */
#if defined(__OS400_TGTVRM__)
/*Note: A macro defined only by the C++ compiler, as an integral value that
  maps to the version/release/modification of the OS/400 that the module or
  program being compiled is intended to run on. The target release, VxRyMz,
  translates to an __OS400_TGTVRM__ value of xyz, where x, y, and z areinteger
  values. For example, a target release of V4R4M0 will cause the macro to have
  an integral value of 440.
 */
  #pragma message ("IBM ILE C++ for AS/400")
/* ========================================================================= */
#endif

#if defined(__SUNPRO_CC) /*Sun C++ Compiler */
/* ========================================================================= */
  #warning "Sun C++ Compiler"
/* 5.0 compiler or better
    'bool' is enabled by default but can be disabled using -features=nobool
    in which case _BOOL is not defined
        this is the default in 4.2 compatibility mode triggered by -compat=4 */
  #if __SUNPRO_CC == 0x500
    #warning "ver. 5.0"
  #endif
  #if __SUNPRO_CC == 0x420
    #warning "ver. 4.2"
  #endif
/* ========================================================================= */
#endif /*__SUNPRO_CC                                                         */




/* ========================================================================= */
/*Edison Design Group C++ Compilers with EDG front end are similar.
  To detect them we test:
   __EDG documented by SGI, observed on MIPSpro 7.3.1.1 and KAI C++ 4.0b
   __EDG__ documented in EDG online docs, observed on Compaq C++ V6.3-002 */
#if defined(__EDG) || defined(__EDG__)
  #warning ("Edison Design Group C++ Compiler")
  #if defined(__DECCXX)
    #warning ("Compaq C++ V6.3-002 DEC system")
  #endif
  #if __DECCXX_VER <= 60060005
    #warning ("Compaq C++ v6.0-005 DEC system")
  #endif
/* ========================================================================= */
#endif


/* ========================================================================= */
#if defined (_OSK)      /*Xcompiler for Microware OS (68K)                   */
  #warning ("Xcompiler for Microware OS 68xxx")
#endif /*_OSK                                                                */

#if defined (_OS9000)      /*Xcompiler for Microware OS (PPC)                */
  #warning ("Xcompiler for Microware OS PPC")
#endif /*_OS9000                                                             */

#if defined (_PSOS)      /*Xcompiler for PSOS (PPC)                          */
  #warning ("Xcompiler for PSOS PPC")
#endif /*_PSOS                                                               */

#if defined (PTV_OS)      /*Xcompiler for PTV_OS (PPC)                       */
  #warning ("Xcompiler for PTV_OS PPC")
#endif /*PTV_OS                                                              */

#if defined (__ARM)      /*Xcompiler for Helios (ARM)                        */
  #warning ("Xcompiler for Helios (ARM)")
#endif /*__ARM                                                               */

#if defined (ST20TP3)      /*Xcompiler for ST20 TP3                          */
  #warning ("Xcompiler for ST20 TP3")
#endif /*ST20TP3                                                             */
/* ========================================================================= */


/* ========================================================================= */
#if defined(__MWERKS__)/* Metrowerks CodeWarrior Compiler                    */
  #pragma message ("Metrowerks CodeWarrior Compiler")

   /*Current version of Metrowerks compiler.
     The __MWERKS__ macro will have one of the following values depending upon
     the particular Metrowerks compiler:

        Compiler                             __MWERKS__ value
        before Codewarrior 7 1995                   1
        CodeWarrior 8                            0x2000
        CodeWarrior 8 v2.2                       0x2200
        CodeWarrior 8 v2.4                       0x2400
        CodeWarrior 8 v2.5                       0x2500
        CodeWarrior 9                            0x3000
        CodeWarrior 9.3                          0x3004

     To determine what version of the CodeWarrior C/C++ compiler you are using,
     follow the steps below.

     1. Create a new source file that contains this header file, and add the
        file to the new project, if CodeWarrior IDE is used.
     2. Select the source file in the project window and from the Project menu,
        choose Preprocess. If you are using the command-line version of the
        CodeWarrior C/C++ type:
        "mwcc -EP source.c" if host is Microsoft Windows
        "mwccppc -e source.c" if host is PowerPC with Apple MPW
     3. Browse the preprocessor output for the value of the variable g__MWERKS__.

    */
  const long g__MWERKS__ = __MWERKS__;
  #if __MWERKS__ < 0x2000
    #pragma message ("  -ver. unknown")
  #endif
  #if __MWERKS__ == 0x2000
    #pragma message ("  ver. 8")
  #endif
  #if __MWERKS__ == 0x2200
    #pragma message ("  ver. 8.2.2")
  #endif
  #if __MWERKS__ == 0x2400
    #pragma message ("  ver. 8.2.4")
  #endif
  #if __MWERKS__ == 0x2500
    #pragma message ("  ver. 8.2.5")
  #endif
  #if __MWERKS__ == 0x3000
    #pragma message ("  ver. 9")
  #endif
  #if __MWERKS__ == 0x3003
    #pragma message ("  ver. 9.2")
  #endif
  #if __MWERKS__ == 0x3004
    #pragma message ("  ver. 9.3")
  #endif
  #if __MWERKS__ > 0x3304
    #pragma message ("  +ver. unknown")
  #endif

  #ifdef __embedded_cplusplus
    #pragma message ("Embedded C++ compilation.")
  #endif

  #if defined(__PALMOS__) || defined (__PALMTYPES_H__) || defined (__PALMOS_H__) || defined(_PALMOS)
     #pragma message ("Target OS is PalmOS.")
  #endif
  #if defined(__ARMLET__) /*Metrowerks armlet */
     #pragma message ("Target OS is an armlet.")
  #endif
  #if defined(macintosh) /*Metrowerks 68K or PowerPC on MacOS */
     #pragma message ("Target OS is MacOS.")
  #endif

 /*Targeted OS systems defined in
   .../MSL/MSL_C/MSL_Common/Include/os_enum.h

        __undef_os       0
        __mac_os         1
        __win32_os       3
        __wince_os       5
        __ppc_eabi       6
        __nec_eabi_bare  7
        __nec_eabi_os    8
        __mips_bare      9
        __m56800_os     10
        __n64_os        11
        __mcore_bare    12
        __emb_68k       13
        __m56300_os     14
        __sh_bare       15
        __m56800E_os    16
        __mac_os_x      17
        __dolphin_os    18
        __palm_os       19
        __arm_bare      20
  */
  #ifdef __dest_os

    #if (__dest_os == __arm_bare)
      #pragma message ("Target OS ARM compliant OS.")
    #elif (__dest_os == __dolphin_os)
      #pragma message ("Target is Dolphin OS.")
    #elif (__dest_os == __emb_68k)
      #pragma message ("Target is Motorla 68k compliant OS.")
    #elif (__dest_os == __m56300_os)
      #pragma message ("Target is Motorla 56300 compliant OS.")
    #elif (__dest_os == __m56800E_os)
      #pragma message ("Target is Motorla 56800E compliant OS.")
    #elif (__dest_os == __m56800_os)
      #pragma message ("Target is Motorla 56800 compliant OS.")
    #elif (__dest_os == __mac_os)
      #pragma message ("Target is MacOS.")
    #elif (__dest_os == __mac_os_x)
      #pragma message ("Target is MacOS X.")
    #elif (__dest_os == __mcore_bare)
      #pragma message ("Target is Motorla compliant OS.")
    #elif (__dest_os == __mips_bare)
      #pragma message ("Target is MIPS compliant OS.")
    #elif (__dest_os == __n64_os)
      #pragma message ("Target is Nintendo 64.")
    #elif (__dest_os == __nec_eabi_bare)
      #pragma message ("Target is NEC compliant OS.")
    #elif (__dest_os == __nec_eabi_os)
      #pragma message ("Target is NEC EABI compliant OS.")
    #elif (__dest_os == __no_os)
      #pragma message ("Target is bare board embedded system.")
    #elif (__dest_os == __palm_os)
      #pragma message ("Target is Palm OS.")
    #elif (__dest_os == __ppc_eabi)
      #pragma message ("Target is PowerPC EABI compliant OS.")
    #elif (__dest_os == __ppc_eabi_bare) /*changed to __ppc_eabi*/
      #pragma message ("Target is PowerPC (Motorola 821) compliant OS.")
    #elif (__dest_os == __sh_bare)
      #pragma message ("Target is Hitachi SH compliant OS.")
    #elif (__dest_os == __undef_os)
      #pragma message ("Target is not defined (__undef_os).")
    #elif (__dest_os == __win32_os)
      #pragma message ("Target is Windows 32b compliant OS.")
    #elif (__dest_os == __wince_os)
      #pragma message ("Target is Windows CE.")
    #else
      #pragma message ("Target is unknown OS (__dest_os).")
      /*Target OS brand.
        Note: Browse the preprocessor output for the value of
              the variable __dest_os.
       */
      long g___dest_os = __dest_os;
    #endif
  #endif

  #ifdef __embedded__
    #pragma message ("Target is an embedded OS.")
  #endif

  #if defined(__INTEL__) || defined(__i386__)
    #pragma message ("Compiling for for Intel x86 platform.")
  #endif
  #ifdef __MC68K__
    #pragma message ("Compiling for Motorola 68k platform.")
  #endif
  #ifdef __MC68020__
    #pragma message ("Compiling for Motorola 68020 platform.")
  #endif
  #ifdef __MC68881__
    #pragma message ("Compiling for Motorola 68881 platform.")
  #endif
  #ifdef __A5__
    /*Defined for 68k targets*/
    #if (__A5__ == 1)
      #pragma message ("  data are A5-relative")
    #else
      #pragma message ("  data are A4-relative")
    #endif
  #endif
  #ifdef __MIPS__
    #pragma message ("Compiling for MIPS platform.")
  #endif
  #ifdef __MIPS_ISA2__
    #pragma message ("Compiling for MIPS ISA II platform.")
  #endif
  #ifdef __MIPS_ISA3__
    #pragma message ("Compiling for MIPS ISA III platform.")
  #endif
  #ifdef __MIPS_ISA4__
    #pragma message ("Compiling for MIPS ISA IV platform.")
  #endif
  #ifdef __MIPS__
    #pragma message ("Compiling for MIPS platform.")
  #endif
  #ifdef __VEC__
    #pragma message ("Compiling for Motorola's AltiVec Technology.")
  #endif
  #ifdef __ALTIVEC__
     /*Note: currently defined as 100000000 */
    #pragma message ("Compiling for PowerPC AltiVec Technology.")
  #endif
  #if defined(__arm__) || defined(__arm)
    #pragma message ("Compiling for ARM Risc platform.")
  #endif
  #ifdef __ARMCC_VERSION
    #pragma message ("Compiling for ARM ADS platform.")
  #endif
  #if defined(__POWERPC__) || defined(__powerpc__)
    #pragma message ("Compiling for Power PC platform.")
  #endif

  #ifdef EMULATION_LEVEL
    #if (EMULATION_LEVEL == EMULATION_WINDOWS)
      #pragma message ("  Windows 32b emulation.")
    #elif (EMULATION_LEVEL == EMULATION_MAC)
      #pragma message ("  MacOS emulation.")
    #elif (EMULATION_LEVEL == EMULATION_DOS)
      #pragma message ("  DOS emulation.")
    #elif (EMULATION_LEVEL == EMULATION_UNIX)
      #pragma message ("  Unix emulation.")
    #elif (EMULATION_LEVEL == EMULATION_NONE)
      #pragma message ("  no OS emulation.")
    #else
      #pragma message ("  unknown emulation.")
      /*OS emulator type */
      long g_EMULATION_LEVEL = EMULATION_LEVEL;
    #endif
  #endif

  #ifdef PALMOS_SDK_VERSION
    #if (PALMOS_SDK_VERSION == 0x0510)
      #pragma message ("  Palm OS 5 SDK (68K) R2.")
    #else
      #pragma message ("  unknown PalmOS SDK.")
      /*Palm OS SDK version.
        See also: BuildDefines.h
       */
      long g_PALMOS_SDK_VERSION = PALMOS_SDK_VERSION;
    #endif
  #endif

  #if (__IEEEdoubles__ == 1)
    #pragma message ("Real numbers are 8 bytes long.")
  #endif
  #if (__fourbyteints__ == 1)
    #pragma message ("Integer numbers are 4 bytes long.")
  #endif
  #if __option (little_endian)
    #pragma message ("Little Endian byte order.")
  #else
    #pragma message ("Big Endian byte order.")
  #endif

  #ifdef _MSL_LITTLE_ENDIAN
    #if (_MSL_LITTLE_ENDIAN == 1)
      #pragma message ("_MSL_: Little Endian byte order.")
    #elif (_MSL_LITTLE_ENDIAN == 0)
      #pragma message ("_MSL_: Big Endian byte order.")
    #else
      #pragma message ("_MSL_: Unknown Endian byte order.")
    #endif
  #endif /*_MSL_LITTLE_ENDIAN*/

  #ifdef CPU_TYPE
    #if (CPU_TYPE == CPU_68K)
      #pragma message ("CPU: Motorola 68xxx family.")
    #elif (CPU_TYPE == CPU_PPC)
      #pragma message ("CPU: Power PC family.")
    #elif (CPU_TYPE == CPU_ARM)
      #pragma message ("CPU: ARM Risc family.")
    #elif (CPU_TYPE == CPU_x86)
      #pragma message ("CPU: Intel x86 family.")
    #else
      #pragma message ("CPU: unknown.")
    #endif
  #endif

  #if __option(bool)
    /*Corresponds to the  #pragma bool on | off | reset.
      If pragma bool is off, CodeWarrior C++ compiler equates the bool type
      with the unsigned char data type.
     */
    #pragma message ("ISO C++ Standard bool data type enabled.")
  #endif

#endif /*__MWERKS__                                                          */

#if defined(applec)/* MPW C++ Compiler                                       */
  #pragma message ("MPW C++ Compiler")
#endif /*applec                                                              */

#if defined(__HIGHC__)/* MetaWare High C/C++ Compiler                                       */
  #pragma message ("MetaWare High C/C++ Compiler")
#endif /*__HIGHC__                                                           */

#if defined(__COMO__) /*Comeau C++ Compiler */
  #warning "Comeau C++ Compiler"

/*Comeau C++ 4.0
# __STDC__ Defined in ANSI C mode and in C++ mode. In C++ mode the value may be redefined. Not defined in Microsoft compatibility mode.
# __cplusplus Defined in C++ mode.
# c_plusplus Defined in default C++ mode, but not in strict mode.
# __STDC_VERSION__ Defined in ANSI C mode with the value 199409L. The name of this macro, and its value, are specified in Normative Addendum 1 of the ISO C Standard.
# __SIGNED_CHARS__ Defined when plain char is signed. This is used in the <limits.h> header file to get the proper definitions of CHAR_MAX and CHAR_MIN.
# _WCHAR_T Defined in C++ mode when wchar_t is a keyword. The name of this predefined macro is specified by a configuration flag. _WCHAR_T is the default.
# _BOOL Defined in C++ mode when bool is a keyword. The name of this predefined macro is specified by a configuration flag. _BOOL is the default.
# __ARRAY_OPERATORS Defined in C++ mode when array new and delete are enabled. The name of this predefined macro is specified by a configuration flag. __ARRAY_OPERATORS is the default.
# __EDG_RUNTIME_USES_NAMESPACES When the runtime uses namespaces, this macro name is also defined by default (by default, the runtime does use namespaces -- both this default and the macro name default can be changed under a custom porting arrangement).
# __EDG_IMPLICIT_USING_STD By default (this can be changed under a custom porting arrangement), the runtime does use namespaces however by default (this too can be changed under a custom porting arrangement, or by using the --using_std command line option) it does not emit an implicit using directive on the std namespace (that is, by default it does not effectively emit a using namespace std;) When it does, this macro name (which can be changed under a custom porting arrangement) is emitted.
# __EDG__ Always defined.
# __COMO__ Always defined.
# __EDG_VERSION_ Defined to an integral value that represents the version number of the front end. For example. version 2.30 is represented as 230.
# __COMO_VERSION__ Defined to an integral value that represents the version number.

 */
#endif

/*HP OpenVMS Systems - Compaq C
__STDC_ISO_10646__ macro evaluates to an integer constant of the form yyyymmL (for example, 199712L), intended to indicate that values of type wchar_t  are the coded representations of the characters defined by ISO/IEC 10646, along with all amendments and technical corrigenda as of the specified year and month.
 */
#if defined(__ZTC__) /*Digital Mars C/C++ Compiler */
  /*Always defined. Set to same value as __DMC__. Obsolete(use __DMC__ instead).*/
  #pragma message "Digital Mars C/C++ Compiler"
  #ifdef __NT__
    /*Obsolete - use _WIN32 instead*/
    #pragma message "Target OS is Windows NT or Win32s."
  #endif
#endif

#if defined(__SC__) /*Digital Mars C/C++ Compiler */
  /*Always defined. Set to same value as __DMC__. Obsolete(use __DMC__ instead).*/
  #pragma message "Digital Mars C/C++ Compiler"
#endif

#if defined(__DMC__) /*Digital Mars C/C++ Compiler */

  /*#pragma message "text"
    Causes the compiler to print text as an informational message while
    compiling.
   */
  #pragma message "Digital Mars C/C++ Compiler"
    /*Digital Mars C/C++ Compiler version number:
        0x700  v7.0,
        0x720  v7.2,
        0x800  v8.0.
     */
  const long g__DMC__VER = __DMC__;

  #ifdef __DMC_VERSION_STRING__
    /*Expands to a string identifying the compiler
      in form such as "Digital Mars C/C++ x.xx.x".
     */
    #pragma message (__DMC_VERSION_STRING__)
  #endif

  #if defined(DOS386)
    #pragma message "Target OS is extended DOS 32-bit."
  #endif
  #if defined(DOS16RM)
    #pragma message "Target OS is extended DOS 16-bit."
  #endif

  /* _WINDOWS Generating Windows program.
    _WINDLL Generating Windows DLL
    __INLINE_8087 Defined if generating inline math coprocessor code.
    __I86__ Always defined. Set to target CPU (0 == 8088, 2 == 286, 3 == 386,
           4 == 486, 5 == P5, 6 == P6).
    __SMALL__
    __MEDIUM__
    __COMPACT__
    __LARGE__
    __VCM__
    __FPCE__  Always defined. Indicates NCEG conformance.
    __FPCE__IEEE__ Indicates IEEE 754 conformance.
    DEBUG
    __FUNCTION__  Same as __FUNC__. Provided for Gnu CC compatibility.
    __PRETTY_FUNCTION__ Same as __FUNC__, but pretty-printed (
          C++ functions become more readable). Provided for Gnu CC compatibility.
    __TIMESTAMP__ Always defined. Set to compilation time in
          the form "Ddd Mmm dd hh:mm:ss yyyy".
    _BOOL_DEFINED Set to 1 (enable bool keyword).
    _WCHAR_T_DEFINED Set to 1 (enable wchar_t keyword).
    _CPPRTTI  Set to 1 (enable RTTI).
    _CPPUNWIND  Set to 1 (enable C++ exception handling).
    _CHAR_UNSIGNED Chars are unsigned.
    _CHAR_EQ_UCHAR  chars and unsigned chars are same type.
    _DEBUG_TRACE  Set to 1 when -gt is set.
    _DLL DLL RTL will be used rather than the statically linked in RTL.
    _MSDOS, MSDOS MSDOS target. Defined for all cases where __OS2__ or
          _WIN32 are not defined.
    __OS2__ OS/2 target.
    WIN32,_WIN32  WIN32 target (NT, Windows 95 or Win32s).
    DOS386  32 bit extended DOS target.
    DOS16RM 16 bit extended DOS target.
    M_I86, _M_I86 Always defined.
    _M_I86TM, M_I86TM Tiny memory model.
    _M_I86SM, M_I86SM Small memory model.
    _M_I86MM, M_I86MM Medium memory model.
    _M_I86CM, M_I86CM Compact memory model.
    _M_I86LM, M_I86LM Large memory model.
    _M_I86VM, M_I86VM VCM memory model.
    _M_I8086, M_I8086 8088 is target.
    _M_I286, M_I286 80286 or better is target.
    _M_IX86 Defined for 32 bit targets. Set to: 300 for 386 targets, 400 for 486,
          500 for Pentium, 600 for P6.
    _M_X64  Defined for 64 bit targets.
    _M_IA64 Intel Itanium
   */
#endif

#if defined(__KCC)/*KAI C++ Compiler */
  #warning "KAI C++ Compiler"
#endif

/* ========================================================================= */

#if defined(__INTEL_COMPILER)/*Intel C++ Compiler */
  #warning      "Intel C++ Compiler"
#endif

/*The Intel® C++ Compiler 10.0 for Linux supports the predefined macros listed in the table below. The compiler also includes predefined macros specified by the ISO/ANSI standard.

The following designations apply:
Label 	Meaning
i32 	Included on systems based on IA-32 architecture.
i64em 	Included on systems based on Intel® 64 architecture.
i64 	Included on systems based on IA-64 architecture.

Macro Name 	Value 	i32 	i64em 	i64
__ARRAY_OPERATORS 	1 	X 	X 	X
__BASE_FILE__ 	Name of source file 	X 	X 	X
_BOOL 	1 	X 	X 	X
__cplusplus 	1 (with C++ compiler) 	X 	X 	X
_CLUSTER_OPENMP 	Defined as 1 when the -cluster-openmp or -cluster-openmp-profile compiler option is used. 	  	X 	X
__DEPRECATED 	1 	X 	X 	X
__ECC 	Intel Compiler Version 	  	  	X
__EDG__ 	1 	X 	X 	X
__EDG_VERSION__ 	EDG version 	X 	X 	X
__ELF__ 	1 	X 	X 	X
__extension__ 	  	X 	X 	X
__EXCEPTIONS 	Defined as 1 when -fno-exceptions is not used. 	X 	X 	X
__GNUC__ 	The major version number of gcc installed on the system. 	X 	X 	X
__GNUG__ 	The major version number of g++ installed on the system. 	X 	X 	X
__gnu_linux__ 	1 	X 	X 	X
__GNUC_MINOR__ 	The minor version number of gcc or g++ installed on the system. 	X 	X 	X
__GNUC_PATCHLEVEL__ 	The patch level version number of gcc or g++ installed on the system. 	X 	X 	X
__GXX_ABI_VERSION 	102 	X 	X 	X
__HONOR_STD 	1 	X 	X
__i386 	1 	X
__i386__ 	1 	X
i386 	1 	X
__ia64 	1 	  	  	X
__ia64__ 	1 	  	  	X
__ICC 	Intel compiler version 	X 	X
_INTEGRAL_MAX_BITS 	64 	  	  	X
__INTEL_COMPILER 	Intel compiler version 	X 	X 	X
__INTEL_COMPILER_BUILD_DATE 	YYYYMMDD 	X 	X 	X
__INTEL_RTTI__ 	Defined as 1 when -fno-rtti is not specified. 	X 	X 	X
__INTEL_STRICT_ANSI__ 	Defined as 1 when -strict-ansi is specified. 	X 	X 	X
__itanium__ 	1 	  	  	X
__linux 	1 	X 	X 	X
__linux__ 	1 	X 	X 	X
linux 	1 	X 	X 	X
__LONG_DOUBLE_SIZE__ 	80 	X 	X 	X
__LONG_MAX__ 	9223372036854775807L 	  	X 	X
__lp64 	1 	  	  	X
__LP64__ 	1 	  	X 	X
_LP64 	1 	  	X 	X
_MT 	1 	  	X
__MMX__ 	1 	  	X
__NO_INLINE__ 	1 	X 	X 	X
__NO_MATH_INLINES 	1 	X 	X 	X
__NO_STRING_INLINES 	1 	X 	X 	X
_OPENMP 	Defined as 200505 when -openmp is specified. 	X 	X 	X
__OPTIMIZE__ 	1 	X 	X 	X
__pentium4 	1 	X 	X
__pentium4__ 	1 	X 	X
__PIC__ 	Defined as 1 when -fPIC is specified. 	X 	X 	X
__pic__ 	Defined as 1 when -fPIC is specified. 	X 	X 	X
_PGO_INSTRUMENT 	Defined as 1 when -prof-gen[x] is specified. 	X 	X 	X
_PLACEMENT_DELETE 	1 	X 	X 	X
__PTRDIFF_TYPE__ 	int on IA-32 architecture
long on Intel® 64 architecture
long on IA-64 architecture 	X 	X 	X
__REGISTER_PREFIX__ 	  	X 	X 	X
__SIGNED_CHARS__ 	1 	X 	X 	X
__SIZE_TYPE__ 	unsigned on IA-32 architecture
unsigned long on Intel® 64 architecture
unsigned long on IA-64 architecture 	X 	X 	X
__SSE__ 	Defined as 1 for processors that support SSE instructions. 	X 	X
__SSE2__ 	Defined as 1 for processors that support SSE2 instructions. 	X 	X
__SSE3__ 	Defined as 1 for processors that support SSE3 instructions. 	X 	X
__SSSE3__ 	Defined as 1 for processors that support SSSE3 instructions. 	X 	X
__unix 	1 	X 	X 	X
__unix__ 	1 	X 	X 	X
unix 	1 	X 	X 	X
__USER_LABEL_PREFIX__ 	  	X 	X 	X
__VERSION__ 	Intel version string 	X 	X 	X
__WCHAR_T 	1 	X 	X 	X
__WCHAR_TYPE__ 	long int on IA-32
int on Intel® 64 architecture
int on IA-64 architecture 	X 	X 	X
__WINT_TYPE__ 	unsigned int 	X 	X 	X
__x86_64 	1 	  	X
__x86_64__ 	1 	  	X
 */

/* ========================================================================= */

#if defined(__USLC__)/*SCO UnixWare C++ Compiler */
  #warning "SCO UnixWare C++ Compiler"
#endif

#if defined(CENTERLINE_CLPP) || defined(OBJECTCENTER)/*CenterLine C++ Compiler*/
  #warning      "CenterLine C++ Compiler"
#endif

#if defined(sgi) || defined(__sgi)/*MIPSpro C++ Compiler */
  #warning      "MIPSpro C++ Compiler"
  #if defined(_MIPS_SIM) && ( _MIPS_SIM == _ABIO32) /* o32 ABI mode*/
    #warning "o32 ABI mode"
  #endif
#endif

#if defined(__SC__)/* Symantec C++ Compiler                                  */
/* ========================================================================= */
  #pragma message ("Symantec C++ Compiler")
#endif /*__SC__                                                              */

#if defined (_AM29K)   /*AMD 29000 HighC Compiler                            */
/* ========================================================================= */
  #ifdef VXWORKS
    #pragma message ("Target OS is WindRiver VxWorks.")
  #endif
/* ========================================================================= */
#endif /*_AM29K                                                              */

#if defined (THINK_C)  /*Macintosh-ThinkC                                    */
/* ========================================================================= */
#endif /*THINK_C                                                             */

#if defined (SUN)      /*SUN C - UNIX                                        */
/* ========================================================================= */
#endif /*SUN                                                                 */

#if defined (MIPS)     /*MIPS - UNIX SYS V                                   */
/* ========================================================================= */
#endif /*MIPS                                                                */

#if defined (__i960)      /*INTEL960                                         */
/* ========================================================================= */
#endif /*__i960                                                              */

#if defined (VAX)            /*  VAX C - VMS                                 */
/* ========================================================================= */
#endif /*VAX                                                                 */

#if defined (LAMIGA)          /*   Lattice C - AmigaDOS                      */
/* ========================================================================= */
#endif /*LAMIGA                                                              */

#if defined (UFST_MIPS64)     /*  MIPS 64-bit, Native                        */
/* ========================================================================= */
#endif /*UFST_MIPS64                                                         */

#if defined (UFST_ALPHA_UNIX) /*  DEC Alpha (UNIX) 64-bit, Native            */
/* ========================================================================= */
#endif /*UFST_ALPHA_UNIX                                                     */

/*DEC C compiler defines other preprocessor macros for various identification purposes.

 Each DEC C platform can have additional predefined macros. See your platform-specific DEC C documentation for more information.

 Digital UNIX Predefined Macro Names
  	Macro Name
Operating system name:  	unix
  	__unix__
  	__osf
  	SYSTYPE_BSD
  	_ SYSTYPE_BSD
Architecture name:  	__alpha
Product name:   	__DECC
  	__DECC_ VER
  	LANGUAGE_C
  	__LANGUAGE_C__

OpenVMS VAX and Alpha Predefined Macro Names
  	New Spelling  	Traditional Spelling
Operating system name:  	__vms  	vms
  	__VMS  	VMS
  	__vms_version  	vms_version
  	__VMS_VERSION  	VMS_ VERSION
Architecture name:  	__vax (VAX)  	vax (VAX)
  	__VAX (VAX)  	VAX (VAX)
  	__alpha (Alpha)  	-
  	__ALPHA (Alpha)  	-
  	__Alpha_AXP (Alpha)  	-
  	__32BITS (Alpha)  	-
Product name:   	__vaxc  	vaxc
  	__VAXC  	VAXC
  	__vax11c  	vax11c
  	__VAX11C  	VAX11C
  	__STDC__  	-
  	__DECC  	-
  	__DECC_VER  	-
  	__VMS_V6_RTL_ COMPAT  	-
Compiler Mode:   	__DECC_MODE_STRICT  	-
  	__DECC_MODE_RELAXED  	-
  	__DECC_MODE_ VAXC  	-
  	__DECC_MODE_COMMON  	-
Floating-Point:   	__D_FLOAT  	-
  	__G_FLOAT  	-
  	__IEEE_FLOAT (Alpha)  	-
  	__X_FLOAT (Alpha)  	-
Other:   	__HIDE_FORBIDDEN_NAMES  	-
  	__INITIAL_POINTER_ SIZE (Alpha)  	-


Library Routine Standards Conformance Macros-All platforms
Macro  	Standard
_XOPEN_SOURCE_EXTENDED  	XPG4-UNIX
_XOPEN_SOURCE  	XPG4
_POSIX_C_SOURCE  	POSIX
_ANSI_C_SOURCE  	ISO C and ANSI C
_AES_SOURCE (Digital UNIX)  	Application Environment Services
_OSF_SOURCE (Digital UNIX)  	OSF compatibility
_VMS_V6_SOURCE (OpenVMS)  	OpenVMS Version 6 compatibility
_DECC_V4_SOURCE (OpenVMS)  	DEC C Version 4 compatibility

 */
#if defined(DOS386)
  #warning "Target OS is extended DOS."
#endif

#if defined(__MACOSX__)
  #warning "Target OS is MacOS."
#endif

#ifndef __MWERKS__ /*Not a Metrowerks CodeWarrior Compiler */
  #if defined(macintosh)
    #warning "Target OS is MacOS 9."
  #endif
#endif

#ifndef _MSC_VER /*Not a Microsoft VC compiler */
  #if defined(MSDOS) || defined(_MSDOS) || defined(__MSDOS__)
    #warning "Target OS is MS DOS"
  #endif
#endif

#if defined(OS2) || defined(_OS2) || defined(__OS2__)
  #if defined(__EMX__)
    #warning "Target OS is OS/2 EMX"
  #else
    #warning "Target OS is OS/2"
  #endif
#endif

#ifndef _MSC_VER /*Not a Microsoft VC compiler */
  #if defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
    #warning "Target OS is MS Windows 64b"
  #endif
#endif

#ifndef _MSC_VER /*Not a Microsoft VC compiler */
  #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #warning "Target OS is MS Windows 32b"
  #endif
#endif


#if defined(sun) || defined(__sun) || defined(__sun__)
  #if defined(__SVR4)
    #warning "Target OS is Sun Solaris"
  #else
    #warning "Target OS is BSD 4"
  #endif
#endif

#if defined(hpux) || defined(__hpux) || defined(__hpux__)
  #warning "Target OS is HPUX"
#endif

#if defined(ultrix) || defined(__ultrix) || defined(__ultrix__)
  #warning "Target OS is Ultrix"
#endif

#if defined(sinix)
  #warning "Target OS is Reliant"
#endif

#if defined(linux) || defined(__linux) || defined(__linux__)
  #warning "Target OS is Linux"
#endif

#if defined(__FreeBSD__)
  #warning "Target OS is FreeBSD (BSD 4)"
#endif

#if defined(__NetBSD__)
  #warning "Target OS is NetBSD (BSD 4)"
#endif

#if defined(__OpenBSD__)
  #warning "Target OS is OpenBSD (BSD 4)"
#endif

#if defined(bsdi) || defined(__bsdi__)
  #warning "Target OS is BSDI (BSD 4)"
#endif

#if defined(sgi) || defined(__sgi)
  #warning "Target OS is Irix"
#endif

#if defined(__osf__)
  #warning "Target OS is OSF"
#endif

#if defined(_AIX)
  #warning "Target OS is IBM AIX"
#endif

#if defined(__Lynx__)
  #warning "Target OS is Lynx"
#endif

#if defined(_UNIXWARE)
  #warning "Target OS is Unixware"
#endif

#if defined(__GNU__)
  #warning "defined __GNU__"
#endif

#if defined(DGUX)
  #warning "defined DGUX"
#endif

#if defined(__QNXNTO__)
  #warning "Target OS is QNX 6"
#endif

#if defined(__QNX__)
  #warning "Target OS is QNX"
#endif

#if defined(_SCO_DS) || defined(M_UNIX) || defined(M_XENIX)
  #warning "Target OS is SCO Unix"
#endif

#if defined(sco) || defined(_UNIXWARE7)
  #warning "Target OS is SCO Unixware 7"
#endif

#if !defined(_SCO_DS) && defined(__USLC__) && defined(__SCO_VERSION__)
  #warning "Target OS is SCO Unixware 7"
#endif

#if defined(_SEQUENT_)
  #warning "defined _SEQUENT_"
#endif

#if defined(__svr4__)
  #warning "defined __svr4__"
#endif

/*---------------------------------------------------------------------------*/
/*Portable Operating System Interface for Computer Environments (POSIX)
  is an IEEE standard that defines the open systems environment standards
  for system interfaces, shells, tools, testing, verification, real-time
  processing, security, system administration, networking, and transaction
  processing.
  The standard is based on UNIX system services, but it allows implementation
  on other operating systems.
 */

#ifdef _POSIX_
  /*Portable Operating System Interface for Computer Environments (POSIX)
   */
  #pragma message ("POSIX conformance.")
#endif

#ifdef _POSIX_VERSION
  /*Portable Operating System Interface for Computer Environments (POSIX) version.
    POSIX is an IEEE standard that defines the open systems environment standards
    for system interfaces, shells, tools, testing, verification, real-time
    processing, security, system administration, networking, and transaction
    processing.
    The standard is based on UNIX system services, but it allows implementation
    on other operating systems.
   */
    const long g__POSIX_VERSION = _POSIX_VERSION;
#endif

/*----------------------------------------------------------------------------*/
/*Preprocessor Directives forUnicode character (16-bit)
  ISO 10646-1 Universal Multiple Octet Coded Character Set (UCS).
 */
#if !defined UNICODE && !defined _UNICODE
  #pragma message ("(0) Non-Unicode text mapping")
#endif
#if defined UNICODE
  #pragma message ("(1: UNICODE) Unicode (wide-character) text mapping")
#endif
#if defined _UNICODE
  #pragma message ("(2: _UNICODE) Unicode (wide-character) text mapping")
#endif

/*----------------------------------------------------------------------------*/
/*Boolen type definitions                                                     */
#if defined (__bool_true_false_are_defined)
  /*ISO/IEC 9899:1999 (ISO C99) standard boolean type*/
  #if (__bool_true_false_are_defined == 0)
    #pragma message ("(0) ISO/IEC 9899:1999 (ISO C99) standard boolean type unavailable.")
  #endif
  #if (__bool_true_false_are_defined == 1)
    #pragma message ("(1) ISO/IEC 9899:1999 (ISO C99) standard boolean type available.")
  #endif
#else
  #pragma message ("(2) ISO/IEC 9899:1999 (ISO C99) standard boolean type not defined.")
#endif

#if defined(__BOOL_DEFINED)
  /*Microsoft Visual C++ 5.0 and later; built-in type. sizeof(bool) = 1*/
  #pragma message ("bool type is supported as a built-in type.")
#else
  /*Microsoft Visual C++ 4.2; typedef as int32. sizeof(bool) = 4 */
  #pragma message ("bool type is not supported.")
#endif

#if defined (true) || defined (false)
  #pragma message ("Boolean true/false is defined.")
#else
  #pragma message ("Boolean true, false are not defined.")
#endif /*true/false*/

#if defined (TRUE) || defined (FALSE)
 #pragma message ("Boolean TRUE/FALSE is defined.")
#else
  #pragma message ("Boolean TRUE, FALSE are not defined.")
#endif /*TRUE/FALSE*/

#ifdef bool
  #pragma message ("bool type defined.")
#else
    /*Validate bool typedef*/
    #if defined(_VALIDATE_BOOLEN_TYPE) && (_VALIDATE_BOOLEN_TYPE > 0)
      /*'ISO/IEC 9899:1999 (ISO C99) standard boolean type is defined' flag */
      bool g_bool = true;
      #pragma message ("bool typedef.")
    #endif
#endif /*bool*/

#ifdef _Bool
  #pragma message ("_Bool type defined.")
#else
    /*Validate bool typedef*/
    #if defined(_VALIDATE_BOOLEN_TYPE) && (_VALIDATE_BOOLEN_TYPE > 0)
      /*'Boolean type alias _Bool is defined' flag */
      _Bool g__Bool = 1;
      #pragma message ("_Bool typedef.")
    #endif
#endif /*bool*/

#ifdef BOOL
  #pragma message ("BOOL type defined.")
#else
    /*Validate bool typedef*/
    #if defined(_VALIDATE_BOOLEN_TYPE) && (_VALIDATE_BOOLEN_TYPE > 0)
      /*'Boolean type alias BOOL is defined' flag */
      BOOL g_BOOL = 1;
      #pragma message ("BOOL typedef.")
    #endif
#endif /*_Bool*/

#ifdef Boolean
  #pragma message ("Boolean type defined.")
#else
    /*Validate bool typedef*/
    #if defined(_VALIDATE_BOOLEN_TYPE) && (_VALIDATE_BOOLEN_TYPE > 0)
      /*'Boolean type alias Boolean is defined' flag */
      Boolean g_Boolean = 1;
      #pragma message ("Boolean typedef.")
    #endif
#endif /*Boolean*/

/* Definitions of _HUGE and HUGE_VAL - respectively the XENIX and ANSI names
 * for a value returned in case of error by a number of the floating point
 * math routines in math.h
 */
#ifdef HUGE_VAL
  #pragma message ("floating point HUGE_VAL defined.")
#endif
#ifdef HUGE
  #pragma message ("floating point HUGE defined.")

#endif
#ifdef _HUGE
  /*ANCI C: _STD_C_*/
  #pragma message ("floating point _HUGE defined.")
#endif

/*---------------------------------------------------------------------------*/
/*Third Party Libraries                                                      */

  /*STLPort Standard Template Library port.                                  */
#ifdef _STLP_DEBUG
  #pragma message ("STLport debug mode.")
#endif

  /*C++  Boost Library.
    See also: "boost/version.hpp"
   */
#ifdef BOOST_VERSION
  #pragma message ("C++  Boost Library included.")
  /*C++  Boost Library version.

      BOOST_VERSION % 100 is the sub-minor version
      BOOST_VERSION / 100 % 1000 is the minor version
      BOOST_VERSION / 100000 is the major version
   */
  const long g__BOOST_VERSION = BOOST_VERSION;
#endif

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*_KDBGMACR_H_                                                        */
/*****************************************************************************
 * $Log:
 *  35   Biblioteka1.34        2004-10-21 13:18:40  Darko Kolakovic Boolean types
 *  34   Biblioteka1.33        2004-10-20 13:22:46  Darko Kolakovic Metrowerks
 *       CodeWarrior
 *  33   Biblioteka1.32        2004-10-13 13:48:52  Darko           g__WIN32_WCE
 *  32   Biblioteka1.31        2004-10-13 12:31:43  Darko           _WIN32_WCE
 *  31   Biblioteka1.30        2004-09-08 14:16:30  Darko           WinCE
 *       implementation
 *  30   Biblioteka1.29        2004-09-07 15:47:59  Darko           Metrowerks
 *  29   Biblioteka1.28        2004-08-31 13:02:26  Darko           C++
 *       non-standard conformance
 *  28   Biblioteka1.27        2004-08-26 13:13:58  Darko           Added POSIX
 *  27   Biblioteka1.26        2004-06-03 11:25:17  Darko           _AFXDLL,
 *       _ATL_DLL
 *  26   Biblioteka1.25        2004-06-01 17:50:22  Darko           time sync
 *  25   Biblioteka1.24        2003-09-30 09:09:30  Darko           __LINE__
 *  24   Biblioteka1.23        2003-09-28 01:41:29  Darko           __DMC__
 *  23   Biblioteka1.22        2003-09-22 22:25:55  Darko           formatting
 *  22   Biblioteka1.21        2003-08-26 01:40:44  Darko           Sentry changed
 *  21   Biblioteka1.20        2003-08-14 11:35:23  Darko
 *       __OS400_TGTVRM__
 *  20   Biblioteka1.19        2003-08-07 17:19:15  Darko           debug
 *       preprocessor directive
 *  19   Biblioteka1.18        2003-08-06 22:49:54  Darko           Added GNU
 *       _UNICODE
 *  18   Biblioteka1.17        2003-08-05 22:02:35  Darko           Updated
 *       _MFC_VER
 *  17   Biblioteka1.16        2003-08-05 21:45:48  Darko           comment
 *  16   Biblioteka1.15        2003-08-05 21:24:19  Darko           Added VS .Net
 *       2003
 *  15   Biblioteka1.14        2003-01-30 22:40:40  Darko           Added VC++.Net
 *       dependencies
 *  14   Biblioteka1.13        2002-10-11 14:33:35  Darko Kolakovic
 *  13   Biblioteka1.12        2002-10-10 20:29:24  Darko Kolakovic Fixed _M_I286
 *       test
 *  12   Biblioteka1.11        2002-09-19 17:37:42  Darko Kolakovic
 *  11   Biblioteka1.10        2002-01-29 20:30:46  Darko           Watcom macros
 *  10   Biblioteka1.9         2002-01-25 16:56:38  Darko           Updated
 *       comments
 *  9    Biblioteka1.8         2002-01-24 19:18:46  Darko           Updated
 *       comments
 *  8    Biblioteka1.7         2002-01-10 01:09:44  Darko           Same as 1.4
 *  7    Biblioteka1.6         2002-01-09 12:59:16  Darko           Added Borland
 *       macros
 *  6    Biblioteka1.5         2002-01-09 12:52:32  Darko           Added Borland
 *       macros
 *  5    Biblioteka1.4         2002-01-09 12:50:30  Darko           Added Borland
 *       macros
 *  4    Biblioteka1.3         2002-01-07 23:23:57  Darko           Added new GNUcc
 *       macros
 *  3    Biblioteka1.2         2002-01-01 15:59:35  Darko           GNU compiler
 *       macros
 *  2    Biblioteka1.1         2001-12-23 01:02:07  Darko           GNU compiler
 *  1    Biblioteka1.0         2001-08-19 23:36:54  Darko
 * $
 *****************************************************************************/
