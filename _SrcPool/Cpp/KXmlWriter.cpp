/*$RCSfile: KXmlWriter.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/11/13 20:42:38 $
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
  m_szRootTag(NULL), 
  m_szTag(NULL),
  m_fileXml(NULL)
{ 
};

CXmlWriter::~CXmlWriter() 
{
Close();
ASSERT(m_szRootTag == NULL);
ASSERT(m_szTag == NULL);
ASSERT(m_fileXml == NULL);
};

//-----------------------------------------------------------------------------
/*Destructive creation!
 */
bool CXmlWriter::Create(LPCTSTR szFilename, //[in]
                        LPCTSTR szRootTag   //[in]
                        )
{
#ifdef _UNICODE
  TRACE2(_T("CXmlWriter::Create(%ws)\n"), szFilename);
#else
  TRACE2(_T("CXmlWriter::Create(%s)\n"), szFilename);
#endif

if( (szFilename == NULL)        ||
    (szFilename[0] == _T('\0')) ||
    (szRootTag == NULL)  ||
    (szRootTag[0] == _T('\0')) )
  return false;

//Clean up residue
if (m_fileXml != NULL)
  {
  fclose(m_fileXml);
  m_fileXml = NULL;
  }

if (m_szRootTag != NULL)
  {
  delete[] m_szRootTag;
  m_szRootTag = NULL;
  }
if (m_szTag != NULL)
  {
  delete[] m_szTag;
  m_szTag = NULL;
  }

//Open an empty file for writing. If the file exists, its contents are destroyed.
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
const size_t nLen = _tcslen(szRootTag) + 1;
m_szRootTag = new TCHAR[nLen];
if(m_szRootTag != NULL)
  {
  #if _MSC_VER < 1400
    _tcscpy(m_szRootTag, szRootTag);
  #else
    //Microsoft Visual C/C++ 2005, version 8.0
    //Note: Off-line MSVC++ 8.0 2005 documentation states wrongly that 2nd
    //parameter of _tcscpy_s is length in bytes, while actually it is number
    //of characters
    if(_tcscpy_s(m_szRootTag, nLen, szRootTag) != S_OK)
      return false;
  #endif

  if(_ftprintf(m_fileXml, _T("<%s>\n"), m_szRootTag) > 0)
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
SetTag(NULL);

if (m_fileXml != NULL)
  {
  if (m_szRootTag != NULL)
    {
    _ftprintf(m_fileXml, _T("</%s>\n"), m_szRootTag);
    }
  fclose(m_fileXml);
  m_fileXml = NULL;
  }

if (m_szRootTag != NULL)
  {
  delete[] m_szRootTag;
  m_szRootTag = NULL;
  }
};

//-----------------------------------------------------------------------------
/*
 */
void CXmlWriter::SetTag(LPCTSTR szElementName //[in] XML element name or NULL
                       )
{
if (m_szTag != NULL)
  delete[] m_szTag;

if((szElementName != NULL) && 
   (szElementName[0] !=  _T('\0')))
  {
  const size_t nLen = _tcslen(szElementName) + 5 + 1;
  m_szTag = new TCHAR[nLen];
  const int POSELEMENTNAME = 3;
  const int POSTAGOPEN = 1;
  if(m_szRootTag != NULL)
    {
    //Format open XML tag as '\t\t<elementName>\n'
    //Note: 1st \t character is space holders for closing tag delimiter
    m_szTag[0] = _T('\t');
    m_szTag[POSTAGOPEN] = _T('\t');
    m_szTag[POSTAGOPEN + 1] = _T('<');

    #if _MSC_VER < 1400
      _tcscpy(&m_szTag[POSELEMENTNAME], szElementName);
    #else
      //Microsoft Visual C/C++ 2005, version 8.0
      if(_tcscpy_s(&m_szTag[POSELEMENTNAME], 
                   nLen - POSELEMENTNAME,  //Size of the destination buffer in characters
                   szElementName) != S_OK)
        {
        delete[] m_szTag;
        m_szTag = NULL;
        return; //Failure;
        }
    #endif
    m_szTag[nLen - 3] = _T('>');
    m_szTag[nLen - 2] = _T('\n');
    m_szTag[nLen - 1] = _T('\0');
    }
  }
else
  m_szTag = NULL;
};

//-----------------------------------------------------------------------------
/*Formats the opening tag of the preset XML element and writes it to 
  the document.

  See also: CXmlWriter::SetTag(), CXmlWriter::CloseTag().
 */
void CXmlWriter::OpenTag()
{
if ((m_fileXml != NULL) && (m_szTag != NULL))
  {
  const int POSTAGOPEN = 1;
  m_szTag[POSTAGOPEN] = _T('\t');
  m_szTag[POSTAGOPEN + 1] = _T('<');
  const size_t nLen = _tcslen(&m_szTag[POSTAGOPEN]);
  fwrite(&m_szTag[POSTAGOPEN], sizeof(TCHAR), nLen, m_fileXml);
  }
};

//-----------------------------------------------------------------------------
/*Formats the closing tag of the preset XML element and writes it to 
  the document.

  See also: CXmlWriter::SetTag(), CXmlWriter::OpenTag().
 */
void CXmlWriter::CloseTag()
{
if ((m_fileXml != NULL) && (m_szTag != NULL))
  {
  m_szTag[1] = _T('<');
  m_szTag[2] = _T('/');
  const size_t nLen = _tcslen(m_szTag);
  fwrite(m_szTag, sizeof(TCHAR), nLen, m_fileXml);
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
        LPCTSTR szFormat = _T("\t\t<%ws>%ws</%ws>\n");
      #else
        LPCTSTR szFormat = _T("\t\t<%s>%s</%s>\n");
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
  LPCTSTR szFormat = _T("\t\t<%ws>%f</%ws>\n");
#else
  LPCTSTR szFormat = _T("\t\t<%s>%f</%s>\n");
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
 * Revision 1.2  2009/11/13 20:42:38  ddarko
 * Added SetTag();  Fixed leak: Off-line MSVC++ 8.0 2005 documentation states
 * wrongly that 2nd parameter of _tcscpy_s is length in bytes, while actually it is
 * number of characters.
 *
 * Revision 1.1  2009/11/09 22:27:36  ddarko
 * Moved WriteXML to CXmlWriter
 *

 * http://xbmc.org/
 * # svn co http://xbmc.svn.sourceforge.net/svnroot/xbmc/trunk
 * /trunk/sources/screensavers/Asteroids/XmlDocument.h – XBMC – Trac  2004-04-05 xbmc.org
 *****************************************************************************/
