/*
 * givens.c
 *
 *  Created on: Aug 18, 2011
 *      Author: Moises Osorio
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "matrix.h"

void givensFactorization(double **A, double **Q, double **R, int tam) {
	int i, j, k;
	double **tmp;
	double b, c, s, x, y;
	
	createMatrix(&tmp, tam, tam);
	
	copyMatrix(tam, tam, A, R);
	for (j = 0; j < tam-1; j++) {
		i = j + 1;
		b = sqrt(R[i-1][j]*R[i-1][j] + R[i][j]*R[i][j]);
		if (b < EPS)
			continue;
		c = R[i-1][j] / b;
		s = R[i][j] / b;
		
		for (k = j; k <= tam; k++) {
			x = c*R[i-1][k] + s*R[i][k];
			y = -s*R[i-1][k] + c*R[i][k];
			R[i][k] = y;
			R[i-1][k] = x;
		}
	}
	
	for (i = 0; i < tam; i++)
		for (j = 0; j < i; j++)
			R[i][j] = 0;
	
	inverseRMatrix(tam, R, tmp);
	multiplyMatrix(tam, tam, tam, A, tmp, Q);
	
	destroyMatrix(&tmp, tam, tam);
}

void givens(double **A, double *l, double **v, int tam) {
	int i, iter;
	double **R, **Q, **tmp;
	createMatrix(&Q, tam, tam);
	createMatrix(&R, tam, tam);
	createMatrix(&tmp, tam, tam);
	
	unitMatrix(tam, v);
	iter = 0;
	while (iter++ < 1000 && !isUpperTriangular(tam, A)) {
		// QR = A
		givensFactorization(A, Q, R, tam);
		
		multiplyMatrix(tam, tam, tam, R, Q, A);
		
		// v = vQ
		multiplyMatrix(tam, tam, tam, v, Q, tmp);
		copyMatrix(tam, tam, tmp, v);
	}
	
	for (i = 0; i < tam; i++)
		l[i] = A[i][i];
	
	destroyMatrix(&Q, tam, tam);
//	destroyMatrix(&R, tam, tam);
//	destroyMatrix(&tmp, tam, tam);
}
