//$Workfile: KLogger.js$: script file
//$Revision: 5$ $Date: 2006-12-06 17:57:20$
//$Author: Darko Kolakovic$
//
//Events or messages recorder
//Copyright: CommonSoft Inc
//2006-12 Darko Kolakovic

///////////////////////////////////////////////////////////////////////////////
// Constants
var LOG_DOM    = 0; //logbook is DOM element with id=ID_LOG
var LOG_WND    = 1; //logbook is pop-up window with name logbook
var LOG_FILE   = 2; //logbook is file with default name event.log
var LOG_STDOUT = 3; //logging to standard output or to the current HTML
                    //document, depending of script shell.

///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
/*A class that records events or messages to an output stream or a log file.

 */
function CLogger(iOutputType //=LOG_DOM [in] log type
                )
{

this.tmStart= new Date().getTime(); //time of log creation in ms since
                                    //1970-01-01T00:00:00
this.m_hLogOut = null;              //output stream
this.m_iType = (iOutputType == null)  ?
               LOG_DOM : (+iOutputType); //plus sign converts var to number
this.m_hLogOut = this.Create(this.m_iType);
};

//-----------------------------------------------------------------------------
/*Creates logger target object.

  Returns the Logbook object if successful; otherwise returns null;
 */
CLogger.prototype.Create = function(iType //=null [in] the document where
                                       //log entries will appear or, if null,
                                       //the current document
                                      )
{
var hLog = null;
switch (iType)
  {
  case LOG_DOM:  //Output to DOM element with id=ID_LOG
    if((hLog = new CLogElement()) != null)
      break;
    //Try next target
  case LOG_WND:  //Output to pop-up window
    if((hLog = new CLogWnd()) != null)
      break;
    //Try next target
  case LOG_FILE: //Output to a file, if file system is avaliable
    if((hLog = new CLogWnd()) != null) //TODO
      break;
    //Try next target
  case LOG_STDOUT: //Output to the standard stream or to the current HTML document
  default:
    hLog = new CLogWnd(); //TODO
  }
return hLog;
}

//-----------------------------------------------------------------------------
/*Writes new entry to the logbook, if the log is created and the text is not
  an empty string.

  Returns true if successful; otherwise returns false;
 */
CLogger.prototype.Append = function(strEntry //[in] text to be added to the log
                                    )
{
if ((this.m_hLogOut != null) && (this.m_hLogOut.Append != null))
  {
  return this.m_hLogOut.Append(strEntry,
                              (new Date().getTime() - this.tmStart) + "ms");
  }
if(document != null) //Try to salvage the message
  document.writeln(strEntry);
return false;
};

///////////////////////////////////////////////////////////////////////////////
/*This class records log entries to the DOM element with id=ID_LOG.
  A new logbook element will be added to the DOM structure if the current
  document does not have such element.

  Returns the Log object if successful; otherwise returns null;
 */
function CLogElement(oDocument //=null [in] the document where
                               //log entries will appear or, if null,
                               //the current document
                    )
{
if (oDocument == null)
  oDocument = document;
var hLog = this.Create(oDocument); //log object
if (hLog != null)
  {
  hLog.Append = this.Append; //Inject methods to the 'base' object
  }
return hLog;
}

//-----------------------------------------------------------------------------
/*Creates element with id = ID_LOG, if such element does not exist.

  Returns the Logbook object if successful; otherwise returns null;
 */
CLogElement.prototype.Create = function (oDocument //[in] the document where
                                                   //log entries will appear
                                         )
{
if (oDocument == null)
  return null; //Failed to obtain the working document
if (oDocument.getElementById == undefined)
  return null; //IE 5.0 missing method.

var hLog = oDocument.getElementById('ID_LOG');
if (hLog == null) //Create missing element
  {
  var hBody = oDocument.getElementsByTagName("body");
  if (hBody == null)
    return null;
  var hLogbook = oDocument.createElement("div"); //Wrapper element
  hLogbook.setAttribute("id","ID_LOGBOOK");
  hBody.item(0).appendChild(hLogbook);
  hLogbook.appendChild(oDocument.createElement("hr"));
  hLog = oDocument.createElement("div");
  hLogbook.setAttribute("id","ID_LOG");
  hLogbook.appendChild(hLog);
  hLogbook.appendChild(oDocument.createElement("hr"));
  hLogbook.setAttribute("style","left: 16px; width: 90%; position: relative;");
  }

//If ownerDocument property is not supported, add new one
if(hLog.ownerDocument == null)
  hLog.ownerDocument = oDocument;

return hLog;
}

//-----------------------------------------------------------------------------
/*Appends the new log entry to the logbook text area. The empty entry will be
  replaced with non-breakable space.

  Returns true if successful; otherwise returns false;
 */
CLogElement.prototype.Append = function(strEntry, //[in] text to be added to the log
                                        strEntryTag //=null [in] a tag that will
                                        //be added to the log entry or current
                                        //time in ms as default entry title
                                       )
{
if (this.ownerDocument != null)
  {
  if ((strEntry == null) || (strEntry == ""))
    strEntry = "&nbsp;" //FixMe! string seen is &amp;nbsp; - not ' ' as supposed to be! D.K.
  //Note: createElement(any) requires Internet Explorer 5.
  var eEntry = this.ownerDocument.createElement("span");
  eEntry.className = "logentry";
  //Add line number
  eEntry.title = ((strEntryTag != null) && (strEntryTag != "")) ?
                 strEntryTag : (new Date().getTime() + "ms");
  eEntry.appendChild(this.ownerDocument.createTextNode(strEntry));
  this.appendChild(eEntry);
  //Add new line
  this.appendChild(this.ownerDocument.createElement("br"));
  //Make the last entry visible in the viewport
  if (this.offsetHeight > this.scrollHeight)
    this.scrollTop = 0;
  else
    this.scrollTop = this.scrollHeight;

  return true;
  }
return false;
}

///////////////////////////////////////////////////////////////////////////////
/*The class creates the new window, named LOGBOOK, as destination for the log
  entries. The ID of the text area for the logs is ID_LOG.

  Returns the Log object if successful; otherwise returns null;
 */
function CLogWnd()
{
var hLog = this.Create(); //log object
if ((hLog != null) && ( hLog.Append != null))
  return hLog; //Return 'base' class
return null;
}

//-----------------------------------------------------------------------------
/*Creates the new window, named LOGBOOK, as destination for log entries.
  The ID of the area for the logs is ID_LOGBOOK.

  Returns the Logbook object if successful; otherwise returns null;
 */
CLogWnd.prototype.Create = function()
{
var hWnd = window.open("", //Optional URL of the document or blank page.
                       "LOGBOOK", //Optional target Id to be used in forms
                       ("left=10,"   + //left position relative to
                                       //the upper-left corner of the screen [px]
                       "top=20,"     + //top position relative to
                                       //the upper-left corner of the screen [px]
                       "width=600,"  + //width of the window [px]
                       "height=450," + //height of the window [px]
                       "scrollbars=yes," + //display horizontal and vertical scroll bars
                       "resizable=yes," + //display resize handles
                       "status=no," +     //display a status bar
                       "toolbar=no," +    //display browser's toolbar
                       "location=no"      //display the input field for URLs
                      ));
if (hWnd == null)
  return null; //Failed to create new pop-up window;
               //probably pop-up blocking is enabled.

  //Create empty logbook document
if (hWnd.document != null)
  {
  hWnd.document.open();
  hWnd.document.write('<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" ' +
                      '  "http://www.w3.org/TR/html4/loose.dtd">' +
                      "<html>\n<head>\n" +
                      "<title>Logbook<\/title>\n" +
                      "<style type='text/css'>\n" +
                      "  .DEBUG{ color: green; }\n" +
                      "  .INFO{ color: navy; }\n" +
                      "  .WARN{ color: black; }\n" +
                      "  .ERROR{ color: red; }\n" +
                      "<\/style>\n" +
                      "<\/head>\n" +
                      "<body>\n<div id='ID_LOG'>\n<\/div>\n<\/body>\n" +
                      "<\/html>\n");
  hWnd.document.close();
  }

//Return log element
var hLog = new CLogElement(hWnd.document);
return hLog;
};

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2006-12-01 17:48:11  Darko Kolakovic
 * $
 *****************************************************************************/
