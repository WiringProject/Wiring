/* -*- mode: jde; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
  Target - represents a hardware platform
  Part of the Arduino project - http://www.arduino.cc/

  Copyright (c) 2009 David A. Mellis

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
  
  $Id$
*/

package processing.app.debug;

import java.io.*;
import java.util.*;

import processing.app.Preferences;

public class Target {
  private String name;
  private File folder;
  private Map<String, Map<String, String>> boards;
  private Map<String, Map<String, String>> programmers;
  
  public Target(String name, File folder) {
    this.name = name;
    this.folder = folder;
    this.boards = new LinkedHashMap<String, Map<String, String>>();
    this.programmers = new LinkedHashMap<String, Map<String, String>>();
    
    File boardsFile = new File(folder, "boards.txt");
    try {
      if (boardsFile.exists()) {
        Map<String, String> boardPreferences =
          new LinkedHashMap<String, String>();
        Preferences.load(new FileInputStream(boardsFile), boardPreferences);
        for (String key : boardPreferences.keySet()) {
          String board = key.substring(0, key.indexOf('.'));
          if (!boards.containsKey(board))
            boards.put(board, new HashMap<String, String>());
          boards.get(board).put(key.substring(key.indexOf('.') + 1),
                                boardPreferences.get(key));
        }
      }
    } catch (Exception e) {
      System.err.println("Error loading boards from " + boardsFile + ": " + e);
    }

    File programmersFile = new File(folder, "programmers.txt");
    try {
      if (programmersFile.exists()) {
        Map<String, String> programmerPreferences =
          new LinkedHashMap<String, String>();
        Preferences.load(new FileInputStream(programmersFile), programmerPreferences);
        for (String key : programmerPreferences.keySet()) {
          String programmer = key.substring(0, key.indexOf('.'));
          if (!programmers.containsKey(programmer))
            programmers.put(programmer, new HashMap<String, String>());
          programmers.get(programmer).put(key.substring(key.indexOf('.') + 1),
                                          programmerPreferences.get(key));
        }
      }
    } catch (Exception e) {
      System.err.println("Error loading programmers from " + 
                         programmersFile + ": " + e);
    }    
  }
  
  public String getName() { return name; }
  public File getFolder() { return folder; }
  public Map<String, Map<String, String>> getBoards() {
    return boards;
  }
  public Map<String, Map<String, String>> getProgrammers() {
    return programmers;
  }
}