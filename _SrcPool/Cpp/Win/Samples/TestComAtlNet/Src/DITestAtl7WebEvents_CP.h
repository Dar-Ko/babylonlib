/*$Workfile: DITestAtl7WebEvents_CP.h$: header file
  $Revision: 5$ $Date: 2007-03-15 16:04:34$
  $Author: Darko Kolakovic$

  Connection Point Object
  Copyright: CommonSoft Inc
  2006-08-30 Darko Kolakovic
*/

#pragma once
#include "KHresult.h" //CHresult class
#ifndef VT_PBSTR
  //Bug Fix for the ATL wizard generated code.
  //A reference to a string was passed. A BSTR* that points to a BSTR is
  //in pbstrVal.
  //The referenced pointer must be obtained or freed by the BSTR functions.
  #define VT_PBSTR VT_BSTR | VT_BYREF
#endif
#ifndef VT_PVARIANT
  //Bug Fix for the ATL wizard generated code.
  //A pointer to another VARIANTARG is passed in pvarVal. This referenced
  //VARIANTARG, pvarVal, cannot be another VT_VARIANT|VT_BYREF.
  //This value can be used to support languages that allow functions to
  //change the types of variables passed by reference.
  #define VT_PVARIANT VT_VARIANT | VT_BYREF
#endif

///////////////////////////////////////////////////////////////////////////////
/*
 {html: <img src="../Images/diagIConnectionPoint.gif" title="IConnectionPointContainer" /><br />}

 */
template<class T>
class CProxyDITestAtl7WebEvents : public IConnectionPointImpl<T, 
                                                &__uuidof(DITestAtl7WebEvents)>
{
public:
  HRESULT Fire_TestAtlEvent( BSTR  bstrValue);
};

///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/*
 */
template<class T>
HRESULT CProxyDITestAtl7WebEvents<T>::Fire_TestAtlEvent(BSTR bstrValue //[in]
                                                       )
{
CHresult hr = S_OK;
try
  {
  T * pThis = static_cast<T *>(this);
  int cConnections = m_vec.GetSize();

  ATLTRACE("CProxyDITestAtl7WebEvents<T>::Fire_TestAtlEvent() subscribers =%d.\n", 
            cConnections);
  for (int iConnection = 0; iConnection < cConnections; iConnection++)
    {
    pThis->Lock();
    CComPtr<IUnknown> punkConnection = m_vec.GetAt(iConnection);
    pThis->Unlock();

    IDispatch * pConnection = static_cast<IDispatch *>(punkConnection.p);

    if (pConnection)
      {
      CComVariant avarParams[1];
      avarParams[0] = bstrValue;  
      avarParams[0].vt = VT_BSTR;
      CComVariant varResult;

      DISPPARAMS params = { avarParams, NULL, 1, 0 };
      hr = pConnection->Invoke( 1, 
                                IID_NULL, 
                                LOCALE_USER_DEFAULT, 
                                DISPATCH_METHOD, 
                                &params, 
                                &varResult, 
                                NULL, 
                                NULL);
      }
    }
  }
catch(...)
  {
  ATLTRACE("  Exception %s!\n", hr.ErrorMessage());
  }
return (HRESULT)hr;
};

////////////////////////////////////////////////////////////////////////////////