// variant that supports bool (checked/not-checked, no intermediate state)
void DDX_Check(CDataExchange* pDX, int nIDC, bool& bCheck)
//(UINT nID, bool& bCheck, BOOL bSave)
{
int nValue = bCheck ? 1 : 0;
DDX_Check(pDX, nIDC, nValue);
if(pDX->m_bSaveAndValidate)
  {
  if(nValue > 1)
    ATLTRACE(("  Warning: checkbox state (%d) out of supported range.\n"), nValue);
  bCheck = (nValue != 0);
  }
}