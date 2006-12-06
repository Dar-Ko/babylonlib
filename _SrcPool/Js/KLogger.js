//$Workfile: KLogger.js$: script file
//$Revision: 3$ $Date: 2006-12-04 17:52:17$
//$Author: Darko Kolakovic$
//
//Events or messages recorder
//Copyright: CommonSoft Inc
//2006-12 Darko Kolakovic

//-----------------------------------------------------------------------------
/*A class that records events or messages to an output stream or a log file.

 */
function CLogger()
{
this.tmStart= new Date().getTime(); //time of log creation in ms since
                                    //1970-01-01T00:00:00
this.m_hLogOut = null;              //output stream
this.m_hLogOut = new CLogWnd();
//this.getWndOut(); //init();
               //this.getDivOut();
};

//-----------------------------------------------------------------------------
/*Creates the new window, named LOGBOOK, as destination for log entries.
  The ID of the area for the logs is ID_LOGBOOK.

  Returns the Logbook object if successful; otherwise returns null;
 */
CLogger.prototype.getWndOut = function()
{
hWnd = window.open("", //Optional URL of the document or blank page.
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
                      "<body>\n<div id='ID_LOG_JOK'>\n<\/div>\n<\/body>\n" +
                      "<\/html>\n");
  hWnd.document.close();
  }

if (hWnd.document.getElementById == undefined)
  return null; //IE 5.0 missing method.

var hLog = hWnd.document.getElementById('ID_LOG');
if (hLog == null) //Create missing element
  return this.getDivOut(hWnd.document);
return hLog;
};

//-----------------------------------------------------------------------------
/*Appends the new text area with Id ID_LOG to the existing document, to be
  the destination for the log entries.

  Returns the Logbook object if successful; otherwise returns null;
 */
CLogger.prototype.getDivOut = function(oDocument //=null [in] the document where
                                       //log entries will appear or, if null,
                                       //the current document
                                      )
{
if (oDocument == null)
  oDocument = document;
if (oDocument == null)
  return null; //Failed to obtain the working document
if (oDocument.getElementById == undefined)
  return null; //IE 5.0 missing method.

var hBody = oDocument.getElementsByTagName("body");
if (hBody == null)
  return null;

var hLog = oDocument.getElementById('ID_LOG');
if (hLog == null) //Create missing element
  {
  var hLogbook = oDocument.createElement("div"); //Wrapper element
  hLogbook.setAttribute("id","ID_LOGBOOK");
  hBody.item(0).appendChild(hLogbook);
  hLogbook.appendChild(oDocument.createElement("hr"));
  hLog = oDocument.createElement("div");
  hLogbook.setAttribute("id","ID_LOG");
  hLogbook.appendChild(hLog);
  hLogbook.appendChild(oDocument.createElement("hr"));
  }
hLogbook.setAttribute("style","left: 16px; width: 90%; position: relative;");

//If ownerDocument property is not supported, add new one
if(hLogbook.ownerDocument == null)
  hLogbook.ownerDocument = oDocument;
if(hLog.ownerDocument == null)
  hLog.ownerDocument = oDocument;

hLog.m_hOwner = this; //owner object of the logbook

return hLog;
};

//-----------------------------------------------------------------------------
/*Writes new entry to the logbook, if the log is created and the text is not
  an empty string.

  Returns true if successful; otherwise returns false;
 */
CLogger.prototype.Append = function(strEntry //[in] text to be added to the log
                                    )
{
if ((strEntry != null) && (strEntry != ""))
  {
  if ((this.m_hLogOut != null) && (this.m_hLogOut.Append != null))
    {
    return this.m_hLogOut.Append(strEntry,
                                (new Date().getTime() - this.tmStart) + "ms");
    }
  }
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

var hBody = oDocument.getElementsByTagName("body");
if (hBody == null)
  return null;

var hLog = oDocument.getElementById('ID_LOG');
if (hLog == null) //Create missing element
  {
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
/*Appends the new log entry to the logbook text area.

  Returns true if successful; otherwise returns false;
 */
CLogElement.prototype.Append = function(strEntry, //[in] text to be added to the log
                                        strEntryTag //=null [in] a tag that will
                                        //be added to the log entry or current
                                        //time in ms as default entry title
                                       )
{
if ((strEntry != null) && (strEntry != ""))
  {
  if (this.ownerDocument != null)
    {
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

////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
/*A log record of events. Stores time of the event, description and
  the event grade.
*/
function CLogEntry(strMessage, //="" [in] event description
                   iLevel      //=null [in] event rank [NONE, ERROR]
                  )
{
this.m_dateRecord = new Date();                    //log entry time
this.m_strRecord = (strMessage ? strMessage : ""); //log record
this.m_iLevel = (iLevel? iLevel : 0);              //log record rank

if (this.m_dateRecord.getFullYear == undefined)
  {
  /*Returns year in the Gregorian Calendar, represented by four digits in
    the range [0000, 9999]. (JavaScript 1.0)
   */
  this.m_dateRecord.getFullYear = function()
    {
    var iYear = this.getYear();
    if(iYear < 100)
      iYear += 1900;
    return iYear;
    }
  };

/*Returns date and time in extended format described by ISO 8601:2000
  'Data Elements and Interchange Formats' standard.
 */
this.m_dateRecord.toISOString = function()
  {
  var iYear = this.getFullYear();
  var vMonth = this.getMonth() + 1;
  vMonth = (vMonth < 10 ? "0" : "") + vMonth;
  var vDay = this.getDate();
  vDay = (vDay < 10 ? "0" : "") + vDay;
  var vHour = this.getHours();
  vHour = (vHour < 10 ? "0" : "") + vHour;
  var vMin = this.getMinutes();
  vMin = (vMin < 10 ? "0" : "") + vMin;
  var vSec = this.getSeconds();
  vSec = (vSec < 10 ? "0" : "") + vSec;

  return (iYear + "-" + vMonth  + "-" + vDay + "T" +
          vHour + ":" + vMin    + ":" + vSec           );
  };
};

/*Returns formatted log entry:
      YYYY-MM-DDThh:mm:ss:\tLevel:\tdescription
 */
CLogEntry.prototype.toString = function()
{
return this.m_dateRecord.toISOString() + ":\t" +
       this.m_iLevel + ":\t" +
       this.m_strRecord;
};

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2006-12-01 17:48:11  Darko Kolakovic
 * $
 *****************************************************************************/
