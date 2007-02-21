/*$Workfile: TestDumpButtonStyle.cpp$: implementation file
  $Revision: 6$ $Date: 2007-02-21 09:10:51$
  $Author: Darko Kolakovic$

  Implementation file
  Copyright: CommonSoft Inc.
  2003-08-25 Darko Kolakovic
 */

// Group=Examples Windows

#include "stdafx.h"
#include "Resource.h"
#include "KTestLog.h"

#ifdef _DEBUG
  #define new DEBUG_NEW
  extern void DumpButtonStyle(HWND hButton);
  extern void DumpButtonStyle(UINT nBtnStyle);
#else
  #if _MSC_VER > 1200
    #define DumpButtonStyle __noop
  #else
    #define DumpButtonStyle (void(0))
  #endif
#endif

bool TestDumpButtonStyle(HWND hButton =NULL);

#ifndef IDD_TESTBUTTON_STYLE
  #error Create IDD_TESTBUTTON_STYLE Dialog first!
#endif

///////////////////////////////////////////////////////////////////////////////
//Helper class used to test setting button types and styles and
//DumpButtonStyle() function.
//
//Note: uses Microsoft Foundation Library (MFC);
//      Microsoft Windows specific (Win).
//
//See also: winuser.h, afxwin2.inl, CButton::GetButtonStyle(), CButton::Create()
class TestDlgDumpButtonStyle : public CDialog
{
public:
  TestDlgDumpButtonStyle();
  virtual ~TestDlgDumpButtonStyle();

// Dialog Data
  enum { IDD = IDD_TESTBUTTON_STYLE };
  CButton m_btnTest; //test button

protected:
  virtual BOOL OnInitDialog();

// Implementation
protected:
  DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(TestDlgDumpButtonStyle, CDialog)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
/*
 */
TestDlgDumpButtonStyle::TestDlgDumpButtonStyle() : CDialog(TestDlgDumpButtonStyle::IDD)
{
}

//-----------------------------------------------------------------------------
/*
 */
TestDlgDumpButtonStyle::~TestDlgDumpButtonStyle()
{
}

//-----------------------------------------------------------------------------
/*This member function performs special processing when the dialog box is
  initialized during the Create(), CreateIndirect(), or DoModal() calls, which occur
  immediately before the dialog box is displayed.
 */
BOOL TestDlgDumpButtonStyle::OnInitDialog()
{
TRACE("TestDlgDumpButtonStyle::OnInitDialog()\n");

CDialog::OnInitDialog();

//Testing creation of a button control
TRACE("\n  Testing creation of a button control\n");
UINT nStyle = BS_PUSHBUTTON    |//    0
              BS_DEFPUSHBUTTON |//    1
              BS_BOTTOM        |//  800
              BS_RIGHT         |//  200
              BS_PUSHLIKE      ;// 1000
//Output: Button style         50001A01h: BS_DEFPUSHBUTTON BS_RIGHT BS_BOTTOM BS_PUSHLIKE
if(!m_btnTest.Create(_T("Cancel"),
                    nStyle | WS_CHILD | WS_VISIBLE,
                    CRect(315,150,384,175),
                    this,
                    IDCANCEL))
  {
  TRACE(_T("  Failed to create a button!\n"));
  return false;
  }
DumpButtonStyle(m_btnTest.GetSafeHwnd());

//Testing changing button control style with SetButtonStyle()
nStyle = BS_AUTOCHECKBOX |//    3
         BS_LEFTTEXT     |//   20
         BS_CENTER       |//  300
         BS_BOTTOM       |//  800
         BS_MULTILINE    |// 2000
         BS_FLAT         ;// 8000
//Output: Button style   50001A03h: BS_AUTOCHECKBOX BS_RIGHT BS_BOTTOM BS_PUSHLIKE
//Note: successfuly changed type, but no style
TRACE(_T("  New "));
DumpButtonStyle(nStyle);
m_btnTest.SetButtonStyle(nStyle);
TRACE(_T("  Result "));
DumpButtonStyle(m_btnTest.GetSafeHwnd());

//Testing changing button control style with SetButtonStyle()
nStyle = BS_PUSHBUTTON   |//    0
         BS_LEFTTEXT     |//   20
         BS_CENTER       |//  300
         BS_BOTTOM       |//  800
         BS_MULTILINE    |// 2000
         BS_FLAT         ;// 8000
//Output: Button style   50001A00h: BS_PUSHBUTTON BS_RIGHT BS_BOTTOM BS_PUSHLIKE
TRACE(_T("  New "));
DumpButtonStyle(nStyle);
m_btnTest.SetButtonStyle(nStyle);
TRACE(_T("  Result "));
DumpButtonStyle(m_btnTest.GetSafeHwnd());

//Testing changing button control style with SetButtonStyle()
nStyle = BS_DEFPUSHBUTTON |//    1
         BS_RADIOBUTTON   |//    4
         BS_LEFTTEXT      |//   20
         BS_CENTER        |//  300
         BS_BOTTOM        |//  800
         BS_MULTILINE     |// 2000
         BS_FLAT          ;// 8000
//Output: Button style    50001A05h: BS_3STATE BS_RIGHT BS_BOTTOM BS_PUSHLIKE
//Note: BS_DEFPUSHBUTTON + BS_RADIOBUTTON = BS_3STATE
TRACE(_T("  New "));
DumpButtonStyle(nStyle);
m_btnTest.SetButtonStyle(nStyle | WS_CHILD | WS_VISIBLE);
TRACE(_T("  Result "));
DumpButtonStyle(m_btnTest.GetSafeHwnd());

//Get styles from dialog's template
TRACE(_T("\n  Template Controls\n"));
CButton* pBtn = (CButton*)GetDlgItem(IDOK);
TRACE(_T("  IDOK: "));
DumpButtonStyle(pBtn->GetSafeHwnd());
for (UINT nID = IDC_BUTTON3; nID >= IDC_PUSHBUTTON1; nID--)
  {
  TRACE(_T("  %d: "), nID);
  pBtn = (CButton*)GetDlgItem(nID);
  DumpButtonStyle(pBtn->GetSafeHwnd());
  }

//Testing changing button control style with SetWindowLong()
nStyle = BS_AUTORADIOBUTTON |//    9
         BS_LEFTTEXT        |//   20
         BS_CENTER          |//  300
         BS_TOP             |//  400
         BS_PUSHLIKE        |// 1000
         BS_MULTILINE       |// 2000
         BS_FLAT            ;// 8000
//Output Button style       5000B729h:
//BS_AUTORADIOBUTTON BS_LEFTTEXT BS_CENTER BS_TOP BS_PUSHLIKE BS_MULTILINE
//BS_RIGHTBUTTON BS_FLAT

LONG lRes = ::SetWindowLong(m_btnTest.GetSafeHwnd(),GWL_STYLE,
                            nStyle| WS_CHILD | WS_VISIBLE);
if (lRes == 0)
  TRACE(_T("\n  Failed to change button's style!\n"));
else
  {
  TRACE(_T("\n  Changed from "));
  DumpButtonStyle((UINT)lRes);
  TRACE(_T("  to new "));
  DumpButtonStyle(m_btnTest.GetSafeHwnd());
  }

//Testing changing owner-drawn button control style
nStyle = BS_AUTORADIOBUTTON |//    9
         BS_LEFTTEXT        |//   20
         BS_CENTER          |//  300
         BS_TOP             |//  400
         BS_PUSHLIKE        |// 1000
         BS_MULTILINE       |// 2000
         BS_FLAT            ;// 8000
//Output Button style       5000B729h:
//BS_AUTORADIOBUTTON BS_LEFTTEXT BS_CENTER BS_TOP BS_PUSHLIKE BS_MULTILINE
//BS_RIGHTBUTTON BS_FLAT
pBtn = (CButton*)GetDlgItem(IDC_BUTTON3);
TRACE(_T("\n  Owner-drawn "));
DumpButtonStyle(pBtn->GetSafeHwnd());
pBtn->SetButtonStyle(nStyle);
TRACE(_T("  changing to "));
DumpButtonStyle(nStyle);
TRACE(_T("  resulted in "));
DumpButtonStyle(pBtn->GetSafeHwnd());

TRACE(LOG_EOT);
return TRUE;  // return TRUE unless you set the focus to a control
// EXCEPTION: OCX Property Pages should return FALSE
}

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
/*Testing seting, retrieving and displaying button's type and style.

  See also: DumpButtonStyle()
 */
bool TestDumpButtonStyle(HWND hButton //=NULL handle of a button control
                        )
{
TRACE(_T("TestDumpButtonStyle(HWND %X)\n"), hButton);

if(::IsWindow(hButton))
  DumpButtonStyle(hButton);
else
  {
  TestDlgDumpButtonStyle dlgTest;
  dlgTest.DoModal();
  }

return true;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         2005-04-26 11:39:33  Darko Kolakovic Document groups
 *       and typo fixes
 *  3    Biblioteka1.2         2004-10-01 22:22:07  Darko           stdafx.h
 *  2    Biblioteka1.1         2003-08-29 08:51:47  Darko           new test cases
 *  1    Biblioteka1.0         2003-08-27 18:08:58  Darko
 * $
 *****************************************************************************/
