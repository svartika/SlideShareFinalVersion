<!DOCTYPE html>
<%@ page language="java" 	contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<html style="height:98%">
<title>SlideShare</title>
<script>
window.onload= function(){};
</script>

<body style="height: 100%; background:url(bg.jpg); background-size:cover; color:#FFF">

<table cellpadding="0px" cellspacing="0px" style="height:100%; width:100%;"><tr><td align="center" id = "mainwindow"></td></tr></table>

<script>

	//if("WebSocket" in window)
	//	alert("WebSocket is supported!");
	//else
	//	alert("WebSocket is not supported!");
	

	var temp = "";
	var currentStudentId;
	var currentProfessor = [];
	var fromServer;
	var ws = new WebSocket('ws://210.107.198.176:22222');
	var random_file_num=-1;
	<%
		request.setCharacterEncoding("UTF-8");
		String successMsg = request.getParameter("successMsg");
	%>
	random_file_num = <%=successMsg%>;
	
	console.log('random_file_num '+random_file_num);
// 	if(random_file_num != "-1" && random_file_num != null){
// 		toServer('5`' +currentProfessor[0] + '`'+random_file_num);
// 	}

	function toServer(data){

		str2 = data.split('`');
		switch(str2[0]){
		case "4":
		alert("wow");
			/*var f = document.getElementById('fstudents').files[0];
					if(f)
					{
						var r = new FileReader();
						r.onload = function(e){
							ws.send(data + '`' + e.target.result);
						}
						r.readAsText(f);
					}*/
		break;
		default:
			ws.send(data);
		}

	}
	
	ws.onmessage = fromServer = function (data){
		str = data.data.split("`");
	
		switch(str[0]){
			case "0":
				if(str[1] == "1")
				{
					currentProfessor[0] = str[2];
					currentProfessor[1] = document.getElementById('txtname').value;
					showProfessorPage();
					toServer('3`' + currentProfessor[0]);
				}else
					alert("Please type in the correct Name/Password combination.");
					
			break;
			case "1":
				if(str[1] == "0")
				{
					alert("Please enter  your id.");
					registerStudent("0");		
				}else
				{
					registerStudent("1", str2[1]);	
					toServer('6`' + str2[1]);
				}
				
			break;
			case "2":
				showAddClass("1", data.data);
			break;
			case "3":
				showMakeLecture(data.data);
			break;
			case "4":
				if(str[1] == "1")
				{
					alert("Class successfuly added.");
					toServer('2`' + currentProfessor[0]);
				}
				else
				{
					alert("Error while adding class");
					showAddClass("2");
				}
					
			break;
			case "5":
				showProfessorLecture(data.data);
			break;
			case "6":
				switch(str[1]){
				case "0":
					toServer('6`' + currentStudentId);
				break;
				case "1":
				if(str[2] == 0)
					alert("No ongoing lecture.");
				else
				{
					showClassInfo(data.data);	//your current location (vartica)
				}
					//show next lecture, next period ...			
				break;
				break;
				case "2":
					str3 = data.data.split('`');
					if(str3[7] != "38.898748,-77.036626") //Your Current Location	(vartica)
						alert("Caution! Your are not in lecture place. Attendance will not be taken!");
						
					studentTakesLecture(data.data);
				break;
			}
			break;
			case "7":
				document.getElementById("mainPic").src = 'p' + str[1] + '/' + str[2] + '.PNG';
				document.getElementById("mainPic").onload =  function(){
					var winDim=getWinDim();
					var img=document.getElementById('mainPic');
					img.style.height=winDim.y + "px";		

				    if (img.offsetWidth > winDim.x)
				    {
				        img.style.height = null;
				        img.style.width = winDim.x + "px";
				    }	
				}				
			break;
			case "8":
				showAttendants("0", data.data);
			break;
			case "9":
				showAttendants("1", data.data);
			break;
			case "10":
				temp = '<div style="color:orange">' + str[1] + ': ' + str[2] + '</div>' + temp;
				document.getElementById('qafeed').innerHTML = '<div style="color:orange">' + str[1] + ': ' + str[2] + '</div>' + document.getElementById('qafeed').innerHTML;
			break;
			case "11":
				temp = '<div style="color:red">' + str[1] + ': ' + str[2] + '</div>' + temp;
				document.getElementById('qafeed').innerHTML = '<div style="color:red">' + str[1] + ': ' + str[2] + '</div>' + document.getElementById('qafeed').innerHTML ;
			break;
			
			case "12":
			//	alert(data.data.substring(5));
			break;
		}
	};
		window.onload = function(){
//		alert("loaded");
		if(document.cookie.indexOf("firsttime") != -1)			//should be ==
		showInitialPage();
	else
		toServer('1`' + document.cookie.substr("firsttime=".length, document.cookie.length - "firsttime=".length)); //reading from cookie (vartica)

	};
	
	function slideChange(imgid){
		document.getElementById("mainPic").src = document.getElementById("i" + imgid).src;
		var winDim=getWinDim();
		var img=document.getElementById('mainPic');
		img.style.height=winDim.y + "px";		

	    if (img.offsetWidth > winDim.x)
	    {
	        img.style.height = null;
	        img.style.width = winDim.x + "px";
	    }
		toServer('7`' + currentProfessor[0] + '`' + imgid);
	}

	function studentInteracts(type){

		if(type=="0")
			document.getElementById('mainwindow').innerHTML = '<table><tr><td><h2><u>Answer</u></h2></td></tr><tr><td> </td></tr><tr><td><textarea id="itext" cols=30 rows=5></textarea></td></tr><tr><td> </td></tr><tr><td align="right"><input type="button" value="Cancel" onclick="toServer(\'6`' + currentStudentId + '`0\')"> <input type="button" value="Submit" onclick="toServer(\'10`' + currentStudentId + '`\' + document.getElementById(\'itext\').value)"></td></tr></table>';
		else
			document.getElementById('mainwindow').innerHTML = '<table><tr><td><h2><u>Question</u></h2></td></tr><tr><td> </td></tr><tr><td><textarea id="itext" cols=30 rows=5></textarea></td></tr><tr><td> </td></tr><tr><td align="right"><input type="button" value="Cancel" onclick="toServer(\'6`' + currentStudentId + '`0\')"> <input type="button" value="Submit" onclick="toServer(\'11`' + currentStudentId + '`\' + document.getElementById(\'itext\').value)"></td></tr></table>';
	
	}

	function showAttendants(type, data){
		str = data.split('`');
		switch(type)
		{
			case "0":
				if(str[1] == "0")
					alert("No Attendants");
				else
				{
					var option = [[]];
					var cntnt = '<table align="center" width="100%" border="0"><tr><td>Room: ' + str[3] + '</td></tr><tr><td>Time: ' + str[2] + '</td><td align="right">Date: <select>';
		
					for(var y = 4; y < str.length - 1; y+=2)
						cntnt += '<option value="' + str[y] + '" onclick="toServer(\'9`' +  str[y] + '\')">' + str[y] + '</option>';
			
			
					cntnt += '</option></td></tr><tr><td colspan="2">&nbsp;</td></tr><tr><td colspan="2" id="attendants">list of students</td></tr></table>';

					document.getElementById('classes').innerHTML = cntnt;
					toServer('9`' + str[4]);
				}
				

			break;
			case "1":
				var x = '<table border="1px" width="100%"><tr><td><b>ID</b></td><td><b>Name</b></td></tr>';
				for(var i = 1; i < str.length - 1; i+=2){
					x += '<tr><td>' + str[i] + '</td><td>' + str[i + 1] + '</td></tr>';
				}
				x += '</table>';
				
				document.getElementById('attendants').innerHTML = x;
			break;
		}
	}

	function showClassInfo(data){
		str = data.split('`');
		//alert(str[6]);
		document.getElementById('mainwindow').innerHTML = '<table border="25%"><tr><td><table border="0"><tr><td>Next Class:</td></tr><tr><td>&nbsp</td></tr><tr><td align="right">Room:</td><td>' + str[3] + '</td></tr><tr><td align="right">Time:</td><td>' + str[4] + '</td></tr><tr><td colspan="2" style="color:red" >' +  (/*vartica, current location*/str[6] != "38.898748,-77.036623"?'<br /><hr></hr>Caution! Attendance will not be marked <br /> unless you physically go to class location.' : '' ) + '</td></tr></table></td></tr></table>';
	}

	function showInitialPage(){
		document.getElementById('mainwindow').innerHTML = '<table border="25%"><tr><td><table cellspacing="5" cellpadding="5"><tr><td>Login As:</td><td>&nbsp;</td></tr><tr align="center"><td>&nbsp;</td><td><input type="button"  style="width:100%"   value="Student" id="btnstudent" onclick="registerStudent(\'0\')" /></td></tr><td>&nbsp;</td><td><input type="button" style="width:100%" value="Professor" id="btnprofesor" onclick="loginProfessor()"/></td></tr></table></td></tr></table>';
	}

	function registerStudent(type, id){
		switch(type)
		{
			case "0":
				document.getElementById('mainwindow').innerHTML = '<table border="25%"><tr><td><table cellspacing="5" cellpadding="5"><tr><td>First Time ID Registration:</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>&nbsp;</td></tr><tr align="rightr"><td align="right">Student ID:</td><td><input type="text" id="txtid" value="201411113" /></td></tr><td>&nbsp;</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td><input type="button" onclick="showInitialPage()" style="width:50%" value="Cancel" /><input type="button" onclick="toServer(\'1`\' + document.getElementById(\'txtid\').value)" style="width:50%" value="Ok" /></td></tr></table></td></tr></table>';
			break; 
			case "1":				
				date = new Date();
				date.setTime(date.getTime() + 315360000000000);	 		//10,000 years for expiry ;)
				
				document.cookie = "firsttime=" + id + "; expires=" + date.toGMTString() + "; path=/";

				currentStudentId = id;
			break;
		}
	}
	
	function loginProfessor(){
		document.getElementById('mainwindow').innerHTML = '<table border="25%"><tr><td><table cellspacing="5" cellpadding="5"><tr><td>Professor Login:</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td>&nbsp;</td></tr><tr align="right"><td>Professor ID/Name:</td><td><input type="text" id="txtname" value="Prof. Seok-Won Lee" /></td></tr><tr align="right"><td>Password:</td><td><input type="password" value="abc" id="txtpass" /></td></tr><td>&nbsp;</td><td>&nbsp;</td></tr><tr><td>&nbsp;</td><td><input type="button" onclick="showInitialPage()" style="width:50%" value="Cancel" /><input type="button" onclick="toServer(\'0`\' + document.getElementById(\'txtname\').value + \'`\' + document.getElementById(\'txtpass\').value)" style="width:50%" value="Ok" /></td></tr></table></td></tr></table>';
	}
	
	
	function showProfessorPage(){
		document.getElementById('mainwindow').style.verticalAlign = "top";
		document.getElementById('mainwindow').innerHTML = '<h2><table border="0%" width="100%" height="100%">'+
		'<tr><td style="vertical-align:top;"><table width="100%" cellspacing="5" cellpadding="5">'+
		'<tr><td><table border="0px" width="100%" align="center"><tr><td><a href="javascript:toServer(\'3`' + currentProfessor[0] + '\')">Lecture</a></td>'+
		'<td><a href="javascript:showAddClass()">Classes</a></td></tr>'+
		'<tr><td colspan="2"><hr></td></tr><tr><td colspan="2" id="subMainWindow"></td></tr>'+
		'</table></td></tr></table></td></tr></table></h2>';
	}
	
	function studentTakesLecture(data){
		str = data.split('`');

		document.getElementById('mainwindow').innerHTML = '<table border="1px" height="99%" width="auto">'+
		'<tr><td colspan="2" align="center"><h2>Slideshare</h2></td></tr>'+
		'<tr><td><input type="button" onclick="studentInteracts(\'0\')" value="Answer!"> <input type="button" onclick="studentInteracts(\'1\')" value="Ask!"></td>'+
		'<td align="right"><div style="color:gray">' + str[4] + '</div></td></tr>'+
		'<tr><td colspan="2" align="center"><img id="mainPic" style="height:80%" src="./p' + str[8] /*hyeonju changed ..str[2]*/ + '/' + str[3] + '.PNG" /></td></tr>'+
		'<tr><td id="sdqa" colspan="2"></td></tr></table>';
		
		
		document.getElementById('mainPic').onload = function(){
			var winDim=getWinDim();
			var img=document.getElementById('mainPic');
			img.style.height=winDim.y + "px";		

		    if (img.offsetWidth > winDim.x)
		    {
		        img.style.height = null;
		        img.style.width = winDim.x + "px";
		    }
			document.getElementById('sdqa').innerHTML = '<div id="qafeed" style="overflow-y:scroll; white-space:wrap; height:4em;width:' +  document.getElementById('mainPic').width + 'px;">' + temp + '</div>';
		};
		
	}
	
	function getWinDim()
	{
	    var body = document.documentElement || document.body;

	    return {
	        x: window.innerWidth  || body.clientWidth,
	        y: window.innerHeight || body.clientHeight
	    }
	}
	alert('window size : '+getWinDim().x);
	if(getWindDim().x < 1000){
		console.log('small size');
		screen.lockOrientation('landscape');
	}
	
	function showMakeLecture(data){
		str = data.split('`');
		//http://210.107.198.176:8080/slideshare/converter.jsp
		document.getElementById('subMainWindow').innerHTML = '<br /><h2><table align="center" cellspacing="3%"><tr><td>Class Location: </td><td>' + str[1] + 
		'</tr><tr><td align="right">Time: </td><td>' + str[2] + '</td></tr><tr><td colspan="2">&nbsp;</td></tr>'+
		"<tr><td>Upload Slides: </td><td>"+
		"<form id=\"setFile\" action=\"http://210.107.198.176:11111/upload\", method=\"post\", enctype=\"multipart/form-data\">"+
		"<input type=\"file\" id=\"filename\" name=\"uploadFile\">"+
		"<input type=\"submit\" value=\"Upload\"></form>"+
		"</td></tr>"+
		"<tr><td colspan=\"2\">&nbsp;</td></tr></table></h2>"+
		"<br /><div align=\"center\"><input align=\"center\" type=\"button\" value=\"Start Lecture!\" id=\"btnstart\" onclick=\"toServer(\'5`' + currentProfessor[0] + '\`'+random_file_num)\" /></div>";
		
	}
	
// 	function showProfessorLecture(data){
// 		str = data.split('`');

// 		var presentation =  '<table id="maintbl" width="70%" align="center" border="8px" >'+
// 		'<tr><td colspan="2" width="100%" align="center"><h2>Slideshare</h2></td></tr>'+
// 		'<tr><td id="slds" align="center" style="vertical-align:top; ">';

// 		for(var i = 0; i < str[1]; i++)
// 			presentation += '<img id="i' + i + '" style="width:100px height:auto" onclick="slideChange(' + i + ')" src="p' + 0/*currentProfessor[0]*/ + "/" + i + '.PNG" /></br>';
		
// 		presentation +=	'</td></td><td align="center"><img id="mainPic" src="p' + 0/*currentProfessor[0]*/ + '/0.PNG" /></td></tr><tr><td style="background:blue; color:white;">Class Participation</td><td></td></tr><tr><td colspan="2" id="sdqa"></td></tr></table>';
		
// 		document.getElementById('mainwindow').innerHTML = presentation;
		
// 		document.getElementById('mainPic').onload = function(){
// 			for(var i = 0; i < str[1]; i++)
// 				document.getElementById('i' + i).width = document.getElementById('mainPic').width*.20;
				
// 				document.getElementById('sdqa').innerHTML = '<div id="qafeed" style="overflow-y:scroll; white-space:wrap; height:4em;width:' +  document.getElementById('maintbl').width + 'px;"></div>';
// 		};
		
// 	}
	
	function showProfessorLecture(data){
		str = data.split('`');

		var presentation =  '<table id="maintbl" width="70%" align="center" border="8px" >'+
		'<tr><td colspan="2" width="100%" align="center"><h2>Slideshare</h2></td></tr>'+
		'<tr><td id="slds" align="center" style="vertical-align:top; ">'+
		'<div id="container" style="overflow-y:scroll; white-space:wrap; height: 600px">';
	
		for(var i = 0; i < str[1]; i++)
			presentation += '<img id="i' + i + '" onclick="slideChange(' + i + ')" src="p' + random_file_num/*currentProfessor[0]*/ + "/" + i + '.PNG" /></br>';
		
		presentation +=	'</div></td></td><td align="center"><img id="mainPic" src="p' + random_file_num/*currentProfessor[0]*/ + '/0.PNG" /></td></tr><tr><td style="background:blue; color:white;">Class Participation</td><td></td></tr><tr><td colspan="2" id="sdqa"></td></tr></table>';
		
		
		document.getElementById('mainwindow').innerHTML = presentation;
		
		
		document.getElementById('mainPic').onload = function(){
			var winDim=getWinDim();
			var img=document.getElementById('mainPic');
			var container= document.getElementById('container');
			img.style.height=winDim.y*0.8 + "px";
			container.style.height=winDim.y*0.8 + "px";

		    if (img.offsetWidth > winDim.x)
		    {
		        img.style.height = null;
		        img.style.width = winDim.x + "px";
		    }
			for(var i = 0; i < str[1]; i++)
				document.getElementById('i' + i).width = document.getElementById('mainPic').width*.20;
				
				document.getElementById('sdqa').innerHTML = '<div id="qafeed" style="overflow-y:scroll; white-space:wrap; height:4em;width:' +  document.getElementById('maintbl').width + 'px;"></div>';
		};
		
	}
	
	function showAddStudent(){
		document.getElementById('subMainWindow').innerHTML = 'Add Student Here';
	}
	
	
	
// 	if(random_file_num!="false"){
// 		toServer('5`' +currentProfessor[0] + '`'+random_file_num);
		
// 		console.log('random_file_num');
// 		//loginProfessor();
		
// 	}else if (random_file_num=="false"){
// 			alert("upload failed!");
// 	}
	
</script>


</html>