/*$Workfile: UsbVid046D.h$: header file
  $Revision: 1.5 $ $Date: 2008/09/04 21:14:48 $
  $Author: ddarko $

  Universal Serial Bus (USB) vendor specific device identification
  Copyright: CommonSoft Inc.
  2004-03-10 Darko Kolakovic
 */

/* Group=USB ID                                                              */

#ifndef _USBVID046D_H_
  //$Workfile: UsbVid046D.h$ sentry
  #define _USBVID046D_H_

/*1133.	USB device vendor identification (VID) number	Logitech Inc.	http://www.logitech.com/

  See also: usb-if.tsv, USB Implementers Forum, Inc (USB-IF) at http://www.usb.org
 */
#define USBVID_LOGITECH 0x046D
#define USBVID_046D _T("Logitech Inc.") //VID 1133 Vendor name

#define USBPID_ACERASPIRE5672WEBCAM             0x0082 //Acer Aspire 5672 Webcam
#define USBPID_WINGMANEXTREMEJOYSTICK           0x0200 //WingMan Extreme Joystick
#define USBPID_M2452KBD                         0x0203 //M2452 Keyboard
#define USBPID_M4848MOUSE                       0x0301 //M4848 Mouse
#define USBPID_PAGESCANHP                       0x0401 //Logitech/SHP PageScan
#define USBPID_PAGESCANNEC                      0x0402 //Logitech/SNEC PageScan
#define USBPID_PAGESCANSTORM                    0x040F //Logitech/Storm PageScan
#define USBPID_MICCORDLESS                      0x0430 //Microphone Cordless
#define USBPID_QUICKCAMHOME                     0x0801 //QuickCam Home
#define USBPID_QUICKCAMPRO0                     0x0810 //QuickCam Pro
#define USBPID_QUICKCAMVC                       0x0820 //QuickCam VC
#define USBPID_QUICKCLIP                        0x0830 //QuickClip
#define USBPID_QUICKCAMEXPRESS40                0x0840 //QuickCam Express
#define USBPID_QUICKCAMWEB                      0x0850 //QuickCam Web
#define USBPID_QUICKCAMEXPRESS70                0x0870 //QuickCam Express
#define USBPID_QUICKCAMTRAVELER                 0x0890 //QuickCam Traveler
#define USBPID_ORBICAM                          0x0892 //OrbiCam
#define USBPID_CRYSTALCAM                       0x0894 //CrystalCam
#define USBPID_QUICKCAMDELL1                    0x0895 //QuickCam for Dell Notebooks
#define USBPID_ORBICAM                          0x0896 //OrbiCam
#define USBPID_QUICKCAMDELL2                    0x0897 //QuickCam for Dell Notebooks
#define USBPID_QUICKCAMDELL3                    0x0899 //QuickCam for Dell Notebooks
#define USBPID_QUICKCAMIM                       0x08A0 //QuickCam IM
#define USBPID_QUICKCAMIMWITHSOUND              0x08A1 //QuickCam IM with sound
#define USBPID_LABTECWEBCAMPRO                  0x08A2 //Labtec WebCam Pro
#define USBPID_QUICKCAMQUICKCAMCHAT             0x08A3 //QuickCam QuickCam Chat
#define USBPID_QUICKCAMIM                       0x08A6 //QuickCam IM
#define USBPID_QUICKCAMIMAGE                    0x08A7 //QuickCam Image
#define USBPID_NOTEBOOKDELUXE                   0x08A9 //Notebook Deluxe
#define USBPID_LABTECNOTEBOOKS                  0x08AA //Labtec Notebooks
#define USBPID_QUICKCAMCOOL                     0x08AC //QuickCam Cool
#define USBPID_QUICKCAMCOMMUNICATESTX           0x08AD //QuickCam Communicate STX
#define USBPID_QUICKCAMFORNOTEBOOKS             0x08AE //Quickcam for Notebooks
#define USBPID_QUICKCAMEASYCOOL                 0x08AF //QuickCam Easy/Cool
#define USBPID_QUICKCAM3000PRO                  0x08B0 //QuickCam 3000 Pro [pwc]
#define USBPID_QUICKCAMNOTEBOOKPRO              0x08B1 //QuickCam Notebook Pro
#define USBPID_QUICKCAMPRO4000                  0x08B2 //QuickCam Pro 4000
#define USBPID_QUICKCAMZOOM3                    0x08B3 //QuickCam Zoom
#define USBPID_QUICKCAMZOOM4                    0x08B4 //QuickCam Zoom
#define USBPID_QUICKCAMSPHERE                   0x08B5 //QuickCam Sphere
#define USBPID_MICPRO4000                       0x08BD //Microphone Pro 4000
#define USBPID_QUICKCAMPRO3000                  0x08C0 //QuickCam Pro 3000
#define USBPID_QUICKCAMFUSION                   0x08C1 //QuickCam Fusion
#define USBPID_QUICKCAMPTZ                      0x08C2 //QuickCam PTZ
#define USBPID_CAMERANOTEBOOKSPRO               0x08C3 //Camera Notebooks Pro
#define USBPID_QUICKCAMPRO5000                  0x08C5 //QuickCam Pro 5000
#define USBPID_QUICKCAMDELL4                    0x08C6 //QuickCam for Dell Notebooks
#define USBPID_QUICKCAMULTRAVISION              0x08C9 //QuickCam Ultra Vision
#define USBPID_MICFUSION                        0x08CA //Microphone Fusion
#define USBPID_MICNOTEBOOKSPRO                  0x08CB //Microphone Notebooks Pro
#define USBPID_MICPTZ                           0x08CC //Microphone PTZ
#define USBPID_QUICKCAMPRO5000                  0x08CE //QuickCam Pro 5000
#define USBPID_QUICKCAM1                        0x08CF //QuickCam FixMe!
#define USBPID_QUICKCAMEXPRESS1                 0x08D0 //QuickCam Express
#define USBPID_QUICKCAMCOMMUNICATESTX           0x08D7 //QuickCam Communicate STX
#define USBPID_QUICKCAMFORNOTEBOOKDELUXE        0x08D8 //QuickCam for Notebook Deluxe
#define USBPID_QUICKCAMIMCONNECT                0x08D9 //QuickCam IM/Connect
#define USBPID_QUICKCAMCONNECT                  0x08D9 //QuickCam Connect
#define USBPID_QUICKCAMMESSANGER0               0x08DA //QuickCam Messanger
#define USBPID_QUICKCAMFORNOTEBOOKS             0x08DD //QuickCam for Notebooks
#define USBPID_QUICKCAMEXPRESS2                 0x08E0 //QuickCam Express
#define USBPID_LABTECWEBCAM2                    0x08E1 //Labtec WebCam
#define USBPID_QUICKCAMMESSENGERA               0x08F0 //QuickCam Messenger
#define USBPID_QUICKCAMEXPRESS                  0x08F1 //QuickCam Express
#define USBPID_MICMESSENGER                     0x08F2 //Microphone Messenger
#define USBPID_QUICKCAMEXPRESS3                 0x08F3 //QuickCam Express
#define USBPID_LABTECWEBCAM2                    0x08F4 //Labtec WebCam
#define USBPID_QUICKCAMMESSENGERCOMMUNICATE     0x08F5 //QuickCam Messenger Communicate
#define USBPID_QUICKCAMMESSENGERPLUS            0x08F6 //Quickcam Messenger Plus
#define USBPID_CLICKSMART310                    0x0900 //ClickSmart 310
#define USBPID_CLICKSMART510                    0x0901 //ClickSmart 510
#define USBPID_CLICKSMART820                    0x0903 //ClickSmart 820
#define USBPID_CLICKSMART820                    0x0905 //ClickSmart 820
#define USBPID_QUICKCAMCORDLESS                 0x0910 //QuickCam Cordless
#define USBPID_QUICKCAMEXPRESS20                0x0920 //QuickCam Express
#define USBPID_LABTECWEBCAM                     0x0921 //Labtec WebCam
#define USBPID_QUICKCAMLIVE                     0x0922 //QuickCam Live
#define USBPID_QUICKCAMEXPRESS28                0x0928 //Quickcam Express
#define USBPID_LABTECWEBCAMPRO                  0x0929 //Labtec WebCam Pro
#define USBPID_QUICKCAMNOTEBOOKS                0x092A //QuickCam for Notebooks
#define USBPID_LABTECWEBCAMPLUS                 0x092B //Labtec WebCam Plus
#define USBPID_QUICKCAMCHAT2                    0x092C //QuickCam Chat
#define USBPID_QUICKCAMEXPRESSGO                0x092D //QuickCam Express / Go
#define USBPID_QUICKCAMCHAT2                    0x092E //QuickCam Chat
#define USBPID_QUICKCAMEXPRESSPLUS              0x092F //QuickCam express Plus
#define USBPID_POCKETCAMERA                     0x0950 //Pocket Camera
#define USBPID_CLICKSMART420                    0x0960 //ClickSmart 420
#define USBPID_POCKET750                        0x0970 //Pocket750
#define USBPID_QUICKCAMPRO9000                  0x0990 //QuickCam Pro 9000
#define USBPID_QUICKCAMPROFORNOTEBOOKS          0x0991 //QuickCam Pro for Notebooks
#define USBPID_QUICKCAMCOMMUNICATEDELUXE        0x0992 //QuickCam Communicate Deluxe
#define USBPID_QUICKCAMORBITSPHEREAF            0x0994 //QuickCam Orbit/Sphere AF
#define USBPID_ORBICAM                          0x09B0 //OrbiCam
#define USBPID_QUICKCAMMICDELL                  0x09C0 //QuickCam for Dell Notebooks Mic
#define USBPID_QUICKCAMDELUXENOTEBOOKS          0x09C1 //QuickCam Deluxe for Notebooks
#define USBPID_LOGITECHUSBHEADSET               0x0A01 //Logitech USB Headset
#define USBPID_PREMIUMSTEREOHEADSET350          0x0A02 //Premium Stereo USB Headset 350
#define USBPID_MICLOGITECH                      0x0A03 //Logitech USB Microphone
#define USBPID_V20PORTABLESPEAKER               0x0A04 //USB powered V20 portable speakers
#define USBPID_BTMINIRECEIVERHID                0x0B02 //BT Mini-Receiver HID mode
#define USBPID_VIDEOCAMERA                      0x8801 //Video Camera
#define USBPID_BTMINIRECEIVER                   0xB305 //BT Mini-Receiver
#define USBPID_MOUSEPREMIUMOPTICALWHEEL         0xBFE4 //Premium Optical Wheel Mouse
#define USBPID_MOUSEPILOTN43                    0xC000 //N43 Pilot Mouse
#define USBPID_MOUSEN48                         0xC001 //N48/M-BB48 FirstMouse Plus
#define USBPID_MOUSEMANMBA47                    0xC002 //M-BA47 MouseMan Plus
#define USBPID_MOUSEMAN                         0xC003 //MouseMan
#define USBPID_MOUSEWINGMANGAMING               0xC004 //WingMan Gaming Mouse
#define USBPID_MOUSEWINGMANGAMINGWHEEL          0xC005 //WingMan Gaming Wheel Mouse
#define USBPID_MOUSEMANWHEEL1                   0xC00B //MouseMan Wheel
#define USBPID_MOUSEOPTICALWHEEL                0xC00C //Optical Wheel Mouse
#define USBPID_MOUSEMANWHEEL2                   0xC00D //MouseMan Wheel+
#define USBPID_MOUSEMBJ69OPTICAL                0xC00E //M-BJ58/M-BJ69 Optical Wheel Mouse
#define USBPID_MOUSEMANTRAVELER                 0xC00F //MouseMan Traveler/Mobile
#define USBPID_MOUSEMANOPTICAL                  0xC011 //Optical MouseMan
#define USBPID_MOUSEOPTICAL                     0xC012 //Optical Mouse
#define USBPID_MOUSECORDEDWKS1                  0xC014 //Corded Workstation Mouse
#define USBPID_MOUSECORDEDWKS2                  0xC015 //Corded Workstation Mouse
#define USBPID_MOUSEMUV69AOPTICAL               0xC016 //M-UV69a Optical Wheel Mouse
#define USBPID_OPTICALWHEELMOUSE                0xC018 //Optical Wheel Mouse
#define USBPID_OPTICALTILTWHEELMOUSE            0xC019 //Optical Tilt Wheel Mouse
#define USBPID_MBQ85OPTICALWHEELMOUSE           0xC01A //M-BQ85 Optical Wheel Mouse
#define USBPID_MOUSEMX310                       0xC01B //MX310 Optical Mouse
#define USBPID_OPTICALMOUSE                     0xC01C //Optical Mouse
#define USBPID_MOUSEMX510                       0xC01D //MX510 Optical Mouse
#define USBPID_MOUSEMX518                       0xC01E //MX518 Optical Mouse
#define USBPID_MOUSEMX300                       0xC024 //MX300 Optical Mouse
#define USBPID_MOUSEMX500                       0xC025 //MX500 Optical Mouse
#define USBPID_MOUSEIFEEL1                      0xC030 //iFeel Mouse
#define USBPID_MOUSEIFEEL2                      0xC031 //iFeel Mouse+
#define USBPID_MOUSEMANIFEEL                    0xC032 //MouseMan iFeel
#define USBPID_MOUSEMANIFEELP                   0xC033 //iFeel MouseMan+
#define USBPID_MOUSEMANOPTICAL                  0xC034 //MouseMan Optical
#define USBPID_LOGITECHMOUSE1                   0xC035 //Logitech Mouse
#define USBPID_LOGITECHMOUSE2                   0xC036 //Logitech Mouse
#define USBPID_LOGITECHMOUSE3                   0xC037 //Logitech Mouse
#define USBPID_LOGITECHMOUSE4                   0xC038 //Logitech Mouse
#define USBPID_MOUSEMBT69APILOT                 0xC03D //M-BT69a Pilot Optical Mouse
#define USBPID_MOUSEPREMIUMOPTICAL              0xC03E //Premium Optical Wheel Mouse
#define USBPID_ULTRAXOPTICALMOUSE               0xC03F //UltraX Optical Mouse
#define USBPID_CORDEDTILTWHEELMOUSE             0xC040 //Corded Tilt-Wheel Mouse
#define USBPID_MX320LASERMOUSE                  0xC043 //MX320 Laser Mouse
#define USBPID_LX3OPTICALMOUSE                  0xC044 //LX3 Optical Mouse
#define USBPID_OPTICALMOUSE                     0xC045 //Optical Mouse
#define USBPID_RX1000LASERMOUSE                 0xC046 //RX1000 Laser Mouse
#define USBPID_LASERMOUSE                       0xC047 //Laser Mouse
#define USBPID_G5LASERMOUSE                     0xC049 //G5 Laser Mouse
#define USBPID_RX250OPTICALMOUSE                0xC050 //RX 250 Optical Mouse
#define USBPID_G3MX518OPTICALMOUSE              0xC051 //G3 (MX518) Optical Mouse
#define USBPID_LASERMOUSE                       0xC053 //Laser Mouse
#define USBPID_ULTRAXMEDIAREMOTE                0xC101 //UltraX Media Remote
#define USBPID_WINGMANEXTREMEJOYSTICK           0xC201 //WingMan Extreme Joystick with Throttle
#define USBPID_WINGMANFORMULA                   0xC202 //WingMan Formula
#define USBPID_WINGMANEXTREMEDIGITAL3D          0xC207 //WingMan Extreme Digital 3D
#define USBPID_WINGMANGAMEPADEXTREME            0xC208 //WingMan Gamepad Extreme
#define USBPID_WINGMANGAMEPAD                   0xC209 //WingMan Gamepad
#define USBPID_WINGMANRUMBLEPAD                 0xC20A //WingMan RumblePad
#define USBPID_WINGMANACTIONPAD                 0xC20B //WingMan Action Pad
#define USBPID_WINGMANPRECISION                 0xC20C //WingMan Precision
#define USBPID_WINGMANATTACK                    0xC20D //WingMan Attack 2
#define USBPID_WINGMANFORMULAGP                 0xC20E //WingMan Formula GP
#define USBPID_ITOUCHCORDLESSRECIEVER           0xC211 //iTouch Cordless Reciever
#define USBPID_DUALACTIONGAMEPAD                0xC216 //Dual Action Gamepad
#define USBPID_WINGMANEXTREMEDIGITAL3D          0xC212 //WingMan Extreme Digital 3D
#define USBPID_JUH16FREEDOM24JOYSTICK           0xC213 //J-UH16 (Freedom 2.4 Cordless Joystick)
#define USBPID_ATK3JOYSTICK                     0xC214 //ATK3 (Attack III Joystick)
#define USBPID_EXTREME3DPRO                     0xC215 //Extreme 3D Pro
#define USBPID_RUMBLEPAD2                       0xC218 //Logitech RumblePad 2 USB
#define USBPID_CORDLESSRUMBLEPAD2               0xC219 //Cordless RumblePad 2
#define USBPID_PRECISIONGAMEPAD                 0xC21A //Precision Gamepad
#define USBPID_G15KBD                           0xC221 //G15 Keyboard
#define USBPID_G15KBDLCD                        0xC222 //G15 Keyboard / LCD
#define USBPID_G15KBDHUB                        0xC223 //G15 Keyboard / USB Hub
#define USBPID_WINGMANFORCE                     0xC281 //WingMan Force
#define USBPID_WINGMANFORCE3D                   0xC283 //WingMan Force 3D
#define USBPID_WINGMANSTRIKEFORCE3D             0xC285 //WingMan Strike Force 3D
#define USBPID_FORCE3DPRO                       0xC286 //Force 3D Pro
#define USBPID_WINGMANFORMULAFORCE              0xC291 //WingMan Formula Force
#define USBPID_WINGMANFORMULAFORCEGP            0xC293 //WingMan Formula Force GP
#define USBPID_DRIVINGFORCE                     0xC294 //Driving Force
#define USBPID_MOMOFORCESTEERINGWHEEL           0xC295 //Momo Force Steering Wheel
#define USBPID_DRIVINGFORCEPRO                  0xC298 //Driving Force Pro
#define USBPID_MOUSEWINGMANFORCEFEEDBACK        0xC2A0 //Wingman Force Feedback Mouse
#define USBPID_WINGMANFORCEFEEDBACKMOUSE        0xC2A1 //WingMan Force Feedback Mouse
#define USBPID_ITOUCHKEYBOARD                   0xC301 //iTouch Keyboard
#define USBPID_ITOUCHPROKEYBOARD                0xC302 //iTouch Pro Keyboard
#define USBPID_ITOUCHKEYBOARD                   0xC303 //iTouch Keyboard
#define USBPID_INTERNETKEYBOARD                 0xC305 //Internet Keyboard
#define USBPID_INTERNETKEYBOARD                 0xC307 //Internet Keyboard
#define USBPID_KBDINTERNETNAVIGATOR             0xC308 //Internet Navigator Keyboard
#define USBPID_KBDINTERNET                      0xC309 //Internet Keyboard
#define USBPID_ITOUCHCOMPOSITE                  0xC30A //iTouch Composite
#define USBPID_INTERNETKEYSX                    0xC30C //Internet Keys (X)
#define USBPID_INTERNETKEYS                     0xC30D //Internet Keys
#define USBPID_ULTRAXKEYSX                      0xC30E //UltraX Keys (X)
#define USBPID_LOGICOOLKBD106HID                0xC30F //Logicool HID-Compliant Keyboard (106 key)
#define USBPID_CLASSICNEWTOUCHKBD               0xC315 //Classic New Touch Keyboard
#define USBPID_LOGITECHKBDHID                   0xC316 //HID-Compliant Keyboard
#define USBPID_TRACKMANMARBLEWHEEL              0xC401 //TrackMan Marble Wheel
#define USBPID_MOUSEMARBLE2BUTTON               0xC402 //Marble Mouse (2-button)
#define USBPID_TURBOTRACKMANMARBLEFX            0xC403 //Turbo TrackMan Marble FX
#define USBPID_TRACKMANWHEEL                    0xC404 //TrackMan Wheel
#define USBPID_MOUSEMARBLE4BUTTON               0xC408 //Marble Mouse (4-button)
#define USBPID_MOUSECORDLESSRECEIVER            0xC501 //Cordless Mouse Receiver
#define USBPID_MOUSEITOUCHKEYS                  0xC502 //Cordless Mouse & iTouch Keys
#define USBPID_MOUSEKBDCORDLESSRECEIVER3        0xC503 //Cordless Mouse+Keyboard Receiver
#define USBPID_MOUSEKBDCORDLESSRECEIVER4        0xC504 //Cordless Mouse+Keyboard Receiver
#define USBPID_MOUSEKBDCORDLESSRECEIVER5        0xC505 //Cordless Mouse+Keyboard Receiver
#define USBPID_MOUSECORDLESSRECEIVERMX700       0xC506 //MX-700 Cordless Mouse Receiver
#define USBPID_CORDLESSTRACKBALL                0xC508 //Cordless Trackball
#define USBPID_CORDLESSKEYBOARD                 0xC509 //Cordless Keyboard
#define USBPID_CORDLESSMOUSE1                   0xC50A //Cordless Mouse
#define USBPID_CORDLESSDESKTOPOPTICAL           0xC50B //Cordless Desktop Optical
#define USBPID_MOUSECORDLESSRECEIVERMX1000      0xC50E //MX-1000 Cordless Mouse Receiver
#define USBPID_CORDLESSMOUSE2                   0xC50D //Cordless Mouse
#define USBPID_CORDLESSMOUSE3                   0xC510 //Cordless Mouse
#define USBPID_LX700RECEIVER                    0xC512 //LX-700 Cordless Desktop Receiver
#define USBPID_MX3000RECEIVER                   0xC513 //MX3000 Cordless Desktop Receiver
#define USBPID_CORDLESSMOUSE                    0xC514 //Cordless Mouse
#define USBPID_LX710LASERMOUSE                  0xC517 //LX710 Cordless Desktop Laser
#define USBPID_MOUSECORDLESSMX610               0xC518 //MX610 Laser Cordless Mouse
#define USBPID_MXREVOLUTIONG7MOUSE              0xC51A //MX Revolution/G7 Cordless Mouse
#define USBPID_MX620LASERMOUSE                  0xC521 //MX620 Laser Cordless Mouse
#define USBPID_3DCONNEXIONSPACEPILOT3DMOUSE     0xC625 //3Dconnexion Space Pilot 3D Mouse
#define USBPID_3DCONNEXIONSPACENAVIGATOR3DMOUSE 0xC626 //3DConnexion Space Navigator 3D Mouse
#define USBPID_3DCONNEXIONSPACEEXPLORER3DMOUSE  0xC627 //3DConnexion Space Explorer 3D Mouse
#define USBPID_CORDLESSPRESENTER                0xC702 //Cordless Presenter
#define USBPID_ELITEKBDRP20MOUSEMX900BT         0xC703 //Elite Keyboard Y-RP20 + Mouse MX900 (Bluetooth)
#define USBPID_BTHUB1                           0xC707 //Bluetooth wireless hub
#define USBPID_BTHUB2                           0xC708 //Bluetooth wireless hub
#define USBPID_BTMINIRECEIVERHCIMODE            0xC709 //BT Mini-Receiver (HCI mode)
#define USBPID_MX5000CORDLESSDESKTOP            0xC70A //MX5000 Cordless Desktop
#define USBPID_BTMINIRECEIVERHID1               0xC70B //BT Mini-Receiver (HID proxy mode)
#define USBPID_BTMINIRECEIVERHID2               0xC70C //BT Mini-Receiver (HID proxy mode)
#define USBPID_BTHUB3                           0xC70D //Bluetooth wireless hub
#define USBPID_MX1000MOUSEBT                    0xC70E //MX1000 Bluetooth Laser Mouse
#define USBPID_BTHUB4                           0xC70F //Bluetooth wireless hub
#define USBPID_BTHUB5                           0xC712 //Bluetooth wireless hub
#define USBPID_BTHUB6                           0xC715 //Bluetooth wireless hub
#define USBPID_BTHUB7                           0xC71A //Bluetooth wireless hub
#define USBPID_BTHUB8                           0xC71D //Bluetooth wireless hub
#define USBPID_BTHUB9                           0xC720 //Bluetooth wireless hub
#define USBPID_MOMORACING                       0xCA03 //MOMO Racing
#define USBPID_FORMULAVIBRATIONFEEDBACKWHEEL    0xCA04 //Formula Vibration Feedback Wheel
#define USBPID_QUICKCAMPRO1                     0xD001 //QuickCam Pro

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
