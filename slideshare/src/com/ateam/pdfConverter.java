package com.ateam;

import java.io.File;

import org.artofsolving.jodconverter.OfficeDocumentConverter;
import org.artofsolving.jodconverter.office.DefaultOfficeManagerConfiguration;
import org.artofsolving.jodconverter.office.OfficeManager;


public class pdfConverter{
	public pdfConverter() {
		
	}
	public boolean convertPPT2PDF(String inputPath, String outputPath) {    
	    try {    
	        File inputFile = new File(inputPath);
	        System.out.println("input path = "+inputPath);
	        File outputFile = new File(outputPath);
	        OfficeManager officeManager = new DefaultOfficeManagerConfiguration()
		    .setOfficeHome("C:\\Program Files (x86)\\OpenOffice 4").buildOfficeManager();
	        //OfficeManager officeManager = new DefaultOfficeManagerConfiguration().buildOfficeManager();
	        officeManager.start(); // may tweak the start and stop code to appear elsewhere for additional efficiency
	        
	        OfficeDocumentConverter pdfConverter = new OfficeDocumentConverter(officeManager);
	        pdfConverter.convert(inputFile, outputFile);
	        System.out.println("converting success!");
	        officeManager.stop(); 
	    } catch (Throwable e) {         
	        e.printStackTrace();    
	    }
	    return true;
	}	
}  