/*$Workfile: KDisplayComError.cpp$: implementation file
  $Revision: 7$ $Date: 2005-06-21 17:51:52$
  $Author: Darko Kolakovic$

  Outputs COM exception.
  Copyright: CommonSoft Inc.
  2005-03-25 Darko Kolakovic
 */

// Group=Diagnostic

#include "stdafx.h"
#pragma comment( lib, "comsupp" ) //comsupp.lib
#include <comdef.h> //_com_error class
#ifndef _ATL_VER
  #include <atldef.h>  //ATL support
#endif
#if (_ATL_VER > 0x0300) /*Active Template Library version 3.0*/
  #include <atlstr.h> //Non-MFC string objects
  //<cstringt.h> MFC-only string objects
#else
  #if !defined(_AFXDLL) && !defined(_AFX)
      //Windows Template Library (WTL) is required for the CString
      #include <atlbase.h>
      #include <atlapp.h>
      extern CAppModule _Module;
      #include <atlmisc.h> //CString class
  #endif
#endif

#ifdef _CONSOLE
  #if defined(_STL) || defined (_USE_STL) //Use Standard Template Library (STL)
    #include <iostream> //cerr class
  #endif
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

void DisplayError(_com_error &e);

///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/*Display of error events generated from the type library or by one of the COM
  support classes. The _com_error class encapsulates the HRESULT error code and
  any associated IErrorInfo object.

  Note: Microsoft Windows specific (Win32)
       and uses Active Template Library (ATL).

  See also: ComErrorShow(), ComProviderErrors()
 */
void DisplayError(_com_error &e //[in] exception condition to report
                 )
{
#if _ATL_VER > 0x0300 /*Active Template Library version 3.0*/
  typedef CStringT<TCHAR, StrTraitATL<TCHAR> > _KErrStringType;
#else //MFC/ATL string implementation
  typedef CString _KErrStringType;
#endif

try
  {
  _bstr_t bstrSource(e.Source());
  _bstr_t bstrDescription(e.Description());
  //TODO: Reformat the optput if Source and/or Description are <BadPtr>

  _KErrStringType strMessage;
  strMessage.Format(_T("%s %08lx\n%s\n%s\n"),
                  e.ErrorMessage(),  //error description
                  e.Error(),         //error code
                  bstrSource,        //error source
                  bstrDescription    //text description of the error contained
                                     //in IErrorInfo
                  );
  //Some of the IErrorInfo error descriptions have undesired CR/LF at the end
  //strMessage.TrimRight();

  TRACE1("%s", (LPCTSTR)strMessage);

  #ifdef _CONSOLE
    #ifdef _STL
      std::_tcerr << LPCTSTR(strMessage);
    #else
      _tprintf(LPCTSTR(strMessage));
    #endif
  #else
    #ifdef _AFX // Microsoft Application Framework Classes
      AfxMessageBox(LPCTSTR(strMessage));
    #else
      //The message box has no owner window.
      MessageBox(NULL, LPCTSTR(strMessage), NULL, MB_OK | MB_ICONEXCLAMATION);
    #endif
  #endif

  }
catch(...)
  {
  ASSERT(FALSE);
  }

}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         2005-04-14 01:00:18  Darko           Fixed build
 *       with ATL7.1
 *  3    Biblioteka1.2         2005-04-14 00:59:51  Darko           Fized build
 *       with ATL7.1
 *  2    Biblioteka1.1         2005-04-06 14:49:34  Darko Kolakovic Compiled with
 *       MSVC6
 *  1    Biblioteka1.0         2005-03-27 02:28:57  Darko
 * $
 *****************************************************************************/
