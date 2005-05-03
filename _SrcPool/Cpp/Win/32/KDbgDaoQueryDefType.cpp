/*$Workfile: KDbgDaoQueryDefType.cpp$: implementation file
  $Revision: 3$ $Date: 2005-04-26 11:28:57$
  $Author: Darko Kolakovic$

  Dumps data access objects (DAO) properties
  Copyright: CommonSoft Inc.
  2001-04 Darko Kolakovic
 */ 

// Group=Diagnostic
#include "stdafx.h"
#ifndef __AFXDAO_H
  #include <afxdao.h>
#endif

//-----------------------------------------------------------------------------
/*Dump information about a querydef object defined for data access objects (DAO).
  The value can be one of the following:

      dbQSelect         query selects records. 
      dbQAction         query moves or changes data but does not return records. 
      dbQCrosstab       query returns data in a spreadsheet-like format. 
      dbQDelete         query deletes a set of specified rows. 
      dbQUpdate         query changes a set of records. 
      dbQAppend         query adds new records to the end of a table or query. 
      dbQMakeTable      query creates a new table from a recordset. 
      dbQDDL            query affects the structure of tables or their parts. 
      dbQSQLPassThrough SQL statement is passed directly to the database backend, without intermediate processing. 
      dbQSetOperation   query creates a snapshot-type recordset object containing data from all specified records in two or more tables with any duplicate records removed. To include the duplicates, add the keyword ALL in the querydef's SQL statement. 
      dbQSPTBulk        Used with dbQSQLPassThrough to specify a query that does not return records. 

  See also: CDaoQueryDefInfo structure

  Note: uses Microsoft Foundation Library (MFC);
        Microsoft Windows specific (Win).
 */
LPCTSTR DumpDaoQueryDefType(short sType //[in] operational type of a querydef object.
                            )
{
switch(sType)
  {
  case (dbQSelect):          return _T("dbQSelect");
  case (dbQAction):          return _T("dbQAction");
  case (dbQCrosstab):        return _T("dbQCrosstab");
  case (dbQDelete):          return _T("dbQDelete");
  case (dbQUpdate):          return _T("dbQUpdate");
  case (dbQAppend):          return _T("dbQAppend");
  case (dbQMakeTable):       return _T("dbQMakeTable");
  case (dbQDDL):             return _T("dbQDDL");
  case (dbQSQLPassThrough):  return _T("dbQSQLPassThrough");
  case (dbQSetOperation):    return _T("dbQSetOperation");
  case (dbQSPTBulk):         return _T("dbQSPTBulk");
  }
return _T("<unknown>");
}

/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2005-04-26 11:28:57  Darko Kolakovic Document groups
 *       and typo fixes
 *  2    Biblioteka1.1         2004-10-01 22:34:10  Darko           stdafx.h
 *  1    Biblioteka1.0         2003-08-13 17:36:32  Darko           
 * $
 *****************************************************************************/
