//============================================================================
// Name        : weolib.cpp
// Author      : Moises Osorio
// Version     :
// Copyright   : 
// Description : Entry point for the EVOP implementation.
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include "evop.h"

// Function to minimize
double f(double *x)
{
	double temp1 = x[0] + 2*x[1] - 7;
	double temp2 = 2*x[0] + x[1] - 5;
	return temp1*temp1 + temp2*temp2;
}

// Entry point of the program
int main(void) {
	Evop evop;
	double delta[2];
	double x0[2];
	double xs[2];
	double e;

	// Read parameters
	printf("Tolerance: ");
	scanf("%lf", &e);
	printf("Delta: ");
	scanf("%lf %lf", delta, delta+1);
	printf("x0 = ");
	scanf("%lf %lf", x0, x0+1);
	
	int iterations = evop.solve(xs, x0, delta, e, 2, f);
	double fxs = f(xs);
	printf("x* = (%.9f, %.9f)\nf(x*) = %.9f\nFound in %d iterations.", xs[0], xs[1], fxs, iterations);

	return EXIT_SUCCESS;
}
