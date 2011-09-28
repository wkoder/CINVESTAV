/*
 * evop.h
 *
 *  Created on: May 26, 2011
 *      Author: Moises Osorio
 */

#ifndef EVOP_H_
#define EVOP_H_

class Evop {
public:
	Evop();
	virtual ~Evop();

	// Minimizes f starting from x0 with the given delta and tolerance e in N dimensions. result in xs.
	int solve(double *xs, double *x0, double *delta, double e, int N, double (*f)(double *x));

private:
	// Calculates the 2-norm of x
	double norm2(double *x, int N);
};

#endif /* EVOP_H_ */
