/*$Workfile: KLogoOut.cpp$: implementation file
  $Revision: 6$ $Date: 2002-01-29 23:21:26$
  $Author: Darko$

  Display a logo in the window client area
  Copyright: CommonSoft Inc.
  Jun. '95 D.Kolakovic
 */ 


#ifndef __AFXWIN_H__
  #include <AfxWin.h> // MFC core and standard components
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//DisplayBackgroundLogo()------------------------------------------------------
#include "UTextMtr.h" //CTextMetric class
#include "D_GFont.h"  //font name
/*Call this function as part of the WM_ERASEBKGND message handling to display
  a logo in the right bottom corner of the frame client area.
  Returns allways TRUE to signal tha no further background painting is required.

   Pseudocode:
      {
      Paints the background the Windows desktop color
      (as default OnEraseBkgnd would do);
      Create a font;
      Calculate the logo display size;
      Substract staus bar height from client area size, if any;
      Draw shadows;
      Display the logo;
      Release resources;
      }

  Note: To  print a logo and change the background color for a CMDIFrameWnd you
  must subclass the multiple document interface (MDI) client window (window in
  the client area of CMDIFrameWnd) and process the WM_ERASEBKGND message.

  See also: KB Q129471 article.

  Note: uses Microsoft Fundation Library (MFC).
  
  Example:
    class CMyFrame: public CFrameWnd
      {
      ...
      };
    BOOL CMyFrame::OnEraseBkgnd(CDC* pDC)
      {
      extern BOOL DisplayBackgroundLogo(CDC* pDC, CString strLogo);
      if (!DisplayBackgroundLogo(pDC,CString(AfxGetAppName())) )
        return CFrameWnd::OnEraseBkgnd(pDC);
      return TRUE;
      }
 */
BOOL DisplayBackgroundLogo(CDC* pDC,     //[in] pointer to device-context object
                           CString strLogo //[in] text to be displayed
                           )
{
ASSERT(pDC != NULL);
CWnd* pWnd = pDC->GetWindow();
ASSERT(::IsWindow(pWnd->m_hWnd));
  //Erase client area
CRect rtTextBox;
pWnd->GetClientRect(&rtTextBox);  //Get client area size

CBrush* pNewBrush = pDC->GetCurrentBrush();
if (pNewBrush == NULL)
  {
  COLORREF rgbBkColor = GetSysColor(COLOR_DESKTOP) ;
  CBrush NewBrush(rgbBkColor) ;
  CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&NewBrush);
  pDC->SetBrushOrg(0,0) ;
  pDC->PatBlt(rtTextBox.left,    rtTextBox.top,
              rtTextBox.Width(), rtTextBox.Height(),PATCOPY);
  pDC->SelectObject(pOldBrush);
  }
else
  {
  pDC->SetBrushOrg(0,0);
  pDC->PatBlt(rtTextBox.left,    rtTextBox.top,
              rtTextBox.Width(), rtTextBox.Height(),PATCOPY);
  }

CFont fontLogo;
  //Creates a font, regardless of screen resolution
const int FONT_SIZE = 24; //[pt]
#define FONT_NAME g_szfontTNewRoman //TrueType font name

int fontSize = -MulDiv(FONT_SIZE, pDC->GetDeviceCaps(LOGPIXELSY), 72);
fontLogo.CreateFont(fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
FIXED_PITCH | FF_ROMAN, FONT_NAME);

pDC->SetBkMode(OPAQUE);
CFont* oldFont = pDC->SelectObject(&fontLogo);

CRect st(0,0,0,0);
CSize sz = pDC->GetTextExtent(strLogo);
  //Calculate the logo display size
CTextMetric tm(pDC);
  //Calculate the box size by subtracting the text width and height from the
  //window size.  Also subtract 20% of the average character size to keep the
  //logo from printing into the borders...
rtTextBox.left = rtTextBox.right  - sz.cx - tm.tmAveCharWidth/2;
rtTextBox.top  = rtTextBox.bottom - sz.cy - st.bottom - tm.tmHeight/5;
  //Get status bar size
CRect saveRect1;
CWnd* pStatusbar = pWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR, TRUE);
if ((pStatusbar != NULL) && pStatusbar->IsWindowVisible())
  {
  pStatusbar->GetWindowRect(&saveRect1);
    //Subtract the status bar height
  rtTextBox.top -= saveRect1.Height();
  }

saveRect1 = rtTextBox;

pDC->SetBkMode(TRANSPARENT);
saveRect1 = rtTextBox;

  //Shift logo box right, and print dark shadow
const int iOffset = tm.tmAveCharWidth/5;
rtTextBox.left += iOffset;
rtTextBox.top  += iOffset;
COLORREF oldColor = pDC->SetTextColor(GetSysColor(COLOR_3DDKSHADOW));
pDC->DrawText(strLogo, &rtTextBox,
              DT_VCENTER | DT_SINGLELINE | DT_CENTER);

  //Shift logo box left and print light shadow
rtTextBox = saveRect1;
rtTextBox.left -= iOffset;
rtTextBox.top  -= iOffset;
pDC->SetTextColor(GetSysColor(COLOR_3DHILIGHT));
pDC->DrawText(strLogo, &rtTextBox,
              DT_VCENTER | DT_SINGLELINE | DT_CENTER);

  //Print in the button face color
rtTextBox = saveRect1;
pDC->SetTextColor(GetSysColor(COLOR_BTNFACE));
pDC->DrawText(strLogo, &rtTextBox, DT_VCENTER | DT_SINGLELINE | DT_CENTER);

  //Testore the DC state and release resources
pDC->SelectObject(oldFont);
pDC->SetTextColor(oldColor);
pDC->SetBkMode(OPAQUE);
fontLogo.DeleteObject();

pWnd->ReleaseDC(pDC);

return TRUE;
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2002-01-29 23:21:26  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         2002-01-29 15:40:41  Darko           Tag update
 *  4    Biblioteka1.3         2001-08-19 23:54:05  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 22:51:50  Darko           
 *  2    Biblioteka1.1         2001-06-08 23:51:01  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:56:45  Darko           
 * $
 *****************************************************************************/
