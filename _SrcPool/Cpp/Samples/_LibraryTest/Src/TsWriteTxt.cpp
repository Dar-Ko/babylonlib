/*$Workfile: S:\_SrcPool\Cpp\Samples\_LibraryTest\Src\TsWriteTxt.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2003/01/31 03:05:28 $
  $Author: ddarko $

  Outputs text to stdout stream
  Copyright: CommonSoft Inc.
  Jan. 2k2 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#ifdef _CONSOLE
//TsWriteToView()--------------------------------------------------------------
/*Writes a character string at the console standard output stream.

  Returns: true always.
  
  Note: uses Standard Template Library (STL).
 */
bool TsWriteToView(LPCTSTR lszText)
{
if (lszText != NULL)
  cout << lszText;
else
  cout << _T("<null>");
cout.flush();
return true;
}

#endif //_CONSOLE
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         27/01/2003 9:37:26 PMDarko           
 * $
 *****************************************************************************/
