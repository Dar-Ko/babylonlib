//$Workfile: S:\_SrcPool\Js\KLogger.js$: script file
//$Revision: 1$ $Date: 2006-12-01 17:48:11$
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
this logStart= new Date().getTime(); //time of log creation
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
this.m_tmRecord = new Date();                      //log entry time
this.m_strRecord = (strMessage ? strMessage : ""); //log record
this.m_ilevel = (iLevel? iLevel : 0);              //log record rank

/*Returns date and time in format described by ISO 8601:2000
  'Data Elements and Interchange Formats' standard.
 */
this.m_tmRecord.toISOString = function()
  {
  var iYear = this.getYear();
  if(iYear < 100 && iYear > 0)
    iYear += 1900;
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
  }

/*Returns formatted log entry
 */
this.toString = function()
  {
  return m_tmRecord.toISOString() + ":\t" + m_iLevel + ":\t" + m_strRecord;
  }
};

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2006-12-01 17:48:11  Darko Kolakovic
 * $
 *****************************************************************************/
