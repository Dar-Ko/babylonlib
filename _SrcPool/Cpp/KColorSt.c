/*$Workfile: KColorSt.c$: implementation file
  $Revision: 1$ $Date: 2004-11-12 16:55:51$
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
      #pragma include_alias("KTChar.h", "wtypes.h")
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
  case black        : return("black");
  case blue         : return("blue");
  case green        : return("green");
  case cyan         : return("cyan");
  case red          : return("red");
  case magenta      : return("magenta");
  case brown        : return("brown");
  case white        : return("white");
  case grey         : return("gray");
  case lightblue    : return("lightblue");
  case lightgreen   : return("lightgreen");
  case lightcyan    : return("lightcyan");
  case lightred     : return("lightred");
  case lightmagenta : return("lightmagenta");
  case yellow       : return("yellow");
  case brightwhite  : return("brightwhite");
  }
}

/* ///////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 *$Log: 
 * 1    Biblioteka1.0         2004-11-12 16:55:51  Darko Kolakovic 
 *$
 *****************************************************************************/
