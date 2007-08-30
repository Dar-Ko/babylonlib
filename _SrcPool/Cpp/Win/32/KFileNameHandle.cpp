#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <psapi.h> //GetMappedFileName()
#include <strsafe.h>

#define BUFSIZE 512

/*Requires psapi.lib

  Note: Microsoft Process Status API (PSAPI).
 */
#pragma comment( lib, "psapi" )

BOOL GetFileNameFromHandle(HANDLE hFile //[in]
                          ) 
{
BOOL bSuccess = FALSE;
TCHAR pszFilename[MAX_PATH+1];
HANDLE hFileMap;

// Get the file size.
DWORD dwFileSizeHi = 0;
DWORD dwFileSizeLo = GetFileSize(hFile, &dwFileSizeHi); 

if( dwFileSizeLo == 0 && dwFileSizeHi == 0 )
{
printf("Cannot map a file with a length of zero.\n");
return FALSE;
}

// Create a file mapping object.
hFileMap = CreateFileMapping(hFile, 
NULL, 
PAGE_READONLY,
0, 
MAX_PATH,
NULL);

if (hFileMap) 
{
// Create a file mapping to get the file name.
void* pMem = MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 1);

if (pMem) 
{
  if (GetMappedFileName (GetCurrentProcess(), 
    pMem, 
    pszFilename,
    MAX_PATH)) 
  {

    // Translate path with device name to drive letters.
    TCHAR szTemp[BUFSIZE];
    szTemp[0] = '\0';

    if (GetLogicalDriveStrings(BUFSIZE-1, szTemp)) 
    {
      TCHAR szName[MAX_PATH];
      TCHAR szDrive[3] = TEXT(" :");
      BOOL bFound = FALSE;
      TCHAR* p = szTemp;

      do 
      {
        // Copy the drive letter to the template string
        *szDrive = *p;

        // Look up each device name
        if (QueryDosDevice(szDrive, szName, BUFSIZE))
        {
          UINT uNameLen = _tcslen(szName);

          if (uNameLen < MAX_PATH) 
          {
            bFound = _tcsnicmp(pszFilename, szName, 
              uNameLen) == 0;

            if (bFound) 
            {
              // Reconstruct pszFilename using szTempFile
              // Replace device path with DOS path
              TCHAR szTempFile[MAX_PATH];
              StringCchPrintf(szTempFile,
                MAX_PATH,
                TEXT("%s%s"),
                szDrive,
                pszFilename+uNameLen);
              StringCchCopyN(pszFilename, MAX_PATH+1, szTempFile, _tcslen(szTempFile));
            }
          }
        }

        // Go to the next NULL character.
        while (*p++);
      } while (!bFound && *p); // end of string
    }
  }
  bSuccess = TRUE;
  UnmapViewOfFile(pMem);
} 

CloseHandle(hFileMap);
}
_tprintf(TEXT("File name is %s\n"), pszFilename);
return(bSuccess);
}

///////////////////////////////////////////////////////////////////////////////
/*Microsoft Developer Network: Obtaining a File Name From a File Handle

  The following example obtains a file name from a file handle using a file 
  mapping object. It uses the CreateFileMapping and MapViewOfFile functions to 
  create the mapping. Next, it uses the GetMappedFileName function to obtain 
  the file name. For remote files, it prints the device path received from 
  this function. For local files, it converts the path to use a drive letter 
  and prints this path. To test this code, create a main function that opens a file using CreateFile and passes the resulting handle to GetFileNameFromHandle.
*/