/*$Workfile: TestAtlObj.cpp$: implementation file
  $Revision: 3$ $Date: 2007-02-16 14:22:26$
  $Author: Darko Kolakovic$

  Implementation file
  Copyright: CommonSoft Inc.
  2003-08-25 Darko Kolakovic
 */

// TestAtlObj.cpp : Implementation of CTestAtlObj
#include "stdafx.h"
#include <shlguid.h> //SID_STopLevelBrowser
//Note: Compile .idl file first
#include "TestComAtl.h"

#include "TestAtlObj.h"

/////////////////////////////////////////////////////////////////////////////
// CTestAtlObj

//-----------------------------------------------------------------------------
/*Provides the IUnknown pointer to site containing this object.

  The IObjectWithSite Interface provides a lightweight (lighter than IOleObject)
  communication with a container site that is managing the object itself.
  Through IObjectWithSite, a container can pass the IUnknown pointer of its site
  to the object through SetSite. Callers can also retrieve the latest site
  passed to SetSite through GetSite().
  This interface should only be used when IOleObject could not provide a pointer
  to the site. For example JavaScript interpreter is not an OLE container and
  controls created within a script have to provide this method if it is required
  to communicate with the container of the script.

  Returns: S_OK in all circumstances.
 */
STDMETHODIMP CTestAtlObj::SetSite(IUnknown* pClientSite //[in] site managing
        //this object. If NULL, the object should call IUnknown::Release()
        //to release the existing site.
                                 )
{
ATLTRACEMETHOD();
HRESULT hr = S_OK;
//Obtain the top-level IWebBrowser2 reference
//See also: MSDN KB257717
CComPtr<IWebBrowser2> spContainer;
CComPtr<IServiceProvider> spServiceProvider, spTopServiceProvider;
if (pClientSite != NULL)
  {
  if (SUCCEEDED(hr = pClientSite->QueryInterface(IID_IServiceProvider,
                                            reinterpret_cast<void **>(&spServiceProvider))))
    {
    if (SUCCEEDED(hr = spServiceProvider->QueryService(SID_STopLevelBrowser,
                                    IID_IServiceProvider,
                                    reinterpret_cast<void **>(&spTopServiceProvider))))
      {
      hr = spTopServiceProvider->QueryService(SID_SWebBrowserApp,
                                                IID_IWebBrowser2,
                                                reinterpret_cast<void **>(&spContainer));
      }
    }
  }
return S_OK;
}

//-----------------------------------------------------------------------------
/*Queries the site containing this object for a pointer to the interface
  identified by riid.

  Returns:
    S_OK          The site was returned successfully and the caller is responsible
                  for calling ((IUnknown *)(*ppvSite))->Release() when the site
                  is no longer needed.
    E_FAIL        There is no site; in that case, *ppvSite contains NULL on return.
    E_NOINTERFACE There is a site, but it does not support the interface
                  requested by riid.

  Note: E_NOTIMPL is disallowed—any object implementing this interface must be
  able to return the last site seen in IObjectWithSite::SetSite.
 */
STDMETHODIMP CTestAtlObj::GetSite(REFIID riid,   //[in] IID of the interface
                                  //pointer that should be returned in ppvSite.
                                  void** ppvSite //[out] pointer to the interface
                                  //supported by the site or NULL
                                  )
{
ATLTRACEMETHOD();
if (NULL != ppvSite)
  {
  //*ppvSite = spContainer;
  }
return S_OK;
}

//-----------------------------------------------------------------------------
/*Test method performing multiplication by two.

  Returns: S_OK and result of multiplication through pResult.
 */
STDMETHODIMP CTestAtlObj::TestMethod(long lInput, //[in] a number
                                     long *pResult//[out] result of multiplication
                                    )
{
*pResult = 2 * lInput;
return S_OK;
}

