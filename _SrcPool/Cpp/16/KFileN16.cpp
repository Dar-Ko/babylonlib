/*$Workfile: KFileN16.cpp$: implementation file
  $Revision: 1$ $Date: 8/27/02 5:04:37 PM$
  $Author: Darko Kolakovic$

  File Name handler (Win16)
  Copyright: CommonSoft Inc.
  Jan 93 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KFileNam.h" //CFileName class

///////////////////////////////////////////////////////////////////////////////
// CFileName class

//::IsFileFound()--------------------------------------------------------------
/*Checks if file is accesibile.  Returns true if the function succeeds, or 
  FALSE if the function fails. To get extended error information, call GetLastError.
 */
bool CFileName::IsFileFound() const
{
OFSTRUCT ofs;
ofs.cBytes = sizeof ofs;
return ::OpenFile(Canonical().c_str(), &ofs, OF_EXIST) != HFILE_ERROR;
}

//::CopyFile()-----------------------------------------------------------------
/*The CopyFile function copies an existing file to a new file. If bFailIfExists
  parameter is TRUE and the new file already exists, the function fails. 
  If this parameter is FALSE and the new file already exists, the function 
  overwrites the existing file and succeeds. 
 */
void CFileName::CopyFile(LPCTSTR lpNewFileName, //pointer to filename to copy to 
                         bool    bFailIfExists  //flag for operation if file exists 
                         ) const
{
FILE *fileSource;
FILE *fileTarget;
CString strnewFile;
strNewFile = CFileName::Canonical(lpNewFileName,FALSE)

char chTmp;

if (bFailIfExists) 
  {
  fileTarget = fopen(strNewFile, "r");
  if (!fileTarget)
    return;
  fclose(fileTarget);
  }

fileTarget = fopen(strNewFile, "w");
if (!fileTarget)
  return;
fileSource = fopen(Canonical().c_str(), "r");
if (!fileSource) 
  {
  fclose(fileTarget);
  return;
  }

while ((chTmp = getc(fileSource)) != 0) //if != 0 part generates compiler warning
  putc(chTmp, fileTarget);

fclose(fileSource);
fclose(fileTarget);
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         8/27/02 5:04:37 PM   Darko Kolakovic 
 * $
 * May 98 Created Win32 version D.K.
 * Jan 93 Darko Kolakovic
 *****************************************************************************/

