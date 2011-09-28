/*
 * Individual.h
 *
 *  Created on: Jun 3, 2011
 *      Author: Moises Osorio
 */

#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <string>

#include "tree.h"

using namespace std;

class Individual {
public:
	Individual();
	virtual ~Individual();
	
	int *getIntChromosome();
	void setIntChromosome(int *gene, int chromosomeLen);
	double *getRealChromosome();
	void setRealChromosome(double *gene, int chromosomeLen);
	Tree *getTreeChromosome();
	void setTreeChromosome(Tree *gene, int chromosomeLen);
	int getChromosomeLength();
	double getFitness();
	void setFitness(double fitness);
	void setRealX(double *x, int n);
	double *getRealX();
	void setIntX(int *x, int n);
	int *getIntX();
	double *getConstraintEqValues();
	double *getConstraintIneqValues();
	int getConstraintEqCount();
	int getConstraintIneqCount();
	void setConstraintEqValues(double *values, int n);
	void setConstraintIneqValues(double *values, int n);
	int getN();
	void setCrosspoint(int crosspoint);
	void setParents(int parent1, int parent2);
	string toString();
	string toXString();
	void incrementMutations();
	int getIndex();
	void setIndex(int index);
	void setFx(double fx);
	double getFx();
	
	bool violatesConstraints();
	Individual *clone();
	bool equals(Individual *ind);
	
private:
	int *intChromosome;
	double *realChromosome;
	Tree *treeChromosome;
	int chromosomeLen;
	double fitness;
	double *realx;
	int *intx;
	int n;
	double fx;
	double *constraintEqValues;
	double *constraintIneqValues;
	int constraintEqCount;
	int constraintIneqCount;
	int crosspoint;
	int parent1;
	int parent2;
	int mutations;
	int index;
};

#endif /* INDIVIDUAL_H_ */
