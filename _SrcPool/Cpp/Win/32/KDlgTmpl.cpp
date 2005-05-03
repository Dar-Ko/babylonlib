/*$Workfile: KDlgTmpl.cpp$: implementation file
  $Revision: 6$ $Date: 2003-09-22 22:26:08$
  $Author: Darko$
  
  Copyright (c) 1996 Microsoft Corporation. All rights reserved.
  Written by Sridhar Madhugiri
  of Microsoft Product Support Services, Languages Developer Support
 */ 

#ifndef __AFXWIN_H__
  #include <AfxWin.h>
#endif

#if _MFC_VER < 0x0400
  #include <WinUser.h>
#else
  #include <WinNls.h>
#endif

#include "KDlgTmpl.h" //CDlgTempl class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDlgTempl
IMPLEMENT_SERIAL(CDlgTempl, CObject, 1)

CDlgTempl::CDlgTempl() : m_hDlgTemplate( NULL ),
    m_lpDlgTemplate( NULL ),
    m_nMenuNameLength(0),
    m_nClassNameLength(0),
    m_nCaptionLength(0),
    m_pMenuName(NULL),
    m_pClassName(NULL),
    m_pCaption(NULL),
    m_nPointSize(0),
    m_nFaceNameLength(0),
    m_pFaceName(NULL)
{
    memset(&m_dlgTemplate, 0, sizeof(m_dlgTemplate));
    SetMenuNameW(NULL);
    SetClassNameW(NULL);
    SetCaptionW(NULL);
}

CDlgTempl::~CDlgTempl()
{
    ResetAll(FALSE);
}

//::ResetAll()-----------------------------------------------------------------
/*Reset the members. If the argument is TRUE it puts out a trace message before
  resetting the contents.
 */
void CDlgTempl::ResetAll(BOOL bWarn /* = TRUE*/)
{
if (bWarn)
  {
  TRACE(_T("Warning : Resetting Old Template\n"));
  }

if (m_lpDlgTemplate)
  {
  UnlockTemplate();
  m_lpDlgTemplate = NULL;
  }

if (m_hDlgTemplate)
  {
  LocalFree(m_hDlgTemplate);
  m_hDlgTemplate = NULL;
  }

if (m_pMenuName)
  delete []m_pMenuName;

if (m_pClassName)
  delete []m_pClassName;

if (m_pCaption)
  delete []m_pCaption;

if (m_pFaceName)
  delete []m_pFaceName;

  //Delete mapped objects
for(POSITION pos = m_controlList.GetHeadPosition();
    pos != NULL;
    pos = m_controlList.GetHeadPosition())
  {
  CObject* p = m_controlList.GetAt(pos);
  m_controlList.RemoveAt(pos);
  delete p;
  }
}

//::Serialize()----------------------------------------------------------------
/*Reads or writes this template object from or to an archive.
 */
void CDlgTempl::Serialize( CArchive& ar )
{
if (ar.IsLoading())
  {
    ResetAll();
    ar.Read(&m_dlgTemplate, sizeof(m_dlgTemplate));

    ar >> m_nMenuNameLength;
    m_pMenuName = new BYTE[m_nMenuNameLength];
    if (!m_pMenuName)
    {
        ResetAll(FALSE);
        TRACE(_T("Failure : %s,%d - Unable To Allocate Memory\n"), __FILE__, __LINE__);
    }
    ar.Read(m_pMenuName,m_nMenuNameLength);

    ar >> m_nClassNameLength;
    m_pClassName = new BYTE[m_nClassNameLength];
    if (!m_pClassName)
    {
        ResetAll(FALSE);
        TRACE(_T("Failure : %s,%d - Unable To Allocate Memory\n"), __FILE__, __LINE__);
        return;
    }

    ar.Read(m_pClassName,m_nClassNameLength);
    ar >> m_nCaptionLength;
    m_pCaption = new BYTE[m_nCaptionLength];
    if (!m_pCaption)
    {
        TRACE(_T("Failure : %s,%d - Unable To Allocate Memory\n"), __FILE__, __LINE__);
        ResetAll(FALSE);
    }
    ar.Read(m_pCaption,m_nCaptionLength);

    if (m_dlgTemplate.style & DS_SETFONT)
    {
        ar >> m_nPointSize;
        ar >> m_nFaceNameLength;
        m_pFaceName = new BYTE[m_nFaceNameLength];
        if (!m_pFaceName)
        {
            ResetAll(FALSE);
            TRACE(_T("Failure : %s,%d - Unable To Allocate Memory\n"), __FILE__, __LINE__);
            return;
        }
        ar.Read(m_pFaceName,m_nFaceNameLength);
    }
  }
else
  {
  ar.Write(&m_dlgTemplate, sizeof(m_dlgTemplate));

  ar << m_nMenuNameLength;
  ar.Write(m_pMenuName,m_nMenuNameLength);

  ar << m_nClassNameLength;
  ar.Write(m_pClassName,m_nClassNameLength);

  ar << m_nCaptionLength;
  ar.Write(m_pCaption,m_nCaptionLength);

  if (m_dlgTemplate.style & DS_SETFONT)
    {
    ar << m_nPointSize;
    ar << m_nFaceNameLength;
    ar.Write(m_pFaceName,m_nFaceNameLength);
    }
  }

m_controlList.Serialize(ar);
}

//::SetDlgTemplate()-----------------------------------------------------------
/*Set the constant part of the dialog template

  Note:
  The DLGTEMPLATE structure defines the dimensions and style of a dialog box.
  This structure, always the first in a dialog box template, also specifies
  the number of controls in the dialog box and therefore specifies the number
  of subsequent DLGITEMTEMPLATE structures in the template

    typedef struct
      {
      DWORD style;            //the dialog box style of the dialog
      DWORD dwExtendedStyle;  //extended styles for a window;
                              //not used to create dialog boxes
      WORD cdit;              //the number of items in the dialog box
      short x;                //the upper-left corner position in dialog box units
      short y;                //the upper-left corner position in dialog box units
      short cx;               //the width, in dialog box units, of the dialog box
      short cy;               //the height, in dialog box units, of the dialog box
      } DLGTEMPLATE;

  Example:
    {
    ...
      //Create dialog template
    CDlgTempl NewTemplate;
    NewTemplate.SetDlgTemplate (
                      //the dialog box style of the dialog
                    WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN | WS_BORDER |
                    DS_CONTROL | DS_LOCALEDIT ,
                      //extended styles for a window
                    WS_EX_TOOLWINDOW | WS_EX_CONTEXTHELP | WS_EX_CONTROLPARENT,
                    0  ,0 , //the upper-left corner position in dialog box units
                    150,50  //the size, in dialog box units, of the dialog box
                    );
      //Add controls
     ...
    CDialog dlgModal;     //Create a modal dialog box
    dlgModal.InitModalIndirect(NewTemplate.LockTemplate(),pParentWnd);
    iRes = dlgModal.DoModal(); //Get exit code
    NewTemplate.UnlockTemplate();
    }
 */
BOOL CDlgTempl::SetDlgTemplate (
                  DWORD dwStyle,        //the dialog box style of the dialog
                  DWORD dwExtendedStyle,//extended styles for a window
                  short x, //the upper-left corner position in dialog box units
                  short y, //the upper-left corner position in dialog box units
                  short cx,//the width, in dialog box units, of the dialog box
                  short cy //the height, in dialog box units, of the dialog box
                  )
{
m_dlgTemplate.style = dwStyle;
m_dlgTemplate.dwExtendedStyle = dwExtendedStyle;
m_dlgTemplate.x = x;
m_dlgTemplate.y = y;
m_dlgTemplate.cx = cx;
m_dlgTemplate.cy = cy;

return TRUE;
}

//::GetLength()----------------------------------------------------------------
/*Returns the size of buffer required to create the template in memory
 */
UINT CDlgTempl::GetLength()
{
UINT nTemplateLength = GetHeaderLength();

POSITION pos = m_controlList.GetHeadPosition();
while(pos != NULL)
  {
  CDlgItemTempl* pControl = (CDlgItemTempl*)m_controlList.GetNext(pos);
  nTemplateLength += pControl->GetLength();
  }

return nTemplateLength;
}

//::SetMenuID()----------------------------------------------------------------
/*Set the menu for the dialog.
 */
BOOL CDlgTempl::SetMenuID(WORD wResourceID)
{
  // three overloaded members to specify the menu
if (!wResourceID)
  return SetMenuNameW(NULL);

if (m_pMenuName)
  delete []m_pMenuName;

m_nMenuNameLength = 2 * sizeof(WORD);
m_pMenuName = new BYTE[m_nMenuNameLength];
if (!m_pMenuName)
  {
  m_nMenuNameLength = 0;
  AfxThrowMemoryException();
  return FALSE;
  }

WORD* p = (WORD*) m_pMenuName;
*p++ = 0xFFFF;
*p = wResourceID;

return TRUE;
}

//::SetMenuNameA()-------------------------------------------------------------
/*Set menu name
 */
BOOL CDlgTempl::SetMenuNameA(const char* szMenuName)
{
    BOOL bRet;

    if (m_pMenuName)
    {
        delete []m_pMenuName;
        m_pMenuName = NULL;
        m_nMenuNameLength = 0;
    }

    if (szMenuName)
    {
        UINT nMenuNameLength = _mbstrlen(szMenuName);
        WCHAR* pszMenuName = new WCHAR[nMenuNameLength + 1];
        if (!pszMenuName)
        {
            m_nMenuNameLength = 0;
            AfxThrowMemoryException();
            return FALSE;
        }
        mbstowcs(pszMenuName, szMenuName, nMenuNameLength + 1);
        bRet = SetMenuNameW(pszMenuName);

        delete []pszMenuName;
    }
    else
    {
        bRet = SetMenuNameW(NULL);
    }
    return bRet;
}

//::SetMenuNameW()-------------------------------------------------------------
/*Set menu name
 */
BOOL CDlgTempl::SetMenuNameW(const WCHAR* szMenuName)
{
    if (m_pMenuName)
    {
        delete []m_pMenuName;
    }

    m_nMenuNameLength = sizeof(WORD);
    if (szMenuName)
    {
        m_nMenuNameLength += (wcslen(szMenuName)) * sizeof(WCHAR);
    }

    m_pMenuName = new BYTE[m_nMenuNameLength];
    if (!m_pMenuName)
    {
        m_nMenuNameLength = 0;
        AfxThrowMemoryException();
        return FALSE;
    }

    *((WORD*)m_pMenuName) = 0x0000;
    if (szMenuName)
    {
        wcscpy((WCHAR*)m_pMenuName, szMenuName);
    }

    return TRUE;
}

// Set the window class for the dialog.
// three overloaded members to specify the window class
// if the window class is 0(default) then the standard class
// is used.
BOOL CDlgTempl::SetClassAtom(WORD wClassAtom)
{
    if (m_pClassName)
    {
        delete []m_pClassName;
    }

    m_nClassNameLength = 2 * sizeof(WORD);

    m_pClassName = new BYTE[m_nClassNameLength];

    if (!m_pClassName)
    {
        m_nClassNameLength = 0;
        AfxThrowMemoryException();
        return FALSE;
    }

    *((WORD*) m_pClassName) = 0xFFFF;
    *((WORD*) m_pClassName + sizeof(WORD)) = wClassAtom;

    return TRUE;
}

//::SetClassNameA()------------------------------------------------------------
/*
 */
BOOL CDlgTempl::SetClassNameA(const char* szClassName)
{
    if (m_pClassName)
    {
        delete []m_pClassName;
        m_pClassName = NULL;
        m_nClassNameLength = 0;
    }

    if (szClassName)
    {
        UINT nClassNameLength = _mbstrlen(szClassName);
        WCHAR* pszClassName = new WCHAR[nClassNameLength + 1];
        if (!pszClassName)
        {
            m_nClassNameLength = 0;
            AfxThrowMemoryException();
            return FALSE;
        }
        mbstowcs(pszClassName, szClassName, nClassNameLength + 1);

        BOOL bRet = SetClassNameW(pszClassName);

        delete []pszClassName;

        return bRet;
    }
    else
    {
        return SetClassNameW(NULL);
    }
}

//::SetClassNameW()------------------------------------------------------------
/*
 */
BOOL CDlgTempl::SetClassNameW(const WCHAR* szClassName)
{
    if (m_pClassName)
    {
        delete []m_pClassName;
    }

    m_nClassNameLength = sizeof(WORD);
    if (szClassName)
    {
        m_nClassNameLength += (wcslen(szClassName)) * sizeof(WCHAR);
    }

    m_pClassName = new BYTE[m_nClassNameLength];
    if (!m_pClassName)
    {
        m_nClassNameLength = 0;
        AfxThrowMemoryException();
        return FALSE;
    }

    *((WORD*) m_pClassName) = 0x0000;
    if (szClassName)
    {
        wcscpy((WCHAR*)m_pClassName, szClassName);
    }

    return TRUE;
}

//::SetCaptionA()--------------------------------------------------------------
/*Sets the caption for the dialog
 */
BOOL CDlgTempl::SetCaptionA(const char* szCaption)
{
if (m_pCaption)
  {
  delete []m_pCaption;
  m_pCaption = NULL;
  }

if (szCaption)
  {
  UINT nCaptionLength = _mbstrlen(szCaption);
  WCHAR* pszCaption = new WCHAR[nCaptionLength + 1];
  if (!pszCaption)
    {
    nCaptionLength = 0;
    AfxThrowMemoryException();
    return FALSE;
    }

  mbstowcs(pszCaption, szCaption, nCaptionLength + 1);
  BOOL bRet = SetCaptionW(pszCaption);
  delete []pszCaption;

  return bRet;
  }
else
  return SetCaptionW(NULL);
}

//::SetCaptionW()--------------------------------------------------------------
/*Sets the caption for the dialog
 */
BOOL CDlgTempl::SetCaptionW(const WCHAR* szCaption)
{
if (m_pCaption)
  delete []m_pCaption;

m_nCaptionLength = sizeof(WCHAR);

if (szCaption)
  m_nCaptionLength += (wcslen(szCaption)) * sizeof(WCHAR);

m_pCaption = new BYTE[m_nCaptionLength];
if (!m_pCaption)
  {
  m_nCaptionLength = 0;
  AfxThrowMemoryException();
  return FALSE;
  }

*((WORD*) m_pCaption) = 0x0000;
if (szCaption)
  wcscpy((WCHAR*)m_pCaption, szCaption);


return TRUE;
}

//::SetFontInfoA()-------------------------------------------------------------
/*Set the font for the dialog, Dialog style DS_SETFONT will be addet to the
  dialog template. This function handles ANSI code.

  Example:
    {
    ...
      //Create dialog template
    CDlgTempl NewTemplate;
    NewTemplate.SetDlgTemplate (
                      //the dialog box style of the dialog
                    WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN | WS_BORDER |
                    DS_CONTROL | DS_LOCALEDIT ,
                      //extended styles for a window
                    WS_EX_TOOLWINDOW | WS_EX_CONTEXTHELP | WS_EX_CONTROLPARENT,
                    0  ,0 , //the upper-left corner position in dialog box units
                    150,50  //the size, in dialog box units, of the dialog box
                    );
    NewTemplate.SetFontInfo(8, "MS Sans Serif");
      //Add controls
     ...
    CDialog dlgModal;     //Create a modal dialog box
    dlgModal.InitModalIndirect(NewTemplate.LockTemplate(),pParentWnd);
    iRes = dlgModal.DoModal(); //Get exit code
    NewTemplate.UnlockTemplate();
    }
*/
BOOL CDlgTempl::SetFontInfoA(WORD wPointSize, const char* szFaceName)
{
if (m_pFaceName)
  {
  delete []m_pFaceName;
  m_pFaceName = NULL;
  m_dlgTemplate.style &= ~DS_SETFONT;
  m_nPointSize = 0;
  }

if (!szFaceName)
  {
  TRACE (_T("Warning : No Font Specified\n"));
  return TRUE;
  }

UINT nFaceNameLength = _mbstrlen(szFaceName);
WCHAR* pszFaceName = new WCHAR[nFaceNameLength + 1];
if (!pszFaceName)
  {
  m_nFaceNameLength = 0;
  AfxThrowMemoryException();
  return FALSE;
  }

mbstowcs(pszFaceName, szFaceName, nFaceNameLength + 1);
BOOL bRet = SetFontInfoW(wPointSize, pszFaceName);

delete []pszFaceName;
return bRet;
}

//::SetFontInfoW()-------------------------------------------------------------
/*Set the font for the dialog, Dialog style DS_SETFONT will be addet to the
  dialog template. This function handles UNICODE code.
 */
BOOL CDlgTempl::SetFontInfoW(WORD wPointSize, const WCHAR* szFaceName)
{
if (m_pFaceName)
  {
  delete []m_pFaceName;
  m_dlgTemplate.style &= ~DS_SETFONT;
  m_nPointSize = 0;
  }

if (!szFaceName)
  {
  TRACE (_T("Warning : No Font Specified\n"));
  return TRUE;
  }

m_nFaceNameLength = (wcslen(szFaceName) + 1) * sizeof(WCHAR);
m_pFaceName = new BYTE[m_nFaceNameLength];
if (!m_pFaceName)
  {
  m_nFaceNameLength = 0;
  AfxThrowMemoryException();
  return FALSE;
  }

wcscpy((WCHAR*)m_pFaceName, szFaceName);

m_dlgTemplate.style |= DS_SETFONT;
m_nPointSize = wPointSize;


return TRUE;
}

//::AddControl()---------------------------------------------------------------
/*Adds a control specified by the input parameters to the dialog template being
  constructed.
  Returns TRUE if control was sucessfully added to the template, or  FALSE  if
  the control could not be added to the template.
*/
BOOL CDlgTempl::AddControl(
                WORD  x, //Horizontal position of the control window in dialog units,
                         //relative to upper-left corner of dialog box’s client area
                WORD  y, //Vertical position of the control window in dialog units,
                         //relative to upper-left corner of dialog box’s client area
                WORD  cx,//Width of the control window in dialog units
                WORD  cy,//Height of the control window in dialog units
                WORD  wID, //ID of the control
                DWORD style, //Control window styles
                WORD controlClass, //Identifies one of the following predefined window
                                   //classes:
                                   //
                                   //   0x0080  IDCTRL_BUTTON     Button
                                   //   0x0081  IDCTRL_EDIT       Edit
                                   //   0x0082  IDCTRL_STATIC     Static
                                   //   0x0083  IDCTRL_LISTBOX    List box
                                   //   0x0084  IDCTRL_SCROLLBAR  Scroll bar
                                   //   0x0085  IDCTRL_COMBOBOX   Combo box
                const TCHAR* szCaption, //Control window’s title string in UNICODE
                WORD  nInitDataLength,  //length of control specific data in BYTES
                WORD* pInitData,        //Array of bytes that is control-specific data
                DWORD dwExtendedStyle   //Extended styles for the control
                )
{
CDlgItemTempl* pDialogItemTempl = new CDlgItemTempl;

if (pDialogItemTempl &&
    pDialogItemTempl->CreateControl(x, y, cx, cy, wID, style,
        controlClass, szCaption, nInitDataLength, pInitData, dwExtendedStyle))
  {
  m_controlList.AddTail(pDialogItemTempl);
  m_dlgTemplate.cdit ++;
  return TRUE;
  }

if (pDialogItemTempl)
  delete pDialogItemTempl;

return FALSE;
}

//::AddControl()---------------------------------------------------------------
/*Adds a control specified by the input parameters to the dialog template
  Returns TRUE or FALSE in case of failure
*/
BOOL CDlgTempl::AddControl(
                WORD  x ,WORD  y,
                WORD  cx,WORD  cy,
                WORD  wID,
                DWORD style,
                LPCTSTR controlClass,  //the class name of the control window
                LPCTSTR szCaption,     //control window’s title string
                WORD  nInitDataLength,
                WORD* pInitData,
                DWORD dwExtendedStyle)
{
CDlgItemTempl* pDialogItemTempl = new CDlgItemTempl;

if (pDialogItemTempl &&
    pDialogItemTempl->CreateControl(x, y, cx, cy, wID, style,
        controlClass, szCaption, nInitDataLength, pInitData, dwExtendedStyle))
  {
  m_controlList.AddTail(pDialogItemTempl);
  m_dlgTemplate.cdit ++;
  return TRUE;
  }
if (pDialogItemTempl)
  delete pDialogItemTempl;

return FALSE;
}

//::AddControl()---------------------------------------------------------------
/*Adds a control specified by the input parameters to the dialog template
  Returns TRUE or FALSE in case of failure
*/
BOOL CDlgTempl::AddControl(
    WORD  x,
    WORD  y,
    WORD  cx,
    WORD  cy,
    WORD  wID,
    DWORD style,
    const TCHAR* controlClass, //UNICODE string identifying the class name of the
                               //control window
    WORD wResourceID,          //Ordinal number identifying a resource such as an
                               //icon for static controls with SS_ICON style
    WORD  nInitDataLength,  //in BYTES
    WORD* pInitData,
    DWORD dwExtendedStyle)
{
CDlgItemTempl* pDialogItemTempl = new CDlgItemTempl;

if (pDialogItemTempl &&
    pDialogItemTempl->CreateControl(x, y, cx, cy, wID, style,
        controlClass, wResourceID, nInitDataLength, pInitData, dwExtendedStyle))
  {
  m_controlList.AddTail(pDialogItemTempl);
  m_dlgTemplate.cdit ++;
  return TRUE;
  }
if (pDialogItemTempl)
    delete pDialogItemTempl;

return FALSE;
}

//::AddControl()---------------------------------------------------------------
/*Adds a control specified by the input parameters to the dialog template
  Returns TRUE or FALSE in case of failure
*/
BOOL CDlgTempl::AddControl(
    WORD  x,
    WORD  y,
    WORD  cx,
    WORD  cy,
    WORD  wID,
    DWORD style,
    WORD controlClass,
    WORD wResourceID,       //Ordinal number identifying a resource such as an
                            //icon for static controls with SS_ICON style
    WORD  nInitDataLength,  //in BYTES
    WORD* pInitData,
    DWORD dwExtendedStyle)
{
CDlgItemTempl* pDialogItemTempl = new CDlgItemTempl;

if (pDialogItemTempl &&
    pDialogItemTempl->CreateControl(x, y, cx, cy, wID, style,
        controlClass, wResourceID, nInitDataLength, pInitData, dwExtendedStyle))
{
    m_controlList.AddTail(pDialogItemTempl);
    m_dlgTemplate.cdit ++;
    return TRUE;
}
if (pDialogItemTempl)
    delete pDialogItemTempl;

return FALSE;
}

//::LockTemplate()-------------------------------------------------------------
/*Call this function to allocate local memory lock it and create the template
  in this memory. The returned pointer can be used to pass into
  CreateDialogIndirect. The memory should be unlocked using UnlockTemplate
  function

  Returns a pointer to memory that contains the dialog template in a form that
  can be used with CreateDialogIndirect.

  Example:
    {
    CDialog dlgModal;             //Create a modal dialog box
    dlgModal.InitModalIndirect(NewTemplate.LockTemplate(),pParentWnd);
    iRes = dlgModal.DoModal();    //Get exit code
    NewTemplate.UnlockTemplate();
    }
*/
void* CDlgTempl::LockTemplate()
{
if (m_lpDlgTemplate)
  {
  TRACE(_T("Warning : This template has already been locked\n"));
  return NULL;
  }

m_hDlgTemplate = LocalAlloc(LHND, GetLength());
if (m_hDlgTemplate == NULL)
  {
  TRACE(_T("Failure : %s,%d - Unable To Allocate Memory\n"), __FILE__, __LINE__);
  return NULL;
  }

m_lpDlgTemplate = LocalLock(m_hDlgTemplate);

if (m_lpDlgTemplate == NULL)
  {
  TRACE(_T("Failure : %s,%d - Unable To Lock Memory\n"), __FILE__, __LINE__);
  LocalFree(m_hDlgTemplate);
  m_hDlgTemplate = NULL;
  return NULL;
  }

CreateTemplateInMemory(m_lpDlgTemplate);

return m_lpDlgTemplate;
}

// Unlock a previously locked template and frees up the memory allocated by LockTemplate
void CDlgTempl::UnlockTemplate()
{
    if (m_lpDlgTemplate)
        LocalUnlock(m_hDlgTemplate);

    m_lpDlgTemplate = NULL;

    LocalFree(m_hDlgTemplate);
    m_hDlgTemplate = NULL;
}

//::CreateTemplateInMemory()--------------------------------------------------
/*Create the template in memory using the data stored in the member variables.
  The memory should be large enough to hold the template.
  This function can be directly used if a valid pointer is passed in.
 */
BOOL CDlgTempl::CreateTemplateInMemory(void* pMemory)
{
if (!pMemory || !AfxIsValidAddress(pMemory, GetLength()))
  {
  TRACE(_T("Failure : Invalid pointer\n"));
  return FALSE;
  }

BYTE* pMain = (BYTE*) pMemory;
DLGTEMPLATE* pTemplate = (DLGTEMPLATE*)pMemory;

*pTemplate = m_dlgTemplate;

pMain += sizeof(m_dlgTemplate);

int nLenght = m_nMenuNameLength;
BYTE* p = (BYTE*) m_pMenuName;

for (; nLenght--; *pMain++ = *p++);

nLenght = m_nClassNameLength;
p = (BYTE*) m_pClassName;

for (; nLenght--; *pMain++ = *p++);

nLenght = m_nCaptionLength;
p = (BYTE*) m_pCaption;

for (; nLenght--; *pMain++ = *p++);

if (m_dlgTemplate.style & DS_SETFONT)
  {
  *((WORD *)pMain) = m_nPointSize;
  pMain += sizeof(WORD);
  nLenght = m_nFaceNameLength;
  p = (BYTE*) m_pFaceName;

  for (; nLenght--; *pMain++ = *p++);
  }

pMain = (BYTE*) pMemory + GetHeaderLength();
ASSERT(m_dlgTemplate.cdit == m_controlList.GetCount());
POSITION pos = m_controlList.GetHeadPosition();

while (pos != NULL)
  {
  CDlgItemTempl* pControl = (CDlgItemTempl*)m_controlList.GetNext(pos);
  pControl->CreateControlInMemory(pMain);
  pMain += pControl->GetLength();
  }

return TRUE;
}

//::FindControl()--------------------------------------------------------------
/*Find the control in the dialog template

  Parameters:
    nID      identifies the control to be moved and its meaning is dependent on
             the nFlag parameter. Can be the control ID or present Z order
    nFlag    specifies the meaning of nID and could be one of two values:
             CDlgTempl::byItemID  nID is the control ID,
             CDlgTempl::byItemPosition nID is the controls present Z order
*/
CDlgItemTempl* CDlgTempl::FindControl(UINT nID, UINT nFlag)
{
ASSERT(nFlag == byItemID || nFlag == byItemPosition);

if (nFlag == byItemID && (nID = FindControlByID(nID)) == (UINT) -1)
  {
  TRACE(_T("Failure : %s,%d - Invalid item ID\n"), __FILE__, __LINE__);
  return NULL;
  }

return FindControlByPosition(nID);
}

//::FindControlByID()----------------------------------------------------------
/*Find the control in the dialog template
 */
UINT CDlgTempl::FindControlByID(UINT nID)
{
// cannot find static controls by their ID
if (nID == (UINT) -1)
  {
    TRACE(_T("Failure : %s,%d - Static controls cannot be located by their ID\n"), __FILE__, __LINE__);
    return (UINT) -1;
  }

POSITION pos = m_controlList.GetHeadPosition();
UINT nIndex = 0;

while (pos != NULL)
  {
    CDlgItemTempl* pControl = (CDlgItemTempl*)m_controlList.GetNext(pos);
    if (pControl->GetID() == nID)
        return nIndex;
    nIndex++;
  }

return (UINT) -1;
}


//::FindControlByPosition------------------------------------------------------------------
/*$Description
 */
// Argument         : UINT position
CDlgItemTempl* CDlgTempl::FindControlByPosition(UINT position)
{
    return (CDlgItemTempl*) m_controlList.GetAt(m_controlList.FindIndex(position));
}

// Remove the control from the template
//
// The control is identified as follows
//
//      wID      -   identifies the control to be moved and its meaning
//                  is dependent on the nFlag parameter.
//
//                  Can be the control ID
//                  or
//                  Present Z order
//
//      nFlag   -   specifies the meaning of wID
//
//              Valid Values
//
//                  CDlgTempl::byItemID          - wID specifies the control ID
//
//                  CDlgTempl::byItemPosition    - wID specifies the controls present
//                                                    Z order
//
//      bDelete -   specifies whether the control which is of type CDlgItemTempl
//                  has to be deleted or returned
//
//                  TRUE - Delete the control
//                  FALSE - return the deleted control in ppControl. It is the pointer
//                          is returned then it is not freed when the template is destroyed
//
//      ppControl - valid pointer CDlgItemTempl* which will point to the deleted control
//                  if bDelete is FALSE
//
BOOL CDlgTempl::RemoveControl(UINT wID, UINT nFlag, BOOL bDelete, CDlgItemTempl** ppControl)
{
    ASSERT(nFlag == byItemID || nFlag == byItemPosition);

    if (nFlag == byItemID && (wID = FindControlByID(wID)) == (UINT) -1)
    {
        return FALSE;
    }

    if ((int)wID >= m_controlList.GetCount())
    {
        TRACE(_T("Failure : %s,%d - Invalid item position\n"), __FILE__, __LINE__);
        return FALSE;
    }


    ASSERT(*ppControl);
    *ppControl = NULL;

    *ppControl = (CDlgItemTempl*) m_controlList.GetAt(m_controlList.FindIndex(wID));

    m_controlList.RemoveAt(m_controlList.FindIndex(wID));

    if (bDelete)
    {
        delete *ppControl;
        *ppControl = NULL;
    }

    return TRUE;
}


// Move the control in the Z order so that it has a Z order identified by nPosition
//
// The control is identified as follows
//
//      wID      -   identifies the control to be moved and its meaning
//                  is dependent on the nFlag parameter.
//
//                  Can be the control ID
//                  or
//                  Present Z order
//
//      nFlag   -   specifies the meaning of wID
//
//              Valid Values
//
//                  CDlgTempl::byItemID          - wID specifies the control ID
//
//                  CDlgTempl::byItemPosition    - wID specifies the controls present
//                                                    Z order
//
//      nPosition - specifies the Z order position of the control.
//
BOOL CDlgTempl::MoveControl(UINT wID, UINT nFlag, UINT nPosition)
{
    ASSERT(nFlag == byItemID || nFlag == byItemPosition);

    if (nFlag == byItemID && (wID = FindControlByID(wID)) == (UINT) -1)
    {
        return FALSE;
    }

    if ((int)wID >= m_controlList.GetCount())
    {
        TRACE(_T("Failure : %s,%d - Invalid item position\n"), __FILE__, __LINE__);
        return FALSE;
    }

    CObject *pControl = m_controlList.GetAt(m_controlList.FindIndex(wID));
    m_controlList.RemoveAt(m_controlList.FindIndex(wID));

    if ((int)nPosition >= m_controlList.GetCount())
    {
        if(m_controlList.AddTail(pControl))
            return TRUE;
        else
            return FALSE;
    }

    m_controlList.InsertBefore(m_controlList.FindIndex(nPosition), pControl);
    return TRUE;
}

//::FromResource()-------------------------------------------------------------
/*Initializes the object with information from the template in resource.

  Note:  The function uses the undocumented function AfxFindResourceHandle()
         and could break in future versions of MFC
 */
BOOL CDlgTempl::FromResource(LPCTSTR lpszTemplateName)
{
  // The following function is an undocumented function and
  // could break in future versions of MFC
//HINSTANCE hInst = AfxFindResourceHandle(lpszTemplateName, RT_DIALOG);
HINSTANCE hInst = AfxGetResourceHandle(); //D.K. TO DO: Check resource in DLL,or in main module
if (!hInst)
  return FALSE;

HRSRC hResource = ::FindResource(hInst, lpszTemplateName, RT_DIALOG);
if (!hResource)
  return FALSE;

HLOCAL hDialogTemplate = LoadResource(hInst, hResource);
if (!hDialogTemplate)
  return FALSE;

BYTE* pDialogTemplate = (BYTE *) LockResource(hDialogTemplate);
if (!pDialogTemplate)
  {
  FreeResource(hDialogTemplate);
  return FALSE;
  }

BOOL bRet = CreateTemplateFromMemory(pDialogTemplate);

UnlockResource(hDialogTemplate);
FreeResource(hDialogTemplate);

return bRet;
}

//::CreateTemplateFromMemory()-------------------------------------------------
/*Parses the template in memory and sets the members and creates a list of
 controls.

  Example:
    {
    ...
    HLOCAL hDialogTemplate = LoadResource(hInst, hResource);
    BYTE* pDialogTemplate = (BYTE *) LockResource(hDialogTemplate);
    BOOL bRet = CreateTemplateFromMemory(pDialogTemplate);
    UnlockResource(hDialogTemplate);
    FreeResource  (hDialogTemplate);
    }
 */
BOOL CDlgTempl::CreateTemplateFromMemory(BYTE* p)
{
m_dlgTemplate = *((DLGTEMPLATE *) p);

p += sizeof(DLGTEMPLATE);

if (*((WORD *) p) == 0xFFFF)
  SetMenuID(*(p + sizeof(WORD)));
else
  SetMenuNameW((WCHAR*) p);

p += m_nMenuNameLength;

if (*((WORD*) p) == 0xFFFF)
  SetClassAtom(*(p + sizeof(WORD)));
else
  SetClassNameW((WORD*)p);

p += m_nClassNameLength;

SetCaptionW((WCHAR*) p);

p += m_nCaptionLength;

if (m_dlgTemplate.style & DS_SETFONT)
  {
  SetFontInfoW(*((WORD*) p), (WCHAR*)(p + sizeof(WORD)));
  p += sizeof(WORD) + m_nFaceNameLength;
  }

p = (BYTE*)AlignDWord((UINT)p);

for (int i = 0; i < m_dlgTemplate.cdit; i++)
  {
  CDlgItemTempl* pDialogItemTempl = new CDlgItemTempl;

  if (!pDialogItemTempl)
    {
    ResetAll(FALSE);
    TRACE(_T("Failure : %s,%d - Unable To Allocate Memory\n"), __FILE__, __LINE__);
    return FALSE;
    }

  if (pDialogItemTempl->CreateControlFromMemory(p))
    {
    p += pDialogItemTempl->GetLength();
    m_controlList.AddTail(pDialogItemTempl);
    }
  else
    {
    ResetAll();
    TRACE(_T("Failure : %s,%d - Invalid template\n"), __FILE__, __LINE__);
    return FALSE;
    }
  }
return TRUE;
}


#ifdef _DEBUG
//::Dump()---------------------------------------------------------------------
/*Dumps the contents of the CDlgTempl object to a CDumpContext object

  Parameter:
  dc   the diagnostic dump context for dumping, usually afxDump.
 */
void CDlgTempl::Dump(CDumpContext& dc) const
{
dc.HexDump(_T("Dialog Template : "), (unsigned char*)&m_dlgTemplate, sizeof(m_dlgTemplate), 16);

dc << _T("Menu : ") << (LPCWSTR)m_pMenuName << _T("\nLen: ")
   <<  m_nMenuNameLength << _T("\n");
dc.HexDump(_T(""), (unsigned char*)m_pMenuName, m_nMenuNameLength, 16);

dc << _T("Class : ") << (LPCWSTR)m_pClassName << _T("\nLen: ")
  << m_nClassNameLength << _T("\n");
dc.HexDump(_T("\t"), (unsigned char*)m_pClassName, m_nClassNameLength, 16);

dc << _T("Caption : ") << (LPCWSTR)m_pCaption << _T("\nLen: ")
   << m_nCaptionLength  << _T("\n");
dc.HexDump(_T("\t"), (unsigned char*)m_pCaption, m_nCaptionLength, 16);

if (m_dlgTemplate.style & DS_SETFONT)
  {
  dc << _T("Font : ") << (LPCWSTR)m_pFaceName <<_T(" Size ")<<  m_nPointSize
    << _T("\nLen: ") << m_nFaceNameLength << _T("\n");
  dc.HexDump(_T("\t"), (unsigned char*)m_pFaceName, m_nFaceNameLength, 16);
  }

m_controlList.Dump(dc);
POSITION pos = m_controlList.GetHeadPosition();
while(pos != NULL)
  {
  CDlgItemTempl* pControl = (CDlgItemTempl*)m_controlList.GetNext(pos);
  dc << _T("\n----------------------");
  pControl->Dump(dc);
  }
dc << _T("\n");

}
#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2003-09-22 22:26:08  Darko           formatting
 *  5    Biblioteka1.4         2002-01-29 15:39:41  Darko           Tag update
 *  4    Biblioteka1.3         2001-08-19 23:53:28  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 22:51:21  Darko           
 *  2    Biblioteka1.1         2001-06-08 23:50:37  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:56:25  Darko           
 * $
 *****************************************************************************/
