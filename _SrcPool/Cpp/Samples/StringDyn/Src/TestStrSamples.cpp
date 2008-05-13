/*$Workfile: TestStrSamples.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2008/05/13 22:21:26 $
  $Author: ddarko $

  Literals used in various test methods
  Copyright: CommonSoft Inc.
  Copyright: The Open Foundation Classes
  Portions of code are extracted from The Open Foundation Classes (OFC) project.
*/

// Group=Examples
#ifdef _USE_STL
  #ifdef _MSC_VER
    //MSVC/C++
    #pragma include_alias("stdafx.h", "stdstl.h")
  #endif
#endif

#include "stdafx.h"

#ifdef _DEBUG
 #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern "C"
{
//-----------------------------------------------------------------------------
//Test zero-terminated string with ANSI characters
TCHAR g_szTestString[] =
  {_T('T'), _T('e'), _T('s'), _T('t'), _T(':'), _T(' '),
   (TCHAR)0xE4/*ae*/,     (TCHAR)0xF6/*oe*/,      (TCHAR)0xFC/*ue*/,
   (TCHAR)0xC4/*AE*/,     (TCHAR)0xD6/*OE*/,      (TCHAR)0xDC/*UE*/,
   (TCHAR)0xDF/*doubles (eszet)*/,
   (TCHAR)0xE0/*agrave*/, (TCHAR)0xE1/*aaccent*/, (TCHAR)0xE2/*acirc*/,
   (TCHAR)0xE8/*egrave*/, (TCHAR)0xE9/*eaccent*/, (TCHAR)0xEA/*ecirc*/,
   (TCHAR)0xEC/*igrave*/, (TCHAR)0xED/*iaccent*/, (TCHAR)0xEE/*icirc*/,
   (TCHAR)0xF2/*ograve*/, (TCHAR)0xF3/*oaccent*/, (TCHAR)0xF4/*ocirc*/,
   (TCHAR)0xF9/*ugrave*/, (TCHAR)0xFA/*uaccent*/, (TCHAR)0xFB/*ucirc*/,
   (TCHAR)0x00
  };

//Test zero-terminated string with OEM characters
TCHAR g_szTestStringOem[] =
  {_T('T'), _T('e'), _T('s'), _T('t'), _T(':'), _T(' '),
   (TCHAR)0x84/*ae*/,     (TCHAR)0x94/*oe*/,      (TCHAR)0x81/*ue*/,
   (TCHAR)0x8E/*AE*/,     (TCHAR)0x99/*OE*/,      (TCHAR)0x9A/*UE*/,
   (TCHAR)0xE1/*doubles (eszet)*/,
   (TCHAR)0x85/*agrave*/, (TCHAR)0xA0/*aaccent*/, (TCHAR)0x83/*acirc*/,
   (TCHAR)0x8A/*egrave*/, (TCHAR)0x82/*eaccent*/, (TCHAR)0x88/*ecirc*/,
   (TCHAR)0x8D/*igrave*/, (TCHAR)0xA1/*iaccent*/, (TCHAR)0x8C/*icirc*/,
   (TCHAR)0x95/*ograve*/, (TCHAR)0xA2/*oaccent*/, (TCHAR)0x93/*ocirc*/,
   (TCHAR)0x97/*ograve*/, (TCHAR)0xA3/*oaccent*/, (TCHAR)0x96/*ocirc*/,
   (TCHAR)0x00
  };

 //Test sentences
LPCTSTR g_szTest[] =
  {
  _T("Faber est suae quisque fortunae") // 0. Every man is the artisan of his own fortune
  };
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: TestStrSamples.cpp,v $
 * Revision 1.2  2008/05/13 22:21:26  ddarko
 * CString test cases
 *
 * Revision 1.1  2008/05/12 21:35:59  ddarko
 * Created
 *
 *****************************************************************************/

/************************************************************************
  T h e   O p e n   F o u n d a t i o n    C l a s s e s
  ------------------------------------------------------------------------
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  ------------------------------------------------------------------------
  Copyright (c) 2000-04 The Open Foundation Classes
  Copyright (c) 2003-04 William D. Herndon
**************************************************************************/
