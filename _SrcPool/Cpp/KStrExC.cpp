/*$Workfile: KStrExC.cpp$: implementation file
  $Revision: 4$ $Date: 1/29/02 11:21:55 PM$
  $Author: Darko$

  Extract number of characters from CString
  May '97 Darko Kolakovic
*/
/* Group=Strings                                                             */

#include "StdAfx.h"
#include "KStrExt.h"  //Declarations

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//Functions using MFC
#ifdef __AFXWIN_H__

//Extract()--------------------------------------------------------------------
/*Extracts an array of characters from the given string. Start and the end
  postion of extraction is validated against legth of source string.
  Returns: an extracted string and source string less exctracted part.

  Note: uses Microsoft Fundation Library (MFC). 
 */
CString Extract(CString& strSrc, //[in/out] source string
                const int iStart,//[in] starting postion to extract from
                const int iEnd   //[in] extract up to iEnd
                )
{
CString strRes;
if(iStart <= iEnd && iStart < strSrc.GetLength())
  {
  strRes = strSrc.Mid(iStart, iEnd - iStart + 1);
  strSrc = strSrc.Mid(0, iStart) + strSrc.Mid(iEnd + 1);
  }
return strRes;
}

///////////////////////////////////////////////////////////////////////////////
#endif //__AFXWIN_H__

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  0    Biblioteka0           Darko Kolakovic  May '97
 * $
 *****************************************************************************/
