/*$RCSfile: KArrayStl.h,v $: header file
  $Revision: 1.5 $ $Date: 2009/07/23 13:22:52 $
  $Author: ddarko $

  STL port of MFC CArray class.
  Copyright: CommonSoft Inc
  2009-07-12 Darko Kolakovic
 */

#ifndef _KARRAYSTL_H_
    //$RCSfile: KArrayStl.h,v $ sentry
  #define _KARRAYSTL_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _DEBUG
  #ifndef _STLP_DEBUG
    #define _STLP_DEBUG 1    //Debug STLPort library
  #endif
#else
  #ifdef _STLP_DEBUG
    #undef _STLP_DEBUG
  #endif
#endif

#ifdef __cplusplus

  #include <vector>     //std::vector template

  /////////////////////////////////////////////////////////////////////////////
  /*The CArray class supports arrays that can dynamically shrink and grow
    as necessary.

    Array indexes always start at position 0. You can decide whether to fix
    the upper bound or allow the array to expand when you add elements past
    the current bound.

    Parameter:
      - TYPE the type of objects stored in the array.

   */
  template<class TYPE>
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
    void  Copy(const CArray& src);
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

  /*Frees up any resources used by the array object.
   */
  template <class TYPE>
  CArray<TYPE>::~CArray()
    {
    std::vector<TYPE>::clear();
    }

  //---------------------------------------------------------------------------
  /*Adds a new element to the end of an array, growing the array by one element.

    Returns the index of the added element.

    Example:
      ...
      CArray<CPoint> ptArray;

      CPoint pt(10,20);
      ptArray.Add(pt);             // Element 0
      ptArray.Add(CPoint(30,40));  // Element 1
   */
  template <class TYPE>
  int CArray<TYPE>::Add(TYPE newElem //[in] new element to be added to this array.
                       )
  {
  std::vector<TYPE>::push_back(newElem);
  return GetUpperBound();
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
  /*Call this method to copy the elements of one array to another.
   */
  template <class TYPE>
  void CArray<TYPE>::Copy(const CArray& src //[in] source of the elements to 
                                            //copy to an array.
                         )
  {
  std::vector<TYPE>::assign(src.begin(), src.end());
    //Disable warning C4127: conditional expression in ASSERT is constant
  #pragma warning (disable: 4127)
    ASSERT(GetSize() == src.GetSize());
  #pragma warning (default: 4127)
  }

  //---------------------------------------------------------------------------
  /*Returns the array element at the specified index.

    Note: Passing a negative index value or a value greater than the value 
    returned by GetUpperBound will result in a failure.
   */
  template <class TYPE>
  TYPE CArray<TYPE>::GetAt(int nIndex //[in] index of the element; value is in
              //the range [0, GetUpperBound()] 
                          ) const
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
  /*Removes one element from the array. Any remaining elements are shifted down
    and the upper bound is decremented,

    Example:
      ...      
      CArray<uint_8> MyArray;          //Declare an array of bytes
      for (int a = 0; a < 10; a++)     //Add ten elements to the array
        MyArray.Add(0x0A);
      MyArray.RemoveAt(5);             //Remove fifth element
      ASSERT(MyArray.GetCount() == 9); //Confirm size of array

   */
  template <class TYPE>
  void CArray<TYPE>::RemoveAt(int nIndex //[in] index of the first element to remove.
                             )
  {
  std::vector<TYPE>::erase(std::vector<TYPE>::begin() + nIndex);
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
#endif  //_KARRAYSTL_H_
/*****************************************************************************
 * $Log: KArrayStl.h,v $
 * Revision 1.5  2009/07/23 13:22:52  ddarko
 * Copy()
 *
 * Revision 1.4  2009/07/15 20:54:10  ddarko
 * RemoveAt()
 *
 * Revision 1.3  2009/07/13 09:04:56  ddarko
 * Comment
 *
 * Revision 1.2  2009/07/13 08:08:17  ddarko
 * Sentry
 *
 * Revision 1.1  2009/07/12 07:01:03  ddarko
 * Created
 *
 *****************************************************************************/
