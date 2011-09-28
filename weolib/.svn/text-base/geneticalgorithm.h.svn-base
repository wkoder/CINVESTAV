/*
 * GeneticAlgorithm.h
 *
 *  Created on: Jun 1, 2011
 *      Author: Moises Osorio
 */

#ifndef GENETICALGORITHM_H_
#define GENETICALGORITHM_H_

#include <vector>

#include "stats.h"
#include "individual.h"
#include "config.h"
#include "tree.h"

using namespace std;

class GeneticAlgorithm {
public:
	GeneticAlgorithm();
	virtual ~GeneticAlgorithm();
	
	void setElitism(bool elitism);
	void setMinimizer(bool minimizer);
	void setFaithDegree(double faithDegree);
	void setInstanceName(string instanceName);
	void setDirectory(string dir);
	
	void setMutationProbability(double probability);
	void setCrossoverProbability(double probability);
	void setInversionProbability(double probability);
	
	void setRepresentationType(RepresentationType type);
	void setSelectionType(SelectionType type);
	void setCrossoverType(CrossoverType type);
	void setMutationType(MutationType type);
	void setConstraintHandlingType(ConstraintHandlingType type);
	void setLocalSearchType(LocalSearchType type);

	void solve(double *xs, int n, int populationSize, double bounds[][2], int *precision, 
			int maxGenerations, double randomSeed, double (*f)(double *x), double (**g)(double *x), 
			int gn, double (**h)(double *x), int hn);
	void solve(double *xs, int n, int populationSize, double bounds[][2], int *precision, 
			int maxGenerations, double randomSeed, double (*f)(double *x));
	void solve(int *xs, int n, int populationSize, int maxGenerations, double randomSeed, 
			double (*f)(int *x));
	void solve(Tree*xs, int n, int populationSize, int maxGenerations, double randomSeed, 
				double (*f)(Tree *x));
		
private:
	int n;
	int nIneq;
	int nEq;
	int chromosomeLen;
	int populationSize;
	double (*bounds)[2];
	int *precision;
	int *varSize;
	int currentGeneration;
	int maxGenerations;
	double mutationProbability;
	double crossoverProbability;
	double inversionProbability;
	vector<Individual *> population;
	Stats *stats;
	double (*realfunction)(double *x);
	double (*intfunction)(int *x);
	double (*treefunction)(Tree *x);
	double (**equalityConstraints)(double *x);
	double (**inequalityConstraints)(double *x);
	double faithDegree;
	bool elitism;
	bool minimizer;
	RepresentationType representationType;
	SelectionType selectionType;
	CrossoverType crossoverType;
	MutationType mutationType;
	ConstraintHandlingType constraintHandlingType;
	LocalSearchType localSearchType;
	string instanceName;
	string directory;
	
	double temperature;
	
	void solve(double *realxs, int *intxs, Tree *treexs, int n, int populationSize, double bounds[][2], int *precision, 
				int maxGenerations, double randomSeed, double (*realf)(double *x), double (*intf)(int *x),
				double (*treef)(Tree *x), double (**g)(double *x), int gn, double (**h)(double *x), int hn);
	bool contains(Individual *individual, vector<Individual *> population);
	
	int calculateGeneSize();
	void setFitness(Individual *individual);
	vector<Individual *> generateRandomPopulation();
	vector<Individual *> generateNextGeneration();
	vector<Individual *> selectNIndividuals(int individuals);
	void mutateIndividual(Individual *individual);
	void crossoverInviduals(Individual *parent1, Individual *parent2, Individual *son1, Individual *son2);
	void invertIndividual(Individual *individual);
	void localSearchIndividual(Individual *individual);
	
	void simulatedAnnealing(Individual *individual);
	void nearestNeighborInterchange(Tree *tree);
	void subtreePruningRegrafting(Tree *tree);
	void treeBisectionReconnection(Tree *tree);
	
	void onePointCrossover(Individual *parent1, Individual *parent2, Individual *son1, Individual *son2);
	void uniformCrossover(Individual *parent1, Individual *parent2, Individual *son1, Individual *son2);
	void partiallyMappedCrossover(Individual *parent1, Individual *parent2, Individual *son1, Individual *son2);
	void simulatedBinaryCrossover(Individual *parent1, Individual *parent2, Individual *son1, Individual *son2);
	void pruneDeleteGraftCrossover(Individual *parent1, Individual *parent2, Individual *son1, Individual *son2);
	
	TreeNode *pdgCrossover(TreeNode *p1, TreeNode *p2, int n);
	
	void uniformMutation(Individual *ind);
	void reciprocalInterchangeMutation(Individual *ind);
	void parameterBasedMutation(Individual *ind);
	void scrambleMutation(Individual *ind);
	
	vector<Individual *> rouletteWheelSelection(int individuals);
	vector<Individual *> stochasticRemainderSelection(int individuals);
	vector<Individual *> deterministicBinaryTournamentSelection(int individuals);
	vector<Individual *> boltzmannSelection(int individuals);
	
	void faithBasedConstraintHandling(double *fitness);
	
	double getPopulationFitness(double *f, vector<Individual *> population);
	void getXFromIndividual(double *x, int *intx, Individual *individual);
	Individual *getBestIndividual(vector<Individual *> population);
	double getStandardDeviation(double *fitness, int n);
	void shuffle(int *x, int n);
	void setPositiveness(double *fitness);
	TreeNode *selectRandomSubtree(TreeNode *node, double prob);
};

#endif /* GENETICALGORITHM_H_ */
