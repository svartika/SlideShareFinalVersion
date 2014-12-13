package com.ateam;

import java.awt.Image;
import java.awt.image.RenderedImage;
import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Random;

import javax.imageio.ImageIO;

import org.ghost4j.document.PDFDocument;
import org.ghost4j.renderer.SimpleRenderer;

public class imageConverter {
	
	public imageConverter(){
		
	}	 
    public int convertPDF2Image(String pdf,String profFolder) {
       int random=-1;
       try {
    	 System.out.println("hey!");
         // load PDF document
         PDFDocument document = new PDFDocument();
         document.load(new File(pdf));
 
         // create renderer
         SimpleRenderer renderer = new SimpleRenderer();
 
         // set resolution (in DPI)
         renderer.setResolution(150);
 
         // render
         List<Image> images = renderer.render(document);
         Random rand = new Random();
         random=rand.nextInt(10000);
 
         // write images to files to disk as PNG
            try {
            	String path="C:\\Users\\AJOU\\Desktop\\eclipse-jee-luna-SR1-win32-x86_64\\workspace\\slideshare\\WebContent\\p"+random+"\\";
            	//String path="C:\\Users\\AJOU\\Desktop\\eclipse-jee-luna-SR1-win32-x86_64\\workspace\\slideshare\\WebContent\\p"+0+"\\";
            	File dir=new File(path);
            	if(!dir.exists()){
            		dir.mkdirs();
            	}else{
            		File[] destroy = dir.listFiles(); 
            		for(File des : destroy){
            		des.delete(); 
            		}	
            	}
                for (int i = 0; i < images.size(); i++) {
                    ImageIO.write((RenderedImage) images.get(i), "png", new File(path+i+ ".PNG"));
                    System.out.println((i+1)+".png is written.");
                }
            } catch (IOException e) {
                System.out.println("ERROR: " + e.getMessage());
            }
 
       } catch (Exception e) {
         System.out.println("ERROR: " + e.getMessage());
       }
       
       return random;
 
    }
}