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
  TsWriteToViewLn(_T("Test CString creation"));

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

  CString str4(_T("Abcdef"), 3);
  bRes = (_tcscmp(str4, _T("Abc")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;

  CString str5( str2 );
  bRes = (_tcscmp(str5, _T("String")) == 0);
  TsWriteToViewLn(bRes);
  if (!bRes)
    goto TESTEXIT;
  
  //Show all the different kinds of initialization
  TsWriteToViewLn(_T("Initialization / Assignment"));
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
