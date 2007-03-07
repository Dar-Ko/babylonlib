// MainTAPICtr.h : Declaration of the CMainTAPICtr

#ifndef __MAINTAPICTR_H_
#define __MAINTAPICTR_H_

#include "resource.h"       // main symbols
#include "Tapi3.h"

/////////////////////////////////////////////////////////////////////////////
// CMainTAPICtr
class ATL_NO_VTABLE CMainTAPICtr : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMainTAPICtr, &CLSID_MainTAPICtr>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CMainTAPICtr>,
	public IDispatchImpl<IMainTAPICtr, &IID_IMainTAPICtr, &LIBID_TAPITESTLib>
{
public:
	CMainTAPICtr()
	{
		// Initialize COM
		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		// Create a TAPI entry point object.
		CoCreateInstance(CLSID_TAPI, NULL, CLSCTX_INPROC_SERVER, IID_ITTAPI,(LPVOID *)&gpTapi);

		// Initialize TAPI
		gpTapi->Initialize();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MAINTAPICTR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMainTAPICtr)
	COM_INTERFACE_ENTRY(IMainTAPICtr)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CMainTAPICtr)
END_CONNECTION_POINT_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMainTAPICtr
public:
	STDMETHOD(MyMakeCall)();
	STDMETHOD(ChooseModem)();

private:
	ITTAPI *gpTapi;
	IEnumAddress *pIEnumAddress;
	ITAddress *pAddress;
	ITMediaSupport *pMediaSupport;
};

#endif //__MAINTAPICTR_H_
