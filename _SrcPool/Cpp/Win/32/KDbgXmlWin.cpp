/*$Workfile: KDbgXmlWin.cpp$: implementation file
  $Revision: 2$ $Date: 2005-05-01 00:35:41$
  $Author: Darko$

  Dumps XML objects
  Copyright: CommonSoft Inc.
  2005-04-28 Darko Kolakovic
 */

// Group=Diagnostic

#include <stdafx.h>

#ifdef _DEBUG

#include "Win/32/KXmlTypeWin.h"
#include "KXmlNode.h"   //CXmlNode class
#include "KDbgXmlWin.h" //Declarations

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

static int s_iIndent = 0;
class CIndent //!todo;
{
public:
    CIndent();
    ~CIndent();
    static int m_iIndent;
    CString m_strIndent;
};

int CIndent::m_iIndent = 0;
CIndent::CIndent()
{
LPCTSTR szIndent= _T("  ");
m_strIndent.Empty();
int i = 0;
while (i < m_iIndent)
  {
  m_strIndent += szIndent;
  i++;
  }
m_iIndent++;
}

CIndent::~CIndent()
{
if (m_iIndent >= 0)
  {
  m_iIndent--;
//  LPCTSTR szIndent= _T("  ");
//  m_strIndent.Empty();
//  int i = 0;
//  while (i < m_iIndent)
//    {
//    strIndent += szIndent;
//    i++;
//    }

  }
}

//-----------------------------------------------------------------------------
/*Dump content of XML element object.

  Note: uses Microsoft Foundation Library (MFC),
        Microsoft Windows specific (Win).
 */
void DumpXmlNode(CDumpContext& dc, //[in] diagnostic output stream
                 const CXmlNode& xmlNode  //[in] XML element object
                )
{
LPCTSTR szEol = _T("\n");
LPCTSTR szEmpty = _T("<empty>");
CIndent indent;

CString strNodeValue = xmlNode.GetValue();
if(strNodeValue.IsEmpty())
    strNodeValue = szEmpty;
int iCount = (int)xmlNode.GetAttributeCount();

dc << indent.m_strIndent << _T("CXmlNode(" << xmlNode.GetName()
   << _T(", ID = ") << xmlNode.GetId() 
   << _T(", Parent ID = ") << xmlNode.GetParentId()
   << ") @ ") << &xmlNode << szEol;


dc << indent.m_strIndent << _T("{") << szEol;
dc << indent.m_strIndent << _T("value = ") << strNodeValue << szEol;

dc << indent.m_strIndent << _T("attributes = ");
if(iCount == 0)
  dc << _T("none") << szEol;
else
  {
  dc << iCount << szEol;
  //Dump the list
  int i = 0;
  while ( i < iCount)
    {
    DumpXmlAttr(dc, xmlNode.GetAttributeAt(i));
    i++;
    }
  }

iCount = (int)xmlNode.GetChildrenCount();
dc << indent.m_strIndent << _T("subelements = ");
if(iCount == 0)
  dc << _T("none") << szEol;
else
  {
  dc << iCount << szEol;
  //Dump the list
  int i = 0;
  while ( i < iCount)
    {
    DumpXmlNode(dc, xmlNode.GetChildAt(i));
    i++;
    }
  }

dc << indent.m_strIndent << _T("}") << szEol;

}

//-----------------------------------------------------------------------------
/*Dump content of XML attribute object.

  Note: uses Microsoft Foundation Library (MFC),
        Microsoft Windows specific (Win).
 */
void DumpXmlAttr(CDumpContext& dc, //[in] diagnostic output stream
                 const CXmlAttribute& xmlAttr  //[in] XML attribute object
                )
{
LPCTSTR szIndent= _T("  ");
LPCTSTR sz2Indent= _T("    ");
LPCTSTR szEol = _T("\n");
LPCTSTR szEmpty = _T("<empty>");
CIndent indent;

CString strAttrValue = xmlAttr.GetValue();
if(strAttrValue.IsEmpty())
    strAttrValue = szEmpty;

dc << indent.m_strIndent << _T("CXmlAttribute(") << xmlAttr.GetName()
   << _T(", ID = ") << xmlAttr.GetId()
   << _T(") @ ") << &xmlAttr << szEol;
  {
    CIndent indent2;
    dc << indent2.m_strIndent << _T("{")
       << _T("value = ") << strAttrValue
       << _T("}") << szEol;
  }
}

///////////////////////////////////////////////////////////////////////////////
#endif //_DEBUG
/******************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2005-05-01 00:35:41  Darko           GetParentId
 *  1    Biblioteka1.0         2005-04-28 18:10:38  Darko Kolakovic 
 * $
 *****************************************************************************/

