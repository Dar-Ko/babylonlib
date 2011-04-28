/*$Workfile: TestGuid.cpp$: implementation file
  $Revision: 2$ $Date: 2005-05-16 14:28:55$
  $Author: Darko Kolakovic$

  Test Universally Unique Identifier (UUID) handling
  Copyright: CommonSoft Inc.
  Aug. 2k2 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

// Each dll/exe must initialize the GUIDs once.  This is done in one of
// two ways.  If you are not using precompiled headers for the file(s) which
// initializes the GUIDs, define INITGUID before including <objbase.h>.
// Microsoft's DEFINE_GUID uses C linkage and therfore generated numbers are global.
#define INITGUID

#include "stdafx.h"
#include "KTypedef.h"
#include "KGuid.h" //CGuid class

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern CString GuidToStr( const UUID& iid );

DEFINE_GUID(g_testGUID,
            0x340BC870, 0xA012, 37819, 0x20, 57, 132, 189, 0x73, 0x4D, 0x76, 0xE7);

//-----------------------------------------------------------------------------
/*Testing generating and handling Universally Unique Identifier (UUID /GUID).

  Returns: true if successful, otherwise returns false.
 */
bool TestGuid()
{
TsWriteToViewLn(_T("TestGuid()"));

bool bRes = true;

  //Test log creation
TESTENTRY logEntry =
{_T("CGuid::CGuid()"), _T("KGuid.h"), false};

TRACE1(_T("UUID = %ws\n"), (LPCTSTR)GuidToStr(g_testGUID));
TsWriteToViewLn((LPCTSTR)GuidToStr(g_testGUID));

  //Test construction
CGuid TestA; //null Uuid
CGuid TestB(_T("{340BC870-A012-93BB-2039-84BD734D76E7}"));
CGuid TestC(g_testGUID);

bRes = TestA.IsNull();
if (bRes)
  {
  }

  //Test assignment
TestA = TestB;

  //Test comparison
bRes = (!(TestA != TestB));
if (bRes)
  {
  }

 //Test generating UUID
TestC.Create();
TRACE1(_T("new UUID = %ws\n"), (LPCTSTR)GuidToStr(TestC));
TsWriteToViewLn((LPCTSTR)GuidToStr(TestC));

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 2    Biblioteka1.1         2005-05-16 14:28:55  Darko Kolakovic Create()
 * 1    Biblioteka1.0         2005-05-16 14:21:34  Darko Kolakovic 
 *$
 *****************************************************************************/
