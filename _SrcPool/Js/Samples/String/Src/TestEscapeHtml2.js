/*$Workfile: S:\_SrcPool\Js\Samples\String\Src\TestEscapeHtml2.js$: script file
  $Revision: 1$ $Date: 2006-12-01 13:54:45$
  $Author: Darko Kolakovic$

  Test string conversion to HTML2.0
  Copyright: CommonSoft Inc.
  2006-11-27  Darko Kolakovic
*/

// Group=Examples

//-----------------------------------------------------------------------------
/*Function validates conversion of a string to HTML2.0 text.

  Returns: true if test is successful, otherwise returns false.
 */
function TestEscapeHtml2()
{
TsWriteToViewLn("TestEscapeHtml2()");
var bRes = true;   //result of the test
//TESTENTRY logEntry =
//  {_T("escapeHtml2()"), _T("KEscapeHtml2.js"), bRes};
//debugger;
var i = 0;
try
  {
  /*Container class for testing string inquisition.
   */
  function CTestCase (strValue, //="" [in] string to be evaluated
                     strTestResult //="" [in] expected result of the test
                     )
    {
    this.strValue = "";
    this.strResult = "";
    if (strValue != undefined)
      this.strValue += strValue;       //string by contract
    if (strTestResult != undefined)
      this.strResult = strTestResult;  //string by contract
    };

  var arrValue = new Array();
  arrValue[ 0] = new CTestCase("abcdesdfsdh",      "abcdesdfsdh"               );
  arrValue[ 1] = new CTestCase("abcd<es>dfsdh",    "abcd&lt;es&gt;dfsdh"       );
  arrValue[ 2] = new CTestCase("abcde\"sdfsdh\"",  "abcde&quot;sdfsdh&quot;"   );
  arrValue[ 3] = new CTestCase("abcd' & esdf sdh", "abcd\\\' &amp; esdf sdh"   );
  arrValue[ 4] = new CTestCase("\&abcdesdfsdh",    "&amp;abcdesdfsdh"          );
  arrValue[ 5] = new CTestCase("<<=>>desdfsdh",    "&lt;&lt;=&gt;&gt;desdfsdh" );
  arrValue[ 6] = new CTestCase(" <&amp;>",         " &lt;&amp;amp;&gt;"        );
  arrValue[ 7] = new CTestCase("",                 ""); //empty string
  arrValue[ 8] = new CTestCase(undefined,          ""); //undefined

  while(i < arrValue.length)
    {
    var strEscaped = escapeHtml2(arrValue[i].strValue);
    TsWriteToViewLn("" + i + ". " + arrValue[i].strValue + " = <code>" +
                     escapeHtml2(strEscaped) + "</code>");
    if (strEscaped != arrValue[i].strResult)
      {
      bRes = false;
      break;
      }
    i++;
    }
  }
catch(error)
  {
  TsWriteToViewLn(error.name + ": " + error.message +
               "; value " + i +  ". " + arrValue[i].strValue);
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
