/*$RCSfile: KGetAppPath.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/10/26 18:21:29 $
  $Author: ddarko $

  Retrieves application's path
  2009-07-15
 */

#include "stdafx.h"

//-----------------------------------------------------------------------------
/*Retrieves the path for the file that contains the specified module.
  The module must have been loaded by the current process. The returned result
  is a path ending with directory delimiter '/'.

  Returns application's path or an empty string in case of failure.
 */
CString GetAppPath()
{
ATLTRACE(_T("GetAppPath()\n"));
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
  ATLTRACE2(_T("  Failed GetModuleFileName: error ox%08X!\n"), GetLastError());
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
    ATLTRACE2(_T("  Failed GetFullPathName: error ox%08X!\n"), GetLastError());
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
  ATLTRACE2(_T("  Failed to allocate lpBuffer: error ox%08X!\n"), GetLastError());
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

ATLTRACE2(TRACEFORMAT, strPath);
return strPath;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: KGetAppPath.cpp,v $
 * Revision 1.1  2009/10/26 18:21:29  ddarko
 * Moved from old repository
 *
 ******************************************************************************/
