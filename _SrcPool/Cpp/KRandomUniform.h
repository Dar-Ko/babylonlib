/*$Workfile: KRandomUniform.h$: header file
  $Revision: 6$ $Date: 2003-09-05 13:17:36$
  $Author: Borislav Lukovic$

  Uniform random number generator
  1987 G. Marsaglia, A. Zaman
  Mar 2k2 A. Janicijevic
*/

#ifndef _KRANDOMUNIFORM_H_
  //KRandomUniform.h sentry
  #define _KRANDOMUNIFORM_H_

#include "KTypedef.h"
#include "KRandom.h"  //CRandomNo class

///////////////////////////////////////////////////////////////////////////////
/*The Uniform Random Number Generator is based on the algorithm first 
  introduced by George Marsaglia and Arif Zaman in 1987.
  It passes all of the tests for random number generators and has a period
  of 2^144, is completely portable (gives bit identical results on all machines
  with at least 24-bit mantissas in the floating point representation).

  The algorithm is a combination of a Fibonacci sequence (with lags of 97 and 33,
  and operation "subtraction plus one, modulo one") and an "arithmetic sequence"
  (using subtraction).
*/
class CRandomUniform : public CRandomNo
{
// Construction
public:
  CRandomUniform();
  CRandomUniform(uint32 ulSeed);
  CRandomUniform(uint16 ulSeed1, uint16 ulSeed2);
  virtual ~CRandomUniform ();

// Attributes
private:
  static const int LAG_A;
  static const int LAG_B;
  double m_dTable[97];
  double m_dDecrement;
  unsigned int m_nIndexA,m_nIndexB;

// Operations
public:
  virtual void SetSeed(uint32 ulSeed = GetTimeSeed());
  void SetSeed (uint16 ulSeed1, uint16 ulSeed2);
  virtual int Get(unsigned int nLimes);
  virtual double Get();
  int Get(int iLower, int iUpper);
  double Get(double dLower, double dUpper);

};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//::SetSeed()------------------------------------------------------------------
/*Set new seed value. By default the system time is used for the seed.
  Note: Uses 32 bit integers.
 */
inline void CRandomUniform::SetSeed(uint32 ulSeed//[in] = GetTimeSeed()
                                   //the starting point for generated numbers
                                   )
{
 //Use high word and low word of the given 32 bit integer as a seeds
SetSeed((uint16)(ulSeed << 16), (uint16)ulSeed);
}

//::Get()----------------------------------------------------------------------
/*Returns: random float point value within a range [dLower, dUpper]
 */
inline double CRandomUniform::Get(double dLower,//[in] lower limit
                                  double dUpper //[in] upper limit
                                  )
{
return ((Get() * (dUpper - dLower)) + dLower);
}

/*Returns: random integer within a range [iLower, iUpper]
 */
inline int CRandomUniform::Get(int iLower, int iUpper)
{
return ((int)(Get() * (iUpper - iLower)) + iLower);
}

//::Get()----------------------------------------------------------------------
/*Retrieves the pseudorandom numbers that are generated.

  Returns: a pseudorandom integer in the range 0 to (nLimes - 1) < UINT_MAX.
 */
inline int CRandomUniform::Get(unsigned int nLimes //[in] upper limit of 
                                                 //generated numbers
                            ) 
{
//Get next seed value and return value from 0 to iLimes -1
return ((int)(Get() * nLimes));
}

///////////////////////////////////////////////////////////////////////////////
#endif // _KRANDOMUNIFORM_H_
