/*$Workfile: KAbout.cpp$: implementation file
  $Revision: 6$ $Date: 2004-10-01 21:33:26$
  $Author: Darko$

  Defines the class behaviors for the application.
  Copyright: CommonSoft Inc.
  Jan 96 Darko Kolakovic
  May 97 Darko Kolakovic 2nd rev
 */

#ifdef BorCpp                //Borland C++ v5.01
  #define _diskfree_t  diskfree_t
  #define _getdiskfree _dos_getdiskfree
#endif

#include "stdafx.h"
#include "KAbtRes.h" //About box resource symbols
#include "KAbout.h"  //CAboutDlg dialog

#if 0
//::CAboutDlg()----------------------------------------------------------------
/*Default constructor
 */
CAboutDlg::CAboutDlg(LPCTSTR lpszAppPath //[in] = NULL; path of module containing 
                     //the version information. If it is NULL, the current module
                     //is interogated for the version information.
                     ) : 
    CDialog(IDD_ABOUTBOX),
    m_lpszFilePath(lpszAppPath)
{
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
}

//-----------------------------------------------------------------------------
/*
 */
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

#endif

//::CAboutDlg()----------------------------------------------------------------
/*Default constructor. By default the dialog uses resource template 
  IDD_ABOUTBOX = 100 defined in KAbtRes.h. Include the header file in your recource 
  file search path.
 */
CAboutDlg::CAboutDlg(LPCTSTR lpszAppPath //[in] = NULL; path of module containing 
                     //the version information. If it is NULL, the current module
                     //is interogated for the version information.
                     ) : 
    CDialog(IDD_ABOUTBOX) ,
    m_lpszFilePath(lpszAppPath)
{
TRACE("IDD_ABOUTBOX = %d\n", IDD_ABOUTBOX);
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
}

//-----------------------------------------------------------------------------
/*
 */
CAboutDlg::~CAboutDlg()
{
}

//-----------------------------------------------------------------------------
/*Called by the framework to exchange and validate dialog data.
 */
void CAboutDlg::DoDataExchange(CDataExchange* pDX //[in] pointer to a 
                                                  //CDataExchange object. 

                               )
{
CDialog::DoDataExchange(pDX);
//{{AFX_DATA_MAP(CAboutDlg)
DDX_Control(pDX, IDC_COPYRIGHT, m_Copyright);
//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
  //{{AFX_MSG_MAP(CAboutDlg)
  ON_WM_PAINT()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
/*Set the new hyperlink control reference.

  Example:
    void CMyApp::OnAppAbout()
      {
      TRACE0("CMyApp::OnAppAbout()\n");
      CAboutDlg aboutDlg;
      CString strUrl;
      strUrl = _T("http://www.CommonSoftInc.com");
      aboutDlg.SetUrl(strUrl);
      if(-1 == aboutDlg.DoModal()) 
        {
        ...
        }
       }

  See also: CHyperlink::SetUrl();
 */
void CAboutDlg::SetUrl(CString& strUrl //[in] Uniform Resource Locator string
                       )
{
m_Copyright.SetUrl(strUrl);
}

void CAboutDlg::SetUrl(LPCTSTR szUrl //[in] zero-terminated Uniform Resource Locator
                       )
{
CString strUrl; //URL or empty string
if (szUrl != NULL)
  {
  strUrl = szUrl;
  }
m_Copyright.SetUrl(strUrl);
}


//::OnInitDialog()-------------------------------------------------------------
#include <dos.h>
#include <direct.h> //_getdrive()
#include "KVerInfo.h"
/*This member function is called in response to the WM_INITDIALOG message.
  This message is sent to the dialog box during the Create, CreateIndirect,
  or DoModal calls, which occur immediately before the dialog box is displayed.
 */
BOOL CAboutDlg::OnInitDialog()
{
TRACE0("CAboutDlg::OnInitDialog()\n");
CDialog::OnInitDialog();
#ifndef _MAC
  {
  CString strFreeDiskSpace;
  CString strFreeMemory;
  CString strFmt;

  // Fill available memory
  MEMORYSTATUS MemStat;
  MemStat.dwLength = sizeof(MEMORYSTATUS);
  GlobalMemoryStatus(&MemStat);
  strFmt.LoadString(IDS_PHYSICAL_MEM);
  strFreeMemory.Format(strFmt, MemStat.dwTotalPhys / 1024L);

  SetDlgItemText(IDC_PHYSICAL_MEM, strFreeMemory); //Initialize the control

  // Fill disk free information
  struct _diskfree_t diskfree;
  int nDrive = _getdrive(); // use current default drive
  if (_getdiskfree(nDrive, &diskfree) == 0)
    {
    strFmt.LoadString(IDS_DISK_SPACE);
    strFreeDiskSpace.Format(strFmt,
                      nDrive-1 + _T('A'),      //disk name (letter)
      (DWORD)diskfree.avail_clusters *         //free disk space
      (DWORD)diskfree.sectors_per_cluster *
      (DWORD)diskfree.bytes_per_sector / (DWORD)1024L
      );
    }
  else
    strFreeDiskSpace.LoadString(IDS_ABT_UNAVAILABLE);

  SetDlgItemText(IDC_DISK_SPACE, strFreeDiskSpace);   //Initialize the control
  }
#endif //_MAC

  //Initialize product information
CVersionInfo AppVersion(m_lpszFilePath);
CString strSendMail = _T("mailto:Info@CommonSoftInc.com?Subject=");
CString lpszString;
VERIFY(AppVersion.GetProductName(lpszString));
SetDlgItemText(IDC_PRODUCTNAME, lpszString);
strSendMail += lpszString;
strSendMail += _T("-");
VERIFY(AppVersion.GetProductVersion(lpszString));
SetDlgItemText(IDC_VERSION, lpszString);
strSendMail += lpszString;

VERIFY(AppVersion.GetCopyright(lpszString));
SetDlgItemText(IDC_COPYRIGHT, lpszString);
VERIFY(AppVersion.GetFileDescription(lpszString));
SetDlgItemText(IDC_DESCRIPTION, lpszString);

if (m_Copyright.GetUrl().IsEmpty())    //Use created URL
  {
  m_Copyright.SetUrl(strSendMail);
  }

return TRUE;
}

//::OnPaint()------------------------------------------------------------------
#ifdef _INCLUDE_KCTLREFF_
#include "KCtlEff.h" //Control 3D effects
/*The framework calls this member function when Windows or an application makes
  a request to repaint a portion of an application’s window. 
  The WM_PAINT message is sent when the UpdateWindow or RedrawWindow member 
  function is called.
*/
void CAboutDlg::OnPaint() 
{
CPaintDC dc(this); // device context for painting
DrawRivets(this);
DrawDlgItemShadow(&dc,IDOK);
  // Do not call CDialog::OnPaint() for painting messages
}
#else
void CAboutDlg::OnPaint()
  {
  CDialog::OnPaint();
  }
#endif
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2004-10-01 21:33:26  Darko           stdafx.h
 *  5    Biblioteka1.4         2003-11-03 12:14:58  Darko           Added SetUrl()
 *  4    Biblioteka1.3         2003-08-13 16:38:21  Darko           formatting
 *  3    Biblioteka1.2         2003-08-06 21:47:42  Darko           Modified
 *       dialog's resource ID
 *  2    Biblioteka1.1         2003-08-06 02:46:34  Darko           Prepared for
 *       Unicode 
 *  1    Biblioteka1.0         2003-08-05 22:17:27  Darko           
 * $
 *****************************************************************************/

