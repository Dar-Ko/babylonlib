/*$RCSfile: KProgCstLin.h,v $: header file
  $Revision: 1.5 $ $Date: 2012/03/06 21:14:15 $
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
      /*Defined when target OS is Linux. */
      #define _KLINUX  1
    #endif
  #endif  /*_KLINUX*/
   
  #ifdef _KLINUX /*Linux OS family*/
  /*/////////////////////////////////////////////////////////////////////////*/
  /* Global macros                                                           */

  #ifndef NULL
    /*Null-pointer value equivalent to 0 used with pointer operations. */
    #define NULL    (0)
  #endif
  #ifndef FALSE
    #define FALSE   (0)
  #endif
  #ifndef TRUE
    #define TRUE    (1)
  #endif

  #ifndef min
    #define min(x,y) ((x) < (y) ? (x) : (y))
  #endif
  #ifndef max
    #define max(x,y) ((x) < (y) ? (y) : (x))
  #endif

  #ifndef INVALID_HANDLE_VALUE
    /*Invalid value of the handle to an object.     */
    #define INVALID_HANDLE_VALUE ((int)-1)
  #endif
  #ifndef IS_HANDLE_VALID
    /*Validates a handle to an object.     */
    #define IS_HANDLE_VALID(handle)  ((int)handle > 0)
  #endif
  
  #ifndef FillMemory
    #define FillMemory(dest, count, fill)    memset((dest),(fill),(count))
  #endif
  #ifndef ZeroMemory
    #define ZeroMemory(dest, count)          memset((dest), 0, (count))
  #endif

  #ifndef Sleep
     /*Suspends the execution of the current thread for at least the specified
       period given in ms.*/
     #define Sleep(ms) usleep(ms*1000)
  #endif
  
  /* /////////////////////////////////////////////////////////////////////// */
  #endif //_KLINUX
#endif  /*__KPROGCSTLIN_H__*/
/*****************************************************************************
 * $Log: KProgCstLin.h,v $
 * Revision 1.5  2012/03/06 21:14:15  ddarko
 * Sleep(ms)
 *
 * Revision 1.4  2012/03/06 20:20:21  ddarko
 * Added new defines
 *
 * Revision 1.3  2012/01/20 22:08:56  ddarko
 * INVALID_HANDLE_VALUE
 *
 * Revision 1.2  2012/01/20 21:03:45  ddarko
 * *** empty log message ***
 *
 * Revision 1.1  2012/01/20 21:01:45  ddarko
 * Created
 *
 *****************************************************************************/
