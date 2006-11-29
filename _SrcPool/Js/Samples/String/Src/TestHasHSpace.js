/*$Workfile: S:\_SrcPool\Js\Samples\String\Src\TestHasHSpace.js$: script file
  $Revision: 1$ $Date: 2006-11-29 13:10:36$
  $Author: Darko Kolakovic$

  Test string validation
  Copyright: CommonSoft Inc.
  2006-11-27  Darko Kolakovic
*/

// Group=Examples

//-----------------------------------------------------------------------------
/*Function validates if a string has horizontal space characters.

  Returns: true if test is successful, otherwise returns false.
 */
function TestHasHSpace()
{
TsWriteToViewLn("TestHasHSpace()");
var bRes = true;   //result of the test
//TESTENTRY logEntry =
//  {_T("hasHSpace()"), _T("KHasHSpace.js"), bRes};
debugger;
var i = 0;
try
  {
  /*Container class for testing string inquisition.
   */
  function CTestCase (strValue, //="" [in] string to be evaluated
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

  var arrValue = new Array();
  arrValue[ 0] = new CTestCase("abcdesdfsdh",       false);
  arrValue[ 1] = new CTestCase("abcd esdfsdh",      true);
  arrValue[ 2] = new CTestCase("abcde\tsdfsdh",     true);
  arrValue[ 3] = new CTestCase("abcd\t.esdf sdh",   true );
  arrValue[ 4] = new CTestCase("   abcdesdfsdh",    true );
  arrValue[ 5] = new CTestCase("abcdesdfsdh\t",     true ); //horizontal tab
  arrValue[ 6] = new CTestCase("abcde\asdfsdh",     false); //bell
  arrValue[ 7] = new CTestCase("",                  false); //empty string

  while(i < arrValue.length)
    {
    var bHasSpace = true; //result of the validation
    bHasSpace = (hasHSpace(arrValue[i].strValue) >= 0);
    TsWriteToViewLn("" + i + ". " + arrValue[i].strValue + " has " +
                     (bHasSpace ? "spaces." : " not spaces."));
    if (bHasSpace != arrValue[i].bResult)
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
