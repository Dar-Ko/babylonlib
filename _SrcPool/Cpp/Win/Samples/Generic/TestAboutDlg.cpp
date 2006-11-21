/*$Workfile: TestAboutDlg.cpp$: implementation file
  $Revision: 1$ $Date: 2006-09-27 22:52:55$
  $Author: Darko$

  Implementation file
  Copyright: CommonSoft Inc.
  2003-08-25 Darko Kolakovic
 */

#include "stdafx.h"
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
/*
 */
void CAboutDlg::DoDataExchange(CDataExchange* pDX //[in]
                               )
{
CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2006-09-27 22:52:55  Darko           
 * $
 *****************************************************************************/
