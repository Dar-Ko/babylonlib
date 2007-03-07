// MainTAPICtr.cpp : Implementation of CMainTAPICtr
#include "stdafx.h"
#include "TAPITest.h"
#include "MainTAPICtr.h"

/////////////////////////////////////////////////////////////////////////////
// CMainTAPICtr

STDMETHODIMP CMainTAPICtr::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMainTAPICtr
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CMainTAPICtr::ChooseModem()
{
	// Use the TAPI object to enumerate available addresses.
	short bSupport;
	gpTapi->EnumerateAddresses( &pIEnumAddress );

	// Locate an address that can support the 
	// media type the application needs.
	while ( S_OK == pIEnumAddress->Next(1, &pAddress, NULL) ) 
	{
		// Determine the media support.
		pAddress->QueryInterface(IID_ITMediaSupport,(void **)&pMediaSupport);

		// In this snippet, the required media type is already known.
		// The application can also use the address object to
		// enumerate the media supported, then choose from there.
//		pMediaSupport->QueryMediaType(TAPIMEDIATYPE_AUDIO|TAPIMEDIATYPE_VIDEO,&bSupport);
		pMediaSupport->QueryMediaType(TAPIMEDIATYPE_AUDIO,&bSupport);
		if (bSupport)
		{
			break;
		}
	}
	// pAddress is now a usable address.
	return S_OK;
}

STDMETHODIMP CMainTAPICtr::MyMakeCall()
{
	// Specify the destination address.
	//
	// szAddressToCall and 
	// dwAddressType have been
	// retrieved from a user interface.
	ITBasicCallControl *pBasicCall;
	BSTR bstrAddressToCall;
	bstrAddressToCall = SysAllocString(L"6661");
//	bstrAddressToCall = SysAllocString(L"94168168169");
	pAddress->CreateCall(bstrAddressToCall,LINEADDRESSTYPE_PHONENUMBER,TAPIMEDIATYPE_AUDIO,&pBasicCall);

	// Create the required terminals for this call.
//	{
		// See the Select a Terminal code snippet.



		// pAddress is an ITAddress interface pointer.
		// pBasicCall is an ITBasicCallControl interface pointer.

		// Get the ITStreamControl interface.
		ITStreamControl * pStreamControl;
		pBasicCall->QueryInterface(IID_ITStreamControl,	(void **) &pStreamControl);

		// Enumerate the streams and select 
		// terminals onto them.
		IEnumStream * pEnumStreams;
		ITStream    * pStream;
		pStreamControl->EnumerateStreams(&pEnumStreams);
		while ( S_OK == pEnumStreams->Next(1, &pStream, NULL) )
			{
				// Get the media type and direction of this stream.
				long lMediaType;
				TERMINAL_DIRECTION  dir;
				pStream->get_MediaType( &lMediaType );
				pStream->get_Direction( &dir );

				// Create the default terminal for this media type
				// and direction.
				//   If lMediaType == TAPIMEDIATYPE_VIDEO and
				//   dir == TD_RENDER, a dynamic video render terminal
				//   is required. Please see Incoming.cpp in 
				//   the samples section of the SDK. 
				// For all other terminals, get the default 
				// static terminal.
				ITTerminal * pTerminal;
				ITTerminalSupport * pTerminalSupport;
				pAddress->QueryInterface(IID_ITTerminalSupport,(void **)&pTerminalSupport);
				pTerminalSupport->GetDefaultStaticTerminal(lMediaType,dir,&pTerminal);
				// Select the terminal on the stream.
				pStream->SelectTerminal(pTerminal);
			}


//	}

	// Make the connection.
	pBasicCall->Connect( TRUE );
	SysFreeString(bstrAddressToCall);

	return S_OK;
}
