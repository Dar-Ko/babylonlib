/*$Workfile: TestStringHandler.cpp$: implementation file
  $Revision: 2$ $Date: 2004-06-06 21:55:28$
  $Author: Darko$

  Test basic string class
  Copyright: CommonSoft Inc.
  2004-06-04 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "KStringHandler.h" //CStringHandler class

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToView(const int& iValue);
extern bool TsWriteToViewLn(const int& iValue);

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Validates CStringHandler class creation ant other methods.

  Returns: true if successful, otherwise returns false.
 */
bool TestStringHandler()
{
TsWriteToView(_T("TestStringHandler()\r\n"));
  //Test default constructor
TESTENTRY logEntry = 
  {_T("CStringHandler::CStringHandler()"), _T("KStringHandler.h"), false};

bool bRes = true;
CStringHandler strText;
bRes = (strText.GetLength() == 0);

  //Test out-of-the-range index
#ifndef _DEBUG
  //Ignore ASSERT in _DEBUG mode
  if (bRes) 
    bRes = strText[2] == _T('\0');  
  if (bRes) 
    bRes = strText[-2] == _T('\0');
#endif

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

  //Test string assignment
if (bRes)
  {
  logEntry.m_szObjectName = _T("CStringHandler::operator=(LPCTSTR)");
  logEntry.m_szFileName = _T("KStringHandler.cpp");

  strText = _T("ABCDEFGH12345678\r\n");
  TsWriteToView((LPCTSTR)strText);
  TsWriteToView(_T(" is "));
  TsWriteToView(strText.GetLength());
  TsWriteToViewLn(_T(" characters long."));

    //If string length is right, validate content
  bRes = (strText.GetLength() == 18); 
  if (bRes)
    {
    bRes = (_tcscmp(_T("ABCDEFGH12345678\r\n"), (LPCTSTR)strText) == 0);
    }

    //Enlarge content
  if (bRes)
    {
    strText = _T("abcdefghijklmnopqrstuvwxyz\r\n");
    TsWriteToView((LPCTSTR)strText);
    TsWriteToView(_T(" is "));
    TsWriteToView(strText.GetLength());
    TsWriteToViewLn(_T(" characters long."));

      //If string length is right, validate content
    bRes = (strText.GetLength() == 28); 
    if (bRes)
      {
      bRes = (_tcscmp(_T("abcdefghijklmnopqrstuvwxyz\r\n"), (LPCTSTR)strText) == 0);
      }
    }

    //Shrink content
  if (bRes)
    {
    strText = _T("0123456789\r\n");
    TsWriteToView((LPCTSTR)strText);
    TsWriteToView(_T(" is "));
    TsWriteToView(strText.GetLength());
    TsWriteToViewLn(_T(" characters long."));

      //If string length is right, validate content
    bRes = (strText.GetLength() == 12); 
    if (bRes)
      {
      bRes = (_tcscmp(_T("0123456789\r\n"), (LPCTSTR)strText) == 0);
      }
    }

    //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

  //Test copy constructor
TsWriteToViewLn(_T("Make a copy of the text"));
CStringHandler strOtherText(strText);
if (bRes)
  {
  logEntry.m_szObjectName = _T("CStringHandler::CStringHandler(CStringHandler)");
  logEntry.m_szFileName = _T("KStringHandler.cpp");

  bRes = (strOtherText.GetLength() == strText.GetLength());
  if (bRes)
    {
    bRes = (_tcscmp((LPCTSTR)strOtherText, (LPCTSTR)strText) == 0);
    }

      //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

  //Test indexed access
if(bRes)
  {
  logEntry.m_szObjectName = _T("CStringHandler::operator[]");
  logEntry.m_szFileName = _T("KStringHandler.cpp");

  bRes = (strOtherText[5] == _T('5'));

  #ifndef _DEBUG
    //Ignore ASSERT in _DEBUG mode
    if (bRes)
      {
      bRes = (strOtherText[25] == _T('\0'));
      }
  #endif
      //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

  //Test replacement
if(bRes)
  {
  logEntry.m_szObjectName = _T("CStringHandler::SetAt()");
  logEntry.m_szFileName = _T("KStringHandler.cpp");

  //Test out-of-range access
  #ifndef _DEBUG
    //Ignore ASSERT in _DEBUG mode
    strOtherText.SetAt(20, _T('B'));
  #endif
  bRes = (_tcscmp(_T("0123456789\r\n"), (LPCTSTR)strOtherText) == 0);
  if (bRes)
    {
    strOtherText.SetAt(5, _T('A'));
    TsWriteToView(_T("Text[5] = A -> "));
    TsWriteToViewLn((LPCTSTR)strOtherText);

    bRes = ((strOtherText[5] == _T('A')) &&
           (_tcscmp(_T("01234A6789\r\n"), (LPCTSTR)strOtherText) == 0));
    }

    //Cut the text
  if (bRes)
    {
    strOtherText.SetAt(5, _T('\0'));

    TsWriteToView(_T("Length of "));
    TsWriteToView((LPCTSTR)strOtherText);
    TsWriteToView(_T(" is "));
    TsWriteToViewLn(strOtherText.GetLength());

    bRes = ((strOtherText.GetLength() == 5) &&
           (_tcscmp(_T("01234"), (LPCTSTR)strOtherText) == 0));
    }
      //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

  //Test comparison
if(bRes)
  {
  logEntry.m_szObjectName = _T("operator<(CStringHandler)");
  logEntry.m_szFileName = _T("KStringHandler.h");

  bRes = strOtherText < strText;

  TsWriteToView((LPCTSTR)strOtherText);
  if (bRes)
     TsWriteToView(_T(" is lesser than "));
  else
     TsWriteToView(_T(" is bigger than "));
  TsWriteToViewLn((LPCTSTR)strText);

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

      //Test equality
  logEntry.m_szObjectName = _T("operator==(CStringHandler)");
  logEntry.m_szFileName = _T("KStringHandler.h");

  strText = strOtherText;
  bRes = (strOtherText == strText);

    //Test comparison with NULL pointer
  if (bRes)
    {
    bRes = (strText != NULL);
    TsWriteToView((LPCTSTR)strText);
    if (bRes)
      TsWriteToView(_T(" is not "));
    else
      TsWriteToView(_T(" is "));
    TsWriteToViewLn(_T("<null>."));
    }

    //Test if it is equal to self
  if (bRes)
    {
    bRes = (strText == strText);
    }
      //Write test log
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  }

TsWriteToView(LOG_EOT);
TsWriteToView(_T("\r\n"));
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-06-06 21:55:28  Darko           Added new test
 *       cases
 *  1    Biblioteka1.0         2004-06-04 16:47:10  Darko           
 * $
 *****************************************************************************/
