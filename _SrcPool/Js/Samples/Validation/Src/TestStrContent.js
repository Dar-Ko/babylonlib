/*$Workfile: S:\_SrcPool\Js\Samples\Validation\Src\TestStrContent.js$: script file
  $Revision: 1$ $Date: 2006-11-09 16:58:32$
  $Author: Darko Kolakovic$

  Test string classifiers
  Copyright: CommonSoft Inc.
  2006-11-09  Darko Kolakovic
*/

// Group=Examples

//-----------------------------------------------------------------------------
/*Function validates a string classifiers

  Returns: true if successful, otherwise returns false.
 */
function TestStrContent()
{
TsWriteToView("TestStrContent()");
var bRes = true;
//TESTENTRY logEntry =
//  {_T("AtoI()"), _T("KStrAtoI.cpp"), bRes};

try
  {
  var strValue = new Array();
  strValue[0] = "abcdesdfsdh";
  strValue[1] = "abcd esdfsdh";
  strValue[2] = "abcde\tsdfsdh";
  strValue[3] = "abcd\t.esdf sdh";
  strValue[4] = "   abcdesdfsdh";
  strValue[5] = "abcdesdfsdh\t";
  strValue[6] = "abcde\asdfsdh";
  var cachedFilespecs;
  var i = 0;
  while (i < strValue.length)
    {
//    var bRes = hasHSpace(strValue[i++]);
i++;
    WScript.echo((i-1) + ". " +strValue[i-1] + " match " + bRes);
    }
  }
catch(error)
  {
  WScript.echo(error.name + ": " + error.message +
               "; text " + i +  ". " + strValue[i]);
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
