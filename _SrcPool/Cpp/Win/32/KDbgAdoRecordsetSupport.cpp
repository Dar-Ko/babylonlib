/*$Workfile: KDbgAdoRecordsetSupport.cpp$: implementation file
  $Revision: 6$ $Date: 2004-10-01 21:34:02$
  $Author: Darko$

  Dumps Recordset functionality
  Copyright: CommonSoft Inc.
  2003-08 Darko Kolakovic
 */ 

// Group=Diagnostic
#include "stdafx.h"

  //afxDump is not defined in release version
#ifdef _DEBUG

/*KB259379 HOWTO: Develop with ADO Version 2.5 or Later and Install on 
  ADO Version 2.0
  Errors are caused by new ActiveX Data Objects (ADO) interfaces that are
  referenced in the ADO 2.5 or later-produced image and that are not found 
  in the Msado15.dll file on the target system. 
 */
#if defined(ADO2_OLD)
  #pragma message( "Using ADO2 TLB <msado20.tlb>" ) 
  #import <msado20.tlb> no_namespace rename("EOF", "adoEOF") 
#else
  #pragma message( "Using ADO 2.7 <msado15.dll>" )
  //Note: Add "C:\Program Files\Common Files\System\ADO" path to 
  //VisualStudio|Tools|Options|Projects|VC++ Directories|Executable files
  #import <msado15.dll> no_namespace rename("EOF", "adoEOF") 
#endif

//-----------------------------------------------------------------------------
/*Dump type of functionality a Recordset object supports.

    Constant          Value     Description 
    adAddNew          0x1000400 AddNew method to add new records. 
    adApproxPosition  0x4000    AbsolutePosition and AbsolutePage properties. 
    adBookmark        0x2000    Bookmark property to gain access to specific
                                records. 
    adDelete          0x1000800 Delete method to delete records. 
    adFind            0x80000   Find method to locate a row in a Recordset. 
    adHoldRecords     0x100     Retrieves more records or changes the next 
                                position without committing all pending changes. 
    adIndex           0x100000  Index property to name an index. 
    adMovePrevious    0x200     MoveFirst and MovePrevious methods, and Move
                                or GetRows methods to move the current record
                                position backward without requiring bookmarks. 
    adNotify          0x40000   Indicates that the underlying data provider
                                supports notifications (which determines
                                whether Recordset events are supported). 
    adResync          0x20000   Resync method to update the cursor with
                                the data that is visible in the underlying
                                database. 
    adSeek            0x200000  Seek method to locate a row in a Recordset. 
    adUpdate          0x1008000 Update method to modify existing data. 
    adUpdateBatch     0x10000   batch updating (UpdateBatch and CancelBatch
                                methods) to transmit groups of changes to
                                the provider.

  Note: uses Microsoft Fundation Library (MFC);
        Microsoft ActiveX Data Objects (ADO).
        Microsoft Windows specific (Win).
 */
void DumpAdoRecorsetSupport(_RecordsetPtr ptrRecordset //[in] Recordset object
                        )
{
if(ptrRecordset)
  {
  afxDump << _T("_RecordsetPtr supports following functionality:\n");
  if (ptrRecordset->Supports(adAddNew))
    afxDump << _T("\tadAddNew\n");
  if (ptrRecordset->Supports(adApproxPosition))
    afxDump << _T("\tadApproxPosition\n");
  if (ptrRecordset->Supports(adBookmark))
    afxDump << _T("\tadBookmark\n");
  if (ptrRecordset->Supports(adDelete))
    afxDump << _T("\tadDelete\n");
  if (ptrRecordset->Supports(adFind))
    afxDump << _T("\tadFind\n");
  if (ptrRecordset->Supports(adHoldRecords))
    afxDump << _T("\tadHoldRecords\n");
  if (ptrRecordset->Supports(adIndex))
    afxDump << _T("\tadIndex\n");
  if (ptrRecordset->Supports(adMovePrevious))
    afxDump << _T("\tadMovePrevious\n");
  if (ptrRecordset->Supports(adNotify))
    afxDump << _T("\tadNotify\n");
  if (ptrRecordset->Supports(adResync))
    afxDump << _T("\tadResync\n");
  if (ptrRecordset->Supports(adSeek))
    afxDump << _T("\tadSeek\n");
  if (ptrRecordset->Supports(adUpdate))
    afxDump << _T("\tadUpdate\n");
  if (ptrRecordset->Supports(adUpdateBatch))
    afxDump << _T("\tadUpdateBatch\n");
  }
}
///////////////////////////////////////////////////////////////////////////////
#endif  //_DEBUG

/*****************************************************************************
 * $Log: 
 *  6    Biblioteka1.5         2004-10-01 21:34:02  Darko           stdafx.h
 *  5    Biblioteka1.4         2003-08-21 14:26:43  Darko           afxDump is not
 *       defined in release version
 *  4    Biblioteka1.3         2003-08-13 16:35:54  Darko           import Ado15
 *  3    Biblioteka1.2         2003-08-13 16:35:12  Darko           
 *  2    Biblioteka1.1         2003-08-13 13:39:34  Darko           formatting
 *  1    Biblioteka1.0         2003-08-12 12:56:55  Darko           
 * $
 *****************************************************************************/
