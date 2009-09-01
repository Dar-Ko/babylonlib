/*MFC40Prp.h
  Fix ups for the CPropertySheet

  Darko Kolakovic
  March 98
  */
#ifndef _MFC40_PROPSH_H_
  #define _MFC40_PROPSH_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#if _MFC_VER == 0x400
  #pragma message (__FILE__ " included fix from Q147206 - MFC 4.0")
  #define  _MFC40    //7.1.00 undefine Bug Fix in the MFC 4.0 D.K.
#endif

#if _MFC_VER == 0x600
  #pragma message (__FILE__ " - MFC 4.2")
  #undef  _MFC40
#endif

#ifdef _MFC40
  #include <AfxPriv.h>

  int CALLBACK  MFC40PropSheetCallback(HWND, UINT message, LPARAM lParam);
  BOOL MFC40PropSheetCreate(CPropertySheet* pSheet, CWnd* pParentWnd, DWORD dwStyle, DWORD dwExStyle);
#endif //_MFC40

///////////////////////////////////////////////////////////////////////////////
#endif //_MFC40_PROPSH_H_

