/*$Workfile: KStrStream.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  String helpers and CString extension with STL operators
  Copyright: CommonSoft Inc.
  May '97 Darko Kolakovic
 */
/* Group=Strings                                                             */

#include "StdAfx.h"
#include <IOstream.h>
#include <IOManip.h>

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
  Note: uses Microsoft Fundation Library (MFC) and Standard Template Library
       (STL).
 */
istream& operator>>(istream& cInput,   //input stream
                    CString& strTarget //[out]
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
  Note: uses Microsoft Fundation Library (MFC) and Standard Template Library
       (STL).
 */
ostream& operator<<(ostream& cOutput,        //output stream
                    const CString& strSource //[in]
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
 *  6    Biblioteka1.5         2/12/02 5:41:45 PM   Darko           comment update
 *  5    Biblioteka1.4         2/1/02 6:32:21 PM    Darko           Updated comment
 *  4    Biblioteka1.3         1/29/02 11:22:08 PM  Darko           Used lbraries
 *       notes 
 *  3    Biblioteka1.2         1/25/02 4:58:42 PM   Darko           Updated
 *       comments
 *  2    Biblioteka1.1         12/23/01 12:26:17 AM Darko           changed header
 *  1    Biblioteka1.0         12/23/01 12:23:03 AM Darko           
 * $
 *****************************************************************************/
