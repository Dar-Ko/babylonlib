/*$Workfile: KFileGetS.cpp$: implementation file
  $Revision: 1$ $Date: 27/08/2002 4:04:34 PM$
  $Author: Darko Kolakovic$

  Obtain the short file path (Win16)
  Copyright: CommonSoft Inc.
  Jan 93 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

///////////////////////////////////////////////////////////////////////////////
// Win16 API substitution

//GetShortPathName()------------------------------------------------------------
/*The GetShortPathName function obtains the short path form of a specified input
  path.

  Returns: the length, in characters, of the string copied to lpszShortPath, 
  not including the terminating null character.

  Note: Used DOS call 0x7160:1 - GetShortPathName to create API function
 */
DWORD GetShortPathName(LPCTSTR lpszLongPath, //[in] zero-terminated path string.
                       //The function retrieves the short form of this path
                       LPTSTR lpszShortPath, //[out] Pointer to a buffer to
                       //receive the null-terminated short form of the path
                       //specified by lpszLongPath
                       DWORD cchBuffer//[in] Specifies the size, in characters,
                       //of the buffer pointed to by lpszShortPath
                       )
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
 *  1    Biblioteka1.0         27/08/2002 4:04:34 PMDarko Kolakovic 
 * $
 * Jan 93 Darko Kolakovic
 *****************************************************************************/
