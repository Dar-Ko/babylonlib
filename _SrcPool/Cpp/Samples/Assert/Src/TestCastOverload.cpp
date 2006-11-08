/*$Workfile: TestCastOverload.cpp$: implementation file
  $Revision: 2$ $Date: 2005-03-22 02:19:30$
  $Author: Darko$

  Test C++ compiler conformance.
  Copyright: CommonSoft Inc.
  2005-03-21 Darko Kolakovic
*/

/* Group=Examples                                                            */

#include "TestConformance.h"
#ifndef _T
  #include "KTChar.h"
#endif
#ifndef LOG_EOT
  #include "KTestLog.h"
#endif

extern bool TsWriteToViewLn(LPCTSTR lszText);
bool TestCastOverload();

class CTestCastOverload
  {
  public:
    CTestCastOverload(int iValue, bool bValue, char* szValue, wchar_t* wszValue);

  public:
    operator int();
    operator bool();
    operator const char*();
    operator const wchar_t*();

  private:
    int   m_iValue;      //number test data
    bool  m_bValue;      //flag test data
    char* m_szValue;     //text test data
    wchar_t* m_wszValue; //Unicode text test data
  };

CTestCastOverload::CTestCastOverload(int iValue,       //[in] number test data
                                     bool bValue,      //[in] flag test data
                                     char* szValue,    //[in] text test data
                                     wchar_t* wszValue //[in] text test data
                                     ) :
   m_iValue( iValue ),
   m_bValue( bValue ),
   m_szValue(szValue)
{
}

CTestCastOverload::operator int()
{
TsWriteToViewLn(_T("int()"));
return m_iValue;  //number test data
}


//#if !defined (HAS_NO_DIFF_OVERLOADED_TYPECAST)
  CTestCastOverload::operator bool()
  {
  TsWriteToViewLn(_T("bool()"));
  return m_bValue;  //flag test data
  }

  CTestCastOverload::operator const char*()
  {
  TsWriteToViewLn(_T("const char*()"));
  return m_szValue; //text test data
  }

  CTestCastOverload::operator const wchar_t*()
  {
  TsWriteToViewLn(_T("const wchar_t*()"));
  return m_wszValue; //text test data
  }

//#endif

template <typename ATYPE, typename BTYPE>
class CTestCastOverloadT
  {
  public:
    CTestCastOverloadT(const ATYPE* aValue, const BTYPE* bValue)
      {
        m_aValue = const_cast<ATYPE*>(aValue);
        m_bValue = const_cast<BTYPE*>(bValue);
      };
    CTestCastOverloadT(const ATYPE* aValue) :
            m_aValue(const_cast<ATYPE*>(aValue)),
            m_bValue(NULL)
      {
      };
    virtual ~CTestCastOverloadT()
      {
      };
    operator const ATYPE* () const;
    operator const BTYPE* ();

  private:
    ATYPE* m_aValue;
    BTYPE* m_bValue;
  };

template <typename ATYPE, typename BTYPE>
CTestCastOverloadT<ATYPE, BTYPE>::operator const ATYPE* () const
  {
  return m_aValue;
  }

template <typename ATYPE, typename BTYPE>
CTestCastOverloadT<ATYPE, BTYPE>::operator const BTYPE* ()
  {
  return m_bValue;
  }

typedef CTestCastOverloadT<char, wchar_t> CTestCastOverloadC;

//Specialization for wchar_t
CTestCastOverloadC::operator const wchar_t*()
{
TsWriteToViewLn(_T("wchar_t()"));
return m_bValue;
}

/*---------------------------------------------------------------------------*/
/*Validates C++ compiler conformance. Compiler will report an error
  "overloaded function differs only by return type" if could not distinguish
   between coercion operators.

  Returns: true if test is successful; otherwise returns false.
 */
bool TestCastOverload()
{
#if defined (HAS_NO_DIFF_OVERLOADED_TYPECAST)
  TsWriteToViewLn(_T("HAS_NO_DIFF_OVERLOADED_TYPECAST"));
  return true;
#else
  TsWriteToViewLn(_T("TestCastOverload()"));

  CTestCastOverload testA(42, true, "Donau", NULL);
  int   iValue            = testA;
  bool  bValue            = testA;
  const char* szValue     = testA;
  const wchar_t* wszValue = testA;

  CTestCastOverloadT<char, int> testB(szValue, NULL);
  szValue = NULL;
  szValue= testB;

  CTestCastOverloadC testC(szValue, wszValue);
  wszValue = NULL;
  wszValue = testC;
  szValue = NULL;
  szValue= testC;

  TsWriteToViewLn(LOG_EOT);

  return ((iValue == 42) && bValue);
#endif
}

/* ////////////////////////////////////////////////////////////////////////// */
/******************************************************************************
 * $Log: 
 *  2    Biblioteka1.1         2005-03-22 02:19:30  Darko            
 *  1    Biblioteka1.0         2005-03-21 15:00:02  Darko Kolakovic 
 * $
 *****************************************************************************/


