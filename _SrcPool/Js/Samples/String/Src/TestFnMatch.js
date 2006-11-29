/*$Workfile: TestFnMatch.js$: script file
  $Revision: 4$ $Date: 2006-11-29 11:50:04$
  $Author: Darko Kolakovic$

  Test filename pattern matching
  Copyright: CommonSoft Inc.
  2006-11-27  Darko Kolakovic
*/

// Group=Examples

//-----------------------------------------------------------------------------
/*Function validates a filename pattern matching

  Returns: true if successful, otherwise returns false.
 */
function TestFnMatch()
{
TsWriteToViewLn("TestFnMatch()");
var bRes = true;   //result of the test
var bMatch = true; //result of the pattern matching
//TESTENTRY logEntry =
//  {_T("FnMatch()"), _T("KFnMatch.js"), bMatch};
//debugger;
var i = 0;
try
  {
  /*Container class for testing filename pattern matching.
    The special characters used in shell-style wildcards are:
      *       matches any number of characters
      ?       matches any single character
      [set]   matches any character in the set
      [!set]  matches any character not in set
   */
  function CTestCase (strPattern, //='*' [in] Unix filename pattern
                     bTestResult //=false [in] expected result of the test
                     )
    {
    this.strPattern = "*";
    this.bResult = false;
    if (strPattern != undefined)
      this.strPattern = "" + strPattern; //string by contract
    if (bTestResult != undefined)
      this.bResult = (bTestResult == true); //boolean by contract
    };

  var szFilename = "Dario [Augustus].ma"
  var arrPattern = new Array();
  arrPattern[ 0] = new CTestCase("D*].?a",      true );
  arrPattern[ 1] = new CTestCase("[xyz]",       false);
  arrPattern[ 2] = new CTestCase("[\\x\\y^z]",  false);
  arrPattern[ 3] = new CTestCase("[!xyz]",      true );
  arrPattern[ 4] = new CTestCase("[x^^yz]",     false);
  arrPattern[ 5] = new CTestCase("[xyz",        false); //not terminated set
  arrPattern[ 6] = new CTestCase("[!!xyz]",     true );
  arrPattern[ 7] = new CTestCase("[\\x\\y^z]",  false);
  arrPattern[ 8] = new CTestCase("[ x\tyz]",    false);
  arrPattern[ 9] = new CTestCase("![xyz]",      false);
  arrPattern[10] = new CTestCase("[]",          false); //empty set
  arrPattern[11] = new CTestCase("[]]",         false);
  arrPattern[12] = new CTestCase("[[]",         false);
  arrPattern[13] = new CTestCase("[\\]]",       false);
  arrPattern[14] = new CTestCase("D[!xyz]*.ma", true );

  TsWriteToViewLn(szFilename);
  var arrCache = new Array(); //regular expression cache
  while(i < arrPattern.length)
    {
    bMatch = FnMatch(szFilename, arrPattern[i].strPattern, true, arrCache);
    TsWriteToViewLn("" + i + ". " + arrPattern[i].strPattern + " match " + bMatch);
    if (bMatch != arrPattern[i].bResult)
      {
      bRes = false;
      break; 
      /*Bug: IE 6.0 generates error #1019 "Error: Can't have 'break' outside of loop"
        The error is caused by the character > 0x7F inside the comment line: see the word
        cache in the comment above (used to be cache')!
       */
      }
    i++;
    }
  if (bRes)
    {
    //Test a pattern from the RegExp cache
    //Note: in the case of an error, the message will show index i. See catch().
    i++;
    bMatch = FnMatch(szFilename, arrPattern[0].strPattern, true, arrCache);
    TsWriteToViewLn(i + ". " + arrPattern[0].strPattern + " match " + bMatch);
    bRes = (bMatch == arrPattern[0].bResult);
    }
  }
catch(error)
  {
  TsWriteToViewLn(error.name + ": " + error.message +
               "; pattern " + i +  ". " + arrPattern[i].strPattern);
  bRes = false;
  }

//logEntry.m_bResult = bMatch;
//LogTest(&logEntry);

TsWriteToViewLn(LOG_EOT);
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2006-11-09 16:58:32  Darko Kolakovic
 * $
 *****************************************************************************/
