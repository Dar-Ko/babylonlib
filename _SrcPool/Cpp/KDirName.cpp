/*$Workfile: KDirName.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:10:21 $
  $Author: ddarko $

  Get file directory from the full file path
  Copyright: CommonSoft Inc.
  Darko Kolakovic Jan 98
*/

//#include <AfxWin.h>

#ifndef __AFXWIN_H__
  #define AFXAPI
#endif

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
UINT AFXAPI GetFileDirectory(LPCTSTR lpszPathName,
                             LPTSTR lpszDir,
                             UINT nDirSize //Specifies the number bytes (ANSI version)
                                           //or characters (Unicode version)
                             )
{
#ifdef __AFXWIN_H__
  //Note: uses Microsoft Fundation Library (MFC).
  ASSERT(lpszDir == NULL ||	AfxIsValidAddress(lpszDir, nDirSize));
  ASSERT(AfxIsValidString(lpszPathName, FALSE));
#endif

	// always capture the complete file name including extension (if present)
LPTSTR lpszTemp = (LPTSTR)lpszPathName;
UINT nPos = 0;
UINT i;
LPCTSTR lpsz;
for (lpsz = lpszPathName, i = 0; *lpsz != '\0'; lpsz = _tcsinc(lpsz), i++)
  {
  //Remember last directory/drive separator
  if (*lpsz == _T('\\') || *lpsz == _T('/') || *lpsz == _T(':'))
    nPos = i + 1;
	}

  //Copy it into the buffer provided
if (lpszDir != NULL)
  {
  if (lpszPathName != lpszDir)
    lstrcpyn(lpszDir, lpszTemp, ((nDirSize < nPos) ? nDirSize: nPos));
  else
    lpszDir[nPos] = _T('\0');
  }
return nPos; //Return length of the directory string
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         1/29/02 2:39:17 PM   Darko           Tag update
 *  4    Biblioteka1.3         8/19/01 10:53:08 PM  Darko           Butyfier
 *  3    Biblioteka1.2         7/11/01 9:50:51 PM   Darko           
 *  2    Biblioteka1.1         6/8/01 10:50:13 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 2:56:05 PM   Darko           
 * $
 *****************************************************************************/
