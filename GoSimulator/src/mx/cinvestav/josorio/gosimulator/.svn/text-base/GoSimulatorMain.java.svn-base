package mx.cinvestav.josorio.gosimulator;

import java.util.Arrays;

import mx.cinvestav.josorio.gosimulator.artificialintelligence.GeneticAlgorithm;
import mx.cinvestav.josorio.gosimulator.player.SmartPlayer;

/**
 * Entry point for the entire project.
 * @author Moises Osorio
 */
public class GoSimulatorMain {
	
	/**
	 * Shows the usage.
	 */
	private static void showUsage() {
		System.out.println("Usage:");
		System.out.println("	No options	Runs the simulator (default option)");
		System.out.println("	-h, --help	Shows this text");
		System.out.println("	-g, --genetic	Runs the genetic algorithm");
		System.out.println("	-s, --stats	Shows some stats");
	}

	/**
	 * Entry point for the program.
	 * @param args Ignored.
	 */
	public static void main(String[] args) {
		double[] weights = new double[]{6.65848104596551, 4.957420471291955, 0.17173231563992442, 0.14907205865599304, 6.323547765543541, 1.5068879040032532, 0.8940641305602423, 0.14785969480772276, 4.734371318223774, 3.11173559940529, 1.8608270227038601, 6.0965022274967895, 1.4808888295505647, 1.3299579918202524, 2.429446870599028, 6.048371792110123, 0.4626823001880045, 0.2534468218051319, 0.48473695698607366, 1.109547431861428, 6.03288930122038, 2.272852295048402, 6.572515222661049, 5.9190114575940465, 3.108062188861422, 1.2875570920524018, 4.1296463433132224, 3.7640690947920996};
		if (args.length > 0) {
			if (args[0].equals("-h") || args[0].equals("--help")) {
				showUsage();
			} else if (args[0].equals("-g") || args[0].equals("--genetic")) {
				GeneticAlgorithm ga = new GeneticAlgorithm();
				double[] w = ga.readAndSearch();
				System.out.println("The best weights are " + Arrays.toString(w));
			} else if (args[0].equals("-s") || args[0].equals("--stats")) {
				Stats stats = new Stats();
				stats.showStats(weights);
			} else {
				showUsage();
			}
			
			return;
		}
		
		SmartPlayer.setWeights(Arrays.copyOfRange(weights, 0, 9), Arrays.copyOfRange(weights, 9, weights.length));
		
		GoSimulatorUI go = new GoSimulatorUI();
		go.setBoardSize(19);
	}
	
}
