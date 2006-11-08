/*$Workfile: TestDumpMemHeap.cpp$: implementation file
  $Revision: 2$ $Date: 2004-11-09 19:46:08$
  $Author: Darko Kolakovic$

  Test tracing memeory heap information.
  Copyright: CommonSoft Inc
  2004-11-06 Darko Kolakovic
 */

// Group=Examples
#ifndef _STDAFX_H_
  #include "stdafx.h"
#endif
#include <HostControl.h>
#if defined(__MWERKS__)/* Metrowerks CodeWarrior Compiler                    */
  #include <wchar_t.h>
  #include "KTChar.h" //LPCTSTR typedef
#else
  #include <tchar.h>
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern void DumpMemHeap(void);
bool TestDumpMemHeap(void);


/*----------------------------------------------------------------------------*/
/*Test tracing heap information, including ROM and RAM based heaps.

  Returns true if test is successful; otherwise returns false.
 */
bool TestDumpMemHeap()
{
bool bResult = true;
TsWriteToViewLn(_T("TestDumpMemHeap()"));
#ifdef _DEBUG
  DumpMemHeap();
#endif
TsWriteToViewLn(LOG_EOT);

return bResult;
}
/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-11-09 19:46:08  Darko Kolakovic implemented
 *       TsWriteToViewLn
 *  1    Biblioteka1.0         2004-11-05 13:25:14  Darko Kolakovic 
 * $
 ******************************************************************************/
