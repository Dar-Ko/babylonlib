/*$Workfile: KStringStd.cpp$: implementation file
  $Revision: 1$ $Date: 2003-09-05 13:20:08$
  $Author: Borislav Lukovic$

  Dynamic string class
  Copyright: B. Lukovic
  Borislav Lukovic 
 */

#include <memory.h> //memset()

#include "KStringStd.h" //CStringStd class


//-------------------------------------------------------------
//
#define BSTRING_GROW_BY 2

//-------------------------------------------------------------
//
const tSize CStringStd::npos = (tSize)(-1);

//-------------------------------------------------------------
// Initialize member variables to default values
void CStringStd::Init(const tChar* psz, tSize len)
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
void CStringStd::reserve(tSize n)
{
   assert(n != 0);
  clear(); 

   tSize newCapacity = n+1;

   tChar* pNewSZ = new tChar[newCapacity];
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
void CStringStd::Realloc(tSize n)
{
   if (n <= m_len)
      return; // already big enough

   // extend 
   if (m_capacity < n+1)
   {
      tSize newCapacity = m_capacity;

    if (newCapacity==0)
      newCapacity = BSTRING_GROW_BY; 

      while (newCapacity < n + 1)
         newCapacity *= BSTRING_GROW_BY;

      tChar* pNewSZ = new tChar[newCapacity];
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
void CStringStd::resize(tSize n, tChar ch)
{
   if (n == m_len)
      return;

   if (n < m_len)
   {
      // shorten the string, no reallocation
      m_psz[n] = '\0';
      m_len = n;
   }
   else
   {
    Realloc(n);
    if (m_capacity < n)
      return; // reallocation did not succeed

     // fill with ch
     for (tSize i=0; i<n; i++)
       m_psz[m_len+i] = ch;

      // adjust length
     m_psz[m_len+n] = '\0';
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
tInt32 CStringStd::compare(tSize p0, tSize n0, const tChar* psz, tSize n) const
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

   tSize comparisonLen = n0 < n ? n0 : n;
  tInt32 answer = 0; // assume both are equeal
   for (tSize i=0; i<comparisonLen; i++)
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
CStringStd& CStringStd::AttachBuffer(const tChar* psz, tSize len, tSize allocatedMemorySize)
{
  // Free current string.
  clear();

  // Save pointer
  if ( psz )
  {
    // Set member variables
    m_psz = const_cast<tChar *>(psz);
      m_len = (len == 0) ? Strlen(psz) : len;
    m_capacity = (allocatedMemorySize == 0) ? len : allocatedMemorySize;;
  }
  return *this;
}

//-------------------------------------------------------------
// take over ownership of the internal buffer
tChar* CStringStd::DetachBuffer(tSize& len, tSize& capacity)
{
   len = m_len;
   capacity = m_capacity;
   tChar* pszDetach = m_psz;

   // reset members
   m_psz = NULL;
   m_len = 0;
   m_capacity = 0;

   return pszDetach;
}



//-------------------------------------------------------------
// Internal version of Assign()
CStringStd& CStringStd::Assign(const tChar* psz, tSize len)
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
      tSize i;

      for (i=0; i<len; i++)
        m_psz[i] = psz[i];

      m_psz[i] = '\0';

      // adjust length, (confirm that there is no NULL char in the string
      i = 0;
      while ( psz[i] != 0  &&  i < len )
        i++;

      m_len = i;
      m_psz[m_len] = '\0';
    }
   }
  return *this;
}


//-------------------------------------------------------------
// Internal version of append()
// Appending overlapping string (i.e psz points somewhere 
// in the m_psz buffer) is not hanlded!! be careful
CStringStd& CStringStd::Append(const tChar* psz, tSize len)
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
      for (tSize i=0; i<len; i++)
        m_psz[m_len+i] = psz[i];

      // adjust length
      m_len += len;
      // and terminate string
      m_psz[m_len] = '\0';
      }
   }

  return *this;
}



// calculate length of the NULL terminated string
tSize CStringStd::Strlen(const tChar* psz) 
{
   tSize len = 0;
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
