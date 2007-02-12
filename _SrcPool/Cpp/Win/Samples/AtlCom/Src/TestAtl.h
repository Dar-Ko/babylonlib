// TestAtl.h : Declaration of the CTestAtl

#ifndef __TESTATL_H_
#define __TESTATL_H_

#include "resource.h"       // main symbols
#include <atlcom.h>
/////////////////////////////////////////////////////////////////////////////
// CTestAtl
class ATL_NO_VTABLE CTestAtl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestAtl, &CLSID_TestAtl>,
	public ITestAtl
{
public:
	CTestAtl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TESTATL)
DECLARE_NOT_AGGREGATABLE(CTestAtl)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestAtl)
	COM_INTERFACE_ENTRY(ITestAtl)
END_COM_MAP()

// ITestAtl
public:
};

#endif //__TESTATL_H_
