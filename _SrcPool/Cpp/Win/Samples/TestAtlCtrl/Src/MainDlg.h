// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

// Group=Examples Windows

#pragma once

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#include "resource.h"
#include "KMsgMapNotify.h" //Notification message handlers

///////////////////////////////////////////////////////////////////////////////
//Note: uses Microsoft Active Template Library (ATL);
//      Windows Template Library (WTL);
//      Microsoft Windows specific (Win32).
class CMainDlg : public CDialogImpl<CMainDlg>,
                 public CUpdateUI<CMainDlg>,
                 public CMessageFilter,
                 public CIdleHandler
{
public:
  enum { IDD = IDD_MAINDLG };

  virtual BOOL PreTranslateMessage(MSG* pMsg);
  virtual BOOL OnIdle();

  BEGIN_UPDATE_UI_MAP(CMainDlg)
  END_UPDATE_UI_MAP()

  BEGIN_MSG_MAP(CMainDlg)
    MSG_WM_INITDIALOG(OnInitDialog)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
    COMMAND_ID_HANDLER(IDOK, OnOK)
    COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
    //List view notifications
    MSG_LVN_GETINFOTIP(IDC_LISTTEST, OnGetInfoTip)
    MSG_LVN_DBLCLK(IDC_LISTTEST, OnDblClk)

  END_MSG_MAP()

  void CloseDialog(int nVal);

// Handler prototypes (uncomment arguments if needed):
//  LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//  LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//  LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

  BOOL OnInitDialog(CWindow /*wndFocus*/, LPARAM /*lInitParam */);
  LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
  LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    //List view notification handlers
  LRESULT OnGetInfoTip(NMLVGETINFOTIP* pHeader);
  LRESULT OnDblClk(NMITEMACTIVATE*);

protected:
  void InitListView(const int idCtrl);

public:
  CListViewCtrl m_ctrlListView; //list view used to test notification messages
};

/////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: MainDlg.h,v $
 * Revision 1.5  2009/04/21 21:33:18  ddarko
 * Initilalize List View control
 *
 *****************************************************************************/
