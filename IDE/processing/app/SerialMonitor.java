/* -*- mode: java; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
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

package processing.app;

import processing.app.debug.MessageConsumer;
import processing.core.*;
import processing.app.tools.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
import javax.swing.text.*;
import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

public class SerialMonitor extends JFrame implements MessageConsumer {
  private Serial serial;
  private String port;
  private JTextArea textArea;
  private JScrollPane scrollPane;
  private JTextField textField;
  private JButton sendButton;
  private JCheckBox autoscrollBox;
  private JComboBox lineEndings;
  private JComboBox serialRates;
  private int serialRate;
  private boolean speedDetection = false;
  private String lineEnding;
  private boolean hasPrintedTime = false;
  private int insertAt = 0;
  
  Color foreground;
  Color background;
  Color messageForeground;
  
  
  public SerialMonitor(String port) {
    super(port);
  
    this.port = port;
  
    addWindowListener(new WindowAdapter() {
        public void windowClosing(WindowEvent e) {
          closeSerialPort();
        }
      });  
      
    // obvious, no?
    KeyStroke wc = Base.WINDOW_CLOSE_KEYSTROKE;
    getRootPane().getInputMap(JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT).put(wc, "close");
    getRootPane().getActionMap().put("close", new AbstractAction() {
      public void actionPerformed(ActionEvent e) {
        closeSerialPort();
        setVisible(false);
      }});
  
    getContentPane().setLayout(new BorderLayout());
    
    Font font = Theme.getFont("console.font");
    foreground = Theme.getColor("serialmonitor.color");
    background = Theme.getColor("serialmonitor.bgcolor");
    messageForeground = Theme.getColor("serialmonitor.message.color");
    
    textArea = new JTextArea(16, 40);
    MouseListener popupListener = new PopupListener();
    textArea.addMouseListener(popupListener);
    textArea.setEditable(false);    
    textArea.setFont(font);
    textArea.setForeground(foreground);
    textArea.setBackground(background);
    // don't automatically update the caret.  that way we can manually decide
    // whether or not to do so based on the autoscroll checkbox.
    ((DefaultCaret)textArea.getCaret()).setUpdatePolicy(DefaultCaret.NEVER_UPDATE);
    
    scrollPane = new JScrollPane(textArea);
    
    getContentPane().add(scrollPane, BorderLayout.CENTER);
    
    JPanel pane = new JPanel();
    pane.setLayout(new BoxLayout(pane, BoxLayout.X_AXIS));
    pane.setBorder(new EmptyBorder(4, 4, 4, 4));

    textField = new JTextField(40);
    textField.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        send(textField.getText());
        textField.setText("");
      }});

    sendButton = new JButton("Send");
    sendButton.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent e) {
        send(textField.getText());
        textField.setText("");
      }});
    
    pane.add(textField);
    pane.add(Box.createRigidArea(new Dimension(4, 0)));
    pane.add(sendButton);
    
    getContentPane().add(pane, BorderLayout.NORTH);
    
    pane = new JPanel();
    pane.setLayout(new BoxLayout(pane, BoxLayout.X_AXIS));
    pane.setBorder(new EmptyBorder(4, 4, 4, 4));
    
    autoscrollBox = new JCheckBox("Autoscroll", true);
    
    lineEndings = new JComboBox(new String[] { "No line ending", "Newline", "Carriage return", "Both NL & CR" });
    lineEnding = Preferences.get("serial.debug_line_end");
    lineEndings.setSelectedItem(lineEnding);
    lineEndings.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent event) {
        String wholeString = (String) lineEndings.getSelectedItem();
        Preferences.set("serial.debug_line_end", wholeString);
      }});
    
    lineEndings.setMaximumSize(lineEndings.getMinimumSize());
      
    String[] serialRateStrings = {
      "300","1200","2400","4800","9600","14400",
      "19200","28800","38400","57600","115200"
    };
    
    serialRates = new JComboBox();
    for (int i = 0; i < serialRateStrings.length; i++)
      serialRates.addItem(serialRateStrings[i] + " baud");

    serialRate = Preferences.getInteger("serial.debug_rate");
    serialRates.setSelectedItem(serialRate + " baud");
    serialRates.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent event) {
        if(speedDetection == true)
          return;
        String wholeString = (String) serialRates.getSelectedItem();
        String rateString = wholeString.substring(0, wholeString.indexOf(' '));
        serialRate = Integer.parseInt(rateString);
        Preferences.set("serial.debug_rate", rateString);
        closeSerialPort();
        try {
	        openSerialPort();
        } catch (SerialException e) {
          //status.error("Error opening serial port '" + this.port + "'.");
          System.err.println(e.getMessage());
          //System.err.println(e);
        }
      }});
      
    serialRates.setMaximumSize(serialRates.getMinimumSize());

    JButton reset = new JButton("Reset Board");
    reset.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent event) {
        serial.setDTR(false);
        serial.setRTS(false);
        
        try {
          Thread.sleep(10);
        } catch (InterruptedException e) {}
        
        serial.setDTR(true);
        serial.setRTS(true);
      }
    });
    pane.add(reset);
    pane.add(Box.createRigidArea(new Dimension(4, 0)));
    pane.add(autoscrollBox);
    pane.add(Box.createHorizontalGlue());
    pane.add(lineEndings);
    pane.add(Box.createRigidArea(new Dimension(8, 0)));
    pane.add(serialRates);
    
    getContentPane().add(pane, BorderLayout.SOUTH);

    Image image = Toolkit.getDefaultToolkit().createImage(PApplet.ICON_IMAGE);
    setIconImage(image);

    pack();
    Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();
    if (Preferences.get("last.screen.height") != null) {
      // if screen size has changed, the window coordinates no longer
      // make sense, so don't use them unless they're identical
      int screenW = Preferences.getInteger("last.screen.width");
      int screenH = Preferences.getInteger("last.screen.height");
      if ((screen.width == screenW) && (screen.height == screenH)) {
        String locationStr = Preferences.get("last.serial.location");
        if (locationStr != null) {
          int[] location = PApplet.parseInt(PApplet.split(locationStr, ','));
          setPlacement(location);
        }
      }
    }
  }

  protected void setPlacement(int[] location) {
    setBounds(location[0], location[1], location[2], location[3]);
  }

  protected int[] getPlacement() {
    int[] location = new int[4];

    // Get the dimensions of the Frame
    Rectangle bounds = getBounds();
    location[0] = bounds.x;
    location[1] = bounds.y;
    location[2] = bounds.width;
    location[3] = bounds.height;

    return location;
  }

  private void send(String s) {
    if (serial != null) {
      switch (lineEndings.getSelectedIndex()) {
        case 1: s += "\n"; break;
        case 2: s += "\r"; break;
        case 3: s += "\r\n"; break;
      }
      serial.write(s);
      echo(s);
    }
  }
  
  public void openSerialPort(int detectedRate) throws SerialException {
    if (serial != null) return;
    serialRate = detectedRate;
    speedDetection = true;
    serialRates.setSelectedItem(serialRate + " baud");   
    speedDetection = false;
    serial = new Serial(port, serialRate);
    serial.addListener(this);
  }
  
  public void openSerialPort() throws SerialException {
    if (serial != null) return;
  
    serial = new Serial(port, serialRate);
    serial.addListener(this);
  }
  
  public void closeSerialPort() {
    if (serial != null) {
      int[] location = getPlacement();
      String locationStr = PApplet.join(PApplet.str(location), ",");
      Preferences.set("last.serial.location", locationStr);
      textArea.setText("");
      insertAt = 0;
      serial.dispose();
      serial = null;
    }
  }
    
  public void message(final String s) {
    SwingUtilities.invokeLater(new Runnable() {
      public void run() {
        textArea.insert(s,insertAt);
        insertAt += s.length();
        if (autoscrollBox.isSelected()) {
        	textArea.setCaretPosition(textArea.getDocument().getLength());
        }
      }});
  }
  
  public void echo(final String s) {
    SwingUtilities.invokeLater(new Runnable() {
      public void run() {
        String prnt = "\r\nsent: "+s+"\r\n";
        textArea.insert(prnt,insertAt);
        insertAt += prnt.length();
        if (autoscrollBox.isSelected()) {
        	textArea.setCaretPosition(textArea.getDocument().getLength());
        }
      }});
  }
  
  private String getDateTime() {
    DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss.SSS");
    Date date = new Date();
    return dateFormat.format(date);
  }
  
  class PopupListener extends MouseAdapter {
    JPopupMenu popup;

    PopupListener() {
      popup = new JPopupMenu();
      JMenuItem item;

      item = new JMenuItem("Clear");
      item.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e) {
          textArea.setText("");
          insertAt = 0;
        }
      });
      popup.add(item);
      
      popup.addSeparator();
      
      item = new JMenuItem("Copy");
      item.addActionListener(new ActionListener() {
          public void actionPerformed(ActionEvent e) {
            textArea.selectAll();
            textArea.copy();
          }
        });
      popup.add(item);
    }

    public void mousePressed(MouseEvent e) {
      maybeShowPopup(e);
    }

    public void mouseReleased(MouseEvent e) {
      maybeShowPopup(e);
    }

    private void maybeShowPopup(MouseEvent e) {
      if (e.isPopupTrigger()) {
        popup.show(e.getComponent(), e.getX(), e.getY());
      }
    }
  }
}
