/*$Workfile: TestSwapRows.cpp$: implementation file
  $Revision: 1$ $Date: 8/3/02 7:26:32 PM$
  $Author: Darko$

  Test reordering of matrix rows
  Copyright: CommonSoft Inc.
  May 2k1 D.Kolakovic
*/
// Group=Examples

#include <iostream>
#include <iomanip.h>
#include "KTrace.h"    //ASSERT macro
#include "KTypedef.h"  //DWORD typedef
#include "KSwpRows.h"

void DumpMatrix(int Array[],  //[in]
                uint32 nRows, //[in]
                uint32 nCols  //[in]
                )
{
unsigned int x, y;
y = 0;
while (y < nRows)
  {
  cout << setw(3) << setfill(' ') << dec << y << ". ";
  x = 0;
  while (x < nCols)
    {
    cout << setw(6) << setfill('0') << hex << Array[y * nCols + x] << ' ';
    x++;
    }
  cout << endl;
  y++;
  }
cout << dec << setw(0);
}

//TestByteSwap()---------------------------------------------------------------
/*Test reversing order of rows in 2D arrays.
 */
bool TestSwapRows()
{
cout << "\nTestSwapRows()" << endl;
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
cout << endl << "Swap..." << endl;
SwapRows<int>((int*)Matrix, ROWS, COLS);
DumpMatrix((int*)Matrix, ROWS, COLS);

int i = 0;
while (i < ROWS*COLS)
  {
  if (((int*)Matrix)[i] != Result[i])
    {
    cout << "Failure: element Matrix[" << i << "] = " << Matrix[i] <<" is not valid" << endl;
    bRes = false;
    break;
    }
  i++;
  }

cout << endl << "======================" << endl;

return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         8/3/02 7:26:32 PM    Darko           
 * $
 *****************************************************************************/
