/*$Workfile: KClipCTx.cpp$: implementation file
  $Revision: 1.4 $ $Date: 2003/01/28 05:29:46 $
  $Author: ddarko $

  Copy text to Clipboard
  Copyright: CommonSoft Inc.
  Nov. 96 D.Kolakovic
*/

/* Group=Strings                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <AfxWin.h>

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//ClipCopyText()---------------------------------------------------------------
/*Called on 'Copy to Clipboard' command. Copies given string to the clipboard
  in standard CF_TEXT format. Throws CMemoryException.

  Note: uses Microsoft Fundation Library (MFC).
        Microsoft Windows specific (Win). 
 */
void ClipCopyText(CWnd* pOwner,          //owner of the Clipborad. If NULL,
                                         //current task becomes owner.
                  const CString& strText //string to be copied
                  )
{
HGLOBAL hMem; 	//data handle
LPSTR lpszText;

        //Allocate memory and copy the text to it
hMem = GlobalAlloc(GMEM_MOVEABLE,strText.GetLength()+1);

if (hMem == NULL  ||
   (lpszText = (LPSTR)GlobalLock(hMem)) == NULL )
  {
  AfxThrowMemoryException();
  return;
  }

lstrcpy(lpszText,(LPCTSTR)strText);  //Copy text to global memory
GlobalUnlock(hMem);

   //Send the data to the clipboard
if (pOwner != NULL)
  pOwner->OpenClipboard();
else
  ::OpenClipboard(NULL); //Clipboard is associated with the current task.

EmptyClipboard();
#ifndef _UNICODE
  if(::SetClipboardData(CF_TEXT, hMem) == NULL)
#else
  if(::SetClipboardData(CF_UNICODETEXT, hMem) == NULL)
#endif
    {
    TRACE0(_T("Failed to set clipboard data"));
    }

CloseClipboard();
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         19/08/2001 11:52:24 PMDarko           Butyfier
 *  3    Biblioteka1.2         11/07/2001 10:50:15 PMDarko
 *  2    Biblioteka1.1         08/06/2001 11:49:12 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:55:35 PMDarko
 * $
 *****************************************************************************/
