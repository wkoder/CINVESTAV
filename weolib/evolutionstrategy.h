/*
 * EvolutionStrategy.h
 *
 *  Created on: May 27, 2011
 *      Author: Moises Osorio
 */

#ifndef EVOLUTIONSTRATEGY_H_
#define EVOLUTIONSTRATEGY_H_

class EvolutionStrategy {
public:
	EvolutionStrategy();
	virtual ~EvolutionStrategy();
	
	// Minimizes f within given bounds for up to gmax iterations.
	int solve(double *xs, double *bounds, double initialDelta, int gmax, int n, double (*f)(double *x));
	
private:
	int n;
};

#endif /* EVOLUTIONSTRATEGY_H_ */
