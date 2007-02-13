// TestAtlObj.h : Declaration of the CTestAtlObj

#ifndef __TESTATLOBJ_H_
#define __TESTATLOBJ_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestAtlObj
class ATL_NO_VTABLE CTestAtlObj :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CTestAtlObj, &CLSID_TestAtlObj>,
  public ITestAtlObj
{
public:
  CTestAtlObj()
  {
  }

DECLARE_REGISTRY_RESOURCEID(IDR_TESTATLOBJ)
DECLARE_NOT_AGGREGATABLE(CTestAtlObj)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTestAtlObj)
  COM_INTERFACE_ENTRY(ITestAtlObj)
END_COM_MAP()

// ITestAtlObj
public:
  STDMETHOD(TestMethod)(/*[in]*/ long lInput, /*[out]*/ long* pResult);
};

#endif //__TESTATLOBJ_H_
