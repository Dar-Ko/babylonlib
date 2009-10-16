/*$Workfile: KXmlNode.cpp$: implementation file
  $Revision: 17$ $Date: 2005-05-13 23:21:25$
  $Author: Darko$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2005-03-20 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _MSC_VER //Microsoft Visual Studio C++ compiler
  #include "stdafx.h"
#endif

#include "KXmlNode.h"  //CXmlNode class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CXmlNode class

//-----------------------------------------------------------------------------
/*Default constructor
 */
CXmlNode::CXmlNode()
{
m_eValue = eXML_UNDEFINED;
m_iIndex = -1;
m_xmlSubelement.m_xmlParentId = -1;
}

CXmlNode::CXmlNode(const CXmlString& strElementName, //[in] XML tag
                   const CXmlString& strValue, //[in] element's value
                   const XmlDataType eDataType,//[in]= eXML_STRING
                                               //element's datatype
                   const int iIndex  //[in]=-1 element's
                                     //identification number
                   )
{
m_strElement = strElementName;
m_strValue   = strValue;
m_eValue     = eDataType;
m_iIndex     = iIndex;
m_xmlSubelement.m_xmlParentId = -1;
}

CXmlNode::CXmlNode(const CXmlString& strElementName, //[in] XML tag
                  const XmlDataType eDataType,//[in]= eXML_STRING
                                              //element's datatype
                  const int iIndex //[in]= -1 element's
                                   //identification number
                  )
{
m_strElement = strElementName;
m_eValue     = eDataType;
m_iIndex     = iIndex;
m_xmlSubelement.m_xmlParentId = -1;
}

CXmlNode::CXmlNode(const CXmlNode& xmlElement //[in] XML element to copy
                  )
{
if(&xmlElement != this)
  this->operator=(xmlElement);
}

//-----------------------------------------------------------------------------
/*Default destructor
 */
CXmlNode::~CXmlNode()
{
}

//-----------------------------------------------------------------------------
/*
 */
CXmlNode& CXmlNode::operator=(const CXmlNode& xmlElement //[in] XML element to
                                                         //assign
                             )
{
if(&xmlElement != this)
  {
  m_iIndex        = xmlElement.m_iIndex;
  m_strElement    = xmlElement.m_strElement;
  m_strValue      = xmlElement.m_strValue;
  m_eValue        = xmlElement.m_eValue;
  m_xmlAttribute  = xmlElement.m_xmlAttribute;
  m_xmlSubelement = xmlElement.m_xmlSubelement;
  }
return *this;
}

//-----------------------------------------------------------------------------
/*Obtains the name of the XML element.

  Returns: wide-characters string containing element's name.
 */
const CXmlString& CXmlNode::GetName() const
{
return m_strElement;
}

//-----------------------------------------------------------------------------
/*Set new name for the XML element representing this node.
 */
void CXmlNode::SetName(const CXmlString& strElementName //[in] XML tag
                      )
{
m_strElement = strElementName;
}

//-----------------------------------------------------------------------------
/*Obtains value of the XML element.

  Returns: wide-characters string containing element's value.
 */
const CXmlString& CXmlNode::GetValue() const
{
return m_strValue;
}

//-----------------------------------------------------------------------------
/*Set the value of the XML element representing this node.
 */
void CXmlNode::SetValue(const CXmlString& strValue, //[in] new value for
                                              //the XML element or empty string
                        const XmlDataType eDataType //[in]= eXML_STRING element's
                                              //datatype
                       )
{
m_strValue = strValue;
m_eValue   = eDataType;
}

//-----------------------------------------------------------------------------
/*Appends new child element to the list of subelement.

  Returns: newly appended child element.
 */
CXmlNode& CXmlNode::AppendChild(CXmlNode& xmlElement //[in] new subelement
                          )
{
return m_xmlSubelement.Append(xmlElement);
}

//-----------------------------------------------------------------------------
/*
 */
bool CXmlNode::HasChild(const CXmlString& strElementName //[in] XML tag
                       )
{
if (m_xmlSubelement.GetCount() > 0)
  {
  return m_xmlSubelement.Find(strElementName);
  }
return false;
}

//-----------------------------------------------------------------------------
/*Retrieves the child element with the given name. An element could have none
  or more than one children elements with the same name (tag).

  Returns: requested subelement or an empty element if subelement is not found.
 */
CXmlNode& CXmlNode::GetChild(const CXmlString& strElementName, //[in] XML tag
                            unsigned int nIndex //[in] = 0 index of subelement
                            //with the same XML tag
                           )
{
return m_xmlSubelement.GetItem(strElementName, nIndex);
}

//-----------------------------------------------------------------------------
/*Retrieves the child element at given position.

  Note: range of the nIndex is [0, INT_MAX]

  Returns: requested subelement.
 */
const CXmlNode& CXmlNode::GetChildAt(const size_t nIndex//[in] index of
                               //the subelement [0, INT_MAX]
                              ) const
{
ASSERT(m_xmlSubelement.GetCount() > (int)nIndex);
return m_xmlSubelement.GetAt(nIndex);
}

CXmlNode& CXmlNode::GetChildAt(const size_t nIndex//[in] index of the subelement
                               //[0, INT_MAX]
                              )
{
ASSERT(nIndex < (size_t)m_xmlSubelement.GetCount());
return m_xmlSubelement.GetAt(nIndex);
}

//-----------------------------------------------------------------------------
/*Obtains number of subelements.

  Returns: number of elements with the given name or number of all children
  elements
 */
size_t CXmlNode::EnumerateChildren(const wchar_t* szElementName //[in]= NULL
                                   //XML tag or NULL to get count of all
                                   //children elements
                                   )
{
return m_xmlSubelement.Enumerate(szElementName);
}

//-----------------------------------------------------------------------------
/*Get number of subelements.

  Returns: number of all children elements.
 */
size_t CXmlNode::GetChildrenCount() const
{
return m_xmlSubelement.GetCount();
}

//-----------------------------------------------------------------------------
/*Removes element form the list of subelements.
 */
void CXmlNode::RemoveChild(const CXmlString& strElementName,
                           unsigned int nIndex //[in]= 0
                           )
{
m_xmlSubelement.RemoveItem(strElementName, nIndex);
}

//-----------------------------------------------------------------------------
/*Appends new attribute object to the list of attributes.

  Returns: newly appended attribute object.
 */
CXmlAttribute& CXmlNode::AppendAttribute(CXmlAttribute& xmlAttribute //[in]
                                         //attribute object to add to the list
                              )
{
return m_xmlAttribute.Append(xmlAttribute);
}

//-----------------------------------------------------------------------------
/*Verifies if the XML element (node) has certain attribute.

  Returns: true if required attribute exist; otherwise returns false.
 */
bool CXmlNode::HasAttribute(const CXmlString& strAttributeName //[in] XML tag
                           )
{
if (m_xmlAttribute.GetCount() > 0)
  {
  return m_xmlAttribute.Find(strAttributeName);
  }
return false;
}

//-----------------------------------------------------------------------------
/*Get the number of attributes for the XML element (node).

  Returns : number of attributes of the XML element
 */
size_t CXmlNode::GetAttributeCount() const
{
return (size_t)m_xmlAttribute.GetCount();
}

//-----------------------------------------------------------------------------
/*Retrieves element's attribute with the given XML tag.

  Returns: requested attribute object or a default, empty object if attribute
  with required tag is not found.
 */
const CXmlAttribute CXmlNode::GetAttribute(const CXmlString& strAttributeName //[in]
                                                                     //XML tag
                                    ) const
{
bool bHasAttribute;
CXmlAttribute& xmlResult = const_cast<CXmlAttributeList*>(&m_xmlAttribute)->
                              GetItem(strAttributeName, bHasAttribute);
if (bHasAttribute)
  return CXmlAttribute(xmlResult);
else
  return CXmlAttribute();
}

//-----------------------------------------------------------------------------
/*Retreives element's attribute with the given XML tag.

  Returns: requested attribute object or a default, empty object if attribute
  with required tag is not found.
 * /
CXmlAttribute& CXmlNode::GetAttribute(const CXmlString& strAttributeName //[in]
                                                                     //XML tag
                                    )
{
CXmlAttribute* pxmlResult = NULL;
m_xmlAttribute.GetItem(strAttributeName, *pxmlResult);
return *pxmlResult;
}
*/
//-----------------------------------------------------------------------------
/*Retrieves element's attribute with the given XML tag.

  Returns: requested attribute object or a default, empty object if attribute
  with required tag is not found.
 */
const CXmlAttribute CXmlNode::GetAttribute(const wchar_t* szAttributeName //[in]
                                                                    //XML tag
                                    ) const
{
bool bHasAttribute;
CXmlAttribute& xmlResult = const_cast<CXmlAttributeList*>(&m_xmlAttribute)->
                              GetItem(szAttributeName, bHasAttribute);
if (bHasAttribute)
  return CXmlAttribute(xmlResult);
else
  return CXmlAttribute();
}

//-----------------------------------------------------------------------------
/*Retrieves element's attribute with the given XML tag.

  Returns: requested attribute object or a default, empty object if attribute
  with required tag is not found.
 */
CXmlAttribute& CXmlNode::GetAttribute(const wchar_t* szAttributeName,//[in]
                                                                    //XML tag
                                      bool& bHasAttribute //[out] true if
                             //attribute with given name exist or false if not.
                                      )
{
return m_xmlAttribute.GetItem(szAttributeName, bHasAttribute);
}

//-----------------------------------------------------------------------------
/*Retrieves the attribute at given position.

  Note: range of the nIndex is [0, INT_MAX]

  Returns: requested subelement.
 */
const CXmlAttribute& CXmlNode::GetAttributeAt(const size_t nIndex//[in] index
                               //of the subelement [0, INT_MAX]
                              ) const
{
ASSERT(nIndex < (size_t)m_xmlAttribute.GetCount());
return m_xmlAttribute.GetAt(nIndex);
}

//-----------------------------------------------------------------------------
/*
 */
bool CXmlNode::operator==(const CXmlString& strElementName //[in] XML tag
                         ) const
{
return (m_strElement == strElementName);
}

//-----------------------------------------------------------------------------
/*
 */
bool CXmlNode::operator!=(const CXmlString& strElementName //[in] XML tag
                         ) const
{
return (strElementName != m_strElement);
}

//-----------------------------------------------------------------------------
/*Validates element's identification number.

  Returns: true if identification is matched; otherwise returns false.
 */
bool CXmlNode::IsId(const int iIndex //element's identification number
                   )
{
return (m_iIndex == iIndex);
}

//-----------------------------------------------------------------------------
/*Obtains element's identification number.

  Returns: element's identification number.
 */
const int CXmlNode::GetId() const
{
return m_iIndex;
}

int& CXmlNode::GetId()
{
return m_iIndex;
}

//-----------------------------------------------------------------------------
/*Set element's identification number. The identification number is
  implementation dependant.
 */
void CXmlNode::SetId(const int iId //[in] element's identification
                    )
{
m_iIndex = iId;
}

//-----------------------------------------------------------------------------
/*Obtains parent element's identification number.

  Returns: parent element's identification number.
 */
const int CXmlNode::GetParentId() const
{
return m_xmlSubelement.m_xmlParentId;
}

//-----------------------------------------------------------------------------
/*Set parent element's identification number. The identification number is
  implementation dependant.
 */
void CXmlNode::SetParentId(const int iId //[in] parent's identification
                           )
{
m_xmlSubelement.m_xmlParentId = iId;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2005-04-13 15:05:42  Darko Kolakovic added datatype
 *  1    Biblioteka1.0         2005-04-12 17:46:21  Darko Kolakovic
 * $
 *****************************************************************************/
