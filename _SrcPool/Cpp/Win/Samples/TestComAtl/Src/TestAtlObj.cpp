/*$Workfile: TestAtlObj.cpp$: implementation file
  $Revision: 3$ $Date: 2007-02-16 14:22:26$
  $Author: Darko Kolakovic$

  Implementation file
  Copyright: CommonSoft Inc.
  2003-08-25 Darko Kolakovic
 */

// TestAtlObj.cpp : Implementation of CTestAtlObj
#include "stdafx.h"
//Note: Compile .idl file first
#include "TestComAtl.h"

#include "TestAtlObj.h"

/////////////////////////////////////////////////////////////////////////////
// CTestAtlObj

//-----------------------------------------------------------------------------
/*Test method performing multiplication by two.

  Returns: S_OK and result of multiplication through pResult.
 */
STDMETHODIMP CTestAtlObj::TestMethod(long lInput, //[in] a number
                                     long *pResult//[out] result of multiplication
                                    )
{
*pResult = 2 * lInput;
return S_OK;
}
