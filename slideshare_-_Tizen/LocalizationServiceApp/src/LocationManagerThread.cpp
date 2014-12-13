//
// Tizen Native SDK
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.1 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license/
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <FUi.h>
#include <FLocations.h>
#include "LocationManagerThread.h"
#include <FAppAppManager.h>
#include <FSysSystemTime.h>
#include <FBase.h>
#include <FAppPkg.h>
#include <FBaseDateTime.h>
#include <Math.h>
#include <FShell.h>
//#include "DataParser.h"

using namespace Tizen::App;
using namespace Tizen::App::Package;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Locations;
using namespace Tizen::Shell;

LocationManagerThread *LocationManagerThread::locationManagerThread = null;
result LocationManagerThread::r = 0;

LocationManagerThread::LocationManagerThread(void)
	: Tizen::Base::Runtime::Thread()
	//, __pUiControl(null)
{
	lectures = null;
}

LocationManagerThread::~LocationManagerThread(void)
{
}

result
LocationManagerThread::Construct()//const Tizen::Ui::Control& uiControl)
{
	//__pUiControl = &uiControl;
	return Thread::Construct();
}

LocationManagerThread* LocationManagerThread::GetInstance()
{
	if(locationManagerThread == null) {
		locationManagerThread =  new (std::nothrow) LocationManagerThread();
		r = locationManagerThread->Construct();
	}
	AppLog("LocationManagerThread::GetInstance");
	return locationManagerThread;

}

void LocationManagerThread::SetLectureInfo(LectureInfo* _lectures)
{
	AppLog("SetLectureInfo");
	LectureInfo* tempLocal = this->lectures;

	while(tempLocal!=null) {
		Tizen::Base::String timingOfCurrentLecture = tempLocal->timing;
		LectureInfo* tempNew = _lectures;
		while(tempNew!=null) {
			if(tempNew->timing.Equals(timingOfCurrentLecture)){
				tempNew->lastShownAt = tempLocal->lastShownAt;
				break;
			}
			tempNew= tempNew->next;
		}
		tempLocal = tempLocal->next;
	}
	this->lectures = _lectures;
	AppLog("SetLectureInfo %d", lectures);
	while(_lectures != null) {
		String latitude = _lectures->latitude;
		String longitude = _lectures->longitude;
		AppLog("setLectureInfo, latitude=%S longitude=%S", latitude.GetPointer(), longitude.GetPointer());
		_lectures=_lectures->next;
	}
}

void LocationManagerThread::showNotification(){

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
	request.SetAlertText(L"Entered the location of the Lecture room.");
	request.SetTitleText(L"TitleText");
	request.SetAppMessage(L"vartika");
	request.SetNotificationStyle(NOTIFICATION_STYLE_NORMAL);

	Tizen::Shell::NotificationManager* __pNotificationManager = null;
	__pNotificationManager = new (std::nothrow) NotificationManager;
	AppAssert(__pNotificationManager);
	__pNotificationManager->Construct();

	//result r = __pNotificationManager->Notify(request);
	/*String appId = L"oxEWc0z8PB.LocalizationServiceApp";
		if((PackageManager::GetInstance())->IsPackageInstalled(PackageManager::GetPackageIdByAppId(appId))){
			AppLog(" THIS PACKAGE IS INSTALLED .....................");
			result r = __pNotificationManager->NotifyByAppId(appId, request);
			AppLog(" THIS NOTIFICATION IS LAUNCHED .....................");
		} else {
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
LocationManagerThread::Run(void)
{
	//showNotification();

	while(true)	{

		result lastResult = E_SUCCESS;
		LocationCriteria locCriteria;

		locCriteria.SetAccuracy(LOC_ACCURACY_HUNDRED_METERS);

		Location location = LocationProvider::GetLocation(locCriteria);

		AppLog("Requested for current location in new thread.");

		lastResult = GetLastResult();

		if (lastResult == E_USER_NOT_CONSENTED)
		{
			//__pUiControl->SendUserEvent(LocationManagerMainForm::LOC_MGR_NOTIFY_ERROR, null);
		}

		//ArrayList* pList = new (std::nothrow) ArrayList();
		Location* pLocation = new (std::nothrow) Location(location);
		Coordinates coordinates = pLocation->GetCoordinates();
		float currentLatitude = (float)coordinates.GetLatitude();
		float currentLongitude = (float)coordinates.GetLongitude();

		LectureInfo* lectureList = this->lectures;
		int lectureIndex = -1;
		if(lectureList != null) {
			while(lectureList != null) {
				lectureIndex++;
				float latitude = 0;
				AppLog("About to parse the latitude %S", lectureList->latitude.GetPointer());
				result r1 = Tizen::Base::Float::Parse(lectureList->latitude, latitude);
				float longitude = 0;
				AppLog("About to parse the longitude %S",lectureList->longitude.GetPointer());
				result r2 = Tizen::Base::Float::Parse(lectureList->longitude, longitude);

				if (latitude==currentLatitude && longitude==currentLongitude) {
					AppLog("Currently inside class location for index %d (%f:%f)", lectureIndex, currentLatitude, currentLongitude);
					Tizen::Base::DateTime* dateTime = new Tizen::Base::DateTime();

					Tizen::System::SystemTime::GetCurrentTime(*dateTime);
					long currentTime = dateTime->GetTicks();
					long classDuration = 75*60*1000; // 1 hour 15 mins
					if(currentTime-lectureList->lastShownAt > classDuration) {
						lectureList->lastShownAt = currentTime;
						AppLog("show notification");
						showNotification();
					}
				} else {
					AppLog("Currently Outside class location for index %d (%f:%f)", lectureIndex, currentLatitude, currentLongitude);
				}
				lectureList=lectureList->next;
			}
		} else {
			AppLog("lectureList is still null");
		}

		//pList->Construct();
		//pList->Add(*pLocation);
		//__pUiControl->SendUserEvent(LocationManagerMainForm::LOC_MGR_DRAW_SYNC_LOC_UPDATE, pList);
		Thread::Sleep(10000);
	}
	return null;
}
