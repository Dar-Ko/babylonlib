/*$Workfile: S:\_SrcPool\Cpp\Samples\Assert\Src\Palm\TestAssert.h$: header file
  $Revision: 2$ $Date: 2004-10-28 02:19:19$
  $Author: Darko$

  Test debugging and tracing routines.
  Copyright: CommonSoft Inc.
  2004-09-15 Darko Kolakovic

 * This wizard-generated code is based on code adapted from the
 * stationery files distributed as part of the Palm OS SDK 4.0.
 *
 * Copyright (c) 1999-2000 Palm, Inc. or its subsidiaries.
 * All rights reserved.
*/

// Group=Examples


#ifndef ASSERT_H_
#define ASSERT_H_

/*********************************************************************
 * Internal Structures
 *********************************************************************/


/*********************************************************************
 * Global variables
 *********************************************************************/


/*********************************************************************
 * Internal Constants
 *********************************************************************/

#define appFileCreator			'DAKO'
#define appName					"Assert"
#define appVersionNum			0x01
#define appPrefID				0x00
#define appPrefVersionNum		0x01

/*********************************************************************
 * Helper template functions
 *********************************************************************/

/* use this template like:
 * ControlType *button; GetObjectPtr(button, MainOKButton); */

template <class T>
void GetObjectPtr(typename T * &ptr, UInt16 id)
{
	FormType * frmP;

	frmP = FrmGetActiveForm();
	ptr = static_cast<T *>(
		FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, id)));
}

/* use this template like:
 * ControlType *button =
 *     GetObjectPtr<ControlType>(MainOKButton); */

template <class T>
typename T * GetObjectPtr(UInt16 id)
{
	FormType * frmP;

	frmP = FrmGetActiveForm();
	return static_cast<T *>(
		FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, id)));
}

#endif /* ASSERT_H_ */
