package mx.cinvestav.josorio.gosimulator.player;

import java.util.Random;

import mx.cinvestav.josorio.gosimulator.Analyzer;
import mx.cinvestav.josorio.gosimulator.Pair;

/**
 * Smart player for the GO game.
 * @author Moises Osorio
 */
public class SmartPlayer extends Player {
	
	private static final double EPS = 1e-9;
	public static final double[] WEIGHTS = new double[9];
	
	private Random random;
	
	public SmartPlayer() {
		random = new Random();
	}
	
	public static void setWeights(double[] weights, double[] analyzerWeights) {
		for (int i = 0; i < weights.length; i++)
			WEIGHTS[i] = weights[i];
		
		for (int i = 0; i < analyzerWeights.length; i++)
			Analyzer.CONSTANTS[i] = analyzerWeights[i];
	}
	
	private double w(int f, double x) {
		f = Math.min(f, 250);
		double v = WEIGHTS[f*3] * x*x + WEIGHTS[f*3+1] * x + WEIGHTS[f*3+2];
//		switch (f) {
//			case 0: v = x <= 17? 1.0 : 0; break;
//			case 1: v = x <= 17? x / 34.0 : 1.0; break;
//			case 2: v = x <= 17? x / 34.0 : 1.0; break;
//		}
		return Math.min(1, Math.max(0, v));
	}
	
	@Override
	protected Pair doMakeTurn(Analyzer analysis) {
		if (analysis.getTurnsTaken() <= 3) { // Throw in zone 4.7
			int x, y;
			do {
				x = 4 + random.nextInt(4);
				y = 4 + random.nextInt(4);
				if (random.nextBoolean())
					x = 18 - x;
				if (random.nextBoolean())
					y = 18 - y;
			} while (Math.min(analysis.getEnemyDistance(x, y), analysis.getFriendDistance(x, y)) <= 6);
			
			return new Pair(x, y);
		}
		
		int bestX = -1;
		int bestY = -1;
		double bestValue = -1;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (analysis.getBoard()[i][j] == PlayerType.EMPTY) {
					double value = 0;
					
					value += w(0, analysis.getTurnsTaken()) * analysis.getTerritoryUtility(i, j);
					value += w(1, analysis.getTurnsTaken()) * analysis.getDefensiveUtility(i, j);
					value += w(2, analysis.getTurnsTaken()) * analysis.getOffensiveUtility(i, j);
					
					if (value > bestValue + EPS) {
						bestValue = value;
						bestX = i;
						bestY = j;
					}
				}
		
//		printUtilities(bestX, bestY, analysis);
		
		return new Pair(bestX, bestY);
	}
	
	private void printUtilities(int x, int y, Analyzer analysis) {
		System.out.println("(" + x + ", " + y + ") Terr: " + analysis.getTerritoryUtility(x, y) + ", Def: " + analysis.getDefensiveUtility(x, y) + ", Off: " + analysis.getOffensiveUtility(x, y));
	}
	
}
