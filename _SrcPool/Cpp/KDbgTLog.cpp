/*$Workfile: H:\_SrcPool\Cpp\KDbgTLog.cpp$: implementation file
  $Revision: 1.1 $ $Date: 2002/09/06 22:10:21 $
  $Author: ddarko $

  Set dump or trace output
  Copyright: CommonSoft Inc.
  July 98 Darko Kolakovic
 */ 

// Group=Diagnostic

#include <AfxWin.h>

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

  Note: uses Microsoft Fundation Library (MFC).
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
    afxDump << "Unable to open file" << szLogFileName << "\n";
    exit(1);
    }
  else
    dc.m_pFile = &fileTraceLog;
  }
else //Redirect output to the output window
  {
  if ((dc.m_pFile != NULL) && (dc.m_pFile->m_hFile != CFile::hFileNull))
    dc.m_pFile->Close();
  dc.m_pFile = pOldFile;
  }
}
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         1/29/02 10:20:33 PM  Darko           Used lbraries
 *       notes 
 *  5    Biblioteka1.4         1/29/02 2:39:08 PM   Darko           Tag update
 *  4    Biblioteka1.3         8/19/01 10:52:59 PM  Darko           Butyfier
 *  3    Biblioteka1.2         7/11/01 9:50:44 PM   Darko           
 *  2    Biblioteka1.1         6/8/01 10:50:09 PM   Darko           VSS
 *  1    Biblioteka1.0         8/13/00 2:56:02 PM   Darko           
 * $
 *****************************************************************************/
