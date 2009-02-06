/*$RCSfile: ATL70SimpleArray.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/02/06 17:16:14 $
  $Author: ddarko $

  Fix: ATL 7.0 implemetation of CSimpleArray::RemoveAt() method causes memory
  leak for arrays of complex objects.

  2004-04-01 Darko Kolakovic
 */

#ifndef __cplusplus
  #error ERROR: ATL requires C++ compilation (use a .cpp suffix)
#endif

#if !defined(_ATL_VER)
  #error ERROR: This header requires ATL!
#endif


#ifndef _KSIMPLEARRAY7_H_
  //$RCSfile: ATL70SimpleArray.h,v $ sentry
  #define _KSIMPLEARRAY7_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

// Group=Windows

#if (_ATL_VER <= 0x0700) /*Active Template Library version 7.0*/
/////////////////////////////////////////////////////////////////////////////
/*This class provides methods for managing a simple array, of any given type T.

  FIX: The class is to be used in place of CSimpleArray. It replaces RemoveAt
  method. If ATL 7.00 version template is used to create an array of complex
  objects, element's destructor is not called, causing memory leak.

  In ATL 7.1 this bug is fixed.

  Parameters:
  T    The type of data to store in the array.

  Note: Microsoft Windows specific (Win32)
        and uses Active Template Library (ATL).

  Example:
      //Create an array of strings
      CSimpleArrayAtl7<CString> arrayString;


  See also: atlsimpcoll.h, CSimpleArray::RemoveAt() method, CAtlArray
 */
template <class T>
class CSimpleArrayAtl7
{
public:
  T* m_aT;
  int m_nSize;
  int m_nAllocSize;

// Construction/destruction

  //---------------------------------------------------------------------------
  /*Initializes the data members, creating a new empty CSimpleArray object.
   */
  CSimpleArrayAtl7() : m_aT(NULL), m_nSize(0), m_nAllocSize(0)
  { }

  /*Frees all allocated resources.
   */
  ~CSimpleArrayAtl7()
  {
    RemoveAll();
  }


// Operations

  //---------------------------------------------------------------------------
  /*Returns the number of elements stored in the array.
   */
  int GetSize() const
  {
    return m_nSize;
  }

  //---------------------------------------------------------------------------
  /*Adds a new element to the array.

    Returns TRUE if the element is successfully added to the array, FALSE otherwise.
   */
  BOOL Add(T& t)
  {
    if(m_nSize == m_nAllocSize)
    {
      T* aT;

      int nNewAllocSize = (m_nAllocSize == 0) ? 1 : (m_nSize * 2);
      aT = (T*)realloc(m_aT, nNewAllocSize * sizeof(T));
      if(aT == NULL)
        return FALSE;

      m_nAllocSize = nNewAllocSize;
      m_aT = aT;
    }
    m_nSize++;
    SetAtIndex(m_nSize - 1, t);
    return TRUE;
  }

  //---------------------------------------------------------------------------
  /*Removes a given element from the array. When an element is removed, the
    remaining elements in the array are renumbered to fill the empty space.

    Returns TRUE if the element is found and removed, FALSE otherwise.
   */
  BOOL Remove(T& t)
  {
    int nIndex = Find(t);

    if(nIndex == -1)
      return FALSE;
    return RemoveAt(nIndex);
  }

  //---------------------------------------------------------------------------
  /*Removes the specified element from the array. When an element is removed,
    the remaining elements in the array are renumbered to fill the empty space.

    Returns TRUE if the element was removed, FALSE if the index was invalid.
   */
  BOOL RemoveAt(int nIndex)
  {
  ATLASSERT(nIndex >= 0 && nIndex < m_nSize);

  if (nIndex < 0 || nIndex >= m_nSize) //Validate index range
    return FALSE;
  m_aT[nIndex].~T(); //FIX: Always call element's destructor

  if(nIndex != (m_nSize - 1))
    memmove((void*)&m_aT[nIndex],
            (void*)&m_aT[nIndex + 1],
            (m_nSize - (nIndex + 1)) * sizeof(T));

  m_nSize--;
  return TRUE;
  }

  //---------------------------------------------------------------------------
  /*Removes all elements currently stored in the array.
   */
  void RemoveAll()
  {
    if(m_aT != NULL)
    {
      for(int i = 0; i < m_nSize; i++)

        m_aT[i].~T();
      free(m_aT);
      m_aT = NULL;
    }
    m_nSize = 0;
    m_nAllocSize = 0;
  }

  //---------------------------------------------------------------------------
  /*Retrieves an element from the array.

   Returns the element of the array referenced by nIndex.
   */
  T& operator[] (int nIndex) const
  {
    ATLASSERT(nIndex >= 0 && nIndex < m_nSize);

    return m_aT[nIndex];
  }

  //---------------------------------------------------------------------------
  /*Returns a pointer to the data stored in the array.
   */
  T* GetData() const
  {
    return m_aT;
  }

  // Implementation

  //---------------------------------------------------------------------------
  /*
   */
  class Wrapper

  {
  public:
    Wrapper(T& _t) : t(_t)
    {
    }

    template <class _Ty>
    void *operator new(size_t, _Ty* p)

    {
      return p;
    }
    T t;
  };

  //---------------------------------------------------------------------------
  /*Set the specified element in the array.

    Returns TRUE if successful, FALSE if the index was not valid.
   */
  void SetAtIndex(int nIndex, //[in] index of the element to change
                  T& t        //[in] value to assign to the specified element
                  )
  {
    ATLASSERT(nIndex >= 0 && nIndex < m_nSize);

    new(&m_aT[nIndex]) Wrapper(t);
  }

  //---------------------------------------------------------------------------
  /*Finds an element in the array.

    Returns the index of the found element, or -1 if the element is not found.

    Example:
        CSimpleArray<int> Array;
        for (int i = 100; i < 110; i++)
          Array.Add(i);
          int e = fMy;
          if (Array.Find(101) == -1)
            ATLTRACE(_T("Could not find element\n"));
          else
            ATLTRACE(_T("Found the element\n"));

   */
  int Find(T& t) const
  {
    for(int i = 0; i < m_nSize; i++)

    {
      if(m_aT[i] == t)
        return i;
    }
    return -1;  // not found
  }
};

#else /*Active Template Library version 7.1 +*/
  #include <atlsimpcoll.h> //CSimpleArray template
#endif

///////////////////////////////////////////////////////////////////////////////
#endif /* !_KSIMPLEARRAY7_H_ */
/*****************************************************************************
 * $Log: ATL70SimpleArray.h,v $
 * Revision 1.1  2009/02/06 17:16:14  ddarko
 * ATL 7.0 CSimpleArray bug fix
 *
 *****************************************************************************/
