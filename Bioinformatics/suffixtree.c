/*
 * suffixtree.c
 *
 *  Created on: Jun 8, 2011
 *      Author: Moises Osorio
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 1001
#define ALPHA_SIZE 26
#define ALPHA_BASE 'a'
#define INF 1<<30

typedef struct Node {
	int minchild;
	int degree;
	struct Node *children[ALPHA_SIZE];
} Node;

char string[MAX_SIZE];
char suffix[MAX_SIZE];
Node pool[MAX_SIZE*MAX_SIZE];
int poolPos;

Node *createNode() {
	int i;
	Node *n;
//	n = (Node *)malloc(sizeof(Node));
	n = &pool[poolPos++];
	n->minchild = -1;
	n->degree = 0;
	for (i = 0; i < ALPHA_SIZE; i++)
		n->children[i] = NULL;
	
	return n;
}

void destroyNode(Node *node) {
	int i;
	if (node == NULL)
		return;
	
	for (i = 0; i < ALPHA_SIZE; i++)
		destroyNode(node->children[i]);
	
	free(node);
}

void addToTrie(Node *node, int from, int to) {
	int ch;

	node->degree++;
	if (from == to)
		return;
	
	ch = string[from] - ALPHA_BASE;
	if (node->children[ch] == NULL)
		node->children[ch] = createNode();
	
	addToTrie(node->children[ch], from+1, to);
}

int findSuffix(Node *node) {
	int min, i, m;
	
	if (node == NULL)
		return INF;
	if (node->degree == 1)
		return 0;
	
	min = INF;
	for (i = 0; i < ALPHA_SIZE; i++) {
		m = findSuffix(node->children[i]);
		if (m < min) {
			min = m;
			node->minchild = i;
		}
	}
	
	return min + 1;
}

void getSuffix(Node *node, int at) {
	if (node->minchild < 0) {
		suffix[at] = 0;
		return;
	}
	
	suffix[at] = ALPHA_BASE + node->minchild;
	getSuffix(node->children[node->minchild], at+1);
}

int main(int argc, char **argv) {
	int i, n;
	Node *root;
	while (scanf("%s", string) != EOF) {
		poolPos = 0;
		n = strlen(string);
		root = createNode();
		for (i = 0; i < n; i++)
			addToTrie(root, i, n);
		
		findSuffix(root);
		getSuffix(root, 0);
		printf("%s\n", suffix);
		
//		destroyNode(root);
	}
	
	return EXIT_SUCCESS;
}
