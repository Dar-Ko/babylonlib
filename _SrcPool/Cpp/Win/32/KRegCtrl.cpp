/*$Workfile: KRegCtrl.cpp$: implementation file
  $Revision: 2$ $Date: 2004-10-01 21:35:11$
  $Author: Darko$

  Defines the class behaviors for the application.

  May. 94 Darko Kolakovic
  Microsoft MSDN Sample
 */

#include "stdafx.h"
#include "KRegCtrl.h" //CRegisterCtrl class

//-----------------------------------------------------------------------------
/*
 */
CRegisterCtrl::CRegisterCtrl()
{
}

//-----------------------------------------------------------------------------
/*
 */
CRegisterCtrl::~CRegisterCtrl()
{
}

//-----------------------------------------------------------------------------
/*
 */
bool CRegisterCtrl::IsRegistered(LPCTSTR szProgID //[in] 
                                )
{
bool bResult = false;

CLSID clsid;
HRESULT hr = AfxGetClassIDFromString(szProgID, &clsid);
if(SUCCEEDED(hr))
  bResult = true;

return bResult;
}

//-----------------------------------------------------------------------------
/*TOOD: description
 */
bool CRegisterCtrl::Register(LPCTSTR szPath //[in] 
                             )
{
bool bResult = true;
HINSTANCE hOCX = NULL;
#ifdef _AFXDLL  
  hOCX = AfxLoadLibrary(szPath);
#else
  hOCX = ::LoadLibrary(szPath);
#endif

if(hOCX == NULL)
  bResult = false;
else
  {
  #ifdef _UNICODE 
    USES_CONVERSION;
    if(FAILED((*(GetProcAddress(hOCX, W2CA(_T("DllRegisterServer")))))()))
      {
      TRACE(_T("DLLRegisterServer() Failed.\n"));
      bResult = false;
      }
  #else
    if(FAILED((*(GetProcAddress(hOCX, "DllRegisterServer")))()))
      {
      TRACE(_T("DLLRegisterServer() Failed.\n"));
      bResult = false;
      }
  #endif

  #ifdef _AFXDLL      
    AfxFreeLibrary(hOCX);
  #else
    ::FreeLibrary(hOCX);
  #endif
  }

return bResult;
}

//-----------------------------------------------------------------------------
/*
 */
bool CRegisterCtrl::Register(LPCTSTR szProgID, //[in] 
                             LPCTSTR szControlName //[in] null-terminated string 
                             //that specifies the name of the control.
                             )
{
bool bResult = IsRegistered(szProgID);
if(!bResult)
  {
  TCHAR szPath[_MAX_PATH]; //buffer that receives the path and file name of
                           //the file found.
  DWORD dwLength = _MAX_PATH;
  if (::SearchPath(NULL, szControlName, NULL, dwLength, szPath, NULL) > 0)
    return Register(szPath);
  //Note: returns result of RegisterControl or false from IsControlRegistered!
  }
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-10-01 21:35:11  Darko           stdafx.h
 *  1    Biblioteka1.0         2003-08-13 16:36:41  Darko           
 * $
 *****************************************************************************/
