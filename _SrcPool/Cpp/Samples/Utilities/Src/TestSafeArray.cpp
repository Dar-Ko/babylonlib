/*$RCSfile: TestSafeArray.cpp,v $: implementation file
  $Revision: 1.13 $ $Date: 2011/04/28 21:59:22 $
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

  //Test log creation
TESTENTRY logEntry =
{_T("TSafeArrayDim<DIM_3D>::TSafeArrayDim()"), _T("KSafeArray.h"), false};

const int DIM_3D = 3;
const int DIM_2D = 2;
const int DIM_1D = 1;

const int ROW = 8;  //number of rows
const int COL = 10; //number of columns
//test controll table
wchar_t wAlphabet[ROW][COL] =
  {0x0061, 0x03B1, 0x0430, 0xFB21, 0xFE8D, 
   0xF900, 0xFF8F, 0x10A0, 0x0F00, 0xE01};

for(int i = 1; i < ROW; i++)
  {
  for(int j = 0; j < COL; j++)
    {
    /*Intialize the table with consecutive characters from each alphabet
        a, alpha, 1072, 64289, 65165, 63744, 65423, 4256, 3840, 3585
        b,  beta, 1073, ...
        c, gamma, 1074, ...
        .    .      .
        .    .      .
        .    .      .
        h, tetha, 1079, 64296, 65172, 63751, 65430, 4263, 3847, 3592
     */
    wAlphabet[i][j] = wAlphabet[i - 1][j] + 1;
    }
  }

#ifdef _USE_ATL
  if(bResult)
    {
    //Create a multidimensional array ROWxCOL, using Microsoft ATL.
    CComSafeArrayBound comsaBound[DIM_2D];  
    //Set the array comsaBound structure
    comsaBound[1].SetCount(ROW); //Number of rows
    comsaBound[1].SetLowerBound(0);
    comsaBound[0].SetCount(COL); //Number of columns
    comsaBound[0].SetLowerBound(0);
    //Create the two-dimensional array
    CComSafeArray<USHORT> comsaD2(comsaBound, DIM_2D);

    //Write elements
    int32_t aIndex[DIM_2D]; //container used to store array indexes
    for (int y = 0; y < ROW; y++)
      {
      for (int x= 0; x < COL; x++)
        {
        aIndex[1] = y; //row index
        aIndex[0] = x; //column index
        HRESULT hr = comsaD2.MultiDimSetAt((LONG*)aIndex, (USHORT)wAlphabet[y][x]);
        ASSERT(hr == S_OK);
        }
     }
    //Read elements
    for (int y = 0; y < ROW; y++)
      {
      for (int x = 0; x < COL; x++)
        {
        wchar_t cElement;
        aIndex[1]=y; //row index
        aIndex[0]=x; //column index
        HRESULT hr = comsaD2.MultiDimGetAt((LONG*)aIndex, *(USHORT*)&cElement);
        ATLASSERT(hr == S_OK);
        bResult = bResult && (cElement == wAlphabet[y][x]);
        ASSERT(bResult == TRUE);
        }
      }
    //Subscript operator returns only values from 0-th row
    wchar_t cTemp = comsaD2[1]; //result is 'aplha'
    bResult = bResult && (cTemp == wAlphabet[0][1]);
    cTemp = comsaD2[2];         //result is 'a'
    bResult = bResult && (cTemp == wAlphabet[0][2]);
    }
#endif //_USE_ATL

//Create 3D matrix.
//Set the dimension of the data cube [7][6][5]
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
  //Create an array of wide characters
  TSafeArrayDim<DIM_1D> sa1Dim(COL);
  TSafeArray<DIM_1D, wchar_t> wVector(sa1Dim);

  //Create a [ROW, COL] table of wide characters and initalize each row 
  //with 10 letters.
  TSafeArrayDim<DIM_2D> sa2Dim(COL, ROW);
  TSafeArray<DIM_2D, wchar_t> wMatrix(sa2Dim);

  //Create 4-dimensional space [6][5][4][3]
  typedef TSafeArray<4, //4-dimensional space
                     uint16_t,
                     static_cast<VARENUM>(TSaType<uint16_t>::VARIANT_TYPE)
                     > SPACE; 
  TSafeArrayDim<4> sa4Dim; //space boundaries [6, 5, 4, 3]
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
      TSaReductor<wchar_t, DIM_1D> sarTempA(wVector, 1);
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

    //Validate boundary operations
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

    //Validate subscript operations
    TSaReductor<wchar_t, DIM_2D> csaTemp = wMatrix[1]; //set to Greek alphabet
    TSaReductor<wchar_t, DIM_2D, 0> cLetter = csaTemp[4];  //Get the character indexed as [2][5]
    wchar_t wValue = wAlphabet[4][1]; //set value to epsilon
    bResult = cLetter.SetAt(wValue, 4);
    
    wchar_t wLetter = wMatrix[1][4];  //Get the character indexed as [4][1]

    int VarType = csaTemp[4]; //Implicit cast from VARENUM to int = 18 (VT_UI2)

    ASSERT(wValue == VarType);
    if(wValue != VarType)
      throw ((unsigned int)ERROR_BAD_ARGUMENTS);

    //Get reference to the 3D space, in 4th universe [4]
    #ifdef HAS_NO_TYPEDEF_INSIDE_TEMPLATE
      TSaReductor<uint16_t, 4> spaceVolume = nSpace[4]; //SUBDIM = DIM_3D
    #else
      SPACE::CSaIterator spaceVolume = nSpace[4]; //SUBDIM = DIM_3D
    #endif
    //Get reference to the surface, in 3rd sector [4][3]
    TSaReductor<uint16_t, 4, DIM_2D> spacePlane = spaceVolume[3];
    //Get reference to the trajectory, on 1st area [4][3][1]
    TSaReductor<uint16_t, 4, DIM_2D -1> spaceLine = spacePlane[1];
    //Get reference to the end point of 2nd segment [4][3][1][2]
    TSaReductor<uint16_t, 4, 0> spaceDot = spaceLine[2];
    uint16_t nValue = 0xFEED;
    bResult = spaceDot.SetAt(nValue, 2); //Set element [4][3][1][2]
    if (bResult)
      {
      uint16_t nTest = nSpace[4][3][1][2];
      bResult = (nTest == nValue);
      }

    //Check error handling
    TSafeArray<DIM_2D, wchar_t>::CSaIterator csaErrorneus = wMatrix[22];
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

  //Write test log
logEntry.m_bResult = bResult;
LogTest(&logEntry);

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
  //Test log creation
TESTENTRY logEntry =
  {_T("SafeArrayCreate()"), _T("KSafeArray.h"), false};

//Create 20 x 10 matrix
const int DIM_2D = 2;
//2D array [20][10] bounds
SAFEARRAYBOUND saBounds[DIM_2D] = { {10, 0}, {20, 0} };

#ifdef _WIN32 //Requires OLE 32 (OleAut32.dll)
  logEntry.m_szFileName = _T("OleAuto.h");
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

  //Write test log
logEntry.m_bResult = bResult;
LogTest(&logEntry);

return bResult;
}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: TestSafeArray.cpp,v $
 * Revision 1.13  2011/04/28 21:59:22  ddarko
 * Created
 *
 * Revision 1.12  2010/03/12 22:52:57  ddarko
 * *** empty log message ***
 *
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
