/*$Workfile: KDbgEvent.c$: implementation file
  $Revision: 1$ $Date: 2004-11-17 17:45:11$
  $Author: Darko Kolakovic$

  Dumps Palm OS event types
  Copyright: CommonSoft Inc.
  2004-11-01 Darko Kolakovic
 */

/* Group=Diagnostic */

#include <PalmOS.h>

#ifndef TRACE1
  #include "KTrace.h"
#endif

void DumpEvent(const EventType event);

/*----------------------------------------------------------------------------*/
/*Dump event types. The EventType structure contains all the data associated
  with a system event. All event types have some common data. Most events also
  have data specific to those events.

        typedef struct
          {
          eventsEnum   eType;    //specifies the type of the event.
          Boolean      penDown;  //true if the pen was down at the time
                                 //of the event, otherwise false
          UInt8        tapCount; //the number of taps received at this location.
          Int16        screenX;  //Window-relative position of the pen in pixels
          Int16        screenY;  //Window-relative position of the pen in pixels
          union
            {
            ...
            } data;             //the specific data for an event, if any.
          } EventType;

  See also: <Event.h>

  Note: Palm OS specific (PalmOS).
 */
void DumpEvent(const EventType event //[in] a system event
              )
{
if ((event.eType >= firstINetLibEvent) && (event.eType < firstWebLibEvent) )
  {
  TRACE(_T("netLibEvent %X\n"), (UInt32)event.eType);
  }
else if ((event.eType >= firstWebLibEvent) &&
         ((UInt32)(event.eType) < (UInt32)(firstWebLibEvent + 0x100)) )
  {
  TRACE(_T("webLibEvent %X\n"), (UInt32)event.eType);
  }
else if ((event.eType >= firstUserEvent) &&
         (event.eType <= lastUserEvent) )
  {
  TRACE(_T("userEvent %X\n"), (UInt32)event.eType);
  }
else
  {
  switch(event.eType)
    {
    case nilEvent             : TRACE(_T("nilEvent %X\n")             , (UInt32)event.eType); break;
    case penDownEvent         : TRACE(_T("penDownEvent %X\n")         , (UInt32)event.eType); break;
    case penUpEvent           : TRACE(_T("penUpEvent %X\n")           , (UInt32)event.eType); break;
    case penMoveEvent         : TRACE(_T("penMoveEvent %X\n")         , (UInt32)event.eType); break;
    case keyDownEvent         : TRACE(_T("keyDownEvent %X\n")         , (UInt32)event.eType); break;
    case winEnterEvent        : TRACE(_T("winEnterEvent %X\n")        , (UInt32)event.eType); break;
    case winExitEvent         : TRACE(_T("winExitEvent %X\n")         , (UInt32)event.eType); break;
    case ctlEnterEvent        : TRACE(_T("ctlEnterEvent %X\n")        , (UInt32)event.eType); break;
    case ctlExitEvent         : TRACE(_T("ctlExitEvent %X\n")         , (UInt32)event.eType); break;
    case ctlSelectEvent       : TRACE(_T("ctlSelectEvent %X\n")       , (UInt32)event.eType); break;
    case ctlRepeatEvent       : TRACE(_T("ctlRepeatEvent %X\n")       , (UInt32)event.eType); break;
    case lstEnterEvent        : TRACE(_T("lstEnterEvent  %X\n")       , (UInt32)event.eType); break;
    case lstSelectEvent       : TRACE(_T("lstSelectEvent %X\n")       , (UInt32)event.eType); break;
    case lstExitEvent         : TRACE(_T("lstExitEvent %X\n")         , (UInt32)event.eType); break;
    case popSelectEvent       : TRACE(_T("popSelectEvent %X\n")       , (UInt32)event.eType); break;
    case fldEnterEvent        : TRACE(_T("fldEnterEvent %X\n")        , (UInt32)event.eType); break;
    case fldHeightChangedEvent: TRACE(_T("fldHeightChangedEvent %X\n"), (UInt32)event.eType); break;
    case fldChangedEvent      : TRACE(_T("fldChangedEvent %X\n")      , (UInt32)event.eType); break;
    case tblEnterEvent        : TRACE(_T("tblEnterEvent  %X\n")       , (UInt32)event.eType); break;
    case tblSelectEvent       : TRACE(_T("tblSelectEvent %X\n")       , (UInt32)event.eType); break;
    case daySelectEvent       : TRACE(_T("daySelectEvent %X\n")       , (UInt32)event.eType); break;
    case menuEvent            : TRACE(_T("menuEvent %X\n")            , (UInt32)event.eType); break;
    case appStopEvent         : TRACE(_T("appStopEvent %X\n")         , (UInt32)event.eType); break;
    case frmLoadEvent         : TRACE(_T("frmLoadEvent %X\n")         , (UInt32)event.eType); break;
    case frmOpenEvent         : TRACE(_T("frmOpenEvent %X\n")         , (UInt32)event.eType); break;
    case frmGotoEvent         : TRACE(_T("frmGotoEvent %X\n")         , (UInt32)event.eType); break;
    case frmUpdateEvent       : TRACE(_T("frmUpdateEvent %X\n")       , (UInt32)event.eType); break;
    case frmSaveEvent         : TRACE(_T("frmSaveEvent %X\n")         , (UInt32)event.eType); break;
    case frmCloseEvent        : TRACE(_T("frmCloseEvent %X\n")        , (UInt32)event.eType); break;
    case frmTitleEnterEvent   : TRACE(_T("frmTitleEnterEvent %X\n")   , (UInt32)event.eType); break;
    case frmTitleSelectEvent  : TRACE(_T("frmTitleSelectEvent %X\n")  , (UInt32)event.eType); break;
    case tblExitEvent         : TRACE(_T("tblExitEvent %X\n")         , (UInt32)event.eType); break;
    case sclEnterEvent        : TRACE(_T("sclEnterEvent %X\n")        , (UInt32)event.eType); break;
    case sclExitEvent         : TRACE(_T("sclExitEvent %X\n")         , (UInt32)event.eType); break;
    case sclRepeatEvent       : TRACE(_T("sclRepeatEvent %X\n")       , (UInt32)event.eType); break;
    case tsmFepModeEvent      : TRACE(_T("tsmFepModeEvent %X\n")      , (UInt32)event.eType); break;
    case menuCmdBarOpenEvent  : TRACE(_T("menuCmdBarOpenEvent %X\n")  , (UInt32)event.eType); break;
    case menuOpenEvent        : TRACE(_T("menuOpenEvent %X\n")        , (UInt32)event.eType); break;
    case menuCloseEvent       : TRACE(_T("menuCloseEvent %X\n")       , (UInt32)event.eType); break;
    case frmGadgetEnterEvent  : TRACE(_T("frmGadgetEnterEvent %X\n")  , (UInt32)event.eType); break;
    case frmGadgetMiscEvent   : TRACE(_T("frmGadgetMiscEvent %X\n")   , (UInt32)event.eType); break;
    default: TRACE(_T("unknown event %X\n"), (UInt32)event.eType);
    }
  }
}

/* ////////////////////////////////////////////////////////////////////////// */
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2004-11-17 17:45:11  Darko Kolakovic 
 * $
 *****************************************************************************/
