/*$Workfile: KAppMain.cpp$: implementation file
  $Revision: 2$ $Date: 2004-11-12 14:56:47$
  $Author: Darko Kolakovic$

  Entry point for the application.
  Copyright: CommonSoft Inc.
  2004-10-21 Darko Kolakovic
 */

/* Group=Palm */

#include <PalmOS.h>
#include "stdafx.h"

#ifndef UNUSED_ARG
  #include "KProgCst.h"
#endif

#ifndef IDA_ROMINCOMPATIBILE
  //Hide error message box. To enable it, include resource header file.
  #define IDA_ROMINCOMPATIBILE 0
#endif

extern "C" Err ValidateRomVersion(const UInt32 nRequiredVersion,
                                  const UInt16 nLaunchFlags,
                                  const UInt16 nAlertID
                                 );
extern "C" bool AppInit(void);
extern "C" void AppRun(void);

//-----------------------------------------------------------------------------
/*This is the main entry point for the application. If the version of the curent
  operating system is less than 3.0, error sysErrRomIncompatible will be
  returned.

  Note: Launch Command codes are declared in the header file SystemMgr.h.
        The associated parameter blocks cmdPBP are declared in
        AppLaunchCmd.h, AlarmMgr.h, ExgMgr.h, and Find.h.

    Launch Command Table:
    Command                             Description
    scptLaunchCmdExecuteCmd             Execute the specified Network login
                                        script plugin command.
    scptLaunchCmdListCmds               Provide information about the commands
                                        that your Network script plugin executes.
    sysAppLaunchCmdAddRecord            Add a record to a database.
    sysAppLaunchCmdAlarmTriggered       Schedule next alarm or perform quick
                                        actions such as sounding alarm tones.
    sysAppLaunchCmdAttention            Perform the action requested by
                                        the attention manager.
    sysAppLaunchCmdCardLaunch           Launch the application. This launch code
                                        signifies that the application is being
                                        launched from an expansion card.
    sysAppLaunchCmdCountryChange        Respond to country change.
    sysAppLaunchCmdDisplayAlarm         Display specified alarm dialog or perform
                                        time-consuming alarm-related actions.
    sysAppLaunchCmdExgAskUser           Let application override display of
                                        dialog asking user if they want to
                                        receive incoming data via
                                        the Exchange Manager.
    sysAppLaunchCmdExgGetData           Notify application that it should send
                                        data using the Exchange Manager.
    sysAppLaunchCmdExgPreview           Notify application that it should display
                                        a preview using the Exchange Manager.
    sysAppLaunchCmdExgReceiveData       Notify application that it should receive
                                        incoming data using the Exchange Manager.
    sysAppLaunchCmdFind                 Find a text string.
    sysAppLaunchCmdGoto                 Go to a particular record, display it and
                                        optionally select the specified text.
    sysAppLaunchCmdGoToURL              Launch an application and open a URL.
    sysAppLaunchCmdHandleSyncCallApp    Perform some application-specific operation
                                        at the behest of the application's conduit.
    sysAppLaunchCmdInitDatabase         Initialize database.
    sysAppLaunchCmdLookup               Look up data. In contrast to
                                        sysAppLaunchCmdFind, a level of
                                        indirection is implied. For example, look
                                        up a phone number associated with a name.
    sysAppLaunchCmdNormalLaunch         Launch normally.
    sysAppLaunchCmdNotify               Notify about an event.
    sysAppLaunchCmdOpenDB               Launch application and open a database.
    sysAppLaunchCmdPanelCalledFromApp   Tell preferences panel that it was
                                        invoked from an application, not the
                                        Preferences application.
    sysAppLaunchCmdReturnFromPanel      Tell an application that it's restarting
                                        after preferences panel had been called.
    sysAppLaunchCmdSaveData             Save data. Often sent before find
                                        operations.
    sysAppLaunchCmdSyncNotify           Notify applications that a HotSync has
                                        been completed.
    sysAppLaunchCmdSystemLock           Sent to the Security application to
                                        request that the system be locked down.
    sysAppLaunchCmdSystemReset          Respond to system reset. No UI is allowed
                                        during this launch code.
    sysAppLaunchCmdTimeChange           Respond to system time change.
    sysAppLaunchCmdURLParams            Launch an application with parameters
                                        from the Web Clipping Application Viewer.


    Launch Flags Table:
    Flag                        Functionality
    sysAppLaunchFlagNewGlobals  Set when the system has created and initialized
                                a new globals world for the application.
                                Implies new owner ID for memory chunks.
    sysAppLaunchFlagUIApp       Set when a UI application is being launched.
    sysAppLaunchFlagSubCall     Set when the application is calling its entry
                                point as a subroutine call. This tells
                                the launch code that it's OK to keep the A5
                                (globals) pointer valid through the call.
                                If this flag is set, it indicates that
                                the application is already running as
                                the current application.


  Returns: error code in case of failure or errNone.

  Note: Palm OS specific (PalmOS).
 */
UInt32 PilotMain(UInt16 nCommand,  //[in] specifies what the application should
                                   //do when executed.
                 MemPtr cmdPBP,    //[in] void pointer to a structure containing
                           //custom launch-command-specific parameters or NULL.
                 UInt16 launchFlags//[in] extra information about the launch
                )
{
UNUSED_ARG(cmdPBP);
Err error;
  //minimum OS version required by application
const UInt32 VER_PALMOS_REQUIRED =
            sysMakeROMVersion(3,0,0,sysROMStageDevelopment,0);

#if (REPORTER_TRACES == 1)
  //Open Palm Reporter to display debugging information
  HostTraceInit();
#endif

 //Validate if minimum requirements are statisfied
error = ValidateRomVersion(VER_PALMOS_REQUIRED,  //required OS version number
                           launchFlags,          //launch information
                           IDA_ROMINCOMPATIBILE  //alert box ID
                           );
if (error == errNone)
  {
  switch (nCommand)
    {
    case sysAppLaunchCmdNormalLaunch:
      if( AppInit() )
        {
        AppRun();    //Create main event loop
        }
      break;
    default:
      //Do not launch, if this is not a normal launch
      break;
    }
  }
#if (REPORTER_TRACES == 1)
  //Close Palm Reporter displaying debugging information
  HostTraceClose();
#endif

return errNone;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2004-10-28 13:10:08  Darko Kolakovic
 * $
 * 0 CodeWarrior 9 wizard-generated code is based on code adapted from the
 * stationery files distributed as part of the Palm OS SDK 4.0.
 *****************************************************************************/
