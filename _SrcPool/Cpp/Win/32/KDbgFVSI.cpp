/*$Workfile: KDbgFVSI.cpp$: implementation file
  $Revision: 10$ $Date: 2004-10-01 21:34:14$
  $Author: Darko$
  
  Dumps the current device-context attributes
  Paul DiLascia, MSJ 6/96
  Jul. 97 cosmetic changes D.K.

// Group=Diagnostic

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */
#include <AfxWin.h>

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

#include <ShlObj.h>   //FVSHOWINFO struct
#include "KDbgDump.h" //Declarations

///////////////////////////////////////////////////////////////////////////////

//DumpFVSHOWINFO()------------------------------------------------------------
#ifndef _AFX_NO_OLE_SUPPORT
/*Dumps the contents of FVSHOWINFO structure that the file viewer uses to
  display a file.

      typedef struct 
        {
        DWORD cbSize;
        HWND hwndOwner;
        int iShow;
        DWORD dwFlags;
        RECT rect;
        IUnknown *punkRel;
        OLECHAR strNewFile[MAX_PATH];
        } FVSHOWINFO, *LPFVSHOWINFO;

  See also: shlobj.h

  Note: uses Microsoft Fundation Library (MFC),
        Microsoft Windows specific (Win).
*/
void DumpFVSHOWINFO(LPFVSHOWINFO lpfvSI //[in] pointer to file viewer FVSHOWINFO
                                        //structure
                    )
{
static LPCTSTR ShowCommands[] = {_T("SW_HIDE"),
                                _T("SW_SHOWNORMAL"),
                                _T("SW_SHOWMINIMIZED"),
                                _T("SW_SHOWMAXIMIZED"),
                                _T("SW_MAXIMIZE"),
                                _T("SW_SHOWNOACTIVATE"),
                                _T("SW_SHOW"),
                                _T("SW_MINIMIZE"),
                                _T("SW_SHOWMINNOACTIVE"),
                                _T("SW_SHOWNA"),
                                _T("SW_RESTORE")
                                };

CString strFlags;
DWORD dwFlags = lpfvSI->dwFlags;
if (dwFlags & FVSIF_RECT)
  strFlags += _T("FVSIF_RECT ");
if (dwFlags & FVSIF_PINNED)
  strFlags += _T("FVSIF_PINNED ");
if (dwFlags & FVSIF_NEWFAILED)
  strFlags += _T("FVSIF_NEWFAILED ");
if (dwFlags & FVSIF_NEWFILE)
  strFlags += _T("FVSIF_NEWFILE ");
if (dwFlags & FVSIF_CANVIEWIT)
  strFlags += _T("FVSIF_CANVIEWIT ");

  //TRACE diagnostics for args
TRACE(_T("FVSHOWINFO @$%X\n\t{\n"),lpfvSI);
TRACE(_T("\thwndOwner  = 0x%08lx\n"), lpfvSI->hwndOwner);
TRACE(_T("\tiShow      = %s\n"), ShowCommands[lpfvSI->iShow]);
TRACE(_T("\tdwFlags    = %s\n"), (LPCTSTR)strFlags);
TRACE(_T("\trect       = (%d,%d,%d,%d)\n"), lpfvSI->rect.left,  lpfvSI->rect.top,
                                       lpfvSI->rect.right, lpfvSI->rect.bottom);
TRACE(_T("\tpunkrel    = %p\n"), lpfvSI->punkRel);
TRACE(_T("\tstrNewFile = %s\n\t}\n"), (LPCTSTR)(CString(lpfvSI->strNewFile)));
}

#endif //_AFX_NO_OLE_SUPPORT

///////////////////////////////////////////////////////////////////////////////
#endif  //_DEBUG
/*****************************************************************************
 * $Log: 
 *  10   Biblioteka1.9         2004-10-01 21:34:14  Darko           stdafx.h
 *  9    Biblioteka1.8         2003-08-17 01:12:34  Darko           replaced LPCSTR
 *       with LPTCTSTR
 *  8    Biblioteka1.7         2003-08-13 09:51:27  Darko           Unicode
 *  7    Biblioteka1.6         2002-08-27 22:37:13  Darko           
 *  6    Biblioteka1.5         2002-01-29 22:20:17  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         2002-01-29 14:38:41  Darko           Tag update
 *  4    Biblioteka1.3         2001-08-19 22:52:39  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 21:50:35  Darko           
 *  2    Biblioteka1.1         2001-06-08 22:49:58  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 14:55:53  Darko           
 * $
 * Jul. 97 cosmetic changes D.K.
 * Paul DiLascia, MSJ 6/96
 *****************************************************************************/
