/*$Workfile: KRvrElements.h$: header file
  $Revision: 5$ $Date: 2004-07-07 16:47:14$
  $Author: Darko$

  Reverses order of array elements
  Copyright: CommonSoft Inc
  D. Kolakovic   May 2k1
 */

#ifndef _KRVRELEMENTS_H_
    //$Workfile: KRvrElements.h$ sentry
  #define _KRVRELEMENTS_H_

#if _MSC_VER > 1000 /*Microsoft Visual Studio C/C++ compiler                 */
  #pragma once
#endif // _MSC_VER > 1000

//ReverseElements()------------------------------------------------------------
/*Reverses order of first nCount elements of the given array. Function does not
  check array's boundaries.

  Example:

    #include <iostream>
    #include <iomanip.h>
    #include "KRvrElements.h"  //ReverseElements()
    {
    ...
    char szOutput[64];
    sprintf(szOutput,"The quick brown fox jumps over the lazy dog.");
    ReverseElements(szOutput, strlen(szOutput));
    cout << szOutput << endl;
    ...
    }

 */
template<class TYPE> void ReverseElements(TYPE Array[],    //[in/out] array to be
                                                           //reversed
                                       unsigned int nCount //[in] number of elements
                                                           //to swap
                                       )
{
unsigned int nHead = 0;
nCount--;  //index of the last element is nCount-1
TYPE  Temp;

while (nHead < nCount)
  {
  Temp            = Array[nHead];
  Array[nHead++]  = Array[nCount];
  Array[nCount--] = Temp;
  }
};

///////////////////////////////////////////////////////////////////////////////
#endif // _KRVRELEMENTS_H_
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         26/07/2001 9:31:33 PMDarko
 * $
 *****************************************************************************/
