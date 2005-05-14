/*$Workfile: KFileShortcut.cpp$: implementation file
  $Revision: 3$ $Date: 2005-05-11 17:39:09$
  $Author: Darko Kolakovic$

  Windows Shortcut (.lnk) files helper
  Copyright: CommonSoft Inc.
  Dec 98 Darko Kolakovic
 */
/* Group=Windows */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifdef WIN32 //Microsoft Win32 platform dependant

  #pragma warning (disable : 4201)  //nonstandard extension used : nameless struct/union

  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
  #include <shlobj.h>
  #pragma warning (default : 4201)
  #include <malloc.h> //_alloca()
  #pragma hdrstop()
  #include "KFileShortcut.h"  //IsShortcut()

//GetShortcutTarget()----------------------------------------------------------
/*Obatins a file name shortcut is linked with. A shortcut (also called a shell
  link) is a data object that contains information used to access another object
  in the system, such as a file, folder, disk drive, or printer.

  Returns: TRUE if function is successful, target file name and target file name
  size (including terminating zero). If address of the target buffer is same as
  address of the shorcut name string, the resulting target path will be copied
  to the string.

  See also: MSDN article Q128932.

  Note: Microsoft Windows specific (Win).

  Example:

      void Example1()
        {
        ...
        LPCTSTR szSource = _T("AnyShortcut.lnk");
        size_t nSize = 0;
          //Get target string size
        if (GetShortcutTarget(szSource,NULL,nSize))
          {
          LPTSTR szBuff = new TCHAR [nSize];
          if (szBuff != NULL)
            {
            GetShortcutTarget(szSource,szBuff,nSize);
            TRACE1("Shortcut to %s\n",szBuff);
            delete [] szBuff;
            }
          }

        }

      void CExample2::OnDropFiles(HDROP hDropInfo)
        {
        TCHAR szFile [MAX_PATH];
        DragQueryFile(hDropInfo,nIndex,lpszFile,sizeof(szFile));
        if(IsShortcut(szFile))
          {
          size_t nSize = sizeof(lpszFile);
            //Resolve shortcut link
          GetShortcutTarget(lpszFile,lpszFile,nSize);
          TRACE2("Shortcut to %s is long %d chars.\n",lpszFile,nSize);
          }
        DragFinish (hDropInfo);
        }
 */
bool GetShortcutTarget(LPCTSTR  szShortcutName, //[in] the shortcut file name
                       LPTSTR   szTargetName,   //[in] target buffer
                       size_t&  nTargetSize     //[in/out] target buffer size and
                                                //as result target name lenght
                      )
{
bool bResult = false;
int iLen = 0; //Actual target's name length
if (IsShortcut(szShortcutName))
  {
  HRESULT hResult = NULL;
  hResult = CoInitialize(NULL); //Initialize the Component Object Model(COM) library
    //Create a single uninitialized object of shell link interface
  if (SUCCEEDED(hResult))
    {
    IShellLink*    pShellLink = NULL;
    hResult = CoCreateInstance( CLSID_ShellLink,       //Class identifier
                                NULL,                  //Object isn't part of an aggregate
                                CLSCTX_INPROC_SERVER,  //Context for running executable code
                                IID_IShellLink,        //Interface identifier
                                (LPVOID*) &pShellLink);//Pointer to storage of interface pointer
      //Get a pointer to a specified persist file interface
    if (SUCCEEDED(hResult))
      {
      IPersistFile*  pPersistFile = NULL;
      hResult = pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*) &pPersistFile);
        //Load a linked component object in a shortcut file.
      if (SUCCEEDED(hResult))
        {
          //Convert shorcut file name into Unicode string
        LPCOLESTR olestrShortcutName;

        #ifdef UNICODE
          olestrShortcutName = szShortcutName;
        #else
          iLen = lstrlen(szShortcutName) + 1;
            //Allocate a buffer on the stack
          olestrShortcutName = (LPOLESTR)_alloca(iLen * sizeof(OLECHAR));
          MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szShortcutName,
                              iLen, (LPOLESTR)olestrShortcutName, iLen);
          iLen = 0; //Set old value
        #endif //UNICODE

          //Load the persist shortcut file
        hResult = pPersistFile->Load(olestrShortcutName, 0);
          //Retrieve the path associated with the shortcut object and search
          //for the object in that path
        if (SUCCEEDED(hResult))
          {
            //If the shell link	cannot be resolved, do not display a dialog box
          hResult = pShellLink->Resolve(NULL, SLR_NO_UI);
          if (SUCCEEDED(hResult))
            {
            TCHAR szTargetPath[MAX_PATH];
            WIN32_FIND_DATA fd;
            szTargetPath[0] = fd.cFileName[0] = _T('\0');
              //Get target's path
            hResult = pShellLink->GetPath(szTargetPath,
                                          sizeof(szTargetPath)/sizeof(szTargetPath[0]),
                                          &fd,
                                          0);
              //Copy target's path to the result buffer
            if (hResult == NOERROR)
              {
              iLen = lstrlen(szTargetPath) + 1;
              if (szTargetName != NULL)
                lstrcpyn(szTargetName,szTargetPath,nTargetSize);
              bResult = true;
              }
            }
          }
        pPersistFile->Release();
        }
      pShellLink->Release();
      }
    CoUninitialize();
    }
  }
nTargetSize = iLen;//Return target's name actual length
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
#endif //WIN32
/******************************************************************************
 *$Log:
 * 2    Biblioteka1.1         2002-07-16 01:41:03  Darko           Fixed VSS Log
 *      tag
 * 1    Biblioteka1.0         2002-03-12 23:01:06  Darko
 *$
 * 0    Dec 98 Darko Kolakovic
 *****************************************************************************/
