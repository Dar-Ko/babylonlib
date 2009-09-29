/*$RCSfile: TestCrtStrtok.c,v $: implementation file
  $Revision: 1.3 $ $Date: 2009/09/29 21:58:50 $
  $Author: ddarko $

  Test string tokenizer.
  Copyright (c) Microsoft Corporation. All rights reserved.
  MSVC 2003 CRT
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"
#include <string.h> //strtok()
#include "KTestLog.h"

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern const char* g_listTestStringsA[]; //Single-byte character set (SBCS) text samples

//-----------------------------------------------------------------------------
/*Test of finding a token in a string.

  Note: strtok considers consecutive delimiters as single.

  Returns: true if successful, otherwise returns false.

  See also: KStrings.h, strtok_r()
  Microsoft C run-time libraries: _strtok(), _strtok_l(), strtok_s().
 */

bool TestCrtStrtok(void)
{
struct tagTestEntry logEntry =
  {
  _T("strtok()"),
  _T("C run-time libraries"),
  false
  };
int i = 0;
TsWriteToViewLn(_T("TestCrtStrtok()"));



/*Test border case with null pointer*/
logEntry.m_bResult = (strtok(NULL) == NULL);
if (logEntry.m_bResult)
  {
  char string[] = "A string\tof ,,tokens\nand some  more tokens";
  char seps[]   = " ,\t\n";
  char *token;
  char* listTokens[] =
  {
    "A",        //0
    "string",   //1
    "of",       //2
                //consecutive delimiters (" ,,") are swallowed by strtok!
    "tokens",   //3
    "and",      //4
    "some",     //5
    "more       //6
    };
  TsWriteToViewLn(_T("Tokens:"));
  /*Establish string and get the first token: */
  token = strtok(string, seps);
  while(token != NULL)
    {
     /*While there are tokens in "string" */
    printf( " %s\n", token );

    token = strtok( NULL, seps ); /* Get next token:  */
    }

	logEntry.m_bResult = false;
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
 *Revision 1.3  2009/09/29 21:58:50  ddarko
 *strtok test
 *
 *Revision 1.2  2009/09/29 21:51:10  ddarko
 *MSDN example
 *
 *Revision 1.1  2009/09/29 21:20:52  ddarko
 *strtok test
 *
 *****************************************************************************/
/*Feb 20 12:43:59 2003 Manoj Srivastava (srivasta@glaurung.green-gryphon.com)
compares 2 strtok implementations...
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

//--------------------------------------------------------
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
*/
