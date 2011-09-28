/*
 * Stats.h
 *
 *  Created on: Jun 3, 2011
 *      Author: Moises Osorio
 */

#ifndef STATS_H_
#define STATS_H_

#include <vector>
#include "individual.h"
#include "config.h"

using namespace std;

class Stats {
public:
	Stats(RepresentationType representationType);
	virtual ~Stats();
	
	void analyzePopulation(vector<Individual *> population);
	void incrementGeneration();
	void incrementMutations();
	void incrementCrossovers();
	void print();
	void printFinal();
	double getVisitedSearchSpace();
	
private:
	int generation;
	int mutations;
	int crossovers;
	double averageFx;
	double minFx;
	double maxFx;
	Individual *bestIndividual;
	int populationSize;
	RepresentationType representationType;
	int violatingCount;

	int totalCrossovers;
	int totalMutations;
	
};

#endif /* STATS_H_ */
