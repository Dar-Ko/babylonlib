/*$RCSfile: TestCrtStrdup.c,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/09/29 19:00:41 $
  $Author: ddarko $

  Test copying a string
  Feb 20 12:43:59 2003 Manoj Srivastava (srivasta@glaurung.green-gryphon.com)
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"
#include "KStrings.h" //StrDup()
#include "STL/KOStream.h" //_tcout

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern "C" const char* g_listTestStringsA; //Single-byte cahcarcter set (SBCS) text samples

//TestStrDup()-----------------------------------------------------------------
/*Test of copying a string to a buffer.

  Returns: true if successful, otherwise returns false.

  See also: KStrings.h, StrDup(),
  Microsoft C run-time libraries: _strdup(), _wcsdup(), _mbsdup().
 */
int test_strdup(void)
{
  int retval = 0;
  int i = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strdup - ");
#endif
  for(i = 0; strings_to_test[i]; i++)
   {
     char * orig = 0;
     orig = strdup(strings_to_test[i]);
     if(orig)
      {
        if(strcmp(orig,strings_to_test[i]))
          {
            retval--;
            fprintf (stderr,
                     "ERROR: manoj_strdup Failed test %d. \n",
                     i);
          }
        free(orig);
      }
     else
      {
        fprintf (stderr,
                 "ERROR: manoj_strdup Failed test %d -- failed malloc\n",
                 i);
      }
#ifdef DEBUG
     fprintf (stderr, ".");
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}

/*
bool TestStdStrDup()
{
TsWriteToView(_T("TestStrDup()\r\n"));
TESTENTRY logEntry;
bool& bRes = logEntry.m_bResult;
bRes = true;

logEntry.m_szObjectName = _T("strdup()");
logEntry.m_szFileName = _T("C run-time libraries");


LogTest(&logEntry);
TsWriteToViewLn(LOG_EOT);
return bRes;
}
*/
//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: TestCrtStrdup.c,v $
 *Revision 1.1  2009/09/29 19:00:41  ddarko
 *strdup test
 *
 *Revision 1.2  2009/09/29 18:53:05  ddarko
 *strdup test
 *
 *****************************************************************************/
