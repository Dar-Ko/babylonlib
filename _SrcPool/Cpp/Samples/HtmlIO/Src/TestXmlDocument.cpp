/*$RCSfile: TestXmlDocument.cpp,v $: implementation file
  $Revision: 1.4 $ $Date: 2009/10/19 20:44:35 $
  $Author: ddarko $

  Test simple XML reader
  2009-09-01 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "KXmlDocument.h" //CXmlDocument class


#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);

extern "C" TCHAR g_szTestXml[];

//-----------------------------------------------------------------------------
/*Function validates XML parser framework.

  Returns: true if successful, otherwise returns false.
 */
bool TestXmlDocument(int argc, //[in] specifies how many arguments are passed
                          // to the program from the command line. The value of
                          // argc is at least one: the program name.
                       TCHAR* argv[] //[in] the program arguments as an array of
                          //pointers to null-terminated strings. The first string
                          //(argv[0]) is the program name. The end of the array
                          //(argv[argc]) is indicated by a NULL pointer.
                       )
{
TsWriteToView(_T("TestXmlDocument()\r\n"));
TESTENTRY logEntry =
{_T("CXmlDocument::Create()"), _T("KXmlDocument.cpp"), true};
bool& bRes = logEntry.m_bResult;

if (argc > 0)
  {
  TsWriteToView(_T("Application "));
  TsWriteToView(argv[0]);
  TsWriteToView(_T(" has "));
  TsWriteToView(argc);
  TsWriteToViewLn(_T(" argument(s)"));
  }

try
  {
  //Create XML reader
  CXmlDocument xmlDocument;
  bRes = xmlDocument.Create(g_szTestXml);
  LogTest(&logEntry);
  if (bRes)
    {
    //Find first element
    logEntry.m_szObjectName = _T("CXmlDocument::GetNextElement(0)");
    int iNodePos = xmlDocument.GetNextElement();
    bRes = (iNodePos > 0);
    if (bRes)
      {
      //Ignore some erroneous tags
      const int POS_MALFORMEDTAG = 770; //position before '</>' XML tag
      iNodePos = xmlDocument.GetNextElement(POS_MALFORMEDTAG -1);
      bRes = (iNodePos > POS_MALFORMEDTAG);
      }
    LogTest(&logEntry);

    //Count elements
    logEntry.m_szObjectName = _T("CXmlDocument::Enumerate()");
    bRes = (xmlDocument.Enumerate(_T("parentNode")) == 2);
    LogTest(&logEntry);
    if (bRes)
      {
      //List all elements
      logEntry.m_szObjectName = _T("CXmlDocument::GetNextElement()");
      iNodePos = xmlDocument.GetNextElement(); //Get 1st iNodePos
      while(iNodePos > 0)
        {
        LPCTSTR szElementName = xmlDocument.GetName(iNodePos);
        TsWriteToViewLn(szElementName);
        #ifdef _UNICODE
          #define DBGTRACEFORMAT1 _T("%ws at position %d\n")
        #else
          #define DBGTRACEFORMAT1 _T("%s at position %d\n")
        #endif
        TRACE2(DBGTRACEFORMAT1, szElementName, iNodePos);

        iNodePos = xmlDocument.GetNextElement(iNodePos);
        }
      LogTest(&logEntry);
      logEntry.m_szObjectName = _T("CXmlDocument::GetName()");
      LogTest(&logEntry);

      //Parse XML elements
      logEntry.m_szObjectName = _T("CXmlDocument::GetChild()");
      int iChildPos = 0;
      iNodePos = xmlDocument.GetNextElement(); //Get 1st iNodePos
      while(iNodePos > 0)
        {
        if (_tcscmp(xmlDocument.GetName(iNodePos),_T("parentNode")) != 0)
          {
          iNodePos = xmlDocument.GetNextElement(iNodePos);
          continue;
          }
        LPCTSTR szElementValue = NULL;
        if (bRes && ((iChildPos = xmlDocument.GetChild(_T("intNode"), iNodePos)) > 0))
          szElementValue = xmlDocument.GetValue(iChildPos);

        if (bRes && ((iChildPos = xmlDocument.GetChild(_T("boolNode"), iNodePos)) > 0))
          szElementValue = xmlDocument.GetValue(iChildPos);

        if (bRes && ((iChildPos = xmlDocument.GetChild(_T("floatNode"), iNodePos)) > 0))
          szElementValue = xmlDocument.GetValue(iChildPos);

        if (bRes && ((iChildPos = xmlDocument.GetChild(_T("emptyNode"), iNodePos)) > 0))
          {
          szElementValue = xmlDocument.GetValue(iChildPos);
          bRes = szElementValue[0] == _T('\0'); //Empty string
          }

        if (bRes && ((iChildPos = xmlDocument.GetChild(_T("unknowNode"), iNodePos)) > 0))
          {
          szElementValue = xmlDocument.GetValue(iChildPos);
          bRes = false;
          }

        if (!bRes)
          break; //Failure

        iNodePos = xmlDocument.GetNextElement(iNodePos);
        }
      LogTest(&logEntry);
      }

    if (bRes)
      {
      //Test shorcut for obtaining elements
      logEntry.m_szObjectName = _T("CXmlDocument::GetElement()");
      logEntry.m_szFileName   = _T("KXmlDocument.h");
      iNodePos = xmlDocument.GetElement(_T("parentNode")); //Get 1st node
      int i2ndPos = xmlDocument.GetElement(_T("parentNode"), iNodePos); //Get 2nd node
      bRes = (i2ndPos > iNodePos) && (iNodePos > 0);
      if (bRes)
        {
        while(i2ndPos > 0)
          {
          LPCTSTR szElementValue = NULL;
          int iChildPos = 0;
          if (bRes && ((iChildPos = xmlDocument.GetChild(_T("intNode"), i2ndPos)) > 0))
            {
            szElementValue = xmlDocument.GetValue(iChildPos);
            //Trailing whitespace is not truncated
            bRes = _tcscmp(szElementValue,_T("65 66 ")) == 0;
            TsWriteToView(_T("intNode = "));
            TsWriteToViewLn(szElementValue);
            }

          if (bRes && ((iChildPos = xmlDocument.GetChild(_T("boolNode"), i2ndPos)) > 0))
            {
            szElementValue = xmlDocument.GetValue(iChildPos);
            bRes = _tcscmp(szElementValue,_T("any value")) == 0;
            TsWriteToView(_T("boolNode = "));
            TsWriteToViewLn(szElementValue);
            }

          if (bRes && ((iChildPos = xmlDocument.GetChild(_T("floatNode"), i2ndPos)) > 0))
            {
            szElementValue = xmlDocument.GetValue(iChildPos);
            bRes = _tcscmp(szElementValue,_T("-45E5")) == 0;
            TsWriteToView(_T("floatNode = "));
            TsWriteToViewLn(szElementValue);
            }

          if (bRes && ((iChildPos = xmlDocument.GetChild(_T("strNode"), i2ndPos)) > 0))
            {
            szElementValue = xmlDocument.GetValue(iChildPos);
            bRes = szElementValue[0] == _T('\0'); //Empty string
            TsWriteToView(_T("strNode = "));
            TsWriteToViewLn(szElementValue);
            }

          if (bRes && ((iChildPos = xmlDocument.GetChild(_T("emptyNode"), i2ndPos)) > 0))
            {
            szElementValue = xmlDocument.GetValue(iChildPos);
            bRes = szElementValue[0] == _T('\0'); //Empty string
            TsWriteToView(_T("emptyNode = "));
            TsWriteToViewLn(szElementValue);
            }

          if (bRes && ((iChildPos = xmlDocument.GetChild(_T("offspringNode"), i2ndPos)) > 0))
            {
            //Element with child nodes, but without a value
            szElementValue = xmlDocument.GetValue(iChildPos);
            bRes = szElementValue[0] == _T('\0'); //Empty string
            TsWriteToView(_T("offspringNode = "));
            TsWriteToViewLn(szElementValue);
            }

          if (!bRes)
            break; //Failure

          i2ndPos = xmlDocument.GetElement(_T("parentNode"), i2ndPos); //Get next element
          }
        }

      if (bRes)
        {
        iNodePos = xmlDocument.GetElement(_T("parentNodeABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmn_2ndLONGNAME"));
        bRes = (iNodePos == 0); //Too long name
        }
      LogTest(&logEntry);
      }

    }
  xmlDocument.Close();

   if (bRes)
    {
    //Test reading from a file
    logEntry.m_szObjectName = _T("CXmlDocument::Read()");
    xmlDocument.Read(argv[1]);

    LogTest(&logEntry);
    }

  }
catch(...)
  {
  bRes = false;
  LogTest(&logEntry);
  }

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: TestXmlDocument.cpp,v $
 * Revision 1.4  2009/10/19 20:44:35  ddarko
 * Fixed obtaining long element names
 *
 * Revision 1.3  2009/10/16 21:41:32  ddarko
 * Get element without  value
 *
 * Revision 1.2  2009/10/07 21:42:17  ddarko
 * Test tag names
 *
 * Revision 1.1  2009/10/02 16:29:53  ddarko
 * Created
 *
 *****************************************************************************/
