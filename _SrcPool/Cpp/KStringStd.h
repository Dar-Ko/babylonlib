/*$Workfile: KStringStd.h$: header file
  $Revision: 1$ $Date: 2003-09-05 13:20:09$
  $Author: Borislav Lukovic$

  Dynamic string class
  Copyright: B. Lukovic
  Borislav Lukovic 
 */

/*
 * Typedefs for basic datatypes
 * Author:  Borislav Lukovic 
 *  
 */

#include <stdio.h>  //FILE structure
#include <time.h>   //time_t typedef
#include <assert.h> //assert()

//#ifdef ND_WIN32
typedef char           tChar;          ///< 8-bit signed char
typedef unsigned char tUchar;         ///< 8-bit unsigned char
typedef unsigned char tUint8;         ///< 8-bit unsigned int
typedef unsigned short  tUint16;        ///< 16-bit unsigned int
typedef unsigned int  tUint32;        ///< 32-bit unsigned int
typedef unsigned long tUlong;         ///< unsigned long 
//typedef signed char tInt8;
typedef signed short     tInt16;         ///< 16-bit signed int
typedef signed int     tInt32;         ///< 32-bit signed int
typedef signed long   tLong;          ///< signed long 

typedef signed long     tInterlocked;   ///< signed long 
//typedef size_t          tSize;          ///< 32-bit unsigned int
typedef unsigned int    tSize;          ///< 32-bit unsigned int
typedef FILE            tFILE;          ///< FILE
typedef time_t          tTime;          ///< signed long
typedef struct timeb    tTimeB;         ///< struct {time; millitm; timezone; dstflag}

typedef wchar_t       tWchar;         ///< wide char
//@}


//#endif // ND_WIN32

#ifndef _BSTRING_H_INCLUDED_
#define _BSTRING_H_INCLUDED_


//=============================================================================
//CStringStd

/**
 * CStringStd encapsulates a dynamically allocated C style null-terminated string.
 *
 * This class's methods correspond to methods of STL's std::string class.
 */
class  CStringStd
{
public:
  /// Default constructor
  CStringStd()
    {  Init((tChar*)NULL, 0); }

  /// constructor (init string to character ch)
  CStringStd(tChar ch)
      {  
         tChar sz[2] = {ch, '\0'};
       Init(sz, 1); 
      }

  /// Construct with an existing ASCII string
  CStringStd(const tChar* psz, tSize len = 0)
     {  
         if (len == 0)
            Init(psz, Strlen(psz));   
         else
            Init(psz, len);   
      }

  /// Copy constructor
  CStringStd(const CStringStd& src)
      {
         // do not copy itself
       if ( &src != this )
            Init(src.c_str(), src.length());  
      } 

  /// non-virtual destructor !
  ~CStringStd()
    {  clear(); }


private:
  // Initialize member variables to default values
  void Init(const tChar* psz, tSize len);

private:
//  static const tChar* __cdecl _Nullstr()
  static const tChar* _Nullstr()
    {  
         static const tChar c = tChar(0);
      return (&c); 
      }

public:
   /// Returns a const ptr to the first element of the sequence (or just beyond the end of an empty sequence).
   const tChar* begin() const
    { return m_psz; }
   /// Returns a ptr to the first element of the sequence (or just beyond the end of an empty sequence).
   tChar* begin()
    { return m_psz; }

   /// Returns the storage currently allocated to hold the controlled sequence, a value at least as large as size().
   tSize capacity() const
   { return m_capacity-1; }  

   /// Returns a pointer to a nonmodifiable C string 

  const tChar* c_str() const
     // Calling any non-const member function for *this can invalidate the pointer.
    { return (m_psz == 0 ? _Nullstr() : m_psz); }

   // Returns a pointer to the first element of the sequence 
   // (or, for an empty sequence, a non-null pointer that cannot be dereferenced).
   //const tChar *data() const
  //  { return m_psz; }

   /// Returns true for an empty controlled sequence.
   bool empty() const
    { return (length() == 0); }

   /// Returns a const char ptr that points just beyond the end of the sequence.
   const tChar* end() const
    { return &m_psz[m_len]; }
   /// Returns a char ptr that points just beyond the end of the sequence.
   tChar*  end()
    { return &m_psz[m_len]; }


  /// Free the internal buffer and reset member variables. 
  void clear(bool bFreeBuffer = true)
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
          m_psz[0] = '\0';
        }
      m_len = 0;
    }

  /// Call clear()
  void erase()
    { clear();  }

   // Removes up to n elements of the string beginning at position p0, 
   // then returns *this.
   //CStringStd& erase(tSize p0 = 0, tSize n = npos)
   //   {}

   /// Returns the length of the controlled sequence (same as size()).
   tSize length() const
    { 
         if ( m_len != 0 )
         assert(m_psz); // If m_len is set, m_psz MUST be valid!

       return m_len;
      }  

   /// Returns the length of the controlled sequence
   tSize size() const
    { return length(); }


   /// Ensures that capacity() henceforth returns at least n.
   void reserve(tSize n);

  /**
    * Ensures that size() henceforth returns n. 
   * If it must lengthen the controlled sequence, it appends elements with value c (MUST NOT BE '0').
   */
   void resize(tSize n, tChar ch = 'A');

   /// Replaces the sequence controlled by *this with the operand sequence, then returns *this.
  CStringStd& assign(tChar ch)
      {
         tChar sz[2] = {ch, '\0'};
       return Assign(sz, 1); 
      }

   /// Replaces the sequence controlled by *this with the operand sequence, then returns *this.
  CStringStd& assign(const tChar* psz)
    {  return Assign(psz, Strlen(psz)); }

   /// Replaces the sequence controlled by *this with the operand sequence, then returns *this.
  CStringStd& assign(const tChar* psz, tSize len)
    {  return Assign(psz, len); }

   /// Replaces the sequence controlled by *this with the operand sequence, then returns *this.
  CStringStd& assign(const CStringStd& str)
    {  
       // protect against assignment from self
       if ( this == &str )
         return *this;

      return Assign(str.c_str(), str.length()); 
    }

   // --- operators ---

  // -- assignment 
   // Each operator replaces the sequence controlled by *this with the operand sequence, 
   // then returns *this.
  /// assignment
  CStringStd& operator= (tChar ch)
    {  return assign(ch); }

  /// assignment
  CStringStd& operator= (const tChar* psz)
    {  return assign(psz); }

  /// assignment
   CStringStd& operator= (const CStringStd& str)
      {  
       // protect against assignment from self
       if ( this == &str )
         return *this;

      return assign(str);  
    } 
   
  // -- Concatenation
   // Each operator appends the operand sequence to the end of the sequence 
   // controlled by *this, then returns *this.
  /// Concatenation
  CStringStd& operator+= (tChar ch)
    {  return append(ch); }

  /// Concatenation
  CStringStd& operator+= (const tChar* psz)
    {  return append(psz, Strlen(psz)); }

  /// Concatenation
  CStringStd& operator+= (const CStringStd& str)
    {  return append(str); }

   // -- comparison
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
   tInt32 compare(const CStringStd& str) const
      {  return (compare(0, m_len, str.c_str(), str.length())); }  

  /// Compare n0 elements of the controlled sequence beginning with position p0   
  tInt32 compare(tSize p0, tSize n0, const CStringStd& str) const
      {  return (compare(p0, n0, str, 0, npos)); }  

  /// Compare this with psz
   tInt32 compare(const tChar* psz) const
      {  return (compare(0, m_len, psz, Strlen(psz))); }

  /// Compare n0 elements of the controlled sequence beginning with position p0   
   tInt32 compare(tSize p0, tSize n0, const tChar* psz) const
      {  return (compare(p0, n0, psz, Strlen(psz))); }

  /// Compare n0 elements of the controlled sequence beginning with position p0   
  tInt32 compare(tSize p0, tSize n0, const CStringStd& str, tSize pos, tSize n) const
    {
      assert(str.length() > pos);

      if (str.length() - pos < n)
        n = str.length() - pos;

      return (compare(p0, n0, str.c_str() + pos, n));
    }

  tInt32 compare(tSize p0, tSize n0, const tChar* psz, tSize n) const;


  /**
    * Finds the char in the controlled sequence beginning on or after position pos.
   * 
    * If it succeeds, it returns the position where the matching subsequence begins. 
    * Otherwise, the function returns npos.
   */
   tSize find(tChar ch, tSize pos = 0) const
      {  
         if (pos<0 || m_len<pos)
            return npos;

         for (tSize i=pos; i<m_len; i++)
         {
            if (m_psz[i] == ch)
               return i;
         }
         return npos;
      }

   //tSize find(const char *psz, tSize pos = 0) const
   //   {  return ???;  }

   //tSize find(const CStringStd& str, tSize pos = 0) const
   //   {  return ???;  }

  /**
    * Substring.
   * 
    * Returns an object whose controlled sequence is a copy of up to n elements of 
   * the controlled sequence beginning at position pos.
   */
  CStringStd substr(tSize pos = 0, tSize n = npos) const
    {
      if (pos < 0) 
        pos = 0;

      if (m_len <= pos)
        return CStringStd(); // NULL string

      if (m_len - pos < n)
        n = m_len-pos;
      
      return CStringStd(&m_psz[pos], n);
    }

public:

   // Concatenation - append new string segment to existing string

  /// Appends a single ASCII character 
  CStringStd& append(tInt32 n, tChar ch)
     {
       tChar sz[2] = {ch, '\0'};
      for (tInt32 i=0; i<n; i++)
        Append(sz, 1);

       return *this;
     }
   
  /// Appends a string of ASCII characters of length len
   CStringStd& append(const tChar* psz, tSize len)
    {  return Append(psz, len);   }

  /// Appends a NULL terminated string of ASCII characters
   CStringStd& append(const tChar* psz)
    {  return Append(psz, Strlen(psz));   }
  
  // Append str
   CStringStd& append(const CStringStd& str)
    {  return Append(str.c_str(), str.size());   }


   /// Returns a const reference to the element of the controlled sequence at position pos, 
   const tChar& at(tSize pos) const
      {
     // Be carefull! position must be valid!
         assert(0<=pos && pos<m_len);
       if (m_psz == 0)
         return (*_Nullstr());
       else
         return (m_psz[pos]); 
      }

   /// Returns a reference to the element of the controlled sequence at position pos, 
   tChar& at(tSize pos)
      {
         assert(0<=pos && pos<m_len);
       if (m_psz == 0)
         return (tChar&)(*_Nullstr());
       else
         return (m_psz[pos]);
      }

   /// Returns a const reference to the element of the controlled sequence at position pos, 
   const tChar& operator[](tSize pos) const
     {  return at(pos);   }

   /// Returns a reference to the element of the controlled sequence at position pos, 
   tChar& operator[](tSize pos) 
     {  return at(pos);   }


  // Set a pointer to an externally allocated C style string (allocated
  // with new/malloc) into object. 
   // This class will assumes ownership of the buffer, deleting it as needed.
   // If you are attaching to tASN_OCTET_STR you should call detach
   // to take over the buffer before destructor of this object is called
   // The length of the allocated memory could be given (if known).
   // if zero M-capacity will be set to len.
  CStringStd&  AttachBuffer(const tChar* psz, tSize len = 0, tSize allocatedMemorySize = 0);

  // take over ownership of the internal buffer
  tChar* DetachBuffer(tSize& len, tSize& capacity);

public:

   // calculate length of the NULL terminated string
  static tSize Strlen(const tChar* psz) ;

protected:

  void Realloc(tSize n);

  // Internal version of Assign()
  CStringStd& Assign(const tChar* psz, tSize len);

  // Internal version of append()
   // Appending overlapping string (i.e psz points somewhere 
   // in the m_psz buffer) is not hanlded!! be careful
  CStringStd&  Append(const tChar* psz, tSize len);

  // Copy internal string if psz points within it
  bool IsOverlapped(const tChar* psz)
     {
       if ( psz && psz!=_Nullstr() && m_psz && m_psz!=_Nullstr() && psz >= m_psz && psz <= m_psz + m_len )
       {
            return true;
       }
       return false;
     }

// data
protected:
  tChar* m_psz;
  tSize  m_len;
  tSize  m_capacity;

public:
   static const tSize npos;





// STL - STL - STL - STL - STL - STL - STL - STL - STL - STL - STL - 
#if defined(_STL_STRING_SUPPORT)

public:
  /// Constructor
  CStringStd(const std::string& src)
      { Init(src.c_str(), src.length());  } 

  /// Assignment
  CStringStd& assign(const std::string& str)
    {  return Assign(str.c_str(), str.length()); }

  /// Assignment
   CStringStd& operator= (const std::string& str)
    {  return Assign(str.c_str(), str.length()); }

  /// Concatenation
  CStringStd& operator+= (const std::string& str)
    {  return Append(str.c_str(), str.length()); }

  /// Append str
   CStringStd& append(const std::string& str)
    {  return Append(str.c_str(), str.length()); }

  /// Compare this with str
   tInt32 compare(const std::string& str) const
      {  return (compare(0, m_len, str.c_str()), str.length()); }  

  /// Compare n0 elements of the controlled sequence beginning with position p0   
  tInt32 compare(tSize p0, tSize n0, const std::string& str) const
      {  return (compare(p0, n0, str, 0, npos)); }  

#endif // _STL_STRING_SUPPORT 

};





/** \defgroup OPERATORS Operators */

/** \addtogroup BSTRING_OPERATORS CStringStd 
 * @ingroup OPERATORS
 */

//@{ 

/// Concatenate
inline  CStringStd operator+(const CStringStd& lhs, const CStringStd& rhs)
  {  return CStringStd(lhs).append(rhs);   }
/// Concatenate
inline  CStringStd operator+(const CStringStd& lhs, const tChar *rhs)
{  return CStringStd(lhs).append(rhs, CStringStd::Strlen(rhs));   }
/// Concatenate
inline  CStringStd operator+(const CStringStd& lhs, tChar rhs)
  {  return CStringStd(lhs).append(rhs, 1);   }
/// Concatenate
inline  CStringStd operator+(const tChar *lhs, const CStringStd& rhs)
  {  return CStringStd(lhs).append(rhs);   }
/// Concatenate
inline  CStringStd operator+(tChar lhs, const CStringStd& rhs)
  {  return CStringStd(lhs).append(rhs);   }

// compare:
//   zero if the strings are identical, 
//     -1 if this object is less than psz, 
//      1 if this object is greater than psz. 

/// equal?
inline  bool operator==(const CStringStd& lhs, const CStringStd& rhs)
   {  return (lhs.compare(rhs)==0); }
/// equal?
inline  bool operator==(const CStringStd& lhs, const tChar *rhs)
   {  return (lhs.compare(rhs)==0); }
/// equal?
inline  bool operator==(const tChar *lhs, const CStringStd& rhs)
   {  return (rhs.compare(lhs)==0); }

/// not equal?
inline  bool operator!=(const CStringStd& lhs, const CStringStd& rhs)
   {  return (lhs.compare(rhs)!=0); }
/// not equal?
inline  bool operator!=(const CStringStd& lhs, const tChar *rhs)
   {  return (lhs.compare(rhs)!=0); }
/// not equal?
inline  bool operator!=(const tChar *lhs, const CStringStd& rhs)
   {  return (rhs.compare(lhs)!=0); }

/// less than?
inline  bool operator<(const CStringStd& lhs, const CStringStd& rhs)
   {  return (lhs.compare(rhs)<0); }
/// less than?
inline  bool operator<(const CStringStd& lhs, const tChar *rhs)
   {  return (lhs.compare(rhs)<0); }
/// less than?
inline  bool operator<(const tChar *lhs, const CStringStd& rhs)
  {  return (rhs.compare(lhs)>0); }  // ! rhs is used at the left side

/// greater than?
inline  bool operator>(const CStringStd& lhs, const CStringStd& rhs)
  {  return (lhs.compare(rhs)>0); }
/// greater than?
inline  bool operator>(const CStringStd& lhs, const tChar *rhs)
   {  return (lhs.compare(rhs)>0); }
/// greater than?
inline  bool operator>(const tChar *lhs, const CStringStd& rhs)
  {  return (rhs.compare(lhs)<0); }  // ! rhs is used at the left side

/// less than or equal?
inline  bool operator<=(const CStringStd& lhs, const CStringStd& rhs)
   {  return (lhs.compare(rhs)<=0); }
/// less than or equal?
inline  bool operator<=(const CStringStd& lhs, const tChar *rhs)
   {  return (lhs.compare(rhs)<=0); }
/// less than or equal?
inline  bool operator<=(const tChar *lhs, const CStringStd& rhs)
  {  return (rhs.compare(lhs)>=0); }  // ! rhs is used at the left side

/// greater than or equal?
inline  bool operator>=(const CStringStd& lhs, const CStringStd& rhs)
  {  return (lhs.compare(rhs)>=0); } 
/// greater than or equal?
inline  bool operator>=(const CStringStd& lhs, const tChar *rhs)
  {  return (lhs.compare(rhs)>=0); }
/// greater than or equal?
inline  bool operator>=(const tChar *lhs, const CStringStd& rhs)
  {  return (rhs.compare(lhs)<=0); }  // ! rhs is used at the left side




#if defined(_STL_STRING_SUPPORT)

  /// Concatenate
  inline  CStringStd operator+(const CStringStd& lhs, const std::string& rhs)
    {  return CStringStd(lhs).append(rhs);   }
  /// Concatenate
  inline  CStringStd operator+(const std::string& lhs, const CStringStd& rhs)
    {  return CStringStd(lhs).append(rhs);   }

  // compare:
  //   zero if the strings are identical, 
  //     -1 if this object is less than psz, 
  //      1 if this object is greater than psz. 

  /// Equal?
  inline  bool operator==(const CStringStd& lhs, const std::string& rhs)
    {  return (lhs.compare(rhs)==0); }
  /// Equal?
  inline  bool operator==(const std::string& lhs, const CStringStd& rhs)
    {  return (rhs.compare(lhs)==0); }

  /// not equal?
  inline  bool operator!=(const CStringStd& lhs, const std::string& rhs)
    {  return (lhs.compare(rhs)!=0); }
  /// not equal?
  inline  bool operator!=(const std::string& lhs, const CStringStd& rhs)
    {  return (rhs.compare(lhs)!=0); }

  /// less than?
  inline  bool operator<(const CStringStd& lhs, const std::string& rhs)
    {  return (lhs.compare(rhs)<0); }
  /// less than?
  inline  bool operator<(const std::string& lhs, const CStringStd& rhs)
    {  return (rhs.compare(lhs)>0); }  // ! rhs is used at the left side

  /// greater than?
  inline  bool operator>(const CStringStd& lhs, const std::string& rhs)
    {  return (lhs.compare(rhs)>0); } 
  /// greater than?
  inline  bool operator>(const std::string& lhs, const CStringStd& rhs)
    {  return (rhs.compare(lhs)<0); }  // ! rhs is used at the left side

  /// less than or equal?
  inline  bool operator<=(const CStringStd& lhs, const std::string& rhs)
    {  return (lhs.compare(rhs)<=0); }
  /// less than or equal?
  inline  bool operator<=(const std::string& lhs, const CStringStd& rhs)
    {  return (rhs.compare(lhs)>=0); }  // ! rhs is used at the left side

  /// greater than or equal?
  inline  bool operator>=(const CStringStd& lhs, const std::string& rhs)
    {  return (lhs.compare(rhs)>=0); }
  /// greater than or equal?
  inline  bool operator>=(const std::string& lhs, const CStringStd& rhs)
    {  return (rhs.compare(lhs)<=0); }  // ! rhs is used at the left side


  // extractor
  inline  ostream& operator<<(ostream& out, const CStringStd& str)
  {
    out << str.c_str();
    return (out);
  }

#endif // _STL_STRING_SUPPORT

//@} 



///////////////////////////////////////////////////////////////////////////////
#endif //_BSTRING_H_INCLUDED_
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2003-09-05 13:20:09  Borislav Lukovic 
 * $
 *  0  Borislav Lukovic 
 *****************************************************************************/
