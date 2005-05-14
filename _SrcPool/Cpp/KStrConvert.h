/*$Workfile: S:\_SrcPool\Cpp\KStrConvert.h$: header file
  $Revision: 4$ $Date: 2005-04-12 17:46:39$
  $Author: Darko Kolakovic$

  Translation between wide and single-byte characters
  Copyright: CommonSoft Inc
  2004-02-01 Darko Kolakovic
 */
/* Group=Strings                                                             */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KSTRCONVERT_H_
    //$Workfile: S:\_SrcPool\Cpp\KStrConvert.h$ sentry
  #define _KSTRCONVERT_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
//Translation between wide and single-byte characters strings.
//
//See also: wchar_t, char, SBCS, ANSI
template <typename CHARTYPE, typename TARGETTYPE>
class TStrConvert
{
public:
  TStrConvert();
  TStrConvert(const CHARTYPE* szSource);
  virtual ~TStrConvert();

public:
  operator const CHARTYPE* () const;
  operator const TARGETTYPE* ();
  TStrConvert& operator=(const TStrConvert& strValue);

private:
  CHARTYPE*   m_szSource; //zero terminated string to be converted
  TARGETTYPE* m_szTarget; //result of the conversion
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
template<typename CHARTYPE, typename TARGETTYPE>
TStrConvert<CHARTYPE, TARGETTYPE>::TStrConvert()  :
    m_szSource(NULL),
    m_szTarget(NULL)
{
}

//-----------------------------------------------------------------------------
/*This implementation only makes copy of the pointer to the source string
  (shallow copy). If source string is invalidated, result of the conversion
  operations is undefined.
 */
template<typename CHARTYPE, typename TARGETTYPE>
TStrConvert<CHARTYPE, TARGETTYPE>::TStrConvert
                        (const CHARTYPE* szSource //[in] zero terminated string
                                                   //to be converted
                        ) :
    m_szSource(const_cast<CHARTYPE*>(szSource)),
    m_szTarget(NULL)
{
}

//-----------------------------------------------------------------------------
/*
 */
template<typename CHARTYPE, typename TARGETTYPE>
TStrConvert<CHARTYPE, TARGETTYPE>::~TStrConvert()
{
if( m_szTarget != NULL)
  delete[] m_szTarget;
}

//-----------------------------------------------------------------------------
/*This implementation only makes copy of the pointer to the source string
  (shallow copy). If source string is invalidated, result of the conversion
  operations is undefined.

  Note: To reduce memory reallocation, make your custom specialization.
 */
template<typename CHARTYPE, typename TARGETTYPE>
TStrConvert<CHARTYPE, TARGETTYPE>& TStrConvert<CHARTYPE, TARGETTYPE>::operator=
       (const TStrConvert<CHARTYPE, TARGETTYPE>& strValue //[in] value to assign
       )
{
if (this != &strValue)  //If operator is not applied on object itself
  {
  if( m_szTarget != NULL)
    delete[] m_szTarget;
  m_szSource = strValue.m_szSource;

  //Note: Conversion will take place when demanded.
  }

return *this;
}

//-----------------------------------------------------------------------------
/*Returns: source string.
 */
template<typename CHARTYPE, typename TARGETTYPE>
TStrConvert<CHARTYPE, TARGETTYPE>::operator const CHARTYPE*() const
{
return m_szSource;
}

///////////////////////////////////////////////////////////////////////////////
// Specialization
#include <stdlib.h> //wcstombs(), mbstowcs()
#include <string.h> //strlen(), wcslen()
#if !defined (ASSERT)
  #include "KTrace.h"
#endif

///////////////////////////////////////////////////////////////////////////////
//Helper class used to convert single-byte to wide character strings.
typedef TStrConvert<char, wchar_t> CStrToWide;

//-----------------------------------------------------------------------------
/*Returns: wide character represenation of the zero-terminated source string.
 */
inline
CStrToWide::operator const wchar_t*()
{
if (m_szTarget == NULL)
  {
  size_t nSize;
  m_szTarget = new TARGETTYPE[nSize = strlen(m_szSource) + 1];
  if( mbstowcs(m_szTarget, m_szSource, nSize) < 0)
    {
    ASSERT(false); //Invalid multibyte character encountered
    }
  m_szTarget[nSize -1] = TARGETTYPE(0);
  }
return m_szTarget;
}

///////////////////////////////////////////////////////////////////////////////
//Helper class used to convert wide character to single-byte strings.
typedef TStrConvert<wchar_t, char> CWideToStr;

//-----------------------------------------------------------------------------
/*Returns: single-byte character represenation of the zero-terminated source string.
 */
inline
CWideToStr::operator const char* ()
{
if (m_szTarget == NULL)
  {
  size_t nSize;
  m_szTarget = new char[nSize = wcslen(m_szSource) + 1];
  if( wcstombs(m_szTarget, m_szSource, nSize) < 0)
    {
    ASSERT(false); //Invalid multibyte character encountered
    }
  m_szTarget[nSize -1] = '\0';
  }
return m_szTarget;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KSTRCONVERT_H_
/*****************************************************************************
 * $Log: 
 *  4    Biblioteka1.3         2005-04-12 17:46:39  Darko Kolakovic TRACE fix
 *  3    Biblioteka1.2         2005-03-22 02:16:13  Darko           fixed MSVC6
 *       compilation
 *  2    Biblioteka1.1         2005-03-22 02:15:44  Darko           fixed MSVC6
 *       compilation
 *  1    Biblioteka1.0         2005-03-21 03:13:43  Darko           
 * $
 *****************************************************************************/
