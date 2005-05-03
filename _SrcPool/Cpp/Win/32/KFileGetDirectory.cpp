/*$Workfile: KFileGetDirectory.cpp$: implementation file
  $Revision: 9$ $Date: 2005-04-26 11:29:48$
  $Author: Darko Kolakovic$

  Get file directory from the full file path
  Copyright: CommonSoft Inc.
  Darko Kolakovic Jan 98
*/

#ifndef __AFXWIN_H__
  #include "KTypedef.h"
  #include "KTchar.h"  //_tcsinc()
  #define AFXAPI
#endif

#include "KFileSys.h" //IS_FILENAME_DELIM_WIN macro

//GetFileDirectory()-----------------------------------------------------------
/*Extracts the path given a full pathname.
  Characters "\", "/" and ":" are used as directory and drive separators.

  Returns: length of the directory name, and directory name itself, if string
  buffer has been given.

  Note: Microsoft DOS specific (DOS),
        Microsoft Windows specific (Win).

  Example:
      //Get path of the current module
    TCHAR szBuff[_MAX_PATH];
    VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), szBuff, _MAX_PATH));
    GetFileDirectory(szBuff,szBuff,_MAX_PATH);
    TRACE1("Directory is %s\n",szBuff);
 */
UINT AFXAPI GetFileDirectory(LPTSTR szPathName, //[in] fully qualified file name
                             LPTSTR szDirectory,//[in/out] buffer where result
                                                //is copied or NULL
                             UINT nDirSize //[in] buffer size in characters
                                           //(wide charecters for Unicode version)
                             )
{
#ifdef __AFXWIN_H__
  //Note: uses Microsoft Foundation Library (MFC).
  ASSERT(szDirectory == NULL || AfxIsValidAddress(szDirectory, nDirSize));
  ASSERT(AfxIsValidString(szPathName, FALSE));
#endif

  //Obtain fully qualified file name
LPTSTR lpszTemp = (LPTSTR)szPathName;
UINT nPos = 0;
UINT i;
LPCTSTR lpsz;
for (lpsz = szPathName, i = 0; *lpsz != _T('\0'); lpsz = _tcsinc(lpsz), i++)
  {
  //Remember last directory or drive separator
  if (IS_FILENAME_DELIM_WIN(*lpsz))
    nPos = i + 1;
  }

  //Copy it into the buffer provided
if (szDirectory != NULL)
  {
  if (szPathName != szDirectory)
    lstrcpyn(szDirectory, lpszTemp, ((nDirSize < nPos) ? nDirSize: nPos));
  else
    szDirectory[nPos] = _T('\0');
  }
return nPos; //Return length of the directory string
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  6    Biblioteka1.5         2002-08-27 23:37:03  Darko           Fixed Unicode
 *       version
 *  5    Biblioteka1.4         2002-01-29 15:39:17  Darko           Tag update
 *  4    Biblioteka1.3         2001-08-19 23:53:08  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 22:50:51  Darko
 *  2    Biblioteka1.1         2001-06-08 23:50:13  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:56:05  Darko
 * $
 *****************************************************************************/
