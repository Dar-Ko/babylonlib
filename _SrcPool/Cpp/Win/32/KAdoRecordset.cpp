/*$Workfile: KAdoRecordset.cpp$: implementation file
  $Revision: 5$ $Date: 2004-10-01 21:33:32$
  $Author: Darko$

  Defines the class behaviors for the application.
  Copyright: CommonSoft Inc.
  2k3-08 Darko Kolakovic
 */

#include "stdafx.h"
#include "KAdoRecordset.h" //class CAdoRecordset
#include "KAdoConnection.h" //TESTHR macro
extern void ComErrorShow(_com_error& cee, 
                         LPCTSTR szHelpFile = NULL, 
                         UINT nHelpContext = 0);
#ifdef _DEBUG
  void DumpAdoRecorsetSupport(_RecordsetPtr ptrRecordset);
#endif

//-----------------------------------------------------------------------------
/*Default constructor.

  See also: CAdoConnection
 */
CAdoRecordset::CAdoRecordset(void)
{
m_ptrCommand = NULL;
m_ptrConnection = NULL;
m_ptrRecordset = NULL;
}

//-----------------------------------------------------------------------------
/*Initializes data source without validation and executes SQL command, if any.
 */
CAdoRecordset::CAdoRecordset(_ConnectionPtr ptrConnection, //[in] data provider
                             LPCTSTR sqlCommand //[in]= NULL SQL command to be
                                                //executed
                            ) throw(_com_error)
{
if ((sqlCommand == NULL) || (sqlCommand[0] == _T('\0')))
  SetDataSource(ptrConnection); //ptrConnection is not validated
else
  {
  if(!Open(ptrConnection,sqlCommand))
    _com_issue_error(E_ABORT);
  }
}

//-----------------------------------------------------------------------------
/*
 */
CAdoRecordset::~CAdoRecordset(void)
{
VERIFY(Close());
}

// CAdoRecordset diagnostics

#ifdef _DEBUG
  //-----------------------------------------------------------------------------
  /*
  */
  void CAdoRecordset::Dump(CDumpContext& dc) const
  {
  extern void DumpComVariant(CDumpContext& dc, const _variant_t& comVariant);
  extern LPCTSTR DumpAdoFieldType(const DataTypeEnum& iType);

  dc << _T("CAdoRecordset @ ") << this;
  dc << _T("\n  {\n");
  if (IsConnected())
    {
    try
      {
      unsigned long lCol = GetFieldCount();
      unsigned long lRow = GetRecordCount();
      dc << _T("  Fields: ")  << lCol
         << _T("  Records: ") << lRow
         << _T("\n  ");

      Fields* pFieldArray = m_ptrRecordset->GetFields();
      unsigned long i = 0;
      while(i < lCol)
        {
        _variant_t vtIndex;
        vtIndex.vt = VT_I2;
        vtIndex.iVal = (SHORT)i;

        Field* pField = pFieldArray->GetItem(vtIndex);
        CString strField = (LPTSTR)pField->GetName();
        dc << _T("    ") << i << _T(". ")
          << strField << _T(": ") 
          << DumpAdoFieldType(pField->Type) << _T("\n      Current value: ");
        DumpComVariant(dc, pField->GetValue());
        dc << _T("\n");
        i++;
        }
      }
    catch(_com_error& cee)
      {
      TRACE(_T("  Failed to dump recordset!\n"));
      ComErrorShow(cee);
      }
    }
  else
    dc << _T(".. not connected\n");
  dc << _T("  }");

  }

#endif //_DEBUG

//-----------------------------------------------------------------------------
/*
  Note: To execute a query without using a Command object, pass a query string to
  the Open method of a Recordset object. However, a Command object is required
  when you want to persist the command text and re-execute it, or use query
  parameters.

 */
bool CAdoRecordset::Open(_ConnectionPtr ptrConnection, //[in] data provider
                         LPCTSTR sqlCommand //[in]= NULL SQL command to be executed
                        )
{
TRACE(_T("CAdoRecordset::Open(connection with %s)"), sqlCommand);
if (IsConnected(ptrConnection))
  {
  SetDataSource(ptrConnection);
  try
    {
    m_ptrRecordset.CreateInstance(__uuidof(Recordset));
    m_ptrRecordset->PutRefActiveConnection(m_ptrConnection);
    if (sqlCommand != NULL) //Execute SQL command
      {
      m_ptrRecordset->Open( sqlCommand ,
                            m_ptrConnection.GetInterfacePtr(),
                            adOpenDynamic,
                            adLockOptimistic,
                            adCmdText);
                          //adOpenKeyset,     adLockBatchOptimistic
                          //adOpenForwardOnly, adLockBatchOptimistic
                          //adOpenKeyset,      adLockOptimistic
      #ifdef _DEBUG
        DumpAdoRecorsetSupport(m_ptrRecordset);
        Dump(afxDump);
      #endif
      }
   // if (m_ptrCommand == NULL)
   //   {
   //   //TODO: Init command will be used to execute a Stored Procedure
   //   m_ptrCommand.CreateInstance(__uuidof(Command));
   //   m_ptrCommand->ActiveConnection = m_ptrConnection;
   //   //m_ptrCommand->CommandText = szStoredProcedureName;
   //   m_ptrCommand->CommandType = adCmdStoredProc;
   //   }
    return true;
    }
  catch(_com_error& cee)
    {
    TRACE(_T("  Failed to open recordset!\n"));
    ComErrorShow(cee);
    }
  }

return false;
}
/* TODO: Open table
BOOL CAdoRecordset::Open(_ConnectionPtr mpdb, LPCTSTR lpstrExec, int nOption)
{  
  Close();
  
  if(strcmp(lpstrExec, _T("")) != 0)
    m_strQuery = lpstrExec;

  ASSERT(!m_strQuery.IsEmpty());

  if(m_pConnection == NULL)
    m_pConnection = mpdb;

  m_strQuery.TrimLeft();
  BOOL bIsSelect = m_strQuery.Mid(0, strlen("Select ")).CompareNoCase("select ") == 
    0 && nOption == openUnknown;

  try
  {
    m_pRecordset->CursorType = adOpenStatic;
    m_pRecordset->CursorLocation = adUseClient;
    if(bIsSelect || nOption == openQuery || nOption == openUnknown)
      m_pRecordset->Open((LPCSTR)m_strQuery, _variant_t((IDispatch*)mpdb, TRUE), 
              adOpenStatic, adLockOptimistic, adCmdUnknown);
    else if(nOption == openTable)
      m_pRecordset->Open((LPCSTR)m_strQuery, _variant_t((IDispatch*)mpdb, TRUE), 
              adOpenKeyset, adLockOptimistic, adCmdTable);
    else if(nOption == openStoredProc)
    {
      m_pCmd->ActiveConnection = mpdb;
      m_pCmd->CommandText = _bstr_t(m_strQuery);
      m_pCmd->CommandType = adCmdStoredProc;
      m_pConnection->CursorLocation = adUseClient;
      
      m_pRecordset = m_pCmd->Execute(NULL, NULL, adCmdText);
    }
    else
    {
      TRACE( "Unknown parameter. %d", nOption);
      return FALSE;
    }
  }
  catch(_com_error &e)
  {
    dump_com_error(e);
    return FALSE;
  }

  return m_pRecordset != NULL;
}
*/
//-----------------------------------------------------------------------------
/*Closes the open ADO Recordset connection. If recordset is already closed, 
  function does nothing. In case of COM exception, the error message box shows 
  the error description.

  Returns: true if successful; otherwise returns false.
 */
bool CAdoRecordset::Close()
{
TRACE("CAdoRecordset::Close()\n");

HRESULT hReturn = S_FALSE;
/*
  if(IsOpen())
  {
    if (m_nEditStatus != dbEditNone)
          CancelUpdate();

    m_pRecordset->PutSort(_T(""));
    m_pRecordset->Close();  
  }
*/

//TODO        Close();
    /*
    if(m_pRecordset)
      m_pRecordset.Release();
    if(m_pCmd)
      m_pCmd.Release();
    m_pRecordset = NULL;
    m_pCmd = NULL;
*/

try
  {

  if(IsConnected())
    {
    hReturn = m_ptrRecordset->Close();
    TESTHR(hReturn);
    m_ptrRecordset.Release();
    m_ptrRecordset = NULL;
    }
  if(m_ptrCommand != NULL)
    {
    m_ptrCommand.Release();
    m_ptrCommand = NULL;
    }
  }
catch(_com_error& cee)
  {
  TRACE("  Failed to close Recordset connection!\n");
  ComErrorShow(cee);
  return false;
  }

return true;
}

//-----------------------------------------------------------------------------
/*Executes the specified query, SQL statement, or provider-specific text and
  replaces current recordset with new one.

  Returns: true if succesfull.

  TODO: Execute table name
  TODO: test it! D.K.
 */
bool CAdoRecordset::Open(LPCTSTR szCommand //[in] SQL statement, or provider-specific text
                            //to execute
                         ) throw (_com_error)
{
TRACE(_T("CAdoRecordset::Open(%s)\n"), szCommand);
ASSERT(m_ptrConnection != NULL);

if ((szCommand != NULL) && (szCommand[0] != _T('\0')) && (m_ptrConnection != NULL))
  {
  if(IsConnected())
    {
    TESTHR(m_ptrRecordset->Close());
    m_ptrRecordset.Release();
    m_ptrRecordset = NULL;
    }
  m_ptrConnection->CursorLocation = adUseClient;
  m_ptrRecordset = m_ptrConnection->Execute(_bstr_t(szCommand), NULL, adOptionUnspecified);
  }
return IsConnected();
}

//-----------------------------------------------------------------------------
/*Executes the specified query, SQL statement, or provider-specific text,
  without retreiving any records.

  Returns: number of records that the operation affected

  See also: adExecuteNoRecords

  Example:
    SetDataSource(ptrConnection);
    Execute(_T("UPDATE Names SET Type = 'YourName' WHERE Type = 'SomeName'"));
      //Retrieve the current data by requerying the recordset.
    m_ptrRecordset->Requery(adCmdUnknown);

  TODO: Execute table name
  TODO: test it! D.K.
 */
_variant_t CAdoRecordset::Execute(LPCTSTR szCommand //[in] SQL statement, (TODO: table name,
                            //), a URL, or provider-specific text
                            //to execute
                            ) throw (_com_error)
{
TRACE(_T("CAdoRecordset::Execute(%s)\n"), szCommand);
_variant_t vResult;
vResult = 0;
ASSERT(m_ptrConnection != NULL);

if ((szCommand != NULL) && (szCommand[0] != _T('\0')) && (m_ptrConnection != NULL))
  {
  m_ptrConnection->CursorLocation = adUseClient;
  /*adExecuteNoRecords = 0x80 
    Indicates that the command text is a command or stored procedure that does 
    not return rows (for example, a command that only inserts data).
    If any rows are retrieved, they are discarded and not returned. 
   */
  m_ptrConnection->Execute(_bstr_t(szCommand), &vResult, adExecuteNoRecords);
  }
return vResult;
}

//-----------------------------------------------------------------------------
/*Executes a Stored Procedure using the CommandPtr Object.

  Returns: true if successful, otherwise returns false.

  TODO: test it! D.K.
 */
bool CAdoRecordset::Execute() throw (_com_error)
{
if (m_ptrCommand != NULL)
  {
  if(IsConnected())
    {
    TESTHR(m_ptrRecordset->Close());
    m_ptrRecordset.Release();
    m_ptrRecordset = NULL;
    }
  m_ptrRecordset = m_ptrCommand->Execute( NULL, NULL, adCmdStoredProc );
    //Retrieve the current data by requerying the recordset.
  m_ptrRecordset->Requery(adCmdUnknown);
  return true;
  }
return false;
}

//-----------------------------------------------------------------------------
/*Removes Connection from a populated recordset. This recordset can be
  manipulated and again connected to the data source for updating.

  Note: Remote Data Services (RDS) uses this feature to send recordsets through
  either HTTP or Distributed Component Object Model (DCOM) protocols to a remote
  computer, however, you are not limited to using Remote Data Service (RDS)
  to generate a disconnected recordset.

  Example:
        try
          {
          CAdoRecordset adoRecorset;
          _ConnectionPtr ptrConn(__uuidof(Connection));
          //Connect and get recordset
          ptrConn->Open((LPCTSTR)strConnection, //ConnectionString
                        _T(""), //UserID
                        _T(""), //Password
                        adConnectUnspecified
                        );
          adoRecorset.Open(ptrConn, _T("SELECT * FROM Table1"));
          adoRecorset.Disconnect();
          //Obtain direct access to recordset pointer
          _RecordsetPtr ptrRec = (_RecordsetPtr)adoRecorset;
          ptrRec->Fields->Item[0L]->Value = _T("NewValue"); //Change the value.
          ptrRec->PutRefActiveConnection(ptrConn); //Re-connect.
          ptrRec->UpdateBatch(adAffectAll); //Send updates.
          //Note:adoRecorset destructor closes the recordset
          ptrConn->Close(); //Close connection
          }
        catch( _com_error cee)
          {
            //Do Exception handling.
          }

 */
bool CAdoRecordset::Disconnect()
{
TRACE("CAdoRecordset::Disconnect()\n");
try
  {
  if(IsConnected())
    {
      //Disassociate the connection from the recordset.
    m_ptrRecordset->PutRefActiveConnection(NULL);
    /*Note: m_ptrRecordset->PutRefActiveConnection(NULL); replaces following
      code:
          {
          var.vt = VT_UNKNOWN;
          var.punkVal = NULL;
          m_ptrRecordset->PutActiveConnection(var);
          }
      or
          {
          var.vt = VT_DISPATCH;
          var.pdispVal = NULL;
          m_ptrRecordset->PutActiveConnection(var);
          }
      */

    }
  return true;
  }
catch( _com_error cee)
  {
  TRACE("  Failed to disconnect Recordset!\n");
  ComErrorShow(cee);
  }
return false;
}

//-----------------------------------------------------------------------------
/*Retreives number of records in a recordset.
  
  Returns: current number of records in a recordset.
 */
unsigned long CAdoRecordset::GetRecordCount() const
{
long lRows = m_ptrRecordset->GetRecordCount();

//If the number of records contained in a Recordset object cannot be determined,
//the GetRecordCount property returns -1 (adUnknown). 
if(lRows == adUnknown)
  {
  lRows = 0;
    //Count records one-by-one
  if(!IsEOF())
    m_ptrRecordset->MoveFirst();

  while(!IsEOF())
    {
    lRows++;
    m_ptrRecordset->MoveNext();
    }

  if(lRows > 0)
    m_ptrRecordset->MoveFirst();
  }
return lRows;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2004-10-01 21:33:32  Darko           stdafx.h
 *  4    Biblioteka1.3         2003-08-19 15:17:13  Darko           Execute(),
 *       Open()
 *  3    Biblioteka1.2         2003-08-17 01:16:25  Darko           Moved Field
 *       functions out
 *  2    Biblioteka1.1         2003-08-14 13:17:23  Darko           GetField
 *       methods
 *  1    Biblioteka1.0         2003-08-12 12:56:49  Darko           
 * $
 *****************************************************************************/
