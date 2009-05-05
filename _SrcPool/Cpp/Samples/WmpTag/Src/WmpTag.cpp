/*$RCSfile: WmpTag.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/05/05 20:15:34 $
  $Author: ddarko $

  Illustrates how to extract WMP tags.
  Copyright: CommonSoft Inc
  2009-05-04 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

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
  extern bool IsFileExisting(LPCTSTR szFileName);
  if(IsFileExisting(szFileList))
    {
    return EXIT_SUCCESS;
    }
  }

return -1;
}