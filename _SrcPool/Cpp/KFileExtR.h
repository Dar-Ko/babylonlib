/*$Workfile: KFileExtR.h$: header file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  CStdioFile class extension: I/O operators
  Copyright: CommonSoft Inc.
  May 98 Darko Kolakovic
  Dec 98 FILETIME comparasion D.K.
 */

#ifndef _KFILEEXTR_H_
    //KFileExtR.h sentry
  #define _KFILEEXTR_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef __AFX_H__
  #include <Afx.h> //CStdioFile class
#endif

#include "KFileTimeCm.h"  //FILETIME comparasion operators
///////////////////////////////////////////////////////////////////////////////
//Declarations
CStdioFile& AFXAPI operator<<(CStdioFile& fileDestination, LPCTSTR strSource);
CStdioFile& AFXAPI operator>>(CStdioFile& fileSource, CString& strDestination);
CStdioFile& AFXAPI operator<<(CStdioFile& fileDestination, TCHAR chSource);

///////////////////////////////////////////////////////////////////////////////
#endif //_KFILEEXTR_H_
