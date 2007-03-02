/*$Workfile: TestAtl7Obj.cpp$: implementation file
  $Revision: 4$ $Date: 2007-03-01 00:10:10$
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
/*Initializes the object instantiated with CoCreateInstance(). The method is
  called immediately after the most derived class is fully constructed if
  the reference count is zero, allowing you to call virtual functions and
  use the reference-counting implementation provided by ATL.

  Returns: S_OK on success or one of the standard error HRESULT values.
*/
HRESULT CTestAtl7Obj::FinalConstruct()
{
//Inserted by the MSVC ATL Wizard
return S_OK;
}

//-----------------------------------------------------------------------------
/*Deletes the object. Called during object destruction when the last client
  has called IUnknown::Release() on the object, this method frees
  the m_contained member.
*/
void CTestAtl7Obj::FinalRelease()
{
//Inserted by the MSVC ATL Wizard
}

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

//-----------------------------------------------------------------------------
/*
 */
STDMETHODIMP CTestAtl7Obj::get_Long(LONG* pVal //[out]
                                   )
{
  // TODO: Add your implementation code here

return S_OK;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
* $Log: 
*  4    Biblioteka1.3         2007-03-01 00:10:10  Darko Kolakovic TestCounter
*       property
*  3    Biblioteka1.2         2007-02-16 14:22:22  Darko Kolakovic Header
*  2    Biblioteka1.1         2007-02-15 20:33:39  Darko Kolakovic Fire an event
*  1    Biblioteka1.0         2007-02-14 16:56:11  Darko Kolakovic 
* $
*****************************************************************************/
