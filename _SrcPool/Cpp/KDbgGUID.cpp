/*$Workfile: KDbgGUID.cpp$: implementation file
  $Revision: 1$ $Date: 27/08/2002 10:33:58 PM$
  $Author: Darko$

  Dumps GUID
  Copyright: CommonSoft Inc.
  D. Kolakovic May 98
 */

// Group=Diagnostic

#ifdef _DEBUG
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <AfxWin.h>
#include "KDbgDump.h" //Declarations

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#ifndef _AFX_NO_OLE_SUPPORT
  //DumpGUID()-----------------------------------------------------------------
  /*Dump global unique ID.

    Note: uses Microsoft Fundation Library (MFC),
          Microsoft Windows specific (Win).
   */
  void DumpGUID(CDumpContext& dc, //[in]
                const GUID GuID   //[in]
                )
  {
  OLECHAR szGuid[40];
  ::StringFromGUID2(GuID, szGuid, 40);

  size_t Len = (wcslen(szGuid)+1)*2;
  //NOTE: alloca() allocates size bytes from the program stack. The allocated 
  //space is automatically freed when the calling function exits.
  LPSTR lpa = (LPSTR) alloca(Len);
  if (lpa != NULL)
    {
 	  lpa[0] = '\0';
	  VERIFY(WideCharToMultiByte(CP_ACP, 0, szGuid, -1, lpa, Len, NULL, NULL));
    }
  dc << lpa;
  }
#endif //_AFX_NO_OLE_SUPPORT

///////////////////////////////////////////////////////////////////////////////
#endif //_DEBUG
