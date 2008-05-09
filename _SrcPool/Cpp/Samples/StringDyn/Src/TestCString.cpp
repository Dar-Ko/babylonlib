/*$Workfile: TsCString.cpp$: implementation file
  $Revision: 4$ $Date: 2002-08-19 10:36:43$
  $Author: Darko Kolakovic$

  Test for CString class (STL port)
  Copyright: CommonSoft Inc.
  Jan. 2k2 Darko Kolakovic
*/
// Group=Examples


/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h" //TCHAR(), TESTENTRY

#ifndef _MFC_VER //Microsoft MFC library
  //include STL implementation for CString
  #include <string> //std::basic_string template
#endif


#include "KTypedef.h"  //BOOL typedef
//#include "KString.h"   //CString class

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);

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



TsWriteToViewLn(LOG_EOT);
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
