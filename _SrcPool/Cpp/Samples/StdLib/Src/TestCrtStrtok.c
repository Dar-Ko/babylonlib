/*$RCSfile: TestCrtStrtok.c,v $: implementation file
  $Revision: 1.5 $ $Date: 2011/04/25 20:31:06 $
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

#ifdef _MSC_VER
  #ifdef _INC_STRING /*Microsoft string.h header file*/
    /*Microsoft CRT _srttok does not handle null pointers*/
    #define STRTOK_NULLEXCEPTION TsWriteToView(_T("Failed test ")) // TODO: exception handler
    #define TRY_EXC __try
    #define CATCH_EXC(e) __except(STRTOK_NULLEXCEPTION, EXCEPTION_EXECUTE_HANDLER)
  #endif
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern const char* g_listTestStringsA[]; //Single-byte character set (SBCS) text samples

//-----------------------------------------------------------------------------
/*Test of finding a token in a string.

  Note: strtok considers consecutive delimiters as single.

  Returns: true if successful, otherwise returns false.

  See also: KStrings.h, strtok_r()
  Microsoft C run-time libraries: strtok(), _strtok_l(), strtok_s().
 */
bool TestCrtStrTok(void)
{
struct tagTestEntry logEntry =
  {
  _T("strtok()"),
  _T("C run-time libraries"),
  false
  };

TsWriteToViewLn(_T("TestCrtStrTok()"));

/*Test border case with null pointer*/
TRY_EXC
  {
  logEntry.m_bResult = (strtok(NULL, NULL) == NULL);
  }
CATCH_EXC(seh)
  {
  unsigned long nExc = GetExceptionCode();
  TRACE1("strtok(NULL, NULL) is not supported (Error: 0x%x).\n", nExc);
  //Microsoft CRT results with Access Violation exception  0xC0000005

  logEntry.m_szObjectName = _T("strtok(NULL, NULL)");
  logEntry.m_bResult = false;
  LogTest(&logEntry);
  TsWriteToViewLn(logEntry.m_szObjectName);

  //Roll back log entry  
  logEntry.m_szObjectName = _T("strtok()");
  logEntry.m_bResult = true;
  }

if (logEntry.m_bResult)
  {
  int i = 0;
  char listSeparators[]   = " ,\t\n";
  char szSource[] = "A string\tof ,,tokens\nand some  more tokens";
  char* szToken;
  char* listTokens[] =
    {
    "A",        //0
    "string",   //1
    "of",       //2
                //consecutive delimiters (" ,,") are swallowed by strtok!
    "tokens",   //3
    "and",      //4
    "some",     //5
    "more",     //6
    "tokens"    //7
    };
  TsWriteToViewLn(_T("Tokens:"));
  /*Establish source and get the first token*/
  szToken = strtok(szSource, listSeparators);
  while(szToken != NULL) /*While there are tokens in source*/
    {
    TsWriteToViewLn(szToken);
    logEntry.m_bResult = (strcmp(szToken, listTokens[i]) == 0); 
    if (!logEntry.m_bResult)
      {
      TsWriteToViewLn(_T("Failed test"));
      break;
      }
    szToken = strtok(NULL, listSeparators); /*Get next token*/
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
 *Revision 1.5  2011/04/25 20:31:06  ddarko
 *Updated test case
 *
 *Revision 1.4  2009/09/30 20:55:29  ddarko
 *MSVC: handling SEH exception
 *
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
