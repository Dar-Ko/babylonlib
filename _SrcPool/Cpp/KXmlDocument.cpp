/*$RCSfile: KXmlDocument.cpp,v $: implementation file
  $Revision: 1.5 $ $Date: 2009/10/05 21:42:31 $
  $Author: ddarko $

  Defines the class behavior.
  Copyright: http://xbmc.org/
  2003-10-14 xbmc.org
  2009-09-01 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _MSC_VER //Micorsoft Visual Studio C++ compiler
  #include "stdafx.h"
#endif  //_MSC_VER

#if _MSC_VER >= 1400
  #define _CRT_SECURE_NO_DEPRECATE //TODO: fopen_s()
#endif

#include <string.h>
#include <stdio.h>
#include "KXmlDocument.h" //CXmlDocument class

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

//-----------------------------------------------------------------------------
/*
 */
CXmlDocument::CXmlDocument() :
    m_szDocument(NULL),
    m_iLength(0),
    m_iNodeCount(0)
{
m_szTag[0]  = _T('\0');
m_szText[0] = _T('\0');
}

//-----------------------------------------------------------------------------
/*
 */
bool CXmlDocument::Create(LPCTSTR szXmlText //[in] source XML document, limited
                         //to INT_MAX characters
                         )
{
bool bResult = false;
if (szXmlText != NULL)
  {
  //Copy the text and append terminating zero.
  m_iLength = (int)_tcslen(szXmlText);
  if ((m_iLength > 0) && (m_iLength < INT_MAX)) //Overflow validation
    {
    m_szDocument = new TCHAR[m_iLength + 1];
    if (m_szDocument != NULL)
      {
      _tcsncpy(m_szDocument, szXmlText, m_iLength);
      m_szDocument[m_iLength] = _T('\0');
      bResult = true;
      }
    }
  }
return bResult;
}

CXmlDocument::~CXmlDocument()
{
if(m_szDocument != NULL)
  {
  delete[] m_szDocument;
  }
}

//-----------------------------------------------------------------------------
/*Function: xml_load_doc
  Opens an XML document and loads it into memory.
 */
int CXmlDocument::Read(LPCTSTR szFilename //[in]
                      )
{
if (szFilename != NULL)
  {
  FILE* hFile;

  hFile  = _tfopen(szFilename, _T("rb"));
  if (hFile == NULL)
    {
    return -1;
    }

  fseek(hFile, 0, SEEK_END);
  ASSERT((ftell(hFile) % sizeof(TCHAR)) == 0); //Unicode files have even number of bytes
  m_iLength = ftell(hFile)/sizeof(TCHAR);

  fseek(hFile, 0, SEEK_SET);

  m_szDocument = new TCHAR[m_iLength];
  if (!m_szDocument)
    {
    m_iLength = 0;
    fclose(hFile);
    return -2;
    }

  if (fread(m_szDocument, m_iLength, sizeof(TCHAR), hFile) <= 0)
    {
    delete[] m_szDocument;
    m_szDocument  = 0;
    m_iLength = 0;
    fclose(hFile);
    return -3;
    }

  fclose(hFile);
  return 0;
  }
return -4;
}

//-----------------------------------------------------------------------------
/*Function: xml_close_doc
  Closes XML document freeing up resources.
 */
void CXmlDocument::Close()
{
if (m_szDocument != NULL)
  {
  delete[] m_szDocument;
  m_szDocument = NULL;
  }

m_iLength    = 0;
m_iNodeCount = 0;
m_szTag[0]  = _T('\0');
m_szText[0] = _T('\0');
}

//-----------------------------------------------------------------------------
/*
 */
int CXmlDocument::GetNodeCount(LPCTSTR szTag //[in]
                              )
{
m_iNodeCount = 0;

if ((szTag != NULL) && (szTag[0] != _T('\0')))
 {
 LPTSTR szCurrentTag;
 int iPos;

 iPos = GetNextNode(XML_POSBEGININING);
 while (iPos > 0)
   {
   szCurrentTag = GetNodeTag(iPos);
   if( !_tcsicmp(szCurrentTag, szTag) )
     m_iNodeCount++;

   iPos = GetNextNode(iPos);
   }
 }
return m_iNodeCount;
}

//-----------------------------------------------------------------------------
/*Function: xml_next_tag
  Moves the current position to the next tag.
 */
int CXmlDocument::GetNextNode(int iPos //[in]
                                 )
{
int  openBracket = -1;
int  closeBracket = -1;
int  i;
for (i = iPos; i < m_iLength; i++)
  {
  TCHAR& c = m_szDocument[i];

  if (openBracket < 0)
    {
    if (c == _T('<'))
      openBracket = i;
    continue;
    }

  if (closeBracket < 0)
    {
    if (c == _T('>'))
      {
      closeBracket = i;
      break;
      }
    }
  }

if ((openBracket >= 0) && (closeBracket >= 0))
  {
  return openBracket + 1;
  }

return 0;
}

//-----------------------------------------------------------------------------
/*Function: xml_get_tag_name
  Gets the tag name at the current position (max 32 chars!).
 */
LPTSTR CXmlDocument::GetNodeTag(int iPos //[in]
                                )
{
int  i;
for (i = iPos; i < m_iLength; i++)
  {
  if ( (m_szDocument[i] == _T(' '))  ||
       (m_szDocument[i] == _T('\n')) ||
       (m_szDocument[i] == _T('\r')) ||
       (m_szDocument[i] == _T('\t')) ||
       (m_szDocument[i] == _T('>')) )
    {
    _tcsncpy(m_szTag, &m_szDocument[iPos], i - iPos);
    m_szTag[i - iPos] = _T('\0');
    return m_szTag;
    }
  }

return NULL;
}

//-----------------------------------------------------------------------------
/*Function: xml_get_child_tag
  Gets the position of the child tag.
 */
int CXmlDocument::GetChildNode(int iPos,//[in]
                                   LPCTSTR szTag   //[in]
                                  )
{
TCHAR  szCurrentTag[XML_MAX_TAGNAME_SIZE];
LPTSTR szChildTag;

// get parent xmlNode tag
_tcscpy(szCurrentTag,GetNodeTag(iPos));

// get child xmlNode
iPos = GetNextNode(iPos);
while (iPos>0)
  {
  // get child xmlNode tag
  szChildTag = GetNodeTag(iPos);

  // does the child's tag match the one we're looking for
  if ( !_tcsicmp(szChildTag, szTag) )
    return iPos;

  // is this actually the parent's closing tag?
  else if ( !_tcsicmp(&szChildTag[1], szCurrentTag) )
    return 0;

  iPos = GetNextNode(iPos);
  }

return 0;
}

//-----------------------------------------------------------------------------
/*Function: xml_get_tag_text
  Gets the text of a given tag (max limit 128 chars!!).
 */
LPTSTR CXmlDocument::GetNodeText(int iPos //[in]
                                )
{
int i, text = 0;
int opens = 1;
int elements = 0;

for (i = iPos; i < (m_iLength - 1); i++)
  {
  switch (m_szDocument[i])
    {
    case _T('<'):
      opens++;
      if (m_szDocument[i + 1]!=_T('/'))
        elements++;
      else
        elements--;
      break;

    case _T('>') :
      opens--;
      break;

    case _T(' ') :
    case _T('\n'):
    case _T('\r'):
    case _T('\t'):
      break;

    default:
      if ((opens == 0) && (elements == 0))
        text = i;
      break;
    }

  if (text > 0)  //??? D.K  move for loop at the bottom here
    break;
  }

if (text == 0)
  return NULL; //??? D.K.

for (i = text; i < m_iLength; i++)
  {
  if (m_szDocument[i] == _T('<'))
    {
    _tcsncpy(m_szText, &m_szDocument[text], i - text);
    m_szText[i - text] = _T('\0');
    return m_szText;
    }
  }

m_szText[0] = _T('\0');
return m_szText;
}

//-----------------------------------------------------------------------------
/*
 */
void CXmlDocument::EnumerateNodes(LPCTSTR szTag,   //[in]
                                  XmlNodeCallback pFunc //[in]
                                 )
{
if (pFunc != NULL)
  {
  LPTSTR szCurrentTag;
  int iPos = GetNextNode(XML_POSBEGININING);
  while (iPos > 0)
    {
    szCurrentTag = GetNodeTag(iPos);
    if (_tcsicmp(szCurrentTag, szTag) != 0)
      pFunc(szTag, iPos);

    iPos = GetNextNode(iPos);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KXmlDocument.cpp,v $
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
 * # svn co http://xbmc.svn.sourceforge.net/svnroot/xbmc/trunk
 * /trunk/sources/screensavers/Asteroids/XmlDocument.h – XBMC – Trac  2004-04-05 xbmc.org
 *****************************************************************************/
