//$Workfile: KLogEntry.js$: script file
//$Revision: 2$ $Date: 2006-12-06 13:31:26$
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
        <span id="ID_LOGDATE" class="logDate">YYYY-MM-DD</span>
        <span id="ID_LOGTIME" class="logTime">hh:mm:ss</span>
        <span id="ID_LOGLVL"  class="Level">Level</span>
        <span id="ID_LOGNOTE" class="logNote">description<span>
      </div>
 */
CLogEntry.prototype.toHtml = function()
{
var strElement =
   '<div id="ID_LOGENTRY" class="logEntry" title="' + this.m_iLevel + '">\n' +
   '  <span id="ID_LOGDATE" class="logDate">' + this.m_dateRecord.toISOString() +'<\/span>\n' + //TODO toDate
   '  <span id="ID_LOGTIME" class="logTime">' + this.m_dateRecord.toISOString() +'<\/span>\n' + //TODO toTime
   '  <span id="ID_LOGLVL"  class="Level' + this.m_iLevel +'">'+ this.m_iLevel +'<\/span>\n' + //TODO toLvlDescription
   '  <span id="ID_LOGNOTE" class="logNote">' + this.m_strRecord + '<\/span>\n<\/dic>\n';
return strElement;
};

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2006-12-06 11:42:37  Darko Kolakovic
 * $
 *****************************************************************************/
