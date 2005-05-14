/*$Workfile: KXmlDataType.cpp$: implementation file
  $Revision: 6$ $Date: 2005-05-14 01:24:22$
  $Author: Darko$

  Xml Data Type conversion.
  Copyright: CommonSoft Inc.
  2005-04-12 Darko Kolakovic
 */

/*Note: MS VC/C++ - Disable precompiled headers (/Yu"stdafx.h" option)       */

#ifdef _MSC_VER //Micorsoft Visual Studio C++ compiler
  #include "stdafx.h"
#endif  //_MSC_VER
#include "KTChar.h"
#ifdef _WIN32
  #include "Win/32/KXmlTypeWin.h"
#endif
#include "KXmlBinding.h" //XmlDataType enum

#ifdef _DEBUG
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Globals

/*string representation of datatypes used in XML Schema.

  See also: {html: <a href="http://www.w3.org/TR/xmlschema-2/#built-in-datatypes">
  W3C Recommendation; XML Schema Part 2: Datatypes; 3. Built-in datatypes</a>}
 */
TCHAR* g_xmlDataTypeList[] =
  {
  //Primitive datatypes

  _T("xsd:string"), //string represents wide-character strings
  _T("xsd:boolean"),//boolean represents the mathematical concept of
                    //binary-valued logic: [true, false]. The canonical
                    //representation for boolean is the set of literals
                    //{true, false}.
  _T("xsd:decimal"),//decimal represents a subset of the real numbers that
                    //can be obtained by multiplying an integer by a
                    //non-positive power of ten
  _T("xsd:float"),  //float represents a subset of the real numbers decribed
                    //in IEEE 754-1985: single-precision 32-bit floating point
                    //type
  _T("xsd:double"), //double represents a subset of the real numbers decribed
                    //in IEEE 754-1985: double-precision 64-bit floating point
                    //type
  _T("xsd:duration"),//duration represents a duration of time decribed
                    //in ISO 8601 §5.5.3.2
  _T("xsd:datetime"),//dateTime represents dates and times decribed in
                    //ISO 8601:2000
  _T("xsd:time"),   //time represents an instant of time that recurs every day
                    //as decribed in ISO 8601 §5.3
  _T("xsd:hexbinary"),//hexBinary represents arbitrary hex-encoded binary data.

  //Derived datatypes

  _T("xsd:integer"),//integer is derived from decimal and represents any
                    //positive or negative number that does not include
                    //a fraction or decimal, including zero
  _T("xsd:nonpositiveinteger"),//nonPositiveInteger is derived from integer and
                    //represents any negative integer number, including zero
  _T("xsd:negativeinteger"),//negativeInteger is derived from nonPositiveInteger
                    //and represents any negative integer number
  _T("xsd:nonnegativeinteger"),//nonNegativeInteger is derived from integer and
                    //represents any positive integer number, including zero
  _T("xsd:positiveinteger"),//positiveInteger is derived from nonNegativeInteger
                    //and represents any positive integer number
  _T("xsd:long"),   //long is derived from  integer and represents any
                    //64-bit integer from I64_MIN to I64_MAX, including zero.
  _T("xsd:int"),    //integer is derived from long and represents any
                    //32-bit integer from INT_MIN to INT_MAX, including zero.
  _T("xsd:short"),  //short is derived from int and represents any
                    //16-bit integer from SHRT_MIN to SHRT_MAX, including zero.
  _T("xsd:byte"),   //byte is derived from short and represents any
                    //8-bit integer from SCHAR_MIN to SCHAR_MAX, including zero.
  _T("xsd:unsignedlong"),//unsignedLong is derived from  nonNegativeInteger and
                    //represents 64-bit integers in the range [0, UI64_MAX]
  _T("xsd:unsignedint"),   //unsignedInt is derived from unsignedLong and
                    //represents 32-bit integers in the range [0, UINT_MAX]
  _T("xsd:unsignedshort"), //unsignedShort is derived from unsignedInt and
                    //represents 16-bit integers in the range [0, USHRT_MAX]
  _T("xsd:unsignedbyte"),  //unsignedByte is derived from unsignedShort and
                    //represents 8-bit integers in the range [0, UCHAR_MAX]

  NULL               //End of list

  };

///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
/*Converts string with XML Schema data type to numerical represntation.

  Returns: enum value correspondig to XML data type.
 */
XmlDataType GetXmlDatatype(const CXmlString& strXmlDatatype //[in] XML Schema
                            //data type string with namespace
                        )
{
int i = 0;
while (g_xmlDataTypeList[i] != NULL)
  {
  #pragma fixme (convert to lowercase before comparison.)
  if (strXmlDatatype == g_xmlDataTypeList[i])
    return (XmlDataType)(++i); //Add one more becouse list begins with
                               //xsd:string, enum with eXML_UNDEFINED
  i++;
  }
return eXML_UNDEFINED;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         2005-05-13 23:37:55  Darko
 * $
 *****************************************************************************/
