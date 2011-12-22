/*$Workfile: KStaticEx.cpp$: implementation file
  $Revision: 1.2 $ $Date: 2011/12/22 16:15:25 $
  $Author: ddarko $

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2001-07-06 Darko Kolakovic
 */
#include "stdafx.h"
#include "resource.h"
#include "KNotifyBox.h" //CNotifyBox class


#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#ifndef _USE_MSFLUENUI_ //Microsoft Fluent UI

///////////////////////////////////////////////////////////////////////////////
// CNotifyBox class

IMPLEMENT_DYNAMIC(CNotifyBox, CDialog)

//Wnd message handlers
BEGIN_MESSAGE_MAP(CNotifyBox, CDialog)
  ON_BN_CLICKED(IDOK, OnBnClickedOk)
  ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
/*Constructor for a resource-based modaless dialog box.
 */
CNotifyBox::CNotifyBox(UINT nIDTemplate, //[in] ID number of a dialog-box template resource
                       CWnd* pParent //[in]=NULL owner window object
                      ) :
  CDialog(nIDTemplate, pParent),
  m_strText(_T("")),
  m_pwndParent(pParent)
{
TRACE0(_TEXT("CNotifyBox::CNotifyBox()\n"));
}

//-----------------------------------------------------------------------------
/*Destructor
 */
CNotifyBox::~CNotifyBox()
{
TRACE0(_TEXT("CNotifyBox::~CNotifyBox()\n"));
}

//-----------------------------------------------------------------------------
/*
 */
void CNotifyBox::OnBnClickedCancel()
{
TRACE0(_TEXT("CNotifyBox::OnBnClickedCancel()\n"));
DestroyWindow();
}

//-----------------------------------------------------------------------------
/*
 */
void CNotifyBox::OnBnClickedOk()
{
TRACE0(_TEXT("CNotifyBox::OnBnClickedOk()\n"));
DestroyWindow();
}

//-----------------------------------------------------------------------------
/*Cleanup procedure.
  Called by the default OnNcDestroy member function after the window has been
  destroyed.
 */
void CNotifyBox::PostNcDestroy()
{
TRACE0(_TEXT("CNotifyBox::PostNcDestroy()\n"));
CDialog::PostNcDestroy();

delete this;
}

///////////////////////////////////////////////////////////////////////////////
#endif //_USE_MSFLUENUI_ Microsoft Fluent UI
/*****************************************************************************
 * $Log: KNotifyBox.cpp,v $
 * Revision 1.2  2011/12/22 16:15:25  ddarko
 * Microsoft Fluent UI implementation
 *
 * Revision 1.1  2011/10/03 20:34:17  ddarko
 * Created
 *
 *****************************************************************************/
