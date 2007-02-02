/*$Workfile: KXmlSaxErrorHandler.h$: header file
  $Revision: 4$ $Date: 2005-04-26 11:36:03$
  $Author: Darko Kolakovic$

  Base class for the XML error handler
  Copyright: CommonSoft Inc
  2005-03-27 Darko Kolakovic
 */
// Group=Windows

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KXMLSAXERRHANDLERMS_H_
    //$Workfile: KXmlSaxErrorHandler.h$ sentry
  #define _KXMLSAXERRHANDLERMS_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include <msxml2.h>  //ISAXErrorHandler interface
//#include <atlstr.h>  //Non-MFC string objects 

///////////////////////////////////////////////////////////////////////////////
/*CXmlSaxErrorHandler class is the default implementation of
  the ISAXErrorHandler interface used to receive the notifications of the
  error events that are thrown when content of parsed XML document is invalid 
  according to the XSD schema used for validation.

  To implement customized error handling, the application must implement 
  ISAXErrorHandler interface and then register an instance with the SAX2 reader 
  using the putErrorHandler() method. The reader then reports all errors and 
  warnings through this interface. 
  If an application does not register an ErrorHandler, XML parsing errors are 
  unreported and unexpected behavior can occur.

  Note: Microsoft Windows specific (Win)
       and uses Active Template Library 7.0+ (ATL).

  See also: ISAXErrorHandler
*/
class CXmlSaxErrorHandler : public ISAXErrorHandler
{
public:
  CXmlSaxErrorHandler();
  virtual ~CXmlSaxErrorHandler();

public:
  unsigned int GetCount();
  LPCTSTR GetErrorMessage(unsigned int nIndex);

  //ISAXErrorHandler interface implemetation
protected:
    virtual HRESULT STDMETHODCALLTYPE error (struct ISAXLocator* pLocator,
                                             const wchar_t* pwchErrorMessage,
                                             HRESULT hrErrorCode );
    virtual HRESULT STDMETHODCALLTYPE fatalError (struct ISAXLocator* pLocator,
                                             const wchar_t * pwchErrorMessage,
                                             HRESULT hrErrorCode );
    virtual HRESULT STDMETHODCALLTYPE ignorableWarning (struct ISAXLocator* pLocator,
                                             const wchar_t* pwchErrorMessage,
                                             HRESULT hrErrorCode );

  //IUnknown interface implemetation
public:
  long __stdcall QueryInterface(REFIID iid, void ** ppvObject);
  unsigned long __stdcall AddRef();
  unsigned long __stdcall Release();

private:
  unsigned long m_nRefCount; //reference counter indicates the state of the COM object
  CXmlStringArray m_strError; //list of errors occured while validating XML object

  /*!todo: D.K. replaced TCHAR with wchar_t; test the benefits
  CAtlArray< CStringT< TCHAR, ATL::StrTraitATL<TCHAR> > > m_strError; //list
                                  //of errors occured while validating XML object*/

};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
inline
CXmlSaxErrorHandler::CXmlSaxErrorHandler() :
      m_nRefCount(1)
  {
  ATLTRACE2(ATL::atlTraceCOM, 0, _T("CXmlSaxErrorHandler::CXmlSaxErrorHandler()\n"));
  }

//-----------------------------------------------------------------------------
/*Destructor
 */
inline
CXmlSaxErrorHandler::~CXmlSaxErrorHandler()
  {
  ATLTRACE2(ATL::atlTraceCOM, 0, _T("CXmlSaxErrorHandler::~CXmlSaxErrorHandler()\n"));
  }

//-----------------------------------------------------------------------------
/*This method gives a client access to other interfaces on the object.
  For any one object, a specific query for the object's interfaces must
  always return the same pointer value.

  Note: If this method returns pointer to the COM object, it must call
  AddRef() before it returns.

  Returns: S_OK (0) if the interface is supported a pointer to a specified
  interface on an object to which a client currently holds an interface pointer.
  If this is not a COM object at all, returns S_OK and NULL pointer.
  Returns E_NOINTERFACE (0x80004002L) if the interface is not supported.

  See also: <unknwn.h>, IUnknown
 */
inline  long __stdcall CXmlSaxErrorHandler::QueryInterface(
                      REFIID iid, //[in] identifier of the interface being
                           //requested
                      void ** ppvObject //[out] address of pointer variable that
                           //receives the interface pointer requested in riid.
                      )
  {
  *ppvObject = NULL;
  if( (iid == IID_IUnknown) || (iid == __uuidof(ISAXErrorHandler)) )
    {
    *ppvObject = static_cast<ISAXErrorHandler *>(this);
    }

  if (*ppvObject)
    {
    AddRef();
    return S_OK;
    }
  else
    return E_NOINTERFACE;
  }

//-----------------------------------------------------------------------------
/*This method increments the reference count for an interface on the object.
  It should be called for every new copy of a pointer to an interface on a given
  object. For example, if you are passing a copy of a pointer back from a
  function, you must call AddRef() on that pointer.
  You must also call AddRef() on a pointer before passing it as an in-out
  parameter to a function; the function will call Release() before copying the
  out-value on top of it.

  Returns: the value of the new reference count in the range [1, (2^31)-1]
 */
inline unsigned long __stdcall CXmlSaxErrorHandler::AddRef()
  {
  InterlockedIncrement((LONG*)&m_nRefCount);
  return (m_nRefCount);
  }

//-----------------------------------------------------------------------------
/*Decrements the reference count for the calling interface on the object.
  If the reference count on the object falls to 0, the object is freed from memory.
  Call this function when you no longer need to use an interface pointer.
  If you are writing a function that takes an in-out parameter, call Release()
   on the pointer you are passing in before copying the out-value on top of it.

  Returns: resulting value of the reference count.
 */
inline unsigned long __stdcall CXmlSaxErrorHandler::Release()
  {
  ATLTRACE2(ATL::atlTraceCOM, 0, _T("CXmlSaxErrorHandler::Release()\n"));
  LONG lResDec = InterlockedDecrement((LONG*)&m_nRefCount);
  //Note: Win95: lResDec matches the decremented variable only by sign; values
  //ares not necessarily equal.

  unsigned long nResult = m_nRefCount;

  if (lResDec <= 0)
    delete this;
  return nResult;
  }

///////////////////////////////////////////////////////////////////////////////
#endif  //_KXMLSAXERRHANDLERMS_H_
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2005-04-26 11:36:03  Darko Kolakovic Document groups
 *       and typo fixes
 *  3    Biblioteka1.2         2005-04-06 14:49:38  Darko Kolakovic Compiled with
 *       MSVC6
 *  2    Biblioteka1.1         2005-03-27 23:05:19  Darko           Store error
 *       messages
 *  1    Biblioteka1.0         2005-03-27 02:29:01  Darko           
 * $
 *****************************************************************************/
