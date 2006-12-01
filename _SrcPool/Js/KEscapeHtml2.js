//$Workfile: S:\_SrcPool\Js\KEscapeHtml2.js$: script file
//$Revision: 1$ $Date: 2006-12-01 13:54:36$
//$Author: Darko Kolakovic$
//
//Escape special HTML2.0 characters
//Copyright: CommonSoft Inc
//2006-10 Darko Kolakovic

//-----------------------------------------------------------------------------
/*Replaces HTML 2.0 special characters with HTML entities. Function also
  converts single quote (') to escaped sequence (\').

     Character          Entity
     Less than sign        &lt;
     Greater than sign     &gt;
     Ampersand            &amp;
     Double quote sign    &quot;

  Returns: string converted to HTML2.0 text.

  See also: RFC1866: Hypertext Markup Language 2.0 - 9.7.1 Numeric and Special
  Graphic Entity Set, ISO 8879:1986.
 */
function escapeHtml2(strText //[in] plain text
                    )
{
if (!strText)
  return "";

return strText.replace(
    /([<>&\"'])/g,
    function ($1)
      {
      switch ($1)
        {
        case "<":   return "&lt;";
        case ">":   return "&gt;";
        case "&":   return "&amp;";
        case "\"":  return "&quot;";
        case "'":   return "\\'";
        }
      }
    );
}
///////////////////////////////////////////////////////////////////////////////
/*9.7.1 Numeric and Special Graphic Entity Set

   The following table lists each of the supported characters specified
   in the Numeric and Special Graphic entity set, along with its name,
   syntax for use, and description.

   This list is derived from "ISO 8879:1986Numeric and Special Graphic", however
   HTML does not provide support for the entire entity set.
   Only the entities listed below are supported.

   Name      Syntax     Description
   lt       &lt;      Less than sign
   gt       &gt;      Greater than sign
   amp      &amp;     Ampersand
   quot     &quot;    Double quote sign
 */
