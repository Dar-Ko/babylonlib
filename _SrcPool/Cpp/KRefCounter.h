/*$Workfile: KRefCounter.h$: header file
  $Revision: 1$ $Date: 2005-04-29 19:16:26$
  $Author: Darko Kolakovic$

  Reference counting
  Copyright: CommonSoft Inc
  2001-08-24 Darko Kolakovic
 */


#ifndef _KREFCOUNTER_H_
    //$Workfile: KRefCounter.h$ sentry
  #define _KREFCOUNTER_H_

#ifdef _DEBUG_INCL_PREPROCESS   /*Preprocessor: debugging included files     */
  #pragma message ("   #include " __FILE__ )
#endif

#include <cassert>

///////////////////////////////////////////////////////////////////////////////
/*Reference counting class for managing a count of references to the object.
  If the counter is zero, the object no longer has any users and is free to
  delete it from memory.
  Call AddRef() to increment and Release() to decrements the counter.
  */
class CRefCounter
{
public:
  CRefCounter();
  CRefCounter(const CRefCounter& dummy);

  virtual ~CRefCounter();

public:
  unsigned long AddRef();
  unsigned long Release();
  unsigned long GetCount() const;
  const CRefCounter& operator=(const CRefCounter& dummy);

protected:
  mutable unsigned long m_nRefCount; //number of references to this object.
};

///////////////////////////////////////////////////////////////////////////////
// Inlines

//-----------------------------------------------------------------------------
/*
 */
inline CRefCounter::CRefCounter():
    m_nRefCount(0)
{
}

inline CRefCounter::CRefCounter(const CRefCounter& dummy):
    m_nRefCount(0)
{
dummy;
}

//-----------------------------------------------------------------------------
/*Counts how many times the object is deleted, without dereferncing first.
  The counter have to be zero before freeing the object from memory.
 */
inline CRefCounter::~CRefCounter()
{
assert(m_nRefCount==0);
--m_nRefCount;
}

//-----------------------------------------------------------------------------
/*Assignment operator does nothing because the reference count shouldn't be
  copied.

  Returns: unchanged reference counter.
*/
inline const RefCounter& CRefCounter::operator=(const CRefCounter& dummy)
{
dummy;
return *this;
}

//-----------------------------------------------------------------------------
/*This method increments the reference count.
  The counter could reference up to UINT_MAX objects.

  Returns: resulting value of the reference count.
*/
inline unsigned long CRefCounter::AddRef()
{
return ++m_nRefCount;
}

//-----------------------------------------------------------------------------
/*This method decrements the reference count. If the reference count is 0,
  the object is could be deleted from memory.

  Returns: resulting value of the reference count.
 */
inline unsigned long CRefCounter::Release()
{
return --m_nRefCount;
}

//-----------------------------------------------------------------------------
/*Get the current reference count.

  Returns: resulting value of the reference count.
*/
inline unsigned long CRefCounter::GetCount() const
{
return m_nRefCount;
}

///////////////////////////////////////////////////////////////////////////////
#endif  //_KREFCOUNTER_H_
/*****************************************************************************
 * $Log: 
 *  1    Biblioteka1.0         2005-04-29 19:16:26  Darko Kolakovic 
 * $
 *****************************************************************************/
