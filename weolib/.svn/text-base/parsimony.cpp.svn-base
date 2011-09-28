/*
 * parsimony.cpp
 *
 *  Created on: Jul 31, 2011
 *      Author: Moises Osorio
 */

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#include "geneticalgorithm.h"

using namespace std;

string SYMBOLS = "ACGT0123RYWSMKHBVDN-?";
int CODES[21] = {
  /* A */  1,
  /* C */  2,
  /* G */  4,
  /* T */  8,
  /* 0 */  1,
  /* 1 */  2,
  /* 2 */  4,
  /* 3 */  8,
  /* R */  5,
  /* Y */ 10,
  /* W */  9,
  /* S */  6,
  /* M */  3,
  /* K */ 12,
  /* H */ 11,
  /* B */ 14,
  /* V */  7,
  /* D */ 13,
  /* N */ 15,
  /* - */ 16,
  /* ? */ 255
};


vector<string> sequences;
int **sequenceCodes;
unsigned int n, len;
map<TreeNode *, int *> parsimony;
map<string, int> index;

int calculateParsimony(TreeNode *node) {
	if (node == NULL)
		return 0;
	
	int cost = 0;
	int *code = new int[len];
	if (node->getLeft() == NULL && node->getRight() == NULL) {
		for (unsigned int i = 0; i < len; i++)
			code[i] = sequenceCodes[node->getId()][i];
	} else {
		cost += calculateParsimony(node->getLeft());
		cost += calculateParsimony(node->getRight());
		
		int *a = parsimony[node->getLeft()];
		int *b = parsimony[node->getRight()];
		for (unsigned int i = 0; i < len; i++) {
			code[i] = a[i] & b[i];
			if (code[i] == 0) {
				cost++;
				code[i] = a[i] | b[i];
			}
		}
		
		parsimony.erase(node->getLeft());
		parsimony.erase(node->getRight());
		delete [] a;
		delete [] b;
	}

	parsimony.insert(pair<TreeNode *, int *>(node, code));
	return cost;
}

double f(Tree *tree) {
	double fx;
	
	if (!tree->isValid(n)) {
		printf("Invalid tree!\n");
		exit(EXIT_FAILURE);
	}
	
	fx = calculateParsimony(tree->getRoot());
	int *code = parsimony[tree->getRoot()];
	parsimony.clear();
	delete [] code;
	
	return fx;
}

void readPhylip(const char *fileName) {
	ifstream file;
	
	file.open(fileName);
	file >> n >> len;
	sequenceCodes = new int*[n];
	for (unsigned int i = 0; i < n; i++) {
		sequenceCodes[i] = new int[len];
		string name, s;
		file >> name;
		file >> s;
		index.insert(pair<string, int>(name, i));
		while (s.size() != len && name.size() < 10) {
			name += " " + s;
			file >> s;
		}
		
		if (s.size() != len) {
			printf("ERROR: Sequence of size %d instead of %d.\n", s.size(), len);
			exit(1);
		}
		
		sequences.push_back(name);
		for (unsigned int j = 0; j < len; j++) {
			size_t p = SYMBOLS.find(s[j], 0);
			if (p == string::npos) {
				printf("ERROR: Unrecognized symbol %c.\n", s[j]);
				exit(EXIT_FAILURE);
			}
			
			sequenceCodes[i][j] = CODES[p];
		}
	}
	
	file.close();
}

TreeNode *createSubtree(const char *data, int from, int to) {
	// Remove parentheses
	if (data[from] == '(') {
		from++;
		to--;
	}
	
	int comma;
	for (comma = from; comma <= to; comma++)
		if (data[comma] == ',')
			break;
	
	TreeNode *node;
	if (comma > to) {
		string name(data+from, to-from+1);
		node = new TreeNode(index[name]);
	} else {
		int sep, par;
		if (data[from] != '(')
			sep = comma-1;
		else
			for (sep = from+1, par=1; sep <= to; sep++) {
				if (data[sep] == '(')
					par++;
				else if (data[sep] == ')')
					par--;
				if (par == 0)
					break;
			}
		
		node = new TreeNode(-1);
		node->setLeft(createSubtree(data, from, sep));
		node->setRight(createSubtree(data, sep+2, to));
	}
	
	return node;
}

Tree *readNewick(const char *fileName) {
	ifstream file;
	file.open(fileName);
	
	string data;
	file >> data;
	
	Tree *tree = new Tree();
	tree->setRoot(createSubtree(data.c_str(), 0, data.size()-2));
	
	file.close();
	return tree;
}

string toString(TreeNode *root) {
	if (root->getLeft() == NULL && root->getRight() == NULL)
		return sequences[root->getId()];
	
	return "(" + toString(root->getLeft()) + "," + toString(root->getRight()) + ")";
}

/**
 * Entry point for the program.
 */
int main(int argc, char **argv) {
#ifdef VERIFY
	string instance(argv[1]);
	string treefile(argv[2]);
	
	readPhylip(("instances/" + instance + ".txt").c_str());
	Tree *tree = readNewick(treefile.c_str());
	
	printf("Parsimony score: %d\n", (int)round(f(tree)));
	
	delete tree;
#else
	GeneticAlgorithm ga;
	Tree xs;
	double mutationRate, crossoverProbability, randomSeed;
	int maxGenerations, populationSize;

	string search(argv[1]);
	string instance(argv[2]);
	
	readPhylip(("instances/" + instance + ".txt").c_str());
	
	if (argc >= 4) // ID
		instance += string("-") + argv[3];
	
	printf("Population size: ");
	scanf("%d", &populationSize);
	printf("Maximum number of generations: ");
	scanf("%d", &maxGenerations);
	printf("Mutation rate (0..1): ");
	scanf("%lf", &mutationRate);
	printf("Crossover probability (0..1): ");
	scanf("%lf", &crossoverProbability);
	printf("Random seed: ");
	scanf("%lf", &randomSeed);
	
	// Solve problem
	ga.setCrossoverProbability(crossoverProbability);
	ga.setMutationProbability(mutationRate);
	ga.setElitism(true);
	ga.setMinimizer(true);
	ga.setRepresentationType(RepresentationType::TREE_REPRESENTATION);
	ga.setSelectionType(SelectionType::UNIFORM_ROULETTE_WHEEL_SELECTION);
	ga.setCrossoverType(CrossoverType::PRUNE_DELETE_GRAFT_CROSSOVER);
	ga.setMutationType(MutationType::SCRAMBLE_MUTATION);
	ga.setInstanceName(instance);
	ga.setDirectory(search);

	if (search == "NNI")
		ga.setLocalSearchType(LocalSearchType::NEAREST_NEIGHBOR_INTERCHANGE_SEARCH);
	else if (search == "SPR")
		ga.setLocalSearchType(LocalSearchType::SUBTREE_PRUNING_REGRAFTING_SEARCH);
	else if (search == "TBR")
		ga.setLocalSearchType(LocalSearchType::TREE_BISECTION_RECONNECTION_SEARCH);
	else
		throw "Unknown local search!";
	
	system(("mkdir -p " + search).c_str());
	ga.solve(&xs, n, populationSize, maxGenerations, randomSeed, f);
	double fxs = f(&xs);
	
	printf("x* = %s\n", toString(xs.getRoot()).c_str());
	printf("f(x*) = %.0f\n", fxs);
	
	ofstream newickfile;
	newickfile.open((search + "/" + instance + ".newick").c_str());
	newickfile << toString(xs.getRoot()).c_str() << ";\n";
	newickfile.close();
#endif
	
	return EXIT_SUCCESS;

}
