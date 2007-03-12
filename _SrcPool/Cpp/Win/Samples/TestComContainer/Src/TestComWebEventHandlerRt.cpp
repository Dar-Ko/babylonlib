/*$Workfile: TestComWebEventHandlerRt.cpp$: implementation file
  $Revision: 3$ $Date: 2007-03-11 02:21:39$
  $Author: Darko$

  Implementation file
  Copyright: CommonSoft Inc.
  2006-09-01 Darko Kolakovic
*/

#define __STDC_LIMIT_MACROS
#include "stdafx.h"
#ifndef uint32_t
  #include "KType32.h"
#endif
#include "STL/KOStream.h" //_tcout
#include "TestComWebEventHandlerRt.h"

TestComWebEventHandlerRt::TestComWebEventHandlerRt(void) :
    TESTCOUNTMAX(3),
    m_nTickCounter(0),
    m_clSignal(TRUE, FALSE) //state of the event object is nonsignaled
{
ATLTRACE("TestComWebEventHandlerRt::TestComWebEventHandlerRt()\n");
}

TestComWebEventHandlerRt::~TestComWebEventHandlerRt(void)
{
ATLTRACE("TestComWebEventHandlerRt::~TestComWebEventHandlerRt()\n");
}

//------------------------------------------------------------------------------
/*Helper for finding the function index for a DISPID. This helper is required
  when the type library is not available or when some special manipulation is
  neccessary.

    struct _ATL_FUNC_INFO
      {
      CALLCONV cc;         //the calling convention.
      VARTYPE vtReturn;    //variant type of the function return value.
      SHORT nParams;       //number of function parameters.
      VARTYPE pVarTypes[_ATL_MAX_VARTYPES]; //array of variant types 
                                            //of the function parameters. 
      };
  
  Returns: HRESULT value and type information used to describe a method or 
  property on a dispinterface.
 */
HRESULT TestComWebEventHandlerRt::GetFuncInfoFromId(const IID& iid,     //[in]
                                          //reference to the ID of the function. 
                                                    DISPID dispidMember,//[in]
                                          //dispatch ID of the function.
                                                    LCID lcid,          //[in]
                                          //locale context of the function ID. 
                                                    _ATL_FUNC_INFO& info//[out]
                           //structure describing the function type and arguments.
                                                    )
{
ATLTRACE("TestComWebEventHandlerRt::GetFuncInfoFromId(dispid = %d)\n", dispidMember);

//Initialise structure describing the function type and arguments
if (InlineIsEqualGUID(iid, DIID_DITestAtl7WebEvents))
  {
  //When IDispEventSimpleImpl is used, cc member must be CC_STDCALL. 
  info.cc = CC_STDCALL; 
  switch(dispidMember)
    {
    case DISPID_TESTATL7EVENT: //[id(DISPID_TESTATL7EVENT)] HRESULT TestAtlEvent([in] BSTR bstrValue)
      info.vtReturn = VT_I4;
      info.nParams = 1;
      info.pVarTypes[0] = VT_BSTR;
      break;

    default:
      return E_FAIL;
    }
  }
return S_OK;
}

//-----------------------------------------------------------------------------
/*This implementation of IDispatch::Invoke calls the event handlers listed 
  in the event sink map.
  To obtain the dispatch identifier, use GetIDsOfNames or the object's 
  documentation. 

  Flags describing call context:

    DISPATCH_METHOD         The member is invoked as a method. If a property 
                            has the same name, both this and 
                            the DISPATCH_PROPERTYGET flag may be set. 
    DISPATCH_PROPERTYGET    The member is retrieved as a property or data member. 
    DISPATCH_PROPERTYPUT    The member is changed as a property or data member. 
    DISPATCH_PROPERTYPUTREF The member is changed by a reference assignment, 
                             rather than a value assignment.  
 
  Returns: S_OK or one of the errors: DISP_E_BADPARAMCOUNT, DISP_E_BADVARTYPE, 
  DISP_E_EXCEPTION, DISP_E_MEMBERNOTFOUND, DISP_E_NONAMEDARGS, DISP_E_OVERFLOW, 
  DISP_E_PARAMNOTFOUND, DISP_E_TYPEMISMATCH, DISP_E_UNKNOWNINTERFACE, 
  DISP_E_UNKNOWNLCID, DISP_E_PARAMNOTOPTIONAL.

  See also: IDispatch::Invoke()
 */
STDMETHODIMP TestComWebEventHandlerRt::Invoke(DISPID dispidMember, //[in] dispatch
                                              //identifier
                                              REFIID riid, //[in] reserved
                            //for future use. Must be IID_NULL. 
                                              LCID lcid, //[in] locale context 
                                              WORD wFlags, //[in] flags  
                                              //describing the context
                                              DISPPARAMS* pdispparams, //[in]
                                              //array of arguments
                                              VARIANT* pvarResult, //[out] 
                            //the result returned by invoked member or NULL 
                                              EXCEPINFO* pexcepinfo, //[out]
                            //exception information or NULL
                                              UINT* puArgErr //[out] index
                            // within rgvarg of the first argument that has 
                            //an error.
                                              )
{
ATLTRACE("TestComWebEventHandlerRt::Invoke(dispid = %d)\n", dispidMember);
return IDispEventSimpleImpl<ID_TESTCOMSINK, 
                           TestComWebEventHandlerRt, 
                           &DIID_DITestAtl7WebEvents>::Invoke(dispidMember, 
                                                              riid,
                                                              lcid, 
                                                              wFlags, 
                                                              pdispparams, 
                                                              pvarResult,
                                                              pexcepinfo, 
                                                              puArgErr
                                                              );
}

//------------------------------------------------------------------------------
/*Event handler for:
      [id(DISPID_TESTATL7EVENT)] HRESULT TestAtlEvent([in] BSTR bstrValue);
 */
STDMETHODIMP TestComWebEventHandlerRt::OnTestAtlEvent(BSTR bstrValue //[in]
                                                     )
{
ATLTRACE("TestComWebEventHandlerRt::OnTestAtlEvent()\n");
//ATLASSERT(m_nTickCounter < UINT32_MAX);
//Output string to the console
std::_tcout << _T("Event Received") << std::endl;
m_nTickCounter++; //count events fired
if (!m_clSignal.Pulse()) //Signal to the message loop
  return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, GetLastError());
if (m_nTickCounter > TESTCOUNTMAX)
  return E_FAIL;

return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
* $Log: 
*  3    Biblioteka1.2         2007-03-11 02:21:39  Darko           Event sink and 
*       apartman message loop
*  2    Biblioteka1.1         2007-03-08 21:40:25  Darko Kolakovic Event sink
*  1    Biblioteka1.0         2007-03-06 19:00:44  Darko Kolakovic 
* $
*****************************************************************************/
/*
///////////////////////////////////////////////////////////////////////////////
#include <atlcom.h> //IDispEventImpl
/ *The object of this class, also called a sink, handles (sinks) events 
generated (fired) by the COM server or the event source.
The classs implements COM server's outgoing {html:<code>}dispinterface{html:</code>} 
interface. This interface is declared in the type-library of the server. For 
every distinct event, the server (connectable object) will call the methods 
of this interface. The client (subscriber) informs the server about the event
handler through the {html:<code>}IConnectionPoint{html:</code>} interface.
Every connection consists of a client-supplied event sink and an identifying 
cookie.
* /
class CSinkObjNI : public IDispEventImpl<ID_TESTCOMSINK, CSinkObjNI>
{
  //Requires AtlGetObjectSourceInterface() to extract information from the type library. Use of AtlGetObjectSourceInterface() requires that the COM object firing the event implement either IProvideClassInfo2 or IPersist*:
public:
  BEGIN_SINK_MAP(CSinkObjNI)
    SINK_ENTRY(ID_TESTCOMSINK, 1 / *DISPID* /, OnTestAtlEvent / *Event Handler* /)
  END_SINK_MAP()
  // event handler for event defined in IDL as
  // HRESULT TestAtlEvent([in] BSTR bstrValue);
};

class CSinkObj : public IDispEventImpl<ID_TESTCOMSINK, CSinkObj,
  &DIID_DITestAtl7WebEvents, // Source interface GUID.
  &LIBID_TestComAtlNetLib, // typelib ID containing source interface.
  1,                // major version number of LIBID_...
  0>                // minor version number of LIBID_...
{
public:
  BEGIN_SINK_MAP(CSinkObj)
    SINK_ENTRY_EX(ID_TESTCOMSINK, DIID_DITestAtl7WebEvents, 1, OnTestAtlEvent)
  END_SINK_MAP()
  // event handler for event defined in IDL as
  // HRESULT TestAtlEvent([in] BSTR bstrValue);
  HRESULT __stdcall OnTestAtlEvent(BSTR bstrValue)
  {
    ATLTRACE("CSinkObj::OnTestAtlEvent()\n");
    return S_OK;
  }

};
*/