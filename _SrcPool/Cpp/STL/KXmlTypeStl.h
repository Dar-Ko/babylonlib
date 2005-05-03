#error 'TODO:'

#if defined (_STL) || defined (_USE_STL)
//-----------------------------------------------------------------------------
#ifndef CXmlString

    #include <string>
      //STL wide-character string handler
    typedef string<wchar_t> CXmlString;

  //XML wide-character string handler type
  #define CXmlString CXmlString
#endif


#endif //_STL || _USE_STL
