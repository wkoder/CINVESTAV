package mx.cinvestav.josorio.gosimulator.artificialintelligence;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;
import java.util.Scanner;

import mx.cinvestav.josorio.gosimulator.PlayerSimulator;

import ec.Evolve;

/**
 * Use a genetic heuristic to search all the space for the best values for weights and 
 * internal factors of utility functions needed by the simulator.
 * @author Moises Osorio
 *
 */
public class GeneticAlgorithm {

	public GeneticAlgorithm() {
		
	}
	
	public double[] readAndSearch() {
		Scanner scan = new Scanner(System.in);
		
		System.out.println("Genetic Algorithm to optimize the performance of the Go Simulator.");
		System.out.print("Number of generations? (recommended = 100) ");
		int generations = scan.nextInt();
		System.out.print("Size of population? (recommended = 100) ");
		int populationSize = scan.nextInt();
		PlayerSimulator opponent = null;
		while (opponent == null) {
			System.out.print("Against GNUGoPlayer or SmartPlayer? (gnu/smart) ");
			String type = scan.next();
			if (type.equalsIgnoreCase("gnu"))
				opponent = PlayerSimulator.GNUGO;
			else if (type.equalsIgnoreCase("smart"))
				opponent = PlayerSimulator.SMART;
		}
		
		return search(generations, populationSize, opponent);
	}
	
	@SuppressWarnings("deprecation")
	public double[] search(int generations, int populationSize, PlayerSimulator opponent) {
		Properties props = new Properties();
		props.setProperty("breedthreads", "1");
		props.setProperty("evalthreads", "1");
//		props.setProperty("seed.0", "4357");
		props.setProperty("seed.0", "time");
		props.setProperty("state", "ec.simple.SimpleEvolutionState");
		props.setProperty("pop", "ec.Population");
		props.setProperty("init", "ec.simple.SimpleInitializer");
		props.setProperty("finish", "ec.simple.SimpleFinisher");
		props.setProperty("breed", "ec.simple.SimpleBreeder");
		props.setProperty("eval", "ec.simple.SimpleEvaluator");
		props.setProperty("stat", "ec.simple.SimpleStatistics");
		props.setProperty("exch", "ec.simple.SimpleExchanger");
		props.setProperty("generations", "" + generations);
		props.setProperty("quit-on-run-complete", "true");
		props.setProperty("checkpoint", "true");
		props.setProperty("prefix", "ec");
		props.setProperty("checkpoint-modulo", "1");
		props.setProperty("stat.file", "$stats.out");
		props.setProperty("pop.subpops", "1");
		props.setProperty("pop.subpop.0", "ec.Subpopulation");
		props.setProperty("pop.subpop.0.size", "" + populationSize);
		props.setProperty("pop.subpop.0.duplicate-retries", "0");
		props.setProperty("pop.subpop.0.species", "ec.vector.FloatVectorSpecies");
		props.setProperty("pop.subpop.0.species.ind", "ec.vector.DoubleVectorIndividual");
//		props.setProperty("pop.subpop.0.species", "ec.vector.VectorSpecies");
//		props.setProperty("pop.subpop.0.species.ind", "ec.vector.BitVectorIndividual");
		props.setProperty("pop.subpop.0.species.genome-size", "28");
		props.setProperty("pop.subpop.0.species.min-gene", "0");
		props.setProperty("pop.subpop.0.species.max-gene", "7");
		props.setProperty("pop.subpop.0.species.crossover-type", "two");
//		props.setProperty("pop.subpop.0.species.crossover-prob", "0.7");
		props.setProperty("pop.subpop.0.species.mutation-type", "reset");
		props.setProperty("pop.subpop.0.species.mutation-prob", "0.007");
		props.setProperty("pop.subpop.0.species.fitness", "ec.simple.SimpleFitness");
		props.setProperty("pop.subpop.0.species.pipe", "ec.vector.breed.VectorMutationPipeline");
		props.setProperty("pop.subpop.0.species.pipe.source.0", "ec.vector.breed.VectorCrossoverPipeline");
		props.setProperty("pop.subpop.0.species.pipe.source.0.source.0", "ec.select.TournamentSelection");
		props.setProperty("pop.subpop.0.species.pipe.source.0.source.1", "ec.select.TournamentSelection");
		props.setProperty("select.tournament.size", "2");
		props.setProperty("eval.problem", "mx.cinvestav.josorio.gosimulator.artificialintelligence.GoGameProblem");
		
		File file = new File("ga_gosimulator.properties");
		try {
			FileOutputStream out = new FileOutputStream(file);
			props.save(out, "Auto generated file by GoSimulator. Needed to apply a Genetic Algorithm");
			out.flush();
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		GoGameProblem.setOpponent(opponent);
		Evolve.main(new String[]{"-file", file.getAbsolutePath()});
		
		return GoGameProblem.bestIndividual;
	}
}
