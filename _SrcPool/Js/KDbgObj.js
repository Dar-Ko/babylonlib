//$Workfile: KDbgObj.js$: script file
//$Revision: 6$ $Date: 2006-11-23 18:20:21$
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
function dbgObj(anyValue //[in] variable of any kind
               )
{
var strResult;
if((anyValue == null))
  strResult = "undefined: null";
else if((anyValue == undefined))
  strResult = "undefined: null";
else
  {
  var strType = typeof(anyValue);
  if(strType != "object")
    {
    strResult = strType + ": ";
    //The callee property is a member of the arguments object that becomes
    //available only when the associated function is executing.
    if( ((anyValue.arguments != undefined) && (anyValue.arguments.callee != undefined)) ||
        ((anyValue.constructor != undefined) && (anyValue.constructor == Function)) )
      {
      //Get function's name
      var regexMatch = anyValue.toString().match(/function(\s*)(\w*)/);
      if (regexMatch && regexMatch.length >= 2 && regexMatch[2])
        strResult += regexMatch[2] + "(";
      else
        strResult += 'anonymous(';

      //Dump function arguments
      if(anyValue.arguments != undefined)
        {
        var i = 0; //Argument 0 is caller function
        while(i < anyValue.arguments.length) //Get arguments passed to function.
          {
          if(typeof(anyValue.arguments[i]) == "string") //Quote a string argument
            strResult += "'" + anyValue.arguments[i];
          else if ((typeof(anyValue.arguments[i]) == "function") ||
                   (typeof(anyValue.arguments[i]) == "object"))
            strResult += typeof(anyValue.arguments[i]);
          else
            strResult += anyValue.arguments[i];
          strResult += ",";
          i++;
          }
        if(strResult.charAt(strResult.length-1) == ',')
          strResult = strResult.substr(0, strResult.length-1);
        }
      else
        {
        strResult += anyValue.length + " param"; //Number of expected arguments
        }
      strResult += ")";
      }
    else
      {
      strResult += (anyValue == "") ? "{empty}" : anyValue;
      }
    }
  else
    {
    var strElements = "";
    //Validate object for two common Array methods
    if((anyValue.concat != undefined) && (anyValue.sort != undefined))
      {
      strType = "Array: ";    //The object appears to be an array
      for (var j in anyValue) //Dump array items
        {
        //The undefined elements would be skiped over
        strElements += "[" + j + "] " + anyValue[j] + "\n";
        if (strElements.length > 256) //Limit the size of the output
          {
          strElements += "...";
          break;
          }
        }
      if(strElements == "")
        strElements =  "{empty}";
      }
    else //Other objects
      {
      strType += ": ";
      for (var j in anyValue) //Dump enumerable object properties
        {
        //The undefined elements would be skiped over
        strElements += "[" + j + "]\n"; //Limit the size of the output
        if (strElements.length > 256)
          {
          strElements += "...";
          break;
          }
        }
      if(strElements == "")
        strElements = "(...)";
      }
    strResult = strType + strElements;
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
