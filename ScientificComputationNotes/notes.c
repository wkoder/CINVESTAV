/*
 * notes.c
 *
 *  Created on: Jul 29, 2011
 *      Author: Moises Osorio
 */

#include <stdlib.h>
#include <omp.h>

#include "notes.h"

#define NT 4

double *unitMatrix_create(int n) {
	int i;
	double *a;
	
	omp_set_num_threads(NT);

	a = (double *) calloc(n*n, sizeof(double));
	
#pragma omp parallel for
	for (i = 0; i < n; i++)
		a[i*n + i] = 1;
	
	return a;
}


void unitMatrix_free(double *a) {
	free(a);
}

double *tridiagonalMatrix_DF(int n) {
	int i;
	double *a;
	
	omp_set_num_threads(NT);
	
	a = (double *) calloc(n*n, sizeof(double));
#pragma omp parallel for
	for (i = 0; i < n; i++) {
		a[i*n + i] = 2;
		if (i > 1)
			a[i*n + i-1] = 1;
		if (i < n-1)
			a[i*n + i+1] = -1;
	}
	
	return a;
}

void sumQToTridiagonal(double *a, int n, double (*q)(double), double xmin, double xmax) {
	int i;
	double x, dx;
	
	dx = (xmax - xmin) / n;
	omp_set_num_threads(NT);
	
	// TODO missing code
}

void LUFactorization(double *t, double *l, double *u, int n) {
	int i;
	double tmp;
	
	tmp = 0;
	for (i = 0; i < n; i++) {
		tmp = i > 0 ? u[(i-1)*n + i] * l[i*n + i-1] : 0;
		u[i*n + i] = t[i*n + i] - tmp;
		if (i < n-1) {
			u[i*n + i+1] = t[i*n + i+1];
			l[(i+1)*n + i] = t[(i+1)*n + i] / u[i*n + i];
		}
	}
}
