/*$Workfile: TsWriteTxt.js$: script file
  $Revision: 2$ $Date: 2006-11-27 16:09:01$
  $Author: Darko Kolakovic$

  Outputs text to the default output device
  Copyright: CommonSoft Inc.
  2006-11 Darko Kolakovic
*/

// Group=Examples

//KTestLog.h TODO: move constants to separate Log.js file
  /*Test succeeded log entry       */
var LOG_SUCCESS = "OK.";
  /*Test failed log entry          */
var LOG_FAILURE = "NOK!";
  /*End-of-Test tag                */
var LOG_EOT     = "======================";


var g_defOut = new Object(); //default output device

if(this.WScript != null) //Windows Script Host shell
  {
  g_defOut.Write = WScript.Echo;
  g_defOut.WriteLn = WScript.Echo;
  }
else if (document != null) //HTML Browser shell
  {
  g_defOut.Write = document.write; //TODO; Replace HTML escapes <>"
  g_defOut.WriteLn = //document.writeln(EscapeHTml());
    function (szText //[in] line of text to output
             )
      {
      if (szText != undefined)
        //Outputs text to either a message box or the command console window.
        document.writeln(szText + "<br />");
      else
        document.writeln("&lt;null&gt;<br />");
      };
  }

//------------------------------------------------------------------------------
/*Display a line of the text.
  Note: Microsoft Windows specific (Win32)
 Requires Microsoft Windows Script Host (WSH) engine.
 */
function TsWriteToView(szMessage //[in] text do be displayed
                      )
{
if (szMessage != undefined)
  //Outputs text to either a message box or the command console window.
  g_defOut.Write(szMessage);
else
  g_defOut.Write("<null>");
}

//------------------------------------------------------------------------------
/*Writes a line of the text at the console standard output stream. New line
  delimiter (EOL) is appended to the end of the text.

  Returns: true always.

  Note: uses Standard Template Library (STL).
 */
function TsWriteToViewLn(szText //[in] line of text to output
                     )
{
if (szText != undefined)
  //Outputs text to either a message box or the command console window.
  g_defOut.WriteLn(szText);
else
  g_defOut.WriteLn("<null>");
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2006-11-27 16:09:01  Darko Kolakovic
 *       TsWriteToViewLn()
 *  1    Biblioteka1.0         2006-11-27 14:26:14  Darko Kolakovic 
 * $
 *****************************************************************************/
