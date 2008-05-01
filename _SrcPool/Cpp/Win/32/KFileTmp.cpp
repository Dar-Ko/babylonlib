/*$Workfile: KFileTmp.cpp$: implementation file
  $Revision: 8$ $Date: 2007-05-04 17:52:20$
  $Author: Darko Kolakovic$

  Creates temporary file
  CommonSoft Inc.
  Jun 98 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#ifdef WIN32 //Microsoft Win32 platform dependant

#ifdef _AFXDLL
  //MSVC and MFC
  #include <afxwin.h>
#else          //use MS SDK
  #include <windows.h>
  #ifndef TRACE0
    #ifndef _T
      #include "KTChar.h"
    #endif
    #include "KTrace.h" //Debugging macros
  #endif
  #ifdef _STL
    #include <string> //base string class
  #endif
  #include "KString.h" //CString class
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Creates an empty temporary file with unique name in the following form:
      X:\TempDir\PPP12345.tmp
  in the directory designated as temporary directory by the TMP or TEMP
  environment variable. PPP is a prefix string with maximum length of 3
  characters. If strPrefix is NULL, the default prefix '~Pr' is used.

  Returns: NULL if function is not succesful, otherwise returns null-terminated
  string with full default file path. To get extended error
  information, call GetLastError() or SystemErrMessage().


  Note: Microsoft Windows specific (Win).
 */
LPCTSTR CreateTmpFile(CString& strResult,//[out] name of temporary file
                      LPCTSTR  strPrefix //[in] NULL or filename prefix.
                                         //Only first 3 characters are
                                         //used for the prefix.
                     )
{
TRACE(_T("CreateTmpFileName()\n"));

  //Set the file prefix
TCHAR  szPrefix[4];
szPrefix[3] = _T('\0');

if (strPrefix != NULL)
  {
  if (strPrefix[0] != '\0')
    szPrefix[0] = strPrefix[0];
  if (strPrefix[1] != '\0')
    szPrefix[1] = strPrefix[1];
  if (strPrefix[2] != '\0')
    szPrefix[2] = strPrefix[2];
  }
else
  {
  szPrefix[0] = _T('~');
  szPrefix[1] = _T('P');
  szPrefix[2] = _T('r');
  }

  //Set temporary file name
TCHAR szTempPath[MAX_PATH];
if(GetTempPath(MAX_PATH,szTempPath) == 0)
  {
  TRACE(_T("  Get Temp. path failed!\n"));
  return NULL;
  }

LPTSTR lpszTempName = strResult.GetBuffer(MAX_PATH);
if(::GetTempFileName(szTempPath,/*dir. for temp. files            */
                    szPrefix,   /*temp. filename prefix           */
                    0,          /*create unique name w/ sys. time */
           lpszTempName) == 0)  /*buffer for the name             */
  {
  TRACE(_T("  Get Temp. name failed!\n"));
  strResult.ReleaseBuffer(0);
  return NULL;
  }

strResult.ReleaseBuffer();
TRACE1(_T("  %s\n"),(LPCTSTR)strResult);
return strResult;
}

///////////////////////////////////////////////////////////////////////////////
#endif //WIN32
/******************************************************************************
 *$Log:
 * 3    Biblioteka1.2         2005-05-05 20:22:20  Darko           comments
 * 2    Biblioteka1.1         2002-07-16 01:41:09  Darko           Fixed VSS Log
 *      tag
 * 1    Biblioteka1.0         2002-04-05 00:50:09  Darko
 *$
 *****************************************************************************/
