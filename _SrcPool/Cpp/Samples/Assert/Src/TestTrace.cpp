/*$Workfile: S:\_SrcPool\Cpp\Samples\Assert\Src\TestTrace.cpp$: implementation file
  $Revision: 6$ $Date: 2004-11-05 12:27:09$
  $Author: Darko Kolakovic$

  Test tracing
  Copyright: CommonSoft Inc.
  2004-09-13 Darko Kolakovic
*/

/* Group=Examples                                                            */
#include "stdafx.h"

#if defined(__MWERKS__)/* Metrowerks CodeWarrior Compiler                    */
  #include <wchar_t.h>
  #include "KTChar.h" //LPCTSTR typedef
#else
  #include <tchar.h>
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);
bool TestTrace();

/*---------------------------------------------------------------------------*/
/*Test tracing. Tracing reports warnings to an output device, such as 
  the debugger window.

  Returns true if test is successful; otherwise returns false.
 */
bool TestTrace()
{
bool bResult = true;
TsWriteToViewLn(_T("TestTrace()"));

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

TRACEINFO(_T("This is a TRACEINFO message (100)\n"));
TRACEINFO(_T("This is a TRACEINFO(%s, %d)\n"), _T("message"), 101);
TRACE(_T("This is TRACE message\n"));
TRACE(_T("This is TRACE(%s, %d, %d, %d)\n"), _T("message"), 102, 1, 2);

TRACE0("This is TRACE0 message\n");
TRACE1("This is TRACE1(%d)\n", 103);
TRACE2("This is TRACE2(%s, %d)\n", _T("message"), 104);
TRACE3("This is TRACE3(%s, %d, %d)\n", _T("message"), 105, 3);


TsWriteToViewLn(LOG_EOT);

return bResult;
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2004-11-05 12:27:09  Darko Kolakovic Moved Palm
 *       specifics to separate header files
 *  5    Biblioteka1.4         2004-11-01 11:07:22  Darko Kolakovic CodeWarrior
 *       KMESSAGE
 *  4    Biblioteka1.3         2004-10-28 01:19:21  Darko           Unicode build
 *       PalmOS
 *  3    Biblioteka1.2         2004-10-25 16:58:08  Darko Kolakovic CodeWarrior 9
 *       fixes
 *  2    Biblioteka1.1         2004-10-22 11:46:54  Darko Kolakovic CodeWarrior
 *  1    Biblioteka1.0         2004-09-13 14:30:08  Darko           
 * $
 *****************************************************************************/
