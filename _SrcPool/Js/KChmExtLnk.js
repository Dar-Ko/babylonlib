//$Workfile: KChmExtLnk.js$: script file
//$Revision: 5$ $Date: 2006-12-13 13:51:23$
//$Author: Darko Kolakovic$
//
//Resolve extern links in .chm
//Copyright: CommonSoft Inc
//2003-02 Darko Kolakovic

//-------------- --------------------------------------------------------------
/* This functions resolves absolute path in order to make a link to a file
  located outside of a Microsoft Compressed HTML Help (.chm) file.
  Function replaces a protocol name used in hypertext reference.(href) with
  'file:///'.
  Following Info-Tech Storage (its) protocols are used by Microsoft
  Help Hotkey file browser: 'ms-its:' or 'mk:@MSITStore:' for older version of
  the help viewer. The browser is using next URI format:
     ms-its:C:\dir\file.chm::/topic.htm

  Returns: URI of the external file or strFilename if protocol is not an ITS
  protocol.

  Note: Microsoft Windows specific (Win32)
  Requires Microsoft Help Hotkey (hh.exe) or any other viewer of
  Microsoft Compressed HTML Help files.

  Example:
   <head>
   <script language="JavaScript" src="Dir/KChmExtLnk.js" type="text/javascript">
   </script>
   </head>
   <script language="JavaScript">
     document.writeln('<applet codebase="' + ChmFilePath('AppletDir') +
         '" archive="Applet.jar" code="Applet.class" width="200" height="50">')
     document.writeln('<param name="input1" value="Some Text">')
     document.writeln('</applet>')
   </script>
 */
function ChmFilePath(strFilename, //[in] file path
                    strHref      //optional [in] URL with ITS protocol of the document to display.
                  //If no URL is specified, current document path will be used.
                  //If protocol is not an ITS protocol, strFilename is returned.
                    )
{
if (strFilename == undefined)
  return ""; //Nothing to do
if (strHref == undefined)
  strHref = location.href; //current URI
var strIts = "ms-its:"; //ITS protocol name
if (strHref.substr(0, strIts.length) != strIts)
  {
  strIts = "mk:@MSITStore:";
  if (strHref.substr(0, strIts.length) != strIts)
    return strFilename; //Return filename if other protocol is used
  }
strHref = strHref.replace(/\\/g, '/'); //Replace Windows path delimiters
strHref = strHref.replace(/[^:\\\/]+\.chm::\//i, ""); //Drop out 'file.chm::/'
//Replace protocol file name and get file path
var iPos = strHref.lastIndexOf('/') + 1;

strHref = "file:///" + strHref.substring(strIts.length, iPos) + strFilename;
return strHref;
}

//-----------------------------------------------------------------------------
/*This functions resolves absolute path in order to make a link to a file
  located outside of a Microsoft Compressed HTML Help (.chm) file.
  The link will be redirected to new location.

  Example:
  location.href = ms-its:C:\dir\file.chm::/topic.htm
   ...
   <head>
   <script language="JavaScript" src="Dir/KChmExtLnk.js" type="text/javascript">
   </script>
   </head>
   <!-- External link -->
   <a onclick="ChmExtLnk('Path/strFilename.ext')"
      style="text-decoration: underline;
      color: red;
      cursor: pointer"> Some text</a>
 */
function ChmExtLnk(strFilename //[in] external file path
                  )
  {
  location.href = ChmFilePath(strFilename);
  }

///////////////////////////////////////////////////////////////////////////////
