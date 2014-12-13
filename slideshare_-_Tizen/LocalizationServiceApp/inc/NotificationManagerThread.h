/*
 * NotificationManagerThread.h
 *
 *  Created on: Nov 23, 2014
 *      Author: misha
 */

#ifndef NOTIFICATIONMANAGERTHREAD_H_
#define NOTIFICATIONMANAGERTHREAD_H_

#include <FBaseRtThread.h>
#include "LectureInfo.h"

class NotificationManagerThread: public Tizen::Base::Runtime::Thread {
public:
	static NotificationManagerThread* GetInstance();
	virtual ~NotificationManagerThread(void);


	result Construct();//const Tizen::Ui::Control& uiControl);
	Tizen::Base::Object* Run(void);
	void setLectures(LectureInfo* lectures);
	static result r;
private:
	LectureInfo* lectures;
	static NotificationManagerThread* instance;
	NotificationManagerThread(void);
	void showNotification();
};

#endif /* NOTIFICATIONMANAGERTHREAD_H_ */
