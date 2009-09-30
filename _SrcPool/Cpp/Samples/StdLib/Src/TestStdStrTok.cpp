/*$RCSfile: TestStdStrTok.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2009/09/30 20:54:36 $
  $Author: ddarko $

  C++ wrapper for string tokenizer test
  2005-03-08 Darko Kolakovic
*/

// Group=Examples

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"

extern "C" bool TestCrtStrtok(void);

//TestStrDup()-----------------------------------------------------------------
/*Test of finding a token in a string.

  Returns: true if successful, otherwise returns false.

  See also: KStrings.h, strtok_r()
  Microsoft C run-time libraries: strtok(), _strtok_l(), strtok_s().
 */
bool TestStdStrTok()
{
return TestCrtStrtok();
}

//////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 *$Log: TestStdStrTok.cpp,v $
 *Revision 1.2  2009/09/30 20:54:36  ddarko
 *Test substrings
 *
 *Revision 1.1  2009/09/29 21:20:53  ddarko
 *strtok test
 *
 *****************************************************************************/
