/*$Workfile: S:\_SrcPool\Cpp\Win\Samples\TestComAtlNet\Src\TestAtl7Web.h$: header file
  $Revision: 1$ $Date: 2007-02-26 18:16:14$
  $Author: Darko Kolakovic$

  COM Object
  Copyright: CommonSoft Inc
  2006-08-30 Darko Kolakovic
*/

#pragma once
#include "resource.h"       // main symbols

#include "TestComAtlNet.h"
#include "DITestAtl7WebEvents_CP.h"


// CTestAtl7Web

class ATL_NO_VTABLE CTestAtl7Web : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTestAtl7Web, &CLSID_TestAtl7Web>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CTestAtl7Web>,
	public CProxyDITestAtl7WebEvents<CTestAtl7Web>, 
	public IDispatchImpl<ITestAtl7Web, &IID_ITestAtl7Web, &LIBID_TestComAtlNetLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CTestAtl7Web()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TESTATL7WEB)

DECLARE_NOT_AGGREGATABLE(CTestAtl7Web)

BEGIN_COM_MAP(CTestAtl7Web)
	COM_INTERFACE_ENTRY(ITestAtl7Web)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTestAtl7Web)
	CONNECTION_POINT_ENTRY(__uuidof(DITestAtl7WebEvents))
END_CONNECTION_POINT_MAP()
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:

};

OBJECT_ENTRY_AUTO(__uuidof(TestAtl7Web), CTestAtl7Web)
