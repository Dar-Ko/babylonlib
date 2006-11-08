//$Workfile: KHasHSpace.js$: script file
//$Revision: 4$ $Date: 2006-11-08 17:53:27$
//$Author: Darko Kolakovic$
//
//Verify if a string has white spaces
//Copyright: CommonSoft Inc
//2006-10 Darko Kolakovic

//------------------------------------------------------------------------------
/*Verifies if a string has white spaces.

  Returns: true if the string has a 'space' or horizontal tabulator ('\t')
  characters. If not, returns false.
 */
function hasHSpace(strValue //[in] string to be evaluated
                  )
{
if(!isBlank(strValue))
  {
  for(var i = 0; i < strValue.length; i++)
    {
    if ((strValue.charAt(i) == ' ') || (strValue.charAt(i) == '\t'))
      {
      return true;
      }
    }
  }
return false;
}
