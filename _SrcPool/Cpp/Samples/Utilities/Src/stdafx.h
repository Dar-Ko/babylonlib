/*$Workfile: stdafx.h$: header file
  $Revision: 1$  $Date: 2005-05-16 14:28:55$

  STandarD Application FrameworX
  header file includes standard system header files, or project specific header
  files that are used frequently, but are changed infrequently.
*/


#if !defined(_UTILITIES_STDAFX_H_)
  /*$Workfile: stdafx.h$ sentry */
  #define _UTILITIES_STDAFX_H_ 21032

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

//////////////////////////////////////////////////////////////////////////////
//Common header files
#include "Common/Src/Win/stdafx.h"
#if defined (_USE_STL) && !defined(_USE_MFC)
  #pragma message( "Using STL string substitute for CString" )
  #include "STL/KTString.h"
  class CString: public tstring
  {
  public:
    void Empty()
      {
      tstring::erase();
      };
    const CString& operator=(LPTSTR lpsz)
      {
      tstring::operator=(lpsz);
      return *this;
      }
    operator LPCTSTR() const
      {
      return c_str();
      }

  };
#endif

///////////////////////////////////////////////////////////////////////////////
#endif // !defined(_UTILITIES_STDAFX_H_)
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2005-05-16 14:28:55  Darko Kolakovic 
 * $
 *****************************************************************************/
