/*$Workfile: S:\_SrcPool\Cpp\KCmdLineParser.h$: header file
  $Revision: 1$ $Date: 2005-03-11 17:05:38$
  $Author: Darko Kolakovic$

  file description
  Copyright: CommonSoft Inc
  <date> Darko Kolakovic
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KCCMDLINEPARSER_H_
    //$Workfile: S:\_SrcPool\Cpp\KCmdLineParser.h$ sentry
  #define _KCCMDLINEPARSER_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif


///////////////////////////////////////////////////////////////////////////////
//CCmdLineParser description.
//
//See also: <baseclass>
class CCmdLineParser
{
public:
  CCmdLineParser();
  CCmdLineParser(const CCmdLineParser& dtValue);

  virtual ~CCmdLineParser();

public:
public:
  CCmdLineParser& operator=(const CCmdLineParser& dtValue);

public:
  virtual LPTSTR toString(LPTSTR szTarget);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
 */
inline CCmdLineParser& CCmdLineParser::operator=(const CCmdLineParser& dtValue //[in] value to assign
                            )
{

return *this;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KCCMDLINEPARSER_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-03-11 17:05:38  Darko Kolakovic
 * $
 *****************************************************************************/
