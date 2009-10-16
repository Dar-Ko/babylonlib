/*$RCSfile: KXmlDocument.cpp,v $: implementation file
  $Revision: 1.11 $ $Date: 2009/10/16 21:47:50 $
  $Author: ddarko $

  Defines the class behavior.
  Copyright: http://xbmc.org/
  2003-10-14 xbmc.org
  2009-09-01 Darko Kolakovic
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

#include <string.h>
#include <stdio.h>
#include "KXmlDocument.h" //CXmlDocument class

//////////////////////////////////////////////////////////////////////
// Construction/Destruction

//-----------------------------------------------------------------------------
/*Default constructor
 */
CXmlDocument::CXmlDocument() :
    m_szDocument(NULL),
    m_iLength(0)
{
m_szElement[0]  = _T('\0');
m_szValue[0] = _T('\0');
}

CXmlDocument::~CXmlDocument()
{
Close();
}

//-----------------------------------------------------------------------------
/*Copies the text to  the allocated conatiner.

  Returns true if successful, otherwise returns false.
 */
bool CXmlDocument::Create(LPCTSTR szXmlText //[in] source XML document, limited
                         //to INT_MAX characters
                         )
{
TRACE1(_T("CXmlDocument::Create(from 0x%0.8X)\n"), szXmlText);
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

//-----------------------------------------------------------------------------
/*Opens an XML document and loads it into memory.
 */
int CXmlDocument::Read(LPCTSTR szFilename //[in]
                      )
{
TRACE1(_T("CXmlDocument::Read(%s)\n"), szFilename);

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
  m_iLength = ftell(hFile) / sizeof(TCHAR);

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
/*Closes XML document freeing up resources.
 */
void CXmlDocument::Close()
{
TRACE(_T("CXmlDocument::Close()\n"));
if (m_szDocument != NULL)
  {
  delete[] m_szDocument;
  m_szDocument = NULL;
  }

m_iLength    = 0;
m_szElement[0] = _T('\0');
m_szValue[0]   = _T('\0');
}

//-----------------------------------------------------------------------------
/*Obtains count of specified elements.

  Note: XML element (and attribute) names are case-sensitive.

  Returns: number of all elements with the given name.

  See also: CXmlNode::EnumerateChildren()
 */
int CXmlDocument::Enumerate(LPCTSTR szElementName //[in] XML tag
                           )
{
TRACE1(_T("CXmlDocument::Enumerate(%s)\n"), szElementName);

int iNodeCount = 0;

if ((szElementName != NULL) && (szElementName[0] != _T('\0')))
 {
 LPTSTR szCurrentTag;
 int iPos;

 iPos = GetNextElement(XML_POSBEGININING);
 while (iPos > 0)
   {
   szCurrentTag = GetName(iPos);
   if( !_tcscmp(szCurrentTag, szElementName) )
     iNodeCount++;

   iPos = GetNextElement(iPos);
   }
 }
return iNodeCount;
}

//-----------------------------------------------------------------------------
/*Calls helper static function to further process every XML element found 
  with given name.

  Note: XML element (and attribute) names are case-sensitive.

  See also: CXmlDocument::GetNextElement()
 */
void CXmlDocument::Enumerate(LPCTSTR szElementName,   //[in] XML tag
                             XmlNodeCallback funcXmlProcessor //[in] prcessing function
                            )
{
TRACE1(_T("CXmlDocument::Enumerate(%s, callback())\n"), szElementName);

if ((funcXmlProcessor != NULL) &&
    (szElementName != NULL) && (szElementName[0] != _T('\0')))
  {
  LPTSTR szCurrentTag;
  int iPos = GetNextElement(XML_POSBEGININING);
  while (iPos > 0)
    {
    szCurrentTag = GetName(iPos);
    //Find the element and proccess element's data
    if (_tcscmp(szCurrentTag, szElementName) == 0)
      funcXmlProcessor(szElementName, iPos);

    iPos = GetNextElement(iPos);
    }
  }
}

//-----------------------------------------------------------------------------
/*Moves the current position to the next XML element (also called a node).
  An XML element describes the data that it contains. Elements can also contain
  other elements and attributes.

    <elementA attributeAA="valueAA" attributeAB="valueAB" ...>
      elementValue
    </elementA>
    <elementB attributeBA="valueBA" attributeBB="valueBB" ... />

  This implementation ignores certain malformed XML tags. Ignored are tags without
  name: '<>', '</>'.

  Note: range of the iPos is [0, INT_MAX)

  Returns: position of the next XML element or 0 if none is found.

  See also: CXmlDocument::EnumerateNodes()
 */
int CXmlDocument::GetNextElement(int iPos //[in] = XML_POSBEGININING position of 
                                //the element [0, INT_MAX)
                                )
{
if (iPos >= 0)
  {
  int  openBracket  = -1; //Used as a guard when iPos points to the middle
  int  closeBracket = -1; //of an XML tag

  for (iPos; iPos < m_iLength; iPos++)
    {
    TCHAR& c = m_szDocument[iPos];

    if (openBracket < 0)
      {
      if (c == _T('<'))
        openBracket = iPos;
      continue;
      }

    if (closeBracket < 0)
      {
      if (c == _T('>')) //Is the tag closed?
        {
        if ((iPos - openBracket) == 1)
          {
          TRACE1(_T("CXmlDocument::GetNextElement():\n  erroneous XML tag at position %d!\n"),
                  iPos);
          openBracket  = -1;  //Ignore malformed tag '<>'
          }
        else
          {
          if ((iPos - openBracket) == 2)
            {
            //Ignore tags have only single special character
            switch(m_szDocument[iPos-1])
              {
              case _T('/'):  //solidus
              case _T('?'):  //question mark
                {
                TRACE1(_T("CXmlDocument::GetNextElement():\n  erroneous XML tag at position %d!\n"),
                        iPos);
                openBracket  = -1;
                continue;
                }
              }
            }

          //Found tag's closing character
          closeBracket = iPos;
          break;
          }
        }
      }
    }

  //Return postion of the element name if the XML tag contains at least one
  //character
  if ((openBracket  >= 0) &&
      (closeBracket >  1) )
    {
    return openBracket + 1;
    }
  }
return 0;
}

//-----------------------------------------------------------------------------
/*Obtains the name of the XML element at the given position.
 
  Note: Element's names longer than XML_MAX_TAGNAME_SIZE -1 characters
  will be truncated. The name is stored in m_szElement member.

  Returns: string containing element's name.

  See also: CXmlNode::GetName()
 */
LPTSTR CXmlDocument::GetName(const int iPos //[in] = XML_POSBEGININING position of 
                             //the  element [0, INT_MAX)
                             )
{
if (iPos > 0)
  {
  int  i;
  for (i = iPos; i < m_iLength; i++)
    {
    //A white space character marks begining of an XML attribute
    if ( (m_szDocument[i] == _T(' '))  ||
         (m_szDocument[i] == _T('\n')) ||
         (m_szDocument[i] == _T('\r')) ||
         (m_szDocument[i] == _T('\t')) ||
         (m_szDocument[i] == _T('>')) )
      {
      int iLen = i - iPos;
      const int BUFFER_CAPACITY = sizeof(m_szElement) / sizeof(TCHAR);
      if (BUFFER_CAPACITY < iLen)
        iLen = BUFFER_CAPACITY - 1; //Truncate data to fit the buffer

      _tcsncpy(m_szElement, &m_szDocument[iPos], iLen);
      m_szElement[iLen] = _T('\0');
      return m_szElement;
      }
    }
  }
return NULL;
}

//-----------------------------------------------------------------------------
/*Gets the position of a child element with the given name. An element could 
  have none or more than one children elements with the same name (tag).

  Note: XML element (and attribute) names are case-sensitive.

  Returns: postion of the subelement or 0 if subelement is not found.

  See also: CXmlNode::GetChild()
 */
int CXmlDocument::GetChild(LPCTSTR szElementName, //[in] parent's tag
                          int iPos //[in] = XML_POSBEGININING position of
                          //parent's element [0, INT_MAX)
                          )
{
TCHAR szCurrentTag[XML_MAX_TAGNAME_SIZE];
ASSERT(szElementName != NULL);
if (szElementName != NULL)
  {
  //Get parent's name and copy it to m_szElement
  if(GetName(iPos) != NULL) 
    {
    _tcsncpy(szCurrentTag, m_szElement, XML_MAX_TAGNAME_SIZE - 1);
    szCurrentTag[XML_MAX_TAGNAME_SIZE - 1] = _T('\0');
    //Get child xmlNode
    iPos = GetNextElement(iPos);
    while (iPos > 0)
      {
      TCHAR* const & szChildTag = GetName(iPos); //Get child xmlNode tag

      //Match the child's tag with the one we're looking for
      if ((szChildTag != NULL) && _tcscmp(szChildTag, szElementName) == 0)
        return iPos;

      //Is this actually the parent's closing tag?
      else if (_tcscmp(&szChildTag[1], szCurrentTag) == 0)
        return 0;

      iPos = GetNextElement(iPos);
      }
    }
  }
return 0;
}

//-----------------------------------------------------------------------------
/*Obtains value of the XML element at the given position.

  Note: Element's data longer than XML_MAX_INNERTEXT_SIZE -1 characters will be
  truncated.

  Returns: string containing element's value or an empty string.

  See also: CXmlNode::GetValue()
 */
LPTSTR CXmlDocument::GetValue(int iPos //[in] position of 
                               //the element [0, INT_MAX)
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
      if (m_szDocument[i + 1] != _T('/'))
        elements++;
      else
        elements--;
      break;

    case _T('/') :  //Element without values i.e. <element attribute="value" />
      if (m_szDocument[i + 1] == _T('>'))
        {
        m_szValue[0] = _T('\0');
        return m_szValue;
        }

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
    int iLen = i - text;
    const int BUFFER_CAPACITY = sizeof(m_szValue) / sizeof(TCHAR);
    if (BUFFER_CAPACITY < iLen)
      iLen = BUFFER_CAPACITY - 1; //Truncate data to fit the buffer
    _tcsncpy(m_szValue, &m_szDocument[text], iLen);
    m_szValue[iLen] = _T('\0');
    return m_szValue;
    }
  }

m_szValue[0] = _T('\0');
return m_szValue;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: KXmlDocument.cpp,v $
 * Revision 1.11  2009/10/16 21:47:50  ddarko
 * fixed GetValue
 *
 * Revision 1.10  2009/10/16 21:41:32  ddarko
 * Get element without  value
 *
 * Revision 1.9  2009/10/16 15:49:52  ddarko
 * Typo
 *
 * Revision 1.8  2009/10/09 17:56:27  ddarko
 * Unit test
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
 * # svn co http://xbmc.svn.sourceforge.net/svnroot/xbmc/trunk
 * /trunk/sources/screensavers/Asteroids/XmlDocument.h – XBMC – Trac  2004-04-05 xbmc.org
 *****************************************************************************/
