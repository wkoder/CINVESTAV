/*
 * main.c
 *
 *  Created on: Nov 4, 2010
 *      Author: Moises Osorio
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "wh.h"
#include "genetic.h"


long long getTime() { // Calcula el numero de microsegundos desde la epoca
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec*1000000LL + tv.tv_usec;
}

int main()
{
	struct individual *temp;
	float Rseed;
	long long start, duration;
	int nonlinearity;

	printf("Heuristic search for Boolean Functions\n\n");

	printf("Number of variables of the boolean functions to find: ");
	scanf("%d", &realsize);
	printf("Desired non-linearity: ");
	scanf("%d", &nonlinearity);

	printf("\nHeuristic search parameters:\n");
	printf("Population size (recommended 100): ");
	scanf("%d", &popsize);
	printf("Maximum number of generations (recommended > 100): ");
	scanf("%d", &Gmax);
	printf("Crossover probability (recommended 0.7): ");
	scanf("%f", &Pc);
	printf("Mutation rate (recommended 0.007): ");
	scanf("%f", &Pm);
	printf("Random seed: ");
	scanf("%f", &Rseed);

//	Pm = 1.0 / 128.0; // Mutation rate
//	Pc = 0.7; // Probability of crossover
//	Gmax = 100; // Maximum number of generations
//	Rseed = 0.1337; // Random seed
//	realsize = 7; // Number of variables of the functions to find
//	popsize = 100; // Population size

	start = getTime();

	/* Perform the previous memory allocation */
	memory_allocation();

	/* Initialize random number generator */
	randomize();

	nmutation = 0;
	ncross = 0;
	bestfit.fitness = 0.0;
	bestfit.generation = 0;

	/* Initialize the populations and report statistics */
	initialize_pop();
	statistics(oldpop);
	for (gen = 0; gen < Gmax; gen++) {
		/* Create a new generation */
		generation();

		/* Compute fitness statistics on new populations */
		statistics(newpop);

		/* Advance the generation */
		temp = oldpop;
		oldpop = newpop;
		newpop = temp;

		if (bestfit.fitness + 1E-6 >= nonlinearity)
			break;
	}

	duration = getTime() - start;
	printf("\nExecution time: %llu.%3llu s\n", duration / 1000000, (duration / 1000) % 1000);

	writeBestFit();

	free_all();
	return 0;
}

int test()
{
	int n = 5, i;
	unsigned int mask;
	int b[1 << n];
	int w[1 << n];
	double p[1 << n];
	int b2[1 << n];

	for (mask = 0; (unsigned long long)mask+1000 < 1LL << (1 << n); mask++) {
		if (bitcount(mask) != 1 << (n-1))
			continue; // Not balanced

		for (i = 0; i < 1 << n; i++)
			b[i] = (mask >> i) & 1;

		walshHadamardTransform(b, w, n);

		if (getBooleanDeviation(w, n) > 1e-9)
			printf("PANIC with mask %d!\n", mask);

		if ((w[0] == 0) != (bitcount(mask) == (1 << (n-1))))
			printf("PANIC with mask %d! %d %d\n", mask, w[0], bitcount(mask));

		int nl = getNonLinearity(w, n);
		if (nl >= 8) {
			int m = getCorrelationImmunity(w, n);
			if (m > 0) {
				printf("f = ");
				printBooleanToHex(b, n);
				printf("\nnl = %d\n", nl);
				printf("m = %d\n", m);
				printf("\n");
			}
		}

		inverseWalshHadamardTransform(w, p, n);
		for (i = 0; i < 1 << n; i++)
			b2[i] = (int) (p[i] + 0.5);

		getBooleanForm(b2, b2, n);

		for (i = 0; i < 1 << n; i++)
			if (b[i] != b2[i]) {
				printf("PANIC with mask %d!\n", mask);
				break;
			}
	}

	return 0;
}
