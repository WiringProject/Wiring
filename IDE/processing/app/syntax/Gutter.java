/*
 * Gutter.java
 * :tabSize=8:indentSize=8:noTabs=false:
 * :folding=explicit:collapseFolds=1:
 *
 * Copyright (C) 1999, 2000 mike dillon
 * Portions copyright (C) 2001, 2002 Slava Pestov
 * minor features added for use with Wiring. [barragan]
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

package processing.app.syntax;

import processing.app.*;

import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
//import org.gjt.sp.jedit.*;

import processing.app.syntax.im.InputMethodSupport;
import processing.core.PApplet;

public class Gutter extends JComponent implements SwingConstants
{
	public Gutter(JEditTextArea textArea, TextAreaDefaults defaults)
	{
		this.textArea = textArea;
    setGutterWidth(defaults.gutterWidth);
    setCollapsed(defaults.gutterCollapsed);
    setLineNumberingEnabled(defaults.gutterLineNumbers);
    setHighlightInterval(defaults.gutterHighlightInterval);
    setCurrentLineHighlightEnabled(defaults.currentLineHighlightEnabled);
    setBackground(defaults.gutterbgcolor);
    setForeground(defaults.gutterfgcolor);
    setHighlightedForeground(defaults.gutterHighlightColor);
    //setMarkerHighlightColor(defaults.gutterMarkerColor);
    //setRegisterHighlightColor(defaults.gutterRegisterColor);
    setCurrentLineForeground(defaults.gutterCurrentLineColor);
    String alignment = defaults.gutterNumberAlignment;
    
    if ("right".equals(alignment)) {
      setLineNumberAlignment(Gutter.RIGHT);
    } else if ("center".equals(alignment)) {
      setLineNumberAlignment(Gutter.CENTER);
    } else // left == default case
    {
      setLineNumberAlignment(Gutter.LEFT);
    }
    setBorder(defaults.gutterBorderWidth, defaults.gutterFocusBorderColor, defaults.gutterNoFocusBorderColor, defaults.bgcolor);
    setFont(defaults.gutterFont);
    
		setDoubleBuffered(true);
    
		MouseHandler ml = new MouseHandler();
		addMouseListener(ml);
		addMouseMotionListener(ml);
	}
  
	public void paintComponent(Graphics gfx)
	{
		if (!collapsed)
		{
			// fill the background
			Rectangle r = gfx.getClipBounds();
			gfx.setColor(getBackground());
			gfx.fillRect(r.x, r.y, r.width, r.height);
            
			// paint custom highlights, if there are any
			if (highlights != null) paintCustomHighlights(gfx);
      
			// paint line numbers, if they are enabled
			if (lineNumberingEnabled) paintLineNumbers(gfx);
		}
	}
  
	private void paintLineNumbers(Graphics gfx)
	{
		FontMetrics pfm = textArea.getPainter().getFontMetrics();
		int lineHeight = pfm.getHeight();

    // XXX this is a hack to resize the gutter so the numbers fill in
    int lineCount = textArea.getLineCount();
    int digitsCount = (Integer.toString(lineCount)).length();
    setGutterWidth(3 + fm.charWidth('w') * ((digitsCount < 2) ? 2 : digitsCount));
    
		Rectangle clip = gfx.getClipBounds();

		int baseline = (int) (clip.y - clip.y % lineHeight) + (int) Math.round(
            (this.baseline + lineHeight - pfm.getDescent()) / 2.0);
    
    int firstLine = clip.y / lineHeight + textArea.getFirstLine() + 1;
		int lastLine = firstLine + clip.height / lineHeight;
		int caretLine = textArea.getCaretLine() + 1;

		int firstValidLine = firstLine > 1 ? firstLine : 1;
		int lastValidLine = (lastLine > textArea.getLineCount())
    ? textArea.getLineCount() : lastLine;
    
		boolean highlightCurrentLine = currentLineHighlightEnabled;
    //&& (textArea.getSelectionStart() == textArea.getSelectionStop());
    
		gfx.setFont(getFont());
    
		Color fg = getForeground();
		Color hfg = getHighlightedForeground();
		Color clfg = getCurrentLineForeground();
    
		String number;
		int offset;
    
		for (int line = firstLine; line <= lastLine;
         line++, baseline += lineHeight)
		{
			// only print numbers for valid lines
			if (line < firstValidLine || line > lastValidLine)
				continue;
      
			number = Integer.toString(line);
      
			switch (alignment)
			{
        case RIGHT:
          //offset = gutterSize.width - collapsedSize.width
          offset = gutterSize.width - 2
					- (fm.stringWidth(number) + 1);
          break;
        case CENTER:
          //offset = ((gutterSize.width - collapsedSize.width)
          offset = ((gutterSize.width - 2)
                    - fm.stringWidth(number)) / 2;
          break;
        case LEFT: default:
          offset = 1;
			}
      
			if (line == caretLine && highlightCurrentLine)
			{
				gfx.setColor(clfg);
			}
			else if (interval > 1 && line % interval == 0)
			{
				gfx.setColor(hfg);
			}
			else
			{
				gfx.setColor(fg);
			}
      
			gfx.drawString(number, ileft + offset, baseline);
		}
	}
  
	private void paintCustomHighlights(Graphics gfx)
	{
		int lineHeight = textArea.getPainter().getFontMetrics()
    .getHeight();
    
		int firstLine = textArea.getFirstLine();
		int lastLine = firstLine + (getHeight() / lineHeight);
    
		int y = 0;
    
		for (int line = firstLine; line < lastLine;
         line++, y += lineHeight)
		{
			highlights.paintHighlight(gfx, line, y);
		}
	}
  
	/**
   * Marks a line as needing a repaint.
   * @param line The line to invalidate
   */
	public final void invalidateLine(int line)
	{
		if(collapsed)
			return;
    
		FontMetrics pfm = textArea.getPainter().getFontMetrics();
		repaint(0,textArea.lineToY(line) + pfm.getDescent() + pfm.getLeading(),
            getWidth(),pfm.getHeight());
	}
  
	/**
   * Marks a range of lines as needing a repaint.
   * @param firstLine The first line to invalidate
   * @param lastLine The last line to invalidate
   */
	public final void invalidateLineRange(int firstLine, int lastLine)
	{
		if(collapsed)
			return;
    
		FontMetrics pfm = textArea.getPainter().getFontMetrics();
		repaint(0,textArea.lineToY(firstLine) + pfm.getDescent() + pfm.getLeading(),
            getWidth(),(lastLine - firstLine + 1) * pfm.getHeight());
	}
  
	/**
	 * Adds a custom highlight painter.
	 * @param highlight The highlight
	 */
	public void addCustomHighlight(TextAreaHighlight highlight)
	{
		highlight.init(textArea, highlights);
		highlights = highlight;
	}
  
	/**
	 * Convenience method for setting a default matte border on the right
	 * with the specified border width and color
	 * @param width The border width (in pixels)
	 * @param color1 The focused border color
	 * @param color2 The unfocused border color
	 * @param color3 The gutter/text area gap color
	 */
	public void setBorder(int width, Color color1, Color color2, Color color3)
	{
		this.borderWidth = width;
    
		focusBorder = new CompoundBorder(new MatteBorder(0,0,0,width,color3),
                                     new MatteBorder(0,0,0,width,color1));
		noFocusBorder = new CompoundBorder(new MatteBorder(0,0,0,width,color3),
                                       new MatteBorder(0,0,0,width,color2));
		updateBorder();
	}
  
	/**
	 * Sets the border differently if the text area has focus or not.
	 */
	public void updateBorder()
	{
		// because we are called from the text area's focus handler,
		// we do an invokeLater() so that the view's focus handler
		// has a chance to execute and set the edit pane properly
		SwingUtilities.invokeLater(new Runnable()
                               {
			public void run()
			{
				/*if(view.getEditPane() == null)
					return;
        
				if(view.getEditPane().getTextArea() == textArea)
					setBorder(focusBorder);
				else*/
					setBorder(noFocusBorder);
			}
		});
	}
  
	/*
	 * JComponent.setBorder(Border) is overridden here to cache the left
	 * inset of the border (if any) to avoid having to fetch it during every
	 * repaint.
	 */
	public void setBorder(Border border)
	{
		super.setBorder(border);
    
		if (border == null)
		{
			ileft = 0;
			collapsedSize.width = 0;
			collapsedSize.height = 0;
		}
		else
		{
			Insets insets = border.getBorderInsets(this);
			ileft = insets.left;
			collapsedSize.width = 5; //insets.left + insets.right;
			collapsedSize.height = insets.top + insets.bottom;
		}
	}
  
	/*
	 * JComponent.setFont(Font) is overridden here to cache the baseline for
	 * the font. This avoids having to get the font metrics during every
	 * repaint.
	 */
	public void setFont(Font font)
	{
		super.setFont(font);
    
    fm = getFontMetrics(font);
    baseline = fm.getAscent();
	}
  
	/**
	 * Get the foreground color for highlighted line numbers
	 * @return The highlight color
	 */
	public Color getHighlightedForeground()
	{
		return intervalHighlight;
	}
  
	public void setHighlightedForeground(Color highlight)
	{
		intervalHighlight = highlight;
	}
  
	public Color getCurrentLineForeground()
 	{
		return currentLineHighlight;
	}
  
	public void setCurrentLineForeground(Color highlight)
	{
		currentLineHighlight = highlight;
 	}
  
	/**
	 * Set the width of the expanded gutter
	 * @param width The gutter width
	 */
	public void setGutterWidth(int width)
	{
		if (width < collapsedSize.width) width = collapsedSize.width;
    
		gutterSize.width = width;
    
		// if the gutter is expanded, ask the text area to revalidate
		// the layout to resize the gutter
		if (!collapsed) textArea.revalidate();
	}

	/**
	 * Get the width of the expanded gutter
	 * @return The gutter width
	 */
	public int getGutterWidth()
	{
		return gutterSize.width;
	}
  
	/*
	 * Component.getPreferredSize() is overridden here to support the
	 * collapsing behavior.
	 */
	public Dimension getPreferredSize()
	{
		if (collapsed)
		{
			return collapsedSize;
		}
		else
		{
			return gutterSize;
		}
	}
  
	public Dimension getMinimumSize()
	{
		return getPreferredSize();
	}
  
	public String getToolTipText(MouseEvent evt)
	{
		return (highlights == null) ? null :
    highlights.getToolTipText(evt);
	}
  
	/**
	 * Identifies whether or not the line numbers are drawn in the gutter
	 * @return true if the line numbers are drawn, false otherwise
	 */
	public boolean isLineNumberingEnabled()
	{
		return lineNumberingEnabled;
	}
  
	/**
	 * Turns the line numbering on or off and causes the gutter to be
	 * repainted.
	 * @param enabled true if line numbers are drawn, false otherwise
	 */
	public void setLineNumberingEnabled(boolean enabled)
	{
		if (lineNumberingEnabled == enabled) return;
    
		lineNumberingEnabled = enabled;
    
		repaint();
	}
  
	/**
	 * Toggles line numbering.
	 * @param enabled true if line numbers are drawn, false otherwise
	 */
	public void toggleLineNumberingEnabled()
	{
		setLineNumberingEnabled(!lineNumberingEnabled);
	}
  
	/**
	 * Identifies whether the horizontal alignment of the line numbers.
	 * @return Gutter.RIGHT, Gutter.CENTER, Gutter.LEFT
	 */
	public int getLineNumberAlignment()
	{
		return alignment;
	}
  
	/**
	 * Sets the horizontal alignment of the line numbers.
	 * @param alignment Gutter.RIGHT, Gutter.CENTER, Gutter.LEFT
	 */
	public void setLineNumberAlignment(int alignment)
	{
		if (this.alignment == alignment) return;
    
		this.alignment = alignment;
    
		repaint();
	}
  
	/**
	 * Identifies whether the gutter is collapsed or expanded.
	 * @return true if the gutter is collapsed, false if it is expanded
	 */
	public boolean isCollapsed()
	{
		return collapsed;
	}
  
	/**
	 * Sets whether the gutter is collapsed or expanded and force the text
	 * area to update its layout if there is a change.
	 * @param collapsed true if the gutter is collapsed,
	 *                   false if it is expanded
	 */
	public void setCollapsed(boolean collapsed)
	{
		if (this.collapsed == collapsed) return;
    
		this.collapsed = collapsed;
    
		textArea.revalidate();
	}
  
	/**
	 * Toggles whether the gutter is collapsed or expanded.
	 */
	public void toggleCollapsed()
	{
		setCollapsed(!collapsed);
	}
  
	/**
	 * Makes the gutter's current size the default for future sessions.
	 * @since jEdit 2.7pre2
	 */
	public void saveGutterSize()
	{
		/*jEdit.setProperty("view.gutter.width", Integer.toString(
                                                            gutterSize.width));
	*/}
  
	/**
	 * Sets the number of lines between highlighted line numbers.
	 * @return The number of lines between highlighted line numbers or
	 *          zero if highlighting is disabled
	 */
	public int getHighlightInterval()
	{
		return interval;
	}
  
	/**
	 * Sets the number of lines between highlighted line numbers. Any value
	 * less than or equal to one will result in highlighting being disabled.
	 * @param interval The number of lines between highlighted line numbers
	 */
	public void setHighlightInterval(int interval)
	{
		if (interval <= 1) interval = 0;
		this.interval = interval;
		repaint();
	}
  
	public boolean isCurrentLineHighlightEnabled()
	{
		return currentLineHighlightEnabled;
	}
  
	public void setCurrentLineHighlightEnabled(boolean enabled)
	{
		if (currentLineHighlightEnabled == enabled) return;
    
		currentLineHighlightEnabled = enabled;
    
		repaint();
	}
  
	public JPopupMenu getContextMenu()
	{
		return context;
	}
  
	public void setContextMenu(JPopupMenu context)
	{
		this.context = context;
	}
  
	// private members
	//private View view;
	private JEditTextArea textArea;
  
	private JPopupMenu context;
  
	private TextAreaHighlight highlights;
  
	private int baseline = 0;
	private int ileft = 0;
  
	private Dimension gutterSize = new Dimension(0,0);
	private Dimension collapsedSize = new Dimension(5,0);
  
	private Color intervalHighlight;
	private Color currentLineHighlight;
  
	private FontMetrics fm;
  
	private int alignment;
  
	private int interval = 0;
	private boolean lineNumberingEnabled = true;
	private boolean currentLineHighlightEnabled = false;
	private boolean collapsed = false;
  
	private int borderWidth;
	private Border focusBorder, noFocusBorder;
  
	class MouseHandler extends MouseAdapter implements MouseMotionListener
	{
		public void mousePressed(MouseEvent e)
		{
			if(e.getX() >= getWidth() - borderWidth)
			{
				e.translatePoint(-getWidth(),0);
				textArea.mouseHandler.mousePressed(e);
				//return;
			}
			else if(context != null && (e.getModifiers()
                                  & InputEvent.BUTTON3_MASK) != 0)
			{
				if(context.isVisible())
					context.setVisible(false);
				else
				{
					//XXX this is a hack to make sure the
					//XXX actions get the right text area
					textArea.requestFocus();
          
					context.show(Gutter.this,
                       e.getX()+1, e.getY()+1);
				}
			}
			else
        if(e.getClickCount() == 2)
				toggleCollapsed();
			else
			{
				dragStart = e.getPoint();
				startWidth = gutterSize.width;
			}
		}
    
		public void mouseDragged(MouseEvent e)
		{
			if ((e.getModifiers() & InputEvent.BUTTON3_MASK) != 0)
				return;
      
			if(collapsed || e.getX() >= getWidth() - borderWidth)
			{
				e.translatePoint(-getWidth(),0);
				textArea.mouseHandler.mouseDragged(e);
				return;
			}
      
			if (dragStart == null) return;
      
//			gutterSize.width = startWidth + e.getX() - dragStart.x;
      
//			if (gutterSize.width < collapsedSize.width)
//				gutterSize.width = startWidth;
      
			textArea.revalidate();
		}
    
		/* public void mouseExited(MouseEvent e)
     {
     if (dragStart != null && dragStart.x > e.getPoint().x)
     {
     setCollapsed(true);
     gutterSize.width = startWidth;
     
     textArea.revalidate();
     }
     
     //dragStart = null;
     } */
    
		public void mouseMoved(MouseEvent e) {}
    
		public void mouseReleased(MouseEvent e)
		{
			if ((e.getModifiers() & InputEvent.BUTTON3_MASK) != 0)
				return;
      
			if(collapsed || e.getX() >= getWidth() - borderWidth)
			{
				e.translatePoint(-getWidth(),0);
				textArea.mouseHandler.mouseReleased(e);
				return;
			}
      
			dragStart = null;
		}
    
		private Point dragStart = null;
		private int startWidth = 0;
	}
}
