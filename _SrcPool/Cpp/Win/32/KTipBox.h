/*$Workfile: KTipBox.h$: header file
  $Revision: 7$ $Date: 2005-04-26 11:35:45$
  $Author: Darko Kolakovic$

  Simple Text Tip Window
  Copyright: CommonSoft Inc
  Jun '97 Darko Kolakovic
  Apr 2k overloading of operator new (exercise) D.K.
 */ 
// Group=Windows

#ifndef _KTIPTEXT_H_
  //$Workfile: KTipBox.h$ sentry
  #define _KTIPTEXT_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef __AFXWIN_H__
  #include <AfxWin.h>
#endif

  //Apr. 2k exercise with operator new  D.K.
#ifdef _DEBUG3
  #ifdef DEBUG_NEW
    #undef DEBUG_NEW
  #endif
    //Note: See KB Q143207 - Common Problems When Using STL with STD Namespace.
    //Same problem is observed with VC++ 6.0 as well and offered resolution does not work D.K.
    //In MFC operator new is defined as placement overload with arguments THIS_FILE and __LINE__
    //    #define DEBUG_NEW new(THIS_FILE, __LINE__) (see Afx.h)
    //and usually a class does not have overload for operator with those arguments.
  #define DEBUG_NEW new
#endif

///////////////////////////////////////////////////////////////////////////////
//CTipBox window shows a small box with a single text line called a tip.
//
//Note: Microsoft Windows specific (Win) and uses Microsoft Foundation Library (MFC).
class CTipBox : public CWnd
{
// Construction
public:
  CTipBox(CWnd* pParent = NULL, 
          BOOL bSelfDestroy = FALSE,
          DWORD dwStyle = WS_POPUP);
  DECLARE_DYNAMIC( CTipBox );

// Attributes
private:
  static   CString m_strClassName;
  static   BOOL m_bRegistered;     //'Wnd class registered' flag
  BOOL     m_bAutoDelete;          //'Delete itself from heap' flag
  COLORREF m_crTextColor;          //Text colors
  COLORREF m_crBkColor;  
  HBRUSH   m_hBkBrush;             //Background brush
  HFONT    m_hFont;                //Text tip font
  CFont*   m_pFontContainer;       //Allocated font
  UINT     m_nIDTimer;             //Timer ID
  int      m_iShadeSize;           //Size of the shaded region
  CWnd*    m_pParent;              //pointer to the parent window
// Operations
public:
  enum {IDT_TEXTTIP = 26788}; //Timer ID
    //Get/set colors
  void SetTextColor(COLORREF crColor,BOOL bRedraw = TRUE);
  COLORREF GetTextColor() const;
  void SetBkColor(COLORREF crColor,BOOL bRedraw = TRUE);
  COLORREF GetBkColor() const;
  void ShowTip(UINT IDS_TipText, LPPOINT lpptPos, const int& iSec = -1);
  void SetShade(int iSize = 0);
  CWnd* GetParent() const;

  #pragma warning( disable : 4290 )  // A function with exception specification is not supported yet
  //void  operator delete(void* pObject)  throw();
  //void* operator new(size_t nSize, BOOL bAutoDelete) throw (CMemoryException);
  //void  operator delete(void* pObject, BOOL bAutoDelete) throw();
  #if _MSC_VER  >= 1100 
    //void* operator new[](size_t nSize, BOOL bAutoDelete) throw (CMemoryException);
    //void  operator delete[](void* pObject) throw();
  #endif  // _MSC_VER  >= 1100

// Overrides
  #ifdef _DEBUG
    virtual void Dump(CDumpContext& dc) const;
  #endif
  virtual void ShowTip(LPCTSTR strTipText, LPPOINT lpptPos, const int& iSec = -1);
  virtual void SetFont(CFont* pNewFont = NULL);
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CTipBox)
  protected:
  //}}AFX_VIRTUAL

// Implementation
public:
  LPCTSTR RegisterClass();
  virtual ~CTipBox();

  // Generated message map functions
protected:
  //{{AFX_MSG(CTipBox)
  afx_msg void OnPaint();
  afx_msg LRESULT OnSetText( WPARAM, LPARAM lpsz );
  afx_msg void OnNcDestroy();
  afx_msg void OnTimer(UINT nIDEvent);
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg void OnDestroy();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Inlines


//::GetTextColor()-------------------------------------------------------------
/*Return stext color.
 */
inline COLORREF CTipBox::GetTextColor() const 
{
return m_crTextColor;
}

//::GetBkColor()---------------------------------------------------------------
/*Return background color.
 */
inline COLORREF CTipBox::GetBkColor() const 
{
return m_crBkColor;
}

//::SetShade()-----------------------------------------------------------------
/*Set shade depth.
 */
inline void CTipBox::SetShade(int iSize//= 0 shade size in pixels
                             )
{
m_iShadeSize = iSize;
}

//::GetParent()----------------------------------------------------------------
/*Returns pointer to the parent window.
 */
inline CWnd* CTipBox::GetParent() const
{
return m_pParent;
}

///////////////////////////////////////////////////////////////////////////////
// Memeory allocation
#ifdef LLLLL
//::operator new()-------------------------------------------------------------
/*Static function by default.

  Example:
    #include "KTipBox.h"  //CTipBox class
    void CMyView::OnEvent(const CPoint& point)
      {
      CTipBox* pNewBox = new(TRUE) CTipBox(this); //Delete itself after time-out
      pNewBox->SetFont();
      pNewBox->SetTextColor(LIGHTBLUE);
      pNewBox->SetShade(5);
      CString strZ;
      strZ.Format(_T("Tooltip"));
      CPoint ptPos = point;
      ClientToScreen(&ptPos);
      ptPos.y -= 15;
      pNewBox->ShowTip(strZ,&ptPos,2);
      }
 */
inline void* CTipBox::operator new(size_t nSize,
                                   BOOL bAutoDelete
                                  )
{
try
  {
  void* pRes = ::operator new(nSize);
  if (pRes != NULL)
    static_cast<CTipBox*>(pRes)->m_bAutoDelete = bAutoDelete;
  else
      //Older compiler versions in case of failure returns NULL without exception
    AfxThrowMemoryException();
  return pRes;
  }
catch(...) //Default operator new throws std::bad_alloc
  {
    //Convert std exception to the MFC exception
  AfxThrowMemoryException();
  }
return NULL;
}

//::operator delete()----------------------------------------------------------
/*Static function by default
 */
inline void CTipBox::operator delete(void* pObject,
                                     BOOL bAutoDelete
                                    ) throw()
{
ASSERT(pObject != NULL);
::delete pObject;
}

//::operator delete()----------------------------------------------------------
/*Static function by default
 */
inline void CTipBox::operator delete(void* pObject) throw()
{
ASSERT(pObject != NULL);
::delete pObject;
}

//Beginning with Visual C++ 5.0, the compiler supports member array new and delete 
//operators in a class declaration.
#if _MSC_VER  >= 1100 
  inline void* CTipBox::operator new [] (size_t nSize,
                                              BOOL bAutoDelete
                                              )
    {
    try
      {
      void* pRes = ::new char[nSize];
      if (pRes != NULL)
        static_cast<CTipBox*>(pRes)->m_bAutoDelete = bAutoDelete;
      else
          //Older compiler versions in case of failure returns NULL without exception
        AfxThrowMemoryException();
      return pRes;
      }
    catch(...)  //Default operator new throws std::bad_alloc
      {
        //Convert std exception to the MFC exception
      AfxThrowMemoryException();
      }
    return NULL;
    }

  inline void CTipBox::operator delete [] (void* pObject) throw()
    {
    ASSERT(pObject != NULL);
    ::delete[] pObject;
    }

#endif  //_MSC_VER  >= 1100

#endif
/////////////////////////////////////////////////////////////////////////////
#endif  //_KTIPTEXT_H_

