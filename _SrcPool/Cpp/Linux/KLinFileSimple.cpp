/*$RCSfile: KLinFileSimple.cpp,v $: implementation file
  $Revision: 1.2 $ $Date: 2014/10/09 18:40:15 $
  $Author: ddarko $

  Basic file-handling API wrapper.
  Copyright: CommonSoft Inc.
  2008-12-12 Darko Kolakovic
 */

#include "KFileSimple.h" //Declarations

#ifdef __linux


///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/*
 */
CFileSimple::CFileSimple(LPCTSTR szFilename) :

{
TRACE()
if ((szFilename != NULL) && (szFilename[0] != T('\0')))
  m_strFile = szFilename;
}

CFileSimple::~CFileSimple()
{
}

//-----------------------------------------------------------------------------
/*
 */
void CFileSimple::Read()
{

}

//-----------------------------------------------------------------------------
/*
 */
void CFileSimple::Write()
{
}
///////////////////////////////////////////////////////////////////////////////
#endif

/******************************************************************************
 *$Log: KLinFileSimple.cpp,v $
 *Revision 1.2  2014/10/09 18:40:15  ddarko
 *Comment
 *
 *Revision 1.1  2009/05/07 21:13:05  ddarko
 *Created
 *
 *****************************************************************************/
