/*$Workfile: $: implementation file
  $Revision: 1.1 $ $Date: 2007/09/12 20:40:58 $
  $Author: ddarko $

  Checks if file exist.
  Jan. 1987 Darko Kolakovic
*/

/* Group=Windows                                                              */

#include <stdio.h>
#include "KTypedef.h" /*bool typedef*/

#ifdef _DEBUG
  #include <assert.h>
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#ifndef _WIN32
/*---------------------------------------------------------------------------*/

/*Verifies if file exist in the current folder.

  Returns true if file exist or false if not.

  Note: PC Disk Operating System specific (DOS),
        Microsoft Windows 16b specific (Win16),
        Microsoft Windows specific (Win32)
*/
bool IsFileExisting(LPCSTR szFileName //[in] null-terminated file name
                   )
{
/*Is the file one of the existing files?*/
if (szFileName != NULL)
  {
  /*Open the existing file*/
  FILE* fpFile;
  fpFile = fopen(szFileName, "r");
  if (fpFile != NULL)
    {
    #ifdef _DEBUG
      int iErr = fclose(fpFile);
      assert(iErr == 0); /*assert the stream is successfully closed*/
    #else
      fclose(fpFile);
    #endif
    return (true);  /*Return success*/
    }
   }

return (false);
}
#else /*_WIN32*/
#include <tchar.h> //_tfopen()
//-----------------------------------------------------------------------------
/*Verifies if file exist in the current folder.

  Returns true if file exist or false if not.

  Note: Microsoft Windows specific (Win32)
*/
bool IsFileExisting(LPCTSTR szFileName //[in] null-terminated file name
                   )
{
//Is the file one of the existing files?
if (szFileName != NULL)
  {
  /*Open the existing file*/
  FILE* fpFile;
  fpFile = _tfopen(szFileName, _T("r"));
  if (fpFile != NULL)
    {
    #ifdef _DEBUG
      int iErr = fclose(fpFile);
      assert(iErr == 0); /*assert the stream is successfully closed*/
    #else
      fclose(fpFile);
    #endif
    return (true);  /*Return success*/
    }
   }

return (false);
}
#endif /*_WIN32*/
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: $
 *****************************************************************************/
