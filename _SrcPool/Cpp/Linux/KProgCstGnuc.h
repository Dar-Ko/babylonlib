/*$RCSfile: KProgCstGnuc.h,v $: header file
  $Revision: 1.1 $ $Date: 2012/01/26 16:22:37 $
  $Author: ddarko $

  Constants used in conjuncture with GNU C
  Jan. 97 D. Kolakovic
  2012-01-17 D.K.
 */

#ifndef __KPROGCSTGNUC_H__
  /*$RCSfile: KProgCstGnuc.h,v $ sentry */
  #define __KPROGCSTGNUC_H__
#ifdef __GNUC__ /*GNU C/C++ Compiler*/

  #ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files*/
    #warning ("   #include " __FILE__ )
  #endif


  /*/////////////////////////////////////////////////////////////////////////*/
  /* Global macros                                                           */

  #ifndef _UNUSED
    #if !defined(__cplusplus)
      /*Attribute of unused function arguments.
        Resolves the compiler warning about unused arguments.
        See also: KProgCst.h

        Example:
            void main (int x, int y)
            {
            _UNUSED(y);
            x = 3;
            ...
            }
      */
      #define _UNUSED(param) param __attribute__((__unused__))
    #else
      //GNU C++ doesn't support this attribute
      #define _UNUSED
    #endif
   //  #define _UNUSED(param) do {/* null */} while (&param == 0) D.K.  TODO: test
   //  #define _UNUSED(param) param = *(&param);
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

#ifndef _KEXPORTDECL
  /*The object attribute can be used to export a function or an object from 
    a shared library (also knows as dynamic-link library DLL). The attribute
    allows the compiler to generate the export names automatically and place
    them in a library (.so) file.
    By default all function are exported unless is used the specifier
      __attribute__ ((visibility("hidden"))) or
      --hidden compiler switch
    This modifier is used to export classes, functions, and data.
    See also: _KEXPORTDECL, _KIMPORTDECL, _USE_EXPORT, ___attribute__ , visibility
   */
  #define _KEXPORTDECL  ___attribute__ ((visibility("default")))
#endif
#ifndef _KIMPORTDECL
/*This specification explicitly describe the object as external to a client of
  the shared library (DLL), which can be the executable file or another DLL.
  It has no effect on the way how an object is stored.

  See also: _KEXPORTDECL, _KINEXDECL,._USE_EXPORT, ___attribute__ , visibility
 */
   #define _KIMPORTDECL
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

      See also: _KEXPORTDECL, _KIMPORTDECL, _USE_EXPORT, ___attribute__ , visibility
     */
    #define _KINEXDECL _KEXPORTDECL
  #else /*!_USE_EXPORT*/
    #define _KINEXDECL _KIMPORTDECL
  #endif /*_USE_EXPORT*/
#endif

/*///////////////////////////////////////////////////////////////////////////*/
/*Common declartions
 */

/* TODO: */

/* ///////////////////////////////////////////////////////////////////////// */
  #endif /*__GNUC__ */
#endif  /*__KPROGCSTGNUC_H__*/
/*****************************************************************************
 * $Log: KProgCstGnuc.h,v $
 * Revision 1.1  2012/01/26 16:22:37  ddarko
 * Extracted specific defintions from KProgCst.h
 *
 * Jan. 97 D. Kolakovic
 *****************************************************************************/
