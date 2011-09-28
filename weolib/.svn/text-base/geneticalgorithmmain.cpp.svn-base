/*
 * geneticalgorithmmain.cpp
 *
 *  Created on: Jun 3, 2011
 *      Author: Moises Osorio
 */

#include <stdio.h>
#include <stdlib.h>
#include "geneticalgorithm.h"

#define N 4

/**
 * Function to minimize.
 */
double f(double *x)
{
	double fx = 0, temp;
	
	temp = 10 * (x[1] - x[0]*x[0]);
	fx += temp*temp;
	temp = 1 - x[0];
	fx += temp*temp;
	temp = x[3] - x[2]*x[2];
	fx += 90 * temp*temp;
	temp = 1 - x[2];
	fx += temp*temp;
	temp = x[1] + x[3] - 2;
	fx += 10 * temp*temp;
	temp = x[1] - x[3];
	fx += 0.1 * temp*temp;
	
	return -fx; // Maximize!
}

/**
 * Entry point for the program.
 */
int main(int argc, char **argv) {
	GeneticAlgorithm ga;
	double xs[N];
	int precision[N];
	double bounds[N][2];
	double mutationRate, crossoverProbability, randomSeed;
	int maxGenerations, populationSize;

	printf("Population size: ");
	scanf("%d", &populationSize);
	printf("Maximum number of generations: ");
	scanf("%d", &maxGenerations);
	printf("Mutation rate (0..1): ");
	scanf("%lf", &mutationRate);
	printf("Crossover probability (0..1): ");
	scanf("%lf", &crossoverProbability);
	printf("Random seed: ");
	scanf("%lf", &randomSeed);
	
	if (randomSeed < 0) { // "Random" random seed
		randomSeed = time(0);
		while (randomSeed >= 1)
			randomSeed /= 10;
		printf("Using random seed: %.10lf\n", randomSeed);
	}
	
	// Set value bounds and required precision
	for (int i = 0; i < N; i++) {
		bounds[i][0] = -20;
		bounds[i][1] = 20;
		precision[i] = 10;
	}
	
	// Solve problem
	ga.solve(xs, N, populationSize, bounds, precision, mutationRate, crossoverProbability, maxGenerations, randomSeed, f);
	double fxs = f(xs);
	
	printf("x* = (%.10f, %.10f, %.10f, %.10f)\nf(x*) = %.10f\n", xs[0], xs[1], xs[2], xs[3], fxs);
	
	return EXIT_SUCCESS;
}
