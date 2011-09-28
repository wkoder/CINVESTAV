package mx.cinvestav.josorio.gosimulator.artificialintelligence;

import java.util.Arrays;
import java.util.Random;

import mx.cinvestav.josorio.gosimulator.GoSimulator;
import mx.cinvestav.josorio.gosimulator.PlayerSimulator;
import mx.cinvestav.josorio.gosimulator.player.GNUGoPlayer;
import mx.cinvestav.josorio.gosimulator.player.SmartPlayer;

import ec.EvolutionState;
import ec.Individual;
import ec.Problem;
import ec.simple.SimpleFitness;
import ec.simple.SimpleProblemForm;
import ec.vector.DoubleVectorIndividual;

/**
 * Implementation of the Fitness function for the Go Game pProblem.
 * @author Moises Osorio
 */
public class GoGameProblem extends Problem implements SimpleProblemForm {

	private static final long serialVersionUID = -6033031378094404106L;
	
	// Starting best individual with a fitness of 0.5384615384615384 against GNUGo.
	public static final double[] bestIndividual = new double[]{4.248674942631921, 3.0623103186362166, 6.819058493935774, 4.448226828913478, 6.783539067286669, 5.755145396130157, 6.987252649229128, 4.647837367989746, 0.9692326722378919, 0.3146319946895668, 2.6044866170364607, 5.252375880420662, 2.4808347522660306, 2.072086595495149, 0.6648364878130842, 2.220960896960672, 0.8396049711889478, 5.7541345769983785, 1.6745063420131054, 3.740727323532985, 0.7591513782872454, 3.3307439538483496, 6.572515222661049, 5.9190114575940465, 2.3953847612301433, 5.94060471474714, 0.3191713749163204, 1.6374205223084313};
	public static double bestFitness = 0.5384615384615384;
	public static PlayerSimulator opponent;

	public GoGameProblem() {
		
	}
	
	public static void setOpponent(PlayerSimulator opponent) {
		GoGameProblem.opponent = opponent;
	}
	
	@Override
	public void evaluate(EvolutionState state, Individual ind, int subpopulation, int threadnum) {
		if (ind.evaluated)
			return;
		
		ind.evaluated = true;
		
		long start = System.currentTimeMillis();
		
		DoubleVectorIndividual ind2 = (DoubleVectorIndividual) ind;
		double fitnessValue = -1;
		while (fitnessValue < 0) {
			try {
				if (opponent == PlayerSimulator.SMART)
					fitnessValue = evaluateAgainstSmartPlayer(ind2.genome, 10);
				else if (opponent == PlayerSimulator.GNUGO)
					fitnessValue = evaluateAgainstGNUGoPlayer(ind2.genome, 10);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		
		long time = System.currentTimeMillis() - start;
		
		SimpleFitness fitness = (SimpleFitness) ind2.fitness;
		fitness.setFitness(state, (float) fitnessValue, false);
		
		if ((opponent == PlayerSimulator.SMART && fitnessValue > 0.5) || 
				(opponent == PlayerSimulator.GNUGO && fitnessValue > bestFitness)) { // Save the best
			bestFitness = fitnessValue;
			for (int i = 0; i < ind2.genomeLength(); i++)
				bestIndividual[i] = ind2.genome[i];
			
			System.out.println("New best individual:");
			System.out.println("Fitness(w) = " + fitnessValue + ". Generated in " + time + " ms. From generation " + state.generation + ".");
			System.out.println("	" + Arrays.toString(ind2.genome));
			System.out.println();
		}
	}
	
	private void applyWeights(double[] w) {
		SmartPlayer.setWeights(Arrays.copyOfRange(w, 0, 9), Arrays.copyOfRange(w, 9, w.length));
	}

	/**
	 * Creates a game between {@link SmartPlayer} and {@link SmartPlayer} to get the fitness value.
	 * @param w
	 * @return
	 */
	public double evaluateAgainstSmartPlayer(double[] w, int repetitions) {
		double sum = 0;
		for (int r = 0; r < repetitions; r++) {
			GoSimulator simulator = new GoSimulator();
			simulator.startSimulation(opponent, PlayerSimulator.SMART, 19);
			for (int i = 0; i < 200; i++) {
				if (i % 2 == 0) // Black's turn
					applyWeights(bestIndividual);
				else // White's turn
					applyWeights(w);
				
				simulator.makeTurn();
			}
			
			// Adds 1 and 2 to prevent false indicators
			int[] scores = simulator.getScores(true);
			sum += (scores[1] + 1) / (double)(scores[1] + scores[0] + 2);
		}
		
		return sum / repetitions;
	}
	
	/**
	 * Creates a game between {@link SmartPlayer} and {@link GNUGoPlayer} to get the fitness value.
	 * @param w
	 * @return
	 */
	public double evaluateAgainstGNUGoPlayer(double[] w, int repetitions) {
		double sum = 0;
		for (int r = 0; r < repetitions; r++) {
			GoSimulator simulator = new GoSimulator();
			simulator.startSimulation(PlayerSimulator.GNUGO, PlayerSimulator.SMART, 19);
			for (int i = 0; i < 200; i++)
				simulator.makeTurn();
			
			int[] scores = simulator.getScores(true);
			sum += (scores[1] + 1) / (double)(scores[1] + scores[0] + 2); // We'd like to crash him!
		}
		
		return sum / repetitions;
	}
	
	public static void main(String[] args) {
		long start = System.currentTimeMillis();
		
		GoGameProblem eval = new GoGameProblem();
		double[] w = new double[28];
		Random r = new Random();
		for (int i = 0; i < w.length; i++)
			w[i] = r.nextDouble();
		System.out.println("Fitness(w) = " + eval.evaluateAgainstSmartPlayer(w, 1));

		long end = System.currentTimeMillis();
		System.out.println("Fitness function took " + (end - start) + " ms.");
	}
}
