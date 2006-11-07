//$Workfile: S:\_SrcPool\Js\KFnMatch.js$: script file
//$Revision: 1$ $Date: 2006-11-07 18:00:41$
//$Author: Darko Kolakovic$
//
//Filename pattern matching.
//Copyright: CommonSoft Inc
//2006-11 Darko Kolakovic
var cachedFilespecs;
test();
function test()
{
try
  {
  var szFilename = "Darko [Kolakovic].ma"
  var szPattern = new Array();
  szPattern[ 0] = "D* ].?a";
  szPattern[ 1] = "[xyz]";
  szPattern[ 2] = "[\\x\\y^z]";
  szPattern[ 3] = "[!xyz]";
  szPattern[ 4] = "[x^^yz]";
  szPattern[ 5] = "[xyz"; //not terminated set
  szPattern[ 6] = "[!!xyz]";
  szPattern[ 7] = "[\\x\\y^z]";
  szPattern[ 8] = "[ x\tyz]";
  szPattern[ 9] = "![xyz]";
  szPattern[10] = "[]"; //empty set
  szPattern[11] = "[]]";
  szPattern[12] = "[[]";
  szPattern[13] = "[\\]]";
  szPattern[14] = "D[!xyz]*.ma";
  //var cachedFilespecs;
  var i = 0;
  while (i < szPattern.length)
    {
    var bRes = FnMatch(szFilename, szPattern[i++], true);
    WScript.echo(szPattern[i-1] + " match " + bRes);
    }
  }
catch(error)
  {
  WScript.echo(error.name + ": " + error.message +
               "; pattern " + i +  ". " + szPattern[i]);
  }
}

//-----------------------------------------------------------------------------
/*Filename pattern matching. Matches a filename with a pattern consisting of
  charaters and wildcards. The special characters used as wildcards are:

     Wildcard    Description
       *        matches everything
       ?        matches any single character
     [list]     matches any character in list
     [!list]    matches any character not in list

  Returns: true or false as result of the pattern match.
 */
function FnMatch(szFilename, //[in] filename to match
                 szPattern , //[in] pattern to match
                 bCaseInsensitive //[in] true or false for case-insensitive
                                  //comparison
                 )
{
if (cachedFilespecs == undefined)
  cachedFilespecs = new Object();

 //Convert filename pattern to regular expression pattern
if (cachedFilespecs[szPattern])
  return szFilename.match( cachedFilespecs[szPattern] );

var szRegex = ""; //regular expression pattern to match
var i = 0;
while (i < szPattern.length)
  {
  var ch = szPattern.charAt(i++);
  if (ch == '*')      //Matches any number of characters
    szRegex += ".*";
  else if (ch == '?') //Matches any character
    szRegex += '.';
  else if (ch == '[') //Matches any single character from the specified set.
    {
    var j = i;
    if (j < szPattern.length && szPattern.charAt(j) == '!')
      j++;
    if (j < szPattern.length && szPattern.charAt(j) == ']')
      j++;
    //Get the size of the character set
    while (j < szPattern.length && szPattern.charAt(j) != ']')
      j++;

    if (j >= szPattern.length)
      {
      //Escape regex special character '[' if no closing ']' is found
      szRegex += "\\[";
      }
    else
      {
      var szList = szPattern.slice(i, j);
      i = j + 1; //Move index to the and of the set

      //Escape every regex special character '\'
      szList = szList.replace(/\\/g, "\\\\");
      //Escape every regex special character '^'
      szList = szList.replace(/\^/g, "\\^");
      //Escape every regex special character ']'
      szList = szList.replace(/\]/g, "\\]");
      //Escape every regex special character '['
      szList = szList.replace(/\[/g, "\\[");

      //To matches any single character not in the specified set of characters,
      //repace first '!' with regex special character '^'
      szList = szList.replace("!", "^");
      szRegex += '[' + szList + ']';
      }
    }
  else if (ch.match(/\W/))
    szRegex += "\\" + ch;
  else
    szRegex += ch;
  }

//Specifies case-insensitive matching.
cachedFilespecs[szPattern] = new RegExp(szRegex + '$', bCaseInsensitive ? "" : "i");
return szFilename.match(cachedFilespecs[szPattern]);
}