/*$Workfile: KAppExit.cpp$: implementation file
  $Revision: 1$ $Date: 2004-11-12 14:55:24$
  $Author: Darko Kolakovic$

  Application's default processing on termination.
  Copyright: CommonSoft Inc.
  2004-10-21 Darko Kolakovic
 */

/* Group=Palm */

#include <PalmOS.h>
#include "stdafx.h"

extern "C" int AppExit(void);

//-----------------------------------------------------------------------------
/*This method is called from AppRun() each time a copy of your application
  terminates, usually as a result of the user quitting the application.
  Deafult implemetation saves the current state of the application and closes
  all open forms by calling FrmCloseAllForms().

  Returns: application's exit code; 0 indicates no errors, and values greater
  than 0 indicate an error.
 */
int AppExit(void)
{
  /*Close all the open forms. */
FrmCloseAllForms();
return 0;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-12 14:55:24  Darko Kolakovic 
 * $
 * 0 CodeWarrior 9 wizard-generated code is based on code adapted from the
 * stationery files distributed as part of the Palm OS SDK 4.0.
 *****************************************************************************/
