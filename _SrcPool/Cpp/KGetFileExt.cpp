/*$Workfile: KGetFileExt.cpp$: implementation file
  $Revision: 3$ $Date: 2004-06-01 16:50:26$
  $Author: Darko$

  Copyright: CommonSoft Inc.
  2001-10 Darko Kolakovic
 */ 

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KTChar.h"  /*LPTSTR*/

//-----------------------------------------------------------------------------
/*Call this function to extract the file extension from a filename.
  For example, if the name of the file entered is DATA.TXT, GetFileExt returns
  "TXT". 

  Returns: pointer to extension part of the filename.
 */
LPTSTR GetFileExt(LPCTSTR szFileName//[in] zero-terminated string with filename
                  )
{
LPTSTR szFileExt = NULL; //Result

unsigned int nLen= (unsigned int)_tcslen(szFileName)-1;

  //Find las tfile extension separator character
for(unsigned int i = nLen; i >= 0; i--)
  {
  if(szFileName[i] == _T('.'))
    {
    szFileExt = (LPTSTR)&szFileName[i+1];
    break;
    }
  }
return szFileExt;

/*Note: Win specific implementation replaced D.K.
      CString GetFileExt(LPCTSTR szFileName) 
      {
      TCHAR szExt[_MAX_EXT];
      _tsplitpath(szFileName, NULL, NULL, NULL, szExt);
      return CString(&szExt[1]);
      }
 */
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2004-06-01 16:50:26  Darko           time sync
 *  2    Biblioteka1.1         2003-08-23 14:05:42  Darko           comment
 *  1    Biblioteka1.0         2003-08-19 15:13:20  Darko           
 * $
 *****************************************************************************/
