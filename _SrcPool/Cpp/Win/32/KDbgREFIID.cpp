/*$Workfile: KDbgREFIID.cpp$: implementation file
  $Revision: 4$ $Date: 2005-04-26 11:29:22$
  $Author: Darko Kolakovic$

  Dumps OLE interface name
  Copyright: CommonSoft Inc.
  D. Kolakovic May 98
 */

// Group=Diagnostic

#ifdef _DEBUG
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#include <AfxWin.h>
#include "KDbgDump.h" //Declarations

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#ifndef _AFX_NO_OLE_SUPPORT
  //DumpREFIID()---------------------------------------------------------------
  /*Dump OLE interface name.

    Note: uses Microsoft Foundation Library (MFC),
          Microsoft Windows specific (Win).
   */
  void DumpREFIID(CDumpContext& dc,  //[in] dump context
                  REFIID iid         //[in] reference to the identifier of the 
                             //interface to be used to communicate 
                             //with the new object
                 )
  {
  CString strGUID;
  strGUID.Format(_T("{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}"),
      iid.Data1, iid.Data2, iid.Data3,
      iid.Data4[0], iid.Data4[1], iid.Data4[2], iid.Data4[3],
      iid.Data4[4], iid.Data4[5], iid.Data4[6], iid.Data4[7]);
  dc << _T("GUID: ") << strGUID << _T("\n");
  }
#endif //_AFX_NO_OLE_SUPPORT

///////////////////////////////////////////////////////////////////////////////
#endif //_DEBUG
