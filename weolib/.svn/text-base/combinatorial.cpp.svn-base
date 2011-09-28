/*
 * combinatorial.cpp
 *
 *  Created on: Jun 28, 2011
 *      Author: Moises Osorio
 */

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "geneticalgorithm.h"
#include <string.h>

int n;
int **dist;
int **flow;

/**
 * Function to minimize.
 */
double f(int *x)
{
	double sum;
	
	// Verification of x
	for (int i = 0; i < n; i++)
		if (x[i] < 0 || x[i] >= n)
			throw "X is not a permutation!";
		else
			for (int j = 0; j < i; j++)
				if  (x[i] == x[j])
					throw "X is not a permutation";
	sum = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			sum += dist[i][j] * flow[x[i]][x[j]];
	
	return sum;
}

/**
 * Entry point for the program.
 */
int main(int argc, char **argv) {
	GeneticAlgorithm ga;
	int *xs;
	double mutationRate, crossoverProbability, randomSeed, inversionProbability;
	int maxGenerations, populationSize;
	FILE *fp;
	
	// Read costs file
	fp = fopen(COSTS_FILE, "r");
	if (fp == NULL) {
		printf("File %s not found.\n", COSTS_FILE);
		return EXIT_FAILURE;
	}
	
	fscanf(fp, "%d", &n);
	xs = new int[n];
	dist = new int*[n];
	flow = new int*[n];
	for (int i = 0; i < n; i++) {
		dist[i] = new int[n];
		flow[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			fscanf(fp, "%d", &dist[i][j]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			fscanf(fp, "%d", &flow[i][j]);
	
	printf("Population size: ");
	scanf("%d", &populationSize);
	printf("Maximum number of generations: ");
	scanf("%d", &maxGenerations);
	printf("Mutation rate (0..1): ");
	scanf("%lf", &mutationRate);
	printf("Crossover probability (0..1): ");
	scanf("%lf", &crossoverProbability);
	printf("Inversion probability (0..1): ");
	scanf("%lf", &inversionProbability);
	printf("Random seed: ");
	scanf("%lf", &randomSeed);
	
	// Solve problem
	ga.setCrossoverProbability(crossoverProbability);
	ga.setMutationProbability(mutationRate);
	ga.setInversionProbability(inversionProbability);
	ga.setElitism(true);
	ga.setMinimizer(true);
	ga.setRepresentationType(RepresentationType::PERMUTATION_REPRESENTATION);
	ga.setSelectionType(SelectionType::DETERMINISTIC_BINARY_TOURNAMENT_SELECTION);
	ga.setCrossoverType(CrossoverType::PARTIALLY_MAPPED_CROSSOVER);
	ga.setMutationType(MutationType::RECIPROCAL_INTERCHANGE_MUTATION);
	ga.solve(xs, n, populationSize, maxGenerations, randomSeed, f);
	double fxs = f(xs);
	
	printf("x* = (%d", xs[0]);
	for (int i = 1; i < n; i++)
		printf(", %d", xs[i]);
	
	printf(")\nf(x*) = %.0f\n", fxs);
	
	delete [] xs;
	for (int i = 0; i < n; i++) {
		delete [] flow[i];
		delete [] dist[i];
	}
	
	delete [] flow;
	delete [] dist;
	
	return EXIT_SUCCESS;
}
