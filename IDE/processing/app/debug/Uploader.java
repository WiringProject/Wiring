/* -*- mode: jde; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
  Uploader - default downloader class that connects to uisp
  Part of the Wiring project - http://wiring.org.co

  Copyright (c) 2004-10
  Hernando Barragan

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

package processing.app.debug;
import processing.app.*;
import java.io.*;
import java.util.*;
import java.util.zip.*;
import javax.swing.*;
import gnu.io.*;


public abstract class Uploader implements MessageConsumer{
  static final String BUGS_URL =
    "http://wiring.org.co/bugs/";
  static final String SUPER_BADNESS =
    "Compiler error, please submit this code to " + BUGS_URL;

  RunnerException exception;
  Sketch sketch;
  //PdePreferences preferences;

  //Serial serialPort;
  static InputStream serialInput;
  static OutputStream serialOutput;
  //int serial; // last byte of data received


  boolean verbose;
  
  public Uploader() {
  }
  
  public abstract boolean uploadUsingPreferences(String buildPath, String className, boolean verbose)
  throws RunnerException;
  
  public abstract boolean burnBootloader(String target, String programmer) throws RunnerException;
  
  protected void flushSerialBuffer() throws RunnerException {
    // Cleanup the serial buffer
    try {
      Serial serialPort = new Serial();
      byte[] readBuffer;
      while(serialPort.available() > 0) {
        readBuffer = serialPort.readBytes();
        try {
          Thread.sleep(100);
        } catch (InterruptedException e) {}
      }
      serialPort.setDTR(false);
      serialPort.setRTS(false);
      
      try {
        Thread.sleep(100);
      } catch (InterruptedException e) {}
      
      serialPort.setDTR(true);
      serialPort.setRTS(true);
      serialPort.dispose();
    } catch(Exception e) {
      System.err.println(e.getMessage());
      //throw new RunnerException(e.getMessage());
    }
  }


  protected boolean executeUploadCommand(Collection commandDownloader) 
  throws RunnerException
  {
    try {
      Serial serialPort = new Serial();
      serialPort.dispose();
    }
    catch (Exception e) {
      //System.err.println(e.getMessage());
      return false;
    }
    firstErrorFound = false;  // haven't found any errors yet
    secondErrorFound = false;
    notFoundError = false;
    int result=0; // pre-initialized to quiet a bogus warning from jikes
    
    String userdir = System.getProperty("user.dir") + File.separator;
    
    try {
      String[] commandArray = new String[commandDownloader.size()];
      commandDownloader.toArray(commandArray);
      
      String avrBasePath;
      
      if(Base.isLinux()) {  
        //avrBasePath = new String(Base.getHardwarePath() + "/tools/");
        avrBasePath = new String(Base.getAvrBasePath());
      }
      else {
        avrBasePath = new String(Base.getAvrBasePath()); //String(Base.getHardwarePath() + "/tools/avr/bin/"); 
      }
      
      commandArray[0] = avrBasePath + commandArray[0];
      
      if (verbose || Preferences.getBoolean("upload.verbose")) {
        for(int i = 0; i < commandArray.length; i++) {
          System.out.print(commandArray[i] + " ");
        }
        System.out.println();
      }
      Process process = Runtime.getRuntime().exec(commandArray);
      new MessageSiphon(process.getInputStream(), this);
      new MessageSiphon(process.getErrorStream(), this);
      
      // wait for the process to finish.  if interrupted
      // before waitFor returns, continue waiting
      //
      boolean compiling = true;
      while (compiling) {
        try {
          result = process.waitFor();
          compiling = false;
        } catch (InterruptedException intExc) {
        }
      } 
      if(exception!=null) {
        exception.hideStackTrace();
        throw exception;   
      }
      if(result!=0)
        return false;
    } catch (Exception e) {
      String msg = e.getMessage();
      if ((msg != null) && (msg.indexOf("uisp: not found") != -1) && (msg.indexOf("avrdude: not found") != -1)) {
        //System.err.println("uisp is missing");
        //JOptionPane.showMessageDialog(editor.base,
        //                              "Could not find the compiler.\n" +
        //                              "uisp is missing from your PATH,\n" +
        //                              "see readme.txt for help.",
        //                              "Compiler error",
        //                              JOptionPane.ERROR_MESSAGE);
        return false;
      } else {
        e.printStackTrace();
        result = -1;
      }
    }
    //System.out.println("result2 is "+result);
    // if the result isn't a known, expected value it means that something
    // is fairly wrong, one possibility is that jikes has crashed.
    //
    if (exception != null) throw exception;
    
    if ((result != 0) && (result != 1 )) {
      exception = new RunnerException(SUPER_BADNESS);
      //editor.error(exception);
      //PdeBase.openURL(BUGS_URL);
      //throw new PdeException(SUPER_BADNESS);
    }
    
    return (result == 0); // ? true : false;      
    
  }

  
  /*
  public boolean upload() throws RunnerException {
    String userdir = System.getProperty("user.dir") + File.separator;
    if (Base.isMacOS()) {
      String javaroot = System.getProperty("javaroot");
      if (javaroot != null) {
        userdir = javaroot  + File.separator;
      }
    }

    protocol_version = Preferences.getInteger("firmware.version");

    
    String commandDownloaderUisp[] = new String[] {
    ((!Base.isMacOS() && !Base.isLinux()) ?  "tools/avr/bin/uisp" :
      userdir + "tools/avr/bin/uisp"),
    //[2] Serial port
    //[6] hex class file
     "-dprog=stk500",
     " ",
     "-dspeed=115200",
     "-dpart=" + Preferences.get("build.mcu"), //atmega128",
     "--upload",
     " "
    };
    
    String commandDownloaderAvrdude[] = new String[] {
    ((!Base.isMacOS() && !Base.isLinux()) ? "tools/avr/bin/avrdude" :
      userdir + "tools/avr/bin/avrdude"),
      "-cstk500v2",
      " ",
      "-b115200",
      "-p" + Preferences.get("upload.mcu"), //m128",
      "-D",
      "-q",
      "-F",
      "-u",
      " ",
      " "
    };
    
    String commandDownloader[];

  

    firstErrorFound = false;  // haven't found any errors yet
    secondErrorFound = false;
    notFoundError = false;
    int result=0; // pre-initialized to quiet a bogus warning from jikes
    try {

      serialPreferences();
      if(protocol_version == 1) {
        commandDownloader = commandDownloaderUisp;
      	commandDownloader[2] = ((Base.isWindows()) ? "-dserial=/dev/" + serial_port.toLowerCase() : "-dserial=" + serial_port );
      	commandDownloader[6] = "if=" + buildPath + File.separator + className + ".hex";
      } else {
        commandDownloader = commandDownloaderAvrdude;
        commandDownloader[2] = ((Base.isWindows()) ? "-P"+ serial_port.toLowerCase() : "-P" + serial_port );
        commandDownloader[9] = "-Uflash:w:" + buildPath + File.separator + className + ".hex:i";
        if(Base.isMacOS()) {
          commandDownloader[10] = "-C" + userdir + "tools/avr/bin/avrdude.conf";
        } else if(Base.isWindows()) {
          commandDownloader[10] = "-C" + "tools/avr/bin/avrdude.conf";
        } else {
          commandDownloader[10] = "-C" + "tools/avr/bin/avrdude.conf";
        }
      }*/
      /*
      for(int i = 0; i < commandDownloader.length; i++) {
	System.out.println(commandDownloader[i]);
      }
      */
/*
      // Cleanup the serial buffer
      // Cleanup the serial buffer
      try {
        Serial serialPort = new Serial();
        byte[] readBuffer;
        while(serialPort.available() > 0) {
          readBuffer = serialPort.readBytes();
          try {
            Thread.sleep(100);
          } catch (InterruptedException e) {}
        }
 */
         /*serialPort.setDTR(false);
         //serialPort.setRTS(false);
         
         try {
         Thread.sleep(100);
         } catch (InterruptedException e) {}
         
         serialPort.setDTR(true);
          */
         //serialPort.setRTS(true);
/*         serialPort.dispose();
      } catch(SerialException e) { 
        System.err.println(e.getMessage());
        return false;
        //throw new SerialException(e.getMessage());
      }
      
      Process process = Runtime.getRuntime().exec(commandDownloader);
      new MessageSiphon(process.getInputStream(), this);
      new MessageSiphon(process.getErrorStream(), this);

      // wait for the process to finish.  if interrupted
      // before waitFor returns, continue waiting
      //
      boolean compiling = true;
      while (compiling) {
        try {
          result = process.waitFor();
          compiling = false;
        } catch (InterruptedException intExc) {
        }
      } 
      if(exception!=null) {
        exception.hideStackTrace();
        throw exception;   
      }
      if(result!=0)
        return false;
    } catch (Exception e) {
      String msg = e.getMessage();
      if ((msg != null) && (msg.indexOf("uisp: not found") != -1)) {
        //System.err.println("uisp is missing");
        //JOptionPane.showMessageDialog(editor.base,
        //                              "Could not find the compiler.\n" +
        //                              "uisp is missing from your PATH,\n" +
        //                              "see readme.txt for help.",
        //                              "Compiler error",
        //                              JOptionPane.ERROR_MESSAGE);
        return false;
      } else {
        e.printStackTrace();
        result = -1;
      }
    }
    //System.out.println("result2 is "+result);
    // if the result isn't a known, expected value it means that something
    // is fairly wrong, one possibility is that jikes has crashed.
    //
    if (exception != null) throw exception;

    if ((result != 0) && (result != 1 )) {
      exception = new RunnerException(SUPER_BADNESS);
      //editor.error(exception);
      //PdeBase.openURL(BUGS_URL);
      //throw new PdeException(SUPER_BADNESS);
    }

    // re-open and close the Serial port to reset the board
    try {
      serialPort = new Serial();
//      serialPort.setDTR(false);

      try {
        Thread.sleep(100);
      } catch (InterruptedException e) {}

//      serialPort.setDTR(true);
    serialPort.dispose();
    } catch(SerialException e) {
      System.err.println(e.getMessage());
      return false;
      //throw new SerialException(e.getMessage());
    }
    return (result == 0); // ? true : false;      

  }
*/
  
  boolean firstErrorFound;
  boolean secondErrorFound;

  // part of the PdeMessageConsumer interface
  //
  boolean notFoundError;

  public void message(String s) {
    //System.err.println("MSG: " + s);
    System.err.print(s);

    // ignore cautions
    if (s.indexOf("Error") != -1) {
      //exception = new RunnerException(s+" Check the serial port selected or your Board is connected");
      //System.out.println(s);
      notFoundError = true;
      return;
    }
    if(notFoundError) {
      //System.out.println("throwing something");
      exception = new RunnerException("the selected serial port "+s+" does not exist or your board is not connected");
      return;
    }
    if (s.indexOf("Device is not responding") != -1 ) {
      exception =  new RunnerException("Device is not responding, check the right serial port is selected or RESET the board right before exporting");
      return;
    }
    if (s.indexOf("Programmer is not responding") != -1 ||
        s.indexOf("programmer is not responding") != -1 ||
        s.indexOf("protocol error") != -1) {
      exception = new RunnerException("Problem uploading to the Wiring hardware. RESET the board right before exporting or choose the right firmware version for your board in the Tools/Firmware version menu.");
      return;
    }
    if (s.indexOf("Expected signature") != -1) {
      exception = new RunnerException("Wrong microcontroller found.  Did you select the right board from the Tools > Board menu?");
      return;
    }    
  }


}
