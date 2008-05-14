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
#ifdef _USE_STL
  #ifdef _MSC_VER
  //MSVC/C++
    #pragma include_alias("stdafx.h", "stdstl.h")
  #endif
#else
  //Use Microsoft Active Template Library (ATL) CString implementation
  #define _USE_ATL
#endif

#include "stdafx.h" //TCHAR(), TESTENTRY


#ifndef _MFC_VER //Microsoft MFC library
  //include STL implementation for CString
  #include <string> //std::basic_string template
#endif

#ifdef _WIN32
  #include <oleauto.h>  //SysFreeString()
  #include "Resource.h" //IDS_TESTSTRING
#endif
#include "KTypedef.h"  //BOOL typedef
#include "KString.h"   //CString class

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToViewLn(const bool& bValue);
bool TsWriteToView(const int& iValue);

extern "C" TCHAR g_szTestStringOem[];
extern "C" TCHAR g_szTestString[];
extern "C" LPCTSTR g_szTest[];


//TestStringClass()------------------------------------------------------------
/*Test different methods of the dynamic string class.
  Function shows how to use CString object.

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

  TsWriteToView(_T("CString strTest0; strTest0 => \"\" = "));
  CString strTest0;
  bRes = (_tcscmp(strTest0, _T("")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("CString strTest1(\"String\") => "));
  CString strTest1(_T("String"));
  bRes = (_tcscmp(strTest1, _T("String")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("CString strTest2('A', 10) => "));
  CString strTest2(_T('A'), 10);
  bRes = (_tcscmp(strTest2, _T("AAAAAAAAAA")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("CString strTest3(\"Abcdef\", 3) => "));
  CString strTest3(_T("Abcdef"), 3);
  bRes = (_tcscmp(strTest3, _T("Abc")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("CString strTest4(strTest1) => "));
  CString strTest4( strTest1 );
  bRes = (_tcscmp(strTest4, _T("String")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Show all the different kinds of initialization
  TsWriteToViewLn(_T("\r\nAssignment"));
  logEntry.m_bResult = false;
  logEntry.m_szObjectName = _T("CString::operator=()");

  TsWriteToView(_T("strTest0 = strTest3 => "));
  strTest0 = strTest3;
  bRes = (_tcscmp(strTest0, _T("Abc")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0 = 'Z' => "));
  strTest0 = _T('Z');
  bRes = (_tcscmp(strTest0, _T("Z")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0 = (const unsigned char*)\"xyz\" => "));
  strTest0 = (const unsigned char*)"xyz";
  bRes = (_tcscmp(strTest0, _T("xyz")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0 = \"pqr\" => "));
  strTest0 = _T("pqr");
  bRes = (_tcscmp(strTest0, _T("pqr")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Show the element and addition operators
  TsWriteToViewLn(_T("\r\nOperators: [],+,+="));
  logEntry.m_bResult = false;
  logEntry.m_szObjectName = _T("CString::operator[]()");

  TsWriteToView(_T("strTest3[0]:A, strTest3[1]:b,strTest3[2]:c => "));
  bRes = ((strTest3[0] == _T('A')) &&
          (strTest3[1] == _T('b')) &&
          (strTest3[2] == _T('c')));
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

  TsWriteToView(_T("strTest0 = strTest1 + strTest2 => "));
  strTest0 = strTest1 + strTest2;
  bRes = (_tcscmp(strTest0, _T("StringAAAAAAAAAA")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0 = strTest1 + 'Z' => "));
  strTest0 = strTest1 + _T('Z');
  bRes = (_tcscmp(strTest0, _T("StringZ")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0 = 'Q' + strTest1 => "));
  strTest0 = _T('Q') + strTest1;
  bRes = (_tcscmp(strTest0, _T("QString")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0 = strTest1 + \"XYZ\" => "));
  strTest0 = strTest1 + _T("XYZ");
  bRes = (_tcscmp(strTest0, _T("StringXYZ")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0 = \"ABC\" + strTest1 => "));
  strTest0 = _T("ABC") + strTest1;
  bRes = (_tcscmp(strTest0, _T("ABCString")) == 0);
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

  TsWriteToView(_T("strTest0 += strTest1 1=> "));
  strTest0 += strTest1;
  bRes = (_tcscmp(strTest0, _T("ABCStringString")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0 += 'W' => "));
  strTest0 += _T('W');
  bRes = (_tcscmp(strTest0, _T("ABCStringStringW")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0 += \"XYZ\" => "));
  strTest0 += _T("XYZ");
  bRes = (_tcscmp(strTest0, _T("ABCStringStringWXYZ")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Miscellaneous methods
  TsWriteToViewLn(_T("\r\nMiscellaneous methods"));

  logEntry.m_szObjectName = _T("CString::GetLength()");
  TsWriteToView(_T("strTest1.GetLength() = "));
  int iTmp1 = strTest1.GetLength();
  TsWriteToView(iTmp1);
  TsWriteToView(_T(" => "));
  bRes = (iTmp1 == (int)_tcsclen(strTest1));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);


  logEntry.m_szObjectName = _T("CString::Empty()");
  TsWriteToView(_T("strTest0.Empty(); => "));
  strTest0.Empty();
  bRes = ((strTest0.GetLength() == 0) && (_tcscmp(strTest0, _T("")) == 0));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::IsEmpty()");
  TsWriteToView(_T("strTest0.IsEmpty() => "));
  bool bTmp1 = strTest0.IsEmpty();
  bool bTmp2 = strTest1.IsEmpty();
  bRes = ((bTmp1 == true) && (bTmp2 == false));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::GetAt()");
  TsWriteToView(_T("strTest1.GetAt(5) => "));
  TCHAR chTmp = strTest1.GetAt(5);
  bRes = (chTmp == _T('g'));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::SetAt()");
  TsWriteToView(_T("strTest1.SetAt(5, 'k') => "));
  strTest1.SetAt(5, _T('k'));
  bRes = (_tcscmp(strTest1, _T("Strink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Comparison methods
  TsWriteToViewLn(_T("\r\nComparison methods"));

  logEntry.m_szObjectName = _T("CString::Compare()");
  TsWriteToView(_T("strTest1.Compare(\"Strink\") => "));
  iTmp1 = strTest1.Compare(_T("Strink"));
  int iTmp2 = strTest1.Compare(_T("strink"));
  int iTmp3 = strTest1.Compare(_T("String"));
  bRes = ((iTmp1 == 0) && (iTmp2 < 0) && (iTmp3 > 0));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::CompareNoCase()");
  TsWriteToView(_T("strTest1.CompareNoCase(\"Strink\") => "));
  iTmp1 = strTest1.CompareNoCase(_T("Strink"));
  iTmp2 = strTest1.CompareNoCase(_T("strinK"));
  iTmp3 = strTest1.CompareNoCase(_T("StrinG"));
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
  TsWriteToView(_T("strTest1.Collate(\"Strink\") => "));
  iTmp1 = strTest1.Collate(_T("Strink"));
  bRes = (iTmp1 == 0);
  TsWriteToViewLn(bRes);

  TsWriteToView(_T("strTest1.Collate(\"strink\") => "));
  iTmp2 = strTest1.Collate(_T("strink"));
  bRes = (iTmp2 < 0);
  TsWriteToViewLn(bRes);

  TsWriteToView(_T("strTest1.Collate(\"Stránk\") => "));
  iTmp3 = strTest1.Collate(_T("Stránk"));
  bRes = (iTmp3 > 0);
  TsWriteToViewLn(bRes);

  //This is locale specific, but even in the original MFC it sometimes produces
  //different results than _tcscmp (or stricmp) for strings only containing
  //standard letters. This contradicts the documentation for strcoll().
  logEntry.m_bResult = true;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::CollateNoCase()");
  TsWriteToView(_T("strTest1.CollateNoCase(\"Strink\") => "));
  iTmp1 = strTest1.CollateNoCase(_T("Strink"));
  bRes = (iTmp1 == 0);
  TsWriteToViewLn(bRes);

  TsWriteToView(_T("strTest1.CollateNoCase(\"strinK\") => "));
  iTmp2 = strTest1.CollateNoCase(_T("strinK"));
  bRes = (iTmp2 == 0);
  TsWriteToViewLn(bRes);

  TsWriteToView(_T("strTest1.CollateNoCase(\"Stránk\") => "));
  iTmp3 = strTest1.CollateNoCase(_T("Stránk"));
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
  TsWriteToView(_T("strTest1.Mid(0) => "));
  strTest0 = strTest1.Mid(0);
  bRes = (_tcscmp(strTest0, _T("Strink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Mid(3) => "));
  strTest0 = strTest1.Mid(3);
  bRes = (_tcscmp(strTest0, _T("ink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Mid(5) => "));
  strTest0 = strTest1.Mid(5);
  bRes = (_tcscmp(strTest0, _T("k")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  //MFC Allows up to 0 length remaining
  TsWriteToView(_T("strTest1.Mid(6) => "));
  strTest0 = strTest1.Mid(6);
  bRes = (_tcscmp(strTest0, _T("")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Mid(0, 3) => "));
  strTest0 = strTest1.Mid(0, 3);
  bRes = (_tcscmp(strTest0, _T("Str")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Mid(3, 2) => "));
  strTest0 = strTest1.Mid(3, 2);
  bRes = (_tcscmp(strTest0, _T("in")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Mid(3, 0) => "));
  strTest0 = strTest1.Mid(3, 0);
  bRes = (_tcscmp(strTest0, _T("")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Mid(5, 3) => "));
  strTest0 = strTest1.Mid(5, 3);
  bRes = (_tcscmp(strTest0, _T("k")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  //MFC Allows up to 0 length remaining
  TsWriteToView(_T("strTest1.Mid(6, 3) => "));
  strTest0 = strTest1.Mid(6, 3);
  bRes = (_tcscmp(strTest0, _T("")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::Left()");
  TsWriteToView(_T("strTest1.Left(0) => "));
  strTest0 = strTest1.Left(0);
  bRes = (_tcscmp(strTest0, _T("")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Left(3) => "));
  strTest0 = strTest1.Left(3);
  bRes = (_tcscmp(strTest0, _T("Str")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Left(6) => "));
  strTest0 = strTest1.Left(6);
  bRes = (_tcscmp(strTest0, _T("Strink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Left(7) => "));
  strTest0 = strTest1.Left(7);
  bRes = (_tcscmp(strTest0, _T("Strink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::Right()");
  TsWriteToView(_T("strTest1.Right(0) => "));
  strTest0 = strTest1.Right(0);
  bRes = (_tcscmp(strTest0, _T("")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Right(3) => "));
  strTest0 = strTest1.Right(3);
  bRes = (_tcscmp(strTest0, _T("ink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Right(6) => "));
  strTest0 = strTest1.Right(6);
  bRes = (_tcscmp(strTest0, _T("Strink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Right(7) => "));
  strTest0 = strTest1.Right(7);
  bRes = (_tcscmp(strTest0, _T("Strink")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::SpanIncluding()");
  TsWriteToView(_T("strTest1.SpanIncluding(\"RSTrst\") => "));
  strTest0 = strTest1.SpanIncluding(_T("RSTrst"));
  bRes = (_tcscmp(strTest0, _T("Str")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::SpanExcluding()");
  TsWriteToView(_T("strTest1.SpanExcluding(\"IGHigh\") => "));
  strTest0 = strTest1.SpanExcluding(_T("IGHigh"));
  bRes = (_tcscmp(strTest0, _T("Str")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Modification methods
  TsWriteToViewLn(_T("\r\nModification methods"));

  logEntry.m_szObjectName = _T("CString::MakeUpper()");
  TsWriteToView(_T("strTest0.MakeUpper() => "));
  strTest0 = _T("Abc123 Def");
  strTest0.MakeUpper();
  bRes = (_tcscmp(strTest0, _T("ABC123 DEF")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::MakeLower()");
  TsWriteToView(_T("strTest0.MakeLower() => "));
  strTest0 = _T("Abc123 Def");
  strTest0.MakeLower();
  bRes = (_tcscmp(strTest0, _T("abc123 def")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::MakeReverse()");
  TsWriteToView(_T("strTest0.MakeReverse() => "));
  strTest0 = _T("Abc123 Def");
  strTest0.MakeReverse();
  bRes = (_tcscmp(strTest0, _T("feD 321cbA")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::Replace()");
  TsWriteToView(_T("strTest1.Replace('k', 'g') => "));
  strTest1.Replace(_T('k'), _T('g'));
  bRes = (_tcscmp(strTest1, _T("String")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0.Replace(\"large\", \"HUGE\") => "));
  strTest0 = _T("This a very large string.\r\n");
  strTest0 += _T("We will test the function 'Replace'\r\n");
  strTest0 += _T("with this large string, large, large\r\n");
  strTest0 += _T("dfsd fsd fds dsf large dsdlkslkd large  jfdfjds\r\n");
  strTest0.Replace(_T("large"), _T("HUGE"));
  strTest2 = _T("This a very HUGE string.\r\nWe will test the function 'Replace'\r\nwith this HUGE string, HUGE, HUGE\r\ndfsd fsd fds dsf HUGE dsdlkslkd HUGE  jfdfjds\r\n");
  bRes = (_tcscmp(strTest0, strTest2) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::Remove()");
  TsWriteToView(_T("strTest1.Remove('i') => "));
  strTest1.Remove(_T('i'));
  bRes = (_tcscmp(strTest1, _T("Strng")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::Insert()");
  TsWriteToView(_T("strTest1.Insert(3, 'i') => "));
  strTest1.Insert(3, _T('i'));
  bRes = (_tcscmp(strTest1, _T("String")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Insert(6, \" Test\") => "));
  strTest1.Insert(6, _T(" Test"));
  bRes = (_tcscmp(strTest1, _T("String Test")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Insert(6, \" Quick\") => "));
  strTest1.Insert(6, _T(" Quick"));
  bRes = (_tcscmp(strTest1, _T("String Quick Test")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::Delete()");
  TsWriteToView(_T("strTest1.Delete(6, 6) => "));
  strTest1.Delete(6, 6);
  bRes = (_tcscmp(strTest1, _T("String Test")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Delete(6, 5) => "));
  strTest1.Delete(6, 5);
  bRes = (_tcscmp(strTest1, _T("String")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::TrimLeft()");
  TsWriteToView(_T("strTest0.TrimLeft() => "));
  strTest0 = _T("\r\n\t This is a test \t\r\n");
  strTest0.TrimLeft();
  bRes = (_tcscmp(strTest0, _T("This is a test \t\r\n")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0.TrimLeft(\" -*\") => "));
  strTest0 = _T("-*-* Test *-*-");
  strTest0.TrimLeft(_T(" -*"));
  bRes = (_tcscmp(strTest0, _T("Test *-*-")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0.TrimLeft('-') => "));
  strTest0 = _T("--Test--");
  strTest0.TrimLeft(_T('-'));
  bRes = (_tcscmp(strTest0, _T("Test--")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::TrimRight()");
  TsWriteToView(_T("strTest0.TrimRight()=> "));
  strTest0 = "\r\n\t This is a test \t\r\n";
  strTest0.TrimRight();
  bRes = (_tcscmp(strTest0,_T( "\r\n\t This is a test")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0.TrimRight(\" -*\") => "));
  strTest0 = _T("-*-* Test *-*-");
  strTest0.TrimRight(_T(" -*"));
  bRes = (_tcscmp(strTest0, _T("-*-* Test")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0.TrimRight('-') => "));
  strTest0 = _T("--Test--");
  strTest0.TrimRight(_T('-'));
  bRes = (_tcscmp(strTest0, _T("--Test")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Find methods
  TsWriteToViewLn(_T("\r\nFind methods\r\n"));

  logEntry.m_szObjectName = _T("CString::Find()");
  TsWriteToView(_T("strTest1.Find('i') => "));
  iTmp1 = strTest1.Find(_T('i'));
  bRes = (iTmp1 == 3);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest1.Find(\"ng\") => "));
  iTmp1 = strTest1.Find(_T("ng"));
  bRes = (iTmp1 == 4);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0.Find('e', 3) => "));
  strTest0 = _T("Test the test");
  iTmp1 = strTest0.Find(_T('e'), 3);
  bRes = (iTmp1 == 7);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  TsWriteToView(_T("strTest0.Find(\"est\", 3) => "));
  iTmp1 = strTest0.Find(_T("est"), 3);
  bRes = (iTmp1 == 10);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::ReverseFind()");
  TsWriteToView(_T("strTest0.ReverseFind('h') => "));
  iTmp1 = strTest0.ReverseFind(_T('h'));
  bRes = (iTmp1 == 6);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::FindOneOf()");
  TsWriteToView(_T("strTest0.FindOneOf(\"ghi\") => "));
  iTmp1 = strTest0.FindOneOf(_T("ghi"));
  bRes = (iTmp1 == 6);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Buffer methods
  TsWriteToViewLn(_T("\r\nBuffer methods\r\n"));

  logEntry.m_szObjectName = _T("CString::GetBuffer(0)");
  strTest1.GetBuffer(0);
  strTest1.ReleaseBuffer();
  iTmp1 = strTest1.GetLength();
  TsWriteToView(_T("strTest1.GetBuffer(0);\r\nstr2.ReleaseBuffer();\r\n  [len= "));
  TsWriteToView(iTmp1);
  TsWriteToView(_T("] => "));
  bRes = (iTmp1 == (int)_tcsclen(strTest1));
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::GetBuffer()");
  TsWriteToView(_T("pszBuf = strTest0.GetBuffer(100) => "));
  LPTSTR pszBuf = strTest0.GetBuffer(100);
  LPCTSTR szTest31 = _T("Testing that it allocates as it should!");
  _tcscpy(pszBuf, szTest31);
  bRes = (pszBuf != NULL);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::ReleaseBuffer()");
  strTest0.ReleaseBuffer(100);
  iTmp1 = strTest0.GetLength();
  TsWriteToView(_T("strTest0.ReleaseBuffer(100);\r\n  [len= "));
  TsWriteToView(iTmp1);
  TsWriteToView(_T("] => "));
  bRes = (_tcscmp(strTest0, szTest31) == 0 && iTmp1 == 100);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::GetBufferSetLength()");
  pszBuf = strTest0.GetBufferSetLength(50);
  LPCTSTR szTest32 = _T("Testing!");
  _tcscpy(pszBuf, szTest32);
  strTest0.ReleaseBuffer(50);
  iTmp1 = strTest0.GetLength();
  TsWriteToView(_T("pszBuf = strTest0.GetBufferSetLength(50);\r\nstr1.ReleaseBuffer(50);\r\n  [len= "));
  TsWriteToView(iTmp1);
  TsWriteToView(_T("] => "));
  bRes = (_tcscmp(strTest0, szTest32) == 0 && iTmp1 == 50);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  logEntry.m_szObjectName = _T("CString::LockBuffer()");
  pszBuf = strTest0.LockBuffer();
  LPCTSTR szTest33 = _T("Test (Un)LockBuffer!");
  _tcscpy(pszBuf, szTest33);
  strTest0.ReleaseBuffer(50);
  iTmp1 = strTest0.GetLength();
  TsWriteToView(_T("strTest0.LockBuffer();\r\nstr1.UnlockBuffer();\r\n  [len= "));
  TsWriteToView(iTmp1);
  TsWriteToView(_T("] => "));
  bRes = (_tcscmp(strTest0, szTest33) == 0 && iTmp1 == 50);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  bRes = false;
  logEntry.m_szObjectName = _T("CString::FreeExtra()");
  TsWriteToView(_T("strTest0.FreeExtra() => "));
  //TODO: Test FreeExtra()
  TsWriteToViewLn(bRes);
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  //Comparison operators
  TsWriteToViewLn(_T("\r\nComparison operators"));

  LPCTSTR szTest[] =
    {
    _T("Abc"), // 0
    _T("Abc"), // 1
    _T("ABC"), // 2
    _T("abc"), // 3
    _T("Def")  // 4
    };
  strTest0 = szTest[0];
  strTest1 = szTest[1];
  strTest2 = szTest[2];
  strTest3 = szTest[3];
  strTest4 = szTest[4];
  const int CMPTESTCOUNT = 12;
  bool bCmpRes[2][CMPTESTCOUNT];

  logEntry.m_szObjectName = _T("CString::operator==()");
  TsWriteToView(_T("A == B => "));
  bCmpRes[0][ 0] = true ; bCmpRes[1][ 0] = (strTest0 == strTest1);
  bCmpRes[0][ 1] = false; bCmpRes[1][ 1] = (strTest2 == strTest3);
  bCmpRes[0][ 2] = false; bCmpRes[1][ 2] = (strTest0 == strTest4);
  bCmpRes[0][ 3] = false; bCmpRes[1][ 3] = (strTest4 == strTest0);
  bCmpRes[0][ 4] = true ; bCmpRes[1][ 4] = (strTest0 == szTest[0]);
  bCmpRes[0][ 5] = false; bCmpRes[1][ 5] = (strTest2 == szTest[3]);
  bCmpRes[0][ 6] = false; bCmpRes[1][ 6] = (strTest0 == szTest[4]);
  bCmpRes[0][ 7] = false; bCmpRes[1][ 7] = (strTest4 == szTest[0]);
  bCmpRes[0][ 8] = true ; bCmpRes[1][ 8] = (szTest[1] == strTest1);
  bCmpRes[0][ 9] = false; bCmpRes[1][ 9] = (szTest[2] == strTest3);
  bCmpRes[0][10] = false; bCmpRes[1][10] = (szTest[1] == strTest4);
  bCmpRes[0][11] = false; bCmpRes[1][11] = (szTest[4] == strTest1);

  bTmp1 = true;
  bRes = true;
  for (int i = 0; (i < CMPTESTCOUNT) && bRes; i++)
    bRes = (bCmpRes[0][i] == bCmpRes[1][i]);
  if (bRes)
    TsWriteToViewLn(bRes);
  else
    {
    TsWriteToView(i-1);
    TsWriteToViewLn(_T(". case failed."));
    }
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  bTmp1 = (bTmp1 && bRes);

  logEntry.m_szObjectName = _T("CString::operator!=()");
  TsWriteToView(_T("A != B => "));
  bCmpRes[0][ 0] = !true ; bCmpRes[1][ 0] = (strTest0 != strTest1);
  bCmpRes[0][ 1] = !false; bCmpRes[1][ 1] = (strTest2 != strTest3);
  bCmpRes[0][ 2] = !false; bCmpRes[1][ 2] = (strTest0 != strTest4);
  bCmpRes[0][ 3] = !false; bCmpRes[1][ 3] = (strTest4 != strTest0);
  bCmpRes[0][ 4] = !true ; bCmpRes[1][ 4] = (strTest0 != szTest[0]);
  bCmpRes[0][ 5] = !false; bCmpRes[1][ 5] = (strTest2 != szTest[3]);
  bCmpRes[0][ 6] = !false; bCmpRes[1][ 6] = (strTest0 != szTest[4]);
  bCmpRes[0][ 7] = !false; bCmpRes[1][ 7] = (strTest4 != szTest[0]);
  bCmpRes[0][ 8] = !true ; bCmpRes[1][ 8] = (szTest[1] != strTest1);
  bCmpRes[0][ 9] = !false; bCmpRes[1][ 9] = (szTest[2] != strTest3);
  bCmpRes[0][10] = !false; bCmpRes[1][10] = (szTest[1] != strTest4);
  bCmpRes[0][11] = !false; bCmpRes[1][11] = (szTest[4] != strTest1);

  bTmp1 = true;
  bRes = true;
  for (int i = 0; (i < CMPTESTCOUNT) && bRes; i++)
    bRes = (bCmpRes[0][i] == bCmpRes[1][i]);
  if (bRes)
    TsWriteToViewLn(bRes);
  else
    {
    TsWriteToView(i-1);
    TsWriteToViewLn(_T(". case failed."));
    }
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  bTmp1 = (bTmp1 && bRes);

  logEntry.m_szObjectName = _T("CString::operator>()");
  TsWriteToView(_T("A >  B => "));
  bCmpRes[0][ 0] = false; bCmpRes[1][ 0] = (strTest0 >  strTest1);
  bCmpRes[0][ 1] = false; bCmpRes[1][ 1] = (strTest2 >  strTest3);
  bCmpRes[0][ 2] = false; bCmpRes[1][ 2] = (strTest0 >  strTest4);
  bCmpRes[0][ 3] = true ; bCmpRes[1][ 3] = (strTest4 >  strTest0);
  bCmpRes[0][ 4] = false; bCmpRes[1][ 4] = (strTest0 >  szTest[0]);
  bCmpRes[0][ 5] = false; bCmpRes[1][ 5] = (strTest2 >  szTest[3]);
  bCmpRes[0][ 6] = false; bCmpRes[1][ 6] = (strTest0 >  szTest[4]);
  bCmpRes[0][ 7] = true ; bCmpRes[1][ 7] = (strTest4 >  szTest[0]);
  bCmpRes[0][ 8] = false; bCmpRes[1][ 8] = (szTest[1] >  strTest1);
  bCmpRes[0][ 9] = false; bCmpRes[1][ 9] = (szTest[2] >  strTest3);
  bCmpRes[0][10] = false; bCmpRes[1][10] = (szTest[1] >  strTest4);
  bCmpRes[0][11] = true ; bCmpRes[1][11] = (szTest[4] >  strTest1);

  bTmp1 = true;
  bRes = true;
  for (int i = 0; (i < CMPTESTCOUNT) && bRes; i++)
    bRes = (bCmpRes[0][i] == bCmpRes[1][i]);
  if (bRes)
    TsWriteToViewLn(bRes);
  else
    {
    TsWriteToView(i-1);
    TsWriteToViewLn(_T(". case failed."));
    }
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  bTmp1 = (bTmp1 && bRes);

  logEntry.m_szObjectName = _T("CString::operator>=()");
  TsWriteToView(_T("A >= B => "));
  bCmpRes[0][ 0] = true ; bCmpRes[1][ 0] = (strTest0 >= strTest1);
  bCmpRes[0][ 1] = false; bCmpRes[1][ 1] = (strTest2 >= strTest3);
  bCmpRes[0][ 2] = false; bCmpRes[1][ 2] = (strTest0 >= strTest4);
  bCmpRes[0][ 3] = true ; bCmpRes[1][ 3] = (strTest4 >= strTest0);
  bCmpRes[0][ 4] = true ; bCmpRes[1][ 4] = (strTest0 >= szTest[0]);
  bCmpRes[0][ 5] = false; bCmpRes[1][ 5] = (strTest2 >= szTest[3]);
  bCmpRes[0][ 6] = false; bCmpRes[1][ 6] = (strTest0 >= szTest[4]);
  bCmpRes[0][ 7] = true ; bCmpRes[1][ 7] = (strTest4 >= szTest[0]);
  bCmpRes[0][ 8] = true ; bCmpRes[1][ 8] = (szTest[1] >= strTest1);
  bCmpRes[0][ 9] = false; bCmpRes[1][ 9] = (szTest[2] >= strTest3);
  bCmpRes[0][10] = false; bCmpRes[1][10] = (szTest[1] >= strTest4);
  bCmpRes[0][11] = true ; bCmpRes[1][11] = (szTest[4] >= strTest1);

  bTmp1 = true;
  bRes = true;
  for (int i = 0; (i < CMPTESTCOUNT) && bRes; i++)
    bRes = (bCmpRes[0][i] == bCmpRes[1][i]);
  if (bRes)
    TsWriteToViewLn(bRes);
  else
    {
    TsWriteToView(i-1);
    TsWriteToViewLn(_T(". case failed."));
    }
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  bTmp1 = (bTmp1 && bRes);

  logEntry.m_szObjectName = _T("CString::operator<=()");
  TsWriteToView(_T("A <= B => "));
  bCmpRes[0][ 0] = true ; bCmpRes[1][ 0] = (strTest0 <= strTest1);
  bCmpRes[0][ 1] = true ; bCmpRes[1][ 1] = (strTest2 <= strTest3);
  bCmpRes[0][ 2] = true ; bCmpRes[1][ 2] = (strTest0 <= strTest4);
  bCmpRes[0][ 3] = false; bCmpRes[1][ 3] = (strTest4 <= strTest0);
  bCmpRes[0][ 4] = true ; bCmpRes[1][ 4] = (strTest0 <= szTest[0]);
  bCmpRes[0][ 5] = true ; bCmpRes[1][ 5] = (strTest2 <= szTest[3]);
  bCmpRes[0][ 6] = true ; bCmpRes[1][ 6] = (strTest0 <= szTest[4]);
  bCmpRes[0][ 7] = false; bCmpRes[1][ 7] = (strTest4 <= szTest[0]);
  bCmpRes[0][ 8] = true ; bCmpRes[1][ 8] = (szTest[1] <= strTest1);
  bCmpRes[0][ 9] = true ; bCmpRes[1][ 9] = (szTest[2] <= strTest3);
  bCmpRes[0][10] = true ; bCmpRes[1][10] = (szTest[1] <= strTest4);
  bCmpRes[0][11] = false; bCmpRes[1][11] = (szTest[4] <= strTest1);

  bTmp1 = true;
  bRes = true;
  for (int i = 0; (i < CMPTESTCOUNT) && bRes; i++)
    bRes = (bCmpRes[0][i] == bCmpRes[1][i]);
  if (bRes)
    TsWriteToViewLn(bRes);
  else
    {
    TsWriteToView(i-1);
    TsWriteToViewLn(_T(". case failed."));
    }
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);
  bTmp1 = (bTmp1 && bRes);

  logEntry.m_szObjectName = _T("CString::operator<()");
  TsWriteToView(_T("A <  B => "));
  bCmpRes[0][ 0] = false; bCmpRes[1][ 0] = (strTest0 <  strTest1);
  bCmpRes[0][ 1] = true ; bCmpRes[1][ 1] = (strTest2 <  strTest3);
  bCmpRes[0][ 2] = true ; bCmpRes[1][ 2] = (strTest0 <  strTest4);
  bCmpRes[0][ 3] = false; bCmpRes[1][ 3] = (strTest4 <  strTest0);
  bCmpRes[0][ 4] = false; bCmpRes[1][ 4] = (strTest0 <  szTest[0]);
  bCmpRes[0][ 5] = true ; bCmpRes[1][ 5] = (strTest2 <  szTest[3]);
  bCmpRes[0][ 6] = true ; bCmpRes[1][ 6] = (strTest0 <  szTest[4]);
  bCmpRes[0][ 7] = false; bCmpRes[1][ 7] = (strTest4 <  szTest[0]);
  bCmpRes[0][ 8] = false; bCmpRes[1][ 8] = (szTest[1] <  strTest1);
  bCmpRes[0][ 9] = true ; bCmpRes[1][ 9] = (szTest[2] <  strTest3);
  bCmpRes[0][10] = true ; bCmpRes[1][10] = (szTest[1] <  strTest4);
  bCmpRes[0][11] = false; bCmpRes[1][11] = (szTest[4] <  strTest1);

  bTmp1 = true;
  bRes = true;
  for (int i = 0; (i < CMPTESTCOUNT) && bRes; i++)
    bRes = (bCmpRes[0][i] == bCmpRes[1][i]);
  if (bRes)
    TsWriteToViewLn(bRes);
  else
    {
    TsWriteToView(i-1);
    TsWriteToViewLn(_T(". case failed."));
    }

  bRes = (bTmp1 && bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  #ifdef _WIN32
    //SysString methods / OLE BSTR support
    TsWriteToViewLn(_T("\r\nWindows specific methods"));
    logEntry.m_szObjectName = _T("CString::AllocSysString()");
    TsWriteToView(_T("bstr = strTest0.AllocSysString() => "));
    strTest0 = _T("Testing");
    BSTR bstr = strTest0.AllocSysString();
    #ifndef _UNICODE
      //Convert a sequence of wide characters to a corresponding sequence of
      //multibyte characters.
      char szBuf[40];
      wcstombs(szBuf, bstr, sizeof(szBuf));
    #else
      LPWSTR szBuf = bstr;
    #endif
    bRes = (_tcscmp(szBuf, strTest0) == 0);
    TsWriteToViewLn(bRes);
    if (!bRes)
      {
      ::SysFreeString(bstr);
      goto TESTEXIT;
      }
    logEntry.m_bResult = bRes;
    LogTest(&logEntry);

    logEntry.m_szObjectName = _T("CString::SetSysString()");
    TsWriteToView(_T("strTest1.SetSysString(&bstr) => "));
    strTest1 = _T("Test #2");
    strTest1.SetSysString(&bstr);
    #ifndef _UNICODE
      //Convert a sequence of wide characters to a corresponding sequence of
      //multibyte characters.
      wcstombs(szBuf, bstr, sizeof(szBuf));
    #else
      szBuf = bstr;
    #endif
    bRes = (_tcscmp(szBuf, strTest1) == 0);
    ::SysFreeString(bstr);
    TsWriteToViewLn(bRes);
    if (!bRes)
      goto TESTEXIT;
    logEntry.m_bResult = bRes;
    LogTest(&logEntry);

  #endif //_WIN32

  TsWriteToViewLn(_T("\r\nResource specific methods"));

  logEntry.m_szObjectName = _T("CString::LoadString()");
  TsWriteToView(_T("strTest0.LoadString(IDS_TESTSTRING) => "));
  strTest0.LoadString(IDS_TESTSTRING);
  bRes = (_tcscmp(strTest0, g_szTest[0]) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  logEntry.m_bResult = bRes;
  LogTest(&logEntry);

  #ifndef _UNICODE
    TsWriteToViewLn(_T("\r\nConvert character set"));
    //ATL: The functions are not available if _UNICODE is defined.
    logEntry.m_szObjectName = _T("CString::AnsiToOem()");
    TsWriteToView(_T("strTest0.AnsiToOem() => "));
    strTest0 = g_szTestString;
    strTest0.AnsiToOem();

    bRes = (_tcscmp(strTest0, g_szTestStringOem) == 0);
    TsWriteToViewLn(bRes);
    if (!bRes)
      goto TESTEXIT;
    logEntry.m_bResult = bRes;
    LogTest(&logEntry);

    logEntry.m_szObjectName = _T("CString::OemToAnsi()");
    TsWriteToView(_T("strTest0.OemToAnsi() => "));
    strTest0.OemToAnsi();

    bRes = (_tcscmp(strTest0, g_szTestString) == 0);
    TsWriteToViewLn(bRes);
    if (!bRes)
      goto TESTEXIT;
    logEntry.m_bResult = bRes;
    LogTest(&logEntry);
  #else
    //ATL: SBCS conversion is not supported
    //Note: Tests is logged as successful just for log comparison purpose.
    logEntry.m_bResult = true;
    logEntry.m_szObjectName = _T("CString::AnsiToOem()");
    LogTest(&logEntry);
    logEntry.m_szObjectName = _T("CString::OemToAnsi()");
    LogTest(&logEntry);
  #endif //_UNICODE

  TsWriteToViewLn(LOG_EOT);
  return bRes;
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
