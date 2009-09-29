/*$RCSfile: TestCrtStrdup.c,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/09/29 21:53:42 $
  $Author: ddarko $

  Test copying a string
  Feb 20 12:43:59 2003 Manoj Srivastava (srivasta@glaurung.green-gryphon.com)
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"
#include <string.h> //strdup(), _strdup()
#include "KTestLog.h"

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern const char* g_listTestStringsA[]; //Single-byte character set (SBCS) text samples

//TestStrDup()-----------------------------------------------------------------
/*Test of copying a string to a buffer.

  Returns: true if successful, otherwise returns false.

  See also: KStrings.h, StrDup(),
  Microsoft C run-time libraries: _strdup(), _wcsdup(), _mbsdup().
 */
bool TestCrtStrdup(void)
{
struct tagTestEntry logEntry = 
  {
  _T("strdup()"),
  _T("C run-time libraries"),
  false
  };
int i = 0;
TsWriteToViewLn(_T("TestCrtStrdup()"));

/*Test border case with null pointer*/
logEntry.m_bResult = (strdup(NULL) == NULL);
if (logEntry.m_bResult)
  {
  while(g_listTestStringsA[i] != NULL)
    {
    char* szOrig = NULL;
    szOrig = strdup(g_listTestStringsA[i]);

    if(szOrig != NULL)
      {
      logEntry.m_bResult = (strcmp(szOrig,g_listTestStringsA[i]) == 0);
      free(szOrig);
      if(!logEntry.m_bResult)
        {
        TsWriteToViewLn(_T("Failed test"));
        break;
        }
      }
    else
      {
      TsWriteToViewLn(_T("Failed malloc"));
      logEntry.m_bResult = false;
      }
    i++;
    }
  }
else
  {
  TsWriteToViewLn(_T("Failed <null> test"));
  }

LogTest(&logEntry);
TsWriteToViewLn(LOG_EOT);
return logEntry.m_bResult;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: TestCrtStrdup.c,v $
 *Revision 1.2  2009/09/29 21:53:42  ddarko
 *test completely rewritten
 *
 *Revision 1.1  2009/09/29 19:00:41  ddarko
 *strdup test
 *
 *Revision 1.2  2009/09/29 18:53:05  ddarko
 *strdup test
 *
 *****************************************************************************/
