/*$Workfile: KDbgAdoPropertyAttributes.cpp$: implementation file
  $Revision: 3$ $Date: 2005-04-26 11:28:39$
  $Author: Darko Kolakovic$

  Dumps Attributes property
  Copyright: CommonSoft Inc.
  2003-08 Darko Kolakovic
 */ 

// Group=Diagnostic
#include "stdafx.h"

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
/*Dump Attributes property decription.
  For a Property object, the Attributes property is read-only and its value can
  be the sum of any one or more of the PropertyAttributesEnum values. 
  The allowable PropertyAttributesEnum values can be one of the following constants:

    Enumeration Value Description 
    adPropNotSupported   0     property is not supported by the provider. 
    adPropRequired     0x1     user must specify a value for this property before the data source is initialized. 
    adPropOptional     0x2     user does not need to specify a value for this property before the data source is initialized. 
    adPropRead         0x200   user can read the property. 
    adPropWrite        0x400   user can set the property. 

  Returns: list of Property Attributes.

  Example:
    PropertiesPtr ptrProperties;
    //intialize ptrProperties
    ...
    TRACE(DumpPropertyAttributes(ptrProperties->GetAttributes()));

  Note: uses Microsoft Foundation Library (MFC);
        Microsoft ActiveX Data Objects (ADO).
        Microsoft Windows specific (Win).
 */
CString DumpAdoPropertyAttributes(
          const PropertyAttributesEnum& nPropertyAttributesEnum //[in]
           )
{
CString strTmp(_T(""));
  
if(nPropertyAttributesEnum & adPropNotSupported)
  strTmp += _T("NotSupported");
else 
  {
  if((nPropertyAttributesEnum & adPropRequired) == adPropRequired)
    strTmp += _T("Required ");
  if((nPropertyAttributesEnum & adPropOptional) == adPropOptional)
    strTmp += _T("Optional ");
  if((nPropertyAttributesEnum & adPropRead) == adPropRead)
    strTmp += _T("Read ");
  if((nPropertyAttributesEnum & adPropWrite) == adPropWrite)
    strTmp += _T("Write ");
  }
return strTmp;
}

/*****************************************************************************
 * $Log: 
 *  3    Biblioteka1.2         2005-04-26 11:28:39  Darko Kolakovic Document groups
 *       and typo fixes
 *  2    Biblioteka1.1         2004-10-01 22:34:00  Darko           stdafx.h
 *  1    Biblioteka1.0         2003-08-13 17:36:18  Darko           
 * $
 *****************************************************************************/
