/*$Workfile: H:\_SrcPool\Cpp\KSkipWSp.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:19:04 $
  $Author: ddarko $

  Skip white spaces from the stream
  Copyright: CommonSoft Inc
  Dec. 99 Darko Kolakovic
*/
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */


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
