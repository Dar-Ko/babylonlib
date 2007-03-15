/*$Workfile: KAtlExt.h$: header file
  $Revision: 4$ $Date: 2007-03-11 02:03:53$
  $Author: Darko$

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

//-----------------------------------------------------------------------------
/*{group:Windows}
  Creates an instance of CComPtr object.
  ATL uses CComPtr to manage COM interface pointers. CComPtr is derived from
  CComPtrBase and to perform automatic reference counting.

  Parameters:
    T - COM interface specifying the type of pointer to be stored.

  Example:
      #include "KAtlExt.h"
      ...
      CAdoConnection adoObj = new_instance<CAdoConnection>();

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
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2005-03-26 00:11:41  Darko           comment
 *  1    Biblioteka1.0         2005-03-23 03:23:26  Darko
 * $
 *****************************************************************************/
