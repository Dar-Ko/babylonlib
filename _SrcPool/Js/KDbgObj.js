//$Workfile: KDbgObj.js$: script file
//$Revision: 2$ $Date: 2006-11-20 15:17:31$
//$Author: Darko Kolakovic$
//
//Dumps variable type and value
//Copyright: CommonSoft Inc
//2006-11 Darko Kolakovic

// Group=Diagnostic

//------------------------------------------------------------------------------
/*Dumps a variable of type object, function or any other kind.

  Returns: string representation of the variable.
 */
function dbgObj(anyValue //[in] varible of any kind
               )
var strResult = "";
var strType = typeof(anyValue);
if(strType != "object")
   strResult += strType + ": " + anyValue;
else
  {
  if(anyValue.callee != undefined)
    {
    //Dump function arguments
    strResult += "(";
    var i = 0;
    while(i < anyValue.length)
      {
      if ( typeof(anyValue[i]) == "string" ) //Quote a string argument
        strResult += "'" + anyValue[i] + "',";
      else
        strResult += anyValue[i] + ",";
      i++;
      }
    if(strResult.charAt(strResult.length-1) == ',')
      strResult = strResult.substr(0, strResult.length-1);
    strResult += ")";
    }
  else
    {
    for (var key in anyValue)
      {
      strResult += key + ": " + anyValue[key] + "\n";
      }
    }
  }

return strResult;

}
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2006-11-20 15:14:13  Darko Kolakovic
 * $
 *****************************************************************************/
