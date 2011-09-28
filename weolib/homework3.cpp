/*
 * geneticalgorithmmain.cpp
 *
 *  Created on: Jun 3, 2011
 *      Author: Moises Osorio
 */

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "geneticalgorithm.h"
#include <string.h>

#define N 2
//#define _NDEBUG

int a(int i, int j) {
	switch (i == 0 ? j % 5 : j / 5) {
		case 0: return -32;
		case 1: return -16;
		case 2: return 0;
		case 3: return 16;
		case 4: return 32;
	}
	
	throw "j value is greater than 24";
}

/**
 * Function to minimize.
 */
double f(double *x)
{
	double sum, f;
	int i, j;
	
	sum = 1.0 / 500.0; // 1 / K
	for (j = 0; j < 25; j++) { // sum f_j^-1
		f = j+1; // c_j
		for (i = 0; i < N; i++) // sum (x_i - a_ij)^6
			f += pow(x[i] - a(i,j), 6.0);
		
		sum += 1.0 / f;
	}
	
	return - 1.0 / sum; // Maximizing!
}

/**
 * Entry point for the program.
 */
int main(int argc, char **argv) {
	FILE *fp;
	GeneticAlgorithm ga;
	double xs[N];
	int precision[N];
	double bounds[N][2];
	double mutationRate, crossoverProbability, randomSeed;
	int maxGenerations, populationSize;
//	char outputFile[1024];
	
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
	fp = NULL;
//	printf("Output file: ");
//	scanf("%[^\n]", outputFile);
//	
//	if (strlen(outputFile) > 0) {
//		if ((fp = freopen(outputFile, "w", stdout)) == NULL) {
//			printf("Cannot open file %s\n", outputFile);
//			exit(1);
//		}
//	}
	
	if (randomSeed < 0) { // "Random" random seed
		randomSeed = time(0);
		while (randomSeed >= 1)
			randomSeed /= 10;
		printf("Using random seed: %.10lf\n", randomSeed);
	}
	
	// Set value bounds and required precision
	for (int i = 0; i < N; i++) {
		bounds[i][0] = -50;
		bounds[i][1] = 50;
		precision[i] = 3;
	}
	
	// Solve problem
#ifdef GRAY_REPR
	ga.setRepresentationType(RepresentationType::GRAY_REPRESENTATION);
#else
#ifdef INTEGER_REPR
	ga.setRepresentationType(RepresentationType::INTEGER_REPRESENTATION);
#else
#error Undefined representation
#endif
#endif
	ga.setSelectionType(SelectionType::STOCHASTIC_REMAINDER_SELECTION);
	ga.setCrossoverType(CrossoverType::UNIFORM_CROSSOVER);
	ga.solve(xs, N, populationSize, bounds, precision, mutationRate, crossoverProbability, maxGenerations, randomSeed, f);
	double fxs = f(xs);
	
	printf("x* = (%.3f, %.3f)\nf(x*) = %.3f\n", xs[0], xs[1], -fxs);
	
	if (fp != NULL)
		fclose(fp);
	
	return EXIT_SUCCESS;
}
