/*$RCSfile: KPackPop.h,v $: header file
  $Revision: 1.3 $ $Date: 2012/06/15 13:14:18 $
  $Author: ddarko $

  Restores packing alignment for structure, union, and class members.
  2007-02-01 Darko Kolakovic
 */

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif


#if !(defined(lint)
  #undef ALIGNDATA
  #define ALIGNDATA

  //////////////////////////////////////////////////////////////////////////////
  /*Restore previous packing alignment for structure, union and class members.
    An include file is needed because various compilers do this in different
    ways.

    Note: for Microsoft compatible compilers, this files uses the pop option
    to the pack pragma; include "KPackPsh.h" (see also <pshpack1.h>) to set
    the packing alignment.
   */
  #if defined(_MSC_VER)
    //Microsoft Visual C/C++ compiler
    #include <poppack.h>

  #elif defined (__GNUC__)
    /*GNU C Compiler.
     */
    #undef ALIGNDATA
    #define ALIGNDATA

    /*Note: For compatibility with Microsoft Windows compilers, GCC added support
      for a set of #pragma directives which change the maximum alignment of
      members of structures.
     */
    #pragma pack(pop)

  #elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
    #pragma pack()

  #elif defined (__ICCAVR32__)
    #pragma pack()

  #else
    #pragma pack()
  #endif
///////////////////////////////////////////////////////////////////////////////
#endif //lint
/******************************************************************************
 * $Log: KPackPop.h,v $
 * Revision 1.3  2012/06/15 13:14:18  ddarko
 * Update
 *
 * Revision 1.2  2009/08/05 19:22:46  ddarko
 * Updated
 *
 *****************************************************************************/
