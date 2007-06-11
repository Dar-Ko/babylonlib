/*$Workfile: TsMfcDoc.h$: header file
  $Revision: 6$ $Date: 2007-06-11 17:00:45$
  $Author: Darko Kolakovic$

  Interface of the application's document

  Darko Kolakovic Jan. 2k Compiled with MSVC++ 4.0
*/

// Group=Examples

#ifndef _TSMFCDOC_H_
  //$Workfile: TsMfcDoc.h$ sentry
  #define _TSMFCDOC_H_

/////////////////////////////////////////////////////////////////////////////
/*Interface of the CTestDoc class.

  Note: Microsoft Windows specific (Win32) 
        and uses Microsoft Foundation Library (MFC).
 */
class CTestDoc : public CDocument
{
protected: // create from serialization only
  CTestDoc();
  DECLARE_DYNCREATE(CTestDoc)

// Attributes
public:

// Operations
public:
  BOOL SetText(LPCTSTR lpszText);
  BOOL AppendText(LPCTSTR lpszText);

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTestDoc)
  public:
  virtual BOOL OnNewDocument();
  virtual void Serialize(CArchive& ar);
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual ~CTestDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
  //{{AFX_MSG(CTestDoc)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#endif //_TSMFCDOC_H_
////////////////////////////////////////////////////////////////////////////////
/*
  $Log: 
   6    Biblioteka1.5         2007-06-11 17:00:45  Darko Kolakovic Windows MFC
        application
   5    Biblioteka1.4         2007-06-11 16:28:58  Darko Kolakovic 
   4    Biblioteka1.3         2007-06-11 16:05:47  Darko Kolakovic 
   3    Biblioteka1.2         2007-05-24 11:51:34  Darko Kolakovic Formatting
   2    Biblioteka1.1         2001-07-11 22:36:55  Darko           
   1    Biblioteka1.0         2001-06-08 22:43:55  Darko           
  $
 */
