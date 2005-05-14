/*$Workfile: S:\_SrcPool\Cpp\KXmlAttribute.cpp$: implementation file
  $Revision: 7$ $Date: 2005-04-27 12:56:03$
  $Author: Darko Kolakovic$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2005-03-20 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _WIN32
  #include "stdafx.h"
  #include "Win/32/KXmlTypeWin.h"   //CXmlString typedef
#endif
#include "KXmlAttribute.h"  //CXmlAttribute class

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
CXmlAttribute::CXmlAttribute()
{
m_eValue = eXML_UNDEFINED;
m_iIndex = -1;
}

CXmlAttribute::CXmlAttribute(const CXmlString& strAttributeName, //[in] XML tag
                             const CXmlString& strValue, //[in] attribute's value
                             const XmlDataType eDataType,//[in]= eXML_STRING
                                                         //attribute's datatype
                             const int iIndex //[in]=-1 attribute's
                                              //identification number
                            )
{
m_strName  = strAttributeName;
m_strValue = strValue;
m_eValue   = eDataType;
m_iIndex   = iIndex;
}

CXmlAttribute::CXmlAttribute(const CXmlString& strAttributeName, //[in] XML tag
                             const XmlDataType eDataType,//[in]= eXML_STRING
                                                         //attribute's datatype
                             const int iIndex //[in]=-1 attribute's
                                              //identification number
                            )
{
m_strName = strAttributeName;
m_eValue  = eDataType;
m_iIndex  = iIndex;
}

CXmlAttribute::CXmlAttribute(const CXmlAttribute& xmlAttribute //[in] XML attribute
                                                               //to copy
                            )
{
if(&xmlAttribute == this)
  return;

this->operator=(xmlAttribute);
}

//-----------------------------------------------------------------------------
/*Default destructor
 */
CXmlAttribute::~CXmlAttribute()
{
}

//-----------------------------------------------------------------------------
/*
 */
CXmlAttribute& CXmlAttribute::operator=(const CXmlAttribute& xmlAttribute //[in]
                                        //XML attribute to assign
                             )
{
if(&xmlAttribute == this)
  return *this;

m_strName   = xmlAttribute.m_strName;
m_strValue  = xmlAttribute.m_strValue;
m_eValue    = xmlAttribute.m_eValue;
m_iIndex    = xmlAttribute.m_iIndex;
return *this;
}

//-----------------------------------------------------------------------------
/*Obtains the name of the XML attribute.

  Returns: wide-characters string containing attribute's name.
 */
const CXmlString& CXmlAttribute::GetName() const
{
return m_strName;
}

//-----------------------------------------------------------------------------
/*Obtains the name of the XML attribute.

  Returns: wide-characters string containing attribute's name.
 */
CXmlAttribute::operator const CXmlString&() const
{
return m_strName;
}

//-----------------------------------------------------------------------------
/*Set new name for the XML attribute.
 */
void CXmlAttribute::SetName(const CXmlString& strAttributeName //[in] XML tag
                           )
{
m_strName = strAttributeName;
}

//-----------------------------------------------------------------------------
/*Obtains value of the XML attribute.

  Returns: wide-characters string containing attribute's value.
 */
const CXmlString& CXmlAttribute::GetValue() const
{
return m_strValue;
}

//-----------------------------------------------------------------------------
/*Set the value of the XML attribute.
 */
void CXmlAttribute::SetValue(const CXmlString& strValue, //[in] new value for
                                            //the XML attribute or empty string
                             const XmlDataType eDataType//[in]= eXML_STRING
                                                        //attribute's datatype
                            )
{
m_strValue = strValue;
m_eValue   = eDataType;
}

//-----------------------------------------------------------------------------
/*Set datatype of the XML element's attribute. The type is used for validation
  and data conversion.
 */
void CXmlAttribute::SetType(const XmlDataType eDataType//[in]
                                                       //attribute's datatype
                            )
{
m_eValue = eDataType;
}

//-----------------------------------------------------------------------------
/*
 */
bool CXmlAttribute::operator==(const CXmlString& strAttributeName //[in] XML tag
                         ) const
{
return (strAttributeName == m_strName);
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2005-04-17 01:45:13  Darko           map key
 *  2    Biblioteka1.1         2005-04-13 15:05:38  Darko Kolakovic added datatype
 *  1    Biblioteka1.0         2005-04-12 17:46:16  Darko Kolakovic
 * $
 *****************************************************************************/
