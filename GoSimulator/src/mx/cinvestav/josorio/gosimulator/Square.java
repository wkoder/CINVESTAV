package mx.cinvestav.josorio.gosimulator;

import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JLabel;

import mx.cinvestav.josorio.gosimulator.player.PlayerType;

/**
 * Shows a square depending of the player selection.
 * @author Moises Osorio
 *
 */
public class Square extends JLabel {

	private static final long serialVersionUID = 6965557105197438618L;
	private static final int DEFAULT_WIDTH = 44;
	private static final int DEFAULT_HEIGHT = 41;
	
	private PlayerType type;
	
	public Square() {
		type = PlayerType.EMPTY;
		setOpaque(true);
		setBackground(new Color(233, 204, 144));
	}
	
	public void setType(PlayerType type) {
		this.type = type;
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		
//		int h = g.getClipBounds().height;
//		int w = g.getClipBounds().width;
		
//		System.out.println(g.getClipBounds());
		
		int h = Math.max(DEFAULT_HEIGHT, g.getClipBounds().height);
		int w = Math.max(DEFAULT_WIDTH, g.getClipBounds().width);
		
		g.setColor(Color.BLACK);
		g.drawLine(0, h/2, w, h/2);
		g.drawLine(w/2, 0, w/2, h);
		
		if (type != PlayerType.EMPTY) {
			if (type == PlayerType.BLACK)
				g.setColor(Color.BLACK);
			else
				g.setColor(Color.WHITE);
			g.fillArc(0, 0, w, h, 0, 360);
		}
	}
}
