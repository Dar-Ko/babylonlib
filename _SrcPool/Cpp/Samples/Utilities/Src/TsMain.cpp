/*$Workfile: TsMain.cpp$: implementation file
  $Revision: 3$ $Date: 10/11/02 2:33:41 PM$
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
#else
  #include <iostream>
  #include <iomanip.h>  //std::endl
  #include <string>     //std::string
#endif

#include "KTrace.h"   //TRACE macro
#include "KTypedef.h" //bool typedef
#include "KDbgMacr.h"

extern bool TestBeep();

//TsWriteToView()--------------------------------------------------------------
#ifndef _DOS
/*Writes a character string at the console standard output stream.

  Returns: TRUE always.
  
  Note: uses Standard Template Library (STL).
 */
  bool TsWriteToView(LPCTSTR lszText)
  {
  if (lszText != NULL)
    cout << lszText;
  else
    cout << "<null>";
  cout.flush();
  return true;
  }           
  
#else //DOS
  bool TsWriteToView(LPCTSTR lszText)
  {
  if (lszText != NULL)
    printf(lszText);
  else
    printf("<null>");
  return true;
  }           
#endif

//main()-----------------------------------------------------------------------
/*Validate different utility routines.

  Returns: EXIT_SUCCESS, which represents a value of 0, if successful. Otherwise
  a non-zero error code is returned.
 */
int main()
{     
TsWriteToView("Start Utility tests:\r\n\r\n");

if(TestBeep())
  TsWriteToView("Succeeded.\r\n\r\n");
else
  {
  TsWriteToView("Failed!.\a\r\n");
  return EXIT_FAILURE + 1;
  }

return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         10/11/02 2:33:41 PM  Darko Kolakovic 
 *  2    Biblioteka1.1         10/10/02 8:37:16 PM  Darko Kolakovic Fixed 16-bit
 *       version
 *  1    Biblioteka1.0         9/16/02 5:58:59 PM   Darko Kolakovic 
 * $
 *****************************************************************************/
