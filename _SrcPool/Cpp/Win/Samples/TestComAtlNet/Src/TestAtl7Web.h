/*$Workfile: TestAtl7Web.h$: header file
  $Revision: 3$ $Date: 2007-03-01 20:09:52$
  $Author: Darko Kolakovic$

  COM Object
  Copyright: CommonSoft Inc
  2006-08-30 Darko Kolakovic
*/

#pragma once
#include "resource.h"       // main symbols

#include "TestComAtlNet.h"
#include "DITestAtl7WebEvents_CP.h"

///////////////////////////////////////////////////////////////////////////////
// CTestAtl7Web

class ATL_NO_VTABLE CTestAtl7Web :
  //COM object implementation
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CTestAtl7Web, &CLSID_TestAtl7Web>,
  
  public ISupportErrorInfo,
  public IConnectionPointContainerImpl<CTestAtl7Web>,
  public CProxyDITestAtl7WebEvents<CTestAtl7Web>,
  public IDispatchImpl<ITestAtl7Web, &IID_ITestAtl7Web, &LIBID_TestComAtlNetLib, 
                        /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
  CTestAtl7Web();

DECLARE_REGISTRY_RESOURCEID(IDR_TESTATL7WEB)

DECLARE_NOT_AGGREGATABLE(CTestAtl7Web)
DECLARE_CLASSFACTORY_SINGLETON(CTestAtl7Web)

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
  HRESULT FinalConstruct();
  void    FinalRelease();
  virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, 
                                                  LPOLESTR *rgszNames,
                                                  UINT cNames,
                                                  LCID lcid,
                                                  DISPID *rgDispId);

public:
  STDMETHOD(TestMethod)(void);
  STDMETHOD(GetMethod)(LONG* pVal);
  STDMETHOD(Long)(LONG* pVal);
  STDMETHOD(get_TestCounter)(long lInput, LONG* pVal);
  STDMETHOD(get_String)(BSTR* pVal);
  STDMETHOD(put_String)(BSTR newVal);
  STDMETHOD(GetString)(BSTR* pVal);
  STDMETHOD(SetString)(BSTR newVal);

//Attributes
public:
  long     m_lTestCount;   //test counter
  CComBSTR m_bstrTestText; //test message
};

OBJECT_ENTRY_AUTO(__uuidof(TestAtl7Web), CTestAtl7Web)

                                       
/*Group COM classes into categories when the module is registered.
  If Standard Component Categories Manager is installed on the system, each 
  class that has an associated OBJECT_ENTRY_AUTO or 
  OBJECT_ENTRY_NON_CREATEABLE_EX_AUTO will be categorized.
  Microsoft Specific: (uuid) attribute can be applied in a redeclaration.
 */
struct __declspec(uuid("{BAB17049-D0DE-4241-4149-4C4F4E4C4942}")) CATID_BABYLONLIB;
struct __declspec(uuid("{BAB17049-D0DE-4886-A995-6E2BE7F1E7E2}")) CATID_BABYLONLIBTEST;
 
BEGIN_CATEGORY_MAP(CTestAtl7Web)
  IMPLEMENTED_CATEGORY(__uuidof(CATID_BABYLONLIB))
  IMPLEMENTED_CATEGORY(__uuidof(CATID_BABYLONLIBTEST))
END_CATEGORY_MAP()


///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
* $Log: 
*  3    Biblioteka1.2         2007-03-01 20:09:52  Darko Kolakovic Test setting a
*       property
*  2    Biblioteka1.1         2007-03-01 00:10:13  Darko Kolakovic TestCounter
*       property
*  1    Biblioteka1.0         2007-02-26 18:16:14  Darko Kolakovic 
* $
*****************************************************************************/
