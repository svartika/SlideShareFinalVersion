#include "LocalizationServiceAppApp.h"
#include "Storage.h"
//#include "DataParser.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::System;

static const wchar_t* LOCAL_MESSAGE_PORT_NAME = L"SAMPLE_PORT";

LocalizationServiceAppApp::LocalizationServiceAppApp(void)
{
	__pLocationManagerThread = null;
	__pNotificationManagerThread = null;
	__pMessagePort = null;
}

LocalizationServiceAppApp::~LocalizationServiceAppApp(void)
{
	delete __pMessagePort;
}

ServiceApp*
LocalizationServiceAppApp::CreateInstance(void)
{
	AppLog("vartika in createInstance");

	// Create the instance through the constructor.
	return new (std::nothrow) LocalizationServiceAppApp();
}

bool
LocalizationServiceAppApp::OnAppInitializing(AppRegistry& appRegistry)
{
	AppLog("vartika in onAppInitializing");
	// TODO:
	// Initialize App specific data, and add your initialization code here
	// The App's permanent data and context can be obtained from the appRegistry.
	//
	// If this method is successful, return true; otherwise, return false.
	// If this method returns false, the App will be terminated.

	result r = E_SUCCESS;
	AppControlProviderManager::GetInstance()->SetAppControlProviderEventListener(this);

	// Initialize ServerMessagePort
	__pMessagePort = new (std::nothrow) MessagePort();
	TryReturn(__pMessagePort != null, false, "[E_FAILURE] Failed to create __pMessagePort.");
	AppLog("__pMessagePort is created.");

	r = __pMessagePort->Construct(LOCAL_MESSAGE_PORT_NAME);
	TryReturn(IsFailed(r) != true, r, "[%s] Failed to construct __pMessagePort", GetErrorMessage(r));
	AppLog("__pMessagePort is constructed.");

	return true;
}

void LocalizationServiceAppApp::OnAppControlRequestReceived(RequestId reqId, const Tizen::Base::String& operationId, const Tizen::Base::String* pUriData, const Tizen::Base::String* pMimeType, const Tizen::Base::Collection::IMap* pExtraData)
{
	AppLog("We are inside OnAppControlRequestReceived and operatib is %ls and pUriData is %ls", operationId.GetPointer(),
			pUriData ? (pUriData->GetPointer()) : L"null");
	AppId calleeAppId = L"23lGZwKekJ.test";

	AppManager* pAppManager = AppManager::GetInstance();

	ArrayList* pArgList = new ArrayList();
	pArgList->Construct();

	String* aArg = new String(L"from service");
	pArgList->Add(*aArg);

	result r = pAppManager->LaunchApplication(calleeAppId, pArgList, AppManager::LAUNCH_OPTION_DEFAULT);
}

bool
LocalizationServiceAppApp::OnAppInitialized(void)
{
	AppLog("vartika in onAppInitialized");
	AppRegistry* appRegistry = GetAppRegistry();
	Storage* storage = Storage::getInstance(appRegistry);
	//storage->Construct(appRegistry);


	__pLocationManagerThread = LocationManagerThread::GetInstance();
	result r = __pLocationManagerThread->r;
	if(IsFailed(r)){
		AppLog("Thread Construct failed.");
		return r;
	}
	/*__pLocationManagerThread =  new (std::nothrow) LocationManagerThread();
		result r = E_SUCCESS;
	r = __pLocationManagerThread->Construct();//*this);
		if (IsFailed(r))
		{
			AppLog("Thread Construct failed.");
			return r;
		}*/
	r = __pLocationManagerThread->Start();

	__pNotificationManagerThread =  NotificationManagerThread::GetInstance();
	result r2 = __pNotificationManagerThread->r;
	if (IsFailed(r2))
	{
		AppLog("Thread Construct failed.");
		return r2;
	}
	r2 = __pNotificationManagerThread->Start();

	return true;
}

bool
LocalizationServiceAppApp::OnAppWillTerminate(void)
{
	AppLog("vartika in onAppWillTerminate");
	return true;
}

bool
LocalizationServiceAppApp::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	AppLog("vartika in onAppTerminating");

	AppLog("vartika deleting __pLocationManagerThread");
	__pLocationManagerThread->Join();
	delete __pLocationManagerThread;

	AppLog("vartika deleting __pNotificationManagerThread");
	__pNotificationManagerThread->Join();
	delete __pNotificationManagerThread;

	// TODO:
	// Deallocate resources allocated by this App for termination, and add your termination code here
	// The App's permanent data and context can be saved via appRegistry.
	return true;
}

void
LocalizationServiceAppApp::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the App.
}

void
LocalizationServiceAppApp::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void
LocalizationServiceAppApp::OnUserEventReceivedN(RequestId requestId, IList* pArgs)
{
	AppLog("OnUserEventReceivedN is called. requestId is %d", requestId);
	String *payload = null;
	//DataParser *dataParser =null;
	switch (requestId)
	{
	/*case TIMER_START :
		if (__pTimer != null)
		{
			__pTimer->Start();
		}
		break;
	case TIMER_STOP :
		if (__pTimer != null)
		{
			__pTimer->Stop();
		}
		break;*/
	case STUDENT_INFO_RECEIVED:
		payload = (String*)(pArgs->GetAt(0));
		pArgs->RemoveAt(0);

		AppLog("OnUserEventReceivedN is called. payload is %S", payload->GetPointer());
	/*	if(!Storage::getInstance(GetAppRegistry())->SaveKeyValuePair(L"student_info", *payload))	{
			//save in to dummy db class
			AppLog("OnUserEventReceivedN save in to dummy db class");
			DataParser *dataParser = new DataParser();
			dataParser->ParseString(*payload);
		}*/
		AppLog("OnUserEventReceivedN save in to dummy db class");
//		dataParser = new DataParser();
//		dataParser->ParseString(*payload);
		break;
	case LECTURE_LOCATION_UPDATED:
			payload = (String*)(pArgs->GetAt(0));


			AppLog("OnUserEventReceivedN is called. payload is %S", payload->GetPointer());
			break;
	/*case TIMER_EXPIRED :
		if (__pMessagePort != null)
		{
			HashMap *pMap =	new HashMap(SingleObjectDeleter);
			pMap->Construct();
			pMap->Add(new String(L"server"), new String(L"timer expired"));

			__pMessagePort->SendMessage(pMap);

			delete pMap;
		}
		break;
	case TIMER_EXIT :
		Terminate();
		break;*/
	default:
		break;
	}
}
