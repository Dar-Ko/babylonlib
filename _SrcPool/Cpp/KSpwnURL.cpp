/*$Workfile: KSpwnURL.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:38:42 $
  $Author: ddarko $

  Opens a hyperlink
  Copyright: CommonSoft Inc.
  Mar 99 Darko Kolakovic
 */ 

#ifndef __AFXWIN_H__
  #include <AfxWin.h>
#endif
#pragma hdrstop

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KRegExt.h"  //CRegExt class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

  //File extension for the HTML (HyperText Markup Language) documents
TCHAR g_szExtHTM[] = _T(".htm");

//SpawnURL()------------------------------------------------------------------
/*Function creates and executes a new process designated to open a hyperlink.
  Usually the application associated with HTML documents is responsibile for
  hyperlinks. Function searches Windows registry to find the application name.
  The destination of the hyperlink is encoded as a URL.  A Uniform Resource
  Locator (URL) gives the location of a file on the World Wide Web and also
  identifies the Internet service, such as FTP or the World Wide Web, that will
  handle the file.
  If the function succeeds, the return value is the instance handle of the
  application that was run, or the handle of a dynamic data exchange (DDE)
  server application. If the function fails, the return value is an error
  value that is less than or equal to 32. The following table lists these
  error values:

    0	                    The system is out of memory or resources.
    ERROR_BAD_FORMAT	    The .EXE file is invalid (non-Win32 .EXE or error
                          in .EXE image).
    ERROR_FILE_NOT_FOUND	The specified file was not found.
    ERROR_PATH_NOT_FOUND	The specified path was not found.

  See also: CRegExt::GetAssociatedExecutable().

  Note: Microsoft Windows specific (Win). 

  Example:
    {
      //View a URL
    SpawnURL(_T("http://www.AnySite.com/"),SW_SHOWNORMAL);
      //Send a message
    SpawnURL(_T("mailto:Support@AnySite.com?Subject=Help me!"),SW_SHOW);
      //Get a document from a FTP server
    SpawnURL(_T("ftp://ftp.AnySite.com/Help.txt"),SW_SHOW);
      //Get a file from a local computer
    SpawnURL(_T("file:///Dir/File.doc"),SW_SHOW);
      //Send a message
    SpawnURL(_T("telnet://www.AnySite.com:1234"),SW_SHOW);
      //Open a socket
    SpawnURL(_T("socket://127.0.0.1:854"),SW_SHOW);
    }
*/
HINSTANCE SpawnURL(LPCTSTR szURL, //a Uniform Resource Locator (URL)
                  int nCmdShow   //specifies how the application is to
                                 //be shown when it is opened
                 )
{
TRACE1(_T("SpawnURL( %s )\n"),szURL);
  //First try ShellExecute()
HINSTANCE hInst = ShellExecute(NULL, _T("open"), szURL, NULL,NULL, nCmdShow);
  //If it failed, get the .htm regkey and lookup the program
if ((UINT)hInst <= HINSTANCE_ERROR)
  {
  CString strHTMLViewer = CRegExt::GetAssociatedExecutable(g_szExtHTM);
  if (!strHTMLViewer.IsEmpty())
    {
    TRACE1(_T("\twith %s\n"),strHTMLViewer);

    strHTMLViewer += _T(" ");
    strHTMLViewer += szURL;
    hInst = (HINSTANCE) WinExec(strHTMLViewer,nCmdShow);
    }
  }

return hInst;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         29/01/2002 10:21:52 PMDarko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         25/01/2002 3:57:54 PMDarko           Updated
 *       comments
 *  4    Biblioteka1.3         16/08/2001 11:38:03 PMDarko           Update
 *  3    Biblioteka1.2         07/07/2001 12:11:45 AMDarko           Note
 *  2    Biblioteka1.1         08/06/2001 10:51:43 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 2:59:02 PMDarko           
 * $
 *****************************************************************************/
