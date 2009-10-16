/*$Workfile: KCmdLineParser.cpp$: implementation file
  $Revision: 3$ $Date: 2005-07-07 17:49:41$
  $Author: Darko Kolakovic$

  Defines the class behavior.
  Copyright: CommonSoft Inc.
  2004-09-14 Darko Kolakovic
 */


#ifdef _MSC_VER //Microsoft Visual Studio C++ compiler
  #ifdef _UNICODE
    #ifndef UNICODE
      //To enable Unicode for some Microsoft Visual C/C++ header files,
      //the UNICODE definition is required
      #define UNICODE
    #endif
  #endif
#endif  //_MSC_VER

#include "KTChar.h"          //TCHAR typedef
#include "KCmdLineParser.h"  //CCmdLineParser class
#ifndef ASSERT
  #include "KTrace.h"
#endif

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CCmdLineParser class

//-----------------------------------------------------------------------------
/*Default constructor
 */
  CCmdLineParser::CCmdLineParser() :  
    m_pcmdOptions(NULL),
    m_nOptionsCount(0)
{
}

CCmdLineParser::CCmdLineParser(int argc, //[in] specifies how many arguments are
                          //passed to the  program from the command line. 
                          //The value of argc is at least one: the program name.
                              TCHAR* argv[] //[in] the program arguments as 
                          //an array of pointers to null-terminated strings. 
                          //The first string (argv[0]) is the program name. 
                          //The end of the array (argv[argc]) is indicated by 
                          //a NULL pointer.
                               )  :  
    m_pcmdOptions(NULL),
    m_nOptionsCount(0)
{
}

CCmdLineParser::CCmdLineParser(const CCmdLineParser& cmdLine) :
    m_pcmdOptions(cmdLine.m_pcmdOptions),
    m_nOptionsCount(cmdLine.m_nOptionsCount)
{
}

//-----------------------------------------------------------------------------
/*Destructor
 */
CCmdLineParser::~CCmdLineParser()
{
}

//-----------------------------------------------------------------------------
/*Set the list of the options or switches used to validate a comand input.
 */
void CCmdLineParser::SetOptions(const PCMDLINEOPTION pcmdOptions,//[in] list of
                                  //the allowed command options and option arguments
                                  //or NULL
                                const unsigned int nCount //[in] number of options
                                  //in the list of allowed command options
                               )
{
#ifndef _UNICODE //!fixme: TRACE unicode macro 
TRACE2(_T("CCmdLineParser::SetOptions(pcmdOptions = %p, nCount = %d"), 
       pcmdOptions, 
       nCount);
#endif
m_pcmdOptions = pcmdOptions;
if ( pcmdOptions == NULL)
  m_nOptionsCount = 0;
else
  m_nOptionsCount = nCount;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2005-07-07 17:49:41  Darko Kolakovic fixme: TRACE
 *       unicode macro
 *  2    Biblioteka1.1         2005-03-14 01:09:18  Darko           Added
 *       SetOptions()
 *  1    Biblioteka1.0         2005-03-11 18:05:36  Darko Kolakovic 
 * $
 *****************************************************************************/
