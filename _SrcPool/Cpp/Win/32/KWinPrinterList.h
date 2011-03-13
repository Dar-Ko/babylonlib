#pragma once

#include <atlmisc.h> //CString included with WTL
/*
Installed Printers List
By Rob Caldecott
http://www.codeproject.com/KB/wtl/wtlinstalledprinters.aspx

PRINTER_INFO_5 structure or PRINTER_INFO_4 struct Depends of Windows version
 */
class CPrinterList : public CSimpleArray<CString>
{
public:
  CInstalledPrinters(void)
  {
    GetPrinters();
  }

  void GetPrinters(void)
  {
    DWORD dwSize = 0;
    DWORD dwPrinters = 0;
    // Enumerate all installed printers
    if (!::EnumPrinters(PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS, NULL,
      5, NULL, 0, &dwSize, &dwPrinters))
    {
      // Check for ERROR_INSUFFICIENT_BUFFER
      // If something else, then quit
      if (::GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        return;
      // Fall through
    }
    // Allocate some buffer memory
    LPBYTE pBuffer = new BYTE [dwSize];
    if (pBuffer == NULL)
      return;
    // Fill the buffer
    // Again, this depends on the O/S
    if (!::EnumPrinters(PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS, NULL,
      5, pBuffer, dwSize, &dwSize, &dwPrinters))
    {
      // Error - unlikely though
      // as first call to EnumPrinters
      // succeeded!
      return;
    }
    // Do we have any printers?
    if (dwPrinters == 0)
      return;
    // Cast to PRINTER_INFO_2
    PRINTER_INFO_5* pInfo = (PRINTER_INFO_5*)pBuffer;
    // Loop adding the printers to the list
    for (DWORD i = 0; i < dwPrinters; i++, pInfo++)
      Add(CString(pInfo->pPrinterName));
    delete [] pBuffer;
  }
};
///////////////////////////////////////////////////////////////////////////////
/*
typedef std::vector  VString;
bool SetCurrentDefaultPrinter         (const std::string& s_printer_name)
{
  SetDefaultPrinter(s_printer_name.c_str());

  return true;
}

bool GetDefaultPrinter              (std::string& s_printer_name)
{
  s_printer_name = "";
  CPrintDialog cpd(FALSE);
  if(!cpd.GetDefaults())
  {
    return false;
  }

  s_printer_name = cpd.GetDeviceName();
  return true;
}

bool GetPrinterList               (VString& v_printers)
{
  v_printers.clear();

  DWORD dwSize = 0;
  DWORD dwPrinters = 0;
  // Enumerate all installed printers
  if (!::EnumPrinters(PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS,
    NULL, 4, NULL, 0, &dwSize, &dwPrinters))
  {
    // Check for ERROR_INSUFFICIENT_BUFFER
    // If something else, then quit
    if (::GetLastError() != ERROR_INSUFFICIENT_BUFFER)
      return false;
  // Fall through
  }

  // Allocate some buffer memory
  LPBYTE pBuffer = new BYTE [dwSize];
  if (pBuffer == NULL)
    return false;

  // Fill the buffer
  // Again, this depends on the O/S
  if (!::EnumPrinters(PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS ,
    NULL, 4, pBuffer, dwSize, &dwSize, &dwPrinters))
  {
    // Error - unlikely though
    // as first call to EnumPrinters
    // succeeded!
    return false;
  }

  // Do we have any printers?
  if (dwPrinters == 0)
    return false;

  // Cast to PRINTER_INFO_2
  PRINTER_INFO_4* pInfo = (PRINTER_INFO_4*)pBuffer;
  // Loop adding the printers to the list
  for (DWORD i = 0; i < dwPrinters; i++, pInfo++)
  {
    std::string s_printer_name = pInfo->pPrinterName;
    v_printers.push_back(s_printer_name);
  }

  return true;
}
*/