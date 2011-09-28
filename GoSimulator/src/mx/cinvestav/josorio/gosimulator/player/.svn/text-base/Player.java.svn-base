package mx.cinvestav.josorio.gosimulator.player;

import mx.cinvestav.josorio.gosimulator.Analyzer;
import mx.cinvestav.josorio.gosimulator.Pair;

/**
 * Interface for Go Players.
 * @author Moises Osorio
 */
public abstract class Player {
	
	protected int n;
	protected PlayerType type;
	protected Analyzer analysis;
	
	public Player() {
		
	}
	
	/**
	 * Initializes the player.
	 * @param n Board size.
	 * @param turn The turn the player has.
	 */
	public void init(int n, PlayerType turn) {
		this.n = n;
		type = turn;
	}
	
	/**
	 * Calls the player to make its turn.
	 * @param board
	 * @return
	 */
	public Pair makeTurn(PlayerType[][] board, int turnsTaken) {
		analysis = new Analyzer(n);
		analysis.processBoard(cloneBoard(board), type, turnsTaken);
		return doMakeTurn(analysis);
	}

	/**
	 * Clones the current board.
	 * @return
	 */
	protected PlayerType[][] cloneBoard(PlayerType[][] board) {
		PlayerType[][] clone = new PlayerType[n][n];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				clone[i][j] = board[i][j];
		
		return clone;
	}
	
	/**
	 * Method to implement subclasses to make their turns.
	 * @return
	 */
	protected abstract Pair doMakeTurn(Analyzer analysis);
	
	public void stop() {
		
	}
}
