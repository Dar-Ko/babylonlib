/*$RCSfile: TestBitset.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2011/05/02 22:10:58 $
  $Author: ddarko $

  Test bitset handling
  2011-04-01 Darko Kolakovic
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

extern bool TsWriteToViewLn(LPCTSTR lszText);

#ifdef _USE_STL
  #include <bitset>
  #include "STL/KOStream.h" //_tcout


//-----------------------------------------------------------------------------
/*Testing handling bitset.
  Required STL support.

  Returns: true if successful, otherwise returns false.
 */
bool TestBitset()
{
TsWriteToViewLn(_T("TestBitset()"));

bool bRes = true;

  //Test log creation
TESTENTRY logEntry =
{_T("std::bitset<>::bitset()"), _T("<bitset>"), false};

  //Test construction
std::bitset<5> bitsetTest;
bitsetTest[1] = 1;
bitsetTest[2] = 0;

std::_tcout << bitsetTest << std::endl;

  //Write test log
logEntry.m_bResult = bRes;
LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

#endif //_USE_STL
//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: TestBitset.cpp,v $
 *Revision 1.1  2011/05/02 22:10:58  ddarko
 *testing <bitset>
 *
 *****************************************************************************/
