/*$Workfile: KAdoRecordset.h$: header file
  $Revision: 5$ $Date: 2004-10-01 21:33:36$
  $Author: Darko$

  Interface of the CAdoRecordset class 
  Copyright: CommonSoft Inc.
  2k3-08 Darko Kolakovic
 */

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

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

#ifndef adUnknown
  //ADO type (TODO: where is MS enum for ADO types? D.K.)
  #define adUnknown -1
#endif

//warning C4290: C++ exception specification ignored except to indicate 
//a function is not __declspec(nothrow)
#pragma warning(disable: 4290)

///////////////////////////////////////////////////////////////////////////////
//Class CAdoRecordset object represents a set of records selected from a data 
//source. You use Recordset objects to manipulate data from a data provider.
//The underlying database objects organize data in a row/column table format.
//The recordset is created using ActiveX Data Objects (ADO).
//Recordset object represents the entire set of records from a base table or 
//the results of an executed command. At any time, the Recordset object refers
//to only a single record within the set as the current record.
//Every Recordset has a Fields collection consisting of one or more Field 
//objects. A Field object usually represents a table column.
//
//      Recordset [n,m]
//       Fields  FIELD0 FIELD1 ... FIELDn 
//      .       +------+------+   +------+
//      RECORD0 |val 00|val 01|   |val 0n|
//      RECORD1 |val 10|val 11|   |val 1n|
//        ...                         
//      RECORDm |val m0|val m1|   |val mn|
//      .       +------+------+   +------+
//
//See also: ms-help://MS.MSDNQTR.2003JUL.1033/ado270/htm/mdaobj01_20.htm
//
//Note: uses Microsoft Fundation Library (MFC);
//      Microsoft ActiveX Data Objects (ADO).
//      Microsoft Windows specific (Win).
class CAdoRecordset
{
public:
  CAdoRecordset(void);
  CAdoRecordset(_ConnectionPtr ptrConnection, LPCTSTR sqlCommand = NULL) 
     throw(_com_error);
  virtual ~CAdoRecordset(void);

public:
  _RecordsetPtr   m_ptrRecordset; //current data record set
protected:
  _CommandPtr     m_ptrCommand;   //command to be executed against a data source
  _ConnectionPtr  m_ptrConnection;//data provider

public:
  virtual bool Open(_ConnectionPtr ptrConnection, LPCTSTR sqlCommand = NULL);
  virtual bool Open(LPCTSTR sqlCommand) throw (_com_error);
  virtual bool Close();
  void SetDataSource(_ConnectionPtr ptrConnection);
  #ifdef _DEBUG
    virtual void Dump(CDumpContext& dc) const;
  #endif
  bool IsConnected() const;
  _variant_t Execute(LPCTSTR szCommand) throw (_com_error);
  bool Execute() throw (_com_error);
  bool Disconnect();
  unsigned long GetFieldCount() const;
  unsigned long GetRecordCount() const;
  operator _RecordsetPtr() const;

  bool IsEOF() const;
  bool IsBOF() const;
  _variant_t GetValue(const SHORT sFieldIndex) const;

protected:
  bool IsConnected(_ConnectionPtr ptrConnection);

};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Validates recordset Open status.

  Returns: true if Recordset Object is connected to the data source; otherwise 
  returns false.
 */
inline bool CAdoRecordset::IsConnected() const
{
return ((m_ptrRecordset != NULL) && 
        (m_ptrRecordset->GetState() == adStateOpen));
}

//-----------------------------------------------------------------------------
/*Validates connection status.

  Returns: true if Connection Object is connected to the data source; otherwise 
  returns false.
 */
inline bool CAdoRecordset::IsConnected(_ConnectionPtr ptrConnection //[in] active connection 
                                                     //to data source
                        )
{
return ((ptrConnection != NULL) && 
        (ptrConnection->GetState() == adStateOpen));
}

//-----------------------------------------------------------------------------
/*Cast operator.
 */
inline CAdoRecordset::operator _RecordsetPtr() const
{
return m_ptrRecordset;
}

//-----------------------------------------------------------------------------
/*
 */
inline unsigned long CAdoRecordset::GetFieldCount() const
{
return m_ptrRecordset->GetFields()->Count;
}

//-----------------------------------------------------------------------------
/*
  If both BOF and EOF are True, the Recordset object is empty.

  Returns: true if dataset pointer is at the end of the recordset.
 */
inline bool CAdoRecordset::IsEOF() const
{
//Note: see stdafx.h: #import <msado15.dll> no_namespace rename("EOF", "adoEOF") 
ASSERT(m_ptrRecordset != NULL);
return (m_ptrRecordset->adoEOF == VARIANT_TRUE);
};

//-----------------------------------------------------------------------------
/*
  If both BOF and EOF are true, the Recordset object is empty.

  Returns: true if dataset pointer is at the begining of the recordset.
 */
inline bool CAdoRecordset::IsBOF() const
{
ASSERT(m_ptrRecordset != NULL);
return (m_ptrRecordset->BOF == VARIANT_TRUE);
};

//-----------------------------------------------------------------------------
/*Initializes pointer to data source without validating connection. If 
  ptrConnection is NULL, data source would be invalidated.
 */
inline void CAdoRecordset::SetDataSource(_ConnectionPtr ptrConnection//[in] data 
                                  //provider or NULL
                                  )
{
if(m_ptrConnection != NULL)
  m_ptrConnection->Release();

m_ptrConnection = ptrConnection;
}

///////////////////////////////////////////////////////////////////////////////
#pragma warning(default: 4290)
/*****************************************************************************
 * $Log: 
 *  5    Biblioteka1.4         2004-10-01 21:33:36  Darko           stdafx.h
 *  4    Biblioteka1.3         2003-08-19 15:17:15  Darko           Execute(),
 *       Open()
 *  3    Biblioteka1.2         2003-08-17 01:16:27  Darko           Moved Field
 *       functions out
 *  2    Biblioteka1.1         2003-08-14 13:17:25  Darko           GetField
 *       methods
 *  1    Biblioteka1.0         2003-08-12 12:56:51  Darko           
 * $
 *****************************************************************************/
