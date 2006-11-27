/*$Workfile: S:\_SrcPool\Js\Samples\String\Src\TestFnMatch.js$: script file
  $Revision: 1$ $Date: 2006-11-27 14:23:03$
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
TsWriteToView("TestFnMatch()");
var bRes = true;
//TESTENTRY logEntry =
//  {_T("AtoI()"), _T("KStrAtoI.cpp"), bRes};

try
  {
  var szFilename = "Darko [Kolakovic].ma"
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
  //var cachedFilespecs;
  var i = 0;
  while (i < szPattern.length)
    {
    var bRes = FnMatch(szFilename, szPattern[i++], true);
    WScript.echo(szPattern[i-1] + " match " + bRes);
    }
  }
catch(error)
  {
  WScript.echo(error.name + ": " + error.message +
               "; pattern " + i +  ". " + szPattern[i]);
  bRes = false
  }

//logEntry.m_bResult = bRes;
//LogTest(&logEntry);

TsWriteToView("LOG_EOT");
return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2006-11-09 16:58:32  Darko Kolakovic
 * $
 *****************************************************************************/
