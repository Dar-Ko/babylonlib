/*$Workfile: KDockBar.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $

  Control bar helper functions
  Copyright: CommonSoft Inc.
  D.Kolakovic Dec. 95
  */

#include "StdAfx.h"

//DockControlBarLeftOf()-------------------------------------------------------
/*Dock tool bar pointed with Bar left of tool bar pointed with nPosition value.

  Note: uses Microsoft Fundation Library (MFC).
 */
void DockControlBarLeftOf(CFrameWnd& Frame, //[in] toolbar owner frame
                          CToolBar* Bar,    //[in] toolbar to be docked
                          CToolBar* LeftOf  //[in] toolbar left of the new toolbar
                          )
{
CRect rect;
DWORD dw;
UINT n;

// get MFC to adjust the dimensions of all docked ToolBars
// so that GetWindowRect will be accurate
Frame.RecalcLayout();
LeftOf->GetWindowRect(&rect);
rect.OffsetRect(1,0);
dw=LeftOf->GetBarStyle();
n = 0;
n = (dw&CBRS_ALIGN_TOP) ? AFX_IDW_DOCKBAR_TOP : n;
n = (dw&CBRS_ALIGN_BOTTOM && n==0) ? AFX_IDW_DOCKBAR_BOTTOM : n;
n = (dw&CBRS_ALIGN_LEFT && n==0) ? AFX_IDW_DOCKBAR_LEFT : n;
n = (dw&CBRS_ALIGN_RIGHT && n==0) ? AFX_IDW_DOCKBAR_RIGHT : n;

// When we take the default parameters on rect, DockControlBar will dock
// each Toolbar on a seperate line.  By calculating a rectangle, we in effect
// are simulating a Toolbar being dragged to that location and docked.
Frame.DockControlBar(Bar,n,&rect);
}

//DockControlTopRight()--------------------------------------------------------
/*Dock tool bar pointed with Bar at frame's top right corner.

  Note: uses Microsoft Fundation Library (MFC).

  Example:

      //Registry entry for toolbar status
    #define REG_ITEM_TREETOOLBAR _T("MyToolBarState")
    CMyToolbar::Dock()
      {
      CFrameWnd* pParentFrame = GetDockingFrame();
      pParentFrame->EnableDocking(CBRS_ALIGN_ANY);
      DockControlBarTopRight(*pParentFrame,this);
      pParentFrame->LoadBarState(REG_ITEM_TREETOOLBAR);
      }
 */
void DockControlBarTopRight(CFrameWnd& Frame, //[in] toolbar owner frame
                            CToolBar * pBar   //[in] toolbar to be docked
                           )
{
	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
Frame.RecalcLayout();

CRect rect;                    //Tool bar position
Frame.GetWindowRect(&rect);

rect.top += 34;                  //Why offseting is 34 and 32 we don't know yet.
rect.SetRect(rect.right - 32,rect.top,rect.right,rect.top+32);
	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line.  By calculating a rectangle, we in effect
	// are simulating a Toolbar being dragged to that location and docked.
ASSERT(pBar != NULL);
Frame.DockControlBar(pBar,AFX_IDW_DOCKBAR_TOP | AFX_IDW_DOCKBAR_RIGHT,&rect);
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         1/29/02 11:20:56 PM  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         1/29/02 3:39:46 PM   Darko           Tag update
 *  4    Biblioteka1.3         8/19/01 11:53:44 PM  Darko           Butyfier
 *  3    Biblioteka1.2         7/11/01 10:51:28 PM  Darko           
 *  2    Biblioteka1.1         6/8/01 11:50:42 PM   Darko           VSS
 *  1    Biblioteka1.0         8/17/00 2:41:26 AM   Darko           
 * $
 *****************************************************************************/
