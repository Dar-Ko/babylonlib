/*$RCSfile: KSet.h,v $: header file
  $Revision: 1.2 $ $Date: 2011/03/14 06:56:32 $
  $Author: ddarko $

  A template for handling sets.
  Copyright: CommonSoft Inc
  D. Kolakovic   Nov 94
*/

#ifndef _KSET_H_
  //$RCSfile: KSet.h,v $ sentry
  #define _KSET_H_

#if _MSC_VER > 1000 /*Microsoft Visual Studio C/C++ compiler         */
  #pragma once
#endif // _MSC_VER > 1000

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

/* ///////////////////////////////////////////////////////////////////////// */
#ifdef __cplusplus

//erase! dk #include "simple.h"
#include "limits.h"
#include <iostream>
//#include "setx.h"

#ifdef __TURBOC__
  #pragma warn -sig
#endif

///////////////////////////////////////////////////////////////////////////////
/*Template ...

  Example:
      #include "KSet.h" //TSet template
      ...
*/
template <class TYPE> class TSet
{
public:
  TSet();
  TSet(const TSet<TYPE> &setValue);
  TSet(const TYPE* arrValue, size_t nCount);
  TSet(const TYPE& minValue, const TYPE& maxValue);
  virtual ~TSet();

public:
  void operator= (const TSet<TYPE>& setValue);
  unsigned int operator[] (const TYPE& setElement) const;
  TSet<TYPE> operator | (const TSet<TYPE>& setValue) const;
  void operator |= (const TSet<TYPE>& setValue);
  TSet<TYPE> operator & (const TSet<TYPE>& setValue) const;
  void operator &=(const TSet<TYPE>& setValue);
  TSet<TYPE> operator ^ (const TSet<TYPE>& setValue) const;
  void operator ^= (const TSet<TYPE>& setValue);
  TSet<TYPE> operator - (const TSet<TYPE>& setValue) const;
  void operator -= (const TSet<TYPE>& setValue);
  TSet<TYPE> operator ~ ();
  bool operator == (const TSet<TYPE>& setValue) const;
  bool operator !=(const TSet<TYPE>& setValue) const;

  void Incl(TYPE setElement);
  void Incl(const TYPE* arrValue, size_t nCount);
  void Excl(TYPE setElement);
  void Excl(const TYPE* arrValue, size_t nCount);
  void AllOn();
  void AllOff();
  bool Disjoint(const TSet<TYPE>& setValue) const;
  bool SubsetOf(const TSet<TYPE>& setValue) const;
  bool ProperSubsetOf(const TSet<TYPE>& setValue) const;
  bool IsNull();

  size_t Cardinality();

  friend std::ostream & operator <<
    (
    std::ostream & os,
    const TSet<TYPE> & s
    );

protected:
  void Calculate();
  void Allocate();
  void Copy
    (
    const TSet<TYPE> & s
    );
  void Destroy();
  static void CalcIdxOff
    (
    TYPE x,
    size_t & idx,
    unsigned int & off
    );

private:
  bool Bounded;  // is this set bounded?
  TYPE MinValue;     // minimum bit value
  TYPE MaxValue;     // maximum bit value
  TYPE Offset;       // offset first bit when bounded
  size_t Alloc;     // number of elements in Data
  size_t Bytes;     // number of bytes in Data
  size_t Count;     // number of elements in set
  unsigned int* Data;// array of set bits
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*Default constructor
 */
template <class TYPE>
inline TSet<TYPE>::TSet()
{
Bounded  = false;

Calculate();
Allocate();
}

template <class TYPE>
inline TSet<TYPE>::TSet(const TSet<TYPE> &setValue //[in]
                        )
{
Copy(s);
}

template <class TYPE>
TSet<TYPE>::TSet(const TYPE* arrValue, //[in]
                const size_t nCount   //[in]
                )
{
Bounded  = false;

Calculate();
Allocate();
Incl(array,no);
}

template <class TYPE>
TSet<TYPE>::TSet(const TYPE& minValue, //[in]
                 const TYPE& maxValue  //[in]
                )
{
// swap min and max, if necessary
if (max < min)
  {
  T temp = max;
  max = min;
  min = temp;
  }

Bounded  = true;
MinValue = min;
MaxValue = max;

Calculate();
Allocate();
}

template <class TYPE>
TSet<TYPE>::~TSet()
{
Destroy();
}

//-----------------------------------------------------------------------------
/*Assignment operator
 */
template <class TYPE>
inline void TSet<TYPE>::operator =(const TSet<TYPE>& setValue //[in]
                                  )
{
Destroy();
Copy(s);
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
unsigned int TSet<TYPE>::operator [](const TYPE& setElement //[in]
                                    ) const
{
if (Bounded)
  {
  if ((x <= MaxValue) && (x >= MinValue))
    x = (T)(x - Offset);
  else
    throw SetEx(SX_BOUNDS);
  }

size_t idx;
unsigned int off;

CalcIdxOff(setElement,idx,off);

return Data[idx] & off;
}


//-----------------------------------------------------------------------------
/*
 */
// union operators
template <class TYPE>
  TSet<TYPE> TSet<TYPE>::operator |
    (
    const TSet<TYPE> & s
    )
    const
{
if (Alloc != s.Alloc)
  throw SetEx(SX_MISMATCH);

TSet<TYPE> result(*this);

for (size_t n = 0; n < Alloc; ++n)
  result.Data[n] |= s.Data[n];

return result;
}

template <class TYPE>
  void TSet<TYPE>::operator |=
    (
    const TSet<TYPE> & s
    )
{
if (Alloc != s.Alloc)
  throw SetEx(SX_MISMATCH);

for (size_t n = 0; n < Alloc; ++n)
    Data[n] |= s.Data[n];
}

//-----------------------------------------------------------------------------
/*
 */
// intersection operators
template <class TYPE>
  TSet<TYPE> TSet<TYPE>::operator &
    (
    const TSet<TYPE> & s
    )
    const
{
if (Alloc != s.Alloc)
  throw SetEx(SX_MISMATCH);

TSet<TYPE> result(*this);

for (size_t n = 0; n < Alloc; ++n)
  result.Data[n] &= s.Data[n];

return result;
}

template <class TYPE>
  void TSet<TYPE>::operator &=
    (
    const TSet<TYPE> & s
    )
{
if (Alloc != s.Alloc)
  throw SetEx(SX_MISMATCH);

for (size_t n = 0; n < Alloc; ++n)
  Data[n] &= s.Data[n];
}

//-----------------------------------------------------------------------------
/*
 */
// exclusive or operators
template <class TYPE>
  TSet<TYPE> TSet<TYPE>::operator ^
    (
    const TSet<TYPE> & s
    )
    const
{
if (Alloc != s.Alloc)
  throw SetEx(SX_MISMATCH);

TSet<TYPE> result(*this);

for (size_t n = 0; n < Alloc; ++n)
  result.Data[n] ^= s.Data[n];

return result;
}

template <class TYPE>
  void TSet<TYPE>::operator ^=
    (
    const TSet<TYPE> & s
    )
{
if (Alloc != s.Alloc)
  throw SetEx(SX_MISMATCH);

for (size_t n = 0; n < Alloc; ++n)
  Data[n] ^= s.Data[n];
}

//-----------------------------------------------------------------------------
/*
 */
// difference operators
template <class TYPE>
  TSet<TYPE> TSet<TYPE>::operator -
    (
    const TSet<TYPE> & s
    )
    const
{
if (Alloc != s.Alloc)
  throw SetEx(SX_MISMATCH);

TSet<TYPE> result(*this);

for (size_t n = 0; n < Alloc; ++n)
  result.Data[n] &= ~s.Data[n];

return result;
}

template <class TYPE>
  void TSet<TYPE>::operator -=
    (
    const TSet<TYPE> & s
    )
{
if (Alloc != s.Alloc)
  throw SetEx(SX_MISMATCH);

for (size_t n = 0; n < Alloc; ++n)
  Data[n] &= ~s.Data[n];
}

//-----------------------------------------------------------------------------
/*
 */
// complement operator
template <class TYPE>
  TSet<TYPE> TSet<TYPE>::operator ~ ()
{
TSet<TYPE> result(*this);

for (size_t n = 0; n < Alloc; ++n)
  result.Data[n] = ~result.Data[n];

return result;
}

//-----------------------------------------------------------------------------
/*
 */
// comparison operator
template <class TYPE>
  bool TSet<TYPE>::operator ==
    (
    const TSet<TYPE> & s
    )
    const
{
if (Alloc != s.Alloc)
  throw SetEx(SX_MISMATCH);

for (size_t n = 0; n < Alloc; ++n)
  {
  if (Data[n] != s.Data[n])
    return false;
  }

return true;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
  bool TSet<TYPE>::operator !=
    (
    const TSet<TYPE> & s
    )
    const
{
if (Alloc != s.Alloc)
  throw SetEx(SX_MISMATCH);

for (size_t n = 0; n < Alloc; ++n)
  {
  if (Data[n] != s.Data[n])
    return true;
  }

return false;
}

//-----------------------------------------------------------------------------
/*
 */
// include and exclude members
template <class TYPE>
  void TSet<TYPE>::Incl
    (
    TYPE x
    )
{
if (Bounded)
  {
  if ((x <= MaxValue) && (x >= MinValue))
    x = (TYPE)(x - Offset);
  else
    throw SetEx(SX_BOUNDS);
  }

size_t idx;
unsigned int off;

CalcIdxOff(x,idx,off);

if (!(Data[idx] & off))
  {
  ++Count;
  Data[idx] |= off;
  }
}

template <class TYPE>
  void TSet<TYPE>::Incl
    (
    const TYPE * array,
    size_t no
    )
{
for (size_t i = 0; i < no; ++i)
  Incl(array[i]);
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
  void TSet<TYPE>::Excl
    (
    TYPE x
    )
{
if (Bounded)
  {
  if ((x <= MaxValue) && (x >= MinValue))
    x = (TYPE)(x - Offset);
  else
    throw SetEx(SX_BOUNDS);
  }

size_t idx;
unsigned int off;

CalcIdxOff(x,idx,off);

if (Data[idx] & off)
  {
  --Count;
  Data[idx] &= ~off;
  }
}

template <class TYPE>
  void TSet<TYPE>::Excl
    (
    const TYPE * array,
    size_t no
    )
{
for (size_t i = 0; i < no; ++i)
  Excl(array[i]);
}

//-----------------------------------------------------------------------------
/*
 */
// turn all members on or off
template <class TYPE>
  inline void TSet<TYPE>::AllOn()
{
memset(Data,'\xff',Bytes);

if (Bounded)
  Count = size_t(MaxValue - MinValue + 1);
else
  Count = size_t((1ul << (sizeof(TYPE) * CHAR_BIT)) - 1);
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
  inline void TSet<TYPE>::AllOff()
{
memset(Data,0,Bytes);

Count = 0;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
  bool TSet<TYPE>::Disjoint
    (
    const TSet<TYPE> & s
    )
    const
{
if (Alloc != s.Alloc)
  throw SetEx(SX_MISMATCH);

for (size_t n = 0; n < Alloc; ++n)
  {
  if (Data[n] & s.Data[n])
    return false;
  }

return true;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
  bool TSet<TYPE>::SubsetOf
    (
    const TSet<TYPE> & s
    )
    const
{
if (Alloc != s.Alloc)
  throw SetEx(SX_MISMATCH);

if (Count > s.Count)
  return false;

for (size_t n = 0; n < Alloc; ++n)
  {
  if (Data[n] != (Data[n] & s.Data[n]))
    return false;
  }

return true;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
  bool TSet<TYPE>::ProperSubsetOf
    (
    const TSet<TYPE> & s
    )
    const
{
if (Alloc != s.Alloc)
  throw SetEx(SX_MISMATCH);

if (s.Count <= Count)
  return false;

for (size_t n = 0; n < Alloc; ++n)
  {
  if (Data[n] != (Data[n] & s.Data[n]))
    return false;
  }

return true;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
  bool TSet<TYPE>::IsNull()
{
if (Count == 0)
  return true;
else
  return false;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
inline void TSet<TYPE>::Calculate()
{
unsigned long bits;

if (Bounded)
  {
  Offset = MinValue;
  bits = MaxValue - MinValue + CHAR_BIT;
  }
else
  {
  bits = 1ul << (sizeof(TYPE) * CHAR_BIT);
  }

Bytes = (size_t)(bits  / (unsigned long)CHAR_BIT);

if (Bytes <= sizeof(unsigned int))
  Alloc = 1;
else
  Alloc = Bytes / sizeof(unsigned int);
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
inline void TSet<TYPE>::Allocate()
{
Data = new unsigned int [Alloc];

if (Data == NULL)
  throw SetEx(SX_ALLOC);

AllOff();
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
  void TSet<TYPE>::Copy
    (
    const TSet<TYPE> & s
    )
{
Bounded  = s.Bounded;
MinValue = s.MinValue;
MaxValue = s.MaxValue;
Offset   = s.Offset;
Bytes  = s.Bytes;
Alloc  = s.Alloc;

Allocate();

Count  = s.Count;

for (size_t n = 0; n < Alloc; ++n)
  Data[n] = s.Data[n];
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
  inline void TSet<TYPE>::Destroy()
{
delete [] Data;
Count = 0;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
  inline void TSet<TYPE>::CalcIdxOff
    (
    TYPE x,
    size_t & idx,
    unsigned int & off
    )
{
idx = x / TYPE(sizeof(unsigned int) * CHAR_BIT);

off = 1u << (unsigned int)((x - (idx *
          sizeof(unsigned int) * CHAR_BIT)));

}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
   inline size_t TSet<TYPE>::Cardinality()
{
return Count;
}

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
  std::ostream & operator <<
    (
    std::ostream & os,
    const TSet<TYPE> & s
    )
    {
    size_t bits = sizeof(unsigned int) * CHAR_BIT;

    for (size_t i = 0; i < s.Alloc; ++i)
      {
      for (size_t n = 0; n < bits; ++n)
        os << ((s.Data[i] & (1 << n)) ? '1' : '0');

      os << ' ';
      }

    return os;
    }

#ifdef __TURBOC__
  #pragma warn .sig
#endif

///////////////////////////////////////////////////////////////////////////////
#endif /* __cplusplus                                                        */
/* ///////////////////////////////////////////////////////////////////////// */
#endif // _KSET_H_
/******************************************************************************
* $Log: KSet.h,v $
* Revision 1.2  2011/03/14 06:56:32  ddarko
* *** empty log message ***
*
* Revision 1.1  2011/03/13 07:10:47  ddarko
* MSVC 2008 v9
*
*****************************************************************************/
#ifdef TODONRE
/*http://www.osl.iu.edu/research/mtl/reference/html/Vector.html
Description  
Not to be confused with the std::vector class. The MTL Vector concept is a Container in which every element has a corresponding index. The elements do not have to be sorted by their index, and the indices do not necessarily have to start at 0. Also the indices do not have to form a contiguous range. The iterator type must be a model of IndexedIterator. Vector is not a refinement of RandomAccessContainer (even though Vector defines operator[]) because Vector does not guarantee amortized constant time for that operation (to allow fo sparse vectors). Note also that the invariant a[n] == advance(A.begin(), n) that applies to RandomAccessContainer does not apply to Vector, since the a[i] is defined for Vector to return the element with the ith index. So a[n] == *i if and only if i.index() == n. The indices of the elements in the subrange remain the same. For example, here is a vector written in terms of index-value pairs: x = [ (0,2), (1,5), (2,3), (3,1), (4,9) ] The subrange [1,3) of x can be obtained with y = x(1,3) which results in y = [ (1,5), (2,3) ] The subrange vector is a reference to a particular portion of the original vector. If you wish to have the subrange vector's starting index to be zero just do the following: y = x(1,3).adjust_index(-1); The adjust_index(delta) function does not affect the indexing of the original vector.  
 
template <class Vector, class T> inline
void
oned_set(Vector x, const T& alpha, fast::count<0>)
{
  mtl_algo::fill(x.begin(), x.end(), alpha);
}
#if USE_BLAIS
template <int N, class Vector, class T> inline
void
oned_set(Vector x, const T& alpha, fast::count<N>)
{
  fast::fill(x.begin(), fast::count<N>(), alpha);
}
#endif //USE_BLAIS
template <class Vector, class T> inline
void
set__(Vector x, const T& alpha, oned_tag)
{
  oned_set(x, alpha, dim_n<Vector>::RET());
}


//: For use in deciding whether to do static algorithm
//!noindex:
template <class Vector>
class dim_n {
public:
#if USE_BLAIS
  enum { N = (0 < Vector::N && Vector::N <= 15 ? Vector::N : 0) };
  typedef fast::count<N> RET;
#else
  typedef fast::count<0> RET;
#endif
};
//
// $COPYRIGHT$
//
//===========================================================================

#ifndef MTL_LINALG_VECTOR_H
#define MTL_LINALG_VECTOR_H


#include <utility>
#include <vector>

#include "mtl/refcnt_ptr.h"
#include "mtl/dense_iterator.h"
#include "mtl/reverse_iter.h"
#include "mtl/light1D.h"
#include "mtl/mtl_config.h"
#include "mtl/matrix_traits.h"
#include "mtl/scaled1D.h"
#include "mtl/mtl_exception.h"
//#include "mtl/external_vector.h"

#include "mtl/mxtl_expr.h"

namespace mtl {

  //: Linalg Vector Adaptor
  //!category: containers, adaptors
  //!component: type
  //
  // This class is obsolete and not used.
  //
  //!definition: linalg_vector.h
  //!tparam: RepType - the underlying representation
  //!models: Linalg_Vector

template <class RepType, class RepPtr = RepType*, int NN = 0>
class linalg_vec {
public:
  typedef linalg_vec self;
  typedef RepType rep_type;
  typedef RepPtr rep_ptr;

  enum { N = NN };

  /**@name Type Definitions */

  /*  enum { dimension = 1 }; */
  typedef oned_tag dimension;

  //: The sparsity tag
  typedef dense_tag sparsity;

  //: The value type
  //!wheredef: Container
  typedef typename rep_type::value_type value_type;

  //: The reference type
  //!wheredef: Container
  typedef typename rep_type::reference reference;

  //: The const reference type
  //!wheredef: Container
  typedef typename rep_type::const_reference const_reference;

  //: The pointer (to the value_type) type
  //!wheredef: Container
  typedef typename rep_type::pointer pointer;

  //: The size type (non negative)
  //!wheredef: Container
  typedef typename rep_type::size_type size_type;

  //: The difference type (an integral type)
  //!wheredef: Container
  typedef typename rep_type::difference_type difference_type;

#if !defined( _MSVCPP_ )
  //: The iterator type
  //!wheredef: Container
  typedef dense_iterator<typename rep_type::iterator> iterator;

  //: The const iterator type
  //!wheredef: Container
  typedef dense_iterator<typename rep_type::const_iterator> const_iterator;
#else
  typedef dense_iterator<typename rep_type::value_type, 0, 0, size_type> iterator;
  typedef dense_iterator<typename rep_type::value_type, 1, 0, size_type> const_iterator;
#endif
  //: The reverse iterator type
  //!wheredef: Reversible Container
  typedef reverse_iter<iterator> reverse_iterator;

  //: The const reverse iterator type
  //!wheredef: Reversible Container
  typedef reverse_iter<const_iterator> const_reverse_iterator;

  /* skip over the zeros and report the indices
     this implements the nonzero structure array
     */
  typedef linalg_vec<RepType, RepPtr, NN> Vec;

  typedef size_type Vec_size_type;
  typedef difference_type Vec_difference_type;
  typedef iterator Vec_iterator;
  typedef const_iterator Vec_const_iterator;

  //: blah
  //!noindex:
  class IndexArray {
  public:

    typedef Vec_size_type size_type;
    typedef Vec_difference_type difference_type;
    typedef Vec_size_type value_type;

    //: blah
    //!noindex:
    class iterator {
    public:
      typedef size_type value_type;
      typedef size_type reference;
      typedef size_type* pointer;
      typedef Vec_difference_type difference_type;
      typedef typename std::iterator_traits<Vec_iterator>::iterator_category iterator_category;
      iterator(Vec_iterator iter, Vec_iterator e) : i(iter), end(e) {
	while (*i == Vec_value_type(0)) ++i;
      }
      reference operator*() const { return i.index(); }
      iterator& operator++() { 
	++i; while (*i == Vec_value_type(0) && i != end) ++i;
	return *this; }
      iterator operator++(int) { iterator t = *this; ++(*this); return t; }
      iterator& operator--() { 
	--i; while (*i == Vec_value_type(0) && i != end) --i;
	return *this; }
      iterator operator--(int) { iterator t = *this; --(*this); return t; }
      difference_type operator-(const iterator& x) const { return i - x.i; }
      bool operator==(const iterator& x) const { return i == x.i; }
      bool operator!=(const iterator& x) const { return i != x.i; }
      bool operator<(const iterator& x) const { return i < x.i; }
      Vec_iterator i;
      Vec_iterator end;
    };

    //: blah
    //!noindex:
    class const_iterator {
    public:
      typedef size_type value_type;
      typedef size_type reference;
      typedef size_type* pointer;
      typedef Vec_difference_type difference_type;
      typedef typename std::iterator_traits<Vec_iterator>::iterator_category iterator_category;
      const_iterator(Vec_const_iterator iter, Vec_const_iterator e)
	: i(iter), end(e) { 
	while (*i == Vec_value_type(0) && i != end) ++i;
      }
      reference operator*() const { return i.index(); }
      const_iterator& operator++() { 
	++i; while (*i == Vec_value_type(0) && i != end) ++i;
	return *this; }
      const_iterator operator++(int) { 
	const_iterator t = *this; ++(*this); return t; }
      const_iterator& operator--() { 
	--i; while (*i == Vec_value_type(0)) --i;
	return *this; }
      const_iterator operator--(int) { 
	const_iterator t = *this; --(*this); return t; }
      difference_type operator-(const const_iterator& x) const { 
	return i - x.i; }
      bool operator==(const const_iterator& x) const { return i == x.i; }
      bool operator!=(const const_iterator& x) const { return i != x.i; }
      bool operator<(const const_iterator& x) const { return i < x.i; }
      Vec_const_iterator i;
      Vec_const_iterator end;
    };

    inline IndexArray(const Vec& v) : vec((Vec*)&v) { }
    inline iterator begin() { return iterator(vec->begin(), vec->end()); }
    inline iterator end() { return iterator(vec->end(), vec->end()); }
    inline const_iterator begin() const{ 
      return const_iterator(((const Vec*)vec)->begin(), 
			    ((const Vec*)vec)->end()); 
    }
    inline const_iterator end() const { 
      return const_iterator(((const Vec*)vec)->end(), 
			    ((const Vec*)vec)->end()); }

    size_type size() const {
      size_type s = 0;
      Vec_const_iterator i;
      for (i = ((const Vec*)vec)->begin(); i != ((const Vec*)vec)->end(); ++i)
	if (*i != Vec_value_type(0)) ++s;
      return s;
    }

    Vec* vec;
  };

  //: The type for an array of the indices of the element in the vector
  //!wheredef: Vector
  typedef IndexArray IndexArrayRef;

  //: The type for a subrange vector-view of the original vector  
  //!wheredef: Vector
  typedef light1D<value_type> subrange_type;

  typedef std::pair<size_type, size_type> range;

  /**@name Constructors */
  
  //: Default Constructor (allocates the container)
  //!wheredef: Container
  inline linalg_vec() : rep(0) { }

  //: Normal Constructor
  inline linalg_vec(rep_ptr x, size_type start_index)
    : rep(x), first(start_index) { }

  //: Copy Constructor  (shallow copy)
  //!wheredef: ContainerRef
  inline linalg_vec(const self& x) : rep(x.rep), first(x.first) { }

  //: The destructor.
  //!wheredef: Container
  inline ~linalg_vec() { }  

  //: Assignment Operator (shallow copy)
  //!wheredef: AssignableRef
  inline self& operator=(const self& x) { 
    rep = x.rep;
    first = x.first;
    return *this; 
  }

  /**@name Access Methods */
  
  /**@name Iterator Access Methods */
  
  //: Return an iterator pointing to the beginning of the vector
  //!wheredef: Container
  inline iterator begin() { return iterator(rep->begin(), 0, first); }
  //: Return an iterator pointing past the end of the vector
  //!wheredef: Container
  inline iterator end() { return iterator(rep->begin(), rep->size(), first); }
  //: Return a const iterator pointing to the begining of the vector
  //!wheredef: Container
  inline const_iterator begin() const { return const_iterator(rep->begin(), 
							      0, first); }
  //: Return a const iterator pointing past the end of the vector
  //!wheredef: Container
  inline const_iterator end() const{ return const_iterator(rep->begin(),
						       rep->size(), first); }
  //: Return a reverse iterator pointing to the last element of the vector
  //!wheredef: Reversible Container
  inline reverse_iterator rbegin() { return reverse_iterator(end()); }
  //: Return a reverse iterator pointing past the end of the vector
  //!wheredef: Reversible Container
  inline reverse_iterator rend() { return reverse_iterator(begin()); }
  //: Return a const reverse iterator pointing to the last element of the vector
  //!wheredef: Reversible Container
  inline const_reverse_iterator rbegin() const { 
    return reverse_iterator(end()); }
  //: Return a const reverse iterator pointing past the end of the vector
  //!wheredef: Reversible Container
  inline const_reverse_iterator rend() const{ 
    return reverse_iterator(begin()); }
  
  /**@name Element Access Methods */
  

  //: Return a reference to the element with the ith index
  //!wheredef: Vector
  inline reference operator[](size_type i) MTL_THROW_ASSERTION {
    MTL_ASSERT(i < size(), "linalg_vec::operator[]");
    return (*rep)[i - first];
  }

  inline subrange_type operator()(range r) MTL_THROW_ASSERTION {
    return subrange_type(data() + r.first, r.second - r.first);
  }
  inline subrange_type operator()(size_type s, size_type f)
    MTL_THROW_ASSERTION 
  {
    return subrange_type(data() + s, f - s);
  }

  //: Return a const reference to the element with the ith index
  //!wheredef: Vector
  inline const_reference operator[](size_type i) const MTL_THROW_ASSERTION {
    MTL_ASSERT(i < size(), "linalg_vec::operator[]");
    return (*rep)[i - first];
  }

  
  /**@name Size Methods */
    
  //: The size of the vector
  //!wheredef: Container  
  inline size_type size() const { return rep->size(); }
  //: The number of non-zeroes in the vector
  inline size_type nnz() const { return rep->size(); }
  //: Resize the vector to n
  inline void resize(size_type n) { rep->resize(n); }
  //: Resize the vector to n, and assign x to the new positions
  inline void resize(size_type n, const value_type& x) { rep->resize(n, x); }
  //: Return the total capacity of the vector
  size_type capacity() const { return rep->capacity(); }

  //: Reserve more space in the vector
  void reserve(size_type n) { rep->reserve(n); }

  //: Raw Memory Access
  inline const value_type* data() const { return &(*rep)[0]; }

  //: Raw Memory Access
  inline value_type* data() { return &(*rep)[0]; }

  //: Insert x at the indicated position in the vector
  //!wheredef: Container
  inline iterator 
  insert (iterator position, const value_type& x = value_type()) {
    return iterator(rep->insert(position.base(), x), position.index()+1);
    /* JGS, not sure about what to do with the index here */
  }  

  inline IndexArrayRef nz_struct() const { return IndexArrayRef(*this); }

  inline self& adjust_index(size_type i) { 
    first += i; 
    return *this; 
  }

protected:

  rep_ptr rep;
  size_type first;
};


//: External 1-D Container
//!category: containers
//!component: type
//
// This is similar to dense1D, except that the memory is provided
// by the user. This allows for interoperability with other array
// packages and even with Fortran.
//
//!definition: linalg_vec.h
//!tparam: T - The element type.
//!tparam: NN - The static size of the Vector, 0 if dynamic size
//!tparam: SizeT - The size type to use - size_t
//!tparam: DiffT - ptrdiff_t
//!models: Vector
//!example: dot_prod.cc, apply_givens.cc, euclid_norm.cc, max_index.cc

template <class T, int NN = 0, class SizeType=unsigned int, class Orien = column_tag>
class external_vec : public mxtl_expr< external_vec<T,NN,SizeType> > {
  typedef external_vec self;
public:
  enum { N = NN, SIZE = NN };

  typedef Orien orientation;

  typedef external_vec<T,NN,SizeType,
    typename orien_trans<Orien>::tag> transpose_type;

  typedef external_vec<int> IndexArray; /* JGS */

  /* Type Definitions */

  //: The vector is dense
  typedef dense_tag sparsity;

  typedef SizeType size_type;
  typedef int difference_type;

  //: The element type
  typedef T value_type;
  //: The reference to the value type
  typedef T& reference;
  //: The pointer ot the value type
  typedef T* pointer;
  typedef const T* const_pointer;
  //: The const reference type
  typedef const T& const_reference;
#if !defined( _MSVCPP_)
  //: The iterator type
  typedef dense_iterator<T*,0,size_type> iterator;
  //: The const iterator type
  typedef dense_iterator<const T*,0,size_type> const_iterator;
#else
  typedef dense_iterator<T, 0, 0, size_type> iterator;
  typedef dense_iterator<T, 1, 0, size_type> const_iterator;
#endif
  //: The reverse iterator type
  typedef reverse_iter<iterator> reverse_iterator;
  //: The const reverse iterator type
  typedef reverse_iter<const_iterator> const_reverse_iterator;

  //:
  //!wheredef: Vector
  typedef self IndexArrayRef;

  //: The type for the subrange vector
  //!wheredef: Vector
  typedef self subrange_type;

  typedef std::pair<size_type, size_type> range;

  //: This is a 1D container
  typedef oned_tag dimension;

  /* Constructors */
  //: Default Constructor
  inline external_vec() : rep(0), size_(0), first(0) { }

  //: External Data Contructor
  inline external_vec(T* data)
    : rep(data), size_(N), first(0) { }

  //: Preallocated Memory Constructor with optional non-zero starting index
  inline external_vec(T* data, size_type n, size_type start = 0)
    : rep(data), size_(n), first(start) { }

  //: Copy Constructor
  inline external_vec(const self& x)
    : rep(x.rep), size_(x.size_), first(x.first) { }

  //: Assignment
  inline self& operator=(const self& x) {
    rep = x.rep; size_ = x.size_; first = x.first; return *this;
  }

  template <class RHS_>
  inline self& operator=(const Expression<RHS_>& rhs) { 
    typedef Expression<RHS_> RHS;
    typedef typename CreateLeaf<RHS>::Leaf_t Leaf_t;
    evaluate(*this, OpAssign(),
	     MakeReturn<Leaf_t>::make(CreateLeaf<RHS>::make(rhs)));
    return *this; 
  }

  //: Destructor
  inline ~external_vec() { }

  /* Access Methods */

  /* Iterator Access Methods */

  //: Return an iterator pointing to the beginning of the vector
  //!wheredef: Container
  inline iterator begin() { return iterator(rep, 0, first); }
  //: Return an iterator pointing past the end of the vector
  //!wheredef: Container
  inline iterator end() { return iterator(rep, size(), first); }
  //: Return a const iterator pointing to the begining of the vector
  //!wheredef: Container
  inline const_iterator begin() const {
    return const_iterator(rep, 0, first); 
  }
  //: Return a const iterator pointing past the end of the vector
  //!wheredef: Container
  inline const_iterator end() const{
    return const_iterator(rep, size(), first); 
  }
  //: Return a reverse iterator pointing to the last element of the vector
  //!wheredef: Reversible Container
  inline reverse_iterator rbegin() {
    return reverse_iterator(end());
  }
  //: Return a reverse iterator pointing past the end of the vector
  //!wheredef: Reversible Container
  inline reverse_iterator rend() { return reverse_iterator(begin()); }
  //: Return a const reverse iterator pointing to the last element of the vector
  //!wheredef: Reversible Container
  inline const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end()); 
  }
  //: Return a const reverse iterator pointing past the end of the vector
  //!wheredef: Reversible Container
  inline const_reverse_iterator rend() const{ 
    return const_reverse_iterator(begin()); 
  }

  /* Element Access Methods */

  //: Return a reference to the element with the ith index
  //!wheredef: Vector
  inline reference operator[](size_type i) { return rep[i - first]; }
  //: Return a const reference to the element with the ith index
  //!wheredef: Vector
  inline const_reference operator[](size_type i) const { return rep[i - first]; }
  //: Return a subrange vector with start at s and finish at f
  //!wheredef: Vector
  inline subrange_type operator()(size_type s, size_type f) const {
    return subrange_type(rep + s - first, f - s, s);
  }

  inline subrange_type operator()(range r) MTL_THROW_ASSERTION {
    return subrange_type(data() + r.first, r.second - r.first);
  }

  /* Size Methods */
  //: The size of the vector
  //!wheredef: Container
  inline size_type size() const { return N ? N : size_; }

  //: The number of non-zeroes in the vector
  //!wheredef: Vector
  inline size_type nnz() const { return size(); }

  //: Resize the vector to size n
#if 0
  inline void resize(size_type n) {
    if (rep) delete [] rep;
    size_ = n;
    rep = new T[size_];
  }
#else
  inline void resize(size_type n) { size_ = n; }
  inline void clear() { size_ = 0; }
#endif

  //:  Raw Memory Access
  inline value_type* data() const { return rep; }

  inline self& adjust_index(size_type i) { 
    first += i; 
    return *this; 
  }

  //: Push x onto the end of the vector, increasing the size
  // This function does not allocation memory. 
  // Better hope enough memory is already there!
  void push_back(const T& x) {
    rep[size_] = x;
    ++size_;
  }

protected:
  T* rep;
  size_type size_;
  size_type first;
};



//: blah
//!noindex:
template <int N>
struct __make_external {
  template <class T>
  inline external_vec<T,N> operator()(T* x) {
    return external_vec<T,N>(x);
  }
};

/* For converting static arrays into MTL vectors */
#define array_to_vec(x) mtl::__make_external<sizeof(x)/sizeof(*x)>()(x)


template <class Container>
inline linalg_vec<Container>
vec(const Container& x)
{
  return linalg_vec<Container>(x);
}

} /* namespace mtl */

#endif

