/*$RCSfile: KXmlDocument.h,v $: header file
  $Revision: 1.4 $ $Date: 2009/10/02 20:20:53 $
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

#define XML_ROOT_NODE              0
#define XML_MAX_TAGNAME_SIZE      32
#define XML_MAX_INNERTEXT_SIZE  1024

typedef int    XmlNode;
typedef void (*XmlNodeCallback) (LPCTSTR szTag, XmlNode node);

///////////////////////////////////////////////////////////////////////////////
/*
 */
class CXmlDocument
{
public:
  CXmlDocument();
  virtual ~CXmlDocument();

  bool    Create(LPCTSTR szXmlText);
  int     Read(LPCTSTR szFilename);
  void    Close();
  int     GetNodeCount(LPCTSTR tag);
  void    EnumerateNodes(LPCTSTR szTag, XmlNodeCallback pFunc);
  XmlNode GetChildNode(XmlNode node, LPCTSTR szTag);
  XmlNode GetNextNode(XmlNode node);
  LPTSTR  GetNodeText(XmlNode node);
  LPTSTR  GetNodeTag(XmlNode node);

private:
  LPTSTR m_szDocument;  //XML document
  int    m_iLength;     //length of the document in characters
  int    m_iNodeCount;
  TCHAR  m_szTag[XML_MAX_TAGNAME_SIZE];
  TCHAR  m_szText[XML_MAX_INNERTEXT_SIZE];
};

///////////////////////////////////////////////////////////////////////////////
/*
 */
class WriteXML
{
public:
  WriteXML() { m_file = NULL; m_rootTag = NULL; };
  ~WriteXML() { Close(); };

  bool Open(const char *szFile, const char *szOpeningTag)
  {
    remove(szFile);
    if (!szFile || !szOpeningTag) return false;
    m_file = fopen(szFile, "w");
    if (!m_file) return false;
    m_rootTag = new char[strlen(szOpeningTag) + 1];
    strcpy(m_rootTag, szOpeningTag);
    fprintf(m_file, "<%s>\n", m_rootTag);
    return true;
  };

  void Close()
  {
    if (m_file)
    {
      if (m_rootTag)
        fprintf(m_file, "</%s>\n", m_rootTag);
      fclose(m_file);
    }
    delete[] m_rootTag;
    m_rootTag = NULL;
    m_file = NULL;
  };

  void WriteTag(const char *szTag, const char *data)
  {
    if (!m_file || !szTag || !data) return;
    fprintf(m_file, "\t<%s>%s</%s>\n", szTag, data, szTag);
  };

  void WriteTag(const char *szTag, int data, const char *format = "%i")
  {
    char temp[10];
    sprintf(temp, format, data);
    WriteTag(szTag, temp);
  };

  void WriteTag(const char *szTag, float data)
  {
    if (!m_file || !szTag) return;
    fprintf(m_file, "\t<%s>%f</%s>\n", szTag, data, szTag);
  };

  void WriteTag(const char *szTag, bool data)
  {
    if (!m_file || !szTag) return;
    fprintf(m_file, "\t<%s>%s</%s>\n", szTag, data ? "true" : "false", szTag);
  };

private:
  char *m_rootTag;
  FILE *m_file;
};

///////////////////////////////////////////////////////////////////////////////
#endif // !defined(_KXMLDOCUMENT_H_)
/*****************************************************************************
 * $Log: KXmlDocument.h,v $
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
