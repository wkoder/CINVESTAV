package mx.cinvestav.josorio.gosimulator;

import static mx.cinvestav.josorio.gosimulator.player.PlayerType.BLACK;
import static mx.cinvestav.josorio.gosimulator.player.PlayerType.WHITE;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.SpinnerNumberModel;

import mx.cinvestav.josorio.gosimulator.player.PlayerType;

/**
 * Simulates a Go game.
 * @author Moises Osorio
 */
public class GoSimulatorUI extends JFrame implements Runnable {
	
	/**
	 * Serial version.
	 */
	private static final long serialVersionUID = 1337L;
	
	/**
	 * If the game is running.
	 */
	private boolean running;
	/**
	 * Turn lock.
	 */
	private Object turnLock;
	/**
	 * If the thread has completely stopped.
	 */
	private boolean completelyStopped;
	/**
	 * Simulator of the game.
	 */
	private GoSimulator simulator;
	
	/**
	 * Graphic elements.
	 */
	private JSpinner boardSizeUI;
	private JSpinner delayUI;
	private JPanel boardUI;
	private JComboBox playerBlackUI;
	private JComboBox playerWhiteUI;
	private JButton stopUI;
	private JLabel blackLabelUI;
	private JLabel whiteLabelUI;
	
	/**
	 * Creates the simulator.
	 */
	public GoSimulatorUI() {
		turnLock = new Object();
		simulator = new GoSimulator();
		init();
	}
	
	/**
	 * Initializes the UI.
	 */
	private void init() {
		playerBlackUI = new JComboBox(GoSimulator.PLAYERS);
		playerBlackUI.setSelectedItem(PlayerSimulator.GNUGO);
		
		playerWhiteUI = new JComboBox(GoSimulator.PLAYERS);
		playerWhiteUI.setSelectedItem(PlayerSimulator.SMART);
		
		boardSizeUI = new JSpinner();
		boardSizeUI.setModel(new SpinnerNumberModel(19, 2, 40, 1));
//		boardSizeUI.addChangeListener(new ChangeListener() {
//			@Override
//			public void stateChanged(ChangeEvent event) {
//				setBoardSize((Integer) boardSizeUI.getValue());
//			}
//		});

		delayUI = new JSpinner();
		delayUI.setModel(new SpinnerNumberModel(200, 0, 2000, 10));
		
		final JButton clearUI = new JButton("New");
		clearUI.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					clear();
				} catch (Exception ee) {
					JOptionPane.showMessageDialog(clearUI, ee.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
				}
			}
		});

		stopUI = new JButton("Stop");
		stopUI.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (running)
					stopRunning();
				else
					try {
						startRunning();
					} catch (Exception ee) {
						JOptionPane.showMessageDialog(stopUI, ee.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
					}
			}
		});

		JButton passUI = new JButton("Pass");
		passUI.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				selectSquare(-1, -1);
			}
		});
		
		whiteLabelUI = new JLabel("White(0): ");
		blackLabelUI = new JLabel("Black(0): ");
		
		JPanel upperPanel = new JPanel();
		upperPanel.add(blackLabelUI);
		upperPanel.add(playerBlackUI);
		upperPanel.add(whiteLabelUI);
		upperPanel.add(playerWhiteUI);
		upperPanel.add(new JLabel("Board size: "));
		upperPanel.add(boardSizeUI);
		upperPanel.add(new JLabel("Delay time: "));
		upperPanel.add(delayUI);
		upperPanel.add(passUI);
		upperPanel.add(stopUI);
		upperPanel.add(clearUI);
		
		boardUI = new JPanel();
		
		JPanel all = new JPanel(new BorderLayout(0, 0));
		all.add(boardUI, BorderLayout.CENTER);
		all.add(upperPanel, BorderLayout.NORTH);
		setContentPane(all);
		
		setBackground(new Color(233, 204, 144));
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				stopRunning();
				System.exit(0);
			}
		});
		setSize(800, 800);
		setTitle("Go Simulator - Moises Osorio");
		//setResizable(false);
		setVisible(true);
	}
	
	/**
	 * Stops running the simulator.
	 */
	public void stopRunning() {
		if (!running)
			return;
		
		stopUI.setText("Resume");
		
		running = false;
		
		synchronized (turnLock) {
			turnLock.notify();
		}
		
		while (!completelyStopped)
			try {
				Thread.sleep(50);
			} catch (InterruptedException e) { }
	}
	
	/**
	 * Clears the board.
	 */
	public void clear() {
		setBoardSize((Integer) boardSizeUI.getValue());
	}
	
	/**
	 * Acts over a user selected square.
	 * @param row
	 * @param col
	 */
	public void selectSquare(int row, int col) {
		if (!running || (row >= 0 && col >= 0 && simulator.getBoard()[row][col] != PlayerType.EMPTY) || 
				(simulator.getTurn() != BLACK && simulator.getPlayerWhite() != null) || 
				(simulator.getTurn() != WHITE && simulator.getPlayerBlack() != null))
			return;
		
		
		makeTurn(row, col, simulator.getTurn());
	}
	
	/**
	 * Sets the board size.
	 * @param boardSize The new board size.
	 */
	public void setBoardSize(int boardSize) {
		stopRunning();
		
		boolean sizeChanged = simulator.getBoardSize() != boardSize;
		boardSizeUI.setValue(boardSize);
		boardUI.setLayout(new GridLayout(boardSize, boardSize, 0, 0));
		boardUI.removeAll();
		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++) {
				Square square = new Square();
				boardUI.add(square);

				final int row = i;
				final int column = j;
				square.addMouseListener(new MouseAdapter() {
					@Override
					public void mouseClicked(MouseEvent e) {
						if ((simulator.getPlayerWhite() != null && simulator.getPlayerBlack() != null) || e.isControlDown())
							JOptionPane.showMessageDialog(boardUI, simulator.getInfo(row, column));
						else
							selectSquare(row, column);
					}
				});
			}
		
//		setSize(n*45, n*45 + boardSizeUI.getHeight());
		setMinimumSize(new Dimension(boardSize*40, boardSize*44 + boardSizeUI.getHeight()));
		if (sizeChanged)
			pack();
		
		simulator = new GoSimulator();
		simulator.startSimulation(GoSimulator.PLAYERS[playerBlackUI.getSelectedIndex()], 
				GoSimulator.PLAYERS[playerWhiteUI.getSelectedIndex()], boardSize);
		
		startRunning();
	}
	
	/**
	 * Starts running the simulator.
	 */
	private void startRunning() {
		if (running)
			return;
		
		stopUI.setText("Stop");
		running = true;
		completelyStopped = false;
		simulator.changePlayers(GoSimulator.PLAYERS[playerBlackUI.getSelectedIndex()], GoSimulator.PLAYERS[playerWhiteUI.getSelectedIndex()]);
		
		if (simulator.getPlayerWhite() != null || simulator.getPlayerBlack() != null) {
			Thread th = new Thread(this, "GoSimulator-TurnController");
			th.start();
		}
	}
	
	/**
	 * Updates the UI to match the current board configuration.
	 */
	private void updateBoard() {
		PlayerType[][] board = simulator.getBoard();
		for (int i = 0; i < simulator.getBoardSize(); i++)
			for (int j = 0; j < simulator.getBoardSize(); j++) {
				Square square = (Square) boardUI.getComponent(i*simulator.getBoardSize() + j);
				square.setType(board[i][j]);
//				square.setToolTipText(simulator.getInfo(i, j));
			}
		
		boardUI.repaint();
	}
	
	/**
	 * Makes a turn for a player. Defines the winner and loser of the game.
	 * @param x Row position.
	 * @param y Column position.
	 * @param player Player who made the turn.
	 */
	public void makeTurn(int x, int y, PlayerType player) {
		if (!running)
			return;
		
		boolean ok = player == null ? simulator.makeTurn() : simulator.makeTurn(x, y, player);
		
		int[] scores = simulator.getScores(true);
		blackLabelUI.setText("Black (" + scores[0] + "):");
		whiteLabelUI.setText("White (" + scores[1] + "):");
		updateBoard();
		
		if (!ok) { // Game ends
			running = false;
			
			String winner;
			if (scores[0] > scores[1])
				winner = "Player Black wins.";
			else if (scores[0] < scores[1])
				winner = "Player White wins.";
			else
				winner = "It's a tie.";
			
			String msg = "";
			if (simulator.getBothPassed())
				msg = "Both players passed their turns. ";
			msg += "Scores are Black: " + scores[0] + " vs. White " + scores[1] + ". " + winner;
			
			JOptionPane.showMessageDialog(this, msg);
		}
		
		synchronized (turnLock) {
			turnLock.notify();
		}
	}
	
	@Override
	public void run() {
		try {
			while (running) {
				if ((simulator.getTurn() == WHITE && simulator.getPlayerWhite() == null) || 
						(simulator.getTurn() == BLACK && simulator.getPlayerBlack() == null))
					synchronized (turnLock) {
						try {
							turnLock.wait();
						} catch (InterruptedException e) { }
					}
				else {
					int delay = (Integer) delayUI.getValue();
					try {
						Thread.sleep(delay);
					} catch (InterruptedException e) { }
				}
				
				if (!running)
					continue;
				
				makeTurn(0, 0, null);
			}
		} catch (Exception e) {
			running = false;
			e.printStackTrace();
			JOptionPane.showMessageDialog(this, "Something went wrong: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
		}
		
		completelyStopped = true;
	}
	
}
