/*$Workfile: KDirName.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  Get file directory from the full file path
  Copyright: CommonSoft Inc.
  Darko Kolakovic Jan 98
*/

#ifndef __AFXWIN_H__
  #include "KTypedef.h"
  #include "KTchar.h"  //_tcsinc()
  #define AFXAPI
#endif

#include "KFileSys.h" //IS_FILENAME_DELIM

//GetFileDirectory()-----------------------------------------------------------
/*Extracts the path given a full pathname.
  Characters "\", "/" and ":" are used as directory and drive separators.

  Returns: length of the directory name, and directory name itself, if string
  buffer has been given.

  Note: Microsoft DOS, Windows specific (Win and DOS).

  Example:
      //Get path of the current module
    TCHAR szBuff[_MAX_PATH];
    VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), szBuff, _MAX_PATH));
    GetFileDirectory(szBuff,szBuff,_MAX_PATH);
    TRACE1("Directory is %s\n",szBuff);
*/
UINT AFXAPI GetFileDirectory(LPTSTR szPathName, //[in] fully qualified file name
                             LPTSTR szDirectory, //[in/out] buffer where result is copied or NULL
                             UINT nDirSize //[in] buffer size in characters
                                           //(wide charecters for Unicode version)
                             )
{
#ifdef __AFXWIN_H__
  //Note: uses Microsoft Fundation Library (MFC).
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
  if (IS_FILENAME_DELIM(*lpsz))
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
 *  6    Biblioteka1.5         8/27/02 11:37:03 PM  Darko           Fixed Unicode
 *       version
 *  5    Biblioteka1.4         1/29/02 3:39:17 PM   Darko           Tag update
 *  4    Biblioteka1.3         8/19/01 11:53:08 PM  Darko           Butyfier
 *  3    Biblioteka1.2         7/11/01 10:50:51 PM  Darko           
 *  2    Biblioteka1.1         6/8/01 11:50:13 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 3:56:05 PM   Darko           
 * $
 *****************************************************************************/
