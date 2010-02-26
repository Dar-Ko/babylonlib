/*$RCSfile: KSafeArray.h,v $: header file
  $Revision: 1.6 $ $Date: 2010/02/26 22:52:51 $
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

  typedef struct tagSAFEARRAY SAFEARRAY; //Safe array descriptor
  typedef SAFEARRAY* LPSAFEARRAY; //Pointer to safe array descriptor
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

//type definition of function geting safe array's type
typedef HRESULT (__stdcall* PFUNC_SAVARTYPE)(SAFEARRAY*, VARTYPE*);

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
    //Note: Visual Basic arrays start with index 0 (lLbound = 0)
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
    - TYPEVAR variant type
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
template <class TYPE, VARENUM TYPEVAR, int DIM>
class TSafeArray
{
public:
  TSafeArray();
  TSafeArray(SAFEARRAY* psaSrc);
  TSafeArray(TSafeArrayDim<DIM>& saDimension);
  ~TSafeArray();

  TSafeArray(const TSafeArray<TYPE, TYPEVAR, DIM>& saSrc);
  TSafeArray<TYPE, TYPEVAR, DIM>& operator=(const TSafeArray<TYPE, TYPEVAR, DIM>& saSrc);

public:
  bool    Destroy();
  VARENUM GetVarType(SAFEARRAY& saSrc) const;
  VARENUM GetVarType() const;
  unsigned int GetDimension(SAFEARRAY& saSrc) const;
  unsigned int GetDimension() const;
  unsigned int GetBoundsLength(const unsigned int nDimId) const;

  //long        Elements();
  bool        Attach(SAFEARRAY* psaData);
  SAFEARRAY*  Detach();

public:
  template <int DIM> class TSaIterator
    {
    protected:
      TSafeArray& m_saArray;
      unsigned int const m_nSize;
    public:
      TSaIterator(TSafeArray& saOwner, unsigned int nCount);
      TYPE& operator[] (int index);
    };
  TSaIterator<DIM> operator[] (int index);
  SAFEARRAY** operator&();

protected:
  SAFEARRAY*   m_psaData; //data container describing the array
};

#define TSafeArrayT TSafeArray //TODO: Synonim description

///////////////////////////////////////////////////////////////////////////////
// Inlines

//------------------------------------------------------------------------------
/*
 */
template <class TYPE, VARENUM TYPEVAR, int DIM>
TSafeArray<TYPE, TYPEVAR, DIM>::TSafeArray() :
  m_psaData(NULL)
{
}

template <class TYPE, VARENUM TYPEVAR, int DIM>
TSafeArray<TYPE, TYPEVAR, DIM>::TSafeArray(SAFEARRAY* psaSrc //[in]
                                          )
{
ASSERT(psaSrc != NULL);
if (psaSrc != NULL)
  {
  //Match the size and the type of the source and target
  if ((GetVarType(*psaSrc) == TYPEVAR) &&
      (GetDimension(*psaSrc) == DIM))
    {
    #ifdef _WIN32
      /*Note: SafeArrayCopy() calls the string or variant manipulation
        functions if the array to copy contains either of these data types.
        If the array being copied contains object references, the reference
        counts for the objects are incremented.
       */
      if(FAILED(::SafeArrayCopy(psaSrc, &m_psaData)))
        {
        TRACE(_T("  SafeArrayCopy() failed!\n"));
        m_psaData = NULL;
        }
    #else
      m_psaData = psaSrc; //Attach the source
      #pragma TODO //TODO: copy the source
    #endif
    }
  else
    {
    TRACE(_T("TSafeArray::TSafeArray(SAFEARRAY*)\n  Failure: Source and target are not compatible!\n"));
    m_psaData = NULL;
    }
  }
}

/*Creates a new array descriptor, allocates and initializes the data for
  the array.
 */
template <class TYPE, VARENUM TYPEVAR, int DIM>
TSafeArray<TYPE, TYPEVAR, DIM>::TSafeArray(TSafeArrayDim<DIM>& saDimension //[in]
                                           //a vector of bounds difining the array
                                          )
{
#ifdef _WIN32
  m_psaData = ::SafeArrayCreate(TYPEVAR,
                                DIM,
                                saDimension);
#else
  m_psaData = NULL;
  #pragma TODO
#endif
}

/*Copy constructor
 */
template <class TYPE, VARENUM TYPEVAR, int DIM>
TSafeArray<TYPE, TYPEVAR, DIM>::TSafeArray(const TSafeArray<TYPE, TYPEVAR, DIM>& saSrc //[in]
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
      TRACE(_T("  SafeArrayCopy() failed!\n"));
      m_psaData = NULL;
      }
  #else
    m_psaData = NULL;
    #pragma TODO
  #endif
  }
}

//-----------------------------------------------------------------------------
/*Destroys the array descriptor and all of the data in the array.
 */
template <class TYPE, VARENUM TYPEVAR, int DIM>
TSafeArray<TYPE, TYPEVAR, DIM>::~TSafeArray()
{
Destroy();
}

//-----------------------------------------------------------------------------
/*Destroys the safe array descriptor and all of the data in the array. If
  objects are stored in the array, Release is called on each object in the array.

  Returns true if the array is successfuly destroyed; otherwise returns false.
 */
template <class TYPE, VARENUM TYPEVAR, int DIM>
bool TSafeArray<TYPE, TYPEVAR, DIM>::Destroy()
{
TRACE(_T("TSafeArray::Destroy()\n"));
if (m_psaData != NULL)
  {
  #ifdef _WIN32
    HRESULT hResult = ::SafeArrayDestroy(m_psaData);
    switch(hResult)
      {
      case S_OK:
        m_psaData = NULL;
        return true;
        break;
      case DISP_E_ARRAYISLOCKED:
        TRACE(_T("  The array is currently locked.\n"));
        break;
      case E_INVALIDARG:
        TRACE(_T("  The item pointed to by m_psaData is not a safe array descriptor.\n"));
        break;
      default:
        TRACE(_T("  Failed to destroy the array.\n"));
      }
  #else
    #pragma TODO
  #endif
  }
return false;
}

//-----------------------------------------------------------------------------
/*Returns the address of the safe array descriptor.
 */
template <class TYPE, VARENUM TYPEVAR, int DIM> SAFEARRAY**
TSafeArray<TYPE, TYPEVAR, DIM>::operator& ()
{
return &m_psaData;
}

//-----------------------------------------------------------------------------
/*Returns subarray with number of dimensions decreased by one.
 */
template <class TYPE, VARENUM TYPEVAR, int DIM> TSAAccessorT<TYPE, DIM>
TSafeArray<TYPE, TYPEVAR, DIM>::operator[] (int index //[in]
                                           )
{
return TSaIterator<DIM>(m_psaData, index);
}

//-----------------------------------------------------------------------------
/*Returns the VARTYPE stored in the given safe array.
 */
template <class TYPE, VARENUM TYPEVAR, int DIM>
VARENUM TSafeArray<TYPE, TYPEVAR, DIM>::GetVarType(SAFEARRAY& saSrc //[in]
                                                   //a safe array descriptor
                                                  ) const
{
VARENUM evarResult = VT_EMPTY;

#if defined (WIN32)
  #if (__BORLANDC__ >= 0x500)
    #pragma option push -w-8104
  #endif //__BORLANDC__

  //address of the procedure used to retreive VARTYPE
  //Note: not all versions of OleAut32.dll export SafeArrayGetVartype function!
  static PFUNC_SAVARTYPE SafeArrayGetVartypeProc = NULL;
  static HINSTANCE hOleAut32 = ::LoadLibrary(_T("oleaut32.dll"));
  //FixMe: FreeLibrary(hOleAut32) at destructor; consider using CDllLoader class D.K.

  if (hOleAut32 != NULL)
    {
    SafeArrayGetVartypeProc = (PFUNC_SAVARTYPE)::GetProcAddress(hOleAut32,
                                                                "SafeArrayGetVartype");
    if(SafeArrayGetVartypeProc!= NULL)
      {
      if(FAILED(SafeArrayGetVartypeProc(&saSrc,
                                        reinterpret_cast<VARTYPE*>(&evarResult))))
        {
        TRACE(_T("  OleAut32.dll: SafeArrayGetVartype() failed!\n"));
        }
      /*Note: When Windows has a SAFEARRAY of type VT_DISPATCH with FADF_HAVEIID,
        it returns VT_UNKNOWN instead of VT_DISPATCH.
        Reference: atlcore.h: AtlSafeArrayGetActualVartype()
      */
      if(evarResult == VT_UNKNOWN)
        {
        if( (saSrc.fFeatures & FADF_HAVEIID) == FADF_HAVEIID) &&
            (saSrc.fFeatures & FADF_DISPATCH) == FADF_DISPATCH) )
          {
          evarResult = VT_DISPATCH;
          }
        }

      if ((saSrc.fFeatures & FADF_UNKNOWN) == FADF_UNKNOWN)
        {
        /*MSDN: SafeArrayGetVartype can sometimes fail to return VT_UNKNOWN
          for SAFEARRAY types that are based on IUnknown. Callers should
          additionally check whether the SAFEARRAY type's fFeatures field has
          the FADF_UNKNOWN flag set.
         */
        evarResult = VT_UNKNOWN;
        }

      }
    else
      {
      TRACE(_T("  OleAut32.dll: SafeArrayGetVartype is not supported in current DLL version!\n"));
      if(::FreeLibrary(hOleAut32))
        hOleAut32 = NULL;
      //TODO: Lock & unclock
      if (saSrc.pvData != NULL)
        {
        VARIANT& varTemp = ((VARIANT*)saSrc.pvData)[0];
        evarResult = static_cast<VARENUM>(varTemp.vt);
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

template <class TYPE, VARENUM TYPEVAR, int DIM>
VARENUM TSafeArray<TYPE, TYPEVAR, DIM>::GetVarType() const
{
if(m_psaData != NULL)
  {
  return GetVarType(*m_psaData);
  }
return VT_EMPTY;
}

//-----------------------------------------------------------------------------
/*Returns number of dimensions of the safe array.
 */
template <class TYPE, VARENUM TYPEVAR, int DIM>
unsigned int TSafeArray<TYPE, TYPEVAR, DIM>::GetDimension(SAFEARRAY& saSrc //[in]
                                                          //a safe array descriptor
                  ) const
{
#ifdef _WIN32
  return ::SafeArrayGetDim(&saSrc);
#else
  return saSrc.cDims;
#endif
}

template <class TYPE, VARENUM TYPEVAR, int DIM>
unsigned int TSafeArray<TYPE, TYPEVAR, DIM>::GetDimension() const
{
if(m_psaData != NULL)
  {
  return GetDimension(*m_psaData);
  }
return 0;
}

//-----------------------------------------------------------------------------
/*Returns the number of elements for specified dimension of the safe array.
 */
template <class TYPE, VARENUM TYPEVAR, int DIM>
unsigned int TSafeArray<TYPE, TYPEVAR, DIM>::GetBoundsLength(
                  const unsigned int nDimId //[in] 0-based index of array dimension
                                            //for which to get the number of elments
                                                            ) const
{
unsigned int nResult = 0;
if (m_psaData != NULL)
  {
  ASSERT(nDimId < GetDimension());
  #ifdef _WIN32
    long lLowerBound, lUpperBound;
    //Note: the array dimension id used by Component Automation is 1-based
    //sequential number.
    if(SUCCEEDED(::SafeArrayGetLBound(m_psaData, nDimId + 1, &lLowerBound)))
      if(SUCCEEDED(::SafeArrayGetUBound(m_psaData, nDimId + 1, &lUpperBound)))
        nResult = (lUpperBound - lLowerBound) + 1;
  #else
    #pragma TODO
  #endif
  }
return nResult;
}

//-----------------------------------------------------------------------------
/*Attaches the given safe array descriptor to this object.
 */
template <class TYPE, VARENUM TYPEVAR, int DIM>
bool TSafeArray<TYPE, TYPEVAR, DIM>::Attach(SAFEARRAY* psaNew //[in] the compatible
                                            //array descriptor to be attached
                                            )
{
if (psaNew != NULL)
  {
  if( (GetVarType(*psaNew) == TYPEVAR) &&
      (GetDimension(*psaNew) == DIM) )
    {
    if(Destroy())
      {
      m_psaData = psaNew;
      return true;
      }
    }
  }
return false;
}

//-----------------------------------------------------------------------------
/*Detaches safe array descriptor associated with this object and sets appropriate
  members to NULL.

  Returns safe array descriptor associated with the object.
 */
template <class TYPE, VARENUM TYPEVAR, int DIM>
SAFEARRAY* TSafeArray<TYPE, TYPEVAR, DIM>::Detach()
{
LPSAFEARRAY psaResult = m_psaData;
m_psaData = NULL;
return psaResult;
}

  #endif /*__BORLANDC__                                                      */
#endif /*__cplusplus*/
///////////////////////////////////////////////////////////////////////////////
#endif /* _KSAFEARRAY_H_                                                     */
/*****************************************************************************
 * $Log: KSafeArray.h,v $
 * Revision 1.6  2010/02/26 22:52:51  ddarko
 * *** empty log message ***
 *
 * Revision 1.5  2010/02/25 22:46:43  ddarko
 * Attach and detach
 *
 * Revision 1.4  2010/02/24 22:48:44  ddarko
 * *** empty log message ***
 *
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
/*(c) Borland (see C++ Builder 5, VCL, safearry.h)
 */