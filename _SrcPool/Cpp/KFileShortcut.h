/*$Workfile: KFileShortcut.h$: header file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  Windows Shortcut (.Lnk) files helpers
  Copyright: CommonSoft Inc.
  Dec 98 Darko Kolakovic
 */

#ifndef _KFILESHORTCUT_H_
  //KFileShortcut.h sentry
  #define _KFILESHORTCUT_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "KTChar.h" //LPCTSTR

  //File extension for the Window's shortcuts
const LPCTSTR g_szExtLnk = _T(".lnk");

///////////////////////////////////////////////////////////////////////////////
// Inlines

//IsShortcut()-----------------------------------------------------------------
/*Returns TRUE if file name have extension same as Window's shortcut file (.Lnk).
 */
inline BOOL IsShortcut(LPCTSTR szFileName)
{
if (szFileName != NULL)
  {
    //Validate extension
  const LPCTSTR szExt = _tcsrchr(szFileName, _T('.'));    
  if (szExt != NULL)
    {
    if( (szExt[1] == g_szExtLnk[1]) &&
        (szExt[2] == g_szExtLnk[2]) &&
        (szExt[3] == g_szExtLnk[3]) )
      return TRUE;
    }
  }
return FALSE;
}
///////////////////////////////////////////////////////////////////////////////
#endif //_KFILESHORTCUT_H_


