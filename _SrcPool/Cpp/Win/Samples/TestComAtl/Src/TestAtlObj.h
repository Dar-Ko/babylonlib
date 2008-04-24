/*$Workfile: TestAtlObj.h$: header file
  $Revision: 2$ $Date: 2007-02-16 14:22:27$
  $Author: Darko Kolakovic$

  Interface of the CTestButtonDlg class
  Copyright: CommonSoft Inc
  2003-08-25 Darko Kolakovic
 */

#ifndef __TESTATLOBJ_H_
#define __TESTATLOBJ_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestAtlObj
class ATL_NO_VTABLE CTestAtlObj :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CTestAtlObj, &CLSID_TestAtlObj>,
  public ITestAtlObj,
  public IObjectWithSite
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
  COM_INTERFACE_ENTRY(IObjectWithSite)
END_COM_MAP()

// IObjectWithSite
// Note: the interface is added after the wizard created the project files.
// The interface is required for occasion of a dynamically created control.
public:
  STDMETHOD(SetSite)(IUnknown* pUnkSite);
  STDMETHOD(GetSite)(REFIID riid, void** ppvSite);

// ITestAtlObj
public:
  STDMETHOD(TestMethod)(/*[in]*/ long lInput, /*[out]*/ long* pResult);

};

#endif //__TESTATLOBJ_H_
