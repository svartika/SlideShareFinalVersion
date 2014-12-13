var fs = require('fs');
var path = require("path");
var mysql = require('mysql');
var WebSocketServer = require('ws').Server;

function Student(id, ws){
	this.id = id;
	this.ws = ws;	
}

function Professor(id) {
		this.students =[];
		this.id = id;
		this.currentSlide = 0;
		this.numberOfSlides = 5;
		this.pptNumber=-1;
		this.ws;
}


function test(d)
{
	this.c = [];
	this.c[0] = d;
}


	
var connection = mysql.createConnection('mysql://root:slideshare@localhost:3306/test');

var professors = [];


wss = new WebSocketServer({ host:'210.107.198.176', port: 22222 });


wss.on('connection', function (ws){

	ws.on('message', function message(data){
		str = data.split("`");

			switch(str[0]){
				case "0":
				connection.query("select * from tblprofessor", function(err, rows, fields) {
				if (err) throw err;
	 
				for(var i in rows) {
					if(rows[i].name == str[1] && rows[i].password == str[2]){
						ws.send('0`1`' + rows[i].id);
						return;
					}
				}

				ws.send('0`0');		//not succesful in loging in
			});
			break;
			case "1":
				connection.query("select * from tblstudent", function(err, rows, fields) {
				if (err) throw err;
	 
				for(var i in rows) {
					if(rows[i].id == str[1]){
						ws.send('1`1`' + rows[i].name);
						return;
					}
				}
				ws.send('1`0');	
			});
			break;
			case "2":
			connection.query("select * from tblclass where professorid='" + str[1] + "' order by time", function(err, rows, fields) {
				if (err) throw err;
	 			
				var x = "";
				
				for(var i in rows)
					x += rows[i].id + '`' +  rows[i].room + '`' +  rows[i].professorid + '`' +  rows[i].time + '`' +  rows[i].location + '`';
					
				ws.send('2`' + x);	
			});
			break;
			case "3":
				connection.query("select * from tblclass where professorid='" + str[1] + "' order by time", function(err, rows, fields) {
				if (err) throw err;
	 							
				var d = new Date();
				for(var i in rows) {
					
					if(d.getHours() * 60 + d.getMinutes() < ((rows[i].time.charCodeAt(0) - 65) * 90 + 9 * 60)){
						ws.send('3`' + rows[i].room + '`' + rows[i].time);	
						return;
					}
				}

				if(rows.length != 0)
					ws.send('3`' + rows[0].room + '`' + rows[0].time);
				else
					ws.send('3`_`_');
				});
			break;
			case "4":
				connection.query('insert into tblclass (room,professorid,time,location) VALUES (\'' + str[2] + '\',\'' + str[1] + '\',\'' + str[3] + '\',\'' + str[4] + '\')' , function(err, rows, fields) {

				if (err)
					throw err;
				else
				{
					connection.query("select id from tblclass", function(err, rows, fields) {
						
						if (err){
							ws.send('4`0');
							throw err;
						}
						else
						{	
							stdnts = str[5].split(",");
							
							for(var i = 0; i < stdnts.length;i++){
								connection.query('insert into tblenroll (classid,studentid) VALUES (\'' + rows[rows.length-1].id + '\',\'' + stdnts[i] + '\')', function(err, rows, fields) {
									if (err)
									{
		   								ws.send('4`0');
										throw err;
									}
								});
							}	
						}
					});
				}
			});
			
				ws.send('4`1');
			break;
			case "5":
				var p = new Professor(str[1]);
				p.ws = ws;				
				console.log('random file number is '+str[2]);
				p.pptNumber=str[2];
				professors.push(p);
				
				//fs.mkdir('p' + p.id, function(err){});
				//conversion and uploading to the above folder is done here
				
				
				
				fs.readdir("p" + str[2]/*p.id*/, function (err, files){
					//files.length;
					
					ws.send('5`' + files.length);
				});
				break;
			case "6":
					connection.query('select tblenroll.studentid,tblclass.professorid, tblprofessor.name, tblclass.room, tblclass.time, tblclass.location, tblenroll.classid from tblprofessor,tblclass,tblenroll where tblprofessor.id=tblclass.professorid and tblenroll.studentid=\'' + str[1]  + '\' order by time', function(err, rows, fields) {
						if (err) throw err;
						
						var found = false;
						for(var n = 0; n < rows.length && !found; n++){
							for(var m = 0; m < professors.length && !found; m++){
								if(professors[m].id == rows[n].professorid){
									if(str[2] == null)
										professors[m].students.push(new Student(str[1], ws));

									ws.send("6`2`" + rows[n].professorid + "`" + professors[m].currentSlide + "`" + rows[n].name + "`" + rows[n].room + "`" + rows[n].time + "`" + rows[n].location+ "`" + professors[m].pptNumber);	
									found = true;
									
									var d = new Date();
									connection.query("insert into tblattendance (classid,studentid,date) values ('" + rows[n].classid + "','" + rows[n].studentid + "','" + (d.getDate() + '/' + (d.getMonth() + 1) + "/" + d.getFullYear()) + "')", function(err, rows, fields) {
									});
								}
							}
						}
						
						if(!found)
						{
							var d = new Date();
							for(var i in rows) {
								if(d.getHours() * 60 + d.getMinutes() < ((rows[i].time.charCodeAt(0) - 65) * 90 + 9 * 60)){
									ws.send('6`1`1`' + rows[i].room + '`' + rows[i].time + '`' + rows[i].name + '`' + rows[i].location);	
									return;
								}
							}
							
							if(rows.length == 0)
								ws.send('6`1`0');

						}
					});

				
			break;
			case "7":
				for(var m = 0; m < professors.length ; m++){
					if(professors[m].id == str[1]){
						for(var i = 0; i < professors[m].students.length; i++){
							professors[m].currentSlide = str[2];
							professors[m].students[i].ws.send('7`' + professors[m].pptNumber/*professors[m].id*/ + '`' + professors[m].currentSlide);
						}
					}
				}
			break;
			case "8":
				connection.query("select distinct tblclass.room,tblattendance.date from tblclass,tblstudent,tblattendance where tblclass.professorid='" + str[1] + "' and tblclass.time='" + str[2] + "' and tblclass.id=tblattendance.classid and tblstudent.id=tblattendance.studentid order by date", function(err, rows, fields) {
					if(err) throw err;
					
		
					var x = "";
					for(var i = 0; i < rows.length; i++){
						x +=  rows[i].room + "`" + rows[i].date + '`' ;
					}
					
					if(rows.length != 0)
						ws.send("8`1`" + str[2] + '`' + x);
					else
						ws.send("8`0");
					
				});
			break;
			case "9":
				connection.query("select distinct tblattendance.studentid, tblstudent.name from tblstudent,tblattendance where tblstudent.id=tblattendance.studentid and tblattendance.date='" + str[1] + "'", function(err, rows, fields) {
					if(err) throw err;
					
					var x = "";
					for(var i = 0; i < rows.length; i++){
						x +=  rows[i].studentid + "`" + rows[i].name + '`' ;
					}
					

					ws.send("9`" + x);
									
				});
			break;
			case "10":
			case "11":
			connection.query("select name from tblstudent where id='" + str[1] + "'", function(err, rows, fields) {
				for(var i = 0; i < professors.length; i++){
					for(var n = 0; n < professors[i].students.length; n++){
						if(professors[i].students[n].id == str[1]){
							for(var m = 0; m < professors[i].students.length; m++)
								professors[i].students[m].ws.send(str[0] + '`' + rows[0].name + '`' + str[2]);
	
							professors[i].ws.send(str[0] + '`' + rows[0].name + '`' + str[2]);
							message('6`' + str[1] +  '`0');
							return;
						}
					}
				}
			});
			
			break;
			case "12":
					connection.query('select tblenroll.studentid, tblstudent.name, tblclass.room, tblclass.time, tblclass.location, tblenroll.classid from tblclass,tblenroll,tblstudent where tblenroll.studentid=tblstudent.id and tblclass.id=tblenroll.classid and tblenroll.studentid=\'' + str[1]  + '\' order by time', function(err, rows, fields) {
						if (err) throw err;
						
						var x="12`1`";
						for(var n = 0; n < rows.length; n++){
							x += rows[n].time + "`" + rows[n].location.replace(',', '`') + '`';	
						}
						
							
							if(rows.length == 0)
								ws.send('12`0');
							else
								ws.send(x);

					});

				
			break;
		}
	});
	
	ws.on('close', function () {

	   for(var i = 0; i < professors.length; i++)
	   {
		   if(professors[i].ws == ws){
				for(var m = 0; m < professors[i].students.length; m++){
					professors[i].students[m].ws.send('6`0');		//class ended
				}

				/*
				fs.readdir("p" + professor[i].id, function (err, files) {
					files.forEach(function (file) {
						fs.unlink("p" + professor[i].id, function(err){console.log(err);});			//for cleaning up slide images of the quiting professor
					});
				});
				
				fs.rmdir("p" +  professor[i].id, function (err) {console.log(err);});
				*/

				professors.splice(i,1);
				break;
		   }
		   else	
				for(var m = 0; m < professors[i].students.length; m++)
					if(professors[i].students[m].ws == ws){
						professors[i].students.splice(m, 1);
						break;
					}
	   }
		   				
    });
});