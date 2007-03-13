/*$Workfile: DITestAtl7ObjEvents_CP.h$: header file
  $Revision: 2$ $Date: 2007-03-02 20:21:48$
  $Author: Darko Kolakovic$

  Connection Point Object
  Copyright: CommonSoft Inc
  2006-08-30 Darko Kolakovic
*/

#pragma once

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
class CProxyDITestAtl7ObjEvents :
  public IConnectionPointImpl<T, &__uuidof(DITestAtl7ObjEvents)>
{
public:
  HRESULT Fire_TestAtlEvent( BSTR  bstrInput,  BSTR *  bstrOutput)
  {
  HRESULT hr = S_OK;
  T * pThis = static_cast<T *>(this);
  int cConnections = m_vec.GetSize();

  for (int iConnection = 0; iConnection < cConnections; iConnection++)
    {
    pThis->Lock();
    CComPtr<IUnknown> punkConnection = m_vec.GetAt(iConnection);
    pThis->Unlock();

    IDispatch * pConnection = static_cast<IDispatch *>(punkConnection.p);

    if (pConnection)
      {
      CComVariant avarParams[2];
      avarParams[1] = bstrInput;
      avarParams[1].vt = VT_BSTR;

      //*bstrOutput = T2BSTR(_T("Event fired!"));
      //FixMe! avarParams[0] = bstrOutput;
      avarParams[0] = 0;
      avarParams[0].vt = VT_PBSTR;
      CComVariant varResult;

      DISPPARAMS params = { avarParams, NULL, 2, 0 };
      hr = pConnection->Invoke(1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &params, &varResult, NULL, NULL);
      }
    }
  return hr;
  }
};

///////////////////////////////////////////////////////////////////////////////
