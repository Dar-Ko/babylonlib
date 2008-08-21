//$Workfile: KIsEmail.js$: script file
//$Revision: 1.4 $ $Date: 2008/08/21 15:01:04 $
//$Author: ddarko $
//
//Validate eMail address
//Copyright: CommonSoft Inc
//2006-10 Darko Kolakovic

_DEBUG = true;
//-----------------------------------------------------------------------------
/*Verifies if an eMail address is in proper form.
  Returns: true if address is in the following format:
    word(.word)@subdomain(.subdomain)

  Note: quoted strings are not validated. A quoted string could have almost any
  character, including space character.

  Returns false if strAddress is an empty string or not in a valid format.

  See also: RFC 2822 - Internet Message Format: 3.4. Address Specification
 */
function isEmail(strAddress //[in] eMail address
                )
{
if(!strAddress || !strAddress.length || (strAddress.length == 0))
  {
  return false;
  }

//Validate unacceptable characters
var regexFilter =  /(@.*@)|(\.\.)|(@\.)|(\.@)|(^\.)/;
//Validate format
var regexFormOk = /^.+\@(\[?)[a-zA-Z0-9\-\.]+\.([a-zA-Z]{2,3}|[0-9]{1,3})(\]?)$/;

if(_DEBUG)
	{
	var bHasNotSpace    = (strAddress.indexOf(' ') == -1); //Exclude space
	var bHasNotExcluded = !regexFilter.test(strAddress); //Exclude some characters
	var bIsValid        =  regexFormOk.test(strAddress);

	document.writeln("<i>(Regex: (hasNotSpace=" + bHasNotSpace +
	                 ") && (hasNotExcluded=" + bHasNotExcluded +
	                 ") && (validForm=" + bIsValid + ")</i>");

	return (bHasNotSpace && bHasNotExcluded && bIsValid);
	}
else

	return((strAddress.indexOf(' ') == -1) && //Exclude space
	       (!regexFilter.test(strAddress)) && //Exclude some characters
	       regexFormOk.test(strAddress));
}

//Exception test
//var regexFilter = new RegExp(
//                  "(@.*@)|(\.\.)|(@\.)|(\.@)|(^\.)","gi");
//var regexFilter = /(@.*@)|(\.\.)|(@\.)|(\.@)|(^\.)/; + exclude Space  OK

//Format test
//var regexOk = new RegExp(
//              "^[\\w-_\.]*[\\w-_\.]\@[\\w]\.+[\\w]+[\\w]$","");
//var regexOk = /^.+\@(\[?)[a-zA-Z0-9\-\.]+\.([a-zA-Z]{2,3}|[0-9]{1,3})(\]?)$/;  OK
//var regexOk = /^.+\@[a-zA-Z0-9\-\.]+\.([a-zA-Z]{2,4}|[0-9]{1,3})$/;
//var regexOk = /^([\w-\.]+)@((\[([0-9]{1,3}\.){3}[0-9]{1,3}\])$|(([\w-]+\.)+)([a-zA-Z]{2,4}))$/;
