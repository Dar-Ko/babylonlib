/*$Workfile: KAdoField.cpp$: implementation file
  $Revision: 6$ $Date: 2004-10-01 22:33:30$
  $Author: Darko$

  Defines the class behaviors for the application.
  Copyright: CommonSoft Inc.
  2k3-08 Darko Kolakovic
 */

#include "stdafx.h"
#include "KAdoField.h"  //CAdoField class
#pragma warning(disable: 4290)

//-----------------------------------------------------------------------------
/*Default constructor.
 */
CAdoField::CAdoField(Field* pField //[in] column of data with a common
                                   //data type
                     ) :
    m_pField(pField),
    m_lSize(adUnknown)
{
ASSERT(pField != NULL);
}

CAdoField::CAdoField(_RecordsetPtr ptrRecordset,  //[in] current data record set
                     const int16_t sIndex //[in] zero-based index of the field
                     ) throw(_com_error)
{
ASSERT(ptrRecordset != NULL);
ASSERT(sIndex >= 0);

Fields* pFields = ptrRecordset->GetFields();
ASSERT (sIndex < pFields->Count);
if ((sIndex >= 0) && (sIndex < pFields->Count))
  {
  _variant_t vtIndex;
  vtIndex.vt = VT_I2;
  vtIndex.iVal = (SHORT)sIndex;

  m_pField = pFields->GetItem(vtIndex);
  m_lSize = GetCount(ptrRecordset);
  }
else
  {
  m_pField = NULL;
  m_lSize = adUnknown;
  _com_issue_error(E_INVALIDARG);
  }
}

CAdoField::CAdoField(_RecordsetPtr ptrRecordset,  //[in] current data record set
                     LPCTSTR szFieldName //[in] field name
                     ) throw(_com_error)
{
ASSERT(ptrRecordset != NULL);
ASSERT(szFieldName != NULL);
if((szFieldName != NULL) && (szFieldName[0] != _T('\0')))
  {
  m_pField = ptrRecordset->Fields->GetItem(szFieldName);
  m_lSize = GetCount(ptrRecordset);
  }
else
  {
  m_pField = NULL;
  m_lSize = adUnknown;
  _com_issue_error(E_INVALIDARG);
  }
}

//-----------------------------------------------------------------------------
/*
 */
CAdoField::~CAdoField(void)
{
}

#ifdef _DEBUG
  //-----------------------------------------------------------------------------
  /*Dumps the contents of CAdoField object to a CDumpContext object if
    _DEBUG macro is defined.
   */
  void CAdoField::Dump(CDumpContext& dc //[in] dump context
                        ) const
  {
  extern void DumpComVariant(CDumpContext& dc, const _variant_t& comVariant);
  extern LPCTSTR DumpAdoFieldType(const DataTypeEnum& iType);

  dc << _T("CAdoField @ ") << this;
  dc << _T("\n  {\n");
      CString strField = GetName();
      dc << _T("  ")
        << strField << _T(": ")
        << DumpAdoFieldType(GetType())
        << _T("\n    Count: ") << m_lSize
        << _T("\n    Current value: ");
      DumpComVariant(dc, GetValue());
  dc << _T("  }\n");

  }
#endif //_DEBUG

//-----------------------------------------------------------------------------
/*Retreives number of records in a field.

  Returns: current number of records in a field or adUnknown.
 */
long CAdoField::GetCount() const
{
return m_lSize;
}

//-----------------------------------------------------------------------------
/*Retreives number of records in a recordset.

  Returns: current number of records in a recordset or adUnknown.
 */
long CAdoField::GetCount(_RecordsetPtr ptrRecordset  //[in] current data
                                                              //record set
                                  )
{
if (ptrRecordset == NULL)
  return adUnknown;

long lRows = ptrRecordset->GetRecordCount();

//If the number of records contained in a Recordset object cannot be determined,
//the GetRecordCount property returns -1 (adUnknown).
if(lRows == adUnknown)
  {
  lRows = 0;
    //Count records one-by-one
  if(ptrRecordset->adoEOF != VARIANT_TRUE)
    ptrRecordset->MoveFirst();

  while(ptrRecordset->adoEOF != VARIANT_TRUE)
    {
    lRows++;
    ptrRecordset->MoveNext();
    }

  if(lRows > 0)
    ptrRecordset->MoveFirst();
  }
return lRows;
}

///////////////////////////////////////////////////////////////////////////////
#pragma warning(default: 4290)
/*
Data Type                      SQL Data Type           Length           ODBC Data Type           Description
Access Currency                Currency       -1           SQL_DECIMAL
BLOB                           Long Varbinary -1           SQL_LONGVARBINARY
CLOB                           Long VarChar   -1           SQL_LONGVARCHAR
Comment Prefix                 VarChar        -1           SQL_VARCHAR
DB2 Eur Date (dd.mm.yyyy)      Date           10           SQL_DATE
DB2 Eur Time (hh.mm.ss.)       Time            8           SQL_TIME
DB2 IEEE 4-byte float          Real            4           SQL_REAL           4-byte byte-reversed (little endian) IEEE float
DB2 IEEE 8-byte float          Double          8           SQL_DOUBLE           8-byte byte-reversed (little endian) IEEE float
DB2 IEEE Big E 4-byte float    Real            4           SQL_REAL           4-byte big endian IEEE float
DB2 IEEE Big E 8-byte float    Double          8           SQL_DOUBLE           8-byte big endian IEEE float
DB2 ISO Date (YYYY-MM-DD)      Date           10           SQL_DATE           ISO DATE column
DB2 ISO Time (hh.mm.ss)        Time            8           SQL_TIME           ISO TIME column
DB2 JIS Date (YYYY-MM-DD)      Date           10           SQL_DATE
DB2 JIS Time (hh:mm:ss)        Time            8           SQL_TIME
DB2 Longword Big Endian        Integer         4           SQL_INTEGER
DB2 Longword Integer           Integer         4           SQL_INTEGER           4-byte signed long integer (-2147483648 thru +2147483647)
DB2 Mainframe 4-byte float     Real            4           SQL_REAL           Mainframe DB2 (MVS or OS/390) 4-byte float
DB2 Mainframe 8-byte float     Double          8           SQL_DOUBLE           Mainframe DB2 (MVS or OS/390) 8-byte float
DB2 Numeric                    Numeric      1-31           SQL_NUMERIC           Zoned numeric columns defined as NUMERIC (precision, scale), where precision >= scale; 0 <= precision <=31; 0 <= scale <=31
DB2 Numeric Integer            Numeric         9           SQL_DECIMAL           Describes an SQL NUMERIC display column with a scale = 0 and precision < = 9, e.g., NUMERIC (9,0). The default conversion from host column to ODBC data type is from SQL_NUMERIC to signed long integer = SQL_C_SLONG.
DB2 Packed Decimal             Decimal      1-16           SQL_DECIMAL           Packed decimal columns defined as DECIMAL (precision, scale), where precision >= scale; 0 <= precision <=31; 0 <= scale <=31
DB2 Packed Decimal Integer     Decimal         9           SQL_DECIMAL           This data type corresponds to an SQL_DECIMAL column with a scale of 0 and a precision < = 9, e.g., DECIMAL(9,0). The default conversion from host column to ODBC data type is from SQL_DECIMAL to signed long integer = SQL_C_SLONG.
DB2 Small Integer              Smallint        2           SQL_SMALLINT           2-byte signed small integer (-32768 thru +32767)
DB2 Timestamp                  Timestamp      26           SQL_TIMESTAMP           ISO Timestamp column (YYYY-MM-DD -HH.MM.SS.123456)
DB2 Text (Null Terminated)     Varchar 255-32767           SQL_VARCHAR           255+ byte variable-length binary (defined as VARCHAR/LONG VARCHAR)
DB2 Text (Right Space Padded)  Char        1-254           SQL_CHAR           1- to 254-byte fixed-length character
DB2 USA Date (mm/dd/yyyy)      Date           10           SQL_DATE
DB2 USA Time (hh:mm xM)        Time            8           SQL_TIME
DB2 Varbinary                  Varbinary 255-32767           SQL_VARBINARY           255+ byte variable-length binary (defined as VARCHAR/LONG VARCHAR FOR BIT DATA)
DB2 Word Big Endian            SmallInt        2           SQL_SMALLINT
Double Prec float (Mainframe)  Double          8           SQL_DOUBLE
Longword 4 bytes               Integer         4           SQL_INTEGER
Longword (BE) -> Double        Double          4           SQL_DOUBLE
Longword (BE) -> Decimal       Decimal         4           SQL_DECIMAL
Single Prec float (Mainframe)  Real            4           SQL_REAL
Text -> Currency               Currency       -1           SQL_DECIMAL
Text (Nullable) -> Integer     Integer        -1           SQL_INTEGER
Text (Nullable) -> Double      Double         -1           SQL_DOUBLE
Text (Right Space Padded)      Char           -1           SQL_CHAR
Text Date (DDMMYY)             Date            6           SQL_DATE
Text Date (DDMMYYYY)           Date            8           SQL_DATE
Text Date (MMDDYY)             Date            6           SQL_DATE
Text Date (MMDDYYYY)           Date            8           SQL_DATE
Text Date (YYMMDD)             Date            6           SQL_DATE
Text Date (YYYYMMDD)           Date            8           SQL_DATE
Text Date 2000(DDMMYY)         Date            6           SQL_DATE
Text Date 2000(MMDDYY)         Date            6           SQL_DATE
Text Date 2000(YYMMDD)         Date            6           SQL_DATE
Text DB2 (Right Space Padded)  Char           -1           SQL_CHAR
Text DB2 (Null Terminated)     VarChar        -1           SQL_VARCHAR
Unsigned Long (BE) -> Decimal  Decimal         2           SQL_DECIMAL
Unsigned Word (BE) -> Decimal  Decimal         2           SQL_DECIMAL
Unsigned Long (BE) -> Double   Double          4           SQL_DOUBLE
Unsigned Word (BE) -> Double   Double          2           SQL_DOUBLE
Word 2 bytes                   SmallInt        2           SQL_SMALLINT
Word (BE) -> Decimal           Decimal         2           SQL_DECIMAL
Word (BE) -> Double            Double          2           SQL_DOUBLE

    MySQL
    Type        Format              Range
    DATE        YYYY-MM-DD          [1000-01-01, 9999-12-31] assign values to DATE columns using either strings or numbers.
    DATETIME    YYYY-MM-DD HH:MM:SS [1000-01-01 00:00:00 to 9999-12-31 23:59:59]
    TIME        HH:MM:SS            [-838:59:59 to 838:59:59]
    TIMESTAMP   YYYYMMDDHHMMSS      [1970-01-01 00:00:00, 2037]
    TIMESTAMP12 YYMMDDHHMMSS        [1970-01-01 00:00:00, 2037]
    TIMESTAMP8  YYYYMMDD            [1970-01-01, 2037]
    TIMESTAMP6  YYMMDD              [1970-01-01, 2037]
    YEAR4       YYYY                [1901 to 2155], 0000
    YEAR2       YY                  [1970-2069]

    SyBase
    datetime                        [1753-01-01,9999-12-31]
    smalldatetime                   [1900-01-01,2079-06-06]
 */
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         2003-09-11 16:57:36  Darko           Updated Dump()
 *  3    Biblioteka1.2         2003-09-10 16:10:55  Darko           comment, Dump
 *       format
 *  2    Biblioteka1.1         2003-08-19 16:17:46  Darko           GetCount()
 *  1    Biblioteka1.0         2003-08-17 02:16:39  Darko
 * $
 *****************************************************************************/