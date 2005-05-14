/*$Workfile: KXmlBinding.h$: header file
  $Revision: 8$ $Date: 2005-05-14 00:40:28$
  $Author: Darko$

  XML Data Binding
  Copyright: C/C++ Users Journal
  2004-03-01 Yingjun Zhang
 */

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
  #pragma once
#endif

#ifndef _KXMLBINDING_H_
    //$Workfile: KXmlBinding.h$ sentry
  #define _KXMLBINDING_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include <stddef.h> //offsetof macro

///////////////////////////////////////////////////////////////////////////////
// XML Data Binding

/*XML schema data types to be used for specifying datatypes on XML elements and
  attributes.

  Note: this is a subset of datatypes defined in XML Schema.

  See also: {html: <a href="http://www.w3.org/TR/xmlschema-2/#built-in-datatypes">
  W3C Recommendation; XML Schema Part 2: Datatypes; 3. Built-in datatypes</a>}
 */
typedef enum XmlDataType
{
  eXML_UNDEFINED  = 0, //datatype is not defined

  //Primitive datatypes

  eXML_STRING,      //string represents wide-character strings
  eXML_BOOLEAN,     //boolean represents the mathematical concept of
                    //binary-valued logic: [true, false]. The canonical
                    //representation for boolean is the set of literals
                    //{true, false}.
  eXML_DECIMAL,     //decimal represents a subset of the real numbers that can
                    //be obtained by multiplying an integer by a non-positive
                    //power of ten
  eXML_FLOAT,       //float represents a subset of the real numbers decribed
                    //in IEEE 754-1985: single-precision 32-bit floating point
                    //type
  eXML_DOUBLE,      //double represents a subset of the real numbers decribed
                    //in IEEE 754-1985: double-precision 64-bit floating point
                    //type
  eXML_DURATION,    //duration represents a duration of time decribed
                    //in ISO 8601 §5.5.3.2
  eXML_DATETIME,    //dateTime represents dates and times decribed in
                    //ISO 8601:2000
  eXML_TIME,        //time represents an instant of time that recurs every day
                    //as decribed in ISO 8601 §5.3
  eXML_HEXBINARY,   //hexBinary represents arbitrary hex-encoded binary data.

  //Derived datatypes

  eXML_INTEGER,     //integer is derived from decimal and represents any
                    //positive or negative number that does not include
                    //a fraction or decimal, including zero
  eXML_NONPOSINTEGER,//nonPositiveInteger is derived from integer and represents
                    //any negative integer number, including zero
  eXML_NEGINTEGER,  //negativeInteger is derived from nonPositiveInteger and
                    //represents any negative integer number
  eXML_NONNEGINTEGER,//nonNegativeInteger is derived from integer and represents
                    //any positive integer number, including zero
  eXML_POSINTEGER,  //positiveInteger is derived from nonNegativeInteger and
                    //represents any positive integer number
  eXML_LONG,        //long is derived from  integer and represents any
                    //64-bit integer from I64_MIN to I64_MAX, including zero.
  eXML_INT,         //integer is derived from long and represents any
                    //32-bit integer from INT_MIN to INT_MAX, including zero.
  eXML_SHORT,       //short is derived from int and represents any
                    //16-bit integer from SHRT_MIN to SHRT_MAX, including zero.
  eXML_BYTE,        //byte is derived from short and represents any
                    //8-bit integer from SCHAR_MIN to SCHAR_MAX, including zero.
  eXML_ULONG,       //unsignedLong is derived from  nonNegativeInteger and
                    //represents 64-bit integers in the range [0, UI64_MAX]
  eXML_UINT,        //unsignedInt is derived from unsignedLong and represents
                    //32-bit integers in the range [0, UINT_MAX]
  eXML_USHORT,      //unsignedShort is derived from unsignedInt and represents
                    //16-bit integers in the range [0, USHRT_MAX]
  eXML_UBYTE,       //unsignedByte is derived from unsignedShort and represents
                    //8-bit integers in the range [0, UCHAR_MAX]

  //End of list; datatype count is the last item

  eXML_DATATYPECOUNT //number of recognized datatypes
} XmlDataType;

///////////////////////////////////////////////////////////////////////////////
/*The XmlBindingEntry object describes data contained in an XML document,
  according to the required data schema.
 */
struct XmlBindingEntry
{
  wchar_t*      m_szElement;    //XML element tag
  XmlDataType   m_eDataType;    //XML schema data type
  unsigned long m_ulDataOffset; //position in local data container
};

///////////////////////////////////////////////////////////////////////////////
// Macros

class CXmlStringData;

/*The macros BEGIN_XML_BINDING, XML_ELEMENT, and END_XML_BINDING are used to
  describe the XML data schema.

  Example:
    #include "KXmlBinding.h"
    #include <iostream>
    using std::wostream;

    class CCustomerData
      {
      protected:
        BEGIN_XML_BINDING(L"CustomerOrder", CCustomerData)
            XML_ELEMENT(L"OrderID",  eXML_INT,    m_iOrderId)
            XML_ELEMENT(L"Customer", eXML_STRING, m_wszCustomerName)
            XML_ELEMENT(L"Item",     eXML_STRING, m_wszItemName)
            XML_ELEMENT(L"Unit",     eXML_STRING, m_wszUnit)
            XML_ELEMENT(L"Quantity", eXML_DOUBLE, m_dQuantity)
        END_XML_BINDING()
        int       m_iOrderId;
        wchar_t   m_wszCustomerName[20];
        wchar_t   m_wszItemName[20];
        wchar_t   m_wszUnit[20];
        double    m_dQuantity;
      public:
          friend wostream& operator << (wostream& wo, const CCustomerData& xmlData);
      };

      wostream& operator << (wostream& wo, const CCustomerData& xmlData)
      {
          return wo <<
                  L"Order " << xmlData.m_iOrderId <<
                  L" from " << xmlData.m_wszCustomerName <<
                  L": "     << xmlData.m_wszItemName <<
                  L" "      << xmlData.m_Quantity <<
                  L" "      << xmlData.m_wszUnit <<
                  L"s has been processed." <<
                  std::endl;
      }

  See also: XML_ELEMENT, XmlDataType, XmlBindingEntry
 */
#define BEGIN_XML_BINDING(XMLELEMENTNAME_, XMLELEMENTDATA_) public: \
  typedef XMLELEMENTDATA_ CXmlElementData; \
  static CXmlStringData GetClassName() { return CXmlStringData(XMLELEMENTNAME_); } \
  const XmlBindingEntry* GetXmlBindingEntries() { \
  static const XmlBindingEntry m_xmlBindingEntries[] = {

/*Appends XML data elements to the data container.
  - XMLELEMENTNAME_   XML element as wide-character zero-terminated string
  - XMLDATATYPE_      XML data type
  - XMLDATACONTAINER_ data container of size sufficient to hold the data of the
                      XMLDATATYPE_ type.

  Example:
    XML_ELEMENT(L"Item", eXML_STRING, m_wszItemName)

  See also: BEGIN_XML_BINDING Example, XmlDataType, XmlBindingEntry
 */
#define XML_ELEMENT(XMLELEMENTNAME_, XMLDATATYPE_, XMLDATACONTAINER_)\
  { \
  XMLELEMENTNAME_, \
  XMLDATATYPE_, \
  offsetof(CXmlElementData, XMLDATACONTAINER_) \
  },

/*Ending macro for XML data binding.
  See also: BEGIN_XML_BINDING Example, XmlDataType, XmlBindingEntry
 */
#define END_XML_BINDING()   {L"", eXML_UNDEFINED, 0}};\
  return m_xmlBindingEntries;}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KXMLBINDING_H_
/*****************************************************************************
 * $Log:
 *  3    Biblioteka1.2         2005-04-13 12:32:31  Darko Kolakovic new datatypes
 *       according to W3C Recommendation
 *  2    Biblioteka1.1         2005-04-06 14:47:03  Darko Kolakovic Renamed
 *       CXmlString
 *  1    Biblioteka1.0         2005-04-03 23:51:08  Darko
 * $
 *****************************************************************************/
