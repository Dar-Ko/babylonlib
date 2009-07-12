/*$RCSfile: KStrArray.h,v $: header file
  $Revision: 1.3 $ $Date: 2009/07/12 05:35:38 $
  $Author: ddarko $

  Array of CString objects.
  Copyright: CommonSoft Inc
  2009-07-01 Darko Kolakovic
 */

#ifndef _KSTRARRAY_H_
    //$RCSfile: KStrArray.h,v $ sentry
  #define _KSTRARRAY_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef __cplusplus
#if 0
#include "KString.h"
  /////////////////////////////////////////////////////////////////////////////
  //The CStringArray class supports arrays of CString objects.

  class IStringArray
  {
  public:
    /*Adds a new element to the array.
      Returns TRUE if the element is successfully added to the array, FALSE otherwise.
     */
    bool Add(const CString& t) = 0;
    /*Finds an element in the array.
      Returns the index of the found element, or -1 if the element is not found.
     */
    int Find(const CString& t) const = 0;
    /*Returns a pointer to the data stored in the array.
     */
    CString* GetData() const = 0;
    /*Returns the number of elements stored in the array.
     */
    int GetSize() const = 0;
    /*Removes a given element from the array.
      Returns TRUE if the element is found and removed, FALSE otherwise.
     */
    bool Remove(const CString& t) = 0;
    /*Removes all elements from the array.
     */
    void RemoveAll() = 0;
    /*Removes the specified element from the array.
     Returns TRUE if the element was removed, FALSE if the index was invalid.
     */
    bool RemoveAt(int nIndex) = 0;
    /*Set the specified element in the array.
      Returns TRUE if successful, FALSE if the index was not valid.
     */
    bool SetAtIndex(int nIndex, const CString& t) = 0;
    /*Retrieves an element from the array.
      Returns the element of the array referenced by nIndex.
     */
    const CString& operator[] (int nIndex) const = 0;
    CString& operator[] (int nIndex) = 0;
    /*Assignment operator.
      Returns the updated CSimpleArray object.
     */
    CSimpleArray& operator=(const CSimpleArray& src) = 0;
  };
#endif

  #ifdef _USE_STL
  #include <string>     //std::string template
  #include <vector>     //std::vector template

  #include "KTString.h" //tstring
  #pragma todo (Quick CStringArray replacement dropin is not test. D.K.)
  class CStringArray : public std::vector<tstring>
  {
  public:
    //CStringArray(const CStringArray& src){};
    /*Adds a new element to the array.
      Returns true if the element is successfully added to the array, false otherwise.
     */
    bool Add(const tstring& t)
      {
      push_back(t);
      return true;
      };
    /*Finds an element in the array.
      Returns the index of the found element, or -1 if the element is not found.
     */
    int Find(const tstring& t) const
    {
    int iRes = 0;
    while ( iRes < (int)size());
      {
      const tstring& j = at(iRes);
      if (t == j)
        return iRes;;
      iRes++;
      }
    return -1;
    };
    /*Returns a pointer to the data stored in the array.
     */
    tstring* GetData() const{};
    /*Returns the number of elements stored in the array.
     */
    int GetSize() const
    {
    return size();
    };
    /*Removes a given element from the array.
      Returns TRUE if the element is found and removed, FALSE otherwise.
     */
    bool Remove(const tstring& t)
    {
    int i = Find(t);
    if (i > -1)
      {
      erase(begin() + i);
      return true;
      }
    return false;
    };
    /*Removes all elements from the array.
     */
    void RemoveAll()
    {
    clear();
    };
    /*Removes the specified element from the array.
      Returns true if the element was removed, false if the index was invalid.
     */
    bool RemoveAt(int nIndex)
    {
    std::vector<tstring>::iterator Iter;
    Iter = begin() + nIndex;
    erase(Iter);
    return (Iter <= end());
    };
    /*Set the specified element in the array.
      Returns true if successful, false if the index was not valid.
     */
    bool SetAtIndex(int nIndex, const tstring& t)
    {
    try
      {
      tstring& j = at(nIndex);
      j = t;
      return true;
      }
    catch(...)
      {
      return false;
      }
    };

    /*Assignment operator.
      Returns the updated CSimpleArray object.
     */
    CStringArray& operator=(const CStringArray& src)
    {
    clear();
#pragma todo( warning: Copy arrays)
//    std::vector<tstring>::iterator Iter = src.begin();
//    while(Iter != src.end())
//      {
//      push_back(src.at(Iter));
//      Iter++;
//      }
    return *this;
    };
  };

  #else //!_USE_STL
    #ifdef _MSC_VER //Microsoft Visual Studio  Compilers
      //Note: to use Microsoft Fundation Classes Library (MFC) define _USE_MFC;
      //Microsoft Active Template Library (ATL) define _USE_ATL and optional
      //_USE_ATLSIMPLEARRAY
      #include "KWinStrArray.h" //CStringAtlArray
    #endif //_MSC_VER

  #endif //_USE_STL
#endif //__cplusplus

///////////////////////////////////////////////////////////////////////////////
#endif  //_KSTRARRAY_H_
/*****************************************************************************
 * $Log: KStrArray.h,v $
 * Revision 1.3  2009/07/12 05:35:38  ddarko
 * Documetation group changed
 *
 * Revision 1.2  2009/07/09 22:16:22  ddarko
 * *** empty log message ***
 *
 * Revision 1.1  2009/07/07 20:44:47  ddarko
 * Created
 *
 *****************************************************************************/
