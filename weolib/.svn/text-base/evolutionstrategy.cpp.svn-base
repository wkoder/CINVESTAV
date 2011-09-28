/*
 * EvolutionStrategy.cpp
 *
 *  Created on: May 27, 2011
 *      Author: Moises Osorio
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#include "evolutionstrategy.h"
#include "rand.h"

using namespace std;

EvolutionStrategy::EvolutionStrategy() {

}

EvolutionStrategy::~EvolutionStrategy() {

}

int EvolutionStrategy::solve(double *xs, double* bounds, double initialDelta, int gmax, int n, double (*f)(double *x))
{
	double C = 0.821137;
	double delta[10000];
	double *x2 = new double[n];
	this->n = n;

	// Generate starting solution.
	initrandom(time(0));
	for (int i = 0; i < n; i++)
		xs[i] = bounds[0] + randreal()*(bounds[1] - bounds[0]);
	double fx = f(xs);
	delta[0] = initialDelta;
	
	int gen = 0;
	int success = 0;
	int ps = 0;
	while (gen < gmax) {
		for (int i = 0; i < n; i++) {
			double rand = N(0, 1);
			if (rand > 0)
				x2[i] = xs[i] + rand * min(delta[gen], (bounds[1]-xs[i])/4);
			else
				x2[i] = xs[i] + rand * min(delta[gen], (xs[i]-bounds[0])/4);
			
			// Just in case
			if (x2[i] < bounds[0])
				x2[i] = bounds[0];
			if (x2[i] > bounds[1])
				x2[i] = bounds[1];
		}
		
		double fx2 = f(x2);
		if (fx2 < fx) {
			success++;
			fx = fx2;
			for (int i = 0; i < n; i++)
				xs[i] = x2[i];
		}
		
		gen++;
		printf("Generation %d\n    x = (%.9f, %.9f)\n    f(x) = %.9f\n", gen, xs[0], xs[1], fx);

		if (gen % (10*n) == 0) // Update ps
			ps = success;
		if (gen % n == 0) {
			delta[gen] = delta[gen - n];
			if (ps*5 > gen)
				delta[gen] /= C;
			else if (ps*5 < gen)
				delta[gen] *= C;
		} else
			delta[gen] = delta[gen - 1];
	}
	
	return gen;
}
