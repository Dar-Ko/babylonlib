/*$Workfile: KStrUtDJ.c$: implementation file
  $Revision: 5$ $Date: 2/12/02 5:39:29 PM$
  $Author: Darko$

  Converts unsigned integer to a right justfied decimal number.
  Jan. 90 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "KTChar.h"  /*TCHAR*/

#ifdef _DEBUG
  static char THIS_FILE[] = __FILE__;
#endif

#ifndef BOOL
  #include "KTypedef.h" //BOOL
#endif

//UtoDecJust()-----------------------------------------------------------------
/*Converts unsigned integer to right justfied decimal number.
  The string is right-justified and filled on the left with the specified pad
  character.
  Returns a pointer to string. There is no error return.

  Example:
    TCHAR szDestination[21];
    unsigned long i;
    i = 9;
    while ( i <= 11)
      {
      _tcscpy(szDestination,_T("BBBBBBBBBBBBBBBBBBBB"));
      TRACE2("%2d. %s\n",i,UtoDecJust(i,szDestination,8,_T('#')) );
      i++;
      }

    Output:
       9. ######9
      10. #####10
      11. #####11

 */
LPTSTR UtoDecJust(unsigned long nValue,  //number to be converted
                  LPTSTR szDestination,  //string result
                  int iSize,             //buffer length 
                  TCHAR cPad   )         //pad character
{
register int iDigit;
BOOL bFill = FALSE;

iSize--;  //Index of the last character
szDestination[iSize--] = _T('\0');    //Terminating null
iDigit = nValue % 10; //The rightmost digit

while (iSize >= 0)
  {
  if (!bFill)
    {
    szDestination[iSize--] = (TCHAR)(iDigit + _T('0')); //Insert a digit
    nValue /= 10;
    iDigit = nValue % 10;
    if ((nValue == 0) && (iDigit == 0))
      bFill = TRUE;
    }
  else  //Fill string with the pad
    szDestination[iSize--] = cPad;
  }
return szDestination;
}

