/*$Workfile: TestAtl7Obj.h$: header file
  $Revision: 4$ $Date: 2007-02-26 18:16:30$
  $Author: Darko Kolakovic$

  COM Object
  Copyright: CommonSoft Inc
  2006-08-25 Darko Kolakovic
 */

#pragma once
#include "resource.h"       // main symbols

#include "TestComAtlNet.h"
#include "DITestAtl7ObjEvents_CP.h"


// CTestAtl7Obj

class ATL_NO_VTABLE CTestAtl7Obj :
  public CComObjectRootEx<CComSingleThreadModel>,
  public CComCoClass<CTestAtl7Obj, &CLSID_TestAtl7Obj>,
  public IConnectionPointContainerImpl<CTestAtl7Obj>,
  public CProxyDITestAtl7ObjEvents<CTestAtl7Obj>,
  public ITestAtl7Obj
{
public:
  CTestAtl7Obj()
  {
  //TODO: Initialize attributes
  }

DECLARE_REGISTRY_RESOURCEID(IDR_TESTATL7OBJ)

DECLARE_NOT_AGGREGATABLE(CTestAtl7Obj)

BEGIN_COM_MAP(CTestAtl7Obj)
  COM_INTERFACE_ENTRY(ITestAtl7Obj)
  COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CTestAtl7Obj)
  CONNECTION_POINT_ENTRY(__uuidof(DITestAtl7ObjEvents))
END_CONNECTION_POINT_MAP()

  DECLARE_PROTECT_FINAL_CONSTRUCT()

  /*Initializes the object instantiated with CoCreateInstance(). The method is
    called immediately after the most derived class is fully constructed if
    the reference count is zero, allowing you to call virtual functions and
    use the reference-counting implementation provided by ATL.

    Returns: S_OK on success or one of the standard error HRESULT values.
   */
  HRESULT FinalConstruct()
  {
  return S_OK;
  }

  /*Deletes the object. Called during object destruction when the last client
    has called IUnknown::Release() on the object, this method frees
    the m_contained member.
   */
  void FinalRelease()
  {
  }

public:

  STDMETHOD(TestMethod)(LONG lInput, LONG* pResult);
};

OBJECT_ENTRY_AUTO(__uuidof(TestAtl7Obj), CTestAtl7Obj)
