/*
 * MessagePort.h
 *
 *  Created on: Nov 23, 2014
 *      Author: misha
 */

#ifndef MESSAGEPORT_H_
#define MESSAGEPORT_H_


#include <FApp.h>
#include <FBase.h>
#include <FIo.h>


class MessagePort : public Tizen::Io::IMessagePortListener	{
public :
	MessagePort(void);

	~MessagePort(void);

	result Construct(const Tizen::Base::String& localPortName);

	virtual void OnMessageReceivedN(Tizen::Io::RemoteMessagePort* pRemoteMessagePort, Tizen::Base::Collection::IMap* pMessage);

	result SendMessage(const Tizen::Base::Collection::IMap* pMessage);

private :
	Tizen::Io::LocalMessagePort* __pLocalMessagePort;
	Tizen::Io::RemoteMessagePort* __pRemoteMessagePort;

};

#endif /* MESSAGEPORT_H_ */
