<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<%@ page import="java.util.*" %>
<%@ page import="java.io.*" %>
<%@ page import ="java.net.URLEncoder" %>
<%@ page import="com.ateam.pdfConverter" %>
<%@ page import="com.ateam.imageConverter" %>
<%@ page import="org.artofsolving.jodconverter.OfficeDocumentConverter"%>
<%@ page import="org.artofsolving.jodconverter.office.DefaultOfficeManagerConfiguration"%>
<%@ page import="org.artofsolving.jodconverter.office.OfficeManager"%>


<%
		File inputFile = new File("C:\\Users\\AJOU\\Desktop\\eclipse-jee-luna-SR1-win32-x86_64\\workspace\\slideshare\\WebContent\\uploads\\test.ppt");
	    File outputFile = new File("C:\\Users\\AJOU\\Desktop\\eclipse-jee-luna-SR1-win32-x86_64\\workspace\\slideshare\\WebContent\\uploads\\test.pdf");
	    OfficeManager officeManager = new DefaultOfficeManagerConfiguration()
	    .setOfficeHome("C:\\Program Files (x86)\\OpenOffice 4").buildOfficeManager();
	    
	    
	    String inputPath="C:\\Users\\AJOU\\Desktop\\eclipse-jee-luna-SR1-win32-x86_64\\workspace\\slideshare\\WebContent\\uploads\\test.ppt";
	    String outputPath="C:\\Users\\AJOU\\Desktop\\eclipse-jee-luna-SR1-win32-x86_64\\workspace\\slideshare\\WebContent\\uploads\\test.pdf";
	    //String inputPath="./uploads/test.ppt";
	    //String outputPath="./uploads/test.pdf";
	   // String inputPath="210.107.198.176:8080\\uploads\\test.ppt";
	    //String outputPath="210.107.198.176:8080\\uploads\\test.pdf";
	    pdfConverter mPdfConverter = new pdfConverter();
	    int randomfile=-1;
	    try{
	    	imageConverter mImageConverter = new imageConverter();
		    if(mPdfConverter.convertPPT2PDF(inputPath, outputPath)){
		    	String profFolder=request.getParameter("profId");
		    	randomfile=mImageConverter.convertPDF2Image(outputPath,profFolder);
		    }
// 		    if(randomfile<0){
// 		    	System.out.println("image converting is failed!");
// 		    }else{
// 		    	System.out.println("converting success!");
// 		    	String rand=""+randomfile;
// 			    request.setAttribute("successMsg",rand);	
// 		    }
		    
	    }catch(Exception e){
	    	System.out.println(e);
	    	System.out.println("converting fail!");
		    request.setAttribute("successMsg","false");
	    }
// 	    finally{
// 	    	RequestDispatcher rd = request.getRequestDispatcher("index.jsp");
// 		    rd.forward(request, response);
// 	    }
	    
	    String value = ""+randomfile;
	    String encodedValue = URLEncoder.encode(value, "UTF-8");
	    response.sendRedirect("index.jsp?successMsg=" + encodedValue);
	    
	    
%>
