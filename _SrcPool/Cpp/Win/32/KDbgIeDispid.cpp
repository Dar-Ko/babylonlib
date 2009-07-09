/*$RCSfile: KDbgIeDispid.cpp,v $: implementation file
  $Revision: 1.5 $ $Date: 2009/07/09 18:11:18 $
  $Author: ddarko $

  Dumps the IExplorer Dispatch Event Ids.

  Note: Microsoft Windows specific (Win32).

  Copyright: babylonlib.sourceforge.net
  2008-07-24 Darko Kolakovic
 */

// Group=Diagnostic

#include "stdafx.h"
#include "ExDispid.h" //IExplorer Dispatch Events (Platform SDK header file)

#if defined _ATL_VER
  #ifndef TRACE
    #include "KTraceAtl.h"
  #endif
#endif

#ifndef TRACE
  #ifndef _T
    #include "KTChar.h"
  #endif
  #include "KTrace.h"
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;

//-----------------------------------------------------------------------------
/*Dumps the IExplorer Dispatch Event Identifier.

  A COM object's methods and properties collectively make up its dispatch
  interface (or dispinterface). Each method and property is identified by a
  unique dispatch identifier (or DispID).
  Event dispatch ID is compiled into the component's type library and then
  used by the host application to bind to events.
  The DISPID for IExplorer events are defined in ExDispid.h.

  Note: Microsoft Windows specific (Win32);

  Returns: zero-terminated string describing IExplorer dispatch event.

  See also: ActiveX, Component Object Model (COM) interfaces. IDispatch::Invoke(),
  ExDispid.h, ExDisp.idl
 */
LPCTSTR DumpIExplorerDispatchId(const DISPID nDispId //[in] dispatch event identifier
                               )
{
LPCTSTR szResult;
switch(nDispId)
  {

  //IExplorer Dispatch Events
  case DISPID_BEFORENAVIGATE             : szResult = _T(" DISPID_BEFORENAVIGATE(100)")            ; break;  //100 this is sent before navigation to give a chance to abort
  case DISPID_NAVIGATECOMPLETE           : szResult = _T(" DISPID_NAVIGATECOMPLETE(101)")          ; break;  //101 in async, this is sent when we have enough to show
  case DISPID_STATUSTEXTCHANGE           : szResult = _T(" DISPID_STATUSTEXTCHANGE(102)")          ; break;  //102 Fired when the status bar text of the object has changed.
  case DISPID_QUIT                       : szResult = _T(" DISPID_QUIT(103)")                      ; break;  //103 Fired when application is quiting.
  case DISPID_DOWNLOADCOMPLETE           : szResult = _T(" DISPID_DOWNLOADCOMPLETE(104)")          ; break;  //104 Fired when a navigation operation finishes, is halted, or fails.
  case DISPID_COMMANDSTATECHANGE         : szResult = _T(" DISPID_COMMANDSTATECHANGE(105)")        ; break;  //105 Fired when the enabled state of a command changes.
  case DISPID_DOWNLOADBEGIN              : szResult = _T(" DISPID_DOWNLOADBEGIN(106)")             ; break;  //106 Fired when a navigation operation is beginning.
  case DISPID_NEWWINDOW                  : szResult = _T(" DISPID_NEWWINDOW(107)")                 ; break;  //107 (obsolete) sent when a new window should be created
  case DISPID_PROGRESSCHANGE             : szResult = _T(" DISPID_PROGRESSCHANGE(108)")            ; break;  //108 sent when download progress is updated
  case DISPID_WINDOWMOVE                 : szResult = _T(" DISPID_WINDOWMOVE(109)")                ; break;  //109 sent when main window has been moved
  case DISPID_WINDOWRESIZE               : szResult = _T(" DISPID_WINDOWRESIZE(110)")              ; break;  //110 sent when main window has been sized
  case DISPID_WINDOWACTIVATE             : szResult = _T(" DISPID_WINDOWACTIVATE(111)")            ; break;  //111 sent when main window has been activated
  case DISPID_PROPERTYCHANGE             : szResult = _T(" DISPID_PROPERTYCHANGE(112)")            ; break;  //112 sent when the PutProperty method is called
  case DISPID_TITLECHANGE                : szResult = _T(" DISPID_TITLECHANGE(113)")               ; break;  //113 sent when the document title changes
  case DISPID_TITLEICONCHANGE            : szResult = _T(" DISPID_TITLEICONCHANGE(114)")           ; break;  //114 sent when the top level window icon may have changed.

  case DISPID_FRAMEBEFORENAVIGATE        : szResult = _T(" DISPID_FRAMEBEFORENAVIGATE(200)")       ; break;  //200 Fired when a new hyperlink is being navigated to in a frame.
  case DISPID_FRAMENAVIGATECOMPLETE      : szResult = _T(" DISPID_FRAMENAVIGATECOMPLETE(201)")     ; break;  //201 Fired when a new hyperlink is being navigated to in a frame.
  case DISPID_FRAMENEWWINDOW             : szResult = _T(" DISPID_FRAMENEWWINDOW(204)")            ; break;  //204 Fired when a new window should be created.

  case DISPID_BEFORENAVIGATE2            : szResult = _T(" DISPID_BEFORENAVIGATE2(250)")           ; break;  //250 hyperlink clicked on
  case DISPID_NEWWINDOW2                 : szResult = _T(" DISPID_NEWWINDOW2(251)")                ; break;  //251 Fired when a new window is to be created.
  case DISPID_NAVIGATECOMPLETE2          : szResult = _T(" DISPID_NAVIGATECOMPLETE2(252)")         ; break;  //252 UIActivate new document
  case DISPID_ONQUIT                     : szResult = _T(" DISPID_ONQUIT(253)")                    ; break;  //253 Fired before the Microsoft Internet Explorer application quits.
  case DISPID_ONVISIBLE                  : szResult = _T(" DISPID_ONVISIBLE(254)")                 ; break;  //254 sent when the window goes visible/hidden
  case DISPID_ONTOOLBAR                  : szResult = _T(" DISPID_ONTOOLBAR(255)")                 ; break;  //255 sent when the toolbar should be shown/hidden
  case DISPID_ONMENUBAR                  : szResult = _T(" DISPID_ONMENUBAR(256)")                 ; break;  //256 sent when the menubar should be shown/hidden
  case DISPID_ONSTATUSBAR                : szResult = _T(" DISPID_ONSTATUSBAR(257)")               ; break;  //257 sent when the statusbar should be shown/hidden
  case DISPID_ONFULLSCREEN               : szResult = _T(" DISPID_ONFULLSCREEN(258)")              ; break;  //258 sent when kiosk mode should be on/off
  case DISPID_DOCUMENTCOMPLETE           : szResult = _T(" DISPID_DOCUMENTCOMPLETE(259)")          ; break;  //259 new document goes ReadyState_Complete
  case DISPID_ONTHEATERMODE              : szResult = _T(" DISPID_ONTHEATERMODE(260)")             ; break;  //260 sent when theater mode should be on/off
  case DISPID_ONADDRESSBAR               : szResult = _T(" DISPID_ONADDRESSBAR(261)")              ; break;  //261 sent when the address bar should be shown/hidden
  case DISPID_WINDOWSETRESIZABLE         : szResult = _T(" DISPID_WINDOWSETRESIZABLE(262)")        ; break;  //262 sent to set the style of the host window frame
  case DISPID_WINDOWCLOSING              : szResult = _T(" DISPID_WINDOWCLOSING(263)")             ; break;  //263 sent before script window.close closes the window
  case DISPID_WINDOWSETLEFT              : szResult = _T(" DISPID_WINDOWSETLEFT(264)")             ; break;  //264 sent when the put_left method is called on the WebOC
  case DISPID_WINDOWSETTOP               : szResult = _T(" DISPID_WINDOWSETTOP(265)")              ; break;  //265 sent when the put_top method is called on the WebOC
  case DISPID_WINDOWSETWIDTH             : szResult = _T(" DISPID_WINDOWSETWIDTH(266)")            ; break;  //266 sent when the put_width method is called on the WebOC
  case DISPID_WINDOWSETHEIGHT            : szResult = _T(" DISPID_WINDOWSETHEIGHT(267)")           ; break;  //267 sent when the put_height method is called on the WebOC
  case DISPID_CLIENTTOHOSTWINDOW         : szResult = _T(" DISPID_CLIENTTOHOSTWINDOW(268)")        ; break;  //268 sent during window.open to request conversion of dimensions
  case DISPID_SETSECURELOCKICON          : szResult = _T(" DISPID_SETSECURELOCKICON(269)")         ; break;  //269 sent to suggest the appropriate security icon to show
  case DISPID_FILEDOWNLOAD               : szResult = _T(" DISPID_FILEDOWNLOAD(270)")              ; break;  //270 Fired to indicate the File Download dialog is opening
  case DISPID_NAVIGATEERROR              : szResult = _T(" DISPID_NAVIGATEERROR(271)")             ; break;  //271 Fired to indicate the a binding error has occured
  case DISPID_PRIVACYIMPACTEDSTATECHANGE : szResult = _T(" DISPID_PRIVACYIMPACTEDSTATECHANGE(272)"); break;  //272 Fired when the user's browsing experience is impacted

  //IExplorer Printing Dispatch Events
  case DISPID_PRINTTEMPLATEINSTANTIATION : szResult = _T(" DISPID_PRINTTEMPLATEINSTANTIATION(225)"); break;  //225 Fired to indicate that a print template is instantiated
  case DISPID_PRINTTEMPLATETEARDOWN      : szResult = _T(" DISPID_PRINTTEMPLATETEARDOWN(226)")     ; break;  //226 Fired to indicate that a print templete is completely gone
  case DISPID_UPDATEPAGESTATUS           : szResult = _T(" DISPID_UPDATEPAGESTATUS(227)")          ; break;  //227 Fired to indicate that the spooling status has changed

  default:
    {
    TRACE(_T(" Dispatch event (%u) "), nDispId);
    szResult = _T(" Unknown IExplorer event");
    }
  }
return szResult;
}

///////////////////////////////////////////////////////////////////////////////
#endif //_DEBUG

/******************************************************************************
 * $Log: KDbgIeDispid.cpp,v $
 * Revision 1.5  2009/07/09 18:11:18  ddarko
 * AtlTrace
 *
 * Revision 1.4  2008/07/24 15:24:34  ddarko
 * Comments
 *
 * Revision 1.2  2008/07/24 14:44:26  ddarko
 * _DEBUG
 *
 * Revision 1.1  2008/07/24 14:40:23  ddarko
 * Created
 *
 ******************************************************************************/

/*Dispatch Ids for other inerfaces:

// define the events for the shell wiwndow list
#define DISPID_WINDOWREGISTERED             200     // Window registered
#define DISPID_WINDOWREVOKED                201     // Window Revoked

#define DISPID_RESETFIRSTBOOTMODE       1
#define DISPID_RESETSAFEMODE            2
#define DISPID_REFRESHOFFLINEDESKTOP    3
#define DISPID_ADDFAVORITE              4
#define DISPID_ADDCHANNEL               5
#define DISPID_ADDDESKTOPCOMPONENT      6
#define DISPID_ISSUBSCRIBED             7
#define DISPID_NAVIGATEANDFIND          8
#define DISPID_IMPORTEXPORTFAVORITES    9
#define DISPID_AUTOCOMPLETESAVEFORM     10
#define DISPID_AUTOSCAN                 11
#define DISPID_AUTOCOMPLETEATTACH       12
#define DISPID_SHOWBROWSERUI            13
#define DISPID_SHELLUIHELPERLAST        13

#define DISPID_ADVANCEERROR             10
#define DISPID_RETREATERROR             11
#define DISPID_CANADVANCEERROR          12
#define DISPID_CANRETREATERROR          13
#define DISPID_GETERRORLINE             14
#define DISPID_GETERRORCHAR             15
#define DISPID_GETERRORCODE             16
#define DISPID_GETERRORMSG              17
#define DISPID_GETERRORURL              18
#define DISPID_GETDETAILSSTATE          19
#define DISPID_SETDETAILSSTATE          20
#define DISPID_GETPERERRSTATE           21
#define DISPID_SETPERERRSTATE           22
#define DISPID_GETALWAYSSHOWLOCKSTATE   23

// Dispatch IDS for ShellFavoritesNameSpace Dispatch Events.
//
#define DISPID_FAVSELECTIONCHANGE       1
#define DISPID_SELECTIONCHANGE          2
#define DISPID_DOUBLECLICK              3
#define DISPID_INITIALIZED              4

#define DISPID_MOVESELECTIONUP          1
#define DISPID_MOVESELECTIONDOWN        2
#define DISPID_RESETSORT                3
#define DISPID_NEWFOLDER                4
#define DISPID_SYNCHRONIZE              5
#define DISPID_IMPORT                   6
#define DISPID_EXPORT                   7
#define DISPID_INVOKECONTEXTMENU        8
#define DISPID_MOVESELECTIONTO          9
#define DISPID_SUBSCRIPTIONSENABLED     10
#define DISPID_CREATESUBSCRIPTION       11
#define DISPID_DELETESUBSCRIPTION       12
#define DISPID_SETROOT                  13
#define DISPID_ENUMOPTIONS              14
#define DISPID_SELECTEDITEM             15
#define DISPID_ROOT                     16
#define DISPID_DEPTH                    17
#define DISPID_MODE                     18
#define DISPID_FLAGS                    19
#define DISPID_TVFLAGS                  20
#define DISPID_NSCOLUMNS                21
#define DISPID_COUNTVIEWTYPES           22
#define DISPID_SETVIEWTYPE              23
#define DISPID_SELECTEDITEMS            24
#define DISPID_EXPAND                   25
#define DISPID_UNSELECTALL              26

*/
