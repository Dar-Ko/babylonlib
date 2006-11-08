/*$Workfile: main.cpp$: implementation file
  $Revision: 14$ $Date: 2004-10-04 23:51:32$
  $Author: Darko$

  Test numerical and machine dependent routines.
  Copyright: CommonSoft Inc.
  July 2k1 D.Kolakovic
*/

// Group=Examples


#ifdef _MSC_VER     /*Microsoft Visual Studio C/C++ compiler                 */
  #ifndef _CONSOLE
    #error "define _CONSOLE macro in the project"
  #endif
#endif

#ifdef __GNUG__     /*GNU C++ compiler                                       */
  #ifndef _CONSOLE
    #warning "define _CONSOLE macro in the project"
  #endif
#endif

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern int TestCommonNumeric();

//main()-----------------------------------------------------------------------
/*Validate different numerical and machine dependent routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesfull. Otherwise
  a non-zero error code is returned.
 */
int main()
{
TsWriteToViewLn(_T("Start Numerical Methods Tests"));
TsWriteToViewLn(_T(""));
int nRetCode = EXIT_SUCCESS;

nRetCode = TestCommonNumeric();

return nRetCode;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  14   Biblioteka1.13        2004-10-04 23:51:32  Darko           fixed
 *       unresolbed TestCommonNumeric()
 *  13   Biblioteka1.12        2004-10-04 23:26:23  Darko           moved to
 *       TestCommonNumeric.cpp
 *  12   Biblioteka1.11        2004-07-09 02:38:02  Darko           TestRound
 *  11   Biblioteka1.10        2004-07-07 17:41:05  Darko           replaced
 *       iomainp.h with stdafx.h
 *  10   Biblioteka1.9         2002-08-03 19:27:55  Darko           
 *  9    Biblioteka1.8         2002-03-14 16:49:54  Darko Kolakovic 
 *  8    Biblioteka1.7         2002-03-11 19:30:14  Darko           KIsPrimeNo()
 *  7    Biblioteka1.6         2002-03-04 19:14:24  Darko          
 *       TestNetByteOrder()
 *  6    Biblioteka1.5         2002-02-03 21:49:01  Darko           
 *  5    Biblioteka1.4         2002-02-03 18:13:29  Darko           Header
 *  4    Biblioteka1.3         2002-02-03 18:11:17  Darko           
 *  3    Biblioteka1.2         2002-01-28 01:01:43  Darko           
 *  2    Biblioteka1.1         2001-07-26 21:35:51  Darko           func... =>
 *       eqt...
 *  1    Biblioteka1.0         2001-07-20 01:15:32  Darko           
 * $
 *****************************************************************************/
