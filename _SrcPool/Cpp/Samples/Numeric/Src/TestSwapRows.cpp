/*$Workfile: TestSwapRows.cpp$: implementation file
  $Revision: 3$ $Date: 2004-10-05 14:05:43$
  $Author: Darko$

  Test reordering of matrix rows
  Copyright: CommonSoft Inc.
  May 2k1 D.Kolakovic
*/
// Group=Examples

#include "stdafx.h"
#include "KTrace.h"    //ASSERT macro
#include "KTypedef.h"  //DWORD typedef
#include "KRvrRows.h"  //ReverseRows()

void DumpMatrix(int Array[],  //[in]
                uint32 nRows, //[in]
                uint32 nCols  //[in]
                )
{
unsigned int x, y;
y = 0;
while (y < nRows)
  {
  std::_tcout << std::setw(3) << std::setfill(_T(' ')) << std::dec 
              << y << _T(". ");
  x = 0;
  while (x < nCols)
    {
    std::_tcout << std::setw(6) << std::setfill(_T('0')) << std::hex 
                << Array[y * nCols + x] << _T(' ');
    x++;
    }
  std::_tcout << std::endl;
  y++;
  }
std::_tcout << std::dec << std::setw(0);
}

//TestByteSwap()---------------------------------------------------------------
/*Test reversing order of rows in 2D arrays.
 */
bool TestSwapRows()
{
std::_tcout << _T("\nTestSwapRows()") << std::endl;
bool bRes = true;
const unsigned int ROWS = 5;
const unsigned int COLS = 6;

int Matrix[ROWS][COLS] =
  {
    { 0xA0000000, 0xA0000001, 0xA0000002, 0xA0000003, 0xA0000004, 0xA0000005 }, 
    { 0xB0000000, 0xB0000001, 0xB0000002, 0xB0000003, 0xB0000004, 0xB0000005 }, 
    { 0xC0000000, 0xC0000001, 0xC0000002, 0xC0000003, 0xC0000004, 0xC0000005 }, 
    { 0xD0000000, 0xD0000001, 0xD0000002, 0xD0000003, 0xD0000004, 0xD0000005 }, 
    { 0xE0000000, 0xE0000001, 0xE0000002, 0xE0000003, 0xE0000004, 0xE0000005 }
  };


int Result[ROWS*COLS] = //Expected result
  {
     0xE0000000, 0xE0000001, 0xE0000002, 0xE0000003, 0xE0000004, 0xE0000005,
     0xD0000000, 0xD0000001, 0xD0000002, 0xD0000003, 0xD0000004, 0xD0000005, 
     0xC0000000, 0xC0000001, 0xC0000002, 0xC0000003, 0xC0000004, 0xC0000005, 
     0xB0000000, 0xB0000001, 0xB0000002, 0xB0000003, 0xB0000004, 0xB0000005, 
     0xA0000000, 0xA0000001, 0xA0000002, 0xA0000003, 0xA0000004, 0xA0000005 
  };
DumpMatrix((int*)Matrix, ROWS, COLS);

 //Test reversing matrix rows
std::_tcout << std::endl << _T("Swap...") << std::endl;
ReverseRows<int>((int*)Matrix, ROWS, COLS);
DumpMatrix((int*)Matrix, ROWS, COLS);

int i = 0;
while (i < ROWS*COLS)
  {
  if (((int*)Matrix)[i] != Result[i])
    {
    std::_tcout << _T("Failure: element Matrix[") << i << _T("] = ") 
                << Matrix[i] << _T(" is not valid") << std::endl;
    bRes = false;
    break;
    }
  i++;
  }

std::_tcout << std::endl << _T("======================") << std::endl;

return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2004-10-05 14:05:43  Darko           fixed Unicode
 *       build
 *  2    Biblioteka1.1         2004-07-07 17:43:37  Darko           replaced
 *       SwapRows() with ReverseRows()
 *  1    Biblioteka1.0         2002-08-03 19:26:32  Darko           
 * $
 *****************************************************************************/
