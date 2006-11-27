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
  WScript.Echo(szMessage);
}

    function TRACE(strMessage)
      {
      document.write(strMessage + "<br />\n");
      }
