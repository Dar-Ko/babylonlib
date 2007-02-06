/*$Workfile: KFileShortcut.h$: header file
  $Revision: 2$ $Date: 2005-05-11 16:39:32$
  $Author: Darko Kolakovic$

  Windows Shortcut (.Lnk) files helpers
  Copyright: CommonSoft Inc.
  Dec 98 Darko Kolakovic
 */

#ifndef _KFILESHORTCUT_H_
  //$Workfile: KFileShortcut.h$ sentry
  #define _KFILESHORTCUT_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef _WINNT_ /*winnt.h sentry*/
  #include "KTChar.h" //LPCTSTR
#endif

  //File extension for the Window's shortcuts (.lnk)
const LPCTSTR g_szExtLnk = _T(".lnk");

///////////////////////////////////////////////////////////////////////////////
// Inlines

//IsShortcut()-----------------------------------------------------------------
/*Validates if a file name has extension '.lnk'.

  Returns: true if file name have extension same as Window's shortcut file (.lnk).
 */
inline bool IsShortcut(LPCTSTR szFileName //[in] zero-terminated string with 
                                          //file name
                      )
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
      return true;
    }
  }
return false;
}
///////////////////////////////////////////////////////////////////////////////
#endif //_KFILESHORTCUT_H_

/******************************************************************************
 *$Log: 
 * 2    Biblioteka1.1         2005-05-11 16:39:32  Darko Kolakovic Replaced BOOL
 *      with bool
 * 1    Biblioteka1.0         2002-03-12 22:01:12  Darko           
 *$
 * 0    Dec 98 Darko Kolakovic
 *****************************************************************************/
