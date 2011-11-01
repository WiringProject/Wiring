/* -*- mode: java; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
  Part of the Processing project - http://processing.org

  Copyright (c) 2004-10 Ben Fry and Casey Reas
  Copyright (c) 2001-04 Massachusetts Institute of Technology

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License version 2
  as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

package processing.app;

import processing.app.debug.*;
import processing.app.syntax.*;
import processing.app.tools.*;
import processing.core.*;

import java.awt.*;
import java.awt.datatransfer.*;
import java.awt.event.*;
import java.awt.print.*;
import java.io.*;
import java.lang.reflect.Method;
import java.net.*;
import java.util.*;
import java.util.zip.*;

import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.*;
import javax.swing.undo.*;

import java.util.regex.*;
import gnu.io.*;

/**
 * Main editor panel for the Processing Development Environment.
 */
public class Editor extends JFrame implements RunnerListener {

  final Base base;

  // otherwise, if the window is resized with the message label
  // set to blank, it's preferredSize() will be fukered
  static protected final String EMPTY =
    "                                                                     " +
    "                                                                     " +
    "                                                                     ";

  /**
   * true if this file has not yet been given a name by the user
   */
  boolean untitled;

  private PageFormat pageFormat;
  private PrinterJob printerJob;

  // file and sketch menus for re-inserting items
  private JMenu fileMenu;
  private JMenu sketchMenu;
  private JMenu helpMenu;
  private JMenu windowMenu;
  JMenu toolsMenu;

  int numTools = 0;

  final EditorToolbar toolbar;
  // these menus are shared so that they needn't be rebuilt for all windows
  // each time a sketch is created, renamed, or moved.
  static JMenu toolbarMenu;
  static JMenu sketchbookMenu;
  static JMenu examplesMenu;
  static JMenu importMenu;
  static JMenu boardsMenu;
  static JMenu serialMenu;
  static JMenu bootloaderMenu;

  static SerialMenuListener serialMenuListener;
  static SerialMonitor serialMonitor;

  Schematics schematics;

  EditorHeader header;
  EditorStatus status;
  EditorConsole console;

  Serial serialPort;

  private final JSplitPane splitPane;
  private final JPanel consolePanel;

  // currently opened program
  private Sketch sketch;

  private EditorLineStatus lineStatus;

  private JEditTextArea textarea;
  private EditorListener listener;

  // runtime information and window placement
  private Point sketchWindowLocation;
  private Runner runtime;

//  private JMenuItem exportAppItem;
  private JMenuItem saveMenuItem;
  private JMenuItem saveAsMenuItem;

  boolean hasSchematics = false;
  boolean running;
  //boolean presenting;
  boolean uploading;

  // undo fellers
  private JMenuItem undoItem, redoItem;
  protected UndoAction undoAction;
  protected RedoAction redoAction;
  private UndoManager undo;
  // used internally, and only briefly
  private CompoundEdit compoundEdit;

  private FindReplace find;

  private Runnable runHandler;
  private Runnable presentHandler;
  private Runnable stopHandler;
  private Runnable exportHandler;
  private Runnable exportAppHandler;
  private Runnable buildHandler;
  private Runnable buildAppHandler;

  private final Stack<Integer> caretUndoStack = new Stack<Integer>();
  private final Stack<Integer> caretRedoStack = new Stack<Integer>();

  public Editor(Base ibase, String path, int[] location) {
    super("Wiring");
    this.base = ibase;

    Base.setIcon(this);
    
    // Install default actions for Run, Present, etc.
    resetHandlers();


    // add listener to handle window close box hit event
    addWindowListener(new WindowAdapter() {
        public void windowClosing(WindowEvent e) {
          base.handleClose(Editor.this);
          base.rebuildWindowMenu(windowMenu);
        }
      });
    // don't close the window when clicked, the app will take care
    // of that via the handleQuitInternal() methods
    // http://dev.processing.org/bugs/show_bug.cgi?id=440
    setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);

    // When bringing a window to front, let the Base know
    addWindowListener(new WindowAdapter() {
        public void windowActivated(WindowEvent e) {
          //          EditorConsole.systemOut.println("editor window activated");
          base.handleActivated(Editor.this);
          // re-add the sub-menus that are shared by all windows
          fileMenu.insert(Base.recentMenu, 2);
          fileMenu.insert(Base.sketchbookMenu, 3);
          //fileMenu.insert(Base.examplesMenu, 3);
          sketchMenu.insert(Base.importMenu, 4);
          toolsMenu.insert(boardsMenu, numTools);
          toolsMenu.insert(serialMenu, numTools + 1);
          toolsMenu.insert(bootloaderMenu, numTools + 3);
          helpMenu.insert(Base.examplesMenu, 1);
        }

        // added for 1.0.5
        // http://dev.processing.org/bugs/show_bug.cgi?id=1260
        public void windowDeactivated(WindowEvent e) {
          //          EditorConsole.systemErr.println("editor window deactivated");
          fileMenu.remove(Base.recentMenu);
          fileMenu.remove(Base.sketchbookMenu);
          //fileMenu.remove(Base.examplesMenu);
          sketchMenu.remove(Base.importMenu);
          toolsMenu.remove(boardsMenu);
          toolsMenu.remove(serialMenu);
          toolsMenu.remove(bootloaderMenu);
          helpMenu.remove(Base.examplesMenu);
        }
      });

    if (serialMonitor == null)
      serialMonitor = new SerialMonitor(Preferences.get("serial.port"));
        
    buildMenuBar();

    // For rev 0120, placing things inside a JPanel
    Container contentPain = getContentPane();
    contentPain.setLayout(new BorderLayout());
    JPanel pain = new JPanel();
    pain.setLayout(new BorderLayout());
    contentPain.add(pain, BorderLayout.CENTER);

    Box box = Box.createVerticalBox();
    Box upper = Box.createVerticalBox();

    if (toolbarMenu == null) {
      toolbarMenu = new JMenu();
      base.rebuildToolbarMenu(toolbarMenu);
    }
    toolbar = new EditorToolbar(this, toolbarMenu);
    upper.add(toolbar);

    header = new EditorHeader(this);
    upper.add(header);

    textarea = new JEditTextArea(new PdeTextAreaDefaults());
    textarea.setRightClickPopup(new TextAreaPopup());
    textarea.setHorizontalOffset(6);

    // assemble console panel, consisting of status area and the console itself
    consolePanel = new JPanel();
    consolePanel.setLayout(new BorderLayout());

    status = new EditorStatus(this);
    consolePanel.add(status, BorderLayout.NORTH);

    console = new EditorConsole(this);
    // windows puts an ugly border on this guy
    console.setBorder(null);
    consolePanel.add(console, BorderLayout.CENTER);

    lineStatus = new EditorLineStatus(textarea);
    consolePanel.add(lineStatus, BorderLayout.SOUTH);

    upper.add(textarea);
    splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT,
                               upper, consolePanel);

    splitPane.setOneTouchExpandable(true);
    // repaint child panes while resizing
    splitPane.setContinuousLayout(true);
    // if window increases in size, give all of increase to
    // the textarea in the uppper pane
    splitPane.setResizeWeight(1D);

    // to fix ugliness.. normally macosx java 1.3 puts an
    // ugly white border around this object, so turn it off.
    splitPane.setBorder(null);

    // the default size on windows is too small and kinda ugly
    int dividerSize = Preferences.getInteger("editor.divider.size");
    if (dividerSize > 10) { //todo define 10 somewhere as constant?
      splitPane.setDividerSize(dividerSize);
    } else {
      splitPane.setDividerSize(10);
    }

    splitPane.setMinimumSize(new Dimension(600, 400));
    box.add(splitPane);

    // hopefully these are no longer needed w/ swing
    // (har har har.. that was wishful thinking)
    listener = new EditorListener(this, textarea);
    pain.add(box);

    // get shift down/up events so we can show the alt version of toolbar buttons
    textarea.addKeyListener(toolbar);
    
    pain.setTransferHandler(new FileDropHandler());
    
    // Finish preparing Editor (formerly found in Base)
    pack();
    
    // Set the window bounds and the divider location before setting it visible
    setPlacement(location);
    
    // If the window is resized too small this will resize it again to the
    // minimums. Adapted by Chris Lonnen from comments here:
    // http://bugs.sun.com/bugdatabase/view_bug.do?bug_id=4320050
    // as a fix for http://dev.processing.org/bugs/show_bug.cgi?id=25
    final int minW = Preferences.getInteger("editor.window.width.min");
    final int minH = Preferences.getInteger("editor.window.height.min");
    addComponentListener(new java.awt.event.ComponentAdapter() {
        public void componentResized(ComponentEvent event) {
          setSize((getWidth() < minW) ? minW : getWidth(),
                  (getHeight() < minH) ? minH : getHeight());
        }
      });
    
    // Bring back the general options for the editor
    applyPreferences();
    
    // Open the document that was passed in
    boolean loaded = handleOpenInternal(path);
    if (!loaded) {
      sketch = null;
    } else {
      //the sketch is now loaded, let's determine if we can show schematics
      String s = sketch.getFolder().getAbsolutePath() + File.separator + sketch.getName() + ".png";
      File file = new File(s);
      if(!file.exists()) {
        sketchMenu.getItem(2/*index of Schematic*/).setEnabled(false);
        toolbar.disable(EditorToolbar.SCHEMATICS);
      }
    }
    base.rebuildRecentMenu();
  }


  /**
   * Handles files dragged & dropped from the desktop and into the editor
   * window. Dragging files into the editor window is the same as using
   * "Sketch &rarr; Add File" for each file.
   */
  class FileDropHandler extends TransferHandler {
    public boolean canImport(JComponent dest, DataFlavor[] flavors) {
      return true;
    }
    
    @SuppressWarnings("unchecked")
    public boolean importData(JComponent src, Transferable transferable) {
      int successful = 0;
      
      try {
        DataFlavor uriListFlavor =
        new DataFlavor("text/uri-list;class=java.lang.String");
        
        if (transferable.isDataFlavorSupported(DataFlavor.javaFileListFlavor)) {
          java.util.List list = (java.util.List)
          transferable.getTransferData(DataFlavor.javaFileListFlavor);
          for (int i = 0; i < list.size(); i++) {
            File file = (File) list.get(i);
            if (sketch.addFile(file)) {
              successful++;
            }
          }
        } else if (transferable.isDataFlavorSupported(uriListFlavor)) {
          // Some platforms (Mac OS X and Linux, when this began) preferred
          // this method of moving files.
          String data = (String)transferable.getTransferData(uriListFlavor);
          String[] pieces = PApplet.splitTokens(data, "\r\n");
          for (int i = 0; i < pieces.length; i++) {
            if (pieces[i].startsWith("#")) continue;
            
            String path = null;
            if (pieces[i].startsWith("file:///")) {
              path = pieces[i].substring(7);
            } else if (pieces[i].startsWith("file:/")) {
              path = pieces[i].substring(5);
            }
            if (sketch.addFile(new File(path))) {
              successful++;
            }
          }
        }
      } catch (Exception e) {
        e.printStackTrace();
        return false;
      }
      
      if (successful == 0) {
        statusError("No files were added to the sketch.");
        
      } else if (successful == 1) {
        statusNotice("One file added to the sketch.");
        
      } else {
        statusNotice(successful + " files added to the sketch.");
      }
      return true;
    }
  }

  
  protected void setPlacement(int[] location) {
    setBounds(location[0], location[1], location[2], location[3]);
    if (location[4] != 0) {
      splitPane.setDividerLocation(location[4]);
    }
  }


  protected int[] getPlacement() {
    int[] location = new int[5];

    // Get the dimensions of the Frame
    Rectangle bounds = getBounds();
    location[0] = bounds.x;
    location[1] = bounds.y;
    location[2] = bounds.width;
    location[3] = bounds.height;

    // Get the current placement of the divider
    location[4] = splitPane.getDividerLocation();

    return location;
  }


  /**
   * Hack for #@#)$(* Mac OS X 10.2.
   * <p/>
   * This appears to only be required on OS X 10.2, and is not
   * even being called on later versions of OS X or Windows.
   */
//  public Dimension getMinimumSize() {
//    //System.out.println("getting minimum size");
//    return new Dimension(500, 550);
//  }



  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


  /**
   * Read and apply new values from the preferences, either because
   * the app is just starting up, or the user just finished messing
   * with things in the Preferences window.
   */
  protected void applyPreferences() {

    // apply the setting for 'use external editor'
    boolean external = Preferences.getBoolean("editor.external");

    textarea.setEditable(!external);
    saveMenuItem.setEnabled(!external);
    saveAsMenuItem.setEnabled(!external);

    TextAreaPainter painter = textarea.getPainter();
    if (external) {
      // disable line highlight and turn off the caret when disabling
      Color color = Theme.getColor("editor.external.bgcolor");
      painter.setBackground(color);
      painter.setLineHighlightEnabled(false);
      textarea.setCaretVisible(false);

      // new stuff
      splitPane.setDividerLocation(toolbar.getHeight() + header.getHeight());
      splitPane.setResizeWeight(0D);
      textarea.setMinimumSize(new Dimension(textarea.getWidth(), 0));
    } else {
      Color color = Theme.getColor("editor.bgcolor");
      painter.setBackground(color);
      boolean highlight = Preferences.getBoolean("editor.linehighlight");
      painter.setLineHighlightEnabled(highlight);
      textarea.setCaretVisible(true);

      // new stuff
      splitPane.setDividerLocation(-1); // any negative value resets to preferred size
      splitPane.setResizeWeight(1D);
      textarea.setMinimumSize(null);
    }

    // apply changes to the font size for the editor
    //TextAreaPainter painter = textarea.getPainter();
    painter.setFont(Preferences.getFont("editor.font"));
    //Font font = painter.getFont();
    //textarea.getPainter().setFont(new Font("Courier", Font.PLAIN, 36));

    // in case tab expansion stuff has changed
    listener.applyPreferences();

    // in case moved to a new location
    // For 0125, changing to async version (to be implemented later)
    //sketchbook.rebuildMenus();
    // For 0126, moved into Base, which will notify all editors.
    //base.rebuildMenusAsync();
  }


  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


  protected void buildMenuBar() {
    JMenuBar menubar = new JMenuBar();
    menubar = new JMenuBar();
    menubar.add(fileMenu = base.buildFileMenu(this));
    menubar.add(buildEditMenu());
    menubar.add(buildSketchMenu());
    menubar.add(buildToolsMenu());
    menubar.add(windowMenu = base.buildWindowMenu());
    windowMenu.addMenuListener(new MenuListener() {
      public void menuCanceled(MenuEvent e) {}
      public void menuDeselected(MenuEvent e) {}
      public void menuSelected(MenuEvent e) {
        base.rebuildWindowMenu(windowMenu);
      }
    });    
    menubar.add(buildHelpMenu());
    setJMenuBar(menubar);
  }

  
  public void setSaveItem(JMenuItem item) {
    saveMenuItem = item;
  }
  
  
  public void setSaveAsItem(JMenuItem item) {
    saveAsMenuItem = item;
  }
  

  protected JMenu buildSketchMenu() {
    JMenuItem item;
    sketchMenu = new JMenu("Sketch");

    item = Base.newJMenuItem("Verify / Compile", 'R');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          handleRun(false);
        }
      });
    sketchMenu.add(item);

    item = Base.newJMenuItem("Build", 'B');
    item.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        handleBuild(false);
      }
    });
    sketchMenu.add(item);
    
/*
    item = newJMenuItemShift("Present", 'R');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          handleRun(true);
        }
      });
    sketchMenu.add(item);
*/
    item = new JMenuItem("Schematics");
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          handleSchematics();
        }
      });
    sketchMenu.add(item);

    sketchMenu.addSeparator();

    if (Base.importMenu == null) {
      Base.importMenu = new JMenu("Import Library...");
      base.rebuildImportMenu();
    }
    sketchMenu.add(Base.importMenu);

    item = Base.newJMenuItem("Show Sketch Folder", 'K');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          Base.openFolder(sketch.getFolder());
        }
      });
    sketchMenu.add(item);
    item.setEnabled(Base.openFolderAvailable());

    item = new JMenuItem("Add File...");
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          sketch.handleAddFile();
        }
      });
    sketchMenu.add(item);

    return sketchMenu;
  }


  protected JMenu buildToolsMenu() {
    toolsMenu = new JMenu("Tools");
    JMenu menu = toolsMenu;
    JMenuItem item;

    addInternalTools(menu);

    item = Base.newJMenuItemShift("Serial Monitor", 'M');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          handleSerial();
        }
      });
    menu.add(item);

    addTools(menu, Base.getToolsFolder());
    File sketchbookTools = new File(Base.getSketchbookFolder(), "tools");
    addTools(menu, sketchbookTools);

    menu.addSeparator();
    
    numTools = menu.getItemCount();
    if (boardsMenu == null) {
      boardsMenu = new JMenu("Board");
    }
    base.rebuildBoardsMenu(boardsMenu);
    //}
    menu.add(boardsMenu);
    
    if (serialMenuListener == null)
      serialMenuListener  = new SerialMenuListener();
    if (serialMenu == null)
      serialMenu = new JMenu("Serial Port");
    populateSerialMenu();
    menu.add(serialMenu);
	  
    menu.addSeparator();

    if (bootloaderMenu == null) {
      bootloaderMenu = new JMenu("Burn Bootloader");
    }
    base.rebuildBurnBootloaderMenu(bootloaderMenu);
    menu.add(bootloaderMenu);
        
    menu.addMenuListener(new MenuListener() {
      public void menuCanceled(MenuEvent e) {}
      public void menuDeselected(MenuEvent e) {}
      public void menuSelected(MenuEvent e) {
        //System.out.println("Tools menu selected.");
        populateSerialMenu();
        base.rebuildBoardsMenu(boardsMenu);
        base.rebuildBurnBootloaderMenu(bootloaderMenu);
      }
    });

    return menu;
  }


  protected void addTools(JMenu menu, File sourceFolder) {
    HashMap<String, JMenuItem> toolItems = new HashMap<String, JMenuItem>();

    File[] folders = sourceFolder.listFiles(new FileFilter() {
      public boolean accept(File folder) {
        if (folder.isDirectory()) {
          //System.out.println("checking " + folder);
          File subfolder = new File(folder, "tool");
          return subfolder.exists();
        }
        return false;
      }
    });

    if (folders == null || folders.length == 0) {
      return;
    }

    for (int i = 0; i < folders.length; i++) {
      File toolDirectory = new File(folders[i], "tool");

      try {
        // add dir to classpath for .classes
        //urlList.add(toolDirectory.toURL());

        // add .jar files to classpath
        File[] archives = toolDirectory.listFiles(new FilenameFilter() {
          public boolean accept(File dir, String name) {
            return (name.toLowerCase().endsWith(".jar") ||
                    name.toLowerCase().endsWith(".zip"));
          }
        });

        URL[] urlList = new URL[archives.length];
        for (int j = 0; j < urlList.length; j++) {
          urlList[j] = archives[j].toURI().toURL();
        }
        URLClassLoader loader = new URLClassLoader(urlList);

        String className = null;
        for (int j = 0; j < archives.length; j++) {
          className = findClassInZipFile(folders[i].getName(), archives[j]);
          if (className != null) break;
        }

        /*
        // Alternatively, could use manifest files with special attributes:
        // http://java.sun.com/j2se/1.3/docs/guide/jar/jar.html
        // Example code for loading from a manifest file:
        // http://forums.sun.com/thread.jspa?messageID=3791501
        File infoFile = new File(toolDirectory, "tool.txt");
        if (!infoFile.exists()) continue;

        String[] info = PApplet.loadStrings(infoFile);
        //Main-Class: org.poo.shoe.AwesomerTool
        //String className = folders[i].getName();
        String className = null;
        for (int k = 0; k < info.length; k++) {
          if (info[k].startsWith(";")) continue;

          String[] pieces = PApplet.splitTokens(info[k], ": ");
          if (pieces.length == 2) {
            if (pieces[0].equals("Main-Class")) {
              className = pieces[1];
            }
          }
        }
        */
        // If no class name found, just move on.
        if (className == null) continue;

        Class<?> toolClass = Class.forName(className, true, loader);
        final Tool tool = (Tool) toolClass.newInstance();

        tool.init(Editor.this);

        String title = tool.getMenuTitle();
        JMenuItem item = new JMenuItem(title);
        item.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            SwingUtilities.invokeLater(tool);
          }
        });
        //menu.add(item);
        toolItems.put(title, item);

      } catch (Exception e) {
        e.printStackTrace();
      }
    }
    ArrayList<String> toolList = new ArrayList<String>(toolItems.keySet());
    if (toolList.size() == 0) return;

    menu.addSeparator();
    Collections.sort(toolList);
    for (String title : toolList) {
      menu.add((JMenuItem) toolItems.get(title));
    }
  }


  protected String findClassInZipFile(String base, File file) {
    // Class file to search for
    String classFileName = "/" + base + ".class";

    try {
      ZipFile zipFile = new ZipFile(file);
      Enumeration<?> entries = zipFile.entries();
      while (entries.hasMoreElements()) {
        ZipEntry entry = (ZipEntry) entries.nextElement();

        if (!entry.isDirectory()) {
          String name = entry.getName();
          //System.out.println("entry: " + name);

          if (name.endsWith(classFileName)) {
            //int slash = name.lastIndexOf('/');
            //String packageName = (slash == -1) ? "" : name.substring(0, slash);
            // Remove .class and convert slashes to periods.
            return name.substring(0, name.length() - 6).replace('/', '.');
          }
        }
      }
    } catch (IOException e) {
      //System.err.println("Ignoring " + filename + " (" + e.getMessage() + ")");
      e.printStackTrace();
    }
    return null;
  }


  protected JMenuItem createToolMenuItem(String className) {
    try {
      Class<?> toolClass = Class.forName(className);
      final Tool tool = (Tool) toolClass.newInstance();

      JMenuItem item = new JMenuItem(tool.getMenuTitle());
      
      tool.init(Editor.this);

      item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          SwingUtilities.invokeLater(tool);
        }
      });
      return item;
      
    } catch (Exception e) {
      e.printStackTrace();
      return null;
    }
  }
  
  
  protected JMenu addInternalTools(JMenu menu) {
    JMenuItem item;

    item = createToolMenuItem("processing.app.tools.AutoFormatTool");
    int modifiers = Toolkit.getDefaultToolkit().getMenuShortcutKeyMask();
    item.setAccelerator(KeyStroke.getKeyStroke('T', modifiers));
    menu.add(item);

//    menu.add(createToolMenuItem("processing.app.tools.CreateFont"));
//    menu.add(createToolMenuItem("processing.app.tools.ColorSelector"));
    menu.add(createToolMenuItem("processing.app.tools.Archiver"));
    menu.add(createToolMenuItem("processing.app.tools.FixEncoding"));
    //menu.add(buildHardwareMenu());
    //menu.add(buildFirmwareMenu());
    //menu.add(buildSerialMenu());
    /* menu.addMenuListener(
      new MenuListener() {
        public void menuCanceled(MenuEvent e) {}
        public void menuDeselected(MenuEvent e) {}
        public void menuSelected(MenuEvent e) {
          // build an updated serial menu
          buildSerialMenu();
        }
      }
    );
    */
    return menu;
  }


  class SerialMenuListener implements ActionListener {
    //public SerialMenuListener() { }

    public void actionPerformed(ActionEvent e) {
      if(serialMenu == null) {
        System.out.println("serialMenu is null");
        return;
      }
      int count = serialMenu.getItemCount();
      for (int i = 0; i < count; i++) {
        ((JCheckBoxMenuItem)serialMenu.getItem(i)).setState(false);
      }
      JCheckBoxMenuItem item = (JCheckBoxMenuItem)e.getSource();
      item.setState(true);
      String name = item.getText();
      //System.out.println(item.getLabel());
      Preferences.set("serial.port", name);
      serialMonitor.closeSerialPort();
      serialMonitor.setVisible(false);
      toolbar.deactivate(EditorToolbar.SERIAL);
      serialMonitor = new SerialMonitor(Preferences.get("serial.port"));
      base.onBoardOrPortChange();
      //System.out.println("set to " + get("serial.port"));
    }

    /*
    public void actionPerformed(ActionEvent e) {
      System.out.println(e.getSource());
      String name = e.getActionCommand();
      PdeBase.properties.put("serial.port", name);
      System.out.println("set to " + get("serial.port"));
      //editor.skOpen(path + File.separator + name, name);
      // need to push "serial.port" into PdeBase.properties
    }
    */
  }
  

  protected void populateSerialMenu() {
    // getting list of ports

    JMenuItem rbMenuItem;
    
    //System.out.println("Clearing serial port menu.");
	
    serialMenu.removeAll();
    boolean empty = true;

    try
    {
      for (Enumeration enumeration = CommPortIdentifier.getPortIdentifiers(); enumeration.hasMoreElements();)
      {
        CommPortIdentifier commportidentifier = (CommPortIdentifier)enumeration.nextElement();
        //System.out.println("Found communication port: " + commportidentifier);
        if (commportidentifier.getPortType() == CommPortIdentifier.PORT_SERIAL)
        {
          //System.out.println("Adding port to serial port menu: " + commportidentifier);
          String curr_port = commportidentifier.getName();
          rbMenuItem = new JCheckBoxMenuItem(curr_port, curr_port.equals(Preferences.get("serial.port")));
          rbMenuItem.addActionListener(serialMenuListener);
          //serialGroup.add(rbMenuItem);
          serialMenu.add(rbMenuItem);
          empty = false;
        }
      }
      if (!empty) {
        //System.out.println("enabling the serialMenu");
        serialMenu.setEnabled(true);
      }

    }

    catch (Exception exception)
    {
      System.out.println("error retrieving port list");
      exception.printStackTrace();
    }
	
    if (serialMenu.getItemCount() == 0) {
      serialMenu.setEnabled(false);
    }

    //serialMenu.addSeparator();
    //serialMenu.add(item);
  }


  protected JMenu buildSerialMenu() {
    // get list of names for serial ports
    // have the default port checked (if present)
    SerialMenuListener listener = new SerialMenuListener();
    String defaultName = Preferences.get("serial.port");
    boolean problem = false;
    if(null == serialMenu){
      serialMenu = new JMenu("Serial Port");
    }else{
      serialMenu.removeAll();
    }

    // if this is failing, it may be because
    // lib/javax.comm.properties is missing.
    // java is weird about how it searches for java.comm.properties
    // so it tends to be very fragile. i.e. quotes in the CLASSPATH
    // environment variable will hose things.
    try {
      //System.out.println("building port list");
      for( Enumeration portList = CommPortIdentifier.getPortIdentifiers(); portList.hasMoreElements();)
      {
        CommPortIdentifier portId =
          (CommPortIdentifier) portList.nextElement();
        //System.out.println(portId);

        if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
          //if (portId.getName().equals(port)) {
          String name = portId.getName();
          JCheckBoxMenuItem mi =
            new JCheckBoxMenuItem(name, name.equals(defaultName));
          mi.addActionListener(listener);
          //mi.addItemListener(listener);
          serialMenu.add(mi);
        }
      }
    } catch (UnsatisfiedLinkError e) {
      e.printStackTrace();
      problem = true;
    } catch (Exception e) {
      System.out.println("Exception building serial menu");
      e.printStackTrace();
    }

    if (serialMenu.getItemCount() == 0) {
      //System.out.println("dimming serial menu");
      serialMenu.setEnabled(false);
    }
    return serialMenu;
  }


/*
  protected JMenu buildHardwareMenu() {
    HardwareMenuListener listener = new HardwareMenuListener();
    String defaultMicrocontroller = Preferences.get("build.mcu");
    if(null == hardwareMenu) {
      hardwareMenu = new JMenu("Target microcontroller");
    } else {
      hardwareMenu.removeAll();
    }
    JCheckBoxMenuItem mi =
      new JCheckBoxMenuItem("atmega128", defaultMicrocontroller.equals("atmega128"));
    mi.addActionListener(listener);
    hardwareMenu.add(mi);
    mi = new JCheckBoxMenuItem("atmega1281", defaultMicrocontroller.equals("atmega1281"));
    mi.addActionListener(listener);
    hardwareMenu.add(mi);
    mi = new JCheckBoxMenuItem("atmega2561", defaultMicrocontroller.equals("atmega2561"));
    mi.addActionListener(listener);
    hardwareMenu.add(mi);
    return hardwareMenu;
  }


  class HardwareMenuListener implements ActionListener {
    public void actionPerformed(ActionEvent e) {
      if(hardwareMenu == null) {
        System.out.println("hardwareMenu is null");
        return;
      }
      int count = hardwareMenu.getItemCount();
      for(int i = 0; i < count; i++) {
        ((JCheckBoxMenuItem)hardwareMenu.getItem(i)).setState(false);
      }
      JCheckBoxMenuItem item = (JCheckBoxMenuItem)e.getSource();
      item.setState(true);
      String name = item.getText();
      if(name.equals("atmega128")) {
		    Preferences.set("board", "Wiring");
        Preferences.set("build.mcu", "atmega128");
        Preferences.set("upload.mcu", "m128");
      } else if(name.equals("atmega1281")) {
		    Preferences.set("board", "Wiring");
        Preferences.set("build.mcu", "atmega1281");
        Preferences.set("upload.mcu", "m1281");
      } else if(name.equals("atmega2561")) {
        Preferences.set("board", "Wiring");
        Preferences.set("build.mcu", "atmega2561");
        Preferences.set("upload.mcu", "m2561");
      }
      //statusNotice("Rebuilding libraries for target "+ Preferences.get("build.mcu"));
      //rebuildLibraries();
      
    }
  }


  protected JMenu buildFirmwareMenu() {
    FirmwareMenuListener listener = new FirmwareMenuListener();
    int defaultVersion = Preferences.getInteger("firmware.version");
    if(null == firmwareMenu) {
      firmwareMenu = new JMenu("Firmware version");
    } else {
      firmwareMenu.removeAll();
    }
    JCheckBoxMenuItem mi =
      new JCheckBoxMenuItem("1.x", 1 == defaultVersion);
    mi.addActionListener(listener);
    firmwareMenu.add(mi);
    mi = new JCheckBoxMenuItem("2.x", 2 == defaultVersion);
    mi.addActionListener(listener);
    firmwareMenu.add(mi);
    return firmwareMenu;
  }


  class FirmwareMenuListener implements ActionListener {
    public void actionPerformed(ActionEvent e) {
      if(firmwareMenu == null) {
        System.out.println("firmwareMenu is null");
        return;
      }
      int count = firmwareMenu.getItemCount();
      for(int i = 0; i < count; i++) {
        ((JCheckBoxMenuItem)firmwareMenu.getItem(i)).setState(false);
      }
      JCheckBoxMenuItem item = (JCheckBoxMenuItem)e.getSource();
      item.setState(true);
      String name = item.getText();
      if(name.equals("1.x")) {
        Preferences.setInteger("firmware.version", 1);
      } else if(name.equals("2.x")) {
        Preferences.setInteger("firmware.version", 2);
      }
    }
  }
*/


  protected JMenu buildHelpMenu() {
    // To deal with a Mac OS X 10.5 bug, add an extra space after the name  
    // so that the OS doesn't try to insert its slow help menu.
    // 
    //JMenu menu = new JMenu("Help ");
    helpMenu = new JMenu("Help ");
    JMenuItem item;

    /*
    // testing internal web server to serve up docs from a zip file
    item = new JMenuItem("Web Server Test");
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          //WebServer ws = new WebServer();
          SwingUtilities.invokeLater(new Runnable() {
            public void run() {
              try {
                int port = WebServer.launch("/Users/fry/coconut/processing/build/shared/reference.zip");
                Base.openURL("http://127.0.0.1:" + port + "/reference/setup_.html");

              } catch (IOException e1) {
                e1.printStackTrace();
              }
            }
          });
        }
      });
    menu.add(item);
    */

    /*
    item = new JMenuItem("Browser Test");
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          //Base.openURL("http://processing.org/learning/gettingstarted/");
          //JFrame browserFrame = new JFrame("Browser");
          BrowserStartup bs = new BrowserStartup("jar:file:/Users/fry/coconut/processing/build/shared/reference.zip!/reference/setup_.html");
          bs.initUI();
          bs.launch();
        }
      });
    menu.add(item);
    */

    item = new JMenuItem("Getting started");
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          Base.showGettingStarted();
        }
      });
    helpMenu.add(item);
    
    if (Base.examplesMenu == null) {
      Base.examplesMenu = new JMenu("Examples");
      base.rebuildExamplesMenu();
    }
    helpMenu.add(Base.examplesMenu);

    item = new JMenuItem("Environment");
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          Base.showEnvironment();
        }
      });
    helpMenu.add(item);
    
    item = new JMenuItem("Reference");
    item.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        Base.showReference();
      }
    });
    helpMenu.add(item);
    
    item = Base.newJMenuItemShift("Find in Reference", 'F');
    item.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        if (textarea.isSelectionActive()) {
          handleFindReference();
        }
      }
    });
    helpMenu.add(item);

    item = new JMenuItem("Wiring Hardware");
    item.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        Base.showHardware();
      }
    });
    helpMenu.add(item);
    
    item = new JMenuItem("Frequently Asked Questions");
    item.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        Base.showFAQ();
      }
    });
    helpMenu.add(item);
    
    item = new JMenuItem("Troubleshooting");
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          Base.showTroubleshooting();
        }
      });
    helpMenu.add(item);

    item = Base.newJMenuItem("Visit wiring.org.co", '5');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          Base.openURL("http://wiring.org.co/");
        }
      });
    helpMenu.add(item);

    // macosx already has its own about menu
    if (!Base.isMacOS()) {
      helpMenu.addSeparator();
      item = new JMenuItem("About Wiring");
      item.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            base.handleAbout();
          }
        });
      helpMenu.add(item);
    }

    return helpMenu;
  }


  protected JMenu buildEditMenu() {
    JMenu menu = new JMenu("Edit");
    JMenuItem item;

    undoItem = Base.newJMenuItem("Undo", 'Z');
    undoItem.addActionListener(undoAction = new UndoAction());
    menu.add(undoItem);

    // Gotta follow them interface guidelines
    // http://code.google.com/p/processing/issues/detail?id=363
    if (Base.isWindows()) {
      redoItem = Base.newJMenuItem("Redo", 'Y');
    } else {  // Linux and OS X
      redoItem = Base.newJMenuItemShift("Redo", 'Z');
    }
    redoItem.addActionListener(redoAction = new RedoAction());
    menu.add(redoItem);

    menu.addSeparator();

    // TODO "cut" and "copy" should really only be enabled
    // if some text is currently selected
    item = Base.newJMenuItem("Cut", 'X');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          handleCut();
        }
      });
    menu.add(item);

    item = Base.newJMenuItem("Copy", 'C');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          textarea.copy();
        }
      });
    menu.add(item);

    item = Base.newJMenuItemShift("Copy as HTML", 'C');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          handleCopyAsHTML();
        }
      });
    menu.add(item);

    item = Base.newJMenuItem("Paste", 'V');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          textarea.paste();
          sketch.setModified(true);
        }
      });
    menu.add(item);

    item = Base.newJMenuItem("Select All", 'A');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          textarea.selectAll();
        }
      });
    menu.add(item);

    menu.addSeparator();

    item = Base.newJMenuItem("Comment/Uncomment", '/');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          handleCommentUncomment();
        }
    });
    menu.add(item);

    item = Base.newJMenuItem("Increase Indent", ']');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          handleIndentOutdent(true);
        }
    });
    menu.add(item);

    item = Base.newJMenuItem("Decrease Indent", '[');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          handleIndentOutdent(false);
        }
    });
    menu.add(item);

    menu.addSeparator();

    item = Base.newJMenuItem("Find...", 'F');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          if (find == null) {
            find = new FindReplace(Editor.this);
          }
          //new FindReplace(Editor.this).show();
          find.setVisible(true);
          //find.setVisible(true);
        }
      });
    menu.add(item);

    // TODO find next should only be enabled after a
    // search has actually taken place
    item = Base.newJMenuItem("Find Next", 'G');
    item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          if (find != null) {
            //find.find(true);
            //FindReplace find = new FindReplace(Editor.this); //.show();
            find.find(true);
          }
        }
      });
    menu.add(item);

    return menu;
  }


  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


  class UndoAction extends AbstractAction {
    public UndoAction() {
      super("Undo");
      this.setEnabled(false);
    }

    public void actionPerformed(ActionEvent e) {
      try {
        final Integer caret = caretUndoStack.pop();
        caretRedoStack.push(caret);
        textarea.setCaretPosition(caret);
        textarea.scrollToCaret();
      } catch (Exception ignore) {
      }
      try {
        undo.undo();
        //sketch.setModified(true);
      } catch (CannotUndoException ex) {
        //System.out.println("Unable to undo: " + ex);
        //ex.printStackTrace();
      }
      updateUndoState();
      redoAction.updateRedoState();
      if (sketch != null) {
        sketch.setModified(!getText().equals(sketch.getCurrentCode().getSavedProgram()));
      }      
    }

    protected void updateUndoState() {
      if (undo.canUndo()) {
        this.setEnabled(true);
        undoItem.setEnabled(true);
        undoItem.setText(undo.getUndoPresentationName());
        putValue(Action.NAME, undo.getUndoPresentationName());
//        if (sketch != null) {
//          sketch.setModified(true);  // 0107
//        }
      } else {
        this.setEnabled(false);
        undoItem.setEnabled(false);
        undoItem.setText("Undo");
        putValue(Action.NAME, "Undo");
//        if (sketch != null) {
//          sketch.setModified(false);  // 0107
//        }
      }
    }
  }


  class RedoAction extends AbstractAction {
    public RedoAction() {
      super("Redo");
      this.setEnabled(false);
    }

    public void actionPerformed(ActionEvent e) {
      try {
        undo.redo();
        //sketch.setModified(true);
      } catch (CannotRedoException ex) {
        //System.out.println("Unable to redo: " + ex);
        //ex.printStackTrace();
      }
      try {
        final Integer caret = caretRedoStack.pop();
        caretUndoStack.push(caret);
        textarea.setCaretPosition(caret);
      } catch (Exception ignore) {
      }
      updateRedoState();
      undoAction.updateUndoState();
      if (sketch != null) {
        sketch.setModified(!getText().equals(sketch.getCurrentCode().getSavedProgram()));
      }
    }

    protected void updateRedoState() {
      if (undo.canRedo()) {
        redoItem.setEnabled(true);
        redoItem.setText(undo.getRedoPresentationName());
        putValue(Action.NAME, undo.getRedoPresentationName());
      } else {
        this.setEnabled(false);
        redoItem.setEnabled(false);
        redoItem.setText("Redo");
        putValue(Action.NAME, "Redo");
      }
    }
  }

  
  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
  
  
  // these will be done in a more generic way soon, more like:
  // setHandler("action name", Runnable);
  // but for the time being, working out the kinks of how many things to
  // abstract from the editor in this fashion.
  
  
  public void setHandlers(Runnable runHandler, Runnable presentHandler,
                          Runnable stopHandler,
                          Runnable exportHandler, Runnable exportAppHandler,
                          Runnable buildHandler, Runnable buildAppHandler) {
    this.runHandler = runHandler;
    this.presentHandler = presentHandler;
    this.stopHandler = stopHandler;
    this.exportHandler = exportHandler;
    this.exportAppHandler = exportAppHandler;
    this.buildHandler = buildHandler;
    this.buildAppHandler = buildAppHandler;
  }
  
  
  public void resetHandlers() {
    runHandler = new DefaultRunHandler();
    presentHandler = new DefaultPresentHandler();
    stopHandler = new DefaultStopHandler();
    exportHandler = new DefaultExportHandler();
    exportAppHandler = new DefaultExportAppHandler();
    buildHandler = new DefaultBuildHandler();
    buildAppHandler = new DefaultBuildAppHandler();
  }
  
  
  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
  

  /**
   * Gets the current sketch object.
   */
  public Sketch getSketch() {
    return sketch;
  }


  /**
   * Get the JEditTextArea object for use (not recommended). This should only
   * be used in obscure cases that really need to hack the internals of the
   * JEditTextArea. Most tools should only interface via the get/set functions
   * found in this class. This will maintain compatibility with future releases,
   * which will not use JEditTextArea.
   */
  public JEditTextArea getTextArea() {
    return textarea;
  }


  /**
   * Get the contents of the current buffer. Used by the Sketch class.
   */
  public String getText() {
    return textarea.getText();
  }


  /**
   * Get a range of text from the current buffer.
   */
  public String getText(int start, int stop) {
    return textarea.getText(start, stop - start);
  }


  /**
   * Replace the entire contents of the front-most tab.
   */
  public void setText(String what) {
    startCompoundEdit();
    textarea.setText(what);
    stopCompoundEdit();
  }


  public void insertText(String what) {
    startCompoundEdit();
    int caret = getCaretOffset();
    setSelection(caret, caret);
    textarea.setSelectedText(what);
    stopCompoundEdit();
  }


  /**
   * Called to update the text but not switch to a different set of code
   * (which would affect the undo manager).
   */
//  public void setText2(String what, int start, int stop) {
//    beginCompoundEdit();
//    textarea.setText(what);
//    endCompoundEdit();
//
//    // make sure that a tool isn't asking for a bad location
//    start = Math.max(0, Math.min(start, textarea.getDocumentLength()));
//    stop = Math.max(0, Math.min(start, textarea.getDocumentLength()));
//    textarea.select(start, stop);
//
//    textarea.requestFocus();  // get the caret blinking
//  }


  public String getSelectedText() {
    return textarea.getSelectedText();
  }


  public void setSelectedText(String what) {
    textarea.setSelectedText(what);
  }


  public void setSelection(int start, int stop) {
    // make sure that a tool isn't asking for a bad location
    start = PApplet.constrain(start, 0, textarea.getDocumentLength());
    stop = PApplet.constrain(stop, 0, textarea.getDocumentLength());

    textarea.select(start, stop);
  }


  /**
   * Get the position (character offset) of the caret. With text selected,
   * this will be the last character actually selected, no matter the direction
   * of the selection. That is, if the user clicks and drags to select lines
   * 7 up to 4, then the caret position will be somewhere on line four.
   */
  public int getCaretOffset() {
    return textarea.getCaretPosition();
  }


  /**
   * True if some text is currently selected.
   */
  public boolean isSelectionActive() {
    return textarea.isSelectionActive();
  }


  /**
   * Get the beginning point of the current selection.
   */
  public int getSelectionStart() {
    return textarea.getSelectionStart();
  }


  /**
   * Get the end point of the current selection.
   */
  public int getSelectionStop() {
    return textarea.getSelectionStop();
  }


  /**
   * Get text for a specified line.
   */
  public String getLineText(int line) {
    return textarea.getLineText(line);
  }


  /**
   * Replace the text on a specified line.
   */
  public void setLineText(int line, String what) {
    startCompoundEdit();
    textarea.select(getLineStartOffset(line), getLineStopOffset(line));
    textarea.setSelectedText(what);
    stopCompoundEdit();
  }


  /**
   * Get character offset for the start of a given line of text.
   */
  public int getLineStartOffset(int line) {
    return textarea.getLineStartOffset(line);
  }


  /**
   * Get character offset for end of a given line of text.
   */
  public int getLineStopOffset(int line) {
    return textarea.getLineStopOffset(line);
  }


  /**
   * Get the number of lines in the currently displayed buffer.
   */
  public int getLineCount() {
    return textarea.getLineCount();
  }


  /**
   * Use before a manipulating text to group editing operations together as a
   * single undo. Use stopCompoundEdit() once finished.
   */
  public void startCompoundEdit() {
    compoundEdit = new CompoundEdit();
  }


  /**
   * Use with startCompoundEdit() to group edit operations in a single undo.
   */
  public void stopCompoundEdit() {
    compoundEdit.end();
    undo.addEdit(compoundEdit);
    undoAction.updateUndoState();
    redoAction.updateRedoState();
    compoundEdit = null;
  }


  public int getScrollPosition() {
    return textarea.getScrollPosition();
  }


  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


  /**
   * Switch between tabs, this swaps out the Document object
   * that's currently being manipulated.
   */
  protected void setCode(SketchCode code) {
    SyntaxDocument document = (SyntaxDocument) code.getDocument();

    if (document == null) {  // this document not yet inited
      document = new SyntaxDocument();
      code.setDocument(document);

      // turn on syntax highlighting
      document.setTokenMarker(new PdeKeywords());

      // insert the program text into the document object
      try {
        document.insertString(0, code.getProgram(), null);
      } catch (BadLocationException bl) {
        bl.printStackTrace();
      }

      // set up this guy's own undo manager
//      code.undo = new UndoManager();

      // connect the undo listener to the editor
      document.addUndoableEditListener(new UndoableEditListener() {
          public void undoableEditHappened(UndoableEditEvent e) {
            if (compoundEdit != null) {
              compoundEdit.addEdit(e.getEdit());

            } else if (undo != null) {
              caretUndoStack.push(textarea.getCaretPosition());
              caretRedoStack.clear();
              undo.addEdit(e.getEdit());
              undoAction.updateUndoState();
              redoAction.updateRedoState();
            }
          }
        });
    }

    // update the document object that's in use
    textarea.setDocument(document,
                         code.getSelectionStart(), code.getSelectionStop(),
                         code.getScrollPosition());

//    textarea.requestFocus();  // get the caret blinking
    textarea.requestFocusInWindow();  // required for caret blinking

    this.undo = code.getUndo();
    undoAction.updateUndoState();
    redoAction.updateRedoState();
  }


  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


  /**
   * Implements Edit &rarr; Cut.
   */
  public void handleCut() {
    textarea.cut();
    sketch.setModified(true);
  }


  /**
   * Implements Edit &rarr; Copy.
   */
  public void handleCopy() {
    textarea.copy();
  }


  public void handleCopyAsHTML() {
    textarea.copyAsHTML();
    statusNotice("Code formatted as HTML has been copied to the clipboard.");
  }
  

  /**
   * Implements Edit &rarr; Paste.
   */
  public void handlePaste() {
    textarea.paste();
    sketch.setModified(true);
  }


  /**
   * Implements Edit &rarr; Select All.
   */
  public void handleSelectAll() {
    textarea.selectAll();
  }


  protected void handleCommentUncomment() {
    startCompoundEdit();

    int startLine = textarea.getSelectionStartLine();
    int stopLine = textarea.getSelectionStopLine();

    int lastLineStart = textarea.getLineStartOffset(stopLine);
    int selectionStop = textarea.getSelectionStop();
    // If the selection ends at the beginning of the last line,
    // then don't (un)comment that line.
    if (selectionStop == lastLineStart) {
      // Though if there's no selection, don't do that
      if (textarea.isSelectionActive()) {
        stopLine--;
      }
    }

    // If the text is empty, ignore the user.
    // Also ensure that all lines are commented (not just the first)
    // when determining whether to comment or uncomment.
    int length = textarea.getDocumentLength();
    boolean commented = true;
    for (int i = startLine; commented && (i <= stopLine); i++) {
      int pos = textarea.getLineStartOffset(i);
      if (pos + 2 > length) {
        commented = false;
      } else {
        // Check the first two characters to see if it's already a comment.
        String begin = textarea.getText(pos, 2);
        //System.out.println("begin is '" + begin + "'");
        commented = begin.equals("//");
      }
    }

    for (int line = startLine; line <= stopLine; line++) {
      int location = textarea.getLineStartOffset(line);
      if (commented) {
        // remove a comment
        textarea.select(location, location+2);
        if (textarea.getSelectedText().equals("//")) {
          textarea.setSelectedText("");
        }
      } else {
        // add a comment
        textarea.select(location, location);
        textarea.setSelectedText("//");
      }
    }
    // Subtract one from the end, otherwise selects past the current line.
    // (Which causes subsequent calls to keep expanding the selection)
    textarea.select(textarea.getLineStartOffset(startLine),
                    textarea.getLineStopOffset(stopLine) - 1);
    stopCompoundEdit();
  }


  protected void handleIndentOutdent(boolean indent) {
    int tabSize = Preferences.getInteger("editor.tabs.size");
    String tabString = Editor.EMPTY.substring(0, tabSize);

    startCompoundEdit();

    int startLine = textarea.getSelectionStartLine();
    int stopLine = textarea.getSelectionStopLine();

    // If the selection ends at the beginning of the last line,
    // then don't (un)comment that line.
    int lastLineStart = textarea.getLineStartOffset(stopLine);
    int selectionStop = textarea.getSelectionStop();
    if (selectionStop == lastLineStart) {
      // Though if there's no selection, don't do that
      if (textarea.isSelectionActive()) {
        stopLine--;
      }
    }

    for (int line = startLine; line <= stopLine; line++) {
      int location = textarea.getLineStartOffset(line);

      if (indent) {
        textarea.select(location, location);
        textarea.setSelectedText(tabString);

      } else {  // outdent
//        System.out.println("location is "+location);
//        System.out.println("tabSize is "+tabSize);
//        System.out.println("location+tabsize is "+location+tabSize);
        int length = textarea.getDocumentLength();
        if (location+tabSize <= length)
          textarea.select(location, location + tabSize);
        else 
          textarea.select(location, length);
        // Don't eat code if it's not indented
        if (textarea.getSelectedText().equals(tabString)) {
          textarea.setSelectedText("");
        }
      }
    }
    // Subtract one from the end, otherwise selects past the current line.
    // (Which causes subsequent calls to keep expanding the selection)
    textarea.select(textarea.getLineStartOffset(startLine),
                    textarea.getLineStopOffset(stopLine) - 1);
    stopCompoundEdit();
  }


  protected void handleFindReference() {
    String text = textarea.getSelectedText().trim();

    if (text.length() == 0) {
      statusNotice("First select a word to find in the reference.");

    } else {
      String referenceFile = PdeKeywords.getReference(text);
      //System.out.println("reference file is " + referenceFile);
      if (referenceFile == null) {
        statusNotice("No reference available for \"" + text + "\"");
      } else {
        Base.showReference(referenceFile + ".html");
      }
    }
  }


  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


  /**
   * Implements Sketch &rarr; Run.
   * @param present Set true to run in full screen (present mode).
   */
  public void handleRun(final boolean verbose) {
    splitPane.setDividerLocation(splitPane.getLastDividerLocation());
    internalCloseRunner();
    running = true;
    toolbar.activate(EditorToolbar.RUN);
    statusEmpty();
    //statusNotice("Compiling...");
    status.progress("Compiling...");
    // do this to advance/clear the terminal window / dos prompt / etc
    for (int i = 0; i < 10; i++) System.out.println();

    // clear the console on each run, unless the user doesn't want to
    if (Preferences.getBoolean("console.auto_clear")) {
      console.clear();
    }

    //presenting = present;

    /*try {
      String appletClassName = sketch.compile(verbose);
      if (appletClassName != null) {
          statusNotice("Done compiling. No syntax errors found");
          handleStop();
      }
    } catch (Exception e) {
      //System.err.println("exception reached editor");
      //e.printStackTrace();
      statusNotice("Error compiling...");
      statusError(e);
      handleStop();
    }
	  toolbar.deactivate(EditorToolbar.RUN);
     */
    new Thread(verbose ? presentHandler : runHandler).start();
  }

  
  class DefaultRunHandler implements Runnable {
    public void run() {
      try {
        //sketch.compile(false);
        String appletClassName = sketch.compile(false);
        statusNotice("Done compiling.");
        if (appletClassName != null) {
          statusNotice("Done compiling. No syntax errors found");
          handleStop();
        }
      } catch (Exception e) {
        status.unprogress();
        statusNotice("Error compiling...");
        statusError(e);
        handleStop();
      }
      status.unprogress();
      toolbar.deactivate(EditorToolbar.RUN);
    }
  }

  
  class DefaultPresentHandler implements Runnable {
    public void run() {
      try {
        //sketch.compile(true);
        String appletClassName = sketch.compile(true);
        statusNotice("Done compiling.");
        if (appletClassName != null) {
          statusNotice("Done compiling. No syntax errors found");
          handleStop();
        }        
      } catch (Exception e) {
        status.unprogress();
        statusNotice("Error compiling...");
        statusError(e);
        handleStop();
      }
      status.unprogress();
      toolbar.deactivate(EditorToolbar.RUN);
    }
  }

  
  /**
   * Called by Sketch &rarr; Build.
   * Handles calling the build() function on sketch, and
   * queues all the gui status stuff that comes along with it.
   * <p/>
   * Made synchronized to (hopefully) avoid problems of people
   * hitting export twice, quickly, and horking things up.
   */
  synchronized public void handleBuild(final boolean verbose) {
    //if (!handleExportCheckModified()) return;
    toolbar.activate(EditorToolbar.RUN);
    console.clear();
    //statusNotice("Uploading to I/O Board...");
    status.progress("Building sketch...");
    new Thread(verbose ? buildAppHandler : buildHandler).start();
  }
  
  
  class DefaultBuildHandler implements Runnable {
    public void run() {
      
      try {
        serialMonitor.closeSerialPort();
        serialMonitor.setVisible(false);
        toolbar.deactivate(EditorToolbar.SERIAL);    
        uploading = true;
        
        boolean success = sketch.buildApplet(false);
        if (success) {
          statusNotice("Done Building.");
          uploading = false;
        } else {
          // error message will already be visible
        }
      } catch (RunnerException e) {
        //statusError("Error during upload.");
        //e.printStackTrace();
        status.unprogress();
        statusError(e);
      } catch (Exception e) {
        e.printStackTrace();
      }
      status.unprogress();
      uploading = false;
      //toolbar.clear();
      toolbar.deactivate(EditorToolbar.RUN);
    }
  }
  
  
  class DefaultBuildAppHandler implements Runnable {
    public void run() {
      
      try {
        serialMonitor.closeSerialPort();
        serialMonitor.setVisible(false);
        toolbar.deactivate(EditorToolbar.SERIAL);    
        uploading = true;
        
        boolean success = sketch.buildApplet(true);
        if (success) {
          statusNotice("Done Building.");
          uploading = false;
        } else {
          // error message will already be visible
        }
      } catch (RunnerException e) {
        //statusError("Error during upload.");
        //e.printStackTrace();
        status.unprogress();
        statusError(e);
      } catch (Exception e) {
        e.printStackTrace();
      }
      status.unprogress();
      uploading = false;
      //toolbar.clear();
      toolbar.deactivate(EditorToolbar.EXPORT);
    }
  }
  
  
  class DefaultStopHandler implements Runnable {
    public void run() {
      try {

      } catch (Exception e) {
        statusError(e);
      }
    }
  }
  

  /**
   * Set the location of the sketch run window. Used by Runner to update the
   * Editor about window drag events while the sketch is running.
   */
  public void setSketchLocation(Point p) {
    sketchWindowLocation = p;
  }


  /**
   * Get the last location of the sketch's run window. Used by Runner to make
   * the window show up in the same location as when it was last closed.
   */
  public Point getSketchLocation() {
    return sketchWindowLocation;
  }


  /**
   * Implements Sketch &rarr; Stop, or pressing Stop on the toolbar.
   */
  public void handleStop() {  // called by menu or buttons

    //toolbar.activate(EditorToolbar.STOP);

    internalCloseRunner();

    toolbar.deactivate(EditorToolbar.RUN);
    //toolbar.deactivate(EditorToolbar.STOP);
    toolbar.deactivate(EditorToolbar.SERIAL);

    // focus the PDE again after quitting presentation mode [toxi 030903]
    toFront();
  }
  
  
  /**
   * Deactivate the Run button. This is called by Runner to notify that the
   * sketch has stopped running, usually in response to an error (or maybe
   * the sketch completing and exiting?) Tools should not call this function.
   * To initiate a "stop" action, call handleStop() instead.
   */
  public void deactivateRun() {
    toolbar.deactivate(EditorToolbar.RUN);
  }
  

  public void handleSchematics() {
    String s = sketch.getFolder().getAbsolutePath() + File.separator + sketch.getName() + ".png";
    File file = new File(s);
    if(file.exists()) {
      hasSchematics = true;
    }
    if(hasSchematics) {
      //System.out.println(s);
      //System.out.println(sketch.getName());
      //System.out.println(folder.getAbsolutePath());
      //System.out.println(sketch.getMainFilePath());
      toolbar.activate(EditorToolbar.SCHEMATICS);
      if (schematics == null) schematics = new Schematics(s);
      schematics.showFrame(this);
    } else {
      sketchMenu.getItem(2/*index of Schematic*/).setEnabled(false);
      statusNotice("This sketch doesn't include schematics");
      toolbar.disable(EditorToolbar.SCHEMATICS);
    }
  }


  /**
   * Called by Runner to notify that the sketch has stopped running.
   * Tools should not call this function, use handleStop() instead.
   */
  public void internalRunnerClosed() {
    running = false;
    toolbar.deactivate(EditorToolbar.RUN);
  }


  /**
   * Handle internal shutdown of the runner.
   */
  public void internalCloseRunner() {
    running = false;
    
    if (stopHandler != null)
      try {
        stopHandler.run();
      } catch (Exception e) { }
    
    sketch.cleanup();
  }


  /**
   * Check if the sketch is modified and ask user to save changes.
   * Immediately should be set true when quitting, or when the save should
   * not happen asynchronously. Come to think of it, that's always now?
   * @return false if canceling the close/quit operation
   */
  protected boolean checkModified() {
    if (!sketch.isModified()) return true;
    
    // As of Processing 1.0.10, this always happens immediately.
    // http://dev.processing.org/bugs/show_bug.cgi?id=1456
    
    String prompt = "Save changes to " + sketch.getName() + "?  ";

    if (!Base.isMacOS()) {
      int result =
        JOptionPane.showConfirmDialog(this, prompt, "Close",
                                      JOptionPane.YES_NO_CANCEL_OPTION,
                                      JOptionPane.QUESTION_MESSAGE);

      if (result == JOptionPane.YES_OPTION) {
        return handleSave(true);

      } else if (result == JOptionPane.NO_OPTION) {
        return true;  // ok to continue

      } else if (result == JOptionPane.CANCEL_OPTION) {
        return false;
      } else {
        throw new IllegalStateException();
      }

    } else {
      // This code is disabled unless Java 1.5 is being used on Mac OS X
      // because of a Java bug that prevents the initial value of the
      // dialog from being set properly (at least on my MacBook Pro).
      // The bug causes the "Don't Save" option to be the highlighted,
      // blinking, default. This sucks. But I'll tell you what doesn't
      // suck--workarounds for the Mac and Apple's snobby attitude about it!
      // I think it's nifty that they treat their developers like dirt.

      // Pane formatting adapted from the quaqua guide
      // http://www.randelshofer.ch/quaqua/guide/joptionpane.html
      JOptionPane pane =
        new JOptionPane("<html> " +
                        "<head> <style type=\"text/css\">"+
                        "b { font: 13pt \"Lucida Grande\" }"+
                        "p { font: 11pt \"Lucida Grande\"; margin-top: 8px }"+
                        "</style> </head>" +
                        "<b>Do you want to save changes to this sketch<BR>" +
                        " before closing?</b>" +
                        "<p>If you don't save, your changes will be lost.",
                        JOptionPane.QUESTION_MESSAGE);

      String[] options = new String[] {
        "Save", "Cancel", "Don't Save"
      };
      pane.setOptions(options);

      // highlight the safest option ala apple hig
      pane.setInitialValue(options[0]);

      // on macosx, setting the destructive property places this option
      // away from the others at the lefthand side
      pane.putClientProperty("Quaqua.OptionPane.destructiveOption",
                             new Integer(2));

      JDialog dialog = pane.createDialog(this, null);
      dialog.setVisible(true);

      Object result = pane.getValue();
      if (result == options[0]) {  // save (and close/quit)
        return handleSave(true);

      } else if (result == options[2]) {  // don't save (still close/quit)
        return true;

      } else {  // cancel?
        return false;
      }
    }
  }


  /**
   * Open a sketch from a particular path, but don't check to save changes.
   * Used by Sketch.saveAs() to re-open a sketch after the "Save As"
   */
  protected void handleOpenUnchecked(String path, int codeIndex,
                                     int selStart, int selStop, int scrollPos) {
    internalCloseRunner();
    handleOpenInternal(path);
    // Replacing a document that may be untitled. If this is an actual
    // untitled document, then editor.untitled will be set by Base.
    untitled = false;

    sketch.setCurrentCode(codeIndex);
    textarea.select(selStart, selStop);
    textarea.setScrollPosition(scrollPos);
  }


  /**
   * Second stage of open, occurs after having checked to see if the
   * modifications (if any) to the previous sketch need to be saved.
   */
  protected boolean handleOpenInternal(String path) {
    // check to make sure that this .pde file is
    // in a folder of the same name
    File file = new File(path);
    File parentFile = new File(file.getParent());
    String parentName = parentFile.getName();
    String pdeName = parentName + ".pde";
    File altFile = new File(file.getParent(), pdeName);

    if (pdeName.equals(file.getName())) {
      // no beef with this guy

    } else if (altFile.exists()) {
      // user selected a .java from the same sketch,
      // but open the .pde instead
      path = altFile.getAbsolutePath();
      //System.out.println("found alt file in same folder");

    } else if (!path.endsWith(".pde")) {
      Base.showWarning("Bad file selected",
                       "Wiring can only open its own sketches\n" +
                       "and other files ending in .pde", null);
      return false;

    } else {
      String properParent =
        file.getName().substring(0, file.getName().length() - 4);

      Object[] options = { "OK", "Cancel" };
      String prompt =
        "The file \"" + file.getName() + "\" needs to be inside\n" +
        "a sketch folder named \"" + properParent + "\".\n" +
        "Create this folder, move the file, and continue?";

      int result = JOptionPane.showOptionDialog(this,
                                                prompt,
                                                "Moving",
                                                JOptionPane.YES_NO_OPTION,
                                                JOptionPane.QUESTION_MESSAGE,
                                                null,
                                                options,
                                                options[0]);

      if (result == JOptionPane.YES_OPTION) {
        // create properly named folder
        File properFolder = new File(file.getParent(), properParent);
        if (properFolder.exists()) {
          Base.showWarning("Error",
                           "A folder named \"" + properParent + "\" " +
                           "already exists. Can't open sketch.", null);
          return false;
        }
        if (!properFolder.mkdirs()) {
          //throw new IOException("Couldn't create sketch folder");
          Base.showWarning("Error",
                           "Could not create the sketch folder.", null);
          return false;
        }
        // copy the sketch inside
        File properPdeFile = new File(properFolder, file.getName());
        File origPdeFile = new File(path);
        try {
          Base.copyFile(origPdeFile, properPdeFile);
        } catch (IOException e) {
          Base.showWarning("Error", "Could not copy to a proper location.", e);
          return false;
        }

        // remove the original file, so user doesn't get confused
        origPdeFile.delete();

        // update with the new path
        path = properPdeFile.getAbsolutePath();

      } else if (result == JOptionPane.NO_OPTION) {
        return false;
      }
    }

    try {
      sketch = new Sketch(this, path);
    } catch (IOException e) {
      Base.showWarning("Error", "Could not create the sketch.", e);
      return false;
    }
    header.rebuild();
    // Set the title of the window to "sketch_070752a - Processing 0126"
    setTitle(sketch.getName() + " | Wiring " + Base.VERSION_NAME);
    // Disable untitled setting from previous document, if any
    untitled = false;

    // Store information on who's open and running
    // (in case there's a crash or something that can't be recovered)
    base.storeSketches();
    Preferences.save();

    // opening was successful
    return true;

//    } catch (Exception e) {
//      e.printStackTrace();
//      statusError(e);
//      return false;
//    }
  }


  /**
   * Actually handle the save command. If 'immediately' is set to false,
   * this will happen in another thread so that the message area
   * will update and the save button will stay highlighted while the
   * save is happening. If 'immediately' is true, then it will happen
   * immediately. This is used during a quit, because invokeLater()
   * won't run properly while a quit is happening. This fixes
   * <A HREF="http://dev.processing.org/bugs/show_bug.cgi?id=276">Bug 276</A>.
   */
  public boolean handleSave(boolean immediately) {
    //stopRunner();
    handleStop();  // 0136

    if (untitled) {
      return handleSaveAs();
      // need to get the name, user might also cancel here

    } else if (immediately) {
      handleSave2();

    } else {
      SwingUtilities.invokeLater(new Runnable() {
          public void run() {
            handleSave2();
          }
        });
    }
    return true;
  }


  protected void handleSave2() {
    toolbar.activate(EditorToolbar.SAVE);
    statusNotice("Saving...");
    try {
      if (sketch.save()) {
        statusNotice("Done Saving.");
      } else {
        statusEmpty();
      }
      // rebuild sketch menu in case a save-as was forced
      // Disabling this for 0125, instead rebuild the menu inside
      // the Save As method of the Sketch object, since that's the
      // only one who knows whether something was renamed.
      //sketchbook.rebuildMenus();
      //sketchbook.rebuildMenusAsync();

    } catch (Exception e) {
      // show the error as a message in the window
      statusError(e);

      // zero out the current action,
      // so that checkModified2 will just do nothing
      //checkModifiedMode = 0;
      // this is used when another operation calls a save
    }
    //toolbar.clear();
    toolbar.deactivate(EditorToolbar.SAVE);
  }


  public boolean handleSaveAs() {
    //stopRunner();  // formerly from 0135
    handleStop();

    toolbar.activate(EditorToolbar.SAVE);

    //SwingUtilities.invokeLater(new Runnable() {
    //public void run() {
    statusNotice("Saving...");
    try {
      if (sketch.saveAs()) {
        statusNotice("Done Saving.");
        // Disabling this for 0125, instead rebuild the menu inside
        // the Save As method of the Sketch object, since that's the
        // only one who knows whether something was renamed.
        //sketchbook.rebuildMenusAsync();
      } else {
        statusNotice("Save Canceled.");
        return false;
      }
    } catch (Exception e) {
      // show the error as a message in the window
      statusError(e);

    } finally {
      // make sure the toolbar button deactivates
      toolbar.deactivate(EditorToolbar.SAVE);
    }

    return true;
  }


  /**
   * Called by Sketch &rarr; Export.
   * Handles calling the export() function on sketch, and
   * queues all the gui status stuff that comes along with it.
   * <p/>
   * Made synchronized to (hopefully) avoid problems of people
   * hitting export twice, quickly, and horking things up.
   */
  synchronized public void handleExport(final boolean verbose) {
    //if (!handleExportCheckModified()) return;
    
    splitPane.setDividerLocation(splitPane.getLastDividerLocation());
    toolbar.activate(EditorToolbar.EXPORT);
    console.clear();
    //statusNotice("Uploading to I/O Board...");
    status.progress("Uploading to Wiring Hardware...");
    new Thread(verbose ? exportAppHandler : exportHandler).start();
  }

  
  class DefaultExportHandler implements Runnable {
    public void run() {

      try {
        serialMonitor.closeSerialPort();
        serialMonitor.setVisible(false);
        toolbar.deactivate(EditorToolbar.SERIAL);    
        uploading = true;
          
        boolean success = sketch.exportApplet(false);
        if (success) {
          statusNotice("Done Uploading.");
          uploading = false;
          if (Preferences.getBoolean("monitor.start")) {
            handleSerial();
            System.out.println("Serial monitor started after upload (Wiring -> Preferences)");
          }
        } else {
          // error message will already be visible
        }
      } catch (RunnerException e) {
        //statusError("Error during upload.");
        //e.printStackTrace();
        status.unprogress();
        statusError(e);
      } catch (Exception e) {
        e.printStackTrace();
      }
      status.unprogress();
      uploading = false;
      //toolbar.clear();
      toolbar.deactivate(EditorToolbar.EXPORT);
    }
  }

  
  class DefaultExportAppHandler implements Runnable {
    public void run() {

      try {
        serialMonitor.closeSerialPort();
        serialMonitor.setVisible(false);
        toolbar.deactivate(EditorToolbar.SERIAL);    
        uploading = true;
          
        boolean success = sketch.exportApplet(true);
        if (success) {
          statusNotice("Done Uploading.");
          uploading = false;
          if (Preferences.getBoolean("monitor.start")) {
            handleSerial();
            System.out.println("Serial monitor started after upload (Wiring -> Preferences)");
          }
        } else {
          // error message will already be visible
        }
      } catch (RunnerException e) {
        //statusError("Error during upload.");
        //e.printStackTrace();
        status.unprogress();
        statusError(e);
      } catch (Exception e) {
        e.printStackTrace();
      }
      status.unprogress();
      uploading = false;
      //toolbar.clear();
      toolbar.deactivate(EditorToolbar.EXPORT);
    }
  }

/*
  synchronized public void handleExport(final boolean verbose) {
    handleStop();
    if(debugging) return;
    //if (!handleExportCheckModified()) return;
    toolbar.activate(EditorToolbar.EXPORT);

    statusNotice("Uploading to I/O Board...");

    //SwingUtilities.invokeLater(new Runnable() {
    Thread t = new Thread(new Runnable() {
        public void run() {
          try {
            boolean success = sketch.exportApplet(verbose);
            if (success) {
//              File appletFolder = new File(sketch.getFolder(), "applet");
//              Base.openFolder(appletFolder);
              statusNotice("Done uploading. Reset to start the new program");
              if (Preferences.getBoolean("monitor.start")) {
                handleSerial();
                System.out.println("Serial monitor started after upload (Wiring -> Preferences)");
              }
            } else {
              // error message will already be visible
            }
          } catch (Exception e) {
            statusError(e);
          }
          //toolbar.clear();
          toolbar.deactivate(EditorToolbar.EXPORT);
        }});
    t.start();
  }
*/

  /**
   * Handler for Sketch &rarr; Export Application
   */
  synchronized public void handleExportApplication() {
    if (!handleExportCheckModified()) return;
    toolbar.activate(EditorToolbar.EXPORT);

    //SwingUtilities.invokeLater(new Runnable() {
    SwingUtilities.invokeLater(new Runnable() {
        public void run() {
          statusNotice("Exporting application...");
          try {
            if (sketch.exportApplicationPrompt()) {
              Base.openFolder(sketch.getFolder());
              statusNotice("Done exporting.");
            } else {
              // error message will already be visible
              // or there was no error, in which case it was canceled.
            }
          } catch (Exception e) {
            statusNotice("Error during export.");
            e.printStackTrace();
          }
          //toolbar.clear();
          toolbar.deactivate(EditorToolbar.EXPORT);
        }});
  }


  /**
   * Checks to see if the sketch has been modified, and if so,
   * asks the user to save the sketch or cancel the export.
   * This prevents issues where an incomplete version of the sketch
   * would be exported, and is a fix for
   * <A HREF="http://dev.processing.org/bugs/show_bug.cgi?id=157">Bug 157</A>
   */
  protected boolean handleExportCheckModified() {
    if (!sketch.isModified()) return true;

    Object[] options = { "OK", "Cancel" };
    int result = JOptionPane.showOptionDialog(this,
                                              "Save changes before export?",
                                              "Save",
                                              JOptionPane.OK_CANCEL_OPTION,
                                              JOptionPane.QUESTION_MESSAGE,
                                              null,
                                              options,
                                              options[0]);

    if (result == JOptionPane.OK_OPTION) {
      handleSave(true);

    } else {
      // why it's not CANCEL_OPTION is beyond me (at least on the mac)
      // but f-- it.. let's get this shite done..
      //} else if (result == JOptionPane.CANCEL_OPTION) {
      statusNotice("Export canceled, changes must first be saved.");
      //toolbar.clear();
      return false;
    }
    return true;
  }


  protected void handleBurnBootloader(final String target, final String programmer) {
    console.clear();
    statusNotice("Burning bootloader to I/O Board (this may take a minute)...");
    SwingUtilities.invokeLater(new Runnable() {
      public void run() {
        try {
          Uploader uploader = new AvrdudeUploader();
          if (uploader.burnBootloader(target, programmer)) {
            statusNotice("Done burning bootloader.");
          } else {
            statusError("Error while burning bootloader.");
            // error message will already be visible
          }
        } catch (RunnerException e) {
          statusError("Error while burning bootloader.");
          e.printStackTrace();
          //statusError(e);
        } catch (Exception e) {
          statusError("Error while burning bootloader.");
          e.printStackTrace();
        }
      }});
  }


  /**
   * Handler for File &rarr; Page Setup.
   */
  public void handlePageSetup() {
    //printerJob = null;
    if (printerJob == null) {
      printerJob = PrinterJob.getPrinterJob();
    }
    if (pageFormat == null) {
      pageFormat = printerJob.defaultPage();
    }
    pageFormat = printerJob.pageDialog(pageFormat);
    //System.out.println("page format is " + pageFormat);
  }


  /**
   * Handler for File &rarr; Print.
   */
  public void handlePrint() {
    statusNotice("Printing...");
    //printerJob = null;
    if (printerJob == null) {
      printerJob = PrinterJob.getPrinterJob();
    }
    if (pageFormat != null) {
      //System.out.println("setting page format " + pageFormat);
      printerJob.setPrintable(textarea.getPainter(), pageFormat);
    } else {
      printerJob.setPrintable(textarea.getPainter());
    }
    // set the name of the job to the code name
    printerJob.setJobName(sketch.getCurrentCode().getPrettyName());

    if (printerJob.printDialog()) {
      try {
        printerJob.print();
        statusNotice("Done printing.");

      } catch (PrinterException pe) {
        statusError("Error while printing.");
        pe.printStackTrace();
      }
    } else {
      statusNotice("Printing canceled.");
    }
    //printerJob = null;  // clear this out?
  }


  private int getFirmataSpeed()
  {
    String mess;
    String speedString = null;
    Integer speedInteger = new Integer(0);
    // create pattern
    mess = "Firmata\\.begin\\(\\s*(\\d+)\\s*\\)";
    Pattern pattern = Pattern.compile(mess);

    // scan for matches in current tab
    ArrayList<String> matches = new ArrayList<String>();
    Matcher matcher = pattern.matcher(sketch.current.program);
    while (matcher.find()) {
      //result = matcher.getMatch();
      speedString = matcher.group(1).toString();
    }  

    // return integer of speed
    if(null != speedString){
      try{
        return speedInteger.parseInt(speedString);
      }catch(Exception e){
        // ignore exceptions
      }
    }
    // or fail
    return 0;
  }

  
  private int getSerialSpeed()
  {
    String mess;
    String speedString = null;
    Integer speedInteger = new Integer(0);
    // create pattern
    mess = "Serial\\.begin\\(\\s*(\\d+)\\s*\\)";
    Pattern pattern = Pattern.compile(mess);

    // scan for matches in current tab
    ArrayList<String> matches = new ArrayList<String>();
    Matcher matcher = pattern.matcher(sketch.current.program);
    while (matcher.find()) {
      //result = matcher.getMatch();
      speedString = matcher.group(1).toString();
    }  
    
    // return integer of speed
    if(null != speedString){
      try{
        return speedInteger.parseInt(speedString);
      }catch(Exception e){
        // ignore exceptions
      }
    }
    // or fail
    return 0;
  }

  
  public void handleSerial() {
    if (uploading) return;
    
    try {
      toolbar.activate(EditorToolbar.SERIAL);
      boolean detectSpeed = Preferences.getBoolean("monitor.detect_speed");
      int portSpeed;
      if (detectSpeed == true) {
        portSpeed = Math.max(getSerialSpeed(), getFirmataSpeed());
      } else {
        portSpeed = 0;
      }

      if(portSpeed == 0)  // no Serial.begin or Firmata.begin guess
          serialMonitor.openSerialPort();
      else 
          // Serial or Firmata speed detected, assume that speed
          serialMonitor.openSerialPort(portSpeed);
           
      //serialMonitor.openSerialPort();        
      serialMonitor.setVisible(true);
      toolbar.deactivate(EditorToolbar.SERIAL);
    } catch (SerialException e) {
    	//statusError(e);
      status.error("Error opening serial port, see possible causes below...");
      System.err.println(e.getMessage());
      handleStop();
    }
  }
  

  /**
   * Handler for Serial Monitor.
   */
  /*
  public void handleSerial() {
    int portSpeed;
    int firmataSpeed;
    String portName;
    if (!debugging) {
      console.clear();
      toolbar.activate(EditorToolbar.SERIAL);
      //buttons.activate(EditorButtons.SERIAL);
      portSpeed = getSerialSpeed();
      firmataSpeed = getFirmataSpeed();
      // if no speed detected for debugging
      // try Firmata detection or 
      // assume speed stored in Preferences
      if(portSpeed == 0) {  // no Serial.begin guess
        if(firmataSpeed == 0)  // no Firmata.begin guess
          portSpeed = Preferences.getInteger("serial.rate");  // get speed from Preferences
        else 
          portSpeed = firmataSpeed;  // Firmata.begin detected, assume that speed
      } else {  // port speed detected, save it to Preferences
        Preferences.setInteger("serial.rate", portSpeed);
      }

      portName = Preferences.get("serial.port");
      try {
        if(0 < portSpeed){
          serialPort = new Serial(portName, portSpeed);
          serialPort.setMonitor(true);
        }else{
          serialPort = new Serial(portName);
          serialPort.setMonitor(true);
        }
      }
      catch (SerialException e) {
        status.error("Error opening serial port '" + portName + "'.");
        System.err.println(e.getMessage());
        handleStop();
        return;
        //e.printStackTrace();
      }
      statusNotice("Serial monitor running at " + serialPort.rate + "bps");
      //System.out.println("Serial monitor running at " + serialPort.rate + "bps");
      debugging = true;
      status.serial();
    } else {
      handleStop();
    }
  }
  */

  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


  /**
   * Show an error int the status bar.
   */
  public void statusError(String what) {
    status.error(what);
    //new Exception("deactivating RUN").printStackTrace();
    toolbar.deactivate(EditorToolbar.RUN);
  }


  /**
   * Show an exception in the editor status bar.
   */
  public void statusError(Exception e) {
    e.printStackTrace();
//    if (e == null) {
//      System.err.println("Editor.statusError() was passed a null exception.");
//      return;
//    }

    if (e instanceof RunnerException) {
      RunnerException re = (RunnerException) e;
      if (re.hasCodeIndex()) {
        sketch.setCurrentCode(re.getCodeIndex());
      }
      if (re.hasCodeLine()) {
        int line = re.getCodeLine();
        // subtract one from the end so that the \n ain't included
        if (line >= textarea.getLineCount()) {
          // The error is at the end of this current chunk of code,
          // so the last line needs to be selected.
          line = textarea.getLineCount() - 1;
          if (textarea.getLineText(line).length() == 0) {
            // The last line may be zero length, meaning nothing to select.
            // If so, back up one more line.
            line--;
          }
        }
        if (line < 0 || line >= textarea.getLineCount()) {
          System.err.println("Bad error line: " + line);
        } else {
          textarea.select(textarea.getLineStartOffset(line),
                          textarea.getLineStopOffset(line) - 1);
        }
      }
    }

    // Since this will catch all Exception types, spend some time figuring
    // out which kind and try to give a better error message to the user.
    String mess = e.getMessage();
    if (mess != null) {
      String javaLang = "java.lang.";
      if (mess.indexOf(javaLang) == 0) {
        mess = mess.substring(javaLang.length());
      }
      String rxString = "RuntimeException: ";
      if (mess.indexOf(rxString) == 0) {
        mess = mess.substring(rxString.length());
      }
      statusError(mess);
    }
//    e.printStackTrace();
  }


  /**
   * Show a notice message in the editor status bar.
   */
  public void statusNotice(String msg) {
    status.notice(msg);
  }


  /**
   * Clear the status area.
   */
  public void statusEmpty() {
    statusNotice(EMPTY);
  }


  // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

  protected void onBoardOrPortChange() {
    Map<String, String> boardPreferences =  Base.getBoardPreferences();
    lineStatus.setBoardName(boardPreferences.get("name"));
    lineStatus.setSerialPort(Preferences.get("serial.port"));
    lineStatus.repaint();
  }
  

  /**
   * Returns the edit popup menu.
   */
  class TextAreaPopup extends JPopupMenu {
    //String currentDir = System.getProperty("user.dir");
    String referenceFile = null;
    String clickedURL;

    JMenuItem cutItem;
    JMenuItem copyItem;
    JMenuItem discourseItem;
    JMenuItem referenceItem;
    JMenuItem openURLItem;
    JSeparator openURLItemSeparator;

    public TextAreaPopup() {
      JMenuItem item;
      openURLItem = new JMenuItem("Open URL");
      openURLItem.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          Base.openURL(clickedURL);
        }
      });
      add(openURLItem);
      
      openURLItemSeparator = new JSeparator();
      add(openURLItemSeparator);

      cutItem = new JMenuItem("Cut");
      cutItem.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            handleCut();
          }
      });
      this.add(cutItem);

      copyItem = new JMenuItem("Copy");
      copyItem.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            handleCopy();
          }
        });
      this.add(copyItem);

      discourseItem = new JMenuItem("Copy as HTML");
      discourseItem.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            handleCopyAsHTML();
          }
        });
      this.add(discourseItem);

      item = new JMenuItem("Paste");
      item.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            handlePaste();
          }
        });
      this.add(item);

      item = new JMenuItem("Select All");
      item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          handleSelectAll();
        }
      });
      this.add(item);

      this.addSeparator();

      item = new JMenuItem("Comment/Uncomment");
      item.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            handleCommentUncomment();
          }
      });
      this.add(item);

      item = new JMenuItem("Increase Indent");
      item.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            handleIndentOutdent(true);
          }
      });
      this.add(item);

      item = new JMenuItem("Decrease Indent");
      item.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            handleIndentOutdent(false);
          }
      });
      this.add(item);

      this.addSeparator();

      referenceItem = new JMenuItem("Find in Reference");
      referenceItem.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            handleFindReference();
          }
        });
      this.add(referenceItem);
    }

    // if no text is selected, disable copy and cut menu items
    public void show(Component component, int x, int y) {
      int lineNo = textarea.getLineOfOffset(textarea.xyToOffset(x, y));
      int offset = textarea.xToOffset(lineNo, x);
      String line = textarea.getLineText(lineNo);
      clickedURL = textarea.checkClickedURL(line, offset);
      if (clickedURL != null) {
        openURLItem.setVisible(true);
        openURLItemSeparator.setVisible(true);
      } else {
        openURLItem.setVisible(false);
        openURLItemSeparator.setVisible(false);
      }
      
      if (textarea.isSelectionActive()) {
        cutItem.setEnabled(true);
        copyItem.setEnabled(true);
        discourseItem.setEnabled(true);

        String sel = textarea.getSelectedText().trim();
        String referenceFile = PdeKeywords.getReference(sel);
        referenceItem.setEnabled(referenceFile != null);

      } else {
        cutItem.setEnabled(false);
        copyItem.setEnabled(false);
        discourseItem.setEnabled(false);
        referenceItem.setEnabled(false);
      }
      super.show(component, x, y);
    }
  }
}


