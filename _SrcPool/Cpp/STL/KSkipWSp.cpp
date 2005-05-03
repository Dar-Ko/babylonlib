/*$Workfile: KSkipWSp.cpp$: implementation file
  $Revision: 7$ $Date: 2004-06-01 18:03:46$
  $Author: Darko$

  Skip white spaces from the stream
  Copyright: CommonSoft Inc
  Dec. 99 Darko Kolakovic
*/
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _DEBUG
  #ifndef _STLP_DEBUG
    #define _STLP_DEBUG 1    //Debug STLPort library
  #endif
#else
  #ifdef _STLP_DEBUG
    #undef _STLP_DEBUG
  #endif
#endif

#include <iostream.h>

#ifndef BOOL
  #include "KTypedef.h" //BOOL
#endif

//SkipWhiteSpace()-------------------------------------------------------------
/*Function reads characters from the stream and skips over white space.
  White space is one of following characters: space, tab, carriage return,
  newline, vertical tab or form feed (0x09 – 0x0D or 0x20).

  Returns: FALSE if stream is at end of file, otherwise returns TRUE.

  Note: uses Standard Template Library (STL).

  Example:
      void MyFunc()
        {
        int ch;

        while (SkipWhiteSpace(cin)) //Skip white spaces
          {
          cin >> ch;
          cout << ch;
          }
        }

 */
BOOL SkipWhiteSpace(istream& Stream //[in/out] input stream
                    )
{
int ch;

ch = Stream.peek(); //Read character without extracting it from the stream
while (_istspace(ch))
  {
  Stream.get();
  ch = Stream.peek();
  }

if (ch == _EOFCH)
   return FALSE; //End-of-file
else
   return TRUE;
}
