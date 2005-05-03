/*$Workfile: S:\_SrcPool\Cpp\Win\32\KListEx.h$: header file
  $Revision: 5$ $Date: 2005-04-27 12:54:30$
  $Author: Darko Kolakovic$

  Interface of the CListEx class
  Copyright: CommonSoft Inc
  Jan.97 Darko Kolakovic
 */
// Group=Windows

#ifndef _KLISTEX_H_
  //$Workfile: S:\_SrcPool\Cpp\Win\32\KListEx.h$ sentry
  #define _KLISTEX_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _AFX_NO_AFXCMN_SUPPORT
  #error Windows Common Control classes not supported in this library variant.
#endif

#ifndef __AFXWIN_H__
  #include <AfxWin.h>
#endif

#include <AfxCmn.h>  //CListCtrl class

int const SMALLIMAGESIZE = 26;  //Resizing dimensions of a image, in pixels;
const BOOL ROW    =FALSE;       //'Row/column header bar' flag values
const BOOL COLUMN = TRUE;       //'Row/column header bar' flag values
const int DIAG_TABSTOP = 4;     //The default number of characters per tab
/////////////////////////////////////////////////////////////////////////////
//CListEx extends functionality of the MFC List Control class.
//
//Note: uses Microsoft Foundation Library (MFC);
//      Microsoft Windows specific (Win).
class CListEx
{
// Construction
public:
  CListEx():m_pListControl(NULL){};

// Attributes
public:
  CListCtrl* m_pListControl;  //Associated CListCtrl (see CListView)
  BOOL m_bHeadings;           //Headings type (column/row)
protected:
  int m_iItemID_;             //Browsing holder
// Operations
public:
  ~CListEx(){};
  void AddItem(int nItem,int nSubItem,LPCTSTR strItem);
  int  AddColumn(LPCTSTR strItem,int nItem,int nSubItem = -1,
        int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM,
        int nFmt = LVCFMT_LEFT);
  int  AddCell(int nRow,int nCol,LPCTSTR strItem,int nImageIndex = -1);
     //Table's heading presentation (row/column)
  void DisplayHeadings(UINT nHeadRowID, UINT nHeadColID=0, BOOL bImage=TRUE);
  BOOL AdjustColumnWidths(int iCol,BOOL bUseHeaderText = FALSE);
  int  SelectRow(const int nRow);
  int  SetTitle(int nRow,LPTSTR strText);  //Set record's title
  int  SetImage(int iRow,int iImageIndex = -1);//Set record's image
  int  GetNextSelection(BOOL bNext =FALSE);//Retreive selected items
     //Get application-specific value
  DWORD GetItemData ( int nItem ) const
    {ASSERT_VALID(m_pListControl);return m_pListControl->GetItemData(nItem); };
  BOOL SelectAll(BOOL bAll = TRUE); //Select all items
  CHeaderCtrl* GetHeaderCtrl();
  static HWND GetHeaderCtrl(HWND hListCtrl);
protected:
  int  SetColJustification(int iCol,int iType);//Sets alignment of the column

// Overrides
  virtual void EraseList();             //Erase displayed table

// Implementation
public:

};

  // This makes ClassWizard happy
  //{{AFX_VIRTUAL(CListEx)
  //}}AFX_VIRTUAL
  //{{AFX_MSG(CListEx)
  //}}AFX_MSG
  //{{AFX_MSG_MAP(CListEx)
  //}}AFX_MSG_MAP

/////////////////////////////////////////////////////////////////////////////
//This class provides a full row selection mode for the report
//mode list view control.
//
//Note: uses Microsoft Foundation Library (MFC);
//      Microsoft Windows specific (Win).
class CListCtrlEx : public CListCtrl
{
  DECLARE_DYNCREATE(CListCtrlEx)

// Construction
public:
  CListCtrlEx();

// Attributes
protected:
  BOOL m_bFullRowSel;

public:
  BOOL SetFullRowSel(BOOL bFillRowSel);
  BOOL GetFullRowSel();

  BOOL m_bClientWidthSel;

// Overrides
protected:
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CListCtrlEx)
  public:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  protected:
  virtual void PreSubclassWindow();
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual ~CListCtrlEx();
#ifdef _DEBUG
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  static LPCTSTR MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset);
  BOOL OnToolTipText(UINT /*uID*/, NMHDR* pNMHDR, LRESULT* pResult);
  virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
  int CellRectFromPoint(CPoint& point, CRect* pRectCell, int* pCol) const;
  void RepaintSelectedItems();

// Implementation - client area width
  int m_cxClient;

// Implementation - state icon width
  int m_cxStateImageOffset;
  afx_msg LRESULT OnSetImageList(WPARAM wParam, LPARAM lParam);

// Implementation - list view colors
  COLORREF m_clrText;
  COLORREF m_clrTextBk;
  COLORREF m_clrBkgnd;
  afx_msg LRESULT OnSetTextColor(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetTextBkColor(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetBkColor(WPARAM wParam, LPARAM lParam);

// Generated message map functions
protected:
  //{{AFX_MSG(CListCtrlEx)
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnPaint();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnKillFocus(CWnd* pNewWnd);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////
// CSortItemText

class CSortItemText
{
public:
  CSortItemText();
  CSortItemText(const DWORD& dwData, const CString& sTxt);
  virtual  ~CSortItemText();

  CString m_strTxt;
  DWORD m_dwData;
};

//////////////////////////////////////////////////////////////////////
// CSortItemInt

class CSortItemInt
{
public:
  CSortItemInt();
  CSortItemInt(const DWORD& dwData, const CString& sTxt);
  virtual ~CSortItemInt();

  CString m_strTxt;
  int m_nInt;
  DWORD m_dwData;
};

//////////////////////////////////////////////////////////////////////
// TODO: CSortColumn insert in CListEx

class CSortColumn
{
public:
  CSortColumn();
  CSortColumn(CListCtrl* pWnd, const int& nCol, const bool& bIsNumeric);
  virtual ~CSortColumn();
  void Sort(const bool& bAsc);

  CListCtrl* m_pWnd;
  int m_nCol;
  bool m_bIsNumeric;

  static int CALLBACK CompareAscText(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
  static int CALLBACK CompareDesText(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

  static int CALLBACK CompareAscInt(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
  static int CALLBACK CompareDesInt(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
};

///////////////////////////////////////////////////////////////////////////////
#endif  //_KLISTEX_H_
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         2004-10-01 22:35:08  Darko           stdafx.h
 *  3    Biblioteka1.2         2003-08-25 01:15:59  Darko           comment
 *  2    Biblioteka1.1         2003-08-14 14:19:16  Darko           draft methods
 *  1    Biblioteka1.0         2003-08-13 13:51:38  Darko
 * $
 *****************************************************************************/
