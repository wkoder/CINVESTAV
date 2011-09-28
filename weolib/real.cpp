/*
 * real.cpp
 *
 *  Created on: Jun 28, 2011
 *      Author: Moises Osorio
 */

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "geneticalgorithm.h"
#include <string.h>

#ifdef F1

#define N 20
#define NG 2
#define NH 0

double f(double *x) {
	double sum = 0;
	for (int i = 0; i < N; i++)
		sum += pow(cos(x[i]), 4);
	double m = 2;
	for (int i = 0; i < N; i++)
		m *= pow(cos(x[i]), 2);
	sum -= m;
	
	double d = 0;
	for (int i = 0; i < N; i++)
		d += (i+1) * x[i] * x[i];
	d = sqrt(d);
	
	sum = abs(sum / d);
	return sum;
}

double g1(double *x) {
	double v = 1;
	for (int i = 0; i < N; i++)
		v *= x[i];
	return 0.75 - v;
}

double g2(double *x) {
	double v = 0;
	for (int i = 0; i < N; i++)
		v += x[i];
	return v - 7.5*N;
}

double (*g[NG])(double *x) = {g1, g2};
double (*h[NH])(double *x);

#else
#ifdef F2

#define N 4
#define NG 2
#define NH 3

double f(double *x) {
	double sum = 0;
	sum = 3*x[0] + 0.000001*pow(x[0], 3) + 2*x[1] + (0.000002/3) * pow(x[1], 3);
	return sum;
}

double g1(double *x) {
	return -x[3] + x[2] - 0.55;
}

double g2(double *x) {
	return -x[2] + x[3] - 0.55;
}

double h3(double *x) {
	return 1000*sin(-x[2] - 0.25) + 1000*sin(-x[3] - 0.25) + 894.8 - x[0];
}

double h4(double *x) {
	return 1000*sin(x[2] - 0.25) + 1000*sin(x[2] - x[3] - 0.25) + 894.8 - x[1];
}

double h5(double *x) {
	return 1000*sin(x[3] - 0.25) + 1000*sin(x[3] - x[2] - 0.25) + 1294.8;
}

double (*g[NG])(double *x) = {g1, g2};
double (*h[NH])(double *x) = {h3, h4, h5};

#else
#ifdef F3

#define N 5
#define NG 0
#define NH 3

double f(double *x) {
	double sum = 0;
	sum = 1;
	for (int i = 0; i < N; i++)
		sum *= x[i];
	sum = exp(sum);
	return sum;
}

double h1(double *x) {
	double v = 0;
	for (int i = 0; i < N; i++)
		v += x[i] * x[i];
	return v - 10;
}

double h2(double *x) {
	return x[1]*x[2] - 5*x[3]*x[4];
}

double h3(double *x) {
	return x[0]*x[0]*x[0] + x[1]*x[1]*x[1] + 1;
}

double (*g[NG])(double *x);
double (*h[NH])(double *x) = {h1, h2, h3};

#endif
#endif
#endif

/**
 * Entry point for the program.
 */
int main(int argc, char **argv) {
	GeneticAlgorithm ga;
	double xs[N];
	double mutationRate, crossoverProbability, randomSeed, faithDegree;
	double bounds[N][2];
	int maxGenerations, populationSize;
	
	printf("Population size: ");
	scanf("%d", &populationSize);
	printf("Maximum number of generations: ");
	scanf("%d", &maxGenerations);
	printf("Mutation rate (0..1): ");
	scanf("%lf", &mutationRate);
	printf("Crossover probability (0..1): ");
	scanf("%lf", &crossoverProbability);
	printf("Faith degree (0..1): ");
	scanf("%lf", &faithDegree);
	printf("Random seed: ");
	scanf("%lf", &randomSeed);
	
#ifdef F1
	for (int i = 0; i < N; i++) {
		bounds[i][0] = 0;
		bounds[i][1] = 10;
	}
#else
#ifdef F2
	bounds[0][0] = 0;
	bounds[0][1] = 1200;
	bounds[1][0] = 0;
	bounds[1][1] = 1200;
	bounds[2][0] = -0.55;
	bounds[2][1] = 0.55;
	bounds[3][0] = -0.55;
	bounds[3][1] = 0.55;
#else
#ifdef F3
	for (int i = 0; i < 2; i++) {
		bounds[i][0] = -2.3;
		bounds[i][1] = 2.3;
	}
	for (int i = 2; i < N; i++) {
		bounds[i][0] = -3.2;
		bounds[i][1] = 3.2;
	}
#endif
#endif
#endif
	
	// Solve problem
	ga.setCrossoverProbability(crossoverProbability);
	ga.setMutationProbability(mutationRate);
	ga.setElitism(true);
#ifdef F1
	ga.setMinimizer(false);
#else
	ga.setMinimizer(true);
#endif
	ga.setFaithDegree(faithDegree);
	ga.setRepresentationType(RepresentationType::REAL_REPRESENTATION);
	ga.setSelectionType(SelectionType::BOLTZMANN_SELECTION);
	ga.setCrossoverType(CrossoverType::SIMULATED_BINARY_CROSSOVER);
	ga.setMutationType(MutationType::PARAMETER_BASED_MUTATION);
	ga.solve(xs, N, populationSize, bounds, NULL, maxGenerations, randomSeed, f, g, NG, h, NH);
	double fxs = f(xs);
	
	printf("x* = (%.10f", xs[0]);
	for (int i = 1; i < N; i++)
		printf(", %.10f", xs[i]);
	
	printf(")\nf(x*) = %.10f\n", fxs);
	
	return EXIT_SUCCESS;
}
