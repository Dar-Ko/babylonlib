//$Workfile: KIsEmail.js$: script file
//$Revision: 1.1 $ $Date: 2008/08/19 18:51:54 $
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
var regexNok = /(@.*@)|(\.\.)|(@\.)|(\.@)|(^\.)/; ..//first validation pass
//Valid format "^[\\w-_\.]*[\\w-_\.]\@[\\w]\.+[\\w]+[\\w]$" second pass
var regexOk = /^([\w-\.]+)@((\[([0-9]{1,3}\.){3}[0-9]{1,3}\])$|(([\w-]+\.)+)([a-zA-Z]{2,4}))$/;

return(!regexNok.test(strAddress) && regexOk.test(strAddress));
}
