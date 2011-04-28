/*$RCSfile: KProgCstMsvc.h,v $: header file
  $Revision: 1.8 $ $Date: 2011/04/28 22:07:26 $
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
      #define MEM_OUTOFPROCESS MEM_OUTOFPROCESS
    #endif
    #ifndef MEM_FREED
      //Freed memory previously allocated
      //See also: MEM_OUTOFPROCESS
      const unsigned int MEM_FREED        = 0xDDDDDDDD;
      #define MEM_FREED        MEM_FREED
    #endif
    #ifndef MEM_UNINITGLOBAL
      //Uninitialized global.
      //See also: MEM_OUTOFPROCESS
      const unsigned int MEM_UNINITGLOBAL = 0xCDCDCDCD;
      #define MEM_UNINITGLOBAL MEM_UNINITGLOBAL
    #endif
    #ifndef MEM_UNINITLOCAL
      //Uninitialized local (on the stack)
      //See also: MEM_OUTOFPROCESS
      const unsigned int MEM_UNINITLOCAL  = 0xCCCCCCCC;
      #define MEM_UNINITLOCAL  MEM_UNINITLOCAL
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

#if _MSC_VER < 1400
  //Older version than Microsoft Visual C/C++ 2005, version 8.0
  typedef int errno_t; //global error type
  #define errno_t errno_t
  /*Set the value of the errno global variable.
    Possible values of errno are defined in <errno.h>.
    Required header is <stdlib.h>.
    Parameters
      [in] value    The new value of errno.

   See also: _get_errno, errno, _doserrno, _sys_errlist, and _sys_nerr
   */
  #define _set_errno(err) (errno = (err))
  /*Gets the current value of the errno global variable.
    Possible values of errno are defined in <errno.h>.
    Required header is <stdlib.h>.
    Parameters
      [out] pValue    A pointer to an integer to be filled with the current
                      value of the errno variable.

    See also: _set_errno, errno, _doserrno, _sys_errlist, and _sys_nerr
   */
  #define _get_errno(perr) (*perr = errno)
#endif


/*Note   When porting DLL source code from Win16 to Win32, replace each instance
  of __export with __declspec(dllexport).
 */

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
        _KEXPORTDECL class <class name>
        _KEXPORTDECL return_type <function name>
        _KEXPORTDECL data_type <data name>

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
        _KINEXDECL class <class name>
        _KINEXDECL return_type <function name>
        _KINEXDECL data_type <data name>

      See also: _KEXPORTDECL, _KIMPORTDECL,._USE_EXPORT, __declspec, dllexport,
      dllimport
     */
    #define _KINEXDECL _KEXPORTDECL
  #else /*!_USE_EXPORT*/
    #define _KINEXDECL _KIMPORTDECL
  #endif /*_USE_EXPORT*/
#endif

/*///////////////////////////////////////////////////////////////////////////*/
/*Common declartions
 */

/*8-bit data type allowing acces to indvidual bit-fields.

  Note: using bit-fields is potentially thread unsafe, if multiple mutexes
  are used to guard different fields. Use instead single mutex to protect
  all fields together.

  Note: The type-specifier for the bit-field declarator must be unsigned int,
  signed int, or int.
  A Microsoft extension to the ANSI C standard allows char and long types 
  (both signed and unsigned) for bit fields.
  
 */
typedef union tagSTATUS8
  {
  uint8  BYTE; //Eight binary digits long unit of data.

  struct tagBIT
    {
    uint8 B0 :1; //Bit 0: Least Significant Bit (LSB)
    uint8 B1 :1; //Bit 1
    uint8 B2 :1; //Bit 2
    uint8 B3 :1; //Bit 3
    uint8 B4 :1; //Bit 4
    uint8 B5 :1; //Bit 5
    uint8 B6 :1; //Bit 6
    uint8 B7 :1; //Bit 7: Most Signficant Bit (MSB)
    } BIT;  //Binary digit
  } STATUS8;

/* ///////////////////////////////////////////////////////////////////////// */
  #endif /*_MSC_VER */
#endif  /*__KPROGCSTMSVC_H__*/
/*****************************************************************************
 * $Log: KProgCstMsvc.h,v $
 * Revision 1.8  2011/04/28 22:07:26  ddarko
 * status with bit-field access
 *
 * Revision 1.7  2009/04/03 20:36:16  ddarko
 * fixed _MSC_VER for errno
 *
 * Revision 1.6  2009/03/09 19:55:40  ddarko
 * typo
 *
 * Revision 1.5  2009/03/01 00:30:48  ddarko
 * formatting
 *
 * Revision 1.3  2009/01/08 22:02:14  ddarko
 * *** empty log message ***
 *
 * Revision 1.2  2008/12/17 21:35:32  ddarko
 * Examples
 *
 * Revision 1.1  2008/12/17 21:10:54  ddarko
 * dllexport macro
 *
 * Nov. 93 D. Kolakovic
 *****************************************************************************/
