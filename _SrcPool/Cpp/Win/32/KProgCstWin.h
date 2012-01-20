/*$RCSfile: KProgCstWin.h,v $: header file
  $Revision: 1.1 $ $Date: 2012/01/20 21:04:17 $
  $Author: ddarko $

  Constants used in conjuncture with Windows environment
  Copyright: D. Kolakovic
  2012-01-17
 */

#ifndef __KPROGCSTWIN_H__
  /*$RCSfile: KProgCstWin.h,v $ sentry */
  #define __KPROGCSTWIN_H__

  #ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files*/
    #pragma message ("   #include " __FILE__ )
  #endif

  #ifndef _KWINDOWS
     /*Mark legacy code with this block*/
    #if defined (DOS) || (MSDOS) || (_MSDOS)
      #define _KWINDOWS  1  /*16-bit DOS target*/
    #endif
  #endif  
   
  #ifndef _KWINDOWS
    #if defined(WIN16) || defined(_WINDOWS) || defined(_WIN95)
      /*Defined when target OS is Microsoft Windows. */
      #define _KWINDOWS  16
    #elif defined(_WINNT) || defined(_WIN32)
      #define _KWINDOWS  32
    #elif defined(_WIN64)
      #define _KWINDOWS  64
    #endif
  #endif //!_KWINDOWS
  
  #ifdef _KWINDOWS /*Microsoft Windows OS family*/
  
  #ifndef _WINBASE_
    #include <winbase.h> //32-Bit Windows Base API, INVALID_HANDLE_VALUE
  #endif

  /*/////////////////////////////////////////////////////////////////////////*/
  /* Global macros                                                           */

  #ifndef IS_HANDLE_VALID
    /*Validates a handle to an object.
      See also: HANDLE, winnt.h, INVALID_HANDLE_VALUE, winbase.h
     */
    #define IS_HANDLE_VALID(handle)  (((HANDLE)handle) != INVALID_HANDLE_VALUE)
  #endif

  /* /////////////////////////////////////////////////////////////////////// */
  #endif /*_KWINDOWS */
#endif  /*__KPROGCSTWIN_H__*/
/*****************************************************************************
 * $Log: KProgCstWin.h,v $
 * Revision 1.1  2012/01/20 21:04:17  ddarko
 * Created
 *
 *****************************************************************************/
