/*$Workfile: KDbgTraceLog.cpp$: implementation file
  $Revision: 10$ $Date: 2005-05-04 01:26:40$
  $Author: Darko$

  Set dump or trace output
  Copyright: CommonSoft Inc.
  July 98 Darko Kolakovic
 */

// Group=Diagnostic

#include <afxwin.h>

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

//EnableTraceLog()-------------------------------------------------------------
/*Creates trace log file for a CDumpContext object and redirects all output
  to the log file. Pointer to the log file name is NULL by default and output
  is redirected to the output window if present.

  Note: CFile* m_pFile is public member of the CDumpContext class and will
  be replaced with pointer to the static CFile object. Trace log file is
  a binary file.

  Note: uses Microsoft Foundation Library (MFC).
        Microsoft Windows specific (Win).

  Example:
      #ifdef _DEBUG
        #define new DEBUG_NEW
        #undef THIS_FILE
        static char THIS_FILE[] = __FILE__;
        extern void EnableTraceLog(CDumpContext& dc,LPCTSTR szLogFileName);
        extern void DumpOSVI();
        LPCTSTR g_strDbgLog = _T("Trace001.Log");//Debug log file name
      #endif
      class CMyApp: public CWinApp
        {
        CMyApp();
        virtual ~CMyApp();
        ...
        };
        //Default constructor
      CMyApp::CMyApp() :  m_hinstRes(NULL)
        {
        #ifdef _DEBUG
          EnableTraceLog(afxDump,g_strDbgLog);
          TRACE0("Debug output is redirected to the file\r\n");
          DumpOSVI(); //Dump the operating system version information
        #endif
        // Place all significant initialization in InitInstance
        }

      CMyApp::~CMyApp()
        {
        TRACE0("CMyApp::~CMyApp\n");
        #ifdef _DEBUG
          if (g_strDbgLog != NULL)  //Disable logging
            {
            EnableTraceLog(afxDump,NULL);
            }
        #endif
        }

  See also: afxDump, CDumpContext.
 */
void EnableTraceLog(CDumpContext& dc, //Dump context (afxDump)
                    LPCTSTR szLogFileName //afxDump output file name.
                                          //if NULL, output will go to the
                                          //output window
                    )
{
static CFile* pOldFile;
static CFile fileTraceLog;
if (pOldFile == NULL)
  pOldFile = dc.m_pFile;

if (szLogFileName != NULL) //Open a log file
  {
  pOldFile = dc.m_pFile;
  if(!fileTraceLog.Open(szLogFileName,
                        CFile::modeCreate |
                        CFile::modeReadWrite ))
    {
    dc << "Unable to open file" << szLogFileName << "\n";
    exit(EXIT_FAILURE);
    }
  else
    dc.m_pFile = &fileTraceLog;
  }
else //Redirect output to the output (debug or auxiliary) window
  {
  if ((dc.m_pFile != NULL) && (dc.m_pFile->m_hFile != CFile::hFileNull))
    dc.m_pFile->Close();
  dc.m_pFile = pOldFile;
  }
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  6    Biblioteka1.5         2002-01-29 23:20:33  Darko           Used lbraries
 *       notes
 *  5    Biblioteka1.4         2002-01-29 15:39:08  Darko           Tag update
 *  4    Biblioteka1.3         2001-08-19 23:52:59  Darko           Butyfier
 *  3    Biblioteka1.2         2001-07-11 22:50:44  Darko
 *  2    Biblioteka1.1         2001-06-08 23:50:09  Darko           VSS
 *  1    Biblioteka1.0         2000-08-13 15:56:02  Darko
 * $
 *****************************************************************************/
