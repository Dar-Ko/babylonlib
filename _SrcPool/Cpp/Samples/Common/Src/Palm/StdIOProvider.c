/******************************************************************************
 *
 * Copyright (c) 1996-1998 Palm Computing, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: StdIOProvider.c
 *
 * Description:
 *	  This module implements stdin/stdout support for a pilot application.
 * It is designed to be linked in with any PalmOS app that wishes to be a
 * StdIO provider application. A StdIO provider app opens a window for
 * output and sub-launches PalmOS stdio apps that can then use that window
 * for output. 
 *
 * History:
 *	5-6-98	RM		Created by Ron Marianetti
 *
 *****************************************************************************/

/*
 *   It requires that the application provide a form with a text field and
 * a scroll bar
 *
 *	 It is designed to be linked in with application code and is not
 * normally part of the system software. 
 *
 *   To use this module, the application must do the following:
 *
 *  1.) Call StdInit during app initialization. StdInit() will save away
 *		the object ID of the form that contains the stdio field, the field
 *		itself, and the scroll bar. 
 *
 *	2.) Call SioHandleEvent from the form's event handler before doing application
 *		specific processing of the event.
 *		In other words, the form event handler that the application
 *		installs with FrmSetEventHandler() should call SioHandleEvent before
 *		it does anything else with the event. 
 *
 *  3.) Call SioFree() during app shutdown.
 *
 *
 * Other than that, the app is free to call printf, getchar, etc anytime it wants
 *		between the SioInit() and SioFree() calls. If the current form is not the
 *		StdIO form when these calls are made, they will record changes to the
 *		active text and display it next time the form becomes active. 
 *
 *
 *----------------------------------------------------------------------------
 *
 * A "typical" application will have the following routine called
 *		ApplicationHandleEvent which gets called from it's main event loop
 *		after SysHandleEvent() and MenuHandleEvent():
 *
 *----------------------------------------------------------------------------
	static Boolean ApplicationHandleEvent (SysEventType * event)
	{
		FormPtr frm;
		UInt16 formId;

		if (event->eType == frmLoadEvent) {
			formId = event->data.frmLoad.formID;
			frm = FrmInitForm (formId);
			FrmSetActiveForm (frm);		
			
			switch (formId) {
				.....
				case myViewWithStdIO:
					FrmSetEventHandler (frm, MyViewHandleEvent);
					break;
				}
			return (true);
			}	 

		return (false);
		}	 
 *
 *
 *----------------------------------------------------------------------------
 *
 * A "typical" application form event handler will look like this:
 *
 *----------------------------------------------------------------------------
	static Boolean MyViewHandleEvent (SysEventType * event)
	{
		FormPtr frm;
		Boolean handled = false;


		// Let StdIO handler to it's thing first.
		if (SioHandleEvent(event)) return true;


		// If StdIO did not completely MemHandle the event...
		if (event->eType == keyDownEvent) {
			if ( (EvtKeydownIsVirtual(event)) &&
					(event->data.keyDown.chr == vchrHardCradle) ) {
				FrmGotoForm( kMainFormID );					// exit to main view
				EvtAddEventToQueue( event );					// ... and repost the key event
				handled = true;
				}
			
		else if (event->eType == ctlSelectEvent) {		
			switch (event->data.ctlSelect.controlID) {
				case myViewDoneButtonID:
					FrmGotoForm (networkFormID);
					handled = true;
					break;
				}
			}


		else if (event->eType == menuEvent) 
			return MyMenuDoCommand( event->data.menu.itemID );

			
		else if (event->eType == frmUpdateEvent) {
			MyViewDraw( FrmGetActiveForm() );
			handled = true;
			}
			
			
		else if (event->eType == frmOpenEvent) {
			frm = FrmGetActiveForm();
			MyViewInit( frm );
			MyViewDraw( frm );
			handled = true;
			}
			
			
		else if (event->eType == frmCloseEvent) {
			frm = FrmGetActiveForm();
			MyViewClose(frm);
			}
			
		return (handled);
	}
 *
 *
 **********************************************************************/

#include <PalmTypes.h>

// public system includes
#include <Chars.h>
#include <DateTime.h>
#include <ErrorMgr.h>
#include <SysEvent.h>
#include <Form.h>
#include <MemoryMgr.h>
#include <Preferences.h>
#include <StringMgr.h>
#include <StdIOProvider.h>
#include <TextMgr.h> // TxtCharIsHardKey

#include <PalmUtils.h>

// private system includes



// Private Functions
static Int16 PrvFPutSProc (void* sioGP, const Char * str, FILE* fs);



/***********************************************************************
 *
 * FUNCTION:		PrvCloneStr
 *
 * DESCRIPTION:		Allocates a MemHandle and stuffs srcStr into it.
 *
 * CALLED BY:		 
 *
 * PARAMETERS:		srcStr - pointer to string to initialize MemHandle with
 *
 * RETURNED:    	MemHandle to string 
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static MemHandle PrvCloneStr(const Char * srcStr)
{
	UInt16		len;
	MemHandle 	stringH;
	Char * 	stringP;
	
	len = StrLen(srcStr);
	if (!len) return NULL;
	
	stringH = MemHandleNew(len+1);
	if (stringH) {
		stringP = MemHandleLock(stringH);
		StrCopy(stringP,srcStr);
		MemPtrUnlock(stringP);
		}
	return stringH;
}



/***********************************************************************
 *
 * FUNCTION:	PrvHandleStrCat
 *
 * DESCRIPTION:	Catenates a string into an existing MemHandle
 *
 * CALLED BY:	PrvFPutSProc when appending text	 
 *
 * PARAMETERS:	stringH 	- existing MemHandle with text
 *				srcP		- pointer to text to catenate
 *
 * RETURNED:    void	 
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static void PrvHandleStrCat(MemHandle stringH, const Char * srcP)
{
	UInt16 newSize,oldLength;
	Char * stringP;
	
	newSize = StrLen(srcP) + 1;					// initialize new size
	
	// Resize the existing MemHandle, if any
	if ( stringH ) {
		stringP = MemHandleLock( stringH );
		oldLength = StrLen(stringP);
		newSize += oldLength;
		MemPtrUnlock( stringP );
		if ( MemHandleResize(stringH, newSize) == 0) {	// Append the new text
			stringP = MemHandleLock( stringH );
			StrCopy( stringP + oldLength, srcP );			// copy the new text
			MemPtrUnlock( stringP );
			}
		}
}




/***********************************************************************
 *
 * FUNCTION:    PrvGetObjectPtr
 *
 * DESCRIPTION: This routine returns a pointer to an object in the current
 *              form.
 *
 * PARAMETERS:  objectID - which object.
 *
 * RETURNED:    Pointer to object
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static void * PrvGetObjectPtr (UInt16 objectID)
{
	FormPtr frm;
	void * obj;
	
	frm = FrmGetActiveForm ();
	obj = FrmGetObjectPtr (frm, FrmGetObjectIndex (frm, objectID));

	return obj;
}




/***********************************************************************
 *
 * FUNCTION:	SetFieldText
 *
 * DESCRIPTION:	Set field object's text MemHandle.  Will reuse an existing
 *						text MemHandle, if any
 *
 * PARAMETERS:	fldID		-- field object id
 *				srcP		-- source text pointer
 *				append		-- if true, the new text will be appended
 *				redraw		-- if true, field will be redrawn
 *
 * RETURNED:    void.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static void PrvSetFieldText(UInt16 fldID, Char * srcP, Boolean append,
								Boolean redraw)
{
	MemHandle 		stringH;
	UInt16			oldLength = 0;
	UInt16			newSize;
	Char * 		stringP;
	FieldPtr		fldP;

	fldP = (FieldPtr)PrvGetObjectPtr(fldID);

	if (!srcP || !*srcP) {						// MemHandle clearing field as well
		FldFreeMemory(fldP);
		if ( redraw )	 {
			FldEraseField( fldP );
			FldDrawField( fldP );
			}
		return;
		}
	
	
	newSize = StrLen(srcP) + 1;					// initialize new size
	stringH = FldGetTextHandle( fldP );			// get the current text MemHandle
	FldSetTextHandle( fldP, 0 );					// release this MemHandle from field

	// Resize the existing MemHandle, if any
	if ( stringH ) {
		if ( append ) {
			stringP = MemHandleLock( stringH );
			oldLength = StrLen(stringP);
			newSize += oldLength;
			MemPtrUnlock( stringP );
			}
		if ( MemHandleResize(stringH, newSize) )
			goto Exit;
		} // Resize the existing MemHandle, if any
	
	// Otherwise, allocate a new MemHandle
	else {
		stringH = MemHandleNew( newSize );		// allocate a new chunk
		if ( !stringH )	return;
		}

	// Append the new text
	stringP = MemHandleLock( stringH );
	StrCopy( stringP + oldLength, srcP );		// copy the new text
	MemPtrUnlock( stringP );
	
Exit:
	FldSetTextHandle( fldP, stringH );			// set the new text MemHandle
	if ( redraw )	 {
		FldEraseField( fldP );
		FldDrawField( fldP );
		}
}



/***********************************************************************
 *
 * FUNCTION:    PrvFormUpdateScroller
 *
 * DESCRIPTION: This routine draws or erases the status view scrollbar
 *
 * PARAMETERS:  frm             -  pointer to the status form
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static void PrvFormUpdateScroller (SioProvGlobalsPtr gP, FormPtr frm)
{
	UInt16 				scrollPos;
	UInt16 				textHeight;
	UInt16 				fieldHeight;
	Int16 			maxValue;
	FieldPtr 		fld;
	ScrollBarPtr 	bar;

	fld = FrmGetObjectPtr (frm, FrmGetObjectIndex (frm, gP->fieldID));
	bar = FrmGetObjectPtr (frm, FrmGetObjectIndex (frm, gP->scrollerID));
	
	FldGetScrollValues (fld, &scrollPos, &textHeight,  &fieldHeight);

	if (textHeight > fieldHeight)
		maxValue = textHeight - fieldHeight;
	else
		maxValue = 0;

	SclSetScrollBar (bar, scrollPos, 0, maxValue, fieldHeight-1);
}



/***********************************************************************
 *
 * FUNCTION:    PrvFieldScroll
 *
 * DESCRIPTION: Scrolls the status view a page or a 
 *              line at a time.
 *
 * PARAMETERS:  direction - up or dowm
 *              oneLine   - true if scrolling a single line
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static void PrvFieldScroll (SioProvGlobalsPtr gP, Int16 linesToScroll)
{
	UInt16				blankLines;
	Int16				min;
	Int16				max;
	Int16				value;
	Int16				pageSize;
	FieldPtr			fld;
	ScrollBarPtr	bar;
	
	fld = PrvGetObjectPtr (gP->fieldID);

	if (linesToScroll < 0) {
		blankLines = FldGetNumberOfBlankLines (fld);
		FldScrollField (fld, -linesToScroll, winUp);
		
		// If there were blank lines visible at the end of the field
		// then we need to update the scroll bar.
		if (blankLines) {
			// Update the scroll bar.
			bar = PrvGetObjectPtr (gP->scrollerID);
			SclGetScrollBar (bar, &value, &min, &max, &pageSize);
			if (blankLines > -linesToScroll)
				max += linesToScroll;
			else
				max -= blankLines;
			SclSetScrollBar (bar, value, min, max, pageSize);
			}
		}

	else if (linesToScroll > 0)
		FldScrollField (fld, linesToScroll, winDown);

}

/***********************************************************************
 *
 * FUNCTION:    PrvFieldPageScroll
 *
 * DESCRIPTION: Scroll the owner message a page up or down.
 *
 * PARAMETERS:  direction - up or down
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static void PrvFieldPageScroll (SioProvGlobalsPtr gP, WinDirectionType direction)
{
	Int16 value;
	Int16 min;
	Int16 max;
	Int16 pageSize;
	UInt16 linesToScroll;
	FieldPtr fld;
	ScrollBarPtr bar;

	fld = PrvGetObjectPtr (gP->fieldID);
	
	if (FldScrollable (fld, direction)) {
		linesToScroll = FldGetVisibleLines (fld) - 1;
		FldScrollField (fld, linesToScroll, direction);

		// Update the scroll bar.
		bar = PrvGetObjectPtr (gP->scrollerID);
		SclGetScrollBar (bar, &value, &min, &max, &pageSize);

		if (direction == winUp)
			value -= linesToScroll;
		else
			value += linesToScroll;
		
		SclSetScrollBar (bar, value, min, max, pageSize);
		return;
		}
}


/***********************************************************************
 *
 * FUNCTION:    PrvFormInit
 *
 * DESCRIPTION: This routine initializes the "Status View"
 *
 * PARAMETERS:  frm  - a pointer to the Status form
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static void PrvFormInit (SioProvGlobalsPtr gP, FormPtr frm)
{
	FieldAttrType 	attr;
	FieldPtr 		fldP;


	if (!gP->textH)
		gP->textH = PrvCloneStr("Pilot StdIO\n");
		
	// Get the field ptr
	fldP = FrmGetObjectPtr (frm, FrmGetObjectIndex (frm, gP->fieldID));
	
	// Indicate that it has a scroll bar
	FldGetAttributes (fldP, &attr);
	attr.hasScrollBar = true;
	FldSetAttributes (fldP, &attr);
	
	// Initialize it's text
	FldSetTextHandle( fldP, gP->textH );			// set the new text MemHandle
	
	// No longer need background copy
	gP->textH = 0;
	
}


/***********************************************************************
 *
 * FUNCTION:    PrvFormClose
 *
 * DESCRIPTION: Closes down the stdio form
 *
 * PARAMETERS:  frm  - a pointer to the Status form
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static void PrvFormClose (SioProvGlobalsPtr gP, FormPtr frm)
{
	FieldPtr fldP;
	
	fldP = FrmGetObjectPtr (frm, FrmGetObjectIndex (frm, gP->fieldID));
	
	// Save the current MemHandle
	if (gP->textH) MemHandleFree(gP->textH);
	gP->textH = FldGetTextHandle(fldP);
	
	// Take it out of the field object.
	FldSetTextHandle( fldP, NULL );			// remove the MemHandle so it 
														//  isn't freed
}


/***********************************************************************
 *
 * FUNCTION:    PrvFormDraw
 *
 * DESCRIPTION: This routine draws the "Sync View"
 *
 * PARAMETERS:  frm - pointer to the view form.
 *
 * RETURNED:    nothing.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static void PrvFormDraw(SioProvGlobalsPtr gP, FormPtr frm)
{
	PrvFormUpdateScroller (gP, frm );
}



/***********************************************************************
 *
 * FUNCTION:    PrvProcessCommand
 *
 * DESCRIPTION: This routine grabs the current line of the text field
 *			and sends it to the application's command processor.
 *
 * PARAMETERS:  void
 *
 * RETURNED:    nothing.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static void PrvProcessCommand(SioProvGlobalsPtr gP)
{
	Char * 		textP;
	Char *		p;
	Int16 		i,j;
	const int 	cmdBufSize = 100; 			// max allowed lenght for a command line
	char 		cmdBuf[cmdBufSize+1];   	// buffer for holding command line
	MemHandle		textH;
	FieldPtr	fldP=0;


	// Get the text MemHandle
	if (FrmGetActiveFormID() == gP->formID) {
		fldP = PrvGetObjectPtr(gP->fieldID);
		textH = FldGetTextHandle(fldP);

		}
	else {
		textH = gP->textH;
		}

   // parse text for command line interface here....
   if (!textH) return;
	textP = MemHandleLock(textH);
   
   if (fldP)
   	i = FldGetInsPtPosition(fldP) - 2;
   else
   	i = StrLen(textP) - 2;  		// skip null and final linefeed
   
   // Added to prevent indexing outside of a memory chunk
   // if StrLen or FldGetInsPtPosition return a value
   // less than two.
   if ( i < 0)
   	i = 0;
   
   // scan back to previous line or start of text
   while (i > 0 && textP[i] != linefeedChr)
   	i--;
   
   if (textP[i] == linefeedChr)		  		// do not include the linefeed...
   	i++;
   
   if (textP[i] == '>') 		 				// skip over prompt...
   	i++;
   	 
   // copy into command buffer leaving out final linefeed
	for (p = &textP[i], j = 0; *p && *p != linefeedChr && j < cmdBufSize; )
		cmdBuf[j++] = *p++;
		
	cmdBuf[j] = 0;
	
	MemHandleUnlock(textH);
		
	// Call command handler
	SioExecCommand(cmdBuf);
}


/***********************************************************************
 *
 * FUNCTION:		PrvBS
 *
 * DESCRIPTION:	Utility used to backspace from stdout
 *
 * CALLED BY:		Applications.
 *
 * PARAMETERS:		PrvFGetCProc when processing backspace key	
 *
 * RETURNED:    	void
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static void PrvBS (void)
{	
	SysEventType	event;
	
	event.eType = sysEventKeyDownEvent;
	event.data.keyDown.chr = 8;
	SioHandleEvent(&event);
	
}



#pragma mark --Callbacks--

/***********************************************************************
 *
 * FUNCTION:		PrvFGetCProc
 *
 * DESCRIPTION:	Waits till the user types a character. Ignores all
 *			other types of events. Returns character or -1 (EOF) if an 
 *			appStop event is encountered or if the user enters the
 *			'~' character.
 *
 * CALLED BY:		fgetc() glue in StdIOPalm.c.
 *
 * PARAMETERS:		sioGP	-> Sio globals pointer
 *					fs		-> file descriptor
 *
 * RETURNED:   character, or -1 if error or end-of-file 
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static Int16	PrvFGetCProc(void* sioGP, FILE* UNUSED_PARAM(fs))
{
	EventType			event;
	Int16				key;
	Char				str[2];
	UInt32				oldA5;
	SioProvGlobalsPtr	gP = (SioProvGlobalsPtr)sioGP;	
	
	// Setup our globals pointer
	oldA5 = SysSetA5(gP->provA5);
		
	str[1] = 0;
	
	while (1) {
		// Check for system events
		EvtGetEvent(&event, evtWaitForever);
		if (SysHandleEvent(&event)) continue;
		
		// On appStop, return end of file
		if (event.eType == appStopEvent) {key = -1; goto Exit;}
		
		// If not a key event, pass to form handler
		if (event.eType != keyDownEvent) {
			FrmDispatchEvent((EventType*)&event);
			continue;
			}
		
		// Get the key
		key = event.data.keyDown.chr;
		
		// Treat ~ as end-of-file 
		if (key == '~') {key = -1; goto Exit;}
		
		// If echo, display it
		if (gP->echo) {
			str[0] = key;
			if (key == 8)
				PrvBS();
			else
				PrvFPutSProc(gP, str, stdout);
			}
			
		// Return the key
		goto Exit;
		}
		
Exit:
	// Restore client's a5
	SysSetA5(oldA5);
	return key;	
}



/***********************************************************************
 *
 * FUNCTION:		PrvFGetSProc
 *
 * DESCRIPTION:	Waits till the user types a string. Ignores all
 *			other types of events. Returns 0 if end-of-file or
 *			pointer to string otherwise. 
 *
 * CALLED BY:		fgets() glue in StdIOPalm.c..
 *
 * PARAMETERS:		sioGP	-> Sio globals pointer
 *					strP	-> string buffer
 *					n		-> size of string buffer
 *					fs		-> file descriptor
 *					
 *
 * RETURNED:   pointer to string, or 0 if error or EOF	 
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static Char *	PrvFGetSProc(void* sioGP, Char * strP, UInt16 UNUSED_PARAM(n), FILE* fs)
{
	Int16			key;
	UInt16		index = 0;
	Char *		result;
	UInt32		oldA5;
	
	SioProvGlobalsPtr	gP = (SioProvGlobalsPtr)sioGP;	
	
	// Setup our globals pointer
	oldA5 = SysSetA5(gP->provA5);
		
	// Terminate the string
	strP[0] = 0;
	result = strP;
		
	while (1) {
		key = fgetc(fs);
		
		// Check for end of file
		if (key == EOF) {result = 0; goto Exit;}
		
		// Look for backspace
		if (key == 8) {
			index--;
			strP[index] = 0;
			continue;
			}
		
		// Append to the string
		strP[index++] = key;
		strP[index] = 0;
		
		// If carriage return, exit
		if (key == '\r' || key == '\n') goto Exit;
		
		}
		
Exit:
	// Restore client's a5
	SysSetA5(oldA5);
	return result;	
	
}





/***********************************************************************
 *
 * FUNCTION:		PrvFPutCProc
 *
 * DESCRIPTION:		Prints a character to a stream
 *
 * CALLED BY:		fputc glue code in StdIOPalm.c.
 *
 * PARAMETERS:		sioGP	-> Sio globals pointer
 *					c		-> character to print
 *					fs		-> file descriptor
 *
 * RETURNED:    	>=0 on success
 *					<0 on failure.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static Int16 PrvFPutCProc (void* sioGP, Int16 c, FILE* fs)
{	
	Char	str[2];
	
	str[0] = c;
	str[1] = 0;
	return PrvFPutSProc(sioGP, str, fs);
}


/***********************************************************************
 *
 * FUNCTION:		PrvFPutSProc
 *
 * DESCRIPTION:		print a string to stdout
 *
 * CALLED BY:		fputs glue code in StdIOPalm.c..
 *
 * PARAMETERS:		sioGP	-> Sio globals pointer
 *					str		-> string to print
 *					fs		-> file descriptor
 *
 * RETURNED:    	>=0 on success
 *					<0 on failure.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static Int16 PrvFPutSProc (void* sioGP, const Char * str, FILE* UNUSED_PARAM(fs))
{	
	FieldPtr 		fldP;
	UInt16			maxSize;
	Char *			textP;
	UInt16			pos;
	UInt16			insertLen;
	Int16			result=0;
	UInt32			oldA5;
	
	SioProvGlobalsPtr	gP = (SioProvGlobalsPtr)sioGP;	
	
	// Setup our globals pointer
	oldA5 = SysSetA5(gP->provA5);
		
	if (FrmGetActiveFormID() == gP->formID) {
		fldP = (FieldPtr)PrvGetObjectPtr(gP->fieldID);
		
		// Make sure there's room for this new text
		maxSize = FldGetMaxChars(fldP);
		textP = FldGetTextPtr(fldP);
		insertLen = StrLen(str);
		if (insertLen > maxSize-1) 
			insertLen = maxSize-1;
		result += insertLen;
			
		// If not enough room, lop off the top.
		if (textP) {
			while (StrLen(textP) + insertLen >= maxSize) {
				RectangleType	clipR, savedClipR;

				// Clip off everything so that field package doesn't
				//  do a redraw during FldDelete()
				WinGetClip (&savedClipR);
				clipR = savedClipR;
				clipR.extent.x = clipR.extent.y = 0;
				WinSetClip (&clipR);

				// Lop off the top
				pos = FldGetInsPtPosition(fldP);
				FldDelete(fldP, 0, maxSize/4);
				FldSetInsPtPosition(fldP, pos);

				// Restore clip region.
				WinSetClip (&savedClipR);
				textP = FldGetTextPtr(fldP);
				}
			}
		
		// Insert the new text
		FldInsert(fldP, str, insertLen);
		PrvFormUpdateScroller (gP, FrmGetActiveForm());
		}
		
	else  {	
		if (gP->textH)
			PrvHandleStrCat(gP->textH, str);
		else
			gP->textH = PrvCloneStr(str);
		}
		
Exit:
	// Restore client's a5
	SysSetA5(oldA5);
	return result;	
}


/***********************************************************************
 *
 * FUNCTION:		PrvFVPrintFProc
 *
 * DESCRIPTION:		print a formatted string to stdout
 *
 * CALLED BY:		fputs glue code in StdIOPalm.c..
 *
 * PARAMETERS:		sioGP		-> Sio globals pointer
 *					fs			-> file descriptor
 *					formatStr	-> format string
 *					args		-> variable arguments
 *
 * RETURNED:    	>=0 on success
 *					<0 on failure.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
#define textLen 0x1FF
static Int16	PrvFVPrintFProc(void* sioGP, FILE* fs, const Char * formatStr,	
		 			_Palm_va_list args)
{
	Int16				result;
	static 	Char		text[textLen+1];		// static so we don't eat up stack space
	UInt32				oldA5;


	// Setup our globals pointer
	SioProvGlobalsPtr	gP = (SioProvGlobalsPtr)sioGP;	
	oldA5 = SysSetA5(gP->provA5);
		
	// Crude check for overflow on the formatStr
	if (StrLen(formatStr) < textLen/2) {
		result = StrVPrintF(text, formatStr, args);
		PrvFPutSProc(sioGP, text, fs);
		}
	else {
		PrvFPutSProc(sioGP, formatStr, fs);
		result = StrLen(formatStr);
		}
		
	// Restore client's a5
	SysSetA5(oldA5);
	return result;
}

/***********************************************************************
 *
 * FUNCTION:		PrvSystemProc
 *
 * DESCRIPTION:		Execute a command line.
 *
 *					This routine will first look for a built-in command
 *					installed using SioAddCommand(). 
 *
 *					If none found, it will look for a Palm StdIO app
 *					database with the name "Cmd-<cmdname>" where <cmdname> is the
 *					first word in the command string. 
 *					
 *
 * CALLED BY:		system() glue code in StdIOPalm.c..
 *
 * PARAMETERS:		sioGP		-> Sio globals pointer
 *					cmdStrP		-> command string to execute
 *
 * RETURNED:    	>=0 on success
 *					<0 on failure.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
static Int16 PrvSystemProc (void* sioGP, const Char * cmdStrP)
{	
	UInt32		oldA5;
	Int16		result;
	
	SioProvGlobalsPtr	gP = (SioProvGlobalsPtr)sioGP;	
	
	// Setup our globals pointer
	oldA5 = SysSetA5(gP->provA5);

	// Execute the command string.
	result = SioExecCommand(cmdStrP);
	
Exit:
	// Restore client's a5
	SysSetA5(oldA5);
	return result;	

}


#pragma mark --Public--

/***********************************************************************
 *
 * FUNCTION:    SioHandleEvent
 *
 * DESCRIPTION: Handles events in the form that contains the
 *		stdio text field and scroll arrows if the event belongs to
 *		the text field or scroll arrows.
 *
 *		This routine should be called from the form event handler
 *		before it does it's own processing with any of the non stdio 
 *		objects in the form.
 *
 * PARAMETERS:  event  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event was handled and should not be 
 *						processed by the app's own form event handler. 
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
Boolean SioHandleEvent (SysEventType * event)
{
	SioProvGlobalsPtr	gP = (SioProvGlobalsPtr)GAppSioGlobalsP;
	FormPtr 			frmP;
	Boolean 			handled = false;


	if (event->eType == keyDownEvent) {
        if	(	(!TxtCharIsHardKey(	event->data.keyDown.modifiers,
									event->data.keyDown.chr))
			&&	(EvtKeydownIsVirtual(event))
			&&	(	(event->data.keyDown.chr == vchrPageUp)
				||	(event->data.keyDown.chr == vchrPageDown))) {

			if (event->data.keyDown.chr == vchrPageUp) {
				PrvFieldPageScroll (gP, winUp);
				}
			else {
				PrvFieldPageScroll (gP, winDown);
				}
			handled = true;
			}
		else {	
			frmP = FrmGetActiveForm ();
			FrmHandleEvent (frmP, (EventType*)event);
			PrvFormUpdateScroller (gP, frmP);
			if ( event->data.keyDown.chr == linefeedChr )	
				PrvProcessCommand(gP);
			handled = true;
			}
		}


	else if (event->eType == sclRepeatEvent)
		{
		EventType *uievent = (EventType*)event;
		
		PrvFieldScroll (gP, uievent->data.sclRepeat.newValue - 
			uievent->data.sclRepeat.value);
		}



	else if (event->eType == frmUpdateEvent) {
		PrvFormDraw( gP, FrmGetActiveForm() );
		}
		
	else if (event->eType == fldChangedEvent) {
		PrvFormUpdateScroller( gP, FrmGetActiveForm() );
		handled = true;
		}
		
		
	else if (event->eType == frmOpenEvent) {
		frmP = FrmGetActiveForm();
		PrvFormInit( gP, frmP );
		PrvFormDraw( gP, frmP );
		FrmSetFocus( frmP, FrmGetObjectIndex (frmP, gP->fieldID)) ;
		}
		
		
	else if (event->eType == frmCloseEvent) {
		frmP = FrmGetActiveForm();
		PrvFormClose(gP, frmP);
		}
		
	return (handled);
}



/***********************************************************************
 *
 * FUNCTION:		SioInit
 *
 * DESCRIPTION:		Initialize the standard IO manager.
 *
 * CALLED BY:		StdIO Provider applications during startup
 *
 * PARAMETERS:		formID		->	form that contains the field used for output
 *					fieldID		-> 	text field in the form for output
 *					scrollerID	-> scroller for this field
 *
 * RETURNED:    	0 if no err
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
Err	SioInit(UInt16 formID, UInt16 fieldID, UInt16 scrollerID)
{
	SioProvGlobalsPtr	gP;
	
	// Allocate our globals
	gP = MemPtrNew(sizeof(SioProvGlobalsType));
	ErrFatalDisplayIf(!gP, "no memory");
	if (!gP) return memErrNotEnoughSpace;
	
	// Init globals
	GAppSioGlobalsP = ( SioGlobalsPtr)gP;
	MemSet(gP, sizeof(SioProvGlobalsType), 0);
	
	// Client fields
	gP->client.size = sizeof(SioGlobalsType);
	gP->client.fgetcProcP = PrvFGetCProc;
	gP->client.fgetsProcP = PrvFGetSProc;
	gP->client.fputcProcP = PrvFPutCProc;
	gP->client.fputsProcP = PrvFPutSProc;
	gP->client.vfprintfProcP = PrvFVPrintFProc;
	gP->client.systemProcP = PrvSystemProc;
	
	
	// Provider specific fields
	gP->provA5 = SysSetA5(0);
	SysSetA5(gP->provA5);
	gP->formID = formID;
	gP->fieldID = fieldID;
	gP->scrollerID = scrollerID;
	gP->echo = true;

	return 0;
}


/***********************************************************************
 *
 * FUNCTION:		SioFree
 *
 * DESCRIPTION:		Closes down the standard IO manager.
 *
 * CALLED BY:		Application during it's shutdown.
 *
 * PARAMETERS:		void 
 *
 * RETURNED:    	0 if no error
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
Err	SioFree(void)
{
	SioProvGlobalsPtr	gP;
	
	gP = (SioProvGlobalsPtr)GAppSioGlobalsP;
	if (!gP) return 0;
	
	// Free the text MemHandle
	if (gP->textH) MemHandleFree(gP->textH);


	// Free the people
	MemPtrFree(gP);
	GAppSioGlobalsP = 0;	
	
	return 0;	
}



/***********************************************************************
 *
 * FUNCTION:   		SioAddCommand
 *
 * DESCRIPTION: 	Registers a built-in command for the command
 *					interpreter. 
 *
 *					This routine MUST be used to test commands under the
 *					Simulator since it can't launch application databases. 
 *
 * CALLED BY:		StdIO Provider apps that wish to provide built-in
 *					commands. 
 *
 * RETURNED:    	void
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 ***********************************************************************/
typedef struct {
	const Char *				nameP;							// command name
	SioMainProcPtr		procP;							// procedure
	} SioTableEntryType;
#define					kMaxCommands 	100				// Max # of commands
static UInt16				GPrvNumCommands = 0;
SioTableEntryType		GPrvCmdTable[kMaxCommands];		// command table
	
void SioAddCommand(const Char * cmdStr, SioMainProcPtr procP)
{
	if (GPrvNumCommands >= kMaxCommands-1) {
		ErrDisplay("Too many commands");
		return;
		}
		
	GPrvCmdTable[GPrvNumCommands].nameP = cmdStr;
	GPrvCmdTable[GPrvNumCommands++].procP = procP;
	

}


/******************************************************************************
 * FUNCTION:		SioExecCommand
 *
 * DESCRIPTION:		Execute a command line.
 *
 *					This routine will first look for a built-in command
 *					installed using SioAddCommand(). 
 *
 *					If none found, it will look for a Palm StdIO app
 *					database with the name "Cmd-<cmdname>" where <cmdname> is the
 *					first word in the command string. 
 *					
 *
 * CALLED BY:		system() glue code in StdIOPalm.c through the
 *					PrvSystemProc callback procedure.
 *
 *					Also called by Stdio provider apps to execute commands
 *					without the extra overhead of the system() call. 
 *					
 *
 * PARAMETERS:		cmdStrP		-> command string to execute
 *
 * RETURNED:    	>=0 on success
 *					<0 on failure.
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 *****************************************************************************/
Int16 SioExecCommand(const Char * cmdParamP)
{
	const int	maxArgc=10;
	const Char *		argv[maxArgc+1];
	int			argc;
	Boolean		done = false;
	UInt16		i;
	Char *		cmdBufP = 0;
	Char *		cmdP;
	Int16		result=0;
#if EMULATION_LEVEL == EMULATION_NONE
	Char		dbName[dmDBNameLength];
	LocalID		dbID;
	UInt16		cardNo;
	Err			err;
#endif


	// if null string, return
	if (!cmdParamP[0]) return -1;

	
	// Make a copy of the command since we'll need to write
	// 0's between the words and it might be from read-only space
	cmdP = cmdBufP = MemPtrNew(StrLen(cmdParamP) + 1);
	if (!cmdP) {
		printf("\nOut of memory\n");
		goto Exit;
		}
	MemMove(cmdP, cmdParamP, StrLen(cmdParamP) + 1);

	// Separate the cmd line into arguments
	argc = 0;
	argv[0] = 0;
	for (argc=0; !done && argc<=maxArgc; argc++) {
	
		// Skip leading spaces
		while((*cmdP == ' ' || *cmdP == '\t') && (*cmdP != 0))
			cmdP++;
			
		// Break out on null
		if (*cmdP == 0)
			break;
		
		// Get pointer to command
		argv[argc] = cmdP;
		if (*cmdP == 0) 
			break;
		
		// Find the end of a quoted argument
		if (*cmdP == '"') {
			cmdP++;
			argv[argc] = cmdP;
			while ( true ) {
				
				if (*cmdP == '"') {
					*cmdP = 0; 
					// Advance to the next argument.
					cmdP++;
					break;
					}
				
				if (*cmdP == 0) {
					done = true; 
					break;
					}
					
				cmdP++;
				}
			}
			
		// Find the end of an unquoted argument
		else {
			while ( true ) {
			
				if (*cmdP == 0) {
					done = true; 
					break;
					}

				if ((*cmdP == ' ') || (*cmdP == '\t')) {
					*cmdP = 0;
					// Advance to the next argument.
					cmdP++;
					break;
					}

				cmdP++;
				}
			}
		}
	
	// Return if no arguments
	if (!argc) {
		result = -1; 
		goto Exit;
		}
		

	//==================================================================
	// Call the appropriate routine
	//==================================================================
	// Pass in the argc and argv
	GAppSioGlobalsP->argc = argc;
	GAppSioGlobalsP->argv = argv;	
		
	
	// ------------------------------------------------------
	// Look for the help command
	// ------------------------------------------------------
	if (!StrCompare(argv[0], "help") || !StrCompare(argv[0], "?")) {
	
		// If asking about a particular command, get extended help (??)
		if (argc > 1) {
			argv[0] = argv[1];
			argv[1] = "??";
			}
			
		// Else, display 1 line help (?)
		else {
			Boolean helpDone = false;
			Boolean internalHelp = true;
#if EMULATION_LEVEL == EMULATION_NONE
			Boolean newSearch = true;
			DmSearchStateType searchState;
#endif
			for (i = 0; !helpDone; ) {
				if (internalHelp) {
					argv[0] = GPrvCmdTable[i].nameP;
					argv[1] = "?";
					(GPrvCmdTable[i].procP)(2, argv);
					if (++i == GPrvNumCommands) {
#if EMULATION_LEVEL == EMULATION_NONE
						// Now list the stdio apps
						internalHelp = false;
#else
						// All done
						helpDone = true;
#endif
						}
					}
#if EMULATION_LEVEL == EMULATION_NONE
				else {
					err = DmGetNextDatabaseByTypeCreator
						(newSearch, &searchState, sioDBType, 0, true, &cardNo, &dbID);
					newSearch = false;
					if (!err) {
						err = DmDatabaseInfo
							(cardNo, dbID, dbName, NULL, NULL, NULL,
							 NULL, NULL, NULL, NULL, NULL, NULL, NULL);
						if (!err) {
							// If name is long enough and begins with 'Cmd-'
							// then display the command name that follows
							if ((StrLen(dbName) > 4) && (!MemCmp(dbName, "Cmd-", 4))) {
								printf("%s\n", &dbName[4]);
								i++;
								}
							}
						}
					if (err) {
						// All done, either end of list or an error
						helpDone = true;
						}
					}
#endif
				
				// Pause after every "page"
				if (i > 0 && (i % 8) == 0) {
					printf("<cr> to continue...");
					if (getchar() != '\n') break;
					printf("\n");
					}
				}
			printf("\n");
			goto Exit;
			}
		}
		
	// ------------------------------------------------------
	// if not help, look for this command in our built-in table of commands
	// ------------------------------------------------------
	for (i=0; i<GPrvNumCommands; i++) {
		if (!StrCompare(argv[0], GPrvCmdTable[i].nameP)) {
			result = (GPrvCmdTable[i].procP)(argc, argv);
			goto Exit;
			}
		}
	
	// ------------------------------------------------------
	// If not found in our built-in commands, look for a separate
	//  executable
	// ------------------------------------------------------
#if EMULATION_LEVEL == EMULATION_NONE
	{
		UInt32		dbType;
		UInt32		dwResult;

		StrCopy(dbName, "Cmd-");
		StrNCat(dbName, argv[0], dmDBNameLength);
		
		// Look for this database
		cardNo = 0;
		dbID = DmFindDatabase(cardNo, dbName);
		if (!dbID) goto NotFound;
		
		// Make sure it's a standard IO app
		err = DmDatabaseInfo(cardNo, dbID, 0, 0, 0, 0,
				0, 0,
				0, 0,
				0, &dbType, 0);
		if (err) goto NotFound;
		if (dbType != sioDBType) goto NotFound;
			
		
		// Execute it. 
		err = SysAppLaunch(cardNo, dbID, sysAppLaunchFlagNewGlobals |
				sysAppLaunchFlagNewStack, sysAppLaunchCmdNormalLaunch, 
				(MemPtr)GAppSioGlobalsP /*cmdPBP*/, &dwResult);
		if (!err) result = (Int32)dwResult;
		goto Exit;
	}
#endif
	
NotFound:	
	printf("Unknown command: %s\n", argv[0]);
	
Exit:
	if (cmdBufP) MemPtrFree(cmdBufP);
	return result;		
}




/******************************************************************************
 * FUNCTION:		SioClearScreen
 *
 * DESCRIPTION:		Clear the entire Sio display area
 *					
 *
 * CALLED BY:		Stdio provider app
 *					
 *
 * PARAMETERS:		void
 *
 * RETURNED:    	void
 *
 * REVISION HISTORY:
 *			Name	Date		Description
 *			----	----		-----------
 *			ron		5/6/98		Initial Revision
 *****************************************************************************/
void SioClearScreen(void)
{
	SioProvGlobalsPtr	gP = (SioProvGlobalsPtr)GAppSioGlobalsP;

	if (FrmGetActiveFormID() == gP->formID) {
		PrvSetFieldText(gP->formID, NULL, false, true);
		PrvFormUpdateScroller (gP, FrmGetActiveForm());
		}
	else {
		if (gP->textH) MemHandleFree(gP->textH);
		gP->textH = NULL;
		}
}





