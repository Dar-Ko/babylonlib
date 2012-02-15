/*$RCSfile: MFC80AfxAssume.h,v $: header file
  $Revision: 1.1 $ $Date: 2012/02/15 16:57:54 $
  $Author: ddarko $

  Fix: AFXASSUME for MSVS 2005 (MSVC8, MFC 8.0) generates compiler warning C4189
  Copyright: naughter
  http://naughter.spaces.live.com/blog/cns!7692E6D72E26EAC!534.entry
 */

#ifndef _KMFC80AFXASSUME_H_
  //$RCSfile: MFC80AfxAssume.h,v $ sentry
  #define _KMFC80AFXASSUME_H_
// Group=Windows

#if defined(_MSC_VER) && (_MSC_VER < 1500)
/*Microsoft Visual C++ .Net 2005, 32-bit, version 8.0 and lesser*/

  #ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
    #pragma message ("   #include " __FILE__ )
  #endif

  #ifdef AFXASSUME 
    #if defined(_PREFAST_) || defined (_DEBUG)
      #undef AFXASSUME
      //Fixing compiler warning "C4189: '__afx_condVal' : local variable is initialized but not referenced".
      #define AFXASSUME(cond)  do { bool __afx_condVal=!!(cond);\
                                  ASSERT(__afx_condVal);\
                                  __analysis_assume(__afx_condVal);\
                                  } while(0) 
    #else
      #undef AFXASSUME
      #define AFXASSUME(cond) ((void)0)
    #endif
  #endif
  
#endif /*_MSC_VER*/
///////////////////////////////////////////////////////////////////////////////
#endif  /*_KMFC80AFXASSUME_H_*/
/*****************************************************************************
 * $Log: MFC80AfxAssume.h,v $
 * Revision 1.1  2012/02/15 16:57:54  ddarko
 * Created
 *
 *****************************************************************************/
