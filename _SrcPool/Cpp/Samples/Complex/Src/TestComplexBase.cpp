/*$Workfile: S:\_SrcPool\Cpp\Samples\Complex\Src\TestComplexBase.cpp$: implementation file
  $Revision: 1$ $Date: 2007-06-08 17:54:56$
  $Author: Darko Kolakovic$

  Complex number basic methods test
  Copyright: CommonSoft Inc.
  2007-07-08 Darko Kolakovic
*/

// Group=Examples

#include "stdafx.h"
#include "KDbgMacr.h"     //Compiler specific constants
#include "KProgCst.inl"   //NaN constants
#include "KComplex.h"     //CComplex class
#include "TestZAssert.h"  //Test validation class

#ifdef _DEBUG
  #define new DEBUG_NEW
  #undef THIS_FILE
  static char THIS_FILE[] = __FILE__;
#endif

#ifdef _MSC_VER
  //Microsoft Visual C/C++ compiler
  #ifdef  _STL
    #pragma message ("Using STL")
  #endif
  #ifdef  _COMPLEX_DEFINED
    #pragma message ("_COMPLEX_DEFINED")
  #endif
  #ifdef  __STD_COMPLEX
    #pragma message ("__STD_COMPLEX")
  #endif
  #ifdef _STLP_INTERNAL_COMPLEX //STLport library
    #pragma message ("_STLP_INTERNAL_COMPLEX")
  #endif
#endif

#ifdef __STD_COMPLEX //template std::complex is used
  #define TBASE_CONJ   std::conj 
  #define TBASE_SQRT   std::sqrt 
  #define TBASE_EXP    std::exp  
  #define TBASE_LOG    std::log  
  #define TBASE_POW    std::pow  
  #define TBASE_COS    std::cos  
  #define TBASE_COSH   std::cosh 
  #define TBASE_SIN    std::sin  
  #define TBASE_SINH   std::sinh 
  #define TBASE_LOG10  std::log10
#endif

extern bool TsWriteToView(LPCTSTR lszText);
extern bool TsWriteToViewLn(LPCTSTR lszText);

extern TestCComplex g_arrTestD[];//test values

//-----------------------------------------------------------------------------
/*Function evaluates complex number base class operations.

  Returns: true if successful, otherwise returns false.
 */
bool TestCComplexBase()
{
TsWriteToViewLn(_T("TestCComplexBase()"));
typedef TComplexBase<double> (*PFUNCCOMPLEXBASE_TEST) (const TComplexBase<double>&);
struct tagSFuncTest
  {
  PFUNCCOMPLEXBASE_TEST m_func; //function to test
  LPCTSTR m_funcName;          //name of the function
  PFUNCCOMPLEXD_TEST m_funcT;  //validating function
  };
bool bRes = false;  

tagSFuncTest funcTest[] =
  {
  
    {TBASE_CONJ , _T("conj(const CComplex&)") ,TsComplexD::Conjugate} ,// 0
    {TBASE_SQRT , _T("sqrt(const CComplex&)") ,TsComplexD::Sqrt}      ,// 1
    {TBASE_EXP  , _T("exp(const CComplex&)")  ,TsComplexD::Exp}       ,// 2
    {TBASE_LOG  , _T("log(const CComplex&)")  ,TsComplexD::Log}       ,// 3
    {TBASE_COS  , _T("cos(const CComplex&)")  ,TsComplexD::Cos}       ,// 4
    {TBASE_COSH , _T("cosh(const CComplex&)") ,TsComplexD::CosH}      ,// 5 
    {TBASE_SIN  , _T("sin(const CComplex&)")  ,TsComplexD::Sin}       ,// 6
    {TBASE_SINH , _T("sinh(const CComplex&)") ,TsComplexD::SinH}      ,// 7
    {TBASE_LOG10, _T("log10(const CComplex&)"),TsComplexD::Log10}     ,// 8
  
  //{polar, _T("polar(const double&, double)"),TsComplexD::polar} , // 4
  //{pow  , _T("pow(const double&)")  ,TsComplexD::Power}, // 8
//    {TBASE_POW  , _T("pow(const CComplex&)")  ,TsComplexD::Power}     ,// 4
  
     //real
     //imag
    //{std::norm , _T("norm(const CComplex&)") ,TsComplexD::Normalize} ,// 0
    //{abs  , _T("abs(const CComplex&)")  ,TsComplexD::Abs}       ,// 1
    //{arg  , _T("arg(const CComplex&)")  ,TsComplexD::Theta}     ,// 2
    {NULL, NULL, NULL} //the end
  };

int f = 0; //function number
while (funcTest[f].m_func != NULL)
  {
  int c = 0; //tested value number
  g_arrTestD[0].m_szFileName = _T("KComplex.h");
  g_arrTestD[0].m_szObjectName = funcTest[f].m_funcName;
  g_arrTestD[0].m_bResult = true;
  while(c < TESTSIZE)
    {      
    g_arrTestD[c] = funcTest[f].m_func(CComplex(g_arrTestD[c])); //Invoke a method
    g_arrTestD[c].Validate(funcTest[f].m_funcT); //Get test values

    g_arrTestD[c].m_szObjectName = funcTest[f].m_funcName;
    g_arrTestD[c].Write();
    
    if (!(g_arrTestD[0].m_bResult = g_arrTestD[c].m_bResult))
      break;
    c++;
    }
  LogTest(&g_arrTestD[0]);
  f++;
  }

return bRes;
}

///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2007-06-08 17:54:56  Darko Kolakovic 
 * $
 *****************************************************************************/

