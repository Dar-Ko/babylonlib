/*$RCSfile: KProgCstMwcw.h,v $: header file
  $Revision: 1.1 $ $Date: 2012/10/30 02:30:11 $
  $Author: ddarko $

  Constants used in conjuncture with Metrowerks Code Warrior C/C++
  2012-10-30 D.K.
 */

#ifndef __KPROGCSTMWCW_H__
  /*$RCSfile: KProgCstMwcw.h,v $ sentry */
  #define __KPROGCSTMWCW_H__
#if defined(__MWERKS__)/* Metrowerks CodeWarrior Compiler                 */

  #ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files*/
    #warning ("   #include " __FILE__ )
  #endif


/*/////////////////////////////////////////////////////////////////////////*/
/* Global macros                                                           */

#ifndef UNUSED_ARG
//  #define UNUSED_ARG(param) do {/* null */} while (&param == 0)
//  #define UNUSED_ARG(param) param = *(&param);
  #if defined(__MWERKS__)
    /*Metrowerks Code Warrior*/
    #define UNUSED_ARG(param)    &(param)
  #endif
#endif /* UNUSED_ARG */


/*---------------------------------------------------------------------------*/
/*Metrowerks CodeWarrior Compiler                                            */
/*CPU specific endianess*/
#if __option (little_endian)
  /*Byte order, according to significance of bytes                         */
  #define _ENDIAN_ORDER_ _ENDIAN_LITTLE_
#else
  /*Byte order, according to significance of bytes                         */
  #define _ENDIAN_ORDER_ _ENDIAN_BIG_
#endif

#ifndef _ENDIAN_ORDER_
  #ifdef _MSL_LITTLE_ENDIAN
    #if (_MSL_LITTLE_ENDIAN == 1)
      #define _ENDIAN_ORDER_ _ENDIAN_LITTLE_
    #elif (_MSL_LITTLE_ENDIAN == 0)
      #define _ENDIAN_ORDER_ _ENDIAN_BIG_
    #else
      #pragma message ("_MSL_: Unknown Endian byte order.")
    #endif
  #endif /*_MSL_LITTLE_ENDIAN*/
#endif /*_ENDIAN_ORDER_*/

/* ///////////////////////////////////////////////////////////////////////// */
#endif /*__MWERKS__                                                          */
#endif  /*__KPROGCSTMWCW_H__*/
/*****************************************************************************
 * $Log: KProgCstMwcw.h,v $
 * Revision 1.1  2012/10/30 02:30:11  ddarko
 * Extracted specific definitions from KProgCst.h
 *****************************************************************************/
