/*$Workfile: TestAtl7Obj.cpp$: implementation file
  $Revision: 3$ $Date: 2007-02-16 14:22:22$
  $Author: Darko Kolakovic$

  Implementation file
  Copyright: CommonSoft Inc.
  2006-08-25 Darko Kolakovic
 */


#include "stdafx.h"
#include "TestAtl7Obj.h"

////////////////////////////////////////////////////////////////////////////////
// CTestAtl7Obj
//-----------------------------------------------------------------------------
/*Test method performing multiplication by two.

  Returns: S_OK and result of multiplication through pResult.
 */
STDMETHODIMP CTestAtl7Obj::TestMethod(long lInput, //[in] a number
                                      long *pResult//[out] result of multiplication
                                     )
{
USES_CONVERSION;
*pResult = 2 + lInput;
BSTR bstrResult;
Fire_TestAtlEvent(T2BSTR(_T("TestMethod")), &bstrResult);
return S_OK;
}
