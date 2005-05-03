/*$Workfile: TestDialogApp.h$: header file
  $Revision: 5$ $Date: 2005-05-02 17:09:48$
  $Author: Darko Kolakovic$

  main header file for the application
  Copyright: CommonSoft Inc
  2003-08-25 Darko Kolakovic
 */

// Group=Examples Windows

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' and MFC before including this file (define _USE_MFC)
  //Note: define _USE_MFC is necessary only if stdafx.h header file
  //from BabylonLib is used.

#endif

//#include "Res/Resource.h"   // main symbols

///////////////////////////////////////////////////////////////////////////////
//CTestDialogApp dialog based application.
//See TestButton.cpp for the implementation of this class
//
//Note: uses Microsoft Foundation Library (MFC);
//      Microsoft Windows specific (Win).
class CTestDialogApp : public CWinApp
{
public:
  CTestDialogApp();

  //Overrides
public:
  virtual BOOL InitInstance();
  virtual bool SetMainWnd();
  virtual void DestroyMainWnd(CWnd* pObject = NULL);

  //Implementation

  DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////////
extern CTestDialogApp theApp;

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  2    Biblioteka1.1         2003-08-27 18:12:11  Darko           renamed class
 *  1    Biblioteka1.0         2003-08-26 01:37:15  Darko
 * $
 *****************************************************************************/
