/*$Workfile: KDbgFVSI.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 05:35:50 $
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
 *  7    Biblioteka1.6         27/08/2002 10:37:13 PMDarko           
 *  6    Biblioteka1.5         29/01/2002 10:20:17 PMDarko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         29/01/2002 2:38:41 PMDarko           Tag update
 *  4    Biblioteka1.3         19/08/2001 10:52:39 PMDarko           Butyfier
 *  3    Biblioteka1.2         11/07/2001 9:50:35 PMDarko           
 *  2    Biblioteka1.1         08/06/2001 10:49:58 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 2:55:53 PMDarko           
 * $
 * Jul. 97 cosmetic changes D.K.
 * Paul DiLascia, MSJ 6/96
 *****************************************************************************/
