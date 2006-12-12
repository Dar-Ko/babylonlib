//$Workfile: KChmExtLnk.js$: script file
//$Revision: 3$ $Date: 2004-10-01 22:07:31$
//$Author: Darko$
//
//Resolve extern links in .chm
//Copyright: CommonSoft Inc
//2003-02 Darko Kolakovic

// ChmFilePath() --------------------------------------------------------------
// This functions resolves absolute path in order to make a link to a file
// located outside of a compiled help (.chm) file.
// Function replaces current moniker protocol name in location.href with
// 'file:///' if it is invoked within HTML browser
// or with 'ms-its:' if the Microsoft help viewer is used (older version of the
// help viewer used now depreciated 'mk:@MSITStore:' moniker).
//
// Returns: absolute file path of the external file
//
// Example:
//  <head>
//  <script language="JavaScript" src="Dir/KChmExtLnk.js" type="text/javascript">
//  </script>
//  </head>
//  <script language="JavaScript">
//    document.writeln('<applet codebase="' + ChmFilePath('AppletDir') +
//        '" archive="Applet.jar" code="Applet.class" width="200" height="50">')
//    document.writeln('<param name="input1" value="Some Text">')
//    document.writeln('</applet>')
//  </script>
function ChmFilePath(Filename)
  {
  var nLen, Backslash, nPos, Del, Link;
  Link = location.href;

  //Find index of the last backslash
  Backslash = "\\";
  nPos = location.href.lastIndexOf(Backslash) + 1;
  if (nPos > 0)
   {
    //Find the index of the first colon
    Del = /:/;
    nLen = location.href.search(Del);
    //Determine moniker protocol name length
    if (nLen == 2) //Protocol is mk:@MSITStore:
      nLen = 14;
    else if (nLen == 6) //Protocol is ms-its:
      {
      nLen = 7;
      }
    else
      nLen = 0;

    //Return new external Link
    Link = 'file:///' + location.href.substring(nLen, nPos) + Filename;
    return(Link);
    }
  else
    {
    return(Filename);
    }
  }

// ChmExtLnk() ----------------------------------------------------------------
// This functions resolves absolute path in order to make a link to a file
// located outside of a compiled help (.chm) file.
// The link will be redirected to new location
//
// Example:
// location.href = ms-its:C:\dir\file.chm::/topic.htm
//  ...
//  <head>
//  <script language="JavaScript" src="Dir/KChmExtLnk.js" type="text/javascript">
//  </script>
//  </head>
//  <!-- External link -->
//  <a onclick="ChmExtLnk('Path/Filename.ext')"
//     style="text-decoration: underline;
//     color: red;
//     cursor: pointer"> Some text</a>
function ChmExtLnk(Filename)
  {
  location.href = ChmFilePath(Filename);
  }

