/*$Workfile: KStrStream.cpp$: implementation file
  $Revision: 10$ $Date: 2005-04-26 16:46:11$
  $Author: Darko Kolakovic$

  String helpers and CString extension with STL operators
  Copyright: CommonSoft Inc.
  May '97 Darko Kolakovic
 */
/* Group=Strings                                                             */

//#include "stdafx.h"
#ifdef _DEBUG
  #ifndef _STLP_DEBUG
    #define _STLP_DEBUG 1    //Debug STLPort library
  #endif
#else
  #ifdef _STLP_DEBUG
    #undef _STLP_DEBUG
  #endif
#endif

#include <afxwin.h>
#include <iostream.h>
#include <iomanip.h>

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//Functions using MFC
#ifdef __AFXWIN_H__
///////////////////////////////////////////////////////////////////////////////
// CString Extension functions

//operator>>()-----------------------------------------------------------------
/*The operator>> is used to populate a string with the contents of an input
  stream. Input buffer is limited to MINIMUMLENGHT characters.

  Note: uses Microsoft Foundation Library (MFC) and Standard Template Library
       (STL).

  TODO: replace MFC D.K.
 */
istream& operator>>(istream& cInput,   //[in] input stream
                    CString& strTarget //[out] resulting string
                    )
{
const int MINIMUMLENGHT = 256;
char strTemp[MINIMUMLENGHT];
//Pad the field with the stream’s fill character, up to MINIMUMLENGHT
cInput >> setw(MINIMUMLENGHT) >> strTemp;
strTarget = CString(strTemp);
return cInput;
}

//operator<<()-----------------------------------------------------------------
/*The operator<< is used to insert a string into an output stream.

  Note: uses Microsoft Foundation Library (MFC) and Standard Template Library
       (STL).

  TODO: replace MFC D.K.
 */
ostream& operator<<(ostream& cOutput,        //[out] output stream
                    const CString& strSource //[in] string to output
                    )
{
int i = 0;
while(i < strSource.GetLength())
  {
  cOutput << strSource[i];
  i++;
  }
return cOutput;
}

///////////////////////////////////////////////////////////////////////////////
#endif //__AFXWIN_H__

///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  8    Biblioteka1.7         2003-09-04 11:18:02  Darko           stdafx.h
 *       excluded
 *  7    Biblioteka1.6         2003-08-07 17:21:40  Darko           comment
 *  6    Biblioteka1.5         2002-02-12 17:41:45  Darko           comment update
 *  5    Biblioteka1.4         2002-02-01 18:32:21  Darko           Updated comment
 *  4    Biblioteka1.3         2002-01-29 23:22:08  Darko           Used lbraries
 *       notes
 *  3    Biblioteka1.2         2002-01-25 16:58:42  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-12-23 00:26:17  Darko           changed header
 *  1    Biblioteka1.0         2001-12-23 00:23:03  Darko
 * $
 *  0    May 97 Darko Kolakovic
 *****************************************************************************/
