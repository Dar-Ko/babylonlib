/*$Workfile: KStringStd.cpp$: implementation file
  $Revision: 2$ $Date: 2005-04-25 20:26:59$
  $Author: Darko$

  Dynamic string class
  Copyright: B. Lukovic
  Borislav Lukovic
 */

// Group=Strings

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
/*Replaces library header file names with the compiler's aliases*/
#ifdef _USE_STD_HEADERS
  #ifdef _WIN32
    #ifdef _MSC_VER //Micorsoft C++ compiler
      #ifdef _UNICODE
        #ifndef UNICODE
          //To enable Unicode for some Microsoft Visual C/C++ header files,
          //the UNICODE definition is required
          #define UNICODE
        #endif
      #endif
      #pragma include_alias("KTChar.h", "wtypes.h")
    #endif  //_MSC_VER
  #endif  //_WIN32

#endif  //_USE_STD_HEADERS


#include <memory.h> //memset()
#include "KTChar.h" /*LPCTSTR typedef*/
#include "KStringStd.h" //CStringStd class

//-------------------------------------------------------------
//
const int BSTRING_GROW_BY 2

//-------------------------------------------------------------
//
const UINT CStringStd::npos = (UINT)(-1);

//-------------------------------------------------------------
// Initialize member variables to default values
void CStringStd::Init(const TCHAR* psz, UINT len)
{
   m_psz      = NULL;
   m_len      = 0;
   m_capacity = 0;

  // Copy string too
  if ( psz && psz!=_Nullstr() && len>0 )
   {
      Assign(psz, len);
   }
}

//-------------------------------------------------------------
/**
 * Ensures that capacity() henceforth returns at least n.
 */
void CStringStd::reserve(UINT n)
{
   assert(n != 0);
  clear();

   UINT newCapacity = n+1;

   TCHAR* pNewSZ = new TCHAR[newCapacity];
  if (!pNewSZ)
    return; //! couldn't allocate more memory

   m_capacity = newCapacity;
   //NDMemset(pNewSZ, 0, m_capacity);
memset(pNewSZ, 0, m_capacity);

  m_psz = pNewSZ;
  pNewSZ = NULL;
}

//-------------------------------------------------------------
/*
 * Realloc so capacity is big enough to receive string of length n
 * Does not shorten the buffer!
 */
void CStringStd::Realloc(UINT n)
{
   if (n <= m_len)
      return; // already big enough

   // extend
   if (m_capacity < n+1)
   {
      UINT newCapacity = m_capacity;

    if (newCapacity==0)
      newCapacity = BSTRING_GROW_BY;

      while (newCapacity < n + 1)
         newCapacity *= BSTRING_GROW_BY;

      TCHAR* pNewSZ = new TCHAR[newCapacity];
    if (!pNewSZ)
      return; //! couldn't allocate more memory

      m_capacity = newCapacity;
//      NDMemset(pNewSZ, 0, m_capacity);
      memset(pNewSZ, 0, m_capacity);

     // copy values to new list and free the old one
      if (m_psz)
      {
//         NDMemcpy(pNewSZ, m_psz, m_len);
         memcpy(pNewSZ, m_psz, m_len);
         delete m_psz;
      }
     // and reassign
     m_psz = pNewSZ;
     pNewSZ = NULL;
   }
}



//-------------------------------------------------------------
/**
 * Ensures that size() henceforth returns n.
 * If it must lengthen the controlled sequence, it appends elements with value ch (MUST NOT BE '0').
 */
void CStringStd::resize(UINT n, TCHAR ch)
{
   if (n == m_len)
      return;

   if (n < m_len)
   {
      // shorten the string, no reallocation
      m_psz[n] = _T('\0');
      m_len = n;
   }
   else
   {
    Realloc(n);
    if (m_capacity < n)
      return; // reallocation did not succeed

     // fill with ch
     for (UINT i=0; i<n; i++)
       m_psz[m_len+i] = ch;

      // adjust length
     m_psz[m_len+n] = _T('\0');
      m_len += n + 1;
   }
}


//-------------------------------------------------------------
/**
 * Compare n0 elements of the controlled sequence beginning with position p0
 * Case sensitive comparison.
 * @return
 *   zero if the strings are identical;
 *     -1 if this object is less than psz;
 *      1 if this object is greater than psz.
 */
int CStringStd::compare(UINT p0, UINT n0, const TCHAR* psz, UINT n) const
{
  if ( !m_psz || m_psz==_Nullstr() || !psz || psz==_Nullstr() ) // at least one string is NULL
  {
    if ( m_psz && m_psz!=_Nullstr() ) // psz is NULL
        return 1;
    else if ( psz && psz!=_Nullstr() ) // this object is null
      return -1;

    return 0; // both are NULL
  }

  assert(m_len > p0);

  if (m_len - p0 < n0)
    n0 = m_len - p0;

   UINT comparisonLen = n0 < n ? n0 : n;
  int answer = 0; // assume both are equeal
   for (UINT i=0; i<comparisonLen; i++)
   {
      if (m_psz[i+p0] != psz[i])
    {
      answer = ((m_psz[i+p0] < psz[i]) ? -1 : +1);
      break;
    }
   }

  if (answer != 0)
    return answer;

  // portion compared is equal
  if (n0 < n)
    return -1; // less than
  else if (n0 == n)
    return  0;
  else
    return +1;
}


//-------------------------------------------------------------
// Set a pointer to an externally allocated C style string (allocated
// with new/malloc) into object.
// This class will assumes ownership of the buffer, deleting it as needed.
// If you are attaching to tASN_OCTET_STR you should call detach
// to take over the buffer before destructor of this object is called
// The length of the allocated memory could be given (if known).
// if zero M-capacity will be set to len.
CStringStd& CStringStd::AttachBuffer(const TCHAR* psz, UINT len, UINT allocatedMemorySize)
{
  // Free current string.
  clear();

  // Save pointer
  if ( psz )
  {
    // Set member variables
    m_psz = const_cast<TCHAR *>(psz);
      m_len = (len == 0) ? Strlen(psz) : len;
    m_capacity = (allocatedMemorySize == 0) ? len : allocatedMemorySize;;
  }
  return *this;
}

//-------------------------------------------------------------
// take over ownership of the internal buffer
TCHAR* CStringStd::DetachBuffer(UINT& len, UINT& capacity)
{
   len = m_len;
   capacity = m_capacity;
   TCHAR* pszDetach = m_psz;

   // reset members
   m_psz = NULL;
   m_len = 0;
   m_capacity = 0;

   return pszDetach;
}



//-------------------------------------------------------------
// Internal version of Assign()
CStringStd& CStringStd::Assign(const TCHAR* psz, UINT len)
{
  // Anything to do?
  if ( psz==NULL || psz==_Nullstr() || len==0)
   {
      clear(true); // reset all member variables
      return *this;
   }

  // Check overlapping
   if ( IsOverlapped(psz) )
   {
      // make copy of psz pointed buffer
      CStringStd strToAppend(psz, len);
      return Assign(strToAppend.c_str(), strToAppend.length());
   }
   else
   {
    Realloc(len+1);
    if (m_capacity >= len+1)
    {
      UINT i;

      for (i=0; i<len; i++)
        m_psz[i] = psz[i];

      m_psz[i] = _T('\0');

      // adjust length, (confirm that there is no NULL char in the string
      i = 0;
      while ( psz[i] != 0  &&  i < len )
        i++;

      m_len = i;
      m_psz[m_len] = _T('\0');
    }
   }
  return *this;
}


//-------------------------------------------------------------
// Internal version of append()
// Appending overlapping string (i.e psz points somewhere
// in the m_psz buffer) is not hanlded!! be careful
CStringStd& CStringStd::Append(const TCHAR* psz, UINT len)
{
  // Anything to do?
  if ( psz==NULL || psz==_Nullstr() )
      return *this;

  // Check overlapping
   if ( IsOverlapped(psz) )
   {
      // make copy of psz pointed buffer
      CStringStd strToAppend(psz, len);
      return Append(strToAppend.c_str(), strToAppend.length());
   }
   else
   {
      // regular appending (do not forget one char for ending NULL
    Realloc(m_len+len+1);
    if (m_capacity >= m_len+len+1)
      {
      // append psz
      for (UINT i=0; i<len; i++)
        m_psz[m_len+i] = psz[i];

      // adjust length
      m_len += len;
      // and terminate string
      m_psz[m_len] = _T('\0');
      }
   }

  return *this;
}



// calculate length of the NULL terminated string
UINT CStringStd::Strlen(const TCHAR* psz)
{
   UINT len = 0;
   while (psz && *(psz+len) != 0)
      len++;
   return len;
}



///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2003-09-05 13:20:08  Borislav Lukovic
 * $
 *  0  Borislav Lukovic
 *****************************************************************************/
