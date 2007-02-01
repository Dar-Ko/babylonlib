/*$Workfile: KXmlParserI.h$: header file
  $Revision: 3$ $Date: 2005-03-26 00:10:52$
  $Author: Darko$

  XML Parser Interface
  Copyright: CommonSoft Inc
  2005-03-16 Darko Kolakovic
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KXMLPARSERI_H_
    //$Workfile: KXmlParserI.h$ sentry
  #define _KXMLPARSERI_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif


//#include "K<baseclass>.h"  //<baseclass> class

///////////////////////////////////////////////////////////////////////////////
// XML Parser Interface
//
template<typename XMLPARSERTYPE>
class IXmlProcessor: public XMLPARSERTYPE
{
public:
  IXmlProcessor();
  //IXmlProcessor(const IXmlProcessor& dtValue);

  virtual ~IXmlProcessor();

public:
  virtual bool Create() = 0;
  //virtual bool parse() = 0;
  //virtual bool parse(const XmlString&) = 0;

  //virtual void SetValidation(bool bValidate = true) = 0;
  //virtual void SetSchema(bool bValidate = true) = 0;
  //virtual void SetSchemaChecking(bool bValidate = true) = 0;
  //virtual void SetNamespace(bool bValidate = true) = 0;

  //bool IsValidation();
  //bool IsSchema();
  //bool IsSchemaChecking();
  //bool IsNamespaces();

/*  enum
    {
    IXML_VALIDATION_NONE   = 0x00,
    IXML_VALIDATION        = 0x01,
    IXML_SCHEMA            = 0x02,
    IXML_VALIDATION_SCHEMA = 0x04,
    IXML_NAMESPACE         = 0x08
    };
*/

protected:
    //UINT  m_nValidation;  //document validation type
  XMLPARSERTYPE m_xmlEngine;  //XML reader

public:
  //IXmlProcessor& operator=(const IXmlProcessor& dtValue);

public:
  //virtual LPTSTR toString(LPTSTR szTarget);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
 * /
inline IXmlProcessor& IXmlProcessor::operator=(const IXmlProcessor& dtValue //[in] value to assign
                            )
{
...
return *this;
}*/

//-----------------------------------------------------------------------------
/*
 * /
template<typename XMLPARSERTYPE>
void IXmlProcessor<XMLPARSERTYPE>::SetValidation(bool bValidate //[in] = true
                                     )
{
m_nValidation = bValidate ? (m_nValidation | IXML_VALIDATION) :
                            (m_nValidation & ~IXML_VALIDATION);
}

//-----------------------------------------------------------------------------
/*
 * /
template<typename XMLPARSERTYPE>
bool IXmlProcessor<XMLPARSERTYPE>::IsValidation()
{
return ((m_nValidation & IXML_VALIDATION) == IXML_VALIDATION);
}

//-----------------------------------------------------------------------------
/*
 * /
template<typename XMLPARSERTYPE>
void IXmlProcessor<XMLPARSERTYPE>::SetSchema(bool bValidate //[in] = true
                                     )
{
m_nValidation = bValidate ? (m_nValidation | IXML_SCHEMA) :
                            (m_nValidation & ~IXML_SCHEMA);
}

//-----------------------------------------------------------------------------
/*
 * /
template<typename XMLPARSERTYPE>
bool IXmlProcessor<XMLPARSERTYPE>::IsSchema()
{
return ((m_nValidation & IXML_SCHEMA) == IXML_SCHEMA);
}

//-----------------------------------------------------------------------------
/*
 * /
template<typename XMLPARSERTYPE>
void IXmlProcessor<XMLPARSERTYPE>::SetSchemaChecking(bool bValidate  //[in] = true
                                     )
{
m_nValidation = bValidate ? (m_nValidation | IXML_VALIDATION_SCHEMA) :
                            (m_nValidation & ~IXML_VALIDATION_SCHEMA);
}

//-----------------------------------------------------------------------------
/*
 * /
template<typename XMLPARSERTYPE>
bool IXmlProcessor<XMLPARSERTYPE>::IsSchemaChecking()
{
return ((m_nValidation & IXML_VALIDATION_SCHEMA) == IXML_VALIDATION_SCHEMA);
}

//-----------------------------------------------------------------------------
/*
 * /
template<typename XMLPARSERTYPE>
void IXmlProcessor<XMLPARSERTYPE>::SetNamespace(bool bValidate //[in] = true
                                     )
{
m_nValidation = bValidate ? (m_nValidation | IXML_NAMESPACE) :
                            (m_nValidation & ~IXML_NAMESPACE);
}

//-----------------------------------------------------------------------------
/*
 * /
template<typename XMLPARSERTYPE>
bool IXmlProcessor<XMLPARSERTYPE>::IsNamespaces()
{
return ((m_nValidation & IXML_NAMESPACE) == IXML_NAMESPACE);
}

*/
///////////////////////////////////////////////////////////////////////////////
#endif  //_KXMLPARSERI_H_
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2005-03-22 01:15:23  Darko           renamed filed
 *  1    Biblioteka1.0         2005-03-21 02:13:46  Darko
 * $
 *****************************************************************************/
