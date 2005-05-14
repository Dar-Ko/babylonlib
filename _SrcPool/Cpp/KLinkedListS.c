/*$Workfile: KLinkedListS.c$: implementation file
  $Revision: 1$ $Date: 2005-04-14 16:14:34$
  $Author: Darko Kolakovic$

  Singly Linked List
  Jun 1989 Darko Kolakovic
*/

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <stdlib.h> /*malloc()*/
#include "KLinkedListS.h"  /*ListNode struct*/

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

/*LinkedListSAddTail()--------------------------------------------------------*/
/*Adds a new element or list of elements to the tail of this list. 

  Note: Uses malloc() to create a copy of the new element.

  Returns: pointer to the last element.
 */
PLISTNODE LinkedListSAddTail(PLISTNODE pEndNode,/*[in] last of the elements in
                                                  a list*/
                                    void* pData /*[in] pointer to new element*/
                            )
{
PLISTNODE pNode;
pNode = malloc(sizeof (struct ListNode));
if (pNode != NULL)
  {
  pNode->m_pData = pData;
  pNode->m_pNext = END_OF_LIST;
  pEndNode->m_pNext = pNode; //Replace the last element with the new one
  }
return pEndNode;
}

/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2005-04-14 16:14:34  Darko Kolakovic 
 * $
 *  0    Biblioteka1.0           Jun 1989 Darko Kolakovic
 *****************************************************************************/
