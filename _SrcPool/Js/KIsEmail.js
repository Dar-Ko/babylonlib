//$Workfile: KIsEmail.js$: script file
//$Revision: 1.3 $ $Date: 2008/08/20 21:34:02 $
//$Author: ddarko $
//
//Validate eMail address
//Copyright: CommonSoft Inc
//2006-10 Darko Kolakovic

//-----------------------------------------------------------------------------
/*Verifies if an eMail address is in proper form.

  Returns: true if address is in the following format:
    name@domain
  Returns false if strAddress is an empty string or not in a valid format.
 */
function isEmail(strAddress //[in] eMail address
                )
{
if(!strAddress || !strAddress.length || (strAddress.length == 0))
  {
  return false;
  }




  var reg1 = /(@.*@)|(\.\.)|(@\.)|(\.@)|(^\.)/; // not valid
  var reg2 = /^.+\@(\[?)[a-zA-Z0-9\-\.]+\.([a-zA-Z]{2,3}|[0-9]{1,3})(\]?)$/; // valid
  //var reg2 = /^([\w-\.]+)@((\[([0-9]{1,3}\.){3}[0-9]{1,3}\])$|(([\w-]+\.)+)([a-zA-Z]{2,4}))$/;
  var result = true;

  var test1 = !reg1.test(strAddress);
  var test2 = reg2.test(strAddress);
  var test3 = (strAddress.indexOf(' ') == -1);

  if (!(test1 && test2 && test3)) { // if syntax is valid
     result = false;
  }

  return result;







//var regexFilter = new RegExp("(@.*@)|(\.\.)|(@\.)|(\.@)|(^\.)","gi");
var regexFilter = new RegExp("(@.*@)|(\.\.)|(@\.)|(\.@)|(^\.)","");
//first validation pass
//Valid format "^[\\w-_\.]*[\\w-_\.]\@[\\w]\.+[\\w]+[\\w]$" second pass
//var regexOk = new RegExp("^[\\w-_\.]*[\\w-_\.]\@[\\w]\.+[\\w]+[\\w]$","");
//var regexOk = /^.+\@(\[?)[a-zA-Z0-9\-\.]+\.([a-zA-Z]{2,3}|[0-9]{1,3})(\]?)$/;
//var regexOk = /^.+\@[a-zA-Z0-9\-\.]+\.([a-zA-Z]{2,4}|[0-9]{1,3})$/;
var regexOk = /^([\w-\.]+)@((\[([0-9]{1,3}\.){3}[0-9]{1,3}\])$|(([\w-]+\.)+)([a-zA-Z]{2,4}))$/;

document.writeln("<i>(Regex: " + (!regexFilter.test(strAddress)) + " && " + regexOk.test(strAddress) + ")</i>");
return(!regexFilter.test(strAddress) && regexOk.test(strAddress));
}
