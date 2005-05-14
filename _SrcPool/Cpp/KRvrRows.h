/*$Workfile: KRvrRows.h$: header file
  $Revision: 5$ $Date: 2004-07-07 17:47:17$
  $Author: Darko$

  Reverse order of matrix rows
  Copyright: CommonSoft Inc
  D. Kolakovic   May 2k1
 */

#ifndef _KSWPROWS_H_
    //$Workfile: KRvrRows.h$ sentry
  #define _KRVRROWS_H_

#if _MSC_VER > 1000 /*Microsoft Visual Studio C/C++ compiler                 */
  #pragma once
#endif // _MSC_VER > 1000

//ReverseRows()----------------------------------------------------------------
/*Reverses order of rows of a 2D array. Function does not check array's 
  boundaries.

  Example:

    #include "KRvrRows.h" //ReverseRows()
    {
    ...
    const int ROWS = 64;
    const int COLS = 30;
    int iOutput[ROWS][COLS];
    ...
    ReverseRows(szOutput, ROWS, COLS);
    ...
    }

 */
template<class TYPE> void ReverseRows(TYPE Array[],    //[in/out] matrix
                                   unsigned int nRows, //[in] number of rows
                                   unsigned int nCols  //[in] number of columns
                                   )
{
unsigned int y = 0;
nRows *= (nCols - 1);  //index of the first element in the last row
nRows--;
while (y < nRows)
  {
  unsigned int x = 0;
  while (x < nCols)
    {
    TYPE Temp = Array[y + x];
    Array[y + x] = Array[nRows + x];
    Array[nRows + x++] = Temp;
    }
  y += nCols;
  nRows -= nCols;
  }
};

///////////////////////////////////////////////////////////////////////////////
#endif // _KRVRROWS_H_
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         26/07/2001 9:31:33 PMDarko
 * $
 *****************************************************************************/
