/*$RCSfile: regobj.h,v $: header file
  $Revision: 1.2 $ $Date: 2008/07/15 20:37:10 $
  $Author: ddarko $

	Declaration of the CRegObject
  This is a part of the Active Template Library.
  Copyright: (C) 1996-1998 Microsoft Corporation. All rights reserved.
  PSDK 2006-03 (R2 3790.2075) Win DDK 2005-03 (3790.1830)
 */
// Group=Windows

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #ifdef _MSC_VER
    //Microsoft Visual C/C++ compiler
    #pragma message ("   #include " __FILE__ )
  #endif
#endif

/////////////////////////////////////////////////////////////////////////////
// register

class ATL_NO_VTABLE CDLLRegObject : public CRegObject, public CComObjectRoot,
            public CComCoClass<CDLLRegObject, &CLSID_Registrar>
{
public:
  CDLLRegObject() {}
  ~CDLLRegObject(){CRegObject::ClearReplacements();}

BEGIN_COM_MAP(CDLLRegObject)
  COM_INTERFACE_ENTRY(IRegistrar)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(CDLLRegObject)
  HRESULT FinalConstruct()
  {
    return CComObjectRoot::FinalConstruct();
  }
  void FinalRelease()
  {
    CComObjectRoot::FinalRelease();
  }
//we can't use the component because that's what we're registering
//we don't want to do the static registry because we'd have extra code
  static HRESULT WINAPI UpdateRegistry(BOOL bRegister)
  {
    CComObject<CDLLRegObject>* p;
    CComObject<CDLLRegObject>::CreateInstance(&p);
    CComPtr<IRegistrar> pR;
    p->QueryInterface(IID_IRegistrar, (void**)&pR);
    return AtlModuleUpdateRegistryFromResourceD(&_Module,
      (LPCOLESTR)MAKEINTRESOURCE(IDR_Registrar), bRegister, NULL, pR);
  }
};
////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: regobj.h,v $
 * Revision 1.2  2008/07/15 20:37:10  ddarko
 * Borland CC build and fixes
 *
 * Revision 1.1.2.1  2008/07/15 15:42:57  ddarko
 * ATL 3.00 Platform SDK (R2 3790.2075) 2006-03 / Borland CC build
 *
 *****************************************************************************/
