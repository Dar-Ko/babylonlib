/*
 * vss2rcs.js - Convert files from MS Visual SourceSafe into RCS format
 *
 * Requires Windows Scripting Host.
 * Requires ci.exe, rcs.exe and diff.exe compiled for NT.
 *
 * This script uses the Automation interface to Visual SourceSafe.
 * As a result, VSS must be installed on the machine where this is
 * run.  This has been tested with Visual Studio 6.0 SP3 under
 * Windows 2000.
 *
 * Copyright (C) 1999-2001 Curt Hagenlocher <curt@hagenlocher.org>
 * You may distribute under the terms of the GNU General Public License.
 *
 * Branching in VSS is completely ignored.  It's not really clear
 * how a VSS branch could map onto a CVS branch.
 *
 * The "shared-ness" of a VSS file is also ignored.  You'll have to
 * manually set up modules for sharing, as this doesn't seem to be
 * something that could be automated.
 *
 * There's no way to tell when in VSS a file was deleted.  As a result,
 * deleted files are put in the Attic, but may be labeled incorrectly.
 *
 * CHANGELOG:
 *
 * 1999-11-30  Initial Release
 * 2000-02-26  Added support for deleted files
 * 2000-04-29  Fixed handling of files which were deleted and recreated
 * 2000-05-18  Added special handling for out-of-order dates
 * 2001-02-01  Forced the revision numbers in the RCS file to match the
 *             VSS version numbers -- VSS version 23 becomes RCS rev 1.23
 * 2001-02-02  Created the repository before the first checkin so that
 *             binary files work correctly.  Previously, the initial add
 *             of the binary file would be truncated.
 * 2001-02-02  Fixed out-of-order date handling.  When the dates in VSS
 *             are somehow disordered, the corresponding dates in RCS
 *             will be wrong, but will at least be checked in correctly.
 *             (Previously, it aborted the file conversion.)
 * 2001-02-02  No longer requires administrator rights under NT/2000.
 * 2001-04-02  Added enhanced logging features (thanks to "ghoz").
 * 2001-07-09  fixed bug in addlog()
 * 2001-07-09  changed parameter '-n' in label_exec() to '-N' to allow
 *             re-labeling
 * 2003-04-03  Improved logging of RCS output to file and other cleanups
 *             (thanks to Nat Goodspeed)
 *
 * TODO:
 *
 * Add error handling
 * Support "Store only latest version" (why?)
 *
 */

///////////////////////////////////////////////////////////////////////
// Configuration information
//
// The only things you should have to change are in this section

// The VSS project directory to convert
var vss_project     = "$/";
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
var vss_ini_file    = "";
var vss_username    = "";
var vss_password    = "";

// Destination directory
var rcs_repository  = "c:\\cvsroot";

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


// With quiet set to true, the script will not popup for any reason,
// including errors
// With verbose set to true, the script will print out all RCS commands
// as they are run, directory and files creation
// With debug set to true, you'll get more popups than you'll ever need
var quiet           = false;
var verbose         = false;
var debug           = false;

// Enable Logging by setting log to true and logfile to the filename
// full_log set to true will log every RCS command

var log             = false
var full_log      = false;
var logfile         = ""

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

function FixupRCSPath(filename, deleted)
{
  if (deleted)
  {
    var re = filename.match(/^(.*)([\\/])([^\\/]+)$/);
    if (re)
      filename = re[1] + re[2] + "Attic" + re[2] + re[3];
    else
      filename = "Attic\\" + filename;
  }
  if (lowercase_paths)
    return filename.toLowerCase();
  else if (lowercase_files)
  {
    var re = filename.match(/^(.*)([\\/])([^\\/]+)$/);
    if (re)
      return re[1] + re[2] + re[3].toLowerCase();
    else
      return filename;
  }
  else if (lowercase_exts)
  {
    var re = filename.match(/^(.*)\.([^\\/.]+)$/);
    if (re)
      return re[1] + "." + re[2].toLowerCase();
    else
      return filename;
  }
  else
    return filename;
}

///////////////////////////////////////////////////////////////////////
// MatchFilename - inspired by the fnmatch module of Python

function MatchFilename(filespec, filename)
{
  return filename.match(TranslateFilespec(filespec));
}

var cachedFilespecs = new Object();

function TranslateFilespec(spec)
{
  if (cachedFilespecs[spec])
    return cachedFilespecs[spec];

  var i = 0;
  var result = "";
  while (i < spec.length)
  {
    var c = spec.charAt(i++);
    if (c == '*')
      result += ".*";
    else if (c == '?')
      result += '.';
    else if (c == '[')
    {
      var j = i;
      if (j < spec.length && spec.charAt(j) == '!')
        j++;
      if (j < spec.length && spec.charAt(j) == ']')
        j++;
      while (j < spec.length && spec.charAt(j) != ']')
        j++;
      if (j >= spec.length)
        result += "\\[";
      else
      {
        var stuff = spec.slice(i, j);
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
      result += "\\" + c;
    else
      result += c;
  }

  var attribute = fnmatch_case ? "" : "i";
  cachedFilespecs[spec] = new RegExp(result + '$', attribute);
  return cachedFilespecs[spec];
}

///////////////////////////////////////////////////////////////////////

function ReadAllStdOutStdErr(oExec)
{
     if (!oExec.StdOut.AtEndOfStream)
          return oExec.StdOut.ReadAll();

     if (!oExec.StdErr.AtEndOfStream)
          return oExec.StdErr.ReadAll();

     return -1;
}

///////////////////////////////////////////////////////////////////////

function ExecRCSCmd(cmd, options, filename)
{
  var cmdline = "\"" + rcs_path + cmd + "\" " + options + " \"" + filename + "\"";
  addlog(verbose, log && full_log, cmdline);

//  var type = (debug ? 1 : 0);
//
// 0 : hidden
// 1 : active restored
// 7 : minimized, active stays active
// 8 : restored, active stays active
//
//  if (shell.Run(cmdline, type, true) != 0)
//  {
//    throw cmdline;
//  }

    // The logic that follows is loosely derived from
    // http://msdn.microsoft.com/library/default.asp?url=/library/en-us/script56/html/wslrfexitcodeproperty.asp

    var oExec = shell.Exec(cmdline);

    var allOutput = "";
    var tryCount = 0;

    while (true)
    {
         var input = ReadAllStdOutStdErr(oExec);
         if (-1 == input)
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

    if (oExec.ExitCode != 0)
    {
        throw cmdline + "\n" + allOutput;
    }

    addlog(verbose, log && full_log, allOutput);
}

///////////////////////////////////////////////////////////////////////
// checkin object definition

function checkin(filename, version, created, binary, lastDate)
{
  this.version  = version;
  this.filename = filename;
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

function label(filename, text)
{
  this.text     = FixupLabel(text);
  this.filename = filename
  this.exec     = label_exec;
}

function label_exec()
{
  var cmdline   = "-N" + this.text + ":";
  ExecRCSCmd("rcs", cmdline, this.filename);
}

///////////////////////////////////////////////////////////////////////
// command object definition

function command(filename, cmd, options)
{
  this.cmd      = cmd;
  this.options  = options;
  this.filename = filename
  this.exec     = command_exec;
}

function command_exec()
{
  ExecRCSCmd(this.cmd, this.options, this.filename);
}

///////////////////////////////////////////////////////////////////////

var duplicatefiles = new Array();

function ConvertFile(project, localdir, filename)
{
  addlog(verbose, log, project + filename);
  var item = null, delitem = null;
  try
  {
    item      = db.VSSItem(project + filename, 0);
  }
  catch (x)
  {
  }
  try
  {
    delitem   = db.VSSItem(project + filename, vss_usedeleted);
  }
  catch (x)
  {
  }

  if (vss_usedeleted)
  {
    if (item != null && delitem != null)
    {
      // This file has both a deleted and an undeleted version
      if (duplicatefiles[project + filename] == "done")
        return; // Already processed
      duplicatefiles[project + filename] = "done";
    }

    if (item == null)
      item = delitem;
  }

  var localfile = FixupRCSPath(localdir + filename, item.Deleted);
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
      addlog(quiet, log, "Unknown action : " + version.Action);
    }
    versions.moveNext();
  }

  if (!created)
  {
    addlog(quiet, log, project + filename +
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
    addlog(quiet, log, "Error in cmd: " + err);
  }
}

function ConvertDir(project, localdir)
{
  try
  {
    addlog(verbose, log, "Creating " + localdir + "...");
    fs.CreateFolder(FixupRCSPath(localdir, false));
  }
  catch (err)
  {
  }
  try
  {
    var items = new Enumerator(db.VSSItem(project).Items(vss_usedeleted));
  }
  catch (err)
  {
    return;
  }
  while (!items.atEnd())
  {
    var item = items.item();
    if (item.Type == 0 && vss_subdirspec.length > 0 &&
      MatchFilename(vss_subdirspec, item.Name))
    {
      ConvertDir(project + item.Name + "/", localdir + item.Name + "\\");
    }
    else if (item.Type == 1 && MatchFilename(vss_filespec, item.Name))
    {
      ConvertFile(project, localdir, item.Name);
    }
    items.moveNext();
  }
}

function addlog(toscreen, tofile, logline)
{
  if (toscreen)
    WScript.Echo(logline);
  if (tofile)
    lf.WriteLine(logline);
}

var db    = new ActiveXObject("SourceSafe");
var fs    = new ActiveXObject("Scripting.FileSystemObject");
var shell = new ActiveXObject("WScript.Shell");

if (log)
  var lf = fs.OpenTextFile(logfile,2,true);

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

ConvertDir(vss_project, rcs_repository);
if (log)
  lf.close();
if (!quiet)
  WScript.echo ("Done.");



