//$Workfile: KFnMatch.js$: script file
//$Revision: 3$ $Date: 2006-12-01 13:55:19$
//$Author: Darko Kolakovic$
//
//Filename pattern matching.
//Copyright: CommonSoft Inc
//2006-11 Darko Kolakovic

//-----------------------------------------------------------------------------
/*Filename pattern matching. Matches a filename with a pattern consisting of
  characters and wildcards. The special characters used as wildcards are:

     Wildcard    Description
       *        matches everything
       ?        matches any single character
     [list]     matches any character in list
     [!list]    matches any character not in list

  Returns: true or false as result of the pattern match.

  Example:
 */
function FnMatch(szFilename, //[in] filename to match
                 szPattern , //[in] pattern to match
                 bCaseInsensitive, //= false [in] true or false for case-insensitive
                                   //comparison
                 arrPatternCache   //= null [in] list of patterns and their regular
                      //expression equivalents, used to speed up the conversion
                 )
{
if ((szFilename == undefined) || (szPattern == undefined))
  return false; //Nothing to do
if (bCaseInsensitive == undefined)
  bCaseInsensitive = false;

var rePattern; //file name RegExp pattern
if (arrPatternCache != undefined)
  rePattern = arrPatternCache[szPattern]; //Get the pattern from the cache

//if ((arrPatternCache==undefined) || (arrPatternCache[szPattern] == undefined))
if(rePattern == undefined)
  {
   //Convert filename pattern to regular expression pattern
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

        //Replace regex special characters '\','^','[' and ']'
        szList = szList.replace(/\\/g, "\\\\");
        szList = szList.replace(/\^/g, "\\^");
        szList = szList.replace(/\]/g, "\\]");
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
  rePattern = new RegExp(szRegex + '$', bCaseInsensitive ? "i" : "");
  if (arrPatternCache != undefined)
    arrPatternCache[szPattern] = rePattern; //Store the pattern to the cache
  }
//Note: the match method returns null or an array with found patterns
return (szFilename.match(rePattern) != null);
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 *See also: fnmatch - Unix filename pattern matching
 *           http://docs.python.org/lib/module-fnmatch.html
 * $Log:
 *  1    Biblioteka1.0         2006-11-09 16:58:32  Darko Kolakovic
 * $
 *****************************************************************************/
