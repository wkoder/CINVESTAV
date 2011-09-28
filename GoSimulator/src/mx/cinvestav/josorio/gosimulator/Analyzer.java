package mx.cinvestav.josorio.gosimulator;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;

import mx.cinvestav.josorio.gosimulator.player.PlayerType;

public class Analyzer {

	/**
	 * Directional delta.
	 */
	public static final int[] DX = {0, -1, 0, 1};
	public static final int[] DY = {-1, 0, 1, 0};
	public static final int INF = 1 << 28;
	public static final double[] CONSTANTS = new double[19];
	
	private int n;
	private PlayerType type;
	private PlayerType[][] board;
	private int[][] chains;
	private int[] chainLength;
	private int[][][] distance;
	private int[] libertyCount;
	private int[][][] nearestChain;
	private int turnsTaken;
	private int chainCount;
	
	public Analyzer(int n) {
		this.n = n;
		chains = new int[n][n];
		chainLength = new int[n*n];
		distance = new int[n][n][2];
		libertyCount = new int[n*n];
		nearestChain = new int[n][n][2];
	}

	/**
	 * Prints the current board.
	 */
	public void printBoard() {
		System.out.print("  ");
		for (int i = 0; i < n; i++)
			System.out.print(" " + (char)('A' + (i >= 8 ? i+1 : i)));
		System.out.println();
		
		for (int i = 0; i < n; i++) {
			System.out.print((n-i < 10? " " : "") + (n-i));
			for (int j = 0; j < n; j++)
				System.out.print(" " + (board[i][j] == PlayerType.BLACK ? "X" : (board[i][j] == PlayerType.WHITE ? "0" : ".")));
			System.out.println();
		}
	}

	/**
	 * Gets the current board.
	 * @return
	 */
	public PlayerType[][] getBoard() {
		return board;
	}
	
	/**
	 * Gets the liberty count of (x,y).
	 * @param x
	 * @param y
	 * @return
	 */
	public int getLibertyCount(int x, int y) {
		return libertyCount[chains[x][y]];
	}
	
	/**
	 * Gets all the positions that belong to the same chain as (x,y).
	 * @param x
	 * @param y
	 * @return
	 */
	public List<Pair> getChain(int x, int y) {
		List<Pair> chain = new ArrayList<Pair>();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (chains[i][j] == chains[x][y])
					chain.add(new Pair(i, j));
		
		return chain;
	}

	/**
	 * Gets the territory utility for the given position.
	 * @param x
	 * @param y
	 * @return
	 */
	public double getTerritoryUtility(int x, int y) {
		double dist = CONSTANTS[0] * Math.min(distance[x][y][0], distance[x][y][1]);
		return dist;
	}
	
	/**
	 * Gets the length of the chain the position belongs to.
	 * @param x
	 * @param y
	 * @return
	 */
	public int getChainLength(int x, int y) {
		return chainLength[chains[x][y]];
	}
	
	/**
	 * Gets the offensive utility for the given position.
	 * @param x
	 * @param y
	 * @return
	 */
	public double getOffensiveUtility(int x, int y) {
		int enemyDist = distance[x][y][1 - type.ordinal()];
		if (enemyDist == INF)
			return CONSTANTS[1];
		
		int friendDist = distance[x][y][type.ordinal()];
		if (friendDist == INF)
//			return 7.0 - Math.log(getChainLength(x, y));
			return CONSTANTS[2] * getChainLength(x, y);
		
		int enemyChain = nearestChain[x][y][1 - type.ordinal()];
		int enemyLib = libertyCount[enemyChain];
		if (enemyDist >= CONSTANTS[3] || enemyLib >= CONSTANTS[4])
//		if (enemyDist >= 4)
			return CONSTANTS[5];

//		if (friendDist >= 4)
//			return 4 - enemyDist;
		
//		return 14 - enemyDist - friendDist;

		if (enemyDist == 1)
			if (enemyLib == 1)
				return CONSTANTS[6];
			else if (enemyLib == 2)
				return CONSTANTS[7];
			else if (enemyLib == 3)
				return CONSTANTS[8];
//			return 7.0 / enemyLib;
//			return 7.0 - Math.log(enemyLib);
		
		return CONSTANTS[9] / enemyDist;
//		return 14 - enemyDist - friendDist;
//		return Math.max(0, 7.0 - enemyDist);
	}
	
	/**
	 * Gets the defensive utility for the given position.
	 * @param x
	 * @param y
	 * @return
	 */
	public double getDefensiveUtility(int x, int y) {
		if (isSuicide(x, y))
			return -INF;
		
		int enemyDist = distance[x][y][1 - type.ordinal()];
		if (enemyDist == INF)
			return CONSTANTS[10]; // Our eye!
		
		int[] adjChains = {-1, -1, -1, -1};
		int lessFree = INF;
		int moreFree = 0;
		int unionChainCount = 0;
		for (int i = 0; i < DX.length; i++) {
			int xx = x + DX[i];
			int yy = y + DY[i];
			if (xx >= 0 && xx < n && yy >= 0 && yy < n && board[xx][yy] == type) {
				adjChains[i] = chains[xx][yy];
				boolean ok = true;
				for (int j = 0; j < i; j++)
					ok &= adjChains[i] != adjChains[j];
				
				if (ok) {
					unionChainCount++;
					lessFree = Math.min(lessFree, libertyCount[adjChains[i]]);
					moreFree = Math.max(moreFree, libertyCount[adjChains[i]]);
				}
			}
		}
		
//		System.out.println(unionChainCount + " " + lessFree + " " + moreFree);
//		if (unionChainCount == 0) {
//			int friendDist = getFriendDistance(x, y);
//			if (friendDist <= 3)
//				return 5.0 - friendDist;
//			return 7.0 / friendDist;
//		}
		
		if (unionChainCount >= CONSTANTS[11] && lessFree <= CONSTANTS[12] && moreFree >= CONSTANTS[13])
			return CONSTANTS[14] - lessFree;
		
		if (unionChainCount < CONSTANTS[11] && lessFree <= CONSTANTS[12])
			return CONSTANTS[15] - lessFree;
		
		if (moreFree < CONSTANTS[13])
			return CONSTANTS[16] - moreFree;
		
		if (unionChainCount >= CONSTANTS[11])
			return CONSTANTS[17] - lessFree;
		
		return CONSTANTS[18];
	}

	/**
	 * Process the board.
	 * @param board
	 */
	public void processBoard(PlayerType[][] board, PlayerType type, int turnsTaken) {
		this.board = board;
		this.type = type;
		this.turnsTaken = turnsTaken;
		
		detectChains();
		computeDistance();
	}
	
	public int getTurnsTaken() {
		return turnsTaken;
	}
	
	public int getDistanceToType(int x, int y, PlayerType type) {
		return distance[x][y][type.ordinal()];
	}
	
	public int getEnemyDistance(int x, int y) {
		return distance[x][y][1 - type.ordinal()];
	}
	
	public int getFriendDistance(int x, int y) {
		return distance[x][y][type.ordinal()];
	}
	
	public int getChainID(int x, int y) {
		return chains[x][y];
	}

	/**
	 * Tells if the given position is a suicide position.
	 * @param x X coordinate.
	 * @param y Y coordinate.
	 * @return If (x,y) is a suicide position.
	 */
	public boolean isSuicide(int x, int y) {
		if (board[x][y] != PlayerType.EMPTY)
			throw new RuntimeException("Position (" + x + ", " + y + ") not empty.");
		
		board[x][y] = type;
		
		Analyzer next = new Analyzer(n);
		next.processBoard(board, type == PlayerType.BLACK? PlayerType.WHITE : PlayerType.BLACK, turnsTaken+1);
		boolean suicide = next.getLibertyCount(x, y) == 0;
		
		board[x][y] = PlayerType.EMPTY;
		return suicide;
	}
	
	/**
	 * Computes the distance between nodes.
	 */
	private void computeDistance() {
		Queue<Integer> q = new LinkedList<Integer>();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				Arrays.fill(distance[i][j], INF);
				Arrays.fill(nearestChain[i][j], -1);
				if (board[i][j] != PlayerType.EMPTY) {
					q.offer(i);
					q.offer(j);
					int t = board[i][j].ordinal();
					q.offer(t);
					
					distance[i][j][t] = 0;
					nearestChain[i][j][t] = chains[i][j];
				}
			}
		
		while (!q.isEmpty()) {
			int x = q.poll();
			int y = q.poll();
			int t = q.poll();
			for (int k = 0; k < DX.length; k++) {
				int xx = x + DX[k];
				int yy = y + DY[k];
				if (xx >= 0 && xx < n && yy >= 0 && yy < n && distance[xx][yy][t] == INF) {
					distance[xx][yy][t] = distance[x][y][t] + 1;
					nearestChain[xx][yy][t] = nearestChain[x][y][t];
					if (board[xx][yy].ordinal() != 1-t) { // If not the enemy propagate the distance
						q.offer(xx);
						q.offer(yy);
						q.offer(t);
					}
				}
			}
		}
	}
	
	/**
	 * Detects chains.
	 */
	private void detectChains() {
		chainCount = 0;
		for (int i = 0; i < n; i++)
			Arrays.fill(chains[i], -1);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (chains[i][j] < 0) {
					Queue<Integer> q = new LinkedList<Integer>();
					q.offer(i);
					q.offer(j);
					chains[i][j] = chainCount;
					chainLength[chainCount] = 1;
					Set<Pair> liberties = new HashSet<Pair>();
					
					while (!q.isEmpty()) {
						int x = q.poll();
						int y = q.poll();
						for (int k = 0; k < DX.length; k++) {
							int xx = x + DX[k];
							int yy = y + DY[k];
							if (xx >= 0 && xx < n && yy >= 0 && yy < n && (chains[xx][yy] < 0 || board[xx][yy] == PlayerType.EMPTY))
								if (chains[xx][yy] == -1 && board[xx][yy] == board[i][j]) {
									chains[xx][yy] = chainCount;
									chainLength[chainCount]++;
									q.offer(xx);
									q.offer(yy);
								} else if (board[xx][yy] == PlayerType.EMPTY)
									liberties.add(new Pair(xx, yy));
						}
					}
					
					libertyCount[chainCount] = liberties.size();
					chainCount++;
				}
	}
	
}
