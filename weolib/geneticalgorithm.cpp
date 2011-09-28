/*
 * GeneticAlgorithm.cpp
 *
 *  Created on: Jun 1, 2011
 *      Author: Moises Osorio
 */
#include <cmath>
#include <algorithm>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <fstream>

#include "geneticalgorithm.h"
#include "randomlib.h"

GeneticAlgorithm::GeneticAlgorithm() {
	currentGeneration = 0;
	maxGenerations = 0;
	varSize = NULL;
	stats = NULL;
	intfunction = NULL;
	realfunction = NULL;
	equalityConstraints = NULL;
	inequalityConstraints = NULL;
	faithDegree = 0;
	elitism = true;
	minimizer = false;
	representationType = RepresentationType::BINARY_REPRESENTATION;
	selectionType = SelectionType::UNIFORM_ROULETTE_WHEEL_SELECTION;
	crossoverType = CrossoverType::ONE_POINT_CROSSOVER;
	mutationType = MutationType::UNIFORM_MUTATION;
	constraintHandlingType = ConstraintHandlingType::FAITH_BASED_CONSTRAINT_HANDLING;
	localSearchType = LocalSearchType::NO_SEARCH;
	
	temperature = 0;
}

GeneticAlgorithm::~GeneticAlgorithm() {
	if (varSize == NULL)
		return;
	if (stats != NULL)
		delete stats;

	delete [] varSize;
	for (auto ind = population.begin(); ind != population.end(); ind++)
		delete *ind;
	population.clear();
}

void GeneticAlgorithm::setMutationProbability(double probability) {
	mutationProbability = probability;
}

void GeneticAlgorithm::setCrossoverProbability(double probability) {
	crossoverProbability = probability;
}

void GeneticAlgorithm::setInversionProbability(double probability) {
	inversionProbability = probability;
}

void GeneticAlgorithm::setElitism(bool elitism) {
	this->elitism = elitism;
}

void GeneticAlgorithm::setMinimizer(bool minimizer) {
	this->minimizer = minimizer;
}

void GeneticAlgorithm::setFaithDegree(double faithDegree) {
	this->faithDegree = faithDegree;
}

void GeneticAlgorithm::setRepresentationType(RepresentationType type) {
	this->representationType = type;
}

void GeneticAlgorithm::setSelectionType(SelectionType type) {
	this->selectionType = type;
}

void GeneticAlgorithm::setCrossoverType(CrossoverType type) {
	this->crossoverType = type;
}

void GeneticAlgorithm::setMutationType(MutationType type) {
	this->mutationType = type;
}

void GeneticAlgorithm::setConstraintHandlingType(ConstraintHandlingType type) {
	this->constraintHandlingType = type;
}

void GeneticAlgorithm::setLocalSearchType(LocalSearchType type) {
	this->localSearchType = type;
}

void GeneticAlgorithm::solve(int *xs, int n, int populationSize, int maxGenerations, double randomSeed, 
		double (*f)(int *x)) {
	solve(NULL, xs, NULL, n, populationSize, NULL, NULL, maxGenerations, randomSeed, NULL, f, NULL, NULL, 0, NULL, 0);
}

void GeneticAlgorithm::solve(double *xs, int n, int populationSize, double bounds[][2], int *precision, 
			int maxGenerations, double randomSeed, double (*f)(double *x)) {
	solve(xs, NULL, NULL, n, populationSize, bounds, precision, maxGenerations, randomSeed, f, NULL, NULL, NULL, 0, NULL, 0);
}

void GeneticAlgorithm::solve(double *xs, int n, int populationSize, double bounds[][2], int *precision, 
		int maxGenerations, double randomSeed, double(*f)(double *x), double (**g)(double *x), int gn, 
		double (**h)(double *x), int hn) {
	solve(xs, NULL, NULL, n, populationSize, bounds, precision, maxGenerations, randomSeed, f, NULL, NULL, g, gn, h, hn);
}

void GeneticAlgorithm::solve(Tree*xs, int n, int populationSize, int maxGenerations, double randomSeed, 
				double (*f)(Tree *x)) {
	solve(NULL, NULL, xs, n, populationSize, NULL, NULL, maxGenerations, randomSeed, NULL, NULL, f, NULL, 0, NULL, 0);
}

// Microseconds since the epoch
long long getTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec*1000000LL + tv.tv_usec) / 1000LL;
}

void GeneticAlgorithm::solve(double *realxs, int *intxs, Tree *treexs, int n, int populationSize, double bounds[][2], int *precision, 
				int maxGenerations, double randomSeed, double (*realf)(double *x), double (*intf)(int *x), double (*treef)(Tree *x),
				double (**g)(double *x), int gn, double (**h)(double *x), int hn) {
	this->currentGeneration = 0;
	this->maxGenerations = maxGenerations;
	this->n = n;
	this->nIneq = gn;
	this->nEq = hn;
	this->populationSize = populationSize;
	this->realfunction = realf;
	this->intfunction = intf;
	this->treefunction = treef;
	this->inequalityConstraints = g;
	this->equalityConstraints = h;
	this->bounds = bounds;
	this->varSize = new int[n];
	this->precision = precision;
	this->chromosomeLen = calculateGeneSize();
	warmup_random(randomSeed);

	ofstream iterfile, resfile;
	if (directory != "") {
		iterfile.open((directory + "/" + instanceName + "-iter.out").c_str());
		resfile.open((directory + "/" + instanceName + ".out").c_str());
	}
	
	long long startTime = getTime();
	
	if (stats != NULL)
		delete stats;
	stats = new Stats(representationType);
	
	population = generateRandomPopulation();
#ifdef NO_STATS
	stats->analyzePopulation(population);
	stats->print();
#endif
	
	Individual *best = getBestIndividual(population);
	int startingScore = round(best->getFx());
	
	for (currentGeneration = 0; currentGeneration < maxGenerations; currentGeneration++) {
		long long startTimeIter = getTime();
#ifdef NO_STATS
		stats->incrementGeneration();
#endif
		
#ifdef _NDEBUG
		printf("\nGeneration %d\n", currentGeneration);
		printf("    Population: \n");
		for (int i = 0; i < populationSize; i++) {
			Individual *ind = population[i];
			printf("        Individual %d:\n", i);
			printf("            Chromosome: %s\n", ind->toString().c_str());
			printf("            X: %s\n", ind->toXString().c_str());
			printf("            Fitness: %.10lf\n", ind->getFitness());
		}
#endif
		
		vector<Individual *> nextGen = generateNextGeneration();
		for (auto ind = population.begin(); ind != population.end(); ind++)
			delete *ind;
		
#ifdef _NDEBUG
		printf("\n");
#endif
		
		population.clear();
		population = nextGen;
		nextGen.clear();
		
#ifdef NO_STATS
		selectNIndividuals(0); // To set the right fitness
		stats->analyzePopulation(population);
		stats->print();
#endif
		
		best = getBestIndividual(population);
		if (directory != "") {
			long long time = getTime() - startTimeIter;
			iterfile << (currentGeneration+1) << " " << round(best->getFx()) << " " << time << "\n";
		}
	}
	
#ifdef _NDEBUG
		printf("\nFinal\n");
		printf("    Population: \n");
		for (int i = 0; i < populationSize; i++) {
			Individual *ind = population[i];
			printf("        Individual %d:\n", i);
			printf("            Chromosome: %s\n", ind->toString().c_str());
			printf("            X: %s\n", ind->toXString().c_str());
			printf("            Fitness: %.10lf\n", ind->getFitness());
		}
		
		printf("\n");
#endif
#ifdef NO_STATS
	stats->printFinal();
#endif
	
	best = getBestIndividual(population);
	if (treexs != NULL)
		treexs->setRoot(best->getTreeChromosome()->getRoot()->clone());
	else
		getXFromIndividual(realxs, intxs, best);
	
	if (directory != "") {
		long long time = getTime() - startTime;
		resfile << instanceName << "\n";
		resfile << n << "\n";
		resfile << startingScore << "\n";
		resfile << round(best->getFx()) << "\n";
		resfile << best->getTreeChromosome()->toString() << ";\n";
		resfile << time << "\n";
		
		iterfile.close();
		resfile.close();
	}
}

Individual *GeneticAlgorithm::getBestIndividual(vector<Individual *> population) {
	Individual *best = NULL;
	for (auto ind = population.begin(); ind != population.end(); ind++)
		if ((best == NULL || best->getFitness() < (*ind)->getFitness()) && !(*ind)->violatesConstraints())
			best = *ind;
	
	if (best == NULL)
		for (auto ind = population.begin(); ind != population.end(); ind++)
			if ((best == NULL || best->getFitness() < (*ind)->getFitness()))
				best = *ind;
	
	return best;
}

TreeNode *generateSubtree(int *ids, int from, int to) {
	if (from == to)
		return new TreeNode(ids[from]);
	
	TreeNode *root = new TreeNode(-1);
	int part = rnd(from, to-1);
	root->setLeft(generateSubtree(ids, from, part));
	root->setRight(generateSubtree(ids, part+1, to));
	
	return root;
}

void GeneticAlgorithm::setInstanceName(string instanceName) {
	this->instanceName = instanceName;
}

void GeneticAlgorithm::setDirectory(string dir) {
	this->directory = dir;
}

vector<Individual *> GeneticAlgorithm::generateRandomPopulation() {
	vector<Individual *> population;
	for (int i = 0; i < populationSize; i++) {
		double *realChromosome = NULL;
		int *intChromosome = NULL;
		Tree *treeChromosome = NULL;
		
		if (representationType == RepresentationType::REAL_REPRESENTATION) {
			realChromosome = new double[chromosomeLen];
			for (int j = 0; j < chromosomeLen; j++)
				realChromosome[j] = rndreal(bounds[j][0], bounds[j][1]);
		} else if (representationType == RepresentationType::TREE_REPRESENTATION) {
			treeChromosome = new Tree();
			intChromosome = new int[chromosomeLen];
			for (int j = 0; j < chromosomeLen; j++)
				intChromosome[j] = j;
			shuffle(intChromosome, chromosomeLen);
			treeChromosome->setRoot(generateSubtree(intChromosome, 0, chromosomeLen-1));
			
			delete [] intChromosome;
			intChromosome = NULL;
		} else {
			intChromosome = new int[chromosomeLen];
			if (representationType == PERMUTATION_REPRESENTATION) {
				for (int j = 0; j < chromosomeLen; j++)
					intChromosome[j] = j;
				shuffle(intChromosome, chromosomeLen);
			} else {
				for (int j = 0; j < chromosomeLen; j++)
					if (representationType == RepresentationType::INTEGER_REPRESENTATION)
						intChromosome[j] = rndint(10);
					else
						intChromosome[j] = flip(0.5);
			}
		}
		
		Individual *ind = new Individual();
		ind->setIntChromosome(intChromosome, chromosomeLen);
		ind->setRealChromosome(realChromosome, chromosomeLen);
		ind->setTreeChromosome(treeChromosome, chromosomeLen);
		if (contains(ind, population)) {
			i--;
			delete ind;
			continue;
		}
		
		setFitness(ind);
		ind->setIndex(i);
		
		population.push_back(ind);
	}
	
	return population;
}

bool GeneticAlgorithm::contains(Individual *individual, vector<Individual *> population) {
	for (auto it = population.begin(); it != population.end(); it++)
		if (individual->equals(*it))
			return true;
	
	return false;
}

vector<Individual *> GeneticAlgorithm::generateNextGeneration() {
	vector<Individual *> newPopulation;
	vector<Individual *> selection = selectNIndividuals(populationSize);

#ifdef _NDEBUG
		printf("    Crossover: \n");
#endif
	
	for (int i = 0; i < populationSize / 2; i++) {
		Individual *parent1 = selection[i*2];
		Individual *parent2 = selection[i*2+1];
		
		Individual *son1 = new Individual();
		if (representationType == RepresentationType::REAL_REPRESENTATION)
			son1->setRealChromosome(new double[chromosomeLen], chromosomeLen);
		else if (representationType == RepresentationType::TREE_REPRESENTATION)
			son1->setTreeChromosome(new Tree(), chromosomeLen);
		else
			son1->setIntChromosome(new int[chromosomeLen], chromosomeLen);
		son1->setIndex(i*2);

		Individual *son2 = new Individual();
		if (representationType == RepresentationType::REAL_REPRESENTATION)
			son2->setRealChromosome(new double[chromosomeLen], chromosomeLen);
		else if (representationType == RepresentationType::TREE_REPRESENTATION)
			son2->setTreeChromosome(new Tree(), chromosomeLen);
		else
			son2->setIntChromosome(new int[chromosomeLen], chromosomeLen);
		son2->setIndex(i*2+1);
		
		crossoverInviduals(parent1, parent2, son1, son2);
//		printf("Son1 valid after XO: %d\n", son1->getTreeChromosome()->isValid(n));
//		printf("Son2 valid after XO: %d\n", son2->getTreeChromosome()->isValid(n));
		mutateIndividual(son1);
		mutateIndividual(son2);
//		printf("Son1 valid after M: %d\n", son1->getTreeChromosome()->isValid(n));
//		printf("Son2 valid after M: %d\n", son2->getTreeChromosome()->isValid(n));
		if (representationType == RepresentationType::PERMUTATION_REPRESENTATION) {
			invertIndividual(son1);
			invertIndividual(son2);
		}
		
		localSearchIndividual(son1);
		localSearchIndividual(son2);
//		printf("Son1 valid after LS: %d\n", son1->getTreeChromosome()->isValid(n));
//		printf("Son2 valid after LS: %d\n", son2->getTreeChromosome()->isValid(n));
		
		if (son1->equals(son2) || contains(son1, newPopulation) || contains(son2, newPopulation)) { // Repeated?
			i--;
			delete son1;
			delete son2;
			continue;
		}
		
		setFitness(son1);
		setFitness(son2);
		
		newPopulation.push_back(son1);
		newPopulation.push_back(son2);
	}

	if (elitism) {
		Individual *best = getBestIndividual(population);
		
		bool repetition = false;
		for (auto it = newPopulation.begin(); repetition && it != newPopulation.end(); it++)
			repetition |= best->equals(*it);
		
		if (!repetition) {
			Individual *unlucky = newPopulation.back();
			newPopulation.pop_back();
			delete unlucky;
			
			best = best->clone();
			best->setIndex(populationSize-1);
			setFitness(best);
			newPopulation.push_back(best);
		}
	}
	
	return newPopulation;
}

void GeneticAlgorithm::localSearchIndividual(Individual *individual) {
	if (localSearchType == LocalSearchType::NO_SEARCH)
		return;
	
	simulatedAnnealing(individual);
}

void GeneticAlgorithm::simulatedAnnealing(Individual *individual) {
	setFitness(individual);
	Tree *s = individual->getTreeChromosome()->clone();
	double e = treefunction(s);
	Tree *sbest = s->clone();
	double ebest = e;
	double T = 0.8;
	
	for (int k = 0; k < 50; k++) {
		Tree *snew = s->clone();
		
		// Get neighbor
		switch (localSearchType) {
			case LocalSearchType::NEAREST_NEIGHBOR_INTERCHANGE_SEARCH:
				nearestNeighborInterchange(snew);
				break;
			case LocalSearchType::SUBTREE_PRUNING_REGRAFTING_SEARCH:
				subtreePruningRegrafting(snew);
				break;
			case LocalSearchType::TREE_BISECTION_RECONNECTION_SEARCH:
				treeBisectionReconnection(snew);
				break;
			default:
				printf("ERROR: Not supported local search with Simulated Annealing.\n");
				exit(EXIT_FAILURE);
		}
		
		// Continue SA
		double enew = treefunction(snew);
		T *= 0.95;
		double prob = exp(-1.0/T * max(0.0, enew - e));
//		printf("PROB SA: %f, from %f to %f\n", prob, e, enew);
		if (flip(prob)) { // Accept solution?
			delete s;
			e = enew;
			s = snew->clone();
		}
		
		if (enew < ebest) { // Elitism
			delete sbest;
			ebest = enew;
			sbest = snew->clone();
		}
		
		delete snew;
	}
	
//	if (es - ebest < 1e-9)
//		printf("Improvement: %f\n", es - ebest);
	
	if (s != sbest)
		delete s;
	individual->setTreeChromosome(sbest, chromosomeLen);
}

void GeneticAlgorithm::subtreePruningRegrafting(Tree *tree) {
	TreeNode *root = selectRandomSubtree(tree->getRoot(), -1);
	while (root->getParent() == NULL || root->getParent()->getParent() == NULL)
		root = selectRandomSubtree(tree->getRoot(), -1);
	
	TreeNode *parent = root->getParent();
	TreeNode *grand = parent->getParent();
	TreeNode *bro = parent->getLeft() == root ? parent->getRight() : parent->getLeft();
	if (grand->getLeft() == parent)
		grand->setLeft(bro);
	else
		grand->setRight(bro);
	delete parent;
	
	bro = selectRandomSubtree(tree->getRoot(), -1);
	while (bro->getParent() == NULL)
		bro = selectRandomSubtree(tree->getRoot(), -1);
	grand = bro->getParent();
	
	parent = new TreeNode(-1);
	parent->setLeft(bro);
	parent->setRight(root);
	if (grand->getLeft() == bro)
		grand->setLeft(parent);
	else
		grand->setRight(parent);
}

void GeneticAlgorithm::treeBisectionReconnection(Tree *tree) {
	TreeNode *sub = selectRandomSubtree(tree->getRoot(), -1);
	while (sub->getParent() == NULL || sub->getParent()->getParent() == NULL)
		sub = selectRandomSubtree(tree->getRoot(), -1);
	
	TreeNode *parent = sub->getParent();
	TreeNode *grand = parent->getParent();
	TreeNode *bro = parent->getLeft() == sub ? parent->getRight() : parent->getLeft();
	if (grand->getLeft() == parent)
		grand->setLeft(bro);
	else
		grand->setRight(bro);
	delete parent;
	
	bro = selectRandomSubtree(tree->getRoot(), -1);
	while (bro->getParent() == NULL)
		bro = selectRandomSubtree(tree->getRoot(), -1);
	grand = bro->getParent();
	
	sub->setParent(NULL);
	TreeNode *subsub = selectRandomSubtree(sub, -1);
	TreeNode *subsubparent = subsub->getParent();
	
	parent = new TreeNode(-1);
	parent->setLeft(bro);
	parent->setRight(subsub);
	if (subsubparent != NULL) {
		TreeNode *subsubbro;
		if (subsubparent->getLeft() == subsub)
			subsubbro = subsubparent->getRight();
		else
			subsubbro = subsubparent->getLeft();
		
		if (subsubparent == sub) {
			sub = subsubbro;
		} else {
			if (subsubparent->getParent()->getLeft() == subsubparent)
				subsubparent->getParent()->setLeft(subsubbro);
			else
				subsubparent->getParent()->setRight(subsubbro);
		}
		delete subsubparent;
		
		TreeNode *parent2 = new TreeNode(-1);
		parent2->setLeft(parent);
		parent2->setRight(sub);
		
		parent = parent2;
	}
	
	if (grand->getLeft() == bro)
		grand->setLeft(parent);
	else
		grand->setRight(parent);
}

void GeneticAlgorithm::nearestNeighborInterchange(Tree *tree) {
	TreeNode *root = selectRandomSubtree(tree->getRoot(), -1);
	while (root->getParent() == NULL || root->getId() >= 0)
		root = selectRandomSubtree(tree->getRoot(), -1);
	
	int sonType = flip(0.5);
	int broType = 0;
	TreeNode *parent = root->getParent();
	TreeNode *bro = parent->getLeft();
	TreeNode *son = sonType == 0 ? root->getLeft() : root->getRight();
	if (parent->getLeft() == root) {
		broType = 1;
		bro = parent->getRight();
	}
	
	if (sonType == 0)
		root->setLeft(bro);
	else
		root->setRight(bro);
	if (broType == 0)
		parent->setLeft(son);
	else
		parent->setRight(son);
}

int GeneticAlgorithm::calculateGeneSize() {
	if (representationType == RepresentationType::PERMUTATION_REPRESENTATION || 
			representationType == RepresentationType::REAL_REPRESENTATION ||
			representationType == RepresentationType::TREE_REPRESENTATION)
		return n;
	
	int size = 0;
	for (int i = 0; i < n; i++) {
		double values = pow(10, precision[i]) * (bounds[i][1] - bounds[i][0]);
		if (representationType == RepresentationType::INTEGER_REPRESENTATION) {
			varSize[i] = ceil(log(values) / log(10));
		} else {
			varSize[i] = ceil(log(values) / log(2));
		}
		
		size += varSize[i];
	}
	
	return size;
}

void GeneticAlgorithm::getXFromIndividual(double *realx, int *intx, Individual *individual) {
	for (int pos = 0, i = 0; i < n; i++) {
		long long maxValue = 1;
		long long value = 0;
		switch (representationType) {
			case RepresentationType::INTEGER_REPRESENTATION:
				for (int j = 0; j < varSize[i]; j++, pos++) {
					value = value*10 + individual->getIntChromosome()[pos];
					maxValue *= 10;
				}
				break;
			case RepresentationType::BINARY_REPRESENTATION:
				maxValue <<= varSize[i];
				for (int j = 0; j < varSize[i]; j++, pos++)
					value = (value << 1) | individual->getIntChromosome()[pos];
				break;
			case RepresentationType::GRAY_REPRESENTATION:
				maxValue <<= varSize[i];
				value = individual->getIntChromosome()[pos++];
				for (int j = 1; j < varSize[i]; j++, pos++)
					value = (value << 1) | ((value & 1) ^ individual->getIntChromosome()[pos]);
				break;
			case RepresentationType::PERMUTATION_REPRESENTATION:
				intx[i] = individual->getIntChromosome()[i];
				continue;
			case RepresentationType::REAL_REPRESENTATION:
				realx[i] = individual->getRealChromosome()[i];
				continue;
			default:
				printf("Cannot get X from individual when using representation type %d.\n", representationType);
				return;
		}

		realx[i] = bounds[i][0] + value*(bounds[i][1] - bounds[i][0]) / (maxValue - 1);
	}
}

void GeneticAlgorithm::setFitness(Individual *individual) {
	double fx;
	if (representationType == RepresentationType::PERMUTATION_REPRESENTATION) {
		int *x = individual->getIntX();
		if (x == NULL)
			x = new int[n];
		getXFromIndividual(NULL, x, individual);
		fx = intfunction(x);
		individual->setIntX(x, n);
	} else if (representationType == RepresentationType::TREE_REPRESENTATION) {
		fx = treefunction(individual->getTreeChromosome());
	} else {
		double *x = individual->getRealX();
		if (x == NULL)
			x = new double[n];
		getXFromIndividual(x, NULL, individual);
		fx = realfunction(x);
		individual->setRealX(x, n);
		
		double *ineqValues = new double[nIneq];
		for (int i = 0; i < nIneq; i++)
			ineqValues[i] = inequalityConstraints[i](x);
		individual->setConstraintIneqValues(ineqValues, nIneq);
		double *eqValues = new double[nEq];
		for (int i = 0; i < nEq; i++)
			eqValues[i] = equalityConstraints[i](x);
		individual->setConstraintEqValues(eqValues, nEq);
	}

	individual->setFx(fx);
}

vector<Individual *> GeneticAlgorithm::selectNIndividuals(int individuals) {
	switch (selectionType) {
		case SelectionType::UNIFORM_ROULETTE_WHEEL_SELECTION:
			return rouletteWheelSelection(individuals);
		case SelectionType::STOCHASTIC_REMAINDER_SELECTION:
			return stochasticRemainderSelection(individuals);
		case SelectionType::DETERMINISTIC_BINARY_TOURNAMENT_SELECTION:
			return deterministicBinaryTournamentSelection(individuals);
		case SelectionType::BOLTZMANN_SELECTION:
			return boltzmannSelection(individuals);
	}
	
	throw "Unknown selection type";
}

double GeneticAlgorithm::getPopulationFitness(double *fitness, vector<Individual *> population) {
	for (int i = 0; i < populationSize; i++)
		fitness[i] = minimizer ? -population[i]->getFx() : population[i]->getFx();
	setPositiveness(fitness);
	if (nEq+nIneq > 0) {
		switch (constraintHandlingType) {
			case ConstraintHandlingType::FAITH_BASED_CONSTRAINT_HANDLING:
				faithBasedConstraintHandling(fitness);
				break;
		}
	}
	
	double fitnessSum = 0;
	for (int i = 0; i < populationSize; i++) {
		fitnessSum += fitness[i];
		population[i]->setFitness(fitness[i]);
	}
	
	return fitnessSum / populationSize;
}

double getPenalization(Individual *individual) {
	double p = 0;
	for (int i = 0; i < individual->getConstraintIneqCount(); i++)
		p += pow(max(0.0, individual->getConstraintIneqValues()[i]), 2);
	for (int i = 0; i < individual->getConstraintEqCount(); i++)
		p += pow(individual->getConstraintEqValues()[i], 2);
	
//	printf("P: %.10f\n", p);
//	for (int i = 0; i < individual->getConstraintIneqCount(); i++) {
//		double value = individual->getConstraintIneqValues()[i];
//		printf("  g%d: %.10lf%s\n", i+1, value, value < EPS? "" : " (Violated)");
//	}
//	for (int i = 0; i < individual->getConstraintEqCount(); i++) {
//		double value = individual->getConstraintEqValues()[i];
//		printf("  h%d: %.10lf%s\n", individual->getConstraintIneqCount()+i+1, value, abs(value) < EPS? "" : " (Violated)");
//	}
	
	return p;
}

bool individualComparator(Individual *a, Individual *b) {
//	if (a->violatesConstraints() == b->violatesConstraints())
//		return a->getFitness() > b->getFitness();
//	return !a->violatesConstraints();
	
	return a->getFitness() > b->getFitness();
	
//	if (a->violatesConstraints() && b->violatesConstraints())
//		return a->getFitness() - getPenalization(a) > b->getFitness() - getPenalization(b);
//	return a->getFitness() > b->getFitness();
}

void GeneticAlgorithm::setPositiveness(double *fitness) {
	double minFitness = 1e30, maxFitness = -1e30;
	for (int i = 0; i < populationSize; i++) {
		minFitness = min(minFitness, fitness[i]);
		maxFitness = max(maxFitness, fitness[i]);
	}
	
	if (minFitness <= EPS) { // Fix negatives
		double delta = minFitness < -EPS ? -2*minFitness : maxFitness + 1;
		for (int i = 0; i < populationSize; i++)
			fitness[i] += delta;
	}
}

void GeneticAlgorithm::faithBasedConstraintHandling(double *fitness) {
	bool nonViolating = false;
	for (int i = 0; i < populationSize && !nonViolating; i++)
		nonViolating |= !population[i]->violatesConstraints();
	if (!nonViolating) {
		for (int i = 0; i < populationSize; i++)
			fitness[i] = -getPenalization(population[i]);
		setPositiveness(fitness);
	}
//	double maxFitness = 0;
//	for (int i = 0; i < populationSize; i++)
//		if (!population[i]->violatesConstraints())
//			maxFitness = max(maxFitness, fitness[i]);
//
//	if (maxFitness < EPS) {
//		for (int i = 0; i < populationSize; i++)
//			fitness[i] = -getPenalization(population[i]);
//		setPositiveness(fitness);
//
//		return;
//	}
	
//	double maxPenal = 0;
//	for (int i = 0; i < populationSize; i++)
//		maxPenal = max(maxPenal, getPenalization(population[i]));
//	if (maxPenal > maxFitness) {
//		for (int i = 0; i < populationSize; i++)
//			fitness[i] -= getPenalization(population[i]) * maxFitness / maxPenal;
//		setPositiveness(fitness);
//	}
	
	vector<Individual *> order = population;
	for (int i = 0; i < populationSize; i++)
		order[i]->setFitness(fitness[i]);
	
	sort(order.begin(), order.end(), individualComparator);
	for (int i = 0; i < populationSize; i++)
		if (order[i]->violatesConstraints()) { // Best violating individual
			double oldValue = order[i]->getFitness();
			for (int j = i+1; j < populationSize; j++)
				if (!order[j]->violatesConstraints()) { // Should we stop?
					if (flip(faithDegree))
						break; // Stop
					else // Reduce fitness
						order[i]->setFitness(order[j]->getFitness() - EPS);
				}
			
			// Normalize according to new fitness value
			for (int j = i+1; j < populationSize; j++)
				if (order[j]->violatesConstraints()) // Reduce value proportionally
					order[j]->setFitness(order[j]->getFitness() * order[i]->getFitness() / oldValue);
			
			break;
		}
	
	for (int i = 0; i < populationSize; i++)
		fitness[i] = population[i]->getFitness();
}

double GeneticAlgorithm::getStandardDeviation(double *fitness, int n) {
	double sigma = 0;
	double averageFitness = 0;
	
	for (int i = 0; i < n; i++)
		averageFitness += fitness[i];
	
	averageFitness /= n;
	for (int i = 0; i < n; i++) {
		double tmp = fitness[i] - averageFitness;
		sigma += tmp * tmp;
	}
	
	return sqrt(sigma / n);
}
	
vector<Individual *> GeneticAlgorithm::stochasticRemainderSelection(int individuals) {
	vector<Individual *> selection;
	double *fitness = new double[populationSize];
	double averageFitness = getPopulationFitness(fitness, population);
	
	// Set expected value using sigma scaling
	double sigma = getStandardDeviation(fitness, populationSize);
	for (int i = 0; i < populationSize; i++) {
		if (sigma < EPS)
			fitness[i] = 1;
		else
			fitness[i] = 1 + (fitness[i] - averageFitness) / (2 * sigma);
	}
	
	// Assign integer parts
	double decimalSum = 0;
	double *roulette = new double[populationSize];
	for (int i = 0; i < populationSize && selection.size() < (unsigned int)individuals; i++) {
		int integer = floor(fitness[i]);
		roulette[i] = fitness[i] - integer;
		decimalSum += roulette[i];
		while (integer-- > 0)
			selection.push_back(population[i]);
	}
	
	// Roulette for decimal parts
	while (selection.size() < (unsigned int)individuals) {
		double r = rndreal(0, decimalSum);
		double sum = 0;
		int selected;
		for (selected = 0; selected < populationSize-1; selected++) {
			sum += roulette[selected];
			if (sum > r)
				break;
		}
		
		selection.push_back(population[selected]);
	}

#ifdef _NDEBUG
	printf("    Selection: \n");
	printf("        i    Expected    Copies\n");
	for (int i = 0; i < populationSize; i++) {
		int copies = 0;
		for (int j = 0; j < individuals; j++)
			if (population[i] == selection[j])
				copies++;
		
		printf("        %d    %.10lf    %d\n", i, fitness[i], copies);
	}
#endif
	
	delete [] roulette;
	delete [] fitness;
	return selection;
}

vector<Individual *> GeneticAlgorithm::rouletteWheelSelection(int individuals) {
	vector<Individual *> selection;
	double *fitness = new double[populationSize];
	double averageFitness = getPopulationFitness(fitness, population);
	
	// Set expected value
	for (int i = 0; i < populationSize; i++)
		fitness[i] /= averageFitness;
	
	// Select n individuals
	for (int i = 0; i < individuals; i++) {
		double r = rndreal(0, populationSize);
		double sum = 0;
		int selected;
		for (selected = 0; selected < populationSize-1; selected++) {
			sum += fitness[selected];
			if (sum > r)
				break;
		}
		
		selection.push_back(population[selected]);
	}
	
#ifdef _NDEBUG
	printf("    Selection: \n");
	printf("        i    Expected    Copies\n");
	for (int i = 0; i < populationSize; i++) {
		int copies = 0;
		for (int j = 0; j < individuals; j++)
			if (population[i] == selection[j])
				copies++;
		
		printf("        %d    %.10lf    %d\n", i, fitness[i], copies);
	}
#endif
	
	delete [] fitness;
	return selection;
}

vector<Individual *> GeneticAlgorithm::boltzmannSelection(int individuals) {
	vector<Individual *> selection;
	double *fitness = new double[populationSize];
	getPopulationFitness(fitness, population);
	double sigma = getStandardDeviation(fitness, populationSize);
	if (sigma < EPS) // All equal
		sigma = 1;
	
	if (currentGeneration == 0) // t_0
		temperature = sigma;
	else { // t_i
//		double alpha = max(0.5, exp(-0.7*temperature / sigma));
//		double alpha = 0.95;
		double alpha = 0.999;
		temperature *= alpha;
	}
	
	double sum = 0;
	for (int i = 0; i < populationSize; i++) { // Recalculate fitness dependent on temperature
		fitness[i] = exp(fitness[i] / temperature);
		sum += fitness[i];
	}
	
	double average = sum / populationSize;
	for (int i = 0; i < populationSize; i++) // Set expected value
		fitness[i] /= average;
	
	// Roulette for new expected values
	while (selection.size() < (unsigned int)individuals) {
		double r = rndreal(0, populationSize);
		double sumi = 0;
		int selected;
		for (selected = 0; selected < populationSize-1; selected++) {
			sumi += fitness[selected];
			if (sumi > r)
				break;
		}
		
		selection.push_back(population[selected]);
	}
	
	delete [] fitness;
	
	return selection;
}

vector<Individual *> GeneticAlgorithm::deterministicBinaryTournamentSelection(int individuals) {
	vector<Individual *> selection;
	int *order = new int[populationSize];
	
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < populationSize; i++)
			order[i] = i;
		shuffle(order, populationSize);
		
		for (int i = 0; i < populationSize; i += 2) {
			int x = order[i];
			int y = order[i+1];
			if (population[x]->getFitness() > population[y]->getFitness())
				selection.push_back(population[x]);
			else
				selection.push_back(population[y]);
		}
	}
	
	delete [] order;
	
	return selection;
}

void GeneticAlgorithm::mutateIndividual(Individual *individual) {
	switch (mutationType) {
		case MutationType::RECIPROCAL_INTERCHANGE_MUTATION:
			reciprocalInterchangeMutation(individual);
			break;
		case MutationType::UNIFORM_MUTATION:
			uniformMutation(individual);
			break;
		case MutationType::PARAMETER_BASED_MUTATION:
			parameterBasedMutation(individual);
			break;
		case MutationType::SCRAMBLE_MUTATION:
			scrambleMutation(individual);
			break;
		default:
			printf("Unknown mutation type %d.\n", mutationType);
	}
}
void GeneticAlgorithm::parameterBasedMutation(Individual *ind) {
	double nm = 100 + currentGeneration;
	for (int i = 0; i < chromosomeLen; i++)
		if (flip(mutationProbability)) {
			stats->incrementMutations();
			
			double u = rndreal(0, 1);
			double d = min(ind->getRealChromosome()[i] - bounds[i][0], bounds[i][1] - ind->getRealChromosome()[i])
					/ (bounds[i][1] - bounds[i][0]);
			if (d < EPS)
				d = EPS;
			double dq;
			if (u <= 0.5)
				dq = pow(2*u + (1 - 2*u) * pow(1-d, nm+1), 1.0 / (nm+1)) - 1;
			else
				dq = 1 - pow(2*(1 - u) + 2*(u - 0.5)*pow(1-d, nm+1), 1.0 / (nm+1));
			
			ind->getRealChromosome()[i] += dq * (bounds[i][1] - bounds[i][0]);
		}
}

TreeNode *GeneticAlgorithm::selectRandomSubtree(TreeNode *node, double prob) {
	if (prob < 0)
		prob = 1.0 / (2*n - 1);
	while (node->getId() < 0 && !flip(prob))
		if (flip(0.5))
			node = node->getLeft();
		else
			node = node->getRight();
	
	return node;
}

void GeneticAlgorithm::scrambleMutation(Individual *ind) {
	TreeNode *node = selectRandomSubtree(ind->getTreeChromosome()->getRoot(), mutationProbability);
	if (node->getId() >= 0) // Cannot mutate just a leaf
		return;
	
	stats->incrementMutations();
	int *ids = new int[n];
	int count = node->getSubtreeIds(ids);
	shuffle(ids, count);
	node->setSubtreeIds(ids);
	
	delete [] ids;
}

void GeneticAlgorithm::uniformMutation(Individual *individual) {
	for (int i = 0; i < chromosomeLen; i++)
		if (flip(mutationProbability)) {
			stats->incrementMutations();
			
#ifdef _NDEBUG
		printf("                Mutating individual %d at %d\n", individual->getIndex(), i);
#endif
		
			if (representationType == RepresentationType::INTEGER_REPRESENTATION)
				individual->getIntChromosome()[i] = rndint(10);
			else
				individual->getIntChromosome()[i] ^= 1;
		}
}

void GeneticAlgorithm::reciprocalInterchangeMutation(Individual *individual) {
	if (flip(mutationProbability)) {
		stats->incrementMutations();
		
		int a = rndint(chromosomeLen);
		int b = rndint(chromosomeLen);
		int tmp = individual->getIntChromosome()[a];
		individual->getIntChromosome()[a] = individual->getIntChromosome()[b];
		individual->getIntChromosome()[b] = tmp;
	}
}

void GeneticAlgorithm::crossoverInviduals(Individual *parent1,
		Individual *parent2, Individual *son1, Individual *son2) {
	
#ifdef _NDEBUG
		printf("        Selecting parents %d and %d for crossover:\n", parent1->getIndex(), parent2->getIndex());
#endif

	if (flip(crossoverProbability)) {
		stats->incrementCrossovers();
		switch (crossoverType) {
			case CrossoverType::ONE_POINT_CROSSOVER:
				onePointCrossover(parent1, parent2, son1, son2);
				return;
			case CrossoverType::UNIFORM_CROSSOVER:
				uniformCrossover(parent1, parent2, son1, son2);
				return;
			case CrossoverType::PARTIALLY_MAPPED_CROSSOVER:
				partiallyMappedCrossover(parent1, parent2, son1, son2);
				return;
			case CrossoverType::SIMULATED_BINARY_CROSSOVER:
				simulatedBinaryCrossover(parent1, parent2, son1, son2);
				return;
			case CrossoverType::PRUNE_DELETE_GRAFT_CROSSOVER:
				pruneDeleteGraftCrossover(parent1, parent2, son1, son2);
				return;
		}
		
		throw "Unknown crossover type";
	} else {
#ifdef _NDEBUG
		printf("            No crossover. Replicating to children.\n");
#endif
		
		if (representationType == RepresentationType::TREE_REPRESENTATION) {
			son1->getTreeChromosome()->setRoot(parent1->getTreeChromosome()->getRoot()->clone());
			son2->getTreeChromosome()->setRoot(parent2->getTreeChromosome()->getRoot()->clone());
		} else {
			for (int i = 0; i < chromosomeLen; i++)
				if (representationType == RepresentationType::REAL_REPRESENTATION) {
					son1->getRealChromosome()[i] = parent1->getRealChromosome()[i];
					son2->getRealChromosome()[i] = parent2->getRealChromosome()[i];
				} else {
					son1->getIntChromosome()[i] = parent1->getIntChromosome()[i];
					son2->getIntChromosome()[i] = parent2->getIntChromosome()[i];
				}
		}
	}
}

void GeneticAlgorithm::simulatedBinaryCrossover(Individual *parent1, Individual *parent2, Individual *son1, Individual *son2) {
	double u = rndreal(0, 1);
	double nc = 2;
	double b;
	if (u <= 0.5)
		b = 2 * u;
	else
		b = 1 / (2 * (1 - u));
	b = pow(b, 1/(nc+1));
	
	for (int i = 0; i < chromosomeLen; i++) {
		double p1 = parent1->getRealChromosome()[i];
		double p2 = parent2->getRealChromosome()[i];
		double s1 = (p1 + p2 - b*(p2 - p1)) / 2;
		double s2 = (p1 + p2 + b*(p2 - p1)) / 2;
		
		son1->getRealChromosome()[i] = max(bounds[i][0], min(bounds[i][1], s1));
		son2->getRealChromosome()[i] = max(bounds[i][0], min(bounds[i][1], s2));
	}
}

TreeNode *GeneticAlgorithm::pdgCrossover(TreeNode *p1, TreeNode *p2, int n) {
	double prob = 1.0 / (2*n - 1);
	TreeNode *root = p1->clone();
	TreeNode *point = selectRandomSubtree(root, prob);
	
	int *ids = new int[n];
	int count = point->getSubtreeIds(ids);
	int *ids2 = new int[n];
	int count2 = p2->getSubtreeIds(ids2);
	for (int i = 0; i < count2; i++) {
		bool found = false;
		for (int j = 0; j < count && !found; j++)
			found |= ids2[i] == ids[j];
		if (!found) {
			count2--;
			for (int j = i; j < count2; j++)
				ids2[j] = ids2[j+1];
			i--;
		}
	}
	point->setSubtreeIds(ids2);
	
	delete [] ids;
	delete [] ids2;
	
	return root;
}

void GeneticAlgorithm::pruneDeleteGraftCrossover(Individual *parent1, Individual *parent2, Individual *son1, Individual *son2) {
	son1->getTreeChromosome()->setRoot(pdgCrossover(parent1->getTreeChromosome()->getRoot(), parent2->getTreeChromosome()->getRoot(), n));
	son2->getTreeChromosome()->setRoot(pdgCrossover(parent2->getTreeChromosome()->getRoot(), parent1->getTreeChromosome()->getRoot(), n));
}

void GeneticAlgorithm::invertIndividual(Individual *individual) {
	if (!flip(inversionProbability))
		return;
	
	int a = rndint(individual->getChromosomeLength());
	int b = rndint(individual->getChromosomeLength());
	if (a > b) {
		int tmp = a;
		a = b;
		b = tmp;
	}
	
	for (int i = a, j = b; i < j; i++, j--) {
		int tmp = individual->getIntChromosome()[i];
		individual->getIntChromosome()[i] = individual->getIntChromosome()[j];
		individual->getIntChromosome()[j] = tmp;
	}
}

void GeneticAlgorithm::partiallyMappedCrossover(Individual *parent1, Individual *parent2, Individual *son1, Individual *son2) {
	Individual *parents[2] = {parent1, parent2};
	Individual *sons[2] = {son1, son2};
	int *mappings[2];
	mappings[0] = new int[n];
	mappings[1] = new int[n];
	for (int k = 0; k < 2; k++)
		for (int i = 0; i < n; i++)
			mappings[k][i] = -1;
	
	for (int i = 0; i < n; i++)
		son1->getIntChromosome()[i] = son2->getIntChromosome()[i] = -1;

	int a = rndint(n);
	int b = rndint(n);
	if (a > b) {
		int tmp = a;
		a = b;
		b = tmp;
	}
	
	// Copy crossover segment
	for (int k = 0; k < 2; k++)
		for (int i = a; i <= b; i++) {
			int x = parents[k^1]->getIntChromosome()[i];
			sons[k]->getIntChromosome()[i] = x;
			mappings[k][x] = i;
		}
	
	// Assign unused values
	for (int k = 0; k < 2; k++)
		for (int i = 0; i < n; i++)
			if (i < a || i > b) {
				int x = parents[k]->getIntChromosome()[i];
				if (mappings[k][x] < 0) {
					mappings[k][x] = i;
					sons[k]->getIntChromosome()[i] = x;
				}
			}
	
	// Map missing values
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < n; i++)
			if (sons[k]->getIntChromosome()[i] < 0) {
				int x = parents[k]->getIntChromosome()[i];
				while (mappings[k][x] >= 0)
					x = sons[k^1]->getIntChromosome()[mappings[k][x]];
				
				mappings[k][x] = i;
				sons[k]->getIntChromosome()[i] = x;
			}
	}
	
	delete [] mappings[0];
	delete [] mappings[1];
}

void GeneticAlgorithm::uniformCrossover(Individual *parent1, Individual *parent2, 
		Individual *son1, Individual *son2) {
	bool ordered = true; // Says who the first parent is
	for (int i = 0; i < chromosomeLen; i++) {
		if (flip(0.5))
			ordered = !ordered;
		if (ordered) {
			son1->getIntChromosome()[i] = parent1->getIntChromosome()[i];
			son2->getIntChromosome()[i] = parent2->getIntChromosome()[i];
		} else {
			son1->getIntChromosome()[i] = parent2->getIntChromosome()[i];
			son2->getIntChromosome()[i] = parent1->getIntChromosome()[i];
		}
	}
}

void GeneticAlgorithm::onePointCrossover(Individual *parent1, Individual *parent2, 
	Individual *son1, Individual *son2) {
	int crossPoint = rndint(chromosomeLen+1);
	
#ifdef _NDEBUG
	printf("            Crosspoint at: %d\n", crossPoint);
#endif
	
	for (int i = 0; i < chromosomeLen; i++)
		if (i < crossPoint) {
			son1->getIntChromosome()[i] = parent1->getIntChromosome()[i];
			son2->getIntChromosome()[i] = parent2->getIntChromosome()[i];
		} else {
			son1->getIntChromosome()[i] = parent2->getIntChromosome()[i];
			son2->getIntChromosome()[i] = parent1->getIntChromosome()[i];
		}
	
	son1->setCrosspoint(crossPoint);
	son2->setCrosspoint(crossPoint);
}

/**
 * Implementation of the Fisher-Yates shuffling algorithm 
 * (http://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle)
 */
void GeneticAlgorithm::shuffle(int *x, int n) {
	for (int i = n-1; i >= 0; i--) {
		int j = rndint(i+1);
		int tmp = x[i];
		x[i] = x[j];
		x[j] = tmp;
	}
}
