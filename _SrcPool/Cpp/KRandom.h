/*$Workfile: KRandom.h$: header file
  $Revision: 7$ $Date: 4/3/02 3:29:10 PM$
  $Author: Darko Kolakovic$

  Random number generator base class
  Copyright: CommonSoft Inc
  Mar. 2k2 Darko Kolakovic
 */

#ifndef _KRANDOMNO_H_
  //KRandom.h sentry
  #define _KRANDOMNO_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef _MSC_VER
  #include <limits.h> //UINT_MAX macro
#endif

#include <time.h>   //time()
///////////////////////////////////////////////////////////////////////////////
/*CRandomNo class is a pseudo-random number generator. It uses ANSI run-time 
  library for generating a series of pseudorandom integers.

  See also: srand() and rand()

  Note: is required to include stdlib.h before KRandom.h header file.
 */
class CRandomNo
{
// Construction
public:
  CRandomNo();
  CRandomNo(unsigned long ulSeed);

// Operations
public:    
  virtual void SetSeed(unsigned long ulSeed = GetTimeSeed());
  virtual int  Get(unsigned long nLimes = ULONG_MAX);
  int operator() (unsigned long nLimes);
protected:
  static unsigned long GetTimeSeed();
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

/*Default constructor. Initialize the number generator by calling SetSeed().
 */
inline CRandomNo::CRandomNo()
{
}

/*
  Example:
    #include "KRandom.h"
    #include <iostream.h>
    #include <iomanip.h>  //setw()

    void main(void)
      {
      const unsigned long TheSeed = 1701UL;
      unsigned int nLimes = 15000;
      CRandomNo RandNo1;
      RandNo1.SetSeed(); //Uses current time as a seed
      CRandomNo RandNo2(TheSeed);
      CRandomNo RandNo3;
      RandNo3.SetSeed(TheSeed);
      
      int i = 0;
      while ( i < 100)
        {
        cout << setw(6) << '\t' << RandNo1(nLimes); 
        cout << setw(6) << '\t' << RandNo2.Get(nLimes);
        cout << setw(6) << '\t' << RandNo3(nLimes);
        cout << endl;
        i++;
        }
      }
 */
inline CRandomNo::CRandomNo(unsigned long ulSeed//[in] the starting point 
                                                //for generated numbers
                            ) 
{
SetSeed(ulSeed);
}

//::SetSeed()------------------------------------------------------------------
#include <stdlib.h> //srand(), rand()
/*Set new seed value. Using same seed value generates the same sequence of
  numbers.
 */
inline void CRandomNo::SetSeed(unsigned long ulSeed//[in] = GetTimeSeed()
                                     //the starting point for generated numbers
                               )
{
  //Sets a random starting point.
srand(ulSeed);
}

//::Get()----------------------------------------------------------------------
/*Retrieves the pseudorandom numbers that are generated.
  Returns: a pseudorandom integer in the range 0 to (nLimes - 1) < UINT_MAX.

  Example:
    #include <stdlib.h>  //srand(), rand()
    #include <stdio.h>   //printf()
    #include "KRandom.h" // CRandomNo class

    void main()
      {
      int i;

      //Seed the random-number generator with current time so that
      //the numbers will be different every time we run.
      CRandomNo RandNo;

      //Display 10 numbers
      for(int i = 0; i < 10; i++ )
        printf( "  %6d\n", RandNo.Get() );
      }

 */
inline int CRandomNo::Get(unsigned long nLimes //[in] = ULONG_MAX upper limit of 
                                               //generated numbers
                         )
{
return rand() % nLimes;
}

//::operator()-----------------------------------------------------------------
/*Get a psuedo-random number. Used as a synonym for the Get() method.

  Example:
    ...
    std::ofstream file(szFileName);
    CRandomNo iRandNo;
    int i = 0;
    while(i < 1000)
      {
      //Get a random letter in range [A,Z]
      file << (char)(iRandNo('Z' - 'A') + 'A');
      i++;
      }

 */
inline int CRandomNo::operator() (unsigned long nLimes //[in] upper limit of 
                                                     //generated numbers
                                 )
{
//Get next seed value and return value from 0 to iLimes -1
return(Get(nLimes));
}

//::GetTimeSeed()--------------------------------------------------------------
/*This static member function generates a seed number based on system time.
 */
inline unsigned long CRandomNo::GetTimeSeed()
{
return (unsigned long)time(NULL);
}

///////////////////////////////////////////////////////////////////////////////
#endif _KRANDOMNO_H_
