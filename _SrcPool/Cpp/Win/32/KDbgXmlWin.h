/*$Workfile: KDbgXmlWin.h$: header file
  $Revision: 2$ $Date: 2005-04-29 01:13:03$
  $Author: Darko$

  Dumps XML objects
  Copyright: CommonSoft Inc.
  2005-04-28 Darko Kolakovic
*/
// Group=Diagnostic

#ifdef __cplusplus

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

///////////////////////////////////////////////////////////////////////////////
// Debug version
#ifdef _DEBUG

  void DumpXmlNode(CDumpContext& dc, const CXmlNode& xmlNode);
  void DumpXmlAttr(CDumpContext& dc, const CXmlAttribute& xmlAttr);

///////////////////////////////////////////////////////////////////////////////
// Release version
#else

  #define DumpXmlNode(dc,object)          ((void)0,(void)0)
  #define DumpXmlAttr(dc,object)          ((void)0,(void)0)

#endif
///////////////////////////////////////////////////////////////////////////////
#endif //__cplusplus
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-04-28 18:10:40  Darko Kolakovic
 * $
 *****************************************************************************/

