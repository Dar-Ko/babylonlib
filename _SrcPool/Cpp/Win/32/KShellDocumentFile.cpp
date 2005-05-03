/*$Workfile: KShellDocumentFile.cpp$: implementation file
  $Revision: 2$ $Date: 2004-10-01 22:35:20$
  $Author: Darko$

  Opens a document file using Shell
  Copyright: CommonSoft Inc.
  2003-08-09 Darko Kolakovic
 */
#include "stdafx.h"

//-----------------------------------------------------------------------------
/*Opens a document file using Shell.

  Returns: true if successful, or false otherwise. Call GetLastError() for error
  information.

  Note: Microsoft Windows specific (Win).
 */
bool ShellDocumentFile(LPCTSTR szFileName, //[in]
                      HWND hWnd = NULL//[in]=NULL owner to any message boxes
                      //that the system might produce while executing this function. 
                        )
{
if(szFileName != NULL)
  {
  SHELLEXECUTEINFO seiInfo;
  memset(&seiInfo, 0, sizeof(seiInfo));//Erase memory block
  seiInfo.cbSize = sizeof(seiInfo);  //Size of the structure, in bytes. 
  seiInfo.hwnd   = hWnd;             //owner's handle
  seiInfo.lpVerb = _T("open");       //Open the file with default program
  seiInfo.lpFile = szFileName;       //File to open
  seiInfo.nShow = SW_NORMAL;         //Open in normal window
  seiInfo.fMask = SEE_MASK_NOCLOSEPROCESS; //Wait for spawned process
  return (ShellExecuteEx(&seiInfo) == TRUE);     // Call to function
  }
return false;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-10-01 22:35:20  Darko           stdafx.h
 *  1    Biblioteka1.0         2003-08-14 13:54:44  Darko           
 * $
 *****************************************************************************/
