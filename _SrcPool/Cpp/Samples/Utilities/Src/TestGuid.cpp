/*$Workfile: TestGuid.cpp$: implementation file
  $Revision: 1$ $Date: 2005-05-16 14:21:34$
  $Author: Darko Kolakovic$

  Test Universally Unique Identifier (UUID) handling
  Copyright: CommonSoft Inc.
  Aug. 2k2 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "stdafx.h"
#include "KTypedef.h"
#include "KGuid.h" //CGuid class

extern bool TsWriteToViewLn(LPCTSTR lszText);

DEFINE_GUID(testGUID,
            0x340BC870, 0xA012, 37819, 0x20, 57, 132, 189, 0x73, 0x4D, 0x76, 0xE7);

//-----------------------------------------------------------------------------
/*Testing generating and handling Universally Unique Identifier (UUID /GUID).

  Returns: true if successful, otherwise returns false.
 */
bool TestGuid()
{
TsWriteToViewLn(_T("TestGuid()"));

bool bRes = true;
//TRACE((LPCTSTR)GuidToStr(testGUID);
//TODO: Non-MFC CString TsWriteToViewLn((LPCTSTR)GuidToStr(testGUID);

  //Test construction
CGuid TestA; //null Uuid
CGuid TestB(_T("{340BC870-A012-93BB-2039-84BD734D76E7}"));
//CGuid TestC(testGUID);

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


TsWriteToViewLn(LOG_EOT);
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 1    Biblioteka1.0         2005-05-16 14:21:34  Darko Kolakovic 
 *$
 *****************************************************************************/
