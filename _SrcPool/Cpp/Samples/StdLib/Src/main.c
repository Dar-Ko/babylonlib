/*$Workfile: main.c$: implementation file
  $Revision: 2$ $Date: 2004-10-04 12:51:19$
  $Author: Darko$

  Test implemented Standard Library routines.
  Copyright: CommonSoft Inc.
  2004-08-14 Darko Kolakovic
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

extern int TestCommonStdLib();

//-----------------------------------------------------------------------------
/*Validates C Standard Library routines. 
  Defines the entry point for the console application.

  Returns: EXIT_SUCCESS, which represents a value of 0, if succesfull. Otherwise
  a non-zero error code is returned.
 */
int main()
{
return TestCommonStdLib();
}

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2004-10-04 12:51:19  Darko           Renamed test
 *       script to TestCommonStdLib
 *  1    Biblioteka1.0         2004-09-14 12:54:51  Darko           
 * $
 *****************************************************************************/
