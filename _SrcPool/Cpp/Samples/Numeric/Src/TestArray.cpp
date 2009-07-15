/*$Workfile: TestLinkedList.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2009/07/15 20:53:04 $
  $Author: ddarko $

  Test dynamic array
  Copyright: CommonSoft Inc.
  2009-07-15 D.Kolakovic
*/
// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _USE_STL
  #include "stdstl.h"
#else
  #include "stdafx.h"
#endif

#include "KTrace.h"    //ASSERT macro
#include "KArrayPtr.h" //CArrayPtr template

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

bool TestArrayPtr();

//-----------------------------------------------------------------------------
/*Test inserting and deleting an array elements.

  Returns: true if successful, otherwise returns false.
 */
bool TestArrayPtr()
{
TsWriteToViewLn(_T("TestArray()"));
TESTENTRY logEntry =
  {_T("CArray::CArray<unsigned>()"), _T("KArray.h"), false};

bool bRes = true;
CArray<unsigned int> arrTest;      //array of unsigned integers
  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

//Test appending elements
if(bRes)
  {
  logEntry.m_szObjectName = _T("CArray<unsigned>::Add()");
  int iIndex = arrTest.Add(202);
  TsWriteToView(_T("array["));
  TsWriteToView(iIndex);
  TsWriteToViewLn(_T("]"));

  bRes = !arrTest.IsEmpty();
  if (bRes)
    {
    iIndex = arrTest.Add(303);
    TsWriteToView(_T("array["));
    TsWriteToView(iIndex);
    TsWriteToViewLn(_T("]"));
    if (bRes)
      {
      iIndex = arrTest.Add(404);
      TsWriteToView(_T("array["));
      TsWriteToView(iIndex);
      TsWriteToViewLn(_T("]"));
      bRes = (arrTest.GetCount() == 3);
      }
    }
  }
  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

//Test creating array of pointers
if(bRes)
  {
  logEntry.m_szObjectName = _T("CArrayPtr<TCHAR*>::Add()");
  logEntry.m_szFileName   = _T("KArrayPtr.h");//function or object file name
  CArrayPtr<LPTSTR> arrLines;
  const int LISTSIZE = 10;
  int i = 0;
  while (i < LISTSIZE)
    {
    LPTSTR szTemp = new TCHAR[64];
    arrLines.Add(szTemp);
    i++;
    }
  bRes = ( arrLines.GetCount() == LISTSIZE);

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  if (bRes)
    {
    logEntry.m_szObjectName = _T("CArrayPtr<TCHAR*>::RemoveAt()");
    arrLines.RemoveAt(5);
    bRes = ( arrLines.GetCount() == (LISTSIZE - 1) );
    }

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  if (bRes)
    {
    logEntry.m_szObjectName = _T("CArrayPtr<TCHAR*>::RemoveAll()");
    arrLines.RemoveAll();
    bRes = ( arrLines.IsEmpty() );
    }
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
 * $Log: TestArray.cpp,v $
 * Revision 1.1  2009/07/15 20:53:04  ddarko
 * Test CArray
 *
 *****************************************************************************/
