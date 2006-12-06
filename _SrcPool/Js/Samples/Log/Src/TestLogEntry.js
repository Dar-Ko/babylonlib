/*$Workfile: TestLogEntry.js$: script file
  $Revision: 2$ $Date: 2006-12-06 13:31:28$
  $Author: Darko Kolakovic$

  Test log entries formatter
  Copyright: CommonSoft Inc.
  2006-12-06  Darko Kolakovic
*/

// Group=Examples

//-----------------------------------------------------------------------------
/*Function validates log entries formatter.

  Returns: true if test is successful, otherwise returns false.
 */
function TestLogEntry()
{
TsWriteToViewLn("TestLogEntry()");
var bRes = false;   //result of the test
//debugger;
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

  //logEntry.m_bResult = bRes;
  //LogTest(&logEntry);
  var oLogEntry = null;
  TsWriteToViewLn("Test CLogEntry");
  //TESTENTRY logEntry =
  //  {_T("CLogEntry()"), _T("KLogEntry.js"), bRes};
  oLogEntry = new CLogEntry(); //empty log record
  bRes = (oLogEntry != undefined);
  if (bRes && (oLogEntry.m_dateRecord != undefined))
    {
    TsWriteToViewLn("Test .toUTCString()");
    TsWriteToViewLn("Log entry created at " + oLogEntry.m_dateRecord.toUTCString() + " UTC");
    TsWriteToViewLn("Test .toISOString()");
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

  TsWriteToViewLn("Test CLogEntry.toString()");
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

  var arrValue = new Array();
  if (bRes)
    {
    TsWriteToViewLn("Test CLogEntry(str, int)");
    arrValue[ 0] = new CTestCase(new CLogEntry("Ursus arctos",     0));
    arrValue[ 1] = new CTestCase(new CLogEntry("Ursus thibetanus", 1));
    arrValue[ 2] = new CTestCase(new CLogEntry("Ursus maritimus",  2));
    arrValue[ 3] = new CTestCase(new CLogEntry("Ursus thibetanus", 3));
    arrValue[ 4] = new CTestCase(new CLogEntry("Ursus americanus", 4));
    arrValue[ 5] = new CTestCase(new CLogEntry("Ursus spelaeus",   5));
    arrValue[ 6] = new CTestCase(new CLogEntry("Ursus malayanus",  6));
    arrValue[ 7] = new CTestCase(new CLogEntry("Ursus arctos horribilis" /*,null*/ ));
    arrValue[ 8] = new CTestCase(new CLogEntry("",                 1));

    while(i < arrValue.length)
      {
      var bLogEntry = true; //result of the validation
      TsWriteToViewLn("" + i + ". " + arrValue[i].oValue);
      //if (bHasSpace != arrValue[i].bResult)
      //  {
      //  bRes = false;
      //  break;
      //  }
      i++;
      }

    }
  if (bRes)
    {
    TsWriteToViewLn("<h3>Test CLogEntry.toHtml()</h3>");
    TsWriteToViewLn("<ol class='logBook'>");
    i = 0;
    while(i < arrValue.length)
      {
      var bLogEntry = true; //result of the validation
      TsWriteToViewLn("<li>" + arrValue[i].oValue.toHtml() +"<\/li>\n");
      //if (bHasSpace != arrValue[i].bResult)
      //  {
      //  bRes = false;
      //  break;
      //  }
      i++;
      }
    TsWriteToViewLn("<\/ol>");
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
