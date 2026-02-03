/*$RCSfile: KPackPsh.h,v $: header file
  $Revision: 1.2 $ $Date: 2009/08/05 19:22:46 $
  $Author: ddarko $

  Set packing alignment for structure, union, and class members.
  2007-02-01 Darko Kolakovic
 */

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#if !(defined(lint)
  #undef ALIGNDATA
  #define ALIGNDATA
  //////////////////////////////////////////////////////////////////////////////
  /*Set packing alignment for structure, union and class members on 1-byte
    boundaries.
    An include file is needed because various compilers do this in different
    ways.

    Note: for Microsoft compatible compilers, this files uses the push option
    to the pack pragma; include "KPackPop.h" (see also <poppack.h>) to restore
    the previous packing alignment.
   */
  #if defined(_MSC_VER)
    //Microsoft Visual C/C++ compiler
    #include <pshpack.h>

  #elif defined (__GNUC__)
    /*GNU C Compiler.
      Note: The GNU C compiler does not support the #pragma directives, like
      "#pragma pack". Instead this, use compiler's extension __attribute__.
     */
    #undef ALIGNDATA
    #define ALIGNDATA __attribute__((__packed__))
    #define PACK_STRUCT ALIGNDATA /*Synonym for ALIGNDATA */

    /*Note: For compatibility with Microsoft Windows compilers, GCC added support
      for a set of #pragma directives which change the maximum alignment of
      members of structures.
     */
    #pragma pack(1)

  #elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
    #pragma pack(1)

  #elif defined (__ICCAVR32__)
    #pragma pack(1)

  #else
    #error the structure members must be byte-aligned; use appropriate compiler directives
  #endif
///////////////////////////////////////////////////////////////////////////////
#endif //lint
/******************************************************************************
 * $Log: KPackPsh.h,v $
 * Revision 1.2  2009/08/05 19:22:46  ddarko
 * Updated
 *
 *****************************************************************************/
/*IBM C for AIX, V6.0 supports pragma pack
 */
