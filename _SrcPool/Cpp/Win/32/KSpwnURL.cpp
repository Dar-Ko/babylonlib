/*$Workfile: KSpwnURL.cpp$: implementation file
  $Revision: 9$ $Date: 2004-10-01 22:35:27$
  $Author: Darko$

  Opens a hyperlink
  Copyright: CommonSoft Inc.
  Mar 99 Darko Kolakovic
 */ 

#ifndef __AFXWIN_H__
  #include <AfxWin.h>
#endif
#pragma hdrstop

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KRegExt.h"  //CRegExt class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

  //File extension for the HTML (HyperText Markup Language) documents
TCHAR g_szExtHTM[] = _T(".htm");

#ifdef _WIN32
    //Validates result of ShellExecute. Returns false if result is an error code.
  #define _FAILED_SHELLEXECUTE(x) (x <= ((HINSTANCE)SE_ERR_DLLNOTFOUND))
#else //Win 16-bit
    //Validates result of ShellExecute. Returns false if result is an error code.
    //
    //Note: Microsoft Windows 16b specific (Win16).
  #define _FAILED_SHELLEXECUTE(x) (x <= HINSTANCE_ERROR)
#endif

//SpawnURL()------------------------------------------------------------------
/*Function creates and executes a new process designated to open a hyperlink.
  Usually the application associated with HTML documents is responsibile for
  hyperlinks. Function searches Windows registry to find the application name.
  The hyperlink reference is a Uniform Resource Locator string.
  The Uniform Resource Locators (URLs) are formatted strings or streams 
  that an Internet application can use to reference resources on the Internet
  or an intranet.

  Returns: If the function fails, the return value is an error code
  that is less than or equal to SE_ERR_DLLNOTFOUND = 32. The following table
  lists these error values:

     0                        The system is out of memory or resources.
     2 ERROR_BAD_FORMAT       The .EXE file is invalid (non-Win32 .EXE or error
                              in .EXE image).
     3 ERROR_FILE_NOT_FOUND   The specified file was not found.
     2 SE_ERR_FNF             The specified file was not found.
     3 SE_ERR_PNF             The specified path was not found.
     5 SE_ERR_ACCESSDENIED    The operating system denied access to the specified
                              file.
     8 SE_ERR_OOM             There was not enough memory to complete the operation.
    11 ERROR_BAD_FORMAT       The .EXE file is invalid (non-Win32 .EXE or error in 
                              .EXE image).
    26 SE_ERR_SHARE           A sharing violation occurred.
    27 SE_ERR_ASSOCINCOMPLETE The filename association is incomplete or invalid.
    28 SE_ERR_DDETIMEOUT      The DDE transaction could not be completed because
                              the request timed out.
    29 SE_ERR_DDEFAIL         The DDE transaction failed.
    30 SE_ERR_DDEBUSY         The DDE transaction could not be completed because
                              other DDE transactions were being processed.
    31 SE_ERR_NOASSOC         There is no application associated with the given
                              filename extension.
    32 SE_ERR_DLLNOTFOUND     The specified dynamic-link library was not found.

  URL string has following form:
  
    protocol:resource

    where protocol  specifies the means of accessing the object, 
                    such as HTTP or FTP;
          resource     is a string passed to the protocol handler.

  Resource in case of HTTP or FTP has following form:

      //host/localinfo

      where host      specifies the remote location where the object resides and 
            localinfo is a string, often a file name at the remote location.

  TODO: Test localinfo cases with space characters ("My Documents/Index.html"); 
  Workaround: replace spaces with '%20' escapes D.K.

  Note: Under WinNT "mailto" Uniform Resource Locator (URL) with a recipient list
  that exceeds 260 bytes is truncated. See Q269272: Mail Client Address List 
  Truncated Using "Mailto:" Link If Tag Exceeds 260 Characters

  Example:
    {
      //View a URL
    SpawnURL(_T("http://www.AnySite.com/"),SW_SHOWNORMAL);
      //Send a message
    SpawnURL(_T("mailto:Support@AnySite.com?Subject=Help me!&Body=Message"),SW_SHOW);
      //Get a document from a FTP server
    SpawnURL(_T("ftp://ftp.AnySite.com/Help.txt"),SW_SHOW);
      //Get a file from a local computer
    SpawnURL(_T("file:///Dir/File.doc"),SW_SHOW);
      //Send a message
    SpawnURL(_T("telnet://www.AnySite.com:1234"),SW_SHOW);
      //Open a socket
    SpawnURL(_T("socket://127.0.0.1:854"),SW_SHOW);
    }

  See also: CRegExt::GetAssociatedExecutable(), ShellExecute(), ShellAPI.h

  Note: Microsoft Windows specific (Win).
*/
int SpawnURL(LPCTSTR szURL, //[in] Uniform Resource Locator (URL)
             int nCmdShow   //[in] specifies how the application is to
                            //be shown when it is opened
            )
{
TRACE1("SpawnURL( %s )\n",szURL);
  //First try ShellExecute()
HINSTANCE hInst = ShellExecute(NULL, _T("open"), szURL, NULL, NULL, nCmdShow);
  /*Note: ShellExecute returns a value greater than 32 if successful, or an error
    value that is less than or equal to 32 otherwise. The following table lists 
    the error values. The return value is cast as an HINSTANCE for backward 
    compatibility with 16-bit Windows applications. It is not a true HINSTANCE,
    however. The only thing that can be done with the returned HINSTANCE is to 
    cast it to an int and compare it with the value 32 or one of the error codes.

    Under Win32s, use SW_NORMAL instead of SW_SHOWDEFAULT when using ShellExecute()
    with a 16-bit Windows-based application. You can use SW_SHOWDEFAULT if the 
    application specified is a Win32-based application. 
    (Q124133: PRB: ShellExecute() Succeeds But App Window Doesn't Appear)
  */

int iErr = 0xFFFF; //Success code > 32
  //If it failed, get the <.htm> registry key and lookup the program
if (_FAILED_SHELLEXECUTE(hInst))
  {
  CString strApplication = CRegExt::GetAssociatedExecutable(g_szExtHTM);
  if (!strApplication.IsEmpty())
    {
    TRACE1("\twith %s\n",strApplication);
    strApplication += _T(" ");
    strApplication += szURL;
    #ifndef _WIN32_WINDOWS
      //Win95 version (!WIN32_WINDOWS && (WINVER == 0x0400))
      iErr = WinExec((LPCTSTR)strApplication, nCmdShow);

      if (iErr > 31)
        iErr = 0xFFFF; //Success code > 32
    #else
      //Use CreateProcess rather than WinExec in Win2k+ D.K.
      STARTUPINFO si;
      PROCESS_INFORMATION pi;

      ZeroMemory( &si, sizeof(si) );
      si.cb = sizeof(si);
      ZeroMemory( &pi, sizeof(pi) );
      //TODO: call CreateProcess(NULL, "\"C:\\Program Files\\MyApp.exe\" -L -S", ...) in order to increase security D.K.

      //Start the child process. 
      if( CreateProcess( NULL, // No module name (use command line). 
          const_cast<LPTSTR>(static_cast<LPCTSTR>(strApplication)),   // Command line. 
          NULL,             // Process handle not inheritable. 
          NULL,             // Thread handle not inheritable. 
          FALSE,            // Set handle inheritance to FALSE. 
          0,                // No creation flags. 
          NULL,             // Use parent's environment block. 
          NULL,             // Use parent's starting directory. 
          &si,              // Pointer to STARTUPINFO structure.
          &pi )             // Pointer to PROCESS_INFORMATION structure.
        ) 
        {
        iErr = 0xFFFF; //Success code > 32
        }
      else
        iErr = (int)GetLastError();
    #endif
    }
  }

return iErr;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  9    Biblioteka1.8         2004-10-01 22:35:27  Darko           stdafx.h
 *  8    Biblioteka1.7         2003-11-03 13:22:28  Darko           Returns
 *       GetLasteError() code in sae of a failure
 *  7    Biblioteka1.6         2003-08-06 03:46:42  Darko           Prepared for
 *       Unicode 
 *  6    Biblioteka1.5         2002-01-29 23:21:52  Darko           Used library
 *       notes 
 *  5    Biblioteka1.4         2002-01-25 16:57:54  Darko           Updated
 *       comments
 *  4    Biblioteka1.3         2001-08-17 00:38:03  Darko           Update
 *  3    Biblioteka1.2         2001-07-07 01:11:45  Darko           Note
 *  2    Biblioteka1.1         2001-06-08 23:51:43  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:59:02  Darko           
 * $
 *****************************************************************************/
