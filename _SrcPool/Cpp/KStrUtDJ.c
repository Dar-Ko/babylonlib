/*$Workfile: KStrUtDJ.c$: implementation file
  $Revision: 7$ $Date: 2004-06-01 17:53:44$
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

#ifndef bool
  #include "KTypedef.h" //bool
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
bool bFill = false;

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
/*****************************************************************************
 * $Log: 
 *  7    Biblioteka1.6         2004-06-01 17:53:44  Darko           time sync
 *  6    Biblioteka1.5         2003-09-25 01:27:14  Darko           Replaced BOOL
 *       with bool
 *  5    Biblioteka1.4         2002-02-12 17:39:29  Darko           Replaced
 *       tchar.h with KTChar.h
 *  4    Biblioteka1.3         2001-12-23 01:23:04  Darko           BOOL
 *  3    Biblioteka1.2         2001-07-11 22:52:59  Darko           
 *  2    Biblioteka1.1         2001-06-08 23:52:01  Darko           VSS
 *  1    Biblioteka1.0         2000-09-21 01:13:49  Darko           
 * $
 *****************************************************************************/

