/*$Workfile: KStColor.c$: implementation file
  $Revision: 1$ $Date: 2004-11-12 16:55:54$
  $Author: Darko Kolakovic$

  Converts a string to the color.
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

/*Convert the name of a color into index of a color from the basic 4-bit
  palette.

  Returns: index of the color or error.

  See also: {html:<a href="Documentation/KColorCt.htm">}16 colors palette
            {html:</a>}
 */
COLOR StrToColor(LPCTSTR szColor /*[in] one of the 16 possible colors*/
                  )
{
_totlower(szColor);
if( str_cmp(str, _T("black")       ) == 0) return(black       );
if( str_cmp(str, _T("blue")        ) == 0) return(blue        );
if( str_cmp(str, _T("green")       ) == 0) return(green       );
if( str_cmp(str, _T("cyan")        ) == 0) return(cyan        );
if( str_cmp(str, _T("red")         ) == 0) return(red         );
if( str_cmp(str, _T("magenta")     ) == 0) return(magenta     );
if( str_cmp(str, _T("brown")       ) == 0) return(brown       );
if( str_cmp(str, _T("white")       ) == 0) return(white       );
if( str_cmp(str, _T("lightgray")   ) == 0) return(white       );
if( str_cmp(str, _T("gray")        ) == 0) return(grey        );
if( str_cmp(str, _T("darkgray")    ) == 0) return(grey        );
if( str_cmp(str, _T("lightblue")   ) == 0) return(lightblue   );
if( str_cmp(str, _T("lightgreen")  ) == 0) return(lightgreen  );
if( str_cmp(str, _T("lightcyan")   ) == 0) return(lightcyan   );
if( str_cmp(str, _T("lightred")    ) == 0) return(lightred    );
if( str_cmp(str, _T("lightmagenta")) == 0) return(lightmagenta);
if( str_cmp(str, _T("yellow")      ) == 0) return(yellow      );
if( str_cmp(str, _T("brightwhite") ) == 0) return(brightwhite );
return(error);

}

/* ///////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 *$Log: 
 * 1    Biblioteka1.0         2004-11-12 16:55:54  Darko Kolakovic 
 *$
 *****************************************************************************/
