/*
 * NotificationManagerThread.cpp
 *
 *  Created on: Nov 23, 2014
 *      Author: misha
 */

#include "NotificationManagerThread.h"
#include <FAppAppManager.h>
#include <FSysSystemTime.h>
#include <FAppPkg.h>
#include <FBase.h>
#include <FBaseDateTime.h>
#include <Math.h>
#include <FShell.h>
#include <FUi.h>
#include <FLocations.h>

using namespace Tizen::App::Package;
using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Locations;
using namespace Tizen::Shell;

NotificationManagerThread *NotificationManagerThread::instance = null;
result NotificationManagerThread::r = 0;

NotificationManagerThread* NotificationManagerThread::GetInstance(void) {
	if(instance==null) {
		instance = new NotificationManagerThread();
		r = instance->Construct();
	}
	return instance;
}

NotificationManagerThread::NotificationManagerThread(void) 	: Tizen::Base::Runtime::Thread() {
	// TODO Auto-generated constructor stub
	lectures = null;

}

NotificationManagerThread::~NotificationManagerThread(void) {
	// TODO Auto-generated destructor stub
}

result
NotificationManagerThread::Construct()//const Tizen::Ui::Control& uiControl)
{
	//__pUiControl = &uiControl;
	return Thread::Construct();
}

void NotificationManagerThread::setLectures(LectureInfo* lectures) {
	this->lectures = lectures;
}

void NotificationManagerThread::showNotification(){

	AppLog("showNotification start");

/*	Tizen::Shell::NotificationManager notiMgr;
	notiMgr.Construct();
	Tizen::Shell::NotificationRequest request;
	request.SetAlertText(L"AlertText");
	request.SetTitleText(L"TitleText");
	request.SetAppMessage(L"AppMessage");
	request.SetNotificationStyle(Tizen::Shell::NOTIFICATION_STYLE_NORMAL);
	notiMgr.Notify(request);*/

	NotificationRequest request;
	request.SetAlertText(L"Reached the timing of the Lecture room.");
	request.SetTitleText(L"TitleText");
	request.SetAppMessage(L"vartika");
	request.SetNotificationStyle(NOTIFICATION_STYLE_NORMAL);
	Tizen::Shell::NotificationManager* __pNotificationManager = null;
	__pNotificationManager = new (std::nothrow) NotificationManager;
	AppAssert(__pNotificationManager);
	__pNotificationManager->Construct();

	/*String appId = L"oxEWc0z8PB.LocalizationServiceApp";
	if((PackageManager::GetInstance())->IsPackageInstalled(PackageManager::GetPackageIdByAppId(appId))){
		AppLog(" THIS PACKAGE IS INSTALLED .....................");
		result r = __pNotificationManager->NotifyByAppId(appId, request);
		AppLog(" THIS NOTIFICATION IS LAUNCHED .....................");
	}else {
		AppLog(" THIS PACKAGE IS NOT INSTALLED .....................");
	}*/

	String operation(L"http://tizen.org/appcontrol/operation/launchWebApp");
						/*String uri(L"mailto:test@tizen.org");
						String mime(L"audio/mp4");*/
						const static wchar_t* key1 = L"http://tizen.org/appcontrol/data/to";
									const static wchar_t* value1 = L"WhoIsIt";
									const static wchar_t* key2 = L"http://tizen.org/appcontrol/data/text";
									const static wchar_t* value2 = L"Hello there.";
									HashMap map;
									map.Construct();
									map.Add(new (std::nothrow) String(key1), new (std::nothrow) String(value1));
									map.Add(new (std::nothrow) String(key2), new (std::nothrow) String(value2));
			result r = __pNotificationManager->NotifyByAppControl(operation, NULL, NULL, &map, request);


/*	__pNotificationManager->Notify(0);
	__pNotificationManager->RemoveNotification();
	delete __pNotificationManager;*/

	AppLog("showNotification ends ");
}

Object*
NotificationManagerThread::Run(void)
{

	while(true)	{
		Thread::Sleep(10000);
		if(lectures!=null) {
			LectureInfo* tempPointer = this->lectures;
			Tizen::Base::DateTime* dateTime = new Tizen::Base::DateTime();
			Tizen::System::SystemTime::GetCurrentTime(Tizen::System::TIME_MODE_STANDARD, *dateTime);
			long currentTime = dateTime->GetTicks();
			int hour = dateTime->GetHour();
			int minutes = dateTime->GetMinute();
			int railwayTiming = (hour*100)+minutes;
			Tizen::Base::String phaseOfDay = "X";
			if(railwayTiming > 900 && railwayTiming < 1015) {
				phaseOfDay = "A";
			} else if (railwayTiming > 1030 && railwayTiming < 1145) {
				phaseOfDay = "B";
			} else if (railwayTiming > 1200 && railwayTiming < 1315) {
				phaseOfDay = "C";
			} else if (railwayTiming > 1330 && railwayTiming < 1445) {
				phaseOfDay = "D";
			} else if (railwayTiming > 1500 && railwayTiming < 1615) {
				phaseOfDay = "E";
			} else if (railwayTiming > 1630 && railwayTiming < 1745) {
				phaseOfDay = "F";
			} else if (railwayTiming > 1600 && railwayTiming < 1915) {
				phaseOfDay = "G";
			} /*else if (railwayTiming > 2100 && railwayTiming < 2230) {
				phaseOfDay = "N";
			}*/

			int lectureIndex = -1;

			while(tempPointer!=null) {
				lectureIndex++;
				String phaseOfLecture = tempPointer->timing;
				AppLog("At (%d) Phase of Day is %S Lecture(%d) timing is %S", railwayTiming, phaseOfDay.GetPointer(), lectureIndex, phaseOfLecture.GetPointer());
				if(phaseOfDay.Equals(phaseOfLecture)) {
					long classDuration = 75*60*1000; // 1 hour 15 mins
					if(currentTime-tempPointer->lastShownAt > classDuration) {
						tempPointer->lastShownAt = currentTime;
						showNotification();
					}
				}
				tempPointer = tempPointer->next;
			}
		}
		AppLog("Requested for time in notification manager thread.");
	}

	return null;
}


