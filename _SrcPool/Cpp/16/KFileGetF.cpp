/*$Workfile: H:\_SrcPool\Cpp\16\KFileGetF.cpp$: implementation file
  $Revision: 1$ $Date: 8/27/02 5:04:31 PM$
  $Author: Darko Kolakovic$

  File Name handler (Win16)
  Copyright: CommonSoft Inc.
  Jan 93 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

///////////////////////////////////////////////////////////////////////////////
// Win16 API substitution

//GetFullPathName()------------------------------------------------------------
/*The GetFullPathName function retrieves the full path and filename of a 
  specified file.

  Returns: the length, in characters, of the string copied to lpBuffer, not 
  including the terminating null character.

  Note: Used DOS call 0x7160:0 - GetFullPathName to create API function
 */
DWORD GetFullPathName(LPCTSTR lpFileName, //[in] a zero-terminated 
                      //string that specifies a valid file name. This string 
                      //can use either short (the 8.3 form) or long file names
                      DWORD nBufferLength, //[in] specifies the size, in 
                      //characters, of the buffer for the drive and path
                      LPTSTR lpBuffer, //[out] pointer to a buffer that receives
                      //the zero-terminated string for the name of the drive 
                      //and path
                      LPTSTR* lpFilePart //[out] pointer to a buffer that receives
                      //the address (in lpBuffer) of the final file name component
                      //in the path
                      )
{
  //MS-DOS long filename function 0x7160:0
char destPath[MAX_PATH]; // defined at top of file
char const far* farFileName = lpFileName;
char far* farDestPath = destPath;
_asm 
  {
  mov ax, 0x7160
  mov cl, 0                    //GetFullPathName()
  mov ch, 0                   
  lds si, farFileName
  les di, farDestPath
  int 21h
  jc  _ERROR
  }
//Note: returned string contains path not SUBST drive

strncpy(lpBuffer, destPath, (int)(nBufferLength - 1));
goto _EXIT;

_ERROR:   //Copy to target
  strncpy(lpBuffer, lpFileName, (int)(nBufferLength - 1)); 

_EXIT:
  int bufferLen = strlen(lpBuffer);

  //Find the beginning of the file name
  if (lpFilePart)
    {
    *lpFilePart = lpBuffer;
    int i;
    for (i = bufferLen -1; i >= 0; i--)
      {
      if (lpBuffer[i] == '\\' || lpBuffer[i] == '/' || lpBuffer[i] == ':') 
        {
        *lpFilePart = lpBuffer + i + 1;
        break;
        }
      }
    }

return bufferLen;
}

//GetShortPathName()------------------------------------------------------------
/*The GetShortPathName function obtains the short path form of a specified input path. 

  Note: Used DOS call 0x7160:1 - GetShortPathName to create API function
 */
DWORD GetShortPathName(LPCTSTR lpszLongPath, LPTSTR lpszShortPath, DWORD cchBuffer)
{
  //MS-DOS short filename function 0x7160:1
char destPath[MAX_PATH];
LPCTSTR farLongPath = lpszLongPath;
LPTSTR farDestPath = destPath;
  
_asm 
  {
  mov ax, 0x7160      //GetShortPathName()
  mov cl, 1                    
  mov ch, 0           
  lds si, farLongPath
  les di, farDestPath
  int 21h
  jc  _ERROR
  }
//Note: returned string contains path not SUBST drive

strncpy(lpszShortPath, destPath, (int)(cchBuffer - 1));
goto _EXIT;

_ERROR:    //Copy to target
    strncpy(lpszShortPath, lpszLongPath, (int)(cchBuffer - 1)); 

_EXIT:
  return strlen(lpszShortPath);
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         8/27/02 5:04:31 PM   Darko Kolakovic 
 * $
 * Jan 93 Darko Kolakovic
 *****************************************************************************/
