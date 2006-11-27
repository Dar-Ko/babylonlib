/*$Workfile: TestFnMatch.js$: script file
  $Revision: 2$ $Date: 2006-11-27 17:43:48$
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
var bRes = true;
//TESTENTRY logEntry =
//  {_T("FnMatch()"), _T("KFnMatch.js"), bRes};
debugger;//
try
  {
  var szFilename = "Dario [Augustus].ma"
  var szPattern = new Array();
  szPattern[ 0] = "D* ].?a";
  szPattern[ 1] = "[xyz]";
  szPattern[ 2] = "[\\x\\y^z]";
  szPattern[ 3] = "[!xyz]";
  szPattern[ 4] = "[x^^yz]";
  szPattern[ 5] = "[xyz"; //not terminated set
  szPattern[ 6] = "[!!xyz]";
  szPattern[ 7] = "[\\x\\y^z]";
  szPattern[ 8] = "[ x\tyz]";
  szPattern[ 9] = "![xyz]";
  szPattern[10] = "[]"; //empty set
  szPattern[11] = "[]]";
  szPattern[12] = "[[]";
  szPattern[13] = "[\\]]";
  szPattern[14] = "D[!xyz]*.ma";

  for (var i in szPattern)
    {
    var bRes = FnMatch(szFilename, szPattern[i], true);
    TsWriteToViewLn("  " + szPattern[i] + " match " + bRes);
    }
  }
catch(error)
  {
  TsWriteToViewLn(error.name + ": " + error.message +
               "; pattern " + i +  ". " + szPattern[i]);
  bRes = false
  }

//logEntry.m_bResult = bRes;
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
