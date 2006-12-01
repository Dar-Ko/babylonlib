/*$Workfile: KStringHandler.h$: header file
  $Revision: 4$ $Date: 2005-04-26 16:39:31$
  $Author: Darko Kolakovic$

  Dynamic string class
  Copyright: CommonSoft Inc.
  2004-06-04 Darko Kolakovic
 */

/* Group=Strings                                                             */
#pragma once


///////////////////////////////////////////////////////////////////////////////
//The CStringHandler manages a variable-length sequence of characters.
//CStringHandler objects can grow as a result of concatenation operations.
//The CStringHandler does not throw any exceptions and creates objects to be used
//in the same thread were created.
class CStringHandler
{
  //Construction/destruction
public:
  CStringHandler(LPCTSTR szSource = NULL);
  CStringHandler(const CStringHandler& strSource);
  ~CStringHandler();

protected:
  LPTSTR m_pData;    //pointer to data holder
  unsigned m_nSize;  //size of the data holder in characters

  unsigned m_nLength;//length of the stored string in characters

//Operations
public:
  const CStringHandler & operator= (const CStringHandler& strSource);
  const CStringHandler & operator= (LPCTSTR szSource);
  const CStringHandler & operator+=(const CStringHandler& strSource);
  TCHAR operator[](int iIndex) const;
  operator LPCTSTR() const;

  int  GetLength() const;
  int  SetSize(unsigned nNewSize);
  int  Compare(LPCTSTR lpsz) const;
  void SetAt(int iIndex, TCHAR ch);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::LPCTSTR()------------------------------------------------------------------
/*Obtains characters array stored in a string object as a C-style
  null-terminated string.

  Returns: a character pointer to the string’s data.

  Note: Calling any non-const member function for this object after you have
        obtained the character pointer can invalidate the returned pointer.
 */
inline CStringHandler::operator LPCTSTR() const
{
return m_pData;
}

//////////////////////////////////////////////////////////////////////////////
//::operator<()----------------------------------------------------------------
/*Operator performs case-sensitive comparison of two strings.
  Returns true if the strings meet the comparison condition;
  otherwise returns false.
 */
inline bool operator< (const CStringHandler& s1, const CStringHandler& s2)
{
return s1.Compare(s2) < 0;
}

inline bool operator< (const CStringHandler& s1, LPCTSTR s2)
{
return s1.Compare(s2) < 0;
}

inline bool operator< (LPCTSTR s1, const CStringHandler& s2)
{
return s2.Compare(s1) > 0;
}

//::operator<=()---------------------------------------------------------------
/*Operator performs case-sensitive comparison of two strings.
  Returns true if the strings meet the comparison condition;
  otherwise returns false.
 */
inline bool operator<=(const CStringHandler& s1, const CStringHandler& s2)
{
return s1.Compare(s2) <= 0;
}

inline bool operator<=(const CStringHandler& s1, LPCTSTR s2)
{
return s1.Compare(s2) <= 0;
}

inline bool operator<=(LPCTSTR  s1, const CStringHandler& s2)
{
return s2.Compare(s1) >= 0;
}

//::operator==()---------------------------------------------------------------
/*Operator performs case-sensitive comparison of two strings.
  Returns true if the strings meet the comparison condition;
  otherwise returns false.
 */
inline bool operator==(const CStringHandler& s1, const CStringHandler& s2)
{
return s1.Compare(s2) == 0;
}

inline bool operator==(const CStringHandler& s1, LPCTSTR s2)
{
return s1.Compare(s2) == 0;
}

inline bool operator==(LPCTSTR s1, const CStringHandler& s2)
{
return s2.Compare(s1) == 0;
}

//::operator>=()---------------------------------------------------------------
/*Operator performs case-sensitive comparison of two strings.
  Returns true if the strings meet the comparison condition;
  otherwise returns false.
 */
inline bool operator>=(const CStringHandler& s1, const CStringHandler& s2)
{
return s1.Compare(s2) >= 0;
}

inline bool operator>=(const CStringHandler& s1, LPCTSTR s2)
{
return s1.Compare(s2) >= 0;
}

inline bool operator>=(LPCTSTR s1, const CStringHandler& s2)
{
return s2.Compare(s1) <= 0;
}

//::operator>()----------------------------------------------------------------
/*Operator performs case-sensitive comparison of two strings.
  Returns true if the strings meet the comparison condition;
  otherwise returns false.
 */
inline bool operator>(const CStringHandler& s1, const CStringHandler& s2)
{
return s1.Compare(s2) > 0;
}

inline bool operator>(const CStringHandler& s1, LPCTSTR s2)
{
return s1.Compare(s2) > 0;
}

inline bool operator>(LPCTSTR s1, const CStringHandler& s2)
{
return s2.Compare(s1) < 0;
}

//::operator!=()---------------------------------------------------------------
/*Operator performs case-sensitive comparison of two strings.
  Returns true if the strings meet the comparison condition;
  otherwise returns false.
 */
inline bool operator!=(const CStringHandler& s1, const CStringHandler& s2)
{
return s1.Compare(s2) != 0;
}

inline bool operator!=(const CStringHandler& s1, LPCTSTR s2)
{
return s1.Compare(s2) != 0;
}

inline bool operator!=(LPCTSTR s1, const CStringHandler& s2)
{
return s2.Compare(s1) != 0;
}


///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2004-06-08 16:42:28  Darko           Deleted friend
 *       operator<<()
 *  2    Biblioteka1.1         2004-06-06 22:50:54  Darko           added operator=
 *       (LPCTSTR szSource)
 *  1    Biblioteka1.0         2004-06-04 16:57:24  Darko
 * $
 *****************************************************************************/
