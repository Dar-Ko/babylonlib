/*$Workfile: KDbgFVSI.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:20 $
  $Author: ddarko $
  
  Dumps the current device-context attributes
  Paul DiLascia, MSJ 6/96
  Jul. 97 cosmetic changes D.K.

// Group=Diagnostic

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */
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
/*Dumps the contents of FVSHOWINFO structure that the quick file viewer uses to
  display a file.

  Note: uses Microsoft Fundation Library (MFC),
        Microsoft Windows specific (Win).
*/
void DumpFVSHOWINFO(LPFVSHOWINFO lpfvSI)
{
static LPCSTR ShowCommands[] = {"SW_HIDE",
                                "SW_SHOWNORMAL",
                                "SW_SHOWMINIMIZED",
                                "SW_SHOWMAXIMIZED",
                                "SW_MAXIMIZE",
                                "SW_SHOWNOACTIVATE",
                                "SW_SHOW",
                                "SW_MINIMIZE",
                                "SW_SHOWMINNOACTIVE",
                                "SW_SHOWNA",
                                "SW_RESTORE"
                                };

CString strFlags;
DWORD dwFlags = lpfvSI->dwFlags;
if (dwFlags & FVSIF_RECT)
	strFlags += "FVSIF_RECT ";
if (dwFlags & FVSIF_PINNED)
	strFlags += "FVSIF_PINNED ";
if (dwFlags & FVSIF_NEWFAILED)
	strFlags += "FVSIF_NEWFAILED ";
if (dwFlags & FVSIF_NEWFILE)
	strFlags += "FVSIF_NEWFILE ";
if (dwFlags & FVSIF_CANVIEWIT)
	strFlags += "FVSIF_CANVIEWIT ";

  //TRACE diagnostics for args
TRACE1("FVSHOWINFO @$%X\n\t{\n",lpfvSI);
TRACE("\thwndOwner  = 0x%08lx\n", lpfvSI->hwndOwner);
TRACE("\tiShow      = %s\n", ShowCommands[lpfvSI->iShow]);
TRACE("\tdwFlags    = %s\n", (LPCSTR)strFlags);
TRACE("\trect       = (%d,%d,%d,%d)\n", lpfvSI->rect.left,  lpfvSI->rect.top,
                                       lpfvSI->rect.right, lpfvSI->rect.bottom);
TRACE("\tpunkrel    = %p\n", lpfvSI->punkRel);
TRACE("\tstrNewFile = %s\n\t}\n", (LPCSTR)(CString(lpfvSI->strNewFile)));
}

#endif //_AFX_NO_OLE_SUPPORT

///////////////////////////////////////////////////////////////////////////////
#endif  //_DEBUG
/*****************************************************************************
 * $Log: 
 *  7    Biblioteka1.6         8/27/02 11:37:13 PM  Darko           
 *  6    Biblioteka1.5         1/29/02 11:20:17 PM  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         1/29/02 3:38:41 PM   Darko           Tag update
 *  4    Biblioteka1.3         8/19/01 11:52:39 PM  Darko           Butyfier
 *  3    Biblioteka1.2         7/11/01 10:50:35 PM  Darko           
 *  2    Biblioteka1.1         6/8/01 11:49:58 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 3:55:53 PM   Darko           
 * $
 * Jul. 97 cosmetic changes D.K.
 * Paul DiLascia, MSJ 6/96
 *****************************************************************************/
