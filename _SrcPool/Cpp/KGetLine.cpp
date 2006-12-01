/*$Workfile: KGetLine.cpp$: implementation file
  $Revision: 5$ $Date: 2004-06-01 16:50:33$
  $Author: Darko$

  Read a line of text from a stream
  CommonSoft Inc.
  Jun 2001 Darko Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

//#include "stdafx.h"
#include <afxwin.h>


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

  TODO: replace MFC D.K.
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
 *  5    Biblioteka1.4         2004-06-01 16:50:33  Darko           time sync
 *  4    Biblioteka1.3         2003-09-05 12:15:54  Darko           excluded
 *       StdAfx.h
 *  3    Biblioteka1.2         2002-02-17 02:17:08  Darko           Comment updated
 *  2    Biblioteka1.1         2002-01-29 14:40:04  Darko           Tag update
 *  1    Biblioteka1.0         2001-12-22 23:19:02  Darko           
 * $
 *****************************************************************************/
