/*$RCSfile: KXmlWriter.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/11/09 22:27:36 $
  $Author: ddarko $

  Defines the class behavior.
  Copyright: http://xbmc.org/
  2003-10-14 xbmc.org
  2009-11-09 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _MSC_VER //Microsoft Visual Studio C++ compiler
  #if _MSC_VER >= 1400
    #define _CRT_SECURE_NO_DEPRECATE //TODO: fopen_s()
  #endif

  #include "stdafx.h"

  #ifdef _CRT_SECURE_NO_DEPRECATE
    #pragma message ("  _CRT_SECURE_NO_DEPRECATE defined.")
  #endif
  #ifdef _DEBUG
    #pragma warning(disable: 4127) //warning C4127: conditional expression is constant
  #endif
#endif  //_MSC_VER

//#include <string.h>
//#include <stdio.h>
#include "KXmlWriter.h" //CXmlWriter class

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

//-----------------------------------------------------------------------------
/*Default constructor
 */
CXmlWriter::CXmlWriter() :
  m_fileXml(NULL),
  m_rootTag(NULL)
{ 
};

CXmlWriter::~CXmlWriter() 
{
Close(); 
};

//-----------------------------------------------------------------------------
/*Destructive creation!
 */
bool CXmlWriter::Create(LPCTSTR szFilename,      //[in]
                        LPCTSTR szOpeningTag //[in]
                        )
{
#ifdef _UNICODE
  TRACE2(_T("CXmlWriter::Create(%ws)\n"), szFilename);
#else
  TRACE2(_T("CXmlWriter::Create(%s)\n"), szFilename);
#endif

if( (szFilename == NULL)        ||
    (szFilename[0] == _T('\0')) ||
    (szOpeningTag == NULL)  ||
    (szOpeningTag[0] == _T('\0')) )
  return false;

//Clean up residue
if (m_fileXml != NULL)
  {
  fclose(m_fileXml);
  m_fileXml = NULL;
  }

if (m_rootTag != NULL)
  {
  delete[] m_rootTag;
  m_rootTag = NULL;
  }

_tremove(szFilename); //Destroy old XML document

#if _MSC_VER < 1400
  m_fileXml = _tfopen(szFilename, _T("w"));
  if (m_fileXml == NULL)
    return false;

  #ifdef _UNICODE
    //Write Byte Order Mark (BOM)
    const unsigned short nBOM = UCBYTEORDERMARK;
    fwrite(&nBOM, sizeof(wchar_t), 1, m_fileXml);
  #endif
#else
  //Microsoft Visual C/C++ 2005, version 8.0
  #ifdef _UNICODE
    //Set the Byte Order Mark (BOM) with ccs flag
    LPCTSTR szFileAccessMode = _T("w, ccs=UNICODE");
  #else
    LPCTSTR szFileAccessMode = _T("w, ccs=UTF-8");
  #endif

  if(_tfopen_s(&m_fileXml, szFilename, szFileAccessMode) != S_OK)
    return false;
#endif

#ifdef _UNICODE
  LPCTSTR szXmlEncoding = _T("<?xml version=\"1.0\" encoding=\"utf-16\">\n");
#else
  LPCTSTR szXmlEncoding = _T("<?xml version=\"1.0\" encoding=\"utf-8\">\n");
#endif

fwrite(szXmlEncoding, sizeof(TCHAR), _tcslen(szXmlEncoding), m_fileXml);
const size_t nLen = _tcslen(szOpeningTag) + 1;
m_rootTag = new TCHAR[nLen];
if(m_rootTag != NULL)
  {
  #if _MSC_VER < 1400
    _tcscpy(m_rootTag, szOpeningTag);
  #else
    //Microsoft Visual C/C++ 2005, version 8.0
    if(_tcscpy_s(m_rootTag, nLen * sizeof(TCHAR), szOpeningTag) != S_OK)
      return false;
  #endif

  if(_ftprintf(m_fileXml, _T("<%s>\n"), m_rootTag) > 0)
    return true;
  }
return false;
};

//-----------------------------------------------------------------------------
/*
 */
void CXmlWriter::Close()
{
TRACE2(_T("CXmlWriter::Close()\n"));

if (m_fileXml != NULL)
  {
  if (m_rootTag != NULL)
    {
    _ftprintf(m_fileXml, _T("</%s>\n"), m_rootTag);
    delete[] m_rootTag;
    m_rootTag = NULL;
    }
  fclose(m_fileXml);
  m_fileXml = NULL;
  }
};

//-----------------------------------------------------------------------------
/*
 */
void CXmlWriter::WriteTag(LPCTSTR szElementName, //[in]
                          LPCTSTR szData         //[in]
                          )
{
if (m_fileXml != NULL)
  {
  if((szElementName  != NULL) && 
     (szElementName[0] !=  _T('\0')))
    if((szData  != NULL) && 
       (szData[0] !=  _T('\0')))
      {
      #ifdef _UNICODE
        LPCTSTR szFormat = _T("\t<%ws>%ws</%ws>\n");
      #else
        LPCTSTR szFormat = _T("\t<%s>%s</%s>\n");
      #endif
      _ftprintf(m_fileXml, 
                szFormat, 
                szElementName, 
                szData, 
                szElementName);
      }
  }
};

/*
 */
void CXmlWriter::WriteTag(LPCTSTR szElementName, //[in]
                          const int iData //[in]
                          )
{
const int LENINTVALUE = 33;
TCHAR szIntValue[LENINTVALUE];

#if _MSC_VER < 1400
  _ltot(iData, szIntValue, 10);
#else
  //Microsoft Visual C/C++ 2005, version 8.0
  if(_ltot_s(iData, szIntValue, LENINTVALUE, 10) != S_OK)
    return;
#endif

WriteTag(szElementName, szIntValue);
};

/*
 */
void CXmlWriter::WriteTag(LPCTSTR szElementName, //[in]
                          const float fData //[in]
                          )
{
if (m_fileXml == NULL ||
    szElementName  == NULL)
  return;
#ifdef _UNICODE
  LPCTSTR szFormat = _T("\t<%ws>%f</%ws>\n");
#else
  LPCTSTR szFormat = _T("\t<%s>%f</%s>\n");
#endif

_ftprintf(m_fileXml, szFormat, szElementName, fData, szElementName);
};

/*
 */
void CXmlWriter::WriteTag(LPCTSTR szElementName, //[in]
                          const bool bData //[in]
                          )
{
LPCTSTR szData = bData ? _T("1") : _T("0");
WriteTag(szElementName, szData);
};
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KXmlWriter.cpp,v $
 * Revision 1.1  2009/11/09 22:27:36  ddarko
 * Moved WriteXML to CXmlWriter
 *

 * http://xbmc.org/
 * # svn co http://xbmc.svn.sourceforge.net/svnroot/xbmc/trunk
 * /trunk/sources/screensavers/Asteroids/XmlDocument.h – XBMC – Trac  2004-04-05 xbmc.org
 *****************************************************************************/
