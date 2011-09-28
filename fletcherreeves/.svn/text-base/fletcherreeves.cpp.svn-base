/*
 * fletcherreeves.cpp
 *
 *  Created on: May 26, 2011
 *      Author: Moises Osorio
 */

#include "fletcherreeves.h"
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

FletcherReeves::FletcherReeves()
{

}

FletcherReeves::~FletcherReeves()
{

}

double FletcherReeves::nextLocation(double *x2, double *x, double *direction, double stepSize, int N, double (*f)(double *x))
{
	for (int i = 0; i < N; i++)
		x2[i] = x[i] + stepSize*direction[i];
	return f(x2);
}

double FletcherReeves::findStepSize(double *x, double *direction, double e, int N, double (*f)(double *x))
{
	double *xr = new double[N];
	double *xl = new double[N];
	double fx = f(x);
	double l = 0, r = 0.5, fr;

	int iter = 0;
	do { // Find right value of ternary search
		iter++;
		r *= 2;
		fr = nextLocation(xr, x, direction, r, N, f);
		if (fr < fx+e) // The first we find
			return r;
	} while (fr < fx && iter <= 20);

	// Ternary search
	while (r-l > 1e-9) { // Range too big and not minimized
		double ll = (l*2 + r) / 3;
		double rr = (l + r*2) / 3;
		double fll = nextLocation(xl, x, direction, ll, N, f);
		double frr = nextLocation(xr, x, direction, rr, N, f);
		if (frr < fx) // The first we find
			return rr;
		if (fll < fx) // The first we find
			return ll;

		if (fll < frr)
			r = rr;
		else
			l = ll;
	}

	return l;
}

double FletcherReeves::norm2(double *x, int N)
{
	double norm = 0;
	for (int i = 0; i < N; i++)
		norm += x[i]*x[i];
	return sqrt(norm);
}

int FletcherReeves::solve(double *xs, double *x0, double e1, double e2, double e3, int N,
		double (*f)(double *x), void (*fp)(double *dx, double *x))
{
	double *s = new double[N];
	double *x1 = new double[N];
	double *dx1 = new double[N];
	double *x2 = new double[N];
	double *dx2 = new double[N];
	double *xdiff = new double[N];
	double fx1, stepSize;

	// Step 2
	fp(dx2, x0);
	for (int i = 0; i < N; i++)
		s[i] = -dx2[i];

	// Step 3
	stepSize = findStepSize(x0, s, e1, N, f);
	fx1 = nextLocation(x1, x0, s, stepSize, N, f);
	fp(dx1, x1);
	for (int i = 0; i < N; i++)
		xdiff[i] = x1[i] - x0[i];

	int iterations = 0;
	while (norm2(xdiff, N)/norm2(x1, N) > e2 && norm2(dx1, N) > e3) { // Step 6 <-
		iterations++;
		// Step 4
		double temp = norm2(dx1, N) / norm2(dx2, N);
		temp *= temp;
		for (int i = 0; i < N; i++)
			s[i] = -dx1[i] + temp*s[i];

		// Step 5
		stepSize = findStepSize(x1, s, e1, N, f);
		fx1 = nextLocation(x2, x1, s, stepSize, N, f);

		for (int i = 0; i < N; i++) {
			xdiff[i] = x1[i] - x2[i];
			x1[i] = x2[i];
			dx2[i] = dx1[i];
		}

		fp(dx1, x1);
	}

	for (int i = 0; i < N; i++)
		xs[i] = x1[i];
	return iterations;
}
