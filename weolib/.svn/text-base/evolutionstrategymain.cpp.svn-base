//============================================================================
// Name        : evolutionstrategymain.cpp
// Author      : Moises Osorio
// Version     :
// Copyright   : 
// Description : Entry point for the Evolution Strategy implementation.
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include "evolutionstrategy.h"

// Function to minimize
double f(double *x)
{
	double temp1 = 1.5 - x[0] * (1 - x[1]);
	double temp2 = 2.25 - x[0] * (1 - x[1]*x[1]);
	double temp3 = 2.625 - x[0] * (1 - x[1]*x[1]*x[1]);
	return temp1*temp1 + temp2*temp2 + temp3*temp3;
}

// Entry point of the program
int main(void) {
	EvolutionStrategy solver;
	double xs[2];
	double bounds[2];
	int gmax;

	printf("Gmax: ");
	scanf("%d", &gmax);
	
	bounds[0] = -5;
	bounds[1] = 10;
	
	int iterations = solver.solve(xs, bounds, 3.0, gmax, 2, f);
	double fxs = f(xs);
	printf("x* = (%.9f, %.9f)\nf(x*) = %.9f\nFound in %d iterations.", xs[0], xs[1], fxs, iterations);
	
	return EXIT_SUCCESS;
}
