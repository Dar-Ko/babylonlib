/*$Workfile: TestCastConst.cpp$: implementation file
  $Revision: 4$ $Date: 2004-11-23 15:51:24$
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
bool TestCastConst();

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance. Compiler will report an error if
  operator const_cast is not supported and HAS_NO_CONST_CAST is not defined.

        const_cast < type-id > ( expression )
  The const_cast operator can be used to remove the const or volatile
  attribute from a class.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestCastConst()
{
#if defined (HAS_NO_CONST_CAST)
  TsWriteToViewLn(_T("HAS_NO_CONST_CAST"));
  return true;
#else
  TsWriteToViewLn(_T("TestCastConst()"));

  const char* szValue = "A verbis ad verbera";
  char* szTest = NULL;
  szTest = const_cast<char*>(szValue);

  TsWriteToViewLn(LOG_EOT);

  return (szTest != NULL);
#endif
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2004-11-22 18:48:14  Darko Kolakovic fixed
 *       unresolved TsWriteToViewLn()
 *  1    Biblioteka1.0         2004-11-22 16:47:01  Darko Kolakovic
 * $
 *****************************************************************************/


