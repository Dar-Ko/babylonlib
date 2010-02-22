/*$RCSfile: TestSafeArray.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2010/02/22 22:38:52 $
  $Author: ddarko $

  Test SAFEARRAY conversion routines.
  2010-02-15 Darko Kolakovic
 */

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "stdafx.h"
#ifdef _WIN32
  #include <oleauto.h> //VarBstrFromDate()
  #pragma comment(lib, "oleaut32")
#endif
#include "KSafeArray.h"

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);
extern bool TsWriteToViewLn(const unsigned int& nValue);
extern "C" VARIANT VarBstrFromStr(LPCWSTR szSource);

//-----------------------------------------------------------------------------
/*Testing generating and handling a safe array.

  Returns: true if successful, otherwise returns false.
 */
bool TestSafeArray()
{
TRACE(_T("TestSafeArray()\n"));
bool bResult = false;
VARIANT    varIn; //test input
LPWSTR     wszResult = NULL; //resulting string
HRESULT    lError = E_FAIL;  //error code


TsWriteToViewLn(LOG_EOT);
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: TestSafeArray.cpp,v $
 * Revision 1.1  2010/02/22 22:38:52  ddarko
 * SAFEARRAYBOUNDS
 *
 ******************************************************************************/
