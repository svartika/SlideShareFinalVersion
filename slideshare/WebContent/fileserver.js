var express = require('express');
var busboy = require('connect-busboy');
var multer = require('multer');
var fs = require('fs');
var app = express();

app.use(busboy());
app.use(multer());

app.listen(11111, "210.107.198.176", function(){
console.log('Server Start.');
});

app.get('/', function(req,res){
fs.readFile('index.html', function(error,data){
res.writeHead(200, {'Content-Type': 'text/html'});
res.end(data, function (error){
console.log(error);
});
});
});

app.post('/upload', function(req,res){
fs.readFile(req.files.uploadFile.path, function(error, data){
var filePath = "./uploads/" + "test.ppt";
fs.writeFile(filePath, data, function(error){
if(error){
throw error;
} else { 
//res.redirect("back");
console.log('uploaded!');
res.redirect('http://210.107.198.176:8080/slideshare/converter.jsp');
//res.writeHead(303, { Location : req.url });
}
});
});
});