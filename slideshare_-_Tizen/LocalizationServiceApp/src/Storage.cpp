/*
 * Storage.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: misha
 */

#include "Storage.h"

using namespace Tizen::Base;

Storage* Storage::instance = null;

Storage::Storage(Tizen::App::AppRegistry* appRegistry) {
	// TODO Auto-generated constructor stub
	m_pAppRegistry = appRegistry;
}
Storage::Storage()	{

}
Storage::~Storage() {
	// TODO Auto-generated destructor stub
}

Storage* Storage::getInstance(Tizen::App::AppRegistry* appRegistry ) {
	if(instance==null){
		instance = new Storage(appRegistry);
	}
	return instance;
}

bool Storage::SaveKeyValuePair(String key, String value)	{

	result r = E_SUCCESS;
	r = m_pAppRegistry->Get(key, value);
	if (r == E_KEY_NOT_FOUND)
	{
		m_pAppRegistry->Add(key, value);
	}

	r = m_pAppRegistry->Save();
	if (IsFailed(r))
	{
		// Failed to save data to registry
		return false;
	}

	// Displays the retrieved data
	AppLog("AppRegistry key: [%ls] & value: [%ls]", key.GetPointer() ,value.GetPointer());

	// Updates the state of the application variables

	// Saves the app registry
	r = m_pAppRegistry->Set(key, value);
	if (IsFailed(r))
	{
		// Error condition
		return false;
	}

	r = m_pAppRegistry->Save();
	if (IsFailed(r))
	{
		// Failed to save data to registry
		return false;
	}

	// Retrieves the saved content
	m_pAppRegistry->Get(key, value);

	AppLog("AppRegistry key: [%ls] & value: [%ls]", key.GetPointer() ,value.GetPointer());

	return true;

}

