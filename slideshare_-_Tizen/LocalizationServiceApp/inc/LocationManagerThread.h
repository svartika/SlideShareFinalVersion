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

#ifndef _LOCATION_MANAGER_THREAD_H_
#define _LOCATION_MANAGER_THREAD_H_

#ifndef _LECTURE_INFO_H_
#include "LectureInfo.h"
#endif

class LocationManagerThread
	:public Tizen::Base::Runtime::Thread
{
public:
	static result r;
	static LocationManagerThread* GetInstance();
	LocationManagerThread(void);
	virtual ~LocationManagerThread(void);
	void SetLectureInfo(LectureInfo* lectures);
	result Construct();//const Tizen::Ui::Control& uiControl);
	Tizen::Base::Object* Run(void);
	void showNotification();

private:
	LectureInfo* lectures = null;
	static LocationManagerThread *locationManagerThread;
	//const Tizen::Ui::Control* __pUiControl;
};

#endif /* _LOCATION_MANAGER_THREAD_H_ */
