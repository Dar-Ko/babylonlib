/*$Workfile: H:\_SrcPool\Cpp\KFileTmpName.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:16:05 $
  $Author: ddarko $

  Creates unique file name
  CommonSoft Inc.
  Jun 98 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifdef _AFXDLL
  //MSVC and MFC
  #include <AfxWin.h>
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//CreateTmpFileName()----------------------------------------------------------
/*Creates unique file name in form X:\TempDir\XXX12345.tmp in the
  directory desgnated as temporary directory by the TMP or TEMP environment 
  variable.
 
  Returns: NULL if function is not succesfull, otherwise returns null-terminated
  ANSI character string with full default file path. To get extended error 
  information, call GetLastError() or SystemErrMessage(). 

  Note: LPCTSTR and TCHAR are used to make easier use of CString class.
  This function is not UNICODE comaptible.
  Microsoft Windows specific (Win).

 */
LPCTSTR CreateTmpFileName(CString& strResult,//[out] unique file name
                          LPCTSTR  strPrefix //[in] address of filename prefix or
                                             //NULL
                          )
{
TRACE0("CreateTmpFileName()\n");
#ifdef _UNICODE
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
  TRACE0("\tGet Temp. path failed!\n");
  return NULL;
  }

LPTSTR lpszTempName = strResult.GetBuffer(MAX_PATH);
if(::GetTempFileName(szTempPath,/*dir. for temp. files            */ 
                    szPrefix,   /*temp. filename prefix           */ 
                    0,          /*create unique name w/ sys. time */ 
           lpszTempName) == 0)  /*buffer for the name             */ 
  {
  TRACE0("\tGet Temp. name failed!\n");
  strResult.ReleaseBuffer(0);
  return NULL;
  }

strResult.ReleaseBuffer();
TRACE1("\t%s\n",(LPCTSTR)strResult);
return strResult;       
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 2    Biblioteka1.1         7/16/02 1:41:09 AM   Darko           Fixed VSS Log 
 *      tag
 * 1    Biblioteka1.0         4/5/02 12:50:09 AM   Darko           
 *$
 *****************************************************************************/
