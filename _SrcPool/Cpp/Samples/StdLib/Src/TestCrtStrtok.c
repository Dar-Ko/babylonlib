/*$RCSfile: TestCrtStrtok.c,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/09/29 21:20:52 $
  $Author: ddarko $

  Test string tokenizer.
  Feb 20 12:43:59 2003 Manoj Srivastava (srivasta@glaurung.green-gryphon.com)
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"
#include <string.h> //strtok()
#include "KTestLog.h"

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern const char* g_listTestStringsA[]; //Single-byte character set (SBCS) text samples

int test_strtok(void)
{
  int            retval   = 0;
  int            i        = 0;
  char          *buffer_p = 0;
  char          *copy_p   = 0;
  const char    *delim_p  = " eta";
  char          *tok1     = 0;
  char          *tok2     = 0;


#ifdef DEBUG
  fprintf (stderr, "manoj_strtok - ");
#endif

  buffer_p = malloc(128);
  if(! buffer_p) return -1;

  copy_p = malloc(128);
  if(! copy_p) return -1;

  (void) strcpy(buffer_p, "The quick brown fox jumps over the lazy dog");
  (void) strcpy(copy_p,   "The quick brown fox jumps over the lazy dog");

  tok1 = manoj_strtok(buffer_p, delim_p);
  tok2 =       strtok(copy_p,   delim_p);
  if(strcmp(tok1, tok2))
   {
     retval--;
     fprintf (stderr,
              "ERROR: manoj_strtok Failed test %d. Got (%s), expected (%s)\n",
              i++, tok1, tok2);
   }
#ifdef DEBUG
  else
   {
     fprintf (stderr, ".");
   }
#endif

  while((tok1 =  manoj_strtok(0, delim_p)))
   {
     tok2 = strtok(0, delim_p);
     if(strcmp(tok1, tok2))
      {
        retval--;
        fprintf(stderr,
                "ERROR: manoj_strtok Failed test %d. Got (%s), expected (%s)\n",
                 i++, tok1, tok2);
      }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      }
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}


int test_strtok_r(void)
{
  int            retval   = 0;
  int            i        = 0;
  char          *orig_p   = 0;
  char          *buffer_p = 0;
  char          *copy_p   = 0;
  const char    *delim_p  = " eta";
  char          *tok1     = 0;
  char          *tok2     = 0;


#ifdef DEBUG
  fprintf (stderr, "manoj_strtok_r - ");
#endif

  orig_p = malloc(128);
  if(! orig_p) return -1;

  buffer_p = malloc(128);
  if(! buffer_p) return -1;

  copy_p = malloc(128);
  if(! copy_p) return -1;

  (void) strcpy(orig_p, "The quick brown fox jumps over the lazy dog");

  tok1 = manoj_strtok_r(orig_p, delim_p, &buffer_p);
  tok2 =       strtok_r(orig_p, delim_p, &copy_p);
  if(strcmp(tok1, tok2))
   {
     retval--;
     fprintf (stderr,
              "ERROR: manoj_strtok_r Failed test %d. Got (%s), expected (%s)\n",
              i++, tok1, tok2);
   }
#ifdef DEBUG
  else
   {
     fprintf (stderr, ".");
   }
#endif

  while((tok1 =  manoj_strtok_r(0, delim_p, &buffer_p)))
   {
     tok2 = strtok_r(0, delim_p, &copy_p);
     if(strcmp(tok1, tok2))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strtok_r Failed test %d. Got (%s), expected (%s)\n",
                 i++, tok1, tok2);
      }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      }
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}

int test_strstr(void)
{
  int            retval   = 0;
  int            i        = 0;

#ifdef DEBUG
  fprintf (stderr, "manoj_strstr - ");
#endif
  for(i = 0; g_listTestStringsA[i]; i++)
   {
     if(manoj_strstr(g_listTestStringsA[i], "at-that") !=
        strstr(g_listTestStringsA[i], "at-that"))
      {
        retval--;
        fprintf (stderr,
                 "ERROR: manoj_strstr Failed test %d. \n",
                 i);
       }
#ifdef DEBUG
     else
      {
        fprintf (stderr, ".");
      } /* end of else */
#endif
   }
#ifdef DEBUG
  fprintf (stderr, " - done\n");
#endif
  return retval;
}


//-----------------------------------------------------------------------------
/*Test of finding a token in a string.

  Returns: true if successful, otherwise returns false.

  See also: KStrings.h, strtok_r()
  Microsoft C run-time libraries: _strtok(), _strtok_l(), strtok_s().
 */

bool TestCrtStrtok(void)
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
 *$Log: TestCrtStrtok.c,v $
 *Revision 1.1  2009/09/29 21:20:52  ddarko
 *strtok test
 *
 *Revision 1.1  2009/09/29 19:00:41  ddarko
 *strdup test
 *
 *Revision 1.2  2009/09/29 18:53:05  ddarko
 *strdup test
 *
 *****************************************************************************/
