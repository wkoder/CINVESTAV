/*
 * Stats.cpp
 *
 *  Created on: Jun 3, 2011
 *      Author: Moises Osorio
 */

#include <string>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

#include "stats.h"

using namespace std;

Stats::Stats(RepresentationType representationType) {
	this->representationType = representationType;
	generation = -1;
	totalCrossovers = 0;
	totalMutations = 0;
	incrementGeneration();
}

Stats::~Stats() {
	
}

void Stats::incrementGeneration() {
	generation++;
	mutations = 0;
	crossovers = 0;
	bestIndividual = NULL;
	minFx = 0;
	maxFx = 0;
	averageFx = 0;
	violatingCount = 0;
}

void Stats::incrementMutations() {
	mutations++;
	totalMutations++;
}

void Stats::incrementCrossovers() {
	crossovers++;
	totalCrossovers++;
}

void Stats::analyzePopulation(vector<Individual *> population) {
	double fxSum = 0, maxFitness = -1e30;
	minFx = 1e20;
	maxFx = -1e20;
	populationSize = population.size();
	
	// Gets statistics from population
	for (auto it = population.begin(); it != population.end(); it++) {
		double fx = (*it)->getFx();
		fxSum += fx;
		
		maxFx = max(maxFx, fx);
		minFx = min(minFx, fx);
		
		if ((*it)->violatesConstraints())
			violatingCount++;
	}
	
	bestIndividual = NULL;
	for (auto it = population.begin(); it != population.end(); it++)
		if ((*it)->getFitness() > maxFitness && !(*it)->violatesConstraints()) {
			maxFitness = (*it)->getFitness();
			bestIndividual = (*it);
		}
	if (bestIndividual == NULL)
		for (auto it = population.begin(); it != population.end(); it++)
			if ((*it)->getFitness() > maxFitness) {
				maxFitness = (*it)->getFitness();
				bestIndividual = (*it);
			}
	
	averageFx = fxSum / population.size();
}

double Stats::getVisitedSearchSpace() {
	int n = bestIndividual->getChromosomeLength();
	double visited = (generation + 1) * populationSize; // Count generation 0
	double total;
	switch (representationType) {
		case RepresentationType::BINARY_REPRESENTATION:
		case RepresentationType::GRAY_REPRESENTATION:
			total = pow(2, n);
			break;
		case RepresentationType::INTEGER_REPRESENTATION:
			total = pow(10, n);
			break;
		case RepresentationType::PERMUTATION_REPRESENTATION:
			total = 1;
			for (int i = 2; i <= n; i++)
				total *= i;
			break;
		case RepresentationType::REAL_REPRESENTATION:
			total = visited;
			break;
		case RepresentationType::TREE_REPRESENTATION:
			total = 1;
			for (int i = n-1; i <= 2*n-3; i++)
				total *= i;
			total /= pow(2.0, n-2);
			break;
		default:
			throw "Unknown representation";
			break;
	}
	
	return visited / total;
}

void Stats::print() {
	printf("Generation %d:\n", generation);
	printf("    Average f(x): %.10f\n", averageFx);
	printf("    Minimum f(x): %.10f\n", minFx);
	printf("    Maximum f(x): %.10f\n", maxFx);
	printf("    Mutations: %d\n", mutations);
	printf("    Crossovers: %d\n", crossovers);
	if (bestIndividual->getConstraintIneqCount() + bestIndividual->getConstraintEqCount() > 0)
		printf("    Violating population: %.2f%%\n", violatingCount*100.0 / populationSize);
	if (representationType != RepresentationType::REAL_REPRESENTATION &&
			representationType != RepresentationType::TREE_REPRESENTATION)
		printf("    Best chromosome: (%s)\n", bestIndividual->toString().c_str());
	printf("    Best X: (%s)\n", bestIndividual->toXString().c_str());
	if (bestIndividual->getConstraintIneqCount() > 0) {
		printf("    Best inequality constraint values:\n");
		for (int i = 0; i < bestIndividual->getConstraintIneqCount(); i++) {
			double value = bestIndividual->getConstraintIneqValues()[i];
			printf("        g%d: %.10lf%s\n", i+1, value, value < EPS? "" : " (Violated)");
		}
	}
	if (bestIndividual->getConstraintEqCount() > 0) {
		printf("    Best equality constraint values:\n");
		for (int i = 0; i < bestIndividual->getConstraintEqCount(); i++) {
			double value = bestIndividual->getConstraintEqValues()[i];
			printf("        h%d: %.10lf%s\n", bestIndividual->getConstraintIneqCount()+i+1, value, abs(value) < EPS? "" : " (Violated)");
		}
	}
}

void Stats::printFinal() {
	printf("Final results:\n");
	printf("    Total mutations: %d\n", totalMutations);
	printf("    Total crossovers: %d\n", totalCrossovers);
	if (representationType != RepresentationType::REAL_REPRESENTATION && 
			representationType != RepresentationType::TREE_REPRESENTATION) {
		printf("    Visited search space: %E%%\n", 100.0 * getVisitedSearchSpace());
		printf("    Best chromosome: (%s)\n", bestIndividual->toString().c_str());
	}
	printf("    Best X: (%s)\n", bestIndividual->toXString().c_str());
	printf("    Best f(X): %.10lf\n", bestIndividual->getFx());
	printf("    Best fitness: %.10lf\n", bestIndividual->getFitness());
	if (bestIndividual->getConstraintIneqCount() > 0) {
		printf("    Best inequality constraint values:\n");
		for (int i = 0; i < bestIndividual->getConstraintIneqCount(); i++) {
			double value = bestIndividual->getConstraintIneqValues()[i];
			printf("        g%d: %.10lf%s\n", i+1, value, value < EPS? "" : " (Violated)");
		}
	}
	if (bestIndividual->getConstraintEqCount() > 0) {
		printf("    Best equality constraint values:\n");
		for (int i = 0; i < bestIndividual->getConstraintEqCount(); i++) {
			double value = bestIndividual->getConstraintEqValues()[i];
			printf("        h%d: %.10lf%s\n", bestIndividual->getConstraintIneqCount()+i+1, value, abs(value) < EPS? "" : " (Violated)");
		}
	}
}
