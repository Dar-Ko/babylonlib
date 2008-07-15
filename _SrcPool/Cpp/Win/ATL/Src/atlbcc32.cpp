
extern "C" void __declspec(naked) __stdcall CComStdCallThunkHelper()
{
        __asm
        {
                mov eax, [esp+4];       // get pThunk
                mov edx, [eax+4];       // get the pThunk->pThis
                mov [esp+4], edx;       // replace pThunk with pThis
                mov eax, [eax+8];       // get pThunk->pfn
                jmp eax;                // jump pfn
        };
}

////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 * $Log: atlbcc32.cpp,v $
 * Revision 1.2  2008/07/15 20:37:11  ddarko
 * Borland CC build and fixes
 *
 * Revision 1.1.2.2  2008/07/15 15:42:57  ddarko
 * ATL 3.00 Platform SDK (R2 3790.2075) 2006-03 / Borland CC build
 *
 *****************************************************************************/
