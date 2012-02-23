#include "KDbgReport.h"

#ifdef _DEBUG
#define MAX_MSG     1024 //Maximum debugging message length

extern "c"
{
int __cdecl DbgReport(LPCTSTR szModule, LPCTSTR szFormat, ... );
}

//-----------------------------------------------------------------------------
/*
 */
int __cdecl DbgReport(LPCTSTR szModule, //[in] name of module
                       //(.exe or .dll) where assert/report occurred.
                      LPCTSTR szFormat, //[in] format-control
                       //string used to create the user message.
                      ...               //[in] optional
                       //substitution arguments used by szFormat.
                      )
{
TCHAR szOutMessage[MAX_MSG];
int iTail = 0;
if (szModule != NULL)
  {
  _tstrcpy(szOutMessage, szModule);
  iTail = strlen(szOutMessage);
  szOutMessage[iTail++] = TEXT(':');
  szOutMessage[iTail++] = TEXT(' ');
  }

//Append listed arguments
va_list pvaArgs;
va_start(pvaArgs, szFormat);
_vsntprintf(szOutMessage + iTail, MAX_MSG - iTail - 2, szFormat, pvaArgs);
va_end(pvaArgs);

_tcscat(szOutMessage, TEXT(CST_EOL)); //Append End-of-Line

OutputDebugString(szOutMessage); //Output to debugger window
return 0;
}
///////////////////////////////////////////////////////////////////////////////
#endif // _DEBUG