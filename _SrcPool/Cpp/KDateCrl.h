/*$Workfile: H:\_SrcPool\Cpp\KDateCrl.h$: header file
  $Revision: 1.1 $ $Date: 2002/09/06 22:09:08 $
  $Author: ddarko $

  Date Control
  Copyright: CommonSoft Inc.
  Dec. 97 Darko Kolakovic
  Mar. 2K GetModify() D.K.
 */ 

#ifndef _KDATECRL_H_
    //KDateCrl.h sentry
  #define _KDATECRL_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef __AFXWIN_H__
	#include <AfxWin.h>
#endif
#include <AfxCmn.h> //CSpinButtonCtrl class

#ifdef _DEBUG
  static char _szDateCtrlTag[] = "KDateCrl.h";
  #undef THIS_FILE
  #define THIS_FILE _szDateCtrlTag
#endif

/////////////////////////////////////////////////////////////////////////////
// CDateCtrl notification structure
//
// Note: Microsoft Windows specific (Win).
typedef struct tagDDATE_RETURN
  {
  NMHDR hdr;   //information about a notification message
  int   iDay;  //current date
  int   iMonth;//current date
  int   iYear; //current date
} DDATE_RETURN;

/////////////////////////////////////////////////////////////////////////////
/*CDateCtrl Date Control allows to edit date.
  Right mouse button have same functionality as Enter key.

  Note: uses Microsoft Fundation Library (MFC).
 */
class CDateCtrl : public CWnd
{
// Construction
public:
	CDateCtrl();
  CDateCtrl(const POINT& pos,      //position in client coordinates of pParentWnd.
            CWnd* pParentWnd,      //the parent window
            UINT nID = IDD_DDATEEDITCTRL);//the ID of the child window
  DECLARE_DYNAMIC(CDateCtrl)

// Attributes
public:
   enum               //control IDs
     {
     IDD_DDATEEDITCTRL = 31415,
     IDC_DDSPINMONTH   = 100,
     IDC_DDEDITMONTH   = 101,
     IDC_DDSPINYEAR    = 200,
     IDC_DDEDITYEAR    = 201,
     IDC_DDDAYOFWEEK   = 300
     };
  static LPCTSTR DCTRLSTRCLASSNAME; //Window class name
  CFont           m_Font;    //Current font
  int             m_dxFont;  //Width of the current font
  int             m_dyFont;  //Height of the current font
    //Current date
  int             m_iDay;
  int             m_iMonth;
  int             m_iYear;
	//{{AFX_DATA(CDateCtrl)
  CSpinButtonCtrl m_spinMonth;
  CSpinButtonCtrl m_spinYear;
  CEdit           m_editMonth;
  CEdit           m_editYear;
  CStatic         m_staticDayOfWeek;
	//}}AFX_DATA
protected:
  HACCEL      m_hAccel;      //Handle to accelerator table
  CPoint      m_posDay;      //Position of the Day Table
  BOOL        m_bHasBeenModified; //TRUE if data has been changed
private:
  static BOOL m_bRegistered; //'Wnd class registered' flag
  BOOL        m_bAutoDelete; //'Delete itself from heap' flag
  UINT        m_nFirstDay;   //Day of the week [0,6] of 1st day of the current month
  UINT        m_nLastDay ;   //Last day of the month [28,31]
// Operations
public:
    //Sets the control’s current font to the specified font
  void SetFont(int nPointSize,        //font height in tenths of a point
               LPCTSTR lpszFaceName); //the typeface name

  CFont* GetFont()     //Gets the current font for this control.
    {return &m_Font;};
  BOOL IsLeapYear(const int& iYear); //Check leap year
  BOOL GetModify() const;

private:
  void SelectDay(CDC* pDC, UINT nDayOfMonth); //Highlight the day [0,30]
  void SetFirstAndLastDay();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	public:
	virtual BOOL Create(const POINT& pos=CPoint(0,0),//position in client coordinates of pParentWnd.
                      CWnd* pParentWnd=NULL ,      //the parent window
                      UINT nID = IDD_DDATEEDITCTRL,//the ID of the child window
                      DWORD dwStyle=WS_VISIBLE   | //the window style attributes
                                    WS_BORDER    );

// Implementation
public:
	virtual ~CDateCtrl();
  static BOOL RegisterClass();  //Register wnd class
protected:
    //Control window main procedure
  static LRESULT CALLBACK DCtrlWndProc(HWND hWnd, UINT uiMsg,
                              WPARAM wParam, LPARAM lParam);

	// Generated message map functions
protected:
	//{{AFX_MSG(CDateCtrl)
	afx_msg void OnNcDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
 	afx_msg void OnOK();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif //_KDATECRL_H_
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         1/29/02 10:20:01 PM  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         1/25/02 3:56:32 PM   Darko           Updated
 *       comments
 *  4    Biblioteka1.3         8/19/01 10:52:30 PM  Darko           Butyfier
 *  3    Biblioteka1.2         7/11/01 9:50:22 PM   Darko           
 *  2    Biblioteka1.1         6/8/01 10:49:24 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 2:55:46 PM   Darko           
 * $
 *****************************************************************************/
