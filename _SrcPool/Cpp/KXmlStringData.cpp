/*$Workfile: KXmlStringData.cpp$: implementation file
  $Revision: 7$ $Date: 2005-04-14 22:25:25$
  $Author: Darko$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2005-03-16 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _MSC_VER //Microsoft Visual Studio C++ compiler
  #include "stdafx.h"
#endif  //_MSC_VER

//#include <string.h>
//#include <stdlib.h> //mbstowcs()

#include "KXmlStringData.h"  //CXmlStringData class

//#ifndef ASSERT
//  #include "KTrace.h"
//#endif

#ifdef _DEBUG
  //#define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CXmlStringData class

//-----------------------------------------------------------------------------
/*Default constructor
 */
  CXmlStringData::CXmlStringData() :
    m_wszData(NULL),
    m_szData(NULL)
{
}

//-----------------------------------------------------------------------------
/*
  Note: Length of the string is limited to INT_MAX characters.
 */
CXmlStringData::CXmlStringData(const char* strSource, //[in] string source
                       int iLength //[in] = -1 length of the string or -1 if
                       //the source string is zero-terminated
                       ) : m_szData(NULL)
{
if (strSource != NULL)
  {
  if (iLength < 0)
    iLength = (int)strlen(strSource);
  m_wszData = new wchar_t[iLength + 1];

  if (mbstowcs(m_wszData, strSource, iLength) < 0)
    {
    ASSERT(false); //Invalid multibyte character encountered
    }
  m_wszData[iLength] = wchar_t(0);
  }
else
  m_wszData = NULL;
}

//-----------------------------------------------------------------------------
/*
  Note: Length of the string is limited to INT_MAX characters.
 */
CXmlStringData::CXmlStringData(const wchar_t* strSource, //[in] string source
                       int iLength //[in] = -1 length of the string or -1 if
                       //the source string is zero-terminated
                       ) : m_szData(NULL)
{
if (strSource != NULL)
  {
  if (iLength < 0)
    iLength = (int)wcslen(strSource);
  m_wszData = new wchar_t[iLength + 1];

  wcsncpy(m_wszData, strSource, iLength);
  m_wszData[iLength] = wchar_t(0);
  }
else
  m_wszData = NULL;
}

//-----------------------------------------------------------------------------
/*Destructor
 */
CXmlStringData::~CXmlStringData()
{
if (m_wszData != NULL)
  {
  delete[] m_wszData;
  }
if (m_szData != NULL)
  {
  delete[] m_szData;
  }
}

//-----------------------------------------------------------------------------
/*
 */
CXmlStringData& CXmlStringData::operator=(const CXmlStringData& strValue //[in] value to assign
                            )
{
if (this != &strValue)
  {
  //Invalidate translated data
  if (m_szData != NULL)
    {
    delete[] m_szData;
    m_szData = NULL;
    }

  size_t nLength = wcslen(strValue.m_wszData);

  //Copy the source string with simpliest possible way
  if (m_wszData != NULL)
    delete[] m_wszData;
  m_wszData = new wchar_t[nLength + 1];
  wcsncpy(m_wszData, strValue.m_wszData, nLength);
  m_wszData[nLength] = wchar_t(0);

  }

return *this;
}

//-----------------------------------------------------------------------------
/*
 */
CXmlStringData::operator const wchar_t*()
{
return m_wszData;
}

//-----------------------------------------------------------------------------
/*
 */
CXmlStringData::operator const char*()
{
ASSERT(m_wszData != NULL);
if (m_wszData == NULL)
  return NULL; //Instead returning an unrelated text if the input is Null,
               //return the Null

 //Translate wide character text to the single-byte string
if (m_szData == NULL)
  {
  size_t nSize;
  m_szData = new char[nSize = wcslen(m_wszData) + 1];
  if(wcstombs(m_szData, m_wszData, nSize) < 0)
    {
    ASSERT(false); //Invalid multibyte character encountered
    }
  m_szData[nSize -1] = '\0';
  }

return m_szData;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  7    Biblioteka1.6         2005-04-14 22:25:25  Darko           deleted MSVC
 *       UNICODE fix
 *  6    Biblioteka1.5         2005-04-12 17:46:49  Darko Kolakovic TRACE fix
 *  5    Biblioteka1.4         2005-04-06 14:45:30  Darko Kolakovic Renamed class
 *       to avoid colision with other xml types
 *  4    Biblioteka1.3         2005-04-06 14:44:06  Darko Kolakovic
 *  3    Biblioteka1.2         2005-04-03 23:52:30  Darko           explicit
 *       typecast
 *  2    Biblioteka1.1         2005-03-27 02:17:39  Darko           operator const
 *       char*()
 *  1    Biblioteka1.0         2005-03-26 01:10:09  Darko
 * $
 *****************************************************************************/
