/*
 * disjointset.c	See http://en.wikipedia.org/wiki/Disjoint-set_data_structure for more information about this data structure.
 *
 *  Created on: May 1, 2011
 *      Author: Moises Osorio
 */

#include "disjointset.h"
#include <stdio.h>
#include <stdlib.h>

disjointset* disjointset_init(int n)
{
	int i;
	disjointset* ds;

	ds = malloc(sizeof(disjointset));
	ds->n = n;
	for (i = 0; i < n; i++) { // First each element is a set
		ds->p[i] = i;
		ds->rank[i] = 0;
	}

	return ds;
}

// Links two sets
void disjointset_link(disjointset* ds, int x, int y)
{
	if (ds->rank[x] > ds->rank[y])
		ds->p[y] = x;
	else {
		ds->p[x] = y;
		if (ds->rank[x] == ds->rank[y])
			ds->rank[y]++;
	}
}

void disjointset_union(disjointset* ds, int x, int y)
{
	link(disjointset_find(ds, x), disjointset_find(ds, y));
}

int disjointset_find(disjointset* ds, int x){
	if (x != ds->p[x])
		ds->p[x] = disjointset_find(ds, ds->p[x]);

	return ds->p[x];
}
