/*$RCSfile: TestSafeArray.cpp,v $: implementation file
  $Revision: 1.4 $ $Date: 2010/02/25 22:44:10 $
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

const int DIM_3D = 3;
const int DIM_2D = 2;

//Create 3D matrix.
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
  bResult = bResult && (intArray.GetVarType() == VT_I4);
  //Get address of the array descriptor
  LPSAFEARRAY* ppTemp = &intArray;
  bResult = bResult && (ppTemp != NULL);
  bResult = bResult && (intArray.GetBoundsLength(0) == 3);
  bResult = bResult && (intArray.GetBoundsLength(1) == 4);
  bResult = bResult && (intArray.GetBoundsLength(2) == 5);
  }

if (bResult)
  {
  extern bool TestTSafeArrayAssignment();
  bResult = TestTSafeArrayAssignment();
  }

if (bResult)
  {
  try
    {
    //Create a [10,10] table of wide characters and initalize each row 
    //with 10 letters.
    const int ROW = 10;
    const int COL = 10;
    TSafeArrayDim<DIM_2D> sa2Dim(ROW, COL);
    TSafeArray<wchar_t, VT_I2, 2> wArray(sa2Dim);

    wchar_t wAlphabet[COL] =
      {0x0061, 0x03B1, 0x0430, 0xFB21, 0xFE8D, 
      0xF900, 0xFF8F, 0x10A0, 0x0F00, 0xE01};
    for(int i = 0; i < ROW; i++)
      {
      for(int j = 0; j < COL; j++)
        {
        //wArray[j][i] = wAlphabet[i] + j;
        }
      }

    }
  catch(...)
    {
    bResult = false;
    TRACE(_T("  An exception occured\n"));
    }
  }

TsWriteToViewLn(LOG_EOT);
return bResult;
}

//-----------------------------------------------------------------------------
/*
 */
bool TestTSafeArrayAssignment()
{
TRACE(_T("TestTSafeArrayAssignment()\n"));
bool bResult = false;
//Create 20 x 10 matrix
const int DIM_2D = 2;
//2D array [20][10] bounds
SAFEARRAYBOUND saBounds[DIM_2D] = { {10, 0}, {20, 0} };

#ifdef _WIN32 //Requires OLE 32 (OleAut32.dll)
  LPSAFEARRAY psaArray = ::SafeArrayCreate(VT_I4, DIM_2D, saBounds);
#else
  /*Allocate space for the safe array and append additional safe array bounds if
    array is  multi-dimensional.
   */
  LPSAFEARRAY psaArray = 
      (LPSAFEARRAY) new uint8_t[sizeof(SAFEARRAY) + sizeof(SAFEARRAYBOUND)*(DIM_2D - 1)] ;
  if(psaArray != NULL)
    {
    psaArray->pvData = new int32_t[saBounds[0].cElements * saBounds[1].cElements];
    if(psaArray->pvData != NULL)
      {
      psaArray->cDims = DIM_2D;
      psaArray->cbElements = sizeof(int32_t);
      psaArray->cLocks = 0;
      psaArray->fFeatures = 128; //Note: array's attributes could not be 0
      //Copy bounds of the last dimenision at the begining
      psaArray->rgsabound[0].cElements = saBounds[DIM_2D - 1].cElements;
      psaArray->rgsabound[0].lLbound   = saBounds[DIM_2D - 1].lLbound;
      psaArray->rgsabound[1].cElements = saBounds[DIM_2D - 2].cElements;
      psaArray->rgsabound[1].lLbound   = saBounds[DIM_2D - 2].lLbound;
      }
    else
      {
      delete psaArray;
      psaArray = NULL;
      }
    }
#endif

if(psaArray != NULL)
  {
  //Fill array with values
  int iIndex0, iIndex1;
  const int iIndexEnd0 = (int)psaArray->rgsabound[0].cElements;
  const int iIndexEnd1 = (int)psaArray->rgsabound[1].cElements;
  int32_t* arrData = (int32_t*)psaArray->pvData;

  for(iIndex0 = 0; iIndex0 < iIndexEnd0; iIndex0++)
    {
    for(iIndex1 = 0; iIndex1 < iIndexEnd1; iIndex1++)
      {
      (&arrData[iIndex0 * iIndexEnd1])[iIndex1] = iIndex0 * 1000 + iIndex1;
      }
    }

  //Create a copy of the safe array
  TSafeArray<int32_t, VT_I4, DIM_2D> intArray(psaArray);
  bResult = (intArray.GetDimension() == DIM_2D);
  bResult = bResult && (intArray.GetVarType() == VT_I4);

  #ifdef _WIN32 //Requires OLE 32 (OleAut32.dll)
    if(FAILED(::SafeArrayDestroy(psaArray))) //Destroy array
      {
      TRACE(_T("  SafeArrayDestroy() failed!\n"));
      bResult = false;
      }
  #else
    delete[] psaArray->pvData;
    delete[] psaArray;
    psaArray = NULL;
  #endif
  }


return bResult;
}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: TestSafeArray.cpp,v $
 * Revision 1.4  2010/02/25 22:44:10  ddarko
 * Test safe array operations
 *
 * Revision 1.3  2010/02/24 22:49:25  ddarko
 * Test assigment constructor
 *
 * Revision 1.2  2010/02/23 22:59:03  ddarko
 * Create SAFEARRAY
 *
 * Revision 1.1  2010/02/22 22:38:52  ddarko
 * SAFEARRAYBOUNDS
 *
 ******************************************************************************/
