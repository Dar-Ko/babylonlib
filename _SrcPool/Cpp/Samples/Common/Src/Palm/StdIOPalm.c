/******************************************************************************
 *
 * Copyright (c) 1996-1999 Palm, Inc. or its subsidiaries.
 * All rights reserved.
 *
 * File: StdIOPalm.c
 *
 * Release: Palm OS SDK 4.0 (63220)
 *
 * Description:
 *	  This module is designed to be linked in with Palm standard IO 
 *  applications. 
 *
 *	  A PalmOS standard IO app is built like a normal PalmOS app but has
 *	a database type of 'sdio' instead of 'appl'. In addition, it must
 *	be named "Cmd-<cmdname>" where <cmdname> is the name of the command that
 *	users will enter to execute the command. For example, the 'ping' command
 * would be placed in a database named "Cmd-ping". 
 *
 *	  Standard IO apps must link with this module. It contains the
 *  glue code necessary to extract the command line arguments from the cmd and
 *	cmdPBP parameters passed in to PilotMain and to map standard IO calls
 *  to the appropriate callback 
 *
 *	  See the comments in <StdIOPalm.h> for more info...
 *
 * History:
 *	5-6-98	RM		Created by Ron Marianetti
 *
 *****************************************************************************/

#include <StringMgr.h>
#include <SystemMgr.h>
#include <unix_stdarg.h>

#define	 _STDIO_PALM_C_
#include <StdIOPalm.h>


/*********************************************************************
 * Globals
 *******************************************************************/
 
// This global is setup in PilotMain from the cmdPBP parameter that
//  is passed in by the Standard IO provider. 
SioGlobalsPtr		GAppSioGlobalsP;



/***********************************************************************
 *
 * FUNCTION:		Siofgetc
 *
 * DESCRIPTION:		See K&R
 *
 ***********************************************************************/
Int16 Siofgetc (FILE*	fs)
{	
	// Call the callback
	return (*GAppSioGlobalsP->fgetcProcP)(GAppSioGlobalsP, fs);
}



/***********************************************************************
 *
 * FUNCTION:		Siofgets
 *
 * DESCRIPTION:		See K&R
 *
 ***********************************************************************/
Char *		Siofgets(Char * strP, UInt16 maxChars, FILE* fs)
{	
	// Call the callback
	return (*GAppSioGlobalsP->fgetsProcP)
				(GAppSioGlobalsP, strP, maxChars, fs);
}


/***********************************************************************
 *
 * FUNCTION:		Siofputc
 *
 * DESCRIPTION:		See K&R
 *
 ***********************************************************************/
Int16 Siofputc (Int16 c, FILE* fs)
{	
	// Call the callback
	return (*GAppSioGlobalsP->fputcProcP)(GAppSioGlobalsP, c, fs);
}


/***********************************************************************
 *
 * FUNCTION:		Siofputs
 *
 * DESCRIPTION:		See K&R
 *
 ***********************************************************************/
Int16 Siofputs (const Char * strP, FILE* fs)
{	
	// Call the callback
	return (*GAppSioGlobalsP->fputsProcP)(GAppSioGlobalsP, strP, fs);
}




/******************************************************************************
 * FUNCTION:		Siofprintf
 *
 * DESCRIPTION:		See K&R
 *
 *****************************************************************************/
Int16	Siofprintf(FILE* fs, const Char * formatP, ...)
{
	va_list			args;
	Int16			result;
	
	va_start(args, formatP);
	result = (*GAppSioGlobalsP->vfprintfProcP)
					(GAppSioGlobalsP, fs, formatP, args);
	va_end(args);
	
	return result;
}


/******************************************************************************
 * FUNCTION:		Siovfprintf
 *
 * DESCRIPTION:		See K&R
 *
 *****************************************************************************/
Int16	Siovfprintf(FILE* fs, const Char * formatP, va_list args)
{
	
	return (*GAppSioGlobalsP->vfprintfProcP)
					(GAppSioGlobalsP, fs, formatP, args);
	
}


/******************************************************************************
 * FUNCTION:		Sioprintf
 *
 * DESCRIPTION:		See K&R
 *
 *****************************************************************************/
Int16	Sioprintf(const Char * formatP, ...)
{
	va_list			args;
	Int16			result;

	va_start(args, formatP);
	result = (*GAppSioGlobalsP->vfprintfProcP)
					(GAppSioGlobalsP, stdout, formatP, args);
	va_end(args);
	
	return result;
}


/******************************************************************************
 * FUNCTION:		Sioputs
 *
 * DESCRIPTION:		See K&R
 *
 *****************************************************************************/
Int16		Sioputs(const Char * strP)
{
	Int16	result;
	
	// "put" the string
	result = (*GAppSioGlobalsP->fputsProcP)(GAppSioGlobalsP, strP, stdout);
	if (result < 0) return result;
	
	// and a new line
	result = (*GAppSioGlobalsP->fputcProcP)(GAppSioGlobalsP, '\n', stdout);
	return result;
}

/******************************************************************************
 * FUNCTION:		Siogets
 *
 * DESCRIPTION:		See K&R
 *
 *****************************************************************************/
Char *		Siogets(Char * strP)
{
	Char *	result;
	UInt16	len;
	
	// "get" the string
	result = fgets(strP, 255, stdin);
	if (!result)  return result;
	
	// Replace newline with 0
	len = StrLen(strP);
	if (len)
	strP[len-1] = 0;

	return strP;	
}

/******************************************************************************
 * FUNCTION:		Siosystem
 *
 * DESCRIPTION:		See K&R
 *
 *****************************************************************************/
Int16		Siosystem(const Char * strP)
{
	return (*GAppSioGlobalsP->systemProcP)(GAppSioGlobalsP, strP);
}




/***********************************************************************
 *
 *  Pilot Main Entry Point
 *
 *	This standard PilotMain entry point is provided for stdio client apps
 *
 ***********************************************************************/
#if 	EMULATION_LEVEL == EMULATION_NONE
#ifndef	STDIO_PALM_PROVIDER


// Global used by stdio for errors
Err		errno;


/***********************************************************************
 *
 * FUNCTION:    PilotMain
 *
 * DESCRIPTION: This is the main entry point for a stdio app. It
 *		sets winUp the GAppSioGlobalsP global used by the stdio glue
 *		code routines then jumps to the routine named SioMain() which
 *		must be provided by the developer.
 *
 *
 * PARAMETERS:  cmd			-> action code
 *				cmdPBP		-> parameter block, GAppSioGlobalsP setup by
 *								stdio provider app when cmd is 
 *								sysAppLaunchCmdNormalLaunch
 *				launchFlags	-> SysAppLaunch flags. 
 *
 * RETURNED:    0 if no err
 *
 * REVISION HISTORY:
 *         Name   Date      Description
 *         ----   ----      -----------
 *			ron		5/6/98		Initial Revision
 *
 ***********************************************************************/
UInt32   PilotMain (UInt16 cmd, void *cmdPBP, UInt16 launchFlags)
{
	
	switch (cmd) {
      	case sysAppLaunchCmdNormalLaunch:
			GAppSioGlobalsP = (SioGlobalsPtr)cmdPBP;   
			if (!GAppSioGlobalsP) return -1;
      		return SioMain(GAppSioGlobalsP->argc, GAppSioGlobalsP->argv);
        	break;
		
		}
		
	return 0;
}

#endif
#endif	//EMULATION_LEVEL
