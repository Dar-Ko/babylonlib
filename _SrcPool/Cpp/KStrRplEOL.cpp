/*$Workfile: KStrRplEOL.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:38:42 $
  $Author: ddarko $

  Replaces Unix EOL with DOS End-of-Line markers
  Copyright: CommonSoft Inc.
  Jun 2001 Darko Kolakovic
*/

#include <string> //std::string
#ifndef _TCHAR_DEFINED
  #include "KTChar.h" //TCHAR typedef
#endif

//::ReplaceEOL()---------------------------------------------------------------
/*Replaces one character End-of-Line markers (CR) with two characters (CR,LF).
  
  Returns: STL string with new End-of-Line markers.

  Note: uses Standard Template Library (STL).
 */
std::string& ReplaceEOL(LPCTSTR szText, //[in] zero-teminated text 
                        std::string& strResult //[out] text with new End-of-Line 
                                               //markers
                       )
{
const TCHAR CR = _T('\r');
const TCHAR LF = _T('\n');

  //Count CR characters that are not in CRLF pairs
UINT nIndex = 0;
UINT nCount = 0;
while(szText[nIndex] != _T('\0'))
  {
  if((szText[nIndex] == CR) && (szText[nIndex+1] != LF))
    nCount++;
  if((szText[nIndex] == LF) && ((nIndex == 0) || (szText[nIndex-1] != CR)))
    nCount++;

  nIndex++;
  }

strResult.empty();
if(nCount > 0)
  {
  strResult.resize(nIndex + nCount + 1);

  nIndex = 0;
  nCount = 0;
  while(szText[nIndex] != _T('\0'))
    {
    strResult.at(nCount) = szText[nIndex];
    if((szText[nIndex] == LF) && ((nIndex == 0) || (szText[nIndex-1] != CR)))
      {
      strResult.at(nCount) = CR;
      nCount++;
      strResult.at(nCount) = LF;
      }

    if((szText[nIndex] == CR) && (szText[nIndex+1] != LF))
      {
      nCount++;
      strResult.at(nCount) = LF;
      }
    nIndex++;
    nCount++;
    }
  }
else
  strResult = szText;

return strResult;
}

///////////////////////////////////////////////////////////////////////////////
