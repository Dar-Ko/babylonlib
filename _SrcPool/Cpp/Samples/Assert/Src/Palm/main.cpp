/*$Workfile: main.cpp$: implementation file
  $Revision: 12$ $Date: 2004-11-24 13:11:42$
  $Author: Darko Kolakovic$

  Entry point for the application.
  Copyright: CommonSoft Inc.
  2004-10-10 Darko Kolakovic
 */

// Group=Examples
//#include <PalmOS.h>

#ifndef _STDAFX_H_
  #include "stdafx.h"
#endif

#include "TestAssert.h"
#include "KTraceFx.h"
FormType* GetMainForm();
//-----------------------------------------------------------------------------
/*This routine initializes the MainForm form.
 */
FormType* GetMainForm()
{
#pragma todo(GetMainForm)
#pragma FIXME(cfcfcfcfGetMainForm)
#pragma deprecated(GetMainForm; TODO)
//TODO:
return NULL;
}

extern "C" void * GetObjectPtr(UInt16 objectID);
/***********************************************************************
 *
 * FUNCTION:    GetObjectPtr
 *
 * DESCRIPTION: This routine returns a pointer to an object in the current
 *              form.
 *
 * PARAMETERS:  formId - id of the form to display
 *
 * RETURNED:    void *
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
void * GetObjectPtr(UInt16 objectID)
{
	FormPtr frmP;

	frmP = FrmGetActiveForm();
	return FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, objectID));
}


FieldType* GetActiveField(FormType* frmOwner);
//-----------------------------------------------------------------------------
/*This routine initializes the MainForm form.
 */
FieldType* GetActiveField(FormType* frmOwner //[in]
                         )
{
if (frmOwner != NULL)
//  frmOwner = FrmGetActiveForm();
  {
    /*Get the 0-based index of an object in the form's objects list*/
  UInt16 nFieldIndex = FrmGetObjectIndex(frmOwner, IDR_MAINFIELD);
  if (nFieldIndex != frmInvalidObjectId)
    {
    /*Get the field object*/
    if (FrmGetObjectType(frmOwner, nFieldIndex) == frmFieldObj)
      return (FieldType*)FrmGetObjectPtr(frmOwner, nFieldIndex);
    }
  return NULL;
  }
return GetObjectPtr<FieldType>(IDR_MAINFIELD);
}


void MainFormInit(FormType *frmP);
//-----------------------------------------------------------------------------
/*This routine initializes the MainForm form.
 */
void MainFormInit(FormType *frmP //[in] pointer to the MainForm form.
                 )
{
RectangleType rectScreen;
  /*Resize the form (window) to the screen size*/

  /*Get the screen dimensions*/
WinGetDisplayExtent(&rectScreen.extent.x, &rectScreen.extent.y);
rectScreen.topLeft.x = 0;
rectScreen.topLeft.y = 0;
  /*Resize the form*/
WinSetWindowBounds(FrmGetWindowHandle(frmP), &rectScreen);

  /*Resize the field (view) to form's size*/
FrmGetFormBounds(frmP, &rectScreen);
FrmSetObjectBounds(frmP, FrmGetObjectIndex(frmP, IDR_MAINFIELD), &rectScreen);
FrmSetFocus(frmP, FrmGetObjectIndex(frmP, IDR_MAINFIELD));


extern int TestCommonAssert();
extern bool TestDumpMemHeap();
FieldType *field;
const char *wizardDescription;

field = GetActiveField(NULL);
frmP;
//FrmSetFocus(frmP, fieldIndex);

wizardDescription =
  "C++ application "
  "Creator Code: DAKO "
  ;

/* dont stack FldInsert calls, since each one generates a
 * fldChangedEvent, and multiple uses can overflow the event queue */
FldInsert(field, wizardDescription, StrLen(wizardDescription));
//TestCommonAssert(); //TODO: move to different place, not in main frame
extern int TestCppConformance(void);
TestCppConformance();
extern int TestCommonAssert();
TestCommonAssert();
TestDumpMemHeap();
}

//-----------------------------------------------------------------------------
/*
 * FUNCTION: MainFormDoCommand
 *
 * DESCRIPTION: This routine performs the menu command specified.
 *
 * PARAMETERS:
 *
 * command
 *     menu item id
 */

static Boolean MainFormDoCommand(UInt16 command)
{
Boolean handled = false;

switch (command)
{
  case OptionsAboutAssert:
  {
    FormType * frmP;

    /* Clear the menu status from the display */
    MenuEraseStatus(0);

    /* Display the About Box. */
    frmP = FrmInitForm (AboutForm);
    FrmDoDialog (frmP);
    FrmDeleteForm (frmP);

    handled = true;
    break;
  }

}

return handled;
}

  /*default event handler callback routine associated with the main form*/
FormEventHandlerType DefFormProc;

//-----------------------------------------------------------------------------
/*This routine is the event handler for the "MainForm" of this
 * application.
 *
 * PARAMETERS:
 *
 * pEvent
 *     a pointer to an EventType structure
 *
 * RETURNED:
 *     true if the event was handled and should not be passed to
 *     FrmHandleEvent

  Note: Palm OS specific (PalmOS).
 */
Boolean DefFormProc(EventType * pEvent //[in] pointer to the event to
                                       //be processed
                            )
{
Boolean handled = false;
FormType * frmP;

switch (pEvent->eType)
{
  case menuEvent:
    return MainFormDoCommand(pEvent->data.menu.itemID);

  case frmOpenEvent:
    frmP = FrmGetActiveForm();
    FrmDrawForm(frmP);
    MainFormInit(frmP);
    handled = true;
    break;

    case frmUpdateEvent:
    /*
     * To do any custom drawing here, first call
     * FrmDrawForm(), then do your drawing, and
     * then set handled to true.
     */
    break;

  case ctlSelectEvent:
  {
    if (pEvent->data.ctlSelect.controlID == MainClearTextButton)
    {
      /* The "Clear" button was hit. Clear the contents of the field. */

      FieldType * field = GetObjectPtr<FieldType>(IDR_MAINFIELD);
      if (field)
      {
        FldDelete(field, 0, 0xFFFF);
        FldDrawField(field);
      }
      break;
    }

    break;
  }
}

return handled;
}


///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log:
 *  4    Biblioteka1.3         2004-10-28 02:19:26  Darko           Unicode build
 *       PalmOS
 *  3    Biblioteka1.2         2004-10-26 14:51:14  Darko Kolakovic TRACE1 macro
 *  2    Biblioteka1.1         2004-10-25 17:58:27  Darko Kolakovic CodeWarrior 9
 *       fixes
 *  1    Biblioteka1.0         2004-10-19 14:51:37  Darko Kolakovic
 * $
 * 0 CodeWarrior 9 wizard-generated code is based on code adapted from the
 * stationery files distributed as part of the Palm OS SDK 4.0.
 *****************************************************************************/
