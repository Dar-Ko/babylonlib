/*$Workfile: KCmdLineParser.h$: header file
  $Revision: 2$ $Date: 2005-03-14 00:09:19$
  $Author: Darko$

  Command line parser
  Copyright: CommonSoft Inc
  2004-09-14 Darko Kolakovic
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KCCMDLINEPARSER_H_
    //$Workfile: KCmdLineParser.h$ sentry
  #define _KCCMDLINEPARSER_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
/*Type of an option argument of command switch or flag. The option type is used
  to validate given option argument.
 */
typedef enum tagCmdLineOptionArgType
{
  CMDLINE_NONE,      //command option does ot require an argument
  CMDLINE_STRING,    //option argument is a string
  CMDLINE_INT,       //option argument is an integer
  CMDLINE_UINT,      //option argument is an unsigned integer
  CMDLINE_DATE,      //option argument is a date
} CMDLINEARGTYPE;

#define CMDLINE_ARG_OPT   0x00 //Command option arguments are not mandatory
#define CMDLINE_ARG_ONE   0x01 //Command option has at least one argument
#define CMDLINE_ARG_MULTI 0x02 //Command option has more than one arguments
#define CMDLINE_ARG_X0R   0x08 //Command option arguments are mutually exclusive


///////////////////////////////////////////////////////////////////////////////
//Description of the command line option
union CmdLineDescription     
  {
  char* m_szDescription;       //description of the option or NULL
  unsigned int m_nDescriptionId;//string resource ID of option's description or 0 
  };

///////////////////////////////////////////////////////////////////////////////
/*Data structure used to describe an option in the command passed through
  application's main entry point.

  See also: main(), argv, argc
 */
typedef struct tagCmdLineOption
{
TCHAR m_cOption; //single alphanumeric character from the portable character set
CMDLINEARGTYPE m_typeArg;       //option argument type
unsigned int   m_nArg;
CmdLineDescription m_cmdDesc;   //description of the command line option
} CMDLINEOPTION, *PCMDLINEOPTION;

///////////////////////////////////////////////////////////////////////////////
/*CCmdLineParser is a class for parsing command arguments passed to 
  an application through the main entry point. The class expect that command 
  arguments are in format described throughout IEEE Std 1003.1-2001
  recommendations for the arguments processed by the utilities.

      utility_name[-a][-b][-c option_argument]
             [-d|-e] [operand...]

  "Options" or "switches" arguments that consist of hyphens and single 
  letters or digits. Certain options are followed by an "option-argument", as
  shown with [-c option_argument]. Option-arguments are separated from their
  options by a whitespaces.The arguments following the last options and
  option-arguments are named "operands". Following rules are implemented:
    - Each option should be a single alphanumeric character from the portable
      character set. Multi-digit options should not be allowed.
    - All options are preceded by the '-' delimiter character.
    - Options without option-arguments could be grouped behind one '-' delimiter.
    - Each option-argument have to be a separate argument.
    - The order of different options relative to one another should not matter,
      unless the options are documented as mutually-exclusive and such an option
      is documented to override any incompatible options preceding it.

  See also: main(), _tmain(), tagCmdLineOption
  */
class CCmdLineParser
{
public:
  CCmdLineParser();
  CCmdLineParser(int argc, TCHAR* argv[]);
  CCmdLineParser(const CCmdLineParser& cmdLine);

  virtual ~CCmdLineParser();

protected:
  PCMDLINEOPTION m_pcmdOptions; //list of the supported command options
  unsigned int m_nOptionsCount; //number of the supported command options in the list

public:
  void SetOptions(const PCMDLINEOPTION pcmdOptions,
                  const unsigned int nCount);

public:
  //virtual LPTSTR toString(LPTSTR szTarget);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
 * /
inline CCmdLineParser& CCmdLineParser::operator=(const CCmdLineParser& dtValue //[in] value to assign
                            )
{
...
return *this;
}*/

///////////////////////////////////////////////////////////////////////////////
#endif  //_KCCMDLINEPARSER_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-03-11 17:05:38  Darko Kolakovic
 * $
 *****************************************************************************/
