#if !defined(AFX_MYPROPERTYSHEET_H__E8F99403_03C8_11D4_AD28_00606767A9D2__INCLUDED_)
#define AFX_MYPROPERTYSHEET_H__E8F99403_03C8_11D4_AD28_00606767A9D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyPropertySheet.h : header file
//

#include "KPropShR.h" //CPropertySheetResizable class
#include "MyPage1.h"
#include "MyPage2.h"
#include "MyPage3.h"
#include "MyPage4.h"

/////////////////////////////////////////////////////////////////////////////
// MyPropertySheet

//##ModelId=3ECE52E600AB
class MyPropertySheet : public CPropertySheetResizable
{
	DECLARE_DYNAMIC(MyPropertySheet)

// Construction
public:
	//##ModelId=3ECE52E600C9
  MyPropertySheet();
	//##ModelId=3ECE52E600CA
	MyPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	//##ModelId=3ECE52E600DE
	MyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

	//##ModelId=3ECE52E600FC
  MyPage1 m_Page1;
	//##ModelId=3ECE52E60110
  MyPage2 m_Page2;
	//##ModelId=3ECE52E60125
  MyPage3 m_Page3;
	//##ModelId=3ECE52E60139
  MyPage4 m_Page4;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyPropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	//##ModelId=3ECE52E60142
	virtual ~MyPropertySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(MyPropertySheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROPERTYSHEET_H__E8F99403_03C8_11D4_AD28_00606767A9D2__INCLUDED_)
