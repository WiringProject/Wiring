/*
 * TextAreaHighlight.java - Paints custom highlights in the text area
 * Copyright (C) 1999, 2000 Slava Pestov
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


import java.awt.Graphics;
import java.awt.event.MouseEvent;

/**
 * Highlight interface. Create implementations of this interface and
 * add them to the text area with <code>TextAreaPainter.addCustomHighlight()</code>
 * to paint custom highlights.
 *
 * @author Slava Pestov
 * @version $Id$
 */
public interface TextAreaHighlight
{
	/**
	 * Called after the highlight painter has been added.
	 * @param textArea The text area
	 * @param next The painter this one should delegate to
	 */
	void init(JEditTextArea textArea, TextAreaHighlight next);

	/**
	 * This should paint the highlight and delgate to the
	 * next highlight painter.
	 * @param gfx The graphics context
	 * @param line The line number
	 * @param y The y co-ordinate of the line
	 */
	void paintHighlight(Graphics gfx, int line, int y);

	/**
	 * Returns the tool tip to display at the specified
	 * location. If this highlighter doesn't know what to
	 * display, it should delegate to the next highlight
	 * painter.
	 * @param evt The mouse event
	 */
	String getToolTipText(MouseEvent evt);
}

