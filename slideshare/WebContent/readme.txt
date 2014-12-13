"database.sql" is the sql file that contains all the database definitions, table definitions and all the records stored in them (it includes the tables (tblstudent, tblprofessor, tblclass, tblattendance, tblenroll), you just need to import this file in your wamp or somtg...
it may be neccesary to change the database username and password (in serverfile.js)
the "abc.csv" file is an example of an csv file the professor could use to enroll students to his newly created class.
everything on the clientside is done on the index.html, and everything on the server is in the serverfile.js
the folder "p0" contains some sample ppt slides in image format, once the conversion part is finished its not neccessary to have it, (the conversion part will convert the file and stores .PNG files in a folder it creates byitself)
The file uploading part will upload to this current directory, thereby the conversion part could proceed in converting it and creates a folder for each professor having all the slides as an image of the ppt file
places where modification is needed is commented in the "index.html" (vartica might need to modify the location and the cookie storage part)


What is left is:
	file uploading
	file converting
	location checking & cookie storage

What is done:
	Q&A
	Streaming
	Professor & Student Interface


it seems to satisfy the functional requirements but interms of the beauty and stuff.... i think the beauty is in the eyes of the beholder... :|