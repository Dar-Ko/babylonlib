/*$Workfile: KDispatchPtr.h$: header file
  $Revision: 1.5 $ $Date: 2011/12/22 15:49:46 $
  $Author: ddarko $

  IDispatch wrapper
  Copyright: Mike Morearty
  2000-04 Mike Morearty <mike@morearty.com>
  http://www.morearty.com/code/dispatch
 */

// Group=Windows

#pragma once

#include <comdef.h>

class CDispatchVariant;
class TDispatchFunctions;

////////////////////////////////////////////////////////////////////////////////
/*CDispatchPtr class is a wrapper for an IDispatch pointer. The class extends
  inherited IDispatchPtr methods with easy way to get or put properties and to
  invoke other methods exposed by IDispatch interface.

  See also: CComDispatchDriver, COleDispatchDriver, _com_dispatch_

  Example:
      #inclde "KDispatchPtr.h"  //CDispatchPtr class
      ...
      CDispatchPtr htmlDoc; //HTML document object

      _bstr_t title = htmlDoc.Get("title");
      htmlDoc.Put("title", "new title");
      htmldoc.Get("body").Get("firstChild").Invoke("insertAdjacentText",
                                                   "afterBegin",
                                                   "hello world");
      _bstr_t html   = htmldoc.Get("body").Get("innerHTML");
      long    height = htmldoc.Get("body").Get("clientHeight");
      CDispatchPtr body = htmlDoc.Get("body");
      ...
 */
class CDispatchPtr :
  public IDispatchPtr,
  public TDispatchFunctions<CDispatchPtr>
{
//Constructors
public:
  CDispatchPtr();
  CDispatchPtr(int null);
  CDispatchPtr(Interface* pInterface);
  CDispatchPtr(Interface* pInterface, bool fAddRef);
  template<typename _InterfacePtr> CDispatchPtr(const _InterfacePtr& p);

  explicit CDispatchPtr(const CLSID& clsid, IUnknown* pOuter = NULL,
                        DWORD dwClsContext = CLSCTX_ALL);
  explicit CDispatchPtr(LPOLESTR str, IUnknown* pOuter = NULL,
                        DWORD dwClsContext = CLSCTX_ALL);
  explicit CDispatchPtr(LPCSTR str, IUnknown* pOuter = NULL,
                        DWORD dwClsContext = CLSCTX_ALL);

//Operations
public:
  template<typename _InterfacePtr> CDispatchPtr& operator=(const _InterfacePtr& p);
  CDispatchPtr& operator=(Interface* pInterface);
  CDispatchPtr& operator=(int null);
};

////////////////////////////////////////////////////////////////////////////////
// Inlines borrowed from _com_ptr_t implementation

//------------------------------------------------------------------------------
/*Constructor
 */
inline CDispatchPtr::CDispatchPtr() throw()
{
}

inline CDispatchPtr::CDispatchPtr(int null) : IDispatchPtr(null)
{
}

inline CDispatchPtr::CDispatchPtr(Interface* pInterface //[in]
                                 ) throw() : IDispatchPtr(pInterface)
{
}

inline CDispatchPtr::CDispatchPtr(Interface* pInterface, //[in]
                                  bool fAddRef           //[in]
                                 ) throw() : IDispatchPtr(pInterface, fAddRef)
{
}

inline template<typename _InterfacePtr>
CDispatchPtr::CDispatchPtr(const _InterfacePtr& p) : IDispatchPtr(p)
{
}

inline CDispatchPtr::CDispatchPtr(const CLSID& clsid, //[in]
                                  IUnknown* pOuter,// = NULL,
                                  DWORD dwClsContext,// = CLSCTX_ALL
                                 ) : IDispatchPtr(clsid, pOuter, dwClsContext)
{
}

inline CDispatchPtr::CDispatchPtr(LPOLESTR str,  //[in]
                                  IUnknown* pOuter, // = NULL,
                                  DWORD dwClsContext, // = CLSCTX_ALL
                                  ) : IDispatchPtr(str, pOuter, dwClsContext)
{
}

inline CDispatchPtr::CDispatchPtr(LPCSTR str,  //[in]
                                  IUnknown* pOuter, // = NULL,
                                  DWORD dwClsContext, // = CLSCTX_ALL
                                  ) : IDispatchPtr(str, pOuter, dwClsContext)
{
}

//------------------------------------------------------------------------------
/*Assignment operator.
 */
inline CDispatchPtr::CDispatchPtr& operator=(Interface* pInterface //[in]
                                            ) throw()
{
IDispatchPtr::operator=(pInterface);
return *this;
}

inline CDispatchPtr::CDispatchPtr& operator=(int null)
{
IDispatchPtr::operator=(null);
return *this;
}

inline template<typename _InterfacePtr>
CDispatchPtr::CDispatchPtr& operator=(const _InterfacePtr& p //[in]
                                     )
    { IDispatchPtr::operator=(p); return *this; }


////////////////////////////////////////////////////////////////////////////////
/*Throughout this class, for any function which is templated on type
  <TDISPATCHITEM>, the TDISPATCHITEM identifies one method or property
  of an object, and the value passed for the TDISPATCHITEM should be
  either a (char*), a (wchar_t*) or a DISPID.
 */
template <class T>
class TDispatchFunctions
{
public:

  // Get: get a property's value
  template <class TDISPATCHITEM>
  CDispatchVariant Get(TDISPATCHITEM property);

  // Put: put a property's value
  template <class TDISPATCHITEM>
  void Put(TDISPATCHITEM property, const _variant_t& value);

  // PutRef: put a reference to a property's value
  template <class TDISPATCHITEM>
  void PutRef(TDISPATCHITEM property, const _variant_t& value);

  // Invoke: invoke a method
  template <class TDISPATCHITEM>
  CDispatchVariant Invoke(TDISPATCHITEM method);

  template <class TDISPATCHITEM>
  CDispatchVariant Invoke(TDISPATCHITEM method,
              const _variant_t& arg1);

  template <class TDISPATCHITEM>
  CDispatchVariant Invoke(TDISPATCHITEM method,
              const _variant_t& arg1,
              const _variant_t& arg2);

  template <class TDISPATCHITEM>
  CDispatchVariant Invoke(TDISPATCHITEM method,
              const _variant_t& arg1,
              const _variant_t& arg2,
              const _variant_t& arg3);

  template <class TDISPATCHITEM>
  CDispatchVariant Invoke(TDISPATCHITEM method,
              const _variant_t& arg1,
              const _variant_t& arg2,
              const _variant_t& arg3,
              const _variant_t& arg4);

  template <class TDISPATCHITEM>
  CDispatchVariant Invoke(TDISPATCHITEM method,
              const _variant_t& arg1,
              const _variant_t& arg2,
              const _variant_t& arg3,
              const _variant_t& arg4,
              const _variant_t& arg5);

  template <class TDISPATCHITEM>
  CDispatchVariant Invoke(TDISPATCHITEM method,
              const _variant_t& arg1,
              const _variant_t& arg2,
              const _variant_t& arg3,
              const _variant_t& arg4,
              const _variant_t& arg5,
              const _variant_t& arg6);

  template <class TDISPATCHITEM>
  CDispatchVariant Invoke(TDISPATCHITEM method,
              const _variant_t& arg1,
              const _variant_t& arg2,
              const _variant_t& arg3,
              const _variant_t& arg4,
              const _variant_t& arg5,
              const _variant_t& arg6,
              const _variant_t& arg7);

  template <class TDISPATCHITEM>
  CDispatchVariant Invoke(TDISPATCHITEM method,
              const _variant_t& arg1,
              const _variant_t& arg2,
              const _variant_t& arg3,
              const _variant_t& arg4,
              const _variant_t& arg5,
              const _variant_t& arg6,
              const _variant_t& arg7,
              const _variant_t& arg8);

  template <class TDISPATCHITEM>
  CDispatchVariant Invoke(TDISPATCHITEM method,
              const _variant_t& arg1,
              const _variant_t& arg2,
              const _variant_t& arg3,
              const _variant_t& arg4,
              const _variant_t& arg5,
              const _variant_t& arg6,
              const _variant_t& arg7,
              const _variant_t& arg8,
              const _variant_t& arg9);

protected:
  void InvokeHelper(DISPID dispatchItem, const VARIANT* params,
                    int cParams, WORD invokeType, VARIANT* result);
  void InvokeHelper(LPCOLESTR dispatchItem, const VARIANT* params,
                    int cParams, WORD invokeType, VARIANT* result);
  void InvokeHelper(LPCSTR dispatchItem, const VARIANT* params,
                    int cParams, WORD invokeType, VARIANT* result);
};

///////////////////////////////////////////////////////////////////////////////
// Inline functions

//-----------------------------------------------------------------------------
/*
 */
template <class T>
void TDispatchFunctions<T>::InvokeHelper( DISPID dispatchItem,
                                          const VARIANT* params,
                                          int cParams,
                                          WORD invokeType,
                                          VARIANT* result)
  {
    IDispatch* disp = *(T*)this;
    DISPPARAMS dispparams = { const_cast<VARIANT*>(params), 0, cParams, 0 };
    HRESULT hr;
    DISPID dispidPut;

    if (invokeType == DISPATCH_PROPERTYPUT ||
      invokeType == DISPATCH_PROPERTYPUTREF)
    {
      dispidPut = DISPID_PROPERTYPUT;

      dispparams.cNamedArgs = 1;
      dispparams.rgdispidNamedArgs = &dispidPut;
    }

    // A hard-coded assumption that "result" does NOT already
    // contain a valid variant!
    if (result)
      V_VT(result) = VT_EMPTY;

    hr = disp->Invoke(dispatchItem, IID_NULL, LOCALE_SYSTEM_DEFAULT,
      invokeType, &dispparams, result, NULL, NULL);
    if (FAILED(hr))
      _com_raise_error(hr);
  }

//-----------------------------------------------------------------------------
/*dispatchItem is (wchar_t*) -- convert it to a DISPID
 */
template <class T>
void TDispatchFunctions<T>::InvokeHelper( LPCOLESTR dispatchItem,
                                          const VARIANT* params,
                                          int cParams,
                                          WORD invokeType,
                                          VARIANT* result)
  {
    IDispatch* disp = *(T*)this;
    DISPID dispid;
    HRESULT hr;

    hr = disp->GetIDsOfNames(IID_NULL, const_cast<LPOLESTR*>(&dispatchItem), 1,
      LOCALE_SYSTEM_DEFAULT, &dispid);
    if (FAILED(hr))
    {
      if (hr == DISP_E_UNKNOWNNAME && invokeType == DISPATCH_PROPERTYGET)
      {
        if (result)
          V_VT(result) = VT_EMPTY;
        return;
      }
      else
      {
        _com_raise_error(hr);
      }
    }

    // call the DISPID overload of InvokeHelper()
    InvokeHelper(dispid, params, cParams, invokeType, result);
  }

//-----------------------------------------------------------------------------
/*dispatchItem is an Ansi LPSTR  -- convert it to an LPOLESTR
 */
template <class T>
void TDispatchFunctions<T>::InvokeHelper( LPCSTR dispatchItem,
                                          const VARIANT* params,
                                          int cParams,
                                          WORD invokeType,
                                          VARIANT* result)
  {
    OLECHAR nameBuff[256]; // try to avoid doing an allocation
    LPOLESTR wideName;

    int cch = lstrlen(dispatchItem) + 1;
    if (cch <= sizeof(nameBuff) / sizeof(OLECHAR))
      wideName = nameBuff;
    else
    {
      // dispatch item name is longer than our fixed-size buffer; allocate.
      // Do NOT use alloca() [or ATL's A2W(), which uses alloca()], because
      // this is function may be inlined (although that's not likely), and
      // that could cause a stack overflow if this function is called from
      // within a loop

      wideName = new OLECHAR[cch]; // cch may be just a bit bigger than necessary
      if (wideName == NULL)
        _com_raise_error(E_OUTOFMEMORY);
    }

    wideName[0] = '\0';
    MultiByteToWideChar(CP_ACP, 0, dispatchItem, -1, wideName, cch);

    // call the LPOLESTR overload of InvokeHelper()
    InvokeHelper(wideName, params, cParams, invokeType, result);

    if (wideName != nameBuff)
      delete[] wideName;
  }
//-----------------------------------------------------------------------------
/*
 */
// Get: get a property's value
template <class T>
template <class TDISPATCHITEM>
CDispatchVariant TDispatchFunctions<T>::Get(TDISPATCHITEM property)
{
  VARIANT result;
  InvokeHelper(property, NULL, 0, DISPATCH_PROPERTYGET, &result);
  return result;
}

//-----------------------------------------------------------------------------
/*
 */
// Put: put a property's value
template <class T>
template <class TDISPATCHITEM>
void TDispatchFunctions<T>::Put(TDISPATCHITEM property,
                                const _variant_t& value)
{
  InvokeHelper(property, &value, 1, DISPATCH_PROPERTYPUT, NULL);
}

//-----------------------------------------------------------------------------
/*
 */
// PutRef: put a reference to a property's value
template <class T>
template <class TDISPATCHITEM>
void TDispatchFunctions<T>::PutRef(TDISPATCHITEM property,
                                   const _variant_t& value)
{
  InvokeHelper(property, &value, 1, DISPATCH_PROPERTYPUTREF, NULL);
}

//-----------------------------------------------------------------------------
/*
 */
// Invoke: invoke a method
template <class T>
template <class TDISPATCHITEM>
CDispatchVariant TDispatchFunctions<T>::Invoke(TDISPATCHITEM method)
{
  VARIANT result;
  InvokeHelper(method, NULL, 0, DISPATCH_METHOD, &result);
  return result;
}

//-----------------------------------------------------------------------------
/*
 */
template <class T>
template <class TDISPATCHITEM>
CDispatchVariant TDispatchFunctions<T>::Invoke( TDISPATCHITEM method,
                                                const _variant_t& arg1)
{
  VARIANT result;
  InvokeHelper(method, &arg1, 1, DISPATCH_METHOD, &result);
  return result;
}

//-----------------------------------------------------------------------------
/*
 */
template <class T>
template <class TDISPATCHITEM>
CDispatchVariant TDispatchFunctions<T>::Invoke( TDISPATCHITEM method,
                                                const _variant_t& arg1,
                                                const _variant_t& arg2)
{
  VARIANT result;
  VARIANT args[2];

  args[0] = arg2;
  args[1] = arg1;

  InvokeHelper(method, args, 2, DISPATCH_METHOD, &result);
  return result;
}

//-----------------------------------------------------------------------------
/*
 */
template <class T>
template <class TDISPATCHITEM>
CDispatchVariant TDispatchFunctions<T>::Invoke( TDISPATCHITEM method,
                                                const _variant_t& arg1,
                                                const _variant_t& arg2,
                                                const _variant_t& arg3)
{
  VARIANT result;
  VARIANT args[3];

  args[0] = arg3;
  args[1] = arg2;
  args[2] = arg1;

  InvokeHelper(method, args, 3, DISPATCH_METHOD, &result);
  return result;
}

//-----------------------------------------------------------------------------
/*
 */
template <class T>
template <class TDISPATCHITEM>
CDispatchVariant TDispatchFunctions<T>::Invoke( TDISPATCHITEM method,
                                                const _variant_t& arg1,
                                                const _variant_t& arg2,
                                                const _variant_t& arg3,
                                                const _variant_t& arg4)
{
  VARIANT result;
  VARIANT args[4];

  args[0] = arg4;
  args[1] = arg3;
  args[2] = arg2;
  args[3] = arg1;

  InvokeHelper(method, args, 4, DISPATCH_METHOD, &result);
  return result;
}

//-----------------------------------------------------------------------------
/*
 */
template <class T>
template <class TDISPATCHITEM>
CDispatchVariant TDispatchFunctions<T>::Invoke( TDISPATCHITEM method,
                                                const _variant_t& arg1,
                                                const _variant_t& arg2,
                                                const _variant_t& arg3,
                                                const _variant_t& arg4,
                                                const _variant_t& arg5)
{
  VARIANT result;
  VARIANT args[5];

  args[0] = arg5;
  args[1] = arg4;
  args[2] = arg3;
  args[3] = arg2;
  args[4] = arg1;

  InvokeHelper(method, args, 5, DISPATCH_METHOD, &result);
  return result;
}

//-----------------------------------------------------------------------------
/*
 */
template <class T>
template <class TDISPATCHITEM>
CDispatchVariant TDispatchFunctions<T>::Invoke( TDISPATCHITEM method,
                                                const _variant_t& arg1,
                                                const _variant_t& arg2,
                                                const _variant_t& arg3,
                                                const _variant_t& arg4,
                                                const _variant_t& arg5,
                                                const _variant_t& arg6)
{
  VARIANT result;
  VARIANT args[6];

  args[0] = arg6;
  args[1] = arg5;
  args[2] = arg4;
  args[3] = arg3;
  args[4] = arg2;
  args[5] = arg1;

  InvokeHelper(method, args, 6, DISPATCH_METHOD, &result);
  return result;
}

//-----------------------------------------------------------------------------
/*
 */
template <class T>
template <class TDISPATCHITEM>
CDispatchVariant TDispatchFunctions<T>::Invoke( TDISPATCHITEM method,
                                                const _variant_t& arg1,
                                                const _variant_t& arg2,
                                                const _variant_t& arg3,
                                                const _variant_t& arg4,
                                                const _variant_t& arg5,
                                                const _variant_t& arg6,
                                                const _variant_t& arg7)
{
  VARIANT result;
  VARIANT args[7];

  args[0] = arg7;
  args[1] = arg6;
  args[2] = arg5;
  args[3] = arg4;
  args[4] = arg3;
  args[5] = arg2;
  args[6] = arg1;

  InvokeHelper(method, args, 7, DISPATCH_METHOD, &result);
  return result;
}

//-----------------------------------------------------------------------------
/*
 */
template <class T>
template <class TDISPATCHITEM>
CDispatchVariant TDispatchFunctions<T>::Invoke( TDISPATCHITEM method,
                                                const _variant_t& arg1,
                                                const _variant_t& arg2,
                                                const _variant_t& arg3,
                                                const _variant_t& arg4,
                                                const _variant_t& arg5,
                                                const _variant_t& arg6,
                                                const _variant_t& arg7,
                                                const _variant_t& arg8)
{
  VARIANT result;
  VARIANT args[8];

  args[0] = arg8;
  args[1] = arg7;
  args[2] = arg6;
  args[3] = arg5;
  args[4] = arg4;
  args[5] = arg3;
  args[6] = arg2;
  args[7] = arg1;

  InvokeHelper(method, args, 8, DISPATCH_METHOD, &result);
  return result;
}

//-----------------------------------------------------------------------------
/*
 */
template <class T>
template <class TDISPATCHITEM>
CDispatchVariant TDispatchFunctions<T>::Invoke( TDISPATCHITEM method,
                                                const _variant_t& arg1,
                                                const _variant_t& arg2,
                                                const _variant_t& arg3,
                                                const _variant_t& arg4,
                                                const _variant_t& arg5,
                                                const _variant_t& arg6,
                                                const _variant_t& arg7,
                                                const _variant_t& arg8,
                                                const _variant_t& arg9)
{
  VARIANT result;
  VARIANT args[9];

  args[0] = arg9;
  args[1] = arg8;
  args[2] = arg7;
  args[3] = arg6;
  args[4] = arg5;
  args[5] = arg4;
  args[6] = arg3;
  args[7] = arg2;
  args[8] = arg1;

  InvokeHelper(method, args, 9, DISPATCH_METHOD, &result);
  return result;
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// CDispatchVariant - a helper class for internal use, usually not needed by
// users of this code, but possibly useful on occasion.  This subclasses
// _variant_t and provides it with the Get/Put/PutRef/Invoke methods.  It only
// makes sense to do that if the _variant_t contains, or can be cast to, an
// IDispatch pointer -- that is, V_VT(variant) == VT_DISPATCH.
//
// In the Get/Put/PutRef/Invoke methods from TDispatchFunctions, the expression
// "*(T*)this" is used where an (IDispatch*) is needed.  In the case
// of CDispatchVariant, that expression will succeed if the variant contains
// (or can be cast to) and (IDispatch*), and will throw a _com_error object
// (with appropriate error code) if not.
//-----------------------------------------------------------------------------
class CDispatchVariant :
  public _variant_t,
  public TDispatchFunctions<CDispatchVariant>
{
public:

  // constructors -- just copied (with slight modifications) from _variant_t

  CDispatchVariant() throw() : _variant_t() { }

  CDispatchVariant(const VARIANT& varSrc) : _variant_t(varSrc) { }
  CDispatchVariant(const VARIANT* pSrc) : _variant_t(pSrc) { }
  CDispatchVariant(const _variant_t& varSrc) : _variant_t(varSrc) { }

  CDispatchVariant(VARIANT& varSrc, bool fCopy) : _variant_t(varSrc, fCopy) { }

  CDispatchVariant(IDispatch* pSrc, bool fAddRef = true) throw() : _variant_t(pSrc, fAddRef) { }
  CDispatchVariant(IUnknown* pSrc, bool fAddRef = true) throw() : _variant_t(pSrc, fAddRef) { }

  // operator=() -- just copied (with slight modifications) from _variant_t

  _variant_t& operator=(const VARIANT& varSrc)
    { return _variant_t::operator=(varSrc); }
  _variant_t& operator=(const VARIANT* pSrc)
    { return _variant_t::operator=(pSrc); }
  _variant_t& operator=(const _variant_t& varSrc)
    { return _variant_t::operator=(varSrc); }

  _variant_t& operator=(IDispatch* pSrc)
    { return _variant_t::operator=(pSrc); }
  _variant_t& operator=(IUnknown* pSrc)
    { return _variant_t::operator=(pSrc); }

  // operator->()

  IDispatch* operator->() const
    { return (IDispatch*)*this; }

  // operator bool()

  operator bool() const
  {
    if (vt == VT_DISPATCH)
      return (pdispVal != NULL);
    else
      return _variant_t::operator bool();
  }
};

////////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: KDispatchPtr.h,v $
 *Revision 1.5  2011/12/22 15:49:46  ddarko
 *Appended article
 *
 * 1    Biblioteka1.0         08/03/2007 2:44:54 PMDarko Kolakovic
 ******************************************************************************/

/*IDispatch Wrapper
ATL, MFC, and the Visual C++ runtime library already have wrappers for IDispatch
(CComDispatchDriver, COleDispatchDriver, and the _com_dispatch_... methods,
respectively). However, all three of these suffer from syntax that is much more
awkward than what you can write in languages such as Visual Basic and Javascript.
This wrapper, CDispatchPtr lets you write code like this:

    CDispatchPtr htmldoc = ...;

    _bstr_t html = htmldoc.Get("body").Get("innerHTML");
    htmldoc.Put("title", "New Title");
    htmldoc.Get("body").Get("firstChild").Invoke(
        "insertAdjacentText", "afterBegin", "hello world");
Methods

All of the methods of CDispatchPtr take a first argument that specifies which member
(i.e. property or method) of the IDispatch is being accessed.  You can pass any one
of the following three data types for this parameter:

    A regular ANSI string, e.g. "name"
    A UNICODE string, e.g. L"name"
    A DISPID, e.g. DISPID_NAME

Using a DISPID is most efficient, but least convenient (because you have to figure
out what the DISPID is by muddling through documentation and header files).  Using
a UNICODE string is second-best.  Using an ANSI string is least efficient.  However,
 the efficiency difference between using a UNICODE string and an ANSI string is very
 small, so don't be afraid to use ANSI strings if you want to.

CDispatchPtr has the following methods:

Get(property)
    Returns the value of the property as a _variant_t.  _variant_t supports
    implicit casting to a number of common types, so all of the following are legal:
        long length = myDispatch.Get("length");
        _bstr_t title = myDispatch.Get("title");
        CDispatchPtr body = myDispatch.Get("body");
        CDispatchPtr htmlElement = myDispatch.Get("body").Get("firstChild");
Put(property, _variant_t value)
PutRef(property, _variant_t value)
    Sets the value of a property.  _variant_t supports implicit casting from
    a number of common types, so all of the following are legal:
        myDispatch.Put("length", 3L);
        myDispatch.Put("title", "New Title");
        myDispatch.PutRef("body", (IDispatch*) mybody);
Invoke(method, ...)
    Invokes a method and returns its value.  Due to the implementation, this is
    not a true "varargs" function, but the implementation allows for up to 9 arguments.
    Examples:
        myDispatch.Invoke("onclick");
        myDispatch.Invoke("insertAdjacentText", "afterBegin", "hello world");
        long difference = myDispatch.Invoke("difference", 3L, 4L);

Put() vs. PutRef()

The difference between Put() and PutRef() is subtle and annoying.  If you know
Visual Basic, then the easiest way to explain it is that PutRef() is used for
VB's "Set" keyword, e.g. "Set x = y", and Put() is used for regular value
assignment, e.g. "x = y".

PutRef() sets the value of a property to be a reference to the passed-in value.
This only makes sense if the passed-in value is of type (IDispatch*) or (IUnknown*).

In most cases, you'll just use Put().

CDispatchPtr, IDispatchPtr, and Exceptions

CDispatchPtr is a subclass of IDispatchPtr, with the Get/Put/PutRef/Invoke
methods added.  IDispatchPtr is com_ptr_t<> templated on IDispatch.

Because of this, any place in your code where you would have used an IDispatchPtr,
you can use a CDispatchPtr in its place.

You need to be aware that, since com_ptr_t<> throws exceptions when errors occur,
CDispatchPtr does as well.  I chose to subclass IDispatchPtr instead of ATL's
CComPtr<IDispatch> because the Get() and Invoke() functions, by necessity of what
they're for, can't return an error code as their return value, so they must throw
exceptions to indicate errors.  CComPtr does not throw exceptions, but
_com_ptr_t does.

In addition to those exceptions that result from com_ptr_t<>'s methods being
called, CDispatchPtr will also raise an exception if an IDispatch-based method
or property that you try to invoke returns an error code -- e.g. because you
passed invalid arguments or because the implementing object fails -- an exception
(of type _com_error) will be thrown.

Because of this, you will need to use try/catch blocks in your code, just as you
would if you used IDispatchPtr or any other _com_ptr_t<>-derived type.

_com_error has a member function called ErrorMessage() which returns the text
error message for the HRESULT that caused the error, so for quickie debugging
code, this is a good starting point:

    try
    {
        // ... your code here ...
    }
    catch( _com_error& err )
    {
        printf( "Error: %s\n", err.ErrorMessage() );
    }

Performance

Methods invoked via IDispatch are always somewhat slower than those invoked via
direct interfaces. However, the performance difference is small enough not to
be a major concern in most cases.

And in the case of accessing properties and methods of MSHTML, going through
IDispatch is dramatically easier than going through direct interfaces, and thus
is almost always worth the small loss in performance.  For example, the Javascript
expression

    document.body.firstChild

is a real pain to write in C++ using direct interfaces:

    IHTMLDocument2Ptr document;
    ((MSHTML::IHTMLDOMNodePtr)document->body)->firstChild

Not only is that hard to read, but the hardest part is that the Microsoft
documentation is usually not too good about specifying which interface each MSHTML
property and method actually belongs to, so figuring out that firstChild is
a member of IHTMLDOMNodePtr is laborious (usually I find it by searching through
the #import-generated mshtml.tlh).

With CDispatchPtr, though, it's much easier to write, and also to read:

    CDispatchPtr document;
    document.Get("body").Get("firstChild")

I ran some crude timing tests to compare C++ native calls, C++ with CDispatchPtr
(and thus IDispatch), and Javascript (which also uses IDispatch).  In each case,
the code repeated a loop 1000 times, and inside the loop, the code did a number
of Get/Put/Invoke operations on an HTML document.

Here are the results:

    C++ with native calls:  1.45 seconds
    C++ with CDispatchPtr:  2.33 seconds
    Javascript:             3.74 seconds

As you can see, CDispatchPtr is about 60% slower than using native calls.  That's
quite a significant slowdown.  However, as I mentioned, this was repeating a loop
1000 times (on my PIII 500MHz).  The inner loop performed 13 Get/Put/Invoke
operations, for a total of 13,000 operations.  Considering that CDispatchPtr
completed that in 2.33 seconds, it's clear that in most cases, the extra overhead
of IDispatch is not a problem.
 */
 