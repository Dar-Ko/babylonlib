/*$Workfile: KAppInit.cpp$: implementation file
  $Revision: 1$ $Date: 2004-11-12 14:55:28$
  $Author: Darko Kolakovic$

  Application's default initialization.
  Copyright: CommonSoft Inc.
  2004-10-21 Darko Kolakovic
 */

/* Group=Palm */

#include <PalmOS.h>
#include "stdafx.h"

#ifndef IDR_MAINFORM
  #error Application initialization requies IDR_MAINFORM resource to be defined!
#endif

extern "C" bool AppInit(void);
extern "C" void SetMainFormId(const UInt32 nMainFormId);

//-----------------------------------------------------------------------------
/*This method initializes an instance of an application and launch
  application's main (default) form. Pointer to this form could be obtained
  with GetMainForm().
  This method is called by the implementation of PalmMain that the framework
  provides.
  Replace AppInit() to implement customized one-time initialization.

  Returns: true if initialization is it is successful; otherwise returns false.

  Note: Palm OS specific (PalmOS).
 */

bool AppInit(void)
{
#if defined (IDR_MAINFORM)
  /*Close any open form (window) and load and open the specified one.
    Note: generates frmCloseEvent, frmLoadEvent and frmOpenEvent events.
   */
  FrmGotoForm(IDR_MAINFORM);
  return true;
#else
  return false;
#endif
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-12 14:55:28  Darko Kolakovic 
 * $
 *****************************************************************************/
