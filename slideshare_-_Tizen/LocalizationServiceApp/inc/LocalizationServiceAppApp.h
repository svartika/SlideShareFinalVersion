#ifndef _LOCALIZATION_SERVICE_APP_APP_H_
#define _LOCALIZATION_SERVICE_APP_APP_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>
#include <FUiIme.h>
#include <FGraphics.h>
#include <gl.h>

#include "LocationManagerThread.h"
#include "NotificationManagerThread.h"
#include "MessagePort.h"
#include "MyType.h"

// LocalizationServiceAppApp must inherit from ServiceApp class
// which provides basic features necessary to define an ServiceApp.
class LocalizationServiceAppApp
	: public Tizen::App::ServiceApp
	 ,public virtual Tizen::App::IAppControlProviderEventListener
{
public:
	// [LocalizationServiceAppApp] ServiceApp must have a factory method that creates an instance of itself.
	static Tizen::App::ServiceApp* CreateInstance(void);
	LocalizationServiceAppApp(void);
	~LocalizationServiceAppApp(void);

private:
	LocationManagerThread* __pLocationManagerThread;
	NotificationManagerThread* __pNotificationManagerThread;
	MessagePort* __pMessagePort;

public:
	virtual void OnAppControlRequestReceived(RequestId reqId, const Tizen::Base::String& operationId,
												 const Tizen::Base::String* pUriData, const Tizen::Base::String* pMimeType,
												 const Tizen::Base::Collection::IMap* pExtraData);
	// Called when the ServiceApp is initializing.
	bool OnAppInitializing(Tizen::App::AppRegistry& appRegistry);

	// Called when the ServiceApp initializing is finished.
	bool OnAppInitialized(void); 

	// Called when the ServiceApp is requested to terminate.
	bool OnAppWillTerminate(void);

	// Called when the ServiceApp is terminating.
	bool OnAppTerminating(Tizen::App::AppRegistry& appRegistry, bool forcedTermination = false);

	// Called when the system memory is not sufficient to run the ServiceApp any further.
	void OnLowMemory(void);

	// Called when the battery level changes.
	void OnBatteryLevelChanged(Tizen::System::BatteryLevel batteryLevel);

	virtual void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);
};

#endif // _LOCALIZATION_SERVICE_APP_APP_H_
