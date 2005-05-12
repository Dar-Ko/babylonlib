/*$Workfile: TestAboutDlg.cpp$: implementation file
  $Revision: 3$ $Date: 2005-05-03 01:43:37$
  $Author: Darko$

  Implementation file
  Copyright: CommonSoft Inc.
  2003-08-25 Darko Kolakovic
 */

#include "stdafx.h"
#include "Res/TestResource.h"
#include "TestAboutDlg.h"   //CAboutDlg class

#ifndef IDD_ABOUTBOX
  #error Create IDD_ABOUTBOX dialog template first!
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
#endif


//-----------------------------------------------------------------------------
/*
 */
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

//-----------------------------------------------------------------------------
/*
 */
CAboutDlg::~CAboutDlg()
{
}

//-----------------------------------------------------------------------------
/*Called by the framework to exchange and validate dialog data.

  Example:
      void CAboutDlg::DoDataExchange(CDataExchange* pDX)
        {
        CDialog::DoDataExchange(pDX);
        DDX_Text(pDX, IDC_VERSION,   m_strVersion);
        DDX_Text(pDX, IDC_COPYRIGHT, m_strOwner);
        }

 */
void CAboutDlg::DoDataExchange(CDataExchange* pDX //[in] pointer to a CDataExchange object.
                               )
{
CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2005-05-03 01:43:37  Darko            
 *  2    Biblioteka1.1         2004-10-01 22:22:40  Darko           stdafx.h
 *  1    Biblioteka1.0         2003-08-26 01:37:10  Darko           
 * $
 *****************************************************************************/
