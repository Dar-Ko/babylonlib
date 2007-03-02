/*$Workfile: TestAtl7Obj.h$: header file
  $Revision: 6$ $Date: 2007-03-01 20:09:50$
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
  HRESULT FinalConstruct();
  void FinalRelease();

public:

  STDMETHOD(TestMethod)(LONG lInput, LONG* pResult);
  STDMETHOD(get_Long)(LONG* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(TestAtl7Obj), CTestAtl7Obj)


/*Group COM classes into categories when the module is registered.
  If Standard Component Categories Manager is installed on the system, each 
  class that has an associated OBJECT_ENTRY_AUTO or 
  OBJECT_ENTRY_NON_CREATEABLE_EX_AUTO will be categorized.
  Microsoft Specific: (uuid) attribute can be applied in a redeclaration.
*/
struct __declspec(uuid("{BAB17049-D0DE-4241-4149-4C4F4E4C4942}")) CATID_BABYLONLIB;
struct __declspec(uuid("{BAB17049-D0DE-4886-A995-6E2BE7F1E7E2}")) CATID_BABYLONLIBTEST;

BEGIN_CATEGORY_MAP(CTestAtl7Obj)
  IMPLEMENTED_CATEGORY(__uuidof(CATID_BABYLONLIB))
  IMPLEMENTED_CATEGORY(__uuidof(CATID_BABYLONLIBTEST))
END_CATEGORY_MAP()

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
* $Log: 
*  6    Biblioteka1.5         2007-03-01 20:09:50  Darko Kolakovic Test setting a
*       property
*  5    Biblioteka1.4         2007-03-01 00:10:10  Darko Kolakovic TestCounter
*       property
*  4    Biblioteka1.3         2007-02-26 18:16:30  Darko Kolakovic IDispatch
*  3    Biblioteka1.2         2007-02-16 14:22:24  Darko Kolakovic Header
*  2    Biblioteka1.1         2007-02-15 20:33:41  Darko Kolakovic Fire an event
*  1    Biblioteka1.0         2007-02-14 16:56:12  Darko Kolakovic 
* $
*****************************************************************************/
