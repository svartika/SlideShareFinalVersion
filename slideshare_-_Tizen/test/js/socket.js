var app = tizen.application.getCurrentApplication();
var gServiceAppId = "oxEWc0z8PB.LocalizationServiceApp"; //23lGZwKekJ.LocalizationServiceApp
var gServicePortName = "SAMPLE_PORT";
var gLocalMessagePortName = "SAMPLE_PORT_REPLY";

var gLocalMessagePort;
var gRemoteMessagePort;

var gLocalMessagePortWatchId;

var isStarting = false;
var funk;


function startMessagePort(func) {
	funk = func;
	try {
		gLocalMessagePort = tizen.messageport.requestLocalMessagePort(gLocalMessagePortName);
		gLocalMessagePortWatchId = gLocalMessagePort.addMessagePortListener( function(data, remote) {
			onReceive(data, remote);
		});
	} catch (e) {
		gLocalMessagePort = null;
		//writeToScreen(e.name);
	}

	try {
		gRemoteMessagePort = tizen.messageport.requestRemoteMessagePort(gServiceAppId, gServicePortName);
	} catch (e) {
		gRemoteMessagePort = null;
		//writeToScreen(e.name);
	}

	isStarting = false;

	sendCommand("connect");
}

function sendCommand(command){
	var jsondata = '{"command" : "' + command + '"}';
	console.log("sendCommand:"+command);
	gRemoteMessagePort.sendMessage([ { key:"command", value:command }], gLocalMessagePort);
	//writeToScreen("Sending: " + command);
}

function sendCommandtwoparams(command, payload){
	var jsondata = '{"command" : "' + command + '"}';
    console.log("sendCommand:"+command+":"+payload);
	gRemoteMessagePort.sendMessage([ { key:"command", value:command }, { key:"payload", value:payload } ], gLocalMessagePort);
	//writeToScreen("Sending: " + command);
}

function onReceive(data, remote) {
	var message;

	for(var i in data) {
		if(data[i].key == "server")
			message = data[i].value;
	}

	//writeToScreen("Received : " + message);
	
	if(message == "WELCOME"){
		sendCommand("start");
	}else if(message == "stopped"){
		sendCommand("exit");
	}else if(message == "student_info_updated"){
		//alert('student_info_updated ... ');
		console.log('student_info_updated');
	}else if(message == "locations_updated"){
		alert('Updated Lecture Location ... ');
	}else if(message == "started"){
		console.log('service started');
		funk.call();
		//sendCommandtwoparams("set_student_info", "12345`37`12`12345678`37`12`23456789");
	}else if(message == "exit"){
		if(gRemoteMessagePort)
			gRemoteMessagePort = null;
		if(gLocalMessagePort) {
			gLocalMessagePort.removeMessagePortListener(gLocalMessagePortWatchId);
			gLocalMessagePort = null;
		}
	}
}
