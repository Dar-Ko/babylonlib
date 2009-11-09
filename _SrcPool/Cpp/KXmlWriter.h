/*$RCSfile: KXmlWriter.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/11/09 22:27:36 $
  $Author: ddarko $

  Interface for the CXmlWriter class
  Copyright: http://xbmc.org/
  2009-11-09 Darko Kolakovic
  2003-10-14 xbmc.org
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#if !defined(_KXMLWRITER_H_)
  //$RCSfile: KXmlWriter.h,v $ sentry
	#define _KXMLWRITER_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
/*Simplistic XML formatter class, suitable for creating small XML documents.

  See also: CXmlNode, CXmlAttribute, CXmlDocument;
  {html <a href="http://msdn.microsoft.com/en-us/library/ms256153%28VS.100%29.aspx">
  MSDN: XML Standards Reference: Document Map;</a>
  <a href="http://www.w3.org/TR/REC-xml/">
  W3C: Extensible Markup Language (XML) 1.0 (Fifth Edition)</a>}
 */
class CXmlWriter
{
public:
  CXmlWriter();
  virtual ~CXmlWriter();

  bool Create(LPCTSTR szFilename, LPCTSTR szOpeningTag);
  void Close();

//Operations
  virtual void WriteTag(LPCTSTR szElementName, LPCTSTR szData);
  virtual void WriteTag(LPCTSTR szElementName, const int iData);
  virtual void WriteTag(LPCTSTR szElementName, const float fData);
  virtual void WriteTag(LPCTSTR szElementName, const bool bData);

protected:
  LPTSTR m_rootTag; //
  FILE*  m_fileXml; //
};

///////////////////////////////////////////////////////////////////////////////
#endif // !defined(_KXMLWRITER_H_)
/*****************************************************************************
 * $Log: KXmlWriter.h,v $
 * Revision 1.1  2009/11/09 22:27:36  ddarko
 * Moved WriteXML to CXmlWriter
 *
 * http://xbmc.org/
 * # svn co http://xbmc.svn.sourceforge.net/svnroot/xbmc/trunk 2003-10-14 xbmc.org
 * /trunk/sources/screensavers/Asteroids/XmlDocument.h – XBMC – Trac
 *****************************************************************************/
