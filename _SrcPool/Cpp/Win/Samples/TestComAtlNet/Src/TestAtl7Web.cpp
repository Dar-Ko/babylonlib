// .\Src\TestAtl7Web.cpp : Implementation of CTestAtl7Web

#include "stdafx.h"
#include "TestAtl7Web.h"


// CTestAtl7Web

STDMETHODIMP CTestAtl7Web::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITestAtl7Web
	};

	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
