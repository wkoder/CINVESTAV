/*
 * simplecenterdiff.c
 *
 *  Created on: Jun 19, 2011
 *      Author: viri
 */
#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"
#include "gram_schmidt.h"

#define maxValue 30;
extern int n,tam;
extern double *x;

extern double h, alfa, beta, ua, ub;

/**
 * function by calculate the matrix Q.
 */
double functionQ() {
	static int i = 0;
	double value;
	
	if (x[i] < -0.5 || x[i] > 0.5) {
		value = maxValue;
	} else
		value = 0;
	
//	if ((i == 0 || i == tam - 1) && (ua != 0 && ub != 0))
//		value /= 2;
	i++;
	
	return value;
}

/**
 * Function by calculate the diagonal down and up of a tridiagonal matrix T.
 */
double functionT() {
	return -1;
}

/**
 * Function by calculate diagonal principal of matrix T.
 */
double functionT2() {
	static int i = 0;
	double value;
	value = 2;
	
	if (i == 0 && ua != 0 && ub != 0)
//		value = (h / alfa) + 1;
		value = 2*((h / alfa) + 1);
	else if (i == tam - 1 && ua != 0 && ub != 0)
//		value = 1 - (h / beta);
		value = 2*(1 - (h / beta));
	i++;
	
	return value;
}

/**
 * Function by calculate matrix M.
 */
double functionM() {
	static int i = 0;
	double values;
	values = 1;
	
	if ((i == 0 || i == tam - 1) && (ua != 0 && ub != 0))
		values = 0.5;
	i++;
	
	return values;
}

int RQP(int tam, double **A, double *l, double **v) {
	double **Q, **R, **matAux, **RQ;
	int i, iter;

	if (!isSymmetricMatrix(A, tam)) {
		printf("A is not symmetric\n");
		return 0;
	}
	
	createMatrix(&Q,tam,tam);
	createMatrix(&R,tam,tam);
	createMatrix(&RQ, tam, tam);
	createMatrix(&matAux, tam, tam);
	unitMatrix(tam, v);

	iter = 0;
	while (iter++ < 1000) {
		// QR = A
		matrixQ(tam, A, Q);
		matrixR(tam, Q, A, R);

		multiplicationMatrix(tam, tam, R, Q, RQ);

		// P = PQ
		multiplicationMatrix(tam, tam, v, Q, matAux);
		copyMatrix(tam, tam, matAux, v);

		if (isUpperTriangular(tam, RQ))
			break;

		copyMatrix(tam, tam, RQ, A);
	}
	
	for (i = 0; i < tam; i++)
		l[i] = RQ[i][i];

	destroyMatrix(&Q, tam, tam);
	destroyMatrix(&R, tam, tam);
	destroyMatrix(&RQ, tam, tam);
	destroyMatrix(&matAux, tam, tam);
	
	return 1;
}
