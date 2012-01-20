/*$RCSfile: KProgCstLin.h,v $: header file
  $Revision: 1.1 $ $Date: 2012/01/20 21:01:45 $
  $Author: ddarko $

  Constants used in conjuncture with Linux environment
  Copyright: D. Kolakovic
  2012-01-17
 */

#ifndef __KPROGCSTLIN_H__
  /*$RCSfile: KProgCstLin.h,v $ sentry */
  #define __KPROGCSTLIN_H__

  #ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files*/
    #warning ("   #include " __FILE__ )
  #endif

  #ifndef _KLINUX
    #if defined(linux) || defined(__linux) || defined(__linux__)
      /*Defined whan target OS is Linux. */
      #define _KLINUX  1
    #endif
  #endif  /!_KLINUX
   
  #ifdef _KLINUX /*Linux OS family*/
  /*/////////////////////////////////////////////////////////////////////////*/
  /* Global macros                                                           */

  #ifndef IS_HANDLE_VALID
    /*Validates a handle to an object.     */
    #define IS_HANDLE_VALID(handle)  ((int)handle > 0)
  #endif
  /* /////////////////////////////////////////////////////////////////////// */
  #endif //_KLINUX
#endif  /*__KPROGCSTLIN_H__*/
/*****************************************************************************
 * $Log: KProgCstLin.h,v $
 * Revision 1.1  2012/01/20 21:01:45  ddarko
 * Created
 *
 *****************************************************************************/
