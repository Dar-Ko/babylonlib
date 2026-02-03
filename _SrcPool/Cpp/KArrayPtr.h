/*$RCSfile: KArrayPtr.h,v $: header file
  $Revision: 1.5 $ $Date: 2009/07/22 16:44:58 $
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
    - TYPE the type of object whose reference is stored in the array.

  Example:
    ...
    typedef CArrayPtr<CObject> CObjectPtrArray; //array of pointers to CObject
    CObjectPtrArray myArray;
    CObject* pNewElement = new CObject;
    myArray.Add(pNewElement);

 */
template<class TYPE>
class CArrayPtr : public CArray<TYPE*>
{
public:
  CArrayPtr();
  CArrayPtr(const CArrayPtr& src);
  ~CArrayPtr();
  void Copy(const CArrayPtr& src);
  void RemoveAt(int nIndex);
  void RemoveAll();
};
///////////////////////////////////////////////////////////////////////////////
//

//-----------------------------------------------------------------------------
/*
 */
template <class TYPE>
CArrayPtr<TYPE>::CArrayPtr()
{
}

template <class TYPE>
CArrayPtr<TYPE>::CArrayPtr(const CArrayPtr& src //[in] source of the elements
                           //to be copied to the array.
                           )
{
Copy(src);
}

/*Frees up any resources used by the objects referred by the array elements.
 */
template <class TYPE>
CArrayPtr<TYPE>::~CArrayPtr()
{
RemoveAll();
}

//-----------------------------------------------------------------------------
/*Removes all of the elements a user-defined type and frees the memory allocated
  to the referring objects.

  Note: It is assumed that objects are created with new operator.

  Example:
      ...
      CArrayPtr<CObject> array;
      CObject* pa1;
      CObject* pa2;

      array.Add( pa1 = new CObject() ); //Element 0
      array.Add( pa2 = new CObject() ); //Element 1
      ASSERT( array.GetSize() == 2 );
      array.RemoveAll(); //Array elemets and objects are deleted.
      ASSERT( array.GetSize() == 0 );

 */
template <class TYPE>
void CArrayPtr<TYPE>::RemoveAll()
{
//Free resources hold by referring object
int i = 0;
while ( i < GetSize())
  {
  TYPE* pTemp = GetAt(i);
  if (pTemp  != NULL)
  	delete pTemp;
  i++;
  }

CArray<TYPE*>::RemoveAll(); //Delete array elements
}

//-----------------------------------------------------------------------------
/*Removes one element from the array and frees referring object. Any remaining
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
template <class TYPE>
void CArrayPtr<TYPE>::RemoveAt(int nIndex //[in] index of the first element
                                           //to remove.
                                )
{
ASSERT((nIndex > 0) && (nIndex < GetSize()));
if ((nIndex > 0) && (nIndex < GetSize()))
	{
  TYPE* pTemp = GetAt(nIndex);
  if (pTemp  != NULL)
  	delete pTemp;
	CArray<TYPE*>::RemoveAt(nIndex);
	}
}

//-----------------------------------------------------------------------------
/*Copies another array over the array. Elements are copied by value.
 */
template <class TYPE>
void CArrayPtr<TYPE>::Copy(const CArrayPtr& src //[in] source of the elements
                            //to be copied to the array.
                           )
{
RemoveAll(); //Free resources hold by the array
//Deep copy of the source array
int i = 0;
while(i < src.GetSize() )
  {
  if (src[i] != NULL)
    {
    //Copy element content.
    TYPE* pTemp = (TYPE*) new TYPE(*src[i]);
    ASSERT(pTemp != NULL);
    Add(pTemp); //Append reference to the object
    }
  else
    Add(NULL); //Append NULL element found in the source

  i++;
  }
}
#endif //__cplusplus
///////////////////////////////////////////////////////////////////////////////
#endif  //_KARRAYPTR_H_
/*****************************************************************************
 * $Log: KArrayPtr.h,v $
 * Revision 1.5  2009/07/22 16:44:58  ddarko
 * Copy using copy constructor instead assignment
 *
 * Revision 1.4  2009/07/21 22:17:37  ddarko
 * Copy NULL elements
 *
 * Revision 1.3  2009/07/16 15:51:18  ddarko
 * *** empty log message ***
 *
 * Revision 1.2  2009/07/16 15:45:13  ddarko
 * Added deep copy method
 *
 * Revision 1.1  2009/07/15 20:55:16  ddarko
 * Created
 *
 *****************************************************************************/
