/*$Workfile: TestStrDup.cpp$: implementation file
  $Revision: 3$ $Date: 2007-06-15 17:28:37$
  $Author: Darko Kolakovic$

  Test string trimming 
  Copyright: CommonSoft Inc.
  Aug. 2k2 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KStrings.h"	//StrDup()
#include <iostream>
#include <iomanip.h>  //std::endl

extern bool TsWriteToView(LPCTSTR lszText);

//TestStrDup()-----------------------------------------------------------------
/*Test of copying a string to a buffer.

  Returns: true if successful, otherwise returns false.
 */
bool TestStrDup()
{
TsWriteToView("TestStrDup()\r\n");

bool bRes = true;
LPCTSTR szText = _T("       CHAPTER VII      \
THE harder Tom tried to fasten his mind on his book, the more his ideas wandered.\r\n \
So at last, with a sigh and a yawn, he gave it up.\r\n  \
   \t \v");
int iTextLen = _tcslen(szText);

LPTSTR szCopy = StrDup(szText);
if (szCopy == NULL)
  bRes = false;
else
  {
  if (iTextLen != _tcslen(szCopy))
    bRes = false;
  else 
    {
    int i = 0;
    while (szCopy[i] != _T('\0'))
      {
      if (szCopy[i] != szText[i])
        {
        bRes = false;
        cout << "Character szText[" << i 
             << "] is not copied properly." << endl;
        break;
        }
      i++;
      }
    }
    //Free allocated storage
  free(szCopy);
  }

TsWriteToView("======================\r\n");
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 3    Biblioteka1.2         2007-06-15 17:28:37  Darko Kolakovic Console traget
 *      fixes
 * 2    Biblioteka1.1         2007-06-15 12:43:09  Darko Kolakovic 
 * 1    Biblioteka1.0         2002-09-11 16:25:48  Darko Kolakovic 
 *$
 *****************************************************************************/
