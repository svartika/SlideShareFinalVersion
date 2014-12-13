var backEventListener = null;

var unregister = function() {
    if ( backEventListener !== null ) {
        document.removeEventListener( 'tizenhwkey', backEventListener );
        backEventListener = null;
        window.tizen.application.getCurrentApplication().exit();
    }
}

//Initialize function
var init = function () {
	console.log('vartika in init');
	// register once
    if ( backEventListener !== null ) {
        return;
    }
    
    // TODO:: Do your initialization job
    console.log("init() called");
    
    var backEvent = function(e) {
        if ( e.keyName == "back" ) {
            try {
                if ( $.mobile.urlHistory.activeIndex <= 0 ) {
                    // if first page, terminate app
                    unregister();
                } else {
                    // move previous page
                    $.mobile.urlHistory.activeIndex -= 1;
                    $.mobile.urlHistory.clearForward();
                    window.history.back();
                }
            } catch( ex ) {
                unregister();
            }
        }
    };
    
    // add eventListener for tizenhwkey (Back Button)
    document.addEventListener( 'tizenhwkey', backEvent );
   // document.
    backEventListener = backEvent;
    
   // watchLocation();
   
/*   setTimeout(
		   function()	{
   console.log("opening web page now");
    //var target = "http://210.107.198.176:8080/pdfConverter/index.html";
    var target = "http://192.168.1.100:420/page.html";
    
    var appControl = new tizen.ApplicationControl("http://tizen.org/appcontrol/operation/view", target);
     
    tizen.application.launchAppControl(appControl, null,
    function() {console.log("browser opened"); },
    function(e) {
    	console.log("browser error" + e.message);
    	App.Share.notify("browser error: " + e.message);
    	});
    console.log("after opening web page now");
		   },2000);*/
    
    //commented this to test launch service app from ui button and now uncommenting it
    
    //startMessagePort();
    launchServiceAppFromWebApp(onServiceConnected);
  //  getStudentInfo(); // to put thomas' API here after his clarification
    console.log('vartika...setStudentInfo');
    //sendCommandtwoparams("set_student_info", "12345`37`12`12345678`37`12`23456789");
}

function onServiceConnected() {
	//alert("adsasda");
	console.log("onServiceConnected");
	toServer('12');
	//sendCommandtwoparams("set_student_info", "38`12`A`51.243629`6.741914`B");
	//sendCommandtwoparams("set_student_info", "38`12`A`39`13`X");
}

$(document).bind( 'pageinit', init );
$(document).unload( unregister );