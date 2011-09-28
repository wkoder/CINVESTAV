/*
 * smartsuffixtree.c
 *
 *  Created on: Jun 8, 2011
 *      Author: Moises Osorio
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 1001
#define INF 1<<30
#define ALPHA_SIZE 28
#define LEN(k) (t[k]->r - t[k]->l)

typedef struct Node {
	int l, r, parent, link;
	int degree, minchild;
	int next[ALPHA_SIZE];
} Node;

typedef struct State {
	int v, pos;
} State;

char s[MAX_SIZE];
char suffix[MAX_SIZE];

Node nodePool[4*MAX_SIZE];
int nodePoolPos;
State statePool[4*MAX_SIZE];
int statePoolPos;

Node *t[4*MAX_SIZE];
State *ptr;
int size;
int n;

void printSuffixTree(int pos, int level) {
	int i;
	Node *node;
	
	node = t[pos];
	for (i = 0; i < level; i++)
		printf(" ");
	printf("+");
	for (i = node->l; i < node->r; i++)
		printf("%c", s[i]);
	
	printf(" (%d)\n", node->degree);
	
	for (i = 0; i < ALPHA_SIZE; i++)
		if (node->next[i] != -1)
			printSuffixTree(node->next[i], level + LEN(pos)+1);
}

Node *createNode(int l, int r, int parent) {
	int i;
	Node *node;
	
	node = &nodePool[nodePoolPos++];
	node->l = l;
	node->r = r;
	node->parent = parent;
	node->link = -1;
	node->degree = 1;
	node->minchild = -1;
	for (i = 0; i < ALPHA_SIZE; i++)
		node->next[i] = -1;
	
	return node;
}

State *createState(int v, int pos) {
	State *state;
	state = &statePool[statePoolPos++];
	state->v = v;
	state->pos = pos;
	
	return state;
}

int charInd(char c) {
	if ('a' <= c && c <= 'z')
		return c - 'a';
	
	if (c == '.')
		return 26;
	
	return 27;
}

State *go(State *st, int l, int r) {
	int d;
	while (l < r) {
		if (st->pos == LEN(st->v)) {
//			t[st->v]->degree++;
			st = createState(t[st->v]->next[charInd(s[l])], 0);
			if (st->v == -1)
				return st;
//			else
//				t[st->v]->degree++;
		} else {
			if (s[l] != s[t[st->v]->l + st->pos])
				return createState(-1, -1);
			
			d = LEN(st->v) - st->pos;
			if (r-l < d) {
//				t[st->v]->degree++;
				d = r-l;
			}
			
			l += d;
			st->pos += d;
		}
	}
	
	return st;
}

int split(State *st) {
	int nv;
	if (st->pos == LEN(st->v))
		return st->v;
	
	if (st->pos == 0)
		return t[st->v]->parent;
	
	nv = size++;
	t[nv] = createNode(t[st->v]->l, t[st->v]->l + st->pos, t[st->v]->parent);
	t[t[st->v]->parent]->next[charInd(s[t[st->v]->l])] = nv;
	t[t[st->v]->parent]->degree++;
	t[nv]->next[charInd(s[t[st->v]->l + st->pos])] = st->v;
	t[nv]->degree++;
	t[st->v]->parent = nv;
	t[st->v]->l += st->pos;
	
	return nv;
}

int link(int v) {
	int p;
	State *st;
	if (t[v]->link != -1)
		return t[v]->link;
	
	if (v == 0)
		return 0;
	
	p = t[v]->parent;
	st = go(createState(link(p), LEN(link(p))), t[v]->l + (t[v]->parent == 0 ? 1 : 0), t[v]->r);
	t[v]->link = split(st);
	
	return t[v]->link;
}

void treeExtend(int i) {
	int mid;
	State *nptr;
	while (1) {
		nptr = go(ptr, i, i+1);
		if (nptr->v != -1) {
			ptr = nptr;
//			t[ptr->v]->degree++;
			break;
		}
		
		mid = split(ptr);
		t[size] = createNode(i, n, mid);
		t[mid]->next[charInd(s[i])] = size++;
		ptr = createState(link(mid), LEN(link(mid)));
//		t[ptr->v]->degree++;
		if (mid == 0)
			break;
	}
	
	printSuffixTree(0, 0);
	printf("\n");
	
//	printf("Extending %d (%c) ended in vertex %d from %d to %d\n", i, s[i], ptr->v, t[ptr->v]->l, t[ptr->v]->r-1);
//	t[ptr->v]->degree++;
}

void createSuffixTree(int m) {
	int i;
	
	n = m;
	size = 1;
	ptr = createState(0, 0);
	for (i = 0; i < 2*n+1; i++)
		t[i] = createNode(0, 0, 0);
	
	for (i = 0; i < n; i++)
		treeExtend(i);
}

int findSuffix(int pos) {
	int min, i, m;
	Node *node;
	
	node = t[pos];
	min = INF;
	for (i = 0; i < ALPHA_SIZE; i++)
		if (node->next[i] != -1) {
			m = findSuffix(node->next[i]);
			if (m < min) {
				min = m;
				node->minchild = i;
			}
		}
	
	if (min == INF && node->degree == 1)
		return 1;
	return min + LEN(pos);
}

void getSuffix(int pos, int at) {
	Node *node;
	int i;
	
	node = t[pos];
	if (node->minchild < 0) {
		suffix[at++] = s[node->l];
		suffix[at] = 0;
		return;
	}

	for (i = node->l; i < node->r; i++)
		suffix[at++] = s[i];

	getSuffix(node->next[node->minchild], at);
}

int main(int argc, char **argv) {
	int n, min;
	while (scanf("%s", s) != EOF) {
		nodePoolPos = 0;
		statePoolPos = 0;
		n = strlen(s);
		
		printf("%d\n", n);
		createSuffixTree(n);
		
		printSuffixTree(0, 0);
		min = findSuffix(0);
		if (min > 1)
			printf("%s\n", s);
		else {
			getSuffix(0, 0);
			printf("%s\n", suffix);
		}
	}
	
	return EXIT_SUCCESS;
}
