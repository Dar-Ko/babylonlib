/*$Workfile: KXmlSaxHandler.h$: header file
  $Revision: 12$ $Date: 2005-05-01 00:34:25$
  $Author: Darko$

  Base class for the XML content handler
  Copyright: CommonSoft Inc
  2005-03-01 Darko Kolakovic
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KXMLSAXHANDLERMS_H_
    //$Workfile: KXmlSaxHandler.h$ sentry
  #define _KXMLSAXHANDLERMS_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include <atlbase.h>  //ATL support
#include "Win/32/KXmlTypeWin.h" //XML's typedef

///////////////////////////////////////////////////////////////////////////////
/*{group:Windows}
  CXmlSaxHandler class is the default implementation of
  the ISAXContentHandler interface used to receive the notifications of the
  logical content of a document, such as startDocument, startElement, characters,
  endElement, endDocument. Use this class as a base class for the more
  customized handler and implement the methods required by application.

  Note: Microsoft Windows specific (Win32)
       and uses Active Template Library 7.0+ (ATL).

  See also: ISAXContentHandler
*/
class CXmlSaxHandler : public ISAXContentHandler
{
public:
  CXmlSaxHandler();
  virtual ~CXmlSaxHandler();

  //ISAXContentHandler interface implemetation
protected:
  virtual HRESULT STDMETHODCALLTYPE putDocumentLocator( ISAXLocator __RPC_FAR *pLocator);
  virtual HRESULT STDMETHODCALLTYPE startDocument();
  virtual HRESULT STDMETHODCALLTYPE endDocument();
  virtual HRESULT STDMETHODCALLTYPE
                  startPrefixMapping( const wchar_t __RPC_FAR *pwchPrefix,
                                      int cchPrefix,
                                      const wchar_t __RPC_FAR *pwchUri,
                                      int cchUri);
  virtual HRESULT STDMETHODCALLTYPE
                    endPrefixMapping( const wchar_t __RPC_FAR *pwchPrefix,
                                      int cchPrefix);
  virtual HRESULT STDMETHODCALLTYPE
                        startElement( const wchar_t __RPC_FAR *pwchNamespaceUri,
                                      int cchNamespaceUri,
                                      const wchar_t __RPC_FAR *pwchLocalName,
                                      int cchLocalName,
                                      const wchar_t __RPC_FAR *pwchQName,
                                      int cchQName,
                                      ISAXAttributes __RPC_FAR *pAttributes);
  virtual HRESULT STDMETHODCALLTYPE
                          endElement( const wchar_t __RPC_FAR *pwchNamespaceUri,
                                      int cchNamespaceUri,
                                      const wchar_t __RPC_FAR *pwchLocalName,
                                      int cchLocalName,
                                      const wchar_t __RPC_FAR *pwchQName,
                                      int cchQName);
  virtual HRESULT STDMETHODCALLTYPE
                          characters( const wchar_t __RPC_FAR *pwchChars,
                                      int cchChars);
  virtual HRESULT STDMETHODCALLTYPE
                 ignorableWhitespace( const wchar_t __RPC_FAR *pwchChars,
                                      int cchChars);
  virtual HRESULT STDMETHODCALLTYPE
               processingInstruction( const wchar_t __RPC_FAR *pwchTarget,
                                      int cchTarget,
                                      const wchar_t __RPC_FAR *pwchData,
                                      int cchData);
  virtual HRESULT STDMETHODCALLTYPE
                       skippedEntity( const wchar_t __RPC_FAR *pwchName,
                                      int cchName);

  //IUnknown interface implemetation
public:
  long __stdcall QueryInterface(REFIID iid, void ** ppvObject);
  unsigned long __stdcall AddRef();
  unsigned long __stdcall Release();

protected:
  CXmlString m_strElementValue; //value of an XML element

private:
  unsigned long m_nRefCount; //reference counter indicates the state of the COM object
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
 */
inline
CXmlSaxHandler::CXmlSaxHandler() :
      m_nRefCount(1)

  {
  ATLTRACE2(ATL::atlTraceCOM, 1, _T("CXmlSaxHandler::CXmlSaxHandler()\n"));
  }

//-----------------------------------------------------------------------------
/*
 */
inline
CXmlSaxHandler::~CXmlSaxHandler()
  {
  ATLTRACE2(ATL::atlTraceCOM, 1, _T("CXmlSaxHandler::~CXmlSaxHandler()\n"));
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
inline  long __stdcall CXmlSaxHandler::QueryInterface(
                      REFIID iid, //[in] identifier of the interface being
                           //requested
                      void ** ppvObject //[out] address of pointer variable that
                           //receives the interface pointer requested in riid.
                      )
  {
  *ppvObject = NULL;
  if( (iid == IID_IUnknown) || (iid == __uuidof(ISAXContentHandler)) )
    {
    *ppvObject = static_cast<ISAXContentHandler *>(this);
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
inline unsigned long __stdcall CXmlSaxHandler::AddRef()
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
inline unsigned long __stdcall CXmlSaxHandler::Release()
  {
  ATLTRACE2(ATL::atlTraceCOM, 1, _T("CXmlSaxHandler::Release()\n"));
  LONG lResDec = InterlockedDecrement((LONG*)&m_nRefCount);
  //Note: Win95: lResDec matches the decremented variable only by sign; values
  //ares not necessarily equal.

  unsigned long nResult = m_nRefCount;

  if (lResDec <= 0)
    delete this;
  return nResult;
  }

//-----------------------------------------------------------------------------
/*Receives an interface for locating the origin of Simple API for XML (SAX)
  document events. The reader supplies a locator to the application by invoking
  this method before invoking any other methods in the ISAXContentHandler
  interface. This locator allows the application to determine the end position
  of any document-related event, even if the parser is not reporting an error.
  Typically, the application uses this information to report its own errors
  (for example, if the character content does not match the business rules of
  the application).

  Note: The locator returns the correct information only during the invocation
         of events in this interface. The application should not attempt to use
         this method at any other time.

  Returns: S_OK if no errors occur or E_FAIL if the parse operation should be
  aborted.

  See also: ISAXLocator
 */
inline HRESULT STDMETHODCALLTYPE CXmlSaxHandler::putDocumentLocator(
      ISAXLocator __RPC_FAR *pLocator //[in] pointer to a valid instance of
                                      //the ISAXLocator interface.
      )
  {
  UNUSED(pLocator);
  ATLTRACE2(ATL::atlTraceCOM, 1, _T("CXmlSaxHandler::putDocumentLocator()\n"));
  return S_OK;
  }

//-----------------------------------------------------------------------------
/*Handles notification of the beginning of a document. The beginning of a
  document is also referred to as the root element and describes what kind of
  XML document it is. The root element must be the first element in an XML
  document and there can only be one root element.

  The reader invokes the startDocument() method only once after the
  putDocumentLocator() method, but before any other methods in the
  ISAXContentHandler interface.

  Returns: S_OK if no errors occur or E_FAIL if the parse operation should be
  aborted.
 */
inline HRESULT STDMETHODCALLTYPE CXmlSaxHandler::startDocument()
  {
  ATLTRACE2(ATL::atlTraceCOM, 1, _T("CXmlSaxHandler::startDocument()\n"));
  return S_OK;
  }

//-----------------------------------------------------------------------------
/*Handles notification of the end of a document. The reader invokes
  the endDocument() method only once. The endDocument() method is the last
  method invoked during the parse. The reader does not invoke this method until
  it has either abandoned parsing upon encountering an unrecoverable error or has
  reached the end of the document.

  Returns: S_OK if no errors occur or E_FAIL if the parse operation should be
  aborted.
 */
inline HRESULT STDMETHODCALLTYPE CXmlSaxHandler::endDocument()
  {
  ATLTRACE2(ATL::atlTraceCOM, 1, _T("CXmlSaxHandler::endDocument()\n"));
  return S_OK;
  }

//-----------------------------------------------------------------------------
/*Begins the scope of the prefix-URI namespace mapping. This method is always
  invoked before the corresponding startElement() method. The order of
  the different startPrefixMapping() events is not guaranteed.

  Returns: S_OK if no errors occur or E_FAIL if the parse operation should be
  aborted.
 */
inline HRESULT STDMETHODCALLTYPE CXmlSaxHandler::startPrefixMapping(
       const wchar_t __RPC_FAR *pwchPrefix,//[in] prefix being mapped
       int cchPrefix, //[in] length of the prefix string or –1
                      //for zero-terminated strings
       const wchar_t __RPC_FAR *pwchUri,   //[in] namespace URI
                      //to which the prefix is mapped
       int cchUri     //[in] length of the namespace URI string
       )
  {
  UNUSED(pwchPrefix);
  UNUSED(cchUri);
  UNUSED(pwchUri);
  ATLTRACE2(ATL::atlTraceCOM, 1, _T("CXmlSaxHandler::startPrefixMapping()\n"));
  return S_OK;
  }

//-----------------------------------------------------------------------------
/*The SAX reader calls this method after the corresponding endElement method to
  end the scope of the prefix-URI namespace mapping. The order of the different
  endPrefixMapping events is not guaranteed.

  The information from this event is not necessary for normal namespace processing.
  The reader automatically replaces prefixes for element and attribute names when
  the "http://xml.org/sax/features/namespaces" feature is set to True (the default).

  There are cases, however, when applications need to use prefixes in character
  data or in attribute values and they cannot safely be expanded automatically.
  In these cases, the startPrefixMapping and endPrefixMapping methods can supply
  the information needed to expand prefixes.

  Returns: S_OK if no errors occur or E_FAIL if the parse operation should be
  aborted.
 */
inline HRESULT STDMETHODCALLTYPE CXmlSaxHandler::endPrefixMapping(
       const wchar_t __RPC_FAR *pwchPrefix,//[in] prefix being mapped.
       int cchPrefix                 //[in] length of the prefix string.
       )
  {
  ATLTRACE2(ATL::atlTraceCOM, 1, _T("CXmlSaxHandler::endPrefixMapping()\n"));
  return S_OK;
  }

//-----------------------------------------------------------------------------
/*Handles notification of the beginning of an element. The reader invokes
  the startElement method at the beginning of every element in the XML document.
  A corresponding endElement method is called for every startElement event, even
  when the element is empty.
  This event allows up to three name components for each element:
    - the namespace URI,
    - the local name.
    - the qualified XML 1.0 name (QName), with prefix or an empty string if
      the QName is not available.
  Any or all of these name components may be provided, depending on the values
  of the "http://xml.org/sax/features/namespaces" and
  the "http://xml.org/sax/features/namespace-prefixes" features. The namespace
  URI and local name are required when the
  "http://xml.org/sax/features/namespaces" feature is set to true (the default).
  hese values are optional when this feature is set to false.

  The attribute list provided contains only attributes with explicit values
  (specified or default). The attribute list omits #IMPLIED attributes.
  Furthermore, the attribute list contains attributes used for namespace
  declarations (xmlns* attributes) only if
  the "http://xml.org/sax/features/namespace-prefixes" feature is set to true.
  This feature is set to False by default.

  An XML element is everything from (including) the element's start tag to
  (including) the element's end tag. An element can have element content,
  mixed content, simple content, or empty content. An element can also have
  attributes.
  XML elements must follow these naming rules:
    - Names can contain letters, numbers, and other characters
    - Names must not start with a number or punctuation character
    - Names must not start with the letters xml (or XML or Xml ..)
    - Names cannot contain spaces

  Note: Neither the URI nor the local name value can be specified alone. Both
  values are required if either is used. The qualified name is required when
  the "http://xml.org/sax/features/namespaces-prefixes feature" is set to true
  and is optional when this feature is set to default value false.

  Returns: S_OK if no errors occur or E_FAIL if the parse operation should be
  aborted.

  See also: {html: <a href="http://www.w3.org/TR/2001/REC-xml-infoset-20011024">
            XML Information Set</a>}
 */
inline HRESULT STDMETHODCALLTYPE CXmlSaxHandler::startElement(
      const wchar_t __RPC_FAR *pwchNamespaceUri,//[in] namespace URI.
      int cchNamespaceUri,                //[in] length of the namespace URI string.
      const wchar_t __RPC_FAR *pwchLocalName,   //[in] local name string.
      int cchLocalName,                   //[in] length of the local name string.
      const wchar_t __RPC_FAR *pwchQName ,     //[in] the qualified name, with prefix
                            //or an empty string (if qualified names are not available).
      int cchQName,                       //[in] length of the qualified name string.
      ISAXAttributes __RPC_FAR *pAttributes//[in] attributes attached to the element.
      )
  {
  UNUSED(pwchNamespaceUri);
  UNUSED(cchNamespaceUri);
  UNUSED(pwchLocalName);
  UNUSED(cchLocalName);
  UNUSED(pwchQName);
  UNUSED(cchQName);
  TRACE0( "CXmlSaxHandler::startElement()\n");
  m_strElementValue.Empty();
  int iAttributes; //number of attributes encountered while processing an XML element
  pAttributes->getLength(&iAttributes);

  return S_OK;
  }

//-----------------------------------------------------------------------------
/*Handles notification of the end of an element. The reader invokes this method
  at the end of every element in the XML document. A corresponding startElement
  event occurs for every endElement event, even when the element is empty.
  This event allows up to three name components for each element:
    - the namespace URI,
    - the local name.
    - the qualified XML 1.0 name (QName), with prefix or an empty string if
      the QName is not available.

  Any or all of these name components may be provided, depending on the values
  of the namespaces and the namespace-prefix features. The namespace URI and
  local name are required when the namespaces feature is set to true (the
  default). These values are optional when this feature is set to false.

  Note: Neither the URI nor the local name value can be specified alone. Both
  values are required if either is used. The QName is required when
  the namespace feature is set to true and is optional when this feature is set to default
  value false.

  Qualified name is defined in the XML specifications:
     - {html: <a href="http://www.w3.org/TR/xmlschema-2/#QName">}
       XML Schema Part2: Datatypes specification{html:</a>},
     - {html: <a href="http://www.w3.org/TR/REC-xml-names/#ns-qualnames">}
       Namespaces in XML{html:</a>},
     - {html: <a href="http://www.w3.org/XML/xml-names-19990114-errata">}
       Namespaces in XML Errata{html:</a>}.

  Returns: S_OK if no errors occur or E_FAIL if the parse operation should be
  aborted.
 */
inline HRESULT STDMETHODCALLTYPE CXmlSaxHandler::endElement(
      const wchar_t __RPC_FAR *pwchNamespaceUri,//[in] namespace URI.
      int cchNamespaceUri,                //[in] length of the namespace URI string.
      const wchar_t __RPC_FAR *pwchLocalName,   //[in] local name string.
      int cchLocalName,                   //[in] length of the local name string.
      const wchar_t __RPC_FAR *pwchQName ,     //[in] the QName, with prefix
                            //or an empty string (if QNames are not available).
      int cchQName                       //[in] length of the QName string.
      )
  {
  ATLTRACE2(ATL::atlTraceCOM, 1, _T("CXmlSaxHandler::endElement()\n"));
  return S_OK;
  }

//-----------------------------------------------------------------------------
/*Handles notification of character data.
  The SAX reader calls the characters method to report each chunk of character
  data. The reader can return all contiguous character data in a single chunk
  or split it into several chunks. All characters in a single event, however,
  must come from the same external entity so that the Locator object can provide
  useful information. The application must not attempt to read from the array
  outside the specified range.
  Use this method  to preserve any carriage return (CR) characters in your XML
  document. Otherwise, carriage return/line feed (CR/LF) occurrences are
  converted to LF-only data by the reader.

  Returns: S_OK if the character data is returned successfully or E_FAIL if an
  internal error occurs.
 */
inline HRESULT STDMETHODCALLTYPE CXmlSaxHandler::characters(
       const wchar_t __RPC_FAR *pwchChars,//[in] character data
       int cchChars                 //[in] length of the character data
       )
  {
  ATLTRACE2(ATL::atlTraceCOM, 1, _T("CXmlSaxHandler::characters()\n"));

  //Sum up all chunks containing an element value
  CXmlStringData szValue(pwchChars, cchChars);
  m_strElementValue += (const wchar_t*)szValue;
  return S_OK;
  }

//-----------------------------------------------------------------------------
/*This method is not called in the current implementation because the
  Simple API for XML (SAX2) implementation is nonvalidating. User could call
  this method to pass ignorable white space characters such as space,
  carriage return (CR), tab, or line feed (LF) to the internal buffer of the
  MXXMLWriter object.

  White space can occur in several places, for example, in an element without
  character data, which contains only child nodes and white space.
  To ignore white space, the parser must be able to distinguish those cases.
  The SAX parser is a nonvalidating parser and cannot distinguish those cases,
  so ignorableWhitespace() never gets called. Nonvalidating parsers treat all
  white space between elements as characters.

  Note: Implemented in MsXml 3.0 and later. The ignorableWhitespace method
  does not convert CR/LF("\r\n") to the Java LF('\n') implementation.

  Returns: S_OK if the character data is returned successfully or E_FAIL if an
  internal error occurs.
 */
inline HRESULT STDMETHODCALLTYPE CXmlSaxHandler::ignorableWhitespace(
       const wchar_t __RPC_FAR *pwchChars,//[in] character data
       int cchChars                 //[in] length of the character data
       )
  {
  ATLTRACE2(ATL::atlTraceCOM, 1, _T("CXmlSaxHandler::ignorableWhitespace()\n"));
  return S_OK;
  }

//-----------------------------------------------------------------------------
/*Handles notification of a processing instruction.
  The reader invokes the processingInstruction method once for each processing
  instruction found. Processing instructions can occur before or after the main
  document element.
  The pwchTarget target is the first piece of the processing instruction.
  For example, "xml-stylesheet" is the target for the following processing
  instruction:
        "<?xml–stylesheet href="sample.css" type="text/css" title="Sample" ?>".

  Returns: S_OK if no errors occur or E_FAIL if the parse operation should be
  aborted.
 */
inline HRESULT STDMETHODCALLTYPE CXmlSaxHandler::processingInstruction(
       const wchar_t __RPC_FAR *pwchTarget,//[in] target for the processing instruction
       int cchTarget,                //[in] length of the target string.
       const wchar_t __RPC_FAR *pwchData,  //[in] processing instruction data or NULL
       int cchData                   //[in] length of the processing instruction string
       )
  {
  ATLTRACE2(ATL::atlTraceCOM, 1, _T("CXmlSaxHandler::processingInstruction()\n"));
  return S_OK;
  }

//-----------------------------------------------------------------------------
/*Handles notification of a skipped entity.
  The skippedEntity method is invoked for each entity skipped. The reader may
  skip entities if they have not been seen in the declarations.
  An example of this is when an entity is declared in an external DTD subset.
  The reader may skip external entities, depending on the values of the
  "http://xml.org/sax/features/external-general-entities" and
  "http://xml.org/sax/features/external-parameter-entities" features.
  The skippedEntity method is also called in the case of an external DTD declaration.
  For example:
      <!DOCTYPE xyz SYSTEM "http://…">

  Returns: S_OK if no errors occur or E_FAIL if the parse operation should be
  aborted.
 */
inline HRESULT STDMETHODCALLTYPE CXmlSaxHandler::skippedEntity(
       const wchar_t __RPC_FAR *pwchName,//[in] name of the skipped entity.
               //If the entity is a parameter entity, the name begins with '%'.
       int cchName          //[in] number of characters in the pwchName string.
       )
  {
  ATLTRACE2(ATL::atlTraceCOM, 1, _T("CXmlSaxHandler::skippedEntity()\n"));
  return S_OK;
  }


///////////////////////////////////////////////////////////////////////////////
#endif  //_KXMLSAXHANDLERMS_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-03-23 03:23:28  Darko
 * $
 *****************************************************************************/
