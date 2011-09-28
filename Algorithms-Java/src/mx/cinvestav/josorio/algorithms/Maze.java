package mx.cinvestav.josorio.algorithms;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Random;
import java.util.Scanner;

/**
 * Solves the maze problem finding the optimal path from a given position to another.
 * @author Moises Osorio
 */
public class Maze {
	
	private static int INF = 1 << 30; // Infininite
	private static final int[] DX = {-1, 0, 1, 0}; // Delta for rows
	private static final int[] DY = {0, -1, 0, 1}; // Delta for columns
	
	private boolean[][] maze; // Maze to use
	private int n; // Length of the squared maze

	public Maze() {
		
	}
	
	/**
	 * Generates a nxn size maze.
	 * @param m Number of obstacles to include in the maze
	 * @param n Maze size
	 * @return The generated maze
	 */
	public boolean[][] generateMaze(int m, int n) {
		this.n = n;
		maze = new boolean[n][n];
		List<Integer> all = new ArrayList<Integer>();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				all.add(i);
				all.add(j);
			}
		
		Random random = new Random();
		for (int i = 0; i < m; i++) {
			int pos = random.nextInt(n*n - i); // Gets a random position
			int x = all.remove(pos << 1);
			int y = all.remove(pos << 1);
			maze[x][y] = true;
		}
		
		return maze;
	}
	
	/**
	 * Prints the generated maze, where a 0 indicates an empty slot and a 1 a wall.
	 */
	public void printMaze() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				System.out.print(maze[i][j]? "1" : "0");
			System.out.println();
		}
	}
	
	/**
	 * Finds the optimal path from (ax, ay) to (bx, by).
	 * @param ax X coordinate value for A
	 * @param ay Y coordinate value for A
	 * @param bx X coordinate value for B
	 * @param by Y coordinate value for B
	 * @return The optimal path from A to B, where 0 = stop, 1 = front, 2 = left, 3 = back, 4 = right.
	 * 		If there's no path the resulting string is empty.
	 */
	public String findOptimalPath(int ax, int ay, int bx, int by) {
		if (ax == bx && ay == by)
			return "0";
		
		int[][] cost = new int[n][n];
		for (int i = 0; i < n; i++)
			Arrays.fill(cost[i], INF);
		
		int[][] directionTo = new int[n][n];
		Queue<Integer> queue = new LinkedList<Integer>();

		boolean done = false;
		directionTo[ax][ay] = -1; // We mark the start
		cost[ax][ay] = 0; // No cost to go to the same block
		queue.add(ax);
		queue.add(ay);
		while (!queue.isEmpty() && !done) {
			int x = queue.poll();
			int y = queue.poll();
			for (int i = 0; i < DX.length; i++) { // Move to each direction
				int xx = x + DX[i];
				int yy = y + DY[i];
				// Is inside the boundaries, not a wall and a minimizer path.
				if (xx >= 0 && xx < n && yy >= 0 && yy < n && !maze[xx][yy] && cost[xx][yy] > cost[x][y] + 1) {
					cost[xx][yy] = cost[x][y] + 1; // Assign new minimized cost
					directionTo[xx][yy] = i; // Assign the direction that took us here
					if (xx == bx && yy == by) { // No need to keep searching, we're already in the final block
						done = true;
						break;
					}
						
					queue.add(xx);
					queue.add(yy);
				}
			}
		}
		
		if (!done) // We didn't get to the goal
			return "";
		
		String path = "";
		int x = bx;
		int y = by;
		while (directionTo[x][y] != -1) { // While is not the start position, move backwards
			path = (directionTo[x][y]+1) + path; // Add the direction index
			int d = directionTo[x][y];
			x -= DX[d]; // Move in the opposite direction
			y -= DY[d];
		}
		
		return path;
	}
	
	/**
	 * Entry point.
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int m = scan.nextInt();
		int n = scan.nextInt();
		if (m > n*n)
			throw new RuntimeException(m + " cannot be greater than " + n + "^2");
		
		Maze maze = new Maze();
		boolean[][] M = maze.generateMaze(m, n);
		maze.printMaze();
		
		int ax = scan.nextInt();
		int ay = scan.nextInt();
		int bx = scan.nextInt();
		int by = scan.nextInt();
		if (M[ax][ay] || M[bx][by])
			throw new RuntimeException("The start and end positions must be empty in the maze.");
		
		System.out.println(maze.findOptimalPath(ax, ay, bx, by));
	}
}
