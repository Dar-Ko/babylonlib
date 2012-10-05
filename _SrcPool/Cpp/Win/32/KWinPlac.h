/*$Workfile: KWinPlac.h$: header file
  $Revision: 9$ $Date: 2005-05-01 00:35:21$
  $Author: Darko$

  Encapsulates the WINDOWPLACEMENT structure
  Copyright: CommonSoft Inc
  July '95 Darko Kolakovic
  Apr. '97 C replaced with C++ D.K.
  Dec. '97 Encapsulated in class  D.K.
  Apr. 2k  Get/SetWindowPlacement D.K.
 */
// Group=Windows

#ifndef _KWINPLAC_H_
    //$Workfile: KWinPlac.h$ sentry
  #define _KWINPLAC_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif


///////////////////////////////////////////////////////////////////////////////
//CWindowPlacement class encapsulates the WINDOWPLACEMENT structure
//
//Note: To store placement settings in the registry key instead .INI file, use
//CWinApp::SetRegistryKey(<UserKey>). The key have following form:
//    HKEY_CURRENT_USER\Software\<UserKey>\<ApplicationName>\<section>\<key>
//
//Note: Microsoft Windows specific (Win32) 
//      and uses Microsoft Foundation Library (MFC).
class CWindowPlacement : public tagWINDOWPLACEMENT
{
// Construction
public:
  CWindowPlacement();
  CWindowPlacement(CWnd* pWnd);
  CWindowPlacement(const CWindowPlacement&   Source);
  CWindowPlacement(const tagWINDOWPLACEMENT* Source);

// Attributes
public:
  CString m_strEntry;   //registry entry containing the window placement
  CString m_strSection; //registry section containing the entry
  static LPCTSTR m_szFormat;

// Operations
public:
  BOOL GetWindowPlacement(CWnd* pWnd);
  BOOL SetWindowPlacement(CWnd* pWnd) const;

// Overrides
public:
  virtual CWindowPlacement& operator=(const tagWINDOWPLACEMENT& Source);
  virtual CWindowPlacement& operator=(const CWindowPlacement&   Source);
  virtual BOOL LoadSettings(LPCTSTR lpszEntry   = NULL, LPCTSTR lpszSection = NULL);
  virtual BOOL SaveSettings(LPCTSTR lpszEntry   = NULL, LPCTSTR lpszSection = NULL);

// Implementation
public:
  virtual ~CWindowPlacement(){};
  #ifdef  _DEBUG
    virtual void Dump( CDumpContext& dc ) const;
  #endif
  void Empty();
  void SetNormalPos(const LPRECT lprtPos);
  CSize GetNormalSize() const;
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::CWindowPlacement()---------------------------------------------------------
/*Copy constructor
 */
inline CWindowPlacement::CWindowPlacement(const CWindowPlacement& Source)
{
*this = Source;
};

inline CWindowPlacement::CWindowPlacement(const tagWINDOWPLACEMENT* Source ):
   m_strEntry  ("WindowPos"),
   m_strSection("Settings")
{
*this = Source;
};

//::operator=()----------------------------------------------------------------
/*
 */
inline CWindowPlacement& CWindowPlacement::operator=(const CWindowPlacement& Source)
{
m_strEntry   = Source.m_strEntry;
m_strSection = Source.m_strSection;
*this = ((const tagWINDOWPLACEMENT)Source);
return (*this);
}

//::Empty------------------------------------------------------------------
/*Intializes an empty placement (all members equal to 0).
 */
inline void CWindowPlacement::Empty()
{
                          //length, in bytes, of the structure
length                 =sizeof(tagWINDOWPLACEMENT);
flags                  =0;//flags that control the position
showCmd                =0;//current show state of the window
ptMinPosition.x        =0;//the position of the window's
ptMinPosition.y        =0;//top-left corner when the window is minimized
ptMaxPosition.x        =0;//the position of the window's
ptMaxPosition.y        =0;//top-left corner when the window is maximized
rcNormalPosition.left  =0;//the window’s coordinates when
rcNormalPosition.top   =0;//the window is in the normal position.
rcNormalPosition.right =0;
rcNormalPosition.bottom=0;
}

//::GetNormalSize()------------------------------------------------------------
/*Get the window's size when the window is in the restored (normal) position.
 */
inline CSize CWindowPlacement::GetNormalSize() const
{
return CSize(rcNormalPosition.right-rcNormalPosition.left,
             rcNormalPosition.bottom-rcNormalPosition.top);
}

//::SetNormalPos------------------------------------------------------------------
/*Set the the window's position in client coordinates
 */
inline void CWindowPlacement::SetNormalPos(const LPRECT lprtPos //[in] new
                                           //window’s coordinates
                                           )
{
rcNormalPosition.left  =lprtPos->left  ;//the window’s coordinates when
rcNormalPosition.top   =lprtPos->top   ;//the window is in the normal position.
rcNormalPosition.right =lprtPos->right ;
rcNormalPosition.bottom=lprtPos->bottom;
}

//::GetWindowPlacement---------------------------------------------------------
/*Retrieves the show state and the normal (restored), minimized, and maximized
  positions of a window.
  If the function succeeds, the return value is TRUE.
  If the function fails, the return value is FALSE. To get extended error
  information, call GetLastError().
 */
inline BOOL CWindowPlacement::GetWindowPlacement(CWnd* pWnd //[in] pointer to
                                                 //window object
                                                 )
{
if (!::IsWindow(pWnd->GetSafeHwnd()))
  return FALSE;
return pWnd->GetWindowPlacement((WINDOWPLACEMENT*)this);
}

//:SetWindowPlacement()--------------------------------------------------------
/*The SetWindowPlacement member function sets the show state and the restored,
  minimized, and maximized positions of the specified window.
  If the function succeeds, the return value is TRUE.
  If the function fails, the return value is FALSE. To get extended error
  information, call GetLastError().

  Example:
    int CMyDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
      {
      if (CDialog::OnCreate(lpCreateStruct) == -1)
          return -1;
      CWindowPlacement wpPos;
        //Read window placement
      if (wpPos.LoadSettings())
        {
        wpPos.SetWindowPlacement(this);
        }
      return 0;
      }
 */
inline BOOL CWindowPlacement::SetWindowPlacement(CWnd* pWnd //[in] pointer
                                                 //to window object
                                                 ) const
{
if (!::IsWindow(pWnd->GetSafeHwnd()))
  return FALSE;
return pWnd->SetWindowPlacement((WINDOWPLACEMENT*)this);
}

///////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif //_KWINPLAC_H_

///////////////////////////////////////////////////////////////////////////////
  // This makes ClassWizard happy
  //{{AFX_VIRTUAL(CWindowPlacement)
  //}}AFX_VIRTUAL
  //{{AFX_MSG(CWindowPlacement)
  //}}AFX_MSG
  //{{AFX_MSG_MAP(CWindowPlacement)
  //}}AFX_MSG_MAP

/*****************************************************************************
 * $Log: 
 *  9    Biblioteka1.8         2005-05-01 00:35:21  Darko           Comment
 *  8    Biblioteka1.7         2005-04-26 11:35:51  Darko Kolakovic Document groups
 *       and typo fixes
 *  7    Biblioteka1.6         2005-04-04 21:57:25  Darko           comments
 *  6    Biblioteka1.5         2003-09-03 15:02:39  Darko           Unicode
 *  5    Biblioteka1.4         2002-01-24 19:22:33  Darko           Updated
 *       comments
 *  4    Biblioteka1.3         2001-08-19 23:56:20  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 22:53:33  Darko           
 *  2    Biblioteka1.1         2001-06-08 23:52:31  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 16:04:13  Darko           
 * $
 *****************************************************************************/
