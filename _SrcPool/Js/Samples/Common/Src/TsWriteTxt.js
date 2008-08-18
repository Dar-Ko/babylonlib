/*$Workfile: TsWriteTxt.js$: script file
  $Revision: 3$ $Date: 2006-12-13 13:52:07$
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
  g_defOut.Write = //TODO; Replace HTML escapes <>"
    function (szText //[in] text to output
             )
    {
    //Note: Firefox 1.5 throws NS_ERROR_XPC_BAD_OP_ON_WN_PROTO:
    //Illegal operation on WrappedNative prototype object; value 0.
    //prototype is assigned directly: g_defOut.Write = document.write;
    //Opera 8.0 skips over function call.
    document.write(szText);
    };
  g_defOut.WriteLn =
    function (szText //[in] line of text to output
             )
      {
      if (szText != 'undefined')
        //TODO: document.writeln(EscapeHTml());
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
if (szMessage != 'undefined')
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
if (szText != 'undefined')
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
