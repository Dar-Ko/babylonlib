/*$Workfile: TestComplexToA.cpp$: implementation file
  $Revision: 2$ $Date: 2007-06-15 17:28:30$
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

#ifdef _DEBUG
  #ifdef _USE_MFC
    #define new DEBUG_NEW
  #endif //_USE_MFC
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#ifndef NUSE_TESTCCOMPLEX
  #include "TestZAssert.h"  //Test validation class
  extern TestCComplex g_arrTestD[];//test values
#else //use _complex
  const int TESTSIZE = 6;
  _complex g_arrTestD[TESTSIZE] = 
    {
      { 0.0,  0.0},
      {10.0,  0.0},
      { 0.0, 11.1},
      {-1.2, -1.3},
      { 0.0, -1.4},
      {-5.1, 0.0}
    };
#endif


extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern LPTSTR ZtoA(double dReal,double dImag, LPTSTR szResult, unsigned int iSize);


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
 *  2    Biblioteka1.1         2007-06-15 17:28:30  Darko Kolakovic Console traget
 *       fixes
 *  1    Biblioteka1.0         2007-06-11 17:01:45  Darko Kolakovic 
 * $
 *****************************************************************************/

