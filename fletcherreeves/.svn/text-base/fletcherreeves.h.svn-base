/*
 * fletcherreeves.h
 *
 *  Created on: May 26, 2011
 *      Author: Moises Osorio
 */

#ifndef WEOLIB_H_
#define WEOLIB_H_

class FletcherReeves {
public:
	FletcherReeves();
	virtual ~FletcherReeves();

	// Minimizes a function f, with gradient function fp, starting from x0 with tolerances e1, e2 and e3 
	// and N dimensions. Solution in saved in xs.
	int solve(double *xs, double *x0, double e1, double e2, double e3, int N, double (*f)(double *x), 
			void (*fp)(double *dx, double *x));

private:
	// Calculates the 2-norm of x.
	double norm2(double *x, int N);
	// Moves x towards direction in a factor of stepSize. Result in x2. 
	double nextLocation(double *x2, double *x, double *direction, double stepSize, int N, 
			double (*f)(double *x));
	// Finds the step size for x in the given direction to x is minimized at least by e.
	double findStepSize(double *x, double *direction, double e, int N, double (*f)(double *x));
};

#endif /* WEOLIB_H_ */
