/*$RCSfile: KSafeArray.h,v $: header file
  $Revision: 1.3 $ $Date: 2010/02/23 22:59:34 $
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

    See also: SAFEARRAY, TSafeArrayDim, TSafeArray.
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
  /*TODO: Description

    See also: SAFEARRAYBOUND, TSafeArrayDim, TSafeArray.
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
    #else
      #pragma TODO
    #endif
  #else //~__BORLANDC__

/*Represents the bounds of a multi-dimensional safe array.

  Parameters:
    - DIM number of dimensions of the safe array.

  Example:

      //Create 3D array
      const int DIM_3D = 3;
      TSafeArrayDim<DIM_3D> saDim(5, 6, 7);
      TSafeArray<double, VT_R8, DIM_3D> saDouble(saDim);

  See also: SAFEARRAYBOUND, SAFEARRAY, TSafeArray.
*/
template<int DIM>
class TSafeArrayDim
{
public:
  TSafeArrayDim<DIM>();
  TSafeArrayDim<DIM>(int nCount1, int nCount2 = 0, int nCount3 = 0);
  ~TSafeArrayDim<DIM>();

  operator SAFEARRAYBOUND* ();
  uint32_t& operator [](int iDimension);
  uint32_t  operator [](int iDimension) const;

public:
  SAFEARRAYBOUND m_saBounds[DIM]; //the bounds of the multi-dimensional safe array
};

#define TArrayDimT TSafeArrayDim //Bounds of a multi-dimensional safe array

///////////////////////////////////////////////////////////////////////////////
// Inlines

//------------------------------------------------------------------------------
/*Default constructor used to create n-dimensional arrays or with elements 
  bounded differently than in C (TODO: better description required)
 */
template <int DIM>
TSafeArrayDim<DIM>::TSafeArrayDim()
{
ASSERTE(DIM > 0);
}

/*
 */
template <int DIM>
TSafeArrayDim<DIM>::TSafeArrayDim(int nCount1, //[in]     the number of elements in
                             //the first dimension of the array
                             int nCount2, //[in] = 0 the number of elements in
                             //the second dimension of the array
                             int nCount3  //[in] = 0 the number of elements in
                             //the third dimension of the array
                             )
{
switch(DIM)
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
    ASSERT(DIM <= 3);
  }
}

/*Destructor
 */
template <int DIM>
TSafeArrayDim<DIM>::~TSafeArrayDim()
{
}

//------------------------------------------------------------------------------
/*Returns the bounds of a multi-dimensional safe array
 */
template <int DIM>
TSafeArrayDim<DIM>::operator SAFEARRAYBOUND* ()
{
return m_saBounds;
}

//------------------------------------------------------------------------------
/*
  Returns the number of elements in the multi-dimensional array for the given 
  dimension.
 */
template <int DIM>
uint32_t& TSafeArrayDim<DIM>::operator[](int iDimension //[in] 0-based index of array's
                                       //bound form the range [0, DIM)
                                      )
{
ASSERT(iDimension >= 0);
ASSERT(iDimension < DIM);
return *(uint32_t*)&m_saBounds[iDimension].cElements;
}

template <int DIM>
uint32_t TSafeArrayDim<DIM>::operator[](int iDimension //[in] 0-based index of array's
                                       //bound form the range [0, DIM)
                                      ) const
{
ASSERT(iDimension >= 0);
ASSERT(iDimension < DIM);
if ((iDimension >= 0) && (iDimension < DIM))
  return (uint32_t)m_saBounds[iDimension].cElements;
return 0;
}

////////////////////////////////////////////////////////////////////////////////
/*TODO: Description
  Parameters:
    - TYPE
    - VARTYPE variant type
    - DIM number of dimensions of the safe array.

  Examples:
      //Create different array types
      TSafeArray<LPDISPATCH, VT_DISPATCH, 1> saDispatch1;
      TSafeArray<LPUNKNOWN,  VT_UNKNOWN,  2> saUnknown2;
      TSafeArray<BSTR,       VT_BSTR,     3> saStr3;
      TSafeArray<double,     VT_R8,       1> saDouble;
      TSafeArray<long,       VT_I4,       1> saLong;
      TSafeArray<uint8_t,    VT_UI1,      1> saByte;
      //Create 2D matrix
      const int DIM_2D = 2;
      TSafeArrayDim<DIM_2D> saDim(9, 5); //Create 2D bounds
      TSafeArray<int, VT_I4, DIM_2D> intArray(saDim);
      ASSERT(intArray.Dimension == DIM_2D);
      //Initialize matrix
      for (int i=0; i < intArray.BoundsLength[0]; i++)
        for (int j=0; j < intArray.BoundsLength[1]; j++)
          intArray[i][j] = i*10 + j;


  See also: SAFEARRAYBOUND, TSafeArrayDim, SAFEARRAY.
 */
template <class TYPE, VARENUM VARTYPE, int DIM>
class TSafeArray
{
public:
  TSafeArray();
  TSafeArray(SAFEARRAY* psaSrc);
  TSafeArray(TSafeArrayDim<DIM>& saDimension);
  ~TSafeArray();

  TSafeArray(const TSafeArray<TYPE, VARTYPE, DIM>& saSrc);
  TSafeArray<TYPE, VARTYPE, DIM>& operator=(const TSafeArray<TYPE, VARTYPE, DIM>& saSrc);

public:
  VARENUM GetVarType(SAFEARRAY& saSrc) const;
  unsigned int GetDimension(SAFEARRAY& saSrc) const;
  unsigned int GetDimension() const;

  long        get_BoundsLength(long idx) const;
  long        Elements();
  void        Attach(SAFEARRAY* psaData);
  SAFEARRAY*  Detach();
  void        Destroy();

public:
  //TSAAccessorT<TYPE, DIM> operator[] (int index);
  SAFEARRAY**        operator& ();

protected:
  SAFEARRAY*   m_psaData; //data container describing the array
};

#define TSafeArrayT TSafeArray //TODO: Synonim description

///////////////////////////////////////////////////////////////////////////////
// Inlines

//------------------------------------------------------------------------------
/*
 */
template <class TYPE, VARENUM VARTYPE, int DIM>
TSafeArray<TYPE, VARTYPE, DIM>::TSafeArray() : 
  m_psaData(NULL)
{
}

template <class TYPE, VARENUM VARTYPE, int DIM>
TSafeArray<TYPE, VARTYPE, DIM>::TSafeArray(SAFEARRAY* psaSrc //[in]
                                          )
{
ASSERT(psaSrc != NULL);
if (psaSrc != NULL)
  {
  //Match the size and the type of the source and target
  if ((GetVarType(*psaSrc) == VARTYPE) &&
      (GetDimension(*psaSrc) == DIM))
    {
    m_psaData = psaSrc;
    }
  else
    m_psaData = NULL;
  }
}

/*Creates a new array descriptor, allocates and initializes the data for
  the array.
 */
template <class TYPE, VARENUM VARTYPE, int DIM>
TSafeArray<TYPE, VARTYPE, DIM>::TSafeArray(TSafeArrayDim<DIM>& saDimension //[in]
                                           //a vector of bounds difining the array
                                          )
{
#ifdef _WIN32
  m_psaData = ::SafeArrayCreate(VARTYPE,
                                DIM,
                                saDimension);
#else
  m_psaData = NULL;
  #pragma TODO
#endif
}

/*Copy constructor
 */
template <class TYPE, VARENUM VARTYPE, int DIM>
TSafeArray<TYPE, VARTYPE, DIM>::TSafeArray(const TSafeArray<TYPE, VARTYPE, DIM>& saSrc //[in]
                                          )
{
if (src.m_psaData != NULL)
  {
  #ifdef _WIN32
    /*Note: SafeArrayCopy() calls the string or variant manipulation
      functions if the array to copy contains either of these data types.
      If the array being copied contains object references, the reference 
      counts for the objects are incremented.
     */
    if(FAILED(::SafeArrayCopy(saSrc.m_psaData, &m_psaData)))
      {
      TRACE(_T("  SafeArrayCopy() failed!"));
      m_psaData = NULL;
      }
  #else
    m_psaData = NULL;
    #pragma TODO
  #endif
  }
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE, VARENUM VARTYPE, int DIM>
TSafeArray<TYPE, VARTYPE, DIM>::~TSafeArray()
{
  Destroy();
}

//template <class TYPE, VARENUM VARTYPE, int DIM> TSAAccessorT<TYPE, DIM>
//TSafeArray<TYPE, VARTYPE, DIM>::operator[] (int index)
//{
//  return TSAAccessorT<TYPE, DIM>(m_psaData, index);
//}

template <class TYPE, VARENUM VARTYPE, int DIM> SAFEARRAY** 
TSafeArray<TYPE, VARTYPE, DIM>::operator& ()
{
  OLECHECK(/* Only allow access to underlying pointer if null */ m_psaData == 0);
  return &m_psaData;
}

template <class TYPE, VARENUM VARTYPE, int DIM>
long TSafeArray<TYPE, VARTYPE, DIM>::get_BoundsLength(long idx) const
{
  _ASSERTE(idx >= 0);
  _ASSERTE(unsigned(idx) < Dimension);
  long len = 0;
  if (m_psaData)
  {
    long lb, ub;
    ::SafeArrayGetUBound(m_psaData, idx+1/*1-based*/, &ub);
    ::SafeArrayGetLBound(m_psaData, idx+1/*1-based*/, &lb);
    len = (ub-lb) + 1;
  }
  return len;
}

//-----------------------------------------------------------------------------
/*Returns the VARTYPE stored in the given safe array.
 */
template <class TYPE, VARENUM VARTYPE, int DIM>
VARENUM TSafeArray<TYPE, VARTYPE, DIM>::GetVarType(SAFEARRAY& saSrc //[in]
                                                   //a safe array descriptor
                  ) const
{
VARENUM evarResult = VT_NULL;
#if defined (WIN32)
  #if (__BORLANDC__ >= 0x500)
    #pragma option push -w-8104
  #endif //__BORLANDC__

  //type definition of function handling safe arrays
  typedef HRESULT (__stdcall* PFUNC_SAFEARRAY)(SAFEARRAY* psa, VARTYPE* pvt);
  //address of the procedure used to retreive VARTYPE
  //Note: not all versions of OleAut32.dll export SafeArrayGetVartype function!
  static PFUNC_SAFEARRAY SafeArrayGetVartypeProc = NULL;
  static HINSTANCE hOleAut32 = ::LoadLibrary(_T("oleaut32.dll"));
  if (hOleAut32 != NULL)
    {
    SafeArrayGetVartypeProc = ::GetProcAddress(hOleAut32, "SafeArrayGetVartype");
    if(SafeArrayGetVartypeProc!= NULL)
      {
      if(FAILED(SafeArrayGetVartypeProc(&saSrc, &evarResult)))
        {
        TRACE(_T("  OleAut32.dll: SafeArrayGetVartype() failed!\n"));
        }
      }
    else
      {
      TRACE(_T("  OleAut32.dll: SafeArrayGetVartype is not supported in current DLL version!\n"));
      //TODO: Lock & unclock
      if (saSrc.pvData != NULl)
        {
        VARIANT& varTemp = ((VARIANT*)saSrc.pvData)[0];
        evarResult = varTemp.vt;
        }
      }
    }
  else
    {
    TRACE(_T("  Failed to load OleAut32.dll!\n"));
    }
  #if (__BORLANDC__ >= 0x500)
    #pragma option pop
  #endif //__BORLANDC__
#endif
return evarResult;
}

//-----------------------------------------------------------------------------
/*Returns number of dimensions of the safe array.
 */
template <class TYPE, VARENUM VARTYPE, int DIM>
unsigned int TSafeArray<TYPE, VARTYPE, DIM>::GetDimension(SAFEARRAY& saSrc //[in]
                                                          //a safe array descriptor
                  ) const
{
#ifdef _WIN32
  return ::SafeArrayGetDim(&saSrc);
#else
  return saSrc.cDims;
#endif
}

template <class TYPE, VARENUM VARTYPE, int DIM>
unsigned int TSafeArray<TYPE, VARTYPE, DIM>::GetDimension() const
{
if(m_psaData != NULL)
  {
  return GetDimension(*m_psaData);
  }
return 0;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE, VARENUM VARTYPE, int DIM>
void TSafeArray<TYPE, VARTYPE, DIM>::Attach(SAFEARRAY *psa)
{
  if (m_psaData)
    Destroy();
  if (psa)
  {
    m_psaData = psa;
    /* Check that the SAFEARRAY we're attaching to is of a compatible VARENUM type & Dimension */
    _ASSERTE(VarType == VARTYPE);
    _ASSERTE(Dimension == DIM);
  }
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE, VARENUM VARTYPE, int DIM>
SAFEARRAY* TSafeArray<TYPE, VARTYPE, DIM>::Detach()
{
  SAFEARRAY *psa = m_psaData;
  m_psaData = 0;
  return psa;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE, VARENUM VARTYPE, int DIM>
void TSafeArray<TYPE, VARTYPE, DIM>::Destroy()
{
  if (m_psaData)
  {
    ::SafeArrayDestroy(m_psaData);
    m_psaData = 0;
  }
}


  #endif /*__BORLANDC__                                                      */
#endif /*__cplusplus*/
///////////////////////////////////////////////////////////////////////////////
#endif /* _KSAFEARRAY_H_                                                     */
/*****************************************************************************
 * $Log: KSafeArray.h,v $
 * Revision 1.3  2010/02/23 22:59:34  ddarko
 * TSafeArray
 *
 * Revision 1.2  2010/02/22 22:38:29  ddarko
 * SAFEARRAYBOUNDS
 *
 * Revision 1.1  2010/02/19 22:24:37  ddarko
 * Created
 *
 *****************************************************************************/
/*(c) Borland (see C++ Builder 5)
 */