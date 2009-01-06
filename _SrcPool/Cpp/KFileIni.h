/*$RCSfile: KFileIni.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/01/06 22:28:06 $
  $Author: ddarko $

  Configuration file hanlder for storing application's setting
  Copyright: CommonSoft Inc.
  1990 Darko Kolakovic
 */

#ifndef _KFILEINI_H_
    //$RCSfile: KFileIni.h,v $ sentry
  #define _KFILEINI_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
/*This class is used to stores and retreive configuration parameters in INI 
  format,  usualy used during application's initialization. 
  The INI file format is a de facto standard for configuration files.
  INI format have three basic elements: section, parameter and comment.

    [sectionname]
    parametername = value
    ;comment
  Sections are used to group parameters. Section name is enclosed with square 
  brackets ([ and ]). Sections end at the next section declaration or the end 
  of the file.
  Parametars are given as name and value pair. 
  Comments are all lines that are not section names or parameters and will be
  ignored
  Comments usually begin with semicolon (;) or number sign (#) and continue 
  to the end of the line.
 */
class CFileIni
{
public:
  CFileIni(LPCTSTR szFilename);
  virtual ~CFileIni();

  void Read();
  void Save(CString strWrite);
  void LoadDefault();

private:
  CString m_strFile;
};

///////////////////////////////////////////////////////////////////////////////
#endif //_KFILEINI_H_
/*****************************************************************************
 * $Log: KFileIni.h,v $
 * Revision 1.1  2009/01/06 22:28:06  ddarko
 * moved from archive
 *
 * 1990 Darko Kolakovic Win95 store application's setting
 *****************************************************************************/
