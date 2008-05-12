/*$Workfile: TsCString.cpp$: implementation file
  $Revision: 4$ $Date: 2002-08-19 10:36:43$
  $Author: Darko Kolakovic$

  Test for CString class
  Copyright: CommonSoft Inc.
  Copyright: The Open Foundation Classes
  Portions of code are extracted from The Open Foundation Classes (OFC) project.
  Jan. 2k4 Darko Kolakovic
*/
// Group=Examples


/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h" //TCHAR(), TESTENTRY

//Use Microsoft Active Template Library (ATL) CString implementation
#define _USE_ATL

#ifndef _MFC_VER //Microsoft MFC library
  //include STL implementation for CString
  #include <string> //std::basic_string template
#endif


#include "KTypedef.h"  //BOOL typedef
#include "KString.h"   //CString class

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToViewLn(const bool& bValue);
bool TsWriteToView(const int& iValue);

//TestStringClass()------------------------------------------------------------
/*Function shows how to use CString object.
  TODO:
  
  Returns: true if successful, otherwise returns false.
 
 */
bool TestStringClass()
{
TsWriteToView(_T("TestStringClass()\r\n"));
bool bRes = true;

//Test object creation
TESTENTRY logEntry =
{_T("CString::CString()"), _T("KString.h"), false};
#ifdef _USE_ATL
  //Use Microsoft Active Template Library (ATL) CString implementation
  logEntry.m_szFileName = _T("atlstr.h");
#endif

try
  {
  TsWriteToViewLn(_T("\r\nTest CString creation"));

  TsWriteToView(_T("CString str1; str1 => \"\" = "));
  CString str1;
  bRes = (_tcscmp(str1, _T("")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  
  TsWriteToView(_T("CString str2(\"String\") => "));
  CString str2(_T("String"));
  bRes = (_tcscmp(str2, _T("String")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  
  TsWriteToView(_T("CString str3('A', 10) => "));
  CString str3(_T('A'), 10);
  bRes = (_tcscmp(str3, _T("AAAAAAAAAA")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("CString str4(\"Abcdef\", 3) => "));
  CString str4(_T("Abcdef"), 3);
  bRes = (_tcscmp(str4, _T("Abc")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("CString str5(str2) => "));
  CString str5( str2 );
  bRes = (_tcscmp(str5, _T("String")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Show all the different kinds of initialization
  TsWriteToViewLn(_T("\r\nAssignment"));
  logEntry.m_bResult = false;
  logEntry.m_szObjectName = _T("CString::operator=()");
  
  TsWriteToView(_T("str1 = str4 => "));
  str1 = str4;
  bRes = (_tcscmp(str1, _T("Abc")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1 = 'Z' => "));
  str1 = _T('Z');
  bRes = (_tcscmp(str1, _T("Z")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1 = (const unsigned char*)\"xyz\" => "));
  str1 = (const unsigned char*)"xyz";
  bRes = (_tcscmp(str1, _T("xyz")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  
  TsWriteToView(_T("str1 = \"pqr\" => "));
  str1 = _T("pqr");
  bRes = (_tcscmp(str1, _T("pqr")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  
  //Show the element and addition operators
  TsWriteToViewLn(_T("\r\nOperators: [],+,+="));
  logEntry.m_bResult = false;
  logEntry.m_szObjectName = _T("CString::operator[]()");

  TsWriteToView(_T("str4[0]:A, str4[1]:b,str4[2]:c => "));
  bRes = ((str4[0] == _T('A')) && (str4[1] == _T('b')) && (str4[2] == _T('c')));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  
  logEntry.m_szObjectName = _T("CString operator+(a, b)");
  #ifdef _USE_ATL
    //Use Microsoft Active Template Library (ATL) CString implementation
    logEntry.m_szFileName = _T("cstringt.h");
  #endif
  
  TsWriteToView(_T("str1 = str2 + str3 => "));
  str1 = str2 + str3;
  bRes = (_tcscmp(str1, _T("StringAAAAAAAAAA")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1 = str2 + 'Z' => "));
  str1 = str2 + _T('Z');
  bRes = (_tcscmp(str1, _T("StringZ")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1 = 'Q' + str2 => "));
  str1 = _T('Q') + str2;
  bRes = (_tcscmp(str1, _T("QString")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  
  TsWriteToView(_T("str1 = str2 + \"XYZ\" => "));
  str1 = str2 + _T("XYZ");
  bRes = (_tcscmp(str1, _T("StringXYZ")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1 = \"ABC\" + str2 => "));
  str1 = _T("ABC") + str2;
  bRes = (_tcscmp(str1, _T("ABCString")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  
  logEntry.m_szObjectName = _T("CString::operator+=()");
  #ifdef _USE_ATL
    //Use Microsoft Active Template Library (ATL) CString implementation
    logEntry.m_szFileName = _T("atlstr.h");
  #endif

  TsWriteToView(_T("str1 += str2 1=> "));
  str1 += str2;
  bRes = (_tcscmp(str1, _T("ABCStringString")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1 += 'W' => "));
  str1 += _T('W');
  bRes = (_tcscmp(str1, _T("ABCStringStringW")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1 += \"XYZ\" => "));
  str1 += _T("XYZ");
  bRes = (_tcscmp(str1, _T("ABCStringStringWXYZ")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Miscellaneous methods
  TsWriteToViewLn(_T("\r\nMiscellaneous methods"));

  logEntry.m_szObjectName = _T("CString::GetLength()");
  TsWriteToView(_T("str2.GetLength() = "));
  int iTmp1 = str2.GetLength();
  TsWriteToView(iTmp1);
  TsWriteToView(_T(" => "));
  bRes = (iTmp1 == (int)_tcsclen(str2));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
 

  logEntry.m_szObjectName = _T("CString::Empty()");
  TsWriteToView(_T("str1.Empty(); => "));
  str1.Empty();
  bRes = ((str1.GetLength() == 0) && (_tcscmp(str1, _T("")) == 0));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::IsEmpty()");
  TsWriteToView(_T("str1.IsEmpty() => "));
  bool bTmp1 = str1.IsEmpty();
  bool bTmp2 = str2.IsEmpty();
  bRes = ((bTmp1 == true) && (bTmp2 == false));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  
  logEntry.m_szObjectName = _T("CString::GetAt()");
  TsWriteToView(_T("str2.GetAt(5) => "));
  TCHAR chTmp = str2.GetAt(5);
  bRes = (chTmp == _T('g'));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::SetAt()");
  TsWriteToView(_T("str2.SetAt(5, 'k') => "));
  str2.SetAt(5, _T('k'));
  bRes = (_tcscmp(str2, _T("Strink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Comparison methods
  TsWriteToViewLn(_T("\r\nComparison methods"));

  logEntry.m_szObjectName = _T("CString::Compare()");
  TsWriteToView(_T("str2.Compare(\"Strink\") => "));
  iTmp1 = str2.Compare(_T("Strink"));
  int iTmp2 = str2.Compare(_T("strink"));
  int iTmp3 = str2.Compare(_T("String"));
  bRes = ((iTmp1 == 0) && (iTmp2 < 0) && (iTmp3 > 0));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::CompareNoCase()");
  TsWriteToView(_T("str2.CompareNoCase(\"Strink\") => "));
  iTmp1 = str2.CompareNoCase(_T("Strink"));
  iTmp2 = str2.CompareNoCase(_T("strinK"));
  iTmp3 = str2.CompareNoCase(_T("StrinG"));
  bRes = ((iTmp1 == 0) && (iTmp2 == 0) && (iTmp3 > 0));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Test arranging in a proper sequence
  TsWriteToViewLn(_T("\r\nArranging in a proper sequence"));
  TsWriteToViewLn(_T("(locale specific methods; result varies with implementation)"));
  logEntry.m_szObjectName = _T("CString::Collate()");
  TsWriteToView(_T("str2.Collate(\"Strink\") => "));
  iTmp1 = str2.Collate(_T("Strink"));
  bRes = (iTmp1 == 0);
  TsWriteToViewLn(bRes);
    
  TsWriteToView(_T("str2.Collate(\"strink\") => "));
  iTmp2 = str2.Collate(_T("strink"));
  bRes = (iTmp2 < 0);
  TsWriteToViewLn(bRes);

  TsWriteToView(_T("str2.Collate(\"Stránk\") => "));
  iTmp3 = str2.Collate(_T("Stránk"));
  bRes = (iTmp3 > 0);
  TsWriteToViewLn(bRes);
    
  //This is locale specific, but even in the original MFC it sometimes produces
  //different results than _tcscmp (or stricmp) for strings only containing
  //standard letters. This contradicts the documentation for strcoll().
  logEntry.m_bResult = true;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::CollateNoCase()");
  TsWriteToView(_T("str2.CollateNoCase(\"Strink\") => "));
  iTmp1 = str2.CollateNoCase(_T("Strink"));
  bRes = (iTmp1 == 0);
  TsWriteToViewLn(bRes);

  TsWriteToView(_T("str2.CollateNoCase(\"strinK\") => "));
  iTmp2 = str2.CollateNoCase(_T("strinK"));
  bRes = (iTmp2 == 0);
  TsWriteToViewLn(bRes);

  TsWriteToView(_T("str2.CollateNoCase(\"Stránk\") => "));
  iTmp3 = str2.CollateNoCase(_T("Stránk"));
  bRes = (iTmp3 > 0);
  TsWriteToViewLn(bRes);

  //This is locale specific, but even in the original MFC it sometimes produces
  //different results than _tcscmp (or stricmp) for strings only containing
  //standard letters. This contradicts the documentation for strcoll().
  logEntry.m_bResult = true;
  LogTest(&logEntry);

  //Substring methods
  TsWriteToViewLn(_T("\r\nSubstring methods"));

  logEntry.m_szObjectName = _T("CString::Mid()");
  TsWriteToView(_T("str2.Mid(0) => "));
  str1 = str2.Mid(0);
  bRes = (_tcscmp(str1, _T("Strink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Mid(3) => "));
  str1 = str2.Mid(3);
  bRes = (_tcscmp(str1, _T("ink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Mid(5) => "));
  str1 = str2.Mid(5);
  bRes = (_tcscmp(str1, _T("k")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  //MFC Allows up to 0 length remaining
  TsWriteToView(_T("str2.Mid(6) => "));
  str1 = str2.Mid(6);
  bRes = (_tcscmp(str1, _T("")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Mid(0, 3) => "));
  str1 = str2.Mid(0, 3);
  bRes = (_tcscmp(str1, _T("Str")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Mid(3, 2) => "));
  str1 = str2.Mid(3, 2);
  bRes = (_tcscmp(str1, _T("in")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Mid(3, 0) => "));
  str1 = str2.Mid(3, 0);
  bRes = (_tcscmp(str1, _T("")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Mid(5, 3) => "));
  str1 = str2.Mid(5, 3);
  bRes = (_tcscmp(str1, _T("k")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  //MFC Allows up to 0 length remaining
  TsWriteToView(_T("str2.Mid(6, 3) => "));
  str1 = str2.Mid(6, 3);
  bRes = (_tcscmp(str1, _T("")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::Left()");
  TsWriteToView(_T("str2.Left(0) => "));
  str1 = str2.Left(0);
  bRes = (_tcscmp(str1, _T("")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Left(3) => "));
  str1 = str2.Left(3);
  bRes = (_tcscmp(str1, _T("Str")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Left(6) => "));
  str1 = str2.Left(6);
  bRes = (_tcscmp(str1, _T("Strink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Left(7) => "));
  str1 = str2.Left(7);
  bRes = (_tcscmp(str1, _T("Strink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::Right()");
  TsWriteToView(_T("str2.Right(0) => "));
  str1 = str2.Right(0);
  bRes = (_tcscmp(str1, _T("")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Right(3) => "));
  str1 = str2.Right(3);
  bRes = (_tcscmp(str1, _T("ink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Right(6) => "));
  str1 = str2.Right(6);
  bRes = (_tcscmp(str1, _T("Strink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Right(7) => "));
  str1 = str2.Right(7);
  bRes = (_tcscmp(str1, _T("Strink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::SpanIncluding()");
  TsWriteToView(_T("str2.SpanIncluding(\"RSTrst\") => "));
  str1 = str2.SpanIncluding(_T("RSTrst"));
  bRes = (_tcscmp(str1, _T("Str")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::SpanExcluding()");
  TsWriteToView(_T("str2.SpanExcluding(\"IGHigh\") => "));
  str1 = str2.SpanExcluding(_T("IGHigh"));
  bRes = (_tcscmp(str1, _T("Str")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Modification methods
  TsWriteToViewLn(_T("\r\nModification methods"));

  logEntry.m_szObjectName = _T("CString::MakeUpper()");
  TsWriteToView(_T("str1.MakeUpper() => "));
  str1 = _T("Abc123 Def");
  str1.MakeUpper();
  bRes = (_tcscmp(str1, _T("ABC123 DEF")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::MakeLower()");
  TsWriteToView(_T("str1.MakeLower() => "));
  str1 = _T("Abc123 Def");
  str1.MakeLower();
  bRes = (_tcscmp(str1, _T("abc123 def")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::MakeReverse()");
  TsWriteToView(_T("str1.MakeReverse() => "));
  str1 = _T("Abc123 Def");
  str1.MakeReverse();
  bRes = (_tcscmp(str1, _T("feD 321cbA")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::Replace()");
  TsWriteToView(_T("str2.Replace('k', 'g') => "));
  str2.Replace(_T('k'), _T('g'));
  bRes = (_tcscmp(str2, _T("String")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1.Replace(\"large\", \"HUGE\") => "));
  str1 = _T("This a very large string.\r\n");
  str1 += _T("We will test the function 'Replace'\r\n");
  str1 += _T("with this large string, large, large\r\n");
  str1 += _T("dfsd fsd fds dsf large dsdlkslkd large  jfdfjds\r\n");
  str1.Replace(_T("large"), _T("HUGE"));
  str3 = _T("This a very HUGE string.\r\nWe will test the function 'Replace'\r\nwith this HUGE string, HUGE, HUGE\r\ndfsd fsd fds dsf HUGE dsdlkslkd HUGE  jfdfjds\r\n");
  bRes = (_tcscmp(str1, str3) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::Remove()");
  TsWriteToView(_T("str2.Remove('i') => "));
  str2.Remove(_T('i'));
  bRes = (_tcscmp(str2, _T("Strng")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::Insert()");
  TsWriteToView(_T("str2.Insert(3, 'i') => "));
  str2.Insert(3, _T('i'));
  bRes = (_tcscmp(str2, _T("String")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Insert(6, \" Test\") => "));
  str2.Insert(6, _T(" Test"));
  bRes = (_tcscmp(str2, _T("String Test")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Insert(6, \" Quick\") => "));
  str2.Insert(6, _T(" Quick"));
  bRes = (_tcscmp(str2, _T("String Quick Test")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::Delete()");
  TsWriteToView(_T("str2.Delete(6, 6) => "));
  str2.Delete(6, 6);
  bRes = (_tcscmp(str2, _T("String Test")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Delete(6, 5) => "));
  str2.Delete(6, 5);
  bRes = (_tcscmp(str2, _T("String")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::TrimLeft()");
  TsWriteToView(_T("str1.TrimLeft() => "));
  str1 = _T("\r\n\t This is a test \t\r\n");
  str1.TrimLeft();
  bRes = (_tcscmp(str1, _T("This is a test \t\r\n")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1.TrimLeft(\" -*\") => "));
  str1 = _T("-*-* Test *-*-");
  str1.TrimLeft(_T(" -*"));
  bRes = (_tcscmp(str1, _T("Test *-*-")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1.TrimLeft('-') => "));
  str1 = _T("--Test--");
  str1.TrimLeft(_T('-'));
  bRes = (_tcscmp(str1, _T("Test--")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::TrimRight()");
  TsWriteToView(_T("str1.TrimRight()=> "));
  str1 = "\r\n\t This is a test \t\r\n";
  str1.TrimRight();
  bRes = (_tcscmp(str1,_T( "\r\n\t This is a test")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1.TrimRight(\" -*\") => "));
  str1 = _T("-*-* Test *-*-");
  str1.TrimRight(_T(" -*"));
  bRes = (_tcscmp(str1, _T("-*-* Test")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1.TrimRight('-') => "));
  str1 = _T("--Test--");
  str1.TrimRight(_T('-'));
  bRes = (_tcscmp(str1, _T("--Test")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Find methods
  TsWriteToViewLn(_T("\r\nFind methods\r\n"));

  logEntry.m_szObjectName = _T("CString::Find()");
  TsWriteToView(_T("str2.Find('i') => "));
  iTmp1 = str2.Find(_T('i'));
  bRes = (iTmp1 == 3);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str2.Find(\"ng\") => "));
  iTmp1 = str2.Find(_T("ng"));
  bRes = (iTmp1 == 4);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1.Find('e', 3) => "));
  str1 = _T("Test the test");
  iTmp1 = str1.Find(_T('e'), 3);
  bRes = (iTmp1 == 7);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("str1.Find(\"est\", 3) => "));
  iTmp1 = str1.Find(_T("est"), 3);
  bRes = (iTmp1 == 10);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::ReverseFind()");
  TsWriteToView(_T("str1.ReverseFind('h') => "));
  iTmp1 = str1.ReverseFind(_T('h'));
  bRes = (iTmp1 == 6);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::FindOneOf()");
  TsWriteToView(_T("str1.FindOneOf(\"ghi\") => "));
  iTmp1 = str1.FindOneOf(_T("ghi"));
  bRes = (iTmp1 == 6);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Buffer methods
  TsWriteToViewLn(_T("\r\nBuffer methods\r\n"));

  logEntry.m_szObjectName = _T("CString::GetBuffer(0)");
  str2.GetBuffer(0);
  str2.ReleaseBuffer();
  iTmp1 = str2.GetLength();
  TsWriteToView(_T("str2.GetBuffer(0);\r\nstr2.ReleaseBuffer();\r\n  [len= "));
  TsWriteToView(iTmp1);
  TsWriteToView(_T("] => "));
  bRes = (iTmp1 == (int)_tcsclen(str2));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::GetBuffer()");
  TsWriteToView(_T("pszBuf = str1.GetBuffer(100) => "));
  LPTSTR pszBuf = str1.GetBuffer(100);
  LPCTSTR szTest31 = _T("Testing that it allocates as it should!");
  _tcscpy(pszBuf, szTest31);
  bRes = (pszBuf != NULL);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::ReleaseBuffer()");
  str1.ReleaseBuffer(100);
  iTmp1 = str1.GetLength();
  TsWriteToView(_T("str1.ReleaseBuffer(100);\r\n  [len= "));
  TsWriteToView(iTmp1);
  TsWriteToView(_T("] => "));
  bRes = (_tcscmp(str1, szTest31) == 0 && iTmp1 == 100);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::GetBufferSetLength()");
  pszBuf = str1.GetBufferSetLength(50);
  LPCTSTR szTest32 = _T("Testing!");
  _tcscpy(pszBuf, szTest32);
  str1.ReleaseBuffer(50);
  iTmp1 = str1.GetLength();
  TsWriteToView(_T("pszBuf = str1.GetBufferSetLength(50);\r\nstr1.ReleaseBuffer(50);\r\n  [len= "));
  TsWriteToView(iTmp1);
  TsWriteToView(_T("] => "));
  bRes = (_tcscmp(str1, szTest32) == 0 && iTmp1 == 50);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::LockBuffer()");
  pszBuf = str1.LockBuffer();
  LPCTSTR szTest33 = _T("Test (Un)LockBuffer!");
  _tcscpy(pszBuf, szTest33);
  str1.ReleaseBuffer(50);
  iTmp1 = str1.GetLength();
  TsWriteToView(_T("str1.LockBuffer();\r\nstr1.UnlockBuffer();\r\n  [len= "));
  TsWriteToView(iTmp1);
  TsWriteToView(_T("] => "));
  bRes = (_tcscmp(str1, szTest33) == 0 && iTmp1 == 50);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  
//TODO: Test FreeExtra()

  //SysString methods
  TsWriteToView(_T("\r\nWindows specific methods"));

  #ifdef _WIN32
    logEntry.m_szObjectName = _T("CString::AllocSysString()");
    TsWriteToView(_T("bstr = str1.AllocSysString() => "));
    str1 = ("Testing");
    BSTR bstr = str1.AllocSysString();
    char szBuf[40];
    wcstombs(szBuf, bstr, sizeof(szBuf));
    bRes = (strcmp(szBuf, str1) == 0);
    TsWriteToViewLn(bRes);
    if (!bRes)
      {
      ::SysFreeString(bstr);
      goto TESTEXIT;
      }
    logEntry.m_bResult = bRes;
    LogTest(&logEntry);

    logEntry.m_szObjectName = _T("CString::SetSysString()");
    TsWriteToView(_T("str2.SetSysString(&bstr) => "));
    str2 = ("Test #2");
    str2.SetSysString(&bstr);
    wcstombs(szBuf, bstr, sizeof(szBuf));
    ::SysFreeString(bstr);
    bRes = (strcmp(szBuf, str2) == 0);
    TsWriteToViewLn(bRes);
    if (!bRes)
      goto TESTEXIT;
    logEntry.m_bResult = bRes;
    LogTest(&logEntry);


    logEntry.m_szObjectName = _T("CString::LoadString()");
    TsWriteToView(_T("str1.LoadString(IDS_TESTSTRING) => "));
    str1.LoadString(IDS_TESTSTRING);
    extern LPCTSTR g_szTest;
    bRes = (_tcscmp(str1, g_szTest[0]) == 0);
    TsWriteToViewLn(bRes);
    if (!bRes)
      goto TESTEXIT;
    logEntry.m_bResult = bRes;
    LogTest(&logEntry);

  #endif //_WIN32
  
  #ifndef _UNICODE
    //ATL: The functions are not available if _UNICODE is defined.
    TsWriteToView(_T("str1.AnsiToOem() => "));
    str1.AnsiToOem();
    bRes = (_tcscmp(str1, (char*)g_szTestStringOem) == 0);
    TsWriteToViewLn(bRes);
    if (!bRes)
      goto TESTEXIT;
    logEntry.m_bResult = bRes;
    LogTest(&logEntry);

    TsWriteToView(_T("str1.OemToAnsi() => "));
    str1.OemToAnsi();
    bRes = (_tcscmp(str1, (char*)g_szTestString) == 0);
    TsWriteToViewLn(bRes);
    if (!bRes)
      goto TESTEXIT;
    logEntry.m_bResult = bRes;
    LogTest(&logEntry);
  #endif //_UNICODE
  }
catch(...)
  {
  bRes = false;
  }

TESTEXIT:

logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

//////////////////////////////////////////////////////////////////////////////

/*****************************************************************************
 * $Log: $
 *
 *mm-dd-yy  ver   who  what
 *10-26-03  0.10 William D. Herndon  Created from cstring_test.cpp
 *05-30-04  0.20 William D. Herndon  Changed OfcTest.h to StdAfx.h
 *
 *****************************************************************************/

/************************************************************************
  T h e   O p e n   F o u n d a t i o n    C l a s s e s
  ------------------------------------------------------------------------
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  ------------------------------------------------------------------------
  Copyright (c) 2000-04 The Open Foundation Classes
  Copyright (c) 2003-04 William D. Herndon
**************************************************************************/
