/*$Workfile: KFileExist.cpp$: implementation file
  $Revision: 2$ $Date: 28/04/2005 8:46:46 PM$
  $Author: Darko$

  Checks if file exist.
  Copyright: CommonSoft Inc.
  Sep. 97 D. Kolakovic
 */

// Group=Windows

#ifdef _WIN32
#if defined _USE_MFC || defined _USE_ATL
  //Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)
  //or preprocessor reports unpaired #endif directive

  #include "stdafx.h" // MFC core and standard components
#else
  #include <windows.h>
#endif

#ifndef _T
  #include "KTChar.h" //LPCTSTR typedef
#endif

#ifdef _DEBUG
  #ifdef _USE_MFC
    #define new DEBUG_NEW
  #endif
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Verifies if file exist in the current folder.

  Note:  device names COM1, LPT2 are also valid names for the streams.

  Returns true if file exist or false if not.

  Note: Microsoft Windows specific (Win32).
*/
bool IsFileExisting(LPCTSTR szFileName //[in] null-terminated file name
                  )
{
if (szFileName != NULL)
  {
  #ifdef _USE_MFC
    CFileStatus fileStatus;
    /*Note: The Microsoft Foundation classes provide an enum type attribute
      so that you can specify attributes symbolically:
        enum CFile::Attribute 
          {
          normal =    0x00,
          readOnly =  0x01,
          hidden =    0x02,
          system =    0x04,
          volume =    0x08,
          directory = 0x10,
          archive =   0x20
          };
     */
    return ((CFile::GetStatus(szFileName, fileStatus ) != FALSE) &&
            (fileStatus.m_attribute != CFile::directory);

  #else
  //Is the file one of the existing files?
  HANDLE hFile = CreateFile(szFileName,
                           0, //query file existence without
                              //accessing the file.
                           FILE_SHARE_READ,
                           NULL,//if lpSecurityAttributes is NULL,
                            //the handle cannot be inherited.
                           OPEN_EXISTING,
                           0,
                           NULL);


  if (hFile != INVALID_HANDLE_VALUE)
    {
    CloseHandle(hFile);
    return true;
    }
  #endif
  }
return false;

}

#endif //_WIN32
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
