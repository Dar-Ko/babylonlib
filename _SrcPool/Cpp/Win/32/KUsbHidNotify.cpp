extern "C"
  {
  #include <hidsdi.h> /* note: part of Windows DDK */
  #pragma warning(disable: 4201) //warning C4201: nonstandard extension used : nameless struct/union
    #include <hidpi.h>  /* note: also part of Windows DDK */
  #pragma warning(default: 4201)
  }

//-----------------------------------------------------------------------------
/*Registers the USB HID type of device for which a window will receive notifications.
 */
BOOL UsbHidNotify(HWND hWnd, //[in] handle to the window or service that will
                       //receive device events for the devices specified
                       PVOID hDevNotify //[out] device notification handle or NULL
                       )
{
ATLTRACE(_T("SetHidDeviceNotify()\n"));
GUID guidHid;                   //temporarily stores Windows HID Class GUID
DEV_BROADCAST_DEVICEINTERFACE NotificationFilter; // un/plug notification filter

HidD_GetHidGuid(&guidHid);

ZeroMemory( &NotificationFilter, sizeof(NotificationFilter));
NotificationFilter.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
NotificationFilter.dbcc_classguid = guidHid;

hDevNotify = RegisterDeviceNotification(hWnd, &NotificationFilter,
                                       DEVICE_NOTIFY_WINDOW_HANDLE);

if(hDevNotify == NULL)
  return FALSE;

return TRUE;
}
