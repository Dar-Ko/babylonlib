/**
 * @file  DebugFlags.h
 * @author  Pat Thoyts <patthoyts@users.sourceforge.net>
 * @note
 * @version $Id: KDbgActiveScript.h,v 1.2 2008/08/22 15:59:58 ddarko Exp $
 * @brief   Various helpers to provide useful human readable output
 *      when printing debug information for the IActiveScript*
 *      interface methods.
 */

#ifndef _DebugFlags_h_INCLUDE
#define _DebugFlags_h_INCLUDE

#include <atlapp.h>
#include <atlmisc.h>
#include <activscp.h>

#pragma warning ( disable : 4530 )
#include <sstream>

typedef std::basic_ostringstream<TCHAR> tostringstream;

#ifdef _DEBUG
#define DUMPSCRIPTTEXTFLAGS(f)  CActiveScriptDump::DumpScriptTextFlags((f));
#define DUMPSCRIPTITEMFLAGS(f)  CActiveScriptDump::DumpScriptItemFlags((f));
#define DUMPSCRIPTSTATEFLAGS(f) CActiveScriptDump::DumpScriptStateFlags((f));
#define DUMPSCRIPTITEMINFOFLAGS(f) CActiveScriptDump::DumpScriptItemInfoFlags((f));
#define DUMPSCRIPTTYPELIBFLAGS(f) CActiveScriptDump::DumpScriptTypeLibFlags((f));
#else // ! _DEBUG
#define DUMPSCRIPTTEXTFLAGS
#define DUMPSCRIPTITEMFLAGS
#define DUMPSCRIPTSTATEFLAGS
#define DUMPSCRIPTITEMINFOFLAGS
#define DUMPSCRIPTTYPELIBFLAGS
#endif // ! _DEBUG

class CActiveScriptDump
{
public:
  struct CTrans {
    DWORD   dw;
    LPCTSTR name;
    DWORD   value;
  };

  struct SS_trans {
    SCRIPTSTATE ss;
    LPCTSTR   name;
    DWORD     value;
  };

  struct STID_trans {
    SCRIPTTHREADID id;
    LPCTSTR    name;
  };

  static void DumpScriptItemFlags(DWORD dwFlags)
  {
    OutputDebugString(ScriptItemFlags(dwFlags));
  }

  static CString ScriptItemFlags(DWORD dwFlags)
  {
    static CTrans SI_tbl[] = {
      {SCRIPTITEM_CODEONLY,    _T("SCRIPTITEM_CODEONLY"),    0x00000200 },
      {SCRIPTITEM_GLOBALMEMBERS, _T("SCRIPTITEM_GLOBALMEMBERS"), 0x00000008 },
      {SCRIPTITEM_ISPERSISTENT,  _T("SCRIPTITEM_ISPERSISTENT"),  0x00000040 },
      {SCRIPTITEM_ISSOURCE,    _T("SCRIPTITEM_ISSOURCE"),    0x00000004 },
      {SCRIPTITEM_ISVISIBLE,   _T("SCRIPTITEM_ISVISIBLE"),   0x00000002 },
      {SCRIPTITEM_NOCODE,    _T("SCRIPTITEM_NOCODE"),    0x00000400 },
      {0, NULL, 0},
    };

    tostringstream toss;

    bool bdoneone = false;
    for (CTrans *p = SI_tbl; p->name != NULL; ++p)
    {
      if (dwFlags & p->dw)
      {
        if (bdoneone)
          toss << _T(" | ");
        toss << p->name;
        bdoneone = true;
      }
    }

    CString s(toss.str().c_str());
    return s;
  }

  static void DumpScriptTextFlags(DWORD dwFlags)
  {
    OutputDebugString(ScriptTextFlags(dwFlags));
  }

  static CString ScriptTextFlags(DWORD dwFlags)
  {
    static CTrans ST_tbl[] = {
      { SCRIPTTEXT_DELAYEXECUTION,  _T("SCRIPTTEXT_DELAYEXECUTION"),  0x00000001},
      { SCRIPTTEXT_ISVISIBLE,     _T("SCRIPTTEXT_ISVISIBLE"),     0x00000002},
      { SCRIPTTEXT_ISEXPRESSION,    _T("SCRIPTTEXT_ISEXPRESSION"),    0x00000020},
      { SCRIPTTEXT_ISPERSISTENT,    _T("SCRIPTTEXT_ISPERSISTENT"),    0x00000040},
      { SCRIPTTEXT_HOSTMANAGESSOURCE, _T("SCRIPTTEXT_HOSTMANAGESSOURCE"), 0x00000080},
      { 0, NULL, 0}
    };

    tostringstream toss;

    bool bOr = false;
    for (CTrans *p = ST_tbl; p->name != NULL; ++p)
    {
      if (p->dw & dwFlags)
      {
        if (bOr)
          toss << _T(" | ");
        toss << p->name;
        bOr = true;
      }
    }

    CString s(toss.str().c_str());
    return s;
  }

  static void DumpScriptStateFlags(SCRIPTSTATE ss)
  {
    OutputDebugString(ScriptStateFlags(ss));
  }

  static LPCTSTR ScriptStateFlags(SCRIPTSTATE ss)
  {
    static SS_trans SS_tbl[] = {
      { SCRIPTSTATE_UNINITIALIZED, _T("SCRIPTSTATE_UNINITIALIZED"), 0 },
      { SCRIPTSTATE_INITIALIZED,   _T("SCRIPTSTATE_INITIALIZED"),   5 },
      { SCRIPTSTATE_STARTED,     _T("SCRIPTSTATE_STARTED"),     1 },
      { SCRIPTSTATE_CONNECTED,   _T("SCRIPTSTATE_CONNECTED"),   2 },
      { SCRIPTSTATE_DISCONNECTED,  _T("SCRIPTSTATE_DISCONNECTED"),  3 },
      { SCRIPTSTATE_CLOSED,    _T("SCRIPTSTATE_CLOSED"),    4 },
      { SCRIPTSTATE_UNINITIALIZED, NULL, 0 }
    };
    for (SS_trans *p = SS_tbl; p->name != NULL && p->ss != ss; ++p) ;
    return p->name;
  }


  static void DumpScriptThreadIdFlags(SCRIPTTHREADID stid)
  {
    OutputDebugString(ScriptThreadIdFlags(stid));
  }

  static LPCTSTR ScriptThreadIdFlags(SCRIPTTHREADID stid)
  {
    static STID_trans tbl[] = {
      { SCRIPTTHREADID_CURRENT, _T("SCRIPTTHREADID_CURRENT") },
      { SCRIPTTHREADID_BASE,  _T("SCRIPTTHREADID_BASE")  },
      { SCRIPTTHREADID_ALL,   _T("SCRIPTTHREADID_ALL")   },
      { 0,            NULL             }
    };
    for (STID_trans *p = tbl; p->name != NULL && p->id != stid; p++) ;
    return p->name;
  }


  static void DumpScriptItemInfoFlags(DWORD dwFlags)
  {
    OutputDebugString(ScriptItemInfoFlags(dwFlags));
  }

  static CString ScriptItemInfoFlags(DWORD dwFlags)
  {
    static CTrans tbl[] = {
      { SCRIPTINFO_IUNKNOWN,  _T("SCRIPTINFO_IUNKNOWN"),  0x00000001 },
      { SCRIPTINFO_ITYPEINFO, _T("SCRIPTINFO_ITYPEINFO"), 0x00000002 },
      { 0, NULL, 0 },
    };

    tostringstream toss;

    bool bOr = false;
    for (CTrans *p = tbl; p->name != NULL; ++p)
    {
      if (p->dw & dwFlags)
      {
        if (bOr)
          toss << _T(" | ");
        toss << p->name;
        bOr = true;
      }
    }

    CString s(toss.str().c_str());
    return s;
  }

  static void DumpScriptTypeLibFlags(DWORD dwFlags)
  {
    OutputDebugString(ScriptTypeLibFlags(dwFlags));
  }

  static CString ScriptTypeLibFlags(DWORD dwFlags)
  {
    static CTrans tbl[] = {
      { SCRIPTTYPELIB_ISCONTROL,  _T("SCRIPTTYPELIB_ISCONTROL"),  0x00000010 },
      { SCRIPTTYPELIB_ISPERSISTENT, _T("SCRIPTTYPELIB_ISPERSISTENT"), 0x00000040 },
      { 0, NULL, 0 },
    };

    tostringstream toss;

    bool bOr = false;
    for (CTrans *p = tbl; p->name != NULL; ++p)
    {
      if (p->dw & dwFlags)
      {
        if (bOr)
          toss << _T(" | ");
        toss << p->name;
        bOr = true;
      }
    }

    CString s(toss.str().c_str());
    return s;
  }

};

#endif // _DebugFlags_h_INCLUDE

/*Copyright (C) 2002 <patthoyts@users.sourceforge.net>
 *
 * This is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2, or (at your option) any later
 * version.
 *
 * This program  is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; see the file `Copying'.  If not, write to the Free
 * Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */
