/*$Workfile: TestCptString.h$: header file
  $Revision: 1$ $Date: 2004-06-08 15:37:13$
  $Author: Darko$

  Test Palindrome string class
  Copyright: CommonSoft Inc.
  2004-06-06 Darko Kolakovic
 */

// Group=Examples
#pragma once

#include "KStrings.h" //Declarations
#include "KStringHandler.h" //CStringHandler class

///////////////////////////////////////////////////////////////////////////////
//The CPTString manages a variable-length sequence of characters.
//CPTString objects can grow as a result of concatenation operations.
//The CPTString does not throw any exceptions and creates objects to be used
//in the same thread were created.
class CPTString: public CStringHandler
{
  //Construction/destruction
public:
  CPTString(LPCTSTR szSource = NULL);
  CPTString(const CPTString& strSource);
  virtual ~CPTString();

//Operations
public:
  bool IsPalindrome() const;
  void TsWriteToViewLn() const;

  friend tostream& operator<<(tostream& out, const CPTString& strSource);
  friend tistream& operator>>(tistream& in, CPTString& strTarget);
  friend tistream& GetLine(tistream& in, CPTString& strTarget);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//----------------------------------------------------------------------------
/*Default constructor
 */
inline CPTString::CPTString(LPCTSTR szSource //[in]= NULL a zero-terminated
                                         //string to be copied into this object
                                         ) : CStringHandler(szSource)
{
}

inline CPTString::CPTString(const CPTString& strSource //[in] a string
                                              //to be copied into this object.
                                         ) : CStringHandler(strSource)
{
}

inline CPTString::~CPTString()
{
}

//----------------------------------------------------------------------------
/*Validates if a string object is a palindrome.

  Returns: true if a string is a palindrome; otherwise, returns false.
 */
inline bool CPTString::IsPalindrome() const
{
return ::IsPalindrome(m_pData, m_nLength);
}

//----------------------------------------------------------------------------
#ifndef _KBOOLSTREAM_H_
  #include "STL/KBoolStream.h"
#endif
/*Writes the string object and the result of palindrome validation at the 
  console standard output stream.

  Note: uses Standard Template Library (STL).
 */
inline void CPTString::TsWriteToViewLn() const
{
if (m_pData != NULL)
  std::_tcout << (tbool)IsPalindrome() << _T(' ') << m_pData << std::endl;
else
  std::_tcout << (tbool)IsPalindrome() << _T(' ') << _T("<null>") << std::endl;
std::_tcout.flush();
}

//////////////////////////////////////////////////////////////////////////////
// Helpers: Stream IO

//-----------------------------------------------------------------------------
/*
 */
inline tostream& operator<<( tostream& out,
                           const CPTString& strSource
                   )
{
return out << (LPCTSTR)strSource;
}

//-----------------------------------------------------------------------------
/*
 */
inline tistream& operator>>(tistream& in,
                           CPTString& strTarget
                           )
{
in >> strTarget.m_pData; //Fixme! overflow D.K.
ASSERT(!in.fail());
return in;
}

//-----------------------------------------------------------------------------
/*
 */
inline tistream& GetLine(tistream& in,
                         CPTString& strTarget
                         )
{
in.getline( strTarget.m_pData, strTarget.m_nSize - 1 );
ASSERT(!in.fail());
return in;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-06-08 15:37:13  Darko           
 * $
 *****************************************************************************/
