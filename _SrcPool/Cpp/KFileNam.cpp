/*$Workfile: H:\_SrcPool\Cpp\KFileNam.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:14:10 $
  $Author: ddarko $

  File Name handler
  Copyright: CommonSoft Inc.
  May 98 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <AfxWin.h>
#include "KFileNam.h" //CFileName class

#ifndef WIN32    //Windows 32b application
  #pragma error ("Requred Windows 32b")
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileName class implementation

//::IsValid()------------------------------------------------------------------
/*Validate the filename
 */
bool CFileName::IsValid() const
{
OFSTRUCT ofs;
ofs.cBytes = sizeof ofs;
return ::OpenFile(Canonical(), &ofs, OF_PARSE) != HFILE_ERROR;
}

//::Parse()--------------------------------------------------------------------
/*Get file name components.

  TODO:
 */
void CFileName::Parse(LPCTSTR szFileName //[in] file path
                      )
{
LPTSTR nextp;
LPTSTR szFileNameEnd = strend(szFileName);

// Parse from the left, the server name and device if UNC "\\", or the
// logical device name if one.
//
nextp = skipstr(szFileName, szFileNameEnd, serverNamePrefix);

if (nextp > szFileName) {
  Unc = true;
  szFileName = nextp;               // skip "\\"
  nextp = find(szFileName, szFileNameEnd, dirSeparator);
  ServerStr = string(szFileName, 0, (int)(nextp-szFileName));
  szFileName = nextp + 1;               // skip past "\"

  nextp = find(szFileName, szFileNameEnd, dirSeparator);
  DeviceStr = string(szFileName, 0, (int)(nextp-szFileName));
  szFileName = nextp + 1;               // skip past "\"
}
else {
  Unc = false;
  ServerStr = "";

  nextp = find(szFileName, szFileNameEnd, FNM_DEVICE_DELIM);
  if (nextp != szFileNameEnd) {
    DeviceStr = string(szFileName, 0, (int)(nextp-szFileName));
    szFileName = nextp + 1;               // skip past "\/:"
  }
  else
    DeviceStr = "";
}

// Parse the extension and filename from the right.
//
nextp = findl(szFileNameEnd-1, szFileName-1, FNM_EXT_DELIM);
const char far* dirp = findl(szFileNameEnd-1, szFileName-1, dirSeparator);

if (nextp > dirp) {
  ExtStr = string(nextp, 0, (int)(szFileNameEnd-nextp));
  szFileNameEnd = nextp;
}
else
  ExtStr = "";

FileStr = string(dirp+1, 0, (int)(szFileNameEnd - (dirp+1)));
szFileNameEnd = dirp;

// What is left is the path
//
if (szFileNameEnd > szFileName)
  PathStr = string(szFileName, 0, (int)(szFileNameEnd-szFileName));
else
  PathStr = "";
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         8/27/02 5:04:48 PM   Darko Kolakovic 
 * $
 *****************************************************************************/
