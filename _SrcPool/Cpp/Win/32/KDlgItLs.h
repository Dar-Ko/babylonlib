/*$Workfile: KDlgItLs.h$: header file
  $Revision: 7$ $Date: 2003-09-22 21:25:58$
  $Author: Darko$

  A list with resizable controls
  Copyright: CommonSoft Inc
  Apr. 2k Darko Kolakovic
 */ 

#ifndef _KDLGITLS_H_
    //KDlgItLs.h sentry
  #define _KDLGITLS_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#include <AfxTempl.h> //CArray template
#include "KDlgItem.h" //CDlgItemResizable class

///////////////////////////////////////////////////////////////////////////////
//CDlgItemResizableList class handles a list of the resizable dialog controls
//
//Note: uses Microsoft Fundation Library (MFC).
//      Microsoft Windows specific (Win).
class CDlgItemResizableList
{
// Construction
public:
  CDlgItemResizableList();
  CDlgItemResizableList(const CWnd* pParent);
  CDlgItemResizableList(HWND hParent);

// Attributes
//protected:
public:
  HWND m_hParent;     //handle of the parent window
  CSize m_sizeParent; //dimensions of parent's client area
  CArray<CDlgItemResizable, CDlgItemResizable> m_arrayDlgItem;  //an array of the dialog controls

// Operations
public:
  HWND SetParent(const CWnd* pParent);
  HWND SetParent(HWND hParent);
  void SetSize(HWND hParent);
  int Add(const CDlgItemResizable& cdlgiResizable);
  int Add(const UINT& nCtrlID , const DWORD& dwStyle = CDlgItemResizable::ALL_FIXED);
  int Add(const HWND& hwndCtrl, const DWORD& dwStyle = CDlgItemResizable::ALL_FIXED);
  int EnumerateControls();
  int GetElementCount() const;
  CDlgItemResizable& operator[](int iIndex);
  CDlgItemResizable  operator[](int iIndex) const;

// Implementation
public:
  BOOL OnInitDialog(CWnd* pParent);
// Overrides
public:
  virtual ~CDlgItemResizableList();
  virtual void Resize(const CSize& sizeNew);
  virtual void OnSize(UINT nType, int cx, int cy);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::SetParent()----------------------------------------------------------------
/*Specifies the parent window of the control windows. If parent is not a window,
  function returns NULL and value of member m_hParent remains unchanged.

  Example:
    class CMyDialog: public CDialog
      {
      ...
      CDlgItemResizableList m_arrControlList;
      virtual BOOL OnInitDialog();
      ...
      };
    BOOL CMyDialog::OnInitDialog() 
      {
      BOOL bResult = CDialog::OnInitDialog();
        //Initialize control list
      m_arrControlList.SetParent(STATIC_DOWNCAST(CWnd,this));
      m_arrControlList.SetSize(m_hWnd);
      m_arrControlList.Add(IDOK);
      return bResult;
      }
 */
inline HWND CDlgItemResizableList::SetParent(const CWnd* pParent //container window
                                             )
{
ASSERT(pParent!= NULL);
HWND hParent = pParent->GetSafeHwnd();
if (hParent != NULL)
  m_hParent = hParent;
return hParent;
}

inline HWND CDlgItemResizableList::SetParent(HWND hParent)
{
if (::IsWindow(hParent))
  return (m_hParent = hParent);
else
  return NULL;
}

//::SetSize()------------------------------------------------------------------
/*Get size of the client area of the container window and save it.
 */
inline void CDlgItemResizableList::SetSize(HWND hParent //handel of the conatiner window
                                           )
{
ASSERT(::IsWindow(hParent));
CRect rect;
if(::GetClientRect(hParent,rect))
  m_sizeParent = rect.Size();
}

//::GetElementCount()----------------------------------------------------------
/*Returns the number of items in of the resizable controls list. If the list 
  is empty, returns zero.
 */
inline int CDlgItemResizableList::GetElementCount() const
{
return m_arrayDlgItem.GetSize();
}

//::operator[]()---------------------------------------------------------------
/*Sets or gets a control information at the specified position in 
  the resizable controls list. 
 */
inline CDlgItemResizable& CDlgItemResizableList::operator[](int iIndex //zero-based 
                                                            //index of the list item 
                                                            )
{
return m_arrayDlgItem.ElementAt(iIndex);
}

inline CDlgItemResizable  CDlgItemResizableList::operator[](int iIndex) const
{
return m_arrayDlgItem.GetAt(iIndex);
}


//::Resize()-------------------------------------------------------------------
/*Change position and size of the listed controls.

  See Also: CDlgItemResizable::Resize()
 */
inline void CDlgItemResizableList::Resize(const CSize& sizeNew //new size of the 
                                //bounding rectangle, usually parent's client area
                                          )
{
int i = 0;
while (i < m_arrayDlgItem.GetSize())
  {
  ASSERT(::IsWindow(m_hParent)); //Object is not initialized properly. See SetParent();
  m_arrayDlgItem[i].Resize(sizeNew,m_sizeParent);
  i++;
  }

}

//::OnInitDialog()-------------------------------------------------------------
/*Call this function to initialize this object during the creation of the 
  container window, but the container window is displayed. 
  
  Returns TRUE in case of success, otherwise returns FALSE. Note that
  meaning of return vale is different than in CDialog::OnInitDialog().

  Example:
    class CMyDialog: public CDialog
      {
      ...
      CDlgItemResizableList m_arrControlList;
      virtual BOOL OnInitDialog();
      ...
      };
    BOOL CMyDialog::OnInitDialog() 
      {
      BOOL bResult = CDialog::OnInitDialog();
        //Initialize control list
      m_arrControlList.OnInitDialog(STATIC_DOWNCAST(CWnd,this));
      m_arrControlList.Add(ID_BUTTON1);
      return bResult;
      }

 */
inline BOOL CDlgItemResizableList::OnInitDialog(CWnd* pParent //container window
                                                )
{
if(SetParent(pParent) != NULL) //Set m_hParent
  {
  SetSize(m_hParent);
  return TRUE;
  }
return FALSE;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //_KDLGITLS_H_

///////////////////////////////////////////////////////////////////////////////
  // Following makes ClassWizard happy
  //{{AFX_VIRTUAL(CDlgItemResizable)
  //}}AFX_VIRTUAL
  //{{AFX_MSG(CDlgItemResizable)
    // NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG

