/*$RCSfile: WmpTag.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2009/05/07 21:18:21 $
  $Author: ddarko $

  Illustrates how to extract WMP tags.
  Copyright: CommonSoft Inc
  2009-05-04 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#ifdef _USE_ATL
#include <atlfile.h>
  typedef CAtlFile CFile;
#endif

//-----------------------------------------------------------------------------
/*
  Returns: EXIT_SUCCESS, which represents a value of 0, if succesful. Otherwise
  a non-zero error code is returned.
 */
int BrowseWmpTags(LPCTSTR szFileList //[in]
                  )
{
TRACE1("BrowseWmpTags(%ws)\n", szFileList);

if ((szFileList != NULL) && (szFileList[0] != _T('\0')))
  {
  const int BUFF_SIZE = 1024;
  BYTE fileHeader[BUFF_SIZE];
  extern bool IsFileExisting(LPCTSTR szFileName);
  if(IsFileExisting(szFileList))
    {
    CFile fileAudio;
    if(fileAudio.Open(szFileName, ))
      {
      //Read data block

      fileAudio.Close();
      return EXIT_SUCCESS;
      }
    }
  }

return -1;
}

///////////////////////////////////////////////////////////////////////////////
/* 
 * $Log: WmpTag.cpp,v $
 * Revision 1.3  2009/05/07 21:18:21  ddarko
 * Added basic file handling
 *
 */