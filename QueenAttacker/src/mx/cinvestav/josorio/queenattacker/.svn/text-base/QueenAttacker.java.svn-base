package mx.cinvestav.josorio.queenattacker;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Arrays;

import javax.swing.BorderFactory;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JSpinner;
import javax.swing.SpinnerNumberModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

/**
 * Simulates the n-queen problem in an interacitve way.
 * @author Moises Osorio
 */
public class QueenAttacker extends JFrame {
	
	private static final long serialVersionUID = 1L;
	
	/**
	 * Value of N.
	 */
	private int n;
	/**
	 * Current board configuration.
	 */
	private SquareType[][] board;
	/**
	 * If set shows the steps while searching for a solution.
	 */
	private boolean showSteps;
	/**
	 * Is the solution shown is reflected.
	 */
	private boolean reflected;
	/**
	 * Rotation ID.
	 */
	private int rotation;
	/**
	 * Current solution.
	 */
	private int[] currentSolution;

	/**
	 * Graphic elements.
	 */
	private JSpinner boardSizeUI;
	private JPanel boardUI;
	private JButton solutionFinderUI;
	private JRadioButton rotation0UI;
	private JCheckBox reflectionUI;
	
	/**
	 * Initializes the UI.
	 */
	private void init() {
		boardSizeUI = new JSpinner();
		boardSizeUI.setModel(new SpinnerNumberModel(8, 5, 20, 1));
		boardSizeUI.addChangeListener(new ChangeListener() {
			@Override
			public void stateChanged(ChangeEvent event) {
				setBoardSize((Integer) boardSizeUI.getValue());
			}
		});
		
		solutionFinderUI = new JButton("Find next solution");
		solutionFinderUI.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				findNextSolution();
			}
		});
		
		JButton clearUI = new JButton("Clear");
		clearUI.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				clear();
			}
		});

		final JCheckBox showStepsUI = new JCheckBox("Show steps");
		showStepsUI.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				showSteps = showStepsUI.isSelected();
			}
		});

		reflectionUI = new JCheckBox("Reflect");
		reflectionUI.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				setReflection(reflectionUI.isSelected());
			}
		});
		
		rotation0UI = new JRadioButton("0°");
		rotation0UI.setSelected(true);
		rotation0UI.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				setRotation(0);
			}
		});
		JRadioButton rotation90UI = new JRadioButton("90°");
		rotation90UI.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				setRotation(1);
			}
		});
		JRadioButton rotation180UI = new JRadioButton("180°");
		rotation180UI.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				setRotation(2);
			}
		});
		JRadioButton rotation270UI = new JRadioButton("270°");
		rotation270UI.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				setRotation(3);
			}
		});
		
		ButtonGroup rotationGroupUI = new ButtonGroup();
		rotationGroupUI.add(rotation0UI);
		rotationGroupUI.add(rotation90UI);
		rotationGroupUI.add(rotation180UI);
		rotationGroupUI.add(rotation270UI);
		
		JPanel rotationPanel = new JPanel();
		rotationPanel.add(rotation0UI);
		rotationPanel.add(rotation90UI);
		rotationPanel.add(rotation180UI);
		rotationPanel.add(rotation270UI);

		JPanel upperPanel = new JPanel();
		upperPanel.add(new JLabel("Board size: "));
		upperPanel.add(boardSizeUI);
		upperPanel.add(solutionFinderUI);
		upperPanel.add(clearUI);
		upperPanel.add(showStepsUI);
		upperPanel.add(reflectionUI);
		upperPanel.add(rotationPanel);
		
		boardUI = new JPanel();
		
		JPanel all = new JPanel(new BorderLayout(0, 0));
		all.add(boardUI, BorderLayout.CENTER);
		all.add(upperPanel, BorderLayout.NORTH);
		setContentPane(all);
		
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setSize(800, 800);
		//setResizable(false);
		setVisible(true);
	}
	
	public void setReflection(boolean reflected) {
		this.reflected = reflected;
		setSolution(currentSolution);
	}
	
	/**
	 * Sets the rotation degree.
	 * @param rotation
	 */
	public void setRotation(int rotation) {
		this.rotation = rotation;
		setSolution(currentSolution);
	}
	
	/**
	 * Finds the next solution from the current board configuration.
	 */
	public void findNextSolution() {
		Thread thread = new Thread(new Runnable() {
			@Override
			public void run() {
				rotation0UI.setSelected(true);
				rotation = 0;
				if (findNextLexSolution())
					updateUI();
				solutionFinderUI.setEnabled(true);
			}
		});
		
		solutionFinderUI.setEnabled(false);
		thread.start();
	}
	
	/**
	 * Maps the current board configuration into a row vector.
	 * @return The mapping.
	 */
	private int[] getCurrentBoardPos() {
		int[] boardPos = new int[n];
		
		if (currentSolution != null)
			for (int i = 0; i < n; i++)
				boardPos[i] = currentSolution[i];
		else
			for (int i = 0; i < n; i++) {
				boardPos[i] = -1; // In case we don't find a queen in this row
				for (int j = 0; j < n; j++)
					if (board[i][j] == SquareType.OCCUPIED) {
						boardPos[i] = j; // Found a queen
						break;
					}
			}
		
		return boardPos;
	}
	
	/**
	 * Gets the non-attacked positions in the row <code>currentPos</code>.
	 * @param currentPos The current position.
	 * @param boardPos The current board configuration.
	 * @param finalPos The final position to check for.
	 * @return The non-attacked columns in the current row.
	 */
	private boolean[] getNonAttackedPositions(int currentPos, int[] boardPos, int finalPos) {
		boolean[] possiblePos = new boolean[n]; // Not attacked positions by the current board configuration
		Arrays.fill(possiblePos, true);
		for (int i = 0; i <= finalPos; i++)
			if (boardPos[i] >= 0) {
				possiblePos[ boardPos[i] ] = false; // Row attacked
				int diff = Math.abs(currentPos - i);
				if (boardPos[i] - diff >= 0) // Increasing diagonal attacked
					possiblePos[boardPos[i] - diff] = false;
				if (boardPos[i] + diff < n) // Decreasing diagonal attacked
					possiblePos[boardPos[i] + diff] = false;
			}
		
		return possiblePos;
	}
	
	/**
	 * Finds the next lexicographically solution.
	 * @return If a solution was found.
	 */
	private boolean findNextLexSolution() {
		int[] boardStart = getCurrentBoardPos();
		for (int i = 0; i < n; i++)
			if (boardStart[i] == -1)
				boardStart[i] = 0; // Set the starting position
		
		int[] boardPos = new int[n];
		Arrays.fill(boardPos, -1);
		if (findNextLexSolution(0, boardPos, boardStart, false)) {
			setSolution(boardPos);
			return true;
		}
		
		// A solution was not found, start over
		Arrays.fill(boardStart, 0);
		if (findNextLexSolution(0, boardPos, boardStart, false)) {
			setSolution(boardPos);
			return true;
		}
		
		return false;
	}
	
	/**
	 * Does the hard word to find the next solution.
	 * @param currentPos
	 * @param boardPos
	 * @param boardStart
	 * @param changeMade
	 * @return
	 */
	private boolean findNextLexSolution(int currentPos, int[] boardPos, int[] boardStart, boolean changeMade) {
		if (currentPos == n)
			return changeMade && isGenSolution(boardPos); // If a change was made and the solution found is the geenrator.
		
		boolean[] possiblePos = getNonAttackedPositions(currentPos, boardPos, currentPos-1); // Get non-attacked positions by previous queen in the board
		int start = changeMade? 0 : boardStart[currentPos]; // This let us make the next lexicographically move
		for (int pos = start; pos < n; pos++)
			if (possiblePos[pos]) {
				boardPos[currentPos] = pos;
				if (showSteps)
					setSolution(boardPos); // Show it!
				if (findNextLexSolution(currentPos+1, boardPos, boardStart, changeMade | (pos != boardStart[currentPos])))
					return true;
				boardPos[currentPos] = -1;
			}
		
		return false;
	}
	
	/**
	 * Clears the board.
	 */
	public void clear() {
		setBoardSize(n);
	}
	
	/**
	 * Checks if a solution is the generator.
	 * @param solution
	 * @return
	 */
	public boolean isGenSolution(int[] solution) {		
		int[] rot = solution;
		for (int i = 0; i < 4; i++) {
			rot = rotate(rot); // Apply next rotation
			if (compare(solution, rot) > 0)
				return false;
			
			int[] ref = reflect(rot); // Reflect the rotation
			if (compare(solution, ref) > 0)
				return false;
		}
		
		return true;
	}
	
	/**
	 * Compares two solutions.
	 * @param a
	 * @param b
	 * @return
	 */
	private int compare(int[] a, int[] b) {
		for (int i = 0; i < n; i++)
			if (a[i] < b[i])
				return -1;
			else if (a[i] > b[i])
				return 1;
		
		return 0;
	}
	
	/**
	 * Reflects a solution.
	 * @param reflect
	 * @return
	 */
	private int[] reflect(int[] reflect) {
		int[] ref = new int[n];
		for (int i = 0; i < n; i++)
			ref[i] = n - 1 - reflect[i];
		
		return ref;
	}
	
	/**
	 * Rotates a solution 90° clockwise.
	 * @param solution
	 * @return
	 */
	private int[] rotate(int[] solution) {
		int[] rot = new int[n];
		for (int i = 0; i < n; i++)
			rot[solution[i]] = n - 1 - i;
		
		return rot;
	}
	
	/**
	 * Shows the given solution.
	 * @param boardPos Row vector of the solution.
	 */
	public void setSolution(int[] solution) {
		int[] b = currentSolution = solution;
		for (int i = 0; i < rotation; i++) // Apply the rotations
			b = rotate(b);
		if (reflected) // Reflect is asked
			 b = reflect(b);
		
		for (int i = 0; i < n; i++) {
			Arrays.fill(board[i], SquareType.ATTACKED);
			if (b[i] >= 0)
				board[i][b[i]] = SquareType.OCCUPIED;
		}
		
		if (showSteps)
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) { }
		
		updateUI();
	}
	
	/**
	 * Acts over a user selected square.
	 * @param row
	 * @param col
	 */
	public void selectSquare(int row, int col) {
		if (board[row][col] == SquareType.OCCUPIED)
			board[row][col] = SquareType.NOT_ATTACKED;
		else if (board[row][col] == SquareType.NOT_ATTACKED)
			board[row][col] = SquareType.OCCUPIED;
		else {
			JOptionPane.showMessageDialog(this, "You cannot select an attacked position.", "Impossible selection", JOptionPane.ERROR_MESSAGE);
			return;
		}
		
		currentSolution = null;
		
		int[] DR = {-1, 1};
		int[] DC = {-1, 1};
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (board[i][j] != SquareType.OCCUPIED) {
					boolean attacked = false;
					for (int k = 0; k < n && !attacked; k++) {
						attacked |= board[i][k] == SquareType.OCCUPIED || board[k][j] == SquareType.OCCUPIED;
						for (int dr = 0; dr < DR.length && !attacked; dr++)
							for (int dc = 0; dc < DC.length && !attacked; dc++) {
								int ii = i + DR[dr]*k;
								int jj = j + DC[dc]*k;
								if (ii >= 0 && ii < n && jj >= 0 && jj < n && board[ii][jj] == SquareType.OCCUPIED)
									attacked = true;
							}
					}
					
					board[i][j] = attacked? SquareType.ATTACKED : SquareType.NOT_ATTACKED;
				}
		
		updateUI();
	}
	
	/**
	 * Updates the UI.
	 */
	private void updateUI() {
		int p = 0;
		for (Component comp : boardUI.getComponents()) {
			int i = p / n;
			int j = p % n;
			p++;
			
			JLabel square = (JLabel) comp;
			if (i % 2 == j % 2)
				square.setBackground(Color.WHITE);
			else
				square.setBackground(Color.GRAY);
			
			if (board[i][j] == SquareType.OCCUPIED)
				square.setIcon(new ImageIcon(getClass().getResource("queen.png")));
			else
				square.setIcon(null);
			if (board[i][j] == SquareType.NOT_ATTACKED)
				square.setBorder(BorderFactory.createLineBorder(Color.GREEN, 2));
			else
				square.setBorder(null);
		}
	}
	
	/**
	 * Sets the board size.
	 * @param boardSize The new board size.
	 */
	public void setBoardSize(int boardSize) {
		n = boardSize;
		board = new SquareType[n][n];
		
		boardSizeUI.setValue(n);
		boardUI.setLayout(new GridLayout(n, n, 0, 0));
		
		boardUI.removeAll();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				board[i][j] = SquareType.NOT_ATTACKED;
				
				JLabel square = new JLabel();
				square.setOpaque(true);
				boardUI.add(square);

				final int row = i;
				final int column = j;
				square.addMouseListener(new MouseAdapter() {
					@Override
					public void mouseClicked(MouseEvent e) {
						selectSquare(row, column);
					}
				});
			}
		
		setSize(n*105, n*105 + boardSizeUI.getHeight());
		updateUI();
	}

	/**
	 * Entry point for the program.
	 * @param args Ignored.
	 */
	public static void main(String[] args) {
		QueenAttacker attacker = new QueenAttacker();
		attacker.init();
		attacker.setBoardSize(8);
	}
	
}
