/*$Workfile: S:\_SrcPool\Cpp\STL\KXmlElementVector.h$: header file
  $Revision: 7$ $Date: 2005-05-02 09:46:16$
  $Author: Darko Kolakovic$

  STL element collection
  Copyright: CommonSoft Inc
  2005-04-23 Darko Kolakovic
 */

#ifndef _KXMLELEMENTVECTOR_H_
    //$Workfile: S:\_SrcPool\Cpp\STL\KXmlElementVector.h$ sentry
  #define _KXMLELEMENTVECTOR_H_

//============================================================================
// Standard Template Library is required for this implementation of the
// XML Element List.
// Note: Define _STL before invoking this header file.
#if defined(_STL) || defined(_USE_STL)

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
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

#include <vector>
#include <algorithm>  //std::find()

///////////////////////////////////////////////////////////////////////////////
/*XML element collection used in XML processing.

  The type of reference to parent's XML element PARENTID depends of underlaying 
  implementation. For example if node collection is implemented as an array of 
  elements, the parent could be reffered through array index or pointer or 
  reference to the parent's node.

  Note: element reallocation occurs when a member function must grow
  the controlled sequence beyond its current storage capacity.
  Other insertions, erasures or algorithms may alter various storage addresses
  within the sequence. In all such cases, iterators or references that point
  at altered portions of the controlled sequence become invalid.

  Note: uses Standard Template Library (STL).

  See also: KXmlTypedef.h, CXmlNode, CXmlAttributeList
 */
template<typename XMLNODE, //The type of XML node class that you want 
                           //the collection to use. 
         typename PARENTID //The type of reference to the parent's node.
        >
class TXmlElementListVector: private std::vector<XMLNODE>
{
public:
  bool Find(const CXmlString& strElementName);
  XMLNODE& GetItem(const CXmlString& strElementName, unsigned int nIndex = 0);
  void RemoveItem(const CXmlString& strElementName, unsigned int nIndex = 0);
  XMLNODE& Append(XMLNODE& xmlElement);
  size_t Enumerate(const wchar_t* szElementName = NULL);
  int GetCount() const;
  const XMLNODE& GetAt(const size_t nIndex) const;
  XMLNODE& GetAt(const size_t nIndex);
  PARENTID GetParentId() const;
  void SetParentId(const PARENTID parentId);
  TXmlElementListVector& operator=(const TXmlElementListVector& xmlElementList);

public:
  mutable PARENTID m_xmlParentId; //reference to the parent's node. 
};


///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Finds the first of many elements with the same given name (tag).

  Returns: true if named element is in the list; otherwise returns false.
 */
template<typename XMLNODE, typename PARENTID>
bool TXmlElementListVector<XMLNODE, PARENTID>::Find(
                         const CXmlString& strElementName //[in] element's tag
                         )
  {
  TXmlElementListVector::iterator iter = std::find(begin(),
                                             end(),
                                             strElementName);
  return (iter != end());
  }

//-----------------------------------------------------------------------------
/*Retrieves XML name with the given name. The list could contain none or more
  elements with the same name (tag).

  Note: element reallocation occurs when a member function must grow
  the controlled sequence beyond its current storage capacity.
  operations like adding elements at its tail with push_back() or Other
  insertions, erasures and algorithms may alter storage addresses
  within the container. In all such cases, iterators or references that point
  at altered portions of the controlled sequence become invalid.

  Returns: required XML element.

  See also: GetAt();
 */
template<typename XMLNODE, typename PARENTID>
XMLNODE& TXmlElementListVector<XMLNODE, PARENTID>::GetItem(
                          const CXmlString& strElementName,//[in] element's tag
                          unsigned int nIndex //[in] = 0 index of the element 
                                              //with the same XML tag
            )
  {
  TXmlElementListVector::iterator iter = std::find(begin(),
                                             end(),
                                             strElementName);
  while ((nIndex > 0) && (iter != end()))
    {
    nIndex--;
    iter = std::find(++iter, end(), strElementName);
    }

  if(iter != end())
    {
    return *iter;
    }
  else
    {
    static XMLNODE xmlNull; //empty element used to mark end of the list
    return xmlNull;
    }
  }

//-----------------------------------------------------------------------------
/*Appends an element to the end of the list.

  Returns: newly appended element.
 */
template<typename XMLNODE, typename PARENTID>
XMLNODE& TXmlElementListVector<XMLNODE, PARENTID>::Append(
                      XMLNODE& xmlElement //[in] new item to append to the list
                      )
  {
  return *insert(end(), xmlElement);
  }

//-----------------------------------------------------------------------------
/*Removes an element from the list.
 */
template<typename XMLNODE, typename PARENTID>
void TXmlElementListVector<XMLNODE, PARENTID>::RemoveItem(
                         const CXmlString& strElementName, //[in] element's tag
                         unsigned int nIndex //[in] = 0 index of the element 
                                             //with the same XML tag
                         )
{
TXmlElementListVector::iterator iter = std::find(begin(), end(), strElementName);

while( iter != end() )
  {
  if (nIndex == 0) //Delete found element
    {
    erase(iter);
    break;
    }

    //Browse elements with the same tag
  nIndex--;
  iter = std::find(++iter, end(), strElementName);
  }
}

//-----------------------------------------------------------------------------
/*Returns: the number of the list items with the given tag or count of all items.
 */
template<typename XMLNODE, typename PARENTID>
size_t TXmlElementListVector<XMLNODE, PARENTID>::Enumerate(
                                       const wchar_t* szElementName //[in]= NULL
                                       )
{
if ((szElementName == NULL) || (szElementName[0] == wchar_t(0)) )
  return (size_t)GetCount();

size_t nResult = 0;
TXmlElementListVector::iterator iter = std::find(begin(), end(), szElementName);
while ( iter != end() )
  {
  nResult++;
  iter = std::find(++iter, end(), szElementName);
  }

return nResult;
}

//-----------------------------------------------------------------------------
/*Returns: the number of the list items.
 */
template<typename XMLNODE, typename PARENTID>
int TXmlElementListVector<XMLNODE, PARENTID>::GetCount() const
  {
  ASSERT(INT_MAX > size());
  return (int)size();
  }

//-----------------------------------------------------------------------------
/*Obtains the list element at the specified index.
  This implementation throws an exception if nIndex is equal or
  greater than the count of elements in the list.

  Returns: list element currently at this index.

  See also: GetItem()
 */
template<typename XMLNODE, typename PARENTID>
const XMLNODE& TXmlElementListVector<XMLNODE, PARENTID>::GetAt(
                                     const size_t nIndex //index of the element
                                     ) const
  {
  return at(nIndex);
  }

/*
  Note: element reallocation occurs when a member function must grow
  the controlled sequence beyond its current storage capacity.
  operations like adding elements at its tail with push_back() or Other
  insertions, erasures and algorithms may alter storage addresses
  within the container. In all such cases, iterators or references that point
  at altered portions of the controlled sequence become invalid.

 */
template<typename XMLNODE, typename PARENTID>
XMLNODE& TXmlElementListVector<XMLNODE, PARENTID>::GetAt(
                                      const size_t nIndex //index of the element
                                      )
  {
  return at(nIndex);
  }

//-----------------------------------------------------------------------------
/*Get the reference to the parent's node.

  Returns: the reference to the parent's node.
 */
template<typename XMLNODE, typename PARENTID>
PARENTID TXmlElementListVector<XMLNODE, PARENTID>::GetParentId() const
  {
  return m_xmlParentId;
  }

//-----------------------------------------------------------------------------
/*Set reference to the parent's node.
 */
template<typename XMLNODE, typename PARENTID>
void TXmlElementListVector<XMLNODE, PARENTID>::SetParentId(
                                const PARENTID parentId //[in] reference to the
                                                        //parent's node
                                )
  {
  m_xmlParentId = parentId;
  }

//-----------------------------------------------------------------------------
/*
 */
template<typename XMLNODE, typename PARENTID>
TXmlElementListVector<XMLNODE, PARENTID>& 
        TXmlElementListVector<XMLNODE, PARENTID>::operator=(
        const TXmlElementListVector<XMLNODE, PARENTID>& xmlElementList //[in]
        )
  {
  if(&xmlElementList != this)
    {
    *(std::vector<XMLNODE>*)this = (xmlElementList);
    m_xmlParentId = xmlElementList.m_xmlParentId;
    }
  return *this;

  }

//============================================================================
#endif //_STL
///////////////////////////////////////////////////////////////////////////////
#endif  //_KXMLELEMENTVECTOR_H_
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2005-04-26 01:26:46  Darko           _USE_STL
 *       sentry; fixed search by name
 *  1    Biblioteka1.0         2005-04-25 21:37:54  Darko
 * $
 *****************************************************************************/
