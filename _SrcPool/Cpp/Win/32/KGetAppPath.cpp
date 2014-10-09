/*$RCSfile: KGetAppPath.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2014/10/09 18:40:16 $
  $Author: ddarko $

  Retrieves application's path
  2009-07-15
 */

#include "stdafx.h"
#if !defined(_USE_MFC)
  #include "KString.h"  //CString.h
#endif

//-----------------------------------------------------------------------------
/*Retrieves the path for the file that contains the specified module.
  The module must have been loaded by the current process. The returned result
  is a path ending with directory delimiter '/'.

  Returns application's path or an empty string in case of failure.
  
  See also: GetExeDirectory(), getcwd(), GetModuleFileName(), GetCurrentDirectory()
 */
CString GetAppPath()
{
TRACE(_T("GetAppPath()\n"));
CString strPath; //application's fully qualified path

LPTSTR szPath = strPath.GetBuffer(MAX_PATH);
DWORD nSize = GetModuleFileName(NULL, szPath, MAX_PATH);
if ((nSize == 0) || (nSize == MAX_PATH))
  {
  /*Windows XP/2000:  If the buffer is too small to hold the module
    name, the function returns size of the buffer. The last error code remains
    ERROR_SUCCESS (ERROR_INSUFFICIENT_BUFFER for older OS versions). If size
    of the buffer is zero, the return value is zero and the last error code is
    ERROR_SUCCESS.
   */
  TRACE1(_T("  Failed GetModuleFileName: error 0X%08X!\n"), GetLastError());
  szPath[0] = _T('\0');
  }

LPTSTR lpFilePart = NULL;
const DWORD nBufferLength = nSize + 1;
LPTSTR lpBuffer = new TCHAR[nBufferLength];
if (lpBuffer != NULL)
  {
  nSize = GetFullPathName(szPath, nBufferLength, lpBuffer, &lpFilePart);

  if ((nSize == 0) || (nSize == nBufferLength))
    {
    TRACE1(_T("  Failed GetFullPathName: error 0X%08X!\n"), GetLastError());
    szPath[0] = _T('\0');
    }
  else
    {
     //Cut of filename portion of the path
    if (lpFilePart != NULL)
      {
      //Get length of the directory path portion
      nSize = (DWORD)(lpFilePart - lpBuffer);
      if ((szPath[nSize - 1] != _T('/')) && (szPath[nSize - 1] != _T('\\')))
        {
        szPath[nSize] = _T('\\');
        nSize++;
        }
      szPath[nSize] = _T('\0');
      }
    }

  delete[] lpBuffer;
  }
else
  {
  TRACE1(_T("  Failed to allocate lpBuffer: error 0x%08X!\n"), GetLastError());
  szPath[0] = _T('\0');
  }

strPath.ReleaseBuffer();  //Free extra space and set string length

#ifdef _UNICODE
  #ifndef TRACEFORMAT
    #define TRACEFORMAT _T("  path is: \"%ws\"\n")
  #endif
#else
  #ifndef TRACEFORMAT
    #define TRACEFORMAT _T("  path is: \"%s\"\n")
  #endif
#endif

TRACE1(TRACEFORMAT, (LPCTSTR)strPath);
return strPath;
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
/******************************************************************************
 * $Log: KGetAppPath.cpp,v $
 * Revision 1.3  2014/10/09 18:40:16  ddarko
 * Comment
 *
 * Revision 1.2  2012/09/25 19:01:04  ddarko
 * Fixed TRACE
 *
 * Revision 1.1  2009/10/26 18:21:29  ddarko
 * Moved from old repository
 *
 ******************************************************************************/
