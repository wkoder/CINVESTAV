package mx.cinvestav.josorio.algorithms;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

/**
 * Finds all the paths from a node a to a node b in a given graph.
 * @author Moises Osorio
 */
public class Paths {

	public Paths() {
		
	}
	
	/**
	 * Computes the maximum flow from a starting node to a goal node.
	 * See http://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm for more information.
	 * @param s Starting node
	 * @param t Goal node
	 * @param cap Capacity matrix, each (i,j) gives the flow capacity from node i to j
	 * @return The maximum flow
	 */
	private int[][] fordFulkerson(int s, int t, int[][] cap) {
		int n = cap.length;
		int[] prev = new int[n];
		int[][] fnet = new int[n][n];
	    int[] q = new int[n];
	    
	    for (int i = 0; i < n; i++)
	    	Arrays.fill(fnet[i], 0, n, 0);
	    
	    int flow = 0;
	    while (true) {
	    	int qf = 0;
	    	int qb = 0;
	    	Arrays.fill(prev, 0, n, -1);

	    	// find an augmenting path
	        prev[q[qb++] = s] = -2;
	        while( qb > qf && prev[t] == -1 )
	            for( int u = q[qf++], v = 0; v < n; v++ )
	                if( prev[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v] )
	                    prev[q[qb++] = v] = u;
	        
	        // see if we're done
	        if (prev[t] == -1)
	        	break;
	        
	        // get the bottleneck capacity
	        int bot = 0x7FFFFFFF; // Infinity
	        for (int v = t, u = prev[v]; u >= 0; v = u, u = prev[v])
	            bot = Math.min(bot, cap[u][v] - fnet[u][v] + fnet[v][u]);
	        
	        // update the flow network
	        for (int v = t, u = prev[v]; u >= 0; v = u, u = prev[v])
	            fnet[u][v] += bot;
	        
	        flow += bot;
	    }
	    
	    return fnet;
	}
	
	/**
	 * Gets the paths computed by Ford-Fulkerson from current to goal.
	 * @param net Network flow
	 * @param n Original number of nodes.
	 * @return The list of paths.
	 */
	private List<List<Integer>> getPaths(int[][] net, int start, int goal, int n) {
		List<List<Integer>> paths = new ArrayList<List<Integer>>();
		for (int i = 0; i < n; i++)
			if (net[n + start][i] > 0) {
				List<Integer> path = getPath(net, i, goal, n);
				path.add(start);
				Collections.reverse(path);
				paths.add(path);
			}
		
		return paths;
	}
	
	/**
	 * Gets the path form the current node to the goal node (must be only one).
	 * @param net Network flow
	 * @param current Current node
	 * @param goal Goal node
	 * @param n Original number of nodes
	 * @return The path from current to goal in reverse order.
	 */
	private List<Integer> getPath(int[][] net, int current, int goal, int n) {
		if (current == goal) {
			List<Integer> path = new ArrayList<Integer>();
			path.add(current);
			return path;
		}
		
		for (int i = 0; i < n; i++)
			if (net[n + current][i] > 0) { // Must be 1
				List<Integer> path = getPath(net, i, goal, n);
				path.add(current);
				return path;
			}
		
		throw new RuntimeException("Something went wrong! No path from " + current + " to " + goal);
	}
	
	/**
	 * Finds all the paths from a to b within the adjacency matrix adj given.
	 * @param a Starting node
	 * @param b Goal node
	 * @param adj Adjacency matrix
	 * @return The list of paths
	 */
	public List<List<Integer>> findPaths(int a, int b, boolean[][] adj) {
		int n = adj.length;
		int[][] cap = new int[2*n][2*n]; // Capacity matrix. Each node has input and output nodes in the modified graph.
		for (int i = 0; i < n; i++) {
			cap[i][n + i] = 1; // Restrict flow from input to output of i
			for (int j = 0; j < n; j++)
				if (adj[i][j])
					cap[n + i][j] = 1; // Restrict flow from output i to input j
		}
		
		// Call Ford-Fulkerson to solve the new problem. n+a = output a, b = input b
		int[][] net = fordFulkerson(n+a, b, cap);
		return getPaths(net, a, b, n);
	}
	
	/**
	 * Computes all the paths from a starting node to a goal node, given a adjacency matrix of 0's and 1's.
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt(); // Number of nodes
		int a = scan.nextInt(); // Starting node
		int b = scan.nextInt(); // Goal node
		
		boolean[][] adj = new boolean[n][n];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				adj[i][j] = scan.nextInt() == 1; // Exists a direct path from i to j
		
		Paths p = new Paths();
		List<List<Integer>> paths = p.findPaths(a, b, adj);
		System.out.println(paths.size()); // Number of paths
		for (List<Integer> path : paths) {
			System.out.print(path.size()); // Path length
			for (Integer v : path) // Each node in the path
				System.out.print(" " + v);
			System.out.println();
		}
	}
	
}
