/*$Workfile: KReal8Cv.h$: header file
  $Revision: 4$ $Date: 1/24/02 7:19:15 PM$
  $Author: Darko$

  Conversion helper for 8 bytes real numbers (double)
  Copyright: CommonSoft Inc
  Mar 2k. D.Kolakovic  
*/

#ifndef __KREAL8CV_H__
  /*KReal8Cv.h sentry                                                       */
  #define __KREAL8CV_H__

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include "KProgCst.h" /*_ENDIAN_HIGH_INDEX constant                          */

  //Number of bits in the exponent for IEEE 754 double precision real
const int REAL8_IE_ExpLEN = 31;
  //Number of bits in the mantissa for IEEE 754 double precision real
const int REAL8_IE_ManLEN = 52;
  //Exponent bias  for IEEE 754 double precision real
const int REAL8_IE_BIAS = 1023;

/*UReal8Conversion objects are used to expand float point numbers into 
  implicit form. This object handles numbers 8 bytes long.
  See Also: IEEE 754 standard
 */
union UReal8Conversion
  {
  double dReal;             /*64-bit float point number                */
  long   lDWord[2];         /*binary presentation of 64-bit float point*/
  unsigned char uByte[8];   /*byte array                               */

  #ifdef __cplusplus
      //Constructon
    UReal8Conversion();
    UReal8Conversion(const double& dValue);
    UReal8Conversion(const long&  lValueLo, const long&  lValueHi);
       //Operators
    operator double() const;
  #endif /*__cplusplus                                                       */
  };

#ifdef __cplusplus
///////////////////////////////////////////////////////////////////////////////
// Inlines

//::UReal8Conversion()---------------------------------------------------------
/*Default constructor
 */
inline UReal8Conversion::UReal8Conversion()
{
lDWord[_ENDIAN_LOW_INDEX] =  0;
lDWord[_ENDIAN_HIGH_INDEX] = 0; 
}

/*Assignment constructor
 */
inline UReal8Conversion::UReal8Conversion(const double& dValue) :
  dReal(dValue)
{
}

inline UReal8Conversion::UReal8Conversion(const long&  lValueLo, const long&  lValueHi)
{
lDWord[_ENDIAN_LOW_INDEX] =  lValueLo;
lDWord[_ENDIAN_HIGH_INDEX] = lValueHi; 
}

//::operator double()----------------------------------------------------------
/*
 */
inline UReal8Conversion::operator double() const
{
return dReal;
}

///////////////////////////////////////////////////////////////////////////////
// Helpers

//IsFinite()-------------------------------------------------------------------
#ifndef _MSC_VER  //~MS C/C++ compiler
  /*Returns zero if float point number in double precision is not a number (NaN).
    NaNs have all exponent bits set to one, but non-zero mantissa field. NaNs
    includes indeterminate, negative infinity and positive infinity. 
    See Also: IEEE 754 standard
   */
  inline int IsFinite(const double& dValue)
    {
    const UReal8Conversion& real = dValue;
    return  (int)((DWORD)((real[_ENDIAN_HIGH_INDEX]&0x7fffffff)-NaN_DPOSINFINITY)>>REAL8_IE_ExpLEN);
    }

#else //_MSC_VER
  #include <Float.h>
  inline int IsFinite(const double& dValue)
    {
    return _finite(dValue);
    }
#endif //~_MSC_VER

#endif  /*__cplusplus                                                        */


/*///////////////////////////////////////////////////////////////////////////*/
#endif  /*__KREAL8CV_H__                                                     */
