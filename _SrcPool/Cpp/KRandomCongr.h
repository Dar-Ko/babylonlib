/*$Workfile: KRandomCongr.h$: header file
  $Revision: 2$ $Date: 18/03/2002 4:35:04 PM$
  $Author: Darko Kolakovic$

  Congruential random number generator
  Copyright: CommonSoft Inc
  1951 D. Lehmer
  Sep. 97. Darko Kolakovic
 */

#ifndef _KRANDOMCONGR_H_
  //KRandomCongr.h sentry
  #define _KRANDOMCONGR_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#define _TABLE2     //Linear Coefficent table selector

#ifdef _TABLE1        //Linear coefficents
  #define CST_RANDOM_MUL   214013L
  #define CST_RANDOM_ADD  2531011L
#else  //_TABLE2
  #define CST_RANDOM_MUL  5709421L
  #define CST_RANDOM_ADD        1L
#endif

#include "KRandom.h"   //CRandomNo class

///////////////////////////////////////////////////////////////////////////////
/*CRandomCongr class is a psuedo-random number generator that uses the linear 
  congruential method first introduced by D. Lehmer in 1951. 
  An application could have several random generators simultaneously.

  Note: This generator depends upon overflow. It will not  work correctly in an 
        environment where integer arithmetic generates an overflow exception.
 */
class CRandomCongr : public CRandomNo
{
// Construction
public:
  CRandomCongr();
  CRandomCongr(unsigned long ulSeed);

// Attributes
private:
    unsigned long m_ulSeed;                 //Random generator seed
    const unsigned long COEFFMULT,COEFFADD; //Linear coefficents

// Operations
public:    
    virtual void SetSeed(unsigned long ulSeed = GetTimeSeed());   
    virtual int  Get(unsigned int nLimes = UINT_MAX);
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

/*Default constructor. The current time is used as a seed.
 */
inline CRandomCongr::CRandomCongr() :
      COEFFMULT(CST_RANDOM_MUL),//Linear coefficents
      COEFFADD (CST_RANDOM_ADD),
      m_ulSeed (GetTimeSeed()) 
{
}

inline CRandomCongr::CRandomCongr(unsigned long ulSeed //[in] the starting
                                                   //point for generated numbers
                            ) :
      COEFFMULT(CST_RANDOM_MUL),//Linear coefficents
      COEFFADD (CST_RANDOM_ADD),
      m_ulSeed (ulSeed) 
{
}

//::SetSeed()------------------------------------------------------------------
/*Set new seed value.
 */
inline void CRandomCongr::SetSeed(unsigned long ulSeed//[in] = GetTimeSeed()
                                 //the starting point for generated numbers
                                 )
{
m_ulSeed = ulSeed;
}

//::Get()----------------------------------------------------------------------
/*Retrieves the pseudorandom numbers that are generated.

  Returns: a pseudorandom integer in the range 0 to (nLimes - 1) < UINT_MAX.
 */
inline int CRandomCongr::Get(unsigned int nLimes //[in] upper limit of 
                                                 //generated numbers
                            ) 
{
//Get next seed value and return value from 0 to iLimes -1
return(((m_ulSeed = m_ulSeed * COEFFMULT + COEFFADD) >> 16) % nLimes);
}

///////////////////////////////////////////////////////////////////////////////
#endif _KRANDOMCONGR_H_

///////////////////////////////////////////////////////////////////////////////
/*References:
  Box, G.E.P, M.E. Muller 1958; A note on the generation of random normal 
  deviates, Annals Math. Stat, V. 29, pp. 610-611 Carter, E.F, 1994; 
  The Generation and Application of Random Numbers, 
  Forth Dimensions Vol XVI Nos 1 & 2, Forth Interest Group, Oakland California 

  Knuth, D.E., 1981; The Art of Computer Programming, Volume 2 Seminumerical 
  Algorithms, Addison-Wesley, Reading Mass., 688 pages, ISBN 0-201-03822-6 

  MacDougall,M.H., 1987; Simulating Computer Systems, M.I.T. Press, Cambridge,
  Ma., 292 pages, ISBN 0-262-13229-X 

  Press, W.H., B.P. Flannery, S.A. Teukolsky, W.T. Vetterling, 1986; 
  Numerical Recipes, The Art of Scientific Computing, 
  Cambridge University Press, Cambridge, 818 pages, ISBN 0-512-30811-9 

  Rubinstein, R.Y., 1981; Simulation and the Monte Carlo method,
  John Wiley & Sons, ISBN 0-471-08917-6 
 *****************************************************************************/
