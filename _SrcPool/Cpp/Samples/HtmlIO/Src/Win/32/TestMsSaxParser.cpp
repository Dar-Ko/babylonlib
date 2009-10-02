/*$Workfile: TestMsSaxParser.cpp$: implementation file
  $Revision: 14$ $Date: 2005-04-26 01:25:06$
  $Author: Darko$

  Test Microsoft XML SAX parser
  Copyright: CommonSoft Inc.
  2005-03-16 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include <comutil.h> //_bstr_t class
#include "KXmlProcessorSax.h"  //CXmlProcessorSax class
#include "KXmlSaxHandler.h"    //CXmlSaxHandler class
#include "KXmlSaxErrorHandler.h" //CXmlSaxErrorHandler class
#include "KXmlStringData.h" //CXmlStringData class

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);

#ifdef _WTL_VER
  #if (_ATL_VER < 0x0700)
    //Windows Template Library (WTL) main module. See <atlmisc.h>
    CAppModule _Module;
  #endif
#endif


///////////////////////////////////////////////////////////////////////////////
//Test implementation of the XML document handler
class CTestMsSaxHandler : public CXmlSaxHandler
  {
  public:
    CTestMsSaxHandler();
    virtual ~CTestMsSaxHandler();
    virtual HRESULT STDMETHODCALLTYPE startDocument();
    virtual HRESULT STDMETHODCALLTYPE endDocument();
    virtual HRESULT STDMETHODCALLTYPE endElement(const wchar_t __RPC_FAR *pwchNamespaceUri,
                                                  int cchNamespaceUri,
                                                  const wchar_t __RPC_FAR *pwchLocalName,
                                                  int cchLocalName,
                                                  const wchar_t __RPC_FAR *pwchQName,
                                                  int cchQName);
  protected:
    unsigned long m_nCount;  //document's element counter
  };

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
/*
 */
CTestMsSaxHandler::CTestMsSaxHandler() :
    m_nCount(0)
{
}

//-----------------------------------------------------------------------------
/*
 */
CTestMsSaxHandler::~CTestMsSaxHandler()
{
}


//-----------------------------------------------------------------------------
/*Handles notification of the beginning of a document.

  Returns: S_OK if no errors occur or E_FAIL if the parse operation should be
  aborted.
 */
HRESULT STDMETHODCALLTYPE  CTestMsSaxHandler::startDocument ( )
{
TRACE(_T("CTestMsSaxHandler::startDocument()\n"));
CXmlSaxHandler::startDocument(); //Count attributes

m_nCount = 0; //Reset the element counter
return S_OK;
}

//-----------------------------------------------------------------------------
/*Handles notification of the end of a document.
  Returns: S_OK if no errors occur or E_FAIL if the parse operation should be
  aborted.
 */
inline HRESULT STDMETHODCALLTYPE CTestMsSaxHandler::endDocument()
{
TRACE(_T("CTestMsSaxHandler::endDocument()\n"));

TsWriteToView(_T("Found "));
TsWriteToView((int)m_nCount);
TsWriteToViewLn(_T(" items in the document."));

return S_OK;
}

//-----------------------------------------------------------------------------
/*Handles notification of the end of an element. This implemetation counts
  XML elements found in the given document.

  Returns: S_OK if no errors occur or E_FAIL if the parse operation should be
  aborted.
 */
inline HRESULT STDMETHODCALLTYPE CTestMsSaxHandler::endElement(
      const wchar_t __RPC_FAR *pwchNamespaceUri,//[in] namespace URI.
      int cchNamespaceUri,                //[in] length of the namespace URI string.
      const wchar_t __RPC_FAR *pwchLocalName,   //[in] local name string.
      int cchLocalName,                   //[in] length of the local name string.
      const wchar_t __RPC_FAR *pwchQName ,     //[in] the QName, with prefix
                            //or an empty string (if QNames are not available).
      int cchQName                       //[in] length of the QName string.
      )
{
CXmlStringData strQuery(pwchQName, cchQName);
#ifdef _UNICODE //TODO: Unicode _CrtDbgReport
  TRACE1(_T("CTestMsSaxHandler::endElement(%ws)\n"), (LPCSTR)strQuery);
#else
  TRACE1(_T("CTestMsSaxHandler::endElement(%s)\n"), (LPCSTR)strQuery);
#endif
CXmlSaxHandler::endElement(pwchNamespaceUri,
                           cchNamespaceUri,
                           pwchLocalName,
                           cchLocalName,
                           pwchQName,
                           cchQName); //Print element value

m_nCount++; //Count elements

return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
/*Function validates XML parser framework.

  Returns: true if successful, otherwise returns false.
 */
bool TestXmlParser(int argc, //[in] specifies how many arguments are passed
                          // to the program from the command line. The value of
                          // argc is at least one: the program name.
                   TCHAR* argv[] //[in] the program arguments as an array of
                          //pointers to null-terminated strings. The first string
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
                   )
{
TsWriteToView(_T("TestXmlParser()\r\n"));
bool bRes = true;
TESTENTRY logEntry =
  {_T("IXmlParser()"), _T("KXmlParserI.h"), bRes};

if (argc > 0)
  {
  TsWriteToView(_T("Application "));
  TsWriteToView(argv[0]);
  TsWriteToView(_T(" has "));
  TsWriteToView(argc);
  TsWriteToViewLn(_T(" argument(s)"));
  }

//Create Microsoft XML SAX parser
CXmlProcessorSax  xmlParser;
CTestMsSaxHandler xmlDocHandler;

logEntry.m_bResult = bRes;
LogTest(&logEntry);

LPTSTR strDocument;
if (argc <= 1)
  strDocument = _T("S:\\_SrcPool\\Cpp\\Samples\\HtmlIO\\Res\\TestIndex.xml");
else
  strDocument = _T("TODO:");

LPTSTR strXsdSchema = _T("S:\\_SrcPool\\Cpp\\Samples\\HtmlIO\\Res\\TestIndex.xsd");

TsWriteToViewLn(strDocument);

logEntry.m_szObjectName = _T("CXmlProcessorSax::Create()");
logEntry.m_szFileName = _T("KXmlProcessorSax.cpp");

//Parse XML document
if( bRes = xmlParser.Create(xmlDocHandler))
  {
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CXmlProcessorSax::Parse()");
  logEntry.m_szFileName = _T("KXmlProcessorSax.cpp");

  bRes = xmlParser.ParseUrl(strDocument);

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

//Create SAX error handler and validate document
if (bRes)
  {
  logEntry.m_szObjectName = _T("CXmlSaxErrorHandler::CXmlSaxErrorHandler()");
  logEntry.m_szFileName = _T("KXmlSaxErrorHandler.h");

  CXmlSaxErrorHandler xmlErrHandler;

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CXmlProcessorSax::SetErrHandler()");
  logEntry.m_szFileName = _T("KXmlProcessorSax.cpp");

  bRes = xmlParser.SetErrHandler(xmlErrHandler);

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  bRes = xmlParser.SetSchema(strXsdSchema);

  bRes = xmlParser.ParseUrl(strDocument);

  }

logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

#include "KXmlBinding.h" //Xml data binding macros
///////////////////////////////////////////////////////////////////////////////
//Test implementation of the XML document handler
class CTestMsSaxFinder : public CTestMsSaxHandler
  {
  public:
    CTestMsSaxFinder();
    virtual ~CTestMsSaxFinder();

  protected:
    BEGIN_XML_BINDING(L"CustomerOrder", CTestMsSaxFinder)
        XML_ELEMENT(L"OrderID",  eXML_INT,    m_iOrderId)
        XML_ELEMENT(L"Customer", eXML_STRING, m_wszCustomerName)
        XML_ELEMENT(L"Item",     eXML_STRING, m_wszItemName)
        XML_ELEMENT(L"Unit",     eXML_STRING, m_wszUnit)
        XML_ELEMENT(L"Quantity", eXML_DOUBLE, m_dQuantity)
    END_XML_BINDING()

    int       m_iOrderId;
    wchar_t   m_wszCustomerName[20];
    wchar_t   m_wszItemName[20];
    wchar_t   m_wszUnit[20];
    double    m_dQuantity;

  };

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
/*
 */
CTestMsSaxFinder::CTestMsSaxFinder() 
{
}

//-----------------------------------------------------------------------------
/*
 */
CTestMsSaxFinder::~CTestMsSaxFinder()
{
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
/*Test finding XML elements.

  Returns: true if successful, otherwise returns false.
 */
bool TestXmlFinder(int argc, //[in] specifies how many arguments are passed
                          // to the program from the command line. The value of
                          // argc is at least one: the program name.
                   TCHAR* argv[] //[in] the program arguments as an array of
                          //pointers to null-terminated strings. The first string
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
                   )
{
TsWriteToView(_T("TestXmlFinder()\r\n"));
bool bRes = true;
TESTENTRY logEntry =
  {_T("BEGIN_XML_BINDING()"), _T("KXmlBinding.h"), bRes};
logEntry.m_bResult = bRes;
LogTest(&logEntry);

LPTSTR strDocument;
if (argc <= 1)
  strDocument = _T("S:\\_SrcPool\\Cpp\\Samples\\HtmlIO\\Res\\TestIndex.xml");
else
  strDocument = _T("TODO:");

//Create Microsoft XML SAX parser
CXmlProcessorSax  xmlParser;
CTestMsSaxFinder  xmlDocHandler;

if( bRes = xmlParser.Create(xmlDocHandler))
  {
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

TsWriteToViewLn(LOG_EOT);
return bRes;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2005-03-22 01:19:51  Darko
 *  2    Biblioteka1.1         2005-03-22 01:18:08  Darko           pasrer Creat()
 *       added
 *  1    Biblioteka1.0         2005-03-21 02:25:05  Darko
 * $
 *****************************************************************************/
