/*$Workfile: KAppIdle.cpp$: implementation file
  $Revision: 1$ $Date: 2004-11-12 14:55:26$
  $Author: Darko Kolakovic$

  Entry point for the application.
  Copyright: CommonSoft Inc.
  2004-10-21 Darko Kolakovic
 */

/* Group=Palm */

#include <PalmOS.h>
#include "stdafx.h"

extern "C" bool AppIdle(long lCount);

//-----------------------------------------------------------------------------
/*This method is called in the default event loop when the appliction's event
  queue is empty.
  Because the application cannot process events until this method returns,
  do not perform lengthy tasks in this function.

  Default implemetation does nothing. Replace this function to perform custom
  idle-time processing.

  Returns: true to receive more idle processing time; false if no more idle
  processing time is needed.

  Note: Palm OS specific (PalmOS).
 */
bool AppIdle(long lCount /*[in] counter incremented each time this procedure is
                           called from application's main event loop.
                           This count is reset to 0 each time a new event is
                           processed. You can use the lCount parameter to
                           determine the relative length of time the application
                           has been idle without processing an event.
                          */

            )
{
UNUSED_ARG(lCount);
return false;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-12 14:55:26  Darko Kolakovic 
 * $
 *****************************************************************************/
