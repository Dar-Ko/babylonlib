/*$Workfile: S:\_SrcPool\Cpp\Samples\Assert\Src\TestTraceC.c$: implementation file
  $Revision: 7$ $Date: 2004-11-09 18:46:13$
  $Author: Darko Kolakovic$

  Test tracing in C functions
  Copyright: CommonSoft Inc.
  2004-09-13 Darko Kolakovic
*/

/* Group=Examples                                                            */
#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);
bool TestTraceC();

/*---------------------------------------------------------------------------*/
/*Test tracing. Tracing reports warnings to an output device, such as 
  the debugger window.

  Returns true if test is successful; otherwise returns false.
 */
bool TestTraceC()
{
bool bResult = true;
TsWriteToViewLn(_T("TestTraceC()"));

/*Testing preprocessor's message output*/
#if defined (_MSC_VER) || defined (__MWERKS__)
  /*Microsoft Visual Studio C/C++ or
    *Metrowerks CodeWarrior preprocessor
   */
  #pragma message( __FILE__ " Your pragma message ") 
#else
  /*Unknown preprocessor*/
  #pragma message( __FILE__ " Your pragma message ") 
#endif

/*Testing customized preprocessor's message output*/
#pragma KMESSAGE(Your KMESSAGE message)
 
TRACEINFO(_T("This is a TRACEINFO message (200)\n"));
TRACEINFO(_T("This is a TRACEINFO(%s, %d)\n"), _T("message"), 201);
TRACE(_T("This is TRACE message\n"));
TRACE(_T("This is TRACE(%s, %d, %d, %d)\n"), _T("message"), 202, 1, 2);

TRACE0("This is TRACE0 message\n");
TRACE1("This is TRACE1(%d)\n", 203);
TRACE2("This is TRACE2(%s, %d)\n", _T("message"), 204);
TRACE3("This is TRACE3(%s, %d, %d)\n", _T("message"), 205, 3);

#if (defined _UNICODE) || (defined UNICODE) || (defined _MBCS)
  TRACE2("This is TRACE2(%ws, %d)\n", _T("message"), 206);
  TRACE3("This is TRACE3(%ws, %d, %d)\n", _T("message"), 207, 4);
#endif /*_UNICODE*/

TsWriteToViewLn(LOG_EOT);

return bResult;
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: 
 *  7    Biblioteka1.6         2004-11-09 18:46:13  Darko Kolakovic implemented
 *       TsWriteToViewLn
 *  6    Biblioteka1.5         2004-11-05 12:27:11  Darko Kolakovic Moved Palm
 *       specifics to separate header files
 *  5    Biblioteka1.4         2004-11-01 11:07:24  Darko Kolakovic CodeWarrior
 *       KMESSAGE
 *  4    Biblioteka1.3         2004-10-28 01:19:22  Darko           Unicode build
 *       PalmOS
 *  3    Biblioteka1.2         2004-10-25 16:58:15  Darko Kolakovic CodeWarrior 9
 *       fixes
 *  2    Biblioteka1.1         2004-10-22 11:46:57  Darko Kolakovic CodeWarrior
 *  1    Biblioteka1.0         2004-09-13 14:30:10  Darko           
 * $
 *****************************************************************************/
