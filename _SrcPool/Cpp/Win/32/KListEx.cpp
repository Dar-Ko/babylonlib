/*DListEx.cpp : implementation file

  Darko Kolakovic Dec.96
  Copyright (C) 1996 Adwel International Ltd.
  All rights reserved.
 */

#include "stdafx.h"
#include "KListEx.h"  //CListEx class
#include "Resource.h"

#ifndef IDS_TBL_HEAD_DEFAULT
  #define IDS_TBL_HEAD_DEFAULT            32080
#endif

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CListEx class

//::AddItem()------------------------------------------------------------------
/*Inserts an item in the specified cell.
 */
void CListEx::AddItem(int nItem,int nSubItem,LPCTSTR strItem)
{
  //1st column is assigned to the headings, and  
  //new item are subitem of existing heading

if (m_bHeadings)
  AddCell(nSubItem,1,strItem);     //Vertical headings (as column)
else
  AddCell(nItem,nSubItem,strItem); //Horizontal headings (as row)
}

//AddColumn()------------------------------------------------------------------
/*Returns the index of the new column if successful or -1 otherwise
 */
int CListEx::AddColumn(LPCTSTR strItem,int nItem,
                               int nSubItem/* = -1*/,
                               int nMask /* = LVCF_FMT |
                                            LVCF_WIDTH |
                                             LVCF_TEXT |
                                            LVCF_SUBITEM*/,
                               int nFmt/* = LVCFMT_LEFT*/)
{
ASSERT_VALID(m_pListControl);
LV_COLUMN lvc;
lvc.mask = nMask;
lvc.fmt = nFmt;
lvc.pszText = (LPTSTR) strItem;
    //Get minimum column width necessary to display all item's attribbutes
lvc.cx = m_pListControl->GetStringWidth(lvc.pszText) + SMALLIMAGESIZE +3;
if(nMask & LVCF_SUBITEM)
  {
  if(nSubItem != -1)
    lvc.iSubItem = nSubItem;
  else
    lvc.iSubItem = nItem;
  }
return m_pListControl->InsertColumn(nItem,&lvc);
}

//::AddCell()------------------------------------------------------------------
/*Inserts cell information in table's item list.
  Returns the index of the new row (item) if successful, otherwise -1.
  Item has no bitmap presentation if nImageIndex is -1. Image could be set only
  for items (cells) in column 0.
 */
int CListEx::AddCell(int nRow,int nCol,LPCTSTR strItem,
                            int nImageIndex/* = -1*/)
{
ASSERT_VALID(m_pListControl);
LV_ITEM lvItem;
lvItem.mask = nCol ? LVIF_TEXT : LVIF_TEXT | LVIF_IMAGE;
lvItem.iItem = nRow;
lvItem.iSubItem = nCol;
lvItem.pszText = (LPTSTR) strItem;
lvItem.iImage = nImageIndex;

if(nCol == 0)        //Insert leftmost field (column) item
  return m_pListControl->InsertItem(&lvItem);

return (m_pListControl->SetItem(&lvItem)? nRow : -1);
}

//::DisplayHeadings()----------------------------------------------------------
/*Reads and displays field headings as horizontal bar, or as separate column.
  Heading fields are in string separated with ','.

  Example:
      COLUMN headings:                      ROW headings:
      |HEADCOL0|HEADCOL1|HEADCOLn|      |HEADROW0|HEADROW1|HEADROWn|
      |HEADROW0| value    value           value     value     value
      |HEADROW1| value    value           value     value     value
      |HEADROWn| value    value           value     value     value
 */
void CListEx::DisplayHeadings(UINT nHeadRowID,  //header string resource ID
                              UINT nHeadColID,  //=0 column titles string ID
                              BOOL bImage       //= TRUE enable bitmaps
                              )
{
ASSERT_VALID(m_pListControl);
ASSERT(::IsWindow(m_pListControl->m_hWnd));
  
CString strHeadings;
int nPos;
int nCount = 0;
int NoImage = -1;
int& ImageID = (bImage ? nCount : NoImage);
BOOL bHeadings = ROW;      //First create horizontal headings
EraseList();               //Erase displayed table


if (m_bHeadings == COLUMN) //Headings are in 1st column
  {
  if (nHeadColID == 0)
    nHeadColID = IDS_TBL_HEAD_DEFAULT; 
  strHeadings.LoadString(nHeadColID);   //Read column titles
  }
else
  strHeadings.LoadString(nHeadRowID);   //Read row titles

   //Parse heading string and add substrings to row(item) / column list
while(TRUE)
  {
  while ((nPos = strHeadings.Find(_T(","))) != -1)
    {
    CString strItem;
    strItem = strHeadings.Left(nPos);

    if (bHeadings== COLUMN) //Set 1st column as vertical headings 
      AddCell(nCount,0,strItem,ImageID);
    else                    //Set 1st row as horizontal headings 
      AddColumn(strItem,nCount);
  
    nCount++;
    strItem = strHeadings.Mid(nPos + 1);
    strHeadings = strItem;
    }
    //Add the last subtoken
  if (bHeadings == COLUMN) //Set 1st column as vertical headings 
    {
    AddCell(nCount,0,strHeadings,ImageID);
    break;
    }
  else  //Set 1st row as horizontal headings 
    {
    AddColumn(strHeadings,nCount);
    if(m_bHeadings == COLUMN)
      {
      bHeadings = COLUMN;
      if (nHeadRowID != 0)
        VERIFY(strHeadings.LoadString(nHeadRowID)); //Read field titles
      else
        strHeadings.Empty();
      }
    else
      break;
    }
  }
}

//::AdjustColumnWidths()-------------------------------------------------------
/*Resizes column to ensure that all items are visible.
  To get or set column width use GetColumnWidth or SetColumnWidth.
 */
BOOL CListEx::AdjustColumnWidths(int iCol, //column index to be resized to 
                                           //largest item width [0,N]
                                 BOOL bUseHeaderText //= FALSE if TRUE 
              //automatically sizes the column to fit the header text,
              //if FALSE (default) automatically sizes the column to fit the
              //largest item text
                                 )
{
ASSERT_VALID(m_pListControl);
ASSERT(::IsWindow(m_pListControl->m_hWnd));

#ifdef _DEBUG
BOOL bResult;
bResult = (BOOL) ::SendMessage(m_pListControl->m_hWnd,
                            LVM_SETCOLUMNWIDTH, 
                            (WPARAM)iCol,
                            MAKELPARAM((bUseHeaderText ?
                                      LVSCW_AUTOSIZE_USEHEADER : LVSCW_AUTOSIZE),
                                      0)
                            );
if (!bResult)
  TRACE1("CListEx::AdjustColumnWidths(iCol = %d) failed!\n",iCol);
return bResult;

#else
return (BOOL) ::SendMessage(m_pListControl->m_hWnd,
                            LVM_SETCOLUMNWIDTH, 
                            (WPARAM)iCol,
                            MAKELPARAM((bUseHeaderText ?
                                      LVSCW_AUTOSIZE_USEHEADER : LVSCW_AUTOSIZE),
                                      0)
                            );
#endif //_DEBUG

}

//::EraseList()----------------------------------------------------------------
/*Erases all displayed table's items
 */
void CListEx::EraseList()
{
ASSERT_VALID(m_pListControl);
m_pListControl->DeleteAllItems();
while(m_pListControl->DeleteColumn(0));
}

//SelectRow()------------------------------------------------------------------
/*Select one row
 */
int CListEx::SelectRow(const int iRow)
{
ASSERT_VALID(m_pListControl);
return (m_pListControl->SetItemState(iRow,LVIS_SELECTED,LVIS_SELECTED)? iRow : -1);
}


//::SetImage()-----------------------------------------------------------------
/*Sets record's image presentation. Returns the record (row) index if
  successful or -1 otherwise.
 */
int CListEx::SetImage(int iRow, //row number to which the new image presentation refers
                      int iImageIndex//=-1 index of the list view item’s icon in the large 
                                     //icon and small icon image lists. If this member is 
                                     //the I_IMAGECALLBACK value, the item is a callback item.
                                     //Value of -1 erases image.
                      )
{
LV_ITEM lvItem;
lvItem.mask = LVIF_IMAGE;
lvItem.iItem = iRow;
lvItem.iSubItem = 0;
lvItem.iImage = iImageIndex;

return (m_pListControl->SetItem(&lvItem)? iRow : -1);
}

//SetTitle()-------------------------------------------------------------------
/*Set record's Title (leftmost column)
 */
int CListEx::SetTitle(int nRow,LPTSTR strText)
{
ASSERT_VALID(m_pListControl);
LV_ITEM lvItem;
lvItem.mask = LVIF_TEXT;
if (m_bHeadings) //Headings are in 1st column
  {
  lvItem.iItem = nRow; 
  lvItem.iSubItem = 0; //Set leftmost field (column) item
  lvItem.pszText = strText;
  return (m_pListControl->SetItem(&lvItem)? nRow : -1);
  }
ASSERT(m_bHeadings); //Headings in the 1st row are unsupported yet!
return -1;  
}

//::SetColJustification()------------------------------------------------------
/*Sets alignment of the column. It can be one of these values:
  LVCFMT_LEFT, 
  LVCFMT_RIGHT,
  or LVCFMT_CENTER.
 */
int CListEx::SetColJustification(int iCol,int iType)
{
#ifdef __DEBUG
if (iType != LVCFMT_LEFT)
  if (iType != LVCFMT_RIGHT)
    if (iType != LVCFMT_CENTER)
      {
      ASSERT (FALSE);
      return -1;
      }
#endif

LV_COLUMN Column;
Column.mask = LVCF_FMT;
Column.fmt = iType;

return (m_pListControl->SetColumn(iCol,&Column)? iCol : -1);
}

//::GetNextSelection()---------------------------------------------------------
/*Returns index of first selected item if bNext is FALSE; if bNext is TRUE 
  returns index of next successive selection. If all selected items are browsed,
  returns -1;
 */
int CListEx::GetNextSelection(BOOL bNext/* =FALSE*/)//Retreive selected items
{
ASSERT_VALID(m_pListControl);
if (!bNext)        //Get first selected item;
  m_iItemID_ = -1;
   
m_iItemID_ = m_pListControl->GetNextItem(m_iItemID_, LVNI_SELECTED);
return m_iItemID_;
}

//::SelectAll()----------------------------------------------------------------
/*Select or unselect all items
  Returns nonzero if successful; otherwise FALSE.
 */
BOOL CListEx::SelectAll(BOOL bSelect //select or unselect all
                       ) 
{ 
LV_ITEM lvItem;
lvItem.mask = LVIF_STATE;
lvItem.iItem =  -1; //All
lvItem.state = bSelect ? LVIS_SELECTED : 0; //current state of the item
lvItem.stateMask = LVIS_SELECTED;           //the valid states of the item

return (m_pListControl->SetItemState(-1,&lvItem));
}

//::GetHeaderCtrl()------------------------------------------------------------
/*Get pointer to the first header control associated with list control
*/
CHeaderCtrl* CListEx::GetHeaderCtrl()
{
ASSERT_VALID(m_pListControl);
ASSERT(::IsWindow(m_pListControl->m_hWnd));
HWND hWnd = CListEx::GetHeaderCtrl(m_pListControl->m_hWnd);
if (hWnd != NULL)
  return (CHeaderCtrl*)CWnd::FromHandle(hWnd);
return NULL;
}

/*Returns handle to the first header control associated with list control or
  NULL if header does not exist.
  (static function)
*/
HWND CListEx::GetHeaderCtrl(HWND hListCtrl)
{
HWND hWnd = ::GetWindow(hListCtrl,GW_CHILD);
static const int WNDNAMESIZE = sizeof (WC_HEADER) / sizeof(TCHAR);
TCHAR szChildWndName[WNDNAMESIZE];
  //Browse all child windows to wind one with WC_HEADER name
for(; hWnd; hWnd = ::GetWindow(hListCtrl,GW_HWNDNEXT))
  {
  ::GetClassName(hWnd,szChildWndName,WNDNAMESIZE);
  if(!lstrcmp(WC_HEADER,szChildWndName))
    return hWnd;
  }
return NULL;
}
/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx message handlers

/////////////////////////////////////////////////////////////////////////////


int CHelpers::Insert(CListCtrlEx* pListCtrl, CString& sRow, int nImage/* = -1*/,
    int nIndex/* = -1*/)
{
  ASSERT(pListCtrl);

  int nItemIndex = -1;
  int nEnd = sRow.Find(_T("|"));
  if(nEnd != -1)
  {
    int nSubItem = 0;
    LV_ITEM lvItem;
    CString sColVal;
    lvItem.mask = LVIF_TEXT;
    
    if(nImage != -1)
    {
      lvItem.mask |= LVIF_IMAGE;
      lvItem.iImage = nImage;
    }
    
    if(nIndex != -1)
      lvItem.iItem = nIndex;

    lvItem.iSubItem = nSubItem++;
    sColVal = sRow.Mid(0, nEnd);
    lvItem.pszText = sColVal.GetBuffer(sColVal.GetLength()+1);
    sColVal.ReleaseBuffer();
    nItemIndex   = pListCtrl->InsertItem(&lvItem);
    ASSERT(nItemIndex != -1);
    if(nItemIndex != -1)
    {
      while(sRow.GetLength() > nEnd) 
      {      
        sRow = sRow.Mid(nEnd + 1);
        nEnd = sRow.Find(_T("|"));
        if(nEnd == -1)
          break;
        
        lvItem.iItem = nItemIndex;
        lvItem.iSubItem = nSubItem++;
        sColVal = sRow.Mid(0, nEnd);
        lvItem.pszText = sColVal.GetBuffer(sColVal.GetLength()+1);
        sColVal.ReleaseBuffer();
        pListCtrl->SetItem(&lvItem);
      }
    }
  }

  return nItemIndex;
}

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

IMPLEMENT_DYNCREATE(CListCtrlEx, CListCtrl)

BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
  //{{AFX_MSG_MAP(CListCtrlEx)
  ON_WM_SIZE()
  ON_WM_PAINT()
  ON_WM_SETFOCUS()
  ON_WM_KILLFOCUS()
  //}}AFX_MSG_MAP
  ON_MESSAGE(LVM_SETIMAGELIST, OnSetImageList)
  ON_MESSAGE(LVM_SETTEXTCOLOR, OnSetTextColor)
  ON_MESSAGE(LVM_SETTEXTBKCOLOR, OnSetTextBkColor)
  ON_MESSAGE(LVM_SETBKCOLOR, OnSetBkColor)
  ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
  ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx construction/destruction

CListCtrlEx::CListCtrlEx()
{
  m_bFullRowSel=FALSE;
  m_bClientWidthSel=TRUE;

  m_cxClient=0;
  m_cxStateImageOffset=0;

  m_clrText=::GetSysColor(COLOR_WINDOWTEXT);
  m_clrTextBk=::GetSysColor(COLOR_WINDOW);
  m_clrBkgnd=::GetSysColor(COLOR_WINDOW);
}

CListCtrlEx::~CListCtrlEx()
{
}

BOOL CListCtrlEx::PreCreateWindow(CREATESTRUCT& cs)
{
  // default is report view and full row selection
  cs.style &= ~LVS_TYPEMASK;
  cs.style |= LVS_REPORT | LVS_OWNERDRAWFIXED;
  
  m_bFullRowSel=TRUE;

  return(CListCtrl::PreCreateWindow(cs));
}

BOOL CListCtrlEx::SetFullRowSel(BOOL bFullRowSel)
{
  // no painting during change
  LockWindowUpdate();

  m_bFullRowSel=bFullRowSel;

  BOOL bRet;

  if(m_bFullRowSel)
    bRet=ModifyStyle(0L,LVS_OWNERDRAWFIXED);
  else
    bRet=ModifyStyle(LVS_OWNERDRAWFIXED,0L);

  // repaint window if we are not changing view type
  if(bRet && (GetStyle() & LVS_TYPEMASK)==LVS_REPORT)
    Invalidate();

  // repaint changes
  UnlockWindowUpdate();

  return(bRet);
}

BOOL CListCtrlEx::GetFullRowSel()
{
  return(m_bFullRowSel);
}

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx drawing

// offsets for first and other columns
#define OFFSET_FIRST  2
#define OFFSET_OTHER  6

void CListCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
  CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
  CRect rcItem(lpDrawItemStruct->rcItem);
  UINT uiFlags=ILD_TRANSPARENT;
  CImageList* pImageList;
  int nItem=lpDrawItemStruct->itemID;
  BOOL bFocus=(GetFocus()==this);
  COLORREF clrTextSave, clrBkSave;
  COLORREF clrImage=m_clrBkgnd;
  static _TCHAR szBuff[MAX_PATH];
  LPCTSTR pszText;

// get item data

  LV_ITEM lvi;
  lvi.mask=LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
  lvi.iItem=nItem;
  lvi.iSubItem=0;
  lvi.pszText=szBuff;
  lvi.cchTextMax=sizeof(szBuff);
  lvi.stateMask=0xFFFF;    // get all state flags
  GetItem(&lvi);

  BOOL bSelected=(bFocus || (GetStyle() /*& LVS_SHOWSELALWAYS*/)) && lvi.state & LVIS_SELECTED;
  bSelected=bSelected || (lvi.state & LVIS_DROPHILITED);

// set colors if item is selected

  CRect rcAllLabels;
  GetItemRect(nItem,rcAllLabels,LVIR_BOUNDS);
  CRect rcLabel;
  GetItemRect(nItem,rcLabel,LVIR_LABEL);
  rcAllLabels.left=rcLabel.left;
  if(m_bClientWidthSel && rcAllLabels.right<m_cxClient)
    rcAllLabels.right=m_cxClient;

  if(bSelected)
  {
    clrTextSave=pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
    clrBkSave=pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));

    pDC->FillRect(rcAllLabels,&CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
  }
  else
    pDC->FillRect(rcAllLabels,&CBrush(m_clrTextBk));

// set color and mask for the icon

  if(lvi.state & LVIS_CUT)
  {
    clrImage=m_clrBkgnd;
    uiFlags|=ILD_BLEND50;
  }
  else if(bSelected)
  {
    clrImage=::GetSysColor(COLOR_HIGHLIGHT);
    uiFlags|=ILD_BLEND50;
  }

// draw state icon

  UINT nStateImageMask=lvi.state & LVIS_STATEIMAGEMASK;
  if(nStateImageMask)
  {
    int nImage=(nStateImageMask>>12)-1;
    pImageList=GetImageList(LVSIL_STATE);
    if(pImageList)
      pImageList->Draw(pDC,nImage,CPoint(rcItem.left,rcItem.top),ILD_TRANSPARENT);
  }

// draw normal and overlay icon

  CRect rcIcon;
  GetItemRect(nItem,rcIcon,LVIR_ICON);

  pImageList=GetImageList(LVSIL_SMALL);
  if(pImageList)
  {
    UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
    if(rcItem.left<rcItem.right-1)
      ImageList_DrawEx(pImageList->m_hImageList,lvi.iImage,pDC->m_hDC,rcIcon.left,rcIcon.top,16,16,m_clrBkgnd,clrImage,uiFlags | nOvlImageMask);
  }

// draw item label

  GetItemRect(nItem,rcItem,LVIR_LABEL);
  rcItem.right-=m_cxStateImageOffset;

  pszText=MakeShortString(pDC,szBuff,rcItem.right-rcItem.left,2*OFFSET_FIRST);

  rcLabel=rcItem;
  rcLabel.left+=OFFSET_FIRST;
  rcLabel.right-=OFFSET_FIRST;

  pDC->DrawText(pszText,-1,rcLabel,DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);

// draw labels for extra columns

  LV_COLUMN lvc;
  lvc.mask=LVCF_FMT | LVCF_WIDTH;

  for(int nColumn=1; GetColumn(nColumn,&lvc); nColumn++)
  {
    rcItem.left=rcItem.right;
    rcItem.right+=lvc.cx;

     int nRetLen=GetItemText(nItem,nColumn,szBuff,sizeof(szBuff));
    if(nRetLen==0) continue;

    pszText=MakeShortString(pDC,szBuff,rcItem.right-rcItem.left,2*OFFSET_OTHER);

    UINT nJustify=DT_LEFT;

    if(pszText==szBuff)
    {
      switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
      {
      case LVCFMT_RIGHT:
        nJustify=DT_RIGHT;
        break;
      case LVCFMT_CENTER:
        nJustify=DT_CENTER;
        break;
      default:
        break;
      }
    }

    rcLabel=rcItem;
    rcLabel.left+=OFFSET_OTHER;
    rcLabel.right-=OFFSET_OTHER;

    pDC->DrawText(pszText,-1,rcLabel,nJustify | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
  }

// draw focus rectangle if item has focus

  if(lvi.state & LVIS_FOCUSED && bFocus)
    pDC->DrawFocusRect(rcAllLabels);

// set original colors if item was selected

  if(bSelected)
  {
          pDC->SetTextColor(clrTextSave);
    pDC->SetBkColor(clrBkSave);
  }
}

LPCTSTR CListCtrlEx::MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset)
{
  static const _TCHAR szThreeDots[]=_T("...");

  int nStringLen=lstrlen(lpszLong);

  if(nStringLen==0 || pDC->GetTextExtent(lpszLong,nStringLen).cx+nOffset<=nColumnLen)
    return(lpszLong);

  static _TCHAR szShort[MAX_PATH];

  lstrcpy(szShort,lpszLong);
  int nAddLen=pDC->GetTextExtent(szThreeDots,sizeof(szThreeDots)).cx;

  for(int i=nStringLen-1; i>0; i--)
  {
    szShort[i]=0;
    if(pDC->GetTextExtent(szShort,i).cx+nOffset+nAddLen<=nColumnLen)
      break;
  }

  lstrcat(szShort,szThreeDots);

  return(szShort);
}

void CListCtrlEx::RepaintSelectedItems()
{
  CRect rcItem, rcLabel;

// invalidate focused item so it can repaint properly

  int nItem=GetNextItem(-1,LVNI_FOCUSED);

  if(nItem!=-1)
  {
    GetItemRect(nItem,rcItem,LVIR_BOUNDS);
    GetItemRect(nItem,rcLabel,LVIR_LABEL);
    rcItem.left=rcLabel.left;

    InvalidateRect(rcItem,FALSE);
  }

// if selected items should not be preserved, invalidate them

  if(!(GetStyle() & LVS_SHOWSELALWAYS))
  {
    for(nItem=GetNextItem(-1,LVNI_SELECTED);
      nItem!=-1; nItem=GetNextItem(nItem,LVNI_SELECTED))
    {
      GetItemRect(nItem,rcItem,LVIR_BOUNDS);
      GetItemRect(nItem,rcLabel,LVIR_LABEL);
      rcItem.left=rcLabel.left;

      InvalidateRect(rcItem,FALSE);
    }
  }

// update changes 

  UpdateWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx diagnostics

#ifdef _DEBUG

void CListCtrlEx::Dump(CDumpContext& dc) const
{
  CListCtrl::Dump(dc);

  dc << "m_bFullRowSel = " << (UINT)m_bFullRowSel;
  dc << "\n";
  dc << "m_cxStateImageOffset = " << m_cxStateImageOffset;
  dc << "\n";
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx message handlers

LRESULT CListCtrlEx::OnSetImageList(WPARAM wParam, LPARAM lParam)
{
  if((int)wParam==LVSIL_STATE)
  {
    int cx, cy;

    if(::ImageList_GetIconSize((HIMAGELIST)lParam,&cx,&cy))
      m_cxStateImageOffset=cx;
    else
      m_cxStateImageOffset=0;
  }

  return(Default());
}

LRESULT CListCtrlEx::OnSetTextColor(WPARAM wParam, LPARAM lParam)
{
  m_clrText=(COLORREF)lParam;
  return(Default());
}

LRESULT CListCtrlEx::OnSetTextBkColor(WPARAM wParam, LPARAM lParam)
{
  m_clrTextBk=(COLORREF)lParam;
  return(Default());
}

LRESULT CListCtrlEx::OnSetBkColor(WPARAM wParam, LPARAM lParam)
{
  m_clrBkgnd=(COLORREF)lParam;
  return(Default());
}

void CListCtrlEx::OnSize(UINT nType, int cx, int cy) 
{
  m_cxClient=cx;
  CListCtrl::OnSize(nType, cx, cy);
}

void CListCtrlEx::OnPaint() 
{
  // in full row select mode, we need to extend the clipping region
  // so we can paint a selection all the way to the right
  if(m_bClientWidthSel && (GetStyle() & LVS_TYPEMASK)==LVS_REPORT && GetFullRowSel())
  {
    CRect rcAllLabels;
    GetItemRect(0,rcAllLabels,LVIR_BOUNDS);

    if(rcAllLabels.right<m_cxClient)
    {
      // need to call BeginPaint (in CPaintDC c-tor)
      // to get correct clipping rect
      CPaintDC dc(this);

      CRect rcClip;
      dc.GetClipBox(rcClip);

      rcClip.left=min(rcAllLabels.right-1,rcClip.left);
      rcClip.right=m_cxClient;

      InvalidateRect(rcClip,FALSE);
      // EndPaint will be called in CPaintDC d-tor
    }
  }

  CListCtrl::OnPaint();
}

void CListCtrlEx::OnSetFocus(CWnd* pOldWnd) 
{
  CListCtrl::OnSetFocus(pOldWnd);

  // check if we are getting focus from label edit box
  if(pOldWnd!=NULL && pOldWnd->GetParent()==this)
    return;

  // repaint items that should change appearance
  if(m_bFullRowSel && (GetStyle() & LVS_TYPEMASK)==LVS_REPORT)
    RepaintSelectedItems();
}

void CListCtrlEx::OnKillFocus(CWnd* pNewWnd) 
{
  CListCtrl::OnKillFocus(pNewWnd);

  // check if we are losing focus to label edit box
  if(pNewWnd!=NULL && pNewWnd->GetParent()==this)
    return;

  // repaint items that should change appearance
  if(m_bFullRowSel && (GetStyle() & LVS_TYPEMASK)==LVS_REPORT)
    RepaintSelectedItems();
}

void CListCtrlEx::PreSubclassWindow() 
{
  CListCtrl::PreSubclassWindow();
  EnableToolTips(TRUE);
}

int CListCtrlEx::CellRectFromPoint(CPoint& point, CRect* pRectCell, int* pCol) const
{
    if((::GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT )
     return -1;

    int nRow = GetTopIndex();
    int nBottom = nRow + GetCountPerPage();
    if(nBottom > GetItemCount())
    nBottom = GetItemCount();
        
    CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();

    for(; nRow <= nBottom; nRow++)
    {
        CRect rect;
        GetItemRect(nRow, &rect, LVIR_BOUNDS);
        if(rect.PtInRect(point))
        {
      for(int nColumn = 0; nColumn < nColumnCount; nColumn++)
      {
        int nColWidth = GetColumnWidth(nColumn);
        if(point.x >= rect.left && point.x <= (rect.left + nColWidth))
        {
          CRect rectClient;
          GetClientRect(&rectClient);
          if(pCol)
            *pCol = nColumn;
          
          rect.right = rect.left + nColWidth;

          if(rect.right > rectClient.right) 
            rect.right = rectClient.right;
          
          *pRectCell = rect;
          
          return nRow;
        }

        rect.left += nColWidth;
      }
    }
  }

  return -1;
}

BOOL CListCtrlEx::OnToolTipText(UINT /*uID*/, NMHDR* pNMHDR, LRESULT* pResult)
{
    BOOL bRet = TRUE;
#ifdef _TOOL_TIP_ENABLE
  TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
    TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
    UINT nID = pNMHDR->idFrom;
    if(!nID)
      bRet = FALSE;

  if(bRet)
  {
    int nRow = ((nID-1) >> 10) & 0x3fffff ;
    int nCol = (nID-1) & 0x3ff;
    CString strTipText = GetItemText(nRow, nCol);
    strTipText.TrimRight();
    strTipText.TrimLeft();
#ifndef _UNICODE
    if (pNMHDR->code == TTN_NEEDTEXTA)
      lstrcpyn(pTTTA->szText, strTipText, 80);
    else
      _mbstowcsz(pTTTW->szText, strTipText, 80);
#else
    if(pNMHDR->code == TTN_NEEDTEXTA)
      _wcstombsz(pTTTA->szText, strTipText, 80);
    else
      lstrcpyn(pTTTW->szText, strTipText, 80);
#endif
  }
    
  *pResult = 0;
#endif

    return bRet;
}

int CListCtrlEx::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
  int nID = -1;
#ifdef _TOOL_TIP_ENABLE
  int nCol;
  CRect rect;
  int nRow = CellRectFromPoint(point, &rect, &nCol);
  if(nRow == -1 ) 
    return -1;
  
  pTI->hwnd = m_hWnd;
  pTI->uId = (UINT)((nRow << 10) + (nCol & 0x3ff) + 1);
  nID = pTI->uId
  pTI->lpszText = LPSTR_TEXTCALLBACK;
  
  pTI->rect = rect;
#endif
  
  return nID;
}

//////////////////////////////////////////////////////////////////////
// CSortColumn

CSortColumn::CSortColumn()
{
  ASSERT(FALSE); // use the other one
}

CSortColumn::CSortColumn(CListCtrl* pWnd, const int& nCol, const bool& bIsNumeric)
{
    m_nCol = nCol;
    m_pWnd = pWnd;
    m_bIsNumeric = bIsNumeric;
    
    ASSERT(m_pWnd);
    int nMax = m_pWnd->GetItemCount();
    DWORD dwData;
    CString sTxt;
    if(m_bIsNumeric)
    {
        for(int n = 0; n < nMax; n++)
        {
            dwData = m_pWnd->GetItemData(n);
            sTxt = m_pWnd->GetItemText(n, m_nCol);
            m_pWnd->SetItemData(n, (DWORD)new CSortItemInt(dwData, sTxt));
        }
    }
    else
    {
        for(int n = 0; n < nMax; n++)
        {
            dwData = m_pWnd->GetItemData(n);
            sTxt = m_pWnd->GetItemText(n, m_nCol);
            m_pWnd->SetItemData(n, (DWORD)new CSortItemText(dwData, sTxt));
        }
    }
}

CSortColumn::~CSortColumn()
{
    ASSERT(m_pWnd);
    int nMax = m_pWnd->GetItemCount();
  if(m_bIsNumeric)
    {
        CSortItemInt* pItem;
    for(int n = 0; n < nMax; n++)
        {
            pItem = (CSortItemInt*)m_pWnd->GetItemData(n);
            ASSERT(pItem);
            m_pWnd->SetItemData(n, pItem->m_dwData);
            delete pItem;
        }
    }
    else
    {
        CSortItemText* pItem;
        for(int n = 0; n < nMax; n++)
        {
            pItem = (CSortItemText*)m_pWnd->GetItemData(n);
            ASSERT(pItem);
            m_pWnd->SetItemData(n, pItem->m_dwData);
            delete pItem;
        }
    }
}

void CSortColumn::Sort(const bool& bAsc)
{
    if(m_bIsNumeric)
    {
        if(bAsc)
            m_pWnd->SortItems(CompareAscInt, 0L);
    else
            m_pWnd->SortItems(CompareDesInt, 0L);
    }
    else
    {
        if(bAsc)
            m_pWnd->SortItems(CompareAscText, 0L);
    else
            m_pWnd->SortItems(CompareDesText, 0L);
    }
}

int CALLBACK CSortColumn::CompareAscText(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CSortItemText* pItem1 = (CSortItemText*)lParam1;
    CSortItemText* pItem2 = (CSortItemText*)lParam2;
    ASSERT(pItem1 && pItem2);
    return pItem1->m_strTxt.CompareNoCase(pItem2->m_strTxt);
}

int CALLBACK CSortColumn::CompareDesText(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CSortItemText* pItem1 = (CSortItemText*)lParam1;
    CSortItemText* pItem2 = (CSortItemText*)lParam2;
    ASSERT(pItem1 && pItem2);
    return pItem2->m_strTxt.CompareNoCase(pItem1->m_strTxt);
}

int CALLBACK CSortColumn::CompareAscInt(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CSortItemInt* pItem1 = (CSortItemInt*)lParam1;
    CSortItemInt* pItem2 = (CSortItemInt*)lParam2;
    ASSERT(pItem1 && pItem2);
    if(pItem1->m_nInt == pItem2->m_nInt)
    return 0;
    return pItem1->m_nInt > pItem2->m_nInt ? 1 : -1;
}

int CALLBACK CSortColumn::CompareDesInt(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CSortItemInt* pItem1 = (CSortItemInt*)lParam1;
    CSortItemInt* pItem2 = (CSortItemInt*)lParam2;
    ASSERT(pItem1 && pItem2);
    if(pItem1->m_nInt == pItem2->m_nInt)
    return 0;
    return pItem1->m_nInt < pItem2->m_nInt ? 1 : -1;
}

//////////////////////////////////////////////////////////////////////
// CSortItemText

CSortItemText::CSortItemText()
{
  ASSERT(FALSE); // use the other one  
}

CSortItemText::CSortItemText(const DWORD& dwData, const CString& sTxt)
{
    m_dwData = dwData;
    m_strTxt = sTxt;
}

CSortItemText::~CSortItemText()
{
}

//////////////////////////////////////////////////////////////////////
// CSortItemInt

CSortItemInt::CSortItemInt()
{
  ASSERT(FALSE); // use the other one  
}

CSortItemInt::CSortItemInt(const DWORD& dwData, const CString& sTxt)
{
    m_dwData = dwData;
#ifdef _UNICODE
  USES_CONVERSION;
  m_nInt = atoi(W2CA((LPCTSTR)sTxt));
#else
  m_nInt = atoi((LPCTSTR)sTxt);
#endif
}

CSortItemInt::~CSortItemInt()
{
}