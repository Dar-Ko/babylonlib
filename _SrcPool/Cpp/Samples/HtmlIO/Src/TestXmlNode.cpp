/*$Workfile: TestXmlNode.cpp$: implementation file
  $Revision: 11$ $Date: 2005-04-27 12:57:50$
  $Author: Darko Kolakovic$

  Test XML Node manipulation
  Copyright: CommonSoft Inc.
  2005-03-21 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"

#include "KXmlNode.h"  //CXmlNode class

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);

bool TestXmlNode();

//-----------------------------------------------------------------------------
/*Function validates XML Node manipulations.

  Returns: true if successful, otherwise returns false.
 */
bool TestXmlNode()
{
TsWriteToView(_T("TestXmlNode()\r\n"));
bool bRes = true;
TESTENTRY logEntry =
  {_T("CXmlNode()"), _T("KXmlNode.h"), bRes};

const wchar_t* wszElement =
    L"  <magazine style=\"glossy\" frequency=\"monthly\">"
    L"    <title>Road and Track</title>"
    L"    <price>3.50</price>"
    L"    <subscription price=\"24\" per=\"year\"/>"
    L"    <subscription price=\"11.50\" per=\"halfyear\"/>"
    L"    <special_edition per_year=\"1\">Yes</special_edition>"
    L"  </magazine>";

  //Test construction of the node
CXmlNode xmlRoot(CXmlString(L"magazine"));
CXmlNode xmlTitle(CXmlString(L"title"), CXmlString(L"Road and Track"));
CXmlString strTitle = xmlTitle.GetValue();
bRes = (strTitle == L"Road and Track");

logEntry.m_bResult = bRes;
LogTest(&logEntry);

  //Test adding the subelements
if (bRes)
  {
  logEntry.m_szFileName = _T("KXmlNode.cpp");

  xmlRoot.AppendChild(xmlTitle);
  CXmlNode xmlNew = xmlRoot.GetChild(CXmlString(L"title"));

  CXmlNode xmlPrice(CXmlString(L"price"), CXmlString(L"3.50"), eXML_DECIMAL);
  xmlRoot.AppendChild(xmlPrice);

  }

  //Test adding the parameters for an element
CXmlAttribute xmlattrStyle(CXmlString(L"style"));
xmlattrStyle.SetValue(L"glossy");
CXmlAttribute xmlattrFrequency(CXmlString(L"frequency"), CXmlString(L"monthly"));
xmlRoot.AppendAttribute(xmlattrStyle);
xmlRoot.AppendAttribute(xmlattrFrequency);

  //Test reteriving a parameter of an element
CXmlAttribute xmlattrTest;
CXmlString strTest;
if (xmlRoot.HasAttribute(L"frequency"))
  {
  xmlattrTest = xmlRoot.GetAttribute(L"frequency");
  }

  //Test changing the parameter value of an element
if (xmlRoot.HasAttribute(L"style"))
  {
  bool bHasAttribute;
  xmlRoot.GetAttribute(L"style", bHasAttribute).SetValue(L"electronic");
  ASSERT(bHasAttribute == true);
  strTest = xmlRoot.GetAttribute(L"style").GetValue();
  bRes = (strTest == L"electronic");
  }
  //Test appending subelements
if(bRes)
  {
  CXmlNode xmlSubscription[2];
  xmlSubscription[0].SetName(L"subscription");
  xmlSubscription[1] = xmlSubscription[0];

  CXmlAttribute xmlattrPrice(CXmlString(L"price"), CXmlString(L"24"), eXML_DECIMAL);
  xmlSubscription[0].AppendAttribute(xmlattrPrice);
  xmlattrPrice.SetValue(CXmlString(L"11.50"), eXML_DECIMAL);
  xmlSubscription[1].AppendAttribute(xmlattrPrice);

  xmlattrFrequency.SetName(CXmlString(L"per"));
  xmlattrFrequency.SetValue(CXmlString(L"year"));
  xmlSubscription[0].AppendAttribute(xmlattrFrequency);
  xmlattrFrequency.SetValue(CXmlString(L"halfyear"));
  xmlSubscription[1].AppendAttribute(xmlattrFrequency);

  xmlRoot.AppendChild(xmlSubscription[0]);
  xmlRoot.AppendChild(xmlSubscription[1]);

  size_t nCount = xmlSubscription[0].GetAttributeCount();
  bRes = (nCount == 2);
  if (bRes)
    {
    nCount = xmlSubscription[1].GetAttributeCount();
    bRes = (nCount == 2);
    }
  
  bRes = bRes && (xmlRoot.EnumerateChildren() == 4);
  }

if (bRes)
  {
  int iCount = (int)xmlRoot.EnumerateChildren(L"subscription");
  bRes = (iCount == 2);
  if (bRes)
    {
    logEntry.m_szObjectName = _T("CXmlNode::GetChild(CXmlString, uint)");

    CXmlNode xmlHalfYear = xmlRoot.GetChild(L"subscription", 1);
    bRes = (xmlHalfYear == L"subscription");

    logEntry.m_bResult = bRes;
    LogTest(&logEntry);
    logEntry.m_szObjectName = _T("CXmlNode::operator==(CXmlString)");
    LogTest(&logEntry);

    bRes = (xmlHalfYear.GetAttributeCount() == 2);

    logEntry.m_bResult = bRes;
    logEntry.m_szObjectName = _T("CXmlNode::GetAttributeCount()");
    LogTest(&logEntry);

    if (bRes && (bRes = xmlHalfYear.HasAttribute(L"price")) )
      {
      CXmlAttribute xmlPrice = xmlHalfYear.GetAttribute(L"price");
      bRes = (xmlPrice.GetValue() == L"11.50");
      }
    }

  }

if (bRes)
  {
  CXmlNode xmlSpecEdition(L"special_edition", L"Yes", eXML_STRING, 4);
  CXmlAttribute xmlattrSpecEditionFrequency(L"per_year", L"1", eXML_UINT, 0);
  xmlSpecEdition.AppendAttribute(xmlattrSpecEditionFrequency);
  xmlRoot.AppendChild(xmlSpecEdition);

  int iCount = (int)xmlRoot.GetAttributeCount();
  bRes = (iCount == 2);
  }

logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2005-03-26 00:15:34  Darko           CXmlString test
 *  1    Biblioteka1.0         2005-03-21 02:23:32  Darko
 * $
 *****************************************************************************/
