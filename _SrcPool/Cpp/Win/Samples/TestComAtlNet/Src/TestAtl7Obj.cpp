// .\Src\TestAtl7Obj.cpp : Implementation of CTestAtl7Obj

#include "stdafx.h"
#include "TestAtl7Obj.h"


// CTestAtl7Obj

STDMETHODIMP CTestAtl7Obj::TestMethod(LONG lInput, LONG* pResult)
{
USES_CONVERSION;
*pResult = 2 + lInput;
BSTR bstrResult;
Fire_TestAtlEvent(T2BSTR(_T("TestMethod")), &bstrResult);
return S_OK;
}
