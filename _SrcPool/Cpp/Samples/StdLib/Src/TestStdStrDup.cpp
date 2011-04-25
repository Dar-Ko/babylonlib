/*$RCSfile: TestStdStrDup.cpp,v $: implementation file
  $Revision: 1.4 $ $Date: 2011/04/25 20:31:06 $
  $Author: ddarko $

  C++ wrapper for string copying test
  2005-03-08 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"

extern "C" bool TestCrtStrDup(void);

//TestStrDup()-----------------------------------------------------------------
/*Test of copying a string to a buffer.

  Returns: true if successful, otherwise returns false.

  See also: KStrings.h, StrDup(),
  Microsoft C run-time libraries: _strdup(), _wcsdup(), _mbsdup().
 */
bool TestStdStrDup()
{
return TestCrtStrDup();
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: TestStdStrDup.cpp,v $
 *Revision 1.4  2011/04/25 20:31:06  ddarko
 *Updated test case
 *
 *Revision 1.3  2009/09/29 21:57:44  ddarko
 *C++ wrapper
 *
 *Revision 1.2  2009/09/29 18:53:05  ddarko
 *strdup test
 *
 *****************************************************************************/
