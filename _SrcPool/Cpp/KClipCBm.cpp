/*$Workfile: KClipCBm.cpp$: implementation file
  $Revision: 1.3 $ $Date: 2003/01/28 04:15:24 $
  $Author: ddarko $

  Copy a bitamp to Clipboard
  Copyright: CommonSoft Inc
  Nov. 96 D.Kolakovic
*/
/* Group=Images                                                             */
/*Note: MS VC/C++ - Disable precompiled headers (/Yu"StdAfx.h" option)       */

#include <AfxWin.h>

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

extern   void SystemErrMessage(UINT uiSystemError);

//ClipCopyBmp()---------------------------------------------------------------
/*Called on 'Copy to Clipboard' command. Copies given rectangle as a bitamp to 
  the clipboard in standard CF_BITMAP format.
  
  Note: uses Microsoft Fundation Library (MFC).
        Microsoft Windows specific (Win). 
 */
void ClipCopyBmp(CWnd* pOwner, //window clipboard belongs to, 
                               //and where our image is stored
                 LPRECT lpRect //source rectangle in logical units
                 ) 
{
CSize sizeBmp(abs(lpRect->right-lpRect->left),abs(lpRect->bottom-lpRect->top));
if (sizeBmp.cx == 0 || sizeBmp.cy == 0)
  return;

CDC* pDC = pOwner->GetDC();
CDC MemDC;
if (MemDC.CreateCompatibleDC(pDC))
  {
  CBitmap bmpTraget;
  if(bmpTraget.CreateCompatibleBitmap (pDC,sizeBmp.cx,sizeBmp.cy))
    {
    CBitmap* pOldBmp = MemDC.SelectObject(&bmpTraget);
    if (MemDC.StretchBlt (0, 0, sizeBmp.cx,sizeBmp.cy,
                         pDC,
                         0,0, sizeBmp.cx,sizeBmp.cy, SRCCOPY))
      {
      if(pOwner->OpenClipboard())
        {
        ::EmptyClipboard();
        if(::SetClipboardData (CF_BITMAP, bmpTraget.GetSafeHandle()) == NULL)
          ::SystemErrMessage(GetLastError());
        ::CloseClipboard();
        }
      else
        AfxMessageBox(_T("Clipboard is busy.\noperation aborted!"));
      }
    /*Select the old bitmap back into the memory DC so that target bitmap is 
      not deleted when MemDC is destroyed. Then we detach the bitmap handle 
      from the target bitmap so that the bitmap is not deleted when cBmp is 
      destroyed. See article Q112530.
     */
    MemDC.SelectObject(pOldBmp);
    bmpTraget.Detach();
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
/*
          //Get DDB size in bytes
        BITMAP bmp; //The height, width, color format, and bit values of a logical bitmap. 
        GetObject((HBITMAP)bmpTraget, sizeof(bmp), &bmp);  
        HGLOBAL hMem;  //data handle 
        sizeBmp.cx =bmp.bmHeight * bmp.bmWidthBytes * bmp.bmPlanes;  //DDB size in bytes
        //    if (cbBmp % 4 != 0)        // dword align TODO: check this D.K.
        //      cbBmp += 4 - (cbBmp % 4);  
          //Allocate memory and copy the DDB into it. 
        hMem = GlobalAlloc(GHND, sizeBmp.cx); 
                if (hMem != NULL)
          {
          LPBYTE lpbDst=(LPBYTE)GlobalLock(hMem);
          if (lpbDst != NULL)
            {
              //Copy the bit pattern of the CBitmap object into the buffer
            if((sizeBmp.cy = ::GetBitmapBits((HBITMAP)bmpTraget,sizeBmp.cx, (LPVOID)lpbDst)) != 0)
              {
              ::GlobalUnlock(hMem); 

            }
          else
            ::GlobalFree(hMem);
           }
*/
