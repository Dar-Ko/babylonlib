/*$Workfile: KGetLine.cpp$: implementation file
  $Revision: 3$ $Date: 2/17/02 3:17:08 AM$
  $Author: Darko$

  Read a line of text from a stream
  CommonSoft Inc.
  Jun 2001 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include "StdAfx.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#ifdef _UNICODE
  #define _INTCH wint_t
  #define _EOFCH WEOF
#else
  #define _INTCH int
  #define _EOFCH EOF
#endif

//GetLine()--------------------------------------------------------------------
/*Functions scans in a stream until it finds end of line characters (LF <or
  TODO: CR-LF pair>).
  Returns: number of characters in the scanned line less
  end of line characters.
 */
int GetLine(FILE* fpSource,   //[in] file stream to parse
            CString& strLine  //[out] resulting line of text
           )
{
_INTCH ch;
int iRes = 0;
strLine.Empty();

while((ch = _fgettc(fpSource)) != _EOFCH && ch != _T('\n'))
  {
  strLine += (TCHAR)ch;
  iRes++;
  }
return iRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2/17/02 3:17:08 AM   Darko           Comment updated
 *  2    Biblioteka1.1         1/29/02 3:40:04 PM   Darko           Tag update
 *  1    Biblioteka1.0         12/23/01 12:19:02 AM Darko           
 * $
 *****************************************************************************/
