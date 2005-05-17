/*$Workfile: TestBeep.cpp$: implementation file
  $Revision: 4$ $Date: 2005-05-16 14:23:03$
  $Author: Darko Kolakovic$

  Test PC beeping
  Copyright: CommonSoft Inc.
  Aug. 2k2 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "stdafx.h"

#include "KTypedef.h" //LPCTSTR typedef
#include "KBeep.h"    //CBeep class
extern bool TsWriteToViewLn(LPCTSTR lszText);

//TestBeep()-------------------------------------------------------------------
/*Testing beep sound.

  Returns: true if successful, otherwise returns false.
 */
bool TestBeep()
{
TsWriteToViewLn(_T("TestBeep()\a"));

bool bRes = true;
if (bRes)
  {
  CBeep beepDefault;
  #ifdef _DEBUG
    beepDefault.Dump();
  #endif
  beepDefault.Start();
  }
CBeep A;
A.m_iFrequency =440;
A.Start();

TsWriteToViewLn(LOG_EOT);
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log:
 * 2    Biblioteka1.1         2002-09-19 01:14:40  Darko
 * 1    Biblioteka1.0         2002-09-16 17:58:56  Darko Kolakovic
 *$
 *****************************************************************************/
