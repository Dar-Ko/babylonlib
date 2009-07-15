/*$RCSfile: KArrayPtr.h,v $: header file
  $Revision: 1.1 $ $Date: 2009/07/15 20:55:16 $
  $Author: ddarko $

  Array of object references.
  Copyright: CommonSoft Inc
  2009-07-15 Darko Kolakovic
 */

#ifndef _KARRAYPTR_H_
    //$RCSfile: KArrayPtr.h,v $ sentry
  #define _KARRAYPTR_H_

#ifdef _DEBUG_INCL_PREPROCESS   //Preprocessor: debugging included files
  #pragma message ("   #include " __FILE__ )
#endif

#ifdef __cplusplus
#include "KArray.h"

///////////////////////////////////////////////////////////////////////////////
/*This class implements an array of references to a user-defined type.

  Parameter:
    - PTYPE the type of objects reference stored in the array.
 */
template<class PTYPE>
class CArrayPtr : public CArray<PTYPE>
{
public:
  CArrayPtr();
  ~CArrayPtr();
  void RemoveAt(int nIndex);
  void RemoveAll();

};
///////////////////////////////////////////////////////////////////////////////
///

//-----------------------------------------------------------------------------
/*
 */
template <class PTYPE>
CArrayPtr<PTYPE>::CArrayPtr()
  {
  }

/*Frees up any resources used by the objectes refered by the array elements.
 */
template <class PTYPE>
CArrayPtr<PTYPE>::~CArrayPtr()
  {
  RemoveAll();
  }

//-----------------------------------------------------------------------------
/*Removes all of the elements a user-defined type and frees the memory allocated
  to the refering objects.

  Note: It is assumed that objects are created with PTYPE::new operator.

  Example:
      ...
      CArrayPtr array;
      CObject* pa1;
      CObject* pa2;

      array.Add( pa1 = new CObject() ); // Element 0
      array.Add( pa2 = new CObject() ); // Element 1
      ASSERT( array.GetSize() == 2 );
      array.RemoveAll(); // Array elemets and objects are deleted.
      ASSERT( array.GetSize() == 0 );

 */
template <class PTYPE>
void CArrayPtr<PTYPE>::RemoveAll()
{
//Free resoures hold by refering object
int i = 0;
while ( i < GetSize())
  {
  PTYPE pTemp = GetAt(i);
  if (pTemp  != NULL)
  	delete pTemp;
  i++;
  }

CArray<PTYPE>::RemoveAll(); //Delete array elements
}

//-----------------------------------------------------------------------------
/*Removes one element from the array and frees refering object. Any remaining
  elements are shifted down and the upper bound is decremented,

  Note: It is assumed that objects are created with PTYPE::new operator.

  Example:
      ...
      CArrayPtr<TCHAR> MyArray;        //Declare an array of strings
      for (int a = 0; a < 10; a++)     //Add ten elements to the array
        {
        LPTSTR strNewElement = new TCHAR[64];
        MyArray.Add(strNewElement);
        }
      MyArray.RemoveAt(5);             //Remove fifth element
      ASSERT(MyArray.GetCount() == 9); //Confirm size of array

 */
template <class PTYPE>
void CArrayPtr<PTYPE>::RemoveAt(int nIndex //[in] index of the first element
                                           //to remove.
                                )
{
ASSERT((nIndex > 0) && (nIndex < GetSize()));
if ((nIndex > 0) && (nIndex < GetSize()))
	{
  PTYPE pTemp = GetAt(nIndex);
  if (pTemp  != NULL)
  	delete pTemp;
	CArray<PTYPE>::RemoveAt(nIndex);
	}
}

#endif //__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif  //_KARRAYPTR_H_
/*****************************************************************************
 * $Log: KArrayPtr.h,v $
 * Revision 1.1  2009/07/15 20:55:16  ddarko
 * Created
 *
 *****************************************************************************/
