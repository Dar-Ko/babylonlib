/*$Workfile: TsConversionToStr.cpp$: implementation file
  $Revision: 4$ $Date: 19/08/2002 9:35:58 AM$
  $Author: Darko Kolakovic$

  Test different conversions from and to string
  Copyright: CommonSoft Inc.
  Jan. 2k2 Darko Kolakovic
*/
// Group=Examples


/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include "KStrings.h"  //OcttoL()
#include <iostream>
#include <iomanip.h>  //std::endl

extern BOOL TsWriteToView(LPCTSTR lszText);
extern "C" LPTSTR ItoOct(int iValue, LPTSTR szResult);

//TestStringConversion()-------------------------------------------------------
/*Test different conversions from and to string.

  Returns: true if successful, otherwise returns false.
 */
bool TestStringConversion()
{
TsWriteToView("TestStringConversion()\r\n");
bool bRes = false;
LPTSTR szTemp;
long lResult;

  //Test conversion from string to long
  //Number in range
szTemp = "567";
lResult = OcttoL(szTemp);
cout << "octal " << szTemp << " = " << lResult << endl;
bRes = (lResult == 375);

if (bRes)
  {
  lResult = HextoL(szTemp);
  cout << "hex " << szTemp << " = " << lResult << endl;
  bRes = (lResult == 1383);
  }

  //Number is out of range
if (bRes)
  {
  szTemp = "567745516123476412444";
  lResult = OcttoL(szTemp);
  cout << "octal " << szTemp << " = " << lResult << endl;
  bRes = (lResult == -1661332188);
  }

if (bRes)
  {
  lResult = HextoL(szTemp); //Truncates to 56774551
  cout << "hex " << szTemp << " = " << lResult << endl;
  bRes = (lResult == 1983980612);
  }

TCHAR szResult[64];
int iValue;

if (bRes)
  {
  iValue = 375;
  ItoOct(iValue,szResult);
  cout << iValue << " = " << "octal " << szResult << endl;
  bRes = ( strcmp(szResult, "567") == 0 );
  }

if (bRes)
  {
  iValue = 65535;
  ItoOct(iValue,szResult);
  cout << iValue << " = " << "octal " << szResult << endl;
  bRes = ( strcmp(szResult, "177777") == 0 );
  }

TsWriteToView("======================\r\n");
return bRes;
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: 
 * 4    Biblioteka1.3         19/08/2002 9:35:58 AMDarko Kolakovic 
 * 3    Biblioteka1.2         13/08/2002 5:52:51 PMDarko Kolakovic 
 * 2    Biblioteka1.1         16/07/2002 12:41:52 AMDarko           Fixed VSS Log 
 *      tag
 * 1    Biblioteka1.0         07/03/2002 4:01:24 PMDarko           
 *$
 *****************************************************************************/
