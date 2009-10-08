/*$RCSfile: KXmlEscape.cpp,v $: implementation file
  $Revision: 1.1 $ $Date: 2009/10/08 21:37:39 $
  $Author: ddarko $

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

  See also: VB Function XmlEscape, Function XmlUnescape,
  Boost STL class xml_escape,class xml_unescape
*/
CString XmlEscape(CString& strData //[in] text to be converted to  the XML format
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
* $Log: KXmlEscape.cpp,v $
* Revision 1.1  2009/10/08 21:37:39  ddarko
* Moved from \Win\32
*
*****************************************************************************/