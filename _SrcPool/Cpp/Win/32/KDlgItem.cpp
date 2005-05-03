/*$Workfile: KDlgItem.cpp$: implementation file
  $Revision: 5$ $Date: 2004-10-01 22:34:40$
  $Author: Darko$

  Resizable dialog control
  Copyright: CommonSoft Inc.
  Mar 2k Darko Kolakovic
 */ 

#include "stdafx.h"
#include "KDlgItem.h" //CDlgItemResizable class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgItemResizable

//::CDlgItemResizable()-----------------------------------------------------------------
/*
 */
CDlgItemResizable::CDlgItemResizable() :
  m_dwStyle(ALL_FIXED), x(0), y(0), cx(0), cy(0), m_hWnd(NULL), m_nControlID((UINT)-1)
{
}

CDlgItemResizable::~CDlgItemResizable()
{
}

//::Resize()-------------------------------------------------------------------
/*Change position and size of the control described with this object.
 */
 CRect CDlgItemResizable::Resize(const CSize& sizeParentNew, //container's new client area size
                                 const CSize& sizeParentOriginal //container's original client area size
                                )
{
CRect rtCtrl(x,y,x+cx,y+cy);

if (m_dwStyle == ALL_FIXED)
  return rtCtrl; //Nothing to do

int iDifference;

  //Resize horizontally
iDifference = sizeParentNew.cx - sizeParentOriginal.cx;

if (IsStyle(SIZE_PROPORTIONAL)) //Lock aspect ratio
  {
  iDifference = min(iDifference,
                    sizeParentNew.cy - sizeParentOriginal.cy);
  }

  //Don't resize controls if new parent size is less than original
if (iDifference > 0)
  {
  if(IsStyle(PROPORTIONAL_HOR))
    {
      //Calculate relative width increase per cent
    iDifference = (100*sizeParentNew.cx)/sizeParentOriginal.cx;
    rtCtrl.left *= iDifference;
    rtCtrl.left  /= 100;
    rtCtrl.right = (cx * iDifference)/100 + rtCtrl.left;
    }
  else
    {
    if(IsStyle(POS_FLOATHOR))
      {
      rtCtrl.left  +=iDifference;
      rtCtrl.right +=iDifference;
      }
    if(IsStyle(SIZE_EXPANDHOR)) //Expand right side
      {
        //Left edge is docked
      rtCtrl.right +=iDifference;
      }
    }
  }

  //Resize vertically
if (!IsStyle(SIZE_PROPORTIONAL))  //Unlock aspect ratio
  iDifference = sizeParentNew.cy - sizeParentOriginal.cy;

  //Don't resize controls if new parent size is less than original
if (iDifference > 0)
  {
  if(IsStyle(PROPORTIONAL_VER))
    {
      //Calculate relative height increase per cent
    iDifference = (100*sizeParentNew.cy)/sizeParentOriginal.cy;
    rtCtrl.top *= iDifference;
    rtCtrl.top  /= 100;
    rtCtrl.bottom = (cy * iDifference)/100 + rtCtrl.top;
    }
  else
    {
    if(IsStyle(POS_FLOATVER))
      {
      rtCtrl.top    += iDifference;
      rtCtrl.bottom += iDifference;
      }
    if(IsStyle(SIZE_EXPANDVER)) //Expand down
      { 
      //Top edge is docked
      rtCtrl.bottom += iDifference;
      }
    }
  }

#ifdef _DEBUG
  if (afxDump.GetDepth() >=3)
    {
    afxDump << "Resize Control =============================\n"
            << *this
            << "New size: " << rtCtrl.TopLeft() << rtCtrl.Size() 
            << "\n--------------------------------------------\n";
    }
#endif

VERIFY(::MoveWindow(m_hWnd,
                    rtCtrl.left,rtCtrl.top,rtCtrl.Width(),rtCtrl.Height(),
                    FALSE));
::InvalidateRect(m_hWnd, NULL, TRUE);
  //Invalidate control's child windows
HWND hChild = ::GetTopWindow(m_hWnd);
while (hChild != NULL)
  {
  ::InvalidateRect(hChild, NULL, TRUE);
  hChild = ::GetTopWindow(hChild);
  }
 
return rtCtrl;
}

