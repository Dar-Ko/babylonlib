/*$Workfile: S:\_SrcPool\Cpp\Platform\UsbVid046D.h$: header file
  $Revision: 1.3 $ $Date: 2007/09/06 01:20:34 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2004-03-10 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID046D_H_
  //$Workfile: S:\_SrcPool\Cpp\Platform\UsbVid046D.h$ sentry
  #define _USBVID046D_H_

/*1133.	USB device vendor identification (VID) number	Logitech Inc.	http://www.logitech.com/

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_LOGITECH 0x046D
#define USBVID_046D _T("Logitech Inc.") //VID 1133 Vendor name

#define USBPID_M2452KBD                      0x0203 //M2452 Keyboard
#define USBPID_M4848MOUSE                    0x0301 //M4848 Mouse
#define USBPID_PAGESCANHP                    0x0401 //Logitech/SHP PageScan
#define USBPID_PAGESCANNEC                   0x0402 //Logitech/SNEC PageScan
#define USBPID_PAGESCANSTORM                 0x040F //Logitech/Storm PageScan
#define USBPID_QUICKCAMHOME                  0x0801 //QuickCam Home
#define USBPID_QUICKCAMPRO0                  0x0810 //QuickCam Pro
#define USBPID_QUICKCAMEXPRESS40             0x0840 //QuickCam Express
#define USBPID_QUICKCAMWEB                   0x0850 //QuickCam Web
#define USBPID_QUICKCAMEXPRESS70             0x0870 //QuickCam Express
#define USBPID_QUICKCAMTRAVELER              0x0890 //QuickCam Traveler
#define USBPID_QUICKCAMIM                    0x08A0 //QuickCam IM
#define USBPID_LABTECWEBCAMPRO               0x08A2 //Labtec WebCam Pro
#define USBPID_QUICKCAM3000PRO               0x08B0 //QuickCam 3000 Pro [pwc]
#define USBPID_QUICKCAMNOTEBOOKPRO           0x08B1 //QuickCam Notebook Pro
#define USBPID_QUICKCAMPRO4000               0x08B2 //QuickCam Pro 4000
#define USBPID_QUICKCAMZOOM3                 0x08B3 //QuickCam Zoom
#define USBPID_QUICKCAMZOOM4                 0x08B4 //QuickCam Zoom
#define USBPID_QUICKCAMSPHERE                0x08B5 //QuickCam Sphere
#define USBPID_QUICKCAMCONNECT               0x08D9 //QuickCam Connect
#define USBPID_QUICKCAMMESSANGER0            0x08DA //QuickCam Messanger
#define USBPID_QUICKCAMMESSENGERA            0x08F0 //QuickCam Messenger
#define USBPID_CLICKSMART310                 0x0900 //ClickSmart 310
#define USBPID_CLICKSMART510                 0x0901 //ClickSmart 510
#define USBPID_CLICKSMART820                 0x0903 //ClickSmart 820
#define USBPID_CLICKSMART820                 0x0905 //ClickSmart 820
#define USBPID_QUICKCAMEXPRESS20             0x0920 //QuickCam Express
#define USBPID_LABTECWEBCAM                  0x0921 //Labtec WebCam
#define USBPID_QUICKCAMEXPRESS28             0x0928 //Quickcam Express
#define USBPID_QUICKCAMNOTEBOOKS             0x092A //QuickCam for Notebooks
#define USBPID_QUICKCAMEXPRESSPLUS           0x092F //QuickCam express Plus
#define USBPID_POCKETCAMERA                  0x0950 //Pocket Camera
#define USBPID_CLICKSMART420                 0x0960 //ClickSmart 420
#define USBPID_POCKET750                     0x0970 //Pocket750
#define USBPID_LOGITECHUSBHEADSET            0x0A01 //Logitech USB Headset
#define USBPID_MOUSEPREMIUMOPTICALWHEEL      0xBFE4 //Premium Optical Wheel Mouse
#define USBPID_MOUSEPILOTN43                 0xC000 //N43 Pilot Mouse
#define USBPID_MOUSEN48                      0xC001 //N48/M-BB48 FirstMouse Plus
#define USBPID_MOUSEMANMBA47                 0xC002 //M-BA47 MouseMan Plus
#define USBPID_MOUSEWINGMANGAMING            0xC004 //WingMan Gaming Mouse
#define USBPID_MOUSEMANWHEEL                 0xC00B //MouseMan Wheel
#define USBPID_MOUSEOPTICALWHEEL             0xC00C //Optical Wheel Mouse
#define USBPID_MOUSEMBJ69OPTICAL             0xC00E //M-BJ69 Optical Wheel Mouse
#define USBPID_MOUSEOPTICAL                  0xC012 //Optical Mouse
#define USBPID_MOUSEMUV69AOPTICAL            0xC016 //M-UV69a Optical Wheel Mouse
#define USBPID_MOUSEMX310                    0xC01B //MX310 Optical Mouse
#define USBPID_MOUSEMX510                    0xC01D //MX510 Optical Mouse
#define USBPID_MOUSEMX518                    0xC01E //MX518 Optical Mouse
#define USBPID_MOUSEMX500                    0xC025 //MX500 Optical Mouse
#define USBPID_MOUSEIFEEL                    0xC030 //iFeel Mouse
#define USBPID_MOUSEMANIFEEL                 0xC032 //MouseMan iFeel
#define USBPID_MOUSEPREMIUMOPTICAL           0xC03E //Premium Optical Wheel Mouse
#define USBPID_WINGMANFORMULA                0xC202 //WingMan Formula
#define USBPID_WINGMANEXTREMEDIGITAL3D       0xC207 //WingMan Extreme Digital 3D
#define USBPID_WINGMANGAMEPADEXTREME         0xC208 //WingMan Gamepad Extreme
#define USBPID_WINGMANGAMEPAD                0xC209 //WingMan Gamepad
#define USBPID_WINGMANRUMBLEPAD              0xC20A //WingMan RumblePad
#define USBPID_WINGMANPRECISION              0xC20C //WingMan Precision
#define USBPID_WINGMANATTACK                 0xC20D //WingMan Attack 2
#define USBPID_ITOUCHCORDLESSRECIEVER        0xC211 //iTouch Cordless Reciever
#define USBPID_DUALACTIONGAMEPAD             0xC216 //Dual Action Gamepad
#define USBPID_RUMBLEPAD2                    0xC218 //Logitech RumblePad 2 USB
#define USBPID_WINGMANFORCE                  0xC281 //WingMan Force
#define USBPID_WINGMANFORCE3D                0xC283 //WingMan Force 3D
#define USBPID_WINGMANSTRIKEFORCE3D          0xC285 //WingMan Strike Force 3D
#define USBPID_WINGMANFORMULAFORCE           0xC291 //WingMan Formula Force
#define USBPID_WINGMANFORMULAFORCEGP         0xC293 //WingMan Formula Force GP
#define USBPID_MOMOFORCESTEERINGWHEEL        0xC295 //Momo Force Steering Wheel
#define USBPID_MOUSEWINGMANFORCEFEEDBACK     0xC2A0 //Wingman Force Feedback Mouse
#define USBPID_ITOUCHKEYBOARD                0xC303 //iTouch Keyboard
#define USBPID_KBDINTERNETNAVIGATOR          0xC308 //Internet Navigator Keyboard
#define USBPID_KBDINTERNET                   0xC309 //Internet Keyboard
#define USBPID_TRACKMANMARBLEWHEEL           0xC401 //TrackMan Marble Wheel
#define USBPID_MOUSEMARBLE2BUTTON            0xC402 //Marble Mouse (2-button)
#define USBPID_TRACKMANWHEEL                 0xC404 //TrackMan Wheel
#define USBPID_MOUSEMARBLE4BUTTON            0xC408 //Marble Mouse (4-button)
#define USBPID_MOUSECORDLESSRECEIVER         0xC501 //Cordless Mouse Receiver
#define USBPID_MOUSEKBDCORDLESSRECEIVER3     0xC503 //Cordless Mouse+Keyboard Receiver
#define USBPID_MOUSEKBDCORDLESSRECEIVER4     0xC504 //Cordless Mouse+Keyboard Receiver
#define USBPID_MOUSEKBDCORDLESSRECEIVER5     0xC505 //Cordless Mouse+Keyboard Receiver
#define USBPID_MOUSECORDLESSRECEIVERMX700    0xC506 //MX-700 Cordless Mouse Receiver
#define USBPID_CORDLESSDESKTOPOPTICAL        0xC50B //Cordless Desktop Optical
#define USBPID_MOUSECORDLESSRECEIVERMX1000   0xC50E //MX-1000 Cordless Mouse Receiver
#define USBPID_MOUSECORDLESSMX610            0xC518 //MX610 Laser Cordless Mouse
#define USBPID_FORMULAVIBRATIONFEEDBACKWHEEL 0xCA04 //Formula Vibration Feedback Wheel
#define USBPID_QUICKCAMPRO1                  0xD001 //QuickCam Pro

///////////////////////////////////////////////////////////////////////////////
#endif //_USBVID046D_H_
/*****************************************************************************
 * $Log:
 *  1    Biblioteka1.0         22/08/2007 10:51:35 AMDarko Kolakovic
 * $
 * Revision 1.1  2007/08/17 21:15:42  ddarko
 * Created
 *
 *****************************************************************************/
