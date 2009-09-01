/*$RCSfile: MFC40Prp.h,v $: header file
  $Revision: 1.2 $ $Date: 2009/09/01 15:11:50 $
  $Author: ddarko $

  Fix: Creating CPropertySheet objects (MFC4.0)
  Darko Kolakovic
  March 98
 */
// Group=Windows
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
  BOOL MFC40PropSheetCreate(CPropertySheet* pSheet,
                            CWnd* pParentWnd,
                            DWORD dwStyle,
                            DWORD dwExStyle);
#endif //_MFC40

///////////////////////////////////////////////////////////////////////////////
#endif //_MFC40_PROPSH_H_
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: MFC40Prp.h,v $
 * Revision 1.2  2009/09/01 15:11:50  ddarko
 * Reformatted
 *
 *****************************************************************************/

