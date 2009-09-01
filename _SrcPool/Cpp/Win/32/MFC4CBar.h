/*MFC4CBar.h
  Fix up for the ControlBars

  Darko Kolakovic
  Aug.  2k
  */

#ifndef _MFC41_CTRLBAR_H_
  #define _MFC41_CTRLBAR_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif


#if _MFC_VER == 0x0400 || _MFC_VER == 0x0410
  #pragma message (__FILE__ " included fix from Q151446 - MFC 4.0, 4.1")

  void MFC41CleanUpControlBarState(CFrameWnd* pOwner, LPCTSTR szCtrlBar);
#else
  #define MFC41CleanUpControlBarState(pOwner,szCtrlBar)          ((void)0,(void)0)
#endif //MFC4.0, 4.1
  
  //Aug. 2k D.K. MFC4.2
void MFCLoadBarState(CFrameWnd* pFrameWnd, LPCTSTR lpszProfileName);
void MFCSetDockState(CFrameWnd* pOwnerFrame, CDockState& state);

///////////////////////////////////////////////////////////////////////////////
#endif //_MFC41_CTRLBAR_H_
