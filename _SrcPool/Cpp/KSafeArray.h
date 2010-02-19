/*$RCSfile: KSafeArray.h,v $: header file
  $Revision: 1.1 $ $Date: 2010/02/19 22:24:37 $
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

///////////////////////////////////////////////////////////////////////////////
/*
 */
struct tagSAFEARRAYBOUND
{
uint32_t cElements; //
int32_t  lLbound;   //
};

typedef struct tagSAFEARRAYBOUND SAFEARRAYBOUND;
#define SAFEARRAYBOUND SAFEARRAYBOUND

///////////////////////////////////////////////////////////////////////////////
/*
 */
struct tagSAFEARRAY
{
uint16_t cDims;       //
uint16_t fFeatures;   //
uint32_t cbElements;  //
uint32_t cLocks;     //
void* pvData;        //
SAFEARRAYBOUND rgsabound[1]; //
} SAFEARRAY;

typedef struct tagSAFEARRAY SAFEARRAY;
#define SAFEARRAY SAFEARRAY

///////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
  #if defined(__BORLANDC__) /*Borland C++ Compiler ver. 5.00 or greater*/
    #if __BORLANDC__ >= 0x500
      #include <safearry.h> //VCL template class TSafeArray
    #endif
  #else //~__BORLANDC__

#pragma TODO
/*The CArray class supports arrays that are are similar to C arrays, but can dynamically shrink and grow as necessary.

Array indexes always start at position 0. You can decide whether to fix the upper bound or allow the array to expand when you add elements past the current bound. Memory is allocated contiguously to the upper bound, even if some elements are null.

As with a C array, the access time for a CArray indexed element is constant and is independent of the array size.

Parameters:
  - TYPE the type of objects stored in the array.
  - ARG_TYPE argument type used to access objects stored in the array;
             default value is the reference to TYPE.
*/
template<int SIZE>
class TSafeArrayDim
{
public:
  TSafeArrayDim<SIZE>(int dim1Len);
  TSafeArrayDim<SIZE>(int dim1Len, int dim2Len);
  TSafeArrayDim<SIZE>(int dim1Len, int dim2Len, int dim3Len);

  operator SAFEARRAYBOUND* ();

  void  set_BoundsLength(int index, long length);
  long  get_BoundsLength(int index);

  long BoundsLength[int index] =
    { read = get_BoundsLength,
      write = set_BoundsLength };

protected:
  SAFEARRAYBOUND m_Bounds[DIM];
};

#define TArrayDimT TSafeArrayDim //Synonim


///////////////////////////////////////////////////////////////////////////////
// Inlines

//------------------------------------------------------------------------------
/*
 */

////////////////////////////////////////////////////////////////////////////////
template <class TYPE, VARENUM vt, int SIZE>
class TSafeArray
{
public:
  TSafeArrayT();
  TSafeArrayT(SAFEARRAY* psa);
  TSafeArrayT(TArrayDimT<SIZE>& dim);
  ~TSafeArrayT();

  TSafeArrayT(const TSafeArrayT<TYPE, vt, SIZE>& src);
  TSafeArrayT<TYPE, vt, SIZE>& operator=(const TSafeArrayT<TYPE, vt, SIZE>& src);

  TSAAccessorT<TYPE, SIZE> operator[] (int index);
  SAFEARRAY**        operator& ();

  long        get_BoundsLength(long idx) const;
  VARENUM     get_VarType() const;
  unsigned    get_Dimension() const;

  long        Elements();

  void        Attach(SAFEARRAY* psa);
  SAFEARRAY*  Detach();
  void        Destroy();

  long BoundsLength[long idx] = { read=get_BoundsLength };

   VARENUM  VarType   = { read=get_VarType };
   unsigned Dimension = { read=get_Dimension };

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
 * Revision 1.1  2010/02/19 22:24:37  ddarko
 * Created
 *
 *****************************************************************************/
/*(c) Borland (see C++ Builder 5)
 */