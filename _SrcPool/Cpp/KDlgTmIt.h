/*$Workfile: KDlgTmIt.h$: header file
  $Revision: 1.2 $ $Date: 2002/09/10 15:22:21 $
  $Author: ddarko $
  
  Encapsulates DLGITEMTEMPLATE structure
  Copyright (c) 1996 Microsoft Corporation. All rights reserved.
  (see the end of the file for copyright grants)
  Written by Sridhar Madhugiri
  Mar. 98 Cosmetic changes D.K.
  Mar. 2k Separate class D.K.
 */ 

#ifndef _KDLGTMIT_H_
    //KDlgTmIt.h sentry
  #define _KDLGTMIT_H_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

// These values can be used for specifying the standard controls.
// They can also be specified by their names passed as strings
//
// Note: Microsoft Windows specific (Win).
enum ID_STDCONTROL
  {
  IDCTRL_FIRST    =0x0080,                //first control ID
  IDCTRL_BUTTON   =0x0080,                //Button
  IDCTRL_EDIT     =0x0081,                //Edit
  IDCTRL_STATIC   =0x0082,                //Static
  IDCTRL_LISTBOX  =0x0083,                //List box
  IDCTRL_SCROLLBAR=0x0084,                //Scroll bar
  IDCTRL_COMBOBOX =0x0085,                //Combo box
  IDCTRL_LAST     =IDCTRL_COMBOBOX
  };

/////////////////////////////////////////////////////////////////////////////
// Map functions to UNICODE or ANSI depending on the build.
// the functions with out the W or A suffix can be used and
// type of string passed in depends on the build
// The W or A function can also be called as long as the
// correct type of string is passed in.

#ifndef _KDLGTMPL_H_
#ifdef UNICODE
  #define SetCaption      SetCaptionW
  #define SetControlClass SetControlClassW
  #define SetCaption      SetCaptionW
  #define SetClassName    SetClassNameW
  #define SetFontInfo     SetFontInfoW
  #define SetMenuName     SetMenuNameW
#else
  #define SetCaption      SetCaptionA
  #define SetControlClass SetControlClassA
  #define SetCaption      SetCaptionA
  #define SetClassName    SetClassNameA
  #define SetFontInfo     SetFontInfoA
  #define SetMenuName     SetMenuNameA
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
/*CDlgItemTempl class encapsulates DLGITEMTEMPLATE structure
  In a dialog box template, the DLGITEMTEMPLATE structure is always
  immediately followed by three variable-length arrays specifying the
  class, title, and creation data for the control. Each array consists
  of one or more 16-bit elements. DLGITEMTEMPLATE defined is in WinUser.h

     typedef struct
       {
       DWORD style;          //the control's windows and control style
       DWORD dwExtendedStyle;//extended styles for a window
       short x;  //the upper-left corner position in dialog box units
       short y;  //the upper-left corner position in dialog box units
       short cx; //the width, in dialog box units, of the control
       short cy; //the height, in dialog box units, of the control
       WORD  wID;//the control identifier
       } DLGITEMTEMPLATE;

  TODO: DLGITEMTEMPLATEEX

  See Also: Serialization operator>>

  Note: Microsoft Windows specific (Win).
 */
class CDlgItemTempl : public CObject
{
// Construction
public:
    CDlgItemTempl();

    void ResetControlClass();
    void ResetCaption();
    void ResetInitData();
    void Reset();
    void SetDlgItemTemplate(WORD  x, WORD  y, WORD  cx, WORD  cy,
                          WORD  wID, DWORD style, DWORD dwExtendedStyle);
    DWORD  GetStyle();
    DWORD  GetExtendedStyle();
    CPoint GetPosition();
    CSize  GetSize();
    WORD   GetID();
    DWORD  SetStyle(DWORD style);
    DWORD  SetExtendedStyle(DWORD dwExtendedStyle);
    CPoint SetPosition(WORD x, WORD y);
    CSize  SetSize(WORD cx, WORD cy);
    WORD   SetID(const WORD& wID);
    WORD   GetDlgItemTemplate(DLGITEMTEMPLATE** ppDlgItemHeader);
    const WCHAR* GetControlClass();
    const WCHAR* GetCaption();
    BOOL SetControlClassAtom(WORD controlClass);
    BOOL SetCaptionA(const char* szCaption);
    BOOL SetControlClassA(const char* controlClass = NULL);
    BOOL SetCaptionW(const WCHAR* szCaption);
    BOOL SetControlClassW(const WCHAR* controlClass = NULL);
    BOOL SetCaptionID(WORD wResourceID);
    WORD GetInitData(const WORD** ppInitData);
    BOOL SetInitData(WORD nInitDataLength, const WORD* pInitData);
    BOOL CreateControl(WORD  x, WORD  y, WORD  cx, WORD  cy, WORD  wID, DWORD style,
        WORD controlClass, const TCHAR* szCaption = NULL, WORD nInitDataLength = 0,
        WORD* pInitData = NULL, DWORD dwExtendedStyle = 0);
    BOOL CreateControl( WORD  x, WORD  y, WORD  cx, WORD  cy, WORD  wID, DWORD style,
        const TCHAR* controlClass, const TCHAR* szCaption = NULL, WORD nInitDataLength = 0,
        WORD* pInitData = NULL, DWORD dwExtendedStyle = 0);
    BOOL CreateControl( WORD  x, WORD  y, WORD  cx, WORD  cy, WORD  wID, DWORD style,
        const TCHAR* controlClass, WORD wResourceID, WORD nInitDataLength = 0,
        WORD* pInitData = NULL, DWORD dwExtendedStyle = 0);
    BOOL CreateControl(WORD  x, WORD  y, WORD  cx, WORD  cy, WORD  wID, DWORD style,
        WORD controlClass, WORD wResourceID, WORD nInitDataLength = 0,
        WORD* pInitData = NULL, DWORD dwExtendedStyle = 0);
    void CreateControlInMemory(BYTE* pMemory);
    BOOL CreateControlFromMemory(BYTE* p);

// Attributes
public:
    UINT GetLength();
protected:
    DLGITEMTEMPLATE m_dlgItemTemplate;
    UINT  m_nControlClassLength;
    BYTE* m_pControlClass;
    UINT  m_nCaptionLength;
    BYTE* m_pCaption;
    UINT  m_nInitDataLength;
    BYTE* m_pInitData;

// Operations
public:

// Implementation
public:
  #ifdef _DEBUG
      void Dump( CDumpContext& dc ) const;
  #endif
    virtual ~CDlgItemTempl();
    virtual void Serialize( CArchive& ar );

protected:
    BOOL ValidControl(WORD wValue);
    ULONG AlignDWord(ULONG uLong);

// Following sets up the structures required for adding runtime
// information to the embedded class
// Normally done for by DECLARE_SERIAL
protected:
    static CRuntimeClass* __stdcall _GetBaseClass();

public:
        static  CRuntimeClass classCDlgItemTempl;
        virtual CRuntimeClass* GetRuntimeClass() const;
        static CObject* __stdcall CreateObject();
        friend CArchive& __stdcall operator>>(CArchive& ar, CDlgItemTempl* &pOb);

//  DECLARE_SERIAL(CDlgItemTempl)
};

///////////////////////////////////////////////////////////////////////////////
    // Following makes ClassWizard happy
    //{{AFX_VIRTUAL(CDlgItemTempl)
    //}}AFX_VIRTUAL
    //{{AFX_MSG(CDlgItemTempl)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG

///////////////////////////////////////////////////////////////////////////////
// Inlines


//::ResetControlClass------------------------------------------------------------------
/*$Description
 */
inline void CDlgItemTempl::ResetControlClass()
{
    if (m_pControlClass)
       delete []m_pControlClass;

    m_pControlClass         = NULL;
    m_nControlClassLength   = 0;
}

//::ResetCaption------------------------------------------------------------------
/*$Description
 */
inline void CDlgItemTempl::ResetCaption()
{
    if (m_pCaption)
       delete []m_pCaption;

    m_pCaption          = NULL;
    m_nCaptionLength    = 0;
}

//::ResetInitData------------------------------------------------------------------
/*$Description
 */
inline void CDlgItemTempl::ResetInitData()
{
    if (m_pInitData)
        delete []m_pInitData;

    m_pInitData = NULL;
    m_nInitDataLength = 0;
}

//::GetStyle------------------------------------------------------------------
/*$Description
 */
inline DWORD CDlgItemTempl::GetStyle()
  {
  return m_dlgItemTemplate.style;
  }

//::GetExtendedStyle------------------------------------------------------------------
/*$Description
 */
inline DWORD CDlgItemTempl::GetExtendedStyle()
  {
  return m_dlgItemTemplate.dwExtendedStyle;
  }

//::GetPosition------------------------------------------------------------------
/*$Description
 */
inline CPoint CDlgItemTempl::GetPosition()
  {
  return CPoint(m_dlgItemTemplate.x, m_dlgItemTemplate.y);
  }

//::GetSize------------------------------------------------------------------
/*$Description
 */
inline CSize CDlgItemTempl::GetSize()
  {
  return CSize(m_dlgItemTemplate.cx, m_dlgItemTemplate.cy);
  }

//::GetID------------------------------------------------------------------
/*$Description
 */
inline WORD CDlgItemTempl::GetID()
  {
  return m_dlgItemTemplate.id;
  }

//::SetStyle------------------------------------------------------------------
/*$Description
 */
// Argument         : DWORD style
inline DWORD CDlgItemTempl::SetStyle(DWORD style)
    {
        DWORD oldStyle = m_dlgItemTemplate.style;
        m_dlgItemTemplate.style = style;
        return oldStyle;
    }

//::SetExtendedStyle------------------------------------------------------------------
/*$Description
 */
// Argument         : DWORD dwExtendedStyle
inline DWORD CDlgItemTempl::SetExtendedStyle(DWORD dwExtendedStyle)
    {
        DWORD oldExtendedStyle = m_dlgItemTemplate.dwExtendedStyle;
        m_dlgItemTemplate.style = dwExtendedStyle;
        return oldExtendedStyle;
    }

//:SetPosition------------------------------------------------------------------
/*$Description
 */
// Argument         : WORD x
// Argument         : WORD y
inline CPoint CDlgItemTempl::SetPosition(WORD x, WORD y)
    {
        CPoint oldPosition = CPoint(m_dlgItemTemplate.x, m_dlgItemTemplate.y);
        m_dlgItemTemplate.x = x;
        m_dlgItemTemplate.y = y;
        return oldPosition;
    }

//::SetSize------------------------------------------------------------------
/*$Description
 */
// Argument         : WORD cx
// Argument         : WORD cy
inline CSize CDlgItemTempl::SetSize(WORD cx, WORD cy)
    {
        CSize oldSize = CSize(m_dlgItemTemplate.cx, m_dlgItemTemplate.cy);
        m_dlgItemTemplate.cx = cx;
        m_dlgItemTemplate.cy = cy;
        return oldSize;
    }

//::SetID------------------------------------------------------------------
/*$Description
 */
// Argument         : const WORD& wID
inline WORD CDlgItemTempl::SetID(const WORD& wID)
{
WORD oldID = m_dlgItemTemplate.id; m_dlgItemTemplate.id = wID;
return oldID;
}

//::GetDlgItemTemplate------------------------------------------------------------------
/*$Description
 */
// Argument         : DLGITEMTEMPLATE** ppDlgItemHeader
inline WORD CDlgItemTempl::GetDlgItemTemplate(DLGITEMTEMPLATE** ppDlgItemHeader)
    {
        *ppDlgItemHeader = &m_dlgItemTemplate;
        return (WORD) sizeof(m_dlgItemTemplate);
    }

//::GetControlClass------------------------------------------------------------------
/*$Description
 */
inline const WCHAR* CDlgItemTempl::GetControlClass()
  {
  return (WCHAR*)m_pControlClass;
  }

//::GetCaption------------------------------------------------------------------
/*$Description
 */
inline const WCHAR* CDlgItemTempl::GetCaption()
  {
  return (WCHAR*)m_pCaption;
  }

//::GetInitData------------------------------------------------------------------
/*$Description
 */
// Argument         : const WORD** ppInitData
inline WORD CDlgItemTempl::GetInitData(const WORD** ppInitData)
    {
        *ppInitData = (WORD*) m_pInitData;
        return (WORD)m_nInitDataLength;
    }

//::GetLength------------------------------------------------------------------
/*$Description
 */
inline UINT CDlgItemTempl::GetLength()
  {
    return AlignDWord(sizeof(m_dlgItemTemplate) +
                          m_nControlClassLength     +
                          m_nCaptionLength          +
                          m_nInitDataLength         +
                          sizeof(WORD)
                    );
    }


//::ValidControl------------------------------------------------------------------
/*$Description
 */
// Argument         : WORD wValue
inline BOOL CDlgItemTempl::ValidControl(WORD wValue)
  {
  return (wValue >= IDCTRL_FIRST && wValue <= IDCTRL_LAST);
  }

//::AlignDWord------------------------------------------------------------------
/*$Description
 */
// Argument         : ULONG uLong
inline ULONG CDlgItemTempl::AlignDWord(ULONG uLong)
  {
  return ((uLong + 3) & ~3);
  }

///////////////////////////////////////////////////////////////////////////////
// Helpers

//operator>>()-----------------------------------------------------------------
/*Loads the CDlgTempl object from the archive.

  Note: uses Microsoft Fundation Library (MFC).
 */
inline CArchive& AFXAPI operator>>(CArchive& ar, CDlgItemTempl* &pOb)
{
pOb = (CDlgItemTempl*) ar.ReadObject((&CDlgItemTempl::classCDlgItemTempl));
return ar;
}

///////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //_KDLGTMIT_H_

/*Microsoft legal stuff
THE INFORMATION AND CODE PROVIDED HEREUNDER (COLLECTIVELY REFERRED TO
AS "SOFTWARE") IS PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. IN
NO EVENT SHALL MICROSOFT CORPORATION OR ITS SUPPLIERS BE LIABLE FOR
ANY DAMAGES WHATSOEVER INCLUDING DIRECT, INDIRECT, INCIDENTAL,
CONSEQUENTIAL, LOSS OF BUSINESS PROFITS OR SPECIAL DAMAGES, EVEN IF
MICROSOFT CORPORATION OR ITS SUPPLIERS HAVE BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES. SOME STATES DO NOT ALLOW THE EXCLUSION OR
LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES SO THE
FOREGOING LIMITATION MAY NOT APPLY.

This Software may be copied and distributed royalty-free subject to
the following conditions:

1. You must copy all Software without modification and must include
   all pages, if the Software is distributed without inclusion in your
   software product. If you are incorporating the Software in
   conjunction with and as a part of your software product which adds
   substantial value, you may modify and include portions of the
   Software.

2. You must place all copyright notices and other protective
   disclaimers and notices contained on the Software on all copies of
   the Software and your software product.

3. Unless the Software is incorporated in your software product which
   adds substantial value, you may not distribute this Software for
   profit.

4. You may not use Microsoft's name, logo, or trademarks to market
   your software product.

5. You agree to indemnify, hold harmless, and defend Microsoft and its
   suppliers from and against any claims or lawsuits, including
   attorneys' fees, that arise or result from the use or distribution
   of your software product and any modifications to the Software.

*/

/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         1/29/02 11:20:50 PM  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         1/25/02 4:56:59 PM   Darko           Updated
 *       comments
 *  4    Biblioteka1.3         8/19/01 11:53:22 PM  Darko           Butyfier
 *  3    Biblioteka1.2         7/11/01 10:51:17 PM  Darko           
 *  2    Biblioteka1.1         6/8/01 11:50:33 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 3:56:21 PM   Darko           
 * $
 *****************************************************************************/
