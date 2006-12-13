/*$Workfile: TestChmExtLnk.js$: script file
  $Revision: 2$ $Date: 2006-12-13 13:54:34$
  $Author: Darko Kolakovic$

  Test .chm External Link redirection
  Copyright: CommonSoft Inc.
  2006-12-06  Darko Kolakovic
*/

// Group=Examples

//-----------------------------------------------------------------------------
/*Function validates redirection of links used in Microsoft Compressed HTML
  Help (.chm) file.

  Returns: true if test is successful, otherwise returns false.
 */
function TestChmExtLnk()
{
TsWriteToViewLn("TestChmExtLnk()");
var bRes = true;   //result of the test
//debugger;
var i = 0;
try
  {
  /*Container class for testing string inquisition.
   */
  function CTestCase (strValue, //="" [in] reference to a file
                      strUri,   //="" [in] URL to be evaluated
                      bTestResult //=false [in] expected result of the test
                     )
    {
    this.strUri = "";
    this.strValue = "";
    this.bResult = false;
    if (strUri != undefined)
      this.strUri += strUri; //string by contract
    if (strValue != undefined)
      this.strValue += strValue; //string by contract
    if (bTestResult != undefined)
      this.bResult = (bTestResult == true); //boolean by contract
    };


  var arrValue = new Array();
  if (bRes)
    {
    //logEntry.m_bResult = bRes;
    //LogTest(&logEntry);
    TsWriteToViewLn("Test ChmFilePath()");
    //TESTENTRY logEntry =
    //  {_T("ChmFilePath()"), _T("KChmExtLnk.js"), bRes};

    arrValue[ 0] = new CTestCase("", "",    true);  //Empty URI
    arrValue[ 1] = new CTestCase("ftp://some.ftp.site:5600", "", true);
    arrValue[ 2] = new CTestCase("file://dir/some.file", "", true);
    arrValue[ 3] = new CTestCase("file:///C:\\dir\\another.file", "", true);
    arrValue[ 4] = new CTestCase("topic1.htm", "ms-its:C:\\dir\\file.chm::/topic1.htm", true);
    arrValue[ 5] = new CTestCase("topic2.htm", "mk:@MSITStore:d:\\dir\\file.chm::/topic2.htm", true);

    while(i < arrValue.length)
      {
      var bOk = true; //result of the validation
      TsWriteToView("" + i + ". " + arrValue[i].strUri + " = ");
      var strLink = ChmFilePath(arrValue[i].strValue, arrValue[i].strUri);
      TsWriteToViewLn(strLink);
      bOk = (strLink == arrValue[i].strValue);
      if (bOk != arrValue[i].bResult)
        {
      //  bRes = false; TODO
      //  break;
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
                  "; value " + i +  ". " + arrValue[i].strUri));
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
