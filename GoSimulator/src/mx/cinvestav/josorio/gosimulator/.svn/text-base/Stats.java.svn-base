package mx.cinvestav.josorio.gosimulator;

import java.text.DecimalFormat;

import mx.cinvestav.josorio.gosimulator.artificialintelligence.GoGameProblem;
import mx.cinvestav.josorio.gosimulator.player.SmartPlayer;

/**
 * Gets some statistics from the current {@link SmartPlayer}.
 * @author Moises Osorio
 */
public class Stats {

	public Stats() {
		
	}
	
	public void showStats(double[] weights) {
		DecimalFormat format = new DecimalFormat("0.####");
		GoGameProblem evaluator = new GoGameProblem();
		for (int i = 0; i < 100; i++) {
			double evaluation = evaluator.evaluateAgainstGNUGoPlayer(weights, 1);
			System.out.print(format.format(evaluation) + " ");
		}
		System.out.println();
	}
}
