/*$Workfile: KStrStream.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:38:42 $
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
 *  6    Biblioteka1.5         12/02/2002 4:41:45 PMDarko           comment update
 *  5    Biblioteka1.4         01/02/2002 5:32:21 PMDarko           Updated comment
 *  4    Biblioteka1.3         29/01/2002 10:22:08 PMDarko           Used lbraries
 *       notes 
 *  3    Biblioteka1.2         25/01/2002 3:58:42 PMDarko           Updated
 *       comments
 *  2    Biblioteka1.1         22/12/2001 11:26:17 PMDarko           changed header
 *  1    Biblioteka1.0         22/12/2001 11:23:03 PMDarko           
 * $
 *****************************************************************************/
