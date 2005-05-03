/*$Workfile: KAdoField.h$: header file
  $Revision: 5$ $Date: 2005-04-29 01:12:59$
  $Author: Darko$

  Interface of the CAdoField class
  Copyright: CommonSoft Inc.
  2k3-08 Darko Kolakovic
 */
// Group=Windows

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

#include "KType32.h"  //ISO C99: 7.18 Integer types

#ifndef adUnknown
  //ADO type (TODO: where is MS enum for ADO types? D.K.)
  #define adUnknown -1
#endif

//warning C4290: C++ exception specification ignored except to indicate
//a function is not __declspec(nothrow)
#pragma warning(disable: 4290)

///////////////////////////////////////////////////////////////////////////////
//Class CAdoField object represents a set of data with a common data type.
//Each Field object corresponds to a column in the Recordset. You use the Value
//property of Field objects to set or return data for the current record.
//Depending on the functionality the provider exposes, some collections,
//methods, or properties of a Field object may not be available.
//
//Note: Microsoft Windows specific (Win).
class CAdoField
{
public:
  CAdoField(Field* pField);
  CAdoField(_RecordsetPtr ptrRecordset, LPCTSTR szFieldName ) throw(_com_error);
  CAdoField(_RecordsetPtr ptrRecordset, const int16_t sIndex) throw(_com_error);
  virtual ~CAdoField();

private:
  //Default constructor is not accesible
  CAdoField(){};

protected:
  Field* m_pField; //a column of data with a common data type.
  long m_lSize;    //number of records in the field or adUnknown

public:
  #ifdef _DEBUG
    virtual void Dump(CDumpContext& dc) const;
  #endif
  DataTypeEnum  GetType () const;
  CString       GetName () const;
  _variant_t    GetValue() const;
  long GetCount() const;
  bool IsNull()  const;
  bool IsEmpty() const;

protected:
  long GetCount(_RecordsetPtr ptrRecordset);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
  Returns: type of the field.
 */
inline DataTypeEnum CAdoField::GetType() const
{
return m_pField->Type;
}

//-----------------------------------------------------------------------------
/*
  Returns: name of the field or empty string if filed index is out of range.
 */
inline CString CAdoField::GetName() const
{
CString strResult = (LPTSTR)m_pField->GetName();
return strResult;
}

//-----------------------------------------------------------------------------
/*
 */
inline _variant_t CAdoField::GetValue() const
{
_variant_t varResult = m_pField->GetValue();
return varResult;
}

//-----------------------------------------------------------------------------
/*
 */
inline bool CAdoField::IsEmpty() const
{
_variant_t varResult = m_pField->GetValue();
return ((varResult.vt == VT_EMPTY) || (varResult.vt == VT_NULL));
}

//-----------------------------------------------------------------------------
/*
 */
inline bool CAdoField::IsNull() const
{
_variant_t varResult = m_pField->GetValue();
return (varResult.vt == VT_NULL);
}

///////////////////////////////////////////////////////////////////////////////
#pragma warning(default: 4290)
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2003-09-10 16:10:57  Darko           comment, Dump
 *       format
 *  2    Biblioteka1.1         2003-08-19 16:17:47  Darko           GetCount()
 *  1    Biblioteka1.0         2003-08-17 02:16:41  Darko
 * $
 *****************************************************************************/
