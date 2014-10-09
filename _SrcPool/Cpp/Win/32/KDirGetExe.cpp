/*$RCSfile: KDirGetExe.cpp$: implementation file
  $Revision: 3$ $Date: 02/05/2005 9:38:08 PM$
  $Author: Darko$

  Get directory of from the full executable file path.
  Copyright: CommonSoft Inc.
  Jan 98 Darko Kolakovic
 */
// Group=Windows

#include "stdafx.h"

#if !defined(_USE_MFC)
  #include "KString.h"  //CString.h
#endif

CString GetExeDirectory();
extern UINT GetFileDirectory(LPTSTR szPathName, LPTSTR szDirectory,UINT nDirSize);

//-----------------------------------------------------------------------------
/*Retrieves the full path for the executable file used to create the calling
  process.

  Returns: string object containing executable directory.
  
  See also: GetAppPath(), getcwd(), GetModuleFileName(), GetCurrentDirectory(),
  current_path()
  */
CString GetExeDirectory()
{
TRACE(_T("  GetExeDirectory()\n"));

CString strResult;
LPSTR szBuff = strResult.GetBuffer(_MAX_PATH);
      //Get path of the current module
VERIFY(::GetModuleFileName(NULL, szBuff, _MAX_PATH));
GetFileDirectory(szBuff,szBuff,_MAX_PATH);
strResult.ReleaseBuffer();

TRACE1(_T("    executable directory is %s.\n"), (LPCTSTR)strResult);
return strResult;
}
///////////////////////////////////////////////////////////////////////////////
/*Notes: Microsoft Visual Studio
    GetModuleFileName()    Retrieves the fully qualified path for the file that 
	contains the specified module. The module must have been loaded by the current process.
	http://msdn.microsoft.com/en-us/library/windows/desktop/ms683197%28v=vs.85%29.aspx
	
	GetCurrentDirectory()  Retrieves the current directory for the current process.
	http://msdn.microsoft.com/en-us/library/windows/desktop/aa364934%28v=vs.85%29.aspx
	
	_getcwd(), _wgetcwd()  POSIX: Gets the current working directory.
	This API CANNOT be used in Windows Store applications 
	MSVC 2013 /ZW option ref.: "CRT functions not supported with /ZW";
	http://msdn.microsoft.com/library/windows/apps/jj606124.aspx).
	http://msdn.microsoft.com/en-us/library/sf98bd4y.aspx
	
	Other
	
	current_path() Boost: Returns: current_path() at the time of entry to main().
	http://www.boost.org/doc/libs/1_36_0/libs/filesystem/doc/reference.html
	
	getcwd(), getwd(), get_current_dir_name() Linux: get current working directory
	http://unixhelp.ed.ac.uk/CGI/man-cgi?getcwd+3
	https://developer.apple.com/library/mac/documentation/Darwin/Reference/ManPages/man3/getcwd.3.html
 */
/*****************************************************************************
 * $Log: $
 *  3    Biblioteka1.2         02/05/2005 9:38:08 PMDarko           Comments
 *  2    Biblioteka1.1         02/05/2005 8:46:35 PMDarko           
 *  1    Biblioteka1.0         02/05/2005 8:44:32 PMDarko           
 * 0:   Jan 98 Darko Kolakovic
 *****************************************************************************/
