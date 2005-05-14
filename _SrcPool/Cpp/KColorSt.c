/*$Workfile: S:\_SrcPool\Cpp\KColorSt.c$: implementation file
  $Revision: 2$ $Date: 2005-05-11 09:11:54$
  $Author: Darko Kolakovic$

  Converts a color to the string.
  Copyright: CommonSoft Inc.
  Mar 1989 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
/*Replaces library header file names with the compiler's aliases*/
#ifdef _USE_STD_HEADERS
  #ifdef _WIN32
    #ifdef _MSC_VER //Micorsoft C++ compiler
      #ifdef _UNICODE
        #ifndef UNICODE
          //To enable Unicode for some Microsoft Visual C/C++ header files,
          //the UNICODE definition is required
          #define UNICODE
        #endif
      #endif
      #pragma include_alias(_T("KTChar.h", "wtypes.h")
    #endif  //_MSC_VER
  #endif  //_WIN32

#endif  //_USE_STD_HEADERS

#include "KTChar.h" /*LPCTSTR typedef*/
#include "KColorCt.h"

/*---------------------------------------------------------------------------*/

/*Converts index of a color from basic 4-bit palette to related string.

  Returns: a name of the color as zero-terminated string.
  There is no error return.

  See also: {html:<a href="Documentation/KColorCt.htm">}16 colors palette
            {html:</a>}
 */
LPCTSTR ColorToStr(COLOR color /*[in] one of the 16 possible colors*/
                  )
{
switch(color)
  {
  case black        : return(_T("black"));
  case blue         : return(_T("blue"));
  case green        : return(_T("green"));
  case cyan         : return(_T("cyan"));
  case red          : return(_T("red"));
  case magenta      : return(_T("magenta"));
  case brown        : return(_T("brown"));
  case white        : return(_T("white"));
  case grey         : return(_T("gray"));
  case lightblue    : return(_T("lightblue"));
  case lightgreen   : return(_T("lightgreen"));
  case lightcyan    : return(_T("lightcyan"));
  case lightred     : return(_T("lightred"));
  case lightmagenta : return(_T("lightmagenta"));
  case yellow       : return(_T("yellow"));
  case brightwhite  : return(_T("brightwhite"));
  }
}

/* ///////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 *$Log:
 * 1    Biblioteka1.0         2004-11-12 17:55:51  Darko Kolakovic
 *$
 *****************************************************************************/
