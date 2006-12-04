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
this.m_hLogOut = this.getWndOut(); //init();
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
  return null; //Failed to create new window

  //Create empty logbook document
if (hWnd.document != null)
  {
  hWnd.document.open();
  hWnd.document.write("<html>\n<head>\n" +
                      "<title>Logbook<\/title>\n" +
                      "<style type='text/css'>\n" +
                      "  .DEBUG{ color: green; }\n" +
                      "  .INFO{ color: navy; }\n" +
                      "  .WARN{ color: black; }\n" +
                      "  .ERROR{ color: red; }\n" +
                      "<\/style>\n" +
                      "<\/head>\n" +
                      "<body>\n<div id='ID_LOGBOOK1'>\n<\/div>\n<\/body>\n" +
                      "<\/html>\n");
  hWnd.document.close();
  }

if (hWnd.document.getElementById == undefined)
  return null; //IE 5.0 missing method.

var hLogbook = hWnd.document.getElementById('ID_LOGBOOK');
if (hLogbook == null) //Create missing element
    return this.getDivOut(hWnd.document);

return hLogbook;
};

//-----------------------------------------------------------------------------
/*Appends the new text area with Id ID_LOGBOOK to the existing document, to be
  the estination for the log entries.

  Returns the Logbook object if successful; otherwise returns null;
 */
CLogger.prototype.getDivOut = function(oDocument //=null [in] the document where
                                       //log entries will appear or, if null,
                                       //the current document
                                      )
{
if (oDocument == null)
  oDocument = this.document;
if (oDocument == null)
  return null; //Failed to obtain the working document
if (oDocument.getElementById == undefined)
  return null; //IE 5.0 missing method.

var hBody = oDocument.getElementsByTagName("body");
if (hBody == null)
  return null;

var hLogbook = oDocument.getElementById('ID_LOGBOOK');
if (hLogbook == null) //Create missing element
  {
  hLogbook = oDocument.createElement("div");
  hLogbook.setAttribute("id","ID_LOGBOOK");
  hBody.item(0).appendChild(hLogbook);
  hHr = oDocument.createElement("hr");
  hBody.item(0).appendChild(hHr);
  }
hLogbook.setAttribute("style","left: 16px; width: 100%; position: relative;");
return hLogbook;
};

//-----------------------------------------------------------------------------
/*Writes new entry to the logbook, if the log is created and the text is not
  an empty string.

  Returns true if successful; otherwise returns false;
 */
CLogger.prototype.WriteLn = function(strEntry //[in] text to be added to the log
                                    )
{
if ((strEntry != null) && (strEntry != ""))
  {
  if (this.m_hLogOut != null)
    {
    var oNewElement = this.m_hLogOut.appendChild(
        strEntry.createElement("p"));
    oNewElement.innerHTML = strEntry;

    return true;
    }
  }
return false;
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
