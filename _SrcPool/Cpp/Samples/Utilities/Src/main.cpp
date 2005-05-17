/*$Workfile: main.cpp$: implementation file
  $Revision: 5$ $Date: 2005-05-16 14:22:38$
  $Author: Darko Kolakovic$

  Console application used to test various helper functions
  Copyright: CommonSoft Inc
  Sep 2k2 Darko Kolakovic
*/

// Group=Examples
#ifdef _MSC_VER     /*Microsoft Visual Studio C/C++ compiler                 */
  #ifdef _DOS
     //Already a console
    #ifndef _CONSOLE
      #define _CONSOLE
    #endif
  #else             /*Windows Console Application                            */
    #ifndef _CONSOLE
      #error "define _CONSOLE macro in the project"
    #endif
  #endif
#endif

#ifdef __GNUG__     /*GNU C++ compiler                                       */
  #ifndef _CONSOLE
    #warning "define _CONSOLE macro in the project"
  #endif
#endif

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DOS
  #include <stdio.h>    //printf()
  #include <stdlib.h>   //EXIT_FAILURE macro
  //TODO : move .h  to Common/SRC/DOs/stdafx.h
#endif

#include "stdafx.h"

extern bool TsWriteToViewLn(LPCTSTR lszText);
extern int TestCommonUtilities();

//main()-----------------------------------------------------------------------
/*Validate different utility routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int main()
{
TsWriteToViewLn(_T("Start Utility Tests"));
TsWriteToViewLn(_T(""));
int nRetCode = EXIT_SUCCESS;

nRetCode = TestCommonUtilities();

return nRetCode;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2002-10-11 14:33:41  Darko Kolakovic
 *  2    Biblioteka1.1         2002-10-10 20:37:16  Darko Kolakovic Fixed 16-bit
 *       version
 *  1    Biblioteka1.0         2002-09-16 17:58:59  Darko Kolakovic
 * $
 *****************************************************************************/
