/*$RCSfile: KXmlDocument.h,v $: header file
  $Revision: 1.8 $ $Date: 2009/10/16 21:41:32 $
  $Author: ddarko $

  Interface for the CXmlDocument class
  Copyright: http://xbmc.org/
  2009-09-01 Darko Kolakovic
  2003-10-14 xbmc.org
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#if !defined(_KXMLDOCUMENT_H_)
  //$RCSfile: KXmlDocument.h,v $ sentry
	#define _KXMLDOCUMENT_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#define XML_POSBEGININING          0  //position at the beginning of XML document
#define XML_MAX_TAGNAME_SIZE      32
#define XML_MAX_INNERTEXT_SIZE  1024

typedef void (*XmlNodeCallback) (LPCTSTR szElementName, int iPos);

///////////////////////////////////////////////////////////////////////////////
/*Simplistic XML parser, suitable for reading small XML documents.
  The class does not require well-formed documents. The number of root elements
  is not validated.
  The class operates with fixed length strings. XML element names are limited to
  XML_MAX_TAGNAME_SIZE -1 and XML values to XML_MAX_INNERTEXT_SIZE -1 characters.
  Reading the XML attributes is not supported. Length of the document is limited
  to INT_MAX characters.

  Example:
      <?xml version="1.0"?>
      <?xml-stylesheet type="text/xsl" href="myfile.xsl"?>
      <!-- example XML document -->
      <parentNode>
        <intNode>10</intNode>
        <strNode>string</strNode>
        <boolNode>true</boolNode>
        <floatNode>0.3</floatNode>
      </parentNode>
      ...
      int iValue = 0;
      bool bValue = false;
      float fFloatValue = 0.0;
      CXmlDocument xmlDoc;
      if (xmlDoc.Read(_T("myfile.xml")) >= 0) //Read the document file
        {
        int iChildPos = 0;
        int iNodePos = xmlDoc.GetNextElement(XML_POSBEGININING); //Get 1st iNodePos
        while(iNodePos > 0)
          {
          if (strcmp(xmlDoc.GetName(iNodePos),"parentNode") != 0)
            {
            iNodePos = xmlDoc.GetNextElement(iNodePos);
            continue;
            }

          if ((iChildPos = xmlDoc.GetChild("intNode", iNodePos)) > 0)
            iValue = atoi(xmlDoc.GetValue(iChildPos));

          if ((iChildPos = xmlDoc.GetChild("boolNode", iNodePos)) > 0)
            bBoolValue = (_stricmp(xmlDoc.GetValue(iChildPos),"true") == 0);

          if ((iChildPos = xmlDoc.GetChild("floatNode", iNodePos)) > 0)
            fFloatValue = (float)atof(xmlDoc.GetValue(iChildPos));

          iNodePos = xmlDoc.GetNextElement(iNodePos);
          }
        xmlDoc.Close();
        }

  See also: CXmlNode, CXmlAttribute;
  {html <a href="http://msdn.microsoft.com/en-us/library/ms256153%28VS.100%29.aspx">
  MSDN: XML Standards Reference: Document Map;</a>
  <a href="http://www.w3.org/TR/REC-xml/">
  W3C: Extensible Markup Language (XML) 1.0 (Fifth Edition)</a>}
 */
class CXmlDocument
{
public:
  CXmlDocument();
  virtual ~CXmlDocument();

  bool    Create(LPCTSTR szXmlText);
  int     Read(LPCTSTR szFilename);
  void    Close();
  int     Enumerate(LPCTSTR szElementName);
  void    Enumerate(LPCTSTR szElementName, XmlNodeCallback funcXmlProcessor);
  int     GetChild(LPCTSTR szElementName, int iPos = XML_POSBEGININING);
  int     GetElement(LPCTSTR szElementName, int iPos = XML_POSBEGININING);
  int     GetNextElement(int iPos = XML_POSBEGININING);
  LPTSTR  GetValue(int iPos);
  LPTSTR  GetName(const int iPos = XML_POSBEGININING);

private:
  LPTSTR m_szDocument;  //XML document
  int    m_iLength;     //length of the document in characters
  TCHAR  m_szElement[XML_MAX_TAGNAME_SIZE];   //element's name (tag)
  TCHAR  m_szValue[XML_MAX_INNERTEXT_SIZE];   //element's value
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Gets the position of an element with the given name.

  Note: XML element (and attribute) names are case-sensitive.

  Returns: postion of the element or 0 if element is not found.

  See also: CXmlDocument::GetChild(), CXmlNode
 */
inline int CXmlDocument::GetElement(LPCTSTR szElementName, //[in] parent's tag
                             int iPos //[in] = XML_POSBEGININING position of 
                              //parent's element [0, INT_MAX)
                            )
{
return GetChild(szElementName, iPos);
}

///////////////////////////////////////////////////////////////////////////////
/*
 */
class WriteXML
{
public:
  WriteXML() { m_file = NULL; m_rootTag = NULL; };
  ~WriteXML() { Close(); };

  bool Open(LPCTSTR szFile,      //[in]
            LPCTSTR szOpeningTag //[in]
            )
  {
    _tremove(szFile);
    if (!szFile || !szOpeningTag)
      return false;
    m_file = _tfopen(szFile, _T("w"));
    if (m_file == NULL)
      return false;

      #ifdef _UNICODE
        //Write Byte Order Mark (BOM)
        unsigned short nBOM = UCBYTEORDERMARK;
        fwrite(&nBOM, sizeof(wchar_t), 1, m_file);
        LPCTSTR szXmlEncoding = _T("<?xml version=\"1.0\" encoding=\"utf-16\">\n");
      #else
        LPCTSTR szXmlEncoding = _T("<?xml version=\"1.0\" encoding=\"utf-8\">\n");
      #endif
    fwrite(szXmlEncoding, sizeof(TCHAR), _tcslen(szXmlEncoding), m_file);

    m_rootTag = new TCHAR[_tcslen(szOpeningTag) + 1];
    _tcscpy(m_rootTag, szOpeningTag);
    _ftprintf(m_file, _T("<%s>\n"), m_rootTag);
    return true;
  };

  void Close()
  {
    if (m_file != NULL)
      {
      if (m_rootTag != NULL)
        _ftprintf(m_file, _T("</%s>\n"), m_rootTag);
      fclose(m_file);
      }
    delete[] m_rootTag;
    m_rootTag = NULL;
    m_file = NULL;
  };

  void WriteTag(LPCTSTR szElementName, //[in]
                LPCTSTR data   //[in]
                )
  {
    if (m_file == NULL ||
        szElementName  == NULL ||
        data   == NULL)
      return;
    _ftprintf(m_file, _T("\t<%s>%s</%s>\n"), szElementName, data, szElementName);
  };

  void WriteTag(LPCTSTR szElementName, //[in]
                int data,
                LPCTSTR format = _T("%i"))
  {
    TCHAR temp[10];
    _stprintf(temp, format, data);
    WriteTag(szElementName, temp);
  };

  void WriteTag(LPCTSTR szElementName, //[in]
                float data
                )
  {
    if (m_file == NULL ||
        szElementName  == NULL)
      return;
    _ftprintf(m_file, _T("\t<%s>%f</%s>\n"), szElementName, data, szElementName);
  };

  void WriteTag(LPCTSTR szElementName, //[in]
                bool data
                )
  {
    if (m_file == NULL ||
        szElementName  == NULL)
      return;
    _ftprintf(m_file, _T("\t<%s>%s</%s>\n"), szElementName,
         data ? _T("true") : _T("false"), szElementName);
  };

private:
  LPTSTR m_rootTag;
  FILE*  m_file;
};

///////////////////////////////////////////////////////////////////////////////
#endif // !defined(_KXMLDOCUMENT_H_)
/*****************************************************************************
 * $Log: KXmlDocument.h,v $
 * Revision 1.8  2009/10/16 21:41:32  ddarko
 * Get element without  value
 *
 * Revision 1.7  2009/10/07 21:43:36  ddarko
 * Fixed getting element's name
 *
 * Revision 1.6  2009/10/06 21:55:21  ddarko
 * fixed overflows in CXmlDocument
 *
 * Revision 1.5  2009/10/05 21:42:31  ddarko
 * Unicode XML output
 *
 * Revision 1.4  2009/10/02 20:20:53  ddarko
 * Unicode build
 *
 * Revision 1.3  2009/10/01 21:39:55  ddarko
 * header files
 *
 * Revision 1.2  2009/10/01 19:46:58  ddarko
 * Formatting
 *
 * Revision 1.1  2009/10/01 19:16:41  ddarko
 * http://xbmc.org/
 * # svn co http://xbmc.svn.sourceforge.net/svnroot/xbmc/trunk 2003-10-14 xbmc.org
 * /trunk/sources/screensavers/Asteroids/XmlDocument.h – XBMC – Trac
 *****************************************************************************/
