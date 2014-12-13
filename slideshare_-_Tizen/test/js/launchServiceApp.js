
var app = tizen.application.getCurrentApplication();
var gServiceAppId = "oxEWc0z8PB.LocalizationServiceApp";



function onGetAppsContextSuccess(contexts) {
	//console.log('contexts: '+contexts);
	for (var i = 0; i < contexts.length; i++) {
		var appInfo = tizen.application.getAppInfo(contexts[i].appId);
		if(appInfo.id == gServiceAppId){
			console.log("Running Service App found");
			break;
		}
	}
	if (i >= contexts.length) {
		console.log("Running Service App not found. Trying to launch it");
		launchServiceApp();
		//listInstalledApps();
	}else{
		startMessagePort(funk);
		
	}
}

function onGetAppsContextError(err) {
	console.log("getAppsContext exc");
}

function listInstalledApps() {
	try {
		tizen.application.getAppsInfo(getAppsInfoSuccessCB, getAppsInfoErrorCB);
	} catch (exc) {
		console.log("Get Installed App Info Error");
	}
}

function getAppsInfoSuccessCB(apps) {
	for (var i = 0; i < apps.length; i++) {
		if(apps[i].id == gServiceAppId){
			console.log("Found installed Service App")
			break;
		}
	}
	if(i >= apps.length){
		console.log("Service App not installed");
		isStarting = false;
		return;
	}
	launchServiceApp();
}

function getAppsInfoErrorCB(err) {
	console.log("getAppsInfo failed");
	isStarting = false;
}

function start() {
	try {
		tizen.application.getAppsContext(onGetAppsContextSuccess, onGetAppsContextError);
	} catch (exc) {
		console.log("Get AppContext Error");
	}
}

function launchServiceApp() {
	function onSuccess() {
		console.log("Service App launched successfully!");
		console.log("Restart...");
		start();
	}

	function onError(err) {
		console.log("Service Applaunch failed"+err);
		isStarting = false;
		console.log("Failed to launch LocalizationServiceApp!");
	}

	try {
		console.log("Launching [" + gServiceAppId + "] ...");
		tizen.application.launch(gServiceAppId, onSuccess, onError);
	} catch (exc) {
		console.log("Exception while launching LocalizationServiceApp: " + exc.message);
	}
}

var funk;

var launchServiceAppFromWebApp = function(myfunc)	{
	funk = myfunc;
	try {
		console.log("launchServiceAppFromWebApp");
		tizen.application.getAppsContext(onGetAppsContextSuccess, onGetAppsContextError);
	} catch (exc) {
		console.log("Get AppContext Error ....Exception while launching LocalizationServiceApp: " + exc.message);
	}
};
	