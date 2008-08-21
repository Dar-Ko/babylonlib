//$Workfile: KIsEmail.js$: script file
//$Revision: 1.5 $ $Date: 2008/08/21 20:16:06 $
//$Author: ddarko $
//
//Validate eMail address
//Copyright: CommonSoft Inc
//2006-10 Darko Kolakovic

//_DEBUG = true;
//-----------------------------------------------------------------------------
/*Verifies if an eMail address is in proper form.
  Returns: true if address is in the following format:
    word(.word)@subdomain(.subdomain).tld
  where
    word(.word) = local address
    @ = delimiter
    subdomain(.subdomain).tld = global address
    tld = top level domain (2-5 ASCII letters)

  Note: quoted strings are not validated. A quoted string could have almost any
  character, including space character.
  Note: top level domain (tld) is not standardized by RFC2822, but with other
  standards.

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

//Validate unacceptable characters or character combination ('..', '.@', '@.'...)
var regexFilter = /(@.*@)|(\.\.)|(@\.)|(\.@)|(^\.)|([\(\)<>,;:\\"\[\] ])/;

//Validate format
/*At least one word "^\w+" have to present at the begining of address;
  more words could follow if prefixed with characters from the set acceptable
  characters or '.';
  only one '\@' address part delimiter could exist;
  at least one subdomain with characters from the set acceptable
  characters or '.' (note that pair '@.' is excluded);
  global address have to be ended with top level domain '\.[A-Za-z]{2,5}$' long up to 5 letters;
  a 32-bit IP address is also accepted.
 */
var regexFormOk = /^\w+([\.!\-#\$%&'\*\+\-=\?\^`{\|}~]|\w+)*\@((([\.!\-#\$%&'\*\+\-=\?\^`{\|}~]|\w+)*\.[A-Za-z]{2,5})|(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}))$/;
/*
if(_DEBUG)
  {
  var bHasNotExcluded = !regexFilter.test(strAddress); //Exclude some characters
  var bIsValid        =  regexFormOk.test(strAddress);

  document.writeln("<i>(Regex: (hasNotExcluded=" + bHasNotExcluded +
                   ") && (validForm=" + bIsValid + ")</i>");

  return (bHasNotExcluded && bIsValid);
  }
else
*/
  return((!regexFilter.test(strAddress)) && //Exclude some characters
         regexFormOk.test(strAddress));
}

//Exception test
//var regexFilter = new RegExp(
//                  "(@.*@)|(\.\.)|(@\.)|(\.@)|(^\.)","gi");
//var regexFilter = /(@.*@)|(\.\.)|(@\.)|(\.@)|(^\.)/; + exclude Space
//var regexFilter = /(@.*@)|(\.\.)|(@\.)|(\.@)|(^\.)|([\(\)<>,;:\\"\[\] ])/; OK

//Format test
//var regexOk = new RegExp(
//              "^[\\w-_\.]*[\\w-_\.]\@[\\w]\.+[\\w]+[\\w]$","");
//var regexOk = /^.+\@(\[?)[a-zA-Z0-9\-\.]+\.([a-zA-Z]{2,3}|[0-9]{1,3})(\]?)$/; OK
//var regexOk = /^.+\@[a-zA-Z0-9\-\.]+\.([a-zA-Z]{2,4}|[0-9]{1,3})$/;
//var regexOk = /^\w+((\.\w+)|(-\w+)|(\_\w+))*\@[A-Za-z0-9]+((\.|-)[A-Za-z0-9]+)*\.[A-Za-z]{2,5}/;
//var regexOk = /^([\w-\.]+)@((\[([0-9]{1,3}\.){3}[0-9]{1,3}\])$|(([\w-]+\.)+)([a-zA-Z]{2,4}))$/;


