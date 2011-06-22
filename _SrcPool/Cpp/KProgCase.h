/*$RCSfile: KProgCase.h,v $: header file
  $Revision: 1.1 $ $Date: 2011/06/22 20:41:31 $
  $Author: ddarko $

  switch statement helper
  Copyright: D. Kolakovic 2011-06-21
 */

#ifndef __KPROGCASE_H__
    /*$RCSfile: KProgCase.h,v $ sentry */
  #define __KPROGCASE_H__

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

  #ifdef _UNICODE
    /*Part of code that converts value of a name constant to the string.
      Requires szResult variable to be defined before usage.
      
      Example:
          ...
          LPTSTR szResult:
          switch(GetLasterror())
            {
            KCONSTCASE(ERROR_SUCCESS);
            KCONSTCASE(ERROR_FAILURE);
            defaut: szResult = _T("unknown");
            }
     */
    #define KCONSTCASE(saErr) \
      case saErr: szResult = L#saErr; break;
  #else //_SBCS
    /*Part of code that converts value of a name constant to the string.
      Requires szResult variable to be defined before usage.
      
      Example:
          ...
          LPTSTR szResult:
          switch(GetLasterror())
            {
            KCONSTCASE(ERROR_SUCCESS);
            KCONSTCASE(ERROR_FAILURE);
            defaut: szResult = _T("unknown");
            }
     */
    #define KCONSTCASE(saErr) \
      case saErr: szResult = #saErr; break;
  #endif //_UNICODE

/* ///////////////////////////////////////////////////////////////////////// */
#endif  /*__KPROGCASE_H__                                                     */
/*****************************************************************************
 * $Log: KProgCase.h,v $
 * Revision 1.1  2011/06/22 20:41:31  ddarko
 * Created
 *
 *****************************************************************************/
