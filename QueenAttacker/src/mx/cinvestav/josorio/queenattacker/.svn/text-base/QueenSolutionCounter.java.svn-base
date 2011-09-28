package mx.cinvestav.josorio.queenattacker;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

public class QueenSolutionCounter {
	
	private int n;
	private int[][] count;
	
	public QueenSolutionCounter() {
		
	}
	
	public int[][] count(int n) {
		this.n = n;
		count = new int[n][n];
		count(0, new int[n]);
		
		Map<Integer, Integer> counter = new HashMap<Integer, Integer>();
		Set<Map<Integer, Integer>> vectors = new HashSet<Map<Integer,Integer>>();
		findSolutionsAndShowCount(0, new int[n], counter, vectors);
		for (int k : counter.keySet())
			System.out.println(k + " = " + counter.get(k));
		for (Map<Integer, Integer> vector : vectors)
			System.out.println("Vector: " + vector);
		
		return count;
	}
	
	private void count(int pos, int[] sol) {
		if (pos == n) {
			for (int i = 0; i < n; i++)
				count[i][sol[i]]++;
			return;
		}
		
		next:
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < pos; j++)
				if (i == sol[j] || pos-j == Math.abs(i - sol[j]))
					continue next;
			
			sol[pos] = i;
			count(pos+1, sol);
		}
	}
	
	private void findSolutionsAndShowCount(int pos, int[] sol, Map<Integer, Integer> counter, Set<Map<Integer, Integer>> vectors) {
		if (pos == n) {
			Map<Integer, Integer> vector = new TreeMap<Integer, Integer>();
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (count[i][j] > 0)
						vector.put(count[i][j], 0);
			
			int sum = 0;
			for (int i = 0; i < n; i++) {
				int k = count[i][sol[i]];
				sum += k;
				vector.put(k, vector.get(k)+1);
			}
			
			Integer k = counter.get(sum);
			if (k == null)
				k = 0;
			
			counter.put(sum, k+1);
			vectors.add(vector);
			return;
		}
		
		next:
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < pos; j++)
				if (i == sol[j] || pos-j == Math.abs(i - sol[j]))
					continue next;
			
			sol[pos] = i;
			findSolutionsAndShowCount(pos+1, sol, counter, vectors);
		}
	}
	
	public static void main(String[] args) {
		final int N = 8;
		QueenSolutionCounter counter = new QueenSolutionCounter();
		int[][] count = counter.count(N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				System.out.print(count[i][j] + " ");
			System.out.println();
		}
	}
}
