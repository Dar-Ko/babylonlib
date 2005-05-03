/*$Workfile: S:\_SrcPool\Cpp\STL\KXmlAttributeVector.h$: header file
  $Revision: 3$ $Date: 2005-05-02 09:27:13$
  $Author: Darko Kolakovic$

  STL XML element attributes collection
  Copyright: CommonSoft Inc
  2005-04-25 Darko Kolakovic
 */

#ifndef _KXMLATTRIBUTETVECTOR_H_
    //$Workfile: S:\_SrcPool\Cpp\STL\KXmlAttributeVector.h$ sentry
  #define _KXMLATTRIBUTETVECTOR_H_

//============================================================================
// Standard Template Library is required for this implementation of the
// XML Attribute List.
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

class CXmlAttribute; //Forward reference

///////////////////////////////////////////////////////////////////////////////
/*XML element attributes collection used in XML processing.

  Note: element reallocation occurs when a member function must grow
  the controlled sequence beyond its current storage capacity.
  Other insertions, erasures or algorithms may alter various storage addresses
  within the sequence. In all such cases, iterators or references that point
  at altered portions of the controlled sequence become invalid.


  Note: uses Standard Template Library (STL).

  See also: KXmlTypedef.h, CXmlNode, TXmlElementListVector
 */
class CXmlAttributeList: private std::vector<CXmlAttribute>
{
public:
  bool Find(const CXmlString& strAttributeName);
  CXmlAttribute& GetItem(const CXmlString& strAttributeName,
                         bool& bHasAttribute);
  const CXmlAttribute& GetAt(const size_t nIndex) const;
  CXmlAttribute& Append(CXmlAttribute& xmlAttribute);
  void Remove(const CXmlString& strAttributeName);
  int GetCount() const;
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Finds the XML attribute with the given name.

  Returns: true if named attribute is in the list; otherwise returns false.
 */
inline
bool CXmlAttributeList::Find(const CXmlString& strAttributeName //[in]
                                                           //attribute's name
                            )
  {
  CXmlAttributeList::iterator iter = std::find(begin(),
                                               end(),
                                               strAttributeName);
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

  Returns: valid XML attribute and validation flag.

  See also: GetAt()
 */
inline
CXmlAttribute& CXmlAttributeList::GetItem(const CXmlString& strAttributeName, //[in]
                       //name of the attribute
                       bool& bHasAttribute //[out] true as result of
                       //operation, if attribute with given
                       //name exist or false if not.
                       )
  {
  CXmlAttributeList::iterator iter = std::find(begin(),
                                               end(),
                                               strAttributeName);
  //If no such name exists in the range, the iterator returned
  //addresses the last position of the range, one past the final
  //element. bResult is false.
  bHasAttribute = (iter != end());
  if(bHasAttribute)
    {
    return *iter;
    }
  else
    {
    static CXmlAttribute xmlNull; //empty element used to mark end of the list
    return xmlNull;
    }
  }

//-----------------------------------------------------------------------------
/*Call this method to add an element to the end of the list.

  Returns: newly appended element.
 */
inline
CXmlAttribute& CXmlAttributeList::Append(CXmlAttribute& xmlAttribute //[in] new
                                        //item to append to the list
           )
  {
  return *insert(end(), xmlAttribute);
  }

//-----------------------------------------------------------------------------
/*Removes an attribute element from the list.
 */
inline
void CXmlAttributeList::Remove(const CXmlString& strAttributeName //[in]
                       //name of the attribute
                             )
  {
  CXmlAttributeList::iterator iter = std::find(begin(),
                                               end(),
                                               strAttributeName);
  if (iter != end())
    erase(iter);
  }

//-----------------------------------------------------------------------------
/*Returns: the number of the list items.
 */
inline
int CXmlAttributeList::GetCount() const
  {
  ASSERT(INT_MAX > size());
  return (int)size();
  }

//-----------------------------------------------------------------------------
/*Returns: valid XML attribute.

  See also: GetItem()
 */
inline
const CXmlAttribute& CXmlAttributeList::GetAt(const size_t nIndex //[in]
                                       ) const
  {
  return at(nIndex);
  }

//============================================================================
#endif //_STL
///////////////////////////////////////////////////////////////////////////////
#endif  //_KXMLATTRIBUTETVECTOR_H_
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2005-04-28 18:12:11  Darko Kolakovic const GetAt()
 *       const
 *  1    Biblioteka1.0         2005-04-27 12:51:38  Darko Kolakovic
 * $
 *****************************************************************************/
