/*$Workfile: KProgCst.inl$: header file
  $Revision: 19$ $Date: 2007-05-31 16:43:25$
  $Author: Darko Kolakovic$

  Constants
  Copyright: CommonSoft Inc.
  Nov. 95 D. Kolakovic
*/

#ifndef _KPROGCST_INL_
    //$Workfile: KProgCst.inl$ sentry
  #define _KPROGCST_INL_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifndef _KPROGCST_H_
  #include "KProgCst.h" //Basic constants and macros
#endif

/* //////////////////////////////////////////////////////////////////////// */
/* Macros                                                                   */

#ifndef DELETE_POBJECT
  /*The macro deletes the memory object that was pointed to if differs from
    NULL.
   */
  #define DELETE_POBJECT(pObject) {\
    if (pObject != NULL)\
      {\
      delete pObject;\
      pObject = NULL;\
      }\
    }
#endif

#ifdef _MSC_VER     //Microsoft VC
  #include <float.h>
  #ifndef __cplusplus
    #define IsNaN(dvalue)   (_isnan(dvalue) != 0)
  #endif
#endif

/////////////////////////////////////////////////////////////////////////////
//Constants
#ifdef _M_IX86    //Intel x86 CPU
  #ifndef _ROUNDOFF_INC_ //define different roundoff than it is in <float.h>

    #include <float.h>   //float point limits
      //Rounding error constant (for x86  2**(-53) = DBL_EPSILON/2)
    #define CST_ROUNDOFF 1.11022302462515654042e-16
      //Rounding error constant (include <float.h>)
    #define CST_fROUNDOFF FLT_EPSILON
  #endif  //_ROUNDOFF_INC_

  #ifndef CST_dQNaN
           //double quiet NaN (not a number) -1.#IND according to IEC 559
    const NaN_NUMBER CST_dQNaN  = {0x0,NaN_DQUIET};
    #define CST_dQNaN CST_dQNaN
  #endif
  #ifndef CST_dSNaN
           //double signaling NaN (not a number) -1.#INF
    const NaN_NUMBER CST_dSNaN = {0x0,NaN_DSIGNAL};
           //double positive infinity 1.#INF
    #define CST_dSNaN CST_dSNaN
  #endif
  #ifndef CST_dINF
    //See also: HUGE_VAL, _HUGE, math.h
    const NaN_NUMBER CST_dINF  = {0x0,NaN_DPOSINFINITY};
    #define CST_dINF CST_dINF
  #endif

#endif    //_M_IX86 Intel x86 CPU

///////////////////////////////////////////////////////////////////////////////
//Template functions
#ifdef __cplusplus
///////////////////////////////////////////////////////////////////////////////
#include <math.h>

#ifndef _ROUNDOFF_INC_ //define different roundoff than it is in <float.h>
 #ifndef IsZero
  //IsZero()-----------------------------------------------------------------
  /*Returns: TRUE if expression is zero
   */
  template <class TYPE> inline bool IsZero(const TYPE&  p)
    {
    return (p == 0);
    };

  /*Returns: TRUE if expression is zero +/- rounding error
   */
  inline bool IsZero(const float&  p)
    {
    return (fabs(p) <= FLT_EPSILON);
    };
  inline bool IsZero(const double& p)
    {
    return (fabs(p) <= DBL_EPSILON);
    };
 #endif

//IsEqual()--------------------------------------------------------------------
/*Returns: TRUE if two  numbers are equal.
 */
template <class TYPE> inline bool IsEqual(const TYPE& a, const TYPE& b)
  {
  return (a == b);
  };

/*Returns: TRUE if two float numbers are equal within an error represented
  with epsilon.

  Epsilon is defined as as the smallest positive number x, such that x+1.0
  is not equal to 1.0.
  FLT_EPSILON is defined in <float.h> as 1.192092896e-07F
 */
inline bool IsEqual(const float& a, const float& b)
  {
  return ((((b - FLT_EPSILON) < a) && (a <( b + FLT_EPSILON))));
  }
/*DBL_EPSILON is defined in <float.h> as 2.2204460492503131e-016
 */
inline bool IsEqual(const double& a, const double& b)
  {
  return ((((b - DBL_EPSILON) < a) && (a <( b + DBL_EPSILON))));
  }
//=============================================================================
#endif  //~_ROUNDOFF_INC_

//IsNaN()----------------------------------------------------------------------
#ifdef _MSC_VER     //Microsoft VC++
 inline bool IsNaN(const double& dValue)
   {
   return (_isnan(dValue) != 0);
   }
#else
  #define _KEXAMIN_NAN_FUNC 1
#endif

#ifdef _KEXAMIN_NAN_FUNC
/*Tests a double value to determine if it is a quiet NaN (not a number). A NaN is
  generated when the result of a floating-point operation cannot be represented
  in Institute of Electrical and Electronics Engineers (IEEE) format.

  Presentation of NaNs according to IEC 559:

    quiet NaN         -1.#IND,
    signaling NaN     -1.#INF,
    positive infinity  1.#INF

  Example:
    #include <Math.h>
    #include "KProgCst.inl"
    void Test(double x)
      {
      double dTest = x*log(x);
        //If x = 0, result is undefined
      if (IsNaN(dTest))
        wprintf("Undefined result for x = %f",x);
      }

   See also: HUGE_VAL, _HUGE, math.h
 */
inline bool IsNaN(const double& dValue)
  {
  NaN_NUMBER Test;
  Test.dValue = dValue;
  if(Test.llValue[_ENDIAN_HIGH_INDEX] != NaN_DQUIET)
    return false;

  return true;
  }
#endif

//IsLittleEndian()-------------------------------------------------------------
/*Validates machine architecture in run-time.
  Returns: TRUE if a machine has Little Endian architecture.

  Note: "Little Endian" flag signals that the little end, or lower end, is
  stored first in the memory (low byte at low address, high byte at high
  address).

  See also: _ENDIAN_LITTLE_, _ENDIAN_BIG_
 */
inline bool IsLittleEndian()
{
const int iOne = 1;
  //Test if low or high byte has been set to one
  //The low byte is examined and if it is zero then the machine is big-endian.
  //If the low byte is one then the machine is little-endian.
return ((*(char *)&iOne) != 0);
}

//-----------------------------------------------------------------------------
/*Returns number of elements contained in an array.

  Example:
      void main()
      {
      int iTest;
      int iArray[255];
      int* pTest;
      std::vector<int> iVector(255);

      //SizeOfArray(iTest); Generates compile-time error as desired
      SizeOfArray(iArray);
      SizeOfArray(pTest);
      SizeOfArray(iVector);
      return 0;
      }
 */
template<typename ARRAY> size_t SizeOfArray(ARRAY &x)
{
size_t const SIZE(sizeof(x) / sizeof(x[0]));
return SIZE;
}

//-----------------------------------------------------------------------------
/*Verfies if an array is an empty or insignificant set.

  Example:
      int arrVec[5];
      if(!IsEmpty<int>(arrVec))
        std::cout << arrVec[0];

  Returns true if the array is NULL pointer or if first element is zero;
  otherwise returns false.
 */
template<typename ARRAY> bool IsEmpty(ARRAY* pVec)
{
return ((pVec == NULL) || (pVec[0] == 0));
}

/*Verfies if zero-terminated string is an empty string.

  Example:
      char* szVec = "123456";
      if(!IsEmpty(szVec))
        std::cout << szVec;

  Returns true if the string is NULL pointer or if it is empty;
  otherwise returns false.
 */
template<LPCTSTR> bool IsEmpty(LPCTSTR pVec)
{
return ((pVec == NULL) || (pVec[0] == _T('\0')));
}

#endif //__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif  //_KPROGCST_INL_
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         18/08/2001 12:45:30 AMDarko
 *  3    Biblioteka1.2         10/07/2001 12:45:49 AMDarko
 *  2    Biblioteka1.1         08/06/2001 11:51:18 PMDarko           VSS
 *  1    Biblioteka1.0         13/08/2000 3:57:01 PMDarko
 * $
 *  Dec. 99 NaN constants D.K.
 *  Nov. 95 D. Kolakovic
 *****************************************************************************/
