/*$Workfile: TsBeep.cpp$: implementation file
  $Revision: 2$ $Date: 19/09/2002 12:14:40 AM$
  $Author: Darko$

  Test PC beeping
  Copyright: CommonSoft Inc.
  Aug. 2k2 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTypedef.h" //LPCTSTR typedef
#include "KBeep.h"    //CBeep class
extern bool TsWriteToView(LPCTSTR lszText);

//TestBeep()-------------------------------------------------------------------
/*Testing beep sound.

  Returns: true if successful, otherwise returns false.
 */
bool TestBeep()
{
TsWriteToView("TestBeep()\a\r\n");

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

TsWriteToView("======================\r\n");
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 2    Biblioteka1.1         19/09/2002 12:14:40 AMDarko           
 * 1    Biblioteka1.0         16/09/2002 4:58:56 PMDarko Kolakovic 
 *$
 *****************************************************************************/
