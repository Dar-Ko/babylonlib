/*$RCSfile: KArrayStl.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/07/12 07:01:03 $
  $Author: ddarko $

  STL port of MFC CArray class.
  Copyright: CommonSoft Inc
  2009-07-12 Darko Kolakovic
 */

#ifndef _KARRAY_H_
    //$RCSfile: KArrayStl.h,v $ sentry
  #define _KARRAY_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef __cplusplus

  #include <vector>     //std::vector template

//TODO: Standard Template Library (STL)
/*The CArray class supports arrays that are are similar to C arrays, but can dynamically shrink and grow as necessary.

Array indexes always start at position 0. You can decide whether to fix the upper bound or allow the array to expand when you add elements past the current bound. Memory is allocated contiguously to the upper bound, even if some elements are null.

As with a C array, the access time for a CArray indexed element is constant and is independent of the array size.
*/
  template<class TYPE //the type of objects stored in the array
          >
  class CArray : private std::vector<TYPE>
  {
  public:
    CArray();
    ~CArray();
  public:
    using std::vector<TYPE>::operator[];
    int   Add(TYPE newElem);
    TYPE& ElementAt(int nIndex);
    bool  IsEmpty() const;
    TYPE  GetAt(int nIndex) const;
    int   GetCount() const;
    int   GetSize() const;
    int   GetUpperBound() const;
    void  InsertAt(int nIndex, TYPE newElem);
    void  RemoveAll();
    void  RemoveAt(int nIndex);
    void  SetAt(int nIndex, TYPE newElem);
    void  SetSize(int newsiz, int growby = -1);
  };
  /////////////////////////////////////////////////////////////////////////////
  //Inlines


  //---------------------------------------------------------------------------
  /*
   */
  template <class TYPE>
  CArray<TYPE>::CArray()
    {
    }

  template <class TYPE>
  CArray<TYPE>::~CArray()
    {
    std::vector<TYPE>::clear();
    }

  //---------------------------------------------------------------------------
  /*
   */
  template <class TYPE>
  int CArray<TYPE>::Add(TYPE newElem)
  {
  std::vector<TYPE>::push_back(newElem);
  return 0;
  }

  //---------------------------------------------------------------------------
  /*
   */
  template <class TYPE>
  TYPE& CArray<TYPE>::ElementAt(int nIndex)
  {
  return (TYPE&)std::vector<TYPE>::at(nIndex);
  }

  //---------------------------------------------------------------------------
  /*
   */
  template <class TYPE>
  bool CArray<TYPE>::IsEmpty() const
  {
  return std::vector<TYPE>::empty();
  }

  //---------------------------------------------------------------------------
  /*
   */
  template <class TYPE>
  TYPE CArray<TYPE>::GetAt(int nIndex) const
  {
  return std::vector<TYPE>::at(nIndex);
  }

  //---------------------------------------------------------------------------
  /*
   */
  template <class TYPE>
  int CArray<TYPE>::GetCount() const
  {
  return std::vector<TYPE>::size();
  }

  //---------------------------------------------------------------------------
  /*
   */
  template <class TYPE>
  int CArray<TYPE>::GetSize() const
  {
  return std::vector<TYPE>::size();
  }

  //---------------------------------------------------------------------------
  /*
   */
  template <class TYPE>
  int CArray<TYPE>::GetUpperBound() const
  {
  return std::vector<TYPE>::size() - 1;
  }

  //---------------------------------------------------------------------------
  /*
   */
  template <class TYPE>
  void CArray<TYPE>::InsertAt(int nIndex, TYPE newElem)
  {
  std::vector<TYPE>::iterator it = std::vector<TYPE>::begin();
  it += index;

  std::vector<TYPE>::insert(it, newElem);
  }

  //---------------------------------------------------------------------------
  /*
   */
  template <class TYPE>
  void CArray<TYPE>::RemoveAll()
  {
  std::vector<TYPE>::clear();
  }

  //---------------------------------------------------------------------------
  /*
   */
  template <class TYPE>
  void CArray<TYPE>::RemoveAt(int nIndex)
  {
  std::vector<TYPE>::erase(std::vector<TYPE>::begin() + index);
  }

  //---------------------------------------------------------------------------
  /*
   */
  template <class TYPE>
  void CArray<TYPE>::SetAt(int nIndex, TYPE newElem)
  {
  this[nIndex] = newElem;
  }

  //---------------------------------------------------------------------------
  /*
   */
  template <class TYPE>
  void CArray<TYPE>::SetSize(int newsiz, int growby = -1)
  {
  std::vector<TYPE>::reserve(newsiz);
  }

#endif //__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif  //_KARRAY_H_
/*****************************************************************************
 * $Log: KArrayStl.h,v $
 * Revision 1.1  2009/07/12 07:01:03  ddarko
 * Created
 *
 *****************************************************************************/
