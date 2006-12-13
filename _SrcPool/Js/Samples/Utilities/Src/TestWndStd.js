/*$Workfile: S:\_SrcPool\Js\Samples\Utilities\Src\TestWndStd.js$: script file
  $Revision: 1$ $Date: 2006-12-13 12:19:32$
  $Author: Darko Kolakovic$

  Test Window sizes
  Copyright: CommonSoft Inc.
  2006-12-13  Darko Kolakovic
*/

// Group=Examples

//-----------------------------------------------------------------------------
/*Function validates resizing the current document with new window.

  Returns: true if test is successful, otherwise returns false.
 */
function TestWndStd()
{
TsWriteToViewLn("TestWndStd()");
var bRes = true;   //result of the test
//debugger;
var i = 0;
try
  {

  //logEntry.m_bResult = bRes;
  //LogTest(&logEntry);
  TsWriteToViewLn("Test OpenWndStd()");
  //TESTENTRY logEntry =
  //  {_T("OpenWndStd()"), _T("KWndSize.js"), bRes};

  var arrValue = new Array();
  if (bRes)
    {
    while(i <= 4) //Test types [0, 4]
      {
      arrValue[i] = OpenWndStd(i,'TestWndStd.js');
      if(arrValue[i] == undefined)
        {
        bRes = false;
        break;
        }
      TsWriteToViewLn("Created Window (size type " + (i + 1) + ").");
      i++;
      }
    }
  if (false)//(bRes)
    {
    i = 0;
    while (i < arrValue.length)
      {
      if (arrValue[i].document.close != undefined) //FixMe! close fails because of permission
        arrValue[i].document.close(); //Closing new windows
      else
        TsWriteToViewLn("[" + i + "] window.close() is undefined!");
      i++;
      }
    TsWriteToViewLn("Windows are closed now.");
    }
  }
catch(error)
  {
  TsWriteToViewLn(error.name + ": " + error.message +
                  ( ((arrValue == undefined) ||
                     (arrValue[0] == undefined))  ? "" :
                  "; value " + i +  ". " + arrValue[i].name));
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
