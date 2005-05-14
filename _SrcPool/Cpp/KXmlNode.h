/*$Workfile: KXmlNode.h$: header file
  $Revision: 18$ $Date: 2005-05-01 00:28:16$
  $Author: Darko$

  XML Element
  Copyright: CommonSoft Inc
  2005-03-20 Darko Kolakovic
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KXMLNODE_H_
    //$Workfile: KXmlNode.h$ sentry
  #define _KXMLNODE_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _WIN32
  #include "Win/32/KXmlTypeWin.h" 
#endif
#include "KXmlBinding.h"  //XmlDataType enum

  //Forward references
class CXmlAttributeList;

///////////////////////////////////////////////////////////////////////////////
// XML Element
//
class CXmlNode
{
public:

  CXmlNode();
  CXmlNode(const CXmlNode& xmlElement);
  CXmlNode(const CXmlString& strElementName, 
           const CXmlString& strValue, 
           const XmlDataType eDataType = eXML_STRING,
           const int iIndex = -1);
  CXmlNode(const CXmlString& strElementName,
           const XmlDataType eDataType = eXML_STRING,
           const int iIndex = -1);
  virtual ~CXmlNode();

public:
  CXmlNode& operator=(const CXmlNode& xmlElement);
  const CXmlString& GetName() const;
  const CXmlString& GetValue() const;
  void SetName(const CXmlString& strElementName);
  void SetValue(const CXmlString& strValue, 
                const XmlDataType eDataType = eXML_STRING);
  CXmlNode& AppendChild(CXmlNode& xmlElement);
  bool HasChild(const CXmlString& strElementName);
  CXmlNode& GetChild(const CXmlString& strElementName, unsigned int nIndex = 0);
  void RemoveChild(const CXmlString& strElementName, unsigned int nIndex = 0);
  const CXmlNode& GetChildAt(const size_t nIndex) const;
  CXmlNode& GetChildAt(const size_t nIndex);
  size_t EnumerateChildren(const wchar_t* szElementName = NULL);
  size_t GetChildrenCount() const;
  CXmlAttribute& AppendAttribute(CXmlAttribute& xmlAttribute);
  bool HasAttribute(const CXmlString& strAttributeName);
  const CXmlAttribute GetAttribute(const CXmlString& strAttributeName) const;
  const CXmlAttribute GetAttribute(const wchar_t* szAttributeName) const;
  CXmlAttribute& GetAttribute(const wchar_t* szAttributeName, 
                              bool& bHasAttribute);
  const CXmlAttribute& GetAttributeAt(const size_t nIndex) const;
  size_t GetAttributeCount() const;
  bool operator==(const CXmlString& strElement) const;
  bool operator!=(const CXmlString& strElement) const;
  bool IsId(const int iIndex);
  const int GetId() const;
  int& GetId();
  void SetId(const int nId);
  const int  GetParentId() const;
  void SetParentId(const int nId);

private:

  int               m_iIndex;        //identification number (key)
  CXmlString        m_strElement;    //element's name (tag)
  CXmlString        m_strValue;      //element's value
  XmlDataType       m_eValue;        //element's datatype
  CXmlAttributeList m_xmlAttribute;  //list of element's attributes
  CXmlElementList   m_xmlSubelement; //list of element's children
};

///////////////////////////////////////////////////////////////////////////////
#endif  //_KXMLNODE_H_
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         2005-04-08 12:31:55  Darko Kolakovic FindChild()
 *  3    Biblioteka1.2         2005-04-07 12:37:42  Darko Kolakovic replaced string
 *       with CXmlString
 *  2    Biblioteka1.1         2005-04-06 14:46:34  Darko Kolakovic Fixed value
 *       error
 *  1    Biblioteka1.0         2005-04-05 14:05:05  Darko Kolakovic
 * $
 *****************************************************************************/
