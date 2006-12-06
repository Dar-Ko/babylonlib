//$Workfile: S:\_SrcPool\Js\KLogEntry.js$: script file
//$Revision: 1$ $Date: 2006-12-06 11:42:37$
//$Author: Darko Kolakovic$
//
//Log Entry formatter
//Copyright: CommonSoft Inc
//2006-12 Darko Kolakovic


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

//-----------------------------------------------------------------------------
/*Returns formatted log entry:
      YYYY-MM-DDThh:mm:ss:\tLevel:\tdescription
 */
CLogEntry.prototype.toString = function()
{
return this.m_dateRecord.toISOString() + ":\t" +
       this.m_iLevel + ":\t" +
       this.m_strRecord;
};

//-----------------------------------------------------------------------------
/*Returns log entry with HTML markup tags:
      <div id="ID_LOGENTRY" class="logEntry" title="Level">
        <div id="ID_LOGDATE" class="logDate">YYYY-MM-DD</div>
        <div id="ID_LOGTIME" class="logTime">hh:mm:ss</div>
        <div id="ID_LOGLVL"  class="Level">Level</div>
        <div id="ID_LOGNOTE" class="logNote">description<div>
      </div>
 */
CLogEntry.prototype.toHtml = function()
{
var strElement =
   '<div id="ID_LOGENTRY" class="logEntry" title="' + this.m_iLevel + '">\n' +
   '  <div id="ID_LOGDATE" class="logDate">' + this.m_dateRecord.toISOString() +'<\/div>\n' + //TODO toDate
   '  <div id="ID_LOGTIME" class="logTime">' + this.m_dateRecord.toISOString() +'<\/div>\n' + //TODO toTime
   '  <div id="ID_LOGLVL"  class="Level' + this.m_iLevel +'">'+ this.m_iLevel +'<\/div>\n' + //TODO toLvlDescription
   '  <div id="ID_LOGNOTE" class="logNote">' + this.m_strRecord + '<\/div>\n<\/div>\n';
return strElement;
};

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2006-12-06 11:42:37  Darko Kolakovic 
 * $
 *****************************************************************************/
