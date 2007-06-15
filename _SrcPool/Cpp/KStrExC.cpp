/*$Workfile: KStrExC.cpp$: implementation file
  $Revision: 9$ $Date: 2007-06-15 17:24:21$
  $Author: Darko Kolakovic$

  Extract number of characters from CString
  May '97 Darko Kolakovic
*/
/* Group=Strings                                                             */

#include "stdafx.h"
#ifndef _USE_MFC
  #include "KStringHandler.h"
  #include "KString.h"  //CString class
#endif //_USE_MFC
#include "KStrExt.h"  //Declarations

#ifdef _DEBUG
  #ifdef _USE_MFC
    #define new DEBUG_NEW
  #endif //_USE_MFC
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//Functions using MFC
#ifdef __AFXWIN_H__

//Extract()--------------------------------------------------------------------
/*Extracts an array of characters from the given string. Start and the end
  postion of extraction is validated against length of source string.
  Returns: an extracted string and source string less extracted part.

  Note: uses Microsoft Foundation Library (MFC).

  TODO: replace MFC D.K.
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
#else
  #pragma message("warning: TODO")
///////////////////////////////////////////////////////////////////////////////
#endif //__AFXWIN_H__

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  9    Biblioteka1.8         2007-06-15 17:24:21  Darko Kolakovic _USE_MFC for
 *       CString
 *  8    Biblioteka1.7         2005-04-26 16:39:18  Darko Kolakovic fixed typo
 *  7    Biblioteka1.6         2004-06-01 17:53:06  Darko           time sync
 *  6    Biblioteka1.5         2003-09-04 09:19:52  Darko           commented out
 *       StdAfx.h
 *  5    Biblioteka1.4         2003-09-04 09:10:48  Darko           comment
 *  4    Biblioteka1.3         2002-01-29 23:21:55  Darko           Used library
 *       notes 
 *  3    Biblioteka1.2         2002-01-25 16:58:04  Darko           Updated
 *       comments
 *  2    Biblioteka1.1         2001-12-23 01:12:23  Darko           Comments
 *  1    Biblioteka1.0         2001-08-18 16:04:07  Darko           
 * $
 *  0    Biblioteka0           Darko Kolakovic  May '97
 *****************************************************************************/
