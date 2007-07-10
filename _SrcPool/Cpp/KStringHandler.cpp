/*$Workfile: KStringHandler.cpp$: implementation file
  $Revision: 4$ $Date: 2007-06-27 16:45:58$
  $Author: Darko Kolakovic$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2004-06-04 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifndef ASSERT
  #include "KTrace.h"
#endif
#include "KTChar.h"    //TCHAR typedef

  //warning C4127: conditional expression is constant
#pragma warning (disable: 4127)

#include "KStringHandler.h" //CStringHandler class

///////////////////////////////////////////////////////////////////////////////
// CStringHandler class

//-----------------------------------------------------------------------------
/*Copies a null-terminated string to the string object. Throws memory exception
  in case of the inadequate memory resource.
 */
CStringHandler::CStringHandler(LPCTSTR szSource //[in]= NULL a zero-terminated
                                         //string to be copied into this object
                               )
{
if( (szSource != NULL ) && (szSource[0] != _T('\0')) )
  {
  m_nLength = (unsigned int)_tcslen((TCHAR*)szSource);
  m_nSize = m_nLength + 1;
  m_pData = new TCHAR[m_nSize];
  if (m_pData != NULL)
    {
      //Copy source, including the terminating null character
     _tcscpy(m_pData, szSource);
    }
  else
    {
    m_pData = NULL;
    m_nSize = 0;
    m_nLength = 0;
    }
 }
else
  {
  m_pData = NULL;
  m_nSize = 0;
  m_nLength = 0;
  }
}

/*Copies a string object. Throws memory exception in case of the inadequate
  memory resource.
 */
CStringHandler::CStringHandler(const CStringHandler& strSource //[in] a string
                                              //to be copied into this object.
                              )
{
if ( (strSource.m_pData != NULL) && (strSource.m_nLength > 0) )
  {
  m_pData = new TCHAR[strSource.m_nLength + 1];
  if (m_pData != NULL)
    {
      //Copy source, including the terminating null character
    _tcscpy(m_pData, strSource.m_pData);
    m_nLength = strSource.m_nLength;
    m_nSize = m_nLength + 1;
    }
  }
else
  {
  m_pData = NULL;
  m_nSize = 0;
  m_nLength = 0;
  }
}

//-----------------------------------------------------------------------------
/*
 */
CStringHandler::~CStringHandler()
{
if(m_pData != NULL)
  {
  delete[] m_pData;
  m_pData = NULL;
  }
}

//-----------------------------------------------------------------------------
/*Assigns a new value to a string object.

  Note: This method makes a new copy of the source object.
 */
const CStringHandler& CStringHandler::operator=(const CStringHandler& strSource //[in]
                                                 //new value.
                                                )
{
if(this != &strSource)
  {
  if ((strSource.m_pData != NULL) && (strSource.m_nLength > 0) )
    {
    if( m_nSize < strSource.m_nLength + 1)
      {
        //Increase size of the data holder
      if (m_pData != NULL)
        delete[] m_pData;
      m_nSize = strSource.m_nLength + 1;
      m_pData = new TCHAR[m_nSize];
      }

      //Copy source, including the terminating null character
    if (m_pData != NULL)
      {
      _tcscpy(m_pData, strSource.m_pData);
      m_nLength = strSource.m_nLength;
      }
    else
      {
      m_nSize = 0;
      m_nLength = 0;
      }
    }
  else //Erase the string
    {
    if (m_pData != NULL)
      {
      delete[] m_pData;
      m_pData = NULL;
      }
    m_nSize = 0;
    m_nLength = 0;
    }
  }
return *this;
}

//-----------------------------------------------------------------------------
/*Assigns a zero-terminated string to a string object. If szSource is NULL, 
  string object will be erased.

  Note: This method makes a new copy of the source object.
 */
const CStringHandler& CStringHandler::operator=(LPCTSTR szSource //[in]
                                                 //new value or NULL.
                                                )
{
if ( szSource != NULL )
  {
  unsigned int nNewLen = (unsigned int)_tcslen(szSource);
  if( m_nSize < (unsigned int)nNewLen + 1)
    {
      //Increase size of the data holder
    if (m_pData != NULL)
      delete[] m_pData;
    m_nSize = nNewLen + 1;
    m_pData = new TCHAR[m_nSize];
    }

    //Copy source, including the terminating null character
  if (m_pData != NULL)
    {
    _tcscpy(m_pData, szSource);
    m_nLength = nNewLen;
    }
  else
    {
    m_nSize = 0;
    m_nLength = 0;
    }
  }
else //Erase the string
  {
  if (m_pData != NULL)
    {
    delete[] m_pData;
    m_pData = NULL;
    }
  m_nSize = 0;
  m_nLength = 0;
  }

return *this;
}

//-----------------------------------------------------------------------------
/*Concatenates a new string to the end of an existing string.
 */
const CStringHandler & CStringHandler::operator+=(const CStringHandler& strSource //[in]
                                                     //a string to concatenate.
                                                  )
{

if ( (strSource.m_pData != NULL) && (strSource.m_nLength > 0) )
  {
  unsigned nNewLen = m_nLength + strSource.m_nLength;
  if (nNewLen < m_nSize)
    {
      //Increase the size of the data holder
    LPTSTR szNew = new TCHAR[nNewLen + 1];
    if (szNew != NULL)
      {
      _tcscpy(m_pData, szNew);
      delete[] m_pData;
      m_pData = szNew;
      m_nSize = nNewLen + 1;
    }
    else //Failed to allocate new data handler
      {
      return *this;
      }
    }
    //Append the new string
  _tcscpy(&m_pData[m_nLength], strSource.m_pData);
  m_nLength = nNewLen;
  }

return *this;
}

//-----------------------------------------------------------------------------
/*Sets a character at a given position.
 */
void CStringHandler::SetAt(int iIndex, //[in] zero-based index of the character
                    //in the string object. The parameter must be greater than
                    //or equal to 0 and less than the value returned by GetLength.
                    TCHAR ch    //[in] character to set.

                    )
{
ASSERT(iIndex > 0 && (unsigned int)iIndex < m_nLength);
if(iIndex > 0 && (unsigned int)iIndex < m_nLength )
  {
  m_pData[iIndex] = ch;

  if( ch == _T('\0') )  //String is cauterized.
    m_nLength = iIndex;
  }
}

//-----------------------------------------------------------------------------
/*Obtains specified element of the character array.

  Returns: the character at a given position or '\0' if position is out of range.


  Example:
    CStringHandler strTemp(_T("abcdef"));
    ASSERT(strTemp[2] == _T('c'));
 */

TCHAR CStringHandler::operator[](int iIndex //[in] zero-based index of the character in
                     //the string object. The parameter must be greater than
                     //or equal to 0 and less than the value returned by GetLength.
                     ) const
{
ASSERT(iIndex > 0 && (unsigned int)iIndex < m_nLength);
if( iIndex < 0 || (unsigned int)iIndex >= m_nLength )
  return _T('\0');
return m_pData[iIndex];
}

//::GetLength()----------------------------------------------------------------
/*Obtains number of letters in a string
  Returns: the number of characters in a CString object, not including
           a null terminator.

  Example:
      CString strTemp(_T("abcdef"));
      ASSERT(strTemp.GetLength() == 6);
 */
int CStringHandler::GetLength() const
{
return (m_pData != NULL) ? (int)m_nLength : 0;
}

//::Compare()------------------------------------------------------------------
/*Performs a case-sensitive comparison of the strings, and is not affected by
  locale. Characters are treated as unsigned charcters (Null character '\0' is
  smallest character).

  Returns:
    - A negative value if the first differing element in the controlled sequence
    compares less than the corresponding element in the operand sequence;
    if the two have a common prefix but the operand sequence is longer or
    if lpsz is NULL pointer.
    - Zero if the two compare equal element by element and are the same length or
      if string object is not initialized and lpsz is NULL pointer.
    - A positive value otherwise.

 */
int CStringHandler::Compare(LPCTSTR lpsz //[in] a zero-terminated string used for
                                  //comparison
                     ) const
{
if (lpsz == m_pData) //Return 0 if both strings are at same place
  return 0;
if (lpsz == NULL)
  return -1;
if (m_pData == NULL)
  return 1;
return _tcscmp(m_pData, lpsz);
}

//-----------------------------------------------------------------------------
/*Set new size of the data holder. If the new holder is smaller than the old, only
  the fitting portion of the string will be copied.

  Returns: new size in characters
 */
int CStringHandler::SetSize(unsigned nNewSize //[in] new size in characters of
                                              //the data holder
                           )
{
if (nNewSize != m_nSize)
  {
    //Reallocate data holder
  LPTSTR szNew = new TCHAR[nNewSize + 1];
  if (szNew != NULL)
    {
    if(m_nLength > 0)
      {
      if (nNewSize > m_nSize)
        _tcscpy(m_pData, szNew);
      else
        {
         m_nLength = nNewSize -1;
        _tcsncpy(m_pData, szNew, m_nLength);
        }
      }
    delete[] m_pData;
    m_pData = szNew;
    m_nSize = nNewSize;
    }
  }
return (int)m_nSize;
}

///////////////////////////////////////////////////////////////////////////////
#pragma warning (default: 4127)
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2007-06-27 16:45:58  Darko Kolakovic typecast
 *  3    Biblioteka1.2         2004-06-08 16:42:26  Darko           Deleted friend
 *       operator<<()
 *  2    Biblioteka1.1         2004-06-06 22:54:35  Darko           Fixed data
 *       holder size in operator=()
 *  1    Biblioteka1.0         2004-06-04 16:57:20  Darko           
 * $
 *****************************************************************************/
