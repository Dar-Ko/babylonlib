/*$Workfile: TestLogger.js$: script file
  $Revision: 5$ $Date: 2006-12-06 17:57:24$
  $Author: Darko Kolakovic$

  Test Logger
  Copyright: CommonSoft Inc.
  2006-11-27  Darko Kolakovic
*/

// Group=Examples

//-----------------------------------------------------------------------------
/*Function validates Logger and its methods.

  Returns: true if test is successful, otherwise returns false.
 */
function TestLogger()
{
TsWriteToViewLn("TestLogger()");
var bRes = false;   //result of the test
debugger;
var i = 0;
try
  {
  /*Container class for testing string inquisition.
   */
  function CTestCase (strValue, //="" [in] log entry
                      bTestResult //=false [in] expected result of the test
                     )
    {
    this.strValue = "";
    this.bResult = false;
    if (strValue != undefined)
      this.strValue += strValue; //string by contract
    if (bTestResult != undefined)
      this.bResult = (bTestResult == true); //boolean by contract
    };

  TsWriteToViewLn("Test CLogger");
  TsWriteToViewLn("Test CLogElement");

  //TESTENTRY logEntry =
  //  {_T("CLogger()"), _T("KLogger.js"), bRes};
  var eLog = document.getElementById('ID_LOG'); //Check for static logbook
  if (eLog == null)
    {
    TsWriteToViewLn("ID_LOG = " + eLog);
    TsWriteToViewLn("Is the element after the script invocation?");
    }

  var oLog = new CLogger(); //logbook
  bRes = (oLog != undefined);
  if (bRes && (oLog.tmStart != undefined))
    {
    TsWriteToViewLn("Log created after " + oLog.tmStart + "ms since 1970-01-01T00:00:00");
    }
  else
    bRes = false;

    //TESTENTRY logEntry =
    //  {_T("CLogger::Append()"), _T("KLogger.js"), bRes};
  if (bRes && (oLog.Append != undefined))
    {
    TsWriteToViewLn("New log entry in the Logbook.");
    bRes = (oLog.Append("Macropus giganteus"));
    }
  else
    {
    bRes = false;
    }
    //logEntry.m_bResult = bRes;
    //LogTest(&logEntry);

  var arrValue = new Array();
  if (bRes)
    {
    arrValue[ 0] = new CTestCase("Macropus agilis"     , true);
    arrValue[ 1] = new CTestCase("Macropus fuliginosus", true);
    arrValue[ 2] = new CTestCase("Macropus rufus"      , true);
    arrValue[ 3] = new CTestCase("Macropus robustus"   , true);
    arrValue[ 4] = new CTestCase("Macropus antilopinus", true);
    arrValue[ 5] = new CTestCase("Macropus rufogriseus", true);
    arrValue[ 6] = new CTestCase("Macropus irma"       , true);
    arrValue[ 7] = new CTestCase(""                    , true);
    TsWriteToViewLn("Append new records:");
    while(i < arrValue.length)
      {
      var bLogEntry = true; //result of the validation
      TsWriteToViewLn("" + i + ". " + arrValue[i].strValue);
      bLogEntry = oLog.Append(arrValue[i].strValue);
      if (bLogEntry != arrValue[i].bResult)
        {
        bRes = false;
        break;
        }
      i++;
      }
    }

  if(bRes)
    {
    TsWriteToViewLn("Test CLogWnd.Create(LOG_WND)");
    oLog.m_hLogOut = oLog.Create(LOG_WND);
    bRes = (oLog.m_hLogOut != null);
    }

  if(bRes)
    {
    TsWriteToViewLn("Append new records to log window:");
    i = 0;
    while(i < arrValue.length)
      {
      var bLogEntry = true; //result of the validation
      TsWriteToViewLn("" + i + ". " + arrValue[i].strValue);
      bLogEntry = oLog.Append(arrValue[i].strValue);
      if (bLogEntry != arrValue[i].bResult)
        {
        TsWriteToViewLn("Are pop-up windows blocked?");
        bRes = false;
        break;
        }
      i++;
      }
    }
  }
catch(error)
  {
  TsWriteToViewLn(error.name + ": " + error.message +
                  ( ((arrValue == undefined) ||
                     (arrValue[0] == undefined))  ? "" :
                  "; value " + i +  ". " + arrValue[i].strValue));
  bRes = false;
  }

//logEntry.m_bResult = bHasSpace;
//LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2006-11-29 13:10:36  Darko Kolakovic
 * $
 *****************************************************************************/
