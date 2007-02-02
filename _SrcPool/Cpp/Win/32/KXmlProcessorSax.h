/*$Workfile: KXmlProcessorSax.h$: header file
  $Revision: 9$ $Date: 2005-04-26 11:36:01$
  $Author: Darko Kolakovic$

  MS XML SAX Parser
  Copyright: CommonSoft Inc
  2005-03-01  Darko Kolakovic
 */
// Group=Windows

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KXMLPROCESSORSAXMS_H_
    //$Workfile: KXmlProcessorSax.h$ sentry
  #define _KXMLPROCESSORSAXMS_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include "KXmlParserI.h"  //IXMLProcessor class
#include <atlbase.h>  //ATL support
#include <msxml2.h>   //ISAXXMLReader

class CXmlSaxHandler;
class CXmlSaxErrorHandler;

///////////////////////////////////////////////////////////////////////////////
/*CXmlProcessorSax description.

  The Simple API for XML (SAX) is a publicly developed standard for
  the events-based (streaming, push) parsing of XML documents. SAX defines an
  abstract programmatic interface that models the XML information set (infoset)
  through a linear sequence of method calls defined by SAX.

  The application have to implement certain event handlers defined by the
  standard. When the SAX parser reads the input XML stream character by
  character, those events will be send (pushed) to the application by calling
  the interface methods.

  SAX is an alternative to DOM, when parsing large XML document or when the
  document have to be interpreted sequentially.

  The ISAXContentHandler interface is the basic parsing interface that defines
  the methods such as startDocument, endDocument, startElement and so on.
  Applications can implements this interface to receive the notifications of
  the logical content of a document.

  The ISAXXMLReader interface allows an application to set and query features
  and properties in Microsoft XML Core Services (MSXML), register event
  handling for document processing and initiate a document parse.

  Note: Microsoft Windows specific (Win32)
       and uses Active Template Library 7.0+ (ATL).

  See also: ISAXContentHandler, ISAXXMLReader
*/
class CXmlProcessorSax//: public IXMLProcessor<int>
{
public:
  CXmlProcessorSax();
  CXmlProcessorSax(const CXmlProcessorSax& dtValue);

  virtual ~CXmlProcessorSax();

public:
  virtual bool Create(const CXmlSaxHandler& xmlHandler);
  virtual bool SetHandler(const CXmlSaxHandler& xmlHandler) const;
  virtual bool SetErrHandler(const CXmlSaxErrorHandler& xmlHandler) const;
  virtual bool SetSchema(LPCTSTR szXsdSchema);

  virtual bool ParseUrl(LPCTSTR szDocument);
  CXmlProcessorSax& operator=(const CXmlProcessorSax& dtValue);

protected:
  ATL::CComPtr<ISAXXMLReader> m_xmlEngine;
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
 */
inline CXmlProcessorSax& CXmlProcessorSax::operator=(const CXmlProcessorSax& dtValue //[in] value to assign
                            )
{
//!todo:
//...
return *this;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KXMLPROCESSORSAXMS_H_
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2005-03-23 03:24:18  Darko           comment
 *  2    Biblioteka1.1         2005-03-22 01:16:57  Darko           added Create()
 *  1    Biblioteka1.0         2005-03-21 02:17:45  Darko
 * $
 *****************************************************************************/
