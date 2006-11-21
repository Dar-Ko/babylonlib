/*$Workfile: TestDialogApp.h$: header file
  $Revision: 1$ $Date: 2006-09-27 22:52:57$
  $Author: Darko$
  
  main header file for the application
  Copyright: CommonSoft Inc
  2003-08-25 Darko Kolakovic
 */

// Group=Samples

#pragma once

#ifndef __AFXWIN_H__
  #error include 'stdafx.h' before including this file for PCH
#endif

#include "Resource.h"   // main symbols

///////////////////////////////////////////////////////////////////////////////
//TestDialogApp dialog based application.
//See TestButton.cpp for the implementation of this class
//
//Note: uses Microsoft Fundation Library (MFC);
//      Microsoft Windows specific (Win).
class TestDialogApp : public CWinApp
{
public:
  TestDialogApp();

  //Overrides
public:
  virtual BOOL InitInstance();
  virtual bool SetMainWnd();
  virtual void DestroyMainWnd();

  //Implementation

  DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////////////////
extern TestDialogApp theApp;

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2006-09-27 22:52:57  Darko           
 * $
 *****************************************************************************/
