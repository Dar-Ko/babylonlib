//$Workfile: KHasHSpace.js$: script file
//$Revision: 3$ $Date: 2006-11-07 18:04:13$
//$Author: Darko Kolakovic$
//
//Verfy a string for white spaces
//Copyright: CommonSoft Inc
//2006-10 Darko Kolakovic

//eval(Include("E:\\MyDocuments\\BabelLib\\_SrcPool\\Js\\KValidate.js"));

test();
function test()
{
try
  {
  var strValue = new Array();
  strValue[0] = "abcdesdfsdh";
  strValue[1] = "abcd esdfsdh";
  strValue[2] = "abcde\tsdfsdh";
  strValue[3] = "abcd\t.esdf sdh";
  strValue[4] = "   abcdesdfsdh";
  strValue[5] = "abcdesdfsdh\t";
  strValue[6] = "abcde\asdfsdh";
  var cachedFilespecs;
  var i = 0;
  while (i < strValue.length)
    {
    var bRes = hasHSpace(strValue[i++]);
    WScript.echo((i-1) + ". " +strValue[i-1] + " match " + bRes);
    }
  }
catch(error)
  {
  WScript.echo(error.name + ": " + error.message +
               "; text " + i +  ". " + strValue[i]);
  }
}

//------------------------------------------------------------------------------
/*Verifies object existence.

  Returns: true if object not exist or if object has no value.
  Otherwise returns false.
 */
function isBlank(oValue //[in] object to validate
                )
{
return ((oValue == null) || (oValue.length == 0));
}

//-----------------------------------------------------------------------------
/*Note: Microsoft Windows specific (Win32)
 */
function Include(szFileName //[in] name of the file to import
                )
{
if( szFileName == undefined || szFileName == "")
  return;
try
  {
  fso = new ActiveXObject("Scripting.FileSystemObject");
  fileImport = fso.OpenTextFile(szFileName);
  strImport = fileImport.ReadAll();
  fileImport.Close();
  return strImport;
  }
catch(error)
  {
  WScript.echo(error.name + ": " + error.message +
               "; file '" + szFileName +  "'.");
  }
}

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
