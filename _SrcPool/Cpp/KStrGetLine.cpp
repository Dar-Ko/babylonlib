/*$Workfile: KStrGetLine.cpp$: implementation file
  $Revision: 6$ $Date: 19/08/2002 9:40:47 AM$
  $Author: Darko Kolakovic$

  Read a line of text from a string buffer
  CommonSoft Inc.
  Jun 2001 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#ifndef _TCHAR_DEFINED
  #include "KTChar.h" //TCHAR typedef
#endif
#include "KTrace.h"   //ASSERT macro

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//GetLine()--------------------------------------------------------------------
/*Functions scans input buffer until it finds end of line characters (LF, CR or
  CR-LF pair).
  The line read will be copied in a resulting buffer. Caller should delete the
  buffer before the program exits. Function as well moves pointer of the source
  buffer to the start of the next line.

  Returns: number of characters in the scanned line less end of line characters,
  but including terminating zero. Also returns a pointer to the beginning of 
  next line and zero-terminated string containing a line of text and pointer 
  to the beginning of next line. If source is an empty string, function returns 
  zero and null pointer in szLine parameter.

  Throws: bad_alloc.

  See also: EOL, EOLUNIX, EOLDOS, EOLMAC, {HTML: <A HREF ="Res/ASCIICharTable.htm#End-of-line_Characters">
    ASCII Character Table </A>}
  
  Example:

      #include "KStrings.h"
      int main()
        {
        LPTSTR szText = "Summer Time\nLast year the summer was long, long...\n";
        LPTSTR szSource = szText;
        LPTSTR szLine;
        while(GetLine(szSource, szLine) > 0)
          {
          if(szLine != NULL)
            {
            printf(szLine);
            printf("<EOL>\n");
            delete[] szLine;
            }
          }
        }
 */
int GetLine(LPTSTR& szSource,//[in/out] zero-terminated text buffer to parse
            LPTSTR& szLine   //[out] resulting line of text or NULL is szSource
			                 //is an empty string
           )
{
int iRes = 0;
szLine = NULL;
if( (szSource != NULL) && (szSource[0] != _T('\0')) )
  {
  int iPos = 0;
  while(szSource[iPos] != _T('\0'))
    {
    const TCHAR CR = _T('\r');
    const TCHAR LF = _T('\n');
    if(szSource[iPos] == LF)   //Unix End-of-Line
      {
      iRes = ++iPos;
      break;
      }

    if(szSource[iPos] == CR)   //Mac End-of-Line
      {
      iRes = ++iPos;
      if(szSource[iPos] == LF) //DOS/Win End-of-Line
        iPos++;
      break;
      }

    iPos++;
    }

    if (iRes == 0) //Source doesn't have any EOL
      {
      iRes = iPos;
        //Allocate space for text and terminating zero
      szLine = new TCHAR[iRes + 1]; //Throws bad_alloc if unsuccessful
      if(szLine != NULL) //Validation in case new() has been overridden
        {
        _tcsncpy(szLine,szSource,iRes);
        szLine[iRes] = _T('\0');
        }
      }
    else
      {
      szLine = new TCHAR[iRes]; //Throws bad_alloc if unsuccessful
      if(szLine != NULL) //Validation in case new() has been overridden
        {
        _tcsncpy(szLine,szSource,iRes);
        szLine[iRes - 1] = _T('\0');
        }
      }
    szSource = &szSource[iPos];
  }
return iRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         19/08/2002 9:40:47 AMDarko Kolakovic Updated
 *       comments
 *  5    Biblioteka1.4         12/02/2002 9:53:46 AMDarko           fixed /n/r case
 *  4    Biblioteka1.3         05/02/2002 6:46:49 PMDarko           LPTSTR&
 *       szSource
 *  3    Biblioteka1.2         04/02/2002 5:36:58 PMDarko           
 *  2    Biblioteka1.1         04/02/2002 1:33:37 PMDarko           Added LF
 *  1    Biblioteka1.0         01/02/2002 5:31:21 PMDarko           
 * $
 *****************************************************************************/
