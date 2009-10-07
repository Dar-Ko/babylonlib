/*$RCSfile: TestText.c,v $: implementation file
  $Revision: 1.3 $ $Date: 2009/10/07 21:42:17 $
  $Author: ddarko $

  Global test samples
  Feb 20 12:43:59 2003 Manoj Srivastava (srivasta@glaurung.green-gryphon.com)
*/

/* Group=Examples
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
#include "stdafx.h"

/*Single-byte character set (SBCS) text samples
 */
const char* g_listTestStringsA[] =
  {
  "This is a longish text string, but not that long, at that",
  "The long jump \0 and some trailing text at-that",
  "",
  "Some more test strings",
  "Yet another one",
  "what-finally-stops--at-at-that point",
  "aksdy923492p4  p39475 q0349750[q3hf30q79340 320496t034 03q495609324uy509y",
  "character is considered to be part of the string. The chr at-that point",
  NULL   //list terminator
  };

/* ///////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: TestText.c,v $
 * Revision 1.3  2009/10/07 21:42:17  ddarko
 * Test tag names
 *
 *****************************************************************************/
