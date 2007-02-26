/*$Workfile: KVss2Cvs.js$: script file
  $Revision: 4$ $Date: 2006-11-02 18:41:01$
  $Author: Darko Kolakovic$

  Converts Microsoft Visual SourceSafe repository to CVS format.
  Copyright: 1999-2001 Curt Hagenlocher
  1999-11-30 Curt Hagenlocher
  2004-10-29 Darko Kolakovic
 */

////////////////////////////////////////////////////////////////////////////////
/*Note: Microsoft Windows specific (Win32).

  Note: Requires Windows Scripting Host, Microsoft Visual SourceSafe (VSS),
  32-bit versions of Revision Control System tools ci.exe, rcs.exe and diff.exe.
  On systems with Win9x or WinNT, Windows Scripting Host have to be installed.

  See also: http://www.cs.purdue.edu/homes/trinkle/RCS/

  The script uses the Automation interface to Visual SourceSafe (VSS). VSS does
  not store date when in VSS a file was deleted, therefore such files are not
  labeled correctly after moving to CVS Attic. Branching is ignored because of
  different meaning of a branch in to systems.
  'Shared file' flag is also ignored.
 */

debugger;

////////////////////////////////////////////////////////////////////////////////
// Set default output

var g_defOut = new Object(); //default output device

if(this.WScript != null) //Windows Script Host shell
  {
  g_defOut.Write   = WScript.Echo;
  g_defOut.WriteLn = g_defOut.Write; //TODO:
  g_defOut.WriteHtml = WScript.Echo; //TODO: strip HTML

  main(); //Run the script
  }
else if (document != null) //HTML Browser shell
  {
    /*Note: Mozilla 1.5 generates NS_ERROR_XPC_BAD_OP_ON_WN_PROTO exception after
      assigning document.write/writeln to an object and accessing it:
         oWrite = document.write;
         oWrite("str");
     */

     //TODO: Replace HTML escapes : document.writeln(EscapeHTml());
  g_defOut.WriteLn =
    function (szText //[in] line of text to output
             )
      {
      if (szText != undefined)
        //Outputs text to either a message box or the command console window.
        document.writeln(escapeHtml2(szText) + "<br />");
      else
        document.writeln("&lt;null&gt;<br />");
      };
  g_defOut.Write =
    function (szText //[in] line of text to output
             )
      {
      if (szText != undefined)
        //Outputs text to either a message box or the command console window.
        document.write(escapeHtml2(szText));
      else
        document.write("&lt;null&gt;");
      };
  //Write preformatted HTML text
  g_defOut.WriteHtml =
    function (szText //[in] line of text to output
             )
      {
      if (szText != undefined)
        //Outputs text to either a message box or the command console window.
        document.write(szText);
      else
        document.write("&lt;null&gt;");
      };

  //Call main() from the HTML document
  }

///////////////////////////////////////////////////////////////////////////////
// Constants

//Definition of the argument values for the exit() function
/*const*/ var EXIT_SUCCESS = 0;
/*const*/ var EXIT_FAILURE = 1;
//Definition of the successful results
/*const*/ var S_OK         = 0;
/*const*/ var S_FALSE      = 1;
/*const*/ var NO_ERROR     = 0;
//Error codes
/*const*/ var ERROR_SUCCESS = 0; //no errors
/*const*/ var EOF = (-1); //'End of File' tags end of a stream

//-----------------------------------------------------------------------------
//COM type library constants
/*const*/ var ForReading   = 1;//open a file for reading only.
/*const*/ var ForWriting   = 2;//open a file for writing
/*const*/ var ForAppending = 8;//open a file and write to the end of the file

/*const*/ var TristateFalse      =  0;//opens the file as ASCII
/*const*/ var TristateTrue       = -1;//opens the file as Unicode
/*const*/ var TristateUseDefault = -2;//opens the file using the system default
/*const*/ var TristateMixed      = -2;

/////////////////////////////////////////////////////////////////////////////
// Resources
var resString = new Array(); //string resource lang=en
resString['ERR_ACTIVEX'] = "The script requires Microsoft ActiveX objects to run!";
resString['IDS_GETIE'] = 'Install the latest version of Internet Explorer.';
resString['IDS_IEVER'] = "This page requires Windows IE 5.5 or higher.";
resString['ERR_VSSARG'] = "Invalid VSS syntax: <syntax>\r\n" +
        "The syntax you entered is invalid in VSS.\r\n" +
        "This error has the following cause and solution:\r\n" +
        "You have entered a VSS file or project path that does not use valid syntax.\r\n"+
        "In VSS syntax, every path starts with a dollar sign followed by a series of\r\n"+
        "project names, which are separated by slashes and optionally\r\n"+
        "followed by a file name. For example:\r\n" +
        "  - $/ is the root project.\r\n" +
        "  - $/Code is a subproject of $/.\r\n" +
        "  - $/Code/Win/Test.C is a file in the $/Code/Win project.\r\n" +
        "Many parts of this syntax are optional. You can omit the dollar sign\r\n"+
        "in most circumstances. You can also shorten the path by basing it\r\n"+
        "on your current project; for example, if you are in $/Code, you can\r\n"+
        "type WIN as a shorthand for $/Code/Win, Test.C for $/Code/Test.C\r\n"+
        "and .. for the root.";
///////////////////////////////////////////////////////////////////////////////
// Starting point

//------------------------------------------------------------------------------
//Main
function main()
{
try
  {
  if (!isWinShell()) //ActiveX is required
    return EXIT_FAILURE;
var fs = new ActiveXObject("Scripting.FileSystemObject");

  }
catch(error)
 {
  if((error.result != undefined) && (error.result == 0x8057000c))
    {
    //NS_ERROR_XPC_BAD_OP_ON_WN_PROTO
    //Illegal operation on WrappedNative prototype object
    g_defOut.WriteLn(error);
    if (lf != undefined)
      lf.close();
    return EXIT_FAILURE;
    }
  g_defOut.WriteLn(error.message + ": " + logfile);
  bEnableLog = false; //Proceed without logging
  }

try
  {
  var db  = new ActiveXObject("SourceSafe");
  if (vss_ini_file.length > 0)
    db.Open(vss_ini_file, vss_username, vss_password);
  else
    db.Open();

  if (vss_project.charAt(vss_project.length - 1) != '/')
    vss_project    += '/';
  if (rcs_repository.charAt(rcs_repository.length - 1) != '\\')
    rcs_repository += '\\';
  if (rcs_path.length > 0 && rcs_path.charAt(rcs_path.length - 1) != '\\')
    rcs_path       += '\\';

  var shell = new ActiveXObject("WScript.Shell");
  ConvertDir(vss_project, rcs_repository);

  }
catch(error)
  {
  addlog(verbose, bEnableLog, error.description);
  g_defOut.WriteLn(error.message);
  }

if (lf != undefined)
  lf.close();
if (!quiet)
  g_defOut.WriteLn ("Done.");
};

///////////////////////////////////////////////////////////////////////////////
// Logger

// With quiet set to true, the script will not popup for any reason,
// including errors
// With verbose set to true, the script will print out all RCS commands
// as they are run, directory and files creation
// With debug set to true, you'll get more popups than you'll ever need
var quiet           = false;
var verbose         = false;
var debug           = true;

// Enable Logging by setting log to true and logfile to the filename
// full_log set to true will log every RCS command

var bEnableLog         = true
var full_log    = true;
var logfile     = "_VssCvs.log"

// Normalize some options
if (quiet)
  {
  verbose = false;
  debug   = false;
  }
var fsLog = new ActiveXObject("Scripting.FileSystemObject");

  //Create log file
var lf;
if(bEnableLog)
  {
  lf = fsLog.OpenTextFile(logfile, ForWriting, true, TristateUseDefault);
  }

//------------------------------------------------------------------------------
/*Display and log event messages.
 */
function addlog(bDisplayMessage,//[in]true if the message is to be displayed
                bWriteMessage, //[in] true if the message is to be written in the log
                szMessage      //[in] text do be displayed
               )
{
try
  {
  if (bDisplayMessage)
    g_defOut.WriteLn(szMessage);
  if (bWriteMessage && (lf != undefined))
    lf.WriteLine(szMessage);
  }
catch (err)
  {
  g_defOut.WriteLn(err.message);
  if (lf != undefined)
    lf.WriteLine(err.description);
  }
}

///////////////////////////////////////////////////////////////////////////////
// Helpers

//------------------------------------------------------------------------------
/*Verifies if the current browser is Microsoft Internet Explorer 5.0+ and if the
  platform is 32-bit Microsoft Windows OS.

  Returns: true if conditions are met, otherwise returns false.
  */
function validateBrowser()
{
var strVers = navigator.appVersion;
var strName = navigator.appName;
var strPlat = navigator.platform;
var intVer = strVers.indexOf("MSIE");
if (intVer > -1)
  {
  intVer = strVers.substring( intVer + 5, strVers.indexOf(";", intVer));
  intVer = parseInt(intVer);
  return (strName == "Microsoft Internet Explorer" && strPlat == "Win32" && intVer > 5);
  }
return false;
}

//------------------------------------------------------------------------------
/*Verifies if environment conditions are met.

  Returns: true if conditions are met, otherwise returns false.
  */
function isWinShell()
{
var bRes = true;
if (typeof ActiveXObject == 'undefined') //Microsoft IE shell is required
  {
  g_defOut.WriteLn(resString['ERR_ACTIVEX']);
  bRes = false;
  }
//Check the version of IE, if the shell is not WSH
if((this.WScript == null) && !validateBrowser())
  {
  g_defOut.WriteLn(resString['IDS_IEVER']);
  var strFormatMsg =
    "<p id='IDS_GETIE'><font size='2'>\n" +
    "  <a href='http://www.microsoft.com/isapi/redir.dll?Prd=Office&Sbp=Access&Pver=10&Ar=DPdesigner&Sba=IEhome&Plcid=1033'>\n  " +
    resString['IDS_GETIE'] +
    "\n  </a></font>\n</p>\n";
    g_defOut.WriteHtml(strFormatMsg);
  bRes = false;
  }
return bRes;
}

//-----------------------------------------------------------------------------
/*Replaces HTML 2.0 special characters with HTML entities. Function also
  converts single quote (') to escaped sequence (\').

     Character          Entity
     Less than sign        &lt;
     Greater than sign     &gt;
     Ampersand            &amp;
     Double quote sign    &quot;

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

//-----------------------------------------------------------------------------
/*Configuration information.
  Initialize following  configuration variables:
     vss_project          specifies the VSS project to use
     rcs_repository       describes the destination path and
     rcs_path             the directory containing RCS/CVS tools.
 */

// The VSS project directory to convert
//var vss_project     = "\\\\TPDC01\\VSS\\$/Build Versions/2002 06 10/Catapult_RAD";
var vss_project     = "$/Build Versions/2002 06 10/Catapult_RAD";
//var vss_project     = "$/";
var vss_usedeleted  = true;

// File specifications for the conversion
// To skip all subdirectories, leave vss_subdirspec empty
// Specifications follow the DOS/Un*x standard with *, ? and [].
var vss_filespec    = "*";
var vss_subdirspec  = "*";
var fnmatch_case    = false; // true if case-sensitive
var max_comment_len = 400;   // depends on various path lengths

// If one of these three is specified, then all must be
// With a standard, single-repository installation of VSS,
// these should probably be left blank.  If you have multiple
// VSS repositories, you may have to specify the one you
// want by setting the environmental variable SSDIR *before*
// running this script.
var vss_ini_file    = "\\\\tpdc01\\VSS\\srcsafe.ini";
var vss_username    = "DKolakovic";
var vss_password    = "a";

// Destination directory
var rcs_repository  = "C:\\Development\\catapult3.a";
//var rcs_repository  = "c:\\cvsroot";

// Directory containing ci.exe, diff.exe and rcs.exe.  This can be
// left blank if these are in current directory.  The versions of
// ci and rcs that come with WinCVS have a bug in their command-line
// parsing that prevent them from working if there are spaces in this
// path name, so instead of (e.g.) "c:\\Program Files\\WinCvs"
// you must specify (e.g.)         "c:\\Progra~1\\WinCvs"
//
// Oh, and for some reason, the Shell.Run command won't find them
// in the path.
var rcs_path        = "";




// Convert filenames to a standard case
// These form a hierarchy -- each (if true) implies that
// the next lower configuration is true as well.
var lowercase_paths = false;
var lowercase_files = false;
var lowercase_exts  = true;

// Convert usernames to a standard case
var lowercase_users = false;





///////////////////////////////////////////////////////////////////////
// Stack object definition

function stack()
{
  this.data   = new Array();
  this.empty  = stack_empty;
  this.push   = stack_push;
  this.pop    = stack_pop;
  this.top    = stack_top;
  this.show   = stack_print;
}

function stack_empty()
{
  if (this.data.length == 0)
    return true;
  else
    return false;
}

function stack_push(data)
{
  this.data[this.data.length] = data
}

function stack_pop()
{
  if (this.data.length == 0)
    return;

  var result = this.data[this.data.length - 1];
  this.data.length = this.data.length - 1;
  return result;
}

function stack_top()
{
  if (this.data.length == 0)
    return;
  return this.data[this.data.length - 1];
}

function stack_print()
{
  var dmesg ="";
  dmesg = "Show stack\n";
  for (var i = this.data.length -1  ; i >=0; i--)
  {
    dmesg += "n "+ i +" :\t"+ this.data[i].name + "\n";
  }
  g_defOut.WriteLn(dmesg);
}

///////////////////////////////////////////////////////////////////////
// Data format manipulation

function TwoDigit(x)
{
  var y = "0" + x;
  return y.substr(y.length-2, 2);
}

function MakeRCSDate(datestring)
{
  var cidate = new Date(datestring);
  return cidate.getUTCFullYear() + "/" + TwoDigit(1+cidate.getUTCMonth()) + "/" +
    TwoDigit(cidate.getUTCDate()) + " " + TwoDigit(cidate.getUTCHours()) + ":" +
    TwoDigit(cidate.getUTCMinutes()) + ":" + TwoDigit(cidate.getUTCSeconds());
}

function left(s, n)
{
  if (s.length < n)
    return s;
  else
    return s.substring(0, n);
}

function FixupComment(comment)
{
  // Comment cannot consist of only whitespace
  if (comment.match(/^\s*$/))
    comment = ".";

  // Replace double-quotes with single-quotes
  comment = comment.replace(/\"/g, "'");

  // Replace CR/LF with LF
  comment = comment.replace(/\r\n/g, "\n");

  // Replace multiple LFs with one
  comment = comment.replace(/\n+/g, "\n");

  return "\"" + left(comment, max_comment_len) + "\"";
}

function FixupLabel(label)
{
  // Convert illegal characters to underscores
  // Illegal characters include spaces
  label = label.replace(/[\000-\031 ,@#\.]/g, "_");

  // Labels cannot be all numeric
  if (label.match(/^\d+$/))
  {
    label = "_" + label;
  }

  return label;
}

function FixupUsername(username)
{
  if (lowercase_users)
    return username.toLowerCase();
  else
    return username;
}

function FixupRCSPath(szFilename, deleted)
{
  if (deleted)
  {
    var re = szFilename.match(/^(.*)([\\/])([^\\/]+)$/);
    if (re)
      szFilename = re[1] + re[2] + "Attic" + re[2] + re[3];
    else
      szFilename = "Attic\\" + szFilename;
  }
  if (lowercase_paths)
    return szFilename.toLowerCase();
  else if (lowercase_files)
  {
    var re = szFilename.match(/^(.*)([\\/])([^\\/]+)$/);
    if (re)
      return re[1] + re[2] + re[3].toLowerCase();
    else
      return szFilename;
  }
  else if (lowercase_exts)
  {
    var re = szFilename.match(/^(.*)\.([^\\/.]+)$/);
    if (re)
      return re[1] + "." + re[2].toLowerCase();
    else
      return szFilename;
  }
  else
    return szFilename;
}


//------------------------------------------------------------------------------
/*Get a text output sent by Windows Script Shell to the standard streams.
  Returns the Windows Script Shell output or EOF if streams are empty.
 */
function ReadAllStdOutStdErr(oExec //[in] WshScriptExec object
                            )
{
//The StdOut property contains a read-only copy of any information the
//script may have sent to the standard output.
if (!oExec.StdOut.AtEndOfStream)
  return oExec.StdOut.ReadAll();
//Get data sent to the stderr stream
if (!oExec.StdErr.AtEndOfStream)
  return oExec.StdErr.ReadAll();

return EOF;
}

//------------------------------------------------------------------------------
//
function ExecRCSCmd(cmd,     //[in] a command to be executed
                    options, //[in] the command arguments
                    szFilename //[in] file name to proccess
                   )
{
var cmdline = "\"" + rcs_path + cmd + "\" " + options + " \"" + szFilename + "\"";
addlog(verbose, bEnableLog && full_log, cmdline);

// The logic that follows is loosely derived from
// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/script56/html/wslrfexitcodeproperty.asp

var oExec = shell.Exec(cmdline);

var allOutput = "";
var tryCount = 0;

while (true)
  {
  var input = ReadAllStdOutStdErr(oExec);
  if (EOF == input)
    {
    if (tryCount++ > 10 && oExec.Status == 1)
      break;
    WScript.Sleep(100);
    }
  else
    {
    allOutput += input;
    tryCount = 0;
    }
  }

/*Check the exit code set by a program run using the Exec() method.
  If the process has not finished, the ExitCode property returns 0.
  The values returned from ExitCode depend on the application that was called.
 */
if (oExec.ExitCode != EXIT_SUCCESS) //Warning: Non-zero exit code
  {
  //It is assumed that the command executed returns non-zero in case of failure
  throw cmdline + "\n" + allOutput;
  }

addlog(verbose, bEnableLog && full_log, allOutput);
}

//------------------------------------------------------------------------------
//Checkin object definition
function checkin(szFilename, version, created, binary, lastDate)
{
  this.version  = version;
  this.filename = szFilename;
  this.exec     = checkin_exec;
  this.first    = created;
  this.binary   = binary;
  this.date = new Date(version.Date);
  if (this.date.getTime() > lastDate.getTime())
  {
    // The files in VSS were not in time order!
    this.comment = FixupComment("[" + this.date + "] " + this.version.Comment);
    this.date = lastDate;
  }
  else
  {
    this.comment = FixupComment(this.version.Comment);
  }
}

//------------------------------------------------------------------------------
function checkin_exec()
{
  var username  = FixupUsername(this.version.Username);
  var date      = MakeRCSDate(this.date);
  var revision  = this.version.VersionNumber;
  var item      = this.version.VSSItem;

  // Get the file from VSS
  item.Get(this.filename, 128);

  // Create the RCS file if it doesn't exist
  if (this.first)
  {
    var rcscmd = "-i -U -t-";
    if (this.binary)
      rcscmd += " -kb";
    ExecRCSCmd("rcs", rcscmd, this.filename);
  }

  // Add the VSS file to the RCS repository
  var cmdline   = "-w" + username + " -d\"" + date + "\" -r1." + revision + " -m" + this.comment;
  ExecRCSCmd("ci", cmdline, this.filename);
}

///////////////////////////////////////////////////////////////////////
// label object definition

function label(szFilename, text)
{
  this.text     = FixupLabel(text);
  this.filename = szFilename
  this.exec     = label_exec;
}

function label_exec()
{
  var cmdline   = "-N" + this.text + ":";
  ExecRCSCmd("rcs", cmdline, this.filename);
}

///////////////////////////////////////////////////////////////////////
// command object definition

function command(szFilename, cmd, options)
{
  this.cmd      = cmd;
  this.options  = options;
  this.filename = szFilename
  this.exec     = command_exec;
}

//-----------------------------------------------------------------------------
function command_exec()
{
  ExecRCSCmd(this.cmd, this.options, this.filename);
}

///////////////////////////////////////////////////////////////////////



//-----------------------------------------------------------------------------
/*
 */
function ConvertFile(project, localdir, szFilename)
{
  addlog(verbose, bEnableLog, project + szFilename);
  var item = null, delitem = null;
  try
  {
    item      = db.VSSItem(project + szFilename, 0);
  }
  catch (x)
  {
  }
  try
  {
    delitem   = db.VSSItem(project + szFilename, vss_usedeleted);
  }
  catch (x)
  {
  }

  if (vss_usedeleted)
  {
    if (item != null && delitem != null)
      {
      var duplicatefiles;
      if(duplicatefiles == undefied)
        duplicatefiles = new Array();
      //This file has both a deleted and an undeleted version
      if (duplicatefiles[project + szFilename] == "done")
        return; // Already processed
      duplicatefiles[project + szFilename] = "done";
      }

    if (item == null)
      item = delitem;
  }

  var localfile = FixupRCSPath(localdir + szFilename, item.Deleted);
  var versions  = new Enumerator(item.Versions);
  var cmds      = new stack();
  var created   = false;

  // Set an upper bound for the time on the checkin
  var lastDate = new Date();
  lastDate.setFullYear(lastDate.getFullYear() + 1);

  if (item.Deleted)
  {
    // For a deleted file, the last thing to do is to mark it dead
    cmds.push(new command(localfile, "rcs", "-sdead"));
  }

  // Otherwise, the last thing to do when converting the file is to
  // reset it back to standard locking.  Put the lock
  // command at the bottom of the stack.
  cmds.push(new command(localfile, "rcs", "-L"));

  while (!created && !versions.atEnd())
  {
    var version = versions.item();
    if (version.Action.substring(0, 7) == "Created")
    {
      var c = new checkin(localfile, version, true, item.Binary, lastDate);
      cmds.push(c);
      lastDate = new Date(c.date);
      created = true;
    }
    else if (version.Action.substring(0, 10) == "Checked in")
    {
      var c = new checkin(localfile, version, false, item.Binary, lastDate);
      cmds.push(c);
      lastDate = new Date(c.date);
    }
    else if (version.Action.substring(0, 7) == "Labeled")
    {
      cmds.push(new label(localfile, version.Label));
    }
    else
    {
      addlog(quiet, bEnableLog, "Unknown action : " + version.Action);
    }
    versions.moveNext();
  }

  if (!created)
  {
    addlog(quiet, bEnableLog, project + szFilename +
      " was never created.  Is there both a deleted and a non-deleted version?");
  }

  try
  {
    if (debug)
      cmds.show();
    while (!cmds.empty())
    {
      cmds.pop().exec();
    }
  }
  catch (err)
  {
    addlog(quiet, bEnableLog, "Error in cmd: " + err);
  }
}

//------------------------------------------------------------------------------
/*
 */
function ConvertDir(project, localdir)
{
try
  {
  addlog(verbose, bEnableLog, "Creating " + localdir + "...");
  fs.CreateFolder(FixupRCSPath(localdir, false));
  }
catch (err)
  {
  addlog(verbose, bEnableLog, err.description + ": " + localdir );
  if (err.number == -2146823279) //TypeError
    {
    if (fs == undefined)
      {
      g_defOut.WriteLn(err.name + ": " + err.description);
      return;
      }
    }
  }

  try
  {
    var items = new Enumerator(db.VSSItem(project).Items(vss_usedeleted));
  }
  catch (err)
  {
    if (err.number == -2147166483)
      {
      g_defOut.WriteLn(resString['ERR_VSSARG']);
      }
    addlog(verbose, bEnableLog, err.description + ": " + project);
    return;
  }
  if (items.atEnd())
    {
    g_defOut.WriteLn("Nothing to do with " + project);
    addlog(verbose, bEnableLog, project + " has no items!");
    return;
    }
  else
    {
    var arrRegexCache = new Array(); //stored filename patterns for speedy access
    while (!items.atEnd())
      {
      var item = items.item();
      if( (item.Type == 0) &&
          (vss_subdirspec.length > 0) &&
          FnMatch(item.Name, vss_subdirspec, fnmatch_case, arrRegexCache) )
        {
        ConvertDir(project + item.Name + "/", localdir + item.Name + "\\");
        }
      else if ( (item.Type == 1) && FnMatch(item.Name, vss_filespec, fnmatch_case, arrRegexCache))
        {
        ConvertFile(project, localdir, item.Name);
        }
      items.moveNext();
      }
    }
}




///////////////////////////////////////////////////////////////////////////////
/* Copyright (C) 1999-2001 Curt Hagenlocher <curt@hagenlocher.org>
   You may distribute under the terms of the GNU General Public License.
 */
/******************************************************************************
 *$Log:
 * 4    Biblioteka1.3         2006-11-02 18:41:01  Darko Kolakovic Replaced
 *      FnMatch()
 * 3    Biblioteka1.2         2006-11-02 10:36:10  Darko Kolakovic Error handling
 * 2    Biblioteka1.1         2006-11-01 16:11:50  Darko Kolakovic Comments
 * 1    Biblioteka1.0         2006-11-01 15:21:31  Darko Kolakovic
 *$
 * 1    Biblioteka1.0         2004-11-12 17:55:51  Darko Kolakovic
 *2003-04-03  Improved logging of RCS output to file and other cleanups
 *2001-07-09  changed parameter '-n' in label_exec() to '-N' to allow
 *            re-labeling
 *2001-07-09  fixed bug in addlog()
 *2001-04-02  Added enhanced logging features (thanks to "ghoz").
 *2001-02-02  No longer requires administrator rights under NT/2000.
 *2001-02-02  Fixed out-of-order date handling.  When the dates in VSS
 *            are somehow disordered, the corresponding dates in RCS
 *            will be wrong, but will at least be checked in correctly.
 *            (Previously, it aborted the file conversion.)
 *2001-02-02  Created the repository before the first checkin so that
 *            binary files work correctly.  Previously, the initial add
 *            of the binary file would be truncated.
 *2001-02-01  Forced the revision numbers in the RCS file to match the  VSS
 *            version numbers -- VSS version 23 becomes RCS rev 1.23
 *2000-05-18  Added special handling for out-of-order dates
 *2000-04-29  Fixed handling of files which were deleted and recreated
 *2000-02-26  Added support for deleted files
 *1999-11-30  Curt Hagenlocher curth@motek.com Initial Release
 *****************************************************************************/

