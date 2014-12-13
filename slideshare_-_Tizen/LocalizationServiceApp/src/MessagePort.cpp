/*
 * MessagePort.cpp
 *
 *  Created on: Nov 23, 2014
 *      Author: misha
 */

#include "MessagePort.h"
#include "MyType.h"
#include "DataParser.h"
//#include "LectureInfo.h"
#include "LocationManagerThread.h"
#include "NotificationManagerThread.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Io;


MessagePort::MessagePort(void)
	: __pLocalMessagePort(null)
	, __pRemoteMessagePort(null)
{
}

MessagePort::~MessagePort(void)
{
}

result
MessagePort::Construct(const String& localPortName)
{
	result r = E_SUCCESS;

	__pLocalMessagePort = MessagePortManager::RequestLocalMessagePort(localPortName);
	TryReturn(__pLocalMessagePort != null, E_FAILURE, "[E_FAILURE] Failed to get LocalMessagePort instance.");

	__pLocalMessagePort->AddMessagePortListener(*this);

	AppLog("LocalMessagePort(\"%ls\") is ready !!!", __pLocalMessagePort->GetName().GetPointer());

	return r;
}

void
MessagePort::OnMessageReceivedN(RemoteMessagePort* pRemoteMessagePort, IMap* pMessage)
{
	AppLog("OnMessageReceivedN is invoked");

	String *pData = static_cast<String *>(pMessage->GetValue(String(L"command")));
	String *pPayload = static_cast<String *>(pMessage->GetValue(String(L"payload")));


	AppLog("OnMessageReceivedN is called. pData is %S", pData->GetPointer());
	if(pPayload!=null)
		AppLog("OnMessageReceivedN is called. pPayload is %S", pPayload->GetPointer());
	HashMap *pMap =	new HashMap(SingleObjectDeleter);
	pMap->Construct();

	if (pData->Equals(String(L"connect")))
	{
		__pRemoteMessagePort = pRemoteMessagePort;
		pMap->Add(new String(L"server"), new String(L"WELCOME"));
	}
	else if (pData->Equals(String(L"start")))
	{
		App* pApp = App::GetInstance();
		//pApp->SendUserEvent(TIMER_START, null);
		pMap->Add(new String(L"server"), new String(L"started"));
	}
	else if (pData->Equals(String(L"set_student_info")))
	{
		App* pApp = App::GetInstance();
		ArrayList* myList = new ArrayList();
		//myList->Construct(1);

		myList->Add(pPayload);

		//hack cos sending of message is corrupting data
		//pApp->SendUserEvent(STUDENT_INFO_RECEIVED, myList);
		AppLog("OnMessageReceivedN is called. payload is %S", pPayload->GetPointer());
		AppLog("OnMessageReceivedN save in to dummy db class");
		DataParser *dataParser = new DataParser();
		LectureInfo* lectureInfo = dataParser->ParseString(*pPayload);
		LocationManagerThread::GetInstance()->SetLectureInfo(lectureInfo);
		NotificationManagerThread::GetInstance()->setLectures(lectureInfo);

		pMap->Add(new String(L"server"), new String(L"student_info_updated"));
	}
	else if (pData->Equals(String(L"lecture_locations")))
	{
		App* pApp = App::GetInstance();
		//String *pData = static_cast<String *>(pMessage->GetValue(String(L"payload")));
		ArrayList* myList = new ArrayList();

		myList->Add(pPayload);
		pApp->SendUserEvent(LECTURE_LOCATION_UPDATED, myList);
		pMap->Add(new String(L"server"), new String(L"locations_updated"));
	}
	else if (pData->Equals(String(L"stop")))
	{
		App* pApp = App::GetInstance();
		//pApp->SendUserEvent(TIMER_STOP, null);
		pMap->Add(new String(L"server"), new String(L"stopped"));
	}
	else if (pData->Equals(String(L"exit")))
	{
		App* pApp = App::GetInstance();
		//pApp->SendUserEvent(TIMER_EXIT, null);
		pMap->Add(new String(L"server"), new String(L"exit"));
	}
	else
	{
		pMap->Add(new String(L"server"), new String(L"unsupported"));
	}

	pRemoteMessagePort->SendMessage(__pLocalMessagePort, pMap);

	delete pMap;

	delete pMessage;
}

result
MessagePort::SendMessage(const IMap* pMessage)
{
	result r = E_SUCCESS;
	AppLog("SendMessage is called.");

	if (__pRemoteMessagePort != null)
	{
		r = __pRemoteMessagePort->SendMessage(pMessage);
	}
	else
	{
		r = E_FAILURE;
	}

	return r;
}
