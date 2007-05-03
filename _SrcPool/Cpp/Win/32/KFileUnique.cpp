/*$Workfile: KFileTmpName.cpp$: implementation file
  $Revision: 4$ $Date: 2007-02-06 10:59:06$
  $Author: Darko Kolakovic$

  Creates unique file name
  CommonSoft Inc.
  Jun 98 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifdef _AFXDLL
  //MSVC and MFC
  #include <afxwin.h>
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//CreateTmpFileName()----------------------------------------------------------
/*Creates an empty temporary file with unique name in the following form:
      X:\TempDir\XXX12345.tmp
  in the directory designated as temporary directory by the TMP or TEMP
  environment variable.

  Returns: NULL if function is not succesful, otherwise returns null-terminated
  (TODO: ANSI character) string with full default file path. To get extended error
  information, call GetLastError() or SystemErrMessage().

  TODO: Make function UNICODE comaptible.

  Note: uses Microsoft Foundation Library (MFC).
        Microsoft Windows specific (Win).
 */
LPCTSTR CreateTmpFileName(CString& strResult,//[out] unique file name
                          LPCTSTR  strPrefix //[in] address of filename prefix or
                                             //NULL
                          )
{
TRACE(_T("CreateTmpFileName()\n"));
#ifdef _UNICODE
  #pragma todo(" Make function UNICODE comaptible")
  return NULL;
#endif

  //Set the file prefix
TCHAR  szPrefix[4];
szPrefix[0] = _T('~');
szPrefix[1] = _T('P');
szPrefix[2] = _T('r');
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
TRACE(_T("  %s\n",(LPCTSTR)strResult));
return strResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log:
 * 3    Biblioteka1.2         2005-05-05 20:22:20  Darko           comments
 * 2    Biblioteka1.1         2002-07-16 01:41:09  Darko           Fixed VSS Log
 *      tag
 * 1    Biblioteka1.0         2002-04-05 00:50:09  Darko
 *$
 *****************************************************************************/
