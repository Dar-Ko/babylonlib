/*$RCSfile: KGetAppPath.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2014/10/09 18:40:15 $
  $Author: ddarko $

  Retrieves application's path
  2014-10-01
 */

#ifdef _USE_STL //TODO:
//TODO: _UNICODE
  #include <string>
  #define CString std::string
#else
  #include "KString.h"  //CString.h
#endif
#include <limits.h>
#include <unistd.h>

#ifdef __linux
//-----------------------------------------------------------------------------
/*Retrieves the path for the file that contains the specified module.
  The module must have been loaded by the current process. The returned result
  is a path ending with directory delimiter '/'.

  Returns application's path or an empty string in case of failure.
  
  See also: getcwd()
 */
CString GetAppPath()
{
TRACE(_T("GetAppPath()\n"));
CString strPath; //application's fully qualified path

LPTSTR szPath = strPath.GetBuffer(PATH_MAX);

ssize_t nSize = readlink( "/proc/self/exe", szPath, PATH_MAX );
/*
sprintf(szTmp, "/proc/%d/exe", getpid());
int bytes = MIN(readlink(szTmp, pBuf, len), len - 1);
 */
/* Note: /proc is not portable on on Linux flavours / OS X
 */
if ((nSize == 0) || (nSize == MAX_PATH))
  {

  TRACE1(_T("  Failed GetModuleFileName: error 0X%08X!\n"), GetLastError());
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
#endif //__linux

#ifdef _HP_UX_ //HP_UNIX
  #define _PSTAT64
  #include <sys/pstat.h>
  #include <sys/types.h>
//-----------------------------------------------------------------------------
/*Retrieves the path for the file that contains the specified module.
  The module must have been loaded by the current process. The returned result
  is a path ending with directory delimiter '/'.

  Returns application's path or an empty string in case of failure.
  
  See also: getcwd()
 */
CString GetAppPath()
{
TRACE(_T("GetAppPath()\n"));
CString strPath; //application's fully qualified path

LPTSTR szPath = strPath.GetBuffer(PATH_MAX);
struct pst_status ps;

if (pstat_getproc( &ps, sizeof( ps ), 0, getpid() ) >= 0)
  {
    if (pstat_getpathname( szPath, PATH_MAX, &ps.pst_fid_text ) < 0)
      {
	  TRACE1(_T("  Failed pstat_getpathname\n"));
      szPath[0] = _T('\0');
      }
  }
 else
  {
  szPath[0] = _T('\0');
  }  
strPath.ReleaseBuffer();  //Free extra space and set string length
//TRACE1(TRACEFORMAT, (LPCTSTR)strPath);
return strPath;
}
#endif //_HP_UX_
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
 * Revision 1.2  2014/10/09 18:40:15  ddarko
 * Comment
 *
 * Revision 1.1  2014/10/09 18:28:50  ddarko
 * Created
 *
 ******************************************************************************/
