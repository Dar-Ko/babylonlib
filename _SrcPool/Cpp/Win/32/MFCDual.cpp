/*$RCSfile: MFCDual.cpp,v $: header file
  $Revision: 1.2 $ $Date: 2008/08/25 15:37:47 $
  $Author: ddarko $

  Helpful macros for adding dual interface support to MFC application
  Copyright: 1992-1998 Microsoft Corporation
  2005 MSDN
 */

// Group=Windows

#include "stdafx.h"
#
#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DualHandleException

/*DualHandleException is a helper function used to set the system's  error
  object, so that container applications that call through VTBLs can retrieve
  rich error information. Function determines the error code to return based on
  the type of exception that occurred.

  Note: Microsoft Windows specific (Win32)
        and uses Microsoft Foundation Library (MFC).

  See also: article TN065 Dual-Interface Support for OLE Automation Servers.
 */
HRESULT DualHandleException(REFIID riidSource, const CException* pAnyException)
{
USES_CONVERSION;

ASSERT_VALID(pAnyException);

TRACE0("DualHandleException()\n");

// Set ErrInfo object so that VTLB binding container
// applications can get rich error information.
ICreateErrorInfo* pcerrinfo;
HRESULT hr = CreateErrorInfo(&pcerrinfo);
if (SUCCEEDED(hr))
  {
  TCHAR   szDescription[256];
  LPCTSTR pszDescription = szDescription;
  GUID    guid = GUID_NULL;
  DWORD   dwHelpContext = 0;
  BSTR    bstrHelpFile = NULL;
  BSTR    bstrSource = NULL;
  if (pAnyException->IsKindOf(RUNTIME_CLASS(COleDispatchException)))
    {
    // specific IDispatch style exception
    COleDispatchException* e = (COleDispatchException*)pAnyException;

    guid = riidSource;
    hr = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF,
              (e->m_wCode + 0x200));

    pszDescription = e->m_strDescription;
    dwHelpContext = e->m_dwHelpContext;

    // propagate source and help file if present
    // call ::SysAllocString directly so no further exceptions are thrown
    if (!e->m_strHelpFile.IsEmpty())
      bstrHelpFile = ::SysAllocString(T2COLE(e->m_strHelpFile));
    if (!e->m_strSource.IsEmpty())
      bstrSource = ::SysAllocString(T2COLE(e->m_strSource));

    }
  else if (pAnyException->IsKindOf(RUNTIME_CLASS(CMemoryException)))
    {
    // failed memory allocation
    AfxLoadString(AFX_IDP_FAILED_MEMORY_ALLOC, szDescription);
    hr = E_OUTOFMEMORY;
    }
  else
    {
    // other unknown/uncommon error
    AfxLoadString(AFX_IDP_INTERNAL_FAILURE, szDescription);
    hr = E_UNEXPECTED;
    }

  if (bstrHelpFile == NULL && dwHelpContext != 0)
    bstrHelpFile = ::SysAllocString(T2COLE(AfxGetApp()->m_pszHelpFilePath));

  if (bstrSource == NULL)
    bstrSource = ::SysAllocString(T2COLE(AfxGetAppName()));

  // Set up ErrInfo object
  pcerrinfo->SetGUID(guid);
  pcerrinfo->SetDescription(::SysAllocString(T2COLE(pszDescription)));
  pcerrinfo->SetHelpContext(dwHelpContext);
  pcerrinfo->SetHelpFile(bstrHelpFile);
  pcerrinfo->SetSource(bstrSource);

  TRACE("  Source = %ws\n", bstrSource);
  TRACE("  Description = %s\n", pszDescription);
  TRACE("  HelpContext = %lx\n", dwHelpContext);
  TRACE("  HelpFile = %ws\n", bstrHelpFile);

  // Set the ErrInfo object for the current thread
  IErrorInfo* perrinfo;
  if (SUCCEEDED(pcerrinfo->QueryInterface(IID_IErrorInfo, (LPVOID*)&perrinfo)))
    {
    SetErrorInfo(0, perrinfo);
    perrinfo->Release();
    }

  pcerrinfo->Release();
  }

TRACE("  HRESULT %lx\n", hr);

return hr;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: MFCDual.cpp,v $
 * Revision 1.2  2008/08/25 15:37:47  ddarko
 * Comments
 *
 *****************************************************************************/

/*This is a part of the Microsoft Foundation Classes C++ library.
  Copyright (C) 1992-1998 Microsoft Corporation
  All rights reserved.
  This source code is only intended as a supplement to the Microsoft Foundation
  Classes Reference and related electronic documentation provided with the
  library.
  See these sources for detailed information regarding the Microsoft Foundation
  Classes product.
 */
