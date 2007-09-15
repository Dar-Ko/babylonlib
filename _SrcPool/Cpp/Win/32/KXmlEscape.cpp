/*$Workfile: KXmlEscape.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2007/09/14 12:40:16 $
  $Author: dkolakovic $

  XML manipulation helpers
  2005-05-05
 */

// Group=Windows

#include "stdafx.h" // MFC core and standard components

#ifndef _T
  #include "KTChar.h" //LPCTSTR typedef
#endif

#ifdef _DEBUG
  #ifdef _USE_MFC
    #define new DEBUG_NEW
  #endif
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
/*Escapes special XML characters in the given text with predefined entities:
      Character          XML entity
      ampersand    &        &amp;
      less than    <        &lt;
      greater than >        &gt;
      quote        "        &quot;
      apostrophe   '        &apos;

  Note: slash (\) and space ( ) characters does not require escaping.

  Returns String value containing escaped characters.
  
  Note: uses Microsoft Foundation Library (MFC) or
        uses Microsoft Active Template Library (ATL);
        Microsoft Windows specific (Win32).
*/
CString XmlEscape(CString& strData //[in]
                 )
{
strData.Replace(_T("&"),  _T("&amp;"));
strData.Replace(_T("<"),  _T("&lt;"));
strData.Replace(_T(">"),  _T("&gt;"));
strData.Replace(_T("\""), _T("&quot;"));
strData.Replace(_T("'"),  _T("&apos;"));

return strData;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
* $Log: $
*****************************************************************************/