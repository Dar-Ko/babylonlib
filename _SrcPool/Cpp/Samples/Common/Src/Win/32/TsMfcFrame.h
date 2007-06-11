/*$Workfile: TsMfcFrame.h$: header file
  $Revision: 5$ $Date: 2007-06-11 17:00:32$
  $Author: Darko Kolakovic$

  Interface of the main frame

  Darko Kolakovic Jan. 2k Compiled with MSVC++ 4.0
*/

// Group=Examples

#ifndef _TSMFCFRAME_H_
  //$Workfile: TsMfcFrame.h$ sentry
  #define _TSMFCFRAME_H_

/////////////////////////////////////////////////////////////////////////////
/*Interface of the CTestMainFrame class.

  Note: Microsoft Windows specific (Win32) 
        and uses Microsoft Foundation Library (MFC).
 */
class CTestMainFrame : public CFrameWnd
{
public:
  CTestMainFrame();
  DECLARE_DYNCREATE(CTestMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTestMainFrame)
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual ~CTestMainFrame();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
  //{{AFX_MSG(CTestMainFrame)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#endif //_TSMFCFRAME_H_
////////////////////////////////////////////////////////////////////////////////
/*
  $Log: 
   5    Biblioteka1.4         2007-06-11 17:00:32  Darko Kolakovic Windows MFC
        application
   4    Biblioteka1.3         2007-06-11 16:05:05  Darko Kolakovic 
   3    Biblioteka1.2         2007-05-24 11:51:26  Darko Kolakovic Formatting
   2    Biblioteka1.1         2001-07-11 22:36:33  Darko           
   1    Biblioteka1.0         2001-06-08 22:43:36  Darko           
  $
 */
