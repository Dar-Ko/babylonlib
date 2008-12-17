/*$RCSfile: KProgCstMsvc.h,v $: header file
  $Revision: 1.1 $ $Date: 2008/12/17 21:10:54 $
  $Author: ddarko $

  Constants used in conjuncture with MSVC/C++
  Copyright: CommonSoft Inc.
  Nov. 93 D. Kolakovic
  2008-12-17 D.K.
 */

#ifndef __KPROGCSTMSVC_H__
  /*$RCSfile: KProgCstMsvc.h,v $ sentry */
  #define __KPROGCSTMSVC_H__
#ifdef _MSC_VER /*Microsoft Visual C/C++ Compiler*/

  #if _MSC_VER > 1000
    #pragma once
  #endif // _MSC_VER > 1000

  #ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files*/
    #pragma message ("   #include " __FILE__ )
  #endif


  #ifndef __cplusplus /*C compilation*/
    #pragma message ("   C compilation " __FILE__ )

    #ifndef MEM_OUTOFPROCESS
    /*Memory usually outside of a process ("No man's land").
      Microsoft compiler initializes certain memory blocks with specific values to
      help problem diagnostic and debugging. In debug builds every byte is set to
      certain value. These values are undocumented and subject to change.
      User should look for patterns of 4 or more bytes with specific values.

      Note: defined also in KProgCst.h to be used as general diagnostic assistance.

      See also: Long, Mark; "Troubleshooting Common Problems with Applications:
      Debugging in the  Real World";
      {html: <a href="msdn.microsoft.com/en-us/library/aa260966(VS.60).aspx" title="MSDN">
      Table 1. Potential patterns</a>},
      KProgCst.h, MEM_FREED, MEM_UNINITGLOBAL, MEM_UNINITLOCAL
     */
      #define MEM_OUTOFPROCESS 0xFDFDFDFD
    #endif
    #ifndef MEM_FREED
      #define MEM_FREED        0xDDDDDDDD //Freed memory previously allocated
                                          //See also: MEM_OUTOFPROCESS
    #endif
    #ifndef MEM_UNINITGLOBAL
      #define MEM_UNINITGLOBAL 0xCDCDCDCD //Uninitialized global.
                                          //See also: MEM_OUTOFPROCESS
    #endif
    #ifndef MEM_UNINITLOCAL
      #define MEM_UNINITLOCAL  0xCCCCCCCC //Uninitialized local (on the stack)
                                          //See also: MEM_OUTOFPROCESS
    #endif

    /*------------------------------------------------------------------------*/
  #else /*__cplusplus  C++ compilation*/
    #pragma message ("   C++ compilation " __FILE__ )

    #ifndef MEM_OUTOFPROCESS
    /*Memory usually outside of a process ("No man's land").
      Microsoft compiler initializes certain memory blocks with specific values
      to help problem diagnostic and debugging. In debug builds every byte is set
      to certain value. These values are undocumented and subject to change.
      User should look for patterns of 4 or more bytes with specific values.

      Note: defined also in KProgCst.h to be used as general diagnostic assistance.

      See also: Long, Mark; "Troubleshooting Common Problems with Applications:
      Debugging in the  Real World";
     {html: <a href="msdn.microsoft.com/en-us/library/aa260966(VS.60).aspx"
      title="MSDN"> Table 1. Potential patterns</a>},
      KProgCst.h, MEM_FREED, MEM_UNINITGLOBAL, MEM_UNINITLOCAL
     */
      const unsigned int MEM_OUTOFPROCESS = 0xFDFDFDFD;
    #endif
    #ifndef MEM_FREED
      //Freed memory previously allocated
      //See also: MEM_OUTOFPROCESS
      const unsigned int MEM_FREED        = 0xDDDDDDDD;
    #endif
    #ifndef MEM_UNINITGLOBAL
      //Uninitialized global.
      //See also: MEM_OUTOFPROCESS
      const unsigned int MEM_UNINITGLOBAL = 0xCDCDCDCD;
    #endif
    #ifndef MEM_UNINITLOCAL
      //Uninitialized local (on the stack)
      //See also: MEM_OUTOFPROCESS
      const unsigned int MEM_UNINITLOCAL  = 0xCCCCCCCC;
    #endif

  #endif /*!__cplusplus*/

  /*/////////////////////////////////////////////////////////////////////////*/
  /* Global macros                                                           */

  #ifndef _UNUSED
    /*Resolves the compiler warning about unused arguments.

      See also: KProgCst.h

      Example:
          void main (int x, int y)
          {
          _UNUSED(y);
          x = 3;
          ...
          }
     */
    #define _UNUSED(x) ((void)x)
  #endif

  #ifndef UNUSED
    /*Resolves the compiler warning about unused arguments.
      Synonim to _UNUSED, UNUSED_ARG.
     */
    #define UNUSED _UNUSED
  #endif
  #ifndef UNUSED_ARG
    /*Resolves the compiler warning about unused arguments.
      Synonim to _UNUSED, UNUSED.
     */
    #define UNUSED_ARG _UNUSED
  #endif

//Note   When porting DLL source code from Win16 to Win32, replace each instance of __export with __declspec(dllexport).

/*Microsoft 16-bit compiler---------------------------------------------------*/
#ifdef MSC        /*Microsoft C - Windows 3.0 Compiler 16-bit*/
  #define _KMSVC16 1630
#endif

#if (_MSC_VER <= 1020) || (MSVC) /*(Microsoft Visual C/C++ - 4.2 or lessc*/
  #define _KMSVC16 1642
#endif

#if defined (DOS) || (MSDOS) || (_MSDOS) || (WIN16) /*16-bit OS target*/
  #define _KMSVC16 1600
#endif

#ifdef _KMSVC16
  /*The function modifier can be used in conjunction with the /GD option switch
    to export a function from a dynamic-link library (DLL) for the
    Microsoft Windows operating system without listing the name of the function
    in the EXPORTS section of the DLL's module definition (.DEF) file.

    Specific to Microsoft C/C++ Optimizing Compiler v7.0+
   */
  #define _KEXPORTDECL  __export
  #define _KIMPORTDECL
#endif /*_KMSVC16*/

#ifndef _KEXPORTDECL
  /*This storage-class specification explicitly define the DLL’s interface to
    its client, which can be the executable file or another DLL. The attribute
    allows the compiler to generate the export names automatically and place
    them in a library (.lib) file.
    When building your DLL, you typically create a header file that contains
    the function prototypes and/or classes you are exporting, and add
    the _KEXPORTDECL specification to the declarations in the header file.
    Exporting a C++ function with this specification  will expose the function
    with C++ name mangling. If C++ name mangling is not desired, either use a
    EXPORTS keyword in associated definition (.def) file or declare the function
    as extern "C".
    This modifiers are used to export classes, functions, and data.

    Examples:
        class _KINEXDECL <class name>
        return_type _KINEXDECL <function name>
        data_type _KINEXDECL <data name>

    Note   When porting DLL source code from Win16 to Win32, replace each instance
    of __export with _KEXPORTDECL.
     .
    See also: _KIMPORTDECL, _KINEXDECL,._USE_EXPORT, __declspec, dllexport
   */
  #define _KEXPORTDECL  __declspec(dllexport)
#endif
#ifndef _KIMPORTDECL
  /*This storage-class specification explicitly define the object as external to
    DLL's client, which can be the executable file or another DLL.

    See also: _KEXPORTDECL, _KINEXDECL,._USE_EXPORT, __declspec, dllimport
   */
   #define _KIMPORTDECL  __declspec(dllimport)
#endif

//Export declartion; to declare class neither exported nor imported,
//undefine _PREMIUM_EXPORT and _PREMIUM_INEX
#ifndef _KINEXDECL
  #ifdef _USE_EXPORT
    /*Command the linker to enter an object name into an export table for the
      module.
      When building your DLL, you typically create a header file that contains
      the function prototypes and/or classes you are exporting, add
      the _KINEXDECL specification to the declarations in the header file and
      define _USE_EXPORT. If _USE_EXPORT is not defined implies import specification.
      This modifiers are used to export classes, functions, and data.

      Examples:
          class _KINEXDECL <class name>
          return_type _KINEXDECL <function name>
          data_type _KINEXDECL <data name>

      See also: _KEXPORTDECL, _KIMPORTDECL,._USE_EXPORT, __declspec, dllexport,
      dllimport
     */
    #define _KINEXDECL _KEXPORTDECL
  #else /*!_USE_EXPORT*/
    #define _KINEXDECL _KIMPORTDECL
  #endif /*_USE_EXPORT*/
#endif
/* ///////////////////////////////////////////////////////////////////////// */
  #endif /*_MSC_VER */
#endif  /*__KPROGCSTMSVC_H__*/
/*****************************************************************************
 * $Log: KProgCstMsvc.h,v $
 * Revision 1.1  2008/12/17 21:10:54  ddarko
 * dllexport macro
 *
 * Nov. 93 D. Kolakovic
 *****************************************************************************/
