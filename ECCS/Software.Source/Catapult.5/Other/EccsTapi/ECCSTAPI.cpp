// ECCSTAPI.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}


int WINAPI DialCall(char *x,int x1, int x2, int x3)
{
	MessageBox(NULL, "Call ECCS", "", 1); 
	return 0;
}

int WINAPI PhoneCall(char *x,int x1, int x2, int x3, int x4, int x5)
{
	MessageBox(NULL, "PhoneCall ECCS", "", 1); 
	return 0;
}