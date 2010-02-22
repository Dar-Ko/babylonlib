/*$RCSfile: KSafeArray.h,v $: header file
  $Revision: 1.2 $ $Date: 2010/02/22 22:38:29 $
  $Author: ddarko $

  Converts a variant value of a VARIANT structure to a string.
  Copyright: babylonlib.sourceforge.net
  2010-02-10 Darko Kolakovic
*/

#ifndef _KSAFEARRAY_H_
    /*RCSfile: $ sentry*/
  #define _KSAFEARRAY_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#if ( defined(_DOS) || defined(DOS) || defined(WIN) || defined(WIN16) )
  /*MS Windows 16-bit, DOS 16-bit                                        */
  #ifndef __NATIVE_16_BIT__
    #define __NATIVE_16_BIT__ 16
  #endif
#endif /* _DOS || DOS || WIN || WIN16*/

#ifdef _WIN32
  #ifndef __oaidl_h__
    #include <oaidl.h> //SAFEARRAY struct
  #endif //__oaidl_h__
  #include <wtypes.h> //VARENUM type
  #define SAFEARRAY SAFEARRAY
  #define SAFEARRAYBOUND SAFEARRAYBOUND
#endif

///////////////////////////////////////////////////////////////////////////////
#ifndef SAFEARRAYBOUND
  /*Represents the bounds of the one dimensional safe array.

    Example:
      //If an array was specified in a C-like syntax as a [2][5], it would have
      //two elements in the rgsabound vector. Element 0 has an lLbound of 0 and
      //a cElements of 2. Element 1 has an lLbound of 0 and a cElements of 5.
     
   */
  struct tagSAFEARRAYBOUND
  {
  uint32_t cElements; //the number of elements in the array
  int32_t  lLbound;   //the lower bound
  };

  /*The bounds of one dimension of the safe array array.
    See also: tagSAFEARRAYBOUND
   */
  typedef struct tagSAFEARRAYBOUND SAFEARRAYBOUND;
  #define SAFEARRAYBOUND SAFEARRAYBOUND
#endif //SAFEARRAYBOUND

///////////////////////////////////////////////////////////////////////////////
#ifndef SAFEARRAY
  /*
   */
  struct tagSAFEARRAY
  {
  uint16_t cDims;         //number of dimensions in the array
  uint16_t fFeatures;     //array's attributes describing what type of data is
                          //stored in the SAFEARRAY and how the array is allocated
  #if defined (__NATIVE_16_BIT__)
    uint16_t cbElements;  //size of the single element of the array in bytes
    uint16_t cLocks;      //lock counter of the array
    uint32_t long handle; //used on Macintosh only.
  #else //__NATIVE_32_BIT__
    uint32_t cbElements;  //size of the single element of the array in bytes
    uint32_t cLocks;      //lock counter of the array
  #endif
  void* pvData;                //contained data elements
  SAFEARRAYBOUND rgsabound[1]; //array dimension bounds

  } SAFEARRAY;

  typedef struct tagSAFEARRAY SAFEARRAY;
  #define SAFEARRAY SAFEARRAY
#endif //SAFEARRAY

///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
  #if defined(__BORLANDC__) /*Borland C++ Compiler ver. 5.00 or greater*/
    #if __BORLANDC__ >= 0x500
      #include <safearry.h> //VCL template class TSafeArray
    #endif
  #else //~__BORLANDC__

#pragma TODO
/*Represents the bounds of a multi-dimensional safe array.

  Parameters:
    - SIZE number of dimensions of the safe array.
*/
template<int SIZE>
class TSafeArrayDim
{
public:
  TSafeArrayDim<SIZE>();
  TSafeArrayDim<SIZE>(int nCount1, int nCount2 = 0, int nCount3 = 0);

  operator SAFEARRAYBOUND* ();
  //operator []; //TODO

public:
  SAFEARRAYBOUND m_saBounds[SIZE]; //the bounds of the multi-dimensional safe array
};

#define TArrayDimT TSafeArrayDim //Bounds of a multi-dimensional safe array

///////////////////////////////////////////////////////////////////////////////
// Inlines

//------------------------------------------------------------------------------
/*Default constructor used to create n-dimensional arrays or with elements 
  bounded differently than in C (TODO: better description required)
 */
template <int SIZE>
TArrayDimT<SIZE>::TArrayDimT()
{
ASSERTE(SIZE > 0);
}

/*
 */
template <int SIZE>
TArrayDimT<SIZE>::TArrayDimT(int nCount1, //[in]     the number of elements in
                             //the first dimension of the array
                             int nCount2, //[in] = 0 the number of elements in
                             //the second dimension of the array
                             int nCount3  //[in] = 0 the number of elements in
                             //the third dimension of the array
                             )
{
switch(SIZE)
  {
  case 3:
    m_saBounds[2].lLbound   = 0;
    m_saBounds[2].cElements = nCount3;
  case 2:
    m_saBounds[1].lLbound   = 0;
    m_saBounds[1].cElements = nCount2;
  case 1:
    m_saBounds[0].lLbound   = 0;
    m_saBounds[0].cElements = nCount1;
    break;
  default:
    ASSERT(SIZE <= 3);
  }
}

//------------------------------------------------------------------------------
/*
 */
template <int SIZE>
TArrayDimT<SIZE>::operator SAFEARRAYBOUND* ()
{
return m_saBounds;
}

//------------------------------------------------------------------------------
/*
 * /
template <int SIZE> void
TArrayDimT<SIZE>::operator[](int index, long length)
{
ASSERT(index >= 0);
ASSERT(index < SIZE);
m_saBounds[index].cElements = length;
}

template <int SIZE> long
TArrayDimT<SIZE>::operator[](int index)
{
ASSERT(index >= 0);
ASSERT(index < SIZE);
return m_saBounds[index].cElements;
}
*/
////////////////////////////////////////////////////////////////////////////////
template <class TYPE, VARENUM vt, int SIZE>
class TSafeArray
{
public:
  TSafeArray();
  TSafeArray(SAFEARRAY* psa);
  TSafeArray(TSafeArrayDim<SIZE>& saDimension);
  ~TSafeArray();

  TSafeArray(const TSafeArray<TYPE, vt, SIZE>& src);
  TSafeArray<TYPE, vt, SIZE>& operator=(const TSafeArray<TYPE, vt, SIZE>& src);

  //TSAAccessorT<TYPE, SIZE> operator[] (int index);
  SAFEARRAY**        operator& ();

  long        get_BoundsLength(long idx) const;
  VARENUM     get_VarType() const;
  unsigned    get_Dimension() const;

  long        Elements();

  void        Attach(SAFEARRAY* psa);
  SAFEARRAY*  Detach();
  void        Destroy();

  //long BoundsLength[long idx] = { read=get_BoundsLength };

   VARENUM  VarType;//   = { read=get_VarType };
   unsigned Dimension;// = { read=get_Dimension };

protected:
  SAFEARRAY   *m_psa;

};

#define TSafeArrayT TSafeArray //Synonim


  #endif /*__BORLANDC__                                                      */
#endif /*__cplusplus*/
///////////////////////////////////////////////////////////////////////////////
#endif /* _KSAFEARRAY_H_                                                     */
/*****************************************************************************
 * $Log: KSafeArray.h,v $
 * Revision 1.2  2010/02/22 22:38:29  ddarko
 * SAFEARRAYBOUNDS
 *
 * Revision 1.1  2010/02/19 22:24:37  ddarko
 * Created
 *
 *****************************************************************************/
/*(c) Borland (see C++ Builder 5)
 */