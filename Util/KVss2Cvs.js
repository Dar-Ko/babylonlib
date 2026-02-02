/*$Workfile: KVss2Cvs.js$: script file
  $Revision: 5$ $Date: 2007-01-11 11:02:54$
  $Author: Darko Kolakovic$

  Converts  Microsoft Visual SourceSafe repository to CVS format.
  Copyright: 1999-2001 Curt Hagenlocher
  1999-11-30 Curt Hagenlocher
 */

////////////////////////////////////////////////////////////////////////////////
/*Note: Microsoft Windows specific (Win32).

  Note: Requires Windows Scripting Host, Microsoft Visual SourceSafe (VSS),
  32-bit versions of Revision Control System tools ci.exe, rcs.exe and diff.exe.
  On systems with Win9x or WinNT, Windows Scripting Host have to be installed.

  Note: The script uses exceptions and requires a script engine compliant
  with ECMA-262, 3rd Edition, 1999.
  
  See also: http://www.cs.purdue.edu/homes/trinkle/RCS/

  The script uses the Automation interface to Visual SourceSafe (VSS). VSS does
  not store date when in VSS a file was deleted, therefore such files are not
  labelled correctly after moving to CVS Attic. Branching is ignored because of
  different meaning of a branch in to systems.
  'Shared file' flag is also ignored.
 */
//-----------------------------------------------------------------------------
/*Configuration information.
  Initialize following  configuration variables:
     g_szVssProject       specifies the VSS project to use
     rcs_repository       describes the destination path and
     rcs_path             the directory containing RCS/CVS tools.
 */

/*The VSS project directory to convert. A project is a collection of files
  that you store in VSS. A VSS database could have one  or more projects.
  Project name have following format:
        $/<project name>/<sub project name>/...
*/
//var g_szVssProject     = "\\\\UNC\\MACHINE\\VSS\\$/Build Versions/ProjectName/";
var g_szVssProject     = "$/Build Versions/ProjectName/";
//var g_szVssProject     = "$/";
/*Indicate if deleted VSS items are to be included in the current items
  collection. The default value of this parameter is false.
  SourceSafe allows the user to delete a file or project item.
  SourceSafe retains deleted items until they are purged or recovered.
  The Deleted property of a VSSItem is used to set or retrieve the current
  deleted state of the object. When a project is deleted, all of
  its files and sub-projects are deleted as well.
 */
var g_bVssIncludeDeleted  = true;

// File specifications for the conversion
// To skip all subdirectories, leave g_szVssFilterSubdir empty
// Filter uses Unix wildcard characters *, ? and [].
var g_szVssFilterFilename  = "*";   //VSS filename filter
var g_szVssFilterSubdir    = "[!xyq]";//"*";   //VSS subdirectory name filter
var g_bCaseComaparaison    = false; //true if case-sensitive
var max_comment_len = 400;   // depends on various path lengths

// If one of these three is specified, then all must be
// With a standard, single-repository installation of VSS,
// these should probably be left blank.  If you have multiple
// VSS repositories, you may have to specify the one you
// want by setting the environmental variable SSDIR *before*
// running this script.
var vss_ini_file    = "\\\\UNC\\VSS\\srcsafe.ini";
var vss_username    = "DKolakovic";
var vss_password    = "a";

// Destination directory
var rcs_repository  = "C:\\Development\\target";
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


// With quiet set to true, the script will not pop-up for any reason,
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

// Convert filenames to a standard case
// These form a hierarchy -- each (if true) implies that
// the next lower configuration is true as well.
var lowercase_paths = false;
var lowercase_files = false;
var lowercase_exts  = true;

// Convert usernames to a standard case
var lowercase_users = false;

// Normalize some options
if (quiet)
  {
  verbose = false;
  debug   = false;
  }

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

//COM type library constants
var ForReading   = 1;//open a file for reading only. You can't write to this file.
var ForWriting   = 2;//open a file for writing
var ForAppending = 8;//open a file and write to the end of the file

var TristateFalse      =  0;//opens the file as ASCII
var TristateTrue       = -1;//opens the file as Unicode
var TristateUseDefault = -2;//opens the file using the system default
var TristateMixed      = -2;

//VSSItemType Constants
//See also: http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dnvss/html/vssauto.asp
/*Const*/ var VSSITEM_FILE    = 1; //the object represents a file
/*Const*/ var VSSITEM_PROJECT = 0; //the object represents a VSS project.

//------------------------------------------------------------------------------
//Main
try
  {
  var fs = new ActiveXObject("Scripting.FileSystemObject");
    //Create log file
  if(bEnableLog)
    {
    var lf = fs.OpenTextFile(logfile, ForWriting, true, TristateUseDefault);
    }
  }
catch(error)
  {
  WScript.echo(error.message + ": " + logfile);
  bEnableLog = false; //Proceed without logging
  }

try
  {
  //Visual SourceSafe 6.0 Automation object
  var db  = new ActiveXObject("SourceSafe");
  if (vss_ini_file.length > 0)
    db.Open(vss_ini_file, vss_username, vss_password);
  else
    db.Open();

  //Append trailing directory delimiter
  if (g_szVssProject.charAt(g_szVssProject.length - 1) != '/')
    g_szVssProject    += '/';
  if (rcs_repository.charAt(rcs_repository.length - 1) != '\\')
    rcs_repository += '\\';
  if (rcs_path.length > 0 && rcs_path.charAt(rcs_path.length - 1) != '\\')
    rcs_path       += '\\';

  var shell = new ActiveXObject("WScript.Shell");
  var duplicatefiles = new Array();
  var cachedFilespecs  = new Object();

  ConvertDir(g_szVssProject, rcs_repository);
  }
catch(error)
  {
  addlog(verbose, bEnableLog, error.description);
  WScript.echo(error.message);
  }

if (lf != undefined)
  lf.close();
if (!quiet)
  WScript.echo ("Done.");

//------------------------------------------------------------------------------
/*
 */
function ConvertDir(szVssProjectName, //[in] VSS project name
                    szWorkingFolder   //[in] folder where VSS copies files out
                    )
{
try
  {
  addlog(verbose, bEnableLog, "Creating " + szWorkingFolder + "...");
  fs.CreateFolder(FixupRCSPath(szWorkingFolder, false));
  }
catch (err)
  {
  addlog(verbose, bEnableLog, err.description + ": " + szWorkingFolder );
  }

try
  {
  /*The Items property is used to reference the collection of VSSItems within
    a project object. Each SourceSafe project may contain up to four types of
    objects. These are:
        - Deleted files
        - Deleted projects
        - Non-deleted files
        - Non-deleted projects
    The optional Boolean parameter is used to indicate if deleted items
    are to be included in the current collection.
   */
  var items = new Enumerator(db.VSSItem(szVssProjectName).Items(g_bVssIncludeDeleted));
  }
catch (err)
  {
  if (err.number == -2147166483)
    {
    WScript.echo("Invalid VSS syntax: <syntax>\r\n" +
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
      "and .. for the root.");
    }
  addlog(verbose, bEnableLog, err.description + ": " + szVssProjectName);
  return;
  }

if (items.atEnd())
  {
  WScript.Echo("Nothing to do with " + szVssProjectName);
  addlog(verbose, bEnableLog, szVssProjectName + " has no items!");
  return;
  }
else while (!items.atEnd())
  {
  //Filter out required items.
  var vssItem = items.item(); //VSSItem object represents a file or project
                              //item within the SourceSafe database.
  switch(vssItem.Type)
    {
    case VSSITEM_PROJECT:
      //A project is a collection of files (any type) that you store in VSS.
      if(g_szVssFilterSubdir.length > 0)
        if (FnMatch(vssItem.Name, g_szVssFilterSubdir, g_bCaseComaparaison) )
          ConvertDir(szVssProjectName + vssItem.Name + "/",
                     szWorkingFolder + vssItem.Name + "\\");
      break;
    case VSSITEM_FILE:
      if(FnMatch(vssItem.Name, g_szVssFilterFilename, g_bCaseComaparaison) )
        ExportVssFile(szVssProjectName, szWorkingFolder, vssItem.Name);
      break;
    default:
    }

  items.moveNext();
  }
}

//-----------------------------------------------------------------------------
/*
 */
function ExportVssFile(szVssProjectName,//[in] VSS project name
                     szWorkingFolder, //[in] folder where VSS copies files out
                     szFilename       //[in]
                    )
{
addlog(verbose, bEnableLog, szVssProjectName + szFilename);
var item = null, itemDeleted = null;
try
  {
  //Obtain an undeleted item
  item = db.VSSItem(szVssProjectName + szFilename, false);
  }
catch (x)
  {
  }

  //Fetch deleted VSS items
try
  {
  itemDeleted   = db.VSSItem(szVssProjectName + szFilename, g_bVssIncludeDeleted);
  }
catch (x)
  {
  }

if (g_bVssIncludeDeleted)
  {
  if (item != null && itemDeleted != null)
    {
    if(duplicatefiles == undefied)
      duplicatefiles = new Array();
    //This file has both a deleted and an undeleted version
    if (duplicatefiles[szVssProjectName + szFilename] == "done")
      return; // Already processed
    duplicatefiles[szVssProjectName + szFilename] = "done";
    }

  if (item == null)
    item = itemDeleted;
  }

//Create a list of actions required to import a file to the CVS repository
var localfile = FixupRCSPath(szWorkingFolder + szFilename, item.Deleted);
var versions  = new Enumerator(item.Versions);
var cmds      = new stack();
var created   = false;

// Set an upper bound for the time on the checking
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

  /*Possible values for the Action property are:
    - Added
    - Branch at version <version number>
    - Checked in <SourceSafe file path>
    - Created
    - Deleted
    - Destroyed
    - Labelled <label>
    - Moved <old SourceSafe path> to <new SourceSafe path>
    - Renamed <old name> to <new name>
    - Shared <SourceSafe file path>
   undocumented values are:
    - Pinned
    - Purged
    - Recovered
    - Roll back to version <number>
    - Unpinned
    Bug: Moved action is impossible to produce because of the bug in the
    Microsoft software.
   */

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
  else if (version.Action.substring(0, 7) == "Labelled")
    {
    cmds.push(new label(localfile, version.Label));
    }
  else if (version.Action.substring(0, 19) == "Roll-back to version")
    {
    var c = new checkin(localfile, version, false, item.Binary, lastDate);
    cmds.push(c);
    lastDate = new Date(c.date);
    }
  else
    {
    addlog(quiet, bEnableLog, "Unhandled action: " + version.Action);
    }
  versions.moveNext();
  }

if (!created)
  {
  addlog(quiet, bEnableLog, szVssProjectName + szFilename +
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
  WScript.echo(dmesg);
}

///////////////////////////////////////////////////////////////////////
// Data format manipulation

function TwoDigit(x)
{
var y = "0" + x;
return y.substr(y.length-2, 2);
}

//-----------------------------------------------------------------------------
function MakeRCSDate(datestring)
{
var cidate = new Date(datestring);
return cidate.getUTCFullYear() + "/" + TwoDigit(1+cidate.getUTCMonth()) + "/" +
  TwoDigit(cidate.getUTCDate()) + " " + TwoDigit(cidate.getUTCHours()) + ":" +
  TwoDigit(cidate.getUTCMinutes()) + ":" + TwoDigit(cidate.getUTCSeconds());
}

//-----------------------------------------------------------------------------
function left(s, n)
{
if (s.length < n)
  return s;
else
  return s.substring(0, n);
}

//-----------------------------------------------------------------------------
function FixupComment(comment)
{
//Comment cannot consist of only white-space
if (comment.match(/^\s*$/))
  comment = ".";

//Replace double-quotes with single-quotes
comment = comment.replace(/\"/g, "'");

//Replace CR/LF with LF
comment = comment.replace(/\r\n/g, "\n");

//Replace multiple LFs with one
comment = comment.replace(/\n+/g, "\n");

return "\"" + left(comment, max_comment_len) + "\"";
}

//-----------------------------------------------------------------------------
function FixupLabel(label)
{
// Convert illegal characters to underscores
// Illegal characters include spaces
label = label.replace(/[\000-\031 ,@#\.]/g, "_");

// Labels cannot be all numeric
if (label.match(/^\d+$/))
  label = "_" + label;

return label;
}

//-----------------------------------------------------------------------------
function FixupUsername(username)
{
if (lowercase_users)
  return username.toLowerCase();
else
  return username;
}

//-----------------------------------------------------------------------------
/*
 */
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

//-----------------------------------------------------------------------------
/*Filename pattern matching. Matches a filename with a pattern consisting of
  characters and wildcards. The special characters used as wildcards are:

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

var i = 0;
var szRegex = ""; //regular expression pattern to match
while (i < szPattern.length)
  {
  var c = szPattern.charAt(i++);
  if (c == '*')
    szRegex += ".*";
  else if (c == '?')
    szRegex += '.';
  else if (c == '[')
    {
    var j = i;
    if (j < szPattern.length && szPattern.charAt(j) == '!')
      j++;
    if (j < szPattern.length && szPattern.charAt(j) == ']')
      j++;
    while (j < szPattern.length && szPattern.charAt(j) != ']')
      j++;
    if (j >= szPattern.length)
      szRegex += "\\[";
    else
      {
      var stuff = szPattern.slice(i, j);
      i = j + 1;
      if (stuff.charAt(0) == '!')
        stuff = "[^" + stuff.slice(1) + ']';
      else if (stuff == substring("^^^^^^^^^^^^^^^^", 0, stuff.length))
        stuff = '\\^';
      else
        {
        while (stuff.charAt(0) == '^')
          stuff = stuff.slice(1) + stuff.charAt(0);
        stuff = '[' + stuff + ']';
        }
      res += stuff;
      }
    }
  else if (c.match(/\W/))
    szRegex += "\\" + c;
  else
    szRegex += c;
  }

cachedFilespecs[szPattern] = new RegExp(szRegex + '$', bCaseInsensitive ? "" : "i");
return szFilename.match(cachedFilespecs[szPattern]);
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
                    szFilename //[in] file name to process
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
//Add a comment if not exist previously
this.comment = ((version.Comment == "") ?
                   this.version.Action : this.version.Comment);

//The files in VSS were not in time order!
if (this.date.getTime() > lastDate.getTime())
  {
  this.comment = this.date + ": " + this.comment;
  this.date = lastDate;
  }
this.comment = FixupComment(this.comment);
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
    WScript.Echo(szMessage);
  if (bWriteMessage && (lf != undefined))
    lf.WriteLine(szMessage);
  }
catch (err)
  {
  WScript.echo(err.message);
  if (lf != undefined)
    lf.WriteLine(err.description);
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

