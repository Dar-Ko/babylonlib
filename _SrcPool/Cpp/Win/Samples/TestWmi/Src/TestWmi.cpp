/*$RCSfile: TestWmi.cpp,v $: implementation file
  $Revision: 1.5 $ $Date: 2010/02/11 22:41:41 $
  $Author: ddarko $

  Test WMI routines.
  2010-01-05 Darko Kolakovic
 */

// Group=Examples Windows

#include "stdafx.h"
#include "KWmi.h" //CWmi class

//-----------------------------------------------------------------------------
/*
 */
bool TestWmi()
{
LPWSTR wszResult = NULL;
LPWSTR* ppszBuf = &wszResult;
HRESULT lError = E_FAIL;
VARIANT varIn;
SYSTEMTIME timeNow;
GetSystemTime(&timeNow);
if (::SystemTimeToVariantTime(&timeNow, &varIn.date) != 0)
  {
  varIn.vt = VT_DATE;
  LPWSTR bstrT;
  BSTR sz;
  OLECHAR d;
//        *ppszBuf = (LPWSTR)malloc((255 + 1) * sizeof(WCHAR));
//        if (*ppszBuf != NULL)
          {
//          (*ppszBuf)[255] = L'\0';
  lError = VarBstrFromDate((static_cast <VARIANT>(varIn)).date,
                            LOCALE_USER_DEFAULT,
                            VAR_FOURDIGITYEARS, //flags
                            &bstrT
                            //(BSTR*)*ppszBuf
                           );
          ASSERT((*ppszBuf)[255] == L'\0'); //Check for the overflow
          }
  }


TRACE(_T("TestWmi()\n"));
bool bResult = false;
CWmi wmiTest;
bResult = wmiTest.Init(NULL);
if(bResult)
  {
  bResult = wmiTest.Query(WQL_HDD);
  bResult = wmiTest.Disconnect();
  }
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: TestWmi.cpp,v $
 * Revision 1.5  2010/02/11 22:41:41  ddarko
 * *** empty log message ***
 *
 * Revision 1.4  2010/02/02 19:19:30  ddarko
 * WQL constats
 *
 * Revision 1.3  2010/02/01 22:28:07  ddarko
 * ExecQuery
 *
 * Revision 1.2  2010/01/26 22:47:05  ddarko
 * Initialization of WMI
 *
 * Revision 1.1  2010/01/21 22:18:19  ddarko
 * Created
 *
 ******************************************************************************/
