/*$Workfile: KXmlProcessorSax.cpp$: implementation file
  $Revision: 15$ $Date: 2007-05-22 17:41:19$
  $Author: Darko Kolakovic$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2005-03-01 Darko Kolakovic
 */

#include "stdafx.h"
#include <atlbase.h>  //ATL support

#include <msxml2.h>   //ISAXXMLReader

#include "KXmlProcessorSax.h"  //CXmlProcessorSax class
#include "KXmlSaxHandler.h" //CXmlSaxHandler class
#include "KXmlStringData.h" //CXmlStringData class

#if _MSC_VER <= 1200  //Microsoft Visual C++, 32-bit, version 6.0
  #pragma comment( lib, "ole32" )
  #pragma comment( lib, "msxml2" )
#endif


//include information from the MsXml type library
#import <msxml4.dll> raw_interfaces_only
//using namespace MSXML2;


#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

void DisplayError(_com_error &e);

///////////////////////////////////////////////////////////////////////////////
// CXmlProcessorSax class

//-----------------------------------------------------------------------------
/*Default constructor initializes the COM library.
  Requires ole32.lib.
 */
CXmlProcessorSax::CXmlProcessorSax()
{
/*To use basic COM services, all COM threads of execution in clients and
  out-of-process servers must call either the CoInitialize() or
  the CoInitializeEx() function before calling any other COM function except
  memory allocation calls.
 */

//Initializes the COM library on the current thread and identifies the concurrency
//model as single-thread apartment (STA).
VERIFY(::CoInitialize(NULL) == S_OK);
}


//-----------------------------------------------------------------------------
/*Destructor closes the COM library on the current thread.
  Throws E_UNEXPECTED
 */
CXmlProcessorSax::~CXmlProcessorSax()
{
try
  {
  m_xmlEngine.Release();
  }
catch(_com_error &e)
  {
  ATLTRACE2(ATL::atlTraceCOM, 0, _T("  Exception trown by ATL Release()!\n"));
  DisplayError(e);
  }
catch(...)
  {
  ATLTRACE2(ATL::atlTraceCOM, 0, _T("  Generic exception trown by ATL Release()!\n"));
  throw _com_error(E_UNEXPECTED);
  }
::CoUninitialize();
}

//-----------------------------------------------------------------------------
/*
  Returns: true if successful, false in case of a failure.
 */
bool CXmlProcessorSax::Create(const CXmlSaxHandler& xmlHandler)
{
ATLTRACE2(ATL::atlTraceCOM, 0, _T("CXmlProcessorSax::Create()\n"));
try
  {
  // Create an instance of the XML processor
  //HRESULT hr = m_xmlEngine.CoCreateInstance(__uuidof(SAXXMLReader));

  //Requires Microsoft XML Core Services (MSXML) 4.0 
  HRESULT hr = (!m_xmlEngine) ?
        m_xmlEngine.CoCreateInstance(__uuidof(SAXXMLReader40)) :
        S_OK;

  /*Note:
      Microsoft XML Core Services (MSXML),  Version 4.0
      Dependent ProgID: SAXXMLReader40
      Dependent CLSID:  88d969c7-f192-11d4-a65f-0040963251e5
  */
  if ( SUCCEEDED(hr) )
    {
    if (!SetHandler(xmlHandler))
      return false;
    }
  else
    throw _com_error(hr);
  }
catch(_com_error &e)
  {
  ATLTRACE2(ATL::atlTraceCOM, 0, _T("  Exception trown by ATL CoCreateInstance()!\n"));
  DisplayError(e);
  return false;
  }

return true;
}

//-----------------------------------------------------------------------------
/*Set a document handler. It is possible to set a new or different handler
  while in the middle of parsing a document, and the reader will immediately
  start using the new handler.

  Returns: true if successful, false in case of a failure.
 */
bool CXmlProcessorSax::SetHandler(const CXmlSaxHandler& xmlHandler //[in]
                                                 //ContentHandler to register
                                 ) const
{
ATLTRACE2(ATL::atlTraceCOM, 0, _T("CXmlProcessorSax::SetHandler()\n"));
try
  {
  if (m_xmlEngine.p == NULL)
    throw _com_error(E_POINTER);

  HRESULT hr = m_xmlEngine->putContentHandler((ISAXContentHandler*)&xmlHandler);
  if ( FAILED(hr) )
    throw _com_error(hr);
  return true;
  }
catch(_com_error &e)
  {
  ATLTRACE2(ATL::atlTraceCOM, 0, _T("  Exception trown by SAX putContentHandler()!\n"));
  DisplayError(e);
  return false;
  }
}

//-----------------------------------------------------------------------------
/*Set a document handler. It is possible to set a new or different handler
  while in the middle of parsing a document, and the reader will immediately
  start using the new handler.

  Returns: true if successful, false in case of a failure.
 */
bool CXmlProcessorSax::SetErrHandler(const CXmlSaxErrorHandler& xmlHandler //[in]
                                    ) const
{
ATLTRACE2(ATL::atlTraceCOM, 0, _T("CXmlProcessorSax::SetErrHandler()\n"));
try
  {
  if (m_xmlEngine.p == NULL)
    throw _com_error(E_POINTER);

  HRESULT hr = m_xmlEngine->putErrorHandler((ISAXErrorHandler*)&xmlHandler);
  if ( FAILED(hr) )
    throw _com_error(hr);
  return true;
  }
catch(_com_error &e)
  {
  ATLTRACE2(ATL::atlTraceCOM, 0, _T("  Exception trown by SAX putErrorHandler()!\n"));
  DisplayError(e);
  return false;
  }
}

/*!todo TODO: reset error handler
ReetErrHandler()
{
m_xmlEngine->putErrorHandler(NULL);
}
*/

//-----------------------------------------------------------------------------
/*Call this method to parse an XML document.

  Note: If you are using Microsoft® Internet Explorer 5.5, you may get an 
  E_PENDING error when you attempt to load an XML file that has external 
  entities. To correct this situation, upgrade to Internet Explorer 5.5, 
  Service Pack 1.

  Returns: true if succesful; otherwise returns false
 */
bool CXmlProcessorSax::ParseUrl(LPCTSTR szDocument //[in] string value that 
                                                   //contains the URL to parse
                               )
{
#ifndef _UNICODE
  TRACE1(_T("CXmlProcessorSax::ParseUrl(%s)\n"), szDocument
        );
#endif
try
  {
  m_xmlEngine->parseURL(CXmlStringData(szDocument));
  return true;
  }
catch(_com_error &e)
  {
  ATLTRACE2(ATL::atlTraceCOM, 0, _T("  Exception trown by ATL CoCreateInstance()!\n"));
  DisplayError(e);
  return false;
  }
catch(...)
  {
  ATLTRACE2(ATL::atlTraceCOM, 0, _T("  Generic exception trown by ATL ParseURL()!\n"));
  return false;
  }
}

//-----------------------------------------------------------------------------
/*Validates an XML document against an W3C XML Schema (XSD) or an XML
  Data-Reduced (XDR) schema or verifies the well-formedness of the XML document.

  Returns; true/ false
 */
bool CXmlProcessorSax::SetSchema(LPCTSTR szXsdSchema //[in] XML Schema Definition
                                                     //file name
                               )
{
try
  {
  if ((szXsdSchema == NULL) || (szXsdSchema[0] == _T('\0')) )
    return false;

  MSXML2::IXMLDOMSchemaCollection2Ptr pSchemaCache;
  HRESULT hr = pSchemaCache.CreateInstance(__uuidof(XMLSchemaCache40));
  if ( FAILED(hr) )
    throw _com_error(hr);

    //Convert file name to BSTR
  //CStringT< TCHAR, StrTraitATL<TCHAR> > strXsdSchema(szXsdSchema); !todo: D.K. Replaced TCHAR with  wchar_t;  test the benefits
  CXmlString strXsdSchema(szXsdSchema);
  CComVariant cvXSDFileName;
  cvXSDFileName.vt = VT_BSTR;
  cvXSDFileName.bstrVal = strXsdSchema.AllocSysString();

    //Add a new schema to the schema collection and associates the given namespace
    //URI with the specified schema.
  hr = pSchemaCache->add(L"",          //namespace to associate with the specified
                                       //schema (xmlns:).
                         cvXSDFileName //specifies the schema (URL or DOMDocument)
                                       // or NULL to remove the schema
                         );
  if ( FAILED(hr) )
    throw _com_error(hr);

  //Include all external general (text) entities
  CXmlStringData strValidation(_T("schema-validation"));
  hr = m_xmlEngine->putFeature((const wchar_t*)strValidation, VARIANT_TRUE);

  //Report all validation errors
  CXmlStringData strReport(_T("exhaustive-errors"));
  hr = m_xmlEngine->putFeature((const wchar_t*)strReport, VARIANT_TRUE);

  //Register a schema with the SAX reader.
  CXmlStringData strSchemas(_T("schemas"));
  hr = m_xmlEngine->putProperty((const wchar_t*)strSchemas, //any Uniform Resource
                                            //Identifier (URI) as property's name
                               _variant_t(pSchemaCache.GetInterfacePtr())//data
                                            //type of the property
                               );

  return true;
  }
catch(_com_error &e)
  {
  ATLTRACE2(ATL::atlTraceCOM, 0, _T("  Exception trown by ATL CoCreateInstance()!\n"));
  DisplayError(e);
  return false;
  }
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  6    Biblioteka1.5         2005-03-31 03:05:51  Darko           SetSchema()
 *  5    Biblioteka1.4         2005-03-27 23:04:41  Darko           SetErrHandler()
 *  4    Biblioteka1.3         2005-03-26 01:12:26  Darko           Added Parse()
 *  3    Biblioteka1.2         2005-03-23 04:24:57  Darko           test case
 *  2    Biblioteka1.1         2005-03-22 02:16:55  Darko           added Create()
 *  1    Biblioteka1.0         2005-03-21 03:17:44  Darko
 * $
 *****************************************************************************/
