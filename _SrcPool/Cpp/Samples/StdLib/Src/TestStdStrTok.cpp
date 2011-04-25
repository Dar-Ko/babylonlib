/*$RCSfile: TestStdStrTok.cpp,v $: implementation file
  $Revision: 1.3 $ $Date: 2011/04/25 20:31:06 $
  $Author: ddarko $

  C++ wrapper for string tokenizer test
  2005-03-08 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"

extern "C" bool TestCrtStrTok(void);

//TestStrDup()-----------------------------------------------------------------
/*Test of finding a token in a string.

  Returns: true if successful, otherwise returns false.

  See also: KStrings.h, strtok_r()
  Microsoft C run-time libraries: strtok(), _strtok_l(), strtok_s().
 */
bool TestStdStrTok()
{
return TestCrtStrTok();
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: TestStdStrTok.cpp,v $
 *Revision 1.3  2011/04/25 20:31:06  ddarko
 *Updated test case
 *
 *Revision 1.2  2009/09/30 20:54:36  ddarko
 *Test substrings
 *
 *Revision 1.1  2009/09/29 21:20:53  ddarko
 *strtok test
 *
 *****************************************************************************/
