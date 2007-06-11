/*$Workfile: S:\_SrcPool\Cpp\Samples\Complex\Src\TestComplexToA.cpp$: implementation file
  $Revision: 1$ $Date: 2007-06-11 17:01:45$
  $Author: Darko Kolakovic$

  Test Complex number presentation
  Copyright: CommonSoft Inc.
  2007-07-11 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "KDbgMacr.h"     //Compiler specific constants
#include "KProgCst.inl"   //NaN constants
#include "KComplex.h"     //CComplex class
#include "TestZAssert.h"  //Test validation class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif



extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern LPTSTR ZtoA(double dReal,double dImag, LPTSTR szResult, unsigned int iSize);

extern TestCComplex g_arrTestD[];//test values

//-----------------------------------------------------------------------------
/*Function evaluates complex number text representation.

  Returns: true if successful, otherwise returns false.
 */
bool TestZtoA()
{
TsWriteToViewLn(_T("TestZtoA()"));
const int BUFFERSIZE = 512;
TCHAR szText[BUFFERSIZE];
TCHAR szMessage[126];

bool bRes = true;
TESTENTRY logEntry = {_T("ZtoA()"), _T("KZtoA.cpp"), false};

int i = 0; 
while (i < TESTSIZE)
  {
  _complex zValue = g_arrTestD[i]; //Get test values
  _stprintf(szMessage, _T("(%e, %e) = "), zValue.x, zValue.y);
  TsWriteToView(szMessage);
  ZtoA(zValue.x, zValue.y, szText, BUFFERSIZE);
  TsWriteToViewLn(szText);
  TRACE(szText); TRACE(_T("\r\n"));

  i++;
  }

logEntry.m_bResult = bRes;
LogTest(&logEntry);

return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-06-11 17:01:45  Darko Kolakovic 
 * $
 *****************************************************************************/

