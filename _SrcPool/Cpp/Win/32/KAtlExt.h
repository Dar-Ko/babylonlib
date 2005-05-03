/*$Workfile: KAtlExt.h$: header file
  $Revision: 2$ $Date: 2005-04-26 16:42:05$
  $Author: Darko Kolakovic$

  ATL Helper methods and objects
  Copyright: CommonSoft Inc
  2004-04-01  Darko Kolakovic
 */


#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

//-----------------------------------------------------------------------------
/*{group:Windows}
  Creates an instance of CComPtr object.
  ATL uses CComPtr to manage COM interface pointers. CComPtr is derived from
  CComPtrBase, and perform automatic reference counting.

  Parameters:
    T - COM interface specifying the type of pointer to be stored.

  Example:
      #include "KAtlExt.h"
      ...
      CAdoConnection = new_instance<CAdoConnection>();

  Note: Microsoft Windows specific (Win32)
       and uses Active Template Library (ATL).

  See also: atlcomcli.h
 */
template<class T> CComPtr<T> new_instance()
{
typedef CComObject<T> ComObject;
ComObject* pcoObject;
ComObject::CreateInstance(&pcoObject);

return CComPtr<T>(pcoObject);
}

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*{group=Diagnostic}
  Validates the result returned by a COM object oparation. If hResult is not SOK,
  throws _com_error exception.

  Note: Microsoft Windows specific (Win).
        and uses Active Template Library (ATL).

  History: Microsoft MSDN Sample
 */
inline void TESTHR(HRESULT hResult //[in] result of COM Objects operation
                  ) throw(_com_error)
{
if (FAILED(hResult))
  _com_issue_error(hResult);
};

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2005-03-26 00:11:41  Darko           comment
 *  1    Biblioteka1.0         2005-03-23 03:23:26  Darko
 * $
 *****************************************************************************/
