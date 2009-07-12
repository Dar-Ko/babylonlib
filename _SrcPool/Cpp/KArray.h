/*$RCSfile: KArray.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/07/12 05:38:09 $
  $Author: ddarko $

  Dynamic array of objects.
  Copyright: CommonSoft Inc
  2009-07-12 Darko Kolakovic
 */

#ifndef _KARRAY_H_
    //$RCSfile: KArray.h,v $ sentry
  #define _KARRAY_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef __cplusplus

#if defined (_USE_STL)
  #include <string>     //std::string template
  #include <vector>     //std::vector template

#elif defined (_USE_MFC) //Microsoft Fundation Classes Library (MFC)
  #include <afxtempl.h>
#elif defined (_USE_ATL) //Microsoft Active Template Library (ATL)
#else
//TODO:
/*The CArray class supports arrays that are are similar to C arrays, but can dynamically shrink and grow as necessary.

Array indexes always start at position 0. You can decide whether to fix the upper bound or allow the array to expand when you add elements past the current bound. Memory is allocated contiguously to the upper bound, even if some elements are null.

As with a C array, the access time for a CArray indexed element is constant and is independent of the array size.
*/
  template<class TYPE, //the type of objects stored in the array
  class ARG_TYPE = const TYPE& //argument type used to access objects stored
  //in the array. Often a reference to TYPE.
  >
  class CArray
  {
  public:
  // Construction
    CArray();

  // Attributes
    INT_PTR GetSize() const;
    INT_PTR GetCount() const;
    BOOL IsEmpty() const;
    INT_PTR GetUpperBound() const;
    void SetSize(INT_PTR nNewSize, INT_PTR nGrowBy = -1);

  // Operations
    // Clean up
    void FreeExtra();
    void RemoveAll();

    // Accessing elements
    const TYPE& GetAt(INT_PTR nIndex) const;
    TYPE& GetAt(INT_PTR nIndex);
    void SetAt(INT_PTR nIndex, ARG_TYPE newElement);
    const TYPE& ElementAt(INT_PTR nIndex) const;
    TYPE& ElementAt(INT_PTR nIndex);

    // Direct Access to the element data (may return NULL)
    const TYPE* GetData() const;
    TYPE* GetData();

    // Potentially growing the array
    void SetAtGrow(INT_PTR nIndex, ARG_TYPE newElement);
    INT_PTR Add(ARG_TYPE newElement);
    INT_PTR Append(const CArray& src);
    void Copy(const CArray& src);

    // overloaded operator helpers
    const TYPE& operator[](INT_PTR nIndex) const;
    TYPE& operator[](INT_PTR nIndex);

    // Operations that move elements around
    void InsertAt(INT_PTR nIndex, ARG_TYPE newElement, INT_PTR nCount = 1);
    void RemoveAt(INT_PTR nIndex, INT_PTR nCount = 1);
    void InsertAt(INT_PTR nStartIndex, CArray* pNewArray);

  // Implementation
  protected:
    TYPE* m_pData;   // the actual array of data
    INT_PTR m_nSize;     // # of elements (upperBound - 1)
    INT_PTR m_nMaxSize;  // max allocated
    INT_PTR m_nGrowBy;   // grow amount

  public:
    ~CArray();
    void Serialize(CArchive&);
  #ifdef _DEBUG
    void Dump(CDumpContext&) const;
    void AssertValid() const;
  #endif
  };

/////////////////////////////////////////////////////////////////////////////
// CArray<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
AFX_INLINE INT_PTR CArray<TYPE, ARG_TYPE>::GetSize() const
  { return m_nSize; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE INT_PTR CArray<TYPE, ARG_TYPE>::GetCount() const
  { return m_nSize; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE BOOL CArray<TYPE, ARG_TYPE>::IsEmpty() const
  { return m_nSize == 0; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE INT_PTR CArray<TYPE, ARG_TYPE>::GetUpperBound() const
  { return m_nSize-1; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE void CArray<TYPE, ARG_TYPE>::RemoveAll()
  { SetSize(0, -1); }
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE& CArray<TYPE, ARG_TYPE>::GetAt(INT_PTR nIndex)
{
  ASSERT(nIndex >= 0 && nIndex < m_nSize);
  if(nIndex >= 0 && nIndex < m_nSize)
    return m_pData[nIndex];
  AfxThrowInvalidArgException();
}
template<class TYPE, class ARG_TYPE>
AFX_INLINE const TYPE& CArray<TYPE, ARG_TYPE>::GetAt(INT_PTR nIndex) const
{
  ASSERT(nIndex >= 0 && nIndex < m_nSize);
  if(nIndex >= 0 && nIndex < m_nSize)
    return m_pData[nIndex];
  AfxThrowInvalidArgException();
}
template<class TYPE, class ARG_TYPE>
AFX_INLINE void CArray<TYPE, ARG_TYPE>::SetAt(INT_PTR nIndex, ARG_TYPE newElement)
{
  ASSERT(nIndex >= 0 && nIndex < m_nSize);
  if(nIndex >= 0 && nIndex < m_nSize)
    m_pData[nIndex] = newElement;
  else
    AfxThrowInvalidArgException();
}
template<class TYPE, class ARG_TYPE>
AFX_INLINE const TYPE& CArray<TYPE, ARG_TYPE>::ElementAt(INT_PTR nIndex) const
{
  ASSERT(nIndex >= 0 && nIndex < m_nSize);
  if(nIndex >= 0 && nIndex < m_nSize)
    return m_pData[nIndex];
  AfxThrowInvalidArgException();
}
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE& CArray<TYPE, ARG_TYPE>::ElementAt(INT_PTR nIndex)
{
  ASSERT(nIndex >= 0 && nIndex < m_nSize);
  if(nIndex >= 0 && nIndex < m_nSize)
    return m_pData[nIndex];
  AfxThrowInvalidArgException();
}
template<class TYPE, class ARG_TYPE>
AFX_INLINE const TYPE* CArray<TYPE, ARG_TYPE>::GetData() const
  { return (const TYPE*)m_pData; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE* CArray<TYPE, ARG_TYPE>::GetData()
  { return (TYPE*)m_pData; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE INT_PTR CArray<TYPE, ARG_TYPE>::Add(ARG_TYPE newElement)
  { INT_PTR nIndex = m_nSize;
    SetAtGrow(nIndex, newElement);
    return nIndex; }
template<class TYPE, class ARG_TYPE>
AFX_INLINE const TYPE& CArray<TYPE, ARG_TYPE>::operator[](INT_PTR nIndex) const
  { return GetAt(nIndex); }
template<class TYPE, class ARG_TYPE>
AFX_INLINE TYPE& CArray<TYPE, ARG_TYPE>::operator[](INT_PTR nIndex)
  { return ElementAt(nIndex); }

/////////////////////////////////////////////////////////////////////////////
// CArray<TYPE, ARG_TYPE> out-of-line functions

template<class TYPE, class ARG_TYPE>
CArray<TYPE, ARG_TYPE>::CArray()
{
  m_pData = NULL;
  m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

template<class TYPE, class ARG_TYPE>
CArray<TYPE, ARG_TYPE>::~CArray()
{
  ASSERT_VALID(this);

  if (m_pData != NULL)
  {
    for( int i = 0; i < m_nSize; i++ )
      (m_pData + i)->~TYPE();
    delete[] (BYTE*)m_pData;
  }
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::SetSize(INT_PTR nNewSize, INT_PTR nGrowBy)
{
  ASSERT_VALID(this);
  ASSERT(nNewSize >= 0);

  if(nNewSize < 0 )
    AfxThrowInvalidArgException();

  if (nGrowBy >= 0)
    m_nGrowBy = nGrowBy;  // set new size

  if (nNewSize == 0)
  {
    // shrink to nothing
    if (m_pData != NULL)
    {
      for( int i = 0; i < m_nSize; i++ )
        (m_pData + i)->~TYPE();
      delete[] (BYTE*)m_pData;
      m_pData = NULL;
    }
    m_nSize = m_nMaxSize = 0;
  }
  else if (m_pData == NULL)
  {
    // create buffer big enough to hold number of requested elements or
    // m_nGrowBy elements, whichever is larger.
#ifdef SIZE_T_MAX
    ASSERT(nNewSize <= SIZE_T_MAX/sizeof(TYPE));    // no overflow
#endif
    size_t nAllocSize = max(nNewSize, m_nGrowBy);
    m_pData = (TYPE*) new BYTE[(size_t)nAllocSize * sizeof(TYPE)];
    memset((void*)m_pData, 0, (size_t)nAllocSize * sizeof(TYPE));
    for( int i = 0; i < nNewSize; i++ )
#pragma push_macro("new")
#undef new
      ::new( (void*)( m_pData + i ) ) TYPE;
#pragma pop_macro("new")
    m_nSize = nNewSize;
    m_nMaxSize = nAllocSize;
  }
  else if (nNewSize <= m_nMaxSize)
  {
    // it fits
    if (nNewSize > m_nSize)
    {
      // initialize the new elements
      memset((void*)(m_pData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
      for( int i = 0; i < nNewSize-m_nSize; i++ )
#pragma push_macro("new")
#undef new
        ::new( (void*)( m_pData + m_nSize + i ) ) TYPE;
#pragma pop_macro("new")
    }
    else if (m_nSize > nNewSize)
    {
      // destroy the old elements
      for( int i = 0; i < m_nSize-nNewSize; i++ )
        (m_pData + nNewSize + i)->~TYPE();
    }
    m_nSize = nNewSize;
  }
  else
  {
    // otherwise, grow array
    nGrowBy = m_nGrowBy;
    if (nGrowBy == 0)
    {
      // heuristically determine growth when nGrowBy == 0
      //  (this avoids heap fragmentation in many situations)
      nGrowBy = m_nSize / 8;
      nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
    }
    INT_PTR nNewMax;
    if (nNewSize < m_nMaxSize + nGrowBy)
      nNewMax = m_nMaxSize + nGrowBy;  // granularity
    else
      nNewMax = nNewSize;  // no slush

    ASSERT(nNewMax >= m_nMaxSize);  // no wrap around

    if(nNewMax  < m_nMaxSize)
      AfxThrowInvalidArgException();

#ifdef SIZE_T_MAX
    ASSERT(nNewMax <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
#endif
    TYPE* pNewData = (TYPE*) new BYTE[(size_t)nNewMax * sizeof(TYPE)];

    // copy new data from old
    memcpy(pNewData, m_pData, (size_t)m_nSize * sizeof(TYPE));

    // construct remaining elements
    ASSERT(nNewSize > m_nSize);
    memset((void*)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
    for( int i = 0; i < nNewSize-m_nSize; i++ )
#pragma push_macro("new")
#undef new
      ::new( (void*)( pNewData + m_nSize + i ) ) TYPE;
#pragma pop_macro("new")

    // get rid of old stuff (note: no destructors called)
    delete[] (BYTE*)m_pData;
    m_pData = pNewData;
    m_nSize = nNewSize;
    m_nMaxSize = nNewMax;
  }
}

template<class TYPE, class ARG_TYPE>
INT_PTR CArray<TYPE, ARG_TYPE>::Append(const CArray& src)
{
  ASSERT_VALID(this);
  ASSERT(this != &src);   // cannot append to itself

  if(this == &src)
    AfxThrowInvalidArgException();

  INT_PTR nOldSize = m_nSize;
  SetSize(m_nSize + src.m_nSize);
  CopyElements<TYPE>(m_pData + nOldSize, src.m_pData, src.m_nSize);
  return nOldSize;
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::Copy(const CArray& src)
{
  ASSERT_VALID(this);
  ASSERT(this != &src);   // cannot append to itself

  if(this != &src)
  {
    SetSize(src.m_nSize);
    CopyElements<TYPE>(m_pData, src.m_pData, src.m_nSize);
  }
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::FreeExtra()
{
  ASSERT_VALID(this);

  if (m_nSize != m_nMaxSize)
  {
    // shrink to desired size
#ifdef SIZE_T_MAX
    ASSERT(m_nSize <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
#endif
    TYPE* pNewData = NULL;
    if (m_nSize != 0)
    {
      pNewData = (TYPE*) new BYTE[m_nSize * sizeof(TYPE)];
      // copy new data from old
      memcpy(pNewData, m_pData, m_nSize * sizeof(TYPE));
    }

    // get rid of old stuff (note: no destructors called)
    delete[] (BYTE*)m_pData;
    m_pData = pNewData;
    m_nMaxSize = m_nSize;
  }
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::SetAtGrow(INT_PTR nIndex, ARG_TYPE newElement)
{
  ASSERT_VALID(this);
  ASSERT(nIndex >= 0);

  if(nIndex < 0)
    AfxThrowInvalidArgException();

  if (nIndex >= m_nSize)
    SetSize(nIndex+1, -1);
  m_pData[nIndex] = newElement;
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::InsertAt(INT_PTR nIndex, ARG_TYPE newElement, INT_PTR nCount /*=1*/)
{
  ASSERT_VALID(this);
  ASSERT(nIndex >= 0);    // will expand to meet need
  ASSERT(nCount > 0);     // zero or negative size not allowed

  if(nIndex < 0 || nCount <= 0)
    AfxThrowInvalidArgException();

  if (nIndex >= m_nSize)
  {
    // adding after the end of the array
    SetSize(nIndex + nCount, -1);   // grow so nIndex is valid
  }
  else
  {
    // inserting in the middle of the array
    INT_PTR nOldSize = m_nSize;
    SetSize(m_nSize + nCount, -1);  // grow it to new size
    // destroy intial data before copying over it
    for( int i = 0; i < nCount; i++ )
      (m_pData + nOldSize + i)->~TYPE();
    // shift old data up to fill gap
    memmove(m_pData + nIndex + nCount, m_pData + nIndex,
      (nOldSize-nIndex) * sizeof(TYPE));

    // re-init slots we copied from
    memset((void*)(m_pData + nIndex), 0, (size_t)nCount * sizeof(TYPE));
    for( int i = 0; i < nCount; i++ )
#pragma push_macro("new")
#undef new
      ::new( (void*)( m_pData + nIndex + i ) ) TYPE;
#pragma pop_macro("new")
  }

  // insert new value in the gap
  ASSERT(nIndex + nCount <= m_nSize);
  while (nCount--)
    m_pData[nIndex++] = newElement;
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::RemoveAt(INT_PTR nIndex, INT_PTR nCount)
{
  ASSERT_VALID(this);
  ASSERT(nIndex >= 0);
  ASSERT(nCount >= 0);
  ASSERT(nIndex + nCount <= m_nSize);

  if(nIndex < 0 || nCount < 0 || (nIndex + nCount > m_nSize))
    AfxThrowInvalidArgException();

  // just remove a range
  INT_PTR nMoveCount = m_nSize - (nIndex + nCount);
  for( int i = 0; i < nCount; i++ )
    (m_pData + nIndex + i)->~TYPE();
  if (nMoveCount)
    memmove( m_pData + nIndex, m_pData + nIndex + nCount,
      (size_t)nMoveCount * sizeof(TYPE));
  m_nSize -= nCount;
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::InsertAt(INT_PTR nStartIndex, CArray* pNewArray)
{
  ASSERT_VALID(this);
  ASSERT(pNewArray != NULL);
  ASSERT_VALID(pNewArray);
  ASSERT(nStartIndex >= 0);

  if(pNewArray == NULL || nStartIndex < 0)
    AfxThrowInvalidArgException();

  if (pNewArray->GetSize() > 0)
  {
    InsertAt(nStartIndex, pNewArray->GetAt(0), pNewArray->GetSize());
    for (INT_PTR i = 0; i < pNewArray->GetSize(); i++)
      SetAt(nStartIndex + i, pNewArray->GetAt(i));
  }
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::Serialize(CArchive& ar)
{
  ASSERT_VALID(this);

  CObject::Serialize(ar);
  if (ar.IsStoring())
  {
    ar.WriteCount(m_nSize);
  }
  else
  {
    DWORD_PTR nOldSize = ar.ReadCount();
    SetSize(nOldSize, -1);
  }
  SerializeElements<TYPE>(ar, m_pData, m_nSize);
}

#ifdef _DEBUG
template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::Dump(CDumpContext& dc) const
{
  CObject::Dump(dc);

  dc << "with " << m_nSize << " elements";
  if (dc.GetDepth() > 0)
  {
    dc << "\n";
    DumpElements<TYPE>(dc, m_pData, m_nSize);
  }

  dc << "\n";
}

template<class TYPE, class ARG_TYPE>
void CArray<TYPE, ARG_TYPE>::AssertValid() const
{
  CObject::AssertValid();

  if (m_pData == NULL)
  {
    ASSERT(m_nSize == 0);
    ASSERT(m_nMaxSize == 0);
  }
  else
  {
    ASSERT(m_nSize >= 0);
    ASSERT(m_nMaxSize >= 0);
    ASSERT(m_nSize <= m_nMaxSize);
    ASSERT(AfxIsValidAddress(m_pData, m_nMaxSize * sizeof(TYPE)));
  }
}
#endif //_DEBUG

#endif

#endif //__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif  //_KARRAY_H_
/*****************************************************************************
 * $Log: KArray.h,v $
 * Revision 1.1  2009/07/12 05:38:09  ddarko
 * Created
 *
 *****************************************************************************/

/*This is a part of the Microsoft Foundation Classes C++ library.
  Copyright (C) Microsoft Corporation. All rights reserved.

  This source code is only intended as a supplement to the Microsoft Foundation
  Classes Reference and related electronic documentation provided with the library.
  See these sources for detailed information regarding the Microsoft Foundation
  Classes product.
  */