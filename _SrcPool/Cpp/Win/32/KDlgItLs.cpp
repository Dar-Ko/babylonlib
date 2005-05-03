/*$Workfile: KDlgItLs.cpp$: implementation file
  $Revision: 5$ $Date: 2004-10-01 22:34:38$
  $Author: Darko$

  A list with resizable controls
  Copyright: CommonSoft Inc.
  Apr. 2k Darko Kolakovic
 */

#include "stdafx.h"
#include "KDlgItLs.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgItemResizableList


//::CDlgItemResizableList()-------------------------------------------------------------
/*
 */
CDlgItemResizableList::CDlgItemResizableList() :
  m_hParent(NULL)
{
}

CDlgItemResizableList::CDlgItemResizableList(const CWnd* pParent //pointer to the container window
                           ) 
{
ASSERT(pParent == NULL);
m_hParent = pParent->GetSafeHwnd();
ASSERT(m_hParent != NULL); //pParent is not attached to a window
}

CDlgItemResizableList::CDlgItemResizableList(HWND hParent //handle of the container window
                           ) :
  m_hParent(hParent)
{
ASSERT(::IsWindow(hParent));
}


CDlgItemResizableList::~CDlgItemResizableList()
{
}

///////////////////////////////////////////////////////////////////////////////
// Operations


//::Add()----------------------------------------------------------------------
/*Adds an element to the end of the item list; grows the list if necessary.
  Returns the index of the added element or -1 in case of failure.
  Throws CMemoryException.
 */
int CDlgItemResizableList::Add(const CDlgItemResizable& cdlgiResizable)
{
ASSERT(::IsWindow(m_hParent));
#ifdef _DEBUG
  if (!::IsWindow(cdlgiResizable.m_hWnd) || (cdlgiResizable.m_nControlID == (UINT)-1))
    {
      //Warning: Uninitialized item
    afxDump << _T("CDlgItemResizableList::Add(\n")
            << cdlgiResizable
            << _T("\t)\n");
    }
#endif
return m_arrayDlgItem.Add(cdlgiResizable); 
}

int CDlgItemResizableList::Add(const UINT& nCtrlID, //ID of the control
                               const DWORD& dwStyle //=BOTH_FIXED one or more style flags
                               )
{
ASSERT(nCtrlID != 0);
ASSERT(m_hParent != NULL);
CDlgItemResizable dlgrItem;
dlgrItem.m_dwStyle = dwStyle;
dlgrItem.m_hWnd = ::GetDlgItem(m_hParent,nCtrlID);
if (dlgrItem.m_hWnd != NULL)
  {
  dlgrItem.m_nControlID = nCtrlID;
  if(dlgrItem.SetDimensions(m_hParent))
    {
    #ifdef _DEBUG
      if(afxDump.GetDepth() >= 2)
        afxDump << _T("CDlgItemResizableList::Add(ID = ")
                << nCtrlID << _T(")\n\t") << dlgrItem;
    #endif
    return m_arrayDlgItem.Add(dlgrItem);
    }
  }

 //Failure: a nonexistent control. To get extended error information, call GetLastError
#ifdef _DEBUG
  TRACE1("CDlgItemResizableList::Add(ID = %d) failed.\n", (INT)nCtrlID);
  if(nCtrlID == IDC_STATIC)  
    _RPTF0(_CRT_ERROR, "IDC_STATIC could not be used as resizable control.\nChange control's ID.\n");
   else
    _RPTF0(_CRT_ERROR, "Failure: a nonexistent control.\n");
#endif

return -1;

}

int CDlgItemResizableList::Add(const HWND& hwndCtrl, //handle to control
                               const DWORD& dwStyle  //=BOTH_FIXED one or more style flags
                               )
{
ASSERT(m_hParent != NULL);
if(::IsWindow(hwndCtrl))
  {
  CDlgItemResizable dlgrItem;
  dlgrItem.m_hWnd = hwndCtrl;
  dlgrItem.m_dwStyle = dwStyle;
    //Get ID of any child window
  dlgrItem.m_nControlID = ::GetDlgCtrlID(hwndCtrl);
  if (dlgrItem.m_nControlID != 0)
    {
    if(dlgrItem.SetDimensions(m_hParent))
      {
      #ifdef _DEBUG
        afxDump << dlgrItem;
      #endif
      return m_arrayDlgItem.Add(dlgrItem);
      }
    }
  }

 //Failure: a nonexistent control. To get extended error information, call GetLastError
return -1;
}

//::EnumerateControls()--------------------------------------------------------
/*Enumerate and store dialog controls.
  Returns the index of the last added item or -1 in case of failure.
  Throws CMemoryException.
 */
int CDlgItemResizableList::EnumerateControls()
{
ASSERT(::IsWindow(m_hParent));

HWND hwndCtrl = ::GetWindow(m_hParent,GW_CHILD);
while (hwndCtrl != NULL)
  {
  ASSERT(::IsWindow(hwndCtrl));
  Add(hwndCtrl);
  hwndCtrl = ::GetNextWindow(hwndCtrl, GW_HWNDNEXT);
  }
return m_arrayDlgItem.GetUpperBound();
}

//::OnSize()-------------------------------------------------------------------
/*Call this member function after the size of the parent window has been changed. 

  Parameter nType can be one of the following values: 

      SIZE_MAXIMIZED   parent's window has been maximized.
      SIZE_MINIMIZED   parent's window has been minimized.
      SIZE_RESTORED    parent's window has been resized, but neither SIZE_MINIMIZED
                       nor SIZE_MAXIMIZED applies.
      SIZE_MAXHIDE     Message is sent to all pop-up windows when some other window 
                       is maximized.
      SIZE_MAXSHOW     Message is sent to all pop-up windows when some other window 
                       has been restored to its former size. 
 */
void CDlgItemResizableList::OnSize(UINT nType, //parent's resizing type
                                   int cx, //the new width of parent's client area
                                   int cy  //the new height of parent's  client area
                                   )
{
if (nType != SIZE_MINIMIZED)
  {
    //Resize controls
  Resize(CSize(cx,cy));
  }
}
