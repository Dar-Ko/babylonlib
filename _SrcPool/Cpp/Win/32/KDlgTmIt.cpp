/*$Workfile: KDlgTmIt.cpp$: implementation file
  $Revision: 7$ $Date: 2004-10-01 21:34:45$
  $Author: Darko$

  Encapsulates DLGITEMTEMPLATE structure
  Copyright (c) 1996 Microsoft Corporation. All rights reserved.
  Written by Sridhar Madhugiri
  Mar. 98 Cosmetic changes D.K.
  Mar. 2k Separate class D.K.
 */ 

#include "stdafx.h"
#include "KDlgTmIt.h" //CDlgItemTempl class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgItemTempl

/////////////////////////////////////////////////////////////////////////////
// CDlgItemTempl

// Following code is for setting up the runtime information
// Normally IMPLEMENT_SERIAL would handle this for us

CObject* __stdcall CDlgItemTempl::CreateObject()
{
return new CDlgItemTempl;
}

CRuntimeClass* __stdcall CDlgItemTempl::_GetBaseClass()
{
return (CRuntimeClass*) (&CObject::classCObject);
}

CRuntimeClass CDlgItemTempl::classCDlgItemTempl =
{
  "CDlgItemTempl",
  sizeof(class CDlgItemTempl),
  1,
  CDlgItemTempl::CreateObject,
#ifdef _AFXDLL
  &CDlgItemTempl::_GetBaseClass,
#else
  &CObject::classCObject,
#endif //!_AFXDLL
  0
};

static const AFX_CLASSINIT _init_CDlgItemTempl(&CDlgItemTempl::classCDlgItemTempl);
CRuntimeClass* CDlgItemTempl::GetRuntimeClass() const
{
  return &CDlgItemTempl::classCDlgItemTempl;
}

//IMPLEMENT_SERIAL(CDlgItemTempl, CObject)


//CDlgItemTempl::CDlgItemTempl()------------------------------------
/*Construction
  Example:
    void CParentWnd::OnAbout()
    {
    CDlgTempl NewTemplate;
    NewTemplate.FromResource(IDD_ABOUTBOX);
    NewTemplate.SetCaption(_T("About Box Dialog")); //change the caption

      //Find the OK button in the template and get its position
    CDlgItemTempl* pOK = NewTemplate.FindControl(IDOK);
    CPoint pos = pOK->GetPosition();
    CSize size = pOK->GetSize();
      //Position and dimension of the new button
    pos.y += size.cy + 7;
          //Add a Cancel button below OK button.
    NewTemplate.AddControl((WORD)pos.x  , (WORD)pos.y,        //position
                           (WORD)size.cx, (WORD)size.cy,      //size
                           IDCANCEL,                          //control's ID
                           WS_VISIBLE | WS_CHILD | WS_TABSTOP,//style
                           _T("Button"),                      //class name
                           _T("Cancel"));                     //caption
    CDialog dlgAbout;     //Create a modal dialog box
    dlgAbout.InitModalIndirect(NewTemplate.LockTemplate());
    dlgAbout.DoModal();
    NewTemplate.UnlockTemplate();
  }

 */
CDlgItemTempl::CDlgItemTempl() :
    m_pControlClass(NULL),
    m_pCaption(NULL),
    m_pInitData(NULL),
    m_nControlClassLength(0),
    m_nCaptionLength(0),
    m_nInitDataLength(0)
{
    memset(&m_dlgItemTemplate, 0, sizeof(m_dlgItemTemplate));
}

CDlgItemTempl::~CDlgItemTempl()
{
    Reset();
}

//::CreateControl()------------------------------------------------------------
/*Creates a control with the given properties
 */
BOOL CDlgItemTempl::CreateControl(WORD  x, WORD  y,
                                  WORD  cx,WORD  cy,
                                  WORD  wID,
                                  DWORD style,
                                   WORD controlClass,
                                  const TCHAR* szCaption,
                                  WORD nInitDataLength,
                                   WORD* pInitData,
                                  DWORD dwExtendedStyle)
{
//There are 4 different combinations of data.
// Set the DLGITEMTEMPLATE structure
SetDlgItemTemplate(x, y, cx, cy, wID, style, dwExtendedStyle);

// Set the control class information
if (!SetControlClassAtom(controlClass))
  {
    Reset();
    TRACE(_T("Unable to Create Control\n"));
    return FALSE;
  }

// Set the caption for the control
if (!SetCaption(szCaption))
  {
    Reset();
    TRACE(_T("Unable to Create Control\n"));
    return FALSE;
  }

// Set extra initialization data
if (nInitDataLength && !SetInitData(nInitDataLength, pInitData))
  {
    Reset();
    TRACE(_T("Unable to Create Control\n"));
    return FALSE;
  }

return TRUE;
}

BOOL CDlgItemTempl::CreateControl(WORD  x,
                                  WORD  y,
                                  WORD  cx,
                                  WORD  cy,
                                  WORD  wID,
                                  DWORD style,
                                   const TCHAR* controlClass,
                                  const TCHAR* szCaption,
                                  WORD nInitDataLength,
                                   WORD* pInitData,
                                  DWORD dwExtendedStyle
                                  )
{
  // Set the DLGITEMTEMPLATE structure
  SetDlgItemTemplate(x, y, cx, cy, wID, style, dwExtendedStyle);

  // Set the control class information
   if (!SetControlClass(controlClass))
{
    Reset();
    TRACE(_T("Unable to Create Control\n"));
    return FALSE;
}

// Set the caption for the control
if (!SetCaption(szCaption))
{
    Reset();
    TRACE(_T("Unable to Create Control\n"));
    return FALSE;
}

// Set extra initialization data
if (nInitDataLength && !SetInitData(nInitDataLength, pInitData))
{
    Reset();
    TRACE(_T("Unable to Create Control\n"));
    return FALSE;
}

return TRUE;
}

BOOL CDlgItemTempl::CreateControl(WORD  x,
                                             WORD  y,
                                             WORD  cx,
                                             WORD  cy,
                                             WORD  wID,
                                             DWORD style,
                                              const TCHAR* controlClass,
                                             WORD wResourceID,
                                             WORD nInitDataLength,
                                              WORD* pInitData,
                                             DWORD dwExtendedStyle)
{
// Set the DLGITEMTEMPLATE structure
SetDlgItemTemplate(x, y, cx, cy, wID, style, dwExtendedStyle);

// Set the control class information
if (!SetControlClass(controlClass))
{
    Reset();
    TRACE(_T("Unable to Create Control\n"));
    return FALSE;
}

// Set the caption for the control
if (!SetCaptionID(wResourceID))
{
    Reset();
    TRACE(_T("Unable to Create Control\n"));
    return FALSE;
}

// Set extra initialization data
if (nInitDataLength && !SetInitData(nInitDataLength, pInitData))
{
    Reset();
    TRACE(_T("Unable to Create Control\n"));
    return FALSE;
}

return TRUE;
}

BOOL CDlgItemTempl::CreateControl(WORD  x,
                                             WORD  y,
                                             WORD  cx,
                                             WORD  cy,
                                             WORD  wID,
                                             DWORD style,
                                              WORD controlClass,
                                             WORD wResourceID,
                                             WORD nInitDataLength,
                                              WORD* pInitData,
                                             DWORD dwExtendedStyle)
{
// Set the DLGITEMTEMPLATE structure
SetDlgItemTemplate(x, y, cx, cy, wID, style, dwExtendedStyle);

// Set the control class information
if (!SetControlClassAtom(controlClass))
{
    Reset();
    TRACE(_T("Unable to Create Control\n"));
    return FALSE;
}

// Set the caption for the control
if (!SetCaptionID(wResourceID))
{
    Reset();
    TRACE(_T("Unable to Create Control\n"));
    return FALSE;
}

// Set extra initialization data
if (nInitDataLength && !SetInitData(nInitDataLength, pInitData))
{
    Reset();
    TRACE(_T("Unable to Create Control\n"));
    return FALSE;
}

return TRUE;
}

//::SetDlgItemTemplate()-------------------------------------------------------
/*Set the values in the DLGITEMTEMPLATE structure

   typedef struct
     {
     DWORD style;          //the control's windows and control style
     DWORD dwExtendedStyle;//extended styles for a window
     short x;      //the upper-left corner position in dialog box units
     short y;      //the upper-left corner position in dialog box units
     short cx;     //the width, in dialog box units, of the control
     short cy;     //the height, in dialog box units, of the control
     WORD  id;     //the control identifier
     } DLGITEMTEMPLATE;
*/
void CDlgItemTempl::SetDlgItemTemplate(WORD  x, WORD  y,
                                                  WORD  cx, WORD  cy,
                                                  WORD  wID, DWORD style,
                                          DWORD dwExtendedStyle)
{
//Sets the fixed part of the DLGITEMTEMPLATE structure
m_dlgItemTemplate.x                 = x;
m_dlgItemTemplate.y                 = y;
m_dlgItemTemplate.cx                = cx;
m_dlgItemTemplate.cy                = cy;
m_dlgItemTemplate.style             = style;
m_dlgItemTemplate.dwExtendedStyle   = dwExtendedStyle;
m_dlgItemTemplate.id                = wID;
}

// Following 3 functions set the control class for the control
// Two distinct functions with the third overloaded for ANSI
// and UNICODE

BOOL CDlgItemTempl::SetControlClassAtom(WORD controlClass)
{
    ResetControlClass();

    if (!ValidControl(controlClass))
    {
        TRACE(_T("Invalid Control class\n"));
        return FALSE;
    }

    m_nControlClassLength = 2 * sizeof(WORD);
    m_pControlClass = new BYTE[m_nControlClassLength];
    if (!m_pControlClass)
    {
        m_nControlClassLength = 0;
        TRACE(_T("Unable to allocate Memory\n"));
        return FALSE;
    }

    WORD* p = (WORD*) m_pControlClass;
    *p++ = 0xFFFF;
    *p = controlClass;

    return TRUE;
}

//::SetControlClassA()---------------------------------------------------------
/*Store control's class name
*/
BOOL CDlgItemTempl::SetControlClassA(const char* controlClass)
{
if (controlClass == NULL)
  {
  TRACE0("CDlgItemTempl::SetControlClassA() failure!\n\tNULL parameter\n");
  AfxThrowResourceException();
  }
ResetControlClass();

UINT nControlClassLength = _mbstrlen(controlClass);
WCHAR* pszControlClass = new WCHAR[nControlClassLength + 1];
if (!pszControlClass)
  {
  m_nControlClassLength = 0;
  TRACE(_T("Failure : %s,%d - Unable To Allocate Memory\n"), __FILE__, __LINE__);
  return FALSE;
  }

mbstowcs(pszControlClass, controlClass, nControlClassLength + 1);
BOOL bRet = SetControlClassW(pszControlClass);

delete []pszControlClass;
return bRet;
}

//::SetControlClassW()---------------------------------------------------------
/*Store control's class name
 */
BOOL CDlgItemTempl::SetControlClassW(const WCHAR* controlClass)
{
if (controlClass == NULL)
  {
  TRACE0("CDlgItemTempl::SetControlClassW() failure!\n\tNULL parameter\n");
  AfxThrowResourceException();
  }

ASSERT(controlClass);

ResetControlClass();

m_nControlClassLength = (wcslen(controlClass) + 1) * sizeof(WCHAR);
m_pControlClass = new BYTE[m_nControlClassLength];
if (!m_pControlClass)
  {
  m_nControlClassLength = 0;
  TRACE(_T("Failure : %s,%d - Unable To Allocate Memory\n"), __FILE__, __LINE__);
  return FALSE;
  }

wcscpy((WCHAR*)m_pControlClass, controlClass);

return TRUE;
}

// Following 3 functions set the caption for the control
// Two distinct functions with the third overloaded for ANSI
// and UNICODE
BOOL CDlgItemTempl::SetCaptionID(WORD wCaptionID)
{
ResetCaption();

m_nCaptionLength = 2 * sizeof(WORD);
m_pCaption = new BYTE[m_nCaptionLength];
if (!m_pCaption)
  {
  m_nCaptionLength = 0;
  TRACE(_T("Failure : %s,%d - Unable To Allocate Memory\n"), __FILE__, __LINE__);
  return FALSE;
  }

WORD* p = (WORD*) m_pCaption;
*p++ = 0xFFFF;
*p = wCaptionID;

return TRUE;
}

//::SetCaptionA()--------------------------------------------------------------
/*Sets the windows title to the specified text. If the window is a control,
 the text within the control is set.
 */
BOOL CDlgItemTempl::SetCaptionA(const char* szCaption)
{
ResetCaption();

if (szCaption != NULL)  //D.K. If caption is not NULL
  {
  UINT nCaptionLength = _mbstrlen(szCaption);
  WCHAR* pszCaption = new WCHAR[nCaptionLength + 1];
  if (!pszCaption)
    {
    m_nCaptionLength = 0;
    TRACE(_T("Failure : %s,%d - Unable To Allocate Memory\n"), __FILE__, __LINE__);
    return FALSE;
    }
  mbstowcs(pszCaption, szCaption, nCaptionLength + 1);

  BOOL bRet = SetCaptionW(pszCaption);

  delete []pszCaption;
  return bRet;
  }
else //D.K. If source is NULL
  return SetCaptionW(NULL);
}

//::SetCaptionW()--------------------------------------------------------------
/*Sets the windows title to the specified text. If the window is a control,
  the text within the control is set.
 */
BOOL CDlgItemTempl::SetCaptionW(const WCHAR* szCaption)
{
ResetCaption();

m_nCaptionLength = ( ((szCaption == NULL)? 0 : wcslen(szCaption)) + 1)*sizeof(WCHAR); //D.K. If caption is NULL add 1 multibyte
m_pCaption = new BYTE[m_nCaptionLength];
if (!m_pCaption)
  {
  m_nCaptionLength = 0;
  TRACE(_T("Failure : %s,%d - Unable To Allocate Memory\n"), __FILE__, __LINE__);
  return FALSE;
  }

//D.K. If source is NULL
if (szCaption != NULL)
  wcscpy((WCHAR*)m_pCaption, szCaption);
else
  *((WORD*) m_pCaption) = 0x0000; //'\0'

return TRUE;
}

//::SetInitData()--------------------------------------------------------------
/*Set the InitData part of the template for the control.
  The control should know how to use this data.
  */
BOOL CDlgItemTempl::SetInitData(WORD nInitDataLength,
                                           const WORD* pInitData)
{
ResetInitData();
m_nInitDataLength = nInitDataLength;

if (m_nInitDataLength)
  {
  m_pInitData = new BYTE[m_nInitDataLength];
  if (!m_pInitData)
    {
    m_nInitDataLength = 0;
    TRACE(_T("Failure : %s,%d - Unable To Allocate Memory\n"), __FILE__, __LINE__);
    return FALSE;
    }

  WORD* p = (WORD*)m_pInitData;
  for ( ; nInitDataLength--; *p++ = *pInitData++);
  }

return TRUE;
}

//::Reset()--------------------------------------------------------------------
/*Reset the template.
 */
void CDlgItemTempl::Reset(void)
{
memset(&m_dlgItemTemplate, 0, sizeof(m_dlgItemTemplate));
ResetControlClass();
ResetCaption();
ResetInitData();
}

//::Serialize()----------------------------------------------------------------
/*Reads or writes the template item object from or to an archive.

  Note: Default CDocument::OnOpenDocument() handles exceptions and returns
        FALSE to the app.
 */
void CDlgItemTempl::Serialize( CArchive& ar )
{
if (ar.IsLoading())
  {
  Reset();
  ar.Read(&m_dlgItemTemplate, sizeof(m_dlgItemTemplate));

  ar >> m_nControlClassLength;
  m_pControlClass = new BYTE[m_nControlClassLength];
  ar.Read(m_pControlClass, m_nControlClassLength);

  ar >> m_nCaptionLength;
  m_pCaption = new BYTE[m_nCaptionLength];
  ar.Read(m_pCaption, m_nCaptionLength);

  ar >> m_nInitDataLength;
  if (m_nInitDataLength)
    {
    m_pCaption = new BYTE[m_nInitDataLength];
    ar.Read(m_pInitData, m_nInitDataLength);
    }
  }
else
  {
  ar.Write(&m_dlgItemTemplate, sizeof(m_dlgItemTemplate));

  ar << m_nControlClassLength;
  ar.Write(m_pControlClass, m_nControlClassLength);

  ar << m_nCaptionLength;
  ar.Write(m_pCaption, m_nCaptionLength);

  ar << m_nInitDataLength;
  if (m_nInitDataLength)
    {
    ar.Write(m_pInitData, m_nInitDataLength);
    }
  }
}

//::CreateControlInMemory()----------------------------------------------------
/*Create the template in memory at the location specified by the pointer. This
  function creates the template in the required format. The memory pointed to
  by pMemory should be DWORD aligned and should be large enough to hold the
  template for the control
*/
void CDlgItemTempl::CreateControlInMemory(BYTE* pMemory)
{
ASSERT(AlignDWord((ULONG)&pMemory) == (ULONG)&pMemory);
ASSERT(AfxIsValidAddress(pMemory, GetLength()));

BYTE* pMain = pMemory;

// Copy constant part of the template
DLGITEMTEMPLATE* pTemplate = (DLGITEMTEMPLATE*) pMain;
*pTemplate = m_dlgItemTemplate;
pMain = pMemory + sizeof(m_dlgItemTemplate);

// Copy control class
int nLenght = m_nControlClassLength;
BYTE* p = (BYTE*) m_pControlClass;
for (; nLenght--; *pMain++ = *p++);

// Copy Caption
nLenght = m_nCaptionLength;
p = (BYTE*) m_pCaption;
for (; nLenght--; *pMain++ = *p++);

// Init Data length
*((WORD *)pMain) = (WORD)m_nInitDataLength;
pMain += sizeof(WORD);

// Copy Init Data
nLenght = m_nInitDataLength;
p = (BYTE*) m_pInitData;
for (; nLenght--; *pMain++ = *p++);
}

// Parse the template in memory and fill the member variables.
// The control template starts at the location pointed by the
// pointer. It has to point to a DWORD aligned boundary

BOOL CDlgItemTempl::CreateControlFromMemory(BYTE* p)
{
ASSERT(AlignDWord((ULONG)&p) == (ULONG)&p);
ASSERT(AfxIsValidAddress(p, GetLength(), FALSE));

// Read in the constant part of the template
m_dlgItemTemplate = *((DLGITEMTEMPLATE*) p);
p += sizeof(DLGITEMTEMPLATE);


if (*((WORD*) p) == 0xFFFF) //Read the control class for the control
  SetControlClassAtom(*(p + sizeof(WORD)));
else
  SetControlClassW((WORD*) p);
p += m_nControlClassLength;


if (*((WORD*) p) == 0xFFFF)  //Read the control caption
  SetCaptionID(*(p + sizeof(WORD)));
else
  SetCaptionW((WORD*) p);
p += m_nCaptionLength;

// Read the controls Init Data Length and the data
SetInitData(*p, (WORD*) (p + sizeof(WORD)));

return TRUE;
}



#ifdef _DEBUG
//::Dump()---------------------------------------------------------------------
/*Dumps the member variables for debugging
 */
void CDlgItemTempl::Dump( CDumpContext& dc ) const
{
CObject::Dump( dc );

dc.HexDump(_T("m_dlgItemTemplate : "), (unsigned char *)&m_dlgItemTemplate,
            sizeof(m_dlgItemTemplate), 20);
dc << "m_nControlClassLength : "<< (LPCWSTR)m_pControlClass<<_T(" Len:")
   << m_nControlClassLength << "\n";
dc.HexDump(_T("m_pControlClass : "), m_pControlClass, m_nControlClassLength, 20);

dc << _T("m_nCaptionLength : ") << (LPCWSTR)m_pCaption<<_T(" Len:")
   << m_nCaptionLength << "\n";
if (m_nCaptionLength)
  dc.HexDump(_T("m_pCaption : "),m_pCaption, m_nCaptionLength, 20);

dc << _T("m_nInitDataLength : ") << m_nInitDataLength << "\n";
if (m_nInitDataLength)
  {
  dc.HexDump(_T("m_pInitData : "),m_pInitData, m_nInitDataLength, 20);
  }
}

#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  7    Biblioteka1.6         2004-10-01 21:34:45  Darko           stdafx.h
 *  6    Biblioteka1.5         2003-09-22 21:26:06  Darko           formatting
 *  5    Biblioteka1.4         2002-01-29 14:39:36  Darko           Tag update
 *  4    Biblioteka1.3         2001-08-19 22:53:14  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 21:51:14  Darko           
 *  2    Biblioteka1.1         2001-06-08 22:50:31  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 14:56:20  Darko           
 * $
 *****************************************************************************/
