/*
 * Individual.cpp
 *
 *  Created on: Jun 3, 2011
 *      Author: Moises Osorio
 */

#include <stdlib.h>
#include <string.h>
#include <cmath>

#include "config.h"
#include "individual.h"

Individual::Individual() {
	intChromosome = NULL;
	realChromosome = NULL;
	realx = NULL;
	intx = NULL;
	treeChromosome = NULL;
	constraintEqValues = NULL;
	constraintIneqValues = NULL;
	constraintEqCount = 0;
	constraintIneqCount = 0;
	chromosomeLen = 0;
	fitness = 0;
	n = 0;
	parent1 = -1;
	parent2 = -1;
	crosspoint = -1;
	mutations = 0;
}

Individual::~Individual() {
	if (intChromosome != NULL)
		delete [] intChromosome;
	if (realChromosome != NULL)
		delete [] realChromosome;
	if (treeChromosome != NULL)
		delete treeChromosome;
	if (realx != NULL)
		delete [] realx;
	if (intx != NULL)
		delete [] intx;
	if (constraintEqValues != NULL)
		delete [] constraintEqValues;
	if (constraintIneqValues != NULL)
		delete [] constraintIneqValues;
}

void Individual::incrementMutations() {
	mutations++;
}

void Individual::setCrosspoint(int crosspoint) {
	this->crosspoint = crosspoint;
}

void Individual::setParents(int parent1, int parent2) {
	this->parent1 = parent1;
	this->parent2 = parent2;
}

Individual *Individual::clone() {
	Individual *clone = new Individual();
	if (intChromosome != NULL) {
		int *geneClone = new int[chromosomeLen];
		memcpy(geneClone, intChromosome, chromosomeLen*sizeof(int));
		clone->setIntChromosome(geneClone, chromosomeLen);
	}
	
	if (realChromosome != NULL) {
		double *geneClone = new double[chromosomeLen];
		memcpy(geneClone, realChromosome, chromosomeLen*sizeof(double));
		clone->setRealChromosome(geneClone, chromosomeLen);
	}
	
	if (treeChromosome != NULL)
		clone->setTreeChromosome(treeChromosome->clone(), chromosomeLen);
	
	if (realx != NULL) {
		double *xClone = new double[n];
		memcpy(xClone, realx, n*sizeof(double));
		clone->setRealX(xClone, n);
	}
	
	if (intx != NULL) {
		int *xClone = new int[n];
		memcpy(xClone, intx, n*sizeof(int));
		clone->setIntX(xClone, n);
	}
	
	if (constraintIneqValues != NULL) {
		double *xClone = new double[constraintIneqCount];
		memcpy(xClone, constraintIneqValues, constraintIneqCount*sizeof(double));
		clone->setConstraintIneqValues(xClone, constraintIneqCount);
	}

	if (constraintEqValues != NULL) {
		double *xClone = new double[constraintEqCount];
		memcpy(xClone, constraintEqValues, constraintEqCount*sizeof(double));
		clone->setConstraintEqValues(xClone, constraintEqCount);
	}
	
	clone->setFx(fx);
	clone->setFitness(fitness);
	
	return clone;
}

int *Individual::getIntChromosome() {
	return intChromosome;
}

int Individual::getChromosomeLength() {
	return chromosomeLen;
}

double *Individual::getRealChromosome() {
	return realChromosome;
}

void Individual::setRealChromosome(double *chromosome, int chromosomeLength) {
	this->realChromosome = chromosome;
	this->chromosomeLen = chromosomeLength;
}

void Individual::setIntChromosome(int *chromosome, int chromosomeLength) {
	this->intChromosome = chromosome;
	this->chromosomeLen = chromosomeLength;
}

double Individual::getFitness()
{
	return fitness;
}

double *Individual::getConstraintEqValues() {
	return constraintEqValues;
}

double *Individual::getConstraintIneqValues() {
	return constraintIneqValues;
}

int Individual::getConstraintEqCount() {
	return constraintEqCount;
}

int Individual::getConstraintIneqCount() {
	return constraintIneqCount;
}

void Individual::setConstraintEqValues(double *values, int n) {
	constraintEqValues = values;
	constraintEqCount = n;
}

void Individual::setConstraintIneqValues(double *values, int n) {
	constraintIneqValues = values;
	constraintIneqCount = n;
}

void Individual::setFitness(double fitness)
{
	this->fitness = fitness;
}

void Individual::setRealX(double *x, int n) {
	this->realx = x;
	this->n = n;
}

double *Individual::getRealX() {
	return realx;
}

void Individual::setIntX(int *x, int n) {
	this->intx = x;
	this->n = n;
}

int *Individual::getIntX() {
	return intx;
}

void Individual::setTreeChromosome(Tree *x, int n) {
	if (treeChromosome != NULL)
		delete treeChromosome;
	treeChromosome = x;
	chromosomeLen = n;
}

Tree *Individual::getTreeChromosome() {
	return treeChromosome;
}

int Individual::getN() {
	return n;
}

int Individual::getIndex() {
	return index;
}

void Individual::setIndex(int index) {
	this->index = index;
}

void Individual::setFx(double fx) {
	this->fx = fx;
}

double Individual::getFx() {
	return fx;
}

bool Individual::violatesConstraints() {
	for (int i = 0; i < constraintIneqCount; i++)
		if (constraintIneqValues[i] > EPS)
			return true;
	
	for (int i = 0; i < constraintEqCount; i++)
		if (abs(constraintEqValues[i]) > EPS)
			return true;
	
	return false;
}

bool Individual::equals(Individual *ind) {
	if (treeChromosome != NULL)
		return false;
	for (int i = 0; i < chromosomeLen; i++)
		if (intChromosome != NULL && intChromosome[i] != ind->getIntChromosome()[i])
			return false;
		else if (realChromosome != NULL && abs(realChromosome[i] - ind->getRealChromosome()[i]) > EPS)
			return false;
	
	return true;
}

string Individual::toString()
{
	if (treeChromosome != NULL)
		return treeChromosome->toString();
	
	string s;
	char buffer[1024];
	for (int i = 0; i < chromosomeLen; i++) {
		if (intChromosome != NULL)
			snprintf(buffer, sizeof(buffer), "%d", intChromosome[i]);
		else {
			if (s.size() > 0)
				s += " ";
			snprintf(buffer, sizeof(buffer), "%.10f", realChromosome[i]);
		}
		s += string(buffer);
	}
	return s;
}

string Individual::toXString()
{
	if (treeChromosome != NULL)
		return treeChromosome->toString();
	
	string s;
	char buffer[1024];
	for (int i = 0; i < n; i++) {
		if (s.size() > 0)
			s += ", ";
		if (realx != NULL)
			snprintf(buffer, sizeof(buffer), "%.10lf", realx[i]); // Representation of x_i
		else if (intx != NULL)
			snprintf(buffer, sizeof(buffer), "%d", intx[i]); // Representation of x_i
		s = s.append(buffer);
	}
	
	return s;
}
