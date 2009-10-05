/*$RCSfile: KXmlDocument.h,v $: header file
  $Revision: 1.5 $ $Date: 2009/10/05 21:42:31 $
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

typedef void (*XmlNodeCallback) (LPCTSTR szTag, int iPos);

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
  int     GetChildNode(int iPos, LPCTSTR szTag);
  int     GetNextNode(int iPos);
  LPTSTR  GetNodeText(int iPos);
  LPTSTR  GetNodeTag(int iPos);

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

  void WriteTag(LPCTSTR szTag, //[in]
                LPCTSTR data   //[in]
                )
  {
    if (m_file == NULL || 
        szTag  == NULL || 
        data   == NULL)
      return;
    _ftprintf(m_file, _T("\t<%s>%s</%s>\n"), szTag, data, szTag);
  };

  void WriteTag(LPCTSTR szTag, //[in]
                int data, 
                LPCTSTR format = _T("%i"))
  {
    TCHAR temp[10];
    _stprintf(temp, format, data);
    WriteTag(szTag, temp);
  };

  void WriteTag(LPCTSTR szTag, //[in]
                float data
                )
  {
    if (m_file == NULL || 
        szTag  == NULL)
      return;
    _ftprintf(m_file, _T("\t<%s>%f</%s>\n"), szTag, data, szTag);
  };

  void WriteTag(LPCTSTR szTag, //[in]
                bool data
                )
  {
    if (m_file == NULL || 
        szTag  == NULL)
      return;
    _ftprintf(m_file, _T("\t<%s>%s</%s>\n"), szTag,
         data ? _T("true") : _T("false"), szTag);
  };

private:
  LPTSTR m_rootTag;
  FILE*  m_file;
};

///////////////////////////////////////////////////////////////////////////////
#endif // !defined(_KXMLDOCUMENT_H_)
/*****************************************************************************
 * $Log: KXmlDocument.h,v $
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
