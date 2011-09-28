package mx.cinvestav.josorio.gosimulator;

import static mx.cinvestav.josorio.gosimulator.player.PlayerType.BLACK;
import static mx.cinvestav.josorio.gosimulator.player.PlayerType.EMPTY;
import static mx.cinvestav.josorio.gosimulator.player.PlayerType.WHITE;

import java.text.DecimalFormat;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.Queue;

import mx.cinvestav.josorio.gosimulator.player.GNUGoPlayer;
import mx.cinvestav.josorio.gosimulator.player.Player;
import mx.cinvestav.josorio.gosimulator.player.PlayerType;
import mx.cinvestav.josorio.gosimulator.player.RandomPlayer;
import mx.cinvestav.josorio.gosimulator.player.SmartPlayer;

public class GoSimulator {

	/**
	 * Different kind of players.
	 */
	public static final PlayerSimulator[] PLAYERS = new PlayerSimulator[]{PlayerSimulator.HUMAN, PlayerSimulator.RANDOM, PlayerSimulator.SMART, PlayerSimulator.GNUGO};
	/**
	 * Directional delta.
	 */
	private static final int[] DX = {0, -1, 0, 1};
	private static final int[] DY = {-1, 0, 1, 0};
	
	/**
	 * Value of N.
	 */
	private int n;
	/**
	 * Current board configuration.
	 */
	private PlayerType[][] board;
	/**
	 * Who owns the next turn.
	 */
	private PlayerType turn;
	/**
	 * Players.
	 */
	private Player playerWhite, playerBlack;
	/**
	 * Turns already taken.
	 */
	private int turnsTaken;
	/**
	 * Indicates if the last player passed his turn.
	 */
	private boolean lastPassed;
	/**
	 * If dead stones are going to be removed.
	 */
	private boolean removeDeadStones;
	/**
	 * Score for players.
	 */
	private int whiteScore;
	private int blackScore;
	/**
	 * Analysis of the board.
	 */
	private Analyzer analysis;
	/**
	 * Tells if both players passed.
	 */
	private boolean bothPassed;
	
	public GoSimulator() {
		removeDeadStones = true;
	}
	
	public int getBoardSize() {
		return n;
	}
	
	public PlayerType[][] getBoard() {
		return board;
	}
	
	public PlayerType getTurn() {
		return turn;
	}
	
	public Player getPlayerBlack() {
		return playerBlack;
	}
	
	public Player getPlayerWhite() {
		return playerWhite;
	}
	
	/**
	 * Sets the board size.
	 * @param boardSize The new board size.
	 */
	public void startSimulation(PlayerSimulator blackPlayer, PlayerSimulator whitePlayer, int boardSize) {
		lastPassed = false;
		n = boardSize;
		board = new PlayerType[n][n];
		turn = EMPTY;
		analysis = new Analyzer(n);
		
		for (int i = 0; i < n; i++)
			Arrays.fill(board[i], EMPTY);
		
		playerBlack = createPlayer(blackPlayer, BLACK);
		playerWhite = createPlayer(whitePlayer, WHITE);
		turn = BLACK;
		blackScore = 0;
		whiteScore = 0;
		turnsTaken = 0;
		analysis.processBoard(board, turn, turnsTaken);
	}
	
	public void changePlayers(PlayerSimulator blackPlayer, PlayerSimulator whitePlayer) {
		if (!isPlayerTypeCorrect(playerBlack, blackPlayer))
			if (blackPlayer == PlayerSimulator.GNUGO)
				throw new RuntimeException("GNU Go must take the game from the start.");
			else
				playerBlack = createPlayer(blackPlayer, BLACK);
		if (!isPlayerTypeCorrect(playerWhite, whitePlayer))
			if (whitePlayer == PlayerSimulator.GNUGO)
				throw new RuntimeException("GNU Go must take the game from the start.");
			else
				playerWhite = createPlayer(whitePlayer, WHITE);
	}
	
	private Player createPlayer(PlayerSimulator player, PlayerType type) {
		Player p = null;
		switch (player) {
			case HUMAN: p = null; break;
			case RANDOM: p = new RandomPlayer(); break;
			case SMART: p = new SmartPlayer(); break;
			case GNUGO: p = new GNUGoPlayer(); break;
			default: throw new RuntimeException("Unknown player " + player);
		}
		
		if (p != null)
			p.init(n, type);
		return p;
	}
	
	private boolean isPlayerTypeCorrect(Player player, PlayerSimulator type) {
		switch (type) {
			case HUMAN: return player == null;
			case RANDOM: return player instanceof RandomPlayer;
			case SMART: return player instanceof SmartPlayer;
			case GNUGO: return player instanceof GNUGoPlayer;
		}
		
		return false;
	}
	
	public boolean makeTurn() {
		Pair xy = null;
		if (turn == WHITE && playerWhite != null)
			xy = playerWhite.makeTurn(board, turnsTaken);
		else if (turn == BLACK && playerBlack != null)
			xy = playerBlack.makeTurn(board, turnsTaken);
		
		if (xy ==  null)
			return makeTurn(-1, -1, turn);
		else
			return makeTurn(xy.getA(), xy.getB(), turn);
	}
	
	/**
	 * Makes a turn for a player. Defines the winner and loser of the game.
	 * @param x Row position.
	 * @param y Column position.
	 * @param player Player who made the turn.
	 */
	public boolean makeTurn(int x, int y, PlayerType player) {
		if (player != turn)
			return false;
		
		if (x >= 0 && y >= 0) {
			if (board[x][y] != PlayerType.EMPTY) {
				analysis.printBoard();
				throw new RuntimeException("Move (" + x + ", " + y + ") not valid by " + player);
			}
			
			lastPassed = false;
			board[x][y] = player;

			analysis.processBoard(board, turn, turnsTaken);
			if (removeDeadStones)
				removeCaptured();
		} else
			System.out.println("Player " + turn + " is passing.");
		
		turnsTaken++;
		turn = turn == WHITE? BLACK : WHITE; // Switch turn
		analysis.processBoard(board, turn, turnsTaken);

		boolean bothPassed = false;
		if (x < 0 || y < 0)
			if (!lastPassed)
				lastPassed = true;
			else
				bothPassed = true;
		else
			lastPassed = false;
		
		if (bothPassed || turnsTaken >= n*n/2)
			return false;
		
		return true;
	}
	
	/**
	 * Removes the captured pieces of both players.
	 */
	private void removeCaptured() {
		PlayerType[] targets = {PlayerType.values()[1 - turn.ordinal()], turn};
		for (PlayerType target : targets)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (board[i][j] == target && analysis.getLibertyCount(i, j) == 0) {
//						System.out.println("Removing chain " + analysis.getChainID(i, j) + " of (" + i + ", " + j + ")");
						PlayerType type = board[i][j];
						for (Pair stone : analysis.getChain(i, j)) {
							board[stone.getA()][stone.getB()] = PlayerType.EMPTY;
							
							if (type == BLACK)
								whiteScore++;
							else
								blackScore++;
						}
						
						analysis.processBoard(board, turn, turnsTaken); // Reset analysis
					}
	}
	
	/**
	 * Gets the score of both players.
	 * @return Both players scores.
	 */
	public int[] getScores(boolean addTerritory) {
		int[] scores = new int[2];
		scores[0] = blackScore;
		scores[1] = whiteScore;
		
		if (addTerritory)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (board[i][j] == PlayerType.EMPTY)
						for (int k = 0; k < 2; k++)
							if (analysis.getDistanceToType(i, j, PlayerType.values()[k]) == Analyzer.INF)
								scores[1 - k]++;
		
		return scores;
	}
	
	/**
	 * Gets the region that is surrounded by this player.
	 * @param player Player.
	 * @return The surrounding region.
	 */
	@SuppressWarnings("unused")
	private boolean[][] getSurroundingRegion(PlayerType player) {
		boolean[][] v = new boolean[n][n];
		Queue<Integer> q = new LinkedList<Integer>();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (board[i][j] == player) {
					v[i][j] = true;
					q.offer(i);
					q.offer(j);
				}
		
		while (!q.isEmpty()) { // Flood fill algorithm O(n^2)
			int x = q.poll();
			int y = q.poll();
			for (int dx = 0; dx < DX.length; dx++)
				for (int dy = 0; dy < DY.length; dy++) {
					int xx = x + DX[dx];
					int yy = y + DY[dy];
					if (xx >= 0 && yy >= 0 && xx < n && yy < n && !v[xx][yy] && (board[xx][yy] == player || board[xx][yy] == EMPTY)) {
						v[xx][yy] = true;
						q.offer(xx);
						q.offer(yy);
					}
				}
		}
		
		return v;
	}
	
	public boolean getBothPassed() {
		return bothPassed;
	}

	/**
	 * Gets the information of the given position.
	 * @param x
	 * @param y
	 * @return
	 */
	public String getInfo(int x, int y) {
		String desc = "Position: (" + x + ", " + y + ")\n";
		
		desc += "\nDistance\n";
		int blackDist = analysis.getDistanceToType(x, y, PlayerType.BLACK);
		int whiteDist = analysis.getDistanceToType(x, y, PlayerType.WHITE);
		desc += "   From black: " + (blackDist == Analyzer.INF? "INF" : blackDist) + "\n";
		desc += "   From white: " + (whiteDist == Analyzer.INF? "INF" : whiteDist) + "\n";
		if (board[x][y] != PlayerType.EMPTY) {
			desc += "\nChain\n";
			desc += "   Chain ID: " + analysis.getChainID(x, y) + "\n";
			desc += "   Liberty count: " + analysis.getLibertyCount(x, y) + "\n";
		} else {
			DecimalFormat format = new DecimalFormat("0.00");
			desc += "\nUtility\n";
			desc += "   Territory: " + format.format(analysis.getTerritoryUtility(x, y)) + "\n";
			desc += "   Defensive: " + format.format(analysis.getDefensiveUtility(x, y)) + "\n";
			desc += "   Offensive: " + format.format(analysis.getOffensiveUtility(x, y)) + "\n";
		}
		
		return desc;
	}
	
}
