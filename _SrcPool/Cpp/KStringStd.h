/*$Workfile: KStringStd.h$: header file
  $Revision: 3$ $Date: 2005-04-26 16:39:33$
  $Author: Darko Kolakovic$

  Dynamic string class
  Copyright: B. Lukovic
  Borislav Lukovic
 */
/* Group=Strings                                                             */


//#include <stdio.h>  //FILE structure
//#include <time.h>   //time_t typedef
//#include <assert.h> //assert()


#ifndef _KSTRINGSTD_H_
    /*$Workfile: KStringStd.h$ sentry */
  #define _KSTRINGSTD_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
/* CStringStd encapsulates a dynamically allocated C style null-terminated
   string.

   Note: This class's methods correspond to methods of STL's std::string class.
 */
class  CStringStd
{
public:
  CStringStd();
  CStringStd(TCHAR ch);
  CStringStd(const TCHAR* psz, UINT len = 0);
  CStringStd(const CStringStd& src);
  #if defined(_STL) || defined (USE_STL)
    CStringStd(const std::string& src);
  #endif //_STL
  virtual ~CStringStd();

private:
  void Init(const TCHAR* psz, UINT len);
  static const TCHAR* _Nullstr();
  static UINT Strlen(const TCHAR* psz) ;

public:
  const TCHAR* begin() const;
  TCHAR*       begin();
  const TCHAR* c_str() const;
  const TCHAR* end() const;
  TCHAR*       end();
  bool empty() const;
  UINT capacity() const;
  void clear(bool bFreeBuffer = true);
  void erase();
  UINT length() const;
  UINT size() const;
  void reserve(UINT n);
  void resize(UINT n, TCHAR ch = _T('A'));
  CStringStd& assign(TCHAR ch);
  CStringStd& assign(const TCHAR* psz);
  CStringStd& assign(const TCHAR* psz, UINT len);
  CStringStd& assign(const CStringStd& str);
  #if defined(_STL) || defined (USE_STL)
    CStringStd& assign(const std::string& str);
    CStringStd& operator= (const std::string& str);
    CStringStd& operator+= (const std::string& str);
  #endif //_STL
  CStringStd& operator=  (TCHAR ch);
  CStringStd& operator=  (const TCHAR* psz);
  CStringStd& operator=  (const CStringStd& str);
  CStringStd& operator+= (TCHAR ch);
  CStringStd& operator+= (const TCHAR* psz);
  CStringStd& operator+= (const CStringStd& str);

  int compare(const CStringStd& str) const;
  int compare(UINT p0, UINT n0, const CStringStd& str) const;
  int compare(const TCHAR* psz) const;
  int compare(UINT p0, UINT n0, const TCHAR* psz) const;
  int compare(UINT p0, UINT n0, const CStringStd& str, UINT pos, UINT n) const;
  int compare(UINT p0, UINT n0, const TCHAR* psz, UINT n) const;
  #if defined(_STL) || defined (USE_STL)
    int compare(const std::string& str) const;
    int compare(UINT p0, UINT n0, const std::string& str) const;
    CStringStd& append(const std::string& str);
  #endif //_STL
  CStringStd& append(int n, TCHAR ch);
  CStringStd& append(const TCHAR* psz, UINT len);
  CStringStd& append(const TCHAR* psz);
  CStringStd& append(const CStringStd& str);
  UINT find(TCHAR ch, UINT pos = 0) const;
  CStringStd substr(UINT pos = 0, UINT n = npos) const;
  const TCHAR& at(UINT pos) const;
  TCHAR& at(UINT pos);
  const TCHAR& operator[](UINT pos) const;
  TCHAR& operator[](UINT pos);
  CStringStd&  AttachBuffer(const TCHAR* psz, UINT len = 0, UINT allocatedMemorySize = 0);
  TCHAR* DetachBuffer(UINT& len, UINT& capacity);

protected:
  void Realloc(UINT n);
  CStringStd& Assign(const TCHAR* psz, UINT len);
  CStringStd& Append(const TCHAR* psz, UINT len);
  bool IsOverlapped(const TCHAR* psz);

// data
protected:
  TCHAR* m_psz;
  UINT   m_len;
  UINT   m_capacity;

public:
   static const UINT npos;

#if defined(_STL) || defined (USE_STL)
  CStringStd(const std::string& src);
  CStringStd& assign(const std::string& str);
  CStringStd& operator= (const std::string& str);
  CStringStd& operator+= (const std::string& str);
  CStringStd& append(const std::string& str);
  int compare(const std::string& str) const;
  int compare(UINT p0, UINT n0, const std::string& str) const;
#endif //_STL

};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
CStringStd::CStringStd()
  {  Init((TCHAR*)NULL, 0); }

CStringStd::CStringStd(TCHAR ch)
    {
       TCHAR sz[2] = {ch, _T('\0')};
     Init(sz, 1);
    }

CStringStd::CStringStd(const TCHAR* psz, UINT len = 0)
   {
       if (len == 0)
          Init(psz, Strlen(psz));
       else
          Init(psz, len);
    }

//-----------------------------------------------------------------------------
/*Copy constructor
 */
CStringStd::CStringStd(const CStringStd& src)
    {
       // do not copy itself
     if ( &src != this )
          Init(src.c_str(), src.length());
    }

//-----------------------------------------------------------------------------
/*Default constructor
 */
CStringStd::~CStringStd()
  {  clear(); }


//-----------------------------------------------------------------------------
/*
 */
  // Initialize member variables to default values
void CStringStd::Init(const TCHAR* psz, UINT len);

//-----------------------------------------------------------------------------
/*
 */
static const TCHAR* CStringStd::_Nullstr()
    {
         static const TCHAR c = TCHAR(0);
      return (&c);
      }

//-----------------------------------------------------------------------------
/*
 */
/// Returns a const ptr to the first element of the sequence (or just beyond the end of an empty sequence).
const TCHAR* CStringStd::begin() const
 { return m_psz; }

//-----------------------------------------------------------------------------
/*
 */
 /// Returns a ptr to the first element of the sequence (or just beyond the end of an empty sequence).
TCHAR* CStringStd::begin()
 { return m_psz; }

//-----------------------------------------------------------------------------
/*
 */
/// Returns the storage currently allocated to hold the controlled sequence, a value at least as large as size().
UINT CStringStd::capacity() const
{ return m_capacity-1; }

//-----------------------------------------------------------------------------
/*
 */
/// Returns a pointer to a nonmodifiable C string
const TCHAR* CStringStd::c_str() const
   // Calling any non-const member function for *this can invalidate the pointer.
  { return (m_psz == 0 ? _Nullstr() : m_psz); }

//-----------------------------------------------------------------------------
/*
 */
/// Returns true for an empty controlled sequence.
bool CStringStd::empty() const
 { return (length() == 0); }

//-----------------------------------------------------------------------------
/*
 */
/// Returns a const char ptr that points just beyond the end of the sequence.
const TCHAR* CStringStd::end() const
 { return &m_psz[m_len]; }

/// Returns a char ptr that points just beyond the end of the sequence.
TCHAR*  CStringStd::end()
 { return &m_psz[m_len]; }


//-----------------------------------------------------------------------------
/*
 */
/// Free the internal buffer and reset member variables.
void CStringStd::clear(bool bFreeBuffer = true)
  {
    // If bFreeBuffer is true the internal buffer will be freed, otherwise this function
    // will only reset internal members so the previously allocated memory can
    // be re-used. If the internal buffer is kept for future use, this class
    // guards against calls that make use of it. In other words, even if the
    // internal pointer m_psz is not NULL, calls to GetLength() or the
    // comparison functions for instance will behave like it is NULL.
    if (m_psz)
      if (bFreeBuffer)
      {
        delete m_psz;
        m_psz = NULL;
        m_capacity = 0;
      }
      else
      {
        m_psz[0] = _T('\0');
      }
    m_len = 0;
  }

//-----------------------------------------------------------------------------
/*
 */
/// Call clear()
void CStringStd::erase()
    { clear();  }

//-----------------------------------------------------------------------------
/*
 */
   /// Returns the length of the controlled sequence (same as size()).
UINT CStringStd::length() const
 {
      if ( m_len != 0 )
      assert(m_psz); // If m_len is set, m_psz MUST be valid!

    return m_len;
   }

//-----------------------------------------------------------------------------
/*
 */
/// Returns the length of the controlled sequence
UINT CStringStd::size() const
 { return length(); }


//-----------------------------------------------------------------------------
/*
 */
// Ensures that capacity() henceforth returns at least n.
void CStringStd::reserve(UINT n);

//-----------------------------------------------------------------------------
/*
 */
/**
  * Ensures that size() henceforth returns n.
 * If it must lengthen the controlled sequence, it appends elements with value c (MUST NOT BE '0').
 */
 void CStringStd::resize(UINT n, TCHAR ch = 'A');

//-----------------------------------------------------------------------------
/*
 */
 /// Replaces the sequence controlled by *this with the operand sequence, then returns *this.
CStringStd& CStringStd::assign(TCHAR ch)
    {
       TCHAR sz[2] = {ch, _T('\0')};
     return Assign(sz, 1);
    }

 /// Replaces the sequence controlled by *this with the operand sequence, then returns *this.
CStringStd& CStringStd::assign(const TCHAR* psz)
  {  return Assign(psz, Strlen(psz)); }

 /// Replaces the sequence controlled by *this with the operand sequence, then returns *this.
CStringStd& CStringStd::assign(const TCHAR* psz, UINT len)
  {  return Assign(psz, len); }

 /// Replaces the sequence controlled by *this with the operand sequence, then returns *this.
CStringStd& CStringStd::assign(const CStringStd& str)
  {
     // protect against assignment from self
     if ( this == &str )
       return *this;

    return Assign(str.c_str(), str.length());
  }

//-----------------------------------------------------------------------------
/*
 */
 // Each operator replaces the sequence controlled by *this with the operand sequence,
 // then returns *this.
/// assignment
CStringStd& CStringStd::operator= (TCHAR ch)
  {  return assign(ch); }

/// assignment
CStringStd& CStringStd::operator= (const TCHAR* psz)
  {  return assign(psz); }

/// assignment
CStringStd& CStringStd::operator= (const CStringStd& str)
    {
     // protect against assignment from self
     if ( this == &str )
       return *this;

      return assign(str);
    }

//-----------------------------------------------------------------------------
/*
 */
// -- Concatenation
 // Each operator appends the operand sequence to the end of the sequence
 // controlled by *this, then returns *this.
/// Concatenation
CStringStd& CStringStd::operator+= (TCHAR ch)
  {  return append(ch); }

/// Concatenation
CStringStd& CStringStd::operator+= (const TCHAR* psz)
  {  return append(psz, Strlen(psz)); }

/// Concatenation
CStringStd& CStringStd::operator+= (const CStringStd& str)
  {  return append(str); }

//-----------------------------------------------------------------------------
/*
 */
 // Each member function compares up to n0 elements of the controlled sequence
 // beginning with position p0, or the entire controlled sequence if these
 // arguments are not supplied, to the operand sequence. The function returns:
 //
 //  A negative value if the first differing element in the controlled sequence
 //       compares less than the corresponding element in the operand sequence
 //      (as determined by T::compare), or if the two have a common prefix but
 //      the operand sequence is longer.
 // Zero if the two compare equal element by element and are the same length.
 //
 // A positive value otherwise.


/// Compare this with str
 int CStringStd::compare(const CStringStd& str) const
    {  return (compare(0, m_len, str.c_str(), str.length())); }

/// Compare n0 elements of the controlled sequence beginning with position p0
int CStringStd::compare(UINT p0, UINT n0, const CStringStd& str) const
    {  return (compare(p0, n0, str, 0, npos)); }

/// Compare this with psz
 int CStringStd::compare(const TCHAR* psz) const
    {  return (compare(0, m_len, psz, Strlen(psz))); }

/// Compare n0 elements of the controlled sequence beginning with position p0
 int CStringStd::compare(UINT p0, UINT n0, const TCHAR* psz) const
    {  return (compare(p0, n0, psz, Strlen(psz))); }

/// Compare n0 elements of the controlled sequence beginning with position p0
int CStringStd::compare(UINT p0, UINT n0, const CStringStd& str, UINT pos, UINT n) const
  {
    assert(str.length() > pos);

    if (str.length() - pos < n)
      n = str.length() - pos;

    return (compare(p0, n0, str.c_str() + pos, n));
  }

int CStringStd::compare(UINT p0, UINT n0, const TCHAR* psz, UINT n) const;


//-----------------------------------------------------------------------------
/*
  * Finds the char in the controlled sequence beginning on or after position pos.
 *
  * If it succeeds, it returns the position where the matching subsequence begins.
  * Otherwise, the function returns npos.
 */
 UINT CStringStd::find(TCHAR ch, UINT pos = 0) const
    {
       if (pos<0 || m_len<pos)
          return npos;

       for (UINT i=pos; i<m_len; i++)
       {
          if (m_psz[i] == ch)
             return i;
       }
       return npos;
    }


//-----------------------------------------------------------------------------
/*
  * Substring.
 *
  * Returns an object whose controlled sequence is a copy of up to n elements of
 * the controlled sequence beginning at position pos.
 */
CStringStd CStringStd::substr(UINT pos = 0, UINT n = npos) const
    {
      if (pos < 0)
        pos = 0;

      if (m_len <= pos)
        return CStringStd(); // NULL string

      if (m_len - pos < n)
        n = m_len-pos;

      return CStringStd(&m_psz[pos], n);
    }

//-----------------------------------------------------------------------------
/*
 */
   // Concatenation - append new string segment to existing string
// Appends a single ASCII character
CStringStd& CStringStd::append(int n, TCHAR ch)
  {
    TCHAR sz[2] = {ch, _T('\0')};
   for (int i=0; i<n; i++)
     Append(sz, 1);

    return *this;
  }

// Appends a string of ASCII characters of length len
CStringStd& CStringStd::append(const TCHAR* psz, UINT len)
 {  return Append(psz, len);   }

// Appends a NULL terminated string of ASCII characters
CStringStd& CStringStd::append(const TCHAR* psz)
 {  return Append(psz, Strlen(psz));   }

/ Append str
CStringStd& CStringStd::append(const CStringStd& str)
 {  return Append(str.c_str(), str.size());   }


//-----------------------------------------------------------------------------
/*
 */
/// Returns a const reference to the element of the controlled sequence at position pos,
const TCHAR& CStringStd::at(UINT pos) const
   {
  // Be carefull! position must be valid!
      assert(0<=pos && pos<m_len);
    if (m_psz == 0)
      return (*_Nullstr());
    else
      return (m_psz[pos]);
   }

/// Returns a reference to the element of the controlled sequence at position pos,
TCHAR& CStringStd::at(UINT pos)
   {
      assert(0<=pos && pos<m_len);
    if (m_psz == 0)
      return (TCHAR&)(*_Nullstr());
    else
      return (m_psz[pos]);
   }

//-----------------------------------------------------------------------------
/*
 */
/// Returns a const reference to the element of the controlled sequence at position pos,
const TCHAR& CStringStd::operator[](UINT pos) const
  {  return at(pos);   }

/// Returns a reference to the element of the controlled sequence at position pos,
TCHAR& CStringStd::operator[](UINT pos)
  {  return at(pos);   }


//-----------------------------------------------------------------------------
/*
 */
// Set a pointer to an externally allocated C style string (allocated
  // with new/malloc) into object.
   // This class will assumes ownership of the buffer, deleting it as needed.
   // If you are attaching to tASN_OCTET_STR you should call detach
   // to take over the buffer before destructor of this object is called
   // The length of the allocated memory could be given (if known).
   // if zero M-capacity will be set to len.
CStringStd&  CStringStd::AttachBuffer(const TCHAR* psz, UINT len = 0, UINT allocatedMemorySize = 0);

//-----------------------------------------------------------------------------
/*
 */
// take over ownership of the internal buffer
TCHAR* CStringStd::DetachBuffer(UINT& len, UINT& capacity);

//-----------------------------------------------------------------------------
/*
 */
 // calculate length of the NULL terminated string
static UINT CStringStd::Strlen(const TCHAR* psz) ;

void CStringStd::Realloc(UINT n);

//-----------------------------------------------------------------------------
/*
 */
// Internal version of Assign()
CStringStd& CStringStd::Assign(const TCHAR* psz, UINT len);

//-----------------------------------------------------------------------------
/*
 */
// Internal version of append()
 // Appending overlapping string (i.e psz points somewhere
 // in the m_psz buffer) is not hanlded!! be careful
CStringStd&  CStringStd::Append(const TCHAR* psz, UINT len);

//-----------------------------------------------------------------------------
/*
 */
// Copy internal string if psz points within it
bool CStringStd::IsOverlapped(const TCHAR* psz)
   {
     if ( psz && psz!=_Nullstr() && m_psz && m_psz!=_Nullstr() && psz >= m_psz && psz <= m_psz + m_len )
     {
          return true;
     }
     return false;
   }






// STL - STL - STL - STL - STL - STL - STL - STL - STL - STL - STL -
#if defined(_STL_STRING_SUPPORT)

  /// Constructor
  CStringStd::CStringStd(const std::string& src)
      { Init(src.c_str(), src.length());  }

  /// Assignment
  CStringStd& CStringStd::assign(const std::string& str)
    {  return Assign(str.c_str(), str.length()); }

  /// Assignment
   CStringStd& CStringStd::operator= (const std::string& str)
    {  return Assign(str.c_str(), str.length()); }

  /// Concatenation
  CStringStd& CStringStd::operator+= (const std::string& str)
    {  return Append(str.c_str(), str.length()); }

  /// Append str
   CStringStd& CStringStd::append(const std::string& str)
    {  return Append(str.c_str(), str.length()); }

  /// Compare this with str
   int CStringStd::compare(const std::string& str) const
      {  return (compare(0, m_len, str.c_str()), str.length()); }

  /// Compare n0 elements of the controlled sequence beginning with position p0
  int CStringStd::compare(UINT p0, UINT n0, const std::string& str) const
      {  return (compare(p0, n0, str, 0, npos)); }

#endif // _STL_STRING_SUPPORT




/** \defgroup OPERATORS Operators */

/** \addtogroup BSTRING_OPERATORS CStringStd
 * @ingroup OPERATORS
 */

//@{

/// Concatenate
inline  CStringStd CStringStd::operator+(const CStringStd& lhs, const CStringStd& rhs)
  {  return CStringStd(lhs).append(rhs);   }
/// Concatenate
inline  CStringStd CStringStd::operator+(const CStringStd& lhs, const TCHAR *rhs)
{  return CStringStd(lhs).append(rhs, CStringStd::Strlen(rhs));   }
/// Concatenate
inline  CStringStd CStringStd::operator+(const CStringStd& lhs, TCHAR rhs)
  {  return CStringStd(lhs).append(rhs, 1);   }
/// Concatenate
inline  CStringStd CStringStd::operator+(const TCHAR *lhs, const CStringStd& rhs)
  {  return CStringStd(lhs).append(rhs);   }
/// Concatenate
inline  CStringStd CStringStd::operator+(TCHAR lhs, const CStringStd& rhs)
  {  return CStringStd(lhs).append(rhs);   }

//-----------------------------------------------------------------------------
/*
 */
//   zero if the strings are identical,
//     -1 if this object is less than psz,
//      1 if this object is greater than psz.

/// equal?
inline  bool CStringStd::operator==(const CStringStd& lhs, const CStringStd& rhs)
   {  return (lhs.compare(rhs)==0); }
/// equal?
inline  bool CStringStd::operator==(const CStringStd& lhs, const TCHAR *rhs)
   {  return (lhs.compare(rhs)==0); }
/// equal?
inline  bool CStringStd::operator==(const TCHAR *lhs, const CStringStd& rhs)
   {  return (rhs.compare(lhs)==0); }

//-----------------------------------------------------------------------------
/*
 */
/// not equal?
inline  bool CStringStd::operator!=(const CStringStd& lhs, const CStringStd& rhs)
   {  return (lhs.compare(rhs)!=0); }
/// not equal?
inline  bool CStringStd::operator!=(const CStringStd& lhs, const TCHAR *rhs)
   {  return (lhs.compare(rhs)!=0); }
/// not equal?
inline  bool CStringStd::operator!=(const TCHAR *lhs, const CStringStd& rhs)
   {  return (rhs.compare(lhs)!=0); }

//-----------------------------------------------------------------------------
/*
 */
/// less than?
inline  bool CStringStd::operator<(const CStringStd& lhs, const CStringStd& rhs)
   {  return (lhs.compare(rhs)<0); }
/// less than?
inline  bool CStringStd::operator<(const CStringStd& lhs, const TCHAR *rhs)
   {  return (lhs.compare(rhs)<0); }
/// less than?
inline  bool CStringStd::operator<(const TCHAR *lhs, const CStringStd& rhs)
  {  return (rhs.compare(lhs)>0); }  // ! rhs is used at the left side

//-----------------------------------------------------------------------------
/*
 */
/// greater than?
inline  bool CStringStd::operator>(const CStringStd& lhs, const CStringStd& rhs)
  {  return (lhs.compare(rhs)>0); }
/// greater than?
inline  bool CStringStd::operator>(const CStringStd& lhs, const TCHAR *rhs)
   {  return (lhs.compare(rhs)>0); }
/// greater than?
inline  bool CStringStd::operator>(const TCHAR *lhs, const CStringStd& rhs)
  {  return (rhs.compare(lhs)<0); }  // ! rhs is used at the left side

//-----------------------------------------------------------------------------
/*
 */
/// less than or equal?
inline  bool CStringStd::operator<=(const CStringStd& lhs, const CStringStd& rhs)
   {  return (lhs.compare(rhs)<=0); }
/// less than or equal?
inline  bool CStringStd::operator<=(const CStringStd& lhs, const TCHAR *rhs)
   {  return (lhs.compare(rhs)<=0); }
/// less than or equal?
inline  bool CStringStd::operator<=(const TCHAR *lhs, const CStringStd& rhs)
  {  return (rhs.compare(lhs)>=0); }  // ! rhs is used at the left side

//-----------------------------------------------------------------------------
/*
 */
/// greater than or equal?
inline  bool CStringStd::operator>=(const CStringStd& lhs, const CStringStd& rhs)
  {  return (lhs.compare(rhs)>=0); }
/// greater than or equal?
inline  bool CStringStd::operator>=(const CStringStd& lhs, const TCHAR *rhs)
  {  return (lhs.compare(rhs)>=0); }
/// greater than or equal?
inline  bool CStringStd::operator>=(const TCHAR *lhs, const CStringStd& rhs)
  {  return (rhs.compare(lhs)<=0); }  // ! rhs is used at the left side




#if defined(_STL_STRING_SUPPORT)

  /// Concatenate
  inline  CStringStd CStringStd::operator+(const CStringStd& lhs, const std::string& rhs)
    {  return CStringStd(lhs).append(rhs);   }
  /// Concatenate
  inline  CStringStd CStringStd::operator+(const std::string& lhs, const CStringStd& rhs)
    {  return CStringStd(lhs).append(rhs);   }

  // compare:
  //   zero if the strings are identical,
  //     -1 if this object is less than psz,
  //      1 if this object is greater than psz.

  /// Equal?
  inline  bool CStringStd::operator==(const CStringStd& lhs, const std::string& rhs)
    {  return (lhs.compare(rhs)==0); }
  /// Equal?
  inline  bool CStringStd::operator==(const std::string& lhs, const CStringStd& rhs)
    {  return (rhs.compare(lhs)==0); }

  /// not equal?
  inline  bool CStringStd::operator!=(const CStringStd& lhs, const std::string& rhs)
    {  return (lhs.compare(rhs)!=0); }
  /// not equal?
  inline  bool CStringStd::operator!=(const std::string& lhs, const CStringStd& rhs)
    {  return (rhs.compare(lhs)!=0); }

  /// less than?
  inline  bool CStringStd::operator<(const CStringStd& lhs, const std::string& rhs)
    {  return (lhs.compare(rhs)<0); }
  /// less than?
  inline  bool CStringStd::operator<(const std::string& lhs, const CStringStd& rhs)
    {  return (rhs.compare(lhs)>0); }  // ! rhs is used at the left side

  /// greater than?
  inline  bool CStringStd::operator>(const CStringStd& lhs, const std::string& rhs)
    {  return (lhs.compare(rhs)>0); }
  /// greater than?
  inline  bool CStringStd::operator>(const std::string& lhs, const CStringStd& rhs)
    {  return (rhs.compare(lhs)<0); }  // ! rhs is used at the left side

  /// less than or equal?
  inline  bool CStringStd::operator<=(const CStringStd& lhs, const std::string& rhs)
    {  return (lhs.compare(rhs)<=0); }
  /// less than or equal?
  inline  bool CStringStd::operator<=(const std::string& lhs, const CStringStd& rhs)
    {  return (rhs.compare(lhs)>=0); }  // ! rhs is used at the left side

  /// greater than or equal?
  inline  bool CStringStd::operator>=(const CStringStd& lhs, const std::string& rhs)
    {  return (lhs.compare(rhs)>=0); }
  /// greater than or equal?
  inline  bool CStringStd::operator>=(const std::string& lhs, const CStringStd& rhs)
    {  return (rhs.compare(lhs)<=0); }  // ! rhs is used at the left side


  // extractor
  inline  ostream& CStringStd::operator<<(ostream& out, const CStringStd& str)
  {
    out << str.c_str();
    return (out);
  }

#endif // _STL_STRING_SUPPORT

///////////////////////////////////////////////////////////////////////////////
#endif //_KSTRINGSTD_H_
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2005-04-25 21:27:01  Darko           Replaced types
 *       with stdtypes
 *  1    Biblioteka1.0         2003-09-05 14:20:09  Borislav Lukovic
 * $
 *  0  Borislav Lukovic
 *****************************************************************************/
