/*$Workfile: KDbgMacr.h$: header file
  $Revision: 14$ $Date: 10/11/02 2:33:35 PM$
  $Author: Darko Kolakovic$

  Dumps values of some compiler-specific predefined macros
  Copyright: CommonSoft Inc.
  Darko Kolakovic April 1988
*/
/* Group=Diagnostic                                                          */

#ifndef __KDBGMACR_H__
    /*KDbgMacr.h sentry                                                      */
  #define __KDBGMACR_H__

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

/* ========================================================================= */
#ifdef GCCx86 /*GNU C Compiler on Intel x86                                  */
  #ifdef VXWORKS
    #warning "Target OS is WindRiver VxWorks."
  #endif
#endif /*GCCx86                                                              */

#ifdef __GNUC__  /*GNU C/C++ Compiler                                        */
  /*ANSI C macros ---------------------------------------------------------- */
  #ifdef __DATE__
    /*Macro expands to a string constant that describes the date on which
      the preprocessor is being run. The formati is as following:
      "Mon dd yyyy".                                                         */
    //#pragma message ("Date: " __DATE__)
  #endif
  #ifdef __TIME__
    /*Macro expands to a string constant that describes the time at which
      the preprocessor is being run. The format is 24 hour clock and looks
      like "hh:mm:ss".                                                       */
    //#pragma message ("Time: " __TIME__)
  #endif
  #ifdef __STDC__
    /*Macro expands to the constant 1, to signify that this is
      ANSI Standard C. (Whether that is actually true depends on what
      C compiler will operate on the output from the preprocessor.)          */
    #warning "ANSI C complience"
  #endif
  #ifdef __STDC_VERSION__
    /*C Standard's version number is a long integer in form: yyyymm where
      yyyy and mm are the year and month of the Standard version.
      This signifies which version of the C Standard the preprocessor
      conforms to.                                                           */
    const long g___STDC_VERSION__ = __STDC_VERSION__;
  #endif
  /*GNU-Specific macros ---------------------------------------------------- */
  #ifdef __GNUG__
    /*GNU C compiler defines this when the compilation language is C++       */
    #warning "GNU C++ Compiler"
  #else
    #warning "GNU C Compiler"
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

  #ifdef __STRICT_ANSI__
    /*Macro is defined if and only if the "-ansi" switch was specified when
      GNU C was invoked. Its definition is the null string. This macro exists
      primarily to direct certain GNU header files not to define certain
      traditional Unix constructs which are incompatible with ANSI C.        */
   #warning  "strict ANSI"
  #endif
  #ifdef __CHAR_UNSIGNED__
    /*Macro is defined if and only if the data type char is unsigned on the
      target machine. It exists to cause the standard header file limit.h to
      work correctly.                                                        */
    #warning  "char type defined as unsigned char"
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
        #if BSD == 44
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
  /*ANSI C macros ---------------------------------------------------------- */
  #ifdef __DATE__
    #pragma message ("Date: " __DATE__)
  #endif
  #ifdef __TIME__
    #pragma message ("Time: " __TIME__)
  #endif
  #ifdef __STDC__
    /*Indicates full conformance with the ANSI C standard.                   */
    #pragma message ("ANSI C complience")
  #endif
  #ifdef __STDC_VERSION__
    /*C Standard's version number                                            */
    const long g___STDC_VERSION__ = __STDC_VERSION__;
  #endif
  /*Microsoft-Specific macros ---------------------------------------------- */
  #ifdef _MSC_VER
    #ifdef _DEBUG
       #pragma message ("Debug version")
    #else
      #pragma message ("Release version")
    #endif
    #if _MSC_VER >= 800
      #pragma message ("Microsoft Visual C/C++ compiler")
    #else
     #if _MSC_VER > 600
       #pragma message ("Microsoft C/C++ compiler")
     #else
       #pragma message ("Microsoft C compiler")
     #endif
    #endif

   /*Current version of Microsoft compiler.
     The _MSC_VER macro will have one of the following values depending upon
     the particular Microsoft compiler:

        Compiler                           _MSC_VER value

        C Compiler version 6.0                  600
        C/C++ compiler version 7.0              700
        Visual C++, Windows, version 1.0        800
        Visual C++, 32-bit, version 1.0         800
        Visual C++, Windows, version 1.5        850
        Visual C++, Windows, version 2.0        900
        Visual C++, 32-bit, version 2.x         900
        Visual C++, 32-bit, version 4.0         1000
        Visual C++, 32-bit, version 4.2         1020
        Visual C++, 32-bit, version 5.0         1100
        Visual C++, 32-bit, version 6.0         1200

     See also: Q65472
    */
    const int g__MSC_VER = _MSC_VER;
    #if _MSC_VER < 600
      #pragma message ("ver. unknown)
    #endif
    #if _MSC_VER == 600
      #pragma message ("ver. 6.0")
    #endif
    #if _MSC_VER == 700
      #pragma message ("ver. 7.0")
    #endif
    #if _MSC_VER == 800
      #pragma message ("ver. 1.0")
    #endif
    #if _MSC_VER == 850
      #pragma message ("ver. 1.5")
    #endif
    #if _MSC_VER == 900
      #pragma message ("ver. 2.0")
    #endif
    #if _MSC_VER == 1000
      #pragma message ("ver. 4.0")
    #endif
    #if _MSC_VER == 1020
      #pragma message ("ver. 4.2")
    #endif
    #if _MSC_VER == 1100
      #pragma message ("ver. 5.0")
    #endif
    #if _MSC_VER == 1200
      #pragma message ("ver. 6.0")
    #endif
    #if _MSC_VER > 1200
      #pragma message ("ver. unknown")
    #endif
  #endif
  #ifdef _MFC_VER
    #pragma message ("Included Microsoft Fundation Class (MFC) library.")
     /*Current version of Microsoft Fundation Class (MFC) library.
      */
    const int g__MFC_VER = _MFC_VER;
    #if _MFC_VER < 300
      #pragma message ("ver. unknown")
    #endif
    #if _MFC_VER == 0x0320
      #pragma message ("ver. 3.2")
    #endif
    #if _MFC_VER == 0x0400
      #pragma message ("ver. 4.0")
    #endif
    #if _MFC_VER == 0x0410
      #pragma message ("ver. 4.10")
    #endif
    #if _MFC_VER == 0x420
      #pragma message ("ver. 4.20")
    #endif
    #if _MFC_VER == 0x0421
      #pragma message ("ver. 4.21")
    #endif
    #if _MFC_VER == 0x0600
      #pragma message ("ver. 6.00")
    #endif
    #if _MFC_VER == 0x0601
      #pragma message ("ver. 6.01")
    #endif
    #if _MFC_VER > 0x0601
      #pragma message ("ver. unknown")
    #endif
  #endif
  #ifdef _MSC_EXTENSIONS
    #pragma message ("Enabled compiler extensions.")
  #endif
  #ifdef _CHAR_UNSIGNED
    #pragma message ("Default char type is unsigned.")
  #endif
  #ifdef __cplusplus
    #pragma message ("C++ compilation.")
  #endif
  #ifdef _CPPUNWIND
    #pragma message ("Enabled Exception Handling.")
  #endif
  #ifdef _CPPRTTI
    #pragma message ("Enabled Run-Time Type Information.")
  #endif
  #ifdef _MT
    #pragma message ("Enabled Multithreading.")
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
      #pragma message ("CPU: unknown)
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
  #endif
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
  #ifdef _M_MPPC
    #pragma message ("Compiling for for Power Macintosh platform.")
  #endif
  #ifdef _M_MRX000
    #pragma message ("Compiling for for MIPS platform.")
  #endif
  #ifdef _M_PPC
    #pragma message ("Compiling for for PowerPC platform.")
  #endif
  #ifdef _WIN32
    #pragma message ("Target OS is Win32.")
  #endif
  #ifdef WIN16
    #pragma message ("Target OS is Win16.")
  #endif
  #ifdef _WINDOWS
    #pragma message ("Target OS is Win16.")
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
     |WINVER=0x0500        |Windows 98 and Windows 2000      |
     |                     |                                 |
     |_WIN32_WINNT=0x0500  |Windows 2000                     |
     |WINVER=0x0500        |                                 |
     |                     |                                 |
     |_WIN32_WINNT=0x0501  |Windows XP                       |
     |WINVER=0x0501        |                                 |
     +---------------------+---------------------------------+
     |_WIN32_IE=0x0300     |Internet Explorer 3.0, 3.01, 3.02|
     |                     |                                 |
     |_WIN32_IE=0x0400     |Internet Explorer 4.0            |
     |                     |                                 |
     |_WIN32_IE=0x0401     |Internet Explorer 4.01           |
     |                     |                                 |
     |_WIN32_IE=0x0500     |Internet Explorer 5.0, 5.0a, 5.0b|
     |                     |                                 |
     |_WIN32_IE=0x0501     |Internet Explorer 5.01, 5.5      |
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
    #elif WINVER == 0x0500
      #pragma message ("Target OS is MS Windows 2000.")
    #elif WINVER == 0x0501
      #pragma message ("Target OS is MS Windows XP.")
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
    #else
      #pragma message ("Target OS is MS Windows ?? (WINNT).")
    #endif
  #endif

  #ifdef _CONSOLE
    #pragma message ("Target is an console application.")
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
    #if _WIN32_IE >= 0x0500
      #pragma message ("5.00 and later.")
    #else
      #if _WIN32_IE >= 0x0400
          #pragma message ("4.0 and later.")
      #else
        #if _WIN32_IE >= 0x0300
          #pragma message ("3.0 and later.")
         #else
           #if _WIN32_IE >= 0x0200
             #pragma message ("2.0 and later.")
           #else
             #pragma message ("unknown.")
          #endif
        #endif
      #endif
    #endif
  #endif


/* ========================================================================= */
#endif /*_MSC_VER                                                            */

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


M_I86

WATCOM C/C++ predefines the macro M_I86 to identify the target as a 16-bit Intel 80x86 compatible environment (defined by the WATCOM C/C++16 compilers).


M_I386

WATCOM C/C++ predefines the macro M_I386 to identify the target as a 32-bit Intel 386 compatible environment (defined by the WATCOM C/C++32 compilers).


__386__

WATCOM C/C++ predefines the macro __386__ to identify the target as a 32-bit Intel 386 compatible environment (defined by the WATCOM C/C++32 compilers).

The WATCOM C/C++ compilers support application development for a variety of operating systems.  The following macros are defined for particular target operating systems.


__DOS__

WATCOM C/C++ predefines the macro __DOS__ to identify the target operating system as MS/DOS (including DOS Extenders).


MSDOS

WATCOM C/C++ predefines the macro MSDOS to identify the target operating system as MS/DOS (including DOS Extenders).


__OS2__

WATCOM C/C++ predefines the macro __OS2__ to identify the target operating system as OS/2 (1.x or 2.x).


__QNX__

WATCOM C/C++ predefines the macro __QNX__ to identify the target operating system as QNX.


__NETWARE_386__

WATCOM C/C++ predefines the macro __NETWARE_386__ to identify the target operating system as Novell NetWare 386.


__NT__

WATCOM C/C++ predefines the macro __NT__ to identify the target operating system as NT.


__WINDOWS__

WATCOM C/C++ predefines the macro __WINDOWS__ to identify the target operating system as Microsoft Windows.

(16-bit only) This macro is defined when the "zw", "zW", "zWs", or "bt=windows" option is specified.

(32-bit only) This macro is defined when the "zw" or "bt=windows" option is specified.


__WINDOWS_386__

WATCOM C/C++ predefines the macro __WINDOWS_386__ to identify the target operating system as 32-bit Microsoft Windows.
This macro is defined when the "zw" or "bt=windows" option is specified and you are using a 32-bit compiler.

The following macros indicate which compiler is compiling the C/C++ source code.


__cplusplus

WATCOM C++ predefines the macro __cplusplus to identify the compiler as a C++ compiler.


__WATCOMC__

WATCOM C/C++ predefines the macro __WATCOMC__ to identify the compiler as one of the WATCOM C/C++ compilers.

The value of the macro depends on the version number of the compiler.  The value is 100 times the version number (version 8.5 yields 850, version 9.0 yields 900, etc.).

The following macros are defined under the conditions described.


__FPI__

WATCOM C/C++ predefines the macro __FPI__ when the "fpi" or "fpi87" option is used.


__CHAR_SIGNED__

WATCOM C/C++ predefines the macro __CHAR_SIGNED__ when the "j" option is used.


__CHEAP_WINDOWS__

(16-bit only) WATCOM C/C++ predefines the macro __CHEAP_WINDOWS__ when the "zW" option is used.


__INLINE_FUNCTIONS__

WATCOM C/C++ predefines the macro __INLINE_FUNCTIONS__ when the "oi" option is used.


NO_EXT_KEYS

WATCOM C/C++ predefines the macro NO_EXT_KEYS when the "za" option is used.


__FLAT__

(32-bit only) WATCOM C/C++ predefines the macro __FLAT__ when the "mf" option is used.


M_I86SM, __SMALL__

WATCOM C/C++ predefines the macros M_I86SM and __SMALL__ when the "ms" option is used.


M_I86MM, __MEDIUM__

WATCOM C/C++ predefines the macros M_I86MM and __MEDIUM__ when the "mm" option is used.


M_I86CM, __COMPACT__

WATCOM C/C++ predefines the macros M_I86CM and __COMPACT__ when the "mc" option is used.


M_I86LM, __LARGE__

WATCOM C/C++ predefines the macros M_I86LM and __LARGE__ when the "ml" option is used.


M_I86HM, __HUGE__

(16-bit only) WATCOM C/C++ predefines the macros M_I86HM and __HUGE__ when the "mh" option is used.
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
#if defined(__IBMCPP__)/* IBM C++ Compiler                                       */
  #pragma message ("IBM C++ Compiler")

/* ========================================================================= */
#endif /*__IBMCPP__                                                          */



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
  #if defined(__INTEL__) /*Werks for Windows */
    #warning "Target OS is MS Windows 32b"
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
#endif

#if defined(__KCC)/*KAI C++ Compiler */
  #warning "KAI C++ Compiler"
#endif

#if defined(__INTEL_COMPILER)/*Intel C++ Compiler */
  #warning      "Intel C++ Compiler"
#endif

#if defined(__USLC__)/*SCO UnixWare C++ Compiler */
  #warning "SCO UnixWare C++ Compiler"
#endif

#if defined(CENTERLINE_CLPP) || defined(OBJECTCENTER)/*CenterLine C++ Compiler */
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



#if defined(__MACOSX__)
  #warning "Target OS is MacOS."
#endif

#if defined(macintosh)
  #warning "Target OS is MacOS 9."
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

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*__KDBGMACR_H__                                                      */
/******************************************************************************
 * $Log:
 *  10   Biblioteka1.9         25/01/2002 3:56:38 PMDarko           Updated
 *       comments
 *  9    Biblioteka1.8         24/01/2002 6:18:46 PMDarko           Updated
 *       comments
 *  8    Biblioteka1.7         10/01/2002 12:09:44 AMDarko           Same as 1.4
 *  7    Biblioteka1.6         09/01/2002 11:59:16 AMDarko           Added Borland
 *       macros
 *  6    Biblioteka1.5         09/01/2002 11:52:32 AMDarko           Added Borland
 *       macros
 *  5    Biblioteka1.4         09/01/2002 11:50:30 AMDarko           Added Borland
 *       macros
 *  4    Biblioteka1.3         07/01/2002 10:23:57 PMDarko           Added new
 *       GNUcc macros
 *  3    Biblioteka1.2         01/01/2002 2:59:35 PMDarko           GNU compiler
 *       macros
 *  2    Biblioteka1.1         23/12/2001 12:02:07 AMDarko           GNU compiler
 *  1    Biblioteka1.0         19/08/2001 10:36:54 PMDarko
 * $
 *****************************************************************************/
