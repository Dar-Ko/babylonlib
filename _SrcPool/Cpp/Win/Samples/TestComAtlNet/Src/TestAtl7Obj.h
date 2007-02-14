// .\Src\TestAtl7Obj.h : Declaration of the CTestAtl7Obj

#pragma once
#include "resource.h"       // main symbols

#include "TestComAtlNet.h"
#include "_ITestAtl7ObjEvents_CP.h"


// CTestAtl7Obj

class ATL_NO_VTABLE CTestAtl7Obj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestAtl7Obj, &CLSID_TestAtl7Obj>,
	public IConnectionPointContainerImpl<CTestAtl7Obj>,
	public CProxy_ITestAtl7ObjEvents<CTestAtl7Obj>, 
	public ITestAtl7Obj
{
public:
	CTestAtl7Obj()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TESTATL7OBJ)

DECLARE_NOT_AGGREGATABLE(CTestAtl7Obj)

BEGIN_COM_MAP(CTestAtl7Obj)
	COM_INTERFACE_ENTRY(ITestAtl7Obj)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTestAtl7Obj)
	CONNECTION_POINT_ENTRY(__uuidof(_ITestAtl7ObjEvents))
END_CONNECTION_POINT_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

  STDMETHOD(TestMethod)(LONG lInput, LONG* pResult);
};

OBJECT_ENTRY_AUTO(__uuidof(TestAtl7Obj), CTestAtl7Obj)
