function showNewLectureNotification()	{
	var appControl = new tizen.ApplicationControl();  // open app here TODO:
	try {
		var notificationDict = {
				content : "New Lecture Available in Notification Dict",
				iconPath : "./images/lecture_notification_icon.jpeg",
				vibration: true,
				appControl: appControl,
				soundPath: "sounds/ping.mp3"
		};
		newLectureNotification = new tizen.StatusNotification("SIMPLE", "New Lecture Available Text", notificationDict);
		tizen.notification.post(newLectureNotification);
		
		} catch (err) {
		console.log (err.name + ": " + err.message);
		}
}