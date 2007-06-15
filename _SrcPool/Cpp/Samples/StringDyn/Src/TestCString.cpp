/*$Workfile: TsCString.cpp$: implementation file
  $Revision: 4$ $Date: 2002-08-19 10:36:43$
  $Author: Darko Kolakovic$

  Test for CString class (STL port)
  Copyright: CommonSoft Inc.
  Jan. 2k2 Darko Kolakovic
*/
// Group=Examples


/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifndef _MFC_VER //Microsoft MFC library
  //include STL implementation for CString
  #include <string> //std::basic_string template
#endif

#ifdef __INCvxWorksh  //VxWorks OS
  #if CPU == SIMNT //target is simulator on WinNT
    #include <stdarg.h>   //va_list
  #endif
#endif

#include "KTypedef.h"  //BOOL typedef
#include "KString.h"   //CString class

extern BOOL TsWriteToView(LPCTSTR lszText);

//TestStringClass()------------------------------------------------------------
/*Function shows how to use CString object.
  TODO:
  
  Returns: true if successful, otherwise returns false.
 
 */
bool TestStringClass()
{
TsWriteToView("TestStringClass()\r\n");
TsWriteToView("TODO:\r\n");
TsWriteToView("======================\r\n");
return true;
}

//////////////////////////////////////////////////////////////////////////////
