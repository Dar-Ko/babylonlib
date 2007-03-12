/*$Workfile: TestComWebEventHandlerRt.h$: header file
  $Revision: 3$ $Date: 2007-03-11 02:21:39$
  $Author: Darko$

  COM Event Sink with run-time binding
  Copyright: CommonSoft Inc
  2006-09-01 Darko Kolakovic
*/

// Group=Examples

#pragma once
#include <atlbase.h>
#include <atlcom.h>
#include <atlsync.h>

#include "TestComAtlNet.h" //DIID

const UINT ID_TESTCOMSINK = 20060830; //arbitrary positive integer as a unique 
//identifier for the source object. 

///////////////////////////////////////////////////////////////////////////////
// TestComWebEventHandlerRt

/*The TestComWebEventHandlerRt implements an event sink object by handling the
  events from the subscribed COM service. Base class is IDispEventSimpleImpl,
  used when a type library describing the event interface is not available or 
  avoiding the overhead associated with using the type library is required.
  The source interface ID is specified as an template argument and the type
  library is not required. The calling convention for the event handlers 
  must be CC_STDCALL (__stdcall) when IDispEventSimpleImpl is used.
  The events are mapped to the handlers with SINK_ENTRY_EX macro and the
  description of the event source interface method is obtained at run time.
  This offers a little more flexibility and is a trade off of speed over size.
 */
class TestComWebEventHandlerRt :
  public IDispEventSimpleImpl<ID_TESTCOMSINK, //an arbitrary positive integer 
                                    //as the identifier for the source object.
                              TestComWebEventHandlerRt, //even sink class derived 
                                   //from IDispEventSimpleImpl
                              &DIID_DITestAtl7WebEvents> //DIID of the event source
                                   //dispinterface implemented by this class.
{
public:
  TestComWebEventHandlerRt(void);
  virtual ~TestComWebEventHandlerRt(void);
  HRESULT GetFuncInfoFromId(const IID& iid, DISPID dispidMember,
                            LCID lcid, _ATL_FUNC_INFO& info);
  STDMETHODIMP OnTestAtlEvent(BSTR bstrValue);
  virtual STDMETHODIMP Invoke(DISPID dispidMember, 
                              REFIID riid,
                              LCID lcid, 
                              WORD wFlags, 
                              DISPPARAMS* pdispparams, 
                              VARIANT* pvarResult,
                              EXCEPINFO* pexcepinfo, 
                              UINT* puArgErr
                              );
//Attributes
  const uint32_t TESTCOUNTMAX;  //tick counter upper limit
  uint32_t  m_nTickCounter;     //tick counter
  CEvent    m_clSignal;         //notification that an event has occurred

  //Event Sink Map lists event handlers
  //Note: Make sure the Event Handlers have __stdcall (STDMETHODIMP) calling convention
BEGIN_SINK_MAP(TestComWebEventHandlerRt)
  //                                                     DISPID ,Event Handler
  SINK_ENTRY_EX(ID_TESTCOMSINK, DIID_DITestAtl7WebEvents, 1     , OnTestAtlEvent)
END_SINK_MAP()
};

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
* $Log: 
*  3    Biblioteka1.2         2007-03-11 02:21:39  Darko           Event sink and 
*       apartman message loop
*  2    Biblioteka1.1         2007-03-08 21:40:26  Darko Kolakovic Event sink
*  1    Biblioteka1.0         2007-03-06 19:00:45  Darko Kolakovic 
* $
*****************************************************************************/
