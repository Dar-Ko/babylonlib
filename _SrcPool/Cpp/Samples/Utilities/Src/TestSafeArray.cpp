/*$RCSfile: TestSafeArray.cpp,v $: implementation file
  $Revision: 1.11 $ $Date: 2010/03/10 22:17:27 $
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
  #ifdef _USE_ATL //use Microsoft ATL
    #include <atlsafe.h> //CComSafeArray template
  #endif //_USE_ATL
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
bool bResult = true;

const int DIM_3D = 3;
const int DIM_2D = 2;

const int COL = 10;
const int ROW = 8;
//test controll table
wchar_t wAlphabet[ROW][COL] =
  {0x0061, 0x03B1, 0x0430, 0xFB21, 0xFE8D, 
   0xF900, 0xFF8F, 0x10A0, 0x0F00, 0xE01};

for(int i = 1; i < ROW; i++)
  {
  for(int j = 0; j < COL; j++)
    {
    //Intialize the table with consecutive characters from each alphabet
    wAlphabet[i][j] = wAlphabet[i - 1][j] + 1;
    }
  }

#ifdef _USE_ATL
  if(bResult)
    {
    //Create a multidimensional array, using Microsoft ATL.
    CComSafeArrayBound comsaBound[DIM_2D];  
    //Set the array comsaBound structure
    comsaBound[0].SetCount(COL); //Number of columns
    comsaBound[0].SetLowerBound(0);
    comsaBound[1].SetCount(ROW); //Number of rows
    comsaBound[1].SetLowerBound(0);
    //Create the two-dimensional array
    CComSafeArray<USHORT> comsaD2(comsaBound, DIM_2D);

    //Write elements
    int32_t aIndex[DIM_2D]; //container used to store array indexes
    for (int x = 0; x < COL; x++)
      {
      for (int y = 0; y < ROW; y++)
        {
        aIndex[0] = x;
        aIndex[1] = y;
        HRESULT hr = comsaD2.MultiDimSetAt((LONG*)aIndex, (USHORT)wAlphabet[x][y]);
        ASSERT(hr == S_OK);
        }
     }
    //Read elements
    for (int x = 0; x < COL; x++)
      {
      for (int y = 0; y < ROW; y++)
        {
        wchar_t cElement;
        aIndex[0]=x;
        aIndex[1]=y;
        HRESULT hr = comsaD2.MultiDimGetAt((LONG*)aIndex, *(USHORT*)&cElement);
        ATLASSERT(hr == S_OK);
        bResult = bResult && (cElement == wAlphabet[x][y]);
        ASSERT(bResult == TRUE);
        }
      }
    //Subscript operator returns only values from 0-th column
    wchar_t cTemp = comsaD2[1];
    bResult = bResult && (cTemp == wAlphabet[1][0]);
    cTemp = comsaD2[2];
    bResult = bResult && (cTemp == wAlphabet[2][0]);
    }
#endif //_USE_ATL

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
  TSafeArray<DIM_3D, int, VT_I4> intArray(saDim);
  bResult = (intArray.GetDimensions() == DIM_3D);
  bResult = bResult && (intArray.GetVarType() == VT_I4);
  bResult = bResult && (intArray.GetType() == VT_I4);
  //Validate type casting
  LPSAFEARRAY psaTemp = (LPSAFEARRAY)intArray;
  bResult = bResult && (psaTemp != NULL);
  //Get address of the array descriptor
  LPSAFEARRAY* ppTemp = &intArray;
  bResult = bResult && (ppTemp != NULL);
  bResult = bResult && (intArray.GetCount() == 3);
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
  //Create a [ROW, COL] table of wide characters and initalize each row 
  //with 10 letters.
  TSafeArrayDim<DIM_2D> sa2Dim(ROW, COL);
  TSafeArray<DIM_2D, wchar_t> wArray(sa2Dim);

  typedef TSafeArray<4, //4-dimensional space
                     uint16_t,
                     static_cast<VARENUM>(TSaType<uint16_t>::VARIANT_TYPE)
                     > SPACE; 
  TSafeArrayDim<4> sa4Dim;
  sa4Dim[0] = 3;
  sa4Dim[1] = 4;
  sa4Dim[2] = 5;
  sa4Dim[3] = 6;
  SPACE nSpace(sa4Dim);
  
  try
    {
    //Test variant helper methods
    if (bResult)
      {
      //Create helper specialized for one-dimensional arrays and set index to 1
      TSaReductor<wchar_t, DIM_2D> sarTempA(wArray, 1);
      VARENUM eTemp = sarTempA;
      if (eTemp == VT_UI2)
        {
        wchar_t sDummy = L'D';
        bResult = sarTempA.SetAt(sDummy, 2);
        if(bResult)
          {
          sDummy = 0;
          bResult = (sarTempA.GetAt(sDummy, 2) && 
                     (sDummy == L'D')             );
          }
        }
      else
        bResult = false;
      }

    if (bResult)
      {
      TSaReductor<uint16_t, 4> sarTempB(nSpace, 2);
      VARENUM eTemp = sarTempB;
      if (eTemp == VT_UI2)
        {
        bResult = true;
        }
      else
        bResult = false;
      }

    //Validate subscript operations
    int32_t testLower, testUpper;
    for(int iSubdim = (4 - 1); (iSubdim >= 0) && bResult; iSubdim--)
      {
      bResult = nSpace.GetBoundLower(&testLower, iSubdim);
      bResult = bResult && nSpace.GetBoundUpper(&testUpper, iSubdim);
      TRACE3(_T("Safe Subarray %d range [%d, %d]\n"), 
            iSubdim, testLower, testUpper);
      }
     if(!bResult)
       throw((unsigned int)ERROR_NOACCESS);

    //Get reference to the 3D space, in 4th universe [4]
    SPACE::CSaIterator spaceVolume = nSpace[4];
    //Get reference to the surface, in 3rd sector [3][4]
    SPACE::TSaIterator<uint16_t, DIM_2D> spacePlane = spaceVolume[3];
    //Get reference to the trajectory, on 1st area [1][3][4]
    SPACE::TSaIterator<uint16_t, DIM_2D -1> spaceLine = spacePlane[1];
    //Get reference to the end point of 2nd segment [2][1][3][4]
    SPACE::TSaIterator<uint16_t, 0> spaceDot = spaceLine[2];

      TSafeArray<DIM_2D, wchar_t>::CSaIterator csaTemp = wArray[2];
    //TSafeArray<wchar_t, VT_UI2, DIM_2D>::TSaIterator<wchar_t, DIM_2D - 1> cLetter = csaTemp[5];  //Get the character indexed as [2][5]

    //wchar_t cLetter = csaTemp[5];  //Get the character indexed as [2][5]

    //Check error handling
    TSafeArray<DIM_2D, wchar_t>::CSaIterator csaErrorneus = wArray[22];
    }
  catch(unsigned int nError)
    {
    switch (nError) 
      {
    case E_INVALIDARG:
      TRACE(_T("  Index is out of bounds!\n"));
      //Expected exception
      break;
    case DISP_E_BADINDEX:
      TRACE(_T("  The specified index or vector with indexes is invalid!\n"));
      bResult = false; 
      break;
    case E_OUTOFMEMORY:
      TRACE(_T("  Memory could not be allocated!\n"));
      bResult = false; 
      break;
    default:
      TRACE(_T("  An exception occured while accessing array's elements!\n"));
      bResult = false; //Unhandled exception
      }
    }

  for(int i = 0; i < ROW; i++)
    {
    for(int j = 0; j < COL; j++)
      {
      //wArray[j][i] = wAlphabet[i] + j;
      }
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
  TSafeArray<DIM_2D, int32_t, VT_I4> intArray(psaArray);
  bResult = (intArray.GetDimensions() == DIM_2D);
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
 * Revision 1.11  2010/03/10 22:17:27  ddarko
 * defaulted template parameter(s)
 *
 * Revision 1.10  2010/03/09 22:51:42  ddarko
 * *** empty log message ***
 *
 * Revision 1.9  2010/03/08 22:40:13  ddarko
 * template specialization issue
 *
 * Revision 1.8  2010/03/04 22:21:16  ddarko
 * test subsscript operator
 *
 * Revision 1.7  2010/03/03 23:18:40  ddarko
 * *** empty log message ***
 *
 * Revision 1.6  2010/03/03 00:06:27  ddarko
 * *** empty log message ***
 *
 * Revision 1.5  2010/03/01 23:52:18  ddarko
 * *** empty log message ***
 *
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
