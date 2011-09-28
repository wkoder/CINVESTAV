/*
 * DifferentialEvolution.h
 *
 *  Created on: Aug 21, 2011
 *      Author: Moises Osorio
 */

#ifndef DIFFERENTIALEVOLUTION_H_
#define DIFFERENTIALEVOLUTION_H_

class DifferentialEvolution {
public:
	DifferentialEvolution();
	virtual ~DifferentialEvolution();
	
	double solve(double *xs, int n, int maxGenerations, int populationSize, double crossover, 
			double mutation, double randomSeed, double (*bounds)[2], double (*F)(double *x));
	
};

#endif /* DIFFERENTIALEVOLUTION_H_ */
