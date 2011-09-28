/*
 * disjointset.h
 *
 *  Created on: May 1, 2011
 *      Author: Moises Osorio
 */

#ifndef DISJOINTSET_H_
#define DISJOINTSET_H_

#define MAX 500

typedef struct {
	int n;
	int p[MAX];
	int rank[MAX];
} disjointset;

// Creates a Disjoint Set data structure. See http://en.wikipedia.org/wiki/Disjoint-set_data_structure for more information.
disjointset* disjointset_init(int n);

// Unite the sets where x and y are contained.
void disjointset_union(disjointset* ds, int x, int y);

// Finds the set ID x is contained.
int disjointset_find(disjointset* ds, int x);

#endif /* DISJOINTSET_H_ */
