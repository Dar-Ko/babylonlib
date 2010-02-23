/*$RCSfile: TestSafeArray.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2010/02/23 22:59:03 $
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

//Create 3D matrix
const int DIM_3D = 3;

//Set the dimension of the matrix
TSafeArrayDim<DIM_3D> saDim(5, 6, 7);

unsigned long nDim = saDim[0];
bResult = (nDim == 5);
bResult = bResult && (6 == saDim[1]);
bResult = bResult && (7 == saDim[2]);

//Change the size of the vectors
saDim[0] = 3;
saDim[1] = 4;
saDim[2] = 5;

if(bResult)
  {
  TSafeArray<int, VT_I4, DIM_3D> intArray(saDim);
  bResult = (intArray.GetDimension() == DIM_3D);
  }

TsWriteToViewLn(LOG_EOT);
return bResult;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: TestSafeArray.cpp,v $
 * Revision 1.2  2010/02/23 22:59:03  ddarko
 * Create SAFEARRAY
 *
 * Revision 1.1  2010/02/22 22:38:52  ddarko
 * SAFEARRAYBOUNDS
 *
 ******************************************************************************/
