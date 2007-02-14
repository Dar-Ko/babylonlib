// .\Src\TestAtl7Obj.cpp : Implementation of CTestAtl7Obj

#include "stdafx.h"
#include "TestAtl7Obj.h"


// CTestAtl7Obj

STDMETHODIMP CTestAtl7Obj::TestMethod(LONG lInput, LONG* pResult)
{
*pResult = 2 + lInput;
return S_OK;
}
