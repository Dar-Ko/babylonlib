/*$Workfile: TestCastReinterpret.cpp$: implementation file
  $Revision: 4$ $Date: 2004-11-23 16:51:29$
  $Author: Darko Kolakovic$

  Test C++ compiler conformance.
  Copyright: CommonSoft Inc.
  2004-09-13 Darko Kolakovic
*/

/* Group=Examples                                                            */

#include "TestConformance.h"
#ifndef _T
  #include "KTChar.h"
#endif
#ifndef LOG_EOT
  #include "KTestLog.h"
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);
bool TestCastReinterpret();

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance. Compiler will report an error if
  operator reinterpret_cast is not supported and HAS_NO_REINTERPRET_CAST
  is not defined.

        reinterpret_cast < type-id > ( expression )
  The reinterpret_cast operator allows any pointer to be converted into any
  other pointer type. The reinterpret_cast operator cannot cast away the const
  or volatile attributes.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestCastReinterpret()
{
#if defined (HAS_NO_REINTERPRET_CAST)
  TsWriteToViewLn(_T("HAS_NO_REINTERPRET_CAST"));
  return true;
#else
  TsWriteToViewLn(_T("TestCastReinterpret()"));

  char* szTest = "A verbis ad verbera";
  int iTest = reinterpret_cast<int>(szTest);

  TsWriteToViewLn(LOG_EOT);

  return (iTest != 0);
#endif
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2004-11-22 18:48:19  Darko Kolakovic fixed
 *       unresolved TsWriteToViewLn()
 *  1    Biblioteka1.0         2004-11-22 16:47:08  Darko Kolakovic
 * $
 *****************************************************************************/


