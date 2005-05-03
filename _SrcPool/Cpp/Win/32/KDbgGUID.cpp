/*$Workfile: KDbgGUID.cpp$: implementation file
  $Revision: 5$ $Date: 2005-04-26 11:29:10$
  $Author: Darko Kolakovic$

  Dumps GUID
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
  //DumpGUID()-----------------------------------------------------------------
  /*Dump Globally Unique Identifier value. A globally unique identifier is
   associated with a group of menu items.

   Example:
     5EFC7975-14BC-11CF-9B2B-00AA00573819

    Note: uses Microsoft Foundation Library (MFC),
          Microsoft Windows specific (Win).
   */
  void DumpGUID(CDumpContext& dc, //[in] diagnostic output stream
                const GUID GuID   //[in] GUID value
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
    VERIFY(WideCharToMultiByte(CP_ACP, 0, szGuid, -1, lpa, (int)Len, NULL, NULL));
    }
  dc << lpa;
  }
#endif //_AFX_NO_OLE_SUPPORT

///////////////////////////////////////////////////////////////////////////////
#endif //_DEBUG
