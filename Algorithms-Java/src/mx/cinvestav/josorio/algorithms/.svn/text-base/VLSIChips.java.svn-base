package mx.cinvestav.josorio.algorithms;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

/**
 * Solves the VLSI chips problem.
 * @author Moises Osorio
 */
public class VLSIChips {

	/**
	 * Number of chips
	 */
	private int n;
	/**
	 * Table of answers
	 */
	private boolean[][] table;
	/**
	 * Tells if chip i is good
	 */
	private boolean[] isGood;
	/**
	 * Random source
	 */
	private Random random;
	
	public VLSIChips() {

	}
	
	/**
	 * Sets a specific answer table.
	 * @param table Answer table.
	 */
	public void setTable(boolean[][] table) {
		n = table.length;
		this.table = table;
	}
	
	/**
	 * Generates the answer table from the number of chips, specifying the good ones.
	 * @param good Number of good chips.
	 * @param n Number of chips.
	 */
	public void generateTable(int good, int n) {
		this.n = n;
		int bad = n - good; // Number of bad chips
		random = new Random(good * 1337 + bad); // Same seed for each good and bad combination

		table = new boolean[n][n];
		isGood = generateGood(good, n);
		for (int i = 0; i < n; i++) {
			table[i][i] = diagnose(i, i);
			for (int j = i+1; j < n; j++) { // Construct answer table
				table[i][j] = diagnose(i, j);
				table[j][i] = diagnose(j, i);
			}
		}
	}
	
	/**
	 * Diagnose chip B using chip A.
	 * @param a Chip A.
	 * @param b Chip B.
	 * @return If chip A diagnoses as good or bad chip B.
	 */
	private boolean diagnose(int a, int b) {
		if (isGood[a])
			return isGood[b];
		
		return random.nextBoolean();
	}
	
	/**
	 * Selects the good chips from the all the chips.
	 * @param good Number of good chips to select.
	 * @param n Number of chips.
	 * @return The array saying what chips are good.
	 */
	private boolean[] generateGood(int good, int n) {
		boolean[] isGood = new boolean[n];
		List<Integer> all = new ArrayList<Integer>();
		for (int i = 0; i < n; i++) // Add all chips
			all.add(i);
		
		for (int i = 0; i < good; i++) {
			int k = random.nextInt(all.size());
			int g = all.get(k); // Choose one random element from all
			isGood[g] = true; // g is good
			all.remove(k); // Remove g as a possibility for next selection
		}
		
		return isGood;
	}
	
	/**
	 * Detects the most probable good chip.
	 * @return A good chip.
	 */
	public int detectGood() {
		int best = -1;
		int bestFriends = 0;
		for (int i = 0; i < n; i++) { // Try each chip
			int count = 0;
			for (int j = 0; j < n; j++) // Count what chips detected it as good, taking into account that this must be reciprocal
				if (table[i][j] && table[j][i])
					count++;
			
			if (count > bestFriends) { // This is a "better" choice
				best = i+1; // 1-based
				bestFriends = count;
			}
		}
		
		return best;
	}
	
	/**
	 * Entry point. Usage:
	 * 		A pair of integers indicating the total number of chips and the number of good ones.
	 * 		A squared data matrix specifying the answer table by 1's and 0's.
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		List<Integer> input = new ArrayList<Integer>();
		while (scan.hasNextInt())
			input.add(scan.nextInt());
		
		VLSIChips chips = new VLSIChips();
		int n;
		if (input.size() == 2) {
			n = input.get(0);
			int good = input.get(1);
			if (n < good)
				throw new RuntimeException("The number of chips should not be greater than the number of good chips.");
			
			chips.generateTable(good, n);
		} else {
			n = (int) Math.round(Math.sqrt(input.size()));
			if (n*n != input.size())
				throw new RuntimeException("Input data is not a squared matrix.");
			
			boolean[][] table = new boolean[n][n];
			for (int i = 0; i < input.size(); i++) {
				if (input.get(i) != 1 && input.get(i) != 0)
					throw new RuntimeException("Answer table contains values different from 0 and 1.");
				
				table[i / n][i % n] = input.get(i) == 1;
			}
			
			chips.setTable(table);
		}
		
		int goodChip = chips.detectGood();
		System.out.println(goodChip);
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				System.out.print(chips.table[i][j]? "1 " : "0 ");
			System.out.println();
		}
		
		if (chips.isGood != null) {
			for (int i = 0; i < n; i++)
				if (chips.isGood[i])
					System.out.print(i + " ");
			System.out.println();
		}
	}
	
}
