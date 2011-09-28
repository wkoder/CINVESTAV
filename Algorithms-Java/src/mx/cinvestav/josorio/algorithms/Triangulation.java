package mx.cinvestav.josorio.algorithms;

import java.util.Arrays;
import java.util.Scanner;

/**
 * Solves the triangulation problem.
 * @author Moises Osorio
 */
public class Triangulation {
	
	private static final double INF = 1e9;

	public Triangulation() {
		
	}
	
	/**
	 * Generates a regular n-gon.
	 * @param n Number of vertices
	 * @param r Radius of the polygon
	 * @return The regular n-gon
	 */
	public Point[] generateRegularPolygon(int n, double r) {
		double angle = Math.PI*2 / n; // Angle between lines cutting the polygon
		Point[] poly = new Point[n];
		poly[0] = new Point(r, 0); // Start point
		double currentAngle = 0;
		for (int i = 1; i < n; i++) { // Generate all points
			currentAngle += angle;
			double x = r * Math.cos(currentAngle);
			double y = r * Math.sin(currentAngle);
			poly[i] = new Point(x, y);
		}
		
		return poly;
	}
	
	/**
	 * Computes the distance between two points.
	 * @param a Point A.
	 * @param b Point B.
	 * @return The distance between A and B.
	 */
	private double length(Point a, Point b) {
		return Math.hypot(a.x - b.x, a.y - b.y);
	}
	
	/**
	 * Computes the triangulation cost of points A, B and C.
	 * @param a Point A.
	 * @param b Point B.
	 * @param c Point C.
	 * @return The triangulation cost.
	 */
	private double f(Point a, Point b, Point c) {
		return length(a, b) + length(b, c) + length(c, a);
	}
	
	/**
	 * Calculates the triangulation of the polygon.
	 * @param polygon Polygon to triangulate.
	 * @param P Contains the lower cost of triangulation.
	 * @param J Describes the triangulation
	 */
	public void triangulate(Point[] polygon, double[][] P, int[][] J) {
		int n = polygon.length;
		for (int i = 0; i < n; i++)
			Arrays.fill(P[i], 0); // Clear P, no need to clear J
		
		for (int j = 1; j < n; j++) {
			for (int t1 = 1; t1 <= n-j; t1++) { // For each pair of points
				int t3 = j - 1 + t1;
				int t2 = -1;
				double t2cost = INF;
				for (int x = t1; x <= t3; x++) { // Look to minimize the cost
					double xcost = P[t1][x-1] + P[(x+1)%n][t3] + f(polygon[t1-1], polygon[x], polygon[(t3+1)%n]);
					if (xcost < t2cost) {
						t2 = x; // Point that minimizes
						t2cost = xcost; // Lower cost
					}
				}
				
				J[t1][t3] = t2; // Remember what we encountered
				P[t1][t3] = t2cost;
				//P[t1][t3] = P[t1][t2] + P[(t2+1)%n][t3] + f(polygon[t1-1], polygon[t2], polygon[(t3+1)%n]);
			}
		}
	}
	
	/**
	 * Represents a Point (vertex).
	 * @author Moises Osorio
	 */
	static class Point {
		private double x, y;
		public Point(double x, double y) {
			this.x = x;
			this.y = y;
		}
		@Override
		public String toString() {
			return x + " " + y;
		}
	}
	
	/**
	 * Entry point. Reads n pair of doubles describing points of a polygon.
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		
		int n = scanner.nextInt(); // Number of points
		if (n < 3)
			throw new RuntimeException("No polygon can be formed from " + n + " points.");
		
		Point[] polygon = new Point[n];
		for (int i = 0; i < n; i++) { // Read all n points.
			double x = scanner.nextDouble();
			double y = scanner.nextDouble();
			polygon[i] = new Point(x, y);
		}
		
		double[][] P = new double[n][n];
		int[][] J = new int[n][n];

		Triangulation triangulation = new Triangulation();
		triangulation.triangulate(polygon, P, J);
		
		System.out.println(P[n-1][n-1]);
	}
}
