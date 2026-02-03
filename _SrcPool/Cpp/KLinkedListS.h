/*$Workfile: KLinkedListS.h$: header file
  $Revision: 2$ $Date: 2005-04-26 01:11:55$
  $Author: Darko$

  Singly Linked List
  Copyright: CommonSoft Inc
  01 Apr. 1999 Darko Kolakovic
 */

#ifndef _KLINKEDLISTS_H_
    /*$Workfile: KLinkedListS.h$ sentry*/
  #define _KLINKEDLISTS_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef __cplusplus
///////////////////////////////////////////////////////////////////////////////
/*Linked List Node. 
  Each node holds reference to the next node in a list and any data encapsulated
  in the node itself. An empty node indicates the last node.
  
  See also: TLinkedListS, struct ListNode (C language), LinkedListSAddTail()
 */
template <typename DATATYPE> struct ListNode
  {
  DATATYPE m_dtData;           //data container
  ListNode<DATATYPE>* m_pNext; //link to the next element (node) in a list
  };

///////////////////////////////////////////////////////////////////////////////
/*Singly Linked List is a collection of list nodes. Each node holds reference
  to the next node in the list and any data encapsulated in the node itself.
  To store the list, you only need a reference to the first node in the list.
  An empty node indicates the last node. Default inserts are made at the head
  of the list.
     {html:<br /><img src="Images/graphLinkedListS.gif"
      alt="Singly Linked List" border="0"><br />}

  Example:
    #include "KLinkedListS.h"  //TLinkedListS template
    int MyList()
      {
      int iNoofElements = 0;
      TLinkedListS<unsigned int> listTest;      //list of unsigned integers
        //Append elements
      listTest.AddTail(202);
      listTest.AddTail(303);
      listTest.AddTail(404);
        //Insert new start element
      listTest.AddHead(101);
      if( !listTest.IsEmpty() )
        iNoofElements = listTest.GetCount();
      return iNoofElements;
      }
 */
template <typename DATATYPE>
class TLinkedListS
{
public:
  TLinkedListS();
  TLinkedListS(const TLinkedListS& listValue);
  virtual ~TLinkedListS();

public:
  TLinkedListS& operator=(const TLinkedListS& listValue);
  void RemoveAll();
  bool IsEmpty() const;
  int  GetCount() const;
  DATATYPE GetHead() const;
  void RemoveHead();
  void AddHead(const DATATYPE& dtData);
  void AddTail(const DATATYPE& dtData);

protected:
  typedef ListNode<DATATYPE>* PLISTNODE; //pointer to Singly Linked List Node
  PLISTNODE m_pElement; //pointer to the first element (node) in the list
  const PLISTNODE END_OF_LIST;
};

///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/*Constructs an empty list.
 */
template <typename DATATYPE>
TLinkedListS<DATATYPE>::TLinkedListS() :
  END_OF_LIST(NULL)
{
m_pElement = END_OF_LIST;
}

//-----------------------------------------------------------------------------
/*Copies another list instance over the current list.
 */
template <typename DATATYPE>
TLinkedListS<DATATYPE>::TLinkedListS(const TLinkedListS& listValue //[in] list
                                       //to copy
                                    ) :
  END_OF_LIST(NULL)
{
if(&listValue != this)
  this->operator=(listValue);
}

//-----------------------------------------------------------------------------
/*Destructor performs memory cleanup before the class instance is destroyed.
 */
template <typename DATATYPE>
TLinkedListS<DATATYPE>::~TLinkedListS()
{
RemoveAll(); //Clean up every node
}

//-----------------------------------------------------------------------------
/*Assigns another list instance to the pNode list.

  Returns: reference to the pNode list.
 */
template <typename DATATYPE>
TLinkedListS<DATATYPE>& TLinkedListS<DATATYPE>::operator=(
                           const TLinkedListS& listValue //[in] value to assign
                          )
{
if(&listValue != this)
  {
  RemoveAll(); //Clean up every node
  PLISTNODE pNode = listValue.m_pElement;
  //Copy the data from each node to the current instance.
  while (pNode != END_OF_LIST)
    {
    DATATYPE dtData = pNode->m_dtData; //Copy the data
    AddTail(dtData); //Append the new data container
    pNode = pNode->m_pNext;
    }
  }
return *this;
}

//-----------------------------------------------------------------------------
/*Removes all the elements from this list and frees the associated memory.
 */
template <typename DATATYPE>
void TLinkedListS<DATATYPE>::RemoveAll()
{
if (!IsEmpty())
  {
    //Delete all node elements, one by one
  PLISTNODE pNode = m_pElement;
  while(pNode != END_OF_LIST)
    {
    PLISTNODE pPreviousNode = pNode; //Get the current element
    pNode = pNode->m_pNext;                    //Move to the next element
    delete pPreviousNode;
    }
  m_pElement = END_OF_LIST; //Mark the list as an empty list
  }
}

//-----------------------------------------------------------------------------
/*Indicates whether this list contains no elements.

  Returns: true if this list is empty; otherwise returns false.
 */
template <typename DATATYPE>
bool TLinkedListS<DATATYPE>::IsEmpty() const
{
return (m_pElement == END_OF_LIST);
}

//-----------------------------------------------------------------------------
/*Gets the number of elements in this list.

  Returns: integer value containing the element count.
 */
template <typename DATATYPE>
int TLinkedListS<DATATYPE>::GetCount() const
{
int iResult = 0; //number of nodes

if (!IsEmpty())
  {
  PLISTNODE pNode = m_pElement;

  //Count all nodes in the list
  while(pNode != END_OF_LIST)
    {
    iResult++;
    pNode = pNode->m_pNext;
    }
  }

return iResult;
}

//-----------------------------------------------------------------------------
/*Gets the head element of this list.

  Returns: returns a copy of the element at the head of the list or an empty
  element.
 */
template <typename DATATYPE>
DATATYPE TLinkedListS<DATATYPE>::GetHead() const
{
DATATYPE dtResult;
if (!IsEmpty())
  dtResult = m_pElement->m_dtData;
return dtResult;
}

//-----------------------------------------------------------------------------
/*Removes the element from the head of the list.
 */
template <typename DATATYPE>
void TLinkedListS<DATATYPE>::RemoveHead()
{
if (!IsEmpty())
  {
  PLISTNODE pNode = m_pElement;
  m_pElement = pNode->m_pNext; //Move the second node forward
  delete pNode;
  }
}

//-----------------------------------------------------------------------------
/*Adds a new element or list of elements to the head of this list.

  Note: Uses new() to create a copy of the new element.
 */
template <typename DATATYPE>
void TLinkedListS<DATATYPE>::AddHead(const DATATYPE& dtData //[in] new element
                                    )
{
PLISTNODE pNode = new ListNode<DATATYPE>;
ASSERT(pNode != NULL);
if (pNode != NULL)
  {
  pNode->m_dtData = dtData;     //Copy element's content
  pNode->m_pNext  = m_pElement; //Link new node with list's head
  m_pElement   = pNode;         //Set new node as head of the list
  }
}

//-----------------------------------------------------------------------------
/*Adds a new element or list of elements to the tail of this list.

  Note: Uses new() to create a copy of the new element.
 */
template <typename DATATYPE>
void TLinkedListS<DATATYPE>::AddTail(const DATATYPE &dtData//[in] new element
                                    )
{
PLISTNODE pNode= new ListNode<DATATYPE>;
ASSERT(pNode != NULL);
if (pNode != NULL)
  {
  pNode->m_dtData = dtData;
  pNode->m_pNext  = END_OF_LIST; //Set new element as a tail element
  if (IsEmpty())
    {
      //Set the begining of the list to point at the new node
    m_pElement = pNode;
    }
  else
    {
      //Find the last of the elements
    PLISTNODE pEndNode = m_pElement;
    while(pEndNode->m_pNext != END_OF_LIST)
      {
      pEndNode = pEndNode->m_pNext;
      }
    pEndNode->m_pNext = pNode; //Replace the last element with the new one
    }
  }
}

#else /*C compilation*/
/* ////////////////////////////////////////////////////////////////////////// */

 /*End of List tag*/
#define END_OF_LIST (NULL)

/*Linked List Node.
  Each node holds reference to the next node in a list and any data encapsulated
  in the node itself. An empty node indicates the last node.
  
  See also: LinkedListSAddTail(); template ListNode (C++ language)
 */
struct ListNode
  {
  void* m_pData;            /*pointer to data container                */
  struct ListNode* m_pNext; /*link to the next element (node) in a list*/
  };

typedef struct ListNode* PLISTNODE;/*Pointer to Singly Linked List Node*/
#endif //_cplusplus

/* ////////////////////////////////////////////////////////////////////////// */
#endif  /*_KLINKEDLISTS_H_*/
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-04-14 16:14:36  Darko Kolakovic
 * $
 *****************************************************************************/
