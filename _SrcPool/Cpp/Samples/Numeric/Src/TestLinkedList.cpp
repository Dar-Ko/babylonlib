/*$Workfile: TestLinkedList.cpp$: implementation file
  $Revision: 1$ $Date: 2005-04-14 16:16:35$
  $Author: Darko Kolakovic$

  Test linked lists
  Copyright: CommonSoft Inc.
  Apr 2k D.Kolakovic
*/
// Group=Examples

#include "stdafx.h"
#include "KTrace.h"        //ASSERT macro
//#include "KTypedef.h"      //DWORD typedef
#include "KLinkedListS.h"  //TLinkedListS template

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

bool TestSinglyLinkedList();

//TestSinglyLinkedList()-------------------------------------------------------
/*Test inserting and deleting singly linked list elements.

  Returns: true if successful, otherwise returns false.
 */
bool TestSinglyLinkedList()
{
TsWriteToViewLn(_T("TestSinglyLinkedList()"));
TESTENTRY logEntry =
  {_T("TLinkedListS::TLinkedListS<unsigned>()"), _T("KLinkedListS.h"), false};

bool bRes = true;
TLinkedListS<unsigned int> listTest;      //list of unsigned integers
  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

 //Test appending elements
if(bRes)
  {
  logEntry.m_szObjectName = _T("TLinkedListS<unsigned>::AddTail()");

  listTest.AddTail(202);
  bRes = !listTest.IsEmpty();
  if (bRes)
    {
    listTest.AddTail(303);
    if (bRes)
      {
      listTest.AddTail(404);
      bRes = (listTest.GetCount() == 3);
      }
    }
  }
  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

 //Test inserting elements before the first element
if(bRes)
  {
  logEntry.m_szObjectName = _T("TLinkedListS<unsigned>::AddHead()");
  listTest.AddHead(101);
  bRes = (listTest.GetCount() == 4);
  }
  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

 //Test deleting the first element
if(bRes)
  {
  logEntry.m_szObjectName = _T("TLinkedListS<unsigned>::RemoveHead()");
  listTest.RemoveHead();
  bRes = (listTest.GetCount() == 3);
  }
  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

 //Test deleting the list
if(bRes)
  {
  logEntry.m_szObjectName = _T("TLinkedListS<unsigned>::RemoveAll()");
  listTest.RemoveAll();
  bRes = listTest.IsEmpty();
  }
  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToView(LOG_EOT);
TsWriteToView(_T("\r\n"));
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  5    Biblioteka1.4         2004-10-05 14:05:40  Darko           fixed Unicode
 *       build
 *  4    Biblioteka1.3         2004-07-07 17:41:02  Darko           replaced
 *       iomainp.h with stdafx.h
 *  3    Biblioteka1.2         2002-08-03 19:27:52  Darko
 *  2    Biblioteka1.1         2002-02-03 18:11:14  Darko
 *  1    Biblioteka1.0         2001-07-26 21:31:37  Darko
 * $
 *****************************************************************************/
