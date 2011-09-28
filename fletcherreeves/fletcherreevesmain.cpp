//============================================================================
// Name        : fletcherreevesmain.cpp
// Author      : Moises Osorio
// Version     : 1.0
// Description : Entry point for the Fletcher-Reeves algorithm.
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fletcherreeves.h"

double E;
double A1;
double A2;
double S;
double L;
double H;
double THETA;
double W;

// Function to minimize
double f(double *x)
{
	double cosB = S / (2*L);
	double sinB = H / L;
	double temp1 = x[0]*cosB + x[1]*sinB;
	double temp2 = -x[0]*cosB + x[1]*sinB;
	return E*A1/(2*L) * temp1*temp1 + E*A2/(2*L) * temp2*temp2 - W*x[0]*cos(THETA) - W*x[1]*sin(THETA);
}

// Gradient of the function to minimize
void fp(double *dx, double *x)
{
	double cosB = S / (2*L);
	double sinB = H / L;
	double temp1 = x[0]*cosB + x[1]*sinB;
	double temp2 = -x[0]*cosB + x[1]*sinB;
	dx[0] = E*A1/L * temp1 * cosB + E*A2/L * temp2 * -cosB - W*cos(THETA);
	dx[1] = E*A1/L * temp1 * sinB + E*A2/L * temp2 * sinB - W*sin(THETA);
}

// Entry point of the program
int main(void) {
	FletcherReeves solver;
	double e1, e2, e3;
	double x0[2];
	double xs[2];

	// Read parameters
	printf("E (N/m^2) = ");
	scanf("%lf", &E);
	printf("s (m) = ");
	scanf("%lf", &S);
	printf("h (m) = ");
	scanf("%lf", &H);
	printf("A1 (m^2) = ");
	scanf("%lf", &A1);
	printf("A2 (m^2) = ");
	scanf("%lf", &A2);
	printf("Theta (degrees) = ");
	scanf("%lf", &THETA);
	printf("W (m) = ");
	scanf("%lf", &W);

	THETA = THETA * (M_PI / 180); // To radians
	L = sqrt(H*H + 0.25*S*S);

	printf("x0 = ");
	scanf("%lf %lf", x0, x0+1);
	printf("Tolerances (3) = ");
	scanf("%lf %lf %lf", &e1, &e2, &e3);

	int iterations = solver.solve(xs, x0, e1, e2, e3, 2, &f, &fp);
	double fxs = f(xs);
	printf("x* = (%.9f, %.9f)\nf(x*) = %.9f\nFound in %d iterations.", xs[0], xs[1], fxs, iterations);

	return EXIT_SUCCESS;
}
