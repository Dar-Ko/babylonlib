//$Workfile: KHasHSpace.js$: script file
//$Revision: 5$ $Date: 2006-11-29 13:10:02$
//$Author: Darko Kolakovic$
//
//Verify if a string has white spaces
//Copyright: CommonSoft Inc
//2006-10 Darko Kolakovic

//Include(KValidate.js);

//------------------------------------------------------------------------------
/*Verifies if a string has white spaces.

  Returns: index of the first 'space' or horizontal tabulator ('\t') character
  inside the string or -1 if the string has not listed white space characters.
  
  Example:
      var bHasSpace = true; //result of the validation
      bHasSpace = (hasHSpace("Some text") >= 0);
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
      return i;
      }
    }
  }
return -1;
}
