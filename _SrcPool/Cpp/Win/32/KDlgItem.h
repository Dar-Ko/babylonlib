/*$Workfile: KDlgItem.h$: header file
  $Revision: 8$ $Date: 2003-09-22 21:26:01$
  $Author: Darko$

  Description of a resizable dialog control
  Copyright: CommonSoft Inc.
  Mar. 2k Darko Kolakovic
 */

#ifndef _KDLGITEM_H_
    //KDlgItem.h sentry
  #define _KDLGITEM_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

class CDlgItemResizableList;
///////////////////////////////////////////////////////////////////////////////
// CDlgItemResizable class contains basic parameters for a dialog control.
// If a control is based on a resource template, position and size are in 
// dialog box units.
//
// See also: diagnostic operator<<()
//
//Note: uses Microsoft Fundation Library (MFC).
//      Microsoft Windows specific (Win).
class CDlgItemResizable
{
// Construction
public:
  CDlgItemResizable();

// Attributes
protected:
  DWORD m_dwStyle; //specifies the resizing style of the control
  short x;     //the upper-left corner position 
               //relative to the upper-left corner of the dialog box's client area.
  short y;     //the upper-left corner position 
               //relative to the upper-left corner of the dialog box's client area.
  short cx;    //the width of the control 
  short cy;    //the height of the control 
  UINT  m_nControlID;   //the control identifier 
public:
  HWND  m_hWnd;         //handle of the control

// Style flags
  enum RESIZING_TYPE
    {
    POS_DOCKBOTH     = 0,   //disable repositioning
    POS_FLOATHOR     = 1,   //translate horizontally {html:<BR><IMG SRC="Res/POS_FLOATHOR.gif" BORDER="0">}
    POS_FLOATVER     = 2,   //translate vertically {html:<BR><IMG SRC="Res/POS_FLOATVER.gif" BORDER="0">}
    POS_FLOATBOTH    = POS_FLOATHOR | POS_FLOATVER, //move in both directions
    SIZE_FIXED       = 0,   //disable resizing
    SIZE_EXPANDHOR   = 0x10000, //stretch out horizontally {html:<BR><IMG SRC="Res/SIZE_EXPANDHOR.gif" BORDER="0">}
    SIZE_EXPANDVER   = 0x20000, //stretch out vertically {html:<BR><IMG SRC="Res/SIZE_EXPANDVER.gif" BORDER="0">}
    SIZE_EXPANDBOTH  = SIZE_EXPANDHOR | SIZE_EXPANDVER, //stretch out both directions
    SIZE_PROPORTIONAL= 0x40000 | SIZE_EXPANDBOTH,    //stretch out both directions preserving aspect ratio
    PROPORTIONAL_HOR = POS_FLOATHOR | SIZE_EXPANDHOR,//stretch out in same proportion 
                                                     //as container window has been 
                                                     //stretched horizontally and 
                                                     //preserve relative position
    PROPORTIONAL_VER = POS_FLOATVER | SIZE_EXPANDVER,//stretch out in same proportion 
                                                     //as container window has been 
                                                     //stretched vertically and 
                                                     //preserve relative position
    ALL_PROPORTIONAL = PROPORTIONAL_HOR|PROPORTIONAL_VER,//resize proportionally to container window
    ALL_FIXED        = POS_DOCKBOTH | SIZE_FIXED   //disable resizing and repositioning
    };

// Operations
public:
   CDlgItemResizable& operator=(const CRect& rtValue);
   DWORD SetStyle(const DWORD& dwFlags);
   DWORD GetStyle() const;
   BOOL  SetDimensions(const HWND& hParent);
   BOOL  IsStyle(const DWORD& dwFlags);

// Implementation

// Overrides
public:
  virtual ~CDlgItemResizable();
  virtual CRect Resize(const CSize& sizeParentNew,const CSize& sizeParentOriginal);

friend CDlgItemResizableList; //list of controls
#ifdef _DEBUG
  friend CDumpContext& AFXAPI operator<<(CDumpContext& dc, const CDlgItemResizable& Data);
#endif
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::operator=()----------------------------------------------------------------
/*Assigns coordinates of the controls corners to position and size members.
 */
inline CDlgItemResizable& CDlgItemResizable::operator=(const CRect& rtValue //control's dimensions
                                                      )
{
x = (short)rtValue.left;
y = (short)rtValue.top;
cx = (short)rtValue.Width();
cy = (short)rtValue.Height();
return (*this);
}

//::GetStyle()-----------------------------------------------------------------
/*Returns the current style for resizable control.
 */
inline DWORD CDlgItemResizable::GetStyle() const
{
return m_dwStyle;
}

//::SetStyle()-----------------------------------------------------------------
/*Sets a new style for resizable control.
 */
inline DWORD CDlgItemResizable::SetStyle(const DWORD& dwFlags //one or more style flags
                                         )
{
m_dwStyle = dwFlags;
return m_dwStyle;
}

//::SetDimensions()------------------------------------------------------------
#include "KMathCst.inl" //SWAP()
#ifndef WS_EX_LAYOUTRTL
    //Fix: Windows extended style WS_EX_LAYOUTRTL will be in WinUser.h someday
  #define WS_EX_LAYOUTRTL 0x00400000L
#endif
BOOL IsOldCombobox(HWND hCtrl);
/*Copies dimensions of the given control to this resizable control. Returns TRUE
  in case of success.
 */
inline BOOL CDlgItemResizable::SetDimensions(const HWND& hParent //container window
                                            )
{
ASSERT(::IsWindow(hParent));
ASSERT(::IsWindow(m_hWnd));

RECT rect;
if(::GetWindowRect(m_hWnd, &rect))
  {
  if(IsOldCombobox(m_hWnd)) //Size of combobox under Win32s/WinNT3.xx
    {
    CRect rtDrop;
    ::SendMessage(m_hWnd, CB_GETDROPPEDCONTROLRECT, 0, (DWORD)(LPRECT)rtDrop);
    rect.bottom = rect.top + rtDrop.Height();
    }

  if(::ScreenToClient(hParent, (LPPOINT)&rect) &&
     ::ScreenToClient(hParent, ((LPPOINT)&rect) +1) )
    {
      //Win2k: WS_EX_LAYOUTRTL style mirrors x-axis.
      //Use this only with SDK, MFC CWnd::ScreenToClient adjust rectangle itself D.K.
    if (WS_EX_LAYOUTRTL & (DWORD)GetWindowLong(m_hWnd, GWL_EXSTYLE))
      SWAP(rect.left, rect.right);
    *this = rect;
    return TRUE;
    }
  }
return FALSE;
}

//::IsStyle()------------------------------------------------------------------
/*Returns TRUE if particular style has been set.
 */
inline BOOL CDlgItemResizable::IsStyle(const DWORD& dwFlags //one or more style flags
                                       )
{
return ((m_dwStyle & dwFlags) == dwFlags);
}

///////////////////////////////////////////////////////////////////////////////
// Diagnostic

//operator<<()-----------------------------------------------------------------
#ifdef _DEBUG
  /*Outputs the CDlgItemResizable object to the dump context. In case of failure throws 
    CFileException;

    Note: uses Microsoft Fundation Library (MFC).
   */
  inline CDumpContext& AFXAPI operator<<(CDumpContext& dc, const CDlgItemResizable& Data)
    {
    dc << _T("CDlgItemResizable @ ") << (PVOID)&Data
       << _T("\n\t{\n\tPosition(")
       << Data.x << _T(",") << Data.y 
       << _T(")\n\tSize(")
       << Data.cx << _T(",") << Data.cy 
       << _T(")\n\tstyle = ") << Data.m_dwStyle
       << _T("\n\tID =")      << Data.m_nControlID
       << _T("\n\tHWND =")    << Data.m_hWnd;

    if (!::IsWindow(Data.m_hWnd))
      dc << _T(" control is not a window");
    dc << _T("\n\t}\n");

    return dc;
    }
#endif


//IsOldCombobox------------------------------------------------------------------
/*Returns TRUE if control is combobox control and current platform is WinNT3.xx
  or Win32s.

  Note: Microsoft Windows specific (Win).
 */
inline BOOL IsOldCombobox(HWND hCtrl //handle of the control
                          )
{
ASSERT(::IsWindow(hCtrl));
DWORD dwVersion = ::GetVersion(); 
if (LOBYTE(LOWORD(dwVersion)) < 4)
  {
  const int BUFFERSIZE = 16;
  char szClassName[BUFFERSIZE];
  ::GetClassName(hCtrl, szClassName, BUFFERSIZE);
  return (lstrcmp(szClassName,"ComboBox") == 0);
  }
return FALSE;
}

///////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //_KDLGITEM_H_

///////////////////////////////////////////////////////////////////////////////

  // Following makes ClassWizard happy
  //{{AFX_VIRTUAL(CDlgItemResizable)
  //}}AFX_VIRTUAL
  //{{AFX_MSG(CDlgItemResizable)
    // NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG
