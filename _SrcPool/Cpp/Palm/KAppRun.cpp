/*$Workfile: KAppRun.cpp$: implementation file
  $Revision: 2$ $Date: 2004-11-12 13:57:36$
  $Author: Darko Kolakovic$

  Entry point for the application.
  Copyright: CommonSoft Inc.
  2004-10-21 Darko Kolakovic
 */

/* Group=Palm */

#include <PalmOS.h>
#include "stdafx.h"

    /*event handler callback routine for the application*/
extern FormEventHandlerType AppEventProc;
extern "C" int AppExit(void);
extern "C" bool AppIdle(long lCount);
extern "C" void AppRun(void);

//-----------------------------------------------------------------------------
/*This method provides a default event processing loop. Run acquires and
  dispatches Palm OS events until the application receives an appStopEvent event.
  The PiltoMain function calls the event loop function, where the event is
  dispatched to appropriate handler. If an event handler returns true, the event
  was handled and will not be processed further.
  If no events are available, which is often true, the method calls AppIdle()
  to do any idle-time processing that you or the framework may need done.
  If there are no events and no idle processing to do, the application waits
  until something happens. When the application terminates, the method calls
  AppExit().
  SysHandleEvent() and MenuHandleEvent() will process Palm system events and
  menu events respectively.
  The AppEventProc() callback function will handle all events regarding
  the application and could be costumized if necessary.


                        (Start)
                           |
                        PilotMain();
                           |
                        AppRun();
                           |
                           +----<-----------------+
                           |                      |
                           |            Process system, menu and
                           |                application events
                           V                      |
           +-Yes--<Is event = appStopEvent?> --No-+
           |
         (Stop)


  Note: Palm OS specific (PalmOS).
 */

void AppRun(void)
{
EventType evtCurrent; /*event to be processed      */
long lCount = 0;      /*"empty event queue" counter*/
bool bEventHandled = false;
  /*number of ticks to wait for an event. Once the specified time has elapsed
    EvtGetEvent() generates a nilEvent.
    To wait indefinitely specify evtWaitForever.
   */
const Int32 WAIT_EVENT_PERIOD = 5*SysTicksPerSecond();

do
  {
  EvtGetEvent(&evtCurrent, WAIT_EVENT_PERIOD);

    //Handle frmLoadEvent event, penDownEvent and keyDownEvent.events in the
    //current menu
  if ( !(bEventHandled = AppEventProc(&evtCurrent)) )
    {
    AppIdle(++lCount);
    }

  if (bEventHandled)
    lCount = 0;

  } while (evtCurrent.eType != appStopEvent);

AppExit();   //Clean it up
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-10-28 13:10:10  Darko Kolakovic
 * $
 * 0 CodeWarrior 9 wizard-generated code is based on code adapted from the
 * stationery files distributed as part of the Palm OS SDK 4.0.
 *****************************************************************************/
