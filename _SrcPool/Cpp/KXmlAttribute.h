/*$Workfile: KXmlAttribute.h$: header file
  $Revision: 8$ $Date: 2005-04-28 17:06:36$
  $Author: Darko Kolakovic$

  XML element's attribute
  Copyright: CommonSoft Inc
  2005-03-20 Darko Kolakovic
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KXMLATTRIBUTE_H_
    //$Workfile: KXmlAttribute.h$ sentry
  #define _KXMLATTRIBUTE_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include "KXmlBinding.h"  //XmlDataType enum

///////////////////////////////////////////////////////////////////////////////
/*XML element's attribute.
  The XML attribute provides additional information about an XML element.
  Altough it is not specified what type of data should be used as attributes 
  or elements, it is recommeded to stror metadata (data about data) as 
  attributes and data itself to store as elements.

    <elementA attributeA="valueA" attributeB="valueB">
      <childA>value1</childA>
      <childB>value2</childB>
    </elementA>

  Default identification number is -1. Set this number to unique value on
  node's level in order to simplify and speed-up attribute classification.

  See also: CXmlNode, CXmlDocument
  {html <a href="http://msdn.microsoft.com/en-us/library/ms256153%28VS.100%29.aspx">
  MSDN: XML Standards Reference: Document Map;</a>
  <a href="http://www.w3.org/TR/REC-xml/">
  W3C: Extensible Markup Language (XML) 1.0 (Fifth Edition)</a>}
 */
class CXmlAttribute
{
public:

  CXmlAttribute();
  CXmlAttribute(const CXmlAttribute& xmlAttribute);
  CXmlAttribute(const CXmlString& strAttributeName,
                const XmlDataType eDataType = eXML_STRING,
                const int iIndex = -1);
  CXmlAttribute(const CXmlString& strAttributeName,
                const CXmlString& strValue,
                const XmlDataType eDataType = eXML_STRING,
                const int iIndex = -1);
  virtual ~CXmlAttribute();

public:
  CXmlAttribute& operator=(const CXmlAttribute& xmlAttribute);
  const CXmlString& GetName() const;
  void SetName(const CXmlString& strAttributeName);
  const CXmlString& GetValue() const;
  void SetValue(const CXmlString& strValue,
                const XmlDataType eDataType = eXML_STRING);
  void SetType(const XmlDataType eDataType);
  void SetId (const int iIndex);
  bool operator==(const CXmlString& strElement) const;
  bool operator!=(const CXmlString& strElement) const;
  operator const CXmlString&() const;
  const int GetId() const;
  bool IsId(const int iIndex) const;

private:
  int         m_iIndex;   //identification number (key)
  CXmlString  m_strName;  //attribute's name
  CXmlString  m_strValue; //attribute's value
  XmlDataType m_eValue;   //attribute's datatype
};


///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Validates attribute's indentification number.

  Returns: true if indentification is matched; otherwise returns false.
 */
inline
bool CXmlAttribute::IsId(const int iIndex //attribute's indentification number
                       ) const
{
return (m_iIndex == iIndex);
}

//-----------------------------------------------------------------------------
/*Changes attribute's indentification number.
 */
inline
void CXmlAttribute::SetId(const int iIndex //attribute's indentification number
                         )
{
m_iIndex = iIndex;
}

//-----------------------------------------------------------------------------
/*Obtains attribute's identification number.

  Returns: attribute's identification number.
 */
inline
const int CXmlAttribute::GetId() const
{
return m_iIndex;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KXMLATTRIBUTE_H_
/*****************************************************************************
 * $Log:
 *  5    Biblioteka1.4         2005-04-19 00:15:34  Darko           SetId ()
 *  4    Biblioteka1.3         2005-04-18 01:18:58  Darko           get attribute
 *       by reference
 *  3    Biblioteka1.2         2005-04-17 01:45:16  Darko           map key
 *  2    Biblioteka1.1         2005-04-13 15:05:40  Darko Kolakovic added datatype
 *  1    Biblioteka1.0         2005-04-12 17:46:19  Darko Kolakovic
 * $
 *****************************************************************************/
