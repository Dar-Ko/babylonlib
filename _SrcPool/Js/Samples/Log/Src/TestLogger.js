/*$Workfile: TestLogger.js$: script file
  $Revision: 3$ $Date: 2006-12-04 17:51:05$
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
  function CTestCase (oValue, //[in] object to be evaluated
                      strValue, //="" [in] expected test object string representation
                      bTestResult //=false [in] expected result of the test
                     )
    {
    this.oValue = "<null>";
    this.strValue = "";
    this.bResult = false;
    if (oValue != undefined)
      this.oValue = oValue; //object
    if (strValue != undefined)
      this.strValue += strValue; //string by contract
    if (bTestResult != undefined)
      this.bResult = (bTestResult == true); //boolean by contract
    };

  //TESTENTRY logEntry =
  //  {_T("CLogger()"), _T("KLogger.js"), bRes};
  var oLog = new CLogger(); //logbook
  bRes = (oLog != undefined);
  if (bRes && (oLog.tmStart != undefined))
    {
    TsWriteToViewLn("Log created after " + oLog.tmStart + "ms since 1970-01-01T00:00:00");
    }
  else
    bRes = false;

    //TESTENTRY logEntry =
    //  {_T("CLogger::WriteLn()"), _T("KLogger.js"), bRes};
  if (bRes && (oLog.WriteLn != undefined))
    {
    if (oLog.WriteLn("Ursus arctos horribilis"));
    TsWriteToViewLn("New log entry. ");
    }
  else
    bRes = false;
    //logEntry.m_bResult = bRes;
    //LogTest(&logEntry);


  //logEntry.m_bResult = bRes;
  //LogTest(&logEntry);
  if(bRes)
    {
    //TESTENTRY logEntry =
    //  {_T("CLogEntry()"), _T("KLogger.js"), bRes};
    var oLogEntry = new CLogEntry(); //empty log record
    bRes = (oLogEntry != undefined);
    if (bRes && (oLogEntry.m_dateRecord != undefined))
      {
      TsWriteToViewLn("Log entry created at " + oLogEntry.m_dateRecord.toUTCString() + " UTC");
      if (oLogEntry.m_dateRecord.toISOString != undefined )
        {
        TsWriteToViewLn("Log entry created at " + oLogEntry.m_dateRecord.toISOString());
        }
      else
        bRes = false;
      }
    else
      bRes = false;
    //logEntry.m_bResult = bRes;
    //LogTest(&logEntry);
    }

    //TESTENTRY logEntry =
    //  {_T("CLogEntry::toString()"), _T("KLogger.js"), bRes};
  if (bRes && (oLogEntry.toString != undefined))
    {
    TsWriteToViewLn("Log empty entry is: " + oLogEntry.toString());
    }
  else
    bRes = false;
    //logEntry.m_bResult = bRes;
    //LogTest(&logEntry);


  if (bRes)
    {
    var arrValue = new Array();
    arrValue[ 0] = new CTestCase(new CLogEntry("Test 0",       0));
    arrValue[ 1] = new CTestCase(new CLogEntry("Test 1",      1));
    arrValue[ 2] = new CTestCase(new CLogEntry("Test 20",     2));
    arrValue[ 3] = new CTestCase(new CLogEntry("Test 30",   3));
    arrValue[ 4] = new CTestCase(new CLogEntry("Test 40",    4));
    arrValue[ 5] = new CTestCase(new CLogEntry("Test 50",     5));
    arrValue[ 6] = new CTestCase(new CLogEntry("Test 60",     6));
    arrValue[ 7] = new CTestCase(new CLogEntry("",                  7));

    while(i < arrValue.length)
      {
      var bLogEntry = true; //result of the validation
      TsWriteToViewLn("" + i + ". " + arrValue[i].oValue);
      oLogEntry.WriteLn(arrValue[i].oValue);
      //if (bHasSpace != arrValue[i].bResult)
      //  {
      //  bRes = false;
      //  break;
      //  }
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
