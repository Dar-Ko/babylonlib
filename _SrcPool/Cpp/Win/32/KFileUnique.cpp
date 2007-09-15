/*$Workfile: KFileUnique.cpp$: implementation file
  $Revision: 2$ $Date: 2007-05-08 10:16:42$
  $Author: Darko Kolakovic$

  Creates unique file name
  CommonSoft Inc.
  Jun 98 Darko Kolakovic
*/

#include "stdafx.h"
#include <errno.h>
#include "KFileSys.h"
#ifndef _AFXDLL
  #define USE_KCSTRING 20070505
#endif

#ifdef USE_KCSTRING
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
/*Creates unique name for a file in the given folder. Filename is generated
  from the current time and has minimum length of 8 characters.
  File name is limited to MAX_PATH. Lengths of directory path and file name
  extension are also included in the limit, if they are not empty strings.

  Note: some other process could create a file with the same name as the name
  returned by the function, in the period before the caller actually creates the
  file.

  Note: Path length limit for FAT32 file systems is MAX_PATH and for NTFS is 32768
  characters (see also: Path Field Limits (CRT)).

  Returns: string with unique file name or NULL in case of a failure.

  Note: uses Microsoft Foundation Library (MFC) or
        uses Microsoft Active Template Library (ATL);
        Microsoft Windows specific (Win32).
 */
LPCTSTR CreateUniqueFileName(CString& strResult,//[out] unique filename
                             LPCTSTR szFilePath,//[in] directory path or NULL.
                             LPCTSTR szPrefix,  //[in] filename prefix or NULL
                             LPCTSTR szExtension//[in] filename extension or NULL
                            )
{
TRACE(_T("CreateUniqueFileName()\n"));

/*File access permission:
  00 Existence only
  02 Write permission
  04 Read permission
  06 Read and write permission
 */
const int EXIST = 0; //existence validation only
const int ACCESS_OK = 0; //File has required access rights
const int EOK = 0; //no error occured
const int NAMESIZE = 8; //size of variable part of the file name is 32-bit
                        //hexadecimal number
int iPos;    //space required for the file name
if((szFilePath != NULL) && (szFilePath[0] != _T('\0')))
  {
  iPos = _tcslen(szFilePath);
  if (!IsPathDelim(szFilePath[iPos-1]))
    iPos++; //Add space for directory delimiter
  }
if (iPos > (MAX_PATH - NAMESIZE))
  return NULL; //This part of the file path is too long

if(szPrefix != NULL)
  iPos += _tcslen(szPrefix);
if (iPos > (MAX_PATH - NAMESIZE))
  return NULL; //This part of the file path is too long

if((szExtension != NULL) && (szExtension[0] != _T('\0')))
  {
  iPos += _tcslen(szExtension);
  if (szExtension[0] != FILEEXTDELIM)
    iPos++; //Add space for extension separator
  }
if (iPos > (MAX_PATH - NAMESIZE))
  return NULL; //File path is too long

//Allocate space for the result
LPTSTR szResult = strResult.GetBuffer(iPos + NAMESIZE);
//Copy directory path
iPos = 0;
if ((szFilePath != NULL) && (szFilePath[0] != _T('\0')))
  {
  while(szFilePath[iPos] != _T('\0'))
    {
    szResult[iPos] = szFilePath[iPos];
    iPos++;
    }

  if (!IsPathDelim(szResult[iPos]))  //Append directory delimiter
    {
    szResult[iPos] = PATHDELIM;
    iPos++;
    }
  }

//Append filename prefix to the directory
int i = 0;
if ((szPrefix != NULL) && (szPrefix[0] != _T('\0')))
  {
  while(szPrefix[i] != _T('\0'))
    {
    szResult[iPos] = szPrefix[i];
    iPos++;
    i++;
    }
  }

int iNamePos = iPos; //begining of the variable part of the filename
FILETIME ftTime; //system time
//32-bit integer is required to create a name
ASSERT (sizeof(ftTime.dwLowDateTime) <= 4);
GetSystemTimeAsFileTime(&ftTime);
//Use lower portion of the FILETIME to create the name
ItoA(ftTime.dwLowDateTime, &szResult[iNamePos], 16);
iPos += NAMESIZE;

//Append filename extension
if ((szExtension != NULL) && (szExtension[0] != _T('\0')))
  {
  if (szExtension[0] != FILEEXTDELIM) //Append filename extension separator
    {
    szResult[iPos] = FILEEXTDELIM;
    iPos++;
    }
  i = 0;
  while(szExtension[i] != _T('\0')) //Copy filename extension
    {
    szResult[iPos] = szExtension[i];
    iPos++;
    i++;
    }
  }
ASSERT((MAX_PATH - iPos) > 0); //Check if enough space is allocated
//Save the character after variable part of filename
TCHAR chNameEnd = szResult[iNamePos + NAMESIZE];
errno = EOK;           //Clear the current error status

ftTime.dwHighDateTime = ftTime.dwLowDateTime; //Save value for later
                                              //sanity check

/*Check all files until _taccess() function does not return failure
  with ENOENT: filename or path not found.
  The function returns –1 if the named file does not exist or
  is not accessible and sets errno to EACCES or ENOENT .
 */
while ((_taccess(szResult, EXIST) == ACCESS_OK) || (errno == EACCES))
  {
  if ((ftTime.dwLowDateTime - ftTime.dwHighDateTime) > 0x1000)
    {
    //Break theoretical endless loop
    TRACE(_T("  Get Temp. name failed!\n"));
    strResult.ReleaseBuffer(0);
    return NULL;
    }
  errno = EOK; //Reset system error
  //Try another name
  ItoA(++ftTime.dwLowDateTime, &szResult[iNamePos], 16);
  //Replace terminating zero inserted by ItoA
  szResult[iNamePos + NAMESIZE] = chNameEnd;
  }

strResult.ReleaseBuffer();
return strResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log:
 * 1    Biblioteka1.0         2007-05-04 17:51:55  Darko Kolakovic
 *$
 *****************************************************************************/
